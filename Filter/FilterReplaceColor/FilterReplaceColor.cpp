/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterReplaceColor\FilterReplaceColor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterReplaceColor.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "SettingDialog.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ReplaceColor";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Replace Color";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterReplaceColor(base);
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

	SettingDialog	D(handle->GetLayersBase(),(FilterReplaceColor *)handle);
	D.exec();
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterReplaceColor::FilterReplaceColor(LayersBase *base)
:FilterClassBase(base)
{	
	SourceLayer	=0;
	AdaptedLayer=0;
	ProcessType	=0;	//0:Replace brightness , 1:Add brightness

	PickupBrightnessLToReplace	=0;
	PickupBrightnessHToReplace	=0;
	AdaptedBrightnessToReplace	=0;

	PickupBrightnessLToShift	=0;
	PickupBrightnessHToShift	=0;
	AddedBrightnessToShift		=0;

}

bool	FilterReplaceColor::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SourceLayer)==false)
		return false;
	if(::Save(f,AdaptedLayer)==false)
		return false;
	if(::Save(f,ProcessType)==false)
		return false;

	if(::Save(f,PickupBrightnessLToReplace)==false)
		return false;
	if(::Save(f,PickupBrightnessHToReplace)==false)
		return false;
	if(::Save(f,AdaptedBrightnessToReplace)==false)
		return false;

	if(::Save(f,PickupBrightnessLToShift)==false)
		return false;
	if(::Save(f,PickupBrightnessHToShift)==false)
		return false;
	if(::Save(f,AddedBrightnessToShift)==false)
		return false;

	return true;
}
bool	FilterReplaceColor::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SourceLayer)==false)
		return false;
	if(::Load(f,AdaptedLayer)==false)
		return false;
	if(::Load(f,ProcessType)==false)
		return false;

	if(::Load(f,PickupBrightnessLToReplace)==false)
		return false;
	if(::Load(f,PickupBrightnessHToReplace)==false)
		return false;
	if(::Load(f,AdaptedBrightnessToReplace)==false)
		return false;

	if(::Load(f,PickupBrightnessLToShift)==false)
		return false;
	if(::Load(f,PickupBrightnessHToShift)==false)
		return false;
	if(::Load(f,AddedBrightnessToShift)==false)
		return false;

	return true;
}

bool	FilterReplaceColor::Initial(void)
{
	return true;
}

bool	FilterReplaceColor::Release(void)
{
	return true;
}

bool	FilterReplaceColor::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	bool	Ret=false;
	if(ProcessType==0){
		Ret=ExecuteReplace(Buff,BufferDimCounts);
	}
	else if(ProcessType==1){
		Ret=ExecuteAdd(Buff,BufferDimCounts);
	}

	return Ret;
}
bool	FilterReplaceColor::ExecuteReplace(ImageBuffer *Buff[],int BufferDimCounts)
{
	ImageBuffer *SB=Buff[SourceLayer];
	ImageBuffer *DB=Buff[AdaptedLayer];

	int	YNumb=GetMaxLines();
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*s=SB->GetY(y);
			BYTE	*d=DB->GetY(y);
			for(int x=0;x<GetDotPerLine();x++){
				short	c=s[x];
				if(PickupBrightnessLToReplace <=c && c<=PickupBrightnessHToReplace){
					d[x]=AdaptedBrightnessToReplace;
				}
			}
		}
	}
	return true;
}

bool	FilterReplaceColor::ExecuteAdd(ImageBuffer *Buff[],int BufferDimCounts)
{
	ImageBuffer *SB=Buff[SourceLayer];
	ImageBuffer *DB=Buff[AdaptedLayer];

	int	YNumb=GetMaxLines();
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*s=SB->GetY(y);
			BYTE	*d=DB->GetY(y);
			for(int x=0;x<GetDotPerLine();x++){
				short	c=s[x];
				if(PickupBrightnessLToShift <=c && c<=PickupBrightnessHToShift){
					int	e=d[x]+AddedBrightnessToShift;
					if(e<0)
						e=0;
					if(e>255)
						e=255;
					d[x]=e;
				}
			}
		}
	}
	return true;
}