/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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
	CmdReqGridList *CmdReqGridListVar = dynamic_cast<CmdReqGridList *>(packet);
	if (CmdReqGridListVar != NULL) {
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetItemClassType()==CmdReqGridListVar->VType){
				ColorCorrectorGridList	*L=new ColorCorrectorGridList();
				L->Page=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				L->ItemID=a->GetID();
				const	AlgorithmThreshold	*r=a->GetThresholdBaseReadable(GetLayersBase());
				const ColorCorrectorThresholdBase	*RThr=dynamic_cast<const ColorCorrectorThresholdBase *>(r);
				a->GetXY(L->x1,L->y1,L->x2,L->y2);
				CmdReqGridListVar->ListData->AppendList(L);
			}
		}		
		return;
	}
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