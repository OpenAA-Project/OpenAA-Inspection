#include "ShowMemoryForm.h"
#include "ui_ShowMemoryForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;



ShowMemoryForm::ShowMemoryForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowMemoryForm)
{
    ui->setupUi(this);
	ShowMemoryStructInSlave	=NULL;
	SlavePageNumb			=0;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	TM.setInterval(5000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}

ShowMemoryForm::~ShowMemoryForm()
{
    delete ui;
	delete	[]ShowMemoryStructInSlave;
}

void	ShowMemoryForm::Prepare(void)
{
	if(ShowMemoryStructInSlave!=NULL){
		delete	[]ShowMemoryStructInSlave;
	}
	if(GetParamComm()->GetConnectedPCNumb()>0){
		SlavePageNumb=GetPageNumb();
		ShowMemoryStructInSlave=new struct	__ShowMemoryStruct[SlavePageNumb];
	}
	ui->tableWidget->setFont (CFont);
	ResizeAction();
}

void	ShowMemoryForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());
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
	return QString::number(fN,'f',1)+QString(/**/" B");
}

void	ShowMemoryForm::SlotTimeout()
{
	if(IsShown()==true){
		if(GetMemoryInfo(
					 ShowMemoryStruct.dwMemoryLoad
					,ShowMemoryStruct.ullTotalPhys
					,ShowMemoryStruct.ullAvailPhys
					,ShowMemoryStruct.ullTotalPageFile
					,ShowMemoryStruct.ullAvailPageFile
					,ShowMemoryStruct.ullTotalVirtual
					,ShowMemoryStruct.ullAvailVirtual
					,ShowMemoryStruct.ullAvailExtendedVirtual
					)==true){
			QStringList	Header;
			int	ColumnCount=1;
				
			Header.append("This");
			
			if(GetParamComm()->GetConnectedPCNumb()>0){
				for(int page=0;page<GetPageNumb();page++){
					Header.append(QString("Page")+QString::number(page));
					ColumnCount++;
				}
			}
			ui->tableWidget->setColumnCount(ColumnCount);
			ui->tableWidget->setHorizontalHeaderLabels(Header);
			::SetDataToTable(ui->tableWidget,0,0,QString::number(ShowMemoryStruct.dwMemoryLoad)+QString(/**/"%"));
			::SetDataToTable(ui->tableWidget,0,1,MakeMemoryStr(ShowMemoryStruct.ullAvailPhys));
			::SetDataToTable(ui->tableWidget,0,2,MakeMemoryStr(ShowMemoryStruct.ullAvailPageFile));
			::SetDataToTable(ui->tableWidget,0,3,MakeMemoryStr(ShowMemoryStruct.ullAvailVirtual));

			if(GetParamComm()->GetConnectedPCNumb()>0){
				for(int page=0;page<GetPageNumb();page++){
					int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
					GUICmdReqShowMemory	RCmd(GetLayersBase(),sRoot,sName,globalPage);
					GUICmdAckShowMemory	ACmd(GetLayersBase(),sRoot,sName,globalPage);
					if(RCmd.Send(globalPage,0,ACmd)==true){
						ShowMemoryStructInSlave[page]=ACmd.ShowMemoryStruct;
						::SetDataToTable(ui->tableWidget,page+1,0,QString::number(ACmd.ShowMemoryStruct.dwMemoryLoad)+QString(/**/"%"));
						::SetDataToTable(ui->tableWidget,page+1,1,MakeMemoryStr(ACmd.ShowMemoryStruct.ullAvailPhys));
						::SetDataToTable(ui->tableWidget,page+1,2,MakeMemoryStr(ACmd.ShowMemoryStruct.ullAvailPageFile));
						::SetDataToTable(ui->tableWidget,page+1,3,MakeMemoryStr(ACmd.ShowMemoryStruct.ullAvailVirtual));
					}
				}
			}
		}
	}
}

//============================================================================================

GUICmdReqShowMemory::GUICmdReqShowMemory(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqShowMemory::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckShowMemory	*SendBack=GetSendBack(GUICmdAckShowMemory,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	GetMemoryInfo(
				SendBack->ShowMemoryStruct.dwMemoryLoad
				,SendBack->ShowMemoryStruct.ullTotalPhys
				,SendBack->ShowMemoryStruct.ullAvailPhys
				,SendBack->ShowMemoryStruct.ullTotalPageFile
				,SendBack->ShowMemoryStruct.ullAvailPageFile
				,SendBack->ShowMemoryStruct.ullTotalVirtual
				,SendBack->ShowMemoryStruct.ullAvailVirtual
				,SendBack->ShowMemoryStruct.ullAvailExtendedVirtual
				);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}

GUICmdAckShowMemory::GUICmdAckShowMemory(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckShowMemory::Load(QIODevice *f)
{
	if(f->read((char *)&ShowMemoryStruct,sizeof(ShowMemoryStruct))!=sizeof(ShowMemoryStruct))
		return false;
	return true;
}

bool	GUICmdAckShowMemory::Save(QIODevice *f)
{
	if(f->write((const char *)&ShowMemoryStruct,sizeof(ShowMemoryStruct))!=sizeof(ShowMemoryStruct))
		return false;
	return true;
}

