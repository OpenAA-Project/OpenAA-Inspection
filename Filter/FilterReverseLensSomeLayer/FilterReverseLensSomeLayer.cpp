
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterReverseLensSomeLayer\FilterReverseLensSomeLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterReverseLensSomeLayer.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ReverseLensSomeLayer";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Reversize cosine in some layer and one side in width direction";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterReverseLensSomeLayer(base);
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

	SettingDialog	D(handle->GetLayersBase()
					, ((FilterReverseLensSomeLayer *)handle)->LayerEnable[0]
					, ((FilterReverseLensSomeLayer *)handle)->LayerEnable[1]
					, ((FilterReverseLensSomeLayer *)handle)->LayerEnable[2]
					, ((FilterReverseLensSomeLayer *)handle)->Strength
					, ((FilterReverseLensSomeLayer *)handle)->Width
					, ((FilterReverseLensSomeLayer *)handle)->LeftSide
					, ((FilterReverseLensSomeLayer *)handle)->RightSide
					,parent);
	if(D.exec()==(int)true){
		((FilterReverseLensSomeLayer *)handle)->LayerEnable[0]		=D.Layer0;
		((FilterReverseLensSomeLayer *)handle)->LayerEnable[1]		=D.Layer1;
		((FilterReverseLensSomeLayer *)handle)->LayerEnable[2]		=D.Layer2;
		((FilterReverseLensSomeLayer *)handle)->Strength			=D.Strength;
		((FilterReverseLensSomeLayer *)handle)->Width				=D.Width;
		((FilterReverseLensSomeLayer *)handle)->LeftSide			=D.LeftSide;
		((FilterReverseLensSomeLayer *)handle)->RightSide			=D.RightSide;
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
FilterReverseLensSomeLayer::FilterReverseLensSomeLayer(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable=NULL;
	LayerEnable[0]=false;
	LayerEnable[1]=false;
	LayerEnable[2]=false;
	//Layer		=0;
	Strength	=1.0;
	Width		=1.0/6.0;
	LeftSide	=false;
	RightSide	=false;
}
FilterReverseLensSomeLayer::~FilterReverseLensSomeLayer(void)
{
	Release();
}

bool	FilterReverseLensSomeLayer::Save(QIODevice *f)
{
	if(::Save(f,LayerEnable[0])==false)
		return false;
	if(::Save(f,LayerEnable[1])==false)
		return false;
	if(::Save(f,LayerEnable[2])==false)
		return false;
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,LeftSide)==false)
		return false;
	if(::Save(f,RightSide)==false)
		return false;
	return true;
}
bool	FilterReverseLensSomeLayer::Load(QIODevice *f)
{
	if(::Load(f,LayerEnable[0])==false)
		return false;
	if(::Load(f,LayerEnable[1])==false)
		return false;
	if(::Load(f,LayerEnable[2])==false)
		return false;
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,LeftSide)==false)
		return false;
	if(::Load(f,RightSide)==false)
		return false;
	return true;
}

bool	FilterReverseLensSomeLayer::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Xn=GetDotPerLine();
	MultiplyTable=new BYTE[Xn*256];
	if(Width>0){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int x=0;x<Xn;x++){
				double	s=x-GetDotPerLine()/2;
				s=s/GetDotPerLine()*2;
				double	G=cos(s*M_PI*Width);
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=i*(Strength/G);
						if(a>0xFF)
							a=0xFF;
						if(a<0)
							a=0;
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
				s=s/GetDotPerLine()*2;
				double	G=cos(s*M_PI*(-Width));
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=i*(Strength*G);
						if(a>0xFF)
							a=0xFF;
						if(a<0)
							a=0;
						MultiplyTable[(x*256)+i]=a;
					}
				}
			}
		}
	}
	return true;
}

bool	FilterReverseLensSomeLayer::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}

bool	FilterReverseLensSomeLayer::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	Xn2=GetDotPerLine()/2;
	int	N=GetMaxLines();
	int	Xn=GetDotPerLine();

	if(BufferDimCounts>0 && LayerEnable[0]==true){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[0]->GetY(y);
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
	
	if(BufferDimCounts>1 && LayerEnable[1]==true){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[1]->GetY(y);
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
	
	if(BufferDimCounts>2 && LayerEnable[2]==true){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[2]->GetY(y);
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

	return true;
}

