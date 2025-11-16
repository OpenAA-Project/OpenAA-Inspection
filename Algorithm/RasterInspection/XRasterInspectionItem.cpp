/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RasterInspection\XRasterInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRasterInspection.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XRasterInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================

RasterInspectionThreshold::RasterInspectionThreshold(RasterInspectionItem *parent)
:AlgorithmThreshold(parent)
{
	GenColorDistance=3;
	SearchAreaDot	=3;
	SearchWaveDiv	=5;
	WaveDistance	=20;
	OKDot			=16;
}

void	RasterInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const RasterInspectionThreshold *s=(const RasterInspectionThreshold *)&src;
	GenColorDistance=s->GenColorDistance;
	SearchAreaDot	=s->SearchAreaDot	;
	SearchWaveDiv	=s->SearchWaveDiv	;
	WaveDistance	=s->WaveDistance	;
	OKDot			=s->OKDot			;
}
bool	RasterInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const RasterInspectionThreshold *s=(const RasterInspectionThreshold *)&src;
	if(GenColorDistance	==s->GenColorDistance
	&& SearchAreaDot	==s->SearchAreaDot	
	&& SearchWaveDiv	==s->SearchWaveDiv	
	&& WaveDistance		==s->WaveDistance	
	&& OKDot			==s->OKDot)
		return true;
	return false;
}
bool	RasterInspectionThreshold::Save(QIODevice *f)
{
	WORD	Ver=RasterInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,GenColorDistance)==false)
		return false;
	if(::Save(f,SearchAreaDot)==false)
		return false;
	if(::Save(f,SearchWaveDiv)==false)
		return false;
	if(::Save(f,WaveDistance)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;
	return true;
}

bool	RasterInspectionThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,GenColorDistance)==false)
		return false;
	if(::Load(f,SearchAreaDot)==false)
		return false;
	if(::Load(f,SearchWaveDiv)==false)
		return false;
	if(::Load(f,WaveDistance)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;
	return true;
}

void	RasterInspectionThreshold::FromLibrary(AlgorithmLibrary *src)
{
	RasterInspectionLibrary	*LSrc=dynamic_cast<RasterInspectionLibrary *>(src);
	if(LSrc==NULL)
		return;
	GenColorDistance=LSrc->GenColorDistance	;
	SearchAreaDot	=LSrc->SearchAreaDot	;
	SearchWaveDiv	=LSrc->SearchWaveDiv	;
	WaveDistance	=LSrc->WaveDistance		;
	OKDot			=LSrc->OKDot			;
}
void	RasterInspectionThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	RasterInspectionLibrary	*LDst=dynamic_cast<RasterInspectionLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->GenColorDistance	=GenColorDistance;
	LDst->SearchAreaDot		=SearchAreaDot	;
	LDst->SearchWaveDiv		=SearchWaveDiv	;
	LDst->WaveDistance		=WaveDistance	;
	LDst->OKDot				=OKDot			;
}
//===========================================================================================
RasterInspectionItem::RasterInspectionItem(void)
{
	AVector		=NULL;
	TargetImageList=NULL;
	YIndex		=NULL;
	TargetC		=NULL;

	Map		=NULL;
	DummyMap=NULL;
	MapXByte=0;
	MapYLen	=0;
}

RasterInspectionItem::~RasterInspectionItem(void)
{
	if(TargetImageList!=NULL){
		delete	[]TargetImageList;
		TargetImageList=NULL;
	}
	if(YIndex!=NULL){
		delete	[]YIndex;
		YIndex=NULL;
	}
	if(TargetC!=NULL){
		delete	[]TargetC;
		TargetC=NULL;
	}
	if(DummyMap!=NULL){
		DeleteMatrixBuff(DummyMap,MapYLen);
		DummyMap=NULL;
	}
	if(Map!=NULL){
		DeleteMatrixBuff(Map,MapYLen);
		Map=NULL;
	}
	MapXByte=0;
	MapYLen	=0;
}
void	RasterInspectionItem::CopyThreshold(RasterInspectionItem &src)
{
	GetThresholdW()->CopyFrom(*((RasterInspectionThreshold *)src.GetThresholdR()));
}

void	RasterInspectionItem::CopyThresholdOnly(RasterInspectionItem &src)
{
	GetThresholdW()->CopyFrom(*((RasterInspectionThreshold *)src.GetThresholdR()));
}

void	RasterInspectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((RasterInspectionItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((RasterInspectionItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((RasterInspectionItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((RasterInspectionItem *)Data)->GetLibID()){
			RasterInspectionInPage	*Ly=dynamic_cast<RasterInspectionInPage *>(GetParentInPage());
			UndoElement<RasterInspectionInPage>	*UPointer=new UndoElement<RasterInspectionInPage>(Ly,&RasterInspectionInPage::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			RasterInspectionItem *src=(RasterInspectionItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}
void	RasterInspectionItem::SetAreaWithImage(FlexArea &area,ImageBufferListContainer &ImageContainer)
{
	ImageBuffer *Buffer[3];
	if(ImageContainer.GetCount()>=3){
		Buffer[0]=ImageContainer[0];
		Buffer[1]=ImageContainer[1];
		Buffer[2]=ImageContainer[2];
		ColorArea.Set(area,Buffer ,3,0);
	}
	SetArea(area);
}

bool    RasterInspectionItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;

	int32	Ver=1;
	if(::Save(file,Ver)==false)
		return false;

	if(ColorArea.Save(file)==false)
		return false;

	return true;
}
bool    RasterInspectionItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(file,Ver)==false)
		return false;

	if(ColorArea.Load(file)==false)
		return false;

	return true;
}
ExeResult	RasterInspectionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	const	RasterInspectionThreshold	*RThr=GetThresholdR();

	if(TargetImageList!=NULL){
		delete	[]TargetImageList;
	}
	TargetImageList=new ImageBuffer *[GetLayerNumb()];
	GetTargetBuffList(TargetImageList);

	if(YIndex!=NULL){
		delete	[]YIndex;
	}
	YIndex=new BYTE*[GetLayerNumb()];

	if(TargetC!=NULL){
		delete	[]TargetC;
	}
	TargetC=new BYTE[GetLayerNumb()];

	int	MaxXLen=GetArea().GetWidth();
	int	MaxYLen=GetArea().GetHeight();
	int	iMapXByte	=(MaxXLen+24)/8;
	int	iMapYLen	=MaxYLen+16;

	if(iMapXByte!=MapXByte || iMapYLen!=MapYLen || Map==NULL || DummyMap==NULL){
		if(Map!=NULL){
			DeleteMatrixBuff(Map,MapYLen);
		}
		if(DummyMap!=NULL){
			DeleteMatrixBuff(DummyMap,MapYLen);
		}
		MapXByte=iMapXByte;
		MapYLen	=iMapYLen;
		Map		=MakeMatrixBuff(MapXByte,MapYLen);
		DummyMap=MakeMatrixBuff(MapXByte,MapYLen);
	}

	return _ER_true;
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	RasterInspectionItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear(Map	,0,MapXByte,MapYLen);
	return _ER_true;
}

static	int	DbgY=4132;

ExeResult	RasterInspectionItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID)
		DbgNumer++;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	const	RasterInspectionThreshold	*RThr=GetThresholdR();
	ResultDx =mx;
	ResultDy =my;
	int	Error=1;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	int	LayerNumb	=GetLayerNumb();
	int	MapXPoint=GetArea().GetMinX()-8;
	int	MapYPoint=GetArea().GetMinY()-8;

	int	N=ColorArea.GetFLineLen();
	for(int i=0;i<N;i++){
		int	y	=ColorArea.GetFLineAbsY(i);
		int	x1	=ColorArea.GetFLineLeftX(i);
		int	numb=ColorArea.GetFLineNumb(i);
		int	Y=y+my;
		if(0<=Y && Y<MaxLines){
			for(int layer=0;layer<LayerNumb;layer++){
				YIndex[layer]=TargetImageList[layer]->GetY(Y);
			}
			for(int k=0;k<numb;k++){
				int	X=x1+k+mx;
				if(0<=X && X<DotPerLine){
					for(int layer=0;layer<LayerNumb;layer++){
						TargetC[layer]=YIndex[layer][X];
					}
					if(CalcDistance(RThr,x1+k,y,TargetC)==false){
						SetBmpBit1(Map,x1+k-MapXPoint,y-MapYPoint);
					}
				}
			}
		}
	}
	int64	NGCount=0;
	int64	NGDots=0;
	ResultPosListContainer	NowList;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(Map,MapXByte,MapXByte*8,MapYLen,FPack);
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetPatternByte()>=RThr->OKDot){
			int64	Dots=p->GetPatternByte();
			int	NGW=p->GetWidth();
			int	NGH=p->GetHeight();
			double	NGLen=hypot(NGW, NGH);
			int	Cx,Cy;
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);
			r->result =0x10001;	//NG

			r->SetResult1(Dots);
			r->SetResult2(NGLen);
			r->NGShape.SuckFrom(*p);
			r->NGShape.MoveToNoClip(MapXPoint,MapYPoint);
			r->NGSize=Dots;
			NowList.AppendList(r);
			NGCount++;
			NGDots+=Dots;
		}
	}
	Res->MovePosList(NowList);
	Res->SetItemSearchedXY(0,0);
	if(NGCount>0){
		Res->SetAlignedXY(mx,my);
		Res->SetError(2);
		Res->SetResult1(NGCount);
		Res->SetResult2(NGDots);
		return _ER_true;	//NG
	}

	Res->SetResult1(NGCount);
	Res->SetResult2(NGDots);
	Res->SetAlignedXY(mx,my);
	Res->SetError(1);	//OK

	return _ER_true;
}

bool	RasterInspectionItem::CalcDistance(const RasterInspectionThreshold *RThr,int MasterX,int MasterY,BYTE *TargetC)
{
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	for(int L=0;L<=RThr->SearchAreaDot;L++){
		{
			int	y=-L;
			if(0<=(MasterY+y) && (MasterY+y)<DotPerLine){
				for(int x=-L;x<=L;x++){
					if(0<=(MasterX+x) && (MasterX+x)<DotPerLine){
						if(CalcDistanceFix(RThr,MasterX+x,MasterY+y,TargetC)==true)
							return true;
					}
				}
			}
		}
		{
			int	x=L;
			if(0<=(MasterX+x) && (MasterX+x)<DotPerLine){
				for(int y=-L+1;y<L;y++){
					if(0<=(MasterY+y) && (MasterY+y)<DotPerLine){
						if(CalcDistanceFix(RThr,MasterX+x,MasterY+y,TargetC)==true)
							return true;
					}
				}
			}
		}
		{
			int	y=L;
			if(0<=(MasterY+y) && (MasterY+y)<DotPerLine){
				for(int x=L;x>-L;x--){
					if(0<=(MasterX+x) && (MasterX+x)<DotPerLine){
						if(CalcDistanceFix(RThr,MasterX+x,MasterY+y,TargetC)==true)
							return true;
					}
				}
			}
		}
		{
			int	x=-L;
			if(0<=(MasterX+x) && (MasterX+x)<DotPerLine){
				for(int y=L;y>-L;y--){
					if(0<=(MasterY+y) && (MasterY+y)<DotPerLine){
						if(CalcDistanceFix(RThr,MasterX+x,MasterY+y,TargetC)==true)
							return true;
					}
				}
			}
		}
	}
	return false;
}
bool	RasterInspectionItem::CalcDistanceFix(const RasterInspectionThreshold *RThr,int MasterX,int MasterY,BYTE *TargetC)
{
	RasterInspectionInPage	*APage=tGetParentInPage();
	int	LayerNumb=GetLayerNumb();
	for(int L=-RThr->SearchWaveDiv;L<=RThr->SearchWaveDiv;L++){
		int	layer=L;
		int	Len=0;
		int	LNumb=0;
		for(ImageBufferList *s=APage->MasterByPDF.GetFirst();s!=NULL;s=s->GetNext(),layer++){
			int	c=s->GetPixel(MasterX,MasterY);
			if(0<=layer && layer<LayerNumb){
				Len+=(c-TargetC[layer])*(c-TargetC[layer]);
				LNumb++;
			}
		}
		double	DLen=sqrt((double)Len/(double)LNumb);
		if(DLen<RThr->WaveDistance)
			return true;
	}

	return false;
}

void	RasterInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	RasterInspectionDrawAttr	*BAttr=dynamic_cast<RasterInspectionDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->ModeShowItemImage==true){
			RasterInspectionBase	*ABase=tGetParentBase();
			ColorArea.DrawImage(0 ,0 ,&pnt
						,ZoomRate ,movx ,movy
						,true,true,true
						,ABase->TransparentPDF);
		}
		else{
			AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
