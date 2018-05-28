#ifndef __GameConfig_H
#define __GameConfig_H


class GameConfig {

	bool isQuietMode;
	bool isConsoleMode;
	int showMode;
	int selected_player;
	int delay;

public:

	GameConfig();
	~GameConfig();

	int getShowMode();
	int getSlected_Player();
	int getDelay();
	bool getIsQuiteMode();
	bool getIsConsoleMode();
	void setShowMode(int showModeStatus);
	void setIsQuiteMode(bool isQuiteModeStatus);
	void setSlected_Player(int slectedPlayerStatus);
	void setDelay(int myDelay);
	void setIsConsoleMode(bool isConsoleModeStatus);

	void InitializeSettings(int args_size, const char** arguments);

};


#endif // !__GameConfig_H
