#pragma once

#include "GamePlayHelper.h"

class ConsoleGameHelper : public GamePlayHelper
{

	int downCounterOfPiecesPlayer1[6] = { 1,0,0,0,0,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	int downCounterOfPiecesPlayer2[6] = { 1,0,0,0,0,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	
	//int downCounterOfPiecesPlayer1[6] = { 2,5,1,2,2,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	//int downCounterOfPiecesPlayer2[6] = { 2,5,1,2,2,1 }; //R = 2 P = 5 S = 1 B = 2 J = 2 F = 1
	void increasePieceArray(char _validationPiece, int playerNumber);

public:
	
	void f() override {}; // for testing
	void consoleInsertPos(BoardManager * _boardManager, Player& p1, Player& p2);
	ConsoleGameHelper();
	~ConsoleGameHelper();
	bool validatePieceConsole(char _validationPiece, int pCol, int pRow, int playNumber);
	bool validatePieceChar(char _validationPiece, int _playerNumber);
	bool checkIfFinsihedLoading();
	void readMoveFileFromConsole(BoardManager * boardManager, int & _weGotAWinner, Player& p1, Player& p2);
	bool validataeMoveConsole(int *_arr, char _jokerPresentationChange, char _jokerNewPres);
	bool checkPiece(char piece);
};

