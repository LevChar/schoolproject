#ifndef __GameManager_H
#define __GameManager_H

#include "GameConfig.h"
#include "FileHelper.h"
#include "BoardPrint.h"
#include "FileGameHelper.h"
class GameManager
{
private:
	int innerFile1Error, innerFile2Error;
	int reason;
	int weGotAWinner;
	FileGameHelper fp;
	GameConfig gameRunSettings;
	BoardManager boardManager;
	int winReason;
	int loadedPosProperly;
	int loadedMoveProperly;
	int innerMoveFileIssue;
	BoardPrint bp;
	//1 - All flags of the opponent are captured
	//2 - All moving PIECEs of the opponent are eaten
	//3 - A tie - both Moves input files done without a winner
	//4 - Bad Positioning input file for player <player> -line <bad line number>
	//5 - Bad Positioning input file for both players - player 1: line <X>, player 2 : line <Y>
	//6 - Bad Moves input file for player <player> -line <bad line number>


public:
	bool CheckPorperlyLoadedAndPrintInfo(int _loadedPosProperly, int _loadedMovProperly);

	int getWeGotAWinner();
	void startTheGame();
	void setWinReason(int reason);
	int getWinReason();
	int getLoadedMovProperly();
	int getLoadedPosProperly();
	//void printBoard(BoardManager boardManager);
	// void InitializePlayers(); //We will be used later on when the game will hold the players.
	int LoadToBoard(BoardManager* _boardManager);
	bool LoadMovesToBoard(BoardManager* _boardManager);
	void FightAfterLoad(BoardManager* _boardManager, int& _weGotAWinner);
	void enterCombat(BoardManager* _boardManager, int _col, int _row, int& _weGotAWinner);
	GameManager(GameConfig i_GameRunSettings);
	int CheckForWinners(int &_reason);
	~GameManager();
	void printToScreenError(int resultsFile, int player);
	void EndManager(BoardManager _boardManager, int Winner, int reasonOfEnd, int problemPlayer1, int problemPlayer2, int UseOption);
};


#endif // !__GameManager_H


