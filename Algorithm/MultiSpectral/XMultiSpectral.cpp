/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMultiSpectral.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XMultiSpectral.h"
#include "XMultiSpectralLibrary.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "omp.h"

//===========================================

void	MultiSpectralInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMultiSpectralAreaPacket	*AddMArea=dynamic_cast<AddMultiSpectralAreaPacket *>(packet);
	if(AddMArea!=NULL){
		MultiSpectralItem	*MData=(MultiSpectralItem	*)CreateItem();
		MData->SetArea(AddMArea->Area);
		//MData->GetThresholdW()->SelAreaID	=AddMArea->LimitedLib;
		MData->SetManualCreated(true);
		AppendItem(MData);
	}
}

void	MultiSpectralInPage::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		MultiSpectralItem	*BI=(MultiSpectralItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

//===========================================
MultiSpectralBase::MultiSpectralBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
}

AlgorithmDrawAttr	*MultiSpectralBase::CreateDrawAttr(void)
{
	return new MultiSpectralDrawAttr();
}

void	MultiSpectralBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetMultiSpectralLibraryListPacket	*AListPacket=dynamic_cast<CmdGetMultiSpectralLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetMultiSpectralLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetMultiSpectralLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertMultiSpectralLibraryPacket	*BInsLib=dynamic_cast<CmdInsertMultiSpectralLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(MultiSpectralVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateMultiSpectralLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateMultiSpectralLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(MultiSpectralVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadMultiSpectralLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadMultiSpectralLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempMultiSpectralLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempMultiSpectralLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearMultiSpectralLibraryPacket	*CmdClearMultiSpectralLibraryPacketVar=dynamic_cast<CmdClearMultiSpectralLibraryPacket *>(packet);
	if(CmdClearMultiSpectralLibraryPacketVar!=NULL){
		CmdClearMultiSpectralLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteMultiSpectralLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteMultiSpectralLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempMultiSpectralItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempMultiSpectralItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new MultiSpectralItem();
		return;
	}
	CmdCreateByteArrayFromMultiSpectralItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromMultiSpectralItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadMultiSpectralItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadMultiSpectralItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
}


bool	MultiSpectralBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==MultiSpectralHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==MultiSpectralHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==MultiSpectralReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==MultiSpectralReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==MultiSpectralReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==MultiSpectralSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==MultiSpectralReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*MultiSpectralBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==MultiSpectralReqThresholdReqCommand){
		return new MultiSpectralThresholdReq();
	}
	else if(Command==MultiSpectralReqThresholdSendCommand){
		MultiSpectralThresholdSend	*pSend=new MultiSpectralThresholdSend();
		if(reqData!=NULL){
			MultiSpectralThresholdReq	*req=(MultiSpectralThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==MultiSpectralReqTryThresholdCommand){
		return new MultiSpectralReqTryThreshold();
	}
	else if(Command==MultiSpectralSendTryThresholdCommand){
		MultiSpectralSendTryThreshold	*pSend=new MultiSpectralSendTryThreshold();
		if(reqData!=NULL){
			MultiSpectralReqTryThreshold	*req=(MultiSpectralReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	MultiSpectralBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==MultiSpectralReqThresholdReqCommand){
		MultiSpectralThresholdReq	*p=(MultiSpectralThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==MultiSpectralReqThresholdSendCommand){
		MultiSpectralThresholdSend	*p=(MultiSpectralThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==MultiSpectralReqTryThresholdCommand){
		MultiSpectralReqTryThreshold	*p=(MultiSpectralReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==MultiSpectralSendTryThresholdCommand){
		MultiSpectralSendTryThreshold	*p=(MultiSpectralSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	MultiSpectralBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==MultiSpectralReqThresholdReqCommand){
		MultiSpectralThresholdReq	*p=(MultiSpectralThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==MultiSpectralReqThresholdSendCommand){
		MultiSpectralThresholdSend	*p=(MultiSpectralThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==MultiSpectralReqTryThresholdCommand){
		MultiSpectralReqTryThreshold	*p=(MultiSpectralReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==MultiSpectralSendTryThresholdCommand){
		MultiSpectralSendTryThreshold	*p=(MultiSpectralSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	MultiSpectralBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==MultiSpectralReqThresholdReqCommand){
		MultiSpectralThresholdReq	*p=(MultiSpectralThresholdReq *)data;
		return true;
	}
	else if(Command==MultiSpectralReqThresholdSendCommand){
		MultiSpectralThresholdSend	*p=(MultiSpectralThresholdSend *)data;
		return true;
	}
	else if(Command==MultiSpectralReqTryThresholdCommand){
		MultiSpectralReqTryThreshold	*p=(MultiSpectralReqTryThreshold *)data;
		return true;
	}
	else if(Command==MultiSpectralSendTryThresholdCommand){
		MultiSpectralSendTryThreshold	*p=(MultiSpectralSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}
