/*
 * Copyright (C) 2023
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

#include "BCRInspectionResource.h"

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