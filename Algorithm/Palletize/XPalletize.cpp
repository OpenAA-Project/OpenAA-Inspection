/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Palletize\XPalletize.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPalletize.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XPalletizeLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================


PalletizeInPage::PalletizeInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<PalletizeItem,PalletizeBase>(parent)
{
}
PalletizeInPage::~PalletizeInPage(void)
{
}
AlgorithmItemRoot	*PalletizeInPage::CreateItem(int ItemClassType)
{
	return new PalletizeItem();
}

void	PalletizeInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddPalletizeItemPacket	*AddBItem=dynamic_cast<CmdAddPalletizeItemPacket *>(packet);
	if(AddBItem!=NULL){
		PalletizeItem	*Item=tCreateItem(0);
		Item->SetArea(AddBItem->Area);
		Item->SetLibID(AddBItem->LibID);
		PalletizeBase	*BBase=tGetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
			Item->CopyThresholdFromLibrary(&LLib);
			if(AppendItem(Item)==true){
				ImageBuffer *TargetImageList[100];
				GetTargetBuffList(TargetImageList);
				Item->ItemArea.Set(AddBItem->Area,*TargetImageList[0]);
				int	Dx=Item->ItemArea.GetMinX();
				int	Dy=Item->ItemArea.GetMinY();
				Item->ItemArea.MoveToNoClip(-Dx,-Dy);
				ExecuteInitialAfterEditInfo EInfo;
				Item->ExecuteInitialAfterEdit(0,0,NULL,EInfo);
			}
			else{
				delete	Item;
			}
		}

		return;
	}

	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		//GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
}

void	PalletizeInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	PalletizeDrawAttr	*BAttr=dynamic_cast<PalletizeDrawAttr *>(Attr);
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);

	QColor Col(255,255,0,196);
}

ExeResult	PalletizeInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePITemplate<PalletizeItem,PalletizeBase>::ExecuteStartByInspection(ExeID ,Res);
}
ExeResult	PalletizeInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	return AlgorithmInPagePITemplate<PalletizeItem,PalletizeBase>::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
ExeResult	PalletizeInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePITemplate<PalletizeItem,PalletizeBase>::ExecuteProcessing(ExeID ,Res);

	return Ret;
}


//===========================================================================================
PalletizeBase::PalletizeBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorArea		=Qt::darkGreen;
	ColorSelected	=Qt::green;
	ColorActive		=Qt::red;
	PickupLineVar	=20;
	AffinParam[0]	=1;
	AffinParam[1]	=0;
	AffinParam[2]	=0;
	AffinParam[3]	=0;
	AffinParam[4]	=1;
	AffinParam[5]	=0;
	MinAvrage		=45;

	SetParam(&ColorArea			, /**/"Color"		,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"		,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"		,/**/"ColorActive"		,"Color for Active Area");

	SetParam(&PickupLineVar		, /**/"Threshold"	,/**/"PickupLineVar"	,"Pickup Line Var");
	SetParam(&MinAvrage			, /**/"Threshold"	,/**/"MinAvrage"		,"Average of background threshold");

	SetParam(&AffinParam[0]		, /**/"AffinParam"	,/**/"AffinParam0"	,"AffinParam 0");
	SetParam(&AffinParam[1]		, /**/"AffinParam"	,/**/"AffinParam1"	,"AffinParam 1");
	SetParam(&AffinParam[2]		, /**/"AffinParam"	,/**/"AffinParam2"	,"AffinParam 2");
	SetParam(&AffinParam[3]		, /**/"AffinParam"	,/**/"AffinParam3"	,"AffinParam 3");
	SetParam(&AffinParam[4]		, /**/"AffinParam"	,/**/"AffinParam4"	,"AffinParam 4");
	SetParam(&AffinParam[5]		, /**/"AffinParam"	,/**/"AffinParam5"	,"AffinParam 5");
}

AlgorithmDrawAttr	*PalletizeBase::CreateDrawAttr(void)
{
	return new PalletizeDrawAttr(GetLayersBase());
}

void	PalletizeBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetPalletizeLibraryListPacket	*AListPacket=dynamic_cast<CmdGetPalletizeLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetPalletizeLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetPalletizeLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertPalletizeLibraryPacket	*BInsLib=dynamic_cast<CmdInsertPalletizeLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(PalletizeVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdatePalletizeLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdatePalletizeLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(PalletizeVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadPalletizeLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadPalletizeLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempPalletizeLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempPalletizeLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearPalletizeLibraryPacket	*CmdClearPalletizeLibraryPacketVar=dynamic_cast<CmdClearPalletizeLibraryPacket *>(packet);
	if(CmdClearPalletizeLibraryPacketVar!=NULL){
		CmdClearPalletizeLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeletePalletizeLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeletePalletizeLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempPalletizeItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempPalletizeItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new PalletizeItem();
		return;
	}
	CmdCreateByteArrayFromPalletizeItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromPalletizeItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadPalletizeItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadPalletizeItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
}

bool	PalletizeBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==PalletizeHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==PalletizeHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==PalletizeReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==PalletizeReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==PalletizeReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==PalletizeSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==PalletizeReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*PalletizeBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	//if(Command==PalletizeReqThresholdReqCommand){
	//	return new PalletizeThresholdReq();
	//}
	//else if(Command==PalletizeReqThresholdSendCommand){
	//	PalletizeThresholdSend	*pSend=new PalletizeThresholdSend();
	//	if(reqData!=NULL){
	//		PalletizeThresholdReq	*req=(PalletizeThresholdReq *)reqData;
	//		pSend->ConstructList(req,this);
	//	}
	//	return pSend;
	//}
	//else if(Command==PalletizeReqTryThresholdCommand){
	//	return new PalletizeReqTryThreshold();
	//}
	//else if(Command==PalletizeSendTryThresholdCommand){
	//	PalletizeSendTryThreshold	*pSend=new PalletizeSendTryThreshold();
	//	if(reqData!=NULL){
	//		PalletizeReqTryThreshold	*req=(PalletizeReqTryThreshold *)reqData;
	//		pSend->ConstructList(req,this);
	//	}
	//	return pSend;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataCreate(Command,reqData);
	//}

	return NULL;
}
bool	PalletizeBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	//if(Command==PalletizeReqThresholdReqCommand){
	//	PalletizeThresholdReq	*p=(PalletizeThresholdReq *)data;
	//	return p->Load(f);
	//}
	//else if(Command==PalletizeReqThresholdSendCommand){
	//	PalletizeThresholdSend	*p=(PalletizeThresholdSend *)data;
	//	return p->Load(f);
	//}
	//else if(Command==PalletizeReqTryThresholdCommand){
	//	PalletizeReqTryThreshold	*p=(PalletizeReqTryThreshold *)data;
	//	return p->Load(f,GetLayersBase());
	//}
	//else if(Command==PalletizeSendTryThresholdCommand){
	//	PalletizeSendTryThreshold	*p=(PalletizeSendTryThreshold *)data;
	//	return p->Load(f);
	//}
	//else{
	//	return AlgorithmBase::GeneralDataLoad(f,Command,data);
	//}
	return false;
}
bool	PalletizeBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	//if(Command==PalletizeReqThresholdReqCommand){
	//	PalletizeThresholdReq	*p=(PalletizeThresholdReq *)data;
	//	return p->Save(f);
	//}
	//else if(Command==PalletizeReqThresholdSendCommand){
	//	PalletizeThresholdSend	*p=(PalletizeThresholdSend *)data;
	//	return p->Save(f);
	//}
	//else if(Command==PalletizeReqTryThresholdCommand){
	//	PalletizeReqTryThreshold	*p=(PalletizeReqTryThreshold *)data;
	//	return p->Save(f);
	//}
	//else if(Command==PalletizeSendTryThresholdCommand){
	//	PalletizeSendTryThreshold	*p=(PalletizeSendTryThreshold *)data;
	//	return p->Save(f);
	//}
	//else{
	//	return AlgorithmBase::GeneralDataSave(f,Command,data);
	//}

	return false;
}
bool	PalletizeBase::GeneralDataReply(int32 Command,void *data)
{
	//if(Command==PalletizeReqThresholdReqCommand){
	//	PalletizeThresholdReq	*p=(PalletizeThresholdReq *)data;
	//	return true;
	//}
	//else if(Command==PalletizeReqThresholdSendCommand){
	//	PalletizeThresholdSend	*p=(PalletizeThresholdSend *)data;
	//	return true;
	//}
	//else if(Command==PalletizeReqTryThresholdCommand){
	//	PalletizeReqTryThreshold	*p=(PalletizeReqTryThreshold *)data;
	//	return true;
	//}
	//else if(Command==PalletizeSendTryThresholdCommand){
	//	PalletizeSendTryThreshold	*p=(PalletizeSendTryThreshold *)data;
	//	return true;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataReply(Command,data);
	//}

	return false;
}
