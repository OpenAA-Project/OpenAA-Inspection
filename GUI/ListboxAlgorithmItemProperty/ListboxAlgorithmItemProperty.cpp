#include "ListboxAlgorithmItemPropertyResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxAlgorithmItemProperty\ListboxAlgorithmItemProperty.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListboxAlgorithmItemProperty.h"
#include "XAlgorithmBase.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Inspection";
	Name=/**/"ListboxAlgorithmItemProperty";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Listbox to view algorithm item property");
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
	return(new ListboxAlgorithmItemProperty(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/ListboxAlgorithmItemProperty.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================

ListboxAlgorithmItemProperty::ListboxAlgorithmItemProperty(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),MainList(this)
{
	resize(250,250);
	MainList.setParent(this);
	//MainList.ShowGrid();
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
ListboxAlgorithmItemProperty::~ListboxAlgorithmItemProperty(void)
{
}
void	ListboxAlgorithmItemProperty::Prepare(void)
{
}
void	ListboxAlgorithmItemProperty::ResizeAction()
{
	MainList.resize(width(),height());
}

