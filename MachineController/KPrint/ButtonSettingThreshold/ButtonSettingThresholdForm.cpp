#include "ButtonSettingThresholdResource.h"
#include "ButtonSettingThresholdForm.h"
#include "ui_ButtonSettingThresholdForm.h"
#include "MenuThresholdDialog.h"
#include "IntegrationStackNGThumbnailForm.h"
#include "XEachThresholdCommon.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ThresholdWholeHistoryList::ThresholdWholeHistoryList(void)
{
	ATime=XDateTime::currentDateTime();
}

bool	ThresholdWholeHistoryList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)	return false;

	if(::Save(f,LibType			)==false)	return false;
	if(::Save(f,LibID			)==false)	return false;
	if(::Save(f,BrightnessDark	)==false)	return false;
	if(::Save(f,BrightnessLight	)==false)	return false;
	if(::Save(f,Shift			)==false)	return false;
	if(::Save(f,OKDotB			)==false)	return false;
	if(::Save(f,OKLengthB		)==false)	return false;
	if(::Save(f,OKDotN			)==false)	return false;
	if(::Save(f,OKLengthN		)==false)	return false;
	if(::Save(f,RedOKDot		)==false)	return false;
	if(::Save(f,MultiSpotDot	)==false)	return false;
	if(::Save(f,MultiSpotCount	)==false)	return false;
	if(::Save(f,AreaSearchX		)==false)	return false;
	if(::Save(f,AreaSearchY		)==false)	return false;
	if(::Save(f,SelfSearch		)==false)	return false;
	if(::Save(f,Enabled			)==false)	return false;

	if(Area.Save(f)==false)	return false;
	if(::Save(f,ATime)==false)	return false;

	return true;
}
bool	ThresholdWholeHistoryList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)	return false;
	if(Ver==1){
		if(::Load(f,LibType			)==false)	return false;
		if(::Load(f,LibID			)==false)	return false;
		if(::Load(f,BrightnessDark	)==false)	return false;
		if(::Load(f,BrightnessLight	)==false)	return false;
		if(::Load(f,Shift			)==false)	return false;
		if(::Load(f,OKDotB			)==false)	return false;
		if(::Load(f,OKLengthB		)==false)	return false;
		if(::Load(f,OKDotN			)==false)	return false;
		if(::Load(f,OKLengthN		)==false)	return false;
		if(::Load(f,RedOKDot		)==false)	return false;
		if(::Load(f,MultiSpotDot	)==false)	return false;
		if(::Load(f,MultiSpotCount	)==false)	return false;
		if(::Load(f,AreaSearchX		)==false)	return false;
		if(::Load(f,AreaSearchY		)==false)	return false;
		if(::Load(f,SelfSearch		)==false)	return false;
		if(::Load(f,Enabled			)==false)	return false;

		if(Area.Load(f)==false)	return false;
		if(::Load(f,ATime)==false)	return false;

		return true;
	}
	return false;
}

//=====================================================================

ButtonSettingThresholdForm::ButtonSettingThresholdForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ButtonSettingThresholdForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SlaveNo=0;
	TargetImageWithNGBuff	=NULL;
	TargetImageWithNGXLen	=0;
	TargetImageWithNGYLen	=0;

	Window=new MenuThresholdDialog(GetLayersBase(),this);
	ui->PushButtonThreshold->move(0,0);
	Msg=/**/"Set Threshold";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalShowWindow()),this,SLOT(SlotShowWindow()),Qt::QueuedConnection);
}

ButtonSettingThresholdForm::~ButtonSettingThresholdForm()
{
    delete ui;
	Window->deleteLater();

	if(TargetImageWithNGBuff!=NULL){
		delete	[]TargetImageWithNGBuff;
	}
	TargetImageWithNGBuff	=NULL;
	TargetImageWithNGXLen	=0;
	TargetImageWithNGYLen	=0;
}

void	ButtonSettingThresholdForm::Prepare(void)
{
	ui->PushButtonThreshold->setText(Msg);
	ui->PushButtonThreshold->setFont (CFont);
	ResizeAction();
}

void	ButtonSettingThresholdForm::ReadyParam(void)
{
	GUIFormBase	*thumbnailform=GetLayersBase()->FindByName(/**/"Integration",/**/"StackNGThumbnail",/**/"");
	if(thumbnailform!=NULL){
		connect(thumbnailform,SIGNAL(SignalReqDetail(EachMaster * ,InspectionList *, InspectionList *, NGPoint *,int,int,IntList&))
				,this,SLOT(SlotReqDetail(EachMaster * ,InspectionList *, InspectionList *, NGPoint *,int,int,IntList&)));
	}
}

void	ButtonSettingThresholdForm::ResizeAction()
{
	ui->PushButtonThreshold->resize(width(),height());
}

void	ButtonSettingThresholdForm::TransmitDirectly(GUIDirectMessage *packet)
{
	IntegrationClickSettingThresholdForm	*IntegrationClickSettingThresholdFormVar=dynamic_cast<IntegrationClickSettingThresholdForm *>(packet);
	if(IntegrationClickSettingThresholdFormVar!=NULL){
		on_PushButtonThreshold_clicked();
	}
}
void	ButtonSettingThresholdForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateUpdateMasterSpecifiedBroadcaster	*CmdUpdatedMasterImageVar=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	CreateNewMasterSpecifiedBroadcaster		*CmdSavedMasterImageVar	 =dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(CmdUpdatedMasterImageVar!=NULL || CmdSavedMasterImageVar!=NULL){
		SaveDataIntoMasterData();
		return;
	}
}

void ButtonSettingThresholdForm::on_PushButtonThreshold_clicked()
{
	Window->SetActiveArea(EachThresholdCommon::_AreaTypeNothing);
	Window->exec();
}

void	ButtonSettingThresholdForm::ShowMenuWindow(void)
{
	emit	SignalShowWindow();
}

void	ButtonSettingThresholdForm::SlotShowWindow()
{
	Window->exec();
}
void	ButtonSettingThresholdForm::SlotReqDetail(EachMaster *m ,InspectionList *Result, InspectionList *CurrentInspection, NGPoint *RepresentativePoint
												,int Phase ,int Page ,IntList &ItemID)
{
	if(m->GetIntegrationSlaveNo()==SlaveNo){
		IntegrationReqAreaType	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckAreaType	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Phase	=Phase;
		RCmd.Page	=Page;
		RCmd.ItemID	=ItemID;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			Window->SetActiveArea(ACmd.AreaType);
			Window->SetActivePosition(Phase,Page,ACmd.GlobalX,ACmd.GlobalY,ItemID);
			Window->exec();
		}
	}
}

void	ButtonSettingThresholdForm::BuildForShow(void)
{
	LoadDataFromMasterData();
}

bool	ButtonSettingThresholdForm::SaveDataIntoMasterData(void)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(HistoryContainer.Save(&Buff)==false)
		return false;
	QVariant	data=Buff.buffer();
	bool	Ret=false;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL && m->GetMasterCode()>0){
		Ret=GetLayersBase()->AddMasterFieldData(m->GetMasterCode(),/**/"BSThreshold", data);
	}
	return Ret;
}
bool	ButtonSettingThresholdForm::LoadDataFromMasterData(void)
{
	QVariant	data;
	bool	Ret=false;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL && m->GetMasterCode()>0){
		Ret=GetLayersBase()->LoadMasterFieldData(m->GetMasterCode(),/**/"BSThreshold", data);
	}
	if(Ret==true){
		HistoryContainer.RemoveAll();
		QByteArray	A=data.toByteArray();
		QBuffer	Buff(&A);
		Buff.open(QIODevice::ReadWrite);
		if(HistoryContainer.Load(&Buff)==false){
			return false;
		}
	}
	return Ret;
}
