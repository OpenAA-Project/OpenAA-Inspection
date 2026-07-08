/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include "FilterUpsideDown.h"
#include "XCommonFilterUpsideDown.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "SettingDialog.h"

DEFFUNCEX	bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="UpsideDown";
	return(true);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(2);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make image Upside Down";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterUpsideDown(base);
}

DEFFUNCEX	bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

DEFFUNCEX	bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
DEFFUNCEX	bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
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
DEFFUNCEX	bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
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