//-------------------------------------------------//
//	Authors:                                       //
//		1. Lev (Arie) Charfnadel, ID: 310207642.   //
//		2. Dolev Levi, ID: 305772600.              //
//	course: oop - c++ -       Home Project #2      //
//	Date: 03/06/2018                               //
//-------------------------------------------------//

#include "GameManager.h"
#include "GameCOnfig.h"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{

	GameConfig gameSettings;
	gameSettings.InitializeSettings(argc, argv);


	GameManager gm(gameSettings);
	
	if (  gm.CheckPorperlyLoadedAndPrintInfo(gm.getLoadedPosProperly(),gm.getLoadedMovProperly()) && gm.getWeGotAWinner() == -1)  {
		gm.startTheGame();
	}
	
	system("pause");	
}


/*

example 1
==========
Winner: 0
Reason: A tie - both Moves input files done without a winner.


F

F



P R


example 2
==========
Winner: 2
Reason: All moving PIECEs of the opponent are eaten.

F



R




F

example 3
==========
Winner: 0
Reason: Bad Positioning input file for both players - player1: line 4, player 2: line 4

R
RB
B



F
F




*/