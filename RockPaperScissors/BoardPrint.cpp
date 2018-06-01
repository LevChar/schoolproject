#include "BoardPrint.h"
#include "FileHelper.h"
#include <iostream>
#include <Windows.h>

  char pices[] = { 'R', 'P', 'S', 'B', 'J', 'F',' ' , };

void BoardPrint::hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


void BoardPrint::printBoard(BoardManager gameBoard) {

	int row = 0;
	std::cout << "     |";
	for (int i = 1; i < 11; i++) {

		if (i<10)
			std::cout << " " << i << "  |";
		else
			std::cout << " " << i << " |";
	}
	cout << endl;
	for (int i = 0; i < (11 * 5) + 1; i++) {
		std::cout << "-";
	}

	cout << endl;
	for (int i = 1; i < 11; i++) {


		if (i<10)
			std::cout << "| " << i << "  |";
		else
			std::cout << "| " << i << " |";

		for (int col = 0; col < M; col++) {

			bool piece1Joker = gameBoard.getSquareInfo(col, row)->GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
			bool piece2Joker = gameBoard.getSquareInfo(col, row)->GetCurrentPiece2() == Piece::pieceType::JOKER ? TRUE : FALSE;

			//case of empty square
			if (gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber() == 0 &&
				gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPlayerNumber() == 0) {


				std::cout << "    ";
			}

			//case of not empty sqaure
			else {

				//case both players @ the square 	// NOT RELEAVNT AS WE WILL DO THE FIGHT AFTER LOAD BEFORE PRINTING TO SCREEN SO ALWAYS ONE WILL BE LEFT.
				if (gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber() != 0 &&
					gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPlayerNumber() != 0) {

					drawWithColor(BOTHPLAYERS, PLAYERA, gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPieceType(), BLACK, piece1Joker);
					drawWithColor(BOTHPLAYERS, PLAYERB, gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPieceType(), BLACK, piece2Joker);
				}
				//case one of the players @ the square
				else {

					int current_player;

					if (gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber()) {

						current_player = gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber();
						drawWithColor(PLAYERA, current_player, gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPieceType(), BLACK, piece1Joker);
					}

					else {

						current_player = gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPlayerNumber();
						drawWithColor(PLAYERB, current_player, gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPieceType(), BLACK, piece2Joker);
					}

				}
			}

			setTextColor(WHITE);  std::cout << "|";
		}
		std::cout << std::endl;
		row++;

		for (int i = 0; i < (11 * 5) + 1; i++)
			std::cout << "-";

		cout << endl;



	}

}


// REUSAGE OF CODE, will change with the new design.
void BoardPrint::printBoardInSpecial(BoardManager gameBoard, int playerNumber)
{
	if (playerNumber != 0) {

	}
	int row = 0;
	std::cout << "     |";
	for (int i = 1; i < 11; i++) {

		if (i<10)
			std::cout << " " << i << "  |";
		else
			std::cout << " " << i << " |";
	}
	cout << endl;
	for (int i = 0; i < (11 * 5) + 1; i++) {
		std::cout << "-";
	}

	cout << endl;
	for (int i = 1; i < 11; i++) {


		if (i<10)
			std::cout << "| " << i << "  |";
		else
			std::cout << "| " << i << " |";

		for (int col = 0; col < M; col++) {

			bool piece1Joker = gameBoard.getSquareInfo(col, row)->GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;
			bool piece2Joker = gameBoard.getSquareInfo(col, row)->GetCurrentPiece1() == Piece::pieceType::JOKER ? TRUE : FALSE;

			//case of empty square
			if (gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber() == 0 &&
				gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPlayerNumber() == 0) {


				std::cout << "    ";
			}

			//case of not empty sqaure
			else {
				// NOT RELEAVNT AS WE WILL DO THE FIGHT AFTER LOAD BEFORE PRINTING TO SCREEN SO ALWAYS ONE WILL BE LEFT.
				//case both players @ the square
				if (gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber() != 0 &&
					gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPlayerNumber() != 0) {

					drawWithColor(BOTHPLAYERS, PLAYERA, gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPieceType(), BLACK, piece1Joker);
					drawWithColor(BOTHPLAYERS, PLAYERB, gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPieceType(), BLACK, piece2Joker);
				}
				//case one of the players @ the square
				else {

					int current_player;

					if (gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber()) {

						current_player = gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPlayerNumber();
						if (playerNumber == 1) {
							drawWithColor(PLAYERA, current_player, gameBoard.getSquareInfo(col, row)->GetCurrentPiece1().getPieceType(), BLACK, piece1Joker);
						}
						else {
							drawWithColor(PLAYERA, current_player, Piece::pieceType::UNKNOWN, BLACK, piece1Joker);
						}
					}

					else {

						current_player = gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPlayerNumber();
						if (playerNumber == 2) {
							drawWithColor(PLAYERB, current_player, gameBoard.getSquareInfo(col, row)->GetCurrentPiece2().getPieceType(), BLACK, piece2Joker);
						}
						else {
							drawWithColor(PLAYERB, current_player, Piece::pieceType::UNKNOWN, BLACK, piece2Joker);
						}
					}

				}
			}

			setTextColor(WHITE);  std::cout << "|";
		}
		std::cout << std::endl;
		row++;

		for (int i = 0; i < (11 * 5) + 1; i++)
			std::cout << "-";

		cout << endl;



	}

}

void BoardPrint::drawWithColor(eSquareType Ctype, int curr_player, Piece::pieceType Ptype, int backroundColor, bool iAmJoker) {

	char printPiece;

	if (iAmJoker) {
		printPiece = tolower(pices[(int)Ptype]);
	}
	else
	{
		printPiece = pices[(int)Ptype];
	}

	if (Ctype == EMPTY) {
		setTextColor(BLACK);
		std::cout << "    ";
	}

	if (Ctype == BOTHPLAYERS) {

		if (curr_player == PLAYERA) {

			setTextColor(RED, WHITE);
			std::cout << printPiece;
			setTextColor(WHITE, WHITE);
			std::cout << "  ";

		}

		else if (curr_player == PLAYERB) {

			setTextColor(BLUE, WHITE);
			std::cout << printPiece;
		}
	}

	else {

		if (curr_player == FIRST_PLAYER) {

			setTextColor(WHITE, RED);
			std::cout << " ";
			std::cout << printPiece;
			std::cout << "  ";
		}

		else if (curr_player == SECOND_PLAYER) {


			setTextColor(WHITE, BLUE);
			std::cout << " ";
			std::cout << printPiece;
			std::cout << "  ";
		}
	}
}


//base col - 0, base row - 0, 
//Ctype = EMPTY - no players, PLAYERA or PLAYERB - one player, BOTHPLAYERS - both of the players
//player1 value = 1 if its only him or both players, -1 if its not him, Ptype1 - the piece type of player 1
//player1 value = 2 if its only him or both players, -1 if its not him, Ptype1 - the piece type of player 2
void BoardPrint::PrintMove(int col, int row, eSquareType Ctype, int pl1, Piece::pieceType Ptype1, int pl2, Piece::pieceType Ptype2, bool iAmJoker) {

	char printPiece1;

	if (iAmJoker) {
		printPiece1 = tolower(pices[(int)Ptype1]);
	}
	else
	{
		printPiece1 = pices[(int)Ptype1];
	}
	char printPiece2;

	if (iAmJoker) {
		printPiece2 = tolower(pices[(int)Ptype2]);
	}
	else
	{
		printPiece2 = pices[(int)Ptype2];
	}

	Sleep(20);
	gotoxyAux(col, row);

	switch (Ctype) {

	case(EMPTY):

		setTextColor(BLACK);
		std::cout << "    ";
		break;

	case(PLAYERA):
	case(PLAYERB):

		if (pl1 == 1) {

			setTextColor(WHITE, RED);
			std::cout << " " << printPiece1 << "  ";
		}

		else if (pl2 == 2) {

			setTextColor(WHITE, BLUE);
			std::cout << " " << printPiece2 << "  ";
		}

		break;


	case(BOTHPLAYERS):

		setTextColor(WHITE, RED);
		std::cout << printPiece1;

		setTextColor(WHITE, WHITE);
		std::cout << "  ";

		setTextColor(WHITE, BLUE);
		std::cout << printPiece2;

		break;
	}

	setTextColor(WHITE, BLACK);
	gotoxy(0, 22);
}

void BoardPrint::eraseFromBoard(int col, int row) {

	gotoxyAux(col, row);
	setTextColor(BLACK);
	std::cout << "    ";
}
