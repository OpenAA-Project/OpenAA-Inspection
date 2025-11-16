#include "DelayExe.h"
#include <QProcess>

DelayExe::DelayExe(const QString &FileName , int WaitingTime , QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	CurrentCounter=WaitingTime;
	ui.labelCounter	->setText(QString::number(CurrentCounter));
	ExeFileName	=FileName;
	ui.labelFileName->setText(FileName);

	TM.setInterval(1000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

DelayExe::~DelayExe()
{

}

void	DelayExe::SlotTimeOut()
{
	CurrentCounter--;
	ui.labelCounter	->setText(QString::number(CurrentCounter));
	if(CurrentCounter==0){
		if(SArg.isEmpty()==true)
			QProcess::startDetached ( ExeFileName);
		else
			QProcess::startDetached ( ExeFileName,SArg);

		close();
	}
}