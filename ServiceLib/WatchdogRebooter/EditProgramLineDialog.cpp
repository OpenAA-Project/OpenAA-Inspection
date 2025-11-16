#include "EditProgramLineDialog.h"
#include <QFileDialog>
#include "ui_EditProgramLineDialog.h"

EditProgramLineDialog::EditProgramLineDialog(QWidget *parent) :
    QDialog(parent)
    ,Current(NULL)
    ,ui(new Ui::EditProgramLineDialog)
{
    ui->setupUi(this);
}

EditProgramLineDialog::~EditProgramLineDialog()
{
    delete ui;
}

void	EditProgramLineDialog::showEvent ( QShowEvent * event )
{
	ui->lineEditPathFileName	->setText(Current.PathFileName);
	ui->lineEditArmuments		->setText(Current.Arguments);
	ui->lineEditWorkingPath		->setText(Current.WorkingPath);
	ui->spinBoxWatchTerm		->setValue(Current.WatchTerm);
}

void EditProgramLineDialog::on_pushButtonOK_clicked()
{
	Current.PathFileName	=ui->lineEditPathFileName	->text();
	Current.Arguments		=ui->lineEditArmuments		->text();
	Current.WorkingPath		=ui->lineEditWorkingPath	->text();
	Current.WatchTerm		=ui->spinBoxWatchTerm		->value();

	accept();
}

void EditProgramLineDialog::on_pushButtonCancel_clicked()
{
	reject();
}

void EditProgramLineDialog::on_pushButtonSelectPathFile_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(NULL,"Program file name");
    if(FileName.isEmpty()==false){
        ui->lineEditPathFileName	->setText(FileName);
    }
}

void EditProgramLineDialog::on_pushButtonSelectWorkingPath_clicked()
{
    QString PathName=QFileDialog::getExistingDirectory(NULL,"Working directory");
    if(PathName.isEmpty()==false){
        ui->lineEditWorkingPath	->setText(PathName);
    }
}
