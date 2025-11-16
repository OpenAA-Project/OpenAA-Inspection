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
#include "XLinePatternInspection.h"

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
	if((ItemRes->GetError()&0x10)!=0){
		RetStrBuff+="InsideLow/";
	}
	if((ItemRes->GetError()&0x20)!=0){
		RetStrBuff+="InsideHigh/";
	}
	if((ItemRes->GetError()&0x40)!=0){
		RetStrBuff+="OutsideLow/";
	}
	else if((ItemRes->GetError()&0x80)!=0){
		RetStrBuff+="OutsideHigh";
	}
	return true;
}


