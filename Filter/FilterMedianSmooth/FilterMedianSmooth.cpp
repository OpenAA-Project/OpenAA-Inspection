/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterMedianSmooth\FilterMedianSmooth.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterMedianSmooth.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingMedianForm.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="MedianSmooth";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Median smoother";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMedianSmooth(base);
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
	FilterMedianSmooth	*H=(FilterMedianSmooth *)handle;
	SettingMedianForm	D(handle->GetLayersBase(),H->FilterDot,parent);
	if(D.exec()==(int)true){
		H->FilterDot	=D.FilterDot;
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
FilterMedianSmooth::FilterMedianSmooth(LayersBase *base)
:FilterClassBase(base)
{	
	TmpImage=NULL;
	AllocatedLayerCount=0;
	FilterDot	=50;
}

bool	FilterMedianSmooth::Save(QIODevice *f)
{
	if(::Save(f,FilterDot)==false)
		return false;
	return true;
}
bool	FilterMedianSmooth::Load(QIODevice *f)
{
	if(::Load(f,FilterDot)==false)
		return false;

	return true;
}

bool	FilterMedianSmooth::Initial(void)
{
	Release();
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	AllocatedLayerCount=GetLayerNumb(LayerNumb);
	TmpImage=new ImageBuffer*[AllocatedLayerCount];
	for(int i=0;i<AllocatedLayerCount;i++){
		TmpImage[i]=new ImageBuffer(0,GetDotPerLine(),GetMaxLines());
		TmpImage[i]->Memset(0);
	}
	return true;
}

bool	FilterMedianSmooth::Release(void)
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

int	FuncDimSort(const void *a ,const void *b)
{
	int d=*((BYTE *)a) - *((BYTE *)b);
	return d;
}


bool	FilterMedianSmooth::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	FilterDot2=FilterDot/2;

	int	AreaDot=FilterDot*FilterDot;
	int	Abandon	=(int)(AreaDot*0.4);
	int	Adopt	=(int)(AreaDot*0.2);

	for(int i=0;i<BufferDimCounts;i++){
		int	YN=GetMaxLines()-FilterDot;
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YN;y++){
				int	Dy=y+FilterDot2;
				BYTE	*d=TmpImage[i]->GetY(Dy);
				int	XN=GetDotPerLine()-FilterDot;
				for(int x=0;x<XN;x++){
					int	Dx=x+FilterDot2;
					int	n=0;
					/*
					BYTE	Dim[2000];
					for(int sy=0;sy<FilterDot;sy++){
						BYTE	*s=Buff[i]->GetY(y+sy);
						for(int sx=0;sx<FilterDot;sx++){
							Dim[n]=s[x+sx];
							n++;
						}
					}
					QSort(Dim,n,1,FuncDimSort);
					int	D=0;
					for(int t=0;t<Adopt;t++){
						D+=Dim[t+Abandon];
					}
					*/
					short	Dim[2000];
					for(int sy=0;sy<FilterDot;sy++){
						BYTE	*s=Buff[i]->GetY(y+sy);
						for(int sx=0;sx<FilterDot;sx++){
							Dim[n]=s[x+sx];
							n++;
						}
					}
					for(int k=0;k<Abandon;k++){
						short	m=0;
						int		Index=0;
						for(int t=0;t<n;t++){
							if(Dim[t]>m){
								m=Dim[t];
								Index=t;
							}
						}
						Dim[Index]=-1;
					}
					int	D=0;
					for(int k=0;k<Adopt;k++){
						short	m=0;
						int		Index=0;
						for(int t=0;t<n;t++){
							if(Dim[t]>m){
								m=Dim[t];
								Index=t;
							}
						}
						D+=m;
						Dim[Index]=-1;
					}

					d[Dx]=D/Adopt;
				}
			}
		}
		*Buff[i]=*TmpImage[i];
	}
	return true;
}
