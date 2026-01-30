/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ExecuteBatchResource.h"

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