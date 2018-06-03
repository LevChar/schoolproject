#ifndef __GameManager_H
#define __GameManager_H

#include "GameConfig.h"
#include "FileHelper.h"
#include "BoardPrint.h"
#include "FileGameHelper.h"
#include "ConsoleGameHelper.h"
#include "Player.h"

class GameManager{

	BoardPrint bp;
	FileGameHelper fp;
	ConsoleGameHelper cp;
	GameConfig gameRunSettings;
	BoardManager boardManager;
	Player p1,p2;
	int innerFile1Read, innerFile2Read;
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
	void printToScreenError(int resultsFile, int player);
	void setWinReason(int reason);
	void FightAfterLoad();
	bool CheckPorperlyLoadedAndPrintInfo(int _loadedPosProperly, int _loadedMovProperly);
	void LoadMovesToBoard();
	int getWeGotAWinner();
	int getWinReason();
	int getLoadedMovProperly();
	int getLoadedPosProperly();
	int CheckForWinners(int &_reason);
	int LoadToBoard();
};

#endif // !__GameManager_H