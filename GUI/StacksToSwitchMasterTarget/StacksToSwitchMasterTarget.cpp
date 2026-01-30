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

#include "StacksToSwitchMasterTargetResource.h"

#include "StacksToSwitchMasterTarget.h"

#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "swap.h"
#include "XEntryPoint.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"StacksToSwitchMasterTarget";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Switch master and target");
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
	return(new StacksToSwitchMasterTarget(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/StacksToSwitchMasterTarget.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================


StacksTabWizardPage::StacksTabWizardPage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
}
StacksTabWizardPage::~StacksTabWizardPage(void)
{
}
void	StacksTabWizardPage::Prepare(void)
{
}
void	StacksTabWizardPage::ResizeAction(void)
{
}


StacksToSwitchMasterTarget::StacksToSwitchMasterTarget(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(400,400);
	MainTab.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	MainTab.move(0,0);
}


void	StacksToSwitchMasterTarget::Prepare(void)
{
	while(2<MainTab.count()){
		MainTab.removeWidget(MainTab.widget(0));
	}
	while(2>MainTab.count()){
		StacksTabWizardPage	*w=new StacksTabWizardPage(GetLayersBase(),&MainTab);
		MainTab.addWidget(w);
	}

	QWidget	*w=MainTab.widget(0);
	StacksTabWizardPage	*wt=dynamic_cast<StacksTabWizardPage *>(w);
	if(wt!=NULL){
		wt->setWindowTitle(/**/"Master");
		wt->SetName(/**/"Master");
	}
	w=MainTab.widget(1);
	wt=dynamic_cast<StacksTabWizardPage *>(w);
	if(wt!=NULL){
		wt->setWindowTitle(/**/"Target");
		wt->SetName(/**/"Target");
	}

	ResizeAction();
	update();
}

int	StacksToSwitchMasterTarget::GetChildCount()
{
	return MainTab.count();
}
GUIFormBase	*StacksToSwitchMasterTarget::GetChild(int index)	const
{
	if(index<MainTab.count())
		return dynamic_cast<GUIFormBase*>(MainTab.widget(index));
	return NULL;
}

GUIFormBase	*StacksToSwitchMasterTarget::GetTopSurfaceWidget(int x ,int y)
{
	if(MainTab.geometry().left()<=x && x<MainTab.geometry().right()
		&& MainTab.geometry().top()<=y && y<MainTab.geometry().bottom()){
		return dynamic_cast<GUIFormBase*>(MainTab.currentWidget());
	}
	return this;
}

void	StacksToSwitchMasterTarget::ResizeAction()
{
	MainTab.resize(width(),height());
}

void	StacksToSwitchMasterTarget::SwitchTab(bool Mastered)
{
	if(Mastered==true){
		MainTab.setCurrentIndex(0);
	}
	else {
		MainTab.setCurrentIndex(1);
	}
}
void	StacksToSwitchMasterTarget::ShowInPlayer(int64 shownInspectionID)
{
	if(GetLayersBase()->GetEntryPoint()!=NULL && GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetCurrentTypeOfCapture()==ExecuteInspectBase::_Master){
			SwitchTab(true);
		}
		else if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetCurrentTypeOfCapture()==ExecuteInspectBase::_Target){
			SwitchTab(false);
		}
		else{
		SwitchTab(true);
		}
	}
}



