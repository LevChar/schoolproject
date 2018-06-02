#ifndef __Piece_H
#define __Piece_H

#include "BoardPoint.h"
#include "Player.h"

class Player;

class Piece{

public:

	enum class pieceType { ROCK, PAPER, SCISSORS, BOMB, JOKER, FLAG, NONE, UNKNOWN };
	enum class moveDirections : int { NONE, LEFT, RIGHT, UP, DOWN };
	
	Piece();
	~Piece();
	pieceType getPieceType() const;
	pieceType getLastKnownRep() const;

	bool getIsMoveable();
	bool getIsJoker();
	bool getIsAlive();
	bool getIsFlag();
	char getCharFromMyPiece();
	bool getTimesJokerExsposed();
	Player& getPlayer();
	void deleteMySelf();
	void setPieceTypeFromChar(char _CharPieceType);
	void setPieceType(pieceType i_pieceType);
	void setIsFlag(bool _isFlag);
	void setIsJoker(bool _isJoker);
	void setIsAlive(bool _isAlive);
	void setisMoveable(bool _isMoveable);
	void setLastKnownPieceType(pieceType LastKnown_pieceType);
	void incTimesJokerExsposed();
	void setPlayer(Player& pl);

	friend bool operator==(const Piece& piece1, const Piece& piece2);
	friend bool operator==(const Piece& piece, const Piece::pieceType type);
	friend bool operator>(const Piece& piece1, const Piece& piece2);
	friend bool operator<(const Piece& piece1, const Piece& piece2);

private:

	pieceType _pieceType;
	pieceType _last_known_rep;
	moveDirections moveDirection;
	Player* player;
	bool isMoveable;
	bool isFlag;
	bool isAlive;
	bool isJoker;
	int playerNumber;
	int timesJokerExposed;
};

#endif // !__Piece_H