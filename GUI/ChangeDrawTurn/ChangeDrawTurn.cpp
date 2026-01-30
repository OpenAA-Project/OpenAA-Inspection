/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ChangeDrawTurnResource.h"

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
