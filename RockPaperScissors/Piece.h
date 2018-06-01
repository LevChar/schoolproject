#ifndef __Piece_H
#define __Piece_H

#include "BoardPoint.h"

class Piece{

public:

	enum class pieceType { ROCK, PAPER, SCISSORS, BOMB, JOKER, FLAG, NONE,UNKNOWN	 };
	enum class moveDirections : int { NONE, LEFT, RIGHT, UP, DOWN };
	
	Piece();
	~Piece();
	pieceType getPieceType() const;
	pieceType getLastKnownRep() const;
	int getPlayerNumber();
	int getPieceTypeInInt(pieceType i_pieceType);
	bool getisMoveable();
	char getCharFromMyPiece();
	void deleteMySelf();
	void  setPlyaerNumber(int _playerNumber);
	void setPieceTypeFromChar(char _CharPieceType);
	void setPieceType(pieceType i_pieceType);
	void setIsFlag(int _isFlag);
	void setisMoveable(bool _isMoveable);
	
	friend bool operator==(const Piece& piece1, const Piece& piece2);
	friend bool operator==(const Piece& piece, const Piece::pieceType type);
	friend bool operator>(const Piece& piece1, const Piece& piece2);
	friend bool operator<(const Piece& piece1, const Piece& piece2);

private:

	pieceType _pieceType;
	pieceType _last_known_rep;
	moveDirections moveDirection;
	bool isMoveable;
	bool isFlag;
	bool isAlive;
	int playerNumber;

	//PlayerProperties *myPlayer;
	//BoardPoint pieceBoardPoint;
};

#endif // !__Piece_H