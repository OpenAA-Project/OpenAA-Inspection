/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShowInPlayer\ButtonShowInPlayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonShowInPlayer.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include "XDoubleClass.h"
#include "swap.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ShowInPlayer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to execute ShowInPlayer function");
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
	return(new ButtonShowInPlayer(Base,parent));
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
	Data[0].Pointer				 =&((ButtonShowInPlayer *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonShowInPlayer *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonShowInPlayer *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonShowInPlayer *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"GUIInst";
	Data[4].Pointer				 =&((ButtonShowInPlayer *)Instance)->GUIInst;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShowInPlayer.png")));
}

//==================================================================================================
ButtonShowInPlayer::ButtonShowInPlayer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ShowInPlayerFunc");
	Msg=/**/"ShowInPlayer";
	LastShownInspectionID=0;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonShowInPlayer::~ButtonShowInPlayer(void)
{
}

void	ButtonShowInPlayer::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setChecked(GetLayersBase()->IsEnableFilter());
	ResizeAction();
}

void	ButtonShowInPlayer::ResizeAction()
{
	Button.resize(width(),height());
}
void	ButtonShowInPlayer::ShowInPlayer(int64 shownInspectionID)
{
	LastShownInspectionID=shownInspectionID;
}

void ButtonShowInPlayer::SlotClicked (bool checked)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(GUIInst);
	if(f!=NULL){
		f->ShowInPlayer(LastShownInspectionID);
	}
}
