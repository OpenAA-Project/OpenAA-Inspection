/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Process3D\XProcess3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "Process3DResource.h"
#include "XProcess3D.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XProcess3DLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
//#include "XPropertyProcess3DPacket.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================
Process3DThreshold::Process3DThreshold(Process3DItem *parent)
:AlgorithmThreshold(parent)
{
	BaseCycleDot	=100;
	HeightPerShift	=1;
	VFilterLength	=5;
	LargeTilt		=10;
	LargeFlatness	=10;
	SmallFlatness	=10;
	SmallAreaSize	=100;
}


void	Process3DThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const Process3DThreshold *s=(const Process3DThreshold *)&src;
	BaseCycleDot	=s->BaseCycleDot	;
	HeightPerShift	=s->HeightPerShift;	
	VFilterLength	=s->VFilterLength;	
	LargeTilt		=s->LargeTilt	;	
	LargeFlatness	=s->LargeFlatness;	
	SmallFlatness	=s->SmallFlatness;	
	SmallAreaSize	=s->SmallAreaSize;	
}
bool	Process3DThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const Process3DThreshold *s=(const Process3DThreshold *)&src;
	if(BaseCycleDot		!=s->BaseCycleDot	)	return false;
	if(HeightPerShift	!=s->HeightPerShift	)	return false;	
	if(VFilterLength	!=s->VFilterLength	)	return false;	
	if(LargeTilt		!=s->LargeTilt		)	return false;	
	if(LargeFlatness	!=s->LargeFlatness	)	return false;	
	if(SmallFlatness	!=s->SmallFlatness	)	return false;	
	if(SmallAreaSize	!=s->SmallAreaSize	)	return false;
	return true;
}
bool	Process3DThreshold::Save(QIODevice *f)
{
	WORD	Ver=Process3DVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,BaseCycleDot)==false)
		return false;
	if(::Save(f,HeightPerShift)==false)
		return false;
	if(::Save(f,VFilterLength)==false)
		return false;
	if(::Save(f,LargeTilt)==false)
		return false;
	if(::Save(f,LargeFlatness)==false)
		return false;
	if(::Save(f,SmallFlatness)==false)
		return false;
	if(::Save(f,SmallAreaSize)==false)
		return false;

	return true;
}

bool	Process3DThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,BaseCycleDot)==false)
		return false;
	if(::Load(f,HeightPerShift)==false)
		return false;
	if(::Load(f,VFilterLength)==false)
		return false;
	if(::Load(f,LargeTilt)==false)
		return false;
	if(::Load(f,LargeFlatness)==false)
		return false;
	if(::Load(f,SmallFlatness)==false)
		return false;
	if(::Load(f,SmallAreaSize)==false)
		return false;
	return true;
}

void	Process3DThreshold::FromLibrary(AlgorithmLibrary *src)
{
	Process3DLibrary	*LSrc=dynamic_cast<Process3DLibrary *>(src);
	if(LSrc==NULL)
		return;

	BaseCycleDot	=LSrc->BaseCycleDot	;
	HeightPerShift	=LSrc->HeightPerShift;
	VFilterLength	=LSrc->VFilterLength;	
	LargeTilt		=LSrc->LargeTilt	;	
	LargeFlatness	=LSrc->LargeFlatness;	
	SmallFlatness	=LSrc->SmallFlatness;	
	SmallAreaSize	=LSrc->SmallAreaSize;	
}
void	Process3DThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	Process3DLibrary	*LDst=dynamic_cast<Process3DLibrary *>(Dest);
	if(LDst==NULL)
		return;

	LDst->BaseCycleDot		=BaseCycleDot	;
	LDst->HeightPerShift	=HeightPerShift	;
	LDst->VFilterLength		=VFilterLength	;
	LDst->LargeTilt			=LargeTilt		;
	LDst->LargeFlatness		=LargeFlatness	;
	LDst->SmallFlatness		=SmallFlatness	;
	LDst->SmallAreaSize		=SmallAreaSize	;
}

//=====================================================================================


Process3DInLayer::Process3DInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLITemplate<Process3DItem,Process3DInPage,Process3DBase>(parent)
{
}
Process3DInLayer::~Process3DInLayer(void)
{
}
bool		Process3DInLayer::AppendItem(AlgorithmItemRoot *item)
{
	if(item->GetLibID()>=0){
		AlgorithmLibraryLevelContainer	*LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		if(LibP==NULL){
			GetParentBase()->LoadAllManagedCacheLib();
			LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		}
		if(LibP!=NULL){
			if(LibP->HasGenLayer(GetLayer())==true){
				return AlgorithmInLayerPLI::AppendItem(item);
			}
			return false;
		}
	}
	return AlgorithmInLayerPLI::AppendItem(item);
}

bool		Process3DInLayer::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}

bool		Process3DInLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	return AlgorithmInLayerPLI::AppendItemFromLoad(item);
}

bool		Process3DInLayer::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	return AlgorithmInLayerPLI::AppendItem(item,itemID);
}

void	Process3DInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedProcess3DFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedProcess3DFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		Process3DItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			Process3DItem	*B=(Process3DItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
		return;
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				Process3DItem	*B=(Process3DItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}

	CmdProcess3DInfoListPacket	*CmdProcess3DInfoListPacketVar=dynamic_cast<CmdProcess3DInfoListPacket *>(packet);
	if(CmdProcess3DInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			Process3DInfoList	*a=new Process3DInfoList();
			a->LibID		=L->GetLibID();
			a->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			a->Layer		=GetLayer();
			a->ItemID		=L->GetID();
			a->ItemName		=L->GetItemName();
			L->GetXY(a->x1,a->y1,a->x2,a->y2);
			CmdProcess3DInfoListPacketVar->Process3DInfos->AppendList(a);
		}
		return;
	}
	CmdGetProcess3DFromList	*CmdGetProcess3DFromListVar=dynamic_cast<CmdGetProcess3DFromList *>(packet);
	if(CmdGetProcess3DFromListVar!=NULL){
		Process3DItem *Item=(Process3DItem *)SearchIDItem(CmdGetProcess3DFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetProcess3DFromListVar->Process3DInfoOnMouse=Item;
		return;
	}
	CmdCreateProcess3DItem	*CmdCreateProcess3DItemVar=dynamic_cast<CmdCreateProcess3DItem *>(packet);
	if(CmdCreateProcess3DItemVar!=NULL){
		CmdCreateProcess3DItemVar->Process3D=(Process3DItem *)CreateItem(0);
		return;
	}
	CmdAddProcess3DItemPacket	*AddBItem=dynamic_cast<CmdAddProcess3DItemPacket *>(packet);
	if(AddBItem!=NULL){
		Process3DItem	*Item=new Process3DItem();
		Item->SetArea	 (AddBItem->Area);
		Item->SetItemName(AddBItem->ItemName);
		Item->SetLibID	 (AddBItem->LibID);
		Process3DBase	*BBase=(Process3DBase *)GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
			((Process3DItem *)Item)->CopyThresholdFromLibrary(&LLib);
		}
		Item->SetManualCreated(true);
		GetParentBase()->ClearManagedCacheLib();
		if(AppendItem(Item)==false){
			delete	Item;
		}
		return;
	}
}

void	Process3DInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		Process3DItem	*BI=(Process3DItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

void	Process3DInLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		Process3DItem	*a=dynamic_cast<Process3DItem *>(k);
		if(a!=NULL){
			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}
	}
}

//===========================================================================================
Process3DInPage::Process3DInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLITemplate<Process3DItem,Process3DInLayer,Process3DBase>(parent)
{
}
Process3DInPage::~Process3DInPage(void)
{
}

void	Process3DInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddProcess3DItemPacket	*AddBItem=dynamic_cast<CmdAddProcess3DItemPacket *>(packet);
	if(AddBItem!=NULL){
		if(0<=AddBItem->Layer && AddBItem->Layer<GetLayerNumb()){
			GetLayerData(AddBItem->Layer)->TransmitDirectly(packet);
		}
		return;
	}

	CmdProcess3DInfoListPacket	*CmdProcess3DInfoListPacketVar=dynamic_cast<CmdProcess3DInfoListPacket *>(packet);
	if(CmdProcess3DInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdGetProcess3DFromList	*CmdGetProcess3DFromListVar=dynamic_cast<CmdGetProcess3DFromList *>(packet);
	if(CmdGetProcess3DFromListVar!=NULL){
		if(CmdGetProcess3DFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetProcess3DFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
}

//===========================================================================================
Process3DBase::Process3DBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	Process3DNormal		=Qt::darkGreen;
	Process3DSelected	=Qt::green;
	Process3DActive		=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;

	SetParam(&Process3DNormal	, /**/"Color" ,/**/"Process3DNormal"		,"Color for Area");
	SetParam(&Process3DSelected	, /**/"Color" ,/**/"Process3DSelected"		,"Color for Selected Area");
	SetParam(&Process3DActive	, /**/"Color" ,/**/"Process3DActive"		,"Color for Active Area");

	SetParam(&BlockColor0		, /**/"BlockColor"	,/**/"BlockColor0"		,"Area Color 0");
	SetParam(&BlockColor1		, /**/"BlockColor"	,/**/"BlockColor1"		,"Area Color 1");
	SetParam(&BlockColor2		, /**/"BlockColor"	,/**/"BlockColor2"		,"Area Color 2");
	SetParam(&BlockColor3		, /**/"BlockColor"	,/**/"BlockColor3"		,"Area Color 3");
	SetParam(&BlockColor4		, /**/"BlockColor"	,/**/"BlockColor4"		,"Area Color 4");
	SetParam(&BlockColor5		, /**/"BlockColor"	,/**/"BlockColor5"		,"Area Color 5");
	SetParam(&BlockColor6		, /**/"BlockColor"	,/**/"BlockColor6"		,"Area Color 6");
	SetParam(&BlockColor7		, /**/"BlockColor"	,/**/"BlockColor7"		,"Area Color 7");

	SetParam(&OmitZoneDot		, /**/"Setting"		,/**/"OmitZoneDot"		,"Omit zone dot in area generation");
}

AlgorithmDrawAttr	*Process3DBase::CreateDrawAttr(void)
{
	return new Process3DDrawAttr();
}

void	Process3DBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetProcess3DLibraryListPacket	*AListPacket=dynamic_cast<CmdGetProcess3DLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetProcess3DLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetProcess3DLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertProcess3DLibraryPacket	*BInsLib=dynamic_cast<CmdInsertProcess3DLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(Process3DVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateProcess3DLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateProcess3DLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(Process3DVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadProcess3DLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadProcess3DLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempProcess3DLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempProcess3DLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearProcess3DLibraryPacket	*CmdClearProcess3DLibraryPacketVar=dynamic_cast<CmdClearProcess3DLibraryPacket *>(packet);
	if(CmdClearProcess3DLibraryPacketVar!=NULL){
		CmdClearProcess3DLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteProcess3DLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteProcess3DLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempProcess3DItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempProcess3DItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new Process3DItem();
		return;
	}
	CmdCreateByteArrayFromProcess3DItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromProcess3DItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadProcess3DItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadProcess3DItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedProcess3DFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedProcess3DFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		AlgorithmLibraryLevelContainer	LibData(this);
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
	CmdCreateProcess3DItem	*CmdCreateProcess3DItemVar=dynamic_cast<CmdCreateProcess3DItem *>(packet);
	if(CmdCreateProcess3DItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

ExeResult	Process3DBase::ExecuteInitialAfterEdit(int ExeID 
													,ResultBaseForAlgorithmRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ColorLogicWithTable::ClearTable();
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}


bool	Process3DBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==Process3DHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==Process3DHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==Process3DReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==Process3DReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==Process3DReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==Process3DSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==Process3DReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*Process3DBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==Process3DReqThresholdReqCommand){
		return new Process3DThresholdReq();
	}
	else if(Command==Process3DReqThresholdSendCommand){
		Process3DThresholdSend	*pSend=new Process3DThresholdSend();
		if(reqData!=NULL){
			Process3DThresholdReq	*req=(Process3DThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==Process3DReqTryThresholdCommand){
		return new Process3DReqTryThreshold();
	}
	else if(Command==Process3DSendTryThresholdCommand){
		Process3DSendTryThreshold	*pSend=new Process3DSendTryThreshold();
		if(reqData!=NULL){
			Process3DReqTryThreshold	*req=(Process3DReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	Process3DBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==Process3DReqThresholdReqCommand){
		Process3DThresholdReq	*p=(Process3DThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==Process3DReqThresholdSendCommand){
		Process3DThresholdSend	*p=(Process3DThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==Process3DReqTryThresholdCommand){
		Process3DReqTryThreshold	*p=(Process3DReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==Process3DSendTryThresholdCommand){
		Process3DSendTryThreshold	*p=(Process3DSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	Process3DBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==Process3DReqThresholdReqCommand){
		Process3DThresholdReq	*p=(Process3DThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==Process3DReqThresholdSendCommand){
		Process3DThresholdSend	*p=(Process3DThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==Process3DReqTryThresholdCommand){
		Process3DReqTryThreshold	*p=(Process3DReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==Process3DSendTryThresholdCommand){
		Process3DSendTryThreshold	*p=(Process3DSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	Process3DBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==Process3DReqThresholdReqCommand){
		Process3DThresholdReq	*p=(Process3DThresholdReq *)data;
		return true;
	}
	else if(Command==Process3DReqThresholdSendCommand){
		Process3DThresholdSend	*p=(Process3DThresholdSend *)data;
		return true;
	}
	else if(Command==Process3DReqTryThresholdCommand){
		Process3DReqTryThreshold	*p=(Process3DReqTryThreshold *)data;
		return true;
	}
	else if(Command==Process3DSendTryThresholdCommand){
		Process3DSendTryThreshold	*p=(Process3DSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}



