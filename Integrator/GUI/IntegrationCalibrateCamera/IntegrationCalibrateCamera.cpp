/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationCalibrateCamera\IntegrationCalibrateCamera.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationCalibrateCamera.h"
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
#include "XCriticalFunc.h"
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"
#include "EditTimeListDialog.h"
#include "IntegrateCalibrateShowForm.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"CalibrateCamera";


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

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdCalibrateCamera(Base,sRoot,sName);
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
	return(new IntegrationCalibrateCamera(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationCalibrateCamera *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationCalibrateCamera *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationCalibrateCamera *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationCalibrateCamera *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationCalibrateCamera.png")));
}


//==================================================================================================

TimeList::TimeList(void)
{
}

bool	TimeList::Save(QIODevice *f)
{
	if(::Save(f,Time)==false)	return false;
	return true;
}
bool	TimeList::Load(QIODevice *f)
{
	if(::Load(f,Time)==false)	return false;
	return true;
}

TimeList	*TimeListContainer::Create(void)
{
	return new TimeList();
}

//==================================================================================================


IntegrationCalibrateCamera::IntegrationCalibrateCamera(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationCalibrateCameraBtn");
	Button.move(0,0);
	Msg=/**/"Calibrate camera";
	AForm	=NULL;

	resize(200,25);
	Button.setStyleSheet(/**/"QToolButton {"
						 /**/"	border-style: outset;"
						 /**/"	border-width: 1px;"
						 /**/"	border-radius: 25px;"
						 /**/"	border-color: gray;"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						 /**/"}"
						 /**/"QToolButton:pressed { 	"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						 /**/"}"
						);
	GetParamGUI()->SetParam(&TimeListArray, /**/"IntegrationCalibrateCamera", /**/"TimeListData"		
											 , "Time list for automatic calibration"		);
		
	bool	Ret=(connect(GetParamGUI(),SIGNAL(SignalExecuteForByteArray(const QString & ,const QString & ,QByteArray &)),this,SLOT(SlotExecuteForByteArray(const QString & ,const QString & ,QByteArray &))))?true:false;


	AutoStartCal.setSingleShot(false);
	AutoStartCal.setInterval(5000);
	connect(&AutoStartCal,SIGNAL(timeout()),this,SLOT(SlotAutoStartCal()));
	AutoStartCal.start();

	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationCalibrateCamera::~IntegrationCalibrateCamera()
{

}

void	IntegrationCalibrateCamera::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationCalibrateCamera::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationCalibrateCamera::SlotClicked ()
{
	GetLayersBase()->ShowProcessingForm("Calibrating...");
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			for(int page=0;page<m->GetPageNumb();page++){
				IntegrationCmdCalibrateCamera	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);	
				RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
			}
			if(m->GetPageNumb()==0){
				int	page=0;
				IntegrationCmdCalibrateCamera	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);	
				RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
			}
		}
	}
	GSleep(1000);
	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SlaveNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<5000;){
		QCoreApplication::processEvents();
	}
	GetLayersBase()->CloseProcessingForm();
}
void	IntegrationCalibrateCamera::SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	EditTimeListDialog	D(TimeListData , GetLayersBase());
	if(D.exec()==true){
		TimeListData =D.LContainer;

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		TimeListData.Save(&Buff);
		TimeListArray=Buff.buffer();
		data=TimeListArray;
	}
}

void	IntegrationCalibrateCamera::SlotAutoStartCal()
{
	QTime	CurrentTime=QTime::currentTime();
	if(LastTime.hour()==CurrentTime.hour()
	&& LastTime.minute()==CurrentTime.minute()){
		return;
	}
	for(TimeList *t=TimeListData.GetFirst();t!=NULL;t=t->GetNext()){
		if(t->Time.hour()==CurrentTime.hour()
		&& t->Time.minute()==CurrentTime.minute()){
			LastTime=CurrentTime;
			StartAutoStartCal();
			break;
		}
	}
}
void	IntegrationCalibrateCamera::StartAutoStartCal(void)
{
	if(AForm==NULL){
		AForm=new IntegrateCalibrateShowForm(GetLayersBase()
                                        ,this);
	}
	if(AForm!=NULL){
		AForm->show();
		AForm->Start();
	}
}


//==================================================================================================

IntegrationCmdCalibrateCamera::IntegrationCmdCalibrateCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdCalibrateCamera::Load(QIODevice *f)
{
	return true;
}
bool	IntegrationCmdCalibrateCamera::Save(QIODevice *f)
{
	return true;
}

void	IntegrationCmdCalibrateCamera::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int32	LocalPage=cmd;
    if(LocalPage==0){
		GetLayersBase()->ShowProcessingForm("On calibrating...");
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"CalibrateCamera",/**/"");
		if(f!=NULL){
			SpecifiedBroadcasterCalibrateCamera	Cmd;
			Cmd.Page=LocalPage;
			f->BroadcastSpecifiedDirectly(&Cmd);
		}
		GetLayersBase()->CloseProcessingForm();
	}
}