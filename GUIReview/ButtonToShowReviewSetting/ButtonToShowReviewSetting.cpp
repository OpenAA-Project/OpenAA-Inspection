/*
 * Copyright (C) 2022
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

#include "ButtonToShowReviewSettingResource.h"
#include "ButtonToShowReviewSetting.h"
#include "../XGUIReviewGlobal.h"
#include "XGUIReviewCommonPacket.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ButtonToShowReviewSetting";

const QString saveFilename = /**/"ReviewSetting.ini";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show ReviewSettingForm.");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ButtonToShowReviewSetting *form = new ButtonToShowReviewSetting(Base,parent);
	return form;
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
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

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToShowReviewSetting.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ButtonToShowTotalNGMap
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonToShowReviewSetting::ButtonToShowReviewSetting(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	connect(ui.pbShowSetting, SIGNAL(clicked()), this, SLOT(clicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonToShowReviewSetting::~ButtonToShowReviewSetting()
{
}

void ButtonToShowReviewSetting::clicked()
{
	ReviewSettingFormBase *Base = new ReviewSettingFormBase(GetLayersBase(), this);
	Base->exec();
	delete Base;
}

void ButtonToShowReviewSetting::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}
}

void ButtonToShowReviewSetting::updateGUI()
{
	GUIFormBase::update();
}

void ButtonToShowReviewSetting::ResizeAction()
{
	QRect rect = ui.pbShowSetting->geometry();

	if(rect.width()==width() && rect.height()==height()){
		return;
	}

	rect.setWidth(width());
	rect.setHeight(height());

	ui.pbShowSetting->setGeometry(rect);
}