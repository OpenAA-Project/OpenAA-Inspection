/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterReverseCosineRing\FilterReverseCosineRing.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterReverseCosineRing.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ReverseCosineRing";
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
	return new FilterReverseCosineRing(base);
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

	SettingDialog	D(handle->GetLayersBase()
						,((FilterReverseCosineRing *)handle)->Strength
						,((FilterReverseCosineRing *)handle)->Width
						,parent);
	if(D.exec()==(int)true){
		((FilterReverseCosineRing *)handle)->Strength	=D.Strength;
		((FilterReverseCosineRing *)handle)->Width		=D.Width;
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
FilterReverseCosineRing::FilterReverseCosineRing(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable	=NULL;
	AllocatedLines	=0;
	AllocatedWidth	=0;
	Strength		=1.0;
	Width			=1.0/6.0;
}
FilterReverseCosineRing::~FilterReverseCosineRing(void)
{
	Release();
}

bool	FilterReverseCosineRing::Save(QIODevice *f)
{
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	return true;
}
bool	FilterReverseCosineRing::Load(QIODevice *f)
{
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	return true;
}

bool	FilterReverseCosineRing::Initial(void)
{
	if(MultiplyTable!=NULL){
		for(int y=0;y<AllocatedLines;y++){
			delete	[]MultiplyTable[y];
		}
		delete	[]MultiplyTable;
	}
	AllocatedLines=GetMaxLines();
	MultiplyTable=new unsigned short *[AllocatedLines];
	AllocatedWidth=GetDotPerLine();
	for(int y=0;y<AllocatedLines;y++){
		MultiplyTable[y]=new unsigned short[AllocatedWidth];
	}
	double	Len=hypot(AllocatedWidth,AllocatedLines)/2.0;

	if(Width>0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<AllocatedLines;y++){
				double	YLen=y-AllocatedLines/2.0;
				for(int x=0;x<AllocatedWidth;x++){
					double	XLen=x-AllocatedWidth/2.0;
					double	s=hypot(XLen,YLen);
					s=s/Len;
					double	G=cos(s*2.0*M_PI*Width);
					if(G>0){
						double	D=1024.0*1.0/G;
						if(D<65536){
							*(MultiplyTable[y]+x)=(unsigned short)D;
						}
						else{
							*(MultiplyTable[y]+x)=1024;
						}
					}
					else{
						*(MultiplyTable[y]+x)=1024;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<AllocatedLines;y++){
				double	YLen=y-AllocatedLines/2.0;
				for(int x=0;x<AllocatedWidth;x++){
					double	XLen=x-AllocatedWidth/2.0;
					double	s=hypot(XLen,YLen);
					s=s/Len;
					double	G=cos(s*2.0*M_PI*(-Width));
					if(G>0){
						double	D=1024.0*1.0*G;
						if(D<65536){
							*(MultiplyTable[y]+x)=(unsigned short)D;
						}
						else{
							*(MultiplyTable[y]+x)=1024;
						}
					}
					else{
						*(MultiplyTable[y]+x)=1024;
					}
				}
			}
		}
	}
	return true;
}

bool	FilterReverseCosineRing::Release(void)
{
	if(MultiplyTable!=NULL){
		for(int y=0;y<AllocatedLines;y++){
			delete	[]MultiplyTable[y];
		}
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	AllocatedLines	=0;
	AllocatedWidth	=0;

	return true;
}

bool	FilterReverseCosineRing::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	for(int L=0;L<BufferDimCounts;L++){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<AllocatedLines;y++){
				BYTE	*d=Buff[L]->GetY(y);
				unsigned short	*M=MultiplyTable[y];
				for(int x=0;x<AllocatedWidth;x++){
					int	k=(((int)d[x])*((int)M[x]))>>10;
					if(0<=k && k<256){
						d[x]=k;
					}
					else if(k<0){
						d[x]=0;
					}
					else{
						d[x]=255;
					}
				}
			}
		}
	}
	return true;
}

