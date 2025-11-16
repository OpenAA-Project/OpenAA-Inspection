#include "BCRInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XBlockForReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XBCRInspection.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmDLL.h"
#include "XDLLType.h"

void	BCRInspectionThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add(LangSolver.GetString(XBCRInspectionReport_LS,LID_17)/*"CheckType"*/	,CheckType);
	RetContainer.Add(LangSolver.GetString(XBCRInspectionReport_LS,LID_18)/*"QuilityGrade"*/	,QuilityGrade);
}


DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=LangSolver.GetString(XBCRInspectionReport_LS,LID_19)/*"Need Fin"*/;
		return false;
	}
	BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(aitem);
	if(Item!=NULL){
		if(ItemRes->GetError()==12){
			RetStrBuff=LangSolver.GetString(XBCRInspectionReport_LS,LID_20)/*"品質検査"*/;
		}
	}		

	return true;
}

DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList)
{
	if(Pos->result==0x11000){
		DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(XBCRInspectionReport_LS,LID_21)/*"Barcode:NG "*/);
		L->Add(Pos->Message,Pos->GetResultDouble());
		RetList.AppendList(L);
	}

	return true;
}
