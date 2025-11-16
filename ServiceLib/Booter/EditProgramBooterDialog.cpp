#include "EditProgramBooterDialog.h"
#include "ui_EditProgramBooterDialog.h"
#include <QFileDialog>

EditProgramBooterDialog::EditProgramBooterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProgramBooterDialog)
{
    ui->setupUi(this);
}

EditProgramBooterDialog::~EditProgramBooterDialog()
{
    delete ui;
}

void	EditProgramBooterDialog::Initial(ExecuteApplicationList &src)
{
	ui->lineEditProgram		->setText(src.Program);
	ui->lineEditParameter	->setText(src.Parameter);
}

void EditProgramBooterDialog::on_pushButtonFile_clicked()
{
	QString Txt=QFileDialog::getOpenFileName ( NULL, "Program file", QString()
											, "Exe file (*.exe);;All file (*.*)");
	if(Txt.isEmpty()==false){
		ui->lineEditProgram->setText(Txt);
	}
}

void EditProgramBooterDialog::on_pushButtonAdd_clicked()
{
	Program		=ui->lineEditProgram	->text();
	Parameter	=ui->lineEditParameter	->text();
	done(1);
}

void EditProgramBooterDialog::on_pushButtonEdit_clicked()
{
	Program		=ui->lineEditProgram	->text();
	Parameter	=ui->lineEditParameter	->text();
	done(2);
}

void EditProgramBooterDialog::on_pushButtonCancel_clicked()
{
	done(-1);
}
