#ifndef __GameConfig_H
#define __GameConfig_H


class GameConfig {

	bool isQuietMode;
	int showMode;
	int selected_player;
	int delay;

public:

	int getShowMode();
	bool getIsQuiteMode();
	int getSlected_Player();
	int getDelay();
	void setShowMode(int showModeStatus);
	void setIsQuiteMode(bool isQuiteModeStatus);
	void setSlected_Player(int slectedPlayerStatus);
	void setDelay(int myDelay);

	GameConfig();
	~GameConfig();
	void InitializeSettings(int args_size, const char** arguments);

};


#endif // !__GameConfig_H
