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



#include "FilterRotationMirror.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "SettingDialog.h"

DEFFUNCEX	bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="RotationMirror";
	return(true);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make Rotation and Mirror";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterRotationMirror(base);
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
DEFFUNCEX	bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
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