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

#include "CameraSettingButtonResource.h"
#include "CameraSettingButton.h"
#include "XExecuteInspectBase.h"
#include "SelectCameraDialog.h"
#include "XEntryPoint.h"


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"CameraSettingButton";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show CameraSetting window");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new CameraSettingButton(Base,parent));
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
	Data[0].Pointer				 =&((CameraSettingButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((CameraSettingButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((CameraSettingButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((CameraSettingButton *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CameraSettingButton.png")));
}

//==================================================================================================
CameraSettingButton::CameraSettingButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"CameraSettingButtonBtn");
	Button.move(0,0);
	Msg=/**/"Setting Camera";
	resize(120,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

CameraSettingButton::~CameraSettingButton(void)
{
}

void	CameraSettingButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	CameraSettingButton::ResizeAction()
{
	Button.resize(width(),height());
}

void CameraSettingButton::SlotClicked (bool checked)
{
	GetLayersBase()->TmpHideProcessingForm();
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SelectCameraDialog	D(GetLayersBase(),this);
		if(D.CamList.GetCount()<=1){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->CamShowSetting(0);
		}
		else{
			if(D.exec()==(int)true){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->CamShowSetting(D.CamNo);
			}
		}
	}
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	CameraSettingButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(CameraSettingButton_LS,LID_0)/*"Setting"*/,LangSolver.GetString(CameraSettingButton_LS,LID_1)/*"Setting Camera"*/,this);
	p->SetMenuNumber(1010);
	Info.AppendList(p);
}
void	CameraSettingButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	CameraSettingButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdOpenCameraSetting	*CmdOpenCameraSettingVar=dynamic_cast<CmdOpenCameraSetting *>(packet);
	if(CmdOpenCameraSettingVar!=NULL){
		SlotClicked(true);
		return;
	}
}