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

public:

	void reset();
	bool checkFlagwasSet();
	int validatePiece(char currentPiece, int col, int row);

	void increaseNumOfRowsRead();
	void setNumOfRowsRead(int rows);
	int getNumOfRowsRead();

	virtual void f() = 0;

	GamePlayHelper();
	~GamePlayHelper();
};

