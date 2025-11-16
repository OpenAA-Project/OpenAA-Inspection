/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterMergeColor\FilterMergeColor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterMergeColor.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "XPointer.h"
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="MergeColor";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Merge Color";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMergeColor(base);
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
	FilterMergeColor	*v=(FilterMergeColor *)handle;
	SettingDialog	D(handle->GetLayersBase(),v,parent);
	D.exec();
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================

bool	ColorPoint::Save(QIODevice *f)
{
	if(::Save(f,SrcColor)==false)
		return false;
	if(::Save(f,TargetColor)==false)
		return false;
	return true;
}
bool	ColorPoint::Load(QIODevice *f)
{
	if(::Load(f,SrcColor)==false)
		return false;
	if(::Load(f,TargetColor)==false)
		return false;
	return true;
}


FilterMergeColor::FilterMergeColor(LayersBase *base)
	:FilterClassBase(base)
{
	dx=0;
	dy=0;

	P1.SrcColor=QColor(40,42,35,255);
	P2.SrcColor=QColor(38,33,28,255);

	Gain=2;

	R1=176.85;
	R2=157.30;

	B1=193.74;
	B2=175.12;

}

bool	FilterMergeColor::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(P1.Save(f)==false)
		return false;
	if(P2.Save(f)==false)
		return false;
	if(::Save(f,dx)==false)
		return false;
	if(::Save(f,dy)==false)
		return false;

	if(::Save(f,R1)==false)
		return false;
	if(::Save(f,B1)==false)
		return false;
	if(::Save(f,R2)==false)
		return false;
	if(::Save(f,B2)==false)
		return false;
	if(::Save(f,Gain)==false)
		return false;
	return true;
}
bool	FilterMergeColor::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(P1.Load(f)==false)
		return false;
	if(P2.Load(f)==false)
		return false;
	if(::Load(f,dx)==false)
		return false;
	if(::Load(f,dy)==false)
		return false;

	if(::Load(f,R1)==false)
		return false;
	if(::Load(f,B1)==false)
		return false;
	if(::Load(f,R2)==false)
		return false;
	if(::Load(f,B2)==false)
		return false;
	if(::Load(f,Gain)==false)
		return false;

	return true;
}

bool	InterpolationFunc(int P1 ,int Q1 ,int P2 ,int Q2 ,double &a ,double &b)
{
	if(P1==P2)
		return false;
	a=(Q1-Q2)/((double)(P1-P2));
	b= Q1-a*P1;
	return true;
}

bool	FilterMergeColor::Initial(void)
{
	//a*P1+b=Q1
	//a*P2+b=Q2
	//(P1-P2)a=Q1-Q2

	double	aR,aG,aB;
	double	bR,bG,bB;

	InterpolationFunc(P1.SrcColor.red()		,P1.TargetColor.red()	,P2.SrcColor.red()	,P2.TargetColor.red()	,aR ,bR);
	InterpolationFunc(P1.SrcColor.green()	,P1.TargetColor.green() ,P2.SrcColor.green(),P2.TargetColor.green() ,aG ,bG);
	InterpolationFunc(P1.SrcColor.blue()	,P1.TargetColor.blue()	,P2.SrcColor.blue() ,P2.TargetColor.blue()	,aB ,bB);

	InterpolationFunc(P1.SrcColor.red() ,P1.SrcColor.blue() ,P2.SrcColor.red() ,P2.SrcColor.blue() ,aR ,bR);

	for(int i=0;i<256;i++){
		TableR[i]=Clipping((int)(i*aR+bR),0,255);
		TableG[i]=Clipping((int)(i*aG+bG),0,255);
		TableB[i]=Clipping((int)(i*aB+bB),0,255);
	}
	return true;
}

double	GetAreaAverage(int x ,int y ,ImageBuffer *Buff,int R)
{
	int	XLen=Buff->GetWidth();
	int	YLen=Buff->GetHeight();
	double	D=0;
	int		Numb=0;
	for(int ry=-R;ry<=R;ry++){
		if(0<=y+ry && y+ry<YLen){
			BYTE	*s=Buff->GetY(y+ry);
			for(int rx=-R;rx<=R;rx++){
				if(0<=(x+rx) && (x+rx)<XLen){
					D+=s[x+rx];
					Numb++;
				}
			}
		}
	}
	return D/Numb;
}

bool	FilterMergeColor::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int YLen=GetMaxLines();
	int	XLen=GetDotPerLine();
	//if(GetLayerNumb()>=3){
	//	for(int y=0;y<YLen;y++){
	//		BYTE	*d0=Buff[0]->GetY(y);
	//		BYTE	*d1=Buff[1]->GetY(y);
	//		BYTE	*d2=Buff[2]->GetY(y);
	//		for(int x=0;x<XLen;x++){
	//			d0[x]=TableR[d0[x]];
	//			d1[x]=TableG[d1[x]];
	//			d2[x]=TableB[d2[x]];
	//		}
	//	}
	//}
	//else
	//if(GetLayerNumb()==2){
	//	for(int y=0;y<YLen;y++){
	//		BYTE	*d0=Buff[0]->GetY(y);
	//		BYTE	*d1=Buff[1]->GetY(y);
	//		for(int x=0;x<XLen;x++){
	//			d0[x]=TableR[d0[x]];
	//			d1[x]=TableG[d1[x]];
	//		}
	//	}
	//}
	//else
	//if(GetLayerNumb()==1){
	//	for(int y=0;y<YLen;y++){
	//		BYTE	*d0=Buff[0]->GetY(y);
	//		for(int x=0;x<XLen;x++){
	//			d0[x]=TableR[d0[x]];
	//		}
	//	}
	//}

	static	int	Px1=2950;
	static	int	Py1=3120;
	static	int	Px2=3580;
	static	int	Py2=3190;
	
	dx=0;
	dy=0;	//-10;
	//Gain=2;
	//R1=GetAreaAverage(Px1 ,Py1 ,Buff[0],12);
	//R2=GetAreaAverage(Px2 ,Py2 ,Buff[0],12);
	//
	//B1=GetAreaAverage(Px1 ,Py1 ,Buff[2],12);
	//B2=GetAreaAverage(Px2 ,Py2 ,Buff[2],12);

	//R1=176.85;
	//R2=157.30;
	//
	//B1=193.74;
	//B2=175.12;

	double	aK,bK;
	InterpolationFunc(R1 ,B1 ,R2 ,B2 ,aK ,bK);

	for(int i=0;i<256;i++){
		TableR[i]=Clipping((int)(i*aK+bK),0,255);
	}

	if(BufferDimCounts>=3){
		for(int y=0;y<YLen;y++){
			if(0<=y+dy && y+dy<YLen){
				BYTE	*d0=Buff[0]->GetY(y+dy);
				BYTE	*d1=Buff[1]->GetY(y);
				BYTE	*d2=Buff[2]->GetY(y);
				for(int x=0;x<XLen;x++){
					if(0<=x+dx && x+dx<XLen){
						d1[x]=Clipping((int)(Gain*(TableR[d0[x+dx]]-d2[x])+128),0,255);
					}
				}
			}
		}
	}
	return true;
}

