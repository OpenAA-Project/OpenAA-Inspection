/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterReverseLensOneSide\FilterReverseLensOneSide.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterReverseLensOneSide.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingReverseLensOneside.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ReverseLensOneSide";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Reversize cosine in one side in width direction";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterReverseLensOneSide(base);
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

	SettingReverseLensOneside	D(handle->GetLayersBase()
								 ,((FilterReverseLensOneSide *)handle)->Strength
								 ,((FilterReverseLensOneSide *)handle)->Width
								 ,((FilterReverseLensOneSide *)handle)->LeftSide
								 ,((FilterReverseLensOneSide *)handle)->RightSide
								 ,parent);
	if(D.exec()==(int)true){
		((FilterReverseLensOneSide *)handle)->Strength	=D.Strength;
		((FilterReverseLensOneSide *)handle)->Width		=D.Width;
		((FilterReverseLensOneSide *)handle)->LeftSide	=D.LeftSide;
		((FilterReverseLensOneSide *)handle)->RightSide	=D.RightSide;
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
FilterReverseLensOneSide::FilterReverseLensOneSide(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable=NULL;
	Strength	=1.0;
	Width		=1.0/6.0;
	LeftSide	=false;
	RightSide	=false;
}
FilterReverseLensOneSide::~FilterReverseLensOneSide(void)
{
	Release();
}

bool	FilterReverseLensOneSide::Save(QIODevice *f)
{
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,LeftSide)==false)
		return false;
	if(::Save(f,RightSide)==false)
		return false;
	return true;
}
bool	FilterReverseLensOneSide::Load(QIODevice *f)
{
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,LeftSide)==false)
		return false;
	if(::Load(f,RightSide)==false)
		return false;
	return true;
}

bool	FilterReverseLensOneSide::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Xn=GetDotPerLine();
	MultiplyTable=new int[Xn*256];
	if(Width>0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int x=0;x<Xn;x++){
				double	s=x-GetDotPerLine()/2;
				s=s/GetDotPerLine()*2;
				double	G=cos(s*M_PI*Width);
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=i*(Strength/G);
						if(a>0xFF)
							a=0xFF;
						if(a<0)
							a=0;
						MultiplyTable[(x*256)+i]=a;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for		
			for(int x=0;x<Xn;x++){
				double	s=x-GetDotPerLine()/2;
				s=s/GetDotPerLine()*2;
				double	G=cos(s*M_PI*(-Width));
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=i*(Strength*G);
						if(a>0xFF)
							a=0xFF;
						if(a<0)
							a=0;
						MultiplyTable[(x*256)+i]=a;
					}
				}
			}
		}
	}
	return true;
}

bool	FilterReverseLensOneSide::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}

bool	FilterReverseLensOneSide::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	Xn2=GetDotPerLine()/2;
	int	N=GetMaxLines();
	int	Xn=GetDotPerLine();

	for(int L=0;L<BufferDimCounts;L++){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[L]->GetY(y);
				if(LeftSide==true){
					for(int x=0;x<Xn2;x++){
						d[x]=MultiplyTable[(x<<8)+d[x]];
					}
				}
				if(RightSide==true){
					for(int x=Xn2;x<Xn;x++){
						d[x]=MultiplyTable[(x<<8)+d[x]];
					}
				}
			}
		}
	}
	return true;
}

