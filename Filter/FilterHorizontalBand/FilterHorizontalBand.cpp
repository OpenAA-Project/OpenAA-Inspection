/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterHorizontalBand\FilterHorizontalBand.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterHorizontalBand.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingFilterHorizontalBand.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="HorizontalBand";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Horizontally change Band brightness";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterHorizontalBand(base);
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

	SettingFilterHorizontalBand		D(handle->GetLayersBase()
										,((FilterHorizontalBand *)handle)->Gain
										,((FilterHorizontalBand *)handle)->CenterX
										,((FilterHorizontalBand *)handle)->BandWidth
										,((FilterHorizontalBand *)handle)->GradationWidth
										,((FilterHorizontalBand *)handle)->Layers
										,((FilterHorizontalBand *)handle)->Gamma
										 ,parent);
	if(D.exec()==(int)true){
		((FilterHorizontalBand *)handle)->Gain			=D.Gain;
		((FilterHorizontalBand *)handle)->CenterX		=D.CenterX;
		((FilterHorizontalBand *)handle)->BandWidth		=D.BandWidth;
		((FilterHorizontalBand *)handle)->GradationWidth=D.GradationWidth;
		((FilterHorizontalBand *)handle)->Layers		=D.Layers;
		((FilterHorizontalBand *)handle)->Gamma			=D.Gamma;
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
FilterHorizontalBand::FilterHorizontalBand(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable	=NULL;
	Gain		=1.0;
	CenterX		=0;
	BandWidth	=100;
	GradationWidth=100;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		Layers.Add(true);
	}
	Gamma	=1.0;
}
FilterHorizontalBand::~FilterHorizontalBand(void)
{
	Release();
}

bool	FilterHorizontalBand::Save(QIODevice *f)
{
	if(::Save(f,Gain)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,BandWidth)==false)
		return false;
	if(::Save(f,GradationWidth)==false)
		return false;
	if(Layers.Save(f)==false)
		return false;
	if(::Save(f,Gamma)==false)
		return false;
	return true;
}
bool	FilterHorizontalBand::Load(QIODevice *f)
{
	if(::Load(f,Gain)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,BandWidth)==false)
		return false;
	if(::Load(f,GradationWidth)==false)
		return false;
	if(Layers.Load(f)==false)
		return false;
	if(::Load(f,Gamma)==false)
		return false;
	return true;
}
double	GetGamma(double m ,double Gamma)
{
	return m*(1.0-pow(m/2000,Gamma));
}
bool	FilterHorizontalBand::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Xn=GetDotPerLine();
	MultiplyTable=new int[Xn*256];

	#pragma omp parallel
	{
		#pragma omp for		
		for(int i=0;i<GradationWidth;i++){
			int	x=-(GradationWidth-i)-BandWidth/2+CenterX;
			if(0<=x && x<Xn){
				double	PosGain=(Gain-1.0)*i/GradationWidth +1.0;
				for(int k=0;k<256;k++){
					int	c=GetGamma(PosGain*k,Gamma);
					if(c<0)
						c=0;
					if(c>=256)
						c=255;
					MultiplyTable[(x*256)+k]=c;
				}
			}
		}
	}
	#pragma omp parallel
	{
		#pragma omp for		
		for(int i=0;i<BandWidth;i++){
			int	x=CenterX+i-BandWidth/2;
			if(0<=x && x<Xn){
				for(int k=0;k<256;k++){
					int	c=GetGamma(Gain*k,Gamma);
					if(c<0)
						c=0;
					if(c>=256)
						c=255;
					MultiplyTable[(x*256)+k]=c;
				}
			}
		}
	}
	#pragma omp parallel
	{
		#pragma omp for		
		for(int i=0;i<GradationWidth;i++){
			int	x=i+BandWidth/2+CenterX;
			if(0<=x && x<Xn){
				double	PosGain=(Gain-1.0)*(GradationWidth-i)/GradationWidth +1.0;
				for(int k=0;k<256;k++){
					int	c=GetGamma(PosGain*k,Gamma);
					if(c<0)
						c=0;
					if(c>=256)
						c=255;
					MultiplyTable[(x*256)+k]=c;
				}
			}
		}
	}

	return true;
}

bool	FilterHorizontalBand::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}
bool	FilterHorizontalBand::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	Release();
	Initial();
	return true;
}

bool	FilterHorizontalBand::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterHorizontalBand::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	N=GetMaxLines();
	int	Xn=GetDotPerLine();

	for(int L=0;L<BufferDimCounts;L++){
		if(Layers.GetCount()<L || Layers[L]==false)
			continue;

		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[L]->GetY(y);
				for(int x=0;x<Xn;x++){
					d[x]=MultiplyTable[(x<<8)+d[x]];
				}
			}
		}
	}
	return true;
}

