/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DalsaLoadImage\DalsaLoadImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DalsaLoadImage.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "SelectDialog.h"

const	char	*sRoot=/**/"Dalsa";
const	char	*sName=/**/"LoadImage";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Load image from Dalsa camera buffer");
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
	return(new DalsaLoadImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DalsaLoadImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//================================================================================================

DalsaLoadImage::DalsaLoadImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive (false);
	Button.setCheckable(true);

	Button.setObjectName(/**/"DalsaLoadImage");
	Msg=/**/"DalsaLoadImage";
	resize(60,25);

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

DalsaLoadImage::~DalsaLoadImage(void)
{
}

void	DalsaLoadImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	DalsaLoadImage::ResizeAction()
{
	Button.resize(width(),height());
}

void DalsaLoadImage::SlotClicked (bool checked)
{
	SelectDialog	D(GetLayersBase());
	D.exec();
}


