#include "Piece.h"

// test
//#include <iostream>
//#include "General.h"
//using namespace std;


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

	if (getPieceType() == pieceType::PAPER)
	{
		return 'P';
	}

	if (getPieceType() == pieceType::SCISSORS)
	{
		return 'S';
	}

	if (getPieceType() == pieceType::BOMB)
	{
		return 'B';
	}

	if (getPieceType() == pieceType::FLAG)
	{
		return 'F';
	}
	// TODO Handle Joker
}

Piece::Piece()
{
	isMoveable = 0;
	_pieceType = pieceType::NONE;
	playerNumber = 0;
	isJoker = 0;
	isAlive = 0;
	isFlag = 0;
}


Piece::~Piece()
{


}
