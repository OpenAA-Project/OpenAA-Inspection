/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\EulerRingL1Result.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "EulerRingL1Resource.h"
#include "XAlgorithmDLL.h"
#include "XEulerRingL1.h"
#include "XEulerRingL1Library.h"
#include "EulerRingL1HistgramForm.h"


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
	if((ItemRes->GetError()&0x0f)==5){
		RetStrBuff+="Hole Shift";
	}
	else if((ItemRes->GetError()&0x0f)==4){
		RetStrBuff+="Hole Diameter";
	}
	else if((ItemRes->GetError()&0x0f)==3){
		RetStrBuff+="Ring";
	}
	else if((ItemRes->GetError()&0x0f)==6){
		RetStrBuff+="Ring";
	}
	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	LayersBase	*LBase=Item->GetLayersBase();
	int		TransparentLevel=100;
	if(LBase!=NULL){
		if(LBase->GetParamGlobal()!=NULL){
			TransparentLevel=LBase->GetParamGlobal()->NGColorTranparency;
		}
	}
	if(Pos->result==0x10001){
		DetailResultInfoList	*L=new DetailResultInfoList("HoleShift");
		L->Add(QString("Shift"),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	if(Pos->result==0x10002){
		DetailResultInfoList	*L=new DetailResultInfoList("HoleDiameter");
		L->Add(QString("Diameter"),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	if(Pos->result==0x10005){
		DetailResultInfoList	*L=new DetailResultInfoList("Ring");
		L->Add(QString("HoleDiameter"),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	if(Pos->result==0x10003){
		DetailResultInfoList	*L=new DetailResultInfoList("Ring");
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	return true;
}
