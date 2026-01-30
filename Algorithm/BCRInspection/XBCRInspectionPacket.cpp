/*
 * Copyright (C) 2026
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

#include "swap.h"
#include "XBCRInspection.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"

BCRInspectionThresholdReq::BCRInspectionThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	BCRInspectionThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
bool	BCRInspectionThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

BCRInspectionThresholdSend::BCRInspectionThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;

	CheckType			=0;		   
	QuilityGrade		=10.0;
	BarcodeIsOnlyDigit	=false;
}

void	BCRInspectionThresholdSend::ConstructList(BCRInspectionThresholdReq *reqPacket,BCRInspectionBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			BCRInspectionItem	*BItem=(BCRInspectionItem *)item;

			const	BCRInspectionThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			CheckType			=RThr->CheckType			;
			QuilityGrade		=RThr->QuilityGrade			;
			GradeList			=RThr->GradeList			;
			BarcodeIsOnlyDigit	=RThr->BarcodeIsOnlyDigit	;
		}
	}
}

bool	BCRInspectionThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	if(::Save(f,CheckType)==false)
		return false;
	if(::Save(f,QuilityGrade)==false)
		return false;
	if(GradeList.Save(f)==false)
		return false;
	if(::Save(f,BarcodeIsOnlyDigit)==false)
		return false;

	return true;
}
bool	BCRInspectionThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	if(::Load(f,CheckType)==false)
		return false;
	if(::Load(f,QuilityGrade)==false)
		return false;
	if(GradeList.Load(f)==false)
		return false;
	if(::Load(f,BarcodeIsOnlyDigit)==false)
		return false;

	return true;
}

BCRInspectionReqTryThreshold::BCRInspectionReqTryThreshold(void)
{
	GlobalPage=-1;
	BCRInspectionItemID=-1;
}
bool	BCRInspectionReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BCRInspectionItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	BCRInspectionReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BCRInspectionItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

BCRInspectionSendTryThreshold::BCRInspectionSendTryThreshold(void)
{
	Result	=new ResultInItemPI();
	ResultQuality	=0;;
}
BCRInspectionSendTryThreshold::~BCRInspectionSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	BCRInspectionSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ResultQuality	)==false)
		return false;
	if(::Save(f,ResultStr	)==false)
		return false;

	return true;
}
bool	BCRInspectionSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,ResultQuality	)==false)
		return false;
	if(::Load(f,ResultStr	)==false)
		return false;

	return true;
}

void	BCRInspectionSendTryThreshold::ConstructList(BCRInspectionReqTryThreshold *reqPacket
													,BCRInspectionBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	BCRInspectionInPage		*BP=(BCRInspectionInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		BCRInspectionItem		*BI=(BCRInspectionItem *)BP->SearchIDItem(reqPacket->BCRInspectionItemID);
		if(BI!=NULL){
			Calc(&reqPacket->Threshold,BI,Base,reqPacket);
		}
	}
}

void	BCRInspectionSendTryThreshold::Calc(BCRInspectionItem *Target
											,BCRInspectionItem *Src
											,BCRInspectionBase *Base
											,BCRInspectionReqTryThreshold *Req)
{
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
	
	Target->SetParent(Src->GetParent());
	Target->SetArea(Src->GetArea());
	ExecuteInitialAfterEditInfo DummyEInfo;
	DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
	Target->ExecuteInitialAfterEdit	(0,0,Result,DummyEInfo);
	Target->AVector				=Src->AVector;
	//BI->ExecuteInitialAfterEdit	(0,Result ,Base->GetLayersBase()->GetEntryPoint());

	if(Req!=NULL){
		Target->GetThresholdW()->CheckType			=Req->Data.CheckType			;		   
		Target->GetThresholdW()->QuilityGrade		=Req->Data.QuilityGrade			;
		Target->GetThresholdW()->GradeList			=Req->Data.GradeList			;
		Target->GetThresholdW()->BarcodeIsOnlyDigit	=Req->Data.BarcodeIsOnlyDigit	;
	}
	Target->ExecuteStartByInspection	(0,0,Result);
	Target->ExecuteProcessing			(0,0,Result);

	ResultStr		=Target->Result;
	ResultQuality	=Result->GetResultDouble();
}