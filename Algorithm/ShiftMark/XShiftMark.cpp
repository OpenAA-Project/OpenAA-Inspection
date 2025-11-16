//#include "ShiftMarkResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ShiftMark\XShiftMark.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XShiftMark.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XShiftMarkLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XShiftMarkAlgoPacket.h"
#include "XDisplaySimPanel.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================
ShiftMarkInPage::ShiftMarkInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<ShiftMarkItem,ShiftMarkBase>(parent)
{
}
ShiftMarkInPage::~ShiftMarkInPage(void)	
{
}

void	ShiftMarkInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdAddShiftMarkItemPacket	*AddItemP=dynamic_cast<CmdAddShiftMarkItemPacket *>(packet);
	//if(AddItemP!=NULL){
	//	IntList AdaptedPickLayers;
	//	IntList AdaptedGenLayers;
	//	GetLibraryContainer()->GetLayers(AddItemP->LibID,AdaptedPickLayers ,AdaptedGenLayers);
	//	for(IntClass *c=AdaptedGenLayers.GetFirst();c!=NULL;c=c->GetNext()){
	//		int	Layer=c->GetValue();
	//		GetLayerData(Layer)->TransmitDirectly(packet);
	//	}
	//	return;
	//}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
	//CmdShiftMarkReqItemResult	*CmdShiftMarkReqItemResultVar=dynamic_cast<CmdShiftMarkReqItemResult *>(packet);
	//if(CmdShiftMarkReqItemResultVar!=NULL){
	//	GetLayerData(CmdShiftMarkReqItemResultVar->Layer)->TransmitDirectly(packet);
	//	return;
	//}
	MakeShiftMarkListPacket	*MakeShiftMarkListPacketVar=dynamic_cast<MakeShiftMarkListPacket *>(packet);
	if(MakeShiftMarkListPacketVar!=NULL){
		ShiftMarkListForPacketPackForPhase *Ph=NULL;
		for(Ph=MakeShiftMarkListPacketVar->ListInfo->GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			if(Ph->Phase==GetPhaseCode()){
				break;
			}
		}
		if(Ph==NULL){
			Ph=new ShiftMarkListForPacketPackForPhase();
			Ph->Phase=GetPhaseCode();
			MakeShiftMarkListPacketVar->ListInfo->AppendList(Ph);
		}
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			ShiftMarkItem	*ai=dynamic_cast<ShiftMarkItem *>(a);
			if(ai!=NULL){
				ShiftMarkListForPacket	*d=new ShiftMarkListForPacket();
				d->ItemID	=ai->GetID();
				d->ItemName	=ai->GetItemName();
				d->LibID	=ai->GetLibID();
				d->Page		=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				if(ai->GetXY(d->x1 ,d->y1 ,d->x2 ,d->y2)==true){
					d->SearchDotEdge=ai->GetThresholdR(GetLayersBase())->SearchDotEdge;
					Ph->AppendList(d);
				}
			}
		}
		return;
	}
	CmdAddByteShiftMarkItemPacket	*AddBItem=dynamic_cast<CmdAddByteShiftMarkItemPacket *>(packet);
	if(AddBItem!=NULL){
		QBuffer	MBuff(&AddBItem->Buff);
		MBuff.open(QIODevice::ReadWrite);

		ShiftMarkItem	*Item	=(ShiftMarkItem *)CreateItem(0);
		Item->Load(&MBuff,GetLayersBase());
		if(AddBItem->Vector!=NULL){
			Item->SetVector(*AddBItem->Vector);
		}
		Item->SetManualCreated(true);
		Item->SetLibID(AddBItem->SelectedLibID);
		Item->SetItemName(AddBItem->ItemName);

		ShiftMarkBase	*BBase=(ShiftMarkBase *)GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->SelectedLibID,LLib)==true){
			ShiftMarkLibrary	*ALib=dynamic_cast<ShiftMarkLibrary *>(LLib.GetLibrary());
			if(ALib!=NULL){
				((ShiftMarkItem *)Item)->CopyThresholdFromLibrary(&LLib);
			}
		}
		Item->SetManualCreated(true);
		GetParentBase()->ClearManagedCacheLib();

		AppendItem(Item);

		return;
	}
	CmdSendAddEdgeMark	*CmdSendAddEdgeMarkVar=dynamic_cast<CmdSendAddEdgeMark *>(packet);
	if(CmdSendAddEdgeMarkVar!=NULL){
		ShiftMarkItem	*Item=tGetItemData(CmdSendAddEdgeMarkVar->ItemID);
		if(Item!=NULL){
			if(CmdSendAddEdgeMarkVar->ModeAddEdge==true){
				Item->EdgePoint=CmdSendAddEdgeMarkVar->Area;
			}
			else
			if(CmdSendAddEdgeMarkVar->ModeAddMark==true){
				Item->MarkPoint=CmdSendAddEdgeMarkVar->Area;
			}
		}
		return;
	}
}

bool	ShiftMarkInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		//SlaveCommReqLibraryInMaskOfShiftMark	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		//SlaveCommAckLibraryInMaskOfShiftMark	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		//RCmd.UsedLibraries.Add(LibID);
		//if(RCmd.Send(globalpage,0,ACmd)==true){
		//	if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
		//		LimitedMaskInOtherPage=true;
		//	}
		//}
	}
	return LimitedMaskInOtherPage;
}

void	ShiftMarkInPage::UndoSetIndependentShiftMarkItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		ShiftMarkItem	*BI=(ShiftMarkItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

//===========================================================================================
ShiftMarkBase::ShiftMarkBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit=false;

	ColorShiftMarkNormal	=Qt::darkGreen;
	ColorShiftMarkSelected	=Qt::green;
	ColorShiftMarkActive	=Qt::red;
	OmitZoneDot				=100;
	MaxRotationDegree		=15;
	DiffColorH				=10;

	SetParam(&ColorShiftMarkNormal	, /**/"Color" ,/**/"ColorShiftMarkNormal"		,"Color for Area");
	SetParam(&ColorShiftMarkSelected, /**/"Color" ,/**/"ColorShiftMarkSelected"		,"Color for Selected Area");
	SetParam(&ColorShiftMarkActive	, /**/"Color" ,/**/"ColorShiftMarkActive"		,"Color for Active Area");

	SetParam(&OmitZoneDot			, /**/"Setting"		,/**/"OmitZoneDot"			,"Omit zone dot in area generation");
	SetParam(&MaxRotationDegree		, /**/"Setting"		,/**/"MaxRotationDegree"	,"Max rotation (Degree)");
	SetParam(&DiffColorH			, /**/"Setting"		,/**/"DiffColorH"			,"Differential ColorH (0-180)");
}

ShiftMarkBase::~ShiftMarkBase(void)
{
}
AlgorithmDrawAttr	*ShiftMarkBase::CreateDrawAttr(void)
{
	return new ShiftMarkDrawAttr();
}

void	ShiftMarkBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetShiftMarkLibraryListPacket	*AListPacket=dynamic_cast<CmdGetShiftMarkLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetShiftMarkLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetShiftMarkLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertShiftMarkLibraryPacket	*BInsLib=dynamic_cast<CmdInsertShiftMarkLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(ShiftMarkVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateShiftMarkLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateShiftMarkLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(ShiftMarkVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadShiftMarkLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadShiftMarkLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempShiftMarkLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempShiftMarkLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearShiftMarkLibraryPacket	*CmdClearShiftMarkLibraryPacketVar=dynamic_cast<CmdClearShiftMarkLibraryPacket *>(packet);
	if(CmdClearShiftMarkLibraryPacketVar!=NULL){
		CmdClearShiftMarkLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteShiftMarkLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteShiftMarkLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempShiftMarkItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempShiftMarkItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new ShiftMarkItem();
		return;
	}
	CmdCreateByteArrayFromShiftMarkItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromShiftMarkItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadShiftMarkItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadShiftMarkItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
}

bool	ShiftMarkBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==ShiftMarkHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ShiftMarkHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ShiftMarkReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ShiftMarkReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ShiftMarkReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ShiftMarkSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ShiftMarkReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*ShiftMarkBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==ShiftMarkReqThresholdReqCommand){
		return new ShiftMarkThresholdReq();
	}
	else if(Command==ShiftMarkReqThresholdSendCommand){
		ShiftMarkThresholdSend	*pSend=new ShiftMarkThresholdSend();
		if(reqData!=NULL){
			ShiftMarkThresholdReq	*req=(ShiftMarkThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ShiftMarkReqTryThresholdCommand){
		return new ShiftMarkReqTryThreshold();
	}
	else if(Command==ShiftMarkSendTryThresholdCommand){
		ShiftMarkSendTryThreshold	*pSend=new ShiftMarkSendTryThreshold();
		if(reqData!=NULL){
			ShiftMarkReqTryThreshold	*req=(ShiftMarkReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	ShiftMarkBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==ShiftMarkReqThresholdReqCommand){
		ShiftMarkThresholdReq	*p=(ShiftMarkThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==ShiftMarkReqThresholdSendCommand){
		ShiftMarkThresholdSend	*p=(ShiftMarkThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==ShiftMarkReqTryThresholdCommand){
		ShiftMarkReqTryThreshold	*p=(ShiftMarkReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==ShiftMarkSendTryThresholdCommand){
		ShiftMarkSendTryThreshold	*p=(ShiftMarkSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	ShiftMarkBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==ShiftMarkReqThresholdReqCommand){
		ShiftMarkThresholdReq	*p=(ShiftMarkThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==ShiftMarkReqThresholdSendCommand){
		ShiftMarkThresholdSend	*p=(ShiftMarkThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==ShiftMarkReqTryThresholdCommand){
		ShiftMarkReqTryThreshold	*p=(ShiftMarkReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==ShiftMarkSendTryThresholdCommand){
		ShiftMarkSendTryThreshold	*p=(ShiftMarkSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	ShiftMarkBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==ShiftMarkReqThresholdReqCommand){
		ShiftMarkThresholdReq	*p=(ShiftMarkThresholdReq *)data;
		return true;
	}
	else if(Command==ShiftMarkReqThresholdSendCommand){
		ShiftMarkThresholdSend	*p=(ShiftMarkThresholdSend *)data;
		return true;
	}
	else if(Command==ShiftMarkReqTryThresholdCommand){
		ShiftMarkReqTryThreshold	*p=(ShiftMarkReqTryThreshold *)data;
		return true;
	}
	else if(Command==ShiftMarkSendTryThresholdCommand){
		ShiftMarkSendTryThreshold	*p=(ShiftMarkSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}

ExeResult	ShiftMarkBase::ExecuteInitialAfterEdit(int ExeID 
											,ResultBaseForAlgorithmRoot *Res
											,ExecuteInitialAfterEditInfo &EInfo)
{
	return AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}

QString	ShiftMarkBase::GetNameByCurrentLanguage(void)
{
	return "見当マーク検査";
}

