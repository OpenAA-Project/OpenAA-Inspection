/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterSmoothLarge\FilterSmoothLarge.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterSmoothLarge.h"
#include "XFilterDLL.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingFormSmoothLarge.h"
#include "swap.h"
#include <omp.h>
#include <memory.h>

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="SmoothLarge";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make smooth-large";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterSmoothLarge(base);
}

bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{

	SettingFormSmoothLarge	D(handle->GetLayersBase(),((FilterSmoothLarge *)handle)->WindowSize,parent);
	if(D.exec()==(int)true){
		((FilterSmoothLarge *)handle)->WindowSize=D.WindowSize;
	}
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterSmoothLarge::FilterSmoothLarge(LayersBase *base)
:FilterClassBase(base)
{	
	TmpBuff=NULL;
	AllocLines=0;
	FormerLineSum=NULL;

	WindowSize=1;
}
FilterSmoothLarge::~FilterSmoothLarge(void)
{
	Release();
}
bool	FilterSmoothLarge::Save(QIODevice *f)
{
	if(::Save(f,WindowSize)==false)
		return false;
	return true;
}
bool	FilterSmoothLarge::Load(QIODevice *f)
{
	if(::Load(f,WindowSize)==false)
		return false;
	return true;
}

bool	FilterSmoothLarge::Initial(void)
{
	Release();

	AllocLines=(WindowSize/2)*2+1;
	TmpBuff	=new int*[AllocLines];
	for(int i=0;i<AllocLines;i++){
		TmpBuff[i]=new int [GetDotPerLine()];
		memset(TmpBuff[i],0,GetDotPerLine()*sizeof(int));
	}
	FormerLineSum=new int[GetDotPerLine()];

	TmpImage.Set(0,0,GetDotPerLine(),GetMaxLines());

	return true;
}

bool	FilterSmoothLarge::Release(void)
{
	if(TmpBuff!=NULL && AllocLines>0){
		for(int i=0;i<AllocLines;i++){
			delete	[]TmpBuff[i];
		}
		delete	[]TmpBuff;
		TmpBuff=NULL;
		AllocLines=0;
	}
	if(FormerLineSum!=NULL){
		delete	[]FormerLineSum;
		FormerLineSum=NULL;
	}

	return true;
}

bool	FilterSmoothLarge::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(WindowSize>0){
		int	YN=GetMaxLines()-WindowSize;
		int	XN=GetDotPerLine()-WindowSize;
		int	XY=65536/(WindowSize*WindowSize);
		for(int L=0;L<BufferDimCounts;L++){
			TmpImage=*Buff[L];
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<YN;y++){				
					BYTE	*d=Buff[L]->GetY(y);
					short		D[16384];
					memset(D,0,XN*sizeof(short));
					for(int i=0;i<WindowSize;i++){
						BYTE	*s=TmpImage.GetY(y+i);
						for(int x=0;x<XN;x++){
							for(int j=0;j<WindowSize;j++){
								D[x]+=s[x+j];
							}
						}
					}
					for(int x=0;x<XN;x++){
						d[x]=(D[x]*XY)>>16;
					}
				}
			}
		}
	}
	return true;



	int	YN=GetMaxLines();
	int	XN=GetDotPerLine()-AllocLines;
	//int	DXNumb=GetDotPerLine();
	int	Numb=AllocLines*AllocLines;
	int	YCount	=YN-AllocLines;

	if(Numb>0){
		for(int L=0;L<BufferDimCounts;L++){
			for(int ny=0;ny<AllocLines;ny++){
				MakeOneSum(TmpBuff[ny],Buff[L]->GetY(ny));
			}
			BYTE	*d=Buff[L]->GetY(0);
			for(int x=0;x<XN;x++){
				int	D=0;
				for(int ny=0;ny<AllocLines;ny++){
					D+=TmpBuff[ny][x];
				}
				FormerLineSum[x]=D;
				d[x]=D/Numb;
			}

			int	APoint=0;
			int	LastPoint=1;
			for(int y=1;y<YCount;y++){
				BYTE	*d=Buff[L]->GetY(y);
				MakeOneSum(TmpBuff[APoint],Buff[L]->GetY(y+AllocLines-1));
				#pragma omp parallel
				{
					#pragma omp for
					for(int x=0;x<XN;x++){
						int	D=FormerLineSum[x]+TmpBuff[APoint][x]-TmpBuff[LastPoint][x];
						FormerLineSum[x]=D;
						d[x]=D/Numb;
					}
				}
				APoint++;
				if(APoint>=AllocLines){
					APoint=0;
				}
				LastPoint++;
				if(LastPoint>=AllocLines){
					LastPoint=0;
				}
			}
		}
		/*
		このインラインアセンブラのために、最適化を禁止しなければならない
		int	i16N= AllocLines/16;
		int	i8N	=(AllocLines-i16N*16)/8;
		int	i4N	=(AllocLines-i16N*16 - i8N*8)/4;
		int	iN	= AllocLines-i16N*16 - i8N*8 -i4N*4;


		__asm	emms

		for(int L=0;L<GetLayerNumb() && L<BufferDimCounts;L++){
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<YCount;y++){

					int	Li16N	= i16N;
					int	Li8N	= i8N;
					int	Li4N	= i4N;
					int	LiN		= iN;
					BYTE	*LPoint[1000];

					for(int ny=0;ny<AllocLines;ny++){
						LPoint[ny]=Buff[L]->GetY(y+ny);
					}

					__asm	pxor	mm0,mm0
					__asm	pxor	xmm0,xmm0

					BYTE	*d=TmpImage.GetY(y);
					for(int x=0;x<XN;x++){
						int	HSum=0;
						for(int ny=0;ny<AllocLines;ny++){
							BYTE	*s=LPoint[ny]+x;
						
							//__asm	push	rax
							//__asm	push	rbx
							//__asm	push	rcx
							//__asm	push	rdx

							__asm	xor		ebx,ebx
							__asm	mov		rdx,s
							__asm	mov		ecx,Li16N
							__asm	jecxz	KK1
KK2:;
							__asm	MOVDQU	xmm1,[rdx]
							__asm	PSADBW	xmm1,xmm0
							__asm	movd	eax,xmm1
							__asm	add		ebx,eax
							__asm	PEXTRD	eax,xmm1,2
							__asm	add		ebx,eax
							__asm	add		rdx,16
							__asm	loop	KK2
KK1:;
							__asm	mov		ecx,Li8N
							__asm	jecxz	KK11
							__asm	movq	mm1,qword ptr [rdx]
							__asm	PSADBW	mm1,mm0
							__asm	movd	eax,mm1
							__asm	add		ebx,eax
							__asm	add		rdx,8
KK11:;
							__asm	mov		ecx,Li4N
							__asm	jecxz	KK21
							__asm	movd	mm1,dword ptr [rdx]
							__asm	PSADBW	mm1,mm0
							__asm	movd	eax,mm1
							__asm	add		ebx,eax
							__asm	add		rdx,4
KK21:
							__asm	xor		eax,eax
							__asm	mov		ecx,LiN
							__asm	jecxz	KK31
KK32:;	
							__asm	mov		al,[rdx]
							__asm	add		ebx,eax
							__asm	inc		rdx
							__asm	loop	KK32
KK31:;
							__asm	add		HSum,ebx

							//__asm	pop		rdx
							//__asm	pop		rcx
							//__asm	pop		rbx
							//__asm	pop		rax
						}
						d[x] = HSum/Numb;
					}
				}
			}
			*Buff[L]=TmpImage;
		}
		*/
		/*
		for(int L=0;L<GetLayerNumb() && L<BufferDimCounts;L++){
			for(int y=0;y<YN;y++){
				BYTE	*d=Buff[L]->GetY(y);
				#pragma omp parallel
				{
					#pragma omp for
					for(int x=0;x<XN;x++){
						int	c=d[x];
						for(int ny=0;ny<AllocLines;ny++){
							int	*B=&TmpBuff[ny][x];
							for(int nx=0;nx<AllocLines;nx++){
								B[nx]+=c;
							}
						}
						d[x] = TmpBuff[0][x]/Numb;
					}
				}
				int	*tmp=TmpBuff[0];
				for(int ny=1;ny<AllocLines;ny++){
					TmpBuff[ny-1]=TmpBuff[ny];
				}
				TmpBuff[AllocLines-1]=tmp;
				memset(tmp,0,DXNumb*sizeof(int));
			}
		}
		*/

	}
	return true;
}

void	FilterSmoothLarge::MakeOneSum(int *TBuff ,BYTE *Source)
{
	int	D=0;
	for(int i=0;i<AllocLines;i++){
		D+=Source[i];
	}
	TBuff[0]=D;
	int	XNumb=GetDotPerLine()-AllocLines;
	BYTE	*p=Source;
	for(int x=1;x<XNumb;x++){
		D+=p[AllocLines]-*p;
		p++;
		TBuff[x]=D;
	}
}

