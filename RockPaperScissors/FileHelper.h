#ifndef __FileHelper_H
#define __FileHelper_H

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "BoardManager.h"

class FileHelper {

	ifstream inFile1;
	ifstream inFile2;

	int numOfRowsRead = 1;
	int count_of_pices[6] = {};
	int current_read_state;
	int current_player;
	bool continueReadingFile = true;

	bool validateFileOpened(ifstream& file, string filename);
	bool checkNextChar(ifstream& file, const char* charTocheck);
	int readNumber(ifstream& file);
	char readchar(ifstream& file);
	char getNextchar(ifstream& file);
	void resetForNewFile();
	bool checkEnterBeforeNextLine(ifstream& file);
	bool checkFlagwasSet();
	bool checkAndSetNextRead(ifstream& file1, ifstream& file2, ifstream*& currentFile, int& r_of_p1, int& r_of_p2, bool& switch_player);
	

public:

	FileHelper();
	~FileHelper();


	bool checkMoveApplicable(int *arr);
	int validateMove(int* arr, char Jrep);
	int readPositioningFileFromDirectory(string fileName, int playerNumber, BoardManager* boardManager);
	int readMoveFileFromDirectory(string _fileName1, string _fileName2, int& playerWithError, BoardManager* boardManager, int& innerIssue, int & _weGotAWinner);
	int CheckMovesCanOpen(string _fileName1, string _fileName2);
	void printGameFinalResults(int winner, int reason, int badposPl1Row, int badposPl2Row, BoardManager boardManager, int _UseOption);

	int validatePiece(char currentPiece, int col, int row);
	
	
	
	void resetForNewData(int* result_array, int& argumentCounter, char& jNewRep, int& current_state);
	
	

};


#endif // !__FileHelper_H








