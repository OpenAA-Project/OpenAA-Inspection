/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterEvenOdd\FilterEvenOdd.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterEvenOdd.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>


bool		DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="EvenOdd";
	return(true);
}

WORD		DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Adjust even and odd gain";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterEvenOdd(base);
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
	FilterEvenOdd	*v=(FilterEvenOdd *)handle;
	SettingDialog	D(handle->GetLayersBase(),v,parent);
	D.exec();
	return true;
}
bool		DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterEvenOdd::FilterEvenOdd(LayersBase *base)
:FilterClassBase(base)
{	
	ALeftEven	=1.0;
	ALeftOdd	=1.0;
	ARightEven	=1.0;
	ARightOdd	=1.0;
	MultiplyTable	=NULL;
}
FilterEvenOdd::~FilterEvenOdd(void)
{
	Release();
}

bool	FilterEvenOdd::Save(QIODevice *f)
{
	if(::Save(f,ALeftEven)==false)
		return false;
	if(::Save(f,ALeftOdd)==false)
		return false;
	if(::Save(f,ARightEven)==false)
		return false;
	if(::Save(f,ARightOdd)==false)
		return false;
	return true;
}
bool	FilterEvenOdd::Load(QIODevice *f)
{
	if(::Load(f,ALeftEven)==false)
		return false;
	if(::Load(f,ALeftOdd)==false)
		return false;
	if(::Load(f,ARightEven)==false)
		return false;
	if(::Load(f,ARightOdd)==false)
		return false;
	return true;
}

bool	FilterEvenOdd::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Xn=GetDotPerLine();
	MultiplyTable=new int[Xn*256];
	int	Xn2=Xn/2;
	for(int x=0;x<Xn2;x++){
		double	d;
		if((x&1)==0)
			d=ALeftEven;
		else
			d=ALeftOdd;
		for(int i=0;i<256;i++){
			int	a=i*d;
			if(a>0xFF)
				a=0xFF;
			MultiplyTable[(x*256)+i]=a;
		}
	}
	for(int x=Xn2;x<Xn;x++){
		double	d;
		if((x&1)==0)
			d=ARightEven;
		else
			d=ARightOdd;
		for(int i=0;i<256;i++){
			int	a=i*d;
			if(a>0xFF)
				a=0xFF;
			MultiplyTable[(x*256)+i]=a;
		}
	}
	return true;
}

bool	FilterEvenOdd::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}
bool	FilterEvenOdd::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	Release();
	Initial();
	return true;
}

bool	FilterEvenOdd::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterEvenOdd::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	for(int L=0;L<BufferDimCounts;L++){
		int	N=GetMaxLines();
		int	Xn=GetDotPerLine();
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[L]->GetY(y);
				for(int x=0;x<Xn;x++){
					d[x]=MultiplyTable[(x<<8)+d[x]];
				}
			}
		}
	}
	return true;
}

