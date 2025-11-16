//#include "StartCaptureOnlyTargetResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureOnlyTarget\StartCaptureOnlyTarget.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "StartInspectionButtonFormResource.h"
#include "StartCaptureOnlyTarget.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"StartCaptureOnlyTarget";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to start capture into target");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdStartCaptureOnlyTarget	 (Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReplyStartCaptureOnlyTarget(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartCaptureOnlyTarget(Base,parent));
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
	Data[0].Pointer				 =&((StartCaptureOnlyTarget *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartCaptureOnlyTarget *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartCaptureOnlyTarget *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartCaptureOnlyTarget *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"WaitingMilisecForSlave";
	Data[4].Pointer				 =&((StartCaptureOnlyTarget *)Instance)->WaitingMilisecForSlave;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartCaptureOnlyTarget.png")));
}



static	bool	MacroStart(GUIFormBase *Instance ,QStringList &Args)
{
	StartCaptureOnlyTarget	*V=dynamic_cast<StartCaptureOnlyTarget *>(Instance);
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
		Functions[ret].Explain.append(/**/"Start capture");
		Functions[ret].DLL_ExcuteMacro	=MacroStart;
		ret++;
	}

	return ret;
}

//==================================================================================================
