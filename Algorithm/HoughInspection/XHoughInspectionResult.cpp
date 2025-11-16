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
#include "XHoughInspection.h"


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

	ResultPosList	*p=ItemRes->GetPosListFirst();
	if(p!=NULL){
		double	Len=p->Vector.GetMaxLength();
		double	Width	=p->GetResult2();
		int		Pixels	=p->GetResult1();
		RetStrBuff+=QString::asprintf(/**/" Len(%.2lf) Width(%.2lf) Dots(%d)",Len,Width,Pixels);
	}
	return true;
}


