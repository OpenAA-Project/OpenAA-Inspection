//#include "FlatInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\FlatInspection\FlatInspectionResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlgorithmDLL.h"
#include "XFlatInspection.h"
#include "XFlatInspectionLibrary.h"
#include "XDLLType.h"

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
	if(Pos->result==0x10000){
		L->SetMessage("広域面積");
	}
	else
	if(Pos->result==0x20001){
		L->SetMessage("広域長さ");
	}
	else
	if(Pos->result==0x30000){
		L->SetMessage("狭域面積");
	}
	else
	if(Pos->result==0x40001){
		L->SetMessage("狭域長さ");
	}
	else
	if(Pos->result==0x50000){
		L->SetMessage("多点判定");
	}
	else
	if(Pos->result==0x10500){
		L->SetMessage("赤色判定");
	}
	else
	if(Pos->result==0x10850){
		L->SetMessage("線判定");
	}

	if(L->ResultValueContainer.GetCount()>0){
		RetList.AppendList(L);
	}

	return true;
}
