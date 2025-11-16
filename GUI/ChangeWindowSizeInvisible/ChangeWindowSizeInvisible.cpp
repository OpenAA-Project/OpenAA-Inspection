#include "ChangeWindowSizeInvisibleResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ChangeWindowSizeInvisible\ChangeWindowSizeInvisible.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ChangeWindowSizeInvisible.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XDisplayImage.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"ChangeWindowSize";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Change Window size in each action");
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
	return(new ChangeWindowSizeInvisible(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"MaximizeWindowOnStartPage";
	Data[0].Pointer				 =&((ChangeWindowSizeInvisible *)Instance)->MaximizeWindowOnStartPage;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ReturnWindowSizewOnStartPage";
	Data[1].Pointer				 =&((ChangeWindowSizeInvisible *)Instance)->ReturnWindowSizewOnStartPage;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"MaximizeWindowOnLeavePage";
	Data[2].Pointer				 =&((ChangeWindowSizeInvisible *)Instance)->MaximizeWindowOnLeavePage;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ReturnWindowSizewOnLeavePage";
	Data[3].Pointer				 =&((ChangeWindowSizeInvisible *)Instance)->ReturnWindowSizewOnLeavePage;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ChangeWindowSizeInvisible.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ChangeWindowSizeInvisible::ChangeWindowSizeInvisible(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MaximizeWindowOnStartPage	=false;
	ReturnWindowSizewOnStartPage=false;
	MaximizeWindowOnLeavePage	=false;
	ReturnWindowSizewOnLeavePage=false;

	CurrentMaxSizeW=16777215;
	CurrentMaxSizeH=16777215;

}

ChangeWindowSizeInvisible::~ChangeWindowSizeInvisible(void)
{
}

void	ChangeWindowSizeInvisible::Prepare(void)
{

}


void	ChangeWindowSizeInvisible::StartPage	(void)
{
	if(MaximizeWindowOnStartPage==true){
		QWidget	*W=GetLayersBase()->GetMainWidget();
		if(W!=NULL){
			int	SzH=W->maximumHeight();
			int	SzW=W->maximumWidth();
			if(SzH!=16777215 && SzW!=16777215){
				CurrentMaxSizeW=SzW;
				CurrentMaxSizeH=SzH;
			}
			W->setMaximumSize(16777215,16777215);
			W->setWindowState(Qt::WindowMaximized);
		}
	}
	if(ReturnWindowSizewOnStartPage==true){
		QWidget	*W=GetLayersBase()->GetMainWidget();
		if(W!=NULL){
			if(CurrentMaxSizeW!=16777215 && CurrentMaxSizeH!=16777215){
				W->setMaximumSize(CurrentMaxSizeW,CurrentMaxSizeH);
			}
			W->setWindowState(Qt::WindowNoState);
		}
	}
}
void	ChangeWindowSizeInvisible::LeavePage	(void)
{
	if(MaximizeWindowOnLeavePage==true){
		QWidget	*W=GetLayersBase()->GetMainWidget();
		if(W!=NULL){
			int	SzH=W->maximumHeight();
			int	SzW=W->maximumWidth();
			if(SzH!=16777215 && SzW!=16777215){
				CurrentMaxSizeW=SzW;
				CurrentMaxSizeH=SzH;
			}
			W->setMaximumSize(16777215,16777215);
			W->setWindowState(Qt::WindowMaximized);
		}
	}
	if(ReturnWindowSizewOnLeavePage==true){
		QWidget	*W=GetLayersBase()->GetMainWidget();
		if(W!=NULL){
			if(CurrentMaxSizeW!=16777215 && CurrentMaxSizeH!=16777215){
				W->setMaximumSize(CurrentMaxSizeW,CurrentMaxSizeH);
			}
			W->setWindowState(Qt::WindowNoState);
		}
	}
}

