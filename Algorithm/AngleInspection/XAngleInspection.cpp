/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XAngleInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAngleInspection.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlignmentLarge.h"
#include "XAlignmentLargeLibrary.h"

//=====================================================================================

AngleInspectionThreshold::AngleInspectionThreshold(AngleInspectionItem *parent)
:AlgorithmThreshold(parent)
{
	OKAngleL=5;
	OKAngleH=5;
}

bool	AngleInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AngleInspectionThreshold	*s=(const AngleInspectionThreshold *)&src;

	if(OKAngleL	==s->OKAngleL
	&& OKAngleH	==s->OKAngleH)
		return true;

	return false;
}
void	AngleInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const	AngleInspectionThreshold	*s=(const AngleInspectionThreshold *)&src;
	OKAngleL	=s->OKAngleL;
	OKAngleH	=s->OKAngleH;
}
bool	AngleInspectionThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,OKAngleL)==false)
		return(false);
	if(::Save(file,OKAngleH)==false)
		return(false);

	return(true);
}
bool	AngleInspectionThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,OKAngleL)==false)
		return(false);
	if(::Load(file,OKAngleH)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
AngleInspectionItem::AngleInspectionItem(void)
{
	AVector	=NULL;
}

ExeResult	AngleInspectionItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	//_CrtCheckMemory();
	GetCenter(MasterCx,MasterCy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	return Ret;
}


ExeResult	AngleInspectionItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	double	Rotation;
	if(AVector!=NULL){
		mx		=AVector->ShiftX;
		my		=AVector->ShiftY;
		Rotation=AVector->Rotation;
	}
	else{
		AlignmentPacket2D	V;
		
		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
		Rotation=V.Rotation;
	}

	double	Angle	=Rotation*180.0/M_PI;
	Res->SetResultDouble(Angle);
	const	AngleInspectionThreshold	*RThr=GetThresholdR();
	if(-RThr->OKAngleL<=Angle && Angle<=RThr->OKAngleH){
		Res->SetError(1);
	}
	else{
		Res->SetError(2);
	}
	Res->SetAlignedXY(mx,my);

	FinishCalc();
	return _ER_true;
}

//===========================================
AngleInspectionInPage::AngleInspectionInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<AngleInspectionItem,AngleInspectionBase>(parent)
{

}
AngleInspectionInPage::~AngleInspectionInPage(void)
{
}
AlgorithmItemRoot	*AngleInspectionInPage::CreateItem(int ItemClassType)
{
	if(ItemClassType==0){
		AngleInspectionItem	*Item=new AngleInspectionItem();
		Item->SetParent(this);
		return Item;
	}
	return NULL;
}

void	AngleInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{	
	CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		AngleInspectionItem	*item=(AngleInspectionItem *)CreateItem(0);
		item->SetArea(CmdAddAreaManualVar->Area);
		item->SetManualCreated(true);
		AppendItem(item);
		return;
	}
	CmdSetAngleInspection	*CmdSetAngleInspectionVar=dynamic_cast<CmdSetAngleInspection *>(packet);
	if(CmdSetAngleInspectionVar!=NULL){
		AngleInspectionItem	*Item=tGetFirstData();
		if(Item==NULL){
			AlignmentLargeBase	*ALBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
			if(ALBase!=NULL){
				AlignmentLargeInPage	*ALPage=(AlignmentLargeInPage *)ALBase->GetPageData(GetPage());
				CmdGetFirstAlignmentArea	TCmd(GetLayersBase());
				ALPage->TransmitDirectly(&TCmd);
				if(TCmd.AreaID>=0){
					Item=(AngleInspectionItem *)CreateItem(0);
					Item->SetArea(TCmd.Area);
					Item->SetManualCreated(false);
					AppendItem(Item);
				}
			}
		}
		if(Item!=NULL){
			AngleInspectionThreshold	*WThr=Item->GetThresholdW();
			WThr->OKAngleL	=CmdSetAngleInspectionVar->OKAngleL;
			WThr->OKAngleH	=CmdSetAngleInspectionVar->OKAngleH;
		}
		return;
	}
}

//===========================================
AngleInspectionBase::AngleInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;

	SetParam(&ColorArea			, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea		, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected	, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel	, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");
}

AlgorithmDrawAttr	*AngleInspectionBase::CreateDrawAttr(void)
{
	return new AngleInspectionDrawAttr(GetLayersBase());
}

void	AngleInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
			
}

QString	AngleInspectionBase::GetNameByCurrentLanguage(void)
{
	return "角度検査";
}
