#include "DisplayServerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayServer\DisplayServer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayServer.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"DisplayServer";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display server name");
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
	return(new DisplayServer(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"CharColor";
	Data[0].Pointer				 =&((DisplayServer *)Instance)->CharColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"BackColor";
	Data[1].Pointer				 =&((DisplayServer *)Instance)->BackColor;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"CFont";
	Data[2].Pointer				 =&((DisplayServer *)Instance)->CFont;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayServer.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
DisplayServer::DisplayServer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	HLabel.setParent(this);
	HLabel.move(0,0);
	HLabel.setObjectName(/**/"DisplayServer");
	HLabel.setText(/**/"DisplayServer");
	resize(80,25);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	DisplayServer::Prepare(void)
{
	HLabel.setFont (CFont);
	ResizeAction();
}

void	DisplayServer::ResizeAction()
{
	HLabel.resize(width(),height());
}
void	DisplayServer::BuildForShow(void)
{
	HLabel.setText(GetLayersBase()->GetParamGlobal()->LocalDatabase_FileName);
}
