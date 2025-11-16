#include "SelectFileOperationDialog.h"
#include "ui_SelectFileOperationDialog.h"
#include <QFileDialog>

SelectFileOperationDialog::SelectFileOperationDialog(DiskFileInfo *data ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFileOperationDialog)
{
    ui->setupUi(this);
	Data=*data;
	ui->lineEditPCName	->setText(Data.PCName);
	ui->lineEditPath	->setText(Data.Path);
	ui->lineEditFileName->setText(Data.FileName);
}

SelectFileOperationDialog::~SelectFileOperationDialog()
{
    delete ui;
}

void SelectFileOperationDialog::on_pushButtonDelete_clicked()
{
	done(2);
}

void SelectFileOperationDialog::on_pushButtonSelectDestination_clicked()
{
	DestPath=QFileDialog::getExistingDirectory(NULL,"Destination path");
	ui->lineEditDestination	->setText(DestPath);
}

void SelectFileOperationDialog::on_pushButtonMoveStart_clicked()
{
	DestPath	=ui->lineEditDestination	->text();
	if(DestPath.isEmpty()==true)
		return;
	done(1);
}

void SelectFileOperationDialog::on_pushButtonClose_clicked()
{
	done(0);
}
