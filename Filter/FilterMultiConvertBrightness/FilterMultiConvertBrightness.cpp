/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterMultiConvertBrightness\FilterMultiConvertBrightness.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterMultiConvertBrightness.h"
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
	str="MultiConvertBrightness";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Reversize cosine in each side with gain/Offset/Linear";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMultiConvertBrightness(base);
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

	SettingDialog	D(handle->GetLayersBase());
	D.Init(	  ((FilterMultiConvertBrightness *)handle)->StrengthL
			, ((FilterMultiConvertBrightness *)handle)->WidthL
			, ((FilterMultiConvertBrightness *)handle)->InclineL
			, ((FilterMultiConvertBrightness *)handle)->AddVL
			, ((FilterMultiConvertBrightness *)handle)->AddBL

			, ((FilterMultiConvertBrightness *)handle)->StrengthR
			, ((FilterMultiConvertBrightness *)handle)->WidthR
			, ((FilterMultiConvertBrightness *)handle)->InclineR
			, ((FilterMultiConvertBrightness *)handle)->AddVR
			, ((FilterMultiConvertBrightness *)handle)->AddBR);

	if(D.exec()==(int)true){
		((FilterMultiConvertBrightness *)handle)->StrengthL	=D.StrengthL;
		((FilterMultiConvertBrightness *)handle)->WidthL	=D.WidthL	;
		((FilterMultiConvertBrightness *)handle)->InclineL	=D.InclineL	;
		((FilterMultiConvertBrightness *)handle)->AddVL		=D.AddVL	;
		((FilterMultiConvertBrightness *)handle)->AddBL		=D.AddBL	;

		((FilterMultiConvertBrightness *)handle)->StrengthR	=D.StrengthR;
		((FilterMultiConvertBrightness *)handle)->WidthR	=D.WidthR	;
		((FilterMultiConvertBrightness *)handle)->InclineR	=D.InclineR	;
		((FilterMultiConvertBrightness *)handle)->AddVR		=D.AddVR	;
		((FilterMultiConvertBrightness *)handle)->AddBR		=D.AddBR	;
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
FilterMultiConvertBrightness::FilterMultiConvertBrightness(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplyTable=NULL;
	StrengthL	=1.0;
	WidthL		=0.16;
	InclineL	=0;
	AddVL		=0;
	AddBL		=0;

	StrengthR	=1.0;
	WidthR		=0.16;
	InclineR	=0;
	AddVR		=0;
	AddBR		=0;
}

FilterMultiConvertBrightness::~FilterMultiConvertBrightness(void)
{
	Release();
}

bool	FilterMultiConvertBrightness::Save(QIODevice *f)
{
	if(::Save(f,StrengthL)==false)
		return false;
	if(::Save(f,WidthL)==false)
		return false;
	if(::Save(f,InclineL)==false)
		return false;
	if(::Save(f,AddVL)==false)
		return false;
	if(::Save(f,AddBL)==false)
		return false;

	if(::Save(f,StrengthR)==false)
		return false;
	if(::Save(f,WidthR)==false)
		return false;
	if(::Save(f,InclineR)==false)
		return false;
	if(::Save(f,AddVR)==false)
		return false;
	if(::Save(f,AddBR)==false)
		return false;

	return true;
}
bool	FilterMultiConvertBrightness::Load(QIODevice *f)
{
	if(::Load(f,StrengthL)==false)
		return false;
	if(::Load(f,WidthL)==false)
		return false;
	if(::Load(f,InclineL)==false)
		return false;
	if(::Load(f,AddVL)==false)
		return false;
	if(::Load(f,AddBL)==false)
		return false;

	if(::Load(f,StrengthR)==false)
		return false;
	if(::Load(f,WidthR)==false)
		return false;
	if(::Load(f,InclineR)==false)
		return false;
	if(::Load(f,AddVR)==false)
		return false;
	if(::Load(f,AddBR)==false)
		return false;

	return true;
}

bool	FilterMultiConvertBrightness::Initial(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	int	Xn=GetDotPerLine();
	int	Xn2=Xn/2;
	MultiplyTable=new int[Xn*256];

	#pragma omp parallel
	{
		#pragma omp for		
		for(int x=0;x<Xn;x++){
			if(x<Xn2){
				double	s=x-GetDotPerLine()/2;
				s=s/GetDotPerLine()*2;
				double	G=cos(s*M_PI*WidthL);
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=i*(StrengthL/G);
						a*=(1.0+InclineL*x+AddVL);
						a+=AddBL;
						if(a>0xFF)
							a=0xFF;
						MultiplyTable[(x*256)+i]=a;
					}
				}
			}
			else{
				double	s=x-GetDotPerLine()/2;
				s=s/GetDotPerLine()*2;
				double	G=cos(s*M_PI*WidthR);
				if(G>0){
					for(int i=0;i<256;i++){
						int	a=i*(StrengthR/G);
						a*=(1.0+InclineR*x+AddVR);
						a+=AddBR;
						if(a>0xFF)
							a=0xFF;
						MultiplyTable[(x*256)+i]=a;
					}
				}
			}
		}
	}

	return true;
}

bool	FilterMultiConvertBrightness::Release(void)
{
	if(MultiplyTable!=NULL){
		delete	[]MultiplyTable;
	}
	MultiplyTable=NULL;
	return true;
}

bool	FilterMultiConvertBrightness::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	Xn2=GetDotPerLine()/2;
	int	N=GetMaxLines();
	int	Xn=GetDotPerLine();

	for(int Layer=0;Layer<BufferDimCounts;Layer++){
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=Buff[Layer]->GetY(y);
				for(int x=0;x<Xn;x++){
					d[x]=MultiplyTable[(x<<8)+d[x]];
				}
			}
		}
	}
	return true;
}

