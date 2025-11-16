#include "CreateRepeatCountDialog.h"
#include "ui_CreateRepeatCountDialog.h"
#include "XGeneralFunc.h"
#include "XRepeatControl.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "swap.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

CreateRepeatCountDialog::CreateRepeatCountDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::CreateRepeatCountDialog)
{
    ui->setupUi(this);

	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	ui->tableWidget->setRowCount(N);
	::SetColumnWidthInTable(ui->tableWidget ,0, 75);
	::SetColumnWidthInTable(ui->tableWidget ,1, 25);
	for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		int	RepeatCount=0;
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			for(int page=0;page<m->GetPageNumb();page++){
				IntegrationCmdReqRepeatCount	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationCmdAckRepeatCount	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
					RepeatCount=max(RepeatCount,ACmd.RepeatCount);
				}
			}
			::SetDataToTable(ui->tableWidget, 0, SlaveNo, m->GetMachineName());
			::SetDataToTableSpinBox(ui->tableWidget, 1, SlaveNo, RepeatCount
																,0,10000);
		}
	}
}

CreateRepeatCountDialog::~CreateRepeatCountDialog()
{
    delete ui;
}

void CreateRepeatCountDialog::on_pushButtonOK_clicked()
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		int	RepeatCount=::GetDataToTableSpinBox(ui->tableWidget, 1, SlaveNo);
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			for(int page=0;page<m->GetPageNumb();page++){
				IntegrationCmdSetRepeatCount	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.RepeatCount=RepeatCount;
				RCmd.Send(NULL,SlaveNo,m->GetLocalPageFromGlobal(page));
			}
		}
	}
	done(true);
}


void CreateRepeatCountDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

//==================================================================================================

IntegrationCmdReqRepeatCount::IntegrationCmdReqRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdReqRepeatCount::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int32	LocalPage	=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationCmdAckRepeatCount	*SendBack=GetSendBackIntegration(IntegrationCmdAckRepeatCount,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	RepeatControlBase *RBBase=(RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			RepeatControlInPage	*PData=dynamic_cast<RepeatControlInPage	*>(Ph->GetPageData(LocalPage));
			if(PData!=NULL){
				CmdReqWholeRepeatControl	Cmd(GetLayersBase());
				PData->TransmitDirectly(&Cmd);
				SendBack->RepeatCount=Cmd.RepeatCount;
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);	
}

IntegrationCmdAckRepeatCount::IntegrationCmdAckRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAckRepeatCount::Load(QIODevice *f)
{
	if(::Load(f,RepeatCount)==false)	return false;
	return true;
}
bool	IntegrationCmdAckRepeatCount::Save(QIODevice *f)
{
	if(::Save(f,RepeatCount)==false)	return false;
	return true;
}
//==================================================================================================

IntegrationCmdSetRepeatCount::IntegrationCmdSetRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdSetRepeatCount::Load(QIODevice *f)
{
	if(::Load(f,RepeatCount)==false)	return false;
	return true;
}
bool	IntegrationCmdSetRepeatCount::Save(QIODevice *f)
{
	if(::Save(f,RepeatCount)==false)	return false;
	return true;
}
void	IntegrationCmdSetRepeatCount::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int32	LocalPage=cmd;
	RepeatControlBase *RBBase=(RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			RepeatControlInPage	*PData=dynamic_cast<RepeatControlInPage	*>(Ph->GetPageData(LocalPage));
			if(PData!=NULL){
				CmdCreateWholeRepeatControl	Cmd(GetLayersBase());
				Cmd.RepeatCount		=RepeatCount	;
				PData->TransmitDirectly(&Cmd);
			}
		}
	}
}
