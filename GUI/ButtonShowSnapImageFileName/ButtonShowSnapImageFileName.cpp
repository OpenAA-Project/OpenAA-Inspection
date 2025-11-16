/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShowSnapImageFileName\ButtonShowSnapImageFileName.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonShowSnapImageFileName.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XStatusController.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ShowSnapImageFileName";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show file name to snap");
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
	return(new ButtonShowSnapImageFileName(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"CharColor";
	Data[0].Pointer				 =&((ButtonShowSnapImageFileName *)Instance)->CharColor;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"CFont";
	Data[1].Pointer				 =&((ButtonShowSnapImageFileName *)Instance)->CFont;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShowSnapImageFileName.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonShowSnapImageFileName::ButtonShowSnapImageFileName(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	setObjectName(QString::fromUtf8(/**/"ButtonShowSnapImageFileNameObj"));
	Label.setParent(this);
	Label.move(0,0);
	Label.setObjectName(/**/"ButtonShowSnapImageFileName");
	Label.setReadOnly(true);
	resize(100,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonShowSnapImageFileName::~ButtonShowSnapImageFileName(void)
{
}

void	ButtonShowSnapImageFileName::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowSnapImageFileName	*CmdShowSnapImageFileNameVar=dynamic_cast<CmdShowSnapImageFileName *>(packet);
	if(CmdShowSnapImageFileNameVar!=NULL){
		Label.setText(CmdShowSnapImageFileNameVar->FileName);
		return;
	}
}

void	ButtonShowSnapImageFileName::ResizeAction()
{
	Label.resize(width(),height());
}
