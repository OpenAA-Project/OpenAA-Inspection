/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveGUILanguage\ButtonSaveGUILanguage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSaveGUILanguage.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include <QFileDialog>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SaveGUILanguage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Save GUILanguage file");
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
	return(new ButtonSaveGUILanguage(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveGUILanguage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveGUILanguage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveGUILanguage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveGUILanguage *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveGUILanguage.png")));
}

//==================================================================================================

ButtonSaveGUILanguage::ButtonSaveGUILanguage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setCheckable(true);
	Msg=/**/"Save GUILanguage";

	resize(100,25);

	bool Ret1=(connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool))))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}
void	ButtonSaveGUILanguage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
void	ButtonSaveGUILanguage::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveGUILanguage::SlotClicked(bool checked)
{
    QString GLNFileName=QFileDialog::getSaveFileName(NULL,"Save GUILanguage file"
                                                    ,/**/""
                                                    ,/**/"GUI language file(*.GLN)");
    if(GLNFileName.isEmpty()==false){
        GetLayersBase()->SaveGUILanguage(GLNFileName);
    }
}
