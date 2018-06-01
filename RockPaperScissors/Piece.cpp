#include "Piece.h"

bool operator==(const Piece& piece, const Piece::pieceType type) {

	if (piece.getPieceType() == type)
		return true;

	return false;
}

bool operator==(const Piece& piece1, const Piece& piece2) {

	if (piece1._last_known_rep == piece2._last_known_rep)
		return true;

	return false;
}

bool operator>(const Piece& piece1, const Piece& piece2) {

	if (piece1._last_known_rep == Piece::pieceType::BOMB)
		return true;

	if (piece1._last_known_rep == Piece::pieceType::ROCK) {
		if (piece2._last_known_rep == Piece::pieceType::SCISSORS)
			return true;
	}

	if (piece1._last_known_rep == Piece::pieceType::PAPER) {
		if (piece2._last_known_rep == Piece::pieceType::ROCK)
			return true;
	}

	if (piece1._last_known_rep == Piece::pieceType::SCISSORS) {
		if (piece2._last_known_rep == Piece::pieceType::PAPER)
			return true;
	}

	//all the other cases, including if piece 1 is flag -> the left is smaller
	return false;
}

bool operator<(const Piece& piece1, const Piece& piece2) {

	return(piece2 > piece1);
}

void Piece::deleteMySelf()
{
	isAlive = 0;
	isFlag = 0;
	playerNumber = 0;
	_last_known_rep =_pieceType = pieceType::NONE;
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


void Piece::setLastKnownPieceType(pieceType LastKnown_pieceType)
{
	_last_known_rep = LastKnown_pieceType;
}

void Piece::incTimesJokerExsposed(){

	timesJokerExposed++;
}

void Piece::setIsFlag(int _isFlag)
{
	isFlag = _isFlag;
}

void Piece::setisMoveable(bool _isMoveable)
{
	isMoveable = _isMoveable;
}


Piece::pieceType Piece::getPieceType() const
{
	return _pieceType;
}


Piece::pieceType Piece::getLastKnownRep() const
{
	return _last_known_rep;
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

bool Piece::getTimesJokerExsposed()
{
	return timesJokerExposed;
}

Piece::Piece()
{
	_last_known_rep = _pieceType = Piece::pieceType::NONE;
	isMoveable = 0;
	playerNumber = 0;
	isAlive = 0;
	isFlag = 0;
	timesJokerExposed = 0;
}

Piece::~Piece(){}