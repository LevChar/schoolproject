#ifndef __GameManager_H
#define __GameManager_H

#include "GameConfig.h"
#include "FileHelper.h"
#include "BoardPrint.h"
#include "FileGameHelper.h"
#include "ConsoleGameHelper.h"

class GameManager{

	BoardPrint bp;
	FileGameHelper fp;
	ConsoleGameHelper cp;
	GameConfig gameRunSettings;
	BoardManager boardManager;
	int innerFile1Error, innerFile2Error;
	int weGotAWinner;
	int winReason;
	int loadedPosProperly;
	int loadedMoveProperly;
	int innerMoveFileIssue;
	int reason;
	//1 - All flags of the opponent are captured
	//2 - All moving PIECEs of the opponent are eaten
	//3 - A tie - both Moves input files done without a winner
	//4 - Bad Positioning input file for player <player> -line <bad line number>
	//5 - Bad Positioning input file for both players - player 1: line <X>, player 2 : line <Y>
	//6 - Bad Moves input file for player <player> -line <bad line number>

public:

	GameManager(GameConfig i_GameRunSettings);
	~GameManager();
	void startTheGame();
	void loadFromConsole(BoardManager *_boardManager);
	void FightAfterLoad(BoardManager* _boardManager, int& _weGotAWinner);
	void enterCombat(BoardManager* _boardManager, int _col, int _row, int& _weGotAWinner);
	void printToScreenError(int resultsFile, int player);
	void EndManager(BoardManager _boardManager, int Winner, int reasonOfEnd, int problemPlayer1, int problemPlayer2, int UseOption);
	void setWinReason(int reason);
	bool CheckPorperlyLoadedAndPrintInfo(int _loadedPosProperly, int _loadedMovProperly);
	bool LoadMovesToBoard(BoardManager* _boardManager);
	int getWeGotAWinner();
	int getWinReason();
	int getLoadedMovProperly();
	int getLoadedPosProperly();
	int CheckForWinners(int &_reason);
	int LoadToBoard(BoardManager* _boardManager);

	//void printBoard(BoardManager boardManager);
	// void InitializePlayers(); //We will be used later on when the game will hold the players.
};

#endif // !__GameManager_H