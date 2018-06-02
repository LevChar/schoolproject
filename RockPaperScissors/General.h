#ifndef __General_H
#define __General_H

#include <string.h>

#define THIS_IS_NOT_A_LETTER -2
#define THIS_IS_NOT_A_DIGIT -3

enum readResult {
	NO_SUCH_PEACE = -12, MISSPLACEMENT = -11, NO_FLAG_WAS_SET = -10, FILE1_OPEN_ERROR = -9,
	FILE2_OPEN_ERROR = -8, BOTH_FILES_OPEN_ERROR = -7, TO_MANY_FLAGS = -6, TO_MANY_JOKERS = -5,
	TO_MANY_BOMBS = -4, TO_MANY_SCISSORS = -3, TO_MANY_PAPERS = -2, TO_MANY_ROCKS = -1, SUCCESS = 0
};
enum class pieceType { ROCK, PAPER, SCISSORS, BOMB, JOKER, FLAG, UNKNOWNNONE };
enum readState { READ_PIECE, READ_COL, READ_ROW, READ_PEACE_AFTER_J, SEND_DATA };
enum readMoveState { RS1, RS2, RD1, RD2, CHECK_FOR_JOKER, RJPOS1, RJPOS2, RJNEWREP, SEND_MOVE_DATA };
enum reasons { 

	ALL_FLAGS_OF_THE_OPPONENT_ARE_CAPTURED, 
	ALL_MOVING_PIECES_OF_THE_OPPONENT_ARE_EATEN, 
	A_TIE_BOTH_MOVES_INPUT_FILES_DONE_WITHOUT_A_WINNER,
	BAD_POSITIONING_INPUT_FILE_FOR_PLAYER_LINE, 
	BAD_POSITIONING_INPUT_FOR_BOTH_PLAYERS,
	BAD_MOVE_FILE_FOR_PLAYER_LINE
};
enum afterMoveWasSentIssues {

	HEY_ALL_IS_FINE, 
	HEY_THIS_IS_NOT_YOUR_PIECE,
	HEY_YOU_DONT_HAVE_A_PIECE_HERE,
	HEY_THIS_PIECE_IS_NOT_MOVEABLE,
	HEY_YOU_ARE_TRYING_TO_MOVE_INTO_YOUR_OWN_PIECE,
	HEY_YOU_ARE_TRYING_TO_MOVE_PIECE_IN_IMPOSSIBLE_WAY
};

enum gameMode{ ALL = 0, KNOWN = 1, PLAYER = 2, TURN_OFF = 4 };
enum outputMode { FILE_OUTPUT = 1, SCREEN_OUTPUT = 2};

static const int MAX_DISPLAY_NAME_LEN = 5; // the max len of a display name of an object in the board 
static const int AMOUNT_OF_PLAYERS = 2; // Number of players
static const int MAX_PLPAYER_NAME_LEN = 10;
static const char* Player1 = "Player 1";
static const char* Player2 = "Player 2";
static const int intPlayer1 = 1;
static const int intPlayer2 = 2;
static const int N = 10; // rows
static const int M = 10; // cols
static const int R = 2; // Rocks
static const int P = 5; // Papers
static const int S = 1; // Scissors
static const int B = 2; // Bomb
static const int J = 2; // Joker
static const int F = 1; // Flag
static const int SUM_OF_ALL_PICES = 13; // sum of all pices
static const char* posFileNameA = "player1.rps_board";
static const char* posFileNameB = "player2.rps_board";
static const char* movFileNameA = "player1.rps_moves";
static const char* movFileNameB = "player2.rps_moves";


#endif // !__General_H
