/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterOneLayer\FilterOneLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterOneLayer.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingOneLayerForm.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="OneLayer";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make one layer processing";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterOneLayer(base);
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

	SettingOneLayerForm	D(handle->GetLayersBase()
						, ((FilterOneLayer *)handle)->Layer
						, ((FilterOneLayer *)handle)->GetLayerNumb(0)
						, ((FilterOneLayer *)handle)->MethodValue
						, ((FilterOneLayer *)handle)->Param,parent);
	if(D.exec()==(int)true){
		((FilterOneLayer *)handle)->Layer		=D.Layer;
		((FilterOneLayer *)handle)->MethodValue	=D.MethodValue;
		((FilterOneLayer *)handle)->Param		=D.Param;
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
FilterOneLayer::FilterOneLayer(LayersBase *base)
:FilterClassBase(base)
{	
	Layer		=0;
	MethodValue	=0;
	Param		=0;
}

bool	FilterOneLayer::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MethodValue)==false)
		return false;
	if(::Save(f,Param)==false)
		return false;
	return true;
}
bool	FilterOneLayer::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,MethodValue)==false)
		return false;
	if(::Load(f,Param)==false)
		return false;
	return true;
}

bool	FilterOneLayer::Initial(void)
{
	if(TmpImage.GetWidth()!=GetDotPerLine() || TmpImage.GetHeight()!=GetMaxLines()){
		TmpImage.Set(0,0,GetDotPerLine(),GetMaxLines());
	}
	TmpImage.Memset(0);
	return true;
}

bool	FilterOneLayer::Release(void)
{
	return true;
}

bool	FilterOneLayer::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	bool	Ret=false;
	if(MethodValue==0){
		Ret=ExecuteAverage(Buff,BufferDimCounts);
	}
	else if(MethodValue==1){
		Ret=ExecuteXAverage(Buff,BufferDimCounts);
	}
	else if(MethodValue==2){
		Ret=ExecuteMedian(Buff,BufferDimCounts);
	}
	else if(MethodValue==3){
		Ret=ExecuteMulAverage(Buff,BufferDimCounts);
	}
	return Ret;
}

bool	FilterOneLayer::ExecuteAverage(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	XLen=GetDotPerLine()-Param;
	int	YLen=GetMaxLines()-Param;
	int	Param2=Param/2;
	double	MulPArea=1.0/(double)(Param*Param);

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*d=TmpImage.GetY(y+Param2);
			for(int x=0;x<XLen;x++){
				int	D=0;
				for(int sy=0;sy<Param;sy++){
					BYTE	*s=Buff[Layer]->GetY(y+sy);
					for(int sx=0;sx<Param;sx++){
						D+=s[x+sx];
					}
				}
				d[x+Param2]=(BYTE)(D*MulPArea);
			}
		}
	}
	*Buff[Layer]=TmpImage;

	return true;
}

bool	FilterOneLayer::ExecuteXAverage(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	XLen=GetDotPerLine()-Param;
	int	YLen=GetMaxLines()-Param;
	int	Param2=Param/2;
	double	MulPArea=1.0/(double)(Param);

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*d=TmpImage.GetY(y+Param2);
			BYTE	*s=Buff[Layer]->GetY(y);
			for(int x=0;x<XLen;x++){
				int	D=0;
				for(int sx=0;sx<Param;sx++){
					D+=s[x+sx];
				}
				d[x+Param2]=(BYTE)(D*MulPArea);
			}
		}
	}
	*Buff[Layer]=TmpImage;
	return true;
}

int	FuncDimSort(const void *a ,const void *b)
{
	int d=*((BYTE *)a) - *((BYTE *)b);
	return d;
}

bool	FilterOneLayer::ExecuteMedian(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	FilterDot2=Param/2;

	int	AreaDot=Param*Param;
	int	Abandon	=(int)(AreaDot*0.4);
	int	Adopt	=(int)(AreaDot*0.2);

	int	YN=GetMaxLines()-Param;
	ImageBuffer	*SBuff=Buff[Layer];
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YN;y++){
			int	Dy=y+FilterDot2;
			BYTE	*d=TmpImage.GetY(Dy);
			int	XN=GetDotPerLine()-Param;
			for(int x=0;x<XN;x++){
				int	Dx=x+FilterDot2;
				int	n=0;
				BYTE	Dim[2000];
				for(int sy=0;sy<Param;sy++){
					BYTE	*s=SBuff->GetY(y+sy);
					memcpy(&Dim[n],&s[x],Param);
					n+=Param;
				}
				QSort(Dim,n,1,FuncDimSort);
				int	D=0;
				for(int t=0;t<Adopt;t++){
					D+=Dim[t+Abandon];
				}
				d[Dx]=D/Adopt;
			}
		}
	}
	*Buff[Layer]=TmpImage;

	return true;
}

bool	FilterOneLayer::ExecuteMulAverage(ImageBuffer *Buff[],int BufferDimCounts)
{
	//’†S“_‚Í‘S‘Ì‚Ì‚Q‚T“‚Ì‰Ád
	//—Ìˆæ‚Ì’†‰›•t‹ß1^2‚Í’Êí
	//—Ìˆæ‚ÌŠOŠs•t‹ß‚Í’Êí‚Ì‚T‚O“‚Ì‰Ád
	int	XLen=GetDotPerLine()-Param;
	int	YLen=GetMaxLines()-Param;
	int	Param2=Param/2;
	int		InsideArea	=Param2*Param2-1;
	int		OutsideArea	=Param*Param-InsideArea-1;
	double	AllMul	=(InsideArea+(OutsideArea*0.5))/0.75;
	double	CenterMul=AllMul-(InsideArea+(OutsideArea*0.5));
	CenterMul-=1.0;
	double	MulPArea=1.0/(double)(AllMul);
	ImageBuffer *SBuff=Buff[Layer];

	int	Dot1=(Param-Param2)/2;
	int	Dot2=Dot1+Param2;
	int	Dot3=Param;


	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*d=TmpImage.GetY(y+Param2);
			for(int x=0;x<XLen;x++){
				int	DOut=0;
				int	DIn=0;
				for(int sy=0;sy<Dot1;sy++){
					BYTE	*s=SBuff->GetY(y+sy);
					for(int sx=0;sx<Param;sx++){
						DOut+=s[x+sx];
					}
				}
				for(int sy=Dot1;sy<Dot2;sy++){
					BYTE	*s=SBuff->GetY(y+sy);
					for(int sx=0;sx<Dot1;sx++){
						DOut+=s[x+sx];
					}
					for(int sx=Dot1;sx<Dot2;sx++){
						DIn+=s[x+sx];
					}
					for(int sx=Dot2;sx<Dot3;sx++){
						DOut+=s[x+sx];
					}
				}
				for(int sy=Dot2;sy<Dot3;sy++){
					BYTE	*s=SBuff->GetY(y+sy);
					for(int sx=0;sx<Param;sx++){
						DOut+=s[x+sx];
					}
				}

				d[x+Param2]=(BYTE)((DOut*0.5+DIn+CenterMul)*MulPArea);
			}
		}
	}
	*Buff[Layer]=TmpImage;

	return true;
}
