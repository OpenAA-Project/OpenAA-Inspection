/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExecuteCommand\ButtonExecuteCommand.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonExecuteCommand.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ExecuteCommand";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to execute command (exe program)");
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
	return(new ButtonExecuteCommand(Base,parent));
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
	Data[0].Pointer				 =&((ButtonExecuteCommand *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonExecuteCommand *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonExecuteCommand *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonExecuteCommand *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"ExecutableProgram";
	Data[4].Pointer				 =&((ButtonExecuteCommand *)Instance)->ExecutableProgram;
	Data[5].Type				 =/**/"QStringList";
	Data[5].VariableNameWithRoute=/**/"ArgumentParam";
	Data[5].Pointer				 =&((ButtonExecuteCommand *)Instance)->ArgumentParam;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"WorkingPath";
	Data[6].Pointer				 =&((ButtonExecuteCommand *)Instance)->WorkingPath;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonExecuteCommand.png")));
}

static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Execute";
		Functions[ret].Explain.append(/**/"Execute");
		Functions[ret].DLL_ExcuteMacro	=MacroExecute;
		ret++;
	}
	return ret;
}

static bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonExecuteCommand	*V=dynamic_cast<ButtonExecuteCommand *>(Instance);
	if(V==NULL){
		return false;
	}

	V->Execute();

	return true;
}

//==================================================================================================
ButtonExecuteCommand::ButtonExecuteCommand(LayersBase *Base ,QWidget *parent)
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

ButtonExecuteCommand::~ButtonExecuteCommand(void)
{
}

void	ButtonExecuteCommand::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonExecuteCommand::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonExecuteCommand::SlotClicked (bool checked)
{
	QProcess::startDetached ( ExecutableProgram, ArgumentParam,WorkingPath);
}

void	ButtonExecuteCommand::Execute(void)
{
	SlotClicked(false);
}

void	ButtonExecuteCommand::TransmitDirectly(GUIDirectMessage *packet)
{

}
