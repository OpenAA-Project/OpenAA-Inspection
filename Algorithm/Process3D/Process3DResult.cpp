/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Process3D\Process3DResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "Process3DResource.h"
#include "XAlgorithmDLL.h"
#include "XProcess3D.h"
#include "XProcess3DLibrary.h"
#include "Process3DHistgramForm.h"


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
	if((ItemRes->GetError()&0x0f)==5){
		RetStrBuff+="Hole Shift";
	}
	else if((ItemRes->GetError()&0x0f)==4){
		RetStrBuff+="Hole Diameter";
	}
	else if((ItemRes->GetError()&0x0f)==3){
		RetStrBuff+="Ring";
	}
	else if((ItemRes->GetError()&0x0f)==6){
		RetStrBuff+="Ring";
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
	//if(Pos->result==0x10001){
	//	RetList.append(QString("HoleShift"));
	//	RetList.append(QString("Shift")+QString::number(Pos->GetResult1()));
	//	NGColor=qRgba(255,0,0,TransparentLevel);
	//}
	//if(Pos->result==0x10002){
	//	RetList.append(QString("HoleDiameter"));
	//	RetList.append(QString("Diameter")+QString::number(Pos->GetResult1()));
	//	NGColor=qRgba(255,0,0,TransparentLevel);
	//}
	//if(Pos->result==0x10005){
	//	RetList.append(QString("Ring"));
	//	RetList.append(QString("HoleDiameter")+QString::number(Pos->GetResult1()));
	//	NGColor=qRgba(255,0,0,TransparentLevel);
	//}
	//if(Pos->result==0x10003){
	//	RetList.append(QString("Ring"));
	//	NGColor=qRgba(255,0,0,TransparentLevel);
	//}
	return true;
}
