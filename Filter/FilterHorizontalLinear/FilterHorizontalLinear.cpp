/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterHorizontalLinear\FilterHorizontalLinear.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterHorizontalLinear.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingFilterHorizontalLinear.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="HorizontalLinear";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Horizontally change  brightness Linearly";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterHorizontalLinear(base);
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

	SettingFilterHorizontalLinear	D(handle->GetLayersBase()
									 ,((FilterHorizontalLinear *)handle)->Strength
									 ,((FilterHorizontalLinear *)handle)->WholeImage
									 ,((FilterHorizontalLinear *)handle)->LeftSide
									 ,((FilterHorizontalLinear *)handle)->RightSide
									 ,((FilterHorizontalLinear *)handle)->Layers
									 ,((FilterHorizontalLinear *)handle)->Gamma
									,parent);
	if(D.exec()==(int)true){
		((FilterHorizontalLinear *)handle)->Strength	=D.Strength;
		((FilterHorizontalLinear *)handle)->WholeImage	=D.WholeImage;
		((FilterHorizontalLinear *)handle)->LeftSide	=D.LeftSide;
		((FilterHorizontalLinear *)handle)->RightSide	=D.RightSide;
		((FilterHorizontalLinear *)handle)->Layers		=D.Layers;
		((FilterHorizontalLinear *)handle)->Gamma		=D.Gamma;
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
FilterHorizontalLinear::FilterHorizontalLinear(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable=NULL;
	Strength	=0;
	WholeImage	=true;
	LeftSide	=false;
	RightSide	=false;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		Layers.Add(true);
	}
	Gamma	=1.0;
}
FilterHorizontalLinear::~FilterHorizontalLinear(void)
{
	Release();
}

bool	FilterHorizontalLinear::Save(QIODevice *f)
{
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,WholeImage)==false)
		return false;
	if(::Save(f,LeftSide)==false)
		return false;
	if(::Save(f,RightSide)==false)
		return false;
	if(Layers.Save(f)==false)
		return false;
	if(::Save(f,Gamma)==false)
		return false;
	return true;
}
bool	FilterHorizontalLinear::Load(QIODevice *f)
{
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,WholeImage)==false)
		return false;
	if(::Load(f,LeftSide)==false)
		return false;
	if(::Load(f,RightSide)==false)
		return false;
	if(Layers.Load(f)==false)
		return false;
	if(::Load(f,Gamma)==false)
		return false;
	return true;
}
double	GetGamma(double m ,double Gamma)
{
	return m*pow(m/2000,Gamma);
}
bool	FilterHorizontalLinear::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Xn=GetDotPerLine();
	MultiplyTable=new int[Xn*256];

	if(WholeImage==true){
		if(LeftSide==true){
			#pragma omp parallel
			{
				#pragma omp for		
				for(int x=0;x<Xn;x++){
					double	G=Strength/(GetDotPerLine())*(Xn/2-x);
					if(G>0){
						for(int i=0;i<256;i++){
							int	a=GetGamma(i*(G+1.0),Gamma);
							if(a<0)
								a=0;
							if(a>=255)
								a=0xFF;
							MultiplyTable[(x*256)+i]=a;
						}
					}
				}
			}
		}
		else if(RightSide==true){
			#pragma omp parallel
			{
				#pragma omp for		
				for(int x=0;x<Xn;x++){
					double	G=Strength/(GetDotPerLine())*(x-Xn);
					if(G>0){
						for(int i=0;i<256;i++){
							int	a=GetGamma(i*(G+1.0),Gamma);
							if(a<0)
								a=0;
							if(a>=255)
								a=0xFF;
							MultiplyTable[(x*256)+i]=a;
						}
					}
				}
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for		
				for(int x=0;x<Xn;x++){
					double	s=x-GetDotPerLine()/2;
					double	G=Strength/(GetDotPerLine()/2.0)*s;
					if(G>0){
						for(int i=0;i<256;i++){
							int	a=GetGamma(i*(G+1.0),Gamma);
							if(a<0)
								a=0;
							if(a>=255)
								a=0xFF;
							MultiplyTable[(x*256)+i]=a;
						}
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for		
			for(int x=0;x<Xn;x++){
				double	s=abs(x-GetDotPerLine()/2);
				double	G=Strength/(GetDotPerLine()/2.0)*s;
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=GetGamma(i*(G+1.0),Gamma);
						if(a<0)
							a=0;
						if(a>=255)
							a=0xFF;
						MultiplyTable[(x*256)+i]=a;
					}
				}
			}
		}
	}
	return true;
}

bool	FilterHorizontalLinear::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}
bool	FilterHorizontalLinear::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	Release();
	Initial();
	return true;
}

bool	FilterHorizontalLinear::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterHorizontalLinear::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	Xn2=GetDotPerLine()/2;
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
				if(WholeImage==true){
					for(int x=0;x<Xn;x++){
						d[x]=MultiplyTable[(x<<8)+d[x]];
					}
				}
				else{
					if(LeftSide==true){
						for(int x=0;x<Xn2;x++){
							d[x]=MultiplyTable[(x<<8)+d[x]];
						}
					}
					if(RightSide==true){
						for(int x=Xn2;x<Xn;x++){
							d[x]=MultiplyTable[(x<<8)+d[x]];
						}
					}
				}
			}
		}
	}
	return true;
}

