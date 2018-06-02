#include "Player.h"
Player::Player(int playerNum):

	playerNumber(playerNum),
	flagCounter(0),
	movingPiecesCounter(0),
	readInputStatus(0)

{}

Player::~Player(){}

int Player::getplayerNumber()
{
	return playerNumber;
}

int Player::getflagCounter()
{
	return flagCounter;
}

int Player::getmovingPiecesCounter()
{
	return movingPiecesCounter;
}
int Player::getreadInputStatus()
{
	return readInputStatus;
}
void Player::setplayerNumber(int Pnum)
{
	playerNumber = Pnum;
}
void Player::setflagCounter(int fCounter)
{
	flagCounter = fCounter;
}
void Player::setmovingPiecesCounter(int MPCounter)
{
	movingPiecesCounter = MPCounter;
}

void Player::setreadInputStatus(int status)
{
	readInputStatus = status;
}