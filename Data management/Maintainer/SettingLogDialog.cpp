#include "SettingLogDialog.h"
#include "ui_SettingLogDialog.h"
#include "Maintainer.h"
#include <QFileDialog>

SettingLogDialog::SettingLogDialog(Maintainer *p,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::SettingLogDialog)
{
    ui->setupUi(this);

	ui->lineEditLogFileName->setText(Parent->LogFileName);
}

SettingLogDialog::~SettingLogDialog()
{
    delete ui;
}

void SettingLogDialog::on_pushButtonSelectFile_clicked()
{
	QString	FileName	=QFileDialog::getOpenFileName(NULL,"Log file name"
									,QString()
									,QString(/**/"Maintainer.log;;Log file(*.log);;All files(*.*)"));
	if(FileName.isEmpty()==false){
		ui->lineEditLogFileName->setText(FileName);
	}
}

void SettingLogDialog::on_pushButtonOK_clicked()
{
	Parent->LogFileName	=ui->lineEditLogFileName->text();
	done(true);
}

void SettingLogDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
