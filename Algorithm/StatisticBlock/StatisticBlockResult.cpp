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
#include "StatisticBlock.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "StatisticHistogramForm.h"
#include "StatisticBlockResource.h"
#include "XDLLType.h"
//#include "ChangeShiftForm.h"	// excerpt from BlockInspectionResult.cpp


DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItemRoot();
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	if((ItemRes->GetError()&0x0f)==2){
		RetStrBuff+="ブロック統計";
	}
	if((ItemRes->GetError()&0xF0)==0x10){
		RetStrBuff+=QString(" 黒")+QString::number((int)ItemRes->GetResult1());
	}
	if((ItemRes->GetError()&0xF0)==0x20){
		RetStrBuff+=QString(" 白")+QString::number((int)ItemRes->GetResult2());
	}
	return true;
}

DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	if(Pos->result==0x20000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側でNG"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側でNG"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側で輝度はＮＧ，長さはＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側で輝度はＮＧ，面積はＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x10){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("黒側で輝度はＮＧ，長さ面積ともＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側で輝度はＮＧ，長さはＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側で輝度はＮＧ，面積はＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("白側で輝度はＮＧ，長さ面積ともＯＫ"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else{
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(QString("表示エラー"));
		L->Add(QString("長さ："),Pos->GetResult2());
		L->Add(QString("面積："),Pos->GetResult1());
		L->SetColor(qRgba(127,127,127,100));
		RetList.AppendList(L);
	}

	return true;
}