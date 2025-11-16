/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RepeatControl\XRepeatControl.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRepeatControl.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "SelectAlgorithmListDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================

RepeatControlInPage::RepeatControlInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<RepeatControlItem,RepeatControlBase>(parent)
{
}
RepeatControlInPage::~RepeatControlInPage(void)
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

void	RepeatControlInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddRepeatControlItemPacket	*AddBItem=dynamic_cast<CmdAddRepeatControlItemPacket *>(packet);
	if(AddBItem!=NULL){
		RepeatControlItem	*item=tCreateItem(0);
		item->SetArea(AddBItem->Area);
		item->SetManualCreated(true);
		RepeatControlThreshold	*WThr=item->GetThresholdW();		
		WThr->RepeatCount		=AddBItem->RepeatCount	;	
		WThr->MeshSize			=AddBItem->MeshSize		;
		WThr->SequenceOffset	=AddBItem->SequenceOffset	;
		WThr->GatherAllPhase	=AddBItem->GatherAllPhase	;
		AppendItem(item);
		return;		
	}
	CmdModifyRepeatControlItemPacket	*ModItem=dynamic_cast<CmdModifyRepeatControlItemPacket *>(packet);
	if(ModItem!=NULL){
		RepeatControlItem	*item=tGetItemData(ModItem->ItemID);
		if(item!=NULL){
			RepeatControlThreshold	*WThr=item->GetThresholdW();		
			WThr->RepeatCount		=ModItem->RepeatCount	;	
			WThr->MeshSize			=ModItem->MeshSize		;
			WThr->SequenceOffset	=ModItem->SequenceOffset	;
			WThr->GatherAllPhase	=ModItem->GatherAllPhase	;
			return;
		}
	}
	CmdReqRepeatControlInfoList	*CmdReqRepeatControlInfoListVar=dynamic_cast<CmdReqRepeatControlInfoList *>(packet);
	if(CmdReqRepeatControlInfoListVar!=NULL){
		for(RepeatControlItem *a=tGetFirstData();a!=NULL;a=(RepeatControlItem *)a->GetNext()) {
			RepeatControlInfoList	*t=new RepeatControlInfoList();
			t->Index.Data.Phase	=GetPhaseCode();
			t->Index.Data.Page	=GetPage();
			t->Index.Data.Layer	=0;
			t->Index.Data.ItemID=a->GetID();
			const	RepeatControlThreshold	*RThr=a->GetThresholdR();
			t->RepeatCount		=RThr->RepeatCount		;	
			t->MeshSize			=RThr->MeshSize			;
			t->SequenceOffset	=RThr->SequenceOffset	;
			t->GatherAllPhase	=RThr->GatherAllPhase	;
			a->GetXY(t->x1,t->y1,t->x2,t->y2);
			CmdReqRepeatControlInfoListVar->RepeatControlInfos.AppendList(t);
		}
		return;
	}
	CmdCreateWholeRepeatControl	*CmdCreateWholeRepeatControlVar=dynamic_cast<CmdCreateWholeRepeatControl *>(packet);
	if(CmdCreateWholeRepeatControlVar!=NULL){
		AlgorithmItemPointerListContainer	Items;
		EnumItems(NULL,Items , Func);
		RemoveItems(Items);

		RepeatControlItem	*item=tCreateItem(0);
		FlexArea	Area;
		Area.SetRectangle(0,0,GetDotPerLine(),GetMaxLines());
		item->SetArea(Area);
		item->SetManualCreated(false);
		RepeatControlBase	*ABase=tGetParentBase();
		RepeatControlThreshold	*WThr=item->GetThresholdW();		
		WThr->RepeatCount		=CmdCreateWholeRepeatControlVar->RepeatCount	;	
		WThr->MeshSize			=ABase->WholeMeshSize		;
		WThr->SequenceOffset	=ABase->WholeSequenceOffset	;
		WThr->GatherAllPhase	=ABase->WholeGatherAllPhase	;
		AppendItem(item);
		return;		
	}
	CmdReqWholeRepeatControl	*CmdReqWholeRepeatControlVar=dynamic_cast<CmdReqWholeRepeatControl *>(packet);
	if(CmdReqWholeRepeatControlVar!=NULL){
		CmdReqWholeRepeatControlVar->RepeatCount=0;
		for(RepeatControlItem *a=tGetFirstData();a!=NULL;a=(RepeatControlItem *)a->GetNext()){
			if(a->GetManualCreated()==false){
				const	RepeatControlThreshold	*RThr=a->GetThresholdR();
				CmdReqWholeRepeatControlVar->RepeatCount=RThr->RepeatCount;
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
RepeatControlBase::RepeatControlBase(LayersBase *Base)
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

AlgorithmDrawAttr	*RepeatControlBase::CreateDrawAttr(void)
{
	return new RepeatControlDrawAttr();
}

bool	RepeatControlBase::SaveParam(QIODevice *f ,int EnableCondition)
{
	if(AlgorithmBase::SaveParam(f,EnableCondition)==false){
		return false;
	}
	if(OperationAlgorithmDim.Save(f)==false){
		return false;
	}
	return true;
}
bool	RepeatControlBase::LoadParam(QIODevice *f ,int EnableCondition)
{
	if(AlgorithmBase::LoadParam(f,EnableCondition)==false){
		return false;
	}
	if(OperationAlgorithmDim.Load(f)==false){
		return false;
	}
	return true;
}
bool	RepeatControlBase::LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition)
{
	if(AlgorithmBase::LoadParam(f,StartPoint,EndPoint,EnableCondition)==false){
		return false;
	}
	if(OperationAlgorithmDim.Load(f)==false){
		return false;
	}
	return true;
}
void	RepeatControlBase::ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	if(KeyName==/**/"OperationAlgorithmData"){
		SelectAlgorithmListDialog	D(GetLayersBase(),this);
		if(D.exec()==true){
			OperationAlgorithmDim=D.OperationAlgorithmDim;
		}
	}
}
RepeatControlInPage	*RepeatControlBase::NewChild(AlgorithmBase *parent)
{	
	return(new RepeatControlInPage(parent));
}
void	RepeatControlBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempRepeatControlItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempRepeatControlItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new RepeatControlItem();
		return;
	}
	CmdCreateByteArrayFromRepeatControlItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromRepeatControlItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadRepeatControlItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadRepeatControlItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdRepeatControlItemIDList	*CmdRepeatControlItemIDListVar=dynamic_cast<CmdRepeatControlItemIDList *>(packet);
	if(CmdRepeatControlItemIDListVar!=NULL){
	}
}

bool	RepeatControlBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==RepeatControlHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==RepeatControlHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==RepeatControlReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==RepeatControlReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==RepeatControlReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==RepeatControlSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==RepeatControlReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*RepeatControlBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==RepeatControlReqThresholdReqCommand){
		return new RepeatControlThresholdReq();
	}
	else if(Command==RepeatControlReqThresholdSendCommand){
		RepeatControlThresholdSend	*pSend=new RepeatControlThresholdSend();
		if(reqData!=NULL){
			RepeatControlThresholdReq	*req=(RepeatControlThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	RepeatControlBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==RepeatControlReqThresholdReqCommand){
		RepeatControlThresholdReq	*p=(RepeatControlThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==RepeatControlReqThresholdSendCommand){
		RepeatControlThresholdSend	*p=(RepeatControlThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	RepeatControlBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==RepeatControlReqThresholdReqCommand){
		RepeatControlThresholdReq	*p=(RepeatControlThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==RepeatControlReqThresholdSendCommand){
		RepeatControlThresholdSend	*p=(RepeatControlThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	RepeatControlBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==RepeatControlReqThresholdReqCommand){
		RepeatControlThresholdReq	*p=(RepeatControlThresholdReq *)data;
		return true;
	}
	else if(Command==RepeatControlReqThresholdSendCommand){
		RepeatControlThresholdSend	*p=(RepeatControlThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}
