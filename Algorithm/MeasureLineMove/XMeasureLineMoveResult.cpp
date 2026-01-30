/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "XMeasureLineMoveResource.h"

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