#include "EasyPropertySwitchPhaseResource.h"
#include "EasyPropertySwitchPhaseForm.h"
#include "ui_EasyPropertySwitchPhaseForm.h"
#include "InputPanelDialog.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "PropertySwitchPhaseForm.h"
#include "IntegrationChangePhaseForm.h"
#include "..\ResultKidaOutput\ResultKidaOutput.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

EasyPropertySwitchPhaseForm::EasyPropertySwitchPhaseForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyPropertySwitchPhaseForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo=0;
	StartPhaseNo=1;

	connect(this,SIGNAL(SignalLoadPhaseImage(int)),this,SLOT(SlotLoadPhaseImage(int)),Qt::QueuedConnection);
}

EasyPropertySwitchPhaseForm::~EasyPropertySwitchPhaseForm()
{
    delete ui;
}

void	EasyPropertySwitchPhaseForm::ReadyParam(void)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertySwitchPhase",/**/"");
	if(f!=NULL){
		PropertySwitchPhaseForm	*Form=dynamic_cast<PropertySwitchPhaseForm *>(f);
		if(Form!=NULL){
			connect(Form,SIGNAL(SignalSwitchedImage(int)),this,SLOT(SlotSwitchedImage(int)));
		}
	}
	GUIFormBase *RetForm[1000];
	int N=GetLayersBase()->EnumGUIInst(/**/"Integration",/**/"ChangePhase",RetForm ,sizeof(RetForm)/sizeof(RetForm[0]));
	for(int i=0;i<N;i++){
		IntegrationChangePhaseForm	*g=dynamic_cast<IntegrationChangePhaseForm *>(RetForm[i]);
		if(g!=NULL && GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(g->MachineCode)==SlaveNo){
			connect(g,SIGNAL(SignalChangePhase(int)),this,SLOT(SlotChangePhase(int)));
		}
	}
	ui->toolButtonFinishCalc->setVisible(false);	//Now it makes invalid shift for all algorithm items
}

void EasyPropertySwitchPhaseForm::on_PushButtonSetPhaseCount_clicked()
{
	EachMaster	*f=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(f!=NULL){
	    InputPanelDialog	D(IPD_Number ,QString(/**/"0"));
		if(D.exec()==(bool)true){
			QString StrCount=D.GetResult();
			bool	ok;
			int	PhaseCount=StrCount.toInt(&ok);
			if(ok==true){
				QStringList	Str;
				for(int i=0;i<PhaseCount;i++){
					Str.append(QString(/**/"Phase")+QString::number(f->GetPhaseNumb()+i));
				}
				GetLayersBase()->GetIntegrationBasePointer()->AddPhase(SlaveNo,Str);
				BroadcastShowInEdit();
			}
		}
    }
}

void	EasyPropertySwitchPhaseForm::LeavePage	(void)
{
	if(ui->toolButtonCaptureFrom1->isChecked()==true){
		ui->toolButtonCaptureFrom1->setChecked(false);
		on_toolButtonCaptureFrom1_clicked();
	}
}

void	EasyPropertySwitchPhaseForm::SlotSwitchedImage(int PhaseNo)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL){
		int	OwnSlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->OwnSlaveNo;
		CmdSignalLoadMasterImage	Cmd(GetLayersBase(),sRoot,sName);
		Cmd.Phase=PhaseNo;
		Cmd.SendFromSlaveToMaster(OwnSlaveNo,0);
	}
}

void	EasyPropertySwitchPhaseForm::ExeLoadPhaseImage(int Phase)
{
	emit	SignalLoadPhaseImage(Phase);
}

void	EasyPropertySwitchPhaseForm::SlotLoadPhaseImage(int Phase)
{
	EachMaster	*f=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(f!=NULL){
		GetLayersBase()->ShowProcessingForm(/**/"Load image");
		GetLayersBase()->SetMaxProcessing(-1);
		f->RequireMasterImageInPhase(Phase,GetParamGlobal()->MixMasterForIntegration);
		f->SetCurrentPhase(Phase);
		GetLayersBase()->CloseProcessingForm();
		SlotChangePhase(Phase+1);
		BroadcastRepaintAll();
	}
}

void EasyPropertySwitchPhaseForm::on_toolButtonCaptureFrom1_clicked()
{
	if(ui->toolButtonCaptureFrom1->isChecked()==true){
		IntegrationCmdScanFrom1	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.StartPhaseNo	=StartPhaseNo;
		RCmd.Send(NULL,SlaveNo,0);

		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"IntegrationOutputController",/**/"");
		if(f!=NULL){
			IntegrationSetControlOutput	Cmd(GetLayersBase());
			Cmd.ControlMode	=_Abs_Blade;	//_Abs_NG;
			f->TransmitDirectly(&Cmd);
		}
	}
	else{
		IntegrationCmdCancelScan	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Send(NULL,SlaveNo,0);
		EachMaster	*f=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(f!=NULL){
			f->SetCurrentPhase(0);
			BroadcastRepaintAll();
		}
		GUIFormBase	*fc=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"IntegrationOutputController",/**/"");
		if(fc!=NULL){
			IntegrationSetControlOutput	Cmd(GetLayersBase());
			Cmd.ControlMode	=_FreeForResult;
			fc->TransmitDirectly(&Cmd);
		}
	}
}

void	EasyPropertySwitchPhaseForm::SlotChangePhase(int phasecode)
{
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas[SlaveNo];
	if(m!=NULL){
		if(phasecode>=m->GetPhaseNumb()){
			ui->toolButtonCaptureFrom1->setChecked(false);
			on_toolButtonCaptureFrom1_clicked();
		}
		else{
			StartPhaseNo=phasecode;
			ui->toolButtonCaptureFrom1->setText(QString::number(StartPhaseNo+1)+QString(LangSolver.GetString(EasyPropertySwitchPhaseForm_LS,LID_1)/*"縺九ｉ謦ｮ蠖ｱ"*/));
		}
	}
}

void EasyPropertySwitchPhaseForm::on_toolButtonFinishCalc_clicked()
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(EasyPropertySwitchPhaseForm_LS,LID_4)/*"險ｭ螳夂｢ｺ螳壻ｸｭ"*/);
	GetLayersBase()->SetMaxProcessing(6);

	GetLayersBase()->GetIntegrationBasePointer()->ExecuteInitialAfterEdit(SlaveNo);
	emit	SignalBusy();

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();
	GetLayersBase()->CloseProcessingForm();
}
void EasyPropertySwitchPhaseForm::on_toolButtonDeleteAllAddition_clicked()
{
	if(QMessageBox::warning(NULL
		,LangSolver.GetString(EasyPropertySwitchPhaseForm_LS,LID_2)/*"隴ｦ蜻�*/								,LangSolver.GetString(EasyPropertySwitchPhaseForm_LS,LID_3)/*"霑ｽ蜉�縺励◆逕ｻ蜒上�縺吶∋縺ｦ繧貞炎髯､縺励※繧ゅ＞縺�〒縺吶°��*/
		,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		DeleteAllAdditionalPhases();
	}
}
void	EasyPropertySwitchPhaseForm::DeleteAllAdditionalPhases(void)
{
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo)	;
	if(m!=NULL){
		GetLayersBase()->ShowProcessingForm(/**/"險ｭ螳夂｢ｺ螳壻ｸｭ");
		GetLayersBase()->SetMaxProcessing(m->GetPhaseNumb()-1);

		IntList	PhaseList;
		for(int phase=m->GetPhaseNumb()-1;phase>=1;phase--){
			m->RemovePhase(phase);
			GetLayersBase()->StepProcessing(0);
		}
			
		IntegrationCmdDeleteAllPhases	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Send(NULL,SlaveNo,0);

		BroadcastShowInEdit();
		GetLayersBase()->CloseProcessingForm();
	}
}

void EasyPropertySwitchPhaseForm::on_PushButtonAutoGeneration_clicked()
{
	IntegrationCmdMakeAutoGeneration	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.Send(NULL,SlaveNo,0);
}

//=============================================================================================
IntegrationCmdScanFrom1::IntegrationCmdScanFrom1(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdScanFrom1::Load(QIODevice *f)
{
	if(::Load(f,StartPhaseNo)==false)	return false;
	return true;
}
bool	IntegrationCmdScanFrom1::Save(QIODevice *f)
{
	if(::Save(f,StartPhaseNo)==false)	return false;
	return true;
}

void	IntegrationCmdScanFrom1::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(/**/"Button",/**/"PropertySwitchPhase",GUIRet ,100);
	for(int i=0;i<n;i++){
		QStringList Args;
		Args.append(QString::number(StartPhaseNo));
		bool ExeReturn;
		GUIRet[i]->ExecuteMacro(/**/"ScanFrom1", Args, ExeReturn);
		break;
	}
}
//=============================================================================================
IntegrationCmdCancelScan::IntegrationCmdCancelScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdCancelScan::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(/**/"Button",/**/"PropertySwitchPhase",GUIRet ,100);
	for(int i=0;i<n;i++){
		QStringList Args;
		bool ExeReturn;
		GUIRet[i]->ExecuteMacro(/**/"CancelScan", Args, ExeReturn);
		break;
	}
}

//=======================================================================================
CmdSignalLoadMasterImage::CmdSignalLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	CmdSignalLoadMasterImage::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	return true;
}
bool	CmdSignalLoadMasterImage::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	return true;
}

void	CmdSignalLoadMasterImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		EasyPropertySwitchPhaseForm	*GUI=dynamic_cast<EasyPropertySwitchPhaseForm *>(GUIRet[i]);
		if(GUI!=NULL){
			if(GUI->SlaveNo==slaveNo){
				GUI->ExeLoadPhaseImage(Phase);
			}
		}
	}
}

//=======================================================================================

IntegrationCmdMakeAutoGeneration::IntegrationCmdMakeAutoGeneration(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdMakeAutoGeneration::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(/**/"Button",/**/"PropertySwitchPhase",GUIRet ,100);
	for(int i=0;i<n;i++){
		QStringList Args;
		bool ExeReturn;
		GUIRet[i]->ExecuteMacro(/**/"AutoGeneration", Args, ExeReturn);
		break;
	}
}

IntegrationCmdDeleteAllPhases::IntegrationCmdDeleteAllPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdDeleteAllPhases::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(/**/"Button",/**/"PropertySwitchPhase",GUIRet ,100);
	for(int i=0;i<n;i++){
		QStringList Args;
		bool ExeReturn;
		GUIRet[i]->ExecuteMacro(/**/"DeleteAllPhases", Args, ExeReturn);
		break;
	}
}

