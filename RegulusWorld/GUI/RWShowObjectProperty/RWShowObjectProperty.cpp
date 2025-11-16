/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorld\GUI\RWShowObjectProperty\RWShowObjectProperty.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "RWShowObjectPropertyResource.h"
#include "RWShowObjectProperty.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XRegulusWorld.h"
#include "XRWDevice.h"
#include "RWShowObjectPropertyForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"

static	const	char	*sRoot=/**/"RegulusWorld";
static	const	char	*sName=/**/"RWShowObjectProperty";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Object property for RegulusWorld");
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
	return(new RWShowObjectPropertyForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RWShowObjectProperty.png")));
}