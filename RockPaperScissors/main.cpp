//-------------------------------------------------//
//	Authors:                                       //
//		1. Lev (Arie) Charfnadel, ID: 310207642.   //
//		2. Dolev Levi, ID: 305772600.              //
//	course: oop - c++ -       Home Project #1      //
//	Date: 22/04/2018                               //
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