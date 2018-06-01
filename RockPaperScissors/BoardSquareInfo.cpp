#include "BoardSquareInfo.h"
#include <string>


BoardSquareInfo::BoardSquareInfo()
{
}


BoardSquareInfo::BoardSquareInfo(BoardPoint i_PointInfo, const char * i_DisplayName, BoardSquareInfo::eSquareType i_SqureType, Piece _emptyPiece) :
	pointInfo(i_PointInfo)
{
	SetDisplayName(i_DisplayName);
	SetSquareType(i_SqureType);
}

void BoardSquareInfo::SetDisplayName(const char * i_DisplayName)
{
	strcpy_s(displayName, i_DisplayName);
	size_t strEndIndex = strlen(i_DisplayName);
	displayName[strEndIndex] = '\0';
}

void BoardSquareInfo::SetPointInfo(BoardPoint i_PointInfo)
{
	pointInfo = i_PointInfo;
}

void BoardSquareInfo::SetCurrentPiece2(Piece i_Piece)
{
	currentPiece2 = i_Piece;
}

void BoardSquareInfo::deleteCurrentPiece1()
{
	currentPiece1.deleteMySelf();

}

void BoardSquareInfo::deleteCurrentPiece2()
{
	currentPiece2.deleteMySelf();

}

Piece BoardSquareInfo::GetCurrentPiece1()
{
	return currentPiece1;
}

Piece BoardSquareInfo::GetCurrentPiece2()
{
	return currentPiece2;
}
void BoardSquareInfo::SetCurrentPiece1(Piece i_Piece)
{
	currentPiece1 = i_Piece;
}

Piece& BoardSquareInfo::GetCurrentPiece1ByRef()
{
	return currentPiece1;
}

Piece& BoardSquareInfo::GetCurrentPiece2ByRef()
{
	return currentPiece2;
}

void BoardSquareInfo::SetSquareType(BoardSquareInfo::eSquareType i_SqureType)
{
	squareType = i_SqureType;
}

BoardSquareInfo::~BoardSquareInfo()
{
}

BoardPoint BoardSquareInfo::GetPointInfo()
{
	return pointInfo;
}