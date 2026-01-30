/*
 * Copyright (C) 2024
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

#pragma once
#include "XTypeDef.h"
#include "XMainSchemeMemory.h"

class LineMatchingX
{
	BYTE	*LineData;
	int		LineLen;
	int		XNumb;
	int		SkipX,SkipY;
	int		LeftX;
	int		Y;
	int		AA;
	int		A;
public:

	LineMatchingX(void);
	LineMatchingX(const LineMatchingX &src);
	virtual ~LineMatchingX(void);

	bool	Initial( int LeftX ,int LineLen,int Y
					,ImageBuffer &SrcImage
					,int skipx=1 ,int skipy=1);
	double	GetVarSrc(void);

	float	SearchMax(int SearchX ,int SearchY
					 ,ImageBuffer &DstImage,int dx ,int dy
					 ,int &MaxDx ,int &MaxDy);
	float	SearchMax(int x1,int y1 ,int x2 ,int y2
					,ImageBuffer &DstImage,int dx ,int dy
					,int &MaxDx ,int &MaxDy);

	LineMatchingX	&operator=(const LineMatchingX &src);
	int				GetStartX(void)	{	return LeftX;	}
	int				GetStartY(void)	{	return Y;		}

public:
	int		Calc1st		 (int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
	int		CalcRightStep(int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
	int		Calc1stSkip1		(int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
	int		CalcRightStepSkip1	(int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
private:
	float	SearchMaxRaw(int x1,int y1 ,int x2 ,int y2
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy);
public:
	float	CalcCoef(int AB ,int BB ,int B);
};


class LineMatchingY
{
	BYTE	*LineData;
	int		LineLen;
	int		YNumb;
	int		SkipX,SkipY;
	int		LeftX;
	int		Y;
	int		AA;
	int		A;
public:

	LineMatchingY(void);
	LineMatchingY(const LineMatchingY &src);
	virtual ~LineMatchingY(void);

	bool	Initial( int LeftX ,int LineLen,int Y
					,ImageBuffer &SrcImage
					,int skipx=1 ,int skipy=1);
	double	GetVarSrc(void);

	float	SearchMax(int SearchX ,int SearchY
					 ,ImageBuffer &DstImage,int dx ,int dy
					 ,int &MaxDx ,int &MaxDy);
	float	SearchMax(int x1,int y1 ,int x2 ,int y2
					,ImageBuffer &DstImage,int dx ,int dy
					,int &MaxDx ,int &MaxDy);

	LineMatchingY	&operator=(const LineMatchingY &src);
	int				GetStartX(void)	{	return LeftX;	}
	int				GetStartY(void)	{	return Y;		}

public:
	int		Calc1st		 (int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
	int		CalcLowerStep(int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
	int		Calc1stSkip1		(int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
	int		CalcLowerStepSkip1	(int x,int y,ImageBuffer &DstImage,int &BB ,int &B);
private:
	float	SearchMaxRaw(int x1,int y1 ,int x2 ,int y2
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy);
public:
	float	CalcCoef(int AB ,int BB ,int B);
};