/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoAlignmentPico.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAutoAlignment.h"
#include "XDoubleClass.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include "XAutoMaskingPI.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "XStatisticPacket.h"
#include "XPointer.h"
#include "XFlexArea.h"
#define _USE_MATH_DEFINES
#include "math.h"
//#include <sse2mmx.h>

#ifdef _MSC_VER
#define	InlineAsmMode
#endif

double	AutoAlignmentInPico::CalcedData::CoefCalc(ImageBuffer &MasterBuff ,ImageBuffer &TargetBuff ,FlexArea &Area,int dx ,int dy)
{
	int	N=Area.GetFLineLen();
	double	TargetAddA	=0;
	double	TargetAddA2	=0;
	double	AddAB		=0;

	//最適化、高速化のために条件分け
	if(StepX>1 && StepY>1){
		if(StepX==2 && StepY==2){

#if	defined(InlineAsmMode)
		static	BYTE	DMask[16]={	0xFF,0,0xFF,0,0xFF,0,0xFF,0,
									0xFF,0,0xFF,0,0xFF,0,0xFF,0	};
			__asm{
				MOVDQU	xmm0, xmmword ptr DMask
				pxor	xmm7, xmm7
			}
			for(int i=0;i<N;i++){
				int	Y	=Area.GetFLineAbsY(i);
				if((Y&1)==0){
					int	X	=Area.GetFLineLeftX(i);
					int	Numb=Area.GetFLineNumb(i)+1;
					BYTE	*a=MasterBuff.GetY(Y)+X;
					BYTE	*b=TargetBuff.GetY(Y+dy)+X+dx;
					int	iTargetAddA	=0;
					int	iTargetAddA2=0;
					int	iAddAB		=0;

					int	Numb8=Numb>>4;
					int	Numb4=Numb&8;
					int	Numb2=Numb&4;
					int	Numb1=Numb&2;

					__asm{
						push	rax
						push	rcx
						push	rsi
						push	rdi
						pxor	xmm3,xmm3	//iAddAB
						pxor	xmm4,xmm4	//iTargetAddA
						pxor	xmm5,xmm5	//iTargetAddA2
						mov		rsi,qword ptr a
						mov		rdi,qword ptr b
						mov		rbx,0
					}
					if(Numb8!=0){
						__asm{
							MOVSXD	rcx,Numb8

WW1:
							MOVDQU	xmm1, xmmword ptr [rsi+rbx]
							MOVDQU	xmm2, xmmword ptr [rdi+rbx]
							pand	xmm1,xmm0
							pand	xmm2,xmm0
							paddw	xmm4,xmm2	//+=d2

							pmaddwd	xmm1,xmm2
							pmaddwd	xmm2,xmm2
							paddd	xmm3,xmm1	//xmm3+=d1*d2
							paddd	xmm5,xmm2	//xmm5+=d2*d2
							add		rbx,16
							loop	WW1
						}
					}
					if(Numb4!=0){
						__asm{
							movq	xmm1, qword ptr [rsi+rbx]
							movq	xmm2, qword ptr [rdi+rbx]
							pand	xmm1,xmm0
							pand	xmm2,xmm0
							paddw	xmm4,xmm2	//+=d2

							pmaddwd	xmm1,xmm2
							pmaddwd	xmm2,xmm2
							paddd	xmm3,xmm1	//xmm3+=d1*d2
							paddd	xmm5,xmm2	//xmm5+=d2*d2
							add		rbx,8
						}
					}
					if(Numb2!=0){
						__asm{
							movd	xmm1, dword ptr [rsi+rbx]
							movd	xmm2, dword ptr [rdi+rbx]
							pand	xmm1,xmm0
							pand	xmm2,xmm0
							paddw	xmm4,xmm2	//+=d2

							pmaddwd	xmm1,xmm2
							pmaddwd	xmm2,xmm2
							paddd	xmm3,xmm1	//xmm3+=d1*d2
							paddd	xmm5,xmm2	//xmm5+=d2*d2
							add		rbx,4
						}
					}
					if(Numb1!=0){
						__asm{
							xor		eax,eax
							mov		al,byte ptr [rsi+rbx]
							movd	xmm1, eax
							mov		al,byte ptr [rdi+rbx]
							movd	xmm2, eax
							paddw	xmm4,xmm2	//+=d2

							pmaddwd	xmm1,xmm2
							pmaddwd	xmm2,xmm2
							paddd	xmm3,xmm1	//xmm3+=d1*d2
							paddd	xmm5,xmm2	//xmm5+=d2*d2
						}
					}
					__asm{
						phaddw	xmm4,xmm7	//8->4
						phaddw	xmm4,xmm7	//4->2
						phaddw	xmm4,xmm7	//2->1
						movd	iTargetAddA,xmm4;

						phaddd	xmm3,xmm7	//4->2
						phaddd	xmm5,xmm7	//4->2

						phaddd	xmm3,xmm5	//2->1
						movd	iAddAB,xmm3
						punpckhqdq	xmm3,xmm3
						movd	iTargetAddA2,xmm3

						pop		rdi
						pop		rsi
						pop		rcx
						pop		rbx
					}

					TargetAddA	+=iTargetAddA;
					TargetAddA2	+=iTargetAddA2;
					AddAB		+=iAddAB;
				}
			}
#else
			for(int i=0;i<N;i++){
				int	Y	=Area.GetFLineAbsY(i);
				if((Y&1)==0){
					int	X	=Area.GetFLineLeftX(i);
					int	Numb=Area.GetFLineNumb(i);
					BYTE	*a=MasterBuff.GetY(Y)+X;
					BYTE	*b=TargetBuff.GetY(Y+dy)+X+dx;
					int	iTargetAddA	=0;
					int	iTargetAddA2=0;
					int	iAddAB		=0;
					if(Numb>=16){
						for(int x=0;x<Numb;x+=2){
							int	d1=a[x];
							int	d2=b[x];
							iTargetAddA	+=d2;
							iTargetAddA2+=d2*d2;
							iAddAB		+=d1*d2;
						}
					}
					else{
						for(int x=0;x<Numb;x+=2){
							int	d1=a[x];
							int	d2=b[x];
							iTargetAddA	+=d2;
							iTargetAddA2+=d2*d2;
							iAddAB		+=d1*d2;
						}
					}
					TargetAddA	+=iTargetAddA;
					TargetAddA2	+=iTargetAddA2;
					AddAB		+=iAddAB;
				}
			}
#endif
		}
		else{
			for(int i=0;i<N;i++){
				int	Y	=Area.GetFLineAbsY(i);
				if((Y%StepY)==0){
					int	X	=Area.GetFLineLeftX(i);
					int	Numb=Area.GetFLineNumb(i);
					BYTE	*a=MasterBuff.GetY(Y)+X;
					BYTE	*b=TargetBuff.GetY(Y+dy)+X+dx;
					int	iTargetAddA	=0;
					int	iTargetAddA2=0;
					int	iAddAB		=0;
					for(int x=0;x<Numb;x+=StepX){
						int	d1=a[x];
						int	d2=b[x];
						iTargetAddA	+=d2;
						iTargetAddA2+=d2*d2;
						iAddAB		+=d1*d2;
					}
					TargetAddA	+=iTargetAddA;
					TargetAddA2	+=iTargetAddA2;
					AddAB		+=iAddAB;
				}
			}
		}
	}
	else if(StepX>1){
		for(int i=0;i<N;i++){
			int	Y	=Area.GetFLineAbsY(i);
			int	X	=Area.GetFLineLeftX(i);
			int	Numb=Area.GetFLineNumb(i);
			BYTE	*a=MasterBuff.GetY(Y)+X;
			BYTE	*b=TargetBuff.GetY(Y+dy)+X+dx;
			int	iTargetAddA	=0;
			int	iTargetAddA2=0;
			int	iAddAB		=0;
			for(int x=0;x<Numb;x+=StepX){
				int	d1=a[x];
				int	d2=b[x];
				iTargetAddA	+=d2;
				iTargetAddA2+=d2*d2;
				iAddAB		+=d1*d2;
			}
			TargetAddA	+=iTargetAddA;
			TargetAddA2	+=iTargetAddA2;
			AddAB		+=iAddAB;
		}
	}
	else if(StepY>1){
		for(int i=0;i<N;i++){
			int	Y	=Area.GetFLineAbsY(i);
			if((Y%StepY)==0){
				int	X	=Area.GetFLineLeftX(i);
				int	Numb=Area.GetFLineNumb(i);
				BYTE	*a=MasterBuff.GetY(Y)+X;
				BYTE	*b=TargetBuff.GetY(Y+dy)+X+dx;
				int	iTargetAddA	=0;
				int	iTargetAddA2=0;
				int	iAddAB		=0;
				for(int x=0;x<Numb;x++){
					int	d1=a[x];
					int	d2=b[x];
					iTargetAddA	+=d2;
					iTargetAddA2+=d2*d2;
					iAddAB		+=d1*d2;
				}
				TargetAddA	+=iTargetAddA;
				TargetAddA2	+=iTargetAddA2;
				AddAB		+=iAddAB;
			}
		}
	}
	else{
#if	defined(InlineAsmMode)
		__asm{
			pxor	xmm0,xmm0
		}
#endif
		for(int i=0;i<N;i++){
			int	Y	=Area.GetFLineAbsY(i);
			int	X	=Area.GetFLineLeftX(i);
			int	Numb=Area.GetFLineNumb(i);
			BYTE	*a=MasterBuff.GetY(Y)+X;
			BYTE	*b=TargetBuff.GetY(Y+dy)+X+dx;
			int	iTargetAddA	=0;
			int	iTargetAddA2=0;
			int	iAddAB		=0;


#if	defined(InlineAsmMode)
			int	Numb8=Numb>>3;
			int	Numb4=Numb&4;
			int	Numb2=Numb&2;
			int	Numb1=Numb&1;

			__asm{
				push	rax
				push	rcx
				push	rsi
				push	rdi
				pxor	xmm3,xmm3	//iAddAB
				pxor	xmm4,xmm4	//iTargetAddA
				pxor	xmm5,xmm5	//iTargetAddA2
				mov		rsi,qword ptr a
				mov		rdi,qword ptr b
				xor		rbx,rbx
			}
			if(Numb8!=0){
				__asm{
					MOVSXD	rcx,Numb8
WW2:
					movq	xmm1, qword ptr [rsi+rbx]
					punpcklbw	xmm1,xmm0				//xmm1=r0,0,r1,0,r2,0,r3,0,r4,0,r5,0,r6,0,r7,0
					movq	xmm2, qword ptr [rdi+rbx]
					punpcklbw	xmm2,xmm0				//xmm1=r0,0,r1,0,r2,0,r3,0,r4,0,r5,0,r6,0,r7,0
					paddw	xmm4,xmm2	//+=d2

					pmaddwd	xmm1,xmm2
					pmaddwd	xmm2,xmm2
					paddd	xmm3,xmm1	//+=d1*d2
					paddd	xmm5,xmm2	//+=d2*d2
					add		rbx,8
					loop	WW2
				}
			}
			if(Numb4!=0){
				__asm{
					movd	xmm1, dword ptr [rsi+rbx]
					punpcklbw	xmm1,xmm0				//xmm1=r0,0,r1,0,r2,0,r3,0,0,0,0,0,0,0,0,0
					movd	xmm2, dword ptr [rdi+rbx]
					punpcklbw	xmm2,xmm0				//xmm1=r0,0,r1,0,r2,0,r3,0,0,0,0,0,0,0,0,0
					paddw	xmm4,xmm2	//+=d2

					pmaddwd	xmm1,xmm2
					pmaddwd	xmm2,xmm2
					paddd	xmm3,xmm1	//+=d1*d2
					paddd	xmm5,xmm2	//+=d2*d2
					add		rbx,4
				}
			}
			if(Numb2!=0){
				__asm{
					xor		rcx,rcx
					mov		cx,word ptr [rsi+rbx]
					movd	xmm1, ecx
					punpcklbw	xmm1,xmm0				//xmm1=r0,0,r1,0,0,0,0,0,0,0,0,0,0,0,0,0
					mov		cx,word ptr [rdi+rbx]
					movd	xmm2, ecx
					punpcklbw	xmm2,xmm0				//xmm1=r0,0,r1,0,0,0,0,0,0,0,0,0,0,0,0,0
					paddw	xmm4,xmm2	//+=d2

					pmaddwd	xmm1,xmm2
					pmaddwd	xmm2,xmm2
					paddd	xmm3,xmm1	//+=d1*d2
					paddd	xmm5,xmm2	//+=d2*d2
					add		rbx,2
				}
			}
			if(Numb1!=0){
				__asm{
					xor		rcx,rcx
					mov		cl,byte ptr [rsi+rbx]
					movd	xmm1, ecx					//xmm1=r0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
					mov		cl,byte ptr [rdi+rbx]
					movd	xmm2, ecx					//xmm2=r0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
					paddw	xmm4,xmm2	//+=d2

					pmaddwd	xmm1,xmm2
					pmaddwd	xmm2,xmm2
					paddd	xmm3,xmm1	//+=d1*d2
					paddd	xmm5,xmm2	//+=d2*d2
				}
			}
			__asm{
				phaddw	xmm4,xmm0	//8->4
				phaddw	xmm4,xmm0	//4->2
				phaddw	xmm4,xmm0	//2->1
				movd	iTargetAddA,xmm4;

				phaddd	xmm3,xmm0	//4->2
				phaddd	xmm5,xmm0	//4->2
				phaddd	xmm3,xmm5	//4->2
				movd	iAddAB,xmm3
				punpckhqdq	xmm3,xmm3
				movd	iTargetAddA2,xmm3

				pop		rdi
				pop		rsi
				pop		rcx
				pop		rax
			}
#else
			for(int x=0;x<Numb;x++){
				int	d1=a[x];
				int	d2=b[x];
				iTargetAddA	+=d2;
				iTargetAddA2+=d2*d2;
				iAddAB		+=d1*d2;
			}
#endif
			TargetAddA	+=iTargetAddA;
			TargetAddA2	+=iTargetAddA2;
			AddAB		+=iAddAB;
		}
	}
	double	AvrS=MasterAddA/DotCount;
	double	AvrD=TargetAddA/DotCount;
	double	M=(MasterAddA2-AvrS*AvrS*DotCount)*(TargetAddA2-AvrD*AvrD*DotCount);
	if(M>0){
		double	R=(AddAB-AvrS*AvrD*DotCount)/sqrt(M);
		return R;
	}
	return 0.0;
}