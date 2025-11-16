/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureHolePos\XMeasureHolePos.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureHolePos.h"
#include "omp.h"


//==============================================================================
MeasureHolePosThreshold::MeasureHolePosThreshold(MeasureHolePosItemBase *parent)
:AlgorithmThreshold(parent)
{
	DiaPrecision=25;	//micron size
	PosPrecision=25;	//micron size
	NoiseSize	=2;
	BandWidth	=10;
	SearchDot	=10;
	CalcMode	=0;
}

void	MeasureHolePosThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MeasureHolePosThreshold *s=(const MeasureHolePosThreshold *)&src;
    HoleColor	=s->HoleColor;
	DiaPrecision=s->DiaPrecision;
	PosPrecision=s->PosPrecision;
	NoiseSize	=s->NoiseSize;
	BandWidth	=s->BandWidth;
	SearchDot	=s->SearchDot;
	CalcMode	=s->CalcMode;
}
bool	MeasureHolePosThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MeasureHolePosThreshold *s=(const MeasureHolePosThreshold *)&src;
    if(HoleColor	!=s->HoleColor		)	return false;
	if(DiaPrecision	!=s->DiaPrecision	)	return false;
	if(PosPrecision	!=s->PosPrecision	)	return false;
	if(NoiseSize	!=s->NoiseSize		)	return false;
	if(BandWidth	!=s->BandWidth		)	return false;
	if(SearchDot	!=s->SearchDot		)	return false;
	if(CalcMode		!=s->CalcMode		)	return false;
	return true;
}
bool	MeasureHolePosThreshold::Save(QIODevice *f)
{
	WORD	Ver=2;

	if(::Save(f,Ver)==false)
		return(false);
	if(HoleColor.Save(f)==false)
		return false;
	if(::Save(f,DiaPrecision)==false)
		return(false);
	if(::Save(f,PosPrecision)==false)
		return(false);
	if(::Save(f,NoiseSize)==false)
		return(false);
	if(::Save(f,SearchDot)==false)
		return(false);
	if(::Save(f,BandWidth)==false)
		return(false);
	if(::Save(f,CalcMode)==false)
		return(false);

	return(true);
}
bool	MeasureHolePosThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(HoleColor.Load(f)==false)
		return false;
	if(::Load(f,DiaPrecision)==false)
		return(false);
	if(::Load(f,PosPrecision)==false)
		return(false);
	if(::Load(f,NoiseSize)==false)
		return(false);
	if(::Load(f,SearchDot)==false)
		return(false);
	if(::Load(f,BandWidth)==false)
		return(false);
	if(Ver>=2){
		if(::Load(f,CalcMode)==false)
			return(false);
	}
	return(true);
}

void	MeasureHolePosThreshold::FromLibrary(AlgorithmLibrary *src)
{
	MeasureHolePosLibrary	*s=dynamic_cast<MeasureHolePosLibrary *>(src);
	if(s!=NULL){
		HoleColor	=s->HoleColor	;
		DiaPrecision=s->DiaPrecision;
		PosPrecision=s->PosPrecision;
		NoiseSize	=s->NoiseSize	;
		BandWidth	=s->BandWidth	;
		SearchDot	=s->SearchDot	;
		CalcMode	=s->CalcMode	;
	}
}

void	MeasureHolePosThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	MeasureHolePosLibrary	*d=dynamic_cast<MeasureHolePosLibrary *>(Dest);
	if(d!=NULL){
		d->HoleColor	=HoleColor		;
		d->DiaPrecision	=DiaPrecision	;
		d->PosPrecision	=PosPrecision	;
		d->NoiseSize	=NoiseSize		;
		d->BandWidth	=BandWidth		;
		d->SearchDot	=SearchDot		;
		d->CalcMode		=CalcMode		;
	}
}

//===========================================

void	MeasureHolePosInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		MeasureHolePosItemBase	*BI=(MeasureHolePosItemBase *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
	
AlgorithmItemRoot		*MeasureHolePosInPage::CreateItem(int ItemClassType)
{	
	if(ItemClassType==MeasureHolePosItem_ItemClass_Area){
		MeasureHolePosItem	*a=new MeasureHolePosItem();	
		a->SetParent(this);
		return a;
	}
	else if(ItemClassType==MeasureHolePosItem_ItemClass_Vector){
		MeasureHolePosVectorItem	*a=new MeasureHolePosVectorItem();	
		a->SetParent(this);
		return a;
	}
	return NULL;
}


void	MeasureHolePosInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMeasureHolePosAreaPacket	*AddMArea=dynamic_cast<AddMeasureHolePosAreaPacket *>(packet);
	if(AddMArea!=NULL){
		MeasureHolePosItem	*MData=(MeasureHolePosItem *)CreateItem();
		MData->GetThresholdW()->HoleColor	=AddMArea->HoleColor;
		MData->SetArea(AddMArea->MaskArea);
		MData->SetManualCreated(true);
		AppendItem(MData);
	}
	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureHolePosItemBase	*ai=dynamic_cast<MeasureHolePosItemBase *>(a);
			if(ai!=NULL){
				HolePosListForPacket	*d=new HolePosListForPacket();
				d->ItemID	=ai->GetID();
				d->ItemName	=ai->GetItemName();
				d->Page		=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				ai->GetXY(d->x1 ,d->y1 ,d->x2 ,d->y2);
				d->SearchDot=ai->GetThresholdR(GetLayersBase())->SearchDot;
				MakeListPacketVar->ListInfo->AppendList(d);
			}
		}
		return;
	}
	CmdReqMeasureDataPacket	*CmdReqMeasureDataVar=dynamic_cast<CmdReqMeasureDataPacket *>(packet);
	if(CmdReqMeasureDataVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureHolePosItemBase	*ai=dynamic_cast<MeasureHolePosItemBase *>(a);
			if(ai!=NULL){
				MeasureDataList	*D=new MeasureDataList();
				D->Page	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				D->Name	=ai->GetItemName();
				D->AlgoType	="Hole Width";
				D->Value=ai->MasterDiameterX+ai->ResultWidthDiff;
				CmdReqMeasureDataVar->Data.AppendList(D);

				D=new MeasureDataList();
				D->Page	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				D->Name	=ai->GetItemName();
				D->AlgoType	="Hole Height";
				D->Value=ai->MasterDiameterX+ai->ResultHeightDiff;
				CmdReqMeasureDataVar->Data.AppendList(D);
			}
		}
		return;
	}
	CmdReqMeasureHolePosDataPacket	*CmdReqMeasureHolePosDataPacketVar=dynamic_cast<CmdReqMeasureHolePosDataPacket *>(packet);
	if(CmdReqMeasureHolePosDataPacketVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureHolePosItemBase	*ai=dynamic_cast<MeasureHolePosItemBase *>(a);
			if(ai!=NULL){
				MeasureHolePosDataList	*D=new MeasureHolePosDataList();
				D->HData.Page	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				D->HData.ItemID	=ai->GetID();
				D->HData.MasterCx=ai->MasterPosX;
				D->HData.MasterCy=ai->MasterPosY;
				D->HData.MasterRx=ai->MasterDiameterX/2.0;
				D->HData.MasterRy=ai->MasterDiameterY/2.0;
				D->HData.TargetCx=(ai->RxRight + ai->RxLeft)/2.0;
				D->HData.TargetCy=(ai->RyTop + ai->RyBottom)/2.0;
				D->HData.TargetRx=(ai->RxRight - ai->RxLeft)/2.0;
				D->HData.TargetRy=(ai->RyBottom - ai->RyTop)/2.0;
				CmdReqMeasureHolePosDataPacketVar->Data.AppendList(D);
			}
		}
		return;
	}
}

//===========================================
MeasureHolePosBase::MeasureHolePosBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	ResultLineWidth	=2;

	Offset	=0;
	Gain	=1.0;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");

	SetParam(&Offset			, /**/"Seting" ,/**/"Offset"			,"Offset from measured diameter to result");
	SetParam(&Gain				, /**/"Seting" ,/**/"Gain"				,"Multplied-gain from measured diameter to result");
	SetParam(&ResultLineWidth	, /**/"Seting" ,/**/"ResultLineWidth"	,"Line width in result");
}

AlgorithmDrawAttr	*MeasureHolePosBase::CreateDrawAttr(void)
{
	return new MeasureHolePosDrawAttr();
}

void	MeasureHolePosBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempMeasureHolePosItemPacket	*CreateMeasureHolePosItem=dynamic_cast<CmdCreateTempMeasureHolePosItemPacket *>(packet);
	if(CreateMeasureHolePosItem!=NULL){
		CreateMeasureHolePosItem->Point=new MeasureHolePosItem();
		return;
	}
	CmdCreateTempMeasureHolePosLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempMeasureHolePosLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdGetMeasureHolePosLibraryListPacket	*AListPacket=dynamic_cast<CmdGetMeasureHolePosLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdLoadMeasureHolePosLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadMeasureHolePosLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearMeasureHolePosLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearMeasureHolePosLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteMeasureHolePosLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteMeasureHolePosLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdAddByteMeasureHolePosItemPacket	*AddBItem=dynamic_cast<CmdAddByteMeasureHolePosItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			if(AddBItem->Vector==NULL){
				MeasureHolePosItem	*Item=new MeasureHolePosItem();
				MBuff.open(QIODevice::ReadWrite);
				Item->Load(&MBuff,GetLayersBase());
				Item->SetArea(AddBItem->Area);
				Item->SetManualCreated(true);
				PData->AppendItem(Item);
			}
			else{
				MeasureHolePosVectorItem	*Item=new MeasureHolePosVectorItem();
				MBuff.open(QIODevice::ReadWrite);
				Item->Load(&MBuff,GetLayersBase());
				Item->SetVector(*AddBItem->Vector);
				Item->SetManualCreated(true);
				PData->AppendItem(Item);
			}
		}
	}
	CmdCreateByteArrayFromMeasureHolePosItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromMeasureHolePosItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdInsertMeasureHolePosLibraryPacket	*BInsLib=dynamic_cast<CmdInsertMeasureHolePosLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(MeasureHolePosVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateMeasureHolePosLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateMeasureHolePosLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(MeasureHolePosVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdCreateThresholdPacket	*CmdCreateThresholdPacketVar=dynamic_cast<CmdCreateThresholdPacket *>(packet);
	if(CmdCreateThresholdPacketVar!=NULL){
		CmdCreateThresholdPacketVar->Thre=new MeasureHolePosThreshold(NULL);
		return;
	}
}

//bool	MeasureHolePosBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
//{
	/*
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(DForm);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	DynamicMaskingPIItem	Item(NULL);
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	*/
//	return true;
//}
