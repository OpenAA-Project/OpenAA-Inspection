#include "AddExcludedFileDialog.h"
#include "ui_AddExcludedFileDialog.h"
#include <QFileDialog>

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
	TableName	=ui->lineEditFileName->text();
	done(true);
}

void AddExcludedFileDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
