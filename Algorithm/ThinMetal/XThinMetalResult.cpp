/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ThinMetal\XThinMetalResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlgorithmDLL.h"
#include "XThinMetal.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"

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
	if((ItemRes->GetError()&0xFF)!=0){
		ResultPosList	*r=ItemRes->GetPosListFirst();
		if(r!=NULL && r->Message!=/**/""){
			RetStrBuff+=r->Message;
		}
		else{
			RetStrBuff+=" Metal";
		}
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
	DetailResultInfoList	*L=new DetailResultInfoList();
	L->Add(QString("Matching:"),Pos->GetResult1());
	L->Add(QString("Sample:"  ),Pos->GetResult2());
	RetList.AppendList(L);

	return true;
}
