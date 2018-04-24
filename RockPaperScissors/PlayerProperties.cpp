#include "PlayerProperties.h"




void PlayerProperties::setPlayerName(const char *_name) {

	strcpy_s(playerName, _name);
}

char * PlayerProperties::getPlayerName()
{
	return playerName;
}


PlayerProperties::PlayerProperties()
{
}


PlayerProperties::~PlayerProperties()
{
}
