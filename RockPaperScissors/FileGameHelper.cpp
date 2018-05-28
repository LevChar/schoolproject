#include "FileGameHelper.h"



FileGameHelper::FileGameHelper()
{
}


FileGameHelper::~FileGameHelper()
{
}

bool FileGameHelper::validateFileOpened(ifstream& file, string filename) {

	if (!file.is_open()) {

		cout << "Could not open file: " << filename << endl;
		return false;
	}
	return true;
}

char FileGameHelper::readchar(ifstream& file) {

	char charToFind = getNextchar(file);

	if (charToFind == EOF || charToFind == '\n' || charToFind == ' ')
		return EOF;

	if (charToFind > 'A' && charToFind < 'Z')
		return charToFind;
	else if (charToFind > 'a' && charToFind < 'z')
		return toupper(charToFind);
	else
		return THIS_IS_NOT_A_LETTER;
}

int FileGameHelper::readPositioningFileFromDirectory(string fileName, int playerNumber, BoardManager* boardManager) {

	char piece, pieceValidation;
	bool searchJockerRep = false;
	int row, col, current_read_state = READ_PIECE, input_validation = SUCCESS;
	ifstream inFile(fileName);

	if (!validateFileOpened(inFile, fileName))
		return FILE1_OPEN_ERROR;

	resetForNewFileSon();

	while (continueReadingFile) {

		switch (current_read_state) {

		case (READ_PIECE):

			if ((piece = readchar(inFile)) != EOF && piece != THIS_IS_NOT_A_LETTER) {

				if (piece == 'J')
					searchJockerRep = true;

				current_read_state = READ_COL;
				pieceValidation = piece;

				if (!checkNextChar(inFile, "  \n"))
					return 	GamePlayHelper::getNumOfRowsRead();
			}

			else {

				if (piece == THIS_IS_NOT_A_LETTER)
					return GamePlayHelper::getNumOfRowsRead();
				else
					continueReadingFile = false;
			}

			break;

		case (READ_COL):

			if ((col = readNumber(inFile)) != EOF && col != THIS_IS_NOT_A_DIGIT) {
				current_read_state = READ_ROW;

				if (!checkNextChar(inFile, "  \n"))
					return 	GamePlayHelper::getNumOfRowsRead();
			}
			else
				return 	GamePlayHelper::getNumOfRowsRead();

			break;

		case (READ_ROW):

			if ((row = readNumber(inFile)) != EOF && row != THIS_IS_NOT_A_DIGIT) {

				if (!searchJockerRep)
					current_read_state = SEND_DATA;
				else
					current_read_state = READ_PEACE_AFTER_J;

				if (!checkNextChar(inFile, "  \n") && inFile.eof())
					return 	GamePlayHelper::getNumOfRowsRead();
			}

			else
				return 	GamePlayHelper::getNumOfRowsRead();
			break;

		case(READ_PEACE_AFTER_J):

			if ((piece = readchar(inFile)) != EOF && piece != THIS_IS_NOT_A_LETTER) {

				searchJockerRep = false;
				current_read_state = SEND_DATA;

				if (!checkNextChar(inFile, "  \n") && inFile.good())
					return GamePlayHelper::getNumOfRowsRead();
			}

			else
				return 	GamePlayHelper::getNumOfRowsRead();;
			break;

		case (SEND_DATA):

			input_validation = validatePiece(pieceValidation, col, row);

			if (!input_validation) {

				//if player try to put 2 pices @ the same square we will get false here
				continueReadingFile = boardManager->loadPosFromFile(piece, col, row, playerNumber, pieceValidation);

				if (!continueReadingFile) {

					inFile.close();
					return GamePlayHelper::getNumOfRowsRead();
				}

				if (checkEnterBeforeNextLine(inFile)) {

					current_read_state = READ_PIECE;
					GamePlayHelper::increaseNumOfRowsRead();
				}

				else {

					inFile.close();
					return GamePlayHelper::getNumOfRowsRead();

				}

			}

			else {

				inFile.close();
				return input_validation;
			}
		}
	}

	inFile.close();

	if (checkFlagwasSet())
		return SUCCESS;

	else
		return NO_FLAG_WAS_SET;
}

int FileGameHelper::readNumber(ifstream& file) {

	int result = 0, temp;
	char numTofind = getNextchar(file);

	if (numTofind == EOF)
		return EOF;

	else if (numTofind > '9' || numTofind < '0')
		return THIS_IS_NOT_A_DIGIT;

	while (!file.eof() && numTofind <= '9' && numTofind >= '0') {

		temp = numTofind - '0';
		result *= 10;
		result += temp;
		file.get(numTofind);
	}

	file.unget();
	return result;
}

bool FileGameHelper::checkNextChar(ifstream& file, const char* charTocheck) {

	char ActualnextChar;
	size_t len = strlen(charTocheck);

	file.get(ActualnextChar);

	if (file.good())

		for (int i = 0; i< len; i++) {
			if (charTocheck[i] == ActualnextChar) {
				file.unget();
				return true;
			}
		}

	return false;
}

char FileGameHelper::getNextchar(ifstream& file) {

	char ch = EOF;

	do {

		file.get(ch);

	} while (!file.eof() && (ch == ' ' || ch == '\n'));


	return ch;
}

void FileGameHelper::resetForNewFileSon() {

	GamePlayHelper::reset();

	GamePlayHelper::setNumOfRowsRead(1);
	current_read_state;
	current_read_state = READ_PIECE;
	continueReadingFile = true;
}

bool FileGameHelper::checkEnterBeforeNextLine(ifstream& file) {

	char ch = EOF;
	bool gotEnter = false;
	int counter = 0;

	do {

		file.get(ch);
		counter++;

		if (ch == '\n') {
			gotEnter = true;
			break;
		}
	} while (!file.eof() && (ch == ' '));


	if (ch != '\n' && gotEnter) {

		for (int i = 0; i < counter; i++)
			file.unget();

		return true;
	}

	else if (ch == '\n' || ch == EOF)
		return true;
	else
		return false;
}

bool FileGameHelper::checkFlagwasSetSon() {

	return GamePlayHelper::checkFlagwasSet();
}

int FileGameHelper::readMoveFileFromDirectory(string _fileName1, string _fileName2, int& playerWithError, BoardManager* boardManager, int& innerIssue, int & _weGotAWinner) {

	int numOfArgsRd = 0, row1Player = 1, row2Player = 1, current_read_state = READ_PIECE;
	int moveAndJockerData[6] = { -1,-1,-1,-1,-1,-1 };
	char tempBuff, jNewRep = -1;
	bool switchPlayer = false;
	ifstream inFile1(_fileName1), inFile2(_fileName2), *currFile = nullptr;

	if (!validateFileOpened(inFile1, _fileName1) || !validateFileOpened(inFile2, _fileName2))
		return ((!validateFileOpened(inFile1, _fileName1)) && !validateFileOpened(inFile2, _fileName2)) ? BOTH_FILES_OPEN_ERROR :
		!validateFileOpened(inFile1, _fileName1) ? FILE1_OPEN_ERROR : FILE2_OPEN_ERROR;

	resetForNewData(moveAndJockerData, numOfArgsRd, jNewRep, current_read_state);

	while (continueReadingFile) {

		if (current_read_state != SEND_MOVE_DATA)
			continueReadingFile = checkAndSetNextRead(inFile1, inFile2, currFile, row1Player, row2Player, switchPlayer);

		switch (current_read_state) {

		case(RS1):
		case(RS2):
		case(RD1):
		case(RD2):
		case(RJPOS1):
		case(RJPOS2):

			if ((moveAndJockerData[numOfArgsRd] = readNumber(*currFile)) != EOF && moveAndJockerData[numOfArgsRd] != THIS_IS_NOT_A_DIGIT) {

				current_read_state++;
				numOfArgsRd++;

				if (!checkNextChar((*currFile), "  \n") && (*currFile).good())
					return 	GamePlayHelper::getNumOfRowsRead();
			}

			//the next Char isn't digit (while it should be) or maybe it's EOF
			else {

				//isn't digit or eof - don't matter in the middle of a move - its error
				if (current_read_state != RS1)
					return 	GamePlayHelper::getNumOfRowsRead();

				//the file of the current player ended
				else if ((moveAndJockerData[numOfArgsRd] == EOF) && current_read_state == RS1) {

					switchPlayer = true;
					continueReadingFile = checkAndSetNextRead(inFile1, inFile2, currFile, row1Player, row2Player, switchPlayer);
				}

				//not a digit
				else
					return 	GamePlayHelper::getNumOfRowsRead();
			}

			break;

		case(CHECK_FOR_JOKER):

			tempBuff = getNextchar(*currFile);

			if (tempBuff == 'J') {

				(*currFile).get(tempBuff);
				if (tempBuff == ':') {
					current_read_state++;
					if (!checkNextChar((*currFile), " "))
						return 	GamePlayHelper::getNumOfRowsRead();
				}

				else
					return 	GamePlayHelper::getNumOfRowsRead();
			}

			else {

				if (isalpha(tempBuff))
					return 	GamePlayHelper::getNumOfRowsRead();


				else if (isdigit(tempBuff)) {

					(*currFile).unget();
					current_read_state = SEND_MOVE_DATA;
				}

				else if (tempBuff == EOF || tempBuff == '\n')
					current_read_state = SEND_MOVE_DATA;
			}

			break;

		case(RJNEWREP):

			if ((jNewRep = readchar(*currFile)) != EOF && jNewRep != THIS_IS_NOT_A_LETTER) {

				current_read_state++;
				numOfArgsRd++;

				if (!checkNextChar((*currFile), " \n") && !(*currFile).eof())
					return 	GamePlayHelper::getNumOfRowsRead();
			}

			else
				return 	GamePlayHelper::getNumOfRowsRead();

		case(SEND_MOVE_DATA):

			if (GamePlayHelper::validateMove(moveAndJockerData, jNewRep) != SUCCESS)
				return GamePlayHelper::getNumOfRowsRead();

			if (_weGotAWinner == -1) {
				if (GamePlayHelper::checkMoveApplicable(moveAndJockerData)) { // TODO we need to return an error for inapplicable move.
															  //cout << "Player" << FileHelper::current_player << " "  <<moveAndJockerData[0] << " " << moveAndJockerData[1] << " " << moveAndJockerData[2] << " " << moveAndJockerData[3] << " " << moveAndJockerData[4] << " " << moveAndJockerData[5] << " " << moveAndJockerData[6] << endl;
					innerIssue = boardManager->checkMovePiece(moveAndJockerData, GamePlayHelper::getCurrentPlayer(), jNewRep, _weGotAWinner);
				}
				else {
					return 	GamePlayHelper::getNumOfRowsRead();
				}
				// here return the line number and the error.
			}

			GamePlayHelper::getNumOfRowsRead();
			switchPlayer = true;
			resetForNewData(moveAndJockerData, numOfArgsRd, jNewRep, current_read_state);

			break;
		}
	}


	return SUCCESS;

}


bool FileGameHelper::checkAndSetNextRead(ifstream& file1, ifstream& file2, ifstream*& currentFile, int& r_of_p1, int& r_of_p2, bool& switch_player) {

	//The function was called but switch_player is set to false (no actual need to change player). 
	//-----------> 3 options: 1. EOF 2. need to set the first player 3. continue input <----------

	if (!switch_player) {

		//1.set the first time
		if (currentFile == nullptr) {

			if (!file1.eof()) {
				GamePlayHelper::setCurrentPlayer(1);
				r_of_p2 = GamePlayHelper::getNumOfRowsRead();;
				GamePlayHelper::setNumOfRowsRead(r_of_p1);
				currentFile = &file1;

			}

			else {
				GamePlayHelper::setCurrentPlayer(2);
				r_of_p1 = GamePlayHelper::getNumOfRowsRead();
				GamePlayHelper::setNumOfRowsRead(r_of_p2);
				
				currentFile = &file2;
			}

			return true;
		}

		//2.check EOF
		if (currentFile->eof()) {

			if (file1.eof() && file2.eof())
				return false;

			else if (currentFile == &file1) {

				if (file2.eof())
					return false;

				else {

					GamePlayHelper::setCurrentPlayer(2);
					r_of_p1 = GamePlayHelper::getNumOfRowsRead();
					GamePlayHelper::setNumOfRowsRead(r_of_p2);
					currentFile = &file2;
				}
			}

			else if (currentFile == &file2) {

				if (file1.eof())
					return false;

				else {

					GamePlayHelper::setCurrentPlayer(1);
					r_of_p2 = GamePlayHelper::getNumOfRowsRead();
					GamePlayHelper::setNumOfRowsRead(r_of_p1);
					currentFile = &file1;
				}
			}
		}

		//3. just continue reading the current file
		else
			return true;
	}

	//switch_player is on - something\someone requested to read a new player
	else {

		//both of the files are finished
		if (!file1.good() && !file2.good())
			return false;

		//asked to chenge the file but the other file is finished, stay @ current file
		if (currentFile == &file1 && !file2.good() || currentFile == &file2 && !file1.good()) {

			switch_player = false;
			return true;

		}

		//switch from 1 to 2
		if (currentFile == &file1 && file2.good()) {

			GamePlayHelper::setCurrentPlayer(2);
			r_of_p1 = GamePlayHelper::getNumOfRowsRead();
			GamePlayHelper::setNumOfRowsRead(r_of_p2);
			currentFile = &file2;
			switch_player = false;
			return true;
		}


		//switch from 2 to 1
		if (currentFile == &file2 && file1.good()) {

			GamePlayHelper::setCurrentPlayer(1);
			r_of_p2 = GamePlayHelper::getNumOfRowsRead();
			GamePlayHelper::setNumOfRowsRead(r_of_p1);
			currentFile = &file1;
			switch_player = false;
			return true;
		}
	}
}

void FileGameHelper::resetForNewDataSon(int* result_array, int& argumentCounter, char& jNewRep, int& current_state) {

	GamePlayHelper::resetForNewData(result_array, argumentCounter, jNewRep, current_state);
	continueReadingFile = true;
}