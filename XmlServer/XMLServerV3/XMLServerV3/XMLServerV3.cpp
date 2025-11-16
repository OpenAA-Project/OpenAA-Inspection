#include "XMLServerV3.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingParamForm.h"
#include "ShowTableDialog.h"

#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include <QMessageBox>

XMLServerV3::XMLServerV3(const QString &_UserPath,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),SMain(this),WDog(this)
{
	ui.setupUi(this);

	UserPath=_UserPath;
	connect(&SMain,SIGNAL(SignalShowClient(int)),this,SLOT(SlotShowClient(int)),Qt::QueuedConnection);
	connect(&SMain,SIGNAL(SignalAnalize(QDateTime , int , int , QString ,int))
		,this,SLOT(SlotAnalize(QDateTime , int, int, QString,int)),Qt::QueuedConnection);
	connect(&SMain,SIGNAL(SignalProgress())		,this,SLOT(SlotProgress()),Qt::QueuedConnection);


    restoreAction = new QAction(tr("&Show"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
	QIcon icon(QPixmap(/**/":Resources/XMLServerV3.png"));
	trayIcon->setIcon(icon);
	setWindowIcon(icon);

	ui.tableWidgetTable->setColumnWidth(0,540);

	ui.tableWidgetClient->setColumnWidth(0,60);
	ui.tableWidgetClient->setColumnWidth(1,80);
	ui.tableWidgetClient->setColumnWidth(2,60);
	ui.tableWidgetClient->setColumnWidth(3,200);
	ui.tableWidgetClient->setColumnWidth(4,60);

	ui.tableWidgetCommand->setColumnWidth(0,130);
	ui.tableWidgetCommand->setColumnWidth(1,60);
	ui.tableWidgetCommand->setColumnWidth(2,70);
	ui.tableWidgetCommand->setColumnWidth(3,194);
	ui.tableWidgetCommand->setColumnWidth(4,60);

	SettingForm=new SettingParamForm(SMain,NULL);
	WDog.Start();

    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &XMLServerV3::messageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &XMLServerV3::iconActivated);

    trayIcon->show();
	hide();
}

XMLServerV3::~XMLServerV3()
{
	delete	SettingForm;
	SettingForm=NULL;
}

void XMLServerV3::showEvent ( QShowEvent * event )
{
	static	bool	FirstMode=true;

	if(FirstMode==true){
		SMain.LoadDefault(LayersBase::GetUserPath(UserPath));
		SMain.StartServer();
		FirstMode=false;
	}
}
void XMLServerV3::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}
void XMLServerV3::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
}
void XMLServerV3::messageClicked()
{
}
void	XMLServerV3::SlotShowClient(int id)
{
	if(id>=0){
		SlotShowClientinside(id);
	}
	else{
		ui.tableWidgetClient->setRowCount(0);
		for(int i=0;i<MaxCommLeafNumb;i++){
			SClient	*SData=SMain.GetSClient(i);
			if(SData!=NULL){
				SlotShowClientinside(i);
			}
		}
	}
	ShowTable();
}
void	XMLServerV3::SlotShowClientinside(int id)
{
	int	RowCount=ui.tableWidgetClient->rowCount();
	int	IndexRow=-1;
	for(int Row=0;Row<RowCount;Row++){
		QString	ClientIDStr=::GetDataToTable(ui.tableWidgetClient ,0,Row);
		int	ClientID=ClientIDStr.toInt(NULL);
		if(id==ClientID){
			IndexRow=Row;
		}
	}
	if(IndexRow<0){
		ui.tableWidgetClient->setRowCount(RowCount+1);
		IndexRow=RowCount;
	}
	SClient	*SData=SMain.GetSClient(id);
	if(SData!=NULL){
		SetDataToTable(ui.tableWidgetClient ,0,IndexRow,QString::number(id));
		SetDataToTable(ui.tableWidgetClient ,1,IndexRow,SData->GetPeerIPAddress());
		SetDataToTable(ui.tableWidgetClient ,2,IndexRow,QString::number(SData->GetCount()));
		SetDataToTable(ui.tableWidgetClient ,3,IndexRow,SData->LastReceivedTime.toString(/**/"MM/dd hh:mm:ss"));
		SetDataToTable(ui.tableWidgetClient ,4,IndexRow,QString::number(SData->GetQueuedCount()));
	}
}

void	XMLServerV3::ShowTable(void)
{
	int	N=SMain.GetRootCount();
	ui.tableWidgetTable->setRowCount(N);
	for(int i=0;i<N;i++){
		XMLElementRoot	*L=SMain.GetRootXML(i);
		if(L!=NULL){
			SetDataToTable(ui.tableWidgetTable,0,i,L->GetTableName());
		}
	}
}

void	XMLServerV3::SlotAnalize(QDateTime tm , int ClientID, int OpeHandleCode, QString Command,int milisec)
{
	while(ui.tableWidgetCommand->rowCount()>100){
		ui.tableWidgetCommand->removeRow (100);
	}
	ui.tableWidgetCommand->insertRow(0);

	SetDataToTable(ui.tableWidgetCommand ,0,0,tm.toString("yy/MM/dd hh:mm:ss"));
	SetDataToTable(ui.tableWidgetCommand ,1,0,QString::number(ClientID));
	SetDataToTable(ui.tableWidgetCommand ,2,0,QString::number(OpeHandleCode));
	SetDataToTable(ui.tableWidgetCommand ,3,0,Command);
	SetDataToTable(ui.tableWidgetCommand ,4,0,QString::number(milisec));
}

void	XMLServerV3::slotSetting()
{
	SettingForm->show();
}
void	XMLServerV3::slotWriteOut()
{
	SMain.WriteOutAll();
}

void	XMLServerV3::SlotProgress()
{
	int	v=ui.progressBar->value()+1;
	if(v>ui.progressBar->maximum())
		v=0;
	ui.progressBar	->setValue(v);

	static	bool	FirstMode=true;
	if(FirstMode==true){
		hide();
		FirstMode=false;
	}
}

void XMLServerV3::on_checkBoxShowAll_clicked()
{
	SMain.SetShowCommandList(ui.checkBoxShowAll->isChecked());
}

void XMLServerV3::on_tableWidgetTable_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetTable->currentRow();
	if(Row<0)
		return;
	XMLElementRoot	*L=SMain.GetRootXML(Row);
	if(L!=NULL){
		ShowTableDialog	D(L,&SMain);
		D.exec();
		//SetDataToTable(ui.tableWidgetTable,0,i,L->GetTableName());
	}
}
