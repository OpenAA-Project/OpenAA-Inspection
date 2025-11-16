#include "ButtonToShowDialogOnGeneralStockerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonToShowDialogOnGeneralStocker\ButtonToShowDialogOnGeneralStocker.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonToShowDialogOnGeneralStocker.h"
#include "XGeneralFunc.h"
#include "SelectGeneralStocker.h"
#include "XDataInLayer.h"
#include "XGeneralStocker.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ButtonToShowDialogOnGeneralStocker";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to ShowDialog on GeneralStocker");
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
	return(new ButtonToShowDialogOnGeneralStocker(Base,parent));
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
	Data[0].Pointer				 =&((ButtonToShowDialogOnGeneralStocker *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToShowDialogOnGeneralStocker *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToShowDialogOnGeneralStocker *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToShowDialogOnGeneralStocker *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"Keyword";
	Data[4].Pointer				 =&((ButtonToShowDialogOnGeneralStocker *)Instance)->Keyword;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToShowDialogOnGeneralStocker.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================


ButtonToShowDialogOnGeneralStocker::ButtonToShowDialogOnGeneralStocker(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"GeneralStocker";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonToShowDialogOnGeneralStocker::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonToShowDialogOnGeneralStocker::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonToShowDialogOnGeneralStocker::SlotClicked (bool checked)
{
	GetLayersBase()->TmpHideProcessingForm();
	GeneralStockerShowDialog(Keyword);
	GetLayersBase()->TmpRercoverProcessingForm();
}

int		ButtonToShowDialogOnGeneralStocker::GeneralStockerShowDialog(const QString &Keyword)
{
	int	n=GetLayersBase()->GetGeneralStocker()->GetCountOfEffectiveShowDialog(Keyword);
	if(n==0){
		return -1;
	}
	else if(n==1){
		return GetLayersBase()->GetGeneralStocker()->ShowDialog(Keyword, GetLayersBase()->GetMainWidget());
	}
	else{
		NPListPack<GeneralStockerPointerList>	Dim;
		for(int i=0;i<n;i++){
			Dim.AppendList(new GeneralStockerPointerList(GetLayersBase()->GetGeneralStocker()->GetShowDialogPointer(i)));
		}
		SelectGeneralStocker	D(GetLayersBase(),Dim, GetLayersBase()->GetMainWidget());
		if(D.exec()==(int)true){
			return D.Selected->ShowDialog(Keyword, GetLayersBase()->GetMainWidget());
		}
	}
	return -1;
}