#pragma once

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "BoardManager.h"
class GamePlayHelper
{
	int count_of_pices[6] = {};
	int numOfRowsRead = 1;
	int current_player;
	
	
public:

	void resetForNewData(int* result_array, int& argumentCounter, char& jNewRep, int& current_state);	
	int validateMove(int* arr, char Jrep);
	bool checkMoveApplicable(int *arr);
	void reset();
	bool checkFlagwasSet();
	int validatePiece(char currentPiece, int col, int row);

	void increaseNumOfRowsRead();
	void setNumOfRowsRead(int rows);
	int getNumOfRowsRead();
	int getCurrentPlayer();
	void setCurrentPlayer(int playerNumber);

	virtual void f() = 0;

	GamePlayHelper();
	~GamePlayHelper();
};

