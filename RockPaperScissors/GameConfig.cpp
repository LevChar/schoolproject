#include <iostream>
#include <string>
#include "GameConfig.h"
#include "General.h"
#include "utils.h"

using std::cout;
using std::endl;

//TODO
//add validation tests
//check cases of delay without number or player without number

int GameConfig::getShowMode()
{
	return showMode;
}

bool GameConfig::getIsQuiteMode()
{
	return isQuietMode;
}

bool GameConfig::getIsConsoleMode()
{
	return isConsoleMode;
}

int GameConfig::getSlected_Player()
{
	return selected_player;
}

int GameConfig::getDelay()
{
	return delay;
}

void GameConfig::setShowMode(int showModeStatus)
{
	showMode = showModeStatus;
}

void GameConfig::setIsQuiteMode(bool isQuiteModeStatus)
{
	isQuietMode = isQuiteModeStatus;
}

void GameConfig::setSlected_Player(int slectedPlayerStatus)
{
	selected_player = slectedPlayerStatus;
}

void GameConfig::setDelay(int myDelay)
{
	delay = myDelay;
}

void GameConfig::setIsConsoleMode(bool isConsoleModeStatus){

	isConsoleMode = isConsoleModeStatus;
}

GameConfig::GameConfig() :

	isQuietMode(false),
	isConsoleMode(false),
	showMode(ALL),
	delay(50)
{}

GameConfig::~GameConfig() {}

void GameConfig::InitializeSettings(int args_size, const char** arguments) {

	for (int i = 1; i < args_size; i++) {

		if (!strcmp(arguments[i], "-console")) {

			isConsoleMode = true;
			showMode = PLAYER;

			//cout << "console" << endl;
			//system("pause");
			break;
		}

		if (!strcmp(arguments[i], "-quiet")) {

			isQuietMode = true;
			showMode = TURN_OFF;
			delay = 0;
			break;
		}

		if (!strcmp(arguments[i], "-show-all"))		
			break; //the default mode - set by the c'tor
	

		if (!strcmp(arguments[i], "-show-only-known-info")) 			
			showMode = KNOWN;

		if (!strcmp(arguments[i], "-show")) {
		
			showMode = PLAYER;

			if (++i >= args_size) //check if there is another argument
				break;

			else {

				int player_to_show_selection;
				bool isInt = converStringToInt(&player_to_show_selection, arguments[i]);

				if (isInt)
					selected_player = player_to_show_selection;
				else
					break;
			}
		}

		if (!strcmp(arguments[i], "-delay")) {

			if (++i >= args_size) //check if there is another argument
				break;

			else {

				int entered_delay;
				bool isInt = converStringToInt(&entered_delay, arguments[i]);

				if (isInt)
					delay = entered_delay;
				else
					break;
			}
		}
	}
}