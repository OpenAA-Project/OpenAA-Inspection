/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonRaiseOtherProcess\ButtonRaiseOtherProcess.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonRaiseOtherProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XForWindows.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"RaiseOtherProcess";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to raise Other Process");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonRaiseOtherProcess(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonRaiseOtherProcess *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonRaiseOtherProcess *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonRaiseOtherProcess *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonRaiseOtherProcess *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"RaisedProcessName";
	Data[4].Pointer				 =&((ButtonRaiseOtherProcess *)Instance)->RaisedProcessName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonRaiseOtherProcess.png")));
}

static	bool	MacroRaiseProcess(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Raise";
		Functions[ret].Explain.append(/**/"Raise other process");
		Functions[ret].DLL_ExcuteMacro	=MacroRaiseProcess;
		ret++;
	}
	return ret;
}

static bool	MacroRaiseProcess(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonRaiseOtherProcess	*V=dynamic_cast<ButtonRaiseOtherProcess *>(Instance);
	if(V==NULL){
		return false;
	}

	V->SlotClicked(true);

	return true;
}


//==================================================================================================
ButtonRaiseOtherProcess::ButtonRaiseOtherProcess(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonExecuteCommand");
	Msg=/**/"Exe cmd";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonRaiseOtherProcess::~ButtonRaiseOtherProcess(void)
{
}

void	ButtonRaiseOtherProcess::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
void	ButtonRaiseOtherProcess::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonRaiseOtherProcess::SlotClicked (bool checked)
{
	DWORD ProcessID[1000];
	int		N=MtEnumProcess(ProcessID, sizeof(ProcessID)/sizeof(ProcessID[0]));
	
	for(int i=0;i<N;i++){
		QString ProcessName;
		if(GetProcessName(ProcessID[i],ProcessName)==true){
			if(ProcessName==RaisedProcessName){
				::SetForegroundOtherWindow(ProcessID[i]);
				break;
			}
		}
	}
}


