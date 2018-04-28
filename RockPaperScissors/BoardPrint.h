#ifndef __boardPrint_H
#define __boardPrint_H

#include <iostream>
#include "Utils.h"
#include "BoardSquareInfo.h"
#include "Piece.h"

class BoardManager;
//#include "BoardManager.h"
//#include "PlayerProperties.h"

//class Player;

class BoardPrint {

	static int const BOARD_STARTING_X = 1;
	static int const BOARD_STARTING_Y = 1;
	static int const BOARD_POINT_WIDTH = 6;
	static int const BOARD_POINT_HIGHT = 3;
	static int const DEFALUT_TEXT_COLOR = WHITE;
	static int const DEFAULT_BACK_COLOR = BLACK;

	void drawWithColor(eSquareType Ctype, int curr_player, Piece::pieceType Ptype, int backroundColor, bool iAmJoker);		//the first drawing of the board

public:

	void hidecursor();
	void printBoard(BoardManager gameBoard);
	void printBoardInSpecial(BoardManager gameBoard, int playerNumber = 0);
	void PrintMove(int col, int row, eSquareType Ctype, int player1, Piece::pieceType Ptype1, int player2, Piece::pieceType Ptype2,bool iAmJoker);
	void eraseFromBoard(int col, int row);
};

#endif // !__boardPrint_H


