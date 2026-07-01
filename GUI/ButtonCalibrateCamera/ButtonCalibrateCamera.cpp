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


#include "ButtonCalibrateCamera.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XCameraClass.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"CalibrateCamera";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to calibrate camera");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdCalibrateCamera	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonCalibrateCamera(Base,parent));
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
	Data[0].Pointer				 =&((ButtonCalibrateCamera *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonCalibrateCamera *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonCalibrateCamera *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonCalibrateCamera *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCalibrateCamera.png")));
}

//==================================================================================================
ButtonCalibrateCamera::ButtonCalibrateCamera(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonCalibrateCamera");
	Msg=/**/"Calibrate Camera";
	Mastered=true;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool))	, this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize())		, this ,SLOT(ResizeAction()));
}

ButtonCalibrateCamera::~ButtonCalibrateCamera(void)
{
}

void	ButtonCalibrateCamera::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonCalibrateCamera::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonCalibrateCamera::SlotClicked (bool checked)
{
	int	page=0;
	GUICmdCalibrateCamera	RCmd(GetLayersBase(),sRoot,sName,page);	
	RCmd.SendOnly(page,0);
}
//=================================================================

GUICmdCalibrateCamera::GUICmdCalibrateCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdCalibrateCamera::Receive(int32 LocalPage,int cmd,QString &EmitterRoot,QString &EmitterName)
{
    if(LocalPage==0){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"CalibrateCamera",/**/"");
		if(f!=NULL){
			SpecifiedBroadcasterCalibrateCamera	Cmd;
			Cmd.Page=LocalPage;
			f->BroadcastSpecifiedDirectly(&Cmd);
		}
	}
	SendAck(LocalPage);
}
