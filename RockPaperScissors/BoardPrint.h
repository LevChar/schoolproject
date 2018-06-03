#ifndef __boardPrint_H
#define __boardPrint_H

#include <iostream>
#include "Utils.h"
#include "BoardSquareInfo.h"
#include "Piece.h"

class BoardManager;

class BoardPrint {

	static int const BOARD_STARTING_X = 1;
	static int const BOARD_STARTING_Y = 1;
	static int const BOARD_POINT_WIDTH = 6;
	static int const BOARD_POINT_HIGHT = 3;
	static int const DEFALUT_TEXT_COLOR = WHITE;
	static int const DEFAULT_BACK_COLOR = BLACK;

public:

	void hidecursor();
	void drawWithColor(eSquareType Ctype, int curr_player, Piece::pieceType Ptype, int backroundColor, bool iAmJoker = false);
	void printBoard(BoardManager gameBoard, int playerNumber = 0);
	void PrintMove(int col, int row, eSquareCapacity Ctype, int player1, Piece::pieceType Ptype1, int player2, Piece::pieceType Ptype2, bool iAmJoker = false);
	void eraseFromBoard(int col, int row);
};

#endif // !__boardPrint_H