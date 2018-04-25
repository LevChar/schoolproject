#include "FileHelper.h"
#include "General.h"
#include <fstream>

FileHelper::FileHelper() {}
FileHelper::~FileHelper() {}


char FileHelper::getNextchar(ifstream& file) {

	char ch = EOF;

	do {

		file.get(ch);

	} while (!file.eof() && (ch == ' ' || ch == '\n'));


	return ch;
}

int FileHelper::readNumber(ifstream& file) {

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

char FileHelper::readchar(ifstream& file) {

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

bool FileHelper::checkNextChar(ifstream& file, const char* charTocheck) {

	char ActualnextChar;
	int len = strlen(charTocheck);

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

bool FileHelper::validateFileOpened(ifstream& file, string filename) {

	if (!file.is_open()) {

		cout << "Could not open file: " << filename << endl;
		return false;
	}
	return true;
}

int FileHelper::readPositioningFileFromDirectory(string fileName, int playerNumber, BoardManager* boardManager) {

	char piece, pieceValidation;
	bool searchJockerRep = false;
	int row, col, current_read_state = READ_PIECE, input_validation = SUCCESS;
	ifstream inFile(fileName);

	if (!validateFileOpened(inFile, fileName))
		return FILE1_OPEN_ERROR;

	resetForNewFile();

	while (continueReadingFile) {

		switch (current_read_state) {

		case (READ_PIECE):

			if ((piece = readchar(inFile)) != EOF && piece != THIS_IS_NOT_A_LETTER) {

				if (piece == 'J')
					searchJockerRep = true;

				current_read_state = READ_COL;
				pieceValidation = piece;

				if (!checkNextChar(inFile, "  \n"))
					return 	FileHelper::numOfRowsRead;
			}

			else {

				if (piece == THIS_IS_NOT_A_LETTER)
					return 	FileHelper::numOfRowsRead;
				else
					continueReadingFile = false;
			}

			break;

		case (READ_COL):

			if ((col = readNumber(inFile)) != EOF && col != THIS_IS_NOT_A_DIGIT) {
				current_read_state = READ_ROW;

				if (!checkNextChar(inFile, "  \n"))
					return 	FileHelper::numOfRowsRead;
			}
			else
				return 	FileHelper::numOfRowsRead;

			break;

		case (READ_ROW):

			if ((row = readNumber(inFile)) != EOF && row != THIS_IS_NOT_A_DIGIT) {

				if (!searchJockerRep)
					current_read_state = SEND_DATA;
				else
					current_read_state = READ_PEACE_AFTER_J;

				if (!checkNextChar(inFile, "  \n") && inFile.eof())
					return 	FileHelper::numOfRowsRead;
			}

			else
				return 	FileHelper::numOfRowsRead;
			break;

		case(READ_PEACE_AFTER_J):

			if ((piece = readchar(inFile)) != EOF && piece != THIS_IS_NOT_A_LETTER) {

				searchJockerRep = false;
				current_read_state = SEND_DATA;

				if (!checkNextChar(inFile, "  \n") && inFile.good())
					return 	FileHelper::numOfRowsRead;
			}

			else
				return 	FileHelper::numOfRowsRead;
			break;

		case (SEND_DATA):

			input_validation = validatePiece(pieceValidation, col, row);

			if (!input_validation) {

				//if player try to put 2 pices @ the same square we will get false here
				continueReadingFile = boardManager->loadPosFromFile(piece, col, row, playerNumber, pieceValidation);

				if (!continueReadingFile) {

					inFile.close();
					return FileHelper::numOfRowsRead;
				}

				if (checkEnterBeforeNextLine(inFile)) {

					current_read_state = READ_PIECE;
					FileHelper::numOfRowsRead++;
				}

				else {

					inFile.close();
					return FileHelper::numOfRowsRead;

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

int FileHelper::readMoveFileFromDirectory(string _fileName1, string _fileName2, int& playerWithError, BoardManager* boardManager, int& innerIssue, int & _weGotAWinner) {

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
					return 	FileHelper::numOfRowsRead;
			}

			//the next Char isn't digit (while it should be) or maybe it's EOF
			else {

				//isn't digit or eof - don't matter in the middle of a move - its error
				if (current_read_state != RS1)
					return 	FileHelper::numOfRowsRead;

				//the file of the current player ended
				else if ((moveAndJockerData[numOfArgsRd] == EOF) && current_read_state == RS1) {

					switchPlayer = true;
					continueReadingFile = checkAndSetNextRead(inFile1, inFile2, currFile, row1Player, row2Player, switchPlayer);
				}

				//not a digit
				else
					return 	FileHelper::numOfRowsRead;
			}

			break;

		case(CHECK_FOR_JOKER):

			tempBuff = getNextchar(*currFile);

			if (tempBuff == 'J') {

				(*currFile).get(tempBuff);
				if (tempBuff == ':') {
					current_read_state++;
					if (!checkNextChar((*currFile), " "))
						return 	FileHelper::numOfRowsRead;
				}

				else
					return 	FileHelper::numOfRowsRead;
			}

			else {

				if (isalpha(tempBuff))
					return 	FileHelper::numOfRowsRead;


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
					return 	FileHelper::numOfRowsRead;
			}

			else
				return 	FileHelper::numOfRowsRead;

		case(SEND_MOVE_DATA):

			if (validateMove(moveAndJockerData, jNewRep) != SUCCESS)
				return FileHelper::numOfRowsRead;

			if (_weGotAWinner == -1) {
				if (checkMoveApplicable(moveAndJockerData)) { // TODO we need to return an error for inapplicable move.
					innerIssue = boardManager->checkMovePiece(moveAndJockerData, FileHelper::current_player, jNewRep, _weGotAWinner);
				}
				else {
					return 	FileHelper::numOfRowsRead;
				}
				// here return the line number and the error.
			}

			FileHelper::numOfRowsRead++;
			switchPlayer = true;
			resetForNewData(moveAndJockerData, numOfArgsRd, jNewRep, current_read_state);

			break;
		}
	}


	return SUCCESS;

}

void FileHelper::printGameFinalResults(int winner, int reason, int badposPl1Row, int badposPl2Row, BoardManager boardManager, int _UseOption) {

	ofstream outFile("rps.output", ios::trunc);

	outFile << "Winner: " << winner << endl;
	outFile << "Reason: ";

	if (_UseOption == 1) {
		if (reason == ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN) {
			if (winner == 0) {
				outFile << "All moving PIECEs of both players are eaten." << endl;
			}
			else {
				outFile << "All moving PIECEs of the opponent are eaten." << endl;
			}
		}
		else if (reason == ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED) {

			if (winner == 0) {
				outFile << "All flags of both players are captured." << endl;
			}
			else {
				outFile << "All flags of the opponent are captured." << endl;
			}
		}
		else if (reason == A_TIE_BOTH_MOVES_INPUT_FILES_DONE_WITHOUT_A_WINNER) {
			outFile << "A tie - both Moves input files done without a winner." << endl;
		}
		else if (reason == BAD_POSITIONING_INPUT_FILE_FOR_PLAYER_LINE) {
			if (winner == 1) {
				outFile << "Bad Positioning input file for player 2 - line " << badposPl2Row << endl;
			}
			else {
				outFile << "Bad Positioning input file for player 1 - line " << badposPl1Row << endl;
			}
		}
		else if (reason == BAD_POSITIONING_INPUT_FOR_BOTH_PLAYERS) {
			outFile << "Bad Positioning input file for both players - player1: line " << badposPl1Row << ", player 2: line " << badposPl2Row << endl;
		}
		else {
			outFile << endl;
		}
		// bad moves input file for player another else if.
	}
	else if (_UseOption == 2) {
		if (reason == HEY_THIS_IS_NOT_YOUR_PIECE) {
			cout << "Player" << winner << "won because the opponent tried to move a piece which is not his." << endl;
		}
		else if (reason == HEY_YOU_DONT_HAVE_A_PIECE_HERE) {
			cout << "Player" << winner << "'won because the opponent tried nothing (pieceless location)." << endl;
		}
		else if (reason == HEY_YOU_ARE_TRYING_TO_MOVE_INTO_YOUR_OWN_PIECE) {
			cout << "Player" << winner << "'won because the opponent moved into his own piece." << endl;
		}
		else if (reason == HEY_THIS_PIECE_IS_NOT_MOVEABLE) {
			cout << "Player" << winner << "'won because the opponent moved unmoveable piece." << endl;
		}
	}

	outFile << endl;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			outFile << boardManager.getCurrentPieceInChar(j, i);
		}
		outFile << endl;
	}
	outFile.close();

}

bool FileHelper::checkMoveApplicable(int * arr)
{
	bool applicable = 0;
	if (abs(arr[0] - arr[2]) == 1) {
		applicable = 1;
	}

	if (abs(arr[1] - arr[3]) == 1) {
		if (applicable == 1) {
			applicable = 0;
		}
		else
			applicable = 1;
	}
	return applicable;
}

void FileHelper::resetForNewFile() {

	for (int i = 0; i < 6; i++) {

		count_of_pices[i] = 0;
	}

	numOfRowsRead = 1;
	current_read_state;
	current_read_state = READ_PIECE;
	continueReadingFile = true;
}

// reusage of code!!!
int FileHelper::CheckMovesCanOpen(string _fileName1, string _fileName2)
{
	int canOpenStatus;

	ifstream inFile1(_fileName1), inFile2(_fileName2);

	if (!validateFileOpened(inFile1, _fileName1) || !validateFileOpened(inFile2, _fileName2))
	{
		if (!validateFileOpened(inFile1, _fileName1))
		{
			canOpenStatus = FILE1_OPEN_ERROR;
		}
		else {
			canOpenStatus = FILE2_OPEN_ERROR;
		}

	}
	else if (!validateFileOpened(inFile1, _fileName1) && !validateFileOpened(inFile2, _fileName2))
	{
		canOpenStatus = BOTH_FILES_OPEN_ERROR;
	}
	else
		canOpenStatus = SUCCESS;

	return canOpenStatus;
}

int FileHelper::validatePiece(char currentPiece, int col, int row) {

	if (col > M || row > N)
		return numOfRowsRead;

	switch (currentPiece) {

	case('R'):

		if (count_of_pices[(int)pieceType::ROCK] < R) {
			count_of_pices[(int)pieceType::ROCK]++;
			return SUCCESS;
		}
		else
			return TO_MANY_ROCKS;

	case('P'):

		if (count_of_pices[(int)pieceType::PAPER] < P) {
			count_of_pices[(int)pieceType::PAPER]++;
			return SUCCESS;
		}
		else
			return TO_MANY_PAPERS;

	case('S'):

		if (count_of_pices[(int)pieceType::SCISSORS] < S) {
			count_of_pices[(int)pieceType::SCISSORS]++;
			return SUCCESS;
		}
		else
			return TO_MANY_SCISSORS;

	case('B'):

		if (count_of_pices[(int)pieceType::BOMB] < B) {
			count_of_pices[(int)pieceType::BOMB]++;
			return SUCCESS;
		}
		else
			return TO_MANY_BOMBS;

	case('J'):

		if (count_of_pices[(int)pieceType::JOKER] < J) {
			count_of_pices[(int)pieceType::JOKER]++;
			return SUCCESS;
		}
		else
			return TO_MANY_JOKERS;


	case('F'):

		if (count_of_pices[(int)pieceType::FLAG] < F) {
			count_of_pices[(int)pieceType::FLAG]++;
			return SUCCESS;
		}
		else
			return TO_MANY_FLAGS;

	default:
		return NO_SUCH_PEACE;
	}
}

int FileHelper::validateMove(int* arr, char Jrep) {

	if (arr[0] > M || arr[1] > N || arr[2] > M || arr[3] > N || arr[4] > M || arr[5] > N)
		return MISSPLACEMENT;

	if (Jrep != 'R' && Jrep != 'S' && Jrep != 'P' && Jrep != 'B' && Jrep != 'F' && Jrep != -1)
		return NO_SUCH_PEACE;

	return SUCCESS;
}

bool FileHelper::checkFlagwasSet() {

	return (count_of_pices[(int)pieceType::FLAG] > 0);
}

bool FileHelper::checkAndSetNextRead(ifstream& file1, ifstream& file2, ifstream*& currentFile, int& r_of_p1, int& r_of_p2, bool& switch_player) {

	//The function was called but switch_player is set to false (no actual need to change player). 
	//-----------> 3 options: 1. EOF 2. need to set the first player 3. continue input <----------

	if (!switch_player) {

		//1.set the first time
		if (currentFile == nullptr) {

			if (!file1.eof()) {
				FileHelper::current_player = 1;
				r_of_p2 = numOfRowsRead;
				numOfRowsRead = r_of_p1;
				currentFile = &file1;

			}

			else {
				FileHelper::current_player = 2;
				r_of_p1 = numOfRowsRead;
				numOfRowsRead = r_of_p2;
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

					FileHelper::current_player = 2;
					r_of_p1 = numOfRowsRead;
					numOfRowsRead = r_of_p2;
					currentFile = &file2;
				}
			}

			else if (currentFile == &file2) {

				if (file1.eof())
					return false;

				else {

					FileHelper::current_player = 1;
					r_of_p2 = numOfRowsRead;
					numOfRowsRead = r_of_p1;
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

			FileHelper::current_player = 2;
			r_of_p1 = numOfRowsRead;
			numOfRowsRead = r_of_p2;
			currentFile = &file2;
			switch_player = false;
			return true;
		}


		//switch from 2 to 1
		if (currentFile == &file2 && file1.good()) {

			FileHelper::current_player = 1;
			r_of_p2 = numOfRowsRead;
			numOfRowsRead = r_of_p1;
			currentFile = &file1;
			switch_player = false;
			return true;
		}
	}
}

void FileHelper::resetForNewData(int* result_array, int& argumentCounter, char& jNewRep, int& current_state) {

	for (int i = 0; i < 6; i++)
		result_array[i] = -1;

	argumentCounter = 0;
	jNewRep = -1;
	current_state = RS1;
	continueReadingFile = true;
}

bool FileHelper::checkEnterBeforeNextLine(ifstream& file) {

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