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


#include "ControllerAccessSelf.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "ControllerAccessSelfForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"ControllerAccessSelf";

class	ConfirmForm;

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show ControllerAccessSelf");
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
	return(new ButtonControllerAccessSelf(Base,parent));
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
	Data[0].Pointer				 =&((ButtonControllerAccessSelf *)Instance)->Msg;
	Data[0].Translatable		=true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonControllerAccessSelf *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonControllerAccessSelf *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonControllerAccessSelf *)Instance)->CFont;

	return(4);
}
static	bool	MacroOpenDialog		(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenDialog";
		Functions[ret].Explain.append(/**/"Open Dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenDialog;
		ret++;
	}

	return ret;
}

static bool	MacroOpenDialog(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonControllerAccessSelf	*V=dynamic_cast<ButtonControllerAccessSelf *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenDialog();

	return true;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ControllerAccessSelf.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================

ButtonControllerAccessSelf::ButtonControllerAccessSelf(LayersBase *Base ,QWidget *parent) :
	GUIFormBase(Base,parent)
{
	Window	=NULL;
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonControllerAccessSelf");
	Button.move(0,0);

	Msg=/**/"Control";
	resize(80,25);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
}

void	ButtonControllerAccessSelf::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonControllerAccessSelf::ResizeAction()
{
	Button.resize(width(),height());
}
void	ButtonControllerAccessSelf::OpenDialog(void)
{
	if(Window==NULL){
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			Window=new ControllerAccessSelfForm(GetLayersBase(),f,this);
		}
	}
	if(Window==NULL){
		Window->show();
		Window->raise();
	}
}
void	ButtonControllerAccessSelf::SlotClicked (bool checked)
{
	OpenDialog();
}