#include "CheckEverydayResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\KDSBeltInspection\KDSBeltInspectionResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlgorithmDLL.h"
#include "XCheckEveryday.h"
#include "XDLLType.h"

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=LangSolver.GetString(XCheckEverydayResult_LS,LID_5)/*"Need Fin"*/;
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
	L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_6)/*"NG"*/);
	int		TransparentLevel=100;
	if(Pos->result==(0x10000+1)){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_7)/*"輝度値が低い"*/);
		L->Add(LangSolver.GetString(XCheckEverydayResult_LS,LID_8)/*"輝度値："*/,Pos->GetResultDouble());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	if(Pos->result==(0x10000+2)){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_9)/*"輝度値が高い"*/);
		L->Add(LangSolver.GetString(XCheckEverydayResult_LS,LID_10)/*"長さ："*/,Pos->GetResultDouble());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else
	if(Pos->result==(0x10000+0x10)){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_11)/*"ピント値が低い"*/);
		L->Add(LangSolver.GetString(XCheckEverydayResult_LS,LID_12)/*"ピントレベル："*/,Pos->GetResultDouble());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}

	return true;
}
