#ifndef __GameGlobals_H
#define __GameGlobals_H

class GameGlobals {

public:

	enum { SHOW = 0, QUIET = 1 };
	enum { ALL = 0, KNOWN = 1, PLAYER = 2, TURN_OFF = 4 };

	GameGlobals();
	~GameGlobals();

private:

};

// TODO Why convertStringToInt is defined here?
static bool converStringToInt(int *backInt, const char * str) {

	int result = 0;
	bool isNumber = true;

	while (*str != '\0') {
		if ((*str < '0') || (*str > '9')) {
			isNumber = false;
		}

		result = (result * 10) + ((*str) - '0');
		str++;
	}

	if (isNumber == true) {
		*backInt = result;
	}
	return isNumber;
}


#endif // !__GameGlobals_H


