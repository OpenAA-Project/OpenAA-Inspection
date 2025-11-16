/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterSmoothing\FilterSmoothing.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterSmoothing.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingSmoothingForm.h"
#include "swap.h"
#include <omp.h>

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="Smoothing";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make smooth";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterSmoothingClass(base);
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

	SettingSmoothingForm	D(handle->GetLayersBase(),((FilterSmoothingClass *)handle)->MethodValue,parent);
	if(D.exec()==(int)true){
		((FilterSmoothingClass *)handle)->MethodValue=D.MethodValue;
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
FilterSmoothingClass::FilterSmoothingClass(LayersBase *base)
:FilterClassBase(base)
{	
	TmpImage=NULL;
	AllocatedLayerCount=0;
	MethodValue=0;
}

bool	FilterSmoothingClass::Save(QIODevice *f)
{
	if(::Save(f,Length)==false)
		return false;
	if(::Save(f,MethodValue)==false)
		return false;
	return true;
}
bool	FilterSmoothingClass::Load(QIODevice *f)
{
	if(::Load(f,Length)==false)
		return false;
	if(::Load(f,MethodValue)==false)
		return false;
	return true;
}

bool	FilterSmoothingClass::Initial(void)
{
	if(MethodValue==1){
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		AllocatedLayerCount=GetLayerNumb(LayerNumb);
		TmpImage=new ImageBuffer*[AllocatedLayerCount];
		for(int i=0;i<AllocatedLayerCount;i++){
			TmpImage[i]=new ImageBuffer(0,GetDotPerLine(),GetMaxLines());
		}
	}
	return true;
}

bool	FilterSmoothingClass::Release(void)
{
	if(TmpImage!=NULL){
		for(int i=0;i<AllocatedLayerCount;i++){
			delete	TmpImage[i];
		}
		delete	[]TmpImage;
		TmpImage=NULL;
	}
	return true;
}

bool	FilterSmoothingClass::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	ThreadNumb;
	#pragma omp parallel
	{
		ThreadNumb=omp_get_num_threads();
	}

	if(MethodValue==0){
		int	YN=GetMaxLines()-1;
		int	XN=GetDotPerLine();
		int	XNDiv=XN/ThreadNumb;

		for(int y=0;y<YN;y++){
			#pragma omp parallel
			{
				#pragma omp for
				for(int k=0;k<ThreadNumb;k++){
					for(int i=0;i<BufferDimCounts;i++){
						BYTE	*d1=Buff[i]->GetY(y)	+k*XNDiv;
						BYTE	*d2=Buff[i]->GetY(y+1)	+k*XNDiv;
						for(int x=0;x<XNDiv;x++){
							*d1=(*d1+*d2)>>1;
							d1++;
							d2++;
						}
					}
				}
			}
		}
	}
	else if(MethodValue==1){
		for(int i=0;i<BufferDimCounts;i++){
			*TmpImage[i]=*Buff[i];
		}
		int	YLen=GetMaxLines()-3;
		for(int n=0;n<YLen;n++){
			int	y=n+1;
			BYTE	*s0[100];
			BYTE	*s1[100];
			BYTE	*s2[100];
			BYTE	*d[100];
			for(int i=0;i<BufferDimCounts;i++){
				s0[i]=TmpImage[i]->GetY(y-1);
				s1[i]=TmpImage[i]->GetY(y+0);
				s2[i]=TmpImage[i]->GetY(y+1);
				d[i] =Buff[i]->GetY(y);
			}
			for(int x=1;x<GetDotPerLine()-1;x++){
				for(int i=0;i<BufferDimCounts;i++){
					int	L1= *(s0[i]+x-1) + *(s0[i]+x)
						   +*(s1[i]+x-1) + *(s1[i]+x);
					int	L2= *(s0[i]+x) + *(s0[i]+x+1)
						   +*(s1[i]+x) + *(s1[i]+x+1);
					int	L3= *(s1[i]+x-1) + *(s1[i]+x)
						   +*(s2[i]+x-1) + *(s2[i]+x);
					int	L4= *(s1[i]+x) + *(s1[i]+x+1)
						   +*(s2[i]+x) + *(s2[i]+x+1);
					int	LMin=min(min(L1,L2),min(L3,L4));
					int	LMax=max(max(L1,L2),max(L3,L4));
					int	D=((LMax-LMin)*(LMax-LMin))>>8;
					if(D==0)
						D=1;
					*(d[i]+x)=(	 *(s0[i]+x-1) +   *(s0[i]+x) + *(s0[i]+x+1) 
								+*(s1[i]+x-1) + D**(s1[i]+x) + *(s1[i]+x+1)
								+*(s2[i]+x-1) +   *(s2[i]+x) + *(s2[i]+x+1))/(D+8);
				}
			}
		}
	}
	return true;
}

