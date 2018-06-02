#pragma once
#include "Piece.h"

class Piece;

class Player{

	int playerNumber;
	int flagCounter;
	int movingPiecesCounter;
	int readInputStatus;
	Piece* pices[SUM_OF_ALL_PICES];

	//todo game result object (lose\win, reason, line)
	
public:

	Player(int playerNum);
	~Player();

	int getplayerNumber();
	int getflagCounter();
	int getmovingPiecesCounter();
	int getreadInputStatus();
	
	void setplayerNumber(int Pnum);
	void setflagCounter(int fCounter);
	void setmovingPiecesCounter(int MPCounter);
	void setreadInputStatus(int status);
};