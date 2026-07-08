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



#include "FilterMoveImage.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingMoveImageForm.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "XCommonFilterMoveImage.h"

DEFFUNCEX	bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="MoveImage";
	return(true);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Move image";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMoveImage(base);
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

	SettingMoveImageForm	D(handle->GetLayersBase(),((FilterMoveImage *)handle)->Dx,((FilterMoveImage *)handle)->Dy);
	if(D.exec()==(int)true){
		((FilterMoveImage *)handle)->Dx	=D.Dx;
		((FilterMoveImage *)handle)->Dy	=D.Dy;
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
FilterMoveImage::FilterMoveImage(LayersBase *base)
:FilterClassBase(base)
{	
	Dx	=0;
	Dy	=0;
}

bool	FilterMoveImage::Save(QIODevice *f)
{
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	FilterMoveImage::Load(QIODevice *f)
{
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

bool	FilterMoveImage::Initial(void)
{
	return true;
}

bool	FilterMoveImage::Release(void)
{
	return true;
}

bool	FilterMoveImage::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(BufferDimCounts==1){
		Buff[0]->MoveImage(Dx,Dy);
	}
	else{
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<BufferDimCounts;i++){
				Buff[i]->MoveImage(Dx,Dy);
			}
		}
	}
	return true;
}

void	FilterMoveImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdFilterReqXY	*CmdFilterReqXYVar=dynamic_cast<CmdFilterReqXY *>(packet);
	if(CmdFilterReqXYVar!=NULL){
		CmdFilterReqXYVar->MovX	=Dx;
		CmdFilterReqXYVar->MovY	=Dy;
		return;
	}
	CmdFilterSetXY	*CmdFilterSetXYVar=dynamic_cast<CmdFilterSetXY *>(packet);
	if(CmdFilterSetXYVar!=NULL){
		Dx	=CmdFilterSetXYVar->MovX;
		Dy	=CmdFilterSetXYVar->MovY;
		return;
	}
}