/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\SwitchPhase\XSwitchPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "SwitchPhaseResource.h"
#include "XSwitchPhase.h"
#include "XResult.h"
#include "swap.h"
#include "XAlgorithmDLL.h"
#include <ctype.h>
#include "XDataInLayer.h"
#include<omp.h>
//#include "XSwitchPhasePacket.h"

//=====================================================================================

SwitchPhaseThreshold::SwitchPhaseThreshold(SwitchPhaseItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDot		=10;
}
SwitchPhaseThreshold::~SwitchPhaseThreshold(void)
{
}
void	SwitchPhaseThreshold::RegistHist(void)
{
	RegistInt	("Shift-X"	,Hist_SwitchPhaseShiftX		);
	RegistInt	("Shift-Y"	,Hist_SwitchPhaseShiftY		);
}

void	SwitchPhaseThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const SwitchPhaseThreshold *s=(const SwitchPhaseThreshold *)&src;
	SearchDot	=s->SearchDot;
}
bool	SwitchPhaseThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const SwitchPhaseThreshold *s=(const SwitchPhaseThreshold *)&src;
	if(SearchDot	!=s->SearchDot)	return false;
	return true;
}
bool	SwitchPhaseThreshold::Save(QIODevice *file)
{
	if(::Save(file,SearchDot)==false)
		return(false);

	return true;
}
bool	SwitchPhaseThreshold::Load(QIODevice *file)
{
	if(::Load(file,SearchDot)==false)
		return(false);

	return true;
}
//=====================================================================================
SwitchPhaseItem::SwitchPhaseItem(void)
{
	AVector	=NULL;
	DimNumb=0;
	Dim=NULL;
	DimSortable=NULL;
	AdaptedLayer	=0;
	ResultDx=ResultDy=0;
	MatchingResult	=0;
	Skip=4;
}
SwitchPhaseItem::~SwitchPhaseItem(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	if(DimSortable!=NULL){
		delete	[]DimSortable;
		DimSortable=NULL;
	}
	DimNumb=0;
}
bool    SwitchPhaseItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    SwitchPhaseItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	return true;
}

void	SwitchPhaseItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SwitchPhaseDrawAttr	*LAttr=dynamic_cast<SwitchPhaseDrawAttr *>(Attr);
	if(LAttr!=NULL){
		SetVisible(true);
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

		QRgb	Col=qRgba(0,0,255,128);
		MatchingAreaSkip.DrawAlpha(0,0,&pnt,Col,ZoomRate,movx ,movy);
	}
}

void	SwitchPhaseItem::DrawResult(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		int	PhaseCode=GetPhaseCode();
		int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
		if(PhaseCode==CurrentPhase){
			QColor	NCol(0,255,100,100);
			GetArea().DrawAlpha(0,0 ,&IData ,NCol.rgba()	,ZoomRate ,MovX ,MovY);

			QColor	SCol(80,255,0,100);
			GetArea().DrawAlpha(ResultDx+Res->GetAlignedX(),ResultDy+Res->GetAlignedY() 
								,&IData ,SCol.rgba()
								,ZoomRate ,MovX ,MovY);

			int	cx,cy;
			GetCenter(cx,cy);
			PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate
				,QString(/**/"Shift:")+QString::number(ResultDx)+QString(/**/",")+QString::number(ResultDy));
			PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate+16
				,QString(/**/"Matching:")+QString::number(MatchingResult,'f',4));
		}
	}
}

ExeResult	SwitchPhaseItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
		AVector->Priority=10;
	}

	ImagePointerContainer ImageList;
	GetMasterBuffList(ImageList);

	int	MaxD=0;
	AdaptedLayer=0;
	SwitchPhaseBase	*ABase=(SwitchPhaseBase *)GetParentBase();

	for(int layer=0;layer<GetLayerNumb();layer++){
		FlexAreaImageListCoeff	Tmp;
		Tmp.Set(GetArea(),*ImageList[layer]);
		Tmp.MakeSum();
		double	D=Tmp.GetV();
		if(D>MaxD){
			MaxD=D;
			AdaptedLayer=layer;
			MatchingArea=Tmp;
			//MatchingAreaSkip.MakeDivArea(MatchingArea,*ImageList[layer]
			//							,ABase->ItemAdoptedRate,ABase->ItemRateFromPeak);
			MatchingAreaSkip.Set(GetArea(),*ImageList[layer],Skip);
			MatchingAreaSkip.MakeSum();
		}
	}
	if(Dim!=NULL){
		delete	[]Dim;
	}
	if(DimSortable!=NULL){
		delete	[]DimSortable;
	}
	const SwitchPhaseThreshold	*RThr=GetThresholdR();
	DimNumb=(2*RThr->SearchDot+1)*(2*RThr->SearchDot+1);
	Dim			=new struct	ShiftDim[DimNumb];
	DimSortable	=new struct	ShiftDim[DimNumb];
	int	n=0;
	int	SkipForRoughSearch=((SwitchPhaseBase *)GetParentBase())->SkipForRoughSearch;
	for(int dy=-RThr->SearchDot;dy<=RThr->SearchDot;dy+=SkipForRoughSearch){
		for(int dx=-RThr->SearchDot;dx<=RThr->SearchDot;dx+=SkipForRoughSearch){
			Dim[n].ShiftX=dx;
			Dim[n].ShiftY=dy;
			n++;
		}
	}
	DimNumb=n;

	return _ER_true;
}

int	DimSortableFunc(const void *a ,const void *b)
{
	struct	SwitchPhaseItem::ShiftDim	*pa=(struct	SwitchPhaseItem::ShiftDim *)a;
	struct	SwitchPhaseItem::ShiftDim	*pb=(struct	SwitchPhaseItem::ShiftDim *)b;
	if(pa->D<pb->D)
		return 1;
	else
	if(pa->D>pb->D)
		return -1;
	return 0;
}

ExeResult	SwitchPhaseItem::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
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
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	static	bool	TestMode=false;

	if(TestMode==false){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<DimNumb;i++){
				DimSortable[i].D=MatchingAreaSkip.CalcCoeff(Dim[i].ShiftX+mx,Dim[i].ShiftY+my,*ImageList[AdaptedLayer]);
				DimSortable[i].ShiftX=Dim[i].ShiftX;
				DimSortable[i].ShiftY=Dim[i].ShiftY;
			}
		}
	}
	else{
		for(int i=0;i<DimNumb;i++){
			DimSortable[i].D=MatchingAreaSkip.CalcCoeff(Dim[i].ShiftX+mx,Dim[i].ShiftY+my,*ImageList[AdaptedLayer]);
			DimSortable[i].ShiftX=Dim[i].ShiftX;
			DimSortable[i].ShiftY=Dim[i].ShiftY;
		}
	}
	QSort(DimSortable,DimNumb,sizeof(struct	ShiftDim),DimSortableFunc);

	double	MaxD=0;
	int	tMaxDx=0;
	int	tMaxDy=0;
	int	SkipForRoughSearch=((SwitchPhaseBase *)GetParentBase())->SkipForRoughSearch;
	if(DimNumb>0 && DimSortable!=NULL){
		for(int n=0;n<10;n++){
			for(int dy=-SkipForRoughSearch;dy<=SkipForRoughSearch;dy+=4){
				for(int dx=-SkipForRoughSearch;dx<=SkipForRoughSearch;dx+=4){
					double D=MatchingAreaSkip.CalcCoeff(DimSortable[n].ShiftX+dx+mx,DimSortable[n].ShiftY+dy+my,*ImageList[AdaptedLayer]);
					if(D>MaxD){
						MaxD=D;
						tMaxDx	=DimSortable[n].ShiftX+dx;
						tMaxDy	=DimSortable[n].ShiftY+dy;
					}
				}
			}
		}
	}

	MaxD=0;
	int	MaxDx=0;
	int	MaxDy=0;
	for(int dy=-3;dy<=3;dy+=2){
		for(int dx=-3;dx<=3;dx+=2){
			double D=MatchingArea.CalcCoeff(tMaxDx+dx+mx,tMaxDy+dy+my	,*ImageList[AdaptedLayer]);
			if(D>MaxD){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	MaxD=0;
	int	MaxTx=0;
	int	MaxTy=0;
	for(int dy=-1;dy<=1;dy++){
		for(int dx=-1;dx<=1;dx++){
			double D=MatchingArea.CalcCoeff(tMaxDx+MaxDx+dx+mx,tMaxDy+MaxDy+dy+my,*ImageList[AdaptedLayer]);
			if(D>MaxD){
				MaxD=D;
				MaxTx=dx;
				MaxTy=dy;
			}
		}
	}

	MatchingResult=MaxD;
	ResultDx	=tMaxDx+MaxDx+MaxTx;
	ResultDy	=tMaxDy+MaxDy+MaxTy;
	Res->SetAlignedXY(mx,my);

	return _ER_true;
}

void	SwitchPhaseItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			SwitchPhaseInPage	*Pg=dynamic_cast<SwitchPhaseInPage *>(GetParentInPage());
			UndoElement<SwitchPhaseInPage>	*UPointer=new UndoElement<SwitchPhaseInPage>(Pg,&SwitchPhaseInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			SwitchPhaseItem *src=(SwitchPhaseItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((SwitchPhaseItem *)Data)->GetLibID()){
			SwitchPhaseInPage	*Pg=dynamic_cast<SwitchPhaseInPage *>(GetParentInPage());
			UndoElement<SwitchPhaseInPage>	*UPointer=new UndoElement<SwitchPhaseInPage>(Pg,&SwitchPhaseInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			SwitchPhaseItem *src=(SwitchPhaseItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}

}
void	SwitchPhaseItem::CopyThresholdOnly(SwitchPhaseItem &src)
{
	GetThresholdW()->CopyFrom(*((SwitchPhaseThreshold *)src.GetThresholdR()));
}

QString	SwitchPhaseItem::GetComment(Type_ItemComment t)
{
	return   QString(/**/"Phase:")+QString::number(GetPhaseCode())
			+QString(/**/" (")+GetParamGlobal()->GetPhaseString(GetPhaseCode())+QString(/**/")");
}
