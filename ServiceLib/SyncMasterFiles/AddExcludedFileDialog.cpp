#include "AddExcludedFileDialog.h"
#include <QFileDialog>
#include "ui_AddExcludedFileDialog.h"

AddExcludedFileDialog::AddExcludedFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddExcludedFileDialog)
{
    ui->setupUi(this);
}

AddExcludedFileDialog::~AddExcludedFileDialog()
{
    delete ui;
}

void AddExcludedFileDialog::on_pushButtonOK_clicked()
{
	FileName	=ui->lineEditFileName->text();
	done(true);
}

void AddExcludedFileDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void AddExcludedFileDialog::on_pushButtonDialog_clicked()
{
	QString	f=QFileDialog::getOpenFileName(NULL,"Add excluded file","File name to be excluded");
	if(f.isNull()==false){
		ui->lineEditFileName->setText(f);
	}
}
