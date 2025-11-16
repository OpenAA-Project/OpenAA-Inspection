#include "NewProjectForm.h"
#include "ui_NewProjectForm.h"

NewProjectForm::NewProjectForm(const QString &ProjName ,QWidget *parent) :
    QDialog(parent)
	,ProjectName(ProjName)
    ,ui(new Ui::NewProjectForm)
{
    ui->setupUi(this);
	ui->lineEditProjectName->setText(ProjectName);
	if(ProjName==/**/""){
		ui->pushButtonDelete->setVisible(false);
	}
	else{
		ui->pushButtonDelete->setVisible(true);
	}
}

NewProjectForm::~NewProjectForm()
{
    delete ui;
}

void NewProjectForm::on_pushButtonOK_clicked()
{
	ProjectName	=ui->lineEditProjectName->text();
	done(true);
}

void NewProjectForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void NewProjectForm::on_pushButtonDelete_clicked()
{
	done(1000);
}
