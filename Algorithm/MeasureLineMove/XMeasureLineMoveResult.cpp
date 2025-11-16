#include "XMeasureLineMoveResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureLineMove\MeasureLineMoveResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureLineMove.h"
#include "omp.h"
#include "XDrawFunc.h"
#include "XResult.h"
#include "XAlgorithmDLL.h"

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=LangSolver.GetString(XMeasureLineMoveResult_LS,LID_19)/*"Need Fin"*/;
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	//if((ItemRes->GetError()&0xFF)!=0){
	//	RetStrBuff+=QString::asprintf(/**/"Length:%.2lf",ItemRes->GetResultDouble());
	//}
	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	//LayersBase	*LBase=Item->GetLayersBase();
	//int		TransparentLevel=100;
	//if(LBase!=NULL){
	//	if(LBase->GetParamGlobal()!=NULL){
	//		TransparentLevel=LBase->GetParamGlobal()->NGColorTranparency;
	//	}
	//}
	if(Pos->result==0x10000){
		DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(XMeasureLineMoveResult_LS,LID_20)/*"間隔"*/);
		L->Add(LangSolver.GetString(XMeasureLineMoveResult_LS,LID_21)/*"間隔"*/,Pos->GetResultDouble());
		RetList.AppendList(L);
	}
	
	return true;
}
