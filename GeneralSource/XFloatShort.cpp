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

#include "XTypeDef.h"
#include "XFloatShort.h"
#include "XGeneralFunc.h"

UFloatShort	&UFloatShort::operator=(int n)
{
	Integer=n;
	Decimal=0;
	return *this;
}
UFloatShort	&UFloatShort::operator=(double n)
{
	Integer=(BYTE)n;
	Decimal=(n-floor(n))*256.0;
	return *this;
}
UFloatShort	&UFloatShort::operator=(const UFloatShort &src)
{
	Integer=src.Integer;
	Decimal=src.Decimal;
	return *this;
}
UFloatShort	&UFloatShort::operator+=(const UFloatShort &src)
{
	if(Decimal+src.Decimal>=256){
		Integer+=src.Integer+1;
	}
	else{
		Integer+=src.Integer+1;
	}
	Decimal+=src.Decimal;
	return *this;
}

UFloatShort	&UFloatShort::operator-=(const UFloatShort &src)
{
	if(Decimal>=src.Decimal){
		Integer-=src.Integer;
	}
	else{
		Integer-=src.Integer+1;
	}
	Decimal-=src.Decimal;
	return *this;
}
UFloatShort	operator+(const UFloatShort &src1 ,const UFloatShort &src2)
{
	UFloatShort	U;
	if(src1.Decimal+src2.Decimal<256){
		U.Integer=src1.Integer+src2.Integer;
	}
	else{
		U.Integer=src1.Integer+src2.Integer+1;
	}
	U.Decimal=src1.Decimal+src2.Decimal;
	return U;
}
UFloatShort	operator-(const UFloatShort &src1 ,const UFloatShort &src2)
{
	UFloatShort	U;
	if(src1.Decimal>=src2.Decimal){
		U.Integer=src1.Integer-src2.Integer;
	}
	else{
		U.Integer=src1.Integer-src2.Integer-1;
	}
	U.Decimal=src1.Decimal-src2.Decimal;
	return U;
}
UFloatShort	operator*(const UFloatShort &src1 ,const UFloatShort &src2)
{
	float	N1=src1.GetFloat();
	float	N2=src2.GetFloat();
	UFloatShort	U(N1*N2);
	return U;
}
UFloatShort	operator/(const UFloatShort &src1 ,const UFloatShort &src2)
{
	float	N1=src1.GetFloat();
	float	N2=src2.GetFloat();
	UFloatShort	U(N1/N2);
	return U;
}

UFloatShort	&UFloatShort::operator++(void)
{
	Integer++;
	return *this;
}
UFloatShort	&UFloatShort::operator--(void)
{
	Integer--;
	return *this;
}
bool	UFloatShort::operator==(const UFloatShort &src)	const
{
	if(Integer==src.Integer && Decimal==src.Decimal)
		return true;
	return false;
}
bool	UFloatShort::operator!=(const UFloatShort &src)	const
{
	if(Integer==src.Integer && Decimal==src.Decimal)
		return false;
	return true;
}


bool	UFloatShort::Save(QIODevice *f)
{
	unsigned short	U=(Integer<<8)+Decimal;
	return ::Save(f,U);
}
bool	UFloatShort::Load(QIODevice *f)
{
	unsigned short	U;
	if(::Load(f,U)==false){
		return false;
	}
	Integer=U>>8;
	Decimal=U&0xFF;
	return true;
}