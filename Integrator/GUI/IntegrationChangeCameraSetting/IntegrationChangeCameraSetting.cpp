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

//#include "ButtonSaveBmpJpgResource.h"
#include "IntegrationChangeCameraSetting.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include "ChangeCameraSetting.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"ChangeCameraSetting";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to change camera setting");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdChangeCameraSetting(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationChangeCameraSetting(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SlaveNo";
	Data[4].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->SlaveNo;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"CamSettingFileNameInSlave";
	Data[5].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->CamSettingFileNameInSlave;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"ChangeSettingInstName";
	Data[6].Pointer				 =&((IntegrationChangeCameraSetting *)Instance)->ChangeSettingInstName;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationChangeCameraSetting.png")));
}


//==================================================================================================
IntegrationChangeCameraSetting::IntegrationChangeCameraSetting(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationChangeCameraSettingBtn");
	Button.move(0,0);
	Msg=/**/"Change camera setting";
	SlaveNo	=0;

	resize(200,25);
	Button.setStyleSheet("QToolButton {"
						"	border-style: outset;"
						"	border-width: 1px;"
						"	border-radius: 25px;"
						"	border-color: gray;"
						"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						"}"
						"QToolButton:pressed { 	"
						"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationChangeCameraSetting::~IntegrationChangeCameraSetting()
{

}

void	IntegrationChangeCameraSetting::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationChangeCameraSetting::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationChangeCameraSetting::SlotClicked ()
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		IntegrationCmdChangeCameraSetting	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.CamSettingFileNameInSlave	=CamSettingFileNameInSlave;
		RCmd.ChangeSettingInstName		=ChangeSettingInstName;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
void	IntegrationChangeCameraSetting::TransmitDirectly(GUIDirectMessage *packet)
{
	IntegrationChangeCameraSettingFile	*v=dynamic_cast<IntegrationChangeCameraSettingFile *>(packet);
	if(v!=NULL){
		int SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(v->MachineID);
		IntegrationCmdChangeCameraSetting	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.CamSettingFileNameInSlave	=v->CameraSettingFileName;
		RCmd.ChangeSettingInstName		=/**/"";
		RCmd.Send(NULL,SlaveNo,0);
		return;
	}
}

//==================================================================================================
IntegrationCmdChangeCameraSetting::IntegrationCmdChangeCameraSetting(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdChangeCameraSetting::Load(QIODevice *f)
{
	if(::Load(f,CamSettingFileNameInSlave)==false)
		return false;
	if(::Load(f,ChangeSettingInstName)==false)
		return false;
	return true;
}
bool	IntegrationCmdChangeCameraSetting::Save(QIODevice *f)
{
	if(::Save(f,CamSettingFileNameInSlave)==false)
		return false;
	if(::Save(f,ChangeSettingInstName)==false)
		return false;
	return true;
}

void	IntegrationCmdChangeCameraSetting::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(ChangeSettingInstName.isEmpty()==true){
		GUIFormBase *RetGUI[100];
		int	N=GetLayersBase()->EnumGUIInst(/**/"Camera" ,/**/"ChangeSetting" ,RetGUI ,sizeof(RetGUI));
		if(N==0){
			QMessageBox::warning(NULL
								, "Error"
								, "Camera:ChangeSetting component doesn\'t exists");
		}
		else{
			CmdChangeCameraSettingFile	RCmd(GetLayersBase());
			RCmd.CameraSettingFileName=CamSettingFileNameInSlave;
			RetGUI[0]->TransmitDirectly(&RCmd);
		}
	}
	else{
		GUIFormBase	*f=GetLayersBase()->FindByName(ChangeSettingInstName);
		if(f==NULL){
			QMessageBox::warning(NULL
								, "Error"
								, QString("Camera:ChangeSetting ")
								 +ChangeSettingInstName
								 +QString(" component doesn\'t exists"));
		}
		else{
			CmdChangeCameraSettingFile	RCmd(GetLayersBase());
			RCmd.CameraSettingFileName=CamSettingFileNameInSlave;
			f->TransmitDirectly(&RCmd);
		}
	}
}