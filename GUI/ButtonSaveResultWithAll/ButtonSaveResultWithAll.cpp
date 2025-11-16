#include "ButtonSaveResultWithAllResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveResultWithAll\ButtonSaveResultWithAll.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSaveResultWithAll.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveResultWithAll";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save ResultWithAll");
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
	return(new ButtonSaveResultWithAll(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveResultWithAll *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveResultWithAll *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveResultWithAll *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveResultWithAll *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileName";
	Data[4].Pointer				 =&((ButtonSaveResultWithAll *)Instance)->FileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveResultWithAll.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveResultWithAll	*V=dynamic_cast<ButtonSaveResultWithAll *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SaveRWA(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save RWA");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSaveResultWithAll::ButtonSaveResultWithAll(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save ResultWithAll";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonSaveResultWithAll::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveResultWithAll::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSaveResultWithAll::SlotClicked (bool checked)
{
	QString	LFileName;
	if(FileName.isEmpty()==true){
		LFileName=GetLayersBase()->LGetSaveFileName (this
									, LangSolver.GetString(ButtonSaveResultWithAll_LS,LID_0)/*"Save ResultWithAll"*/
									, QString()
									, tr(/**/"RWA File (*.rwa)") );
	}
	else{
		LFileName=FileName;
	}
	SaveRWA(LFileName);
}

bool	ButtonSaveResultWithAll::SaveRWA(QString LFileName)
{
	QFile	FL(LFileName);

	if(FL.open(QIODevice::WriteOnly)==false)
		return false;

	if(GetLayersBase()->SavePixWithAlgorithm(&FL)==false){
		return false;
	}
	if(GetLayersBase()->SaveResult(&FL)==false){
		return false;
	}
	return true;
}

