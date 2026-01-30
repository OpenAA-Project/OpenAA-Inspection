/*
 * Copyright (C) 2025
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

