#pragma once

#include "GamePlayHelper.h"

class ConsoleGameHelper : GamePlayHelper
{

	int downCounterOfPiecesPlayer1[6] = { 2,5,1,2,2,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	int downCounterOfPiecesPlayer2[6] = { 2,5,1,2,2,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	

public:
	void consoleInsertPos();
	void f() override {}; // for testing

	ConsoleGameHelper();
	~ConsoleGameHelper();

};

