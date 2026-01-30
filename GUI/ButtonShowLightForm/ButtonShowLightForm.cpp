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

#include "ButtonShowLightFormResource.h"

#include "ButtonShowLightForm.h"
#include "XDataInLayer.h"
#include "XLightClass.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"ButtonShowLightForm";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show LightSetting window");
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
	return(new ButtonShowLightForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonShowLightForm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonShowLightForm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonShowLightForm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonShowLightForm *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"LightNumber";
	Data[4].Pointer				 =&((ButtonShowLightForm *)Instance)->LightNumber;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShowLightForm.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonShowLightForm::ButtonShowLightForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Setting Light";
	LightNumber	=0;
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	Once=false;
}

ButtonShowLightForm::~ButtonShowLightForm(void)
{
}

void	ButtonShowLightForm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonShowLightForm::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonShowLightForm::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetLightBase()!=NULL && Once==false){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			connect(L->GetHandle(),SIGNAL(SignalReflectDataInDialog()),this,SLOT(SlotReflectDataInDialog()));
			connect(L->GetHandle(),SIGNAL(SignalReflectOnOffInDialog(bool)),this,SLOT(SlotReflectOnOffInDialog(bool)));
		}
		Once=true;
	}
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			if(L->ShowSetting(this)==true){
				QString	SysPath=GetLayersBase()->GetSystemPath();
				QDir::setCurrent(SysPath);
				QFile	File(GetParamGlobal()->LightSettingFileName);
				File.open(QIODevice::WriteOnly);
				if(GetLayersBase()->GetLightBase()->Save(&File)==true){
					GetLayersBase()->GetLightBase()->SetPattern(0);
				}
			}
		}
	}
}

void	ButtonShowLightForm::SlotReflectDataInDialog()
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			L->GetHandle()->ReflectPhysical();
		}
	}
}
void	ButtonShowLightForm::SlotReflectOnOffInDialog(bool LightOn)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			L->GetHandle()->ReflectPhysicalTurnOn(LightOn);
		}
	}
}