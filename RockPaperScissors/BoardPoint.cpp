#include "BoardPoint.h"

BoardPoint::BoardPoint(int i_Row, int i_Col) :

	row(i_Row), 
	column(i_Col)
{}

BoardPoint::~BoardPoint(){}

int BoardPoint::GetRow()
{
	return row;
}

int BoardPoint::GetColumn()
{
	return column;
}

void BoardPoint::SetRow(int i_Row)
{
	row = i_Row;
}

void BoardPoint::SetColumn(int i_Column)
{
	column = i_Column;
}