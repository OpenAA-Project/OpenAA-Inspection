#include "ExecuteBatchResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ExecuteBatch\ExecuteBatch.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ExecuteBatch.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "ExecuteBatchForm.h"
#include "swap.h"
#include "XGUIDLL.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"ExecuteBatch";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show batch(macro)-list to execute");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdSendExecuteBatch(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ExecuteBatchForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);


	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ExecuteBatch.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

static	bool	MacroWait(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMessage(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCloseMessage(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Wait";
		Functions[ret].Explain.append(/**/"Wait milisec");
		Functions[ret].ArgName.append(/**/"waiting time");
		Functions[ret].DLL_ExcuteMacro	=MacroWait;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShowMessage";
		Functions[ret].Explain.append(/**/"Show message without input");
		Functions[ret].ArgName.append(/**/"message text");
		Functions[ret].DLL_ExcuteMacro	=MacroMessage;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MessageOff";
		Functions[ret].Explain.append(/**/"Close message window");
		Functions[ret].DLL_ExcuteMacro	=MacroCloseMessage;
		ret++;
	}

	return ret;
}


static	bool	MacroWait(GUIFormBase *Instance ,QStringList &Args)
{
	ExecuteBatchForm	*V=dynamic_cast<ExecuteBatchForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	WaitMiliSec=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->Sleep(WaitMiliSec);

	return true;
}

static	bool	MacroMessage(GUIFormBase *Instance ,QStringList &Args)
{
	ExecuteBatchForm	*V=dynamic_cast<ExecuteBatchForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	V->ShowMessage(Args[0]);

	return true;
}

static	bool	MacroCloseMessage(GUIFormBase *Instance ,QStringList &Args)
{
	ExecuteBatchForm	*V=dynamic_cast<ExecuteBatchForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CloseMessage();

	return true;
}