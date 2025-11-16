#include "ReportDisk.h"
#include <QDir>
#include <QTextCodec>
#include <QFileDialog>
#include "XForWindows.h"
#include "XGeneralFunc.h"
#include "XDIskInfoCommon.h"

ReportDisk::ReportDisk(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),FRegistry(/**/"ReportDisk.dat"),MClient(this)
{
	ui.setupUi(this);

	//QTextCodec::setCodecForCStrings ( QTextCodec::codecForName(/**/"Shift-JIS"));
	QTextCodec::setCodecForLocale 	( QTextCodec::codecForName(/**/"Shift-JIS"));
	//QTextCodec::setCodecForTr 		( QTextCodec::codecForName(/**/"Shift-JIS"));

	connect(&MClient,SIGNAL(SignalReceived()),this,SLOT(SlotReceived()));

	QFileInfoList	FInfos=QDir::drives();
	for(int i=0;i<FInfos.count();i++){
		QString	f=FInfos[i].path();
		ui.comboBoxDrive1->addItem(f);
		ui.comboBoxDrive2->addItem(f);
		ui.comboBoxDrive3->addItem(f);
		ui.comboBoxDrive4->addItem(f);
	}

	ThreadDisk	=new ThreadDiskChecker(this);
	QString	Disk1=FRegistry.LoadRegString("Disk1","C:");
	ThreadDisk->DiskPath1=Disk1;
	ui.comboBoxDrive1->setCurrentIndex(ui.comboBoxDrive1->findText(Disk1));
	int		AlertSpace1=FRegistry.LoadRegInt("Space1",1000000);
	ThreadDisk->AlertSpace1=AlertSpace1;
	ui.spinBoxAlertSpace1->setValue(AlertSpace1);

	QString	Disk2=FRegistry.LoadRegString("Disk2","D:");
	ThreadDisk->DiskPath2=Disk2;
	ui.comboBoxDrive2->setCurrentIndex(ui.comboBoxDrive2->findText(Disk2));
	int		AlertSpace2=FRegistry.LoadRegInt("Space2",1000000);
	ThreadDisk->AlertSpace2=AlertSpace2;
	ui.spinBoxAlertSpace2->setValue(AlertSpace2);

	QString	Disk3=FRegistry.LoadRegString("Disk3","E:");
	ThreadDisk->DiskPath3=Disk3;
	ui.comboBoxDrive3->setCurrentIndex(ui.comboBoxDrive3->findText(Disk3));
	int		AlertSpace3=FRegistry.LoadRegInt("Space3",1000000);
	ThreadDisk->AlertSpace3=AlertSpace3;
	ui.spinBoxAlertSpace3->setValue(AlertSpace3);

	QString	Disk4=FRegistry.LoadRegString("Disk4","");
	ThreadDisk->DiskPath4=Disk4;
	ui.comboBoxDrive4->setCurrentIndex(ui.comboBoxDrive4->findText(Disk4));
	int		AlertSpace4=FRegistry.LoadRegInt("Space4",1000000);
	ThreadDisk->AlertSpace4=AlertSpace4;
	ui.spinBoxAlertSpace4->setValue(AlertSpace4);

	QString	IPAddress=FRegistry.LoadRegString("IPAddress","192.168.1.50");
	ui.lineEditIPAddress->setText(IPAddress);
	MClient.Start();
	MClient.Initial(IPAddress);


	bool	AutoMode=FRegistry.LoadRegBool("AutoMode",false);
	ThreadDisk->AutoMode=AutoMode;
	ui.checkBoxAutoMode->setChecked(AutoMode);

	int	PassedYear=FRegistry.LoadRegInt("PassedYear",0);
	ui.spinBoxYear->setValue(PassedYear);
	int	PassedMonth=FRegistry.LoadRegInt("PassedMonth",1);
	ui.spinBoxMonth->setValue(PassedMonth);
	int	PassedDay=FRegistry.LoadRegInt("PassedDay",1);
	ui.spinBoxDay->setValue(PassedDay);

	int	PassedHour=FRegistry.LoadRegInt("PassedHour",0);
	ui.spinBoxHour->setValue(PassedHour);
	int	PassedMinute=FRegistry.LoadRegInt("PassedMinute",0);
	ui.spinBoxMinute->setValue(PassedMinute);
	int	PassedSecond=FRegistry.LoadRegInt("PassedSecond",0);
	ui.spinBoxSecond->setValue(PassedSecond);
	ThreadDisk->PassedTime.set(PassedYear,PassedMonth,PassedDay ,PassedHour,PassedMinute,PassedSecond);

	bool	RemoveMode=FRegistry.LoadRegBool("RemoveMode",false);
	ThreadDisk->RemoveMode=RemoveMode;
	ui.checkBoxExecuteDelete->setChecked(RemoveMode);

	QStringList	Destinations=FRegistry.LoadRegStringList("Destinations");
	ui.listWidgetDestination->addItems(Destinations);
	ThreadDisk->Destinations=Destinations;

	on_checkBoxAutoMode_clicked();
	on_checkBoxExecuteDelete_clicked();

	QString	CName;
	MtGetComputerName(CName);
	ui.lineEditComputerName->setText(CName);
	setWindowState(Qt::WindowMinimized);

	ThreadDisk->start();
	ThreadDisk->ComputerName=CName;
}

void ReportDisk::closeEvent ( QCloseEvent * event )
{
	ThreadDisk->CloseMode=true;
	ThreadDisk->terminate();
	ThreadDisk->wait(10000);
}

ReportDisk::~ReportDisk()
{
}


void ReportDisk::on_pushButtonOK_clicked()
{
	QString	Drive1=ui.comboBoxDrive1->currentText();
	FRegistry.Save("Disk1",Drive1);
	ThreadDisk->DiskPath1=Drive1;

	QString	Drive2=ui.comboBoxDrive2->currentText();
	FRegistry.Save("Disk2",Drive2);
	ThreadDisk->DiskPath2=Drive2;

	QString	Drive3=ui.comboBoxDrive3->currentText();
	FRegistry.Save("Disk3",Drive3);
	ThreadDisk->DiskPath3=Drive3;

	QString	Drive4=ui.comboBoxDrive4->currentText();
	FRegistry.Save("Disk4",Drive4);
	ThreadDisk->DiskPath4=Drive4;

	int	AlertSpace1=ui.spinBoxAlertSpace1->value();
	FRegistry.Save("Space1",AlertSpace1);
	ThreadDisk->AlertSpace1=AlertSpace1;

	int	AlertSpace2=ui.spinBoxAlertSpace2->value();
	FRegistry.Save("Space2",AlertSpace2);
	ThreadDisk->AlertSpace2=AlertSpace2;

	int	AlertSpace3=ui.spinBoxAlertSpace3->value();
	FRegistry.Save("Space3",AlertSpace3);
	ThreadDisk->AlertSpace3=AlertSpace3;

	int	AlertSpace4=ui.spinBoxAlertSpace4->value();
	FRegistry.Save("Space4",AlertSpace4);
	ThreadDisk->AlertSpace4=AlertSpace4;


	QString	IPAddress=ui.lineEditIPAddress->text();
	FRegistry.Save("IPAddress",IPAddress);

	bool	AutoMode=ui.checkBoxAutoMode->isChecked();
	FRegistry.Save("AutoMode",AutoMode);
	ThreadDisk->AutoMode=AutoMode;

	int	PassedYear=ui.spinBoxYear->value();
	FRegistry.Save("PassedYear",PassedYear);
	int	PassedMonth=ui.spinBoxMonth->value();
	FRegistry.Save("PassedMonth",PassedMonth);
	int	PassedDay=ui.spinBoxDay->value();
	FRegistry.Save("PassedDay",PassedDay);
	int	PassedHour=ui.spinBoxHour->value();
	FRegistry.Save("PassedHour",PassedHour);
	int	PassedMinute=ui.spinBoxMinute->value();
	FRegistry.Save("PassedMinute",PassedMinute);
	int	PassedSecond=ui.spinBoxSecond->value();
	FRegistry.Save("PassedSecond",PassedSecond);
	ThreadDisk->PassedTime.set(PassedYear,PassedMonth,PassedDay ,PassedHour,PassedMinute,PassedSecond);

	bool	RemoveMode	=ui.checkBoxExecuteDelete->isChecked();
	FRegistry.Save("RemoveMode",RemoveMode);
	ThreadDisk->RemoveMode=RemoveMode;

	QStringList	Destinations;
	for(int i=0;i<ui.listWidgetDestination->count();i++){
		Destinations.append(ui.listWidgetDestination->item(i)->text());
	}
	FRegistry.Save("Destinations",Destinations);
	ThreadDisk->Destinations=Destinations;

}

void ReportDisk::on_checkBoxAutoMode_clicked()
{
	if(ui.checkBoxAutoMode->isChecked()==true){
		ui.frame->setDisabled(false);
	}
	else{
		ui.frame->setDisabled(true);
	}
}

void ReportDisk::on_pushButtonAddDestination_clicked()
{
	QString	s=QFileDialog::getExistingDirectory(NULL,"Add destination folder");
	if(s.isEmpty()==false){
		ThreadDisk->Destinations.append(s);
		ui.listWidgetDestination	->addItems(ThreadDisk->Destinations);
	}
}

void ReportDisk::on_pushButtonDeleteDestination_clicked()
{
	int	Row=ui.listWidgetDestination->currentRow();
	if(Row<0)
		return;
	ThreadDisk->Destinations.removeAt(Row);
	ui.listWidgetDestination	->addItems(ThreadDisk->Destinations);
}

void	Search(DiskFileInfoContainer &AckInfo,QString Path)
{
	QDir	Dir(Path);

	QStringList	List;
	List.append("*.*");

	QFileInfoList	FInfo=Dir.entryInfoList(List,QDir::Files);
	for(int i=0;i<FInfo.count();i++){
		DiskFileInfo	*a=new DiskFileInfo();
		a->Path		=FInfo[i].absolutePath();
		a->FileName	=FInfo[i].fileName();
		a->Size		=FInfo[i].size();
		a->UpdatedTime	=FInfo[i].lastModified ();
		AckInfo.AppendList(a);
	}
	QStringList	ListSubFolder;
	ListSubFolder.append("*");

	QFileInfoList	SubFolders=Dir.entryInfoList(ListSubFolder,QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<SubFolders.count();i++){
		QString	LPath=SubFolders[i].absoluteFilePath();
		Search(AckInfo,LPath);
	}
}

void	ReportDisk::SlotReceived()
{
	QBuffer	Buff(&MClient.ReceivedData);
	Buff.open(QIODevice::ReadOnly);
	int32	Cmd;

	if(::Load(&Buff,Cmd)==false)
		return;
	if(Cmd==10){
		QString		Disk;
		if(::Load(&Buff,Disk)==false)
			return;

		DiskFileInfoContainer	AckData;
		Search(AckData ,Disk);
		for(DiskFileInfo *a=AckData.GetFirst();a!=NULL;a=a->GetNext()){
			a->PCName=ui.lineEditComputerName->text();
		}

		QBuffer	ABuff;
		ABuff.open(QIODevice::WriteOnly);
		int32	AckCmd=11;
		AckData.Save(&ABuff);
		MClient.Send(AckCmd,ABuff.buffer());
	}
	if(Cmd==21){
		QString	Path;
		QString	FileName;
		QString	DestPath;
		if(::Load(&Buff,Path)==false)
			return;
		if(::Load(&Buff,FileName)==false)
			return;
		if(::Load(&Buff,DestPath)==false)
			return;

		QString	AllFileName=Path + GetSeparator()+FileName;
		QFileInfo	Info(AllFileName);
		XDateTime	UpDateTime	=Info.lastModified();
		QFile	File(AllFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			QByteArray	Data=File.readAll();

			QBuffer	ABuff;
			ABuff.open(QIODevice::WriteOnly);
			int32	AckCmd=31;

			::Save(&ABuff,DestPath);
			::Save(&ABuff,FileName);
			::Save(&ABuff,UpDateTime);
			::Save(&ABuff,Data);
			MClient.Send(AckCmd,ABuff.buffer());
			File.close();

			File.remove();
		}
	}
	else if(Cmd==22){
		QString	Path;
		QString	FileName;
		QString	DestPath;
		if(::Load(&Buff,Path)==false)
			return;
		if(::Load(&Buff,FileName)==false)
			return;

		QFile	File(Path + GetSeparator()+FileName);
		File.remove();
	}
	else if(Cmd==25){
		QByteArray	BArray;
		if(::Load(&Buff,BArray)==false)
			return;
		QBuffer	MBuff(&BArray);
		MBuff.open(QIODevice::ReadOnly);
		if(ThreadDisk->LoadSetting(&MBuff)==true){
			ui.checkBoxAutoMode->setChecked(ThreadDisk->AutoMode);
			ui.spinBoxYear->setValue(ThreadDisk->PassedTime.year());
			ui.spinBoxMonth->setValue(ThreadDisk->PassedTime.month());
			ui.spinBoxDay->setValue(ThreadDisk->PassedTime.day());

			ui.spinBoxHour->setValue(ThreadDisk->PassedTime.hour());
			ui.spinBoxMinute->setValue(ThreadDisk->PassedTime.minute());
			ui.spinBoxSecond->setValue(ThreadDisk->PassedTime.second());
			ui.checkBoxExecuteDelete->setChecked(ThreadDisk->RemoveMode);

			on_pushButtonOK_clicked();
			on_checkBoxAutoMode_clicked();
			on_checkBoxExecuteDelete_clicked();
		}
	}
}


void ReportDisk::on_pushButtonForceExecute_clicked()
{
	if(ThreadDisk!=NULL){
		ThreadDisk->ForceExecute();
	}
}

void ReportDisk::on_checkBoxExecuteDelete_clicked()
{
	if(ui.checkBoxExecuteDelete->isChecked()==true){
		ui.frameDestination->setEnabled(false);
	}
	else{
		ui.frameDestination->setEnabled(true);
	}
}
