/*
 * Copyright (C) 2023
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

#if	!defined(XFloatShort_h)
#define	XFloatShort_h

#include "XTypeDef.h"
#include <QIODevice>
#define	_USE_MATH_DEFINES
#include <math.h>

class	UFloatShort
{
#pragma	pack(push,1)
	BYTE	Integer;
	BYTE	Decimal;
#pragma	pack(pop)

public:
	UFloatShort(void)								{	Integer=0;	Decimal=0;	}
	explicit	UFloatShort(int n)					{	Integer=n;	Decimal=0;	}
	explicit	UFloatShort(double n)				{	Integer=(BYTE)n;	Decimal=(n-floor(n))*256.0;	}
	UFloatShort(const UFloatShort &src)	{	Integer=src.Integer;	Decimal=src.Decimal;	}

	UFloatShort	&operator=(int n);
	UFloatShort	&operator=(double n);
	UFloatShort	&operator=(const UFloatShort &src);
	UFloatShort	&operator+=(const UFloatShort &src);
	UFloatShort	&operator-=(const UFloatShort &src);
	friend	UFloatShort	operator+(const UFloatShort &src1 ,const UFloatShort &src2);
	friend	UFloatShort	operator-(const UFloatShort &src1 ,const UFloatShort &src2);
	friend	UFloatShort	operator*(const UFloatShort &src1 ,const UFloatShort &src2);
	friend	UFloatShort	operator/(const UFloatShort &src1 ,const UFloatShort &src2);

	UFloatShort	&operator++(void);
	UFloatShort	&operator--(void);

	bool	operator==(const UFloatShort &src)	const;
	bool	operator!=(const UFloatShort &src)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	int		GetInt(void)	const	{	return Integer;	}
	int		GetCeil(void)	const	{	return (Decimal==0)?Integer:Integer+1;	}
	float	GetFloat(void) const	{	return Integer+(Decimal/256.0);		}
};

#endif