/*
 * Copyright (C) 2023
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


#include "XAlgorithmDLL.h"
#include "VIAInspection.h"
#include "XViaInspection.h"
#include "XViaInspectionLibrary.h"
#include "HistogramForm.h"
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
	if((ItemRes->GetError()&0x10)!=0){
		RetStrBuff+=" BNG";
	}
	if((ItemRes->GetError()&0x20)!=0){
		RetStrBuff+=" WNG";
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
	if(Pos->result==0x20000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/""));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LNG-Area"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20002){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LNG-Len"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20003){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LNG-Len&Area"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}

	else if(Pos->result==0x30000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/""));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"HNG-Area"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30002){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"HNG-Len"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30003){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"HNG-Len&Area"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}

	else if(Pos->result==0x10){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LOK-Area"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LOK-Len"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LOK-Area&Len"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LOK-Area"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LOK-Len"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString(/**/"LOK-Area&Len"));
		L->Add(QString(/**/"Area:"),Pos->GetResult1());
		L->Add(QString(/**/"Len:" ),Pos->GetResult2());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	return true;
}