#pragma once
#include "GamePlayHelper.h"

class FileGameHelper: public GamePlayHelper
{
	ifstream inFile1;
	ifstream inFile2;

	int current_read_state;
	bool continueReadingFile = true;

	int current_player;
	bool validateFileOpened(ifstream& file, string filename);
	bool checkNextChar(ifstream& file, const char* charTocheck);
	int readNumber(ifstream& file);
	char readchar(ifstream& file);
	char getNextchar(ifstream& file);
	bool checkEnterBeforeNextLine(ifstream& file);
	bool checkFlagwasSetSon();
	bool checkAndSetNextRead(ifstream& file1, ifstream& file2, ifstream*& currentFile, int& r_of_p1, int& r_of_p2, bool& switch_player);
	void resetForNewDataSon(int* result_array, int& argumentCounter, char& jNewRep, int& current_state);
public:
	void f() override {}; // for testing
	void resetForNewFileSon();
	int readPositioningFileFromDirectory(string fileName, Player& player, BoardManager& boardManager);
	int readMoveFileFromDirectory(string _fileName1, string _fileName2, int& playerWithError, BoardManager& boardManager, int& innerIssue, int & _weGotAWinner);
	int CheckMovesCanOpen(string _fileName1, string _fileName2);
	void printGameFinalResults(int winner, int reason, int badposPl1Row, int badposPl2Row, BoardManager boardManager, int _UseOption);
	void printConsoleResults(int winner, int reason);

	FileGameHelper();
	~FileGameHelper();
};
