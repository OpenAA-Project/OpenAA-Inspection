/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\TrueColorBlockResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XTrueColorBlockResource.h"
#include "TrueColorBlock.h"
#include "XAlgorithmDLL.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "TrueColorHistgramForm.h"
#include "TrueColorChangeShiftForm.h"
#include "XGeneralFunc.h"

static	char* SetTextFromString(char* fp, int& ByteOfStrBuff, const QString& Text)
{
	char	Buff[10000];
	::QString2Char(Text, Buff, sizeof(Buff));

	int	Len = strlen(Buff);
	ByteOfStrBuff -= Len;
	if (ByteOfStrBuff < 0)
		return NULL;
	strcpy(fp, Buff);
	fp = strchr(fp, 0);
	return fp;
}

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=/**/"Need Fin";
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	if((ItemRes->GetError()&0x0f)==3){
		RetStrBuff+=LangSolver.GetString(TrueColorBlockResult_LS, LID_30)/*"狭域"*/;
	}
	else if((ItemRes->GetError()&0x0f)==2){
		RetStrBuff+=LangSolver.GetString(TrueColorBlockResult_LS, LID_31)/*"広域"*/;
	}
	return true;
}

DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList)
{
	if(Pos->result==0x20000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_32)/*"狭域でNG"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_33)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_34)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_35)/*"広域でNG"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_36)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_37)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_38)/*"狭域で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_39)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_40)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_41)/*"狭域で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_42)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_43)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x10){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_44)/*"狭域で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_45)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_46)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x31){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_47)/*"広域で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_48)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_49)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x21){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_50)/*"広域で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_51)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_52)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x11){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(TrueColorBlockResult_LS,LID_53)/*"広域で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_54)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(TrueColorBlockResult_LS,LID_55)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	return true;
}
