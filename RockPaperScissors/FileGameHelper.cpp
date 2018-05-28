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