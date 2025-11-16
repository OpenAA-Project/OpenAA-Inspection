/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RWCamRecognition\XRWCamRecognition.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRWCamRecognition.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================

RWCamRecognitionInPage::RWCamRecognitionInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<RWCamRecognitionItem,RWCamRecognitionBase>(parent)
{
}
RWCamRecognitionInPage::~RWCamRecognitionInPage(void)
{
}

static	bool Func(void *caller,AlgorithmItemRoot *item)
{
	AlgorithmItemPointerListContainer	*Items=(AlgorithmItemPointerListContainer *)caller;
	if(item->GetManualCreated()==false){
		return true;
	}
	return false;
}

void	RWCamRecognitionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddRWCamRecognitionItemPacket	*AddBItem=dynamic_cast<CmdAddRWCamRecognitionItemPacket *>(packet);
	if(AddBItem!=NULL){
		RWCamRecognitionItem	*item=tCreateItem(0);
		item->SetArea(AddBItem->Area);
		item->SetManualCreated(true);
		RWCamRecognitionThreshold	*WThr=item->GetThresholdW();		
		WThr->RepeatCount		=AddBItem->RepeatCount	;	
		WThr->MeshSize			=AddBItem->MeshSize		;
		WThr->SequenceOffset	=AddBItem->SequenceOffset	;
		WThr->GatherAllPhase	=AddBItem->GatherAllPhase	;
		AppendItem(item);
		return;		
	}
	CmdModifyRWCamRecognitionItemPacket	*ModItem=dynamic_cast<CmdModifyRWCamRecognitionItemPacket *>(packet);
	if(ModItem!=NULL){
		RWCamRecognitionItem	*item=tGetItemData(ModItem->ItemID);
		if(item!=NULL){
			RWCamRecognitionThreshold	*WThr=item->GetThresholdW();		
			WThr->RepeatCount		=ModItem->RepeatCount	;	
			WThr->MeshSize			=ModItem->MeshSize		;
			WThr->SequenceOffset	=ModItem->SequenceOffset	;
			WThr->GatherAllPhase	=ModItem->GatherAllPhase	;
			return;
		}
	}
	CmdReqRWCamRecognitionInfoList	*CmdReqRWCamRecognitionInfoListVar=dynamic_cast<CmdReqRWCamRecognitionInfoList *>(packet);
	if(CmdReqRWCamRecognitionInfoListVar!=NULL){
		for(RWCamRecognitionItem *a=tGetFirstData();a!=NULL;a=(RWCamRecognitionItem *)a->GetNext()) {
			RWCamRecognitionInfoList	*t=new RWCamRecognitionInfoList();
			t->Index.Data.Phase	=GetPhaseCode();
			t->Index.Data.Page	=GetPage();
			t->Index.Data.Layer	=0;
			t->Index.Data.ItemID=a->GetID();
			const	RWCamRecognitionThreshold	*RThr=a->GetThresholdR();
			t->RepeatCount		=RThr->RepeatCount		;	
			t->MeshSize			=RThr->MeshSize			;
			t->SequenceOffset	=RThr->SequenceOffset	;
			t->GatherAllPhase	=RThr->GatherAllPhase	;
			a->GetXY(t->x1,t->y1,t->x2,t->y2);
			CmdReqRWCamRecognitionInfoListVar->RWCamRecognitionInfos.AppendList(t);
		}
		return;
	}
	CmdCreateWholeRWCamRecognition	*CmdCreateWholeRWCamRecognitionVar=dynamic_cast<CmdCreateWholeRWCamRecognition *>(packet);
	if(CmdCreateWholeRWCamRecognitionVar!=NULL){
		AlgorithmItemPointerListContainer	Items;
		EnumItems(NULL,Items , Func);
		RemoveItems(Items);

		RWCamRecognitionItem	*item=tCreateItem(0);
		FlexArea	Area;
		Area.SetRectangle(0,0,GetDotPerLine(),GetMaxLines());
		item->SetArea(Area);
		item->SetManualCreated(false);
		RWCamRecognitionBase	*ABase=tGetParentBase();
		RWCamRecognitionThreshold	*WThr=item->GetThresholdW();		
		WThr->RepeatCount		=CmdCreateWholeRWCamRecognitionVar->RepeatCount	;	
		WThr->MeshSize			=ABase->WholeMeshSize		;
		WThr->SequenceOffset	=ABase->WholeSequenceOffset	;
		WThr->GatherAllPhase	=ABase->WholeGatherAllPhase	;
		AppendItem(item);
		return;		
	}
	CmdReqWholeRWCamRecognition	*CmdReqWholeRWCamRecognitionVar=dynamic_cast<CmdReqWholeRWCamRecognition *>(packet);
	if(CmdReqWholeRWCamRecognitionVar!=NULL){
		CmdReqWholeRWCamRecognitionVar->RepeatCount=0;
		for(RWCamRecognitionItem *a=tGetFirstData();a!=NULL;a=(RWCamRecognitionItem *)a->GetNext()){
			if(a->GetManualCreated()==false){
				const	RWCamRecognitionThreshold	*RThr=a->GetThresholdR();
				CmdReqWholeRWCamRecognitionVar->RepeatCount=RThr->RepeatCount;
				break;
			}
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
}

//===========================================================================================
RWCamRecognitionBase::RWCamRecognitionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorNormal			=Qt::darkGreen;
	ColorSelected		=Qt::green;
	ColorActive			=Qt::red;
	Color0				=Qt::green;
	Color1				=Qt::yellow;
	Color2				=Qt::darkRed;
	Color3				=Qt::cyan;
	Color4				=Qt::magenta;
	Color5				=Qt::darkGreen;
	Color6				=Qt::darkYellow;
	Color7				=Qt::darkCyan;

	SequenceBaseNo		=270;
	SequenceRegCount	=10;
	DefaultRepeatCount	=50;
	WholeMeshSize		=100;	
	WholeSequenceOffset	=0;
	WholeGatherAllPhase	=true;

	SetParam(&ColorNormal		, /**/"Color"	,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"		,"Color for Active Area");

	SetParam(&Color0			, /**/"Color"	,/**/"Color0"		,"Level Color 0");
	SetParam(&Color1			, /**/"Color"	,/**/"Color1"		,"Level Color 1");
	SetParam(&Color2			, /**/"Color"	,/**/"Color2"		,"Level Color 2");
	SetParam(&Color3			, /**/"Color"	,/**/"Color3"		,"Level Color 3");
	SetParam(&Color4			, /**/"Color"	,/**/"Color4"		,"Level Color 4");
	SetParam(&Color5			, /**/"Color"	,/**/"Color5"		,"Level Color 5");
	SetParam(&Color6			, /**/"Color"	,/**/"Color6"		,"Level Color 6");
	SetParam(&Color7			, /**/"Color"	,/**/"Color7"		,"Level Color 7");

	SetParam(&OperationAlgorithmData, /**/"Setting", /**/"OperationAlgorithmData"		
											 , "Operated Algorithm "		);
	SetParam(&DefaultRepeatCount, /**/"Setting"		,/**/"DefaultRepeatCount"	,"Default repeat count");
	SetParam(&SequenceBaseNo	, /**/"Sequence"	,/**/"SequenceBaseNo"		,"Sequence Base Number");
	SetParam(&SequenceRegCount	, /**/"Sequence"	,/**/"SequenceRegCount"		,"Sequence Register Count");

	SetParam(&WholeMeshSize			, /**/"Whole"	,/**/"WholeMeshSize"		,"Whole Mesh size");
	SetParam(&WholeSequenceOffset	, /**/"Whole"	,/**/"WholeSequenceOffset"	,"Whole SequenceOffset");
	SetParam(&WholeGatherAllPhase	, /**/"Whole"	,/**/"WholeGatherAllPhase"	,"Whole GatherAllPhase");

	OperationAlgorithmDim.Add(/**/"Basic",/**/"DotColorMatching");
}

AlgorithmDrawAttr	*RWCamRecognitionBase::CreateDrawAttr(void)
{
	return new RWCamRecognitionDrawAttr();
}

bool	RWCamRecognitionBase::SaveParam(QIODevice *f ,int EnableCondition)
{
	if(AlgorithmBase::SaveParam(f,EnableCondition)==false){
		return false;
	}
	if(OperationAlgorithmDim.Save(f)==false){
		return false;
	}
	return true;
}
bool	RWCamRecognitionBase::LoadParam(QIODevice *f ,int EnableCondition)
{
	if(AlgorithmBase::LoadParam(f,EnableCondition)==false){
		return false;
	}
	if(OperationAlgorithmDim.Load(f)==false){
		return false;
	}
	return true;
}
bool	RWCamRecognitionBase::LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition)
{
	if(AlgorithmBase::LoadParam(f,StartPoint,EndPoint,EnableCondition)==false){
		return false;
	}
	if(OperationAlgorithmDim.Load(f)==false){
		return false;
	}
	return true;
}

RWCamRecognitionInPage	*RWCamRecognitionBase::NewChild(AlgorithmBase *parent)
{	
	return(new RWCamRecognitionInPage(parent));
}
void	RWCamRecognitionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempRWCamRecognitionItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempRWCamRecognitionItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new RWCamRecognitionItem();
		return;
	}
	CmdCreateByteArrayFromRWCamRecognitionItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromRWCamRecognitionItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadRWCamRecognitionItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadRWCamRecognitionItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdRWCamRecognitionItemIDList	*CmdRWCamRecognitionItemIDListVar=dynamic_cast<CmdRWCamRecognitionItemIDList *>(packet);
	if(CmdRWCamRecognitionItemIDListVar!=NULL){
	}
}

bool	RWCamRecognitionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==RWCamRecognitionHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==RWCamRecognitionHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==RWCamRecognitionReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==RWCamRecognitionReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==RWCamRecognitionReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==RWCamRecognitionSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==RWCamRecognitionReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*RWCamRecognitionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==RWCamRecognitionReqThresholdReqCommand){
		return new RWCamRecognitionThresholdReq();
	}
	else if(Command==RWCamRecognitionReqThresholdSendCommand){
		RWCamRecognitionThresholdSend	*pSend=new RWCamRecognitionThresholdSend();
		if(reqData!=NULL){
			RWCamRecognitionThresholdReq	*req=(RWCamRecognitionThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	RWCamRecognitionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==RWCamRecognitionReqThresholdReqCommand){
		RWCamRecognitionThresholdReq	*p=(RWCamRecognitionThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==RWCamRecognitionReqThresholdSendCommand){
		RWCamRecognitionThresholdSend	*p=(RWCamRecognitionThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	RWCamRecognitionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==RWCamRecognitionReqThresholdReqCommand){
		RWCamRecognitionThresholdReq	*p=(RWCamRecognitionThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==RWCamRecognitionReqThresholdSendCommand){
		RWCamRecognitionThresholdSend	*p=(RWCamRecognitionThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	RWCamRecognitionBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==RWCamRecognitionReqThresholdReqCommand){
		RWCamRecognitionThresholdReq	*p=(RWCamRecognitionThresholdReq *)data;
		return true;
	}
	else if(Command==RWCamRecognitionReqThresholdSendCommand){
		RWCamRecognitionThresholdSend	*p=(RWCamRecognitionThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}
