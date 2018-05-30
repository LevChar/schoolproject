#include "Piece.h"

// test
//#include <iostream>
//#include "General.h"
//using namespace std;

bool operator==(const Piece& piece1, const Piece& piece2) {

	if (piece1._last_known_rep == piece2._last_known_rep)
		return true;
	return false;
}

bool operator>(const Piece& piece1, const Piece& piece2) {

	//write the operator and test it
	return true; // From Dolev: I can compile because of the error of nothing being returned. - do what ever you want afterwards.
}

void Piece::deleteMySelf()
{
	isAlive = 0;
	isJoker = 0;
	isFlag = 0;
	playerNumber = 0;
	_pieceType = pieceType::NONE;

}

void Piece::setPlyaerNumber(int _playerNumber)
{
	playerNumber = _playerNumber;
}

int Piece::getPlayerNumber()
{
	return playerNumber;
}

int Piece::getPieceTypeInInt(pieceType i_pieceType)
{
	
	return 1;
}


void Piece::setPieceTypeFromChar(char _CharPieceType)
{


	if ( (_CharPieceType == 'R') )
	{
		setPieceType(pieceType::ROCK);
	}

	if ( (_CharPieceType == 'P') )
	{
		setPieceType(pieceType::PAPER);
	}

	if ( (_CharPieceType == 'S') )
	{
		setPieceType(pieceType::SCISSORS);
	}

	if ( (_CharPieceType == 'B') )
	{
		setPieceType(pieceType::BOMB);
	}

	if (_CharPieceType == 'J')
	{
		setPieceType(pieceType::JOKER);
	}

	if (_CharPieceType == 'F')
	{
		setPieceType(pieceType::FLAG);
	}

	//
	if ((_CharPieceType == 'r'))
	{
		setPieceType(pieceType::ROCK);
	}

	if ((_CharPieceType == 'p'))
	{
		setPieceType(pieceType::PAPER);
	}

	if ((_CharPieceType == 's'))
	{
		setPieceType(pieceType::SCISSORS);
	}

}

void Piece::setPieceType(pieceType i_pieceType)
{
	_pieceType = i_pieceType;
}

void Piece::setIsJoker(int _isJoker)
{
	isJoker = _isJoker;
}

bool Piece::getIsJoker()
{
	return isJoker;
}

void Piece::setIsFlag(int _isFlag)
{
	isFlag = _isFlag;
}

void Piece::setisMoveable(bool _isMoveable)
{
	isMoveable = _isMoveable;
}


Piece::pieceType Piece::getPieceType()
{
	return _pieceType;
}


bool Piece::getisMoveable()
{
	return isMoveable;
}

char Piece::getCharFromMyPiece()
{
	if (getPieceType() == pieceType::ROCK)
	{
		return 'R';
	}
	else if (getPieceType() == pieceType::PAPER)
	{
		return 'P';
	}

	else if (getPieceType() == pieceType::SCISSORS)
	{
		return 'S';
	}

	else if (getPieceType() == pieceType::BOMB)
	{
		return 'B';
	}

	else if (getPieceType() == pieceType::FLAG)
	{
		return 'F';
	}
	else {
		return 'U';
	}
	
}

Piece::Piece()
{
	_last_known_rep = _pieceType = Piece::pieceType::NONE;
	isMoveable = 0;
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
	_pieceType = pieceType::NONE;
>>>>>>> Stashed changes
>>>>>>> Stashed changes
	playerNumber = 0;
	isJoker = 0;
	isAlive = 0;
	isFlag = 0;
}

<<<<<<< Updated upstream
Piece::~Piece(){}
=======
<<<<<<< Updated upstream
Piece::~Piece(){}
=======

Piece::~Piece()
{


}
>>>>>>> Stashed changes
>>>>>>> Stashed changes
