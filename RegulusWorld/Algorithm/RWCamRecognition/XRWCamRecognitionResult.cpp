/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RWCamRecognition\RWCamRecognitionResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlgorithmDLL.h"
#include "XRWCamRecognition.h"
#include "XDLLType.h"

void	RWCamRecognitionThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("RepeatCount"		,RepeatCount	);
	RetContainer.Add("MeshSize"			,MeshSize		);
	RetContainer.Add("SequenceOffset"	,SequenceOffset	);
	RetContainer.Add("GatherAllPhase"	,GatherAllPhase	);
}

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff="Need Fin";
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	QString	Str;
	DetailResultInfoList	*L=new DetailResultInfoList();
	L->SetMessage("NG");

	return true;
}
