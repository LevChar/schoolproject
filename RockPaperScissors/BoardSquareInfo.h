#ifndef __BoardSquareInfo_H
#define __BoardSquareInfo_H

#include "BoardPoint.h"
#include "Piece.h"

class BoardSquareInfo
{

	//enum eSquareType :int;
	char displayName[MAX_DISPLAY_NAME_LEN];



public:

	enum  eSquareType :int {EMPTY, PLAYERA, PLAYERB, BOTHPLAYERS};
	
	void SetSquareType(BoardSquareInfo::eSquareType i_SqureType);
	void SetDisplayName(const char* i_DisplayName);
	
	void SetPointInfo(BoardPoint i_PointInfo);

	void SetCurrentPiece1(Piece i_Piece);
	void SetCurrentPiece2(Piece i_Piece);
	
	void deleteCurrentPiece1();
	void deleteCurrentPiece2();

	Piece GetCurrentPiece1();
	Piece GetCurrentPiece2();
	Piece& GetCurrentPiece1ByRef();
	Piece& GetCurrentPiece2ByRef();
	BoardPoint GetPointInfo();
	BoardSquareInfo();
	BoardSquareInfo(BoardPoint i_PointInfo, const char* i_DisplayName, BoardSquareInfo::eSquareType i_SqureType, Piece _emptyPiece);

	~BoardSquareInfo();

private:
	BoardPoint pointInfo;
	eSquareType squareType;
	Piece  currentPiece1;
	Piece  currentPiece2;
};

#endif // !__BoardSquareInfo_H


