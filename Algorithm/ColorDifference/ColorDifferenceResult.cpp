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

#include "ColorDifferenceResource.h"
#include "XAlgorithmDLL.h"

#include "XColorDifference.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=/**/"Need Fin";
		return false;
	}

	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	if(c!=NULL){
		RetStrBuff+=c->GetLibName();
	}

	return true;
}

DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	QString	Str;
	if((Pos->result&0xFF00)==0x000){
		DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(ColorDifferenceResult_LS,LID_15)/*"色差検査 OK/NG"*/);
		if(Pos->result==1){
			L->Add(LangSolver.GetString(ColorDifferenceResult_LS,LID_16)/*"OK"*/,Pos->GetResultDouble());
		}
		if(Pos->result==1){
			L->Add(LangSolver.GetString(ColorDifferenceResult_LS,LID_17)/*"NG"*/,Pos->GetResultDouble());
		}
		RetList.AppendList(L);
	}
	else
	if((Pos->result&0xFF00)==0x100){
		DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(ColorDifferenceResult_LS,LID_18)/*"色差検査 ΔE"*/);
		L->Add(LangSolver.GetString(ColorDifferenceResult_LS,LID_19)/*"NG"*/,Pos->GetResultDouble());
		RetList.AppendList(L);
	}
	else
	if((Pos->result&0xFF00)==0x200){
		DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(ColorDifferenceResult_LS,LID_20)/*"色差検査 HSV"*/);
		L->Add(LangSolver.GetString(ColorDifferenceResult_LS,LID_21)/*"NG"*/,Pos->GetResultDouble());
		RetList.AppendList(L);
	}

	return true;
}