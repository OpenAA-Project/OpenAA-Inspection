/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\OutlineInspection\OutlineResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAlgorithmDLL.h"
#include "XOutlineInspect.h"


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
	if((ItemRes->GetError()&0x010)!=0){
		RetStrBuff+=QString(" InN")+QString::number((int)(ItemRes->GetResult1()>>16));
	}
	if((ItemRes->GetError()&0x020)!=0){
		RetStrBuff+=QString(" OutN")+QString::number((int)(ItemRes->GetResult2()>>16));
	}
	if((ItemRes->GetError()&0x040)!=0){
		RetStrBuff+=QString(" InB")+QString::number((int)(ItemRes->GetResult1()&0xFFFF));
	}
	if((ItemRes->GetError()&0x080)!=0){
		RetStrBuff+=QString(" OutB")+QString::number((int)(ItemRes->GetResult2()&0xFFFF));
	}
	return true;
}


