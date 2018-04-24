#ifndef __BoardManager_H
#define __BoardManager_H

#include "BoardSquareInfo.h"
#include "BoardPoint.h"
#include "PlayerProperties.h"
#include "BoardPrint.h"
#include <Windows.h>
#include "GameConfig.h"

class BoardManager
{
public:

	static const int BOARD_ROW_START_INDEX = 1;
	static const int BOARD_ROW_COUNT = N;
	static const int BOARD_COLUMN_COUNT = M;

	BoardManager(GameConfig _gameRunSettings);
	void InitializeBoard();
	
	static void ParsePointToIndex(BoardPoint i_BoardPoint, int* i_Row, int * i_Col);
	static void ParseIndexToBoardPoint(int i_Row, int i_Col, BoardPoint* i_BoardPoint);
	void SetSquareInfo(BoardSquareInfo i_NewInfo);
	//BoardSquareInfo getSquareInfo(int _col, int _row);
	BoardSquareInfo *getSquareInfo(int _col, int _row);

	// Reusage of code, need remodeling with new design.
	// Couldnt create player and piece that hold each other from loadPosFromFile as the GM holds the players.
	int getMovingPiecesCounterPlayer1();
	int getMovingPiecesCounterPlayer2();
	void setMovingPiecesCounterPlayer1(int amountOfPieces);
	void setMovingPiecesCounterPlayer2(int amountOfPieces);
	void decreaseMovingPiecesPlayer1();
	void decreaseMovingPiecesPlayer2();
	int checkMovePiece(int* arr, int playerNumber, char jokerNewForm, int & i_weGotAWinner);
	void movePiece(int *arr, int _playerNumber ,char jokerNewForm = 'N');
	char getCurrentPieceInChar(int col, int row);

	~BoardManager();
	int loadPosFromFile(char _piece, int _col, int _row, int playerNumber, char _pieceValidation);
	Piece convertCharToPiece(char _piece, int playerNumber, int _isJokerOrFlag, bool _isMoveable);
	//void printBoard();
	//Piece::pieceType convertCharToPieceType(char _piece);
	void innerComabat(int _col, int _row, int& _weGotAWinner);
	void setWinReason(int reason);
	
	void decreaseFlagCounter(int _playerNumber);
	void increaseFlagCounter(int _playerNumber);
	void setFlagCounterPlayer1(int _flagCounterPlayer1);
	void setFlagCounterPlayer2(int _flagCounterPlayer2);
	int getFlagCounterPlayer1();
	int getFlagCounterPlayer2();

private:
	GameConfig i_gameRunSettings;
	int winReason;
	//1 - All flags of the opponent are captured
	//2 - All moving PIECEs of the opponent are eaten
	//3 - A tie - both Moves input files done without a winner
	//4 - Bad Positioning input file for player <player> -line <bad line number>
	//5 - Bad Positioning input file for both players - player 1: line <X>, player 2 : line <Y>
	//6 - Bad Moves input file for player <player> -line <bad line number>

	int flagCounterPlayer1;
	int flagCounterPlayer2;
	int movingPiecesCounterPlayer1;
	int movingPiecesCounterPlayer2;
	BoardPrint bp;
	//PlayerProperties players[AMOUNT_OF_PLAYERS];
	BoardSquareInfo gameBoard[BOARD_COLUMN_COUNT][BOARD_ROW_COUNT];
};

#endif // !__BoardManager_H