/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterHResolution\FilterHResolution.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterHResolution.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "SettingHResolutionDialog.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="FilterHResolution";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Extend resolution in horizontal direction";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterHResolution(base);
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

	SettingHResolutionDialog	D(handle->GetLayersBase(),((FilterHResolution *)handle)->Rate);
	if(D.exec()==(int)true){
		((FilterHResolution *)handle)->Rate	=D.Rate;
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
FilterHResolution::FilterHResolution(LayersBase *base)
:FilterClassBase(base)
{	
	Rate		=1;
	IndxRoot	=NULL;
	MultA		=NULL;
	MultB		=NULL;
}

FilterHResolution::~FilterHResolution(void)
{
	Release();
}

bool	FilterHResolution::Save(QIODevice *f)
{
	if(::Save(f,Rate)==false)
		return false;

	return true;
}
bool	FilterHResolution::Load(QIODevice *f)
{
	if(::Load(f,Rate)==false)
		return false;

	return true;
}

bool	FilterHResolution::Initial(void)
{
	if(IndxRoot!=NULL){
		delete	[]IndxRoot;
	}
	if(MultA!=NULL){
		delete	[]MultA;
	}
	if(MultB!=NULL){
		delete	[]MultB;
	}
	IndxRoot	=new int[GetDotPerLine()];
	MultA		=new int[GetDotPerLine()];
	MultB		=new int[GetDotPerLine()];

	for(int x=0;x<GetDotPerLine();x++){
		int	Mx=x*Rate;
		if(Mx>=GetDotPerLine()-2){
			Mx=GetDotPerLine()-2;
		}
		IndxRoot[x]=Mx;
		double	a=x*Rate-Mx;
		MultA[x]=(1.0-a)*256.0;
		MultB[x]=a*256.0;
	}


	return true;
}

bool	FilterHResolution::Release(void)
{
	if(IndxRoot!=NULL){
		delete	[]IndxRoot;
	}
	if(MultA!=NULL){
		delete	[]MultA;
	}
	if(MultB!=NULL){
		delete	[]MultB;
	}
	IndxRoot	=NULL;
	MultA		=NULL;
	MultB		=NULL;

	return true;
}

bool	FilterHResolution::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	XN=GetDotPerLine();
	int	YN=GetMaxLines();
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YN;y++){
			BYTE	TmpBuff[100000];
			for(int i=0;i<BufferDimCounts;i++){
				BYTE	*d=Buff[i]->GetY(y);
				memcpy(TmpBuff,d,XN);
				for(int x=0;x<XN-1;x++){
					int	k=IndxRoot[x];
					d[x]=((int)(TmpBuff[k]*MultA[x]+TmpBuff[k+1]*MultB[x]))>>8;
				}
			}
		}
	}

	return true;
}

void	FilterHResolution::TransmitDirectly(GUIDirectMessage *packet)
{
}
