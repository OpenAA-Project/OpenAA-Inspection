/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorBlockInspectionResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ColorBlockInspection.h"
#include "XAlgorithmDLL.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "ColorHistogramForm.h"
#include "ColorBlockFormResource.h"
#include "ColorChangeShiftForm.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"

static	char* SetTextFromString(char* fp, int& ByteOfStrBuff, const QString& Text)
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
	if((ItemRes->GetError()&0x0f)==3){
		RetStrBuff+=LangSolver.GetString(ColorBlockInspectionResult_LS, LID_80)/*" 狭域"*/;
	}
	else if((ItemRes->GetError()&0x0f)==2){
		RetStrBuff+=LangSolver.GetString(ColorBlockInspectionResult_LS, LID_81)/*" 広域"*/;
	}
	if((ItemRes->GetError()&0x10)!=0){
		char	Buff[1000];
		::QString2Char(LangSolver.GetString(ColorBlockInspectionResult_LS, LID_82)/*" 黒%d"*/, Buff, sizeof(Buff));
		char	mbuff[20];
		sprintf(mbuff, Buff,(int)ItemRes->GetResult1());
		RetStrBuff+=QString::fromLocal8Bit(mbuff);
	}
	if((ItemRes->GetError()&0x20)!=0){
		char	Buff[1000];
		::QString2Char(LangSolver.GetString(ColorBlockInspectionResult_LS, LID_83)/*" 白%d"*/, Buff, sizeof(Buff));
		char	mbuff[20];
		sprintf(mbuff, Buff,(int)ItemRes->GetResult2());
		RetStrBuff+=QString::fromLocal8Bit(mbuff);
	}
	return true;
}
DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList)
{
	if(Pos->result==0x20000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_84)/*"狭域黒側ＲでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_85)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_86)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_87)/*"広域黒側ＲでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_88)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_89)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_90)/*"狭域白側ＲでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_91)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_92)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_93)/*"広域白側ＲでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_94)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_95)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x30){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_96)/*"狭域黒側Ｒで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_97)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_98)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x20){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_99)/*"狭域黒側Ｒで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_100)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_101)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x10){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_102)/*"狭域黒側Ｒで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_103)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_104)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x31){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_105)/*"広域黒側Ｒで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_106)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_107)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x21){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_108)/*"広域黒側Ｒで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_109)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_110)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x11){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_111)/*"広域黒側Ｒで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_112)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_113)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_114)/*"狭域白側Ｒで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_115)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_116)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_117)/*"狭域白側Ｒで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_118)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_119)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_120)/*"狭域白側Ｒで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_121)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_122)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x131){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_123)/*"広域白側Ｒで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_124)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_125)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x121){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_126)/*"広域白側Ｒで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_127)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_128)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x111){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_129)/*"広域白側Ｒで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_130)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_131)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}

	else if(Pos->result==0x120000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_132)/*"狭域黒側ＧでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_133)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_134)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x120001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_135)/*"広域黒側ＧでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_136)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_137)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_138)/*"狭域白側ＧでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_139)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_140)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x130001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_141)/*"広域白側ＧでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_142)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_143)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1030){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_144)/*"狭域黒側Ｇで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_145)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_146)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1020){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_147)/*"狭域黒側Ｇで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_148)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_149)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1010){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_150)/*"狭域黒側Ｇで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_151)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_152)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1031){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_153)/*"広域黒側Ｇで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_154)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_155)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1021){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_156)/*"広域黒側Ｇで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_157)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_158)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1011){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_159)/*"広域黒側Ｇで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_160)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_161)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_162)/*"狭域白側Ｇで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_163)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_164)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_165)/*"狭域白側Ｇで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_166)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_167)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_168)/*"狭域白側Ｇで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_169)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_170)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1131){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_171)/*"広域白側Ｇで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_172)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_173)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1121){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_174)/*"広域白側Ｇで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_175)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_176)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x1111){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_177)/*"広域白側Ｇで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_178)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_179)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}

	else if(Pos->result==0x220000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_180)/*"狭域黒側ＢでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_181)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_182)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x220001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_183)/*"広域黒側ＢでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_184)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_185)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x230000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_186)/*"狭域白側ＢでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_187)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_188)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x230001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_189)/*"広域白側ＢでNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_190)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_191)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2030){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_192)/*"狭域黒側Ｂで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_193)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_194)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2020){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_195)/*"狭域黒側Ｂで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_196)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_197)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2010){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_198)/*"狭域黒側Ｂで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_199)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_200)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2031){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_201)/*"広域黒側Ｂで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_202)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_203)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2021){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_204)/*"広域黒側Ｂで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_205)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_206)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2011){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_207)/*"広域黒側Ｂで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_208)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_209)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2130){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_210)/*"狭域白側Ｂで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_211)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_212)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2120){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_213)/*"狭域白側Ｂで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_214)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_215)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2110){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_216)/*"狭域白側Ｂで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_217)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_218)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2131){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_219)/*"広域白側Ｂで輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_220)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_221)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2121){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_222)/*"広域白側Ｂで輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_223)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_224)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x2111){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_225)/*"広域白側Ｂで輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_226)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_227)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}

	else if(Pos->result==0x40000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_228)/*"狭域黒側でNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_229)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_230)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x40001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_231)/*"広域黒側でNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_232)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_233)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x50000){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_234)/*"狭域白側でNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_235)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_236)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(255,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x50001){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_237)/*"広域白側でNG"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_238)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_239)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,0,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x60){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_240)/*"狭域黒側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_241)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_242)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x50){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_243)/*"狭域黒側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_244)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_245)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x40){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_246)/*"狭域黒側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_247)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_248)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x61){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_249)/*"広域黒側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_250)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_251)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x51){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_252)/*"広域黒側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_253)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_254)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x41){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_255)/*"広域黒側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_256)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_257)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x160){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_258)/*"狭域白側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_259)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_260)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x150){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_261)/*"狭域白側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_262)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_263)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x140){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_264)/*"狭域白側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_265)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_266)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x161){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_267)/*"広域白側で輝度はＮＧ，長さはＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_268)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_269)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x151){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_270)/*"広域白側で輝度はＮＧ，面積はＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_271)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_272)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	else if(Pos->result==0x141){
		DetailResultInfoList	*L=new DetailResultInfoList();
		L->SetMessage(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_273)/*"広域白側で輝度はＮＧ，長さ面積ともＯＫ"*/);
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_274)/*"長さ："*/,Pos->GetResult2());
		L->Add(LangSolver.GetString(ColorBlockInspectionResult_LS,LID_275)/*"面積："*/,Pos->GetResult1());
		L->SetColor(qRgba(160,255,0,100));
		RetList.AppendList(L);
	}
	return true;
}
