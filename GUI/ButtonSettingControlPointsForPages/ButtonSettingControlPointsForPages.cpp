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


#include "ButtonSettingControlPointsForPages.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "ShowSettingControlPointsForPagesForm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SettingControlPointsForPages";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to set ControlPointsForPages");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,__Master);

	(*Base)=new GUICmdReqControlPoints	(Base,sRoot,sName);
	(*Base)=new GUICmdAckControlPoints	(Base,sRoot,sName);
	(*Base)=new GUICmdSetControlPoints	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSettingControlPointsForPages(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSettingControlPointsForPages *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSettingControlPointsForPages *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSettingControlPointsForPages *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSettingControlPointsForPages *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"Mastered";
	Data[4].Pointer				 =&((ButtonSettingControlPointsForPages *)Instance)->Mastered;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSettingControlPointsForPages.png")));
}

//==================================================================================================
ButtonSettingControlPointsForPages::ButtonSettingControlPointsForPages(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonSettingControlPointsForPages");
	Msg=/**/"ControlPoints";
	Window  =NULL;
	Mastered=true;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool))	, this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize())		, this ,SLOT(ResizeAction()));
}

ButtonSettingControlPointsForPages::~ButtonSettingControlPointsForPages(void)
{
}

void	ButtonSettingControlPointsForPages::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSettingControlPointsForPages::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSettingControlPointsForPages::SlotClicked (bool checked)
{
	if(Window!=NULL){
		Window->show();
	}
	else{
		if(Mastered==true){
			Window=new ShowSettingControlPointsForPagesForm(GetLayersBase()
														,__Master);
		}
		else{
			Window=new ShowSettingControlPointsForPagesForm(GetLayersBase()
														,__Target);
		}
		Window->show();
	}
}