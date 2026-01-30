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


#include "ShowThresholdLevel.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include <QIcon>
#include <QPixmap>
#include "SetThresholdLevelForm.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ShowThresholdLevel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show threshold level");
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
	return(new ShowThresholdLevel(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/ShowThresholdLevel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================

ShowThresholdLevel::ShowThresholdLevel(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	SForm=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()),Qt::QueuedConnection);
}

ShowThresholdLevel::~ShowThresholdLevel(void)
{
	if(SForm!=NULL){
		SForm->deleteLater();
		SForm=NULL;
	}
}
void	ShowThresholdLevel::ReadyParam(void)
{
	if(SForm==NULL){
		SForm=new SetThresholdLevelForm(GetLayersBase());
		SForm->setParent(this);
		SForm->show();
	}
}

void	ShowThresholdLevel::ResizeAction()
{
	if(SForm!=NULL){
		SForm->setGeometry(0,0,width(),height());
	}
}

void	ShowThresholdLevel::BuildForShow(void)
{
	if(SForm!=NULL){
		SForm->SetCurrentThresholdLevelID(GetLayersBase()->GetThresholdLevelID());
	}
}