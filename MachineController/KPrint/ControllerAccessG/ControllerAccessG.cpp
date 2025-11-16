/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ControllerAccessG\ControllerAccessG.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ControllerAccessG.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "ControllerAccessGForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"ControllerAccessG";

class	ConfirmForm;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show ControllerAccessG for KidaPrint");
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
	return(new ButtonControllerAccessG(Base,parent));
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
	Data[0].Pointer				 =&((ButtonControllerAccessG *)Instance)->Msg;
	Data[0].Translatable		=true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonControllerAccessG *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonControllerAccessG *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonControllerAccessG *)Instance)->CFont;

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
	ButtonControllerAccessG	*V=dynamic_cast<ButtonControllerAccessG *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenDialog();

	return true;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ControllerAccessG.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================

ButtonControllerAccessG::ButtonControllerAccessG(LayersBase *Base ,QWidget *parent) :
	GUIFormBase(Base,parent)
{
	Window	=NULL;
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonControllerAccessG");
	Button.move(0,0);

	Msg=/**/"Control";
	resize(80,25);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
}

void	ButtonControllerAccessG::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonControllerAccessG::ResizeAction()
{
	Button.resize(width(),height());
}
void	ButtonControllerAccessG::OpenDialog(void)
{
	if(Window==NULL){
		CartonMenuForm	*f=(CartonMenuForm	*)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			Window=new ControllerAccessGForm(GetLayersBase(),f,this);
		}
	}
	if(Window==NULL){
		Window->show();
		Window->raise();
	}
}
void	ButtonControllerAccessG::SlotClicked (bool checked)
{
	OpenDialog();
}
