#include "DisplayStatusResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayStatus\DisplayStatus.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayStatusForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"DisplayStatus";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show staus");
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
	return(new DisplayStatusForm(Base,parent));
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
	Data[0].Pointer				 =&((DisplayStatusForm *)Instance)->CharColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"BackColor";
	Data[1].Pointer				 =&((DisplayStatusForm *)Instance)->BackColor;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"CFont";
	Data[2].Pointer				 =&((DisplayStatusForm *)Instance)->CFont;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayStatus.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}