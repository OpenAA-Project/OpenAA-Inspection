#include "StartInspectionWithoutCaptureResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionWithoutCapture\StartInspectionWithoutCapture.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "StartInspectionButtonFormResource.h"
#include "StartInspectionWithoutCapture.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"StartInspectionWithoutCapture";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to start Inspection without capture");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdStartInspectWithoutCapture(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReplyInspectWithoutCapture(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartInspectionWithoutCapture(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((StartInspectionWithoutCapture *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartInspectionWithoutCapture *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartInspectionWithoutCapture *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartInspectionWithoutCapture *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"WaitingMilisecForSlave";
	Data[4].Pointer				 =&((StartInspectionWithoutCapture *)Instance)->WaitingMilisecForSlave;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"CheckExecuteInNoMaster";
	Data[5].Pointer				 =&((StartInspectionWithoutCapture *)Instance)->CheckExecuteInNoMaster;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartInspectionWithoutCapture.png")));
}



static	bool	MacroStart(GUIFormBase *Instance ,QStringList &Args)
{
	StartInspectionWithoutCapture	*V=dynamic_cast<StartInspectionWithoutCapture *>(Instance);
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
