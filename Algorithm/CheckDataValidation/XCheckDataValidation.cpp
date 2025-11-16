/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XCheckDataValidation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XCheckDataValidation.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XAlignmentLarge.h"
#include "XAlignmentLargeLibrary.h"

//===========================================
CheckDataValidationInPage::CheckDataValidationInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<CheckDataValidationItemBase,CheckDataValidationBase>(parent)
{

}
CheckDataValidationInPage::~CheckDataValidationInPage(void)
{
}
AlgorithmItemRoot	*CheckDataValidationInPage::CreateItem(int ItemClassType)
{
	if(ItemClassType==(int32)CheckDataValidation_ExistItemArea){
		CheckDataValidationExistItemAreaItem	*Item=new CheckDataValidationExistItemAreaItem();
		Item->SetParent(this);
		return Item;
	}
	else
	if(ItemClassType==(int32)CheckDataValidation_ExistItemVector){
		CheckDataValidationExistItemVectorItem	*Item=new CheckDataValidationExistItemVectorItem();
		Item->SetParent(this);
		return Item;
	}
	else
	if(ItemClassType==(int32)CheckDataValidation_MinMax){
		CheckDataValidationCheckMinMaxItem	*Item=new CheckDataValidationCheckMinMaxItem();
		Item->SetParent(this);
		return Item;
	}
	else
	if(ItemClassType==(int32)CheckDataValidation_ProhibiteItem){
		CheckDataValidationProhibiteItemItem	*Item=new CheckDataValidationProhibiteItemItem();
		Item->SetParent(this);
		return Item;
	}
	return NULL;
}

void	CheckDataValidationInPage::TransmitDirectly(GUIDirectMessage *packet)
{	
	CmdAddByteCheckDataValidationItemPacket	*CmdAddAreaManualVar=dynamic_cast<CmdAddByteCheckDataValidationItemPacket *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		AlgorithmItemRoot	*Item=CreateItem((int32)CmdAddAreaManualVar->VType);
		CheckDataValidationThresholdBase	*WThr=dynamic_cast<CheckDataValidationThresholdBase *>(Item->GetThresholdBaseWritable(GetLayersBase()));
		QBuffer	Buff(&CmdAddAreaManualVar->Buff);
		Buff.open(QIODevice::ReadWrite);
		if(WThr!=NULL){
			WThr->Load(&Buff);
			WThr->LibType	=CmdAddAreaManualVar->LibType;
			WThr->LibID		=CmdAddAreaManualVar->LibID;
		}
		Item->SetArea(CmdAddAreaManualVar->Area);
		Item->SetManualCreated(true);
		AppendItem(Item);
		return;
	}
	//CmdSetCheckDataValidation	*CmdSetCheckDataValidationVar=dynamic_cast<CmdSetCheckDataValidation *>(packet);
	//if(CmdSetCheckDataValidationVar!=NULL){
	//	CheckDataValidationItem	*Item=tGetFirstData();
	//	if(Item==NULL){
	//		AlignmentLargeBase	*ALBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
	//		if(ALBase!=NULL){
	//			AlignmentLargeInPage	*ALPage=(AlignmentLargeInPage *)ALBase->GetPageData(GetPage());
	//			CmdGetFirstAlignmentArea	TCmd(GetLayersBase());
	//			ALPage->TransmitDirectly(&TCmd);
	//			if(TCmd.AreaID>=0){
	//				Item=(CheckDataValidationItem *)CreateItem(0);
	//				Item->SetArea(TCmd.Area);
	//				Item->SetManualCreated(false);
	//				AppendItem(Item);
	//			}
	//		}
	//	}
	//	if(Item!=NULL){
	//		CheckDataValidationThreshold	*WThr=Item->GetThresholdW();
	//		WThr->OKAngleL	=CmdSetCheckDataValidationVar->OKAngleL;
	//		WThr->OKAngleH	=CmdSetCheckDataValidationVar->OKAngleH;
	//	}
	//	return;
	//}
}
ExeResult	CheckDataValidationInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	NGMessage.clear();
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		CheckDataValidationItemBase	*item=dynamic_cast<CheckDataValidationItemBase *>(p);
		if(item!=NULL){
			item->CheckNG=false;
		}
	}
	AlgorithmInPagePITemplate<CheckDataValidationItemBase,CheckDataValidationBase>::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	
	bool	CheckNG=false;
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		CheckDataValidationItemBase	*item=dynamic_cast<CheckDataValidationItemBase *>(p);
		if(item!=NULL){
			if(item->CheckNG==true){
				CheckNG=true;
				NGMessage=item->CheckedMessage();
			}
		}
	}

	if(CheckNG==true){
		emit	SignalNGOccurs(GetPhaseCode(),GetPage());
	}
	return _ER_true;
}
bool	CheckDataValidationInPage::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(AlgorithmInPagePITemplate<CheckDataValidationItemBase,CheckDataValidationBase>::ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false)
		return false;
	CheckDataValidationBase	*ABase=tGetParentBase();
	if(ABase->LoadDefaultOnStart==true){
		ABase->LoadDefaultValidation();
	}
	return true;
}

//===========================================
CheckDataValidationBase::CheckDataValidationBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;
	LoadDefaultOnStart	=false;
	DefaultLoadFileName	=/**/"DefaultDataValidation.dat";

	SetParam(&ColorArea			, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea		, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected	, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel	, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");

	SetParam(&LoadDefaultOnStart, /**/"Setting",/**/"LoadDefaultOnStart"	,"Mode to load default validation data on start");
	SetParam(&DefaultLoadFileName, /**/"Setting",/**/"DefaultLoadFileName"	,"Default DataValidation file name");
}

AlgorithmDrawAttr	*CheckDataValidationBase::CreateDrawAttr(void)
{
	return new CheckDataValidationDrawAttr(GetLayersBase());
}

void	CheckDataValidationBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateThreshold	*CmdCreateThresholdVar=dynamic_cast<CmdCreateThreshold *>(packet);
	if(CmdCreateThresholdVar!=NULL){		
		if(CmdCreateThresholdVar->VType==CheckDataValidation_ExistItemArea){
			CmdCreateThresholdVar->Thr=new CheckDataValidationExistItemAreaThreshold();
		}
		else
		if(CmdCreateThresholdVar->VType==CheckDataValidation_ExistItemVector){
			CmdCreateThresholdVar->Thr=new CheckDataValidationExistItemVectorThreshold();
		}
		else
		if(CmdCreateThresholdVar->VType==CheckDataValidation_MinMax){
			CmdCreateThresholdVar->Thr=new CheckDataValidationCheckMinMaxThreshold();
		}
		else
		if(CmdCreateThresholdVar->VType==CheckDataValidation_ProhibiteItem){
			CmdCreateThresholdVar->Thr=new CheckDataValidationProhibiteItemThreshold();
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

QString	CheckDataValidationBase::GetNameByCurrentLanguage(void)
{
	return "CheckDataValidation";
}
bool	CheckDataValidationBase::SaveDefaultValidation(void)
{
	if(DefaultLoadFileName.isEmpty()==true)
		return true;
	QFile	File(DefaultLoadFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		int32	iPhaseNumb=GetPhaseNumb();
		if(::Save(&File,iPhaseNumb)==false){
			return false;
		}
		int32	iPageNumb=GetPageNumb();
		if(::Save(&File,iPageNumb)==false){
			return false;
		}
		for(int phase=0;phase<iPhaseNumb;phase++){
			for(int page=0;page<iPageNumb;page++){
				AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
				AlgorithmInPageRoot		*Ap=Ah->GetPageData(page);
				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				Ap->Save(&Buff);
				QByteArray	tData=Buff.buffer();
				if(::Save(&File,tData)==false){
					return  false;
				}
			}
		}
	}
	return  true;
}

bool	CheckDataValidationBase::LoadDefaultValidation(void)
{
	if(DefaultLoadFileName.isEmpty()==true)
		return true;
	QFile	File(DefaultLoadFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	iPhaseNumb;
		if(::Load(&File,iPhaseNumb)==false){
			return false;
		}
		int32	iPageNumb;
		if(::Load(&File,iPageNumb)==false){
			return false;
		}
		for(int phase=0;phase<iPhaseNumb;phase++){
			for(int page=0;page<iPageNumb;page++){
				QByteArray	tData;
				if(::Load(&File,tData)==false){
					return  false;
				}
				if(phase<GetPhaseNumb() && page<GetPageNumb()){
					AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
					AlgorithmInPageRoot		*Ap=Ah->GetPageData(page);
					QBuffer	Buff(&tData);
					Buff.open(QIODevice::ReadOnly);
					Ap->Load(&Buff);
				}
			}
		}
	}
	return  true;
}
