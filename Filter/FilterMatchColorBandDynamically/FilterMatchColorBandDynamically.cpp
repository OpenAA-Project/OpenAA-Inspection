/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterMatchColorBandDynamically\FilterMatchColorBandDynamically.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterMatchColorBandDynamically.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "XPointer.h"
#include "XGeneralFunc.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="MatchColorBandDynamically";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Match ColorBand dynamically";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMatchColorBandDynamically(base);
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
	//FilterLineShading	*H=(FilterLineShading *)handle;
	//SettingDialog	D(H->GetLayersBase(),H,parent);
	//
	//if(D.exec()==(int)true){
	//}
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================


RectImageList::RectImageList(void)
{
	Data=NULL;
}
RectImageList::RectImageList(int x ,int y ,int w ,int h)
{
	TargetPosX=MasterPosX=x;
	TargetPosY=MasterPosY=y;
	XLen=w;
	YLen=h;
	Data=NULL;
	DataLen=0;
	Var=0;
}
RectImageList::~RectImageList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

double	RectImageList::Match(ImageBuffer *Buff ,int dx, int dy)
{
	int64	B=0;
	int64	BB=0;
	int64	AB=0;
	BYTE	*s=Data;

	if((TargetPosY+dy)<0 || Buff->GetHeight()<=(TargetPosY+YLen+dy)
	|| (TargetPosX+dx)<0 || Buff->GetWidth() <=(TargetPosX+XLen+dx))
		return 0.0;

	for(int y=0;y<YLen;y++){
		BYTE	*d=Buff->GetYWithoutDepended(TargetPosY+y+dy);
		int	X=TargetPosX+dx;
		for(int x=0;x<XLen;x++,X++){
			BYTE	c=d[X];
			B+=c;
			BB+=c*c;
			AB+=*s*c;
			s++;
		}
	}
	int	Numb=XLen*YLen;
	double	AvrA=((double)A)/(double)Numb;
	double	AvrB=((double)B)/(double)Numb;
	double	M=(AA-AvrA*AvrA*Numb)*(BB-AvrB*AvrB*Numb);
	if(M<0)
		return 0;
	M=sqrt(M);
	double	W=(AB-AvrA*AvrB*Numb)/M;
	return W;
}

int	RectImageList::Compare(RectImageList &src)
{
	if(Var>src.Var)
		return -1;
	if(Var<src.Var)
		return 1;
	return 0;
}

bool	RectImageList::SetImage(ImageBuffer *Buff,int dx,int dy)
{
	int	Numb=XLen*YLen;
	if(Data!=NULL && DataLen!=Numb){
		delete	[]Data;
		Data=NULL;
	}
	DataLen=Numb;
	if(Data==NULL){
		Data=new BYTE[DataLen];
	}
	BYTE	*d=Data;
	A=0;
	AA=0;
	if((MasterPosY+dy)<0 || Buff->GetHeight()<=(MasterPosY+YLen+dy))
		return false;

	for(int y=0;y<YLen;y++){
		BYTE	*s=Buff->GetYWithoutDepended(MasterPosY+y+dy);
		int	X=MasterPosX+dx;
		for(int x=0;x<XLen;x++,X++){
			BYTE	c=s[X];
			*d=c;
			d++;
			A+=c;
			AA+=c*c;
		}
	}
	return true;
}


//================================================================================================


FilterMatchColorBandDynamically::FilterMatchColorBandDynamically(LayersBase *base)
:FilterClassBase(base)
{	
	BandR=NULL;
	BandB=NULL;
	DefaultBandHeight	=200;
	DefaultRectSize		=20;
	BandHeight	=0;
	BandCount	=0;
	TmpR=new ImageBuffer();
	TmpB=new ImageBuffer();
}

FilterMatchColorBandDynamically::~FilterMatchColorBandDynamically(void)
{
	delete	TmpR;
	delete	TmpB;
	Release();
}

bool	FilterMatchColorBandDynamically::Save(QIODevice *f)
{
	return true;
}
bool	FilterMatchColorBandDynamically::Load(QIODevice *f)
{
	Release();

	return true;
}

bool	FilterMatchColorBandDynamically::Initial(void)
{
	Release();

	XLen=GetDotPerLine();
	YLen=GetMaxLines();
	BandCount=(YLen+DefaultBandHeight-1)/DefaultBandHeight;
	BandHeight	=YLen/BandCount;

	BandR=new ColorBandInfo[BandCount];
	BandB=new ColorBandInfo[BandCount];

	TmpR->Set(0,0,XLen,YLen);
	TmpB->Set(0,0,XLen,YLen);

	return true;
}

bool	FilterMatchColorBandDynamically::Release(void)
{
	if(BandR!=NULL){
		delete	[]BandR;
		BandR=NULL;
	}
	if(BandB!=NULL){
		delete	[]BandB;
		BandB=NULL;
	}
	BandHeight	=0;
	BandCount	=0;

	return true;
}
bool	FilterMatchColorBandDynamically::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(XLen==NewDotPerLine && YLen==NewMaxLines)
		return false;
	Initial();
	return FilterClassBase::ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}

bool	FilterMatchColorBandDynamically::Reallocate(int newLayerNumb)
{
	if(3==newLayerNumb)
		return false;
	return FilterClassBase::Reallocate(newLayerNumb);
}

double	FilterMatchColorBandDynamically::CalcVar(int x,int y,int RectSize,ImageBuffer *Buff)
{
	int64	A=0;
	int64	AA=0;
	int		Numb=0;
	for(int ky=0;ky<RectSize;ky++){
		BYTE	*d=Buff->GetY(y+ky);
		for(int kx=0;kx<RectSize;kx++){
			BYTE	c=d[x+kx];
			A+=c;
			AA+=c*c;
			Numb++;
		}
	}
	if(Numb<10)
		return 0;
	double	Avr=((double)A)/(double)Numb;
	double	V=(AA-Avr*Avr*Numb)/Numb;
	return V;
}

ExeResult	FilterMatchColorBandDynamically::ExecuteInitialAfterEdit(void)
{
	if(GetLayerNumb(GetPage())<3)
		return _ER_true;

	int	SearchAroundDot=10;
	for(int i=0;i<BandCount;i++){
		BandR[i].RemoveAll();
		BandB[i].RemoveAll();
	}
	ImagePointerContainer Images;
	GetPageData()->GetMasterImages(Images);
	ImageBuffer	*BuffR=Images[0];
	ImageBuffer	*BuffB=Images[2];
	for(int i=0;i<BandCount;i++){
		NPListPack<RectImageList>	TmpBandR;
		NPListPack<RectImageList>	TmpBandB;
		int	y1=BandHeight*i;
		int	y2=BandHeight*(i+1);
		for(int y=y1;y<y2-DefaultRectSize;y+=DefaultRectSize){
			if(y==0)
				continue;
			if((y+DefaultRectSize+15)>=YLen)
				continue;
			for(int x=20;x<(XLen-20);x+=DefaultRectSize){
				{
					RectImageList	*rr=new RectImageList(x,y,DefaultRectSize,DefaultRectSize);
					rr->SetImage(BuffR,0,0);
					int	px,py;
					double	MaxV=0;
					py=-10;
					for(px=-10;px<10;px++){
						double	v=rr->Match(BuffR,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					px=10;
					for(py=-10;py<10;py++){
						double	v=rr->Match(BuffR,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					py=10;
					for(px=10;px>-10;px--){
						double	v=rr->Match(BuffR,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					px=-10;
					for (py=10;py>-10;py--) {
						double	v=rr->Match(BuffR,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					rr->Var=CalcVar(x,y,DefaultRectSize,BuffR)*(1.0-MaxV);

					TmpBandR.AppendList(rr);
				}
				{
					RectImageList	*rb=new RectImageList(x,y,DefaultRectSize,DefaultRectSize);
					rb->SetImage(BuffB,0,0);
					int	px,py;
					double	MaxV=0;
					py=-10;
					for(px=-10;px<10;px++){
						double	v=rb->Match(BuffB,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					px=10;
					for(py=-10;py<10;py++){
						double	v=rb->Match(BuffB,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					py=10;
					for(px=10;px>-10;px--){
						double	v=rb->Match(BuffB,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					px=-10;
					for (py=10;py>-10;py--) {
						double	v=rb->Match(BuffB,px,py);
						if(MaxV<v){
							MaxV=v;
						}
					}
					rb->Var=CalcVar(x,y,DefaultRectSize,BuffB)*(1.0-MaxV);

					TmpBandB.AppendList(rb);
				}
			}
		}
		TmpBandR.Sort();
		TmpBandB.Sort();

		RectImageList	*rr1=TmpBandR.GetFirst();
		TmpBandR.RemoveList(rr1);
		BandR[i].AppendList(rr1);
		rr1->SetImage(BuffR,0,0);
		RectImageList	*rr2=TmpBandR.GetFirst();
		TmpBandR.RemoveList(rr2);
		BandR[i].AppendList(rr2);
		rr2->SetImage(BuffR,0,0);

		RectImageList	*rb1=TmpBandB.GetFirst();
		TmpBandB.RemoveList(rb1);
		BandB[i].AppendList(rb1);
		rb1->SetImage(BuffB,0,0);
		RectImageList	*rb2=TmpBandB.GetFirst();
		TmpBandB.RemoveList(rb2);
		BandB[i].AppendList(rb2);
		rb2->SetImage(BuffB,0,0);
	}
	return _ER_true;
}

bool	FilterMatchColorBandDynamically::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	return true;
}

ExeResult	FilterMatchColorBandDynamically::ExecutePreProcessing	(void)
{
	if(GetLayerNumb(GetPage())<3)
		return _ER_true;

	int	MaxShiftY=6;
	int	MaxShiftX=2;
	int	SearchBlockArea=5;
	ImagePointerContainer Images;
	GetPageData()->GetTargetImages(Images);
	ImageBuffer	*Buff[3];
	Buff[0]=Images[0];
	Buff[1]=Images[1];
	Buff[2]=Images[2];

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<BandCount;i++){
			double	MaxR=0;
			int		MaxRDx=0;
			int		MaxRDy=0;

			for(RectImageList *r=BandR[i].GetFirst();r!=NULL;r=r->GetNext()){
				AlignmentPacket2D	ACmd;
				ACmd.PosXOnTarget=r->MasterPosX;
				ACmd.PosYOnTarget=r->MasterPosY;
				GetLayersBase()->GetAlignmentForProcessing(GetPage() ,ACmd);
				r->TargetPosX=r->MasterPosX+ACmd.ShiftX;
				r->TargetPosY=r->MasterPosY+ACmd.ShiftY;
				r->Possible=r->SetImage(Buff[1],ACmd.ShiftX,ACmd.ShiftY);
			}
			for(RectImageList *r=BandB[i].GetFirst();r!=NULL;r=r->GetNext()){
				AlignmentPacket2D	ACmd;
				ACmd.PosXOnTarget=r->MasterPosX;
				ACmd.PosYOnTarget=r->MasterPosY;
				GetLayersBase()->GetAlignmentForProcessing(GetPage() ,ACmd);
				r->TargetPosX=r->MasterPosX+ACmd.ShiftX;
				r->TargetPosY=r->MasterPosY+ACmd.ShiftY;
				r->Possible=r->SetImage(Buff[1],ACmd.ShiftX,ACmd.ShiftY);
			}


			for(int dy=-MaxShiftY;dy<=MaxShiftY;dy++){
				for(int dx=-MaxShiftX;dx<=MaxShiftX;dx++){
					double	Ld=0;
					for(RectImageList *r=BandR[i].GetFirst();r!=NULL;r=r->GetNext()){
						if(r->Possible==true){
							double	d=r->Match(Buff[0],dx,dy);
							Ld+=d;
						}
					}
					if(Ld>MaxR){
						MaxR=Ld;
						MaxRDx=dx;
						MaxRDy=dy;
					}
				}
			}
			BandR[i].Matched=MaxR;
			BandR[i].Dx=MaxRDx;
			BandR[i].Dy=MaxRDy;

			double	MaxB=0;
			int		MaxBDx=0;
			int		MaxBDy=0;

			for(int dy=-MaxShiftY;dy<=MaxShiftY;dy++){
				for(int dx=-MaxShiftX;dx<=MaxShiftX;dx++){
					double	Ld=0;
					for(RectImageList *r=BandB[i].GetFirst();r!=NULL;r=r->GetNext()){
						if(r->Possible==true){
							double	d=r->Match(Buff[2],dx,dy);
							Ld+=d;
						}
					}
					if(Ld>MaxB){
						MaxB=Ld;
						MaxBDx=dx;
						MaxBDy=dy;
					}
				}
			}
			BandB[i].Matched=MaxB;
			BandB[i].Dx=MaxBDx;
			BandB[i].Dy=MaxBDy;
		}
	}
	*TmpR=*Buff[0];
	*TmpB=*Buff[2];

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<BandCount;i++){
			int	Y=BandHeight*i;
			for(int y=0;y<BandHeight;y++){
				{
					BYTE	*d=Buff[0]->GetYWithoutDepended(Y+y);
					int	sy=Y+y+BandR[i].Dy;
					if(sy<0 || sy>=YLen)
						continue;
					BYTE	*s=TmpR->GetYWithoutDepended(sy);
					memcpy(d,s,XLen);
				}
				{
					BYTE	*d=Buff[2]->GetYWithoutDepended(Y+y);
					int	sy=Y+y+BandB[i].Dy;
					if(sy<0 || sy>=YLen)
						continue;
					BYTE	*s=TmpB->GetYWithoutDepended(sy);
					memcpy(d,s,XLen);
				}
			}
		}
	}

	return _ER_true;
}
