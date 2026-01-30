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
#include <cmath>
#include "XPointer.h"
#include "swap.h"

void	XReverseAsm(BYTE *Src ,BYTE *Dst ,int Len)
{
#if	defined(NO_INLINE_ASSEMBLER) | !defined(WIN64)
	int	Len2=Len/2;
	for(int i=0;i<Len2;i++){
		BYTE	*s=&Src[i];
		BYTE	*d=&Dst[Len-i-1];
		swap(*s,*d);
	}
#else
	int	AsmCount=Len>>4;
	BYTE	*DstEnd=Dst+Len-16;
	BYTE	ShuffleIndex[]={	15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0	};

	__asm{
		push	rcx
		push	rsi
		push	rdi

		mov		ecx,AsmCount
		mov		rsi,Src
		mov		rdi,DstEnd
		movdqu	xmm1,ShuffleIndex

LOOPPoint:;
		movdqu	xmm0,[rsi]
		pshufb	xmm0,xmm1
		movdqu	[rdi],xmm0
		add		rsi,16
		sub		rdi,16
		loop	LOOPPoint

		pop		rdi
		pop		rsi
		pop		rcx
	}
	int	AsmByte=(AsmCount<<4);
	int	SpareCounter=Len-AsmByte;
	for(int i=0;i<SpareCounter;i++){
		Dst[Len-(AsmByte+i)-1]=Src[AsmByte+i];
	}
#endif
}