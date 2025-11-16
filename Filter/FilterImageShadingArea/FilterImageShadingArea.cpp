/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterImageShadingArea\FilterImageShadingArea.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterImageShadingArea.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "XPointer.h"
#include "XGeneralFunc.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ImageShading Area";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Shading for area";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterImageShadingArea(base);
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
	FilterImageShadingArea	*H=(FilterImageShadingArea *)handle;
	SettingDialog	D(handle->GetLayersBase(),H,parent);
	
	D.MagR	=H->MagR;
	D.MagG	=H->MagG;
	D.MagB	=H->MagB;
	D.UsagePhaseNumber	=H->UsagePhaseNumber;
	D.UsagePageNumber	=H->UsagePageNumber;
	D.FileList			=H->FileList;
	D.Reflect();
	if(D.exec()==(int)true){
		H->MagR	=D.MagR;
		H->MagG	=D.MagG;
		H->MagB	=D.MagB;
		H->UsagePhaseNumber	=D.UsagePhaseNumber;
		H->UsagePageNumber	=D.UsagePageNumber;
		H->FileList			=D.FileList;
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
FilterImageShadingArea::FilterImageShadingArea(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplePerDot=NULL;
	XLen	=0;
	YLen	=0;
	LayerNumb=0;

	MagR	=1.0;
	MagG	=1.0;
	MagB	=1.0;
	UsagePhaseNumber=0;
	UsagePageNumber	=0;
}

bool	FilterImageShadingArea::Save(QIODevice *f)
{
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	if(::Save(f,LayerNumb)==false)
		return false;

	if(::Save(f,MagR)==false)
		return false;
	if(::Save(f,MagG)==false)
		return false;
	if(::Save(f,MagB)==false)
		return false;
	if(::Save(f,UsagePhaseNumber)==false)
		return false;
	if(::Save(f,UsagePageNumber)==false)
		return false;
	if(::Save(f,FileList)==false)
		return false;

	if(MultiplePerDot!=NULL){
		for(int L=0;L<LayerNumb;L++){
			if(::Save(f,(BYTE **)MultiplePerDot[L],XLen*2,YLen)==false){
				return false;
			}
		}
	}
	return true;
}
bool	FilterImageShadingArea::Load(QIODevice *f)
{
	int32	tLayerNumb;
	int32	tXLen;
	int32	tYLen;

	if(::Load(f,tXLen)==false)
		return false;
	if(::Load(f,tYLen)==false)
		return false;
	if(::Load(f,tLayerNumb)==false)
		return false;

	if(::Load(f,MagR)==false)
		return false;
	if(::Load(f,MagG)==false)
		return false;
	if(::Load(f,MagB)==false)
		return false;
	if(::Load(f,UsagePhaseNumber)==false)
		return false;
	if(::Load(f,UsagePageNumber)==false)
		return false;
	if(::Load(f,FileList)==false)
		return false;

	BYTE	Dummy[100000];
	Initial();
	if(MultiplePerDot!=NULL){
		int	MinXLen=min(XLen,tXLen);
		int	MinYLen=min(YLen,tYLen);
		for(int L=0;L<LayerNumb && L<tLayerNumb;L++){
			for(int y=0;y<MinYLen;y++){
				if(f->read((char *)(MultiplePerDot[L])[y],MinXLen*2)!=MinXLen*2){
					return false;
				}
				int	LeftX=tXLen-MinXLen;
				if(LeftX!=0){
					if(f->read((char *)Dummy,LeftX*2)!=LeftX*2){
						return false;
					}
				}
			}
			for(int y=MinYLen;y<tYLen;y++){
				if(f->read((char *)Dummy,tXLen*2)!=tXLen*2){
					return false;
				}
			}
		}
	}

	return true;
}

bool	FilterImageShadingArea::Initial(void)
{
	Release();
	LayerNumb=GetLayersBase()->GetMaxLayerNumb();

	XLen	=GetDotPerLine();
	YLen	=GetMaxLines();
	MultiplePerDot	=new short**[LayerNumb];
	for(int L=0;L<LayerNumb;L++){
		MultiplePerDot[L]=(short **)MakeMatrixBuff(XLen*2,YLen);
		MatrixBuffClear	((BYTE **)MultiplePerDot[L] ,0,XLen*2,YLen);
	}
	return true;
}

bool	FilterImageShadingArea::Release(void)
{
	if(MultiplePerDot!=NULL){
		for(int L=0;L<LayerNumb;L++){
			DeleteMatrixBuff((BYTE **)MultiplePerDot[L],YLen);
		}
	}
	return true;
}

bool	FilterImageShadingArea::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(MultiplePerDot==NULL)
		return false;

	int	MinXLen=min(XLen,GetDotPerLine());
	int	MinYLen=min(YLen,GetMaxLines());
	for(int L=0;L<LayerNumb && L<BufferDimCounts;L++){
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<MinYLen;y++){
				BYTE	*d=Buff[L]->GetY(y);
				short	*m=(MultiplePerDot[L])[y];
				for(int x=0;x<MinXLen;x++){
					int	c=((*d)*(*m))>>8;
					*d=Saturation256(c);
					d++;
					m++;
				}
			}
		}
	}

	return true;
}
