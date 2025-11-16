/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\StatisticBlockResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAlgorithmDLL.h"
#include "StatisticBlock.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "StatisticHistogramForm.h"
#include "StatisticBlockResource.h"
#include "XDLLType.h"
//#include "ChangeShiftForm.h"	// excerpt from BlockInspectionResult.cpp


DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItemRoot();
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	if((ItemRes->GetError()&0x0f)==2){
		RetStrBuff+="ブロック統計";
	}
	if((ItemRes->GetError()&0xF0)==0x10){
		RetStrBuff+=QString(" 黒")+QString::number((int)ItemRes->GetResult1());
	}
	if((ItemRes->GetError()&0xF0)==0x20){
		RetStrBuff+=QString(" 白")+QString::number((int)ItemRes->GetResult2());
	}
	return true;
}

DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	if(Pos->result==0x20000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側でNG"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側でNG"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側で輝度はＮＧ，長さはＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側で輝度はＮＧ，面積はＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x10){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側で輝度はＮＧ，長さ面積ともＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側で輝度はＮＧ，長さはＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側で輝度はＮＧ，面積はＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側で輝度はＮＧ，長さ面積ともＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else{
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("表示エラー"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(127,127,127,100));
		RetList.AppendList(L);
	}

	return true;
}
