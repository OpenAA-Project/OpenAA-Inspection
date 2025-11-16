/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterBrightnessLogConvert\FilterBrightnessLogConvert.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterBrightnessLogConvert.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "FilterSettingDialog.h"
#include "XPointer.h"

bool		DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="BrightnessLogConvert";
	return(true);
}

WORD		DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Convert brightness logarithmically";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterBrightnessLogConvert(base);
}

bool		DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool		DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool		DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	FilterBrightnessLogConvert	*v=(FilterBrightnessLogConvert *)handle;
	FilterSettingDialog	D(v->Position ,v->Strength ,handle->GetLayersBase(),parent);
	D.exec();
	v->Position	=D.Position;
	v->Strength	=D.Strength;
	return true;
}
bool		DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterBrightnessLogConvert::FilterBrightnessLogConvert(LayersBase *base)
	:FilterClassBase(base)
{	
	Position	=128;
	Strength	=10.0;
}
FilterBrightnessLogConvert::~FilterBrightnessLogConvert(void)
{
}

bool	FilterBrightnessLogConvert::Save(QIODevice *f)
{
	if(::Save(f,Position)==false)
		return false;
	if(::Save(f,Strength)==false)
		return false;
	return true;
}
bool	FilterBrightnessLogConvert::Load(QIODevice *f)
{
	if(::Load(f,Position)==false)
		return false;
	if(::Load(f,Strength)==false)
		return false;
	return true;
}
bool	FilterBrightnessLogConvert::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return true;
}

bool	FilterBrightnessLogConvert::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterBrightnessLogConvert::Initial(void)
{
	//a(x-b)^2+c=y
	//Peak(Xp,Yp)
	//b=Xp, c=Yp
	//a1*Xp*Xp+Yp=0		a1=-Yp/(Xp*Xp)
	//a2(Xm-Xp)^2+Yp=0

	double	Xp=Position;
	double	Yp=Strength*(256-Position)/100.0;
	double	a1=-Yp/(Xp*Xp);
	double	a2=-Yp/((256-Xp)*(256-Xp));

	for(int x=0;x<Position;x++){
		double	d=a1*(x-Xp)*(x-Xp)+Yp;
		int	D=d+x;
		if(D<0)
			D=0;
		if(D>255)
			D=255;
		TransTable[x]=D;
	}
	for(int x=Position;x<256;x++){
		double	d=a2*(x-Xp)*(x-Xp)+Yp;
		int	D=d+x;
		if(D<0)
			D=0;
		if(D>255)
			D=255;
		TransTable[x]=D;
	}		

	return true;
}

bool	FilterBrightnessLogConvert::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	YLen=GetMaxLines();
	int	XLen=GetDotPerLine();

	for(int L=0;L<BufferDimCounts;L++){
		ImageBuffer *B=Buff[L];
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<YLen;y++){
				BYTE	*d=B->GetY(y);
				for(int x=0;x<XLen;x++){
					d[x]=TransTable[d[x]];
				}
			}
		}
	}	

	return true;
}

