#include "Piece.h"

Piece::Piece()
{
	_last_known_rep = _pieceType = Piece::pieceType::NONE;
	playerNumber = 0;			//TODO - delete after player class implementation
	timesJokerExposed = 0;
	isMoveable = false;
	isAlive = false;
	isFlag = false;
	isJoker = false;
	player = nullptr;
}

Piece::~Piece() {}

//TODO - delete after player class implementation
int Piece::getPlayerNumber() { return playerNumber; }
Piece::pieceType Piece::getPieceType() const { return _pieceType; }
Piece::pieceType Piece::getLastKnownRep() const { return _last_known_rep; }
bool Piece::getIsMoveable() { return isMoveable; }
bool Piece::getIsJoker() { return isJoker; }
bool Piece::getIsAlive() { return isAlive; }
bool Piece::getIsFlag() { return isFlag; }
bool Piece::getTimesJokerExsposed() { return timesJokerExposed; }
Player& Piece::getPlayer() { return *player; }

//TODO - delete after player class implementation
void Piece::setPlyaerNumber(int _playerNumber) { playerNumber = _playerNumber; }
void Piece::setPieceType(pieceType i_pieceType) { _pieceType = i_pieceType; }
void Piece::setLastKnownPieceType(pieceType LastKnown_pieceType) { _last_known_rep = LastKnown_pieceType; }
void Piece::setisMoveable(bool _isMoveable) { isMoveable = _isMoveable; }
void Piece::setIsJoker(bool _isJoker) { isJoker = _isJoker; }
void Piece::setIsAlive(bool _isAlive) { isAlive = _isAlive; }
void Piece::setIsFlag(bool _isFlag) { isFlag = _isFlag; }
void Piece::incTimesJokerExsposed() { timesJokerExposed++; }
void Piece::setPlayer(Player& pl) { player = &pl; }


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
	isAlive = false;
	isFlag = false;
	isJoker = false;
	playerNumber = 0;									 //TODO - delete after player class implementation
	_last_known_rep =_pieceType = pieceType::NONE;
	player = nullptr;
}

void Piece::setPieceTypeFromChar(char _CharPieceType)
{
	if ( (_CharPieceType == 'R') )
	{
		setPieceType(pieceType::ROCK);
		setLastKnownPieceType(pieceType::ROCK);
	}

	if ( (_CharPieceType == 'P') )
	{
		setPieceType(pieceType::PAPER);
		setLastKnownPieceType(pieceType::PAPER);
	}

	if ( (_CharPieceType == 'S') )
	{
		setPieceType(pieceType::SCISSORS);
		setLastKnownPieceType(pieceType::SCISSORS);
	}

	if ( (_CharPieceType == 'B') )
	{
		setPieceType(pieceType::BOMB);
		setLastKnownPieceType(pieceType::BOMB);
	}

	if (_CharPieceType == 'J')
	{
		setPieceType(pieceType::JOKER);
		setLastKnownPieceType(pieceType::NONE);
	}

	if (_CharPieceType == 'F')
	{
		setPieceType(pieceType::FLAG);
		setLastKnownPieceType(pieceType::FLAG);
	}

	if ((_CharPieceType == 'r'))
	{
		setPieceType(pieceType::ROCK);
		setLastKnownPieceType(pieceType::ROCK);
	}

	if ((_CharPieceType == 'p'))
	{
		setPieceType(pieceType::PAPER);
		setLastKnownPieceType(pieceType::PAPER);
	}

	if ((_CharPieceType == 's'))
	{
		setPieceType(pieceType::SCISSORS);
		setLastKnownPieceType(pieceType::SCISSORS);
	}
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