
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorld\GUI\RWView3D\RWView3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RWView3D.h"
#include "XCrossObj.h"
#include "XGUIDLL.h"
#include "XRegulusWorld.h"

static	const	char	*sRoot=/**/"RegulusWorld";
static	const	char	*sName=/**/"RWView3D";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display 3D of RegulusWorld");
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
	return(new RWView3D(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=0;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RWView3D.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
RWView3D::RWView3D(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Panel(GetRegulusWorld(Base),this)
{
	Panel.setGeometry(0,0,width(),height());
}
void RWView3D::resizeEvent(QResizeEvent *event)
{
	Panel.setGeometry(0,0,width(),height());
}