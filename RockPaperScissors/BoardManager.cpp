#include "BoardManager.h"

// test
//using namespace std;
//#include <iostream>
// test

BoardManager::BoardManager(GameConfig _gameRunSettings)
{
	i_gameRunSettings = _gameRunSettings;
	movingPiecesCounterPlayer1 = 0;
	movingPiecesCounterPlayer2 = 0;
	InitializeBoard();
	flagCounterPlayer1 = 0;
	flagCounterPlayer2 = 0;
}

void BoardManager::InitializeBoard()
{
	Piece emptyPiece;
	
	for (int i = 0; i < BOARD_ROW_COUNT; i++)
	{
		for (int j = 0; j < BOARD_COLUMN_COUNT; j++)
		{
			SetSquareInfo(BoardSquareInfo(BoardPoint(i + 1, j +  1), "", BoardSquareInfo::eSquareType::EMPTY,  emptyPiece ));
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

int BoardManager::loadPosFromFile(char _piece, int _col, int _row, int playerNumber, char _pieceValidation)
{
	Piece tempPiece;
	int jokerOrFlag = 0;
	int proceed = 1;
	int reason = 0; // 1 = 
	bool isMoveable = 0;

	if (_pieceValidation == 'J')
	{
		jokerOrFlag = 1;
		isMoveable = 1;
		_piece = _tolower(_piece);
	}
	else if (_pieceValidation == 'R' || _pieceValidation == 'P' || _pieceValidation == 'S') {
		isMoveable = 1;
	}
	else if (_pieceValidation == 'F')
	{
		increaseFlagCounter(playerNumber);
		jokerOrFlag = 2;
	}

	tempPiece = convertCharToPiece(_piece, playerNumber, jokerOrFlag, isMoveable);

	if (playerNumber == 1) {

		if (gameBoard[_col - 1][_row - 1].GetCurrentPiece1().getPlayerNumber() == 0)
		{
			gameBoard[_col - 1][_row - 1].SetCurrentPiece1(tempPiece);
		}
		else {
			std::cout << "Player " << playerNumber << " placed two pieces in the same location!" << std::endl;
			proceed = 0;
		}
	}
	else if (gameBoard[_col - 1][_row - 1].GetCurrentPiece2().getPlayerNumber() == 0)
	{
		gameBoard[_col - 1][_row - 1].SetCurrentPiece2(tempPiece);
	}
	else {
		std::cout << "Player " << playerNumber << " placed two pieces in the same location!" << std::endl;
		proceed = 0;
	}
		

	if (proceed != 0) {
		if (_pieceValidation != 'F' && _pieceValidation != 'B') {

			if (playerNumber == 1) {
				movingPiecesCounterPlayer1++;
			}
			else
			{
				movingPiecesCounterPlayer2++;
			}
		}
	}

	return proceed;
}

int BoardManager::getMovingPiecesCounterPlayer2()
{
	return movingPiecesCounterPlayer2;
}
int BoardManager::getMovingPiecesCounterPlayer1()
{
	return movingPiecesCounterPlayer1;
}

void BoardManager::setMovingPiecesCounterPlayer1(int amountOfPieces)
{
	movingPiecesCounterPlayer1 = amountOfPieces;
}
void BoardManager::setMovingPiecesCounterPlayer2(int amountOfPieces)
{
	movingPiecesCounterPlayer2 = amountOfPieces;
}
void BoardManager::decreaseMovingPiecesPlayer1()
{
	movingPiecesCounterPlayer1--;
}
void BoardManager::decreaseMovingPiecesPlayer2()
{
	movingPiecesCounterPlayer2--;
}


int BoardManager::checkMovePiece(int *arr, int playerNumber, char jokerNewForm, int & i_weGotAWinner)
{
	int issue = HEY_ALL_IS_FINE;

	// Making the user format to suit the board format.
	for (int i = 0; i < 6; i++) {
		arr[i]--;
	}

	if ((gameBoard[arr[0]][arr[1]].GetCurrentPiece1().getPlayerNumber() == 0) && (gameBoard[arr[0]][arr[1]].GetCurrentPiece2().getPlayerNumber() == 0)) {
		issue = HEY_YOU_DONT_HAVE_A_PIECE_HERE;
		if (playerNumber == 1) {
			i_weGotAWinner = 2;
		}
		else {
			i_weGotAWinner = 0;
		}
	}
	else if (playerNumber == 1) {

		if (gameBoard[arr[0]][arr[1]].GetCurrentPiece2().getPlayerNumber() == 2) {
			issue = HEY_THIS_IS_NOT_YOUR_PIECE;
			i_weGotAWinner = 2;
		}
		else if (!(gameBoard[arr[0]][arr[1]].GetCurrentPiece1().getisMoveable()) ) {
			issue = HEY_THIS_PIECE_IS_NOT_MOVEABLE;
			i_weGotAWinner = 2;
		}
		else {
			
			if (gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPlayerNumber() == 1) {
				issue = HEY_YOU_ARE_TRYING_TO_MOVE_INTO_YOUR_OWN_PIECE;
				i_weGotAWinner = 2;
			}
			else if (gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPlayerNumber() == 2) {
				
				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece1() == Piece::pieceType::JOKER) {
						movePiece(arr, playerNumber, jokerNewForm);
					}
				}
				else {
					movePiece(arr, playerNumber);
				}

				innerComabat(arr[2], arr[3], i_weGotAWinner);
				// to handle - EnterComabt TODO
			}
			
			else { // Just move the piece regullary.
				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece1() == Piece::pieceType::JOKER) {
						movePiece(arr, playerNumber,jokerNewForm);
						issue = HEY_ALL_IS_FINE;
					}
				}
				else {
					movePiece(arr, playerNumber);
					issue = HEY_ALL_IS_FINE;
				}				
			}
		}
	}

	else if (playerNumber == 2) {

		if (gameBoard[arr[0]][arr[1]].GetCurrentPiece1().getPlayerNumber() == 1) {
			issue = HEY_THIS_IS_NOT_YOUR_PIECE;
			i_weGotAWinner = 1;
		}
		else if (!(gameBoard[arr[0]][arr[1]].GetCurrentPiece2().getisMoveable())) {
			issue = HEY_THIS_PIECE_IS_NOT_MOVEABLE;
			i_weGotAWinner = 1;
		}
		else {

			if (gameBoard[arr[2]][arr[3]].GetCurrentPiece2().getPlayerNumber() == 2) {
				issue = HEY_YOU_ARE_TRYING_TO_MOVE_INTO_YOUR_OWN_PIECE;
				i_weGotAWinner = 1;
			}
			else if (gameBoard[arr[2]][arr[3]].GetCurrentPiece1().getPlayerNumber() == 1) {

				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER) {
						movePiece(arr, playerNumber, jokerNewForm);
					}
				}
				else {
					movePiece(arr, playerNumber);
				}

				innerComabat(arr[2], arr[3], i_weGotAWinner);
				// to handle - EnterComabt TODO
			}

			else {// Just move the piece regullary.
				if (jokerNewForm == 'R' || jokerNewForm == 'P' || jokerNewForm == 'S' || jokerNewForm == 'B')
				{
					if (gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER) {
						movePiece(arr, playerNumber, jokerNewForm);
						issue = HEY_ALL_IS_FINE;
					}
				}
				else {
					movePiece(arr, playerNumber);
					issue = HEY_ALL_IS_FINE;
				}
			}
		}
	}

	return issue;
}

void BoardManager::movePiece(int * arr, int _playerNumber,char jokerNewForm)
{
	bool pieceJoker;
	Piece tempPiece;

	if (_playerNumber == 1)
	{
		pieceJoker = gameBoard[arr[0]][arr[1]].GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
		tempPiece = gameBoard[arr[0]][arr[1]].GetCurrentPiece1();
		gameBoard[arr[0]][arr[1]].deleteCurrentPiece1();
		gameBoard[arr[2]][arr[3]].SetCurrentPiece1(tempPiece);

		if (i_gameRunSettings.getIsQuiteMode() != 1) {
			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[0], arr[1]);
			Sleep(i_gameRunSettings.getDelay());
			if (i_gameRunSettings.getShowMode() == 1) {
				bp.PrintMove(arr[2], arr[3], (eSquareType)1, 1, Piece::pieceType::UNKNOWN, -1, (Piece::pieceType)(-1), pieceJoker);
			}
			else if (i_gameRunSettings.getShowMode() == 2) {
				if (i_gameRunSettings.getSlected_Player() == 1) {
					bp.PrintMove(arr[2], arr[3], (eSquareType)1, 1, tempPiece.getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);
				}
				else {
					bp.PrintMove(arr[2], arr[3], (eSquareType)1, 1, Piece::pieceType::UNKNOWN, -1, (Piece::pieceType)(-1), pieceJoker);
				}
			}
			else {
				bp.PrintMove(arr[2], arr[3], (eSquareType)1, 1, tempPiece.getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);
			}
		}
	

		if (jokerNewForm != 'N')
		{
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
			bp.PrintMove(arr[4], arr[5], eSquareType(1), 1, gameBoard[arr[4]][arr[5]].GetCurrentPiece1().getPieceType(), -1, (Piece::pieceType)(-1), pieceJoker);

		}
	}
	else if (_playerNumber == 2)
	{
		pieceJoker = gameBoard[arr[0]][arr[1]].GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;
		tempPiece = gameBoard[arr[0]][arr[1]].GetCurrentPiece2();
		gameBoard[arr[0]][arr[1]].deleteCurrentPiece2();
		gameBoard[arr[2]][arr[3]].SetCurrentPiece2(tempPiece);

		if (i_gameRunSettings.getIsQuiteMode() != 1) {
			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[0], arr[1]);
			Sleep(i_gameRunSettings.getDelay());

			if (i_gameRunSettings.getShowMode() == 1) {
				bp.PrintMove(arr[2], arr[3], (eSquareType)2, -1, (Piece::pieceType)(-1), 2, Piece::pieceType::UNKNOWN, pieceJoker);
			}
			else if (i_gameRunSettings.getShowMode() == 2) {
				if (i_gameRunSettings.getSlected_Player() == 1) {
					bp.PrintMove(arr[2], arr[3], (eSquareType)2, -1, (Piece::pieceType)(-1), 2, tempPiece.getPieceType(), pieceJoker);
				}
				else {
					bp.PrintMove(arr[2], arr[3], (eSquareType)1, 1, Piece::pieceType::UNKNOWN, -1, (Piece::pieceType)(-1), pieceJoker);
				}
			}
			else {
				bp.PrintMove(arr[2], arr[3], (eSquareType)2, -1, (Piece::pieceType)(-1), 2, tempPiece.getPieceType(), pieceJoker);
			}
		}

		if (jokerNewForm != 'N')
		{
			pieceJoker = gameBoard[arr[4]][arr[5]].GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;
			tempPiece = gameBoard[arr[4]][arr[5]].GetCurrentPiece2();
			tempPiece.setPieceTypeFromChar(jokerNewForm);
			
			

			if (jokerNewForm == 'B') {

				tempPiece.setisMoveable(0);

			}
			gameBoard[arr[4]][arr[5]].deleteCurrentPiece2();
			gameBoard[arr[4]][arr[5]].SetCurrentPiece2(tempPiece);
			Sleep(i_gameRunSettings.getDelay());
			bp.eraseFromBoard(arr[4], arr[5]);
			Sleep(i_gameRunSettings.getDelay());
			bp.PrintMove(arr[4], arr[5], eSquareType(2), 011, (Piece::pieceType)(-1), 2, gameBoard[arr[4]][arr[5]].GetCurrentPiece2().getPieceType(), pieceJoker);

		}
	}
}

char BoardManager::getCurrentPieceInChar(int col, int row)
{
	if (gameBoard[col][row].GetCurrentPiece1().getPlayerNumber() != 0) {
		return gameBoard[col][row].GetCurrentPiece1().getCharFromMyPiece();
	}
	else if (gameBoard[col][row].GetCurrentPiece2().getPlayerNumber() != 0) {
		return gameBoard[col][row].GetCurrentPiece2().getCharFromMyPiece();
	}
	else
		return ' ';
}

// 0 regular 1 Joker 2 Flag
Piece BoardManager::convertCharToPiece(char _piece, int playerNumber, int _isJokerOrFlag, bool _isMoveable) 
{
	Piece tempPiece;

	tempPiece.setPieceTypeFromChar(_piece);
	tempPiece.setPlyaerNumber(playerNumber);
	tempPiece.setisMoveable(_isMoveable);
	if (_isJokerOrFlag == 1) 
	{
		tempPiece.setLastKnownPieceType(Piece::pieceType::JOKER);
	}
	else if (_isJokerOrFlag == 2) 
	{
		tempPiece.setIsFlag(_isJokerOrFlag);
	}
	return tempPiece;
}


//test
//void BoardManager::printBoard()
//{
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < M; j++)
//		{
//			cout << gameBoard[i][j].GetCurrentPiece1().getPlayerNumber();
//			cout << gameBoard[i][j].GetCurrentPiece2().getPlayerNumber();
//			cout << " ";
//		}
//		cout << endl;
//	}
//	
//}

void BoardManager::innerComabat(int _col, int _row, int& _weGotAWinner){

	Piece& pieceA = gameBoard[_col][_row].GetCurrentPiece1ByRef();
	Piece& pieceB = gameBoard[_col][_row].GetCurrentPiece2ByRef();

	if (pieceA == Piece::pieceType::JOKER) {

		pieceA.incTimesJokerExsposed();
	}

	if (pieceB == Piece::pieceType::JOKER) {

		pieceB.incTimesJokerExsposed();
	}

	if (pieceA == pieceB || pieceA == Piece::pieceType::BOMB || pieceB == Piece::pieceType::BOMB) {

		gameBoard[_col][_row].deleteCurrentPiece1();
		decreaseMovingPiecesPlayer1();
		gameBoard[_col][_row].deleteCurrentPiece2();
		decreaseMovingPiecesPlayer2();
		bp.eraseFromBoard(_col, _row);
		return;
	}

	if (pieceA == Piece::pieceType::FLAG || pieceB == Piece::pieceType::FLAG) {

		if (pieceA == Piece::pieceType::FLAG) {

			gameBoard[_col][_row].deleteCurrentPiece1();
			decreaseMovingPiecesPlayer1();
		}

		else {

			gameBoard[_col][_row].deleteCurrentPiece2();
			decreaseMovingPiecesPlayer2();
		}

		return;
	}

	if (pieceA > pieceB) {

		gameBoard[_col][_row].deleteCurrentPiece2();
		decreaseMovingPiecesPlayer2();
		return;
	}

	else {

		gameBoard[_col][_row].deleteCurrentPiece1();
		decreaseMovingPiecesPlayer1();
		return;
	}

	if (_weGotAWinner == -1)
	{
		if ((getMovingPiecesCounterPlayer1() == 0) && (getMovingPiecesCounterPlayer2() == 0))
		{
			_weGotAWinner = 0;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (getMovingPiecesCounterPlayer2() == 0)
		{
			_weGotAWinner = 1;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
		else if (getMovingPiecesCounterPlayer1() == 0)
		{
			_weGotAWinner = 2;
			setWinReason(ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN);
		}
	}

	if (_weGotAWinner == -1) {
		if (getFlagCounterPlayer1() == 0 && getFlagCounterPlayer1()) {
			_weGotAWinner = 0;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (getFlagCounterPlayer1() == 0) {
			_weGotAWinner = 2;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
		else if (getFlagCounterPlayer2() == 0) {
			_weGotAWinner = 1;
			setWinReason(ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED);
		}
	}

}

void BoardManager::setWinReason(int reason)
{
	winReason = reason;
}

void BoardManager::decreaseFlagCounter(int _playerNumber)
{
	if (_playerNumber == 1)
	{
		flagCounterPlayer1--;
	}
	else if (_playerNumber == 2) {
		flagCounterPlayer2--;
	}
}

void BoardManager::increaseFlagCounter(int _playerNumber)
{
	if (_playerNumber == 1)
	{
		flagCounterPlayer1++;
	}
	else if (_playerNumber == 2) {
		flagCounterPlayer2++;
	}
}

void BoardManager::setFlagCounterPlayer1(int _flagCounterPlayer1)
{
	flagCounterPlayer1 = _flagCounterPlayer1;
}

void BoardManager::setFlagCounterPlayer2(int _flagCounterPlayer2)
{
	flagCounterPlayer2 = _flagCounterPlayer2;
}

int BoardManager::getFlagCounterPlayer1()
{
	return flagCounterPlayer1;
}

int BoardManager::getFlagCounterPlayer2()
{
	return flagCounterPlayer2;
}