/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\CategorizedShader\XCategorizedShader.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XCategorizedShader.h"
#include "XGeneralFunc.h"
#include "XPointer.h"


CategorizedShaderLibrary::CategorizedShaderLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
}

bool	CategorizedShaderLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=CategorizedShaderVersion;

	if(::Save(f,Ver)==false){
		return false;
	}

	return true;
}
bool	CategorizedShaderLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}

	return true;
}
//=============================================================================

CategorizedShaderThreshold::CategorizedShaderThreshold(CategorizedShaderItem *parent)
:AlgorithmThreshold(parent)
{
	Strength=1.0;
}

bool	CategorizedShaderThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CategorizedShaderThreshold *s=(const CategorizedShaderThreshold *)&src;

	if(Strength!=s->Strength)	return false;
	return true;
}

bool	CategorizedShaderThreshold::Save(QIODevice *f)
{
	int32	Ver=CategorizedShaderVersion;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,Strength)==false){
		return false;
	}

	return true;
}
bool	CategorizedShaderThreshold::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,Strength)==false){
		return false;
	}

	return true;
}

//=============================================================================

CategorizedShaderInPage::CategorizedShaderInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	UncoveredMap	=NULL;
	XByte	=0;
	YLen	=0;
}
CategorizedShaderInPage::~CategorizedShaderInPage(void)
{
	if(UncoveredMap!=NULL){
		DeleteMatrixBuff(UncoveredMap,YLen);
		UncoveredMap	=NULL;
		XByte	=0;
		YLen	=0;
	}
}

void	CategorizedShaderInPage::TransmitDirectly(GUIDirectMessage *packet)
{
}

ExeResult	CategorizedShaderInPage::ExecuteInitialAfterEdit(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	
	if(UncoveredMap!=NULL){
		DeleteMatrixBuff(UncoveredMap,YLen);
	}
	XByte	=(GetDotPerLine()+7)/8;
	YLen	=GetMaxLines();
	UncoveredMap	=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear(UncoveredMap,0 ,XByte,YLen);
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		p->GetArea().MakeBitData(UncoveredMap,GetDotPerLine(),GetMaxLines());
	}
	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

ExeResult	CategorizedShaderInPage::ExecutePreProcessing(int ExeID ,ResultInPageRoot *Res)
{
	return _ER_true;
}

//=============================================================================

CategorizedShaderBase::CategorizedShaderBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorItem		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorItem	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	DefaultStrength	=0.8;
	MeshSize		=2000;

	SetParam(&ColorItem			, /**/"Color" ,/**/"ColorItem"			,"Color for Item");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Item");
	SetParam(&NegColorItem		, /**/"Color" ,/**/"NegColorItem"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");

	SetParam(&DefaultStrength	, /**/"Color" ,/**/"DefaultStrength"	,"Default Strength(0.0 - 1.0)");
	SetParam(&MeshSize			, /**/"Color" ,/**/"MeshSize"			,"Mesh Size");
}

AlgorithmDrawAttr	*CategorizedShaderBase::CreateDrawAttr(void)
{
	return NULL;
}

void	CategorizedShaderBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetCategorizedShaderLibraryListPacket	*AListPacket=dynamic_cast<CmdGetCategorizedShaderLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetCategorizedShaderLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetCategorizedShaderLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertCategorizedShaderLibraryPacket	*BInsLib=dynamic_cast<CmdInsertCategorizedShaderLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(CategorizedShaderVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateCategorizedShaderLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateCategorizedShaderLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(CategorizedShaderVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadCategorizedShaderLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadCategorizedShaderLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempCategorizedShaderLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempCategorizedShaderLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearCategorizedShaderLibraryPacket	*CmdClearCategorizedShaderLibraryPacketVar=dynamic_cast<CmdClearCategorizedShaderLibraryPacket *>(packet);
	if(CmdClearCategorizedShaderLibraryPacketVar!=NULL){
		CmdClearCategorizedShaderLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteCategorizedShaderLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteCategorizedShaderLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	
	CmdCreateTempCategorizedShaderItemPacket	*CreateCategorizedShaderItem=dynamic_cast<CmdCreateTempCategorizedShaderItemPacket *>(packet);
	if(CreateCategorizedShaderItem!=NULL){
		CreateCategorizedShaderItem->Point=new CategorizedShaderItem();
		return;
	}
	CmdCreateByteArrayFromCategorizedShaderItemPacket	*BAFromCategorizedShaderItem=dynamic_cast<CmdCreateByteArrayFromCategorizedShaderItemPacket *>(packet);
	if(BAFromCategorizedShaderItem!=NULL){
		QBuffer	Buff(&BAFromCategorizedShaderItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromCategorizedShaderItem->Point->Save(&Buff);
	}
	CmdAddByteCategorizedShaderItemPacket	*AddBItem=dynamic_cast<CmdAddByteCategorizedShaderItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI		*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			CategorizedShaderItem	*Item=new CategorizedShaderItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);
		}
	}
	CmdLoadCategorizedShaderItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadCategorizedShaderItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedCategorizedShaderFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedCategorizedShaderFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
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
	/*
	CmdAreaInfoListPacket	*CmdCategorizedShaderInfoListPacketVar=dynamic_cast<CmdAreaInfoListPacket *>(packet);
	if(CmdCategorizedShaderInfoListPacketVar!=NULL){
		GetPageData(CmdCategorizedShaderInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	*/
	CmdGetCategorizedShaderFromList	*CmdGetCategorizedShaderFromListVar=dynamic_cast<CmdGetCategorizedShaderFromList *>(packet);
	if(CmdGetCategorizedShaderFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetCategorizedShaderFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateCategorizedShaderItem	*CmdCreateCategorizedShaderItemVar=dynamic_cast<CmdCreateCategorizedShaderItem *>(packet);
	if(CmdCreateCategorizedShaderItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}
