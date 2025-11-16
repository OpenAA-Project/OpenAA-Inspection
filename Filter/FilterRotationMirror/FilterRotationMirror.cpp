/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterRotationMirror\FilterRotationMirror.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterRotationMirror.h"
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
	str="RotationMirror";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make Rotation and Mirror";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterRotationMirror(base);
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
					, ((FilterRotationMirror *)handle)->UpsideDown
					, ((FilterRotationMirror *)handle)->LeftRight
					, ((FilterRotationMirror *)handle)->Angle);
	if(D.exec()==(int)true){
		((FilterRotationMirror *)handle)->UpsideDown	=D.UpsideDown;
		((FilterRotationMirror *)handle)->LeftRight		=D.LeftRight;
		((FilterRotationMirror *)handle)->Angle			=D.Angle;
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
FilterRotationMirror::FilterRotationMirror(LayersBase *base)
:FilterClassBase(base)
{	
	UpsideDown	=false;
	LeftRight	=false;
	Angle		=0;
}

bool	FilterRotationMirror::Save(QIODevice *f)
{
	if(::Save(f,UpsideDown)==false)
		return false;
	if(::Save(f,LeftRight)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	return true;
}
bool	FilterRotationMirror::Load(QIODevice *f)
{
	if(::Load(f,UpsideDown)==false)
		return false;
	if(::Load(f,LeftRight)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	return true;
}

bool	FilterRotationMirror::Initial(void)
{
	return true;
}

bool	FilterRotationMirror::Release(void)
{
	return true;
}

bool	FilterRotationMirror::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(UpsideDown==true){
		for(int i=0;i<BufferDimCounts;i++){
			Buff[i]->TopsideBottom();
		}
	}
	if(LeftRight==true){
		for(int i=0;i<BufferDimCounts;i++){
			Buff[i]->LeftsideRight();
		}
	}
	return true;
}

void	FilterRotationMirror::TransmitDirectly(GUIDirectMessage *packet)
{
}
