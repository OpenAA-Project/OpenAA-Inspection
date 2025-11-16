#include "CartonMenuResource.h"
#include "OthersDialog.h"
#include "ui_OthersDialog.h"
#include "CartonMenuForm.h"
#include "SetThresholdDialog.h"
#include "IntegrationShowConnectionState.h"
#include "IntegrationShowMemoryForm.h"
#include "EasyLevelAllocationForm.h"
#include "InputBeltSpeedDialog.h"

OthersDialog::OthersDialog(LayersBase *Base ,CartonMenuForm *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),Parent(p),
    ui(new Ui::OthersDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	IntegrationShowConnectionState	*f=dynamic_cast<IntegrationShowConnectionState *>(GetLayersBase()->FindByName(/**/"Integration",/**/"ShowConnectionState",/**/""));
	if(f!=NULL){
		IntegrationGetConnectionState	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
		if(RCmd.State.GetCount()>=2){
			ui->checkBoxStateTop	->setChecked(RCmd.State[0]);
			ui->checkBoxStateBottom	->setChecked(RCmd.State[1]);
		}
	}
	bool	Ret=false;
	Mem=dynamic_cast<IntegrationShowMemoryForm *>(GetLayersBase()->FindByName(/**/"Integration",/**/"ShowMemory",/**/""));
	if(Mem!=NULL){
		Ret=(connect(Mem,SIGNAL(SignalShowMemory()),this,SLOT(SlotShowMemory())))?true:false;
	}
	ui->tableWidgetMemory->setColumnWidth(0,64);
	ui->tableWidgetMemory->setColumnWidth(1,64);

	SetRunningGray();

	TM.setInterval(1000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int ,int64,bool)),this,SLOT(SlotInspectionDone(int,int64 ,bool)));

	const	int	MachineCount = GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if (MachineCount == 1) {
		ui->checkBoxStateBottom->setVisible(false);
	}
	ui->tableWidgetMemory->setColumnCount(MachineCount);

	for(int i=0;i<MachineCount;i++){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(m!=NULL){
			QString	s=m->GetMachineName();
			if(i==0){
				ui->checkBoxStateTop	->setText(s);
			}
			else if(i==1){
				ui->checkBoxStateBottom	->setText(s);
			}
			else if(i==2){
				//ui->PushButtonMonoDetail3	->setText(s);
			}
		}
	}

	QStringList	HeaderList;
	::SetColumnWidthInTable(ui->tableWidgetMemory ,0, 40);
	for(int SlaveNo=0;SlaveNo<MachineCount;SlaveNo++){
		::SetColumnWidthInTable(ui->tableWidgetMemory ,1+SlaveNo, 60/MachineCount);
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas[SlaveNo];
		if(m!=NULL){
			HeaderList.append(m->GetMachineName());
		}
	}
	ui->tableWidgetMemory->setHorizontalHeaderLabels(HeaderList);
}

OthersDialog::~OthersDialog()
{
  	disconnect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int ,int64,bool)),this,SLOT(SlotInspectionDone(int,int64 ,bool)));
	disconnect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));

	delete ui;
}
void	OthersDialog::SetRunningGray(void)
{
	//if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		ui->PushButtonCheck			->setEnabled(true);
		ui->PushButtonNew			->setEnabled(true);
		ui->PushButtonSwitchImage	->setEnabled(true);
	//}
	//else{
	//	ui->PushButtonCheck			->setEnabled(false);
	//	ui->PushButtonNew			->setEnabled(false);
	//	ui->PushButtonSwitchImage	->setEnabled(false);
	//}
}
void OthersDialog::on_PushButtonLevel_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"EasyLevelAllocation",/**/"");
	if(f!=NULL){
		//f->ExecAsDialog(this);
		IntegrationShowLevelDialog	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
	}
	close();
}

void OthersDialog::on_PushButtonCheck_clicked()
{
	Parent->on_PushButtonCheck_clicked();
	close();
}

void OthersDialog::on_PushButtonSetting_clicked()
{
	Parent->on_PushButtonSetting_clicked();
	close();
}

void OthersDialog::on_PushButtonNew_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"NewMaster",/**/"");
	if(f!=NULL){
		QStringList Args;
		bool ExeReturn;
		f->ExecuteMacro(/**/"OpenDialog", Args, ExeReturn);
	}
	close();
}

void OthersDialog::on_PushButtonSwitchImage_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"WizardMasterMenu",/**/"");
	if(f!=NULL){
		QStringList Args;
		bool ExeReturn;
		f->ExecuteMacro(/**/"SwitchImage", Args, ExeReturn);
	}
	close();
}

void OthersDialog::on_PushButtonClose_clicked()
{
	close();
}

QString	MakeMemoryStr(unsigned long long N)
{
	if(N>1000000000ULL){
		double	fN=N;
		fN/=1024.0;
		fN/=1024.0;
		fN/=1024.0;
		return QString::number(fN,'f',2) +QString(/**/" GB");
	}
	if(N>1000000ULL){
		double	fN=N;
		fN/=1024.0;
		fN/=1024.0;
		return QString::number(fN,'f',2)+QString(/**/" MB");
	}
	if(N>1000ULL){
		double	fN=N;
		fN/=1024.0;
		return QString::number(fN,'f',2)+QString(/**/" KB");
	}
	double	fN=N;
	return QString::number(fN,'f',1)+QString(/**/"B");
}
void	OthersDialog::SlotShowMemory()
{
	if(Mem!=NULL){
		int	MachineCount = GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int SlaveNo=0;SlaveNo< MachineCount;SlaveNo++){
			::SetDataToTable(ui->tableWidgetMemory,SlaveNo,0,MakeMemoryStr(Mem->MachineMemory[SlaveNo].ShowMemoryStruct.ullAvailPhys));
		}
	}
}

void	OthersDialog::SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK)
{
	SetRunningGray();
}

void	OthersDialog::SlotTimeOut()
{
	SetRunningGray();
}

void OthersDialog::on_PushButtonSetBeltVelocity_clicked()
{
	InputBeltSpeedDialog	D(GetLayersBase(),Parent);
	if(D.exec()==true){
		Parent->DeliverTimeoutValue(D.TimeOutValue);
	}
}
