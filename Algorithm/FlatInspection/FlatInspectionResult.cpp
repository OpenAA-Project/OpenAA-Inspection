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

//#include "FlatInspectionResource.h"
#include "XAlgorithmDLL.h"
#include "XFlatInspection.h"
#include "XFlatInspectionLibrary.h"
#include "XDLLType.h"

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff="Need Fin";
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
	if(Pos->result==0x10000){
		L->SetMessage("広域面積");
	}
	else
	if(Pos->result==0x20001){
		L->SetMessage("広域長さ");
	}
	else
	if(Pos->result==0x30000){
		L->SetMessage("狭域面積");
	}
	else
	if(Pos->result==0x40001){
		L->SetMessage("狭域長さ");
	}
	else
	if(Pos->result==0x50000){
		L->SetMessage("多点判定");
	}
	else
	if(Pos->result==0x10500){
		L->SetMessage("赤色判定");
	}
	else
	if(Pos->result==0x10850){
		L->SetMessage("線判定");
	}

	if(L->ResultValueContainer.GetCount()>0){
		RetList.AppendList(L);
	}

	return true;
}