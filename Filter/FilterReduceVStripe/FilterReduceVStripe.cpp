/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterReduceVStripe\FilterReduceVStripe.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterReduceVStripe.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ReduceVStripe";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Reduce Vertical Stripe by 1024";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterReduceVStripe(base);
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

	//SettingOneLayerForm	D(handle->GetLayersBase()
	//					, ((FilterReduceVStripe *)handle)->Layer
	//					, ((FilterReduceVStripe *)handle)->GetLayerNumb()
	//					, ((FilterReduceVStripe *)handle)->MethodValue
	//					, ((FilterReduceVStripe *)handle)->Param,parent);
	//if(D.exec()==(int)true){
	//	((FilterReduceVStripe *)handle)->Layer		=D.Layer;
	//	((FilterReduceVStripe *)handle)->MethodValue	=D.MethodValue;
	//	((FilterReduceVStripe *)handle)->Param		=D.Param;
	//}
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterReduceVStripe::FilterReduceVStripe(LayersBase *base)
:FilterClassBase(base)
{	
	FirstMode	=true;
	Step		=1024;
	TopY		=10;
	YLen		=30;
	BoxSize		=50;
}

bool	FilterReduceVStripe::Save(QIODevice *f)
{
	if(::Save(f,Step)==false)
		return false;
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	if(::Save(f,BoxSize)==false)
		return false;
	return true;
}
bool	FilterReduceVStripe::Load(QIODevice *f)
{
	if(::Load(f,Step)==false)
		return false;
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YLen)==false)
		return false;
	if(::Load(f,BoxSize)==false)
		return false;
	return true;
}

bool	FilterReduceVStripe::Initial(void)
{
	FirstMode	=true;
	return true;
}

bool	FilterReduceVStripe::Release(void)
{
	return true;
}

bool	FilterReduceVStripe::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	XLen=GetDotPerLine();
	int	XNumb=(XLen+Step-1)/Step;

	for(int i=0;i<XNumb;i++){
		for(int layer=0;layer<BufferDimCounts;layer++){
			CurrentBrightness[i][0][layer]=GetBoxBrightness(i*Step+1,TopY,i*Step+1+BoxSize,TopY+YLen
															,Buff[layer]);
			int	X2=i*Step+Step-1;
			if(X2>=XLen){
				X2=XLen-1;
			}
			CurrentBrightness[i][1][layer]=GetBoxBrightness(X2-BoxSize,TopY,X2,TopY+YLen,Buff[layer]);
		}
	}
	int	CXPoint=XNumb/2;
	for(int layer=0;layer<BufferDimCounts;layer++){
		AddBrightness[CXPoint][layer]=0;
		for(int i=CXPoint-1;i>=1;i--){
			if(CurrentBrightness[i-1][1][layer]<CurrentBrightness[i][0][layer] && CurrentBrightness[i][1][layer]>CurrentBrightness[i+1][0][layer]){
				AddBrightness[i][layer]=CurrentBrightness[i+1][0][layer]-CurrentBrightness[i][1][layer];
			}
			else
			if(CurrentBrightness[i-1][1][layer]>CurrentBrightness[i][0][layer] && CurrentBrightness[i][1][layer]<CurrentBrightness[i+1][0][layer]){
				AddBrightness[i][layer]=CurrentBrightness[i+1][0][layer]-CurrentBrightness[i][1][layer];
			}
			else{
				AddBrightness[i][layer]=0;
			}
		}
		if(CurrentBrightness[0][1][layer]>CurrentBrightness[1][0][layer]){
			AddBrightness[0][layer]=CurrentBrightness[1][0][layer]-CurrentBrightness[0][1][layer];
		}
		else
		if(CurrentBrightness[0][1][layer]<CurrentBrightness[1][0][layer]){
			AddBrightness[0][layer]=CurrentBrightness[1][0][layer]-CurrentBrightness[0][1][layer];
		}
		else{
			AddBrightness[0][layer]=0;
		}
		for(int i=CXPoint+1;i<XNumb-1;i++){
			if(CurrentBrightness[i-1][1][layer]<CurrentBrightness[i][0][layer] && CurrentBrightness[i][1][layer]>CurrentBrightness[i+1][0][layer]){
				AddBrightness[i][layer]=CurrentBrightness[i-1][1][layer]-CurrentBrightness[i][0][layer];
			}
			else
			if(CurrentBrightness[i-1][1][layer]<CurrentBrightness[i][0][layer] && CurrentBrightness[i][1][layer]>CurrentBrightness[i+1][0][layer]){
				AddBrightness[i][layer]=CurrentBrightness[i-1][1][layer]-CurrentBrightness[i][0][layer];
			}
			else{
				AddBrightness[i][layer]=0;
			}
		}
		if(CurrentBrightness[XNumb-2][1][layer]>CurrentBrightness[XNumb-1][0][layer]){
			AddBrightness[XNumb-1][layer]=CurrentBrightness[XNumb-2][1][layer]-CurrentBrightness[XNumb-1][0][layer];
		}
		else
		if(CurrentBrightness[XNumb-2][1][layer]<CurrentBrightness[XNumb-1][0][layer]){
			AddBrightness[XNumb-1][layer]=CurrentBrightness[XNumb-2][1][layer]-CurrentBrightness[XNumb-1][0][layer];
		}
		else{
			AddBrightness[XNumb-1][layer]=0;
		}
	}
	if(FirstMode==true){
		for(int i=0;i<XNumb;i++){
			for(int layer=0;layer<BufferDimCounts;layer++){
				IdealBrightness[i][0][layer]=CurrentBrightness[i][0][layer]+AddBrightness[i][layer];
				IdealBrightness[i][1][layer]=CurrentBrightness[i][1][layer]+AddBrightness[i][layer];
			}
		}
		FirstMode=false;
	}
	int	YLen=GetMaxLines();
	for(int layer=0;layer<BufferDimCounts;layer++){
		double	AddedM=0;
		for(int i=0;i<XNumb;i++){
			AddedM+=IdealBrightness[i][0][layer];
		}
		double	AddedT=0;
		for(int i=0;i<XNumb;i++){
			AddedT+=CurrentBrightness[i][0][layer]+AddBrightness[i][layer];
		}
		double	AvrM=AddedM/XNumb;
		double	AvrT=AddedT/XNumb;

		int	Diff=AvrM-AvrT;


		#pragma omp parallel
		{
			#pragma omp for
				for(int y=0;y<YLen;y++){
				BYTE	*d=Buff[layer]->GetY(y);
				for(int i=0;i<XNumb;i++){
					int	X=Step*i;
					int	DLen=Step;
					if(X+DLen>=XLen){
						DLen=XLen-X;
					}
					for(int x=0;x<DLen;x++){
						d[X+x]=Clipping(d[X+x]+AddBrightness[i][layer] + Diff,0,255);
					}
				}
			}
		}
	}

	return true;
}

double	FilterReduceVStripe::GetBoxBrightness(int x1 ,int y1 ,int x2,int y2, ImageBuffer *Buff)
{
	double	A=0;
	for(int y=y1;y<y2;y++){
		BYTE	*s=Buff->GetY(y);
		int	D=0;
		for(int x=x1;x<x2;x++){
			D+=s[x];
		}
		A+=D;
	}
	return A/((x2-x1)*(y2-y1));
}
