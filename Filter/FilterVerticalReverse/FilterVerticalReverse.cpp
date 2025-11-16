/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterVerticalReverse\FilterVerticalReverse.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterVerticalReverse.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingVerticalReverse.h"
#include "swap.h"
#include <omp.h>
//#define	_USE_MATH_DEFINES
//#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="VerticalReverse";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Reversize cosine in one side in width direction vertically";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterVerticalReverse(base);
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

	SettingVerticalReverse		D(handle->GetLayersBase()
								 ,((FilterVerticalReverse *)handle)->Strength
								 ,((FilterVerticalReverse *)handle)->Width
								 ,((FilterVerticalReverse *)handle)->TopSide
								 ,((FilterVerticalReverse *)handle)->BottomSide
								 ,((FilterVerticalReverse *)handle)->Layers
								 ,((FilterVerticalReverse *)handle)->Gamma
								 ,parent);
	if(D.exec()==(int)true){
		((FilterVerticalReverse *)handle)->Strength	=D.Strength;
		((FilterVerticalReverse *)handle)->Width	=D.Width;
		((FilterVerticalReverse *)handle)->TopSide	=D.TopSide;
		((FilterVerticalReverse *)handle)->BottomSide=D.BottomSide;
		((FilterVerticalReverse *)handle)->Layers	=D.Layers;
		((FilterVerticalReverse *)handle)->Gamma	=D.Gamma;
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
FilterVerticalReverse::FilterVerticalReverse(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable=NULL;
	Strength	=1.0;
	Width		=1.0/6.0;
	TopSide	=false;
	BottomSide	=false;

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		Layers.Add(true);
	}
	Gamma	=1.0;
}
FilterVerticalReverse::~FilterVerticalReverse(void)
{
	Release();
}

bool	FilterVerticalReverse::Save(QIODevice *f)
{
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,TopSide)==false)
		return false;
	if(::Save(f,BottomSide)==false)
		return false;
	if(Layers.Save(f)==false)
		return false;
	if(::Save(f,Gamma)==false)
		return false;
	return true;
}
bool	FilterVerticalReverse::Load(QIODevice *f)
{
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,TopSide)==false)
		return false;
	if(::Load(f,BottomSide)==false)
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
bool	FilterVerticalReverse::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Yn=GetMaxLines();
	MultiplyTable=new int[Yn*256];
	if(Width>0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<Yn;y++){
				double	s=y-GetMaxLines()/2;
				s=s/GetMaxLines()*2;
				double	G=cos(s*M_PI*Width);
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=GetGamma(i*(Strength/G),Gamma);
						if(a>0xFF)
							a=0xFF;
						MultiplyTable[(y*256)+i]=a;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<Yn;y++){
				double	s=y-GetMaxLines()/2;
				s=s/GetMaxLines()*2;
				double	G=cos(s*M_PI*(-Width));
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=GetGamma(i*(Strength*G),Gamma);
						if(a>0xFF)
							a=0xFF;
						MultiplyTable[(y*256)+i]=a;
					}
				}
			}
		}
	}
	return true;
}

bool	FilterVerticalReverse::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}

bool	FilterVerticalReverse::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	N =GetMaxLines();
	int	N2=GetMaxLines()/2;
	int	Xn=GetDotPerLine();

	for(int L=0;L<BufferDimCounts;L++){
		if(Layers.GetCount()<L || Layers[L]==false)
			continue;

		if(TopSide==true){
			#pragma omp parallel
			{
				#pragma omp for		
				for(int y=0;y<N2;y++){
					BYTE	*d=Buff[L]->GetY(y);
					for(int x=0;x<Xn;x++){
						d[x]=MultiplyTable[(y<<8)+d[x]];
					}
				}
			}
		}
		if(BottomSide==true){
			int	LN=N-N2;
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<LN;i++){
					int	y=N2+i;
				//for(int y=N2;y<N;y++){
					BYTE	*d=Buff[L]->GetY(y);
					for(int x=0;x<Xn;x++){
						d[x]=MultiplyTable[(y<<8)+d[x]];
					}
				}
			}
		}
	}
	return true;
}

