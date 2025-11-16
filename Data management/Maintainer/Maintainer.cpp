#include "Maintainer.h"
#include "SettingDeleteDialog.h"
#include <QFile>
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "SettingLogDialog.h"
#include "SettingBackupDialog.h"

Maintainer::Maintainer(const QString &settingFileName ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,SettingFileName(settingFileName)
	,MaintainThreadInst(this,this)
{
	ui.setupUi(this);
	NowOnShowing=true;
	MaxLines	=1000;
	ModeExecuteNow	=false;
	LogFileName	=/**/"Maintainer.log";
	QueuedCounter	=0;
	LoadSetting();

	connect(this,SIGNAL(SignalDoneRemoveFile(const QString &)),this,SLOT(SlotDoneRemoveFile(const QString &)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalDoneBackupFile(const QString &)),this,SLOT(SlotDoneBackupFile(const QString &)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalDoneRemoveDir (const QString &)),this,SLOT(SlotDoneRemoveDir (const QString &)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalStep()),this,SLOT(SlotStep()),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalSetMaxStep(const QString &,const QString &,int)),this,SLOT(SlotSetMaxStep(const QString &,const QString &,int)),Qt::QueuedConnection);

	MaintainThreadInst.start();
}

Maintainer::~Maintainer()
{
	MaintainThreadInst.Terminated=true;
	MaintainThreadInst.wait(5000);
}

bool	Maintainer::SaveSetting(void)
{
	QFile	File(SettingFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		int32	Ver=2;
		if(::Save(&File,Ver)==false)
			return false;
		if(::Save(&File,LogFileName)==false)
			return false;
		if(DeleteData.Save(&File)==false)
			return false;
		if(BackupData.Save(&File)==false)
			return false;

		return true;
	}
	return false;
}

bool	Maintainer::LoadSetting(void)
{
	QFile	File(SettingFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	Ver;
		if(::Load(&File,Ver)==false)
			return false;
		if(::Load(&File,LogFileName)==false)
			return false;
		if(DeleteData.Load(&File)==false)
			return false;
		if(Ver>=2){
			if(BackupData.Load(&File)==false)
				return false;
		}
		return true;
	}
	return false;
}

void Maintainer::on_pushButtonSettingDelete_clicked()
{
	SettingDeleteDialog	D(this);
	if(D.exec()==(int)true){
		SaveSetting();
	}
}

void	Maintainer::DoneRemoveFile(const QString &FileName)
{
	while(QueuedCounter!=0){
		GSleep(10);
	}
	QueuedCounter++;
	emit	SignalDoneRemoveFile(FileName);
}

void	Maintainer::DoneBackupFile(const QString &FileName)
{
	while(QueuedCounter!=0){
		GSleep(10);
	}
	QueuedCounter++;
	emit	SignalDoneBackupFile(FileName);
}

void	Maintainer::DoneRemoveDir (const QString &Path)
{
	while(QueuedCounter!=0){
		GSleep(10);
	}
	QueuedCounter++;
	emit	SignalDoneRemoveDir(Path);
}
void	Maintainer::Step(void)
{
	while(QueuedCounter!=0){
		GSleep(10);
	}
	QueuedCounter++;
	emit	SignalStep();
}

void	Maintainer::SlotDoneRemoveFile(const QString &FileName)
{
	NowOnShowing=false;
	QString	Str=QString(/**/"Del ")+FileName;
	ui.listWidget->setUpdatesEnabled(false);
	ui.listWidget->insertItem(0,Str);
	while(ui.listWidget->count()>MaxLines){
		QListWidgetItem *item=ui.listWidget->takeItem(ui.listWidget->count()-1);
		if(item!=NULL){
			//ui.listWidget->removeItemWidget(item);
			delete	item;
		}
	}
	ui.listWidget->setUpdatesEnabled(true);

	QFile	File(LogFileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	Txt(&File);
		Txt<<QDateTime::currentDateTime().toString(/**/"yyyy-MM-dd hh:mm:ss");
		Txt<</**/" Del ";
		Txt<<FileName;
		Txt<</**/"\n";
	}
	NowOnShowing=true;
	//QApplication::processEvents();
	QueuedCounter--;
}

void	Maintainer::SlotDoneBackupFile(const QString &FileName)
{
	NowOnShowing=false;
	QString	Str=QString(/**/"Backup ")+FileName;
	ui.listWidget->setUpdatesEnabled(false);
	ui.listWidget->insertItem(0,Str);
	while(ui.listWidget->count()>MaxLines){
		QListWidgetItem *item=ui.listWidget->takeItem(ui.listWidget->count()-1);
		if(item!=NULL){
			//ui.listWidget->removeItemWidget(item);
			delete	item;
		}
	}
	ui.listWidget->setUpdatesEnabled(true);

	QFile	File(LogFileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	Txt(&File);
		Txt<<QDateTime::currentDateTime().toString(/**/"yyyy-MM-dd hh:mm:ss");
		Txt<</**/" Backup ";
		Txt<<FileName;
		Txt<</**/" -> ";
		Txt<<BackupData.DestinationPath;
		Txt<</**/"\n";
	}
	NowOnShowing=true;
	//QApplication::processEvents();
	QueuedCounter--;
}

void	Maintainer::SlotDoneRemoveDir (const QString &Path)
{
	NowOnShowing=false;
	QString	Str=QString(/**/"RD ")+Path;
	ui.listWidget->setUpdatesEnabled(false);
	ui.listWidget->insertItem(0,Str);
	while(ui.listWidget->count()>MaxLines){
		QListWidgetItem *item=ui.listWidget->takeItem(ui.listWidget->count()-1);
		if(item!=NULL){
			//ui.listWidget->removeItemWidget(item);
			delete	item;
		}
	}
	ui.listWidget->setUpdatesEnabled(true);

	QFile	File(LogFileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	Txt(&File);
		Txt<<QDateTime::currentDateTime().toString(/**/"yyyy-MM-dd hh:mm:ss");
		Txt<</**/" RD ";
		Txt<<Path;
		Txt<</**/"\n";
	}
	//QApplication::processEvents();
	NowOnShowing=true;
	QueuedCounter--;
}

void	Maintainer::SlotStep()
{
	int	n=ui.progressBar->value();
	n++;
	if(ui.progressBar->maximum()<n)
		n=0;
	ui.progressBar->setValue(n);
	QueuedCounter--;
}

void Maintainer::on_pushButtonSettingBackup_clicked()
{
	SettingBackupDialog	D(this);
	if(D.exec()==(int)true){
		SaveSetting();
	}
}

void Maintainer::on_pushButtonSetting_clicked()
{
	SettingBackupDialog	D(this);
	if(D.exec()==(int)true){
		SaveSetting();
	}
}
void	Maintainer::SetMaxStep(const QString &ActionName ,const QString &path ,int MaxN)
{
	while(QueuedCounter!=0){
		GSleep(10);
	}
	QueuedCounter++;
	emit	SignalSetMaxStep(ActionName ,path ,MaxN);
}

void	Maintainer::SlotSetMaxStep(const QString &ActionName ,const QString &path ,int MaxN)
{
	ui.labelAction	->setText(ActionName);
	ui.labelPath	->setText(path);
	ui.progressBar	->setMaximum(MaxN);
	QueuedCounter--;
}


void Maintainer::on_pushButtonExecuteNow_clicked()
{
	ModeExecuteNow=true;
}
