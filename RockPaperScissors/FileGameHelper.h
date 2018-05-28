#pragma once
#include "GamePlayHelper.h"

class FileGameHelper:GamePlayHelper
{
	ifstream inFile1;
	ifstream inFile2;

	int current_read_state;
	int current_player;
	bool continueReadingFile = true;

	bool validateFileOpened(ifstream& file, string filename);
	bool checkNextChar(ifstream& file, const char* charTocheck);
	int readNumber(ifstream& file);
	char readchar(ifstream& file);
	char getNextchar(ifstream& file);
	bool checkEnterBeforeNextLine(ifstream& file);
	bool checkFlagwasSetSon();

public:

	void resetForNewFileSon();
	int readPositioningFileFromDirectory(string fileName, int playerNumber, BoardManager* boardManager);
	//int readMoveFileFromDirectory(string _fileName1, string _fileName2, int& playerWithError, BoardManager* boardManager, int& innerIssue, int & _weGotAWinner);
	//int CheckMovesCanOpen(string _fileName1, string _fileName2);
	//void printGameFinalResults(int winner, int reason, int badposPl1Row, int badposPl2Row, BoardManager boardManager, int _UseOption);


	FileGameHelper();
	~FileGameHelper();
};

