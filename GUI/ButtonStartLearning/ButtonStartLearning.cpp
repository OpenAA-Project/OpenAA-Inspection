#include "ButtonStartLearningResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonStartLearning\ButtonStartLearning.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonStartLearning.h"
#include "StartLearningForm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"StartLearning";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load BMP/JPG file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqStartLearning		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningReqStartOne	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningAckStartOne	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningExeTop		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningExeLoopTop	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningExeLoopNext	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningReqData		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningAckData		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningSetData		(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartLearningForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonStartLearning.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}