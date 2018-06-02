#ifndef  __utils_H
#define __utlis_H

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define MAX_PICES_NUMBER 16
#define SIZE			10
#define CELL_SIZE_ROW	2
#define CELL_SIZE_COL	5
#define FIRST_PLAYER 1
#define SECOND_PLAYER 2
#define PL1_POS_FILE "player1.rps_board"
#define PL2_POS_FILE "player2.rps_board"
#define BASE_COL 6
#define BASE_ROW 2

enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, OLIVE, WHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW };
enum  eSquareType :int { EMPTY, PLAYERA, PLAYERB, BOTHPLAYERS };
enum  eSquareCapacity :int { EMPTYZ, ONEPLAYER, BOTHPLAYERSINTHECELL };

void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void gotoxy(int x, int y);
void gotoxyAux(int col, int row);
void hidecursor();
void clearScreen();

bool converStringToInt(int *backInt, const char * str);
#endif // ! __utils_H
