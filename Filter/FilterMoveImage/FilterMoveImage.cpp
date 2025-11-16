/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterMoveImage\FilterMoveImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="MoveImage";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Move image";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMoveImage(base);
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

	SettingMoveImageForm	D(handle->GetLayersBase(),((FilterMoveImage *)handle)->Dx,((FilterMoveImage *)handle)->Dy);
	if(D.exec()==(int)true){
		((FilterMoveImage *)handle)->Dx	=D.Dx;
		((FilterMoveImage *)handle)->Dy	=D.Dy;
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
