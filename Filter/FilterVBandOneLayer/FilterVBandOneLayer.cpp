/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterVBandOneLayer\FilterVBandOneLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterVBandOneLayer.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "SettingBandDialog.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="FilterVBandOneLayer";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Emphasize Vertical band";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterVBandOneLayer(base);
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

	SettingBandDialog	D(handle->GetLayersBase()
						, ((FilterVBandOneLayer *)handle)->Layer 
						, ((FilterVBandOneLayer *)handle)->X1 
						, ((FilterVBandOneLayer *)handle)->X2 
						, ((FilterVBandOneLayer *)handle)->MultipleRate 
						, ((FilterVBandOneLayer *)handle)->Offset);
	if(D.exec()==(int)true){
		((FilterVBandOneLayer *)handle)->Layer	=D.Layer;
		((FilterVBandOneLayer *)handle)->X1		=D.X1;
		((FilterVBandOneLayer *)handle)->X2		=D.X2;
		((FilterVBandOneLayer *)handle)->MultipleRate	=D.MultipleRate; 
		((FilterVBandOneLayer *)handle)->Offset			=D.Offset;
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
FilterVBandOneLayer::FilterVBandOneLayer(LayersBase *base)
:FilterClassBase(base)
{	
	Layer			=0;
	MultipleRate	=1.0;
	Offset			=0;
	X1				=100;
	X2				=200;
}

FilterVBandOneLayer::~FilterVBandOneLayer(void)
{
	Release();
}

bool	FilterVBandOneLayer::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MultipleRate)==false)
		return false;
	if(::Save(f,Offset)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;

	return true;
}
bool	FilterVBandOneLayer::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,MultipleRate)==false)
		return false;
	if(::Load(f,Offset)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;

	return true;
}

bool	FilterVBandOneLayer::Initial(void)
{
	for(int i=0;i<256;i++){
		BandTable[i]=(int)(((double)i*MultipleRate)+Offset);
		if(BandTable[i]>255){
			BandTable[i]=255;
		}
		if(BandTable[i]<0){
			BandTable[i]=0;
		}
	}
	for(int i=0;i<256;i++){
		BandTable1[i]=(int)(((double)i*(1.0+1.0*(MultipleRate-1.0)/4))+1*Offset/4);
		if(BandTable1[i]>255){
			BandTable1[i]=255;
		}
		if(BandTable1[i]<0){
			BandTable1[i]=0;
		}
	}
	for(int i=0;i<256;i++){
		BandTable2[i]=(int)(((double)i*(1.0+2.0*(MultipleRate-1.0)/4))+2*Offset/4);
		if(BandTable2[i]>255){
			BandTable2[i]=255;
		}
		if(BandTable2[i]<0){
			BandTable2[i]=0;
		}
	}
	for(int i=0;i<256;i++){
		BandTable3[i]=(int)(((double)i*(1.0+3.0*(MultipleRate-1.0)/4))+3*Offset/4);
		if(BandTable3[i]>255){
			BandTable3[i]=255;
		}
		if(BandTable3[i]<0){
			BandTable3[i]=0;
		}
	}
	return true;
}

bool	FilterVBandOneLayer::Release(void)
{
	return true;
}

bool	FilterVBandOneLayer::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	XN=GetDotPerLine();
	int	YN=GetMaxLines();
	int	hx1=X1;
	int	hx2=X2;
	if(hx1<3)		hx1=3;
	if(hx2>XN-4)	hx2=XN-4;

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YN;y++){
			BYTE	*d=Buff[Layer]->GetY(y);
			d[hx1-3]=(int)(BandTable1[d[hx1-3]]);
			d[hx1-2]=(int)(BandTable2[d[hx1-2]]);
			d[hx1-1]=(int)(BandTable3[d[hx1-1]]);
			for(int x=hx1;x<=hx2;x++){
				d[x]=(int)(BandTable[d[x]]);
			}
			d[hx2+1]=(int)(BandTable3[d[hx2+1]]);
			d[hx2+2]=(int)(BandTable2[d[hx2+2]]);
			d[hx2+3]=(int)(BandTable1[d[hx2+3]]);
		}
	}

	return true;
}

void	FilterVBandOneLayer::TransmitDirectly(GUIDirectMessage *packet)
{
}
