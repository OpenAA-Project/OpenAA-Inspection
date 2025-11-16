#ifndef MATRIXHEADER_H
#define MATRIXHEADER_H

#include "XTypeDef.h"

struct	MatrixStruct
{
	int32	x1,y1,x2,y2;
	char	AreaName[32];
	char	Namings[10][32];
	int32	Attr;
};

struct	PieceStruct
{
	int32	x1,y1,x2,y2;
	char	NGPieceName[64];
	bool	NG;
};

#endif