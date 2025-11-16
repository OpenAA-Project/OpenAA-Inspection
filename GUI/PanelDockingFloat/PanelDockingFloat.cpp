/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelDockingFloat\PanelDockingFloat.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelDockingFloat.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include <QMessageBox>

static	char	*sRoot=/**/"General";
static	char	*sName=/**/"PanelDockingFloat";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Add General panel");
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
	return(new PanelDockingFloat(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"BaseCol";
	Data[0].Pointer				 =&((PanelDockingFloat *)Instance)->BaseCol;
	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelDockingFloat.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
PanelDockingFloat::PanelDockingFloat(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(100,18);
	BaseCol=Qt::lightGray;
}

PanelDockingFloat::~PanelDockingFloat()
{

}

void	PanelDockingFloat::Prepare(void)
{
	if(BaseCol.isValid()==true){
		setAutoFillBackground(true);
		QPalette	P=palette();
		P.setColor(QPalette::Window,BaseCol);
		setPalette(P);
	}
}