/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\BlockInspectionResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAlgorithmDLL.h"
#include "XNickInspection.h"


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
	if((ItemRes->GetError()&0x01)!=0){
		RetStrBuff+="Master比較";
	}
	else if((ItemRes->GetError()&0x02)!=0){
		RetStrBuff+="Gap";
	}
	else if((ItemRes->GetError()&0x04)!=0){
		RetStrBuff+="Width";
	}
	return true;
}


