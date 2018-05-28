#include "GamePlayHelper.h"



void GamePlayHelper::reset()
{
	for (int i = 0; i < 6; i++) {

		count_of_pices[i] = 0;
	}

}

bool GamePlayHelper::checkFlagwasSet() {

	return (count_of_pices[(int)pieceType::FLAG] > 0);
}

int GamePlayHelper::validatePiece(char currentPiece, int col, int row) {

	if (col > M || row > N)
		return numOfRowsRead;

	switch (currentPiece) {

	case('R'):

		if (count_of_pices[(int)pieceType::ROCK] < R) {
			count_of_pices[(int)pieceType::ROCK]++;
			return SUCCESS;
		}
		else
			return TO_MANY_ROCKS;

	case('P'):

		if (count_of_pices[(int)pieceType::PAPER] < P) {
			count_of_pices[(int)pieceType::PAPER]++;
			return SUCCESS;
		}
		else
			return TO_MANY_PAPERS;

	case('S'):

		if (count_of_pices[(int)pieceType::SCISSORS] < S) {
			count_of_pices[(int)pieceType::SCISSORS]++;
			return SUCCESS;
		}
		else
			return TO_MANY_SCISSORS;

	case('B'):

		if (count_of_pices[(int)pieceType::BOMB] < B) {
			count_of_pices[(int)pieceType::BOMB]++;
			return SUCCESS;
		}
		else
			return TO_MANY_BOMBS;

	case('J'):

		if (count_of_pices[(int)pieceType::JOKER] < J) {
			count_of_pices[(int)pieceType::JOKER]++;
			return SUCCESS;
		}
		else
			return TO_MANY_JOKERS;


	case('F'):

		if (count_of_pices[(int)pieceType::FLAG] < F) {
			count_of_pices[(int)pieceType::FLAG]++;
			return SUCCESS;
		}
		else
			return TO_MANY_FLAGS;

	default:
		return NO_SUCH_PEACE;
	}
}

void GamePlayHelper::increaseNumOfRowsRead()
{
	numOfRowsRead++;
}

void GamePlayHelper::setNumOfRowsRead(int rows)
{
	numOfRowsRead = rows;
}

int GamePlayHelper::getNumOfRowsRead()
{
	return numOfRowsRead;
}

GamePlayHelper::GamePlayHelper()
{
}


GamePlayHelper::~GamePlayHelper()
{
}
