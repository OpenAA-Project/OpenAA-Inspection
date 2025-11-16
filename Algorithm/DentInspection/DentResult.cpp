/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Dent\DentResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "DentResource.h"
#include "XAlgorithmDLL.h"
#include "XDentInspection.h"
#include "XDentLibrary.h"
#include "DentHistgramForm.h"


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
	/*
	if((ItemRes->GetError()&0x0f)==5){
		char	*txt="Hole Shift";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	else if((ItemRes->GetError()&0x0f)==4){
		char	*txt="Hole Diameter";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	else if((ItemRes->GetError()&0x0f)==3){
		char	*txt="Ring";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	else if((ItemRes->GetError()&0x0f)==6){
		char	*txt="Ring";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	*/
	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList)
{
	//QString	Str;
	//if((Pos->result&0xFF00)==0x000){
	//	Str="OK/NG";
	//}
	//else
	//if((Pos->result&0xFF00)==0x100){
	//	Str="ƒ¢E";
	//}
	//else
	//if((Pos->result&0xFF00)==0x200){
	//	Str="HSV";
	//}
	//
	//RetList.append(Str);

	return true;
}
