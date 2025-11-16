#include "ShowExecutingDialog.h"
#include "ui_ShowExecutingDialog.h"
#include "XDataInLayer.h"

ShowExecutingDialog::ShowExecutingDialog(int masterCode
										,ParamGlobal *_GlobalParam
										,LayersBase *Base 
										,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,RunningThread(masterCode,Base,this)
	,GlobalParam(_GlobalParam)
    ,ui(new Ui::ShowExecutingDialog)
{
    ui->setupUi(this);
	
	ui->progressBar->setValue(0);
	connect(&RunningThread,SIGNAL(SignalStep(QString)),this,SLOT(SlotStep(QString)),Qt::QueuedConnection);
	connect(&RunningThread,SIGNAL(SignalReqLibrary()),this,SLOT(SlotReqLibrary()),Qt::QueuedConnection);
	connect(&RunningThread,SIGNAL(finished()),this,SLOT(SlotFinished()),Qt::QueuedConnection);

	ui->frameOperation->setEnabled(false);
	RunningThread.LoadMaster();
	RunningThread.start();
}

ShowExecutingDialog::~ShowExecutingDialog()
{
    delete ui;
}

void ShowExecutingDialog::on_pushButtonSaveEXCEL_clicked()
{
	QString FileName=GetLayersBase()->LGetSaveFileName(0
													, "EXCEL file"
													, QString()
													, "EXCEL file(*.xlsx)");
	if(FileName.isEmpty()==false){
		RunningThread.SaveEXCEL(FileName);
	}
}

void ShowExecutingDialog::on_pushButtonClose_clicked()
{
	close();
}

void	ShowExecutingDialog::SlotStep(QString Msg)
{
	ui->progressBar->setValue(ui->progressBar->value()+1);
	ui->listWidget->addItem(Msg);
}

void	ShowExecutingDialog::SlotReqLibrary()
{
	RunningThread.GetLibraryOutOfThread();
}

void	ShowExecutingDialog::SlotFinished()
{
	ui->progressBar->setValue(0);
	ui->frameOperation->setEnabled(true);
}
