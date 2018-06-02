#ifndef __BoardManager_H
#define __BoardManager_H

#include "BoardSquareInfo.h"
#include "BoardPoint.h"
#include "BoardPrint.h"
#include <Windows.h>
#include "GameConfig.h"

class BoardManager{

public:

	static const int BOARD_ROW_START_INDEX = 1;
	static const int BOARD_ROW_COUNT = N;
	static const int BOARD_COLUMN_COUNT = M;

	BoardManager(GameConfig _gameRunSettings);
	~BoardManager();

	void InitializeBoard();
	static void ParsePointToIndex(BoardPoint i_BoardPoint, int* i_Row, int * i_Col);
	static void ParseIndexToBoardPoint(int i_Row, int i_Col, BoardPoint* i_BoardPoint);
	void SetSquareInfo(BoardSquareInfo i_NewInfo);
	
	BoardSquareInfo *getSquareInfo(int _col, int _row);
	
	// Reusage of code, need remodeling with new design.
	// Couldnt create player and piece that hold each other from loadPosFromFile as the GM holds the players.

	int checkMovePiece(int* arr, int playerNumber, char jokerNewForm, int & i_weGotAWinner);
	void movePiece(int *arr, int _playerNumber, int& winnerTocheck, bool moveBeforeFight = false ,char jokerNewForm = 'N');
	char getCurrentPieceInChar(int col, int row);
	
	bool loadPosFromFile(char _piece, int _col, int _row, Player& playa, char _pieceValidation);
	Piece convertCharToPiece(char _piece, Player& player, int _isJokerOrFlag, bool _isMoveable);
	int enterCombat(int _col, int _row, int& weGotAWinner);
	void checkIfMoveWin(Player* pl1, Player* pl2, int& weGotAWinner);
	void setWinReason(int reason);
	int getWinReason();
	BoardPrint getBoardPrint();
	
	//void printBoard();
	//Piece::pieceType convertCharToPieceType(char _piece);
	//BoardSquareInfo getSquareInfo(int _col, int _row);
	

private:

	GameConfig i_gameRunSettings;
	BoardPrint bp;
	BoardSquareInfo gameBoard[BOARD_COLUMN_COUNT][BOARD_ROW_COUNT];
	int winReason;

	//1 - All flags of the opponent are captured
	//2 - All moving PIECEs of the opponent are eaten
	//3 - A tie - both Moves input files done without a winner
	//4 - Bad Positioning input file for player <player> -line <bad line number>
	//5 - Bad Positioning input file for both players - player 1: line <X>, player 2 : line <Y>
	//6 - Bad Moves input file for player <player> -line <bad line number>

	//PlayerProperties players[AMOUNT_OF_PLAYERS];
};

#endif // !__BoardManager_H