/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMakeAverageImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "MakeAverageImageResource.h"
#include "XMakeAverageImage.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XMakeAverageImagePacket.h"
#include <QColor>
#include <omp.h>
#include "swap.h"
#include "XMaskingFromGeneral.h"
#include "XMainSchemeMemory.h"
#include "XImageProcess.h"

MakeAverageImageThreshold::MakeAverageImageThreshold(MakeAverageImageItem *parent)
	:AlgorithmThreshold(parent)
{
	SearchDot=10;
	RotationDegree=5;
}

void	MakeAverageImageThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MakeAverageImageThreshold *s=(const MakeAverageImageThreshold *)&src;
	SearchDot		=s->SearchDot;
	RotationDegree	=s->RotationDegree;
}
bool	MakeAverageImageThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MakeAverageImageThreshold *d=(const MakeAverageImageThreshold *)&src;
	if(SearchDot		!= d->SearchDot)	return false;
	if(RotationDegree	!= d->RotationDegree)	return false;
	return true;
}
bool	MakeAverageImageThreshold::Save(QIODevice *f)
{
	WORD	Ver=MakeAverageImageVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f, SearchDot) == false)
		return false;
	if(::Save(f, RotationDegree) == false)
		return false;
	return true;
}
bool	MakeAverageImageThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f, SearchDot) == false)
		return false;
	if(::Load(f, RotationDegree) == false)
		return false;
	return true;
}

MakeAverageImageUsageAreaThreshold::MakeAverageImageUsageAreaThreshold(MakeAverageImageUsageAreaItem *parent)
	:AlgorithmThreshold(parent)
{
}

//==============================================================
MakeAverageImageItem::MakeAverageImageItem(void)
{
	AVector=NULL;
	AdoptedLayer=0;
}
ExeResult	MakeAverageImageItem::ExecuteInitialAfterEdit(int ExeID, int ThreadNo
														, ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx, cy;
	if(GetCenter(cx, cy)==true){
		AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx, cy,false);
		if(AVector != NULL)
			AVector->Set(this);
	}
	else{
		AVector=NULL;
	}
	ImagePointerContainer ImageList;
	GetMasterBuffList(ImageList);
	AdoptedLayer=0;
	double	MaxV=0;
	for(int layer=0;layer < GetLayerNumb();layer++) {
		double	Average;
		if(ImageList[layer]!=NULL){
			double	Var=GetArea().GetVar(0, 0, *ImageList[layer], Average);
			double	V=sqrt(Var) / Average;
			if(MaxV < V) {
				MaxV=V;
				AdoptedLayer=layer;
			}
		}
	}
	MakeAverageImageBase *ABase=(MakeAverageImageBase *)GetParentBase();
	GetThresholdW()->SearchDot		=ABase->DefaultSearchDot;
	GetThresholdW()->RotationDegree	=ABase->DefaultRotationDegree;

	return _ER_true;
}

static	int	DbgItemID=647;
static	int	DbgCounter=0;

ExeResult	MakeAverageImageItem::ExecuteScanning(int ExeID, int ThreadNo, ResultInItemRoot *Res)
{
	if(GetID()==DbgItemID){
		DbgCounter++;
	}
	int	mx, my;
	if(AVector != NULL) {
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else {
		AlignmentPacket2D	V;
		int	cx, cy;
		GetCenter(cx, cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ImagePointerContainer MasterImageList;
	GetMasterBuffList(MasterImageList);
	ImagePointerContainer TargetImageList;
	GetTargetBuffList(TargetImageList);

	double	sMaxD=0;
	int	sMaxDx=0;
	int	sMaxDy=0;
	double	MaxR=0;
	int Isolation=3;
	FlexArea &Area=GetArea();

	int		Cx,Cy;
	Area.GetCenter(Cx,Cy);
	double	AreaLen=hypot(Area.GetWidth(),Area.GetHeight());
	double	DivR=atan(2.0/AreaLen);
	const MakeAverageImageThreshold	*RThr=GetThresholdR();
	double	RotRange=RThr->RotationDegree*2.0*M_PI/360.0;

	for(double R=-RotRange;R<=RotRange;R+=DivR){
		for(int dy=-RThr->SearchDot;dy <= RThr->SearchDot;dy+=Isolation) {
			for(int dx=-RThr->SearchDot;dx <= RThr->SearchDot;dx+=Isolation) {


				double	D=Area.GetCoeff(*MasterImageList[AdoptedLayer]
												, mx+dx, my+dy ,Cx,Cy,R
												, *TargetImageList[AdoptedLayer]
												, Isolation, true);
				if(sMaxD < D) {
					sMaxD=D;
					sMaxDx=dx;
					sMaxDy=dy;
					MaxR	=R;
				}
			}
		}
	}
	double	MaxD=0;
	int	MaxDx=0;
	int	MaxDy=0;
	for(int dy=-Isolation;dy <= Isolation;dy++) {
		for(int dx=-Isolation;dx <= Isolation;dx++) {
			double	D=Area.GetCoeff(*MasterImageList[AdoptedLayer]
											, mx+sMaxDx+dx, my+sMaxDy + dy ,Cx,Cy,MaxR
											, *TargetImageList[AdoptedLayer]
											, 1, true);
			if(MaxD < D) {
				MaxD=D;
				MaxDx=sMaxDx + dx;
				MaxDy=sMaxDy + dy;
			}
		}
	}
	int	Mx=mx+MaxDx;
	int	My=my+MaxDy;
	double	SinS=sin(MaxR);
	double	CosS=cos(MaxR);	
	int		Width	=GetDotPerLine();
	int		Height	=GetMaxLines();

	for(int layer=0;layer < GetLayerNumb();layer++) {
		MakeAverageImageInPage::AverageLayerImage *L=((MakeAverageImageInPage *)GetParentInPage())->ALayerImages[layer];
		//ImageBuffer	*MImage=MasterImageList[layer];
		ImageBuffer *TImage=TargetImageList[layer];
		ImageBuffer *LImage=&L->LightImage;
		ImageBuffer *DImage=&L->DarkImage;
		ImageBuffer *AImage=&L->AddedImage;
		ImageBuffer *VImage=&L->Added2Image;
		int	N=Area.GetFLineLen();
		for(int i=0;i < N;i++) {
			int	sAbsY	=Area.GetFLineAbsY(i);
			int	sLeftX	=Area.GetFLineLeftX(i);
			int	Numb	=Area.GetFLineNumb(i);

			if(Numb > 0) {
				BYTE *wL=&LImage->GetY(sAbsY)[sLeftX];
				BYTE *wD=&DImage->GetY(sAbsY)[sLeftX];
				WORD *wA=&((WORD *)AImage->GetY(sAbsY))[sLeftX];
				DWORD *wV=&((DWORD *)VImage->GetY(sAbsY))[sLeftX];

				double	SinDxY=-(sAbsY-Cy)*SinS+Cx+Mx;
				double	CosDyY= (sAbsY-Cy)*CosS+Cy+My;

				for(int n=0;n < Numb;n++) {
					int	x=sLeftX+n;
					int	DstY=(x-Cx)*SinS+CosDyY;
					if(0<=DstY && DstY<Height){
						int	DstX=(x-Cx)*CosS+SinDxY;
						if(0<=DstX && DstX<Width){
							BYTE t=TImage->GetY(DstY)[DstX];

							if(t > *wL) {
								*wA+=*wL;
								*wV+=(*wL)*(*wL);
								*wL=t;
							}
							else{
								if(t < *wD) {
									*wA+=*wD;
									*wV+=(*wD)*(*wD);
									*wD=t;
								}
								else {
									*wA+=t;
									*wV+=t*t;
								}
							}
						}
					}
					wL++;
					wD++;
					wA++;
					wV++;
				}
			}
		}
	}

	return _ER_true;
}
void	MakeAverageImageItem::CopyThresholdOnly(MakeAverageImageItem *src)
{
	GetThresholdW()->SearchDot=src->GetThresholdR(GetLayersBase())->SearchDot;
}

void	MakeAverageImageItem::DrawArea(FlexArea &area, QImage &pnt, int movx, int movy, double ZoomRate, AlgorithmDrawAttr *Attr)
{
	MakeAverageImageDrawAttr	*MAttr=dynamic_cast<MakeAverageImageDrawAttr *>(Attr);
	if(MAttr!=NULL && MAttr->ModeShowItems == true) {
		AlgorithmItemPI::DrawArea(area, pnt, movx, movy, ZoomRate, Attr);
	}
}
int		MakeAverageImageItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 10;
}
void	MakeAverageImageItem::SetIndependentItemData(int32 Command, int32 LocalPage, int32 Layer, AlgorithmItemRoot *Data,IntList &EdittedMemberID, QByteArray &Something,QByteArray &AckData)
{
	if(Command == SetIndependentItemDataCommand_OnlyOne) {
		if(GetParentInPage()->GetPage() == LocalPage && GetID() == Data->GetID()) {
			MakeAverageImageInPage *Pg=dynamic_cast<MakeAverageImageInPage *>(GetParentInPage());
			UndoElement<MakeAverageImageInPage> *UPointer=new UndoElement<MakeAverageImageInPage>(Pg, &MakeAverageImageInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(), GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MakeAverageImageItem *src=(MakeAverageImageItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command == SetIndependentItemDataCommand_All) {
		if(GetLibID() == ((MakeAverageImageItem *)Data)->GetLibID()) {
			MakeAverageImageInPage *Pg=dynamic_cast<MakeAverageImageInPage *>(GetParentInPage());
			UndoElement<MakeAverageImageInPage> *UPointer=new UndoElement<MakeAverageImageInPage>(Pg, &MakeAverageImageInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(), GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MakeAverageImageItem *src=(MakeAverageImageItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
}
//==============================================================
MakeAverageImageUsageAreaItem::MakeAverageImageUsageAreaItem(void)
{
}

void	MakeAverageImageUsageAreaItem::DrawArea(FlexArea &area, QImage &pnt, int movx, int movy, double ZoomRate, AlgorithmDrawAttr *Attr)
{
	MakeAverageImageBase *ABase=(MakeAverageImageBase *)GetParentBase();
	QColor	NormalColor	=Attr->NormalColor;
	Attr->NormalColor	=ABase->UsageAreaColor;
	AlgorithmItemPI::DrawArea(area, pnt, movx, movy, ZoomRate, Attr);
	Attr->NormalColor	=NormalColor;
}
int		MakeAverageImageUsageAreaItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 5;
}