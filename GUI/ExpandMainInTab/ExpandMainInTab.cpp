/*
 * Copyright (C) 2025
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

#include "ExpandMainInTabResource.h"

#include "ExpandMainInTab.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XGUI.h"
#include <QGuiApplication>

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"ExpandMainInTab";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Expand Main window in Tab opened");
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
	return(new ExpandMainInTab(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/ExpandMainInTab.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ExpandMainInTab::ExpandMainInTab(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
}
void	ExpandMainInTab::Prepare(void)
{
}
ExpandMainInTab::~ExpandMainInTab(void)
{
}

void	ExpandMainInTab::StartPage	(void)
{
	for(QWidget	*w=parentWidget();w!=NULL;w=w->parentWidget()){
		MainGUIFormBase	*d=dynamic_cast<MainGUIFormBase	*>(w);
		if(d!=NULL){
			SavedX1=d->geometry().left();
			SavedY1=d->geometry().top();
			SavedX2=d->geometry().right();
			SavedY2=d->geometry().bottom();

			QScreen	*Scr=qGuiApp->screens()[0];
			d->move(0,0);
			d->resize(Scr->geometry().width(),Scr->geometry().height());
			return;
		}
	}
}
void	ExpandMainInTab::LeavePage	(void)
{
	for(QWidget	*w=parentWidget();w!=NULL;w=w->parentWidget()){
		MainGUIFormBase	*d=dynamic_cast<MainGUIFormBase	*>(w);
		if(d!=NULL){
			d->move(SavedX1,SavedY1);
			d->resize(SavedX2-SavedX1,SavedY2-SavedY1);
			break;
		}
	}
}