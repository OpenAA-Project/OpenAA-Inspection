/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentBlock\XAlignmentBlockItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlignmentBlock.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XAlignmentBlockLibrary.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//=====================================================================================

AlignmentBlockThreshold::AlignmentBlockThreshold(AlignmentBlockItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDot	=200;
	MaxDegree	=10;
	LineLength	=20;
	MinVar		=5;
	ThreDiv		=20;
}

void	AlignmentBlockThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AlignmentBlockThreshold *s=(const AlignmentBlockThreshold *)&src;
	SearchDot		=s->SearchDot;
}
bool	AlignmentBlockThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AlignmentBlockThreshold *s=(const AlignmentBlockThreshold *)&src;
	if(SearchDot		==s->SearchDot)
		return true;
	return false;
}
bool	AlignmentBlockThreshold::Save(QIODevice *f)
{
	WORD	Ver=AlignmentBlockVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,MaxDegree)==false)
		return false;
	if(::Save(f,LineLength)==false)
		return false;
	if(::Save(f,MinVar)==false)
		return false;
	if(::Save(f,ThreDiv)==false)
		return false;

	return true;
}

bool	AlignmentBlockThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,MaxDegree)==false)
		return false;
	if(::Load(f,LineLength)==false)
		return false;
	if(::Load(f,MinVar)==false)
		return false;
	if(Ver>=4){
		if(::Load(f,ThreDiv)==false)
			return false;
	}
	return true;
}

void	AlignmentBlockThreshold::FromLibrary(AlgorithmLibrary *src)
{
	AlignmentBlockLibrary	*s=dynamic_cast<AlignmentBlockLibrary *>(src);
	if(s!=NULL){
		SearchDot	=s->SearchDot;
		MaxDegree	=s->MaxDegree;
		LineLength	=s->LineLength;
		MinVar		=s->MinVar	;
		ThreDiv		=s->ThreDiv	;
	}
}
void	AlignmentBlockThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	AlignmentBlockLibrary	*d=dynamic_cast<AlignmentBlockLibrary *>(Dest);
	if(d!=NULL){
		d->SearchDot	=SearchDot;
		d->MaxDegree	=MaxDegree;
		d->LineLength	=LineLength;
		d->MinVar		=MinVar	;
		d->ThreDiv		=ThreDiv;
	}
}

//===========================================================================================

AlignmentBlockItem::AlignmentBlockItem(void)
{
	CurrentRotationPatternNo=0;
}

AlignmentBlockItem::~AlignmentBlockItem(void)
{
}

AlignmentBlockItem &AlignmentBlockItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((AlignmentBlockItem *)&src));
	return *this;
}

void	AlignmentBlockItem::CopyThreshold(AlignmentBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((AlignmentBlockThreshold *)src.GetThresholdR()));
}

void	AlignmentBlockItem::CopyThresholdOnly(AlignmentBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((AlignmentBlockThreshold *)src.GetThresholdR()));
}

bool    AlignmentBlockItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;

	return true;
}
bool    AlignmentBlockItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;

	return true;
}

void	AlignmentBlockItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((AlignmentBlockItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AlignmentBlockItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((AlignmentBlockItem *)Data));
		}
	}
}

void	AlignmentBlockItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
}
void	AlignmentBlockItem::CopyArea(AlignmentBlockItem &src)
{
	SetArea(src.GetArea());
}

void	AlignmentBlockItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentBlockDrawAttr	*BAttr=dynamic_cast<AlignmentBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		if(BAttr->ShowLines==true){
			double	MinRadian=99999999;
			RotatedMatchingPattern *MinR=NULL;
			for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->NPList<RotatedMatchingPattern>::GetNext()){
				double	L=fabs(r->Radian-BAttr->Radian);
				if(L<MinRadian){
					MinRadian	=L;
					MinR		=r;
				}
			}
			if(MinR!=NULL){
				QColor	LineCol(255,255,0,128);
				MinR->DrawLine(pnt,LineCol,movx ,movy ,ZoomRate);
			}
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}


}

void	AlignmentBlockItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	cm=Qt::green;
		cm.setAlpha(100);
		GetArea().Draw(0,0,&IData ,cm.rgba()
						,ZoomRate ,MovX ,MovY);

		QColor	ct=Qt::red;
		ct.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,ct.rgba()
						,ZoomRate ,MovX ,MovY);

		int	GWidth	=IData.width();
		int	GHeight=IData.height();

		PData.setBrush(Qt::yellow);
		PData.setPen(Qt::yellow);
	}
}

void	AlignmentBlockItem::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdAlignmentBlockResultInItem	*CmdAlignmentBlockResultInItemVar=dynamic_cast<CmdAlignmentBlockResultInItem *>(packet);
	//if(CmdAlignmentBlockResultInItemVar!=NULL){
	//	if(0<=CmdAlignmentBlockResultInItemVar->ResultIndex
	//	&& CmdAlignmentBlockResultInItemVar->ResultIndex<Results.ResultCount){
	//		RotatedMatchingPattern	*R=GetRotPattern(Results.ResultList[CmdAlignmentBlockResultInItemVar->ResultIndex].RotatedIndex
	//												,Results.ResultList[CmdAlignmentBlockResultInItemVar->ResultIndex].ZoomSizeIndex);
	//		if(R!=NULL){
	//			CmdAlignmentBlockResultInItemVar->Radian=R->Radian;
	//		}
	//	}
	//	return;
	//}
}

void	AlignmentBlockItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	AlgorithmItemPITemplate<AlignmentBlockInPage,AlignmentBlockBase>::MakeIndependentItems(AInd,LocalX ,LocalY);

	//QBuffer	Buff;
	//Buff.open(QIODevice::ReadWrite);
	//MasterPositions.Save(&Buff);
	//AInd->Something=Buff.buffer();
}

ExeResult	AlignmentBlockItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	AlignmentBlockBase	*BBase=tGetParentBase();
	double	RLen=hypot(GetArea().GetWidth(),GetArea().GetHeight())/2.0;
	double	DivDegR=3.0*180.0*atan(1.0/RLen)/M_PI;
	int	N=ceil(GetThresholdR()->MaxDegree/DivDegR/2.0);

	for(int k=-N;k<=N;k++){
		RotatedMatchingPattern	*r=new RotatedMatchingPattern(this ,k*DivDegR*M_PI/180.0);
		RotatedContainer.AppendList(r);
	}

	int	CountRotatedContainer=RotatedContainer.GetCount();
	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int i=0;i<CountRotatedContainer;i++){
			RotatedMatchingPattern	*v=RotatedContainer[i];
			v->BuildInitial(BBase->ModeCalcIncline);
		}
	}

	return Ret;
}

RotatedMatchingPattern	*AlignmentBlockItem::GetRotatedPattern(int n)
{
	return RotatedContainer[n];
}

static	int	DbgPage=1;
static	int	DbgID	=2;
static	int	DbgCounter=0;


ExeResult	AlignmentBlockItem::ExecuteAlignment(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetPage()==DbgPage && GetID()==DbgID){
		DbgCounter++;
	}

	AlignmentBlockBase	*BBase=tGetParentBase();
	ImagePointerContainer TargetImages;
	GetTargetBuffList(TargetImages);

	int	SearchDot=GetThresholdR()->SearchDot;
	int	CountRotatedContainer=RotatedContainer.GetCount();
	//if(GetParamGlobal()->CalcSingleThread==false){
	//	#pragma omp parallel
	//	{                                                
	//		#pragma omp for schedule(dynamic)
	//		for(int i=0;i<CountRotatedContainer;i++){
	//			RotatedMatchingPattern	*v=RotatedContainer[i];
	//			v->MatchByLine(BBase->ModeCalcIncline,0,0,TargetImages,SearchDot);
	//		}
	//	}
	//}
	//else{
		for(int i=0;i<CountRotatedContainer;i++){
			RotatedMatchingPattern	*v=RotatedContainer[i];
			v->MatchByLine(BBase->ModeCalcIncline,0,0,TargetImages,SearchDot);
		}
	//}

	int	iN=0;
	double	MaxResult=0;
	RotatedMatchingPattern *MaxR=NULL;
	for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->NPList<RotatedMatchingPattern>::GetNext(),iN++){
		if(MaxResult<r->Result){
			MaxResult=r->Result;
			MaxR=r;
			CurrentRotationPatternNo	=iN;
		}
	}
	if(MaxR!=NULL){	
		ResultRadian=MaxR->Radian;
		ResultDx	=MaxR->ResultDx;
		ResultDy	=MaxR->ResultDy;
		SetCalcDone(true);
	}
	Res->SetAlignedXY(ResultDx,ResultDy);
	return _ER_true;
}

void	AlignmentBlockItem::CalcByNeighbor(void)
{
	int	Cx,Cy;
	GetCenter(Cx,Cy);
	AlignmentBlockItem *Neighbor=NULL;
	double	MaxLen=99999999;
	for(AlignmentBlockItem *item=tGetParentInPage()->tGetFirstData();item!=NULL;item=item->tGetNext()){
		if(item->IsCalcDone()==true){
			int	icx,icy;
			item->GetCenter(icx,icy);
			double	Len=hypot(Cx-icx,Cy-icy);
			if(Len<MaxLen){
				MaxLen=Len;
				Neighbor=item;
			}
		}
	}
	if(Neighbor!=NULL){
		ResultRadian=Neighbor->ResultRadian;
		ResultDx	=Neighbor->ResultDx;
		ResultDy	=Neighbor->ResultDy;
	}
	else{
		ResultRadian=0;
		ResultDx	=0;
		ResultDy	=0;
	}
}	
