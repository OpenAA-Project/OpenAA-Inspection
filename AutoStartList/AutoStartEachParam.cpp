#include "AutoStartEachParam.h"
#include <QFileDialog>

AutoStartEachParam::AutoStartEachParam(const QString &_ExeFilePath,const QString &_Parameters,const QString &_WorkingPath,int32	_Location ,int32 _BootingWaitTime
									   ,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ExeFilePath		=_ExeFilePath;
	Parameters		=_Parameters;
	WorkingPath		=_WorkingPath;
	Location		=_Location;
	BootingWaitTime	=_BootingWaitTime;

	ui.lineEditExeFilePath	->setText(ExeFilePath);
	ui.lineEditParameters	->setText(Parameters);
	ui.lineEditWorkingPath	->setText(WorkingPath);
	ui.comboBoxLocation		->setCurrentIndex(Location);
	ui.spinBoxBootingWaitTime	->setValue(BootingWaitTime);
}

AutoStartEachParam::~AutoStartEachParam()
{

}


void AutoStartEachParam::on_pushButtonOK_clicked()
{
	ExeFilePath		=ui.lineEditExeFilePath	->text();
	Parameters		=ui.lineEditParameters	->text();
	WorkingPath		=ui.lineEditWorkingPath	->text();
	Location		=ui.comboBoxLocation	->currentIndex();
	BootingWaitTime	=ui.spinBoxBootingWaitTime->value();
	done(true);
}

void AutoStartEachParam::on_pushButtonCancel_clicked()
{
	done(false);
}

void AutoStartEachParam::on_pushButtonFile_clicked()
{
	QString	F=QFileDialog::getOpenFileName ( 0, /**/"File name", QString());
	if(F.isEmpty()==false){
		ui.lineEditExeFilePath	->setText(F);
	}
}