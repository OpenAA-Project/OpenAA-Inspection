//#include "ShiftMarkResource.h"
#include "XAlgorithmDLL.h"

#include "XShiftMark.h"
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
	AlgorithmBase	*ABase=aitem->GetParentBase();
	if(ABase!=NULL){
		AlgorithmLibraryList	*c=ABase->FindLibFromCache(aitem->GetLibID());
		if(c!=NULL){
			RetStrBuff+=c->GetLibName();
		}
	}

	return true;
}

DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos 
										 ,DetailResultInfoListContainer &RetList)
{
	QString	Str;
	//if((Pos->result&0xFF00)==0x000){
	//	DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(ShiftMarkResult_LS,LID_15)/*"F·ŒŸ¸ OK/NG"*/);
	//	if(Pos->result==1){
	//		L->Add(LangSolver.GetString(ShiftMarkResult_LS,LID_16)/*"OK"*/,Pos->GetResultDouble());
	//	}
	//	if(Pos->result==1){
	//		L->Add(LangSolver.GetString(ShiftMarkResult_LS,LID_17)/*"NG"*/,Pos->GetResultDouble());
	//	}
	//	RetList.AppendList(L);
	//}
	//else
	//if((Pos->result&0xFF00)==0x100){
	//	DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(ShiftMarkResult_LS,LID_18)/*"F·ŒŸ¸ ƒ¢E"*/);
	//	L->Add(LangSolver.GetString(ShiftMarkResult_LS,LID_19)/*"NG"*/,Pos->GetResultDouble());
	//	RetList.AppendList(L);
	//}
	//else
	//if((Pos->result&0xFF00)==0x200){
	//	DetailResultInfoList	*L=new DetailResultInfoList(LangSolver.GetString(ShiftMarkResult_LS,LID_20)/*"F·ŒŸ¸ HSV"*/);
	//	L->Add(LangSolver.GetString(ShiftMarkResult_LS,LID_21)/*"NG"*/,Pos->GetResultDouble());
	//	RetList.AppendList(L);
	//}

	return true;
}
