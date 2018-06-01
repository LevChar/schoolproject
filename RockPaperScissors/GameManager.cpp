#include "GameManager.h"

GameManager::GameManager(GameConfig i_GameRunSettings) :
	innerFile1Error(0),
	innerFile2Error(0),
	reason(-1),
	innerMoveFileIssue(HEY_ALL_IS_FINE),
	weGotAWinner(-1),
	winReason(-2),
	gameRunSettings(i_GameRunSettings),
	boardManager(i_GameRunSettings)

{

	if (!i_GameRunSettings.getIsConsoleMode()) {
		// InitializePlayers(); // We will be used later on when the game will hold the players.
		//boardFactory = new BoardFactory(&boardManager, players);
		loadedPosProperly = LoadToBoard(&boardManager);
		loadedMoveProperly = fp.CheckMovesCanOpen(movFileNameA, movFileNameB);


		if (loadedPosProperly == 0 && loadedMoveProperly == 0) { // 0 = Able to open.
			weGotAWinner = CheckForWinners(reason);
		}

		// TODO if we didnt have an issue during the load then we will print the board according to the settings.
		if (weGotAWinner != -1) {
			if (innerFile1Error > 0 || innerFile2Error > 0) {
				EndManager(boardManager, weGotAWinner, loadedPosProperly, innerFile1Error, innerFile2Error, 1);
			}
			else if (loadedPosProperly < 0) {
				EndManager(boardManager, weGotAWinner, loadedPosProperly, innerFile1Error, innerFile2Error, 1);
			}
			else {
				EndManager(boardManager, weGotAWinner, reason, innerFile1Error, innerFile2Error, 1);
			}
		}
	}
	else {
		loadFromConsole(&boardManager);
		
		//function to request the information from the user.
		//validate that the information was inserted properly.
		//start fights if there are.
		//check for winners.
	}
}

void GameManager::startTheGame()
{

	FightAfterLoad(&boardManager, weGotAWinner);

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
		EndManager(boardManager, weGotAWinner, winReason, -1, -1, 1);
	}

	else {
		LoadMovesToBoard(&boardManager);
		// I AM HERE
		if (innerMoveFileIssue != 0) {
			EndManager(boardManager, weGotAWinner, innerMoveFileIssue, -1, -1, 2);
		}
		else if (innerMoveFileIssue == 0) {
			if (weGotAWinner == -1) {
				winReason = A_TIE_BOTH_MOVES_INPUT_FILES_DONE_WITHOUT_A_WINNER;
				weGotAWinner = 0;
				EndManager(boardManager, weGotAWinner, winReason, -1, -1, 1);
			}
			else if (weGotAWinner != -1) {

			}
		}
	}
}

int GameManager::CheckForWinners(int &_reason)
{
	int Winner = -1; // 0 Tie, 1 - Player1, 2- Player2, -1- No Winner yet.

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

//void GameManager::printBoard(BoardManager boardManager)
//{
//	boardManager.printBoard();
//}

//We will be used later on when the game will hold the players.
/*void GameManager::InitializePlayers()
{
players[0].setPlayerName(Player1);
players[1].setPlayerName(Player2);

}
*/

int GameManager::LoadToBoard(BoardManager* boardManager)
{
	int playerNumber1 = 1;
	int playerNumber2 = 2;
	int loadStatus = 0;
	int resultsFile1 = 0;
	int resultsFile2;

	resultsFile1 = fp.readPositioningFileFromDirectory(posFileNameA, playerNumber1, boardManager);
	if (resultsFile1 < 0) {
		printToScreenError(resultsFile1, playerNumber1);
		weGotAWinner = 2;
		loadStatus = -100;
	}

	resultsFile2 = fp.readPositioningFileFromDirectory(posFileNameB, playerNumber2, boardManager);
		if (resultsFile2 < 0) {
		printToScreenError(resultsFile2, playerNumber2);
		if (weGotAWinner == 2) {
			weGotAWinner = 0;
		}
		else {
			weGotAWinner = 1;
		}
		loadStatus = -100;
	}

	if (resultsFile1 == -9 && resultsFile2 == -9)
	{
		loadStatus = BOTH_FILES_OPEN_ERROR;
	}
	else if (resultsFile1 == -9) {
		loadStatus = resultsFile1;
	}
	else if (resultsFile2 == -9) {
		loadStatus = resultsFile2;
	}
	else if (resultsFile1 > 0 && resultsFile2 > 0) {
		innerFile1Error = resultsFile1;
		innerFile2Error = resultsFile2;
		weGotAWinner = 0; // tie
		loadStatus = BAD_POSITIONING_INPUT_FOR_BOTH_PLAYERS;
	}
	else if (resultsFile1 > 0) {
		innerFile1Error = resultsFile1;
		weGotAWinner = playerNumber2;
		loadStatus = BAD_POSITIONING_INPUT_FILE_FOR_PLAYER_LINE;
	}
	else if (resultsFile2 > 0) {
		innerFile2Error = resultsFile2;
		weGotAWinner = playerNumber1;
		loadStatus = BAD_POSITIONING_INPUT_FILE_FOR_PLAYER_LINE;
	}

	return loadStatus;
}

void GameManager::loadFromConsole(BoardManager * _boardManager)
{
	cp.consoleInsertPos(_boardManager);
}

bool GameManager::LoadMovesToBoard(BoardManager * _boardManager)
{
	int resultsFile1 = 0;

	int playerNumberWithIssue;

	resultsFile1 = fp.readMoveFileFromDirectory(movFileNameA, movFileNameB, playerNumberWithIssue, _boardManager, innerMoveFileIssue, weGotAWinner);

	return 1;
}

void GameManager::FightAfterLoad(BoardManager * _boardManager, int & _weGotAWinner)
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (((_boardManager->getSquareInfo(j, i)->GetCurrentPiece1().getPlayerNumber()) == 1) &&
				((_boardManager->getSquareInfo(j, i)->GetCurrentPiece2().getPlayerNumber()) == 2))
			{
				enterCombat(_boardManager, j, i, weGotAWinner);
			}
		}
	}
}

void GameManager::enterCombat(BoardManager *_boardManager, int _col, int _row, int& _weGotAWinner)
{
	Piece pieceA = _boardManager->getSquareInfo(_col, _row)->GetCurrentPiece1();
	Piece pieceB = _boardManager->getSquareInfo(_col, _row)->GetCurrentPiece2();

	if (pieceA == pieceB || pieceA == Piece::pieceType::BOMB || pieceB == Piece::pieceType::BOMB) {

		_boardManager->getSquareInfo(_col, _row)->deleteCurrentPiece1();
		_boardManager->decreaseMovingPiecesPlayer1();
		_boardManager->getSquareInfo(_col, _row)->deleteCurrentPiece2();
		_boardManager->decreaseMovingPiecesPlayer2();
		return;
	}

	if (pieceA == Piece::pieceType::FLAG || pieceB == Piece::pieceType::FLAG) {
		
		if (pieceA == Piece::pieceType::FLAG) {

			_boardManager->getSquareInfo(_col, _row)->deleteCurrentPiece1();
			_boardManager->decreaseMovingPiecesPlayer1();
		}

		else {

			_boardManager->getSquareInfo(_col, _row)->deleteCurrentPiece2();
			_boardManager->decreaseMovingPiecesPlayer2();
		}

		return;
	}

	if (pieceA > pieceB) {

		_boardManager->getSquareInfo(_col, _row)->deleteCurrentPiece2();
		_boardManager->decreaseMovingPiecesPlayer2();
	}

	else {

		_boardManager->getSquareInfo(_col, _row)->deleteCurrentPiece1();
		_boardManager->decreaseMovingPiecesPlayer1();
	}

if (_weGotAWinner == -1)
	{
		if ((_boardManager->getMovingPiecesCounterPlayer1() == 0) && (_boardManager->getMovingPiecesCounterPlayer2() == 0))
		{
			_weGotAWinner = 0;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (_boardManager->getMovingPiecesCounterPlayer2() == 0)
		{
			_weGotAWinner = 1;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (_boardManager->getMovingPiecesCounterPlayer1() == 0)
		{
			_weGotAWinner = 2;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
	}

	if (_weGotAWinner == -1) {
		if (_boardManager->getFlagCounterPlayer1() == 0 && _boardManager->getFlagCounterPlayer1()) {
			_weGotAWinner = 0;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (_boardManager->getFlagCounterPlayer1() == 0) {
			_weGotAWinner = 2;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (_boardManager->getFlagCounterPlayer2() == 0) {
			_weGotAWinner = 1;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
	}
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

void GameManager::EndManager(BoardManager _boardManager, int Winner, int reasonOfEnd, int problemPlayer1, int problemPlayer2, int UseOption)
{
	fp.printGameFinalResults(Winner, reasonOfEnd, problemPlayer1, problemPlayer2, boardManager, UseOption);
}

int GameManager::getWeGotAWinner()
{
	return weGotAWinner;
}