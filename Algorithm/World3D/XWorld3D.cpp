/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\World3D\XWorld3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XWorld3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
//#include "XWorld3DLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================


World3DInPage::World3DInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<World3DItem,World3DBase>(parent)
{
}
World3DInPage::~World3DInPage(void)
{
}
AlgorithmItemRoot	*World3DInPage::CreateItem(int ItemClassType)
{
	return new World3DItem();
}

void	World3DInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddWorld3DItemPacket	*AddBItem=dynamic_cast<CmdAddWorld3DItemPacket *>(packet);
	if(AddBItem!=NULL){
		//World3DItem	*Item=tCreateItem(0);
		//Item->SetArea(AddBItem->Area);
		//Item->SetLibID(AddBItem->LibID);
		//World3DBase	*BBase=tGetParentBase();
		//AlgorithmLibraryLevelContainer	LLib(BBase);
		//if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
		//	Item->CopyThresholdFromLibrary(&LLib);
		//	if(AppendItem(Item)==true){
		//		ImageBuffer *TargetImageList[100];
		//		GetTargetBuffList(TargetImageList);
		//		Item->ItemArea.Set(AddBItem->Area,*TargetImageList[0]);
		//		int	Dx=Item->ItemArea.GetMinX();
		//		int	Dy=Item->ItemArea.GetMinY();
		//		Item->ItemArea.MoveToNoClip(-Dx,-Dy);
		//		ExecuteInitialAfterEditInfo EInfo;
		//		Item->ExecuteInitialAfterEdit(0,0,NULL,EInfo);
		//	}
		//	else{
		//		delete	Item;
		//	}
		//}

		return;
	}
	CmdLoadStepFile	*CmdLoadStepFileVar=dynamic_cast<CmdLoadStepFile *>(packet);
	if(CmdLoadStepFileVar!=NULL){
		World3DItem	*Item=new World3DItem();
		QBuffer	Buff(&CmdLoadStepFileVar->FArray);
		Buff.open(QIODevice::ReadWrite);
		if(Item->StepData.LoadStepFile(&Buff)==true){
			Item->SetParent(this);
			AppendItem(Item);
		}
		return;
	}
}

void	World3DInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	World3DDrawAttr	*BAttr=dynamic_cast<World3DDrawAttr *>(Attr);
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
}

ExeResult	World3DInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePITemplate<World3DItem,World3DBase>::ExecuteStartByInspection(ExeID ,Res);
}
ExeResult	World3DInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	return AlgorithmInPagePITemplate<World3DItem,World3DBase>::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
ExeResult	World3DInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePITemplate<World3DItem,World3DBase>::ExecuteProcessing(ExeID ,Res);

	return Ret;
}


//===========================================================================================
World3DBase::World3DBase(LayersBase *Base)
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

AlgorithmDrawAttr	*World3DBase::CreateDrawAttr(void)
{
	return new World3DDrawAttr(GetLayersBase());
}

void	World3DBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetWorld3DLibraryListPacket	*AListPacket=dynamic_cast<CmdGetWorld3DLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetWorld3DLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetWorld3DLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertWorld3DLibraryPacket	*BInsLib=dynamic_cast<CmdInsertWorld3DLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(World3DVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateWorld3DLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateWorld3DLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(World3DVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadWorld3DLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadWorld3DLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempWorld3DLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempWorld3DLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearWorld3DLibraryPacket	*CmdClearWorld3DLibraryPacketVar=dynamic_cast<CmdClearWorld3DLibraryPacket *>(packet);
	if(CmdClearWorld3DLibraryPacketVar!=NULL){
		CmdClearWorld3DLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteWorld3DLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteWorld3DLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempWorld3DItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempWorld3DItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new World3DItem();
		return;
	}
	CmdCreateByteArrayFromWorld3DItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromWorld3DItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadWorld3DItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadWorld3DItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
}

bool	World3DBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==World3DHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==World3DHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==World3DReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==World3DReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==World3DReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==World3DSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==World3DReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*World3DBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	//if(Command==World3DReqThresholdReqCommand){
	//	return new World3DThresholdReq();
	//}
	//else if(Command==World3DReqThresholdSendCommand){
	//	World3DThresholdSend	*pSend=new World3DThresholdSend();
	//	if(reqData!=NULL){
	//		World3DThresholdReq	*req=(World3DThresholdReq *)reqData;
	//		pSend->ConstructList(req,this);
	//	}
	//	return pSend;
	//}
	//else if(Command==World3DReqTryThresholdCommand){
	//	return new World3DReqTryThreshold();
	//}
	//else if(Command==World3DSendTryThresholdCommand){
	//	World3DSendTryThreshold	*pSend=new World3DSendTryThreshold();
	//	if(reqData!=NULL){
	//		World3DReqTryThreshold	*req=(World3DReqTryThreshold *)reqData;
	//		pSend->ConstructList(req,this);
	//	}
	//	return pSend;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataCreate(Command,reqData);
	//}

	return NULL;
}
bool	World3DBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	//if(Command==World3DReqThresholdReqCommand){
	//	World3DThresholdReq	*p=(World3DThresholdReq *)data;
	//	return p->Load(f);
	//}
	//else if(Command==World3DReqThresholdSendCommand){
	//	World3DThresholdSend	*p=(World3DThresholdSend *)data;
	//	return p->Load(f);
	//}
	//else if(Command==World3DReqTryThresholdCommand){
	//	World3DReqTryThreshold	*p=(World3DReqTryThreshold *)data;
	//	return p->Load(f,GetLayersBase());
	//}
	//else if(Command==World3DSendTryThresholdCommand){
	//	World3DSendTryThreshold	*p=(World3DSendTryThreshold *)data;
	//	return p->Load(f);
	//}
	//else{
	//	return AlgorithmBase::GeneralDataLoad(f,Command,data);
	//}
	return false;
}
bool	World3DBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	//if(Command==World3DReqThresholdReqCommand){
	//	World3DThresholdReq	*p=(World3DThresholdReq *)data;
	//	return p->Save(f);
	//}
	//else if(Command==World3DReqThresholdSendCommand){
	//	World3DThresholdSend	*p=(World3DThresholdSend *)data;
	//	return p->Save(f);
	//}
	//else if(Command==World3DReqTryThresholdCommand){
	//	World3DReqTryThreshold	*p=(World3DReqTryThreshold *)data;
	//	return p->Save(f);
	//}
	//else if(Command==World3DSendTryThresholdCommand){
	//	World3DSendTryThreshold	*p=(World3DSendTryThreshold *)data;
	//	return p->Save(f);
	//}
	//else{
	//	return AlgorithmBase::GeneralDataSave(f,Command,data);
	//}

	return false;
}
bool	World3DBase::GeneralDataReply(int32 Command,void *data)
{
	//if(Command==World3DReqThresholdReqCommand){
	//	World3DThresholdReq	*p=(World3DThresholdReq *)data;
	//	return true;
	//}
	//else if(Command==World3DReqThresholdSendCommand){
	//	World3DThresholdSend	*p=(World3DThresholdSend *)data;
	//	return true;
	//}
	//else if(Command==World3DReqTryThresholdCommand){
	//	World3DReqTryThreshold	*p=(World3DReqTryThreshold *)data;
	//	return true;
	//}
	//else if(Command==World3DSendTryThresholdCommand){
	//	World3DSendTryThreshold	*p=(World3DSendTryThreshold *)data;
	//	return true;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataReply(Command,data);
	//}

	return false;
}
