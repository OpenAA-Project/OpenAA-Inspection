/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterReverseLens\FilterReverseLens.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterReverseLens.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingReverseLens.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ReverseLens";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(2);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Reversize cosine in width direction";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterReverseLens(base);
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

	SettingReverseLens	D(handle->GetLayersBase()
						,((FilterReverseLens *)handle)->Strength,((FilterReverseLens *)handle)->Width
						,((FilterReverseLens *)handle)->StartX	,((FilterReverseLens *)handle)->EndX
						,parent);
	if(D.exec()==(int)true){
		((FilterReverseLens *)handle)->Strength=D.Strength;
		((FilterReverseLens *)handle)->Width	=D.Width;
		((FilterReverseLens *)handle)->StartX	=D.StartX;
		((FilterReverseLens *)handle)->EndX		=D.EndX;
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
FilterReverseLens::FilterReverseLens(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable=NULL;
	Strength	=1.0;
	Width		=1.0/6.0;
	StartX		=0;
	EndX		=0;
}
FilterReverseLens::~FilterReverseLens(void)
{
	Release();
}

bool	FilterReverseLens::Save(QIODevice *f)
{
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,StartX)==false)
		return false;
	if(::Save(f,EndX)==false)
		return false;
	return true;
}
bool	FilterReverseLens::Load(QIODevice *f)
{
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(GetLoadedDLLVersion()>=2){
		if(::Load(f,StartX)==false)
			return false;
		if(::Load(f,EndX)==false)
			return false;
	}
	return true;
}

bool	FilterReverseLens::Initial(void)
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

bool	FilterReverseLens::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}

bool	FilterReverseLens::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	N=GetMaxLines();
	int	Xn=(EndX==0)?GetDotPerLine():EndX;
	if(Xn>=GetDotPerLine()){
		Xn=GetDotPerLine();
	}
	for(int L=0;L<BufferDimCounts;L++){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[L]->GetY(y);
				for(int x=StartX;x<Xn;x++){
					d[x]=MultiplyTable[(x<<8)+d[x]];
				}
			}
		}
	}
	return true;
}

