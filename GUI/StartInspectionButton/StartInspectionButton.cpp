/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionButton\StartInspectionButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "StartInspectionButtonFormResource.h"
#include "StartInspectionButton.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"StartInspectionButton";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to start Inspection");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdStartInspect(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReplyInspect(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartInspectionButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((StartInspectionButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartInspectionButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartInspectionButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartInspectionButton *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"WaitingMilisecForSlave";
	Data[4].Pointer				 =&((StartInspectionButton *)Instance)->WaitingMilisecForSlave;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"CheckExecuteInNoMaster";
	Data[5].Pointer				 =&((StartInspectionButton *)Instance)->CheckExecuteInNoMaster;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"RegNoInFlagSet";
	Data[6].Pointer				 =&((StartInspectionButton *)Instance)->RegNoInFlagSet;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartInspectionButton.png")));
}



static	bool	MacroStart(GUIFormBase *Instance ,QStringList &Args)
{
	StartInspectionButton	*V=dynamic_cast<StartInspectionButton *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandStart();

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Start";
		Functions[ret].Explain.append(/**/"Start inspection");
		Functions[ret].DLL_ExcuteMacro	=MacroStart;
		ret++;
	}

	return ret;
}

//==================================================================================================
