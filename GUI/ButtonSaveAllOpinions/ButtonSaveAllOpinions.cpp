/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveAllOpinions\ButtonSaveAllOpinions.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSaveAllOpinionsResource.h"
#include "ButtonSaveAllOpinions.h"
#include "XStatusController.h"

#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveAllOpinions";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save Status opinions with comments");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonSaveAllOpinions(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveAllOpinions *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveAllOpinions *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveAllOpinions *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveAllOpinions *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveAllOpinions.png")));
}

//==================================================================================================
ButtonSaveAllOpinions::ButtonSaveAllOpinions(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save Opinions";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSaveAllOpinions::~ButtonSaveAllOpinions(void)
{
}

void	ButtonSaveAllOpinions::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveAllOpinions::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveAllOpinions::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetSaveFileName (this
									, LangSolver.GetString(ButtonSaveAllOpinions_LS,LID_0)/*"Save opinions"*/
									, GetLayersBase()->GetStatusController()->GetDefaultFileName()
									, /**/"Opinion (*.dat);;All files (*.*)");
	if(FileName.isEmpty()==false){
		GetLayersBase()->GetStatusController()->SaveDef(FileName);
	}
}
void	ButtonSaveAllOpinions::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSaveAllOpinions_LS,LID_1)/*"FILE"*/,LangSolver.GetString(ButtonSaveAllOpinions_LS,LID_2)/*"Save All opinions"*/,this);
	p->SetMenuNumber(5010);
	Info.AppendList(p);
}
void	ButtonSaveAllOpinions::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
