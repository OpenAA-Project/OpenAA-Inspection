#include "DotColorMatchingResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotColorMatching\DotColorMatchingResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlgorithmDLL.h"
#include "XDotColorMatching.h"
#include "XDotColorMatchingLibrary.h"
#include "XDLLType.h"

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=LangSolver.GetString(DotColorMatchingResult_LS,LID_13)/*"Need Fin"*/;
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
	if((Pos->result&0xFF00)==0x100){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_14)/*"単色"*/);
	}
	else
	if((Pos->result&0xFF00)==0x200){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_15)/*"グラデ*/);
	}
	else
	if((Pos->result&0xFF00)==0x300){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_16)/*文字*/);
	}
	else
	if((Pos->result&0xFF00)==0x400){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_19)/*無地*/);
	}
	else
	if((Pos->result&0xFF00)==0x500){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_63)/*赤色*/);
	}
	else
	if((Pos->result&0xFF00)==0x600){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_82)/*"HSV面積*/);
	}
	else
	if((Pos->result&0xFF00)==0x700){
		L->SetMessage(LangSolver.GetString(DotColorMatchingResult_LS,LID_83)/*"HSV長さ*/);
	}
	else
	if((Pos->result&0xFF00)==0x800){
		L->SetMessage("線不良");
	}

	if((Pos->result&0xFF)==0x00){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_64)/*"-面積*/,Pos->GetResult1());
	}
	else
	if((Pos->result&0xFF)==0x02){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_65)/*"-長さ*/,Pos->GetResult2());
	}
	else
	if((Pos->result&0xFF)==0x10){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_66)/*"-背景面積*/,Pos->GetResult1());
	}
	else
	if((Pos->result&0xFF)==0x12){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_67)/*"-背景長さ*/,Pos->GetResult2());
	}
	else
	if((Pos->result&0xFF)==0x01){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_68)/*-多点*/,Pos->GetResult1());
	}
	else
	if((Pos->result&0xFF)==0x02){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_69)/*-グレイ*/,Pos->GetResult1());
	}
	else
	if((Pos->result&0xFF)==0x21){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_84)/*-密集多点*/,Pos->GetResult1());
	}
	else
	if((Pos->result&0xFF)==0x30){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_260)/*"バラつきR"*/,Pos->GetResultDouble());
	}
	else
	if((Pos->result&0xFF)==0x31){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_261)/*"バラつきG"*/,Pos->GetResultDouble());
	}
	else
	if((Pos->result&0xFF)==0x32){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_262)/*"バラつきB"*/,Pos->GetResultDouble());
	}
	else
	if((Pos->result&0xFF)==0x50){
		L->Add(LangSolver.GetString(DotColorMatchingResult_LS,LID_132)/*"線不良"*/,Pos->GetResult2());
	}

	if(L->ResultValueContainer.GetCount()>0){
		RetList.AppendList(L);
	}

	return true;
}
