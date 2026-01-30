/*
 * Copyright (C) 2024
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

#include "CheckEverydayResource.h"
#include "XAlgorithmDLL.h"
#include "XCheckEveryday.h"
#include "XDLLType.h"

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=LangSolver.GetString(XCheckEverydayResult_LS,LID_5)/*"Need Fin"*/;
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	QString	Str;
	DetailResultInfoList	*L=new DetailResultInfoList();
	L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_6)/*"NG"*/);
	int		TransparentLevel=100;
	if(Pos->result==(0x10000+1)){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_7)/*"輝度値が低い"*/);
		L->Add(LangSolver.GetString(XCheckEverydayResult_LS,LID_8)/*"輝度値："*/,Pos->GetResultDouble());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	if(Pos->result==(0x10000+2)){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_9)/*"輝度値が高い"*/);
		L->Add(LangSolver.GetString(XCheckEverydayResult_LS,LID_10)/*"長さ："*/,Pos->GetResultDouble());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else
	if(Pos->result==(0x10000+0x10)){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(XCheckEverydayResult_LS,LID_11)/*"ピント値が低い"*/);
		L->Add(LangSolver.GetString(XCheckEverydayResult_LS,LID_12)/*"ピントレベル："*/,Pos->GetResultDouble());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}

	return true;
}