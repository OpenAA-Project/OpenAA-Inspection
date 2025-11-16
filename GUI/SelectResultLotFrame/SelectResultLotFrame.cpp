/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SelectResultLotFrame\SelectResultLotFrame.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "SelectResultLotFrameResource.h"
#include "SelectResultLotFrame.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "SelectResultLotFrameDialog.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "XLotInformation.h"
#include "XResult.h"
#include "XCriticalFunc.h"

#include "ButtonAutoMode.h"
#include "ButtonToSelectResultLotFrameForm.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SelectResultLotFrame";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for select-LotFrame dialog");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqGroupList(Base ,sRoot,sName ,-1);
	(*Base)=new GUICmdAckGroupList(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonToSelectResultLotFrameForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonToSelectResultLotFrameForm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToSelectResultLotFrameForm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToSelectResultLotFrameForm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToSelectResultLotFrameForm *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SelectResultLotFrame.png")));
}

//==================================================================================================
