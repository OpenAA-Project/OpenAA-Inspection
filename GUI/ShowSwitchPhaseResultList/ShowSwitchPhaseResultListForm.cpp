#include "ShowSwitchPhaseResultListForm.h"
#include "ui_ShowSwitchPhaseResultListForm.h"
#include "XGeneralFunc.h"
#include "XSwitchPhase.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowSwitchPhaseResultListForm::ShowSwitchPhaseResultListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowSwitchPhaseResultListForm)
{
    ui->setupUi(this);
	Horizontal	=true;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowSwitchPhaseResultListForm::~ShowSwitchPhaseResultListForm()
{
    delete ui;
}

void	ShowSwitchPhaseResultListForm::ResizeAction()
{
	ui->stackedWidget->resize(width(),height()-ui->pushButtonClear->height());
	ui->tableWidgetHorizontal->resize(width(),height()-ui->pushButtonClear->height());
	ui->tableWidgetVertical	 ->resize(width(),height()-ui->pushButtonClear->height());
	ui->pushButtonClear->move(0,height()-ui->pushButtonClear->height());
}

void	ShowSwitchPhaseResultListForm::Prepare(void)
{
	if(Horizontal==true)
		ui->stackedWidget->setCurrentIndex(0);
	else
		ui->stackedWidget->setCurrentIndex(1);
}
void	ShowSwitchPhaseResultListForm::BuildForShow(void)
{
	if(Horizontal==true){
		ui->tableWidgetHorizontal->setColumnCount(GetPhaseNumb());
		QStringList	Labels;
		for(int phase=0;phase<GetPhaseNumb();phase++){
			Labels.append(GetParamGlobal()->GetPhaseString(phase));
		}
		ui->tableWidgetHorizontal->setVerticalHeaderLabels(Labels);
	}
	else{
		ui->tableWidgetVertical->setRowCount(GetPhaseNumb());
		QStringList	Labels;
		for(int phase=0;phase<GetPhaseNumb();phase++){
			Labels.append(GetParamGlobal()->GetPhaseString(phase));
		}
		ui->tableWidgetVertical->setHorizontalHeaderLabels(Labels);
	}
}

void	ShowSwitchPhaseResultListForm::ShowInPlayer(int64 shownInspectionID)
{
	if(IsShown()==true){
		GUICmdReqSwitchPhaseResult	RCmd(GetLayersBase(),sRoot,sName,0);
		GUICmdAckSwitchPhaseResult	ACmd(GetLayersBase(),sRoot,sName,0);
		if(RCmd.Send(0,0,ACmd)==true){
			if(Horizontal==true){
				for(int phase=0;phase<GetPhaseNumb();phase++){
					SetDataToTable(ui->tableWidgetHorizontal,phase ,0,QString::number(ACmd.InspectionCountInPhase[phase]));
				}
			}
			else{
				for(int phase=0;phase<GetPhaseNumb();phase++){
					SetDataToTable(ui->tableWidgetVertical,0,phase,QString::number(ACmd.InspectionCountInPhase[phase]));
				}
			}				
		}
	}
}

void ShowSwitchPhaseResultListForm::on_pushButtonClear_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearSwitchPhaseResult	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
	ShowInPlayer(0);
}

//============================================================================================

GUICmdReqSwitchPhaseResult::GUICmdReqSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqSwitchPhaseResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSwitchPhaseResult	*SendBack=GetSendBack(GUICmdAckSwitchPhaseResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(BBase!=NULL){
		SendBack->InspectionCountInPhaseNumb=GetPhaseNumb();
		if(SendBack->InspectionCountInPhase!=NULL){
			delete	[]SendBack->InspectionCountInPhase;
			SendBack->InspectionCountInPhase=NULL;
		}
		SendBack->InspectionCountInPhase=new int32[GetPhaseNumb()];
		for(int phase=0;phase<GetPhaseNumb();phase++){
			SendBack->InspectionCountInPhase[phase]=BBase->InspectionCountInPhase[phase];
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSwitchPhaseResult::GUICmdAckSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	InspectionCountInPhase		=NULL;
	InspectionCountInPhaseNumb	=0;
}
GUICmdAckSwitchPhaseResult::~GUICmdAckSwitchPhaseResult(void)
{
	if(InspectionCountInPhase!=NULL){
		delete	[]InspectionCountInPhase;
		InspectionCountInPhase=NULL;
	}
	InspectionCountInPhaseNumb=0;
}
bool	GUICmdAckSwitchPhaseResult::Load(QIODevice *f)
{
	if(::Load(f,InspectionCountInPhaseNumb)==false)
		return false;
	if(InspectionCountInPhase!=NULL){
		delete	[]InspectionCountInPhase;
		InspectionCountInPhase=NULL;
	}
	if(InspectionCountInPhaseNumb!=0){
		InspectionCountInPhase=new int32[InspectionCountInPhaseNumb];
		if(f->read((char *)InspectionCountInPhase,sizeof(int32)*InspectionCountInPhaseNumb)!=sizeof(int32)*InspectionCountInPhaseNumb){
			return false;
		}
	}
	return true;
}
bool	GUICmdAckSwitchPhaseResult::Save(QIODevice *f)
{
	if(::Save(f,InspectionCountInPhaseNumb)==false)
		return false;
	if(InspectionCountInPhaseNumb!=NULL){
		if(f->write((const char *)InspectionCountInPhase,sizeof(int32)*InspectionCountInPhaseNumb)!=sizeof(int32)*InspectionCountInPhaseNumb){
			return false;
		}
	}
	return true;
}

GUICmdClearSwitchPhaseResult::GUICmdClearSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdClearSwitchPhaseResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(BBase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			BBase->InspectionCountInPhase[phase]=0;
		}
	}
}