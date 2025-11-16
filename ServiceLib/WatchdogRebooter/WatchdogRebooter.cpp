#include "stdafx.h"
#include "WatchdogRebooter.h"
#include "EditProgramLineDialog.h"
#include "XForWindows.h"	
#include "XGeneralFunc.h"
#include <QMessageBox>

WatchdogRebooter::WatchdogRebooter(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	LoadData();
	ShowList();

	connect(&WPack,SIGNAL(SignalShow()),this,SLOT(SlotShow()));
	connect(&WPack,SIGNAL(SignalWatchdogEvent(const QString &,const QString & ,int )),this,SLOT(SlotWatchdogEvent(const QString &,const QString & ,int )));

	ui.tableWidget->setColumnWidth(0,300);
	ui.tableWidget->setColumnWidth(1,120);
	ui.tableWidget->setColumnWidth(2,120);
	ui.tableWidget->setColumnWidth(3,50);
	ui.tableWidget->setColumnWidth(4,40);

	ui.tableWidgetLog->setColumnWidth(0,48);
	ui.tableWidgetLog->setColumnWidth(1,100);
	ui.tableWidgetLog->setColumnWidth(2,110);
	ui.tableWidgetLog->setColumnWidth(3,48);

	DWORD ProcessID[16384];
	int	N=MtEnumProcess(ProcessID, sizeof(ProcessID)/sizeof(ProcessID[0]));
	for(int i=0;i<N;i++){
		QString ProcessName;
		if(GetProcessName(ProcessID[i] ,ProcessName)==false){
			continue;
		}
		bool	Found=false;
		for(WatchdogTarget *a=WPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(ProcessID[i]==a->GetPID()){
				Found=true;
				break;
			}
		}
		if(Found==true){
			continue;
		}
		for(WatchdogTarget *a=WPack.GetFirst();a!=NULL;a=a->GetNext()){
			QFileInfo	Info(a->PathFileName);
			QString	Name=Info.fileName();
			if(ProcessName==Name){
				if(a->IsConnected()==false){
					a->TryConnection(ProcessID[i]);
				}
			}
		}
	}


	TM.setInterval(10000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),SLOT(SlotTimeOut()));
	TM.start();
}

WatchdogRebooter::~WatchdogRebooter()
{

}


bool	WatchdogRebooter::LoadData(void)
{
	QFile	File(GetDefaultFileName());
	if(File.open(QIODevice::ReadOnly)==true){
		return WPack.Load(&File);
	}
	return false;
}

bool	WatchdogRebooter::SaveData(void)
{
	QFile	File(GetDefaultFileName());
	if(File.open(QIODevice::WriteOnly)==true){
		return WPack.Save(&File);
	}
	return false;
}

void WatchdogRebooter::ShowList(void)
{
	int	Row=0;
	ui.tableWidget->setRowCount(WPack.GetCount());
	for(WatchdogTarget *a=WPack.GetFirst();a!=NULL;a=a->GetNext()){
		QFileInfo	Info(a->PathFileName);
		SetDataToTable(ui.tableWidget ,0 ,Row,Info.path());
		SetDataToTable(ui.tableWidget ,1 ,Row,Info.fileName());
		SetDataToTable(ui.tableWidget ,2 ,Row,a->Arguments);
		SetDataToTable(ui.tableWidget ,3 ,Row,a->GetPID());
		SetDataToTable(ui.tableWidget ,4 ,Row,(a->IsAlive()==true)?QString("Alive"):QString("Dead"));
		Row++;
	}
}

void WatchdogRebooter::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=index.row();
	WatchdogTarget *a=WPack.GetItem(Row);
	if(a!=NULL){
		EditProgramLineDialog	D;
		D.Current	=*a;
		if(D.exec()==true){
			*a=D.Current;
			ShowList();
			SaveData();
		}
	}
}

void WatchdogRebooter::on_pushButtonAddProgram_clicked()
{
	EditProgramLineDialog	D;
	if(D.exec()==true){
		WatchdogTarget	*a=WPack.Create();
		*a=D.Current;
		WPack.AppendList(a);
		ShowList();
		SaveData();
	}
}

void WatchdogRebooter::on_pushButtonDeleteProgram_clicked()
{
	if(QMessageBox::warning(NULL,"Alert","Delete OK?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
		int	Row=ui.tableWidget->currentRow();
		WatchdogTarget *a=WPack.GetItem(Row);
		if(a!=NULL){
			WPack.RemoveList(a);
			ShowList();
			SaveData();
			delete	a;
		}
	}
}

void WatchdogRebooter::SlotTimeOut()
{
	int	Row=0;
	for(WatchdogTarget *a=WPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->TimerFunc();
		SetDataToTable(ui.tableWidget ,4 ,Row,(a->IsAlive()==true)?QString("Alive"):QString("Dead"));
		Row++;
	}
}

void WatchdogRebooter::on_pushButtonClose_clicked()
{
	if(QMessageBox::warning(NULL,"Alert","Do you close all softwares?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
		for(WatchdogTarget *a=WPack.GetFirst();a!=NULL;a=a->GetNext()){
			a->Kill();
		}
	}
	WPack.RemoveAll();
	close();
}

void	WatchdogRebooter::SlotShow()
{
	ShowList();
}

void	WatchdogRebooter::SlotWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid)
{
	ui.tableWidgetLog->insertRow(0);
	::SetDataToTable(ui.tableWidgetLog ,0 ,0,ErrorType);
	::SetDataToTable(ui.tableWidgetLog ,1 ,0,XDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss"));
	::SetDataToTable(ui.tableWidgetLog ,2 ,0,FileName);
	::SetDataToTable(ui.tableWidgetLog ,3 ,0,QString::number(pid));

	while(ui.tableWidgetLog->rowCount()>1000){
		ui.tableWidgetLog->removeRow(ui.tableWidgetLog->rowCount()-1);
	}
}

void	WatchdogRebooter::resizeEvent(QResizeEvent *ev)
{
	ui.tableWidgetLog	->move(width()-ui.tableWidgetLog->width(),0);
	ui.tableWidgetLog	->resize(ui.tableWidgetLog	->width(),height()-ui.frame->height());
	ui.tableWidget		->resize(width()-ui.tableWidgetLog->width(),height()-ui.frame->height());
	ui.frame->move(0,height()-ui.frame->height());
	ui.frame->resize(width(),ui.frame->height());
}