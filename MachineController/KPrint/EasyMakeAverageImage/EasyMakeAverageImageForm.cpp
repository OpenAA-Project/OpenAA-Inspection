#include "EasyMakeAverageImageResource.h"
#include "EasyMakeAverageImageForm.h"
#include "ui_EasyMakeAverageImageForm.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "StartCaptureOnlyTarget.h"
#include "ButtonAutoScanningMode.h"
#include "XMakeAverageImage.h"
#include "XIntegrationSimpleImagePanel.h"
#include "..\ResultKidaOutput\ResultKidaOutput.h"
#include "XPropertyMakeAverageImagePacket.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

EasyMakeAverageImageForm::EasyMakeAverageImageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyMakeAverageImageForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	TargetSlaveNo=-1;
}

EasyMakeAverageImageForm::~EasyMakeAverageImageForm()
{
    delete ui;
}

void	EasyMakeAverageImageForm::ReadyParam(void)
{
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalScanningDone(int,int64))
			,this,SLOT(SlotScanningDone(int,int64))
			,Qt::QueuedConnection);

	CartonMenuForm	*f1=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(f1!=NULL){
		connect(f1,SIGNAL(SignalRun(bool)),this,SLOT(SlotRun(bool)));
	}

}

void	EasyMakeAverageImageForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqAverageDrawMode	*CmdReqAverageDrawModeVar=dynamic_cast<CmdReqAverageDrawMode *>(packet);
	if(CmdReqAverageDrawModeVar!=NULL){
		if(ui->toolButtonViewMaster->isChecked()==true)
			CmdReqAverageDrawModeVar->DrawAttr=MakeAverageImageDrawAttr::_None;
		if(ui->toolButtonViewLowSide->isChecked()==true)
			CmdReqAverageDrawModeVar->DrawAttr=MakeAverageImageDrawAttr::_Dark;
		if(ui->toolButtonViewHighSide->isChecked()==true)
			CmdReqAverageDrawModeVar->DrawAttr=MakeAverageImageDrawAttr::_Light;
		if(ui->toolButtonViewVariation->isChecked()==true)
			CmdReqAverageDrawModeVar->DrawAttr=MakeAverageImageDrawAttr::_Variable;
		if(ui->toolButtonViewAverage->isChecked()==true)
			CmdReqAverageDrawModeVar->DrawAttr=MakeAverageImageDrawAttr::_AverageWithManualItem;
		return;
	}
}
void EasyMakeAverageImageForm::on_toolButtonScan_clicked()
{
	ShowCountList();

	bool	ScanMode=ui->toolButtonScan->isChecked();
	if(TargetSlaveNo<0){
		for(int SlaveNo=0;SlaveNo<GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();SlaveNo++){
			IntegrationCmdStartScan	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.OnMode=ScanMode;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
	else{
		IntegrationCmdStartScan	RCmd(GetLayersBase(),sRoot,sName,TargetSlaveNo);
		RCmd.OnMode=ScanMode;
		RCmd.Send(NULL,TargetSlaveNo,0);
	}
	if(ScanMode==false){
		GUIFormBase	*f1=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f1!=NULL){
			QStringList Args;
			bool ExeReturn;
			if(ScanMode==true){
				Args.append("false");
			}
			else{
				Args.append("true");
			}
			f1->ExecuteMacro(/**/"SetInspectionRunOnly", Args, ExeReturn);
		}
		GUIFormBase	*f2=GetLayersBase()->FindByName(/**/"Integration",/**/"AutoGenerator",/**/"");
		if(f2!=NULL){
			QStringList Args;
			bool ExeReturn;
			if(ScanMode==true){
				Args.append("false");
			}
			else{
				Args.append("true");
			}
			f2->ExecuteMacro(/**/"SetInspectionRunOnly", Args, ExeReturn);
		}
	}

	if(ScanMode==true){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"IntegrationOutputController",/**/"");
		if(f!=NULL){
			IntegrationSetControlOutput	Cmd(GetLayersBase());
			Cmd.ControlMode	=_Abs_Blade;	//_Abs_NG;
			f->TransmitDirectly(&Cmd);
		}
	}
	else{
		GUIFormBase	*fc=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"IntegrationOutputController",/**/"");
		if(fc!=NULL){
			IntegrationSetControlOutput	Cmd(GetLayersBase());
			Cmd.ControlMode	=_FreeForResult;
			fc->TransmitDirectly(&Cmd);
		}
	}
}

void	EasyMakeAverageImageForm::SlotRun(bool pushed)
{
	if(pushed==true){
		LeavePage();
	}
}

void	EasyMakeAverageImageForm::LeavePage	(void)
{
	ui->toolButtonScan->setChecked(false);
	on_toolButtonScan_clicked();
}

void	EasyMakeAverageImageForm::ShowCountList(void)
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	ui->tableWidget->setColumnCount(N);
	int	PhaseNumb=GetPhaseNumb();
	ui->tableWidget->setRowCount(PhaseNumb);
	if(TargetSlaveNo<0){
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			IntegrationReqScanningCount	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckScanningCount	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			if(RCmd.Send(SlaveNo,0,ACmd)==true){
				if(PhaseNumb<ACmd.ScanningCountInPhaseNumb){
					PhaseNumb=ACmd.ScanningCountInPhaseNumb;
					ui->tableWidget->setRowCount(PhaseNumb);
				}
				for(int phase=0;phase<ACmd.ScanningCountInPhaseNumb;phase++){
					::SetDataToTable(ui->tableWidget ,SlaveNo ,phase,QString::number(ACmd.ScanningCountInPhase[phase]));
				}
			}
		}
	}
	else{
		IntegrationReqScanningCount	RCmd(GetLayersBase(),sRoot,sName,TargetSlaveNo);
		IntegrationAckScanningCount	ACmd(GetLayersBase(),sRoot,sName,TargetSlaveNo);
		if(RCmd.Send(TargetSlaveNo,0,ACmd)==true){
			if(PhaseNumb<ACmd.ScanningCountInPhaseNumb){
				PhaseNumb=ACmd.ScanningCountInPhaseNumb;
				ui->tableWidget->setRowCount(PhaseNumb);
			}
			for(int phase=0;phase<ACmd.ScanningCountInPhaseNumb;phase++){
				::SetDataToTable(ui->tableWidget ,TargetSlaveNo ,phase,QString::number(ACmd.ScanningCountInPhase[phase]));
			}
		}
	}
}

void EasyMakeAverageImageForm::RedrawImage(void)
{
	if(TargetSlaveNo>=0) {
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(TargetSlaveNo);
		if(m!=NULL){
			int	MachineCode=m->GetMachineCode();
			GUIFormBase *RetGUI[100];
			int	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint" ,/**/"EasyMakeAverageImagePanel" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));
			for(int i=0;i<N;i++){
				IntegrationAlgoSimpleImagePanel	*a=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(RetGUI[i]);
				if(a!=NULL){
					if(a->MachineCode==MachineCode){
						a->Repaint();
					}
				}
			}
		}
	}
}

void EasyMakeAverageImageForm::on_toolButtonGenerateImage_clicked()
{
	if(TargetSlaveNo<0){
		for(int SlaveNo=0;SlaveNo<GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();SlaveNo++){
			IntegrationGenerateAverageImage	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
	else{
		IntegrationGenerateAverageImage	RCmd(GetLayersBase(),sRoot,sName,TargetSlaveNo);
		RCmd.Send(NULL,TargetSlaveNo,0);
	}
}
void EasyMakeAverageImageForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Phase=ui->tableWidget->currentRow();
	if(Phase<0)
		return;

	if(QMessageBox::question(nullptr, LangSolver.GetString(EasyMakeAverageImageForm_LS,LID_1)/*"�N���A"*/
						, LangSolver.GetString(EasyMakeAverageImageForm_LS,LID_2)/*"���ω����̃N���A"*/)==QMessageBox::Yes){
		for(int SlaveNo=0;SlaveNo<GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();SlaveNo++){
			IntegrationClearScanningCount	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase=Phase;
			RCmd.Send(NULL,SlaveNo,0);
		}
		ShowCountList();
	}
}

void	EasyMakeAverageImageForm::SlotScanningDone	(int SlaveNo,int64 InspectionID)
{
	ShowCountList();
}

void EasyMakeAverageImageForm::on_toolButtonViewAverage_clicked()
{
	RedrawImage();
}


void EasyMakeAverageImageForm::on_toolButtonViewVariation_clicked()
{
	RedrawImage();
}


void EasyMakeAverageImageForm::on_toolButtonViewHighSide_clicked()
{
	RedrawImage();
}


void EasyMakeAverageImageForm::on_toolButtonViewLowSide_clicked()
{
	RedrawImage();
}

void EasyMakeAverageImageForm::on_toolButtonViewMaster_clicked()
{
	RedrawImage();
}


void EasyMakeAverageImageForm::on_toolButtonResetAverage_clicked()
{
	if(QMessageBox::question(nullptr
						, "注意"
						, "平均化をクリアしてもいいですか？　反映したマスター画像は残ります。")==QMessageBox::Yes){
		for(int SlaveNo=0;SlaveNo<GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();SlaveNo++){
			IntegrationResetAverageImage	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Send(NULL,SlaveNo,0);
		}
		RedrawImage();
	}
}


//=========================================================================================================================

IntegrationCmdStartScan::IntegrationCmdStartScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdStartScan::Load(QIODevice *f)
{
	if(::Load(f,OnMode)==false)
		return false;
	return true;
}
bool	IntegrationCmdStartScan::Save(QIODevice *f)
{
	if(::Save(f,OnMode)==false)
		return false;
	return true;
}

void	IntegrationCmdStartScan::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f1=GetLayersBase()->FindByName(/**/"Inspection",/**/"StartCaptureOnlyTarget",/**/"");
	if(f1!=NULL){
		CmdSetStateStartCaptureOnlyTarget	RCmd(GetLayersBase());
		RCmd.StartCaptureOnlyTargetOn=OnMode;
		f1->TransmitDirectly(&RCmd);
	}
	GUIFormBase	*f2=GetLayersBase()->FindByName(/**/"Button",/**/"AutoScanningMode",/**/"");
	if(f2!=NULL){
		CmdSetScanningStateOnAutoMode	RCmd(GetLayersBase());
		RCmd.AutoModeOn=OnMode;
		f2->TransmitDirectly(&RCmd);
	}
}
//=========================================================================================================================

IntegrationReqScanningCount::IntegrationReqScanningCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationReqScanningCount::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckScanningCount	*SendBack=GetSendBackIntegration(IntegrationAckScanningCount,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	SendBack->ScanningCountInPhaseNumb	=GetPhaseNumb();
	SendBack->ScanningCountInPhase=new int32[SendBack->ScanningCountInPhaseNumb];
	memset(SendBack->ScanningCountInPhase,0,sizeof(int32)*SendBack->ScanningCountInPhaseNumb);
	MakeAverageImageBase	*ABase=(MakeAverageImageBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MakeAverageImage");
	if(ABase!=NULL){
		CmdGetAddedCountByPhases	RCmd(GetLayersBase());
		RCmd.AddedCountByPhases=SendBack->ScanningCountInPhase;
		ABase->TransmitDirectly(&RCmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}
	
IntegrationAckScanningCount::IntegrationAckScanningCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	ScanningCountInPhase	=NULL;
	ScanningCountInPhaseNumb=0;
}
IntegrationAckScanningCount::~IntegrationAckScanningCount(void)
{
	if(ScanningCountInPhase!=NULL){
		delete	[]ScanningCountInPhase;
		ScanningCountInPhase=NULL;
	}
	ScanningCountInPhaseNumb=0;
}
bool	IntegrationAckScanningCount::Load(QIODevice *f)
{
	if(::Load(f,ScanningCountInPhaseNumb)==false)
		return false;
	if(ScanningCountInPhase!=NULL){
		delete	[]ScanningCountInPhase;
		ScanningCountInPhase=NULL;
	}
	if(ScanningCountInPhaseNumb!=0){
		ScanningCountInPhase=new int32[ScanningCountInPhaseNumb];
		if(f->read((char *)ScanningCountInPhase,sizeof(ScanningCountInPhase[0])*ScanningCountInPhaseNumb)!=sizeof(ScanningCountInPhase[0])*ScanningCountInPhaseNumb){
			return false;
		}
	}
	return true;
}
bool	IntegrationAckScanningCount::Save(QIODevice *f)
{
	if(::Save(f,ScanningCountInPhaseNumb)==false)
		return false;
	if(ScanningCountInPhaseNumb!=0){
		if(f->write((const char *)ScanningCountInPhase,sizeof(ScanningCountInPhase[0])*ScanningCountInPhaseNumb)!=sizeof(ScanningCountInPhase[0])*ScanningCountInPhaseNumb){
			return false;
		}
	}
	return true;
}
//=========================================================================================================================
IntegrationClearScanningCount::IntegrationClearScanningCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationClearScanningCount::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	return true;
}
bool	IntegrationClearScanningCount::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	return true;
}
void	IntegrationClearScanningCount::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MakeAverageImageBase	*ABase=(MakeAverageImageBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MakeAverageImage");
	if(ABase!=NULL){
		CmdClearAverage	RCmd(GetLayersBase());
		RCmd.Phase=Phase;
		ABase->TransmitDirectly(&RCmd);
	}
}
//=========================================================================================================================
IntegrationGenerateAverageImage::IntegrationGenerateAverageImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationGenerateAverageImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MakeAverageImageBase	*ABase=(MakeAverageImageBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MakeAverageImage");
	if(ABase!=NULL){
		CmdExecuteAverage	RCmd(GetLayersBase());
		ABase->TransmitDirectly(&RCmd);
	}
}

//=========================================================================================================================
IntegrationResetAverageImage::IntegrationResetAverageImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationResetAverageImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"EasyMakeAverageImage",/**/"");
	if(f!=NULL){
		CmdReqReset	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
	}
}

