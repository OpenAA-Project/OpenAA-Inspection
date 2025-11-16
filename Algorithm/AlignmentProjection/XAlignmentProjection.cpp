/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlignmentProjection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XAlignmentProjectionResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentProjection.h"
#include "XCrossObj.h"
#include "XPointer.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XImageProcess.h"
#include <omp.h>

extern	char	*sRoot;
extern	char	*sName;

//==========================================================================================
AlignmentProjectionInPage::AlignmentProjectionInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
	ModeParallel.ModeParallelExecutePreAlignment=true;
}


AlignmentPacket2D	*AlignmentProjectionInPage::AppendAlignmentProjectionPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal)
{
	int	LibType	=Item->GetParentBase()->GetLibType();
	int	LibID	=Item->GetLibID();
	int	SourceID=Item->GetID();

	AlignmentPacket2DCreaterMutex.lock();
	for(AlignmentPacket2DList *a=AlignmentPacket2DContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PosXOnTarget==localX && a->PosYOnTarget==localY
		&& a->LibType==LibType && a->LibID==LibID){	// && a->SourceID==SourceID){
			AlignmentPacket2DCreaterMutex.unlock();
			return a;
		}
	}
	AlignmentPacket2DList	*L=new AlignmentPacket2DList();
	L->LibType		=LibType;
	L->LibID		=LibID;
	L->SourceID		=Item->GetID();
	L->PosXOnTarget	=localX;
	L->PosYOnTarget	=localY;
	L->AlignmentItem=NULL;
	for(AlgorithmItemPI *p=GetFirstData();p!=NULL;p=p->GetNext()){
		AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(p);
		if(Item!=NULL){
			if(Item->IsInclude(L->PosXOnTarget ,L->PosYOnTarget)==true){
				L->AlignmentItem=Item;
				break;
			}
		}
	}
	if(L->AlignmentItem==NULL){
		AlgorithmItemPI *p=GetFirstData();
		AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(p);
		if(Item!=NULL){
			L->AlignmentItem=Item;
		}
	}
	AlignmentPacket2DContainer.AppendList(L);
	AlignmentPacket2DCreaterMutex.unlock();

	return L;
}

ExeResult	AlignmentProjectionInPage::ExecuteInitialAfterEdit	(int ExeID 
																,ResultInPageRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	AlignmentPacket2DContainer.RemoveAll();
	return AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}

int	AlignmentProjectionLibType=1;
int	AlignmentProjectionPage=0;
int	AlignmentProjectionID	=139;
int	AlignmentProjectionDbg;

ExeResult	AlignmentProjectionInPage::ExecuteAlignment		(int ExeID,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteAlignment	(ExeID,Res);

	int	AlignmentLargePacket2ContainerNumb=AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList *PListDim[10000];
	AlignmentPacket2DList **PList;

	if(AlignmentLargePacket2ContainerNumb>sizeof(PListDim)/sizeof(PListDim[0])){
		PList=new AlignmentPacket2DList *[AlignmentLargePacket2ContainerNumb];
	}
	else{
		PList=PListDim;
	}
	int	N=0;
	for(AlignmentPacket2DList *p=AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}
	if(GetParamGlobal()->CalcSingleThread==true){
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *a=PList[i];
			if(a->AlignmentItem!=NULL){
				a->AlignmentItem->GetAlignmentProjection(*a);
			}
		}
	}
	else{
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
				AlignmentPacket2DList *a=PList[i];
				if(a->AlignmentItem!=NULL){
					a->AlignmentItem->GetAlignmentProjection(*a);
				}
			}
		}
	}
	if(PListDim!=PList){
		delete	[]PList;
		PList=NULL;
	}


	return Ret;
}

void	AlignmentProjectionInPage::GetAlignmentProjection(AlignmentPacket2D &AData)
{
	if(AData.LibType==AlignmentProjectionLibType
	&& AData.Page==AlignmentProjectionPage
	&& AData.SourceID==AlignmentProjectionID)
		AlignmentProjectionDbg++;

	AData.ShiftX=0;
	AData.ShiftY=0;
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(AData.PosXOnTarget ,AData.PosYOnTarget)==true){
			AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(a);
			if(Item!=NULL){
				Item->GetAlignmentProjection(AData);
			}
		}
	}
}

void	AlignmentProjectionInPage::GetAlignmentProjectionByHandle(AlignmentPacket2D &AData ,void *Handle)
{
	if(AData.LibType==AlignmentProjectionLibType
	&& AData.Page==AlignmentProjectionPage
	&& AData.SourceID==AlignmentProjectionID)
		AlignmentProjectionDbg++;
	AData.ShiftX=0;
	AData.ShiftY=0;
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(AData.PosXOnTarget ,AData.PosYOnTarget)==true){
			AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(a);
			if(Item!=NULL){
				Item->GetAlignmentByHandle(AData,Handle);
			}
		}
	}
}

void	AlignmentProjectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(a);
			if(Item!=NULL){
				//Item->SetSearchDot(CmdAlignmentSetSearchDotVar->SearchDotX,CmdAlignmentSetSearchDotVar->SearchDotY);
			}
		}
		return;
	}
	AddAlignmentProjectionPointPacket	*AddAlignmentProjectionPointPacketVar=dynamic_cast<AddAlignmentProjectionPointPacket *>(packet);
	if(AddAlignmentProjectionPointPacketVar!=NULL){
		AlignmentProjectionItem	*item=(AlignmentProjectionItem *)CreateItem(0);
		item->SetArea(AddAlignmentProjectionPointPacketVar->Area);
		item->SetManualCreated(true);
		item->SetItemName(AddAlignmentProjectionPointPacketVar->ItemName);
		item->GetThresholdW()->PeakCount	=AddAlignmentProjectionPointPacketVar->PeakCount;
		item->GetThresholdW()->Angle		=AddAlignmentProjectionPointPacketVar->Angle;
		item->GetThresholdW()->UsageLayer	=AddAlignmentProjectionPointPacketVar->UsageLayer;
		item->GetThresholdW()->AbandonRateL	=AddAlignmentProjectionPointPacketVar->AbandonRateL;
		item->GetThresholdW()->AbandonRateH	=AddAlignmentProjectionPointPacketVar->AbandonRateH;

		AppendItem(item);
		return;
	}
	ModifyAlignmentProjectionPointPacket	*ModifyAlignmentProjectionPointPacketVar=dynamic_cast<ModifyAlignmentProjectionPointPacket *>(packet);
	if(ModifyAlignmentProjectionPointPacketVar!=NULL){
		AlignmentProjectionItem	*item=(AlignmentProjectionItem *)SearchIDItem(ModifyAlignmentProjectionPointPacketVar->ItemID);
		if(item!=NULL){
			item->SetManualCreated(true);
			item->SetItemName(ModifyAlignmentProjectionPointPacketVar->ItemName);
			item->GetThresholdW()->PeakCount	=ModifyAlignmentProjectionPointPacketVar->PeakCount;
			item->GetThresholdW()->Angle		=ModifyAlignmentProjectionPointPacketVar->Angle;
			item->GetThresholdW()->UsageLayer	=ModifyAlignmentProjectionPointPacketVar->UsageLayer;
			item->GetThresholdW()->AbandonRateL	=ModifyAlignmentProjectionPointPacketVar->AbandonRateL;
			item->GetThresholdW()->AbandonRateH	=ModifyAlignmentProjectionPointPacketVar->AbandonRateH;
		}
		return;
	}
	ReqAlignmentProjectionPointPacket	*ReqAlignmentProjectionPointPacketVar=dynamic_cast<ReqAlignmentProjectionPointPacket *>(packet);
	if(ReqAlignmentProjectionPointPacketVar!=NULL){
		AlignmentProjectionItem	*item=(AlignmentProjectionItem *)SearchIDItem(ReqAlignmentProjectionPointPacketVar->ItemID);
		if(item!=NULL){
			ReqAlignmentProjectionPointPacketVar->ItemName		=item->GetItemName();
			ReqAlignmentProjectionPointPacketVar->PeakCount		=item->GetThresholdW()->PeakCount	;
			ReqAlignmentProjectionPointPacketVar->Angle			=item->GetThresholdW()->Angle		;
			ReqAlignmentProjectionPointPacketVar->UsageLayer	=item->GetThresholdW()->UsageLayer	;
			ReqAlignmentProjectionPointPacketVar->AbandonRateL	=item->GetThresholdW()->AbandonRateL	;
			ReqAlignmentProjectionPointPacketVar->AbandonRateH	=item->GetThresholdW()->AbandonRateH	;
		}
		return;
	}

	/*
	AddAlignmentMarkPacket	*AddAlignmentMarkPacketVar=dynamic_cast<AddAlignmentMarkPacket *>(packet);
	if(AddAlignmentMarkPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlignmentProjectionInLayer	*L=(AlignmentProjectionInLayer *)GetLayerData(Layer);
			for(XAlignmentProjectionArea *a=L->Areas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Area.CheckOverlap(&AddAlignmentMarkPacketVar->Area)==true){
					AddAlignmentProjectionPointPacket	Cmd(GetLayersBase());
					Cmd.AreaID		=a->AreaID;
					Cmd.Area		=AddAlignmentMarkPacketVar->Area;
					Cmd.MoveDotX	=AddAlignmentMarkPacketVar->MoveDotX	;
					Cmd.MoveDotY	=AddAlignmentMarkPacketVar->MoveDotY	;
					Cmd.MoveDotX2	=AddAlignmentMarkPacketVar->MoveDotX2	;
					Cmd.MoveDotY2	=AddAlignmentMarkPacketVar->MoveDotY2	;
					Cmd.SearchAround=AddAlignmentMarkPacketVar->SearchAround;
					Cmd.GroupNumber	=AddAlignmentMarkPacketVar->GroupNumber	;
					Cmd.UsageGlobal	=AddAlignmentMarkPacketVar->UsageGlobal	;
					L->TransmitDirectly(&Cmd);
					return;
				}
			}
		}
		return;
	}
	*/
	SelectAlignmentPoints	*SelectAlignmentPointsVar=dynamic_cast<SelectAlignmentPoints *>(packet);
	if(SelectAlignmentPointsVar!=NULL){
		SelectArea(SelectAlignmentPointsVar->Area,false);
		return;
	}
}
bool	AlignmentProjectionInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentProjectionItem	*a=dynamic_cast<AlignmentProjectionItem *>(k);
			if(a!=NULL){
				double	Cx,Cy;
				double	AckX,AckY;
				a->GetCenter(Cx,Cy);
				if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
					a->MoveTo(AckX-Cx,AckY-Cy);
				}
			}
		}
		return true;
	}

	return false;
}

void	AlignmentProjectionInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		AlignmentProjectionItem	*BI=(AlignmentProjectionItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

bool	AlignmentProjectionInPage::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy
														,FlexArea &area ,AlgorithmBase *OriginBase
														,int ItemClass)
{
	if(Buff.isOpen()==false){
		Buff.open(QIODevice::ReadOnly);
	}
	else{
		Buff.close();
		Buff.open(QIODevice::ReadOnly);		
	}
	int32	Kind;
	if(::Load(&Buff,Kind)==false)
		return false;

	WORD	PeakCount;
	if(::Load(&Buff,PeakCount)==false)
		return false;
	double	Angle;
	if(::Load(&Buff,Angle)==false)
		return false;
	int		UsageLayer;
	if(::Load(&Buff,UsageLayer)==false)
		return false;
	double		AbandonRateL;
	double		AbandonRateH;
	if(::Load(&Buff,AbandonRateL)==false)
		return false;
	if(::Load(&Buff,AbandonRateH)==false)
		return false;

	AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(CreateItem(ItemClass));
	Item->GetThresholdW()->PeakCount	=PeakCount;
	Item->GetThresholdW()->Angle		=Angle;
	Item->GetThresholdW()->UsageLayer	=UsageLayer;
	Item->GetThresholdW()->AbandonRateL	=AbandonRateL;
	Item->GetThresholdW()->AbandonRateH	=AbandonRateH;
	Item->SetArea(area);

	Item->SetManualCreated(true);
	AppendItem(Item);

	UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
	::Save(UPointer->GetWritePointer(),Item->GetID());
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	
	Item->SetOrigin(OriginBase);
	
	Changed=true;
	CalcDone =false;

	return true;
}
//==========================================================================================
AlignmentProjectionBase::AlignmentProjectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea			=Qt::darkYellow;
	ColorAreaSelected	=Qt::yellow;
	ColorAreaActive		=Qt::red;
	ColorPoint			=Qt::darkGreen;
	ColorPointSelected	=Qt::green;
	ColorPointActive	=Qt::red;
	AlphaLevel			=100;
	UseBitBuff			=false;
	DrawOnlyTopPage		=false;

	SetParam(&ColorArea					, /**/"Color"		,/**/"ColorArea"			,"AlignmentProjection Area color");
	SetParam(&ColorAreaSelected			, /**/"Color"		,/**/"ColorAreaSelected"	,"Selected AlignmentProjection Area color");
	SetParam(&ColorAreaActive			, /**/"Color"		,/**/"ColorAreaActive"		,"Active AlignmentProjection Area color");
	SetParam(&ColorPoint				, /**/"Color"		,/**/"ColorPoint"			,"AlignmentProjection Point color");
	SetParam(&ColorPointSelected		, /**/"Color"		,/**/"ColorPointSelected"	,"Selected AlignmentProjection Point color");
	SetParam(&ColorPointActive			, /**/"Color"		,/**/"ColorPointActive"		,"Active AlignmentProjection Point color");
	SetParam(&AlphaLevel				, /**/"Color"		,/**/"AlphaLevel"			,"AlignmentProjection transparent level");
	SetParam(&UseBitBuff				, /**/"Setting"		,/**/"UseBitBuff"			,"Use BitBuff for MasterImage");
	SetParam(&DrawOnlyTopPage			, /**/"Setting"		,/**/"DrawOnlyTopPage"		,"Draw only current top page");
}

AlgorithmDrawAttr	*AlignmentProjectionBase::CreateDrawAttr(void)
{
	return new AlignmentProjectionDrawAttr();
}

bool	AlignmentProjectionBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	FlexArea	area=item->Area;
	area.MoveToNoClip(globalDx,globalDy);
	for(int page=0;page<GetPageNumb();page++){
		if(GetLayersBase()->GetPageData(page)->IsOverlapped(area)==true){
			GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(area);
			AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(GetPageData(page));
			if(Ap!=NULL){
				AlgorithmItemRoot	*a=Ap->CreateItem(item->ItemClassType);
				QBuffer	Buff(&item->ItemData);
				Buff.open(QIODevice::ReadOnly);
				ListLayerAndIDPack	SelectedArea;
				SelectedArea.Load(&Buff);
				for(ListLayerAndID *s=SelectedArea.GetFirst();s!=NULL;s=s->GetNext()){
					a->SetArea(area);
					Ap->AppendItem(a);
				}
			}
		}
	}
	return true;
}

void	AlignmentProjectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
}

