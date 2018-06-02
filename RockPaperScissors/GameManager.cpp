#include "GameManager.h"

GameManager::GameManager(GameConfig i_GameRunSettings) :

	p1(1),
	p2(2),
	reason(-1),
	innerMoveFileIssue(HEY_ALL_IS_FINE),
	weGotAWinner(-1),
	winReason(-2),
	gameRunSettings(i_GameRunSettings),
	boardManager(i_GameRunSettings)
{
	if (!i_GameRunSettings.getIsConsoleMode()) {

		//boardFactory = new BoardFactory(&boardManager, players);
		loadedPosProperly = LoadToBoard();
		loadedMoveProperly = fp.CheckMovesCanOpen(movFileNameA, movFileNameB);

		// 0 == Able to open.
		if (loadedPosProperly == 0 && loadedMoveProperly == 0) { 
			weGotAWinner = CheckForWinners(reason);
		}

		// TODO if we didnt have an issue during the load then we will print the board according to the settings.
		if (weGotAWinner != -1) {

			if (innerFile1Read != 0 || innerFile2Read != 0 || loadedPosProperly != 0) {
				fp.printGameFinalResults(weGotAWinner, loadedPosProperly, innerFile1Read, innerFile2Read, boardManager, FILE_OUTPUT);
			}
			else {
				fp.printGameFinalResults(weGotAWinner, reason, innerFile1Read, innerFile2Read, boardManager, FILE_OUTPUT);
			}
		}
	}

	else {
		loadFromConsole(&boardManager);
		weGotAWinner = CheckForWinners(reason);
		if (weGotAWinner != -1) {
			fp.printGameFinalResults(weGotAWinner, reason, 0, 0, boardManager, FILE_OUTPUT);
		}
	}
}

void GameManager::startTheGame() {

	FightAfterLoad();
	bp.hidecursor();

	if (gameRunSettings.getShowMode() == 0) {
		clearScreen();
		bp.printBoard(boardManager);
	}
	else if (gameRunSettings.getShowMode() == 1) {
		clearScreen();
		bp.printBoardInSpecial(boardManager);
	}
	else if (gameRunSettings.getShowMode() == 2) {
		clearScreen();
		bp.printBoardInSpecial(boardManager, gameRunSettings.getSlected_Player());
	}

	if (weGotAWinner != -1) {
		fp.printGameFinalResults(weGotAWinner, winReason, -1, -1, boardManager, FILE_OUTPUT);
		return;
	}

	LoadMovesToBoard();

	if (innerMoveFileIssue != 0) {
		fp.printGameFinalResults(weGotAWinner, innerMoveFileIssue, -1, -1, boardManager, SCREEN_OUTPUT);
		return;
	}

	if (weGotAWinner == -1) {
		winReason = A_TIE_BOTH_MOVES_INPUT_FILES_DONE_WITHOUT_A_WINNER;
		weGotAWinner = 0;
		fp.printGameFinalResults(weGotAWinner, winReason, -1, -1, boardManager, FILE_OUTPUT);
		return;
	}
}

int GameManager::CheckForWinners(int &_reason)
{
	int Winner = -1; // 0 Tie, 1 - Player1, 2- Player2, -1 ---- No Winner yet.

					 // Can be both dead flag and dead moving pieces as this is the load file we will call it for flags.

	if (boardManager.getMovingPiecesCounterPlayer1() == 0 && boardManager.getMovingPiecesCounterPlayer2() == 0) {
		Winner = 0;
		_reason = ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN;
	}
	else if (boardManager.getMovingPiecesCounterPlayer1() == 0)
	{
		Winner = 2;
		_reason = ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN;
	}
	else if (boardManager.getMovingPiecesCounterPlayer2() == 0) {
		Winner = 1;
		_reason = ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN;
	}

	return Winner;
}

bool GameManager::CheckPorperlyLoadedAndPrintInfo(int _loadedPosProperly, int _loadedMovProperly)
{
	bool startTheGameMov;
	bool startTheGame = 0;
	bool startTheGamePos;

	if (_loadedPosProperly < 0) {
		if (_loadedPosProperly == FILE1_OPEN_ERROR)
		{
			cout << "Error when opening file: " << posFileNameA << endl;
		}
		else if (_loadedPosProperly == FILE2_OPEN_ERROR)
		{
			cout << "Error when opening file: " << posFileNameB << endl;
		}
		else if (_loadedPosProperly == BOTH_FILES_OPEN_ERROR)
		{
			cout << "Error when opening files: " << posFileNameB << " and " << posFileNameB << endl;
		}

		startTheGamePos = 0;
	}
	else
		startTheGamePos = 1;

	if (_loadedMovProperly < 0) {
		if (_loadedMovProperly == -1)
		{
			cout << "Error when opening file: " << movFileNameA << endl;
		}
		else if (_loadedMovProperly == -2)
		{
			cout << "Error when opening file: " << movFileNameB << endl;
		}
		else
		{
			cout << "Error when opening files: " << movFileNameA << " and " << movFileNameB << endl;
		}

		startTheGameMov = 0;
	}
	else
		startTheGameMov = 1;

	if (startTheGameMov && startTheGamePos) {
		startTheGame = 1;
	}

	return startTheGame;
}

void GameManager::setWinReason(int reason)
{
	winReason = reason;
}

int GameManager::getWinReason()
{
	return winReason;
}

int GameManager::getLoadedMovProperly()
{
	return loadedMoveProperly;
}

int GameManager::getLoadedPosProperly()
{
	return loadedPosProperly;
}

int GameManager::LoadToBoard()
{
	int loadStatus = 0;

	innerFile1Read = fp.readPositioningFileFromDirectory(posFileNameA, p1.getplayerNumber(), boardManager);

	//read of first file returned error
	if (innerFile1Read < 0) {
 		printToScreenError(innerFile1Read, p1.getplayerNumber());
		weGotAWinner = 2;
		loadStatus = innerFile1Read;
	}

	innerFile2Read = fp.readPositioningFileFromDirectory(posFileNameB, p2.getplayerNumber(), boardManager);
	
	//read of second file returned error
	if (innerFile2Read < 0) {
		printToScreenError(innerFile2Read, p2.getplayerNumber());
		weGotAWinner = (weGotAWinner == 2 ? 0 : 1); //if the first loset and the second lost they both loose, or just the second lost
		loadStatus = innerFile2Read;
	}

	if (innerFile1Read == -9 && innerFile2Read == -9)
	{
		loadStatus = BOTH_FILES_OPEN_ERROR;
	}

	else if (innerFile1Read == -9) {
		loadStatus = innerFile1Read;
	}
	else if (innerFile2Read == -9) {
		loadStatus = innerFile2Read;
	}

	else if (innerFile1Read > 0 && innerFile2Read > 0) {

		weGotAWinner = 0; // tie
		loadStatus = BAD_POSITIONING_INPUT_FOR_BOTH_PLAYERS;
	}

	else if (innerFile1Read > 0) {
		weGotAWinner = p1.getplayerNumber();
		loadStatus = BAD_POSITIONING_INPUT_FILE_FOR_PLAYER_LINE;
	}
	else if (innerFile2Read > 0) {
		weGotAWinner = p2.getplayerNumber();
		loadStatus = BAD_POSITIONING_INPUT_FILE_FOR_PLAYER_LINE;
	}

	return loadStatus;
}

void GameManager::loadFromConsole(BoardManager * _boardManager)
{
	cp.consoleInsertPos(_boardManager);
}

void GameManager::LoadMovesToBoard()
{
	int playerNumberWithIssue;
	innerFile1Read = 0;
	innerFile1Read = fp.readMoveFileFromDirectory(movFileNameA, movFileNameB, playerNumberWithIssue, boardManager, innerMoveFileIssue, weGotAWinner);
}

void GameManager::FightAfterLoad()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if ((boardManager.getSquareInfo(j, i)->GetCurrentPiece1().getPlayerNumber() == 1) &&
				(boardManager.getSquareInfo(j, i)->GetCurrentPiece2().getPlayerNumber() == 2))
			{
				enterCombat(j, i);
			}
		}
	}
}

void GameManager::enterCombat(int _col, int _row){

	Piece& pieceA = boardManager.getSquareInfo(_col, _row)->GetCurrentPiece1ByRef();
	Piece& pieceB = boardManager.getSquareInfo(_col, _row)->GetCurrentPiece2ByRef();

	if (pieceA == Piece::pieceType::JOKER) {
		
		pieceA.incTimesJokerExsposed();
	}

	if (pieceB == Piece::pieceType::JOKER) {

		pieceB.incTimesJokerExsposed();
	}

	if (pieceA == pieceB || pieceA == Piece::pieceType::BOMB || pieceB == Piece::pieceType::BOMB) {

		boardManager.getSquareInfo(_col, _row)->deleteCurrentPiece1();
		boardManager.decreaseMovingPiecesPlayer1();
		boardManager.getSquareInfo(_col, _row)->deleteCurrentPiece2();
		boardManager.decreaseMovingPiecesPlayer2();
		checkIfMoveWin();
		return;
	}

	if (pieceA == Piece::pieceType::FLAG || pieceB == Piece::pieceType::FLAG) {
		
		if (pieceA == Piece::pieceType::FLAG) {

			boardManager.getSquareInfo(_col, _row)->deleteCurrentPiece1();
			boardManager.decreaseMovingPiecesPlayer1();
		}

		else {

			boardManager.getSquareInfo(_col, _row)->deleteCurrentPiece2();
			boardManager.decreaseMovingPiecesPlayer2();
		}

		checkIfMoveWin();
		return;
	}

	if (pieceA > pieceB) {

		boardManager.getSquareInfo(_col, _row)->deleteCurrentPiece2();
		boardManager.decreaseMovingPiecesPlayer2();
	}

	else {

		boardManager.getSquareInfo(_col, _row)->deleteCurrentPiece1();
		boardManager.decreaseMovingPiecesPlayer1();
	}

	checkIfMoveWin();
	return;
}

GameManager::~GameManager()
{
	// delete boardFactory;
}

void GameManager::printToScreenError(int resultsFile, int player)
{
	if (resultsFile == NO_FLAG_WAS_SET) {
		cout << "Player " << player << " did not place a flag" << endl;
	}
	else if (resultsFile == TO_MANY_ROCKS) {
		cout << "Player " << player << " placed too many rocks" << endl;
	}
	else if (resultsFile == TO_MANY_BOMBS) {
		cout << "Player " << player << " placed too many bombs" << endl;
	}
	else if (resultsFile == TO_MANY_JOKERS) {
		cout << "Player " << player << " placed too many jokers" << endl;
	}
	else if (resultsFile == TO_MANY_PAPERS) {
		cout << "Player " << player << " placed too many papers" << endl;
	}
	else if (resultsFile == TO_MANY_SCISSORS) {
		cout << "Player " << player << " placed too many scissors" << endl;
	}
	else if (resultsFile == TO_MANY_FLAGS) {
		cout << "Player " << player << " placed too many flags" << endl;
	}
	else if (resultsFile == NO_SUCH_PEACE) {
		cout << "Player " << player << " entered incorrect piece" << endl;
	}
}

int GameManager::getWeGotAWinner()
{
	return weGotAWinner;
}

void GameManager::checkIfMoveWin(){

	if (weGotAWinner == -1) {

		if ((boardManager.getMovingPiecesCounterPlayer1() == 0) && (boardManager.getMovingPiecesCounterPlayer2() == 0))
		{
			weGotAWinner = 0;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (boardManager.getMovingPiecesCounterPlayer2() == 0)
		{
			weGotAWinner = 1;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (boardManager.getMovingPiecesCounterPlayer1() == 0)
		{
			weGotAWinner = 2;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
	}

	if (weGotAWinner == -1) {

		if (boardManager.getFlagCounterPlayer1() == 0 && boardManager.getFlagCounterPlayer1()) {
			weGotAWinner = 0;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (boardManager.getFlagCounterPlayer1() == 0) {
			weGotAWinner = 2;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (boardManager.getFlagCounterPlayer2() == 0) {
			weGotAWinner = 1;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
	}
}