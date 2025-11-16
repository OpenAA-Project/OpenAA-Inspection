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