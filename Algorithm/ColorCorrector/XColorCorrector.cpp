/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XColorCorrector.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XColorCorrector.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XCriticalFunc.h"


//===========================================
ColorCorrectorInPage::ColorCorrectorInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<ColorCorrectorItemBase,ColorCorrectorBase>(parent)
{

}
ColorCorrectorInPage::~ColorCorrectorInPage(void)
{
}
AlgorithmItemRoot	*ColorCorrectorInPage::CreateItem(int ItemClassType)
{
	if(ItemClassType==(int32)ItemClassColorShiftV){
		ColorShiftVItem	*Item=new ColorShiftVItem();
		Item->SetParent(this);
		return Item;
	}
	else
	if(ItemClassType==(int32)ItemClassColorChangeV){
		ColorChangeVItem	*Item=new ColorChangeVItem();
		Item->SetParent(this);
		return Item;
	}
	return NULL;
}

void	ColorCorrectorInPage::TransmitDirectly(GUIDirectMessage *packet)
{	
	CmdAddByteColorCorrectorItemPacket	*CmdAddAreaManualVar=dynamic_cast<CmdAddByteColorCorrectorItemPacket *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		AlgorithmItemRoot	*Item=CreateItem((int32)CmdAddAreaManualVar->VType);
		ColorCorrectorThresholdBase	*WThr=dynamic_cast<ColorCorrectorThresholdBase *>(Item->GetThresholdBaseWritable(GetLayersBase()));
		QBuffer	Buff(&CmdAddAreaManualVar->Buff);
		Buff.open(QIODevice::ReadWrite);
		if(WThr!=NULL){
			WThr->Load(&Buff);
		}
		Item->SetArea(CmdAddAreaManualVar->Area);
		Item->SetManualCreated(true);
		AppendItem(Item);
		return;
	}
	//CmdSetColorCorrector	*CmdSetColorCorrectorVar=dynamic_cast<CmdSetColorCorrector *>(packet);
	//if(CmdSetColorCorrectorVar!=NULL){
	//	ColorCorrectorItem	*Item=tGetFirstData();
	//	if(Item==NULL){
	//		AlignmentLargeBase	*ALBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
	//		if(ALBase!=NULL){
	//			AlignmentLargeInPage	*ALPage=(AlignmentLargeInPage *)ALBase->GetPageData(GetPage());
	//			CmdGetFirstAlignmentArea	TCmd(GetLayersBase());
	//			ALPage->TransmitDirectly(&TCmd);
	//			if(TCmd.AreaID>=0){
	//				Item=(ColorCorrectorItem *)CreateItem(0);
	//				Item->SetArea(TCmd.Area);
	//				Item->SetManualCreated(false);
	//				AppendItem(Item);
	//			}
	//		}
	//	}
	//	if(Item!=NULL){
	//		ColorCorrectorThreshold	*WThr=Item->GetThresholdW();
	//		WThr->OKAngleL	=CmdSetColorCorrectorVar->OKAngleL;
	//		WThr->OKAngleH	=CmdSetColorCorrectorVar->OKAngleH;
	//	}
	//	return;
	//}
}


//===========================================
ColorCorrectorBase::ColorCorrectorBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorNormal		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;

	SetParam(&ColorNormal		, /**/"Color"	,/**/"ColorNormal"			,"Color for area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea		, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected	, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel	, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");

}

AlgorithmDrawAttr	*ColorCorrectorBase::CreateDrawAttr(void)
{
	return new ColorCorrectorDrawAttr(GetLayersBase());
}

void	ColorCorrectorBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateThreshold	*CmdCreateThresholdVar=dynamic_cast<CmdCreateThreshold *>(packet);
	if(CmdCreateThresholdVar!=NULL){		
		if(CmdCreateThresholdVar->VType==ItemClassColorShiftV){
			CmdCreateThresholdVar->Thr=new ColorShiftVThreshold();
		}
		else
		if(CmdCreateThresholdVar->VType==ItemClassColorShiftH){
			//CmdCreateThresholdVar->Thr=new ColorCorrectorExistItemVectorThreshold();
		}
		else
		if(CmdCreateThresholdVar->VType==ItemClassColorShiftV){
			CmdCreateThresholdVar->Thr=new ColorChangeVThreshold();
		}
		else
		if(CmdCreateThresholdVar->VType==ItemClassColorChangeH){
			//CmdCreateThresholdVar->Thr=new ColorCorrectorProhibiteItemThreshold();
		}
		return;
	}
	CmdLoadThreshold	*CmdLoadThresholdVar=dynamic_cast<CmdLoadThreshold *>(packet);
	if(CmdLoadThresholdVar!=NULL){
		QBuffer	Buff(&CmdLoadThresholdVar->Data);
		Buff.open(QIODevice::ReadWrite);
		CmdLoadThresholdVar->Thr->Load(&Buff);
		return;
	}
	CmdSaveThreshold	*CmdSaveThresholdVar=dynamic_cast<CmdSaveThreshold *>(packet);
	if(CmdSaveThresholdVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		CmdSaveThresholdVar->Thr->Save(&Buff);
		CmdSaveThresholdVar->Data=Buff.buffer();
		return;
	}
}

QString	ColorCorrectorBase::GetNameByCurrentLanguage(void)
{
	return "ColorCorrector";
}
