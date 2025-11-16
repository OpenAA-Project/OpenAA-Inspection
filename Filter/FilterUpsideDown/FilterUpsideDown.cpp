/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterSmoothing\FilterSmoothing.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterUpsideDown.h"
#include "XCommonFilterUpsideDown.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "SettingDialog.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="UpsideDown";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(2);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make image Upside Down";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterUpsideDown(base);
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
	FilterUpsideDown	*H=(FilterUpsideDown *)handle;
	SettingDialog	D(handle->GetLayersBase(),H->UseShouldExecute);
	if(D.exec()==true){
		H->UseShouldExecute=D.UseShouldExecute;
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
FilterUpsideDown::FilterUpsideDown(LayersBase *base)
:FilterClassBase(base)
{
	ShouldExecute=false;
	UseShouldExecute=true;
}

bool	FilterUpsideDown::Initial(void)
{
	return true;
}

bool	FilterUpsideDown::Release(void)
{
	return true;
}

bool	FilterUpsideDown::Save(QIODevice *f)
{
	if(GetDLLVersion()>=2){
		if(::Save(f,UseShouldExecute)==false){
			return false;
		}
	}
	return true;
}

bool	FilterUpsideDown::Load(QIODevice *f)
{
	if(GetDLLVersion()>=2){
		if(::Load(f,UseShouldExecute)==false){
			return false;
		}
	}
	return true;
}

bool	FilterUpsideDown::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(ShouldExecute==true || UseShouldExecute==false){
		for(int i=0;i<BufferDimCounts;i++){
			Buff[i]->TopsideBottom();
		}
	}
	ShouldExecute=false;
	return true;
}

void	FilterUpsideDown::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdExecuteFilter	*CmdExecuteFilterVar=dynamic_cast<CmdExecuteFilter *>(packet);
	if(CmdExecuteFilterVar!=NULL){
		ShouldExecute=true;
		return;
	}
	CmdExecuteClearFilter	*CmdExecuteClearFilterVar=dynamic_cast<CmdExecuteClearFilter *>(packet);
	if(CmdExecuteClearFilterVar!=NULL){
		ShouldExecute=false;
		return;
	}
}