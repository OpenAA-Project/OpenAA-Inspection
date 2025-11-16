/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterDynamicBrightness\FilterDynamicBrightness.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterDynamicBrightness.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "XPointer.h"
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="DynamicBrightness";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Change brightness dynamically";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterDynamicBrightness(base);
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
	FilterDynamicBrightness	*v=(FilterDynamicBrightness *)handle;
	SettingDialog	D(handle->GetLayersBase(),v,parent);
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
FilterDynamicBrightness::FilterDynamicBrightness(LayersBase *base)
	:FilterClassBase(base)
{	
	CheckPointX		=6700;
	CheckPointWidth	=300;
	ExeX1			=4096;
	ExeX2			=8191;
	GainP			=0.96;
	GainM			=1.04;
	StaticBrightness		=18;
	CurrentBrightness	=NULL;
	TmpDim				=NULL;
}
FilterDynamicBrightness::~FilterDynamicBrightness(void)
{
	if(CurrentBrightness!=NULL){
		delete	[]CurrentBrightness;
		CurrentBrightness=NULL;
	}
	if(TmpDim!=NULL){
		delete	[]TmpDim;
		TmpDim=NULL;
	}
}

bool	FilterDynamicBrightness::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,CheckPointX)==false)
		return false;
	if(::Save(f,ExeX1)==false)
		return false;
	if(::Save(f,ExeX2)==false)
		return false;
	if(::Save(f,GainP)==false)
		return false;
	if(::Save(f,GainM)==false)
		return false;
	if(::Save(f,StaticBrightness)==false)
		return false;
	return true;
}
bool	FilterDynamicBrightness::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,CheckPointX)==false)
		return false;
	if(::Load(f,ExeX1)==false)
		return false;
	if(::Load(f,ExeX2)==false)
		return false;
	if(::Load(f,GainP)==false)
		return false;
	if(::Load(f,GainM)==false)
		return false;
	if(::Load(f,StaticBrightness)==false)
		return false;
	return true;
}
bool	FilterDynamicBrightness::Initial(void)
{
	if(CheckPointX<1)
		CheckPointX=1;
	if(GetDotPerLine()-1<=CheckPointX)
		CheckPointX=GetDotPerLine()-2;

	if(ExeX1<0)
		ExeX1=0;
	if(GetDotPerLine()<=ExeX1)
		ExeX1=GetDotPerLine()-1;
	if(ExeX2<0)
		ExeX2=0;
	if(GetDotPerLine()<=ExeX2)
		ExeX2=GetDotPerLine()-1;

	if(CurrentBrightness!=NULL){
		delete	[]CurrentBrightness;
	}
	CurrentBrightness=new double [GetMaxLines()];

	if(TmpDim!=NULL){
		delete	[]TmpDim;
	}
	TmpDim=new double [GetMaxLines()];

	return true;
}
bool	FilterDynamicBrightness::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(CurrentBrightness!=NULL){
		delete	[]CurrentBrightness;
	}
	CurrentBrightness=new double [NewMaxLines];

	if(TmpDim!=NULL){
		delete	[]TmpDim;
	}
	TmpDim=new double [NewMaxLines];

	return true;
}

bool	FilterDynamicBrightness::Reallocate(int newLayerNumb)
{
	return true;
}
int FuncDouble(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(*pa>*pb)
		return 1;
	if(*pa<*pb)
		return -1;
	return 0;
}


bool	FilterDynamicBrightness::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int YLen=GetMaxLines();

	for(int L=0;L<BufferDimCounts;L++){
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				double	BrightnessL=0;
				BYTE	*sY1=Buff[L]->GetY(y);
				for(int i=0;i<CheckPointWidth;i++){
					BrightnessL+=sY1[CheckPointX+i];
				}
				CurrentBrightness[y]=BrightnessL/((double)CheckPointWidth);
				TmpDim[y]	=CurrentBrightness[y];
			}
		}

		QSort(TmpDim,YLen,sizeof(double),FuncDouble);
		int	DN=YLen/8;
		int	Count=0;
		double	Br=0;
		for(int i=YLen/16;i<DN;i++){
			Br+=TmpDim[i];
			Count++;
		}
		double	DarkLevel=Br/Count;

		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				double	BrightnessL=CurrentBrightness[y];
				BYTE	*d=Buff[L]->GetY(y);
				if(BrightnessL<DarkLevel){
					for(int x=ExeX1;x<ExeX2;x++){
						d[x]=Clipping((int)(d[x]+(DarkLevel-BrightnessL)*GainM),0,255);
					}
				}
				else if(BrightnessL>DarkLevel){
					for(int x=ExeX1;x<ExeX2;x++){
						d[x]=Clipping((int)(d[x]-(BrightnessL-DarkLevel)*GainP),0,255);
					}
				}
			}
		}
	}	

	return true;
}

