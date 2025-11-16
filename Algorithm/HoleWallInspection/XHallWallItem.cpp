/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\HoleWallInspection\XHoleWallItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XHoleWallInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XHoleWallLibrary.h"
#include "XImageProcess.h"
#include "swap.h"
#include <omp.h>
#include "XDisplayBitImage.h"
#include "XPropertyHoleWallCommon.h"
#include "XAlgorithmDLL.h"
#define	_USE_MATH_DEFINES
#include <math.h>

HoleWallItem::HoleWallItem(void)
{
	AVector=NULL;
	ResultShiftX=0;
	ResultShiftY=0;
	BmpMap	=NULL;
	TmpMap	=NULL;
	MaskMap	=NULL;
	XLen	=0;
	XByte	=0;
	YLen	=0;
}

HoleWallItem::HoleWallItem(FlexArea &area)
:AlgorithmItemPLITemplate<HoleWallInLayer,HoleWallInPage,HoleWallBase>(area)
{
	AVector=NULL;
	ResultShiftX=0;
	ResultShiftY=0;
	BmpMap	=NULL;
	TmpMap	=NULL;
	MaskMap	=NULL;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	SetEdited(true);
}
HoleWallItem::~HoleWallItem(void)
{
	if(BmpMap!=NULL){
		DeleteMatrixBuff(BmpMap,YLen);
		BmpMap	=NULL;
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,YLen);
		TmpMap	=NULL;
	}
	if(MaskMap!=NULL){
		DeleteMatrixBuff(MaskMap,YLen);
		MaskMap	=NULL;
	}
	XLen	=0;
	XByte	=0;
	YLen	=0;
}

AlgorithmItemPLI &HoleWallItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(*((HoleWallItem *)&src));
	return *this;
}

void	HoleWallItem::CopyThreshold(HoleWallItem &src)
{
	GetThresholdW()->CopyFrom(*((HoleWallThreshold *)src.GetThresholdR()));
}

void	HoleWallItem::CopyThresholdOnly(HoleWallItem &src)
{
	GetThresholdW()->CopyFrom(*((HoleWallThreshold *)src.GetThresholdR()));
}

bool    HoleWallItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;
	if(OutsideArea.Save(file)==false)
		return false;
	return true;
}
bool    HoleWallItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	if(OutsideArea.Load(file)==false)
		return false;
	return true;
}

void	HoleWallItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((HoleWallItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((HoleWallItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((HoleWallItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((HoleWallItem *)Data)->GetLibID()){
			HoleWallInLayer	*Ly=dynamic_cast<HoleWallInLayer *>(GetParentInLayer());
			UndoElement<HoleWallInLayer>	*UPointer=new UndoElement<HoleWallInLayer>(Ly,&HoleWallInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			HoleWallItem *src=(HoleWallItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}
void	HoleWallItem::SetThresholdFromCommon(SetThresholdHoleWallInfo *Info)
{
	if(Info->Shift>=0)
		GetThresholdW()->SearchDot	=Info->Shift;
	if(Info->NGSize1>=0)
		GetThresholdW()->NGSize	=Info->NGSize1;
}

int		HoleWallItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}
void	HoleWallItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	HoleWallItem	*ASrc=dynamic_cast<HoleWallItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((HoleWallBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
	}
}

static	int	Mergin=8;

ExeResult	HoleWallItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);


	//if(IsEdited()==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true){
		MapXPos = GetArea().GetMinX()-Mergin;
		MapYPos = GetArea().GetMinY()-Mergin;
		int	iXLen=GetArea().GetWidth() +Mergin*2;
		int	iYLen=GetArea().GetHeight()+Mergin*2;

		if(iXLen!=XLen || iYLen!=YLen || BmpMap==NULL || TmpMap==NULL || MaskMap==NULL){
			if(BmpMap!=NULL){
				DeleteMatrixBuff(BmpMap,YLen);
				BmpMap	=NULL;
			}
			if(TmpMap!=NULL){
				DeleteMatrixBuff(TmpMap,YLen);
				TmpMap	=NULL;
			}
			if(MaskMap!=NULL){
				DeleteMatrixBuff(MaskMap,YLen);
				MaskMap	=NULL;
			}
			XLen	=iXLen;
			YLen	=iYLen;
			XByte=(XLen+7)/8;
			BmpMap =MakeMatrixBuff(XByte,YLen);
			TmpMap =MakeMatrixBuff(XByte,YLen);
			MaskMap=MakeMatrixBuff(XByte,YLen);
		}

		MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
		MatrixBuffClear	(MaskMap ,0 ,XByte,YLen);

		MakeOutsideArea();
	//}
	return _ER_true;
}

void	HoleWallItem::RebuildWallShape(void)
{
	int	Cx,Cy;

	HoleWallInPage	*Ap=(HoleWallInPage	*)GetParentInPage();
	HoleWallBase	*ABase=(HoleWallBase *)GetParentBase();
	GetArea().GetCenter(Cx,Cy);
	int	XPosFromCenter=Cx-GetDotPerLine()/2;
	double	sX=0;
	if(XPosFromCenter<0){
		double	dx=XPosFromCenter;
		double	*M=Ap->ShiftXParamLeft;
		sX=M[0]+M[1]*dx+M[2]*dx*dx+M[3]*dx*dx*dx;
	}
	else{
		double	dx=XPosFromCenter;
		double	*M=Ap->ShiftXParamRight;
		sX=M[0]+M[1]*dx+M[2]*dx*dx+M[3]*dx*dx*dx;
	}
	int	ShiftY=Ap->ShiftYRate*ABase->Thickness;
	int	tXLen=GetArea().GetWidth() +2*Mergin+2*fabs(sX);
	int	tYLen=GetArea().GetHeight()+2*Mergin+2*abs(ShiftY);
	int	tXByte	=(tXLen+7)/8;
	int	tMapPointX=GetArea().GetMinX()-Mergin-fabs(sX);
	int	tMapPointY=GetArea().GetMinY()-Mergin-abs(ShiftY);

	BYTE	MapBuff[10000];
	BYTE	TmpBuff[10000];
	BYTE	CTmpBuff[10000];

	BYTE	**tMap=MakeMatrixBuff(tXByte,tYLen,MapBuff,sizeof(MapBuff));
	BYTE	**tTmp=MakeMatrixBuff(tXByte,tYLen,TmpBuff,sizeof(TmpBuff));
	BYTE	**cTmp=MakeMatrixBuff(tXByte,tYLen,CTmpBuff,sizeof(CTmpBuff));
	MatrixBuffClear	(tMap ,0 ,tXByte,tYLen);
	MatrixBuffClear	(tTmp ,0 ,tXByte,tYLen);
	HoleWallLibrary	*TmpLib=(HoleWallLibrary *)GetParentBase()->FindLibFromManagedCacheLib(GetLibID());
	
	GetArea().MakeBitData(tMap ,-tMapPointX ,-tMapPointY
                               ,tXLen, tYLen);
	GetLayersBase()->ThinAreaN(tMap,cTmp,tXByte,tYLen,TmpLib->SpaceToOutline);

	GetArea().MakeBitData(tTmp ,-tMapPointX+sX ,-tMapPointY+ShiftY
                               ,tXLen, tYLen);
	GetLayersBase()->FatAreaN(tTmp,cTmp,tXByte,tYLen,TmpLib->SpaceToOutline);

	MatrixBuffNotAnd(tMap ,(const BYTE **)tTmp ,tXByte,tYLen);

	GetLayersBase()->ThinAreaN(tMap,cTmp,tXByte,tYLen,TmpLib->NoiseSize);
	GetLayersBase()->FatAreaN (tMap,cTmp,tXByte,tYLen,TmpLib->NoiseSize);

	FlexArea	Area;
	Area.BuildFromRaster(tMap ,tXByte,tYLen ,tMapPointX ,tMapPointY);
	SetArea(Area);

	DeleteMatrixBuff(tMap,MapBuff,tYLen);
	DeleteMatrixBuff(tTmp,TmpBuff,tYLen);
	DeleteMatrixBuff(cTmp,CTmpBuff,tYLen);
}

void	HoleWallItem::MakeOutsideArea(void)
{
	int	OutlineWidth=4;
		
	HoleWallLibrary	*TmpLib=(HoleWallLibrary *)GetParentBase()->FindLibFromManagedCacheLib(GetLibID());
	if(TmpLib!=NULL){
		int	tXLen=GetArea().GetWidth() +2*Mergin+4*TmpLib->SpaceToOutline+2*OutlineWidth;
		int	tYLen=GetArea().GetHeight()+2*Mergin+4*TmpLib->SpaceToOutline+2*OutlineWidth;
		int	tXByte	=(tXLen+7)/8;
		int	tMapPointX=GetArea().GetMinX()-Mergin-OutlineWidth-2*TmpLib->SpaceToOutline;
		int	tMapPointY=GetArea().GetMinY()-Mergin-OutlineWidth-2*TmpLib->SpaceToOutline;
	
		BYTE	MapBuff[10000];
		BYTE	DstBuff[10000];
		BYTE	TmpBuff[10000];

		BYTE	**tMap=MakeMatrixBuff(tXByte,tYLen,MapBuff,sizeof(MapBuff));
		BYTE	**tDst=MakeMatrixBuff(tXByte,tYLen,DstBuff,sizeof(DstBuff));
		BYTE	**tTmp=MakeMatrixBuff(tXByte,tYLen,TmpBuff,sizeof(TmpBuff));
		MatrixBuffClear	(tMap ,0 ,tXByte,tYLen);
		MatrixBuffClear	(tTmp ,0 ,tXByte,tYLen);
	
		GetArea().MakeBitData(tMap	,-tMapPointX ,-tMapPointY
                                    ,tXLen, tYLen);

		GetLayersBase()->FatAreaN(tMap,tTmp,tXByte,tYLen,2*TmpLib->SpaceToOutline);
		MatrixBuffCopy	(tDst	,tXByte,tYLen
						,(const BYTE **)tMap ,tXByte,tYLen);

		GetLayersBase()->FatAreaN(tDst,tTmp,tXByte,tYLen,OutlineWidth);
		MatrixBuffNotAnd(tDst ,(const BYTE **)tMap ,tXByte,tYLen);
		OutsideArea.BuildFromRaster(tDst ,tXByte,tYLen ,tMapPointX ,tMapPointY);

		DeleteMatrixBuff(tMap,MapBuff,tYLen);
		DeleteMatrixBuff(tDst,DstBuff,tYLen);
		DeleteMatrixBuff(tTmp,TmpBuff,tYLen);
	}
}


int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	HoleWallItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteStartByInspection(ExeID ,ThreadNo,Res);
	MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
	MatrixBuffClear	(MaskMap ,0 ,XByte,YLen);
	return Ret;
}

ExeResult	HoleWallItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AlgorithmItemPLI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);

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
	if(GetID()==DbgID && GetParent()->GetLayer()==DbgLayer)
		DbgNumer++;

	ImageBuffer	&Target=GetTargetBuff();
	double	MaxDiff=0;
	int		MaxDiffX=0;
	int		MaxDiffY=0;
	const HoleWallThreshold	*RThr=GetThresholdR();

	for(int dy=-RThr->SearchDot;dy<=RThr->SearchDot;dy+=4){
		for(int dx=-RThr->SearchDot;dx<=RThr->SearchDot;dx+=4){
			double	d=GetMaxDiff(Target,mx+dx ,my+dy);
			if(d>=MaxDiff){
				MaxDiff=d;
				MaxDiffX=dx;
				MaxDiffY=dy;
			}
		}
	}
	double	tMaxDiff=0;
	int		tMaxDiffX=0;
	int		tMaxDiffY=0;
	for(int dy=-4;dy<=4;dy++){
		for(int dx=-4;dx<=4;dx++){
			double	d=GetMaxDiff(Target,mx+MaxDiffX+dx ,my+MaxDiffY+dy);
			if(d>=tMaxDiff){
				tMaxDiff=d;
				tMaxDiffX=dx;
				tMaxDiffY=dy;
			}
		}
	}
	int	Rx=0;
	int	Ry=0;
	double	MaxNGSize=9999999999;
	PureFlexAreaListContainer	NGArea;	
	for(int dy=-4;dy<=4;dy++){
		for(int dx=-4;dx<=4;dx++){
			PureFlexAreaListContainer	tNGArea;
			double	d=CalcClusterize(Target,mx+MaxDiffX+tMaxDiffX+dx ,my+MaxDiffY+tMaxDiffY+dy,tNGArea);
			if(d<MaxNGSize){
				MaxNGSize=d;
				NGArea.RemoveAll();
				NGArea.Move(tNGArea);
				Rx=MaxDiffX+tMaxDiffX+dx;
				Ry=MaxDiffY+tMaxDiffY+dy;
			}
		}
	}
	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(Rx,Ry);
	Res->SetResult1(MaxNGSize);

	if(NGArea.GetCount()==0){
		//OK
		Res->SetError(1);
		FinishCalc();
		return _ER_true;
	}
	//NG
	for(PureFlexAreaList *a=NGArea.GetFirst();a!=NULL;a=a->GetNext()){
		ResultPosList	*f=new ResultPosList(MapXPos,MapYPos,Rx,Ry);
		f->NGShape.SuckFrom(*a);
		f->NGShape.MoveToNoClip(MapXPos,MapYPos);
		f->result =0x20000;
		f->SetResult1(a->GetPatternByte());
		Res->AddPosList(f);
	}
	Res->SetError(2);
	FinishCalc();
	return _ER_true;
}

double	HoleWallItem::GetMaxDiff(ImageBuffer &Target , int dx ,int dy)
{
	double  InsideCol =GetArea().GetAverage(Target, dx , dy);
	double  OutsideCol=OutsideArea.GetAverage(Target, dx , dy);
	return fabs(InsideCol - OutsideCol);
}
double	HoleWallItem::CalcClusterize(ImageBuffer &Target , int dx ,int dy,PureFlexAreaListContainer &NGArea)
{
	double  OutsideCol=OutsideArea.GetAverage(Target, dx , dy);
	int	Threshold=OutsideCol*1.2;

	MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
	int	N=GetArea().GetFLineLen();
	for(int n=0;n<N;n++){
		int	y	=GetArea().GetFLineAbsY(n);
		int	Y	=y+dy;
		if(Y<0 || GetMaxLines()<=Y)
			continue;
		int	hY=y-MapYPos;
		if(hY<0 || YLen<=hY)
			continue;
		int	x1	=GetArea().GetFLineLeftX(n);
		int	X1	=x1+dx;
		int	Numb=GetArea().GetFLineNumb(n);
		BYTE	*s=Target.GetY(Y);
		BYTE	*d=BmpMap[hY];
		for(int i=0;i<Numb;i++){
			int	X=X1+i;
			if(X<0)
				continue;
			if(X>=GetDotPerLine())
				break;
			int	hX=x1-MapXPos+i;
			if(hX<0)
				continue;
			if(hX>=XLen)
				break;
			if(s[X]<=Threshold){		//Pick up NG
				SetBmpBitOnY1(d,hX);
			}
		}
	}
	GetLayersBase()->ThinAreaN(BmpMap
				,TmpMap
				,XByte ,YLen ,1,NULL,false);
	GetLayersBase()->FatAreaN(BmpMap
				,TmpMap
				,XByte ,YLen ,1,NULL,false);
	double	TotalNGSize=0;
	const HoleWallThreshold	*RThr=GetThresholdR();
	PickupFlexArea(BmpMap ,XByte ,XLen, YLen ,NGArea ,-1,false);
	for(PureFlexAreaList *f=NGArea.GetFirst();f!=NULL;){
		PureFlexAreaList *NextF=f->GetNext();
		if(f->GetPatternByte()<RThr->NGSize){
			NGArea.RemoveList(f);
			delete	f;
		}
		else{
			TotalNGSize+=f->GetPatternByte();
		}
		f=NextF;
	}
	return TotalNGSize;
}
void	HoleWallItem::CopyArea(HoleWallItem &BI)
{
	SetArea(BI.GetArea());
	OutsideArea=BI.OutsideArea;
}

void	HoleWallItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	HoleWallDrawAttr	*BAttr=dynamic_cast<HoleWallDrawAttr *>(Attr);
	if(BAttr!=NULL){
		QColor	SavedColor;
		SavedColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	BAttr->NormalColor=BAttr->BlockColor0;	break;
			case 1:	BAttr->NormalColor=BAttr->BlockColor1;	break;
			case 2:	BAttr->NormalColor=BAttr->BlockColor2;	break;
			case 3:	BAttr->NormalColor=BAttr->BlockColor3;	break;
			case 4:	BAttr->NormalColor=BAttr->BlockColor4;	break;
			case 5:	BAttr->NormalColor=BAttr->BlockColor5;	break;
			case 6:	BAttr->NormalColor=BAttr->BlockColor6;	break;
			case 7:	BAttr->NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		BAttr->NormalColor=SavedColor;
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	HoleWallItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false){
				QColor	d=Qt::yellow;
				d.setAlpha(150);
			}
		}
	}
}

//===========================================================================================
