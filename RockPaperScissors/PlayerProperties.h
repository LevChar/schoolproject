#ifndef __PlayerProperties_H
#define __PlayerProperties_H

#include "General.h"
#include "Piece.h"
#include <string.h>

class PlayerProperties
{
private:
	char playerName[MAX_PLPAYER_NAME_LEN];
	
	//Piece * myPieces[R+P+S+B+J+F];

public:
	void setPlayerName(const char* _name);
	char* getPlayerName();



	PlayerProperties();
	~PlayerProperties();
};


#endif // !__PlayerProperties_H



