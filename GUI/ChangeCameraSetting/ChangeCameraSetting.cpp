#include "ChangeCameraSettingResource.h"
#include "ChangeCameraSetting.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XEntryPoint.h"

const	char	*sRoot=/**/"Camera";
const	char	*sName=/**/"ChangeSetting";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Change Camera-Setting");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeCameraSetting	 (Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeCameraSettingFile(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeCameraSettingData(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLoadCameraSettingData	 (Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ChangeCameraSetting(Base,parent));
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
	Data[0].Pointer				 =&((ChangeCameraSetting *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ChangeCameraSetting *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ChangeCameraSetting *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ChangeCameraSetting *)Instance)->CFont;
	Data[4].Type				 =/**/"FileName";
	Data[4].VariableNameWithRoute=/**/"CameraSettingFileName";
	Data[4].Pointer				 =&((ChangeCameraSetting *)Instance)->CameraSettingFileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ChangeCameraSetting.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	BArray;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"CameraSetting",BArray);
	Data.AppendList(A);
}
//==================================================================================================
ChangeCameraSetting::ChangeCameraSetting(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	NormalColor=Qt::lightGray;
	PushedColor=Qt::red;
	Msg=/**/"Set Cam";
	resize(60,25);

	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ChangeCameraSetting::~ChangeCameraSetting(void)
{
}

void	ChangeCameraSetting::Prepare(void)
{
	Button.setText(Msg);
	Button.setColor(NormalColor);
	Button.setFont (CFont);
	ResizeAction();
}

void	ChangeCameraSetting::ResizeAction()
{
	Button.resize(width(),height());
}

void	ChangeCameraSetting::SlotToggled (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	if(checked==true){
		Button.setColor(PushedColor);
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
			GetLayersBase()->ClearAllAckFlag();
			GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ChangeCameraSetting_LS,LID_0)/*"Changing camera setting"*/);
			QCoreApplication::processEvents();

			for(int page=0;page<GetPageNumb();page++){
				GUICmdChangeCameraSetting	RCmd(GetLayersBase(),sRoot,sName,page);
				RCmd.FormName=GetName();
				RCmd.Send(NULL,page,0);
			}
			GetLayersBase()->WaitAllAcknowledged(60*100);
			GetLayersBase()->CloseProcessingForm ();
		}
	}
	else{
		Button.setColor(NormalColor);
	}
	GUIFormBase *SameForms[1000];
	int	N=GetLayersBase()->EnumGUIInst(sRoot,sName ,SameForms ,1000);
	for(int i=0;i<N;i++){
		if(SameForms[i]->GetName()==GetName() || SameForms[i]==this){
			continue;
		}
		ChangeCameraSetting	*a=dynamic_cast<ChangeCameraSetting *>(SameForms[i]);
		if(a!=NULL){
			a->Button.setChecked(false);
		}
	}
	
	ReEntrant=false;
}
	
void	ChangeCameraSetting::ChangeCamSetting(void)
{
	if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->LoadCameraSetting(CameraSettingFileName);
		}
	}
}

void	ChangeCameraSetting::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdChangeCameraSettingFile	*CmdChangeCameraSettingFileVar=dynamic_cast<CmdChangeCameraSettingFile *>(packet);
	if(CmdChangeCameraSettingFileVar!=NULL){
		if(GetLayersBase()->IsLocalCamera()==true){
			if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
					GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->LoadCameraSetting(CmdChangeCameraSettingFileVar->CameraSettingFileName);
				}
			}
		}
		else{
			GetLayersBase()->ClearAllAckFlag();
			GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ChangeCameraSetting_LS,LID_0)/*"Changing camera setting"*/);
			QCoreApplication::processEvents();

			for(int page=0;page<GetPageNumb();page++){
				GUICmdChangeCameraSettingFile	RCmd(GetLayersBase(),sRoot,sName,page);
				RCmd.CameraSettingFileName=CmdChangeCameraSettingFileVar->CameraSettingFileName;
				RCmd.Send(NULL,page,0);
			}
			GetLayersBase()->WaitAllAcknowledged(60*100);
			GetLayersBase()->CloseProcessingForm ();
		}
		return;
	}
	CmdChangeCameraSettingData	*CmdChangeCameraSettingDataVar=dynamic_cast<CmdChangeCameraSettingData *>(packet);
	if(CmdChangeCameraSettingDataVar!=NULL){
		if(GetLayersBase()->IsLocalCamera()==true){
			if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
					QBuffer	Buff(&CmdChangeCameraSettingDataVar->CameraSettingData);
					if(Buff.open(QIODevice::ReadOnly)==true){
						GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->LoadCameraSetting(&Buff);
					}
				}
			}
		}
		else{
			GetLayersBase()->ClearAllAckFlag();
			GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ChangeCameraSetting_LS,LID_0)/*"Changing camera setting"*/);
			QCoreApplication::processEvents();

			for(int page=0;page<GetPageNumb();page++){
				GUICmdChangeCameraSettingData	RCmd(GetLayersBase(),sRoot,sName,page);
				RCmd.CameraSettingData=CmdChangeCameraSettingDataVar->CameraSettingData;
				RCmd.Send(NULL,page,0);
			}
			GetLayersBase()->WaitAllAcknowledged(60*100);
			GetLayersBase()->CloseProcessingForm ();
		}
		return;
	}
}

void	ChangeCameraSetting::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*s=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(s!=NULL){
		QVariant	data;
		if(GetLayersBase()->LoadMasterFieldData(/**/"CameraSetting", data)==true){
			if(data.isValid()==true){
				QByteArray	BArray=data.toByteArray();
				QBuffer	Buff(&BArray);
				Buff.open(QIODevice::ReadOnly);
				int32	PageNumb;
				::Load(&Buff,PageNumb);
				for(int page=0;page<PageNumb && page<GetPageNumb();page++){
					QByteArray	PageData;
					::Load(&Buff,PageData);
					if(PageData.isNull()==false){
						GUICmdChangeCameraSettingData	RCmd(GetLayersBase(),sRoot,sName,page);
						RCmd.CameraSettingData=PageData;
						RCmd.Send(NULL,page,0);
					}
				}
			}
		}
		return;
	}
	CreateNewMasterSpecifiedBroadcaster		*c1=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	CreateUpdateMasterSpecifiedBroadcaster	*c2=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	if(c1!=NULL || c2!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		int32	PageNumb=GetPageNumb();
		::Save(&Buff,PageNumb);
		for(int page=0;page<PageNumb;page++){
			GUICmdLoadCameraSettingData	RCmd(GetLayersBase(),sRoot,sName,page);
			RCmd.Send(NULL,page,0);
			::Save(&Buff,RCmd.CameraSettingData);
		}
		QVariant	data=Buff.buffer();
		GetLayersBase()->AddMasterFieldData(/**/"CameraSetting", data);
		return;
	}
}

//==================================================================================================

GUICmdChangeCameraSetting::GUICmdChangeCameraSetting(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdChangeCameraSetting::~GUICmdChangeCameraSetting(void)
{
}

bool	GUICmdChangeCameraSetting::Load(QIODevice *f)
{
	if(::Load(f,FormName)==false)
		return false;
	return true;
}
	
bool	GUICmdChangeCameraSetting::Save(QIODevice *f)
{
	if(::Save(f,FormName)==false)
		return false;
	return true;
}

void	GUICmdChangeCameraSetting::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot ,sName ,FormName);
	ChangeCameraSetting	*a=dynamic_cast<ChangeCameraSetting *>(f);
	if(a!=NULL){
		a->ChangeCamSetting();
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			a->Button.setChecked(true);
		}
	}
	SendAck(localPage);
}

//==================================================================================================

GUICmdChangeCameraSettingFile::GUICmdChangeCameraSettingFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdChangeCameraSettingFile::~GUICmdChangeCameraSettingFile(void)
{
}

bool	GUICmdChangeCameraSettingFile::Load(QIODevice *f)
{
	if(::Load(f,CameraSettingFileName)==false)
		return false;
	return true;
}
	
bool	GUICmdChangeCameraSettingFile::Save(QIODevice *f)
{
	if(::Save(f,CameraSettingFileName)==false)
		return false;
	return true;
}

void	GUICmdChangeCameraSettingFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot ,sName ,/**/"");
	ChangeCameraSetting	*a=dynamic_cast<ChangeCameraSetting *>(f);
	if(a!=NULL){
		a->ChangeCamSetting();
		if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
			ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
			if(E!=NULL){
				E->LoadCameraSetting(CameraSettingFileName);
			}
		}
	}
	SendAck(localPage);
}

//==================================================================================================

GUICmdChangeCameraSettingData::GUICmdChangeCameraSettingData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdChangeCameraSettingData::~GUICmdChangeCameraSettingData(void)
{
}

bool	GUICmdChangeCameraSettingData::Load(QIODevice *f)
{
	if(::Load(f,CameraSettingData)==false)
		return false;
	return true;
}
	
bool	GUICmdChangeCameraSettingData::Save(QIODevice *f)
{
	if(::Save(f,CameraSettingData)==false)
		return false;
	return true;
}

void	GUICmdChangeCameraSettingData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot ,sName ,/**/"");
	ChangeCameraSetting	*a=dynamic_cast<ChangeCameraSetting *>(f);
	if(a!=NULL){
		a->ChangeCamSetting();
		if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
			ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
			if(E!=NULL){
				QBuffer	Buff(&CameraSettingData);
				if(Buff.open(QIODevice::ReadOnly)==true){
					E->LoadCameraSetting(&Buff);
				}
			}
		}
	}
	SendAck(localPage);
}

//==================================================================================================

GUICmdLoadCameraSettingData::GUICmdLoadCameraSettingData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdLoadCameraSettingData::~GUICmdLoadCameraSettingData(void)
{
}

bool	GUICmdLoadCameraSettingData::Load(QIODevice *f)
{
	if(::Load(f,CameraSettingData)==false)
		return false;
	return true;
}
	
bool	GUICmdLoadCameraSettingData::Save(QIODevice *f)
{
	if(::Save(f,CameraSettingData)==false)
		return false;
	return true;
}

void	GUICmdLoadCameraSettingData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot ,sName ,/**/"");
	ChangeCameraSetting	*a=dynamic_cast<ChangeCameraSetting *>(f);
	if(a!=NULL){
		a->ChangeCamSetting();
		if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
			ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
			if(E!=NULL){
				QBuffer	Buff;
				if(Buff.open(QIODevice::WriteOnly)==true){
					E->SaveCameraSetting(&Buff);
					CameraSettingData=Buff.buffer();
				}
			}
		}
	}
	SendAck(localPage);
}


