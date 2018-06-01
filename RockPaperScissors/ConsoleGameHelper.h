#pragma once

#include "GamePlayHelper.h"

class ConsoleGameHelper : GamePlayHelper
{

	int downCounterOfPiecesPlayer1[6] = { 2,5,1,2,2,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	int downCounterOfPiecesPlayer2[6] = { 2,5,1,2,2,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	

public:
	
	void f() override {}; // for testing
	void consoleInsertPos(BoardManager * _boardManager);
	ConsoleGameHelper();
	~ConsoleGameHelper();
	bool validatePieceConsole(char validationPiece, int pCol, int pRow, int playNumber);


};

