/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaColorConverter\XAreaColorConverter.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaColorConverter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaColorConverterPacket.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>


AreaColorConverterLibrary::AreaColorConverterLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	ConvertType=_CMYK;
}

AreaColorConverterLibrary::~AreaColorConverterLibrary(void)
{
}

bool	AreaColorConverterLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int32	D=(int32)ConvertType;
	if(::Save(f,D)==false)
		return false;

	return true;
}
bool	AreaColorConverterLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int32	D;
	if(::Load(f,D)==false)
		return false;
	ConvertType=(_ConvertType)D;

	return true;
}
AreaColorConverterLibrary	&AreaColorConverterLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AreaColorConverterLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

AreaColorConverterLibraryContainer::AreaColorConverterLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
AreaColorConverterLibraryContainer::~AreaColorConverterLibraryContainer(void)
{
}

//====================================================================================

void	AreaColorConverterInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaColorConverterItemPacket	*CmdAddAreaColorConverterItemPacketVar=dynamic_cast<CmdAddAreaColorConverterItemPacket *>(packet);
	if(CmdAddAreaColorConverterItemPacketVar!=NULL){
		AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
		Lib.SetLibID(CmdAddAreaColorConverterItemPacketVar->SelectedLibID);
		if(GetLibraryContainer()->GetLibrary(CmdAddAreaColorConverterItemPacketVar->SelectedLibID,Lib)==true){
			AlgorithmItemRoot	*Item=CreateItem();
			Item->SetArea(CmdAddAreaColorConverterItemPacketVar->Area);
			Item->SetLibID(CmdAddAreaColorConverterItemPacketVar->SelectedLibID);
			Item->CopyThresholdFromLibrary(&Lib);
			AppendItem(Item);
		}
	}
}

void	AreaColorConverterInPage::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		AreaColorConverterItem	*BI=(AreaColorConverterItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}
//===========================================
AreaColorConverterBase::AreaColorConverterBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	AreaColor				=Qt::green;
	NegAreaColorSelected	=Qt::yellow;
	NegAreaColor			=Qt::red;
	TransparentLevel		=80;

	SetParam(&AreaColor				, /**/"Color" ,/**/"AreaColor"				,"filtered Area Color");
	SetParam(&NegAreaColorSelected	, /**/"Color" ,/**/"NegAreaColorSelected"	,"Color for Selected filtered area");
	SetParam(&NegAreaColor			, /**/"Color" ,/**/"NegAreaColor"			,"Color for Active filtered area");
	SetParam(&TransparentLevel		, /**/"Color" ,/**/"TransparentLevel"		,"Color for Transparent display level");
}

AlgorithmDrawAttr	*AreaColorConverterBase::CreateDrawAttr(void)
{
	return new AreaColorConverterDrawAttr();
}


bool	AreaColorConverterBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

void	AreaColorConverterBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetAreaColorConverterLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAreaColorConverterLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetAreaColorConverterLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAreaColorConverterLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertAreaColorConverterLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAreaColorConverterLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AreaColorConverterVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAreaColorConverterLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAreaColorConverterLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AreaColorConverterVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadAreaColorConverterLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAreaColorConverterLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempAreaColorConverterLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAreaColorConverterLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdDeleteAreaColorConverterLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAreaColorConverterLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	/*
	CmdCreateByteArrayFromAreaColorConverterItemPacket	*BAFromAreaColorConverterItem=dynamic_cast<CmdCreateByteArrayFromAreaColorConverterItemPacket *>(packet);
	if(BAFromAreaColorConverterItem!=NULL){
		QBuffer	Buff(&BAFromAreaColorConverterItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromAreaColorConverterItem->Point->Save(&Buff);
	}
	*/
	CmdAddAreaColorConverterItemPacket	*CmdAddAreaColorConverterItemPacketVar=dynamic_cast<CmdAddAreaColorConverterItemPacket *>(packet);
	if(CmdAddAreaColorConverterItemPacketVar!=NULL){
		GetPageData(CmdAddAreaColorConverterItemPacketVar->LocalPage)->TransmitDirectly(CmdAddAreaColorConverterItemPacketVar);
	}
}

