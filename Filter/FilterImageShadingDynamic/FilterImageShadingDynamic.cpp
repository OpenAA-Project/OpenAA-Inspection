/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterImageShadingDynamic\FilterImageShadingDynamic.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterImageShadingDynamic.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "XPointer.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ImageShading Dynamically";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Shading dynamically";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterImageShadingDynamic(base);
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
	FilterImageShadingDynamic	*H=(FilterImageShadingDynamic *)handle;
	SettingDialog	D(handle->GetLayersBase(),H,parent);
	if(D.exec()==(int)true){
		return true;
	}
	return false;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================

const	int	StepY=64;

FilterImageShadingDynamic::FilterImageShadingDynamic(LayersBase *base)
:FilterClassBase(base)
{	
	RefStartX=0,RefEndX=99999;
	RefStartY=0,RefEndY=1000;
	Threshold=30;

	RefTableR=NULL;
	RefTableG=NULL;
	RefTableB=NULL;
}

bool	FilterImageShadingDynamic::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	Release();
	Initial();
	return true;
}

bool	FilterImageShadingDynamic::Save(QIODevice *f)
{
	if(::Save(f,RefStartX)==false)
		return false;
	if(::Save(f,RefEndX)==false)
		return false;
	if(::Save(f,RefStartY)==false)
		return false;
	if(::Save(f,RefEndY)==false)
		return false;

	if(::Save(f,DataR.BrightnessL)==false)
		return false;
	if(::Save(f,DataG.BrightnessL)==false)
		return false;
	if(::Save(f,DataB.BrightnessL)==false)
		return false;
	if(::Save(f,DataR.BrightnessH)==false)
		return false;
	if(::Save(f,DataG.BrightnessH)==false)
		return false;
	if(::Save(f,DataB.BrightnessH)==false)
		return false;

	if(::Save(f,DataR.Ideal)==false)
		return false;
	if(::Save(f,DataG.Ideal)==false)
		return false;
	if(::Save(f,DataB.Ideal)==false)
		return false;

	if(::Save(f,DataR.Offset)==false)
		return false;
	if(::Save(f,DataG.Offset)==false)
		return false;
	if(::Save(f,DataB.Offset)==false)
		return false;

	return true;
}
bool	FilterImageShadingDynamic::Load(QIODevice *f)
{
	if(::Load(f,RefStartX)==false)
		return false;
	if(::Load(f,RefEndX)==false)
		return false;
	if(::Load(f,RefStartY)==false)
		return false;
	if(::Load(f,RefEndY)==false)
		return false;

	if(::Load(f,DataR.BrightnessL)==false)
		return false;
	if(::Load(f,DataG.BrightnessL)==false)
		return false;
	if(::Load(f,DataB.BrightnessL)==false)
		return false;
	if(::Load(f,DataR.BrightnessH)==false)
		return false;
	if(::Load(f,DataG.BrightnessH)==false)
		return false;
	if(::Load(f,DataB.BrightnessH)==false)
		return false;

	if(::Load(f,DataR.Ideal)==false)
		return false;
	if(::Load(f,DataG.Ideal)==false)
		return false;
	if(::Load(f,DataB.Ideal)==false)
		return false;

	if(::Load(f,DataR.Offset)==false)
		return false;
	if(::Load(f,DataG.Offset)==false)
		return false;
	if(::Load(f,DataB.Offset)==false)
		return false;
	return true;
}

FilterImageShadingDynamic::ShadingDynamicStruct::ShadingDynamicStruct(void)
{
	InsideDim		=NULL;
	InsideDimCount	=NULL;
	InsideDim16		=NULL;
	InsideDimCount16=NULL;
	BrightTable		=NULL;
	BrL				=NULL;
	BrH				=NULL;
	DotL			=NULL;
	DotH			=NULL;
	HAvr			=NULL;
}
void	FilterImageShadingDynamic::ShadingDynamicStruct::Initial(int DotPerLine,int MaxLines)
{
	InsideDim		=new int[DotPerLine];
	InsideDimCount	=new int[DotPerLine];
	MaxInsideDim16	=DotPerLine*(MaxLines/StepY+1);
	InsideDim16		=new int[MaxInsideDim16];
	InsideDimCount16=new int[MaxInsideDim16];
	BrightTable		=new int[DotPerLine*256];
	BrL				=new int[DotPerLine];
	BrH				=new int[DotPerLine];
	DotL			=new int[DotPerLine];
	DotH			=new int[DotPerLine];
	HAvr			=new int[DotPerLine];
}
void	FilterImageShadingDynamic::ShadingDynamicStruct::Release(void)
{
	if(InsideDim!=NULL){
		delete	[]InsideDim;
	}
	InsideDim=NULL;

	if(InsideDimCount!=NULL){
		delete	[]InsideDimCount;
	}
	InsideDimCount=NULL;

	if(InsideDim16!=NULL){
		delete	[]InsideDim16;
	}
	InsideDim16=NULL;

	if(InsideDimCount16!=NULL){
		delete	[]InsideDimCount16;
	}
	InsideDimCount16=NULL;

	delete	[]BrightTable	;
	delete	[]BrL			;
	delete	[]BrH			;
	delete	[]DotL		;
	delete	[]DotH		;
	delete	[]HAvr		;

	BrightTable	=NULL;
	BrL			=NULL;
	BrH			=NULL;
	DotL		=NULL;
	DotH		=NULL;
	HAvr		=NULL;

}

bool	FilterImageShadingDynamic::Initial(void)
{
	Release();
	RefTableR=new BYTE[GetDotPerLine()*256];
	RefTableG=new BYTE[GetDotPerLine()*256];
	RefTableB=new BYTE[GetDotPerLine()*256];

	DataR.Initial(GetDotPerLine(),GetMaxLines());
	DataG.Initial(GetDotPerLine(),GetMaxLines());
	DataB.Initial(GetDotPerLine(),GetMaxLines());

	return true;
}

bool	FilterImageShadingDynamic::Release(void)
{
	if(RefTableR!=NULL){
		delete	[]RefTableR;
	}
	if(RefTableG!=NULL){
		delete	[]RefTableG;
	}
	if(RefTableB!=NULL){
		delete	[]RefTableB;
	}
	RefTableR=NULL;
	RefTableG=NULL;
	RefTableB=NULL;

	DataR.Release();
	DataG.Release();
	DataB.Release();

	return true;
}

bool	FilterImageShadingDynamic::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	DWORD	D1=::GetComputerMiliSec();
	int	n=omp_get_max_active_levels();
	omp_set_max_active_levels(n+10);
	#pragma omp parallel                             
	{                                                
        #pragma omp sections
        {
			#pragma omp section
            {
				Execute1(*Buff[0] ,DataR);
			}
			#pragma omp section
            {
				Execute1(*Buff[1] ,DataG);
			}
			#pragma omp section
            {
				Execute1(*Buff[2] ,DataB);
			}
		}
	}
	omp_set_max_active_levels(n);
	DWORD	D4=::GetComputerMiliSec();

	//DWORD	D1=::GetComputerMiliSec();
	//Execute1(*Buff[0] ,DataR);
	//DWORD	D2=::GetComputerMiliSec();
	//DWORD	t1=D2-D1;
	//Execute1(*Buff[1] ,DataG);
	//DWORD	D3=::GetComputerMiliSec();
	//DWORD	t2=D3-D2;
	//Execute1(*Buff[2] ,DataB);
	//DWORD	D4=::GetComputerMiliSec();
	//DWORD	t3=D4-D2;
	DWORD	tTotal=D4-D1;
	return true;
}

bool	FilterImageShadingDynamic::Execute1(ImageBuffer &Buff ,struct ShadingDynamicStruct &Data)
{
	DWORD	D1=::GetComputerMiliSec();
	int	DotPerLine=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	int	YNumb=1024;

	int	OffsetS=Data.Offset*1024;
	memset(Data.InsideDim		,0,sizeof(int)*DotPerLine);
	memset(Data.InsideDimCount	,0,sizeof(int)*DotPerLine);
	memset(Data.BrightTable,0,256*sizeof(int)*DotPerLine);

	int	N=YNumb*StepY;
	for(int y=0;y<N;y+=StepY){
		BYTE	*s=Buff.GetYWithoutDepended(y);
		BYTE	*sk=s;
		int		sAvrK=0;
		int		tDotPerLine=0;
		for(int x=0;x<DotPerLine;x++,sk++){
			int	t=*sk;
			if(Data.BrightnessL<=t && t<=Data.BrightnessH){
				sAvrK+=*sk;
				tDotPerLine++;
			}
		}
		if(tDotPerLine!=0){
			sAvrK/=tDotPerLine;
			int	sKL=sAvrK-Threshold;
			int	sKH=sAvrK+Threshold;

			for(int x=0;x<DotPerLine;x++,s++){
				int	t=*s;
				if(sKL<=t && t<=sKH && Data.BrightnessL<=t && t<=Data.BrightnessH){
					Data.InsideDim[x]+=t;
					Data.InsideDimCount[x]++;
				}
				(Data.BrightTable[(x<<8)+t])++;
			}
		}
	}
	DWORD	D2=::GetComputerMiliSec();
	int	SparePixles=YNumb/4;
	for(int x=0;x<DotPerLine;x++){
		Data.DotL[x]=0;
		int	Xn=x<<8;
		for(int i=0;i<256;i++){
			Data.DotL[x]+=Data.BrightTable[Xn+i];
			if(Data.DotL[x]>=SparePixles){
				Data.BrL[x]=i;
				break;
			}
		}
		Data.DotH[x]=0;
		for(int i=255;i>=0;i--){
			Data.DotH[x]+=Data.BrightTable[Xn+i];
			if(Data.DotH[x]>=SparePixles){
				Data.BrH[x]=i;
				break;
			}
		}
	}
	double	AddedD=0;
	int		AddedN=0;
	for(int x=0;x<DotPerLine;x++){
		if(Data.InsideDimCount[x]>0){
			AddedD+=Data.InsideDim[x]/(double)Data.InsideDimCount[x];
			AddedN++;
		}
	}
	if(AddedN>0){
		double	AvrD=AddedD/AddedN;
		for(int x=0;x<DotPerLine;x++){
			if(Data.InsideDimCount[x]>0){
				Data.HAvr[x]=Data.InsideDim[x];
			}
			else{
				Data.InsideDim[x]=AvrD;
				Data.HAvr[x]=Data.InsideDim[x];
				Data.InsideDimCount[x]=1;
			}
		}
	}
	else{
		double	AvrD=30;
		for(int x=0;x<DotPerLine;x++){
			Data.InsideDim[x]=AvrD;
			Data.HAvr[x]=Data.InsideDim[x];
			Data.InsideDimCount[x]=1;
		}
	}
	DWORD	D3=::GetComputerMiliSec();
	int	NY=MaxLines;	//-YNumb;
	int	LPoint=0;
	for(int Y=0;Y<NY;Y+=StepY){
		int		sY=Y+YNumb;
		if(sY>=MaxLines){
			sY=MaxLines-1;
		}
		BYTE	*s=Buff.GetYWithoutDepended(sY);
		BYTE	*d=Buff.GetYWithoutDepended(Y);

		BYTE	*dk=d;
		BYTE	*sk=s;
		int		dAvrK=0;
		int		sAvrK=0;
		int		dDotPerLine=0;
		int		sDotPerLine=0;
		for(int x=0;x<DotPerLine;x++,dk++,sk++){
			int	c=*dk;
			int	t=*sk;
			if(Data.BrightnessL<=c && c<=Data.BrightnessH){
				dAvrK+=*dk;
				dDotPerLine++;
			}
			if(Data.BrightnessL<=t && t<=Data.BrightnessH){
				sAvrK+=*sk;
				sDotPerLine++;
			}
		}
		if(dDotPerLine!=0)
			dAvrK/=dDotPerLine;
		else
			dAvrK=*d;
		int	dKL=max(Data.BrightnessL,dAvrK-Threshold);
		int	dKH=min(Data.BrightnessH,dAvrK+Threshold);

		if(sDotPerLine!=0)
			sAvrK/=sDotPerLine;
		else
			sAvrK=*s;
		int	sKL=max(Data.BrightnessL,sAvrK-Threshold);
		int	sKH=min(Data.BrightnessH,sAvrK+Threshold);

		for(int x=0;x<DotPerLine;x++){
			int	c=d[x];
			int	t=s[x];
			if(sKL<=t && t<=sKH){
				if(dKL<=c && c<=dKH){
					if(Data.InsideDimCount[x]>=YNumb)
						Data.InsideDim[x]+=t-c;
					if(Data.InsideDim[x]<0){
						Data.InsideDim[x]=0;
					}
					else{
						Data.InsideDim[x]+=t;
						Data.InsideDimCount[x]++;
					}
				}
				else if(Data.InsideDimCount[x]<YNumb){
					Data.InsideDim[x]+=t;
					Data.InsideDimCount[x]++;
				}
			}
			if(LPoint<Data.MaxInsideDim16){
				Data.InsideDim16[LPoint]	=Data.InsideDim[x];
				Data.InsideDimCount16[LPoint]=Data.InsideDimCount[x];
			}
			LPoint++;
		}
	}
	DWORD	D4=::GetComputerMiliSec();

	int	NYStep=NY/StepY;
	#pragma omp parallel                             
	{   
		#pragma omp for
		for(int yi=0;yi<NYStep;yi++){
			int	MulAvr[16384];
			int		LPoint=yi*DotPerLine;
			for(int x=0;x<DotPerLine;x++,LPoint++){
				MulAvr[x]=(int)(65536.0*((double)(Data.Ideal*Data.InsideDimCount16[LPoint]))/(double)(Data.InsideDim16[LPoint]+Data.Offset*Data.InsideDimCount16[LPoint]));			
			}
			int	LStepY=StepY;
			int	YBase=yi*StepY;
			LStepY=min(LStepY,NY-YBase);
			for(int i=0;i<LStepY;i++){
				BYTE	*w=Buff.GetYWithoutDepended(YBase+i);
				for(int x=0;x<DotPerLine;x++,w++){
					int	e=(((*w)+Data.Offset)*MulAvr[x])>>16;
					(*w)=(BYTE)Saturation256(e);
				}
			}
		}
	}
	DWORD	D5=::GetComputerMiliSec();
	for(int y=NY;y<MaxLines;y++){
		BYTE	*d=Buff.GetYWithoutDepended(y);

		BYTE	*dk=d;
		int		AvrK=0;
		int		dDotPerLine=0;
		for(int x=0;x<DotPerLine;x++,dk++){
			int	t=*dk;
			if(Data.BrightnessL<=t && t<=Data.BrightnessH){
				AvrK+=t;
				dDotPerLine++;
			}
		}
		if(dDotPerLine!=NULL){
			AvrK/=dDotPerLine;
		}
		else{
			AvrK=*d;
		}
		int	KL=AvrK-Threshold;
		int	KH=AvrK+Threshold;

		for(int x=0;x<DotPerLine;x++,d++){
			int	c=*d;
			if(KL<=c && c<KH && Data.BrightnessL<=c && c<=Data.BrightnessH){
				int	h=Data.InsideDim[x];
				if(Data.BrL[x]<=c && c<=Data.BrH[x]){
					(*d)=(c+Data.Offset)*Data.Ideal*1024/(h+OffsetS);
					Data.HAvr[x]=h;
				}
				else{
					int	e=(c+Data.Offset)*Data.Ideal*1024/(Data.HAvr[x]+OffsetS);
					(*d)=(BYTE)Saturation256(e);
				}
			}
			else{
				int	e=(c+Data.Offset)*Data.Ideal*1024/(Data.HAvr[x]+OffsetS);
				(*d)=(BYTE)Saturation256(e);
			}
		}
	}
	DWORD	D6=::GetComputerMiliSec();

	SpanTime1=D2-D1;
	SpanTime2=D3-D2;
	SpanTime3=D4-D3;
	SpanTime4=D5-D4;
	SpanTime5=D6-D5;

	return true;
}
