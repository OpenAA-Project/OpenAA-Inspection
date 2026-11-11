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

//#include "ButtonSaveInitialLoadGUIDataResource.h"
#include "ChangeCameraByInspection.h"

#include <QMessageBox>
#include <QApplication>
#include "XGUIDLL.h"
#include "XGUI.h"
#include "XCameraClass.h"
#include "XExecuteInspectBase.h"

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"ChangeCameraByInspection";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Change Camera setting by Inspection");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ChangeCameraByInspection(Base,parent));
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
	Data[0].Pointer				 =&((ChangeCameraByInspection *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ChangeCameraByInspection *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ChangeCameraByInspection *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ChangeCameraByInspection *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"PageNo";
	Data[4].Pointer				 =&((ChangeCameraByInspection *)Instance)->PageNo;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveInitialLoadGUIData.png")));
}

//==================================================================================================

ChangeCameraByInspection::ChangeCameraByInspection(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Cam setting";
	PageNo	=0;
	resize(60,25);

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ChangeCameraByInspection::~ChangeCameraByInspection(void)
{
}

void	ChangeCameraByInspection::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	ExecuteInspectBase *E = GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		E->EmitTimingFlag._EmitBeforeScan=true;
		connect(E,SIGNAL(SignalBeforeScan()),this,SLOT(SlotBeforeScan()),Qt::DirectConnection);
	}
}

bool	ChangeCameraByInspection::SaveContent(QIODevice *f)
{
	if(::Save(f,PageNo)==false)		return false;
	if(::Save(f,CamData)==false)	return false;
	return true;
}

bool	ChangeCameraByInspection::LoadContent(QIODevice *f)
{
	if(::Load(f,PageNo)==false)		return false;
	if(::Load(f,CamData)==false)	return false;
	return true;
}

void	ChangeCameraByInspection::ResizeAction()
{
	Button.resize(width(),height());
}

void ChangeCameraByInspection::SlotClicked (bool checked)
{
	GetLayersBase()->TmpHideProcessingForm();
	ExecuteInspectBase *E = GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		int32	CamNo = GetParamGlobal()->GetCameraNo(PageNo);
		if(CamNo>=0){
			CameraClass	*c=E->GetCamera(CamNo);
			QByteArray	Info=CamData;
			if(c->ShowInfoNumber(Info)==true){
				CamData = Info;
			}

			/*
			{
				QBuffer RCamDataBuffer(&CamData);
				RCamDataBuffer.open(QIODevice::ReadOnly);
				c->Load(RCamDataBuffer);
			}

			if(c->ShowSetting(NULL)==true){
				QBuffer CamDataBuffer;
				CamDataBuffer.open(QIODevice::WriteOnly);
				c->Save(CamDataBuffer);
				CamData = CamDataBuffer.buffer();
			}
			*/
		}
	}
	GetLayersBase()->TmpRercoverProcessingForm();
}
void	ChangeCameraByInspection::SlotBeforeScan()
{
	QFile	TextFile("TestStrategicNumber.txt");
	TextFile.open(QIODevice::Append);
	QTextStream	TxtStr(&TextFile);

	int	SNumber=GetLayersBase()->GetCurrentStrategicNumber();
	TxtStr<<SNumber;
	TxtStr<<"n";


	IntList	PageList;
	GetParamGlobal()->GetStrategyPage(SNumber,PageList);
	if(PageList.IsInclude(PageNo)==true){
		ExecuteInspectBase *E = GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(E!=NULL){
			int32	CamNo = GetParamGlobal()->GetCameraNo(PageNo);
			if(CamNo>=0){
				CameraClass	*c=E->GetCamera(CamNo);
				if(c!=NULL){
					c->SetInfoNumber(CamData);

					//QBuffer RCamDataBuffer(&CamData);
					//RCamDataBuffer.open(QIODevice::ReadOnly);
					//c->Load(RCamDataBuffer);
				}
			}
		}
	}
}
