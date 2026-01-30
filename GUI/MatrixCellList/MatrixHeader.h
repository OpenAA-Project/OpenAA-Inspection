/*
 * Copyright (C) 2012
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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