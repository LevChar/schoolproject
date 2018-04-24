#ifndef __BoardPoint_H
#define __BoardPoint_H

#include "General.h"

class BoardPoint
{

private:
	int row = N;
	int column = M;

public:
	BoardPoint(int i_Row = 1, int i_Col = 1);

	int GetRow();
	int GetColumn();
	void SetRow(int i_Row);
	void SetColumn(int i_Column);
	~BoardPoint();
};


#endif // !__BoardPoint_H

