#include "ConsoleGameHelper.h"


//boardManager->loadPosFromFile(piece, col, row, playerNumber, pieceValidation);


void ConsoleGameHelper::consoleInsertPos(BoardManager * _boardManager)
{
	cout << "Both players, please enter.... " << endl;

	int pCol;
	int pRow;
	char presentationPiece;
	char validationPiece;
	char input_validation;

	int completed = 0;
	GamePlayHelper::setCurrentPlayer(1);

	// We need to move from one player to the other, inserting the peices, all of them deduing whatever he entred from the array and one he reaches zero he finish i can also print to the screen after each intercation how many pices of each kind he needs to put.
	while (!completed) {

		if (GamePlayHelper::getCurrentPlayer() == 1) {
			cout << "Player1, please enter one of the following pieces left." << endl;
			cout << "Rocks left: " << downCounterOfPiecesPlayer1[0] << "." << endl;
			cout << "Papers left: " << downCounterOfPiecesPlayer1[1] << "." << endl;
			cout << "Scissors left: " << downCounterOfPiecesPlayer1[2] << "." << endl;
			cout << "Bombs left: " << downCounterOfPiecesPlayer1[3] << "." << endl;
			cout << "Joers left: " << downCounterOfPiecesPlayer1[4] << "." << endl;
			cout << "Flag left: " << downCounterOfPiecesPlayer1[5] << "." << endl;
			cout << "The game will not start until all pieces are played with." << endl;
			cin >> presentationPiece;
			cin >> pCol;
			cin >> pRow;
			validationPiece = presentationPiece;

			if (presentationPiece == 'J') {
				cin >> validationPiece;
			}

			input_validation = validatePieceConsole(validationPiece, pCol, pRow,1);

			if (!input_validation) {

				//if player try to put 2 pices @ the same square we will get false here
				//continueReadingFile = boardManager->loadPosFromFile(piece, col, row, playerNumber, pieceValidation);

				GamePlayHelper::setCurrentPlayer(2);
			}
			else {

				GamePlayHelper::setCurrentPlayer(1);
			}


			//R = 2
			//P = 5
			//S = 1
			//B = 2
			//J = 2
			//F = 1
			// After every insert we need to call another function to actual put it on the board, now when we are puting it in the obard we need to verify that there is no collision if there is a collision we need to request the data again, therefore
			// the function should return a value with errors to the screen.
			// 
		}
	}
}

	ConsoleGameHelper::ConsoleGameHelper()
{
}


ConsoleGameHelper::~ConsoleGameHelper()
{
}

bool ConsoleGameHelper::validatePieceConsole(char validationPiece, int pCol, int pRow, int playerNumber)
{

	if (playerNumber == 1) {
		
		
	}
	else {

	}

	
}
