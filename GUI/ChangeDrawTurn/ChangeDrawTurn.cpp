#include "ChangeDrawTurnResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ChangeDrawTurn\ChangeDrawTurn.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ChangeDrawTurn.h"

static	const	char	*sRoot=/**/"List";
static	const	char	*sName=/**/"ChangeDrawTurn";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show list to change drawing turn");
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
	return(new ChangeDrawTurn(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/ChangeDrawTurn.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==============================================================================================

ChangeDrawTurn::ChangeDrawTurn(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	resize(150,100);
	List.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&List,SIGNAL(clicked(const QModelIndex)), this ,SLOT(ListClicked(const QModelIndex)));
	List.setSelectionMode(QAbstractItemView::SingleSelection);
	List.setSelectionBehavior(QAbstractItemView::SelectRows);
}

ChangeDrawTurn::~ChangeDrawTurn()
{

}

void	ChangeDrawTurn::Prepare(void)
{
	ResizeAction();
}

void	ChangeDrawTurn::ResizeAction()
{
	List.move(0,0);
	List.resize(width(),height());
}

void	ChangeDrawTurn::BuildForShow(void)
{
	List.clear();
	for(int page=0;page<GetPageNumb();page++){
		List.addItem(QString(/**/"Page ")+QString::number(GetLayersBase()->GetDrawturn(page)->GetPage()));
	}
}
void	ChangeDrawTurn::ShowInEdit(void)
{
	List.clear();
	for(int page=0;page<GetPageNumb();page++){
		List.addItem(QString(/**/"Page ")+QString::number(GetLayersBase()->GetDrawturn(page)->GetPage()));
	}
}

void ChangeDrawTurn::ListClicked (const QModelIndex index )
{
	int	RIndex=index.row();
	GetLayersBase()->SetTopInPage(GetLayersBase()->GetDrawturn(RIndex));
	BuildForShow();
	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
}

