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
#include "BlockInspection.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "HistogramForm.h"
#include "BlockFormResource.h"
#include "ChangeShiftForm.h"
#include <stdlib.h>
#include "XGeneralFunc.h"
#include "XDLLType.h"

static	char	*SetTextFromString(char *fp, int& ByteOfStrBuff, const QString& Text)
{
	char	Buff[10000];
	::QString2Char(Text, Buff, sizeof(Buff));

	int	Len = strlen(Buff);
	ByteOfStrBuff -= Len;
	if (ByteOfStrBuff < 0)
		return NULL;
	strcpy(fp, Buff);
	fp = strchr(fp, 0);
	return fp;
}

DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuf)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuf=/**/"Need Fin";
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	RetStrBuf.clear();
	if(c!=NULL){
		RetStrBuf=c->GetLibName();
	}
	if((ItemRes->GetError()&0x0f)==3){
		RetStrBuf+=LangSolver.GetString(BlockInspectionResult_LS, LID_55)/*"狭域"*/;
	}
	else if((ItemRes->GetError()&0x0f)==2){
		RetStrBuf+=LangSolver.GetString(BlockInspectionResult_LS, LID_56)/*"広域*/;
	}
	if((ItemRes->GetError()&0x10)!=0){
		char	Buff[1000];
		::QString2Char(LangSolver.GetString(BlockInspectionResult_LS, LID_57)/*"黒%d"*/, Buff, sizeof(Buff));
		char	mbuff[20];
		sprintf(mbuff, Buff,(int)ItemRes->GetResult1());
		RetStrBuf+=QString::fromLocal8Bit(mbuff);
	}
	if((ItemRes->GetError()&0x20)!=0){
		char	Buff[1000];
		::QString2Char(LangSolver.GetString(BlockInspectionResult_LS, LID_58)/*"白%d"*/, Buff, sizeof(Buff));
		char	mbuff[20];
		sprintf(mbuff, Buff,(int)ItemRes->GetResult2());
		RetStrBuf+=QString::fromLocal8Bit(mbuff);
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
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_59)/*"狭域黒側でNG*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_60)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_61)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_62)/*"広域黒側でNG"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_63)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_64)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_65)/*"狭域白側でNG"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_66)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_67)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_68)/*"広域白側でNG"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_69)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_70)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_71)/*"狭域黒側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_72)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_73)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_74)/*"狭域黒側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_75)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_76)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x10){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_77)/*"狭域黒側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_78)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_79)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x31){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_80)/*"広域黒側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_81)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_82)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x21){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_83)/*"広域黒側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_84)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_85)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x11){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_86)/*"広域黒側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_87)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_88)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_89)/*"狭域白側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_90)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_91)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_92)/*"狭域白側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_93)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_94)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_95)/*"狭域白側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_96)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_97)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x131){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_98)/*"広域白側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_99 )/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_100)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x121){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_101)/*"広域白側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_102)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_103)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x111){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(BlockInspectionResult_LS,LID_104)/*"広域白側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_105)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(BlockInspectionResult_LS,LID_106)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,TransparentLevel));
		RetList.AppendList(L);
	}
	return true;
}
