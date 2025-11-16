/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationLoadMaster\IntegrationLoadMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationLoadMasterResource.h"
#include "IntegrationLoadMaster.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "LoadMasterDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XMacroFunction.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"LoadMaster";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load master data");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdLoadMaster(Base,sRoot,sName);

	//(*Base)=new GUICmdReqSaveBmpJpg(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationLoadMaster(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationLoadMaster *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationLoadMaster *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationLoadMaster *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationLoadMaster *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"EnableLoadAtFirst";
	Data[4].Pointer				 =&((IntegrationLoadMaster *)Instance)->EnableLoadAtFirst;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationLoadMaster.png")));
}

static	bool	MacroLoadDialog(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroLoadWithoutDialog(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"LoadDialog";
		Functions[ret].Explain.append(/**/"Open loading dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroLoadDialog;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"LoadWithoutDialog";
		Functions[ret].Explain.append(/**/"Load master without dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroLoadWithoutDialog;
		ret++;
	}
	return ret;
}

static bool	MacroLoadDialog(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationLoadMaster	*V=dynamic_cast<IntegrationLoadMaster *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenDialog();

	return true;
}

static bool	MacroLoadWithoutDialog(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationLoadMaster	*V=dynamic_cast<IntegrationLoadMaster *>(Instance);
	if(V==NULL){
		return false;
	}

	V->LoadWithoutDialog();

	return true;
}


//==================================================================================================
IntegrationLoadMaster::IntegrationLoadMaster(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	LangSolver.SetUI(this);

	Button.setObjectName(/**/"IntegrationLoadMasterBtn");
	Button.move(0,0);
	LastOpenedID	=-1;
	LastAcsendantOrder=false;
	LastOrderMode	=0;
	LastOpenedFileName	=/**/"IntegratorLastOpenedID.dat";
	EnableLoadAtFirst	=false;
	LoadedAtFirst		=false;

	Msg=/**/"Load master data";
	resize(80,25);
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
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	IntegrationLoadMaster::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	{
		QFile	File(LastOpenedFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			::Load(&File,LastOpenedID);
			::Load(&File,LastAcsendantOrder);
			::Load(&File,LastOrderMode);
		}
	}
	if(GetEditMode()==false
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->Mastered==true){
		connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalAllSlaveConnected())	,this,SLOT(SlotSlaveConnected())	,Qt::QueuedConnection);
		connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalSlaveDisconnected())	,this,SLOT(SlotSlaveDisconnected())	,Qt::QueuedConnection);
	}
}
void	IntegrationLoadMaster::ReadyParam(void)
{
}

void	IntegrationLoadMaster::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationLoadMaster::OpenDialog(void)
{
	SlotClicked();
}
bool	IntegrationLoadMaster::LoadWithoutDialog(void)
{
	GetLayersBase()->GetIntegrationBasePointer()->AvailableIntegrationResource=false;
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationLoadMaster_LS,LID_3)/*"マスターデータ読み込み中"*/);

	int	RelationCode=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
	return LoadOnly(RelationCode);
}

bool	IntegrationLoadMaster::LoadOnly(int	RelationCode)
{
	if(RelationCode>=0){
		LastOpenedID		=RelationCode;
		{
			QFile	File(LastOpenedFileName);
			if(File.open(QIODevice::WriteOnly)==true){
				::Save(&File,LastOpenedID);
				::Save(&File,LastAcsendantOrder);
				::Save(&File,LastOrderMode);
			}
		}
		GetLayersBase()->GetIntegrationBasePointer()->MasterRelationCode=RelationCode;

		QString RetRelationNumber	;
		QString RetRelationName	;
		QString RetRemark		;
		int		RetRelationType	;
		QByteArray	CommonByteArray;
		int32	ThresholdLevelID=0;
		if(GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation(GetLayersBase()->GetDatabase() 
										,RelationCode
										,RetRelationNumber
										,RetRelationName
										,RetRemark
										,RetRelationType
										,CommonByteArray
										,ThresholdLevelID)==true){
			QBuffer	CommonBuff(&CommonByteArray);
			CommonBuff.open(QIODevice::ReadOnly);
			IntegrationCommonData	CommonData;
			CommonData.Load(&CommonBuff);
			GetLayersBase()->GetMainWidget()->LoadAll(&CommonBuff);
			GetLayersBase()->GetIntegrationBasePointer()->SetCommonData(CommonData);
			GetLayersBase()->GetIntegrationBasePointer()->DeliverThresholdLevel(ThresholdLevelID);
		}


		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		QString	S=QString(/**/"SELECT MASTERCODE,MASTERNAME,MACHINEID FROM MASTERDATA WHERE RELATIONCODE=")
			+QString::number(RelationCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		for(int i=0;i<1000;i++){
			if(query.next ()==false)
				break;

			int		MasterCode	=query.value(query.record().indexOf(/**/"MASTERCODE")).toInt();
			QString	MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
			int		MachineID	=query.value(query.record().indexOf(/**/"MACHINEID"	)).toInt();

			EachMaster *Pointer[10];
			int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
			for(int m=0;m<MasterCount;m++){				
				Pointer[m]->ClearMaster();
				Pointer[m]->SetMasterCode(MasterCode);
				Pointer[m]->SetMasterName(MasterName);
				int	SlaveNo=Pointer[m]->GetIntegrationSlaveNo();
				IntegrationCmdLoadMaster	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.MasterCode=MasterCode;
				RCmd.Send(NULL,SlaveNo,0);
			}
		}
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

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			m->ReleaseImageBuffer();
			m->RequireSlaveInfo();
			m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
		}
		GetLayersBase()->GetIntegrationBasePointer()->LoadLotData();
		GetLayersBase()->GetIntegrationBasePointer()->AvailableIntegrationResource=true;
		CmdUpdatedMasterImage	ICmd;
		BroadcastSpecifiedDirectly(&ICmd);
		LoadMasterSpecifiedBroadcaster	LSCmd;
		BroadcastSpecifiedDirectly(&LSCmd);
		CmdClearCounter	ClearCCmd;
		BroadcastSpecifiedDirectly(&ClearCCmd);
		BroadcastBuildForShow();

		GetLayersBase()->GetIntegrationBasePointer()->UpdateLastLoadedTimeMasterRelation();

		LoadedAtFirst=true;
	}
	GetLayersBase()->CloseProcessingForm();
	return true;
}
void	IntegrationLoadMaster::SlotClicked ()
{
//	if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		LoadMasterDialog	D(GetLayersBase(),LastOrderMode,LastAcsendantOrder,LastOpenedID);
		if(D.exec()==true){
			LastOrderMode		=D.OrderMode;
			LastOpenedID		=D.ResultRelationCode;
			LastAcsendantOrder	=D.AcsendantOrder;
			{
				QFile	File(LastOpenedFileName);
				if(File.open(QIODevice::WriteOnly)==true){
					::Save(&File,LastOpenedID);
					::Save(&File,LastAcsendantOrder);
					::Save(&File,LastOrderMode);
				}
			}

			GetLayersBase()->GetIntegrationBasePointer()->AvailableIntegrationResource=false;
			GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationLoadMaster_LS,LID_4)/*"マスターデータ読み込み中"*/);

			int	RelationCode=D.ResultRelationCode;
			GetLayersBase()->GetIntegrationBasePointer()->MasterRelationCode=RelationCode;

			QString RetRelationNumber	;
			QString RetRelationName	;
			QString RetRemark		;
			int		RetRelationType	;
			QByteArray	CommonByteArray;
			int32	ThresholdLevelID;
			if(GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation(GetLayersBase()->GetDatabase() 
											,RelationCode
											,RetRelationNumber
											,RetRelationName
											,RetRemark
											,RetRelationType
											,CommonByteArray
											,ThresholdLevelID)==true){
				QBuffer	CommonBuff(&CommonByteArray);
				CommonBuff.open(QIODevice::ReadOnly);
				IntegrationCommonData	CommonData;
				CommonData.Load(&CommonBuff);
				GetLayersBase()->GetIntegrationBasePointer()->SetCommonData(CommonData);
				GetLayersBase()->GetMainWidget()->LoadAll(&CommonBuff);
				GetLayersBase()->GetIntegrationBasePointer()->DeliverThresholdLevel(ThresholdLevelID);
			}


			int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
			QString	S=QString(/**/"SELECT MASTERCODE,MASTERNAME,MACHINEID FROM MASTERDATA WHERE RELATIONCODE=")
				+QString::number(RelationCode);
			QSqlQuery query(S ,GetLayersBase()->GetDatabase());
			for(int i=0;i<1000;i++){
				if(query.next ()==false)
					break;

				int		MasterCode	=query.value(query.record().indexOf(/**/"MASTERCODE")).toInt();
				QString	MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
				int		MachineID	=query.value(query.record().indexOf(/**/"MACHINEID"	)).toInt();

				EachMaster *Pointer[10];
				int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
				for(int m=0;m<MasterCount;m++){				
					Pointer[m]->ClearMaster();
					Pointer[m]->SetMasterCode(MasterCode);
					Pointer[m]->SetMasterName(MasterName);
					int	SlaveNo=Pointer[m]->GetIntegrationSlaveNo();
					IntegrationCmdLoadMaster	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RCmd.MasterCode=MasterCode;
					RCmd.Send(NULL,SlaveNo,0);
				}
			}
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

			GSleep(2000);
			QApplication::processEvents();
			GSleep(2000);

			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				m->ReleaseImageBuffer();
				if(m->RequireSlaveInfo()==false){
					GSleep(2000);
					m->RequireSlaveInfo();
				}
				if(m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration)==false){
					GSleep(2000);
					m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
				}
			}
			GetLayersBase()->GetIntegrationBasePointer()->LoadLotData();
			GetLayersBase()->GetIntegrationBasePointer()->AvailableIntegrationResource=true;
			CmdUpdatedMasterImage	ICmd;
			BroadcastSpecifiedDirectly(&ICmd);
			LoadMasterSpecifiedBroadcaster	LSCmd;
			BroadcastSpecifiedDirectly(&LSCmd);
			CmdClearCounter	ClearCCmd;
			BroadcastSpecifiedDirectly(&ClearCCmd);
			BroadcastBuildForShow();
			LoadedAtFirst=true;

			GetLayersBase()->GetIntegrationBasePointer()->UpdateLastLoadedTimeMasterRelation();

			GetLayersBase()->CloseProcessingForm();
		}
//	}
}
void	IntegrationLoadMaster::SlotSlaveConnected()
{
	if(EnableLoadAtFirst==true && LoadedAtFirst==false && LastOpenedID>=0){
		LoadedAtFirst=true;
		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationLoadMaster_LS,LID_5)/*"マスターデータ読み込み中"*/);
		LoadOnly(LastOpenedID);
		GetLayersBase()->CloseProcessingForm();
	}
}
void	IntegrationLoadMaster::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdEnableLoadAtFirst	*CmdEnableLoadAtFirstVar=dynamic_cast<CmdEnableLoadAtFirst *>(packet);
	if(CmdEnableLoadAtFirstVar!=NULL){
		EnableLoadAtFirst	=CmdEnableLoadAtFirstVar->EnableLoadAtFirst;
		return;
	}
	CmdReqEnableLoadAtFirst	*CmdReqEnableLoadAtFirstVar=dynamic_cast<CmdReqEnableLoadAtFirst *>(packet);
	if(CmdReqEnableLoadAtFirstVar!=NULL){
		CmdReqEnableLoadAtFirstVar->EnableLoadAtFirst=EnableLoadAtFirst;
		return;
	}
}
void	IntegrationLoadMaster::SlotSlaveDisconnected()
{
}
//==================================================================================================
IntegrationCmdLoadMaster::IntegrationCmdLoadMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdLoadMaster::Load(QIODevice *f)
{
	if(::Load(f,MasterCode	)==false)
		return false;
	return true;
}
bool	IntegrationCmdLoadMaster::Save(QIODevice *f)
{
	if(::Save(f,MasterCode	)==false)
		return false;
	return true;
}
void	IntegrationCmdLoadMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"LoadMasterData",/**/"");
	if(f!=NULL){
		QStringList Args;
		bool ExeReturn;
		Args.append(QString::number(MasterCode));
		Args.append(/**/"true");
		Args.append(/**/"TRUE");	//Silent mode
		f->ExecuteMacro(/**/"Load master", Args, ExeReturn);
	}
}
