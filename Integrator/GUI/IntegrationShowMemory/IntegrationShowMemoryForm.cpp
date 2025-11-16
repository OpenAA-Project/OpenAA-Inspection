#include "IntegrationShowMemoryResource.h"
#include "IntegrationShowMemoryForm.h"
#include "ui_IntegrationShowMemoryForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

IntegrationShowMemoryForm::IntegrationShowMemoryForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationShowMemoryForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationShowMemoryForm::~IntegrationShowMemoryForm()
{
    delete ui;
}

void	IntegrationShowMemoryForm::Prepare(void)
{
	if(GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->Mastered==true){
		TM.setInterval(5000);
		TM.setSingleShot(false);
		connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
		TM.start();
	}
	ui->tableWidget->setFont (CFont);
	ResizeAction();
	ShowGrid();
}

void	IntegrationShowMemoryForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());
	int	W=ui->tableWidget->verticalHeader()->width();
	int	ColmnCount=ui->tableWidget->columnCount();
	if(ColmnCount>0){
		int	ColW=(width()-W-32)/ColmnCount;
		for(int i=0;i<ColmnCount;i++){
			ui->tableWidget->setColumnWidth(i,ColW);
		}
	}
}
void	IntegrationShowMemoryForm::SlotTimeout()
{
	if(IsShown()==true){
		IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
		int	N=IBase->GetParamIntegrationMaster()->GetIntegrationSlaveCount();
		for(int i=0;i<N;i++){
			if(IBase->IsConnected(i)!=NULL){
				CmdReqMemoryInfoToMaster	RCmd(GetLayersBase(),sRoot,sName,i);
				RCmd.Send(NULL,i,0);
			}
		}
	}
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

void	IntegrationShowMemoryForm::ShowGrid(void)
{
	if(IsShown()==true){
		IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
		int	SlaveCount=IBase->GetIntegrationSlaveCount();
		int	ColumnCount=0;
		::SetColumnWidthInTable(ui->tableWidget ,0, 40);

		for(int SlaveNo=0;SlaveNo<SlaveCount;SlaveNo++){
			::SetColumnWidthInTable(ui->tableWidget ,1+SlaveNo, 60/SlaveCount);
			ColumnCount++;
			ColumnCount+=IBase->GetParamIntegrationMaster()->Slaves[SlaveNo]->CountOfConnectedPC;
		}
		QStringList	HeaderList;
		ui->tableWidget->setColumnCount(ColumnCount);
		if(IBase->GetParamIntegrationMaster()->Mastered==true){
			int	ColumnNo=0;
			for(int SlaveNo=0;SlaveNo<SlaveCount;SlaveNo++){
				struct	__MachineMemory	*M=&MachineMemory[SlaveNo];
				::SetDataToTable(ui->tableWidget,ColumnNo,0,QString::number(M->ShowMemoryStruct.dwMemoryLoad)+QString(/**/"%"));
				::SetDataToTable(ui->tableWidget,ColumnNo,1,MakeMemoryStr(M->ShowMemoryStruct.ullAvailPhys));
				::SetDataToTable(ui->tableWidget,ColumnNo,2,MakeMemoryStr(M->ShowMemoryStruct.ullAvailPageFile));
				::SetDataToTable(ui->tableWidget,ColumnNo,3,MakeMemoryStr(M->ShowMemoryStruct.ullAvailVirtual));
				ColumnNo++;
				EachMaster	*m=IBase->MasterDatas[SlaveNo];
				if(m!=NULL){
					HeaderList.append(m->GetMachineName());
				}
				int	ConnectedPCCount=IBase->GetParamIntegrationMaster()->Slaves[SlaveNo]->CountOfConnectedPC;
				for(int i=0;i<ConnectedPCCount;i++){
					HeaderList.append(m->GetMachineName()+QString(/**/"-P")+QString::number(i));
					::SetDataToTable(ui->tableWidget,ColumnNo,0,QString::number(M->ShowMemoryStructInSlave[i].dwMemoryLoad)+QString(/**/"%"));
					::SetDataToTable(ui->tableWidget,ColumnNo,1,MakeMemoryStr(M->ShowMemoryStructInSlave[i].ullAvailPhys));
					::SetDataToTable(ui->tableWidget,ColumnNo,2,MakeMemoryStr(M->ShowMemoryStructInSlave[i].ullAvailPageFile));
					::SetDataToTable(ui->tableWidget,ColumnNo,3,MakeMemoryStr(M->ShowMemoryStructInSlave[i].ullAvailVirtual));
					ColumnNo++;
				}
			}
			ui->tableWidget->setHorizontalHeaderLabels(HeaderList);
		}
	}
	emit	SignalShowMemory();
}

//====================================================================================================
CmdReqMemoryInfoToMaster::CmdReqMemoryInfoToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	CmdReqMemoryInfoToMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSendMemoryInfoToMaster	*SendBack=GetSendBackIntegration(CmdSendMemoryInfoToMaster,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	ShowMemoryForm *f=dynamic_cast<ShowMemoryForm *>(GetLayersBase()->FindByName(/**/"General",/**/"ShowMemory",/**/""));
	if(f!=NULL){
		SendBack->ShowMemoryStruct	=f->ShowMemoryStruct;
		SendBack->SlavePageNumb		=f->SlavePageNumb;
		for(int i=0;i<SendBack->SlavePageNumb && i<10;i++){
			SendBack->ShowMemoryStructInSlave[i]=f->ShowMemoryStructInSlave[i];
		}
	}
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

CmdSendMemoryInfoToMaster::CmdSendMemoryInfoToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	CmdSendMemoryInfoToMaster::Load(QIODevice *f)
{
	if(f->read((char *)&ShowMemoryStruct,sizeof(ShowMemoryStruct))!=sizeof(ShowMemoryStruct))
		return false;
	return true;
	if(::Load(f,SlavePageNumb)==false)
		return false;
	for(int i=0;i<SlavePageNumb && i<10;i++){
		if(f->read((char *)&ShowMemoryStructInSlave[0],sizeof(struct __ShowMemoryStruct))!=sizeof(struct __ShowMemoryStruct))
			return false;
	}
	return true;
}
bool	CmdSendMemoryInfoToMaster::Save(QIODevice *f)
{
	if(f->write((const char *)&ShowMemoryStruct,sizeof(ShowMemoryStruct))!=sizeof(ShowMemoryStruct))
		return false;
	return true;
	if(::Save(f,SlavePageNumb)==false)
		return false;
	for(int i=0;i<SlavePageNumb && i<10;i++){
		if(f->write((const char *)&ShowMemoryStructInSlave[0],sizeof(struct __ShowMemoryStruct))!=sizeof(struct __ShowMemoryStruct))
			return false;
	}
	return true;
}

void	CmdSendMemoryInfoToMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationShowMemoryForm *f=dynamic_cast<IntegrationShowMemoryForm *>(GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/""));
	if(f!=NULL){
		f->MachineMemory[slaveNo].ShowMemoryStruct	=ShowMemoryStruct;
		f->MachineMemory[slaveNo].SlavePageNumb		=SlavePageNumb;
		for(int i=0;i<SlavePageNumb && i<10;i++){
			if(f->MachineMemory[slaveNo].ShowMemoryStructInSlave!=NULL){
				f->MachineMemory[slaveNo].ShowMemoryStructInSlave[i]=ShowMemoryStructInSlave[i];
			}
		}
		f->ShowGrid();
	}
}

