#ifndef __PLAYER_H
#define __PLAYER_H

#include "Piece.h"

class Piece;

class Player{

	int playerNumber;
	int flagCounter;
	int movingPiecesCounter;
	int readInputStatus;
	Piece* pices[SUM_OF_ALL_PICES];

	//todo - IDEA FOR CONTINUE AFTER THECORSE - game result object (lose\win, reason, line)
	
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
	void decreaseMovingPieces();
	void increaseMovingPieces();
	void increaseFlagCounter();
	void decreaseFlagCounter();

};

#endif // !__PLAYER_H