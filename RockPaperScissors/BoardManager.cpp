#include "BoardManager.h"

BoardManager::BoardManager(GameConfig _gameRunSettings){

	i_gameRunSettings = _gameRunSettings;
	InitializeBoard();
}

void BoardManager::InitializeBoard(){

	Piece emptyPiece;
	
	for (int i = 0; i < BOARD_ROW_COUNT; i++)
	{
		for (int j = 0; j < BOARD_COLUMN_COUNT; j++)
		{
			SetSquareInfo(BoardSquareInfo(BoardPoint(i + 1, j +  1), "", BoardSquareInfo::eSquareType::EMPTYZ,  emptyPiece ));
		}
	}
}

void BoardManager::ParsePointToIndex(BoardPoint i_BoardPoint, int * i_Row, int * i_Col)
{
	*i_Row = i_BoardPoint.GetRow() - 1;
	*i_Col = i_BoardPoint.GetColumn() - 1;
}

void BoardManager::ParseIndexToBoardPoint(int i_Row, int i_Col, BoardPoint * i_BoardPoint)
{
	if (i_Row < 0)
		i_Row = 0;
	if (i_Row >= BOARD_ROW_COUNT)
		i_Row = BOARD_ROW_COUNT - 1;
	if (i_Col < 0)
		i_Col = 0;
	if (i_Col >= BOARD_COLUMN_COUNT)
		i_Col = BOARD_COLUMN_COUNT - 1;
	i_BoardPoint->SetRow(i_Row + 1);
	i_BoardPoint->SetColumn( i_Col + 1);
}

void BoardManager::SetSquareInfo(BoardSquareInfo i_NewInfo)
{
	int row, col;
	ParsePointToIndex(i_NewInfo.GetPointInfo(), &row, &col);
	gameBoard[col][row] = i_NewInfo;
}

/*
BoardSquareInfo BoardManager::getSquareInfo(int _col, int _row)
{
	return gameBoard[_row-1][_col-1];
}
*/

BoardSquareInfo * BoardManager::getSquareInfo(int _col, int _row)
{
	return &gameBoard[_col][_row];
}

BoardManager::~BoardManager()
{
}

bool BoardManager::loadPosFromFile(char _piece, int _col, int _row, Player& player, char _pieceValidation){

	Piece tempPiece;
	int jokerOrFlag = 0;
	int proceed = true;
	int reason = 0; // 1 = 
	bool isMoveable = 0;

	if (_pieceValidation == 'J'){

		jokerOrFlag = 1;
		isMoveable = 1;
		_piece = _tolower(_piece);
	}

	else if (_pieceValidation == 'R' || _pieceValidation == 'P' || _pieceValidation == 'S') 
		isMoveable = 1;

	else if (_pieceValidation == 'F')
		jokerOrFlag = 2;

	tempPiece = convertCharToPiece(_piece, player, jokerOrFlag, isMoveable);

	if (player.getplayerNumber() == 1) {

		if (gameBoard[_col - 1][_row - 1].GetCurrentPiece1().getPlayer().getplayerNumber() == 0){
			gameBoard[_col - 1][_row - 1].SetCurrentPiece1(tempPiece);
			
			if(jokerOrFlag==2)
				gameBoard[_col - 1][_row - 1].GetCurrentPiece1ByRef().getPlayer().increaseFlagCounter();
		}

		else {
			std::cout << "Player " << player.getplayerNumber() << " placed two pieces in the same location!" << std::endl;
			proceed = false;
		}
	}

	else if (gameBoard[_col - 1][_row - 1].GetCurrentPiece2().getPlayer().getplayerNumber() == 0){
			gameBoard[_col - 1][_row - 1].SetCurrentPiece2(tempPiece);

			if (jokerOrFlag == 2)
				gameBoard[_col - 1][_row - 1].GetCurrentPiece2ByRef().getPlayer().increaseFlagCounter();
	}

	else {
		std::cout << "Player " << player.getplayerNumber() << " placed two pieces in the same location!" << std::endl;
		proceed = false;
	}
		
	if (proceed != false) {
		if (_pieceValidation != 'F' && _pieceValidation != 'B') {

			if (player.getplayerNumber() == 1)
				gameBoard[_col - 1][_row - 1].GetCurrentPiece1ByRef().getPlayer().increaseMovingPieces();
			else
				gameBoard[_col - 1][_row - 1].GetCurrentPiece2ByRef().getPlayer().increaseMovingPieces();
		}
	}

	return proceed;
}

int BoardManager::checkMovePiece(int *arr, int playerNumber, char jokerNewForm, int & i_weGotAWinner) {

	int issue = HEY_ALL_IS_FINE;

	// Making the user format to suit the board format.
	for (int i = 0; i < 6; i++) { arr[i]--; }

	if ((gameBoard[arr[0]][arr[1]].GetCurrentPiece1().getPlayer().getplayerNumber() == 0) && (gameBoard[arr[0]][arr[1]].GetCurrentPiece2().getPlayer().getplayerNumber() == 0)) {

		issue = HEY_YOU_DONT_HAVE_A_PIECE_HERE;
		i_weGotAWinner = playerNumber == 1 ? 2 : 1;
		return issue;
	}


	if (playerNumber == 1) {

		if (gameBoard[arr[0]][arr[1]].GetCurrentPiece2().getPlayer().getplayerNumber() == 2) {
			issue = HEY_THIS_IS_NOT_YOUR_PIECE;
			i_weGotAWinner = 2;
			return issue;
		}
		else if (!(gameBoard[arr[0]][arr[1]].GetCurrentPiece1().getIsMoveable())) {
			issue = HEY_THIS_PIECE_IS_NOT_MOVEABLE;
			i_weGotAWinner = 2;
			return issue;
		}

		else {

			if (gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPlayer().getplayerNumber() == 1) {
				issue = HEY_YOU_ARE_TRYING_TO_MOVE_INTO_YOUR_OWN_PIECE;
				i_weGotAWinner = 2;
			}

			else if (gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPlayer().getplayerNumber() == 2) {

				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece1() == Piece::pieceType::JOKER)
						movePiece(arr, playerNumber, i_weGotAWinner, TRUE, jokerNewForm);
				}
				else 
					movePiece(arr, playerNumber, i_weGotAWinner, TRUE);
				}

			// Just move the piece regullary.
			else { 
				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece1() == Piece::pieceType::JOKER)
						movePiece(arr, playerNumber, i_weGotAWinner, FALSE, jokerNewForm);
						
				}
				else 
					movePiece(arr, playerNumber, i_weGotAWinner);
			}

			return issue;
		}
	}

	else if (playerNumber == 2) {

		if (gameBoard[arr[0]][arr[1]].GetCurrentPiece1().getPlayer().getplayerNumber() == 1) {
			issue = HEY_THIS_IS_NOT_YOUR_PIECE;
			i_weGotAWinner = 1;
			return issue;
		}
		else if (!(gameBoard[arr[0]][arr[1]].GetCurrentPiece2().getIsMoveable())) {
			issue = HEY_THIS_PIECE_IS_NOT_MOVEABLE;
			i_weGotAWinner = 1;
			return issue;
		}
		else {

			if (gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPlayer().getplayerNumber() == 2) {
				issue = HEY_YOU_ARE_TRYING_TO_MOVE_INTO_YOUR_OWN_PIECE;
				i_weGotAWinner = 1;
			}

			else if (gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPlayer().getplayerNumber() == 1) {

				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER)
						movePiece(arr, playerNumber, i_weGotAWinner, TRUE, jokerNewForm);
				}
				else
					movePiece(arr, playerNumber, i_weGotAWinner, TRUE);
			}

			// Just move the piece regullary.
			else {
				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER)
						movePiece(arr, playerNumber, i_weGotAWinner, FALSE, jokerNewForm);
				}
				else 
					movePiece(arr, playerNumber,i_weGotAWinner);
			}

			return issue;
		}
	}

	return issue;
}

void BoardManager::movePiece(int * arr, int _playerNumber, int& winnerTocheck, bool moveBeforeFight, char jokerNewForm) {

	bool pieceJoker;
	Piece tempPiece;
	int winner_of_this_move = 0;

	if (moveBeforeFight) {

		if (_playerNumber == 1) {

			pieceJoker = gameBoard[arr[0]][arr[1]].GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
			tempPiece = gameBoard[arr[0]][arr[1]].GetCurrentPiece1();
			gameBoard[arr[0]][arr[1]].deleteCurrentPiece1();
			gameBoard[arr[2]][arr[3]].SetCurrentPiece1(tempPiece);

			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[0], arr[1]);
			Sleep(i_gameRunSettings.getDelay());
			bp.PrintMove(arr[2], arr[3], eSquareCapacity(BOTHPLAYERS), 1, gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPieceType(), 2, gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPieceType(), pieceJoker);
			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[2], arr[3]);

			winner_of_this_move = enterCombat(arr[2], arr[3], winnerTocheck);

			switch (winner_of_this_move) {

			case(EMPTY):
				bp.PrintMove(arr[2], arr[3], eSquareCapacity(EMPTY), -1, (Piece::pieceType)(-1), -1, (Piece::pieceType)(-1), pieceJoker);
				return;

			case(PLAYERA):

				bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), PLAYERA, gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);
				return;

			case(PLAYERB):

				bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), -1, (Piece::pieceType)(-1), PLAYERB, gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPieceType(), pieceJoker);
				return;
			}

			if (jokerNewForm != 'N') {

				pieceJoker = gameBoard[arr[4]][arr[5]].GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
				tempPiece = gameBoard[arr[4]][arr[5]].GetCurrentPiece1();
				tempPiece.setPieceTypeFromChar(jokerNewForm);
				gameBoard[arr[4]][arr[5]].deleteCurrentPiece1();
				gameBoard[arr[4]][arr[5]].SetCurrentPiece1(tempPiece);

				if (jokerNewForm == 'B')
					tempPiece.setisMoveable(0);

				Sleep(i_gameRunSettings.getDelay());
				bp.eraseFromBoard(arr[4], arr[5]);
				Sleep(i_gameRunSettings.getDelay());
				bp.PrintMove(arr[4], arr[5], eSquareCapacity(ONEPLAYER), 1, gameBoard[arr[4]][arr[5]].GetCurrentPiece1().getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);

			}
		}

		else if (_playerNumber == 2) {

			pieceJoker = gameBoard[arr[0]][arr[1]].GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;
			tempPiece = gameBoard[arr[0]][arr[1]].GetCurrentPiece2();
			gameBoard[arr[0]][arr[1]].deleteCurrentPiece2();
			gameBoard[arr[2]][arr[3]].SetCurrentPiece2(tempPiece);

			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[0], arr[1]);
			Sleep(i_gameRunSettings.getDelay());

			bp.PrintMove(arr[2], arr[3], eSquareCapacity(BOTHPLAYERS), 1, gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPieceType(), 2, gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPieceType(), pieceJoker);
			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[2], arr[3]);

			winner_of_this_move = enterCombat(arr[2], arr[3], winnerTocheck);

			switch (winner_of_this_move) {

			case(EMPTY):
				bp.PrintMove(arr[2], arr[3], eSquareCapacity(EMPTY), -1, (Piece::pieceType)(-1), -1, (Piece::pieceType)(-1), pieceJoker);
				return;

			case(PLAYERA):

				bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), PLAYERA, gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);
				return;

			case(PLAYERB):

				bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), -1 , (Piece::pieceType)(-1), PLAYERB, gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPieceType(), pieceJoker);
				return;
			}

			if (jokerNewForm != 'N') {

				pieceJoker = gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;
				tempPiece = gameBoard[arr[4]][arr[5]].GetCurrentPiece2();
				tempPiece.setPieceTypeFromChar(jokerNewForm);

				if (jokerNewForm == 'B')
					tempPiece.setisMoveable(0);


				gameBoard[arr[4]][arr[5]].deleteCurrentPiece2();
				gameBoard[arr[4]][arr[5]].SetCurrentPiece2(tempPiece);
				Sleep(i_gameRunSettings.getDelay());
				bp.eraseFromBoard(arr[4], arr[5]);
				Sleep(i_gameRunSettings.getDelay());
				bp.PrintMove(arr[4], arr[5], eSquareCapacity(ONEPLAYER), -1, (Piece::pieceType)(-1), 2, gameBoard[arr[4]][arr[5]].GetCurrentPiece2().getPieceType(), pieceJoker);

			}
		}
	}

	else {

		if (_playerNumber == 1) {

			pieceJoker = gameBoard[arr[0]][arr[1]].GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
			tempPiece = gameBoard[arr[0]][arr[1]].GetCurrentPiece1();
			gameBoard[arr[0]][arr[1]].deleteCurrentPiece1();
			gameBoard[arr[2]][arr[3]].SetCurrentPiece1(tempPiece);

			if (i_gameRunSettings.getIsQuiteMode() != 1) {
				Sleep(i_gameRunSettings.getDelay());
				bp.eraseFromBoard(arr[0], arr[1]);
				Sleep(i_gameRunSettings.getDelay());
				if (i_gameRunSettings.getShowMode() == 1) {
					bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), 1, Piece::pieceType::UNKNOWN, -1, (Piece::pieceType)(-1), pieceJoker);
				}
				else if (i_gameRunSettings.getShowMode() == 2) {
					if (i_gameRunSettings.getSlected_Player() == 1) {
						bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), 1, tempPiece.getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);
					}

					else
						bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), 1, Piece::pieceType::UNKNOWN, -1, (Piece::pieceType)(-1), pieceJoker);
				}
				else
					bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), 1, tempPiece.getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);
			}


			if (jokerNewForm != 'N') {

				pieceJoker = gameBoard[arr[4]][arr[5]].GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
				tempPiece = gameBoard[arr[4]][arr[5]].GetCurrentPiece1();
				tempPiece.setPieceTypeFromChar(jokerNewForm);
				gameBoard[arr[4]][arr[5]].deleteCurrentPiece1();
				gameBoard[arr[4]][arr[5]].SetCurrentPiece1(tempPiece);

				if (jokerNewForm == 'B') {

					tempPiece.setisMoveable(0);

				}
				Sleep(i_gameRunSettings.getDelay());
				bp.eraseFromBoard(arr[4], arr[5]);
				Sleep(i_gameRunSettings.getDelay());
				bp.PrintMove(arr[4], arr[5], eSquareCapacity(ONEPLAYER), 1, gameBoard[arr[4]][arr[5]].GetCurrentPiece1().getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);

			}
		}

		else if (_playerNumber == 2) {

			pieceJoker = gameBoard[arr[0]][arr[1]].GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;
			tempPiece = gameBoard[arr[0]][arr[1]].GetCurrentPiece2();
			gameBoard[arr[0]][arr[1]].deleteCurrentPiece2();
			gameBoard[arr[2]][arr[3]].SetCurrentPiece2(tempPiece);

			if (i_gameRunSettings.getIsQuiteMode() != 1) {
				Sleep(i_gameRunSettings.getDelay());
				bp.eraseFromBoard(arr[0], arr[1]);
				Sleep(i_gameRunSettings.getDelay());

				if (i_gameRunSettings.getShowMode() == 1) {
					bp.PrintMove(arr[2], arr[3], eSquareCapacity(BOTHPLAYERS), -1, (Piece::pieceType)(-1), 2, Piece::pieceType::UNKNOWN, pieceJoker);
				}
				else if (i_gameRunSettings.getShowMode() == 2) {
					if (i_gameRunSettings.getSlected_Player() == 1)
						bp.PrintMove(arr[2], arr[3], eSquareCapacity(BOTHPLAYERS), -1, (Piece::pieceType)(-1), 2, tempPiece.getPieceType(), pieceJoker);
					else
						bp.PrintMove(arr[2], arr[3], eSquareCapacity(ONEPLAYER), 1, Piece::pieceType::UNKNOWN, -1, (Piece::pieceType)(-1), pieceJoker);
				}
				else
					bp.PrintMove(arr[2], arr[3], eSquareCapacity(BOTHPLAYERS), -1, (Piece::pieceType)(-1), 2, tempPiece.getPieceType(), pieceJoker);

			}

			if (jokerNewForm != 'N') {

				pieceJoker = gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;
				tempPiece = gameBoard[arr[4]][arr[5]].GetCurrentPiece2();
				tempPiece.setPieceTypeFromChar(jokerNewForm);



				if (jokerNewForm == 'B')
					tempPiece.setisMoveable(0);

				gameBoard[arr[4]][arr[5]].deleteCurrentPiece2();
				gameBoard[arr[4]][arr[5]].SetCurrentPiece2(tempPiece);
				Sleep(i_gameRunSettings.getDelay());
				bp.eraseFromBoard(arr[4], arr[5]);
				Sleep(i_gameRunSettings.getDelay());
				bp.PrintMove(arr[4], arr[5], eSquareCapacity(BOTHPLAYERS), -1, (Piece::pieceType)(-1), 2, gameBoard[arr[4]][arr[5]].GetCurrentPiece2().getPieceType(), pieceJoker);

			}
		}
	}
}

char BoardManager::getCurrentPieceInChar(int col, int row){

	if (gameBoard[col][row].GetCurrentPiece1().getPlayer().getplayerNumber() != 0)
		return gameBoard[col][row].GetCurrentPiece1().getCharFromMyPiece();

	else if (gameBoard[col][row].GetCurrentPiece2().getPlayer().getplayerNumber() != 0)
		return gameBoard[col][row].GetCurrentPiece2().getCharFromMyPiece();

	else
		return ' ';
}

// 0 regular 1 Joker 2 Flag
Piece BoardManager::convertCharToPiece(char _piece, Player& player, int _isJokerOrFlag, bool _isMoveable) {
	
	Piece tempPiece;

	tempPiece.setPieceTypeFromChar(_piece);
	tempPiece.setPlayer(player);
	tempPiece.setisMoveable(_isMoveable);

	if (_isJokerOrFlag == 1) 
		tempPiece.setLastKnownPieceType(Piece::pieceType::JOKER);
	else if (_isJokerOrFlag == 2) 
		tempPiece.setIsFlag(_isJokerOrFlag);

	return tempPiece;
}

void BoardManager::setWinReason(int reason) { winReason = reason; }

int BoardManager::enterCombat(int _col, int _row, int& weGotAWinner) {

	Player* p1, *p2;

	int winnerOfThisMove = 0;

	Piece& pieceA = gameBoard[_col][_row].GetCurrentPiece1ByRef();
	Piece& pieceB = gameBoard[_col][_row].GetCurrentPiece2ByRef();

	p1 = &pieceA.getPlayer();
	p2 = &pieceB.getPlayer();

	if (pieceA == Piece::pieceType::JOKER) { pieceA.incTimesJokerExsposed();}

	if (pieceB == Piece::pieceType::JOKER) { pieceB.incTimesJokerExsposed();}

	if (pieceA == pieceB || pieceA == Piece::pieceType::BOMB || pieceB == Piece::pieceType::BOMB) {

		pieceA.getPlayer().decreaseMovingPieces();
		pieceB.getPlayer().decreaseMovingPieces(); 
		gameBoard[_col][_row].deleteCurrentPiece1();
		gameBoard[_col][_row].deleteCurrentPiece2();
		checkIfMoveWin(p1,p2, weGotAWinner);
		return winnerOfThisMove;
	}

	if (pieceA == Piece::pieceType::FLAG || pieceB == Piece::pieceType::FLAG) {

		if (pieceA == Piece::pieceType::FLAG) {

			pieceA.getPlayer().decreaseMovingPieces();
			gameBoard[_col][_row].deleteCurrentPiece1();
			winnerOfThisMove = 2;
		}

		else {

			pieceB.getPlayer().decreaseMovingPieces();
			gameBoard[_col][_row].deleteCurrentPiece2();
			winnerOfThisMove = 1;
		}

		checkIfMoveWin(p1, p2, weGotAWinner);
		return winnerOfThisMove;
	}

	if (pieceA > pieceB) {

		pieceB.getPlayer().decreaseMovingPieces();
		gameBoard[_col][_row].deleteCurrentPiece2();
		winnerOfThisMove = 1;
	}

	else {

		pieceA.getPlayer().decreaseMovingPieces();
		gameBoard[_col][_row].deleteCurrentPiece1();
		winnerOfThisMove = 2;
	}

	checkIfMoveWin(p1, p2, weGotAWinner);
	return winnerOfThisMove;
}

void BoardManager::checkIfMoveWin(Player* pl1, Player* pl2, int& weGotAWinner) {

	if (weGotAWinner == -1) {

		if(pl1->getmovingPiecesCounter() == 0 && pl2->getmovingPiecesCounter() == 0){

			weGotAWinner = 0;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}

		else if (pl2->getmovingPiecesCounter() == 0)
		{
			weGotAWinner = 1;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (pl1->getmovingPiecesCounter() == 0)
		{
			weGotAWinner = 2;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
	}

	if (weGotAWinner == -1) {

		if (pl1->getflagCounter() == 0 && pl2->getflagCounter() == 0) {

			weGotAWinner = 0;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}

		else if (pl1->getflagCounter() == 0) {
			weGotAWinner = 2;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (pl2->getflagCounter() == 0) {
			weGotAWinner = 1;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
	}
}

BoardPrint BoardManager::getBoardPrint() { return bp;}