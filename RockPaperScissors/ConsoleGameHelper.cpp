#include "ConsoleGameHelper.h"



void ConsoleGameHelper::consoleInsertPos()
{
	cout << "Both players, please enter.... " << endl;
	
	int pCol;
	int pRow;
	char presentationPiece;
	char validationPiece;

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

ConsoleGameHelper::ConsoleGameHelper()
{
}


ConsoleGameHelper::~ConsoleGameHelper()
{
}
