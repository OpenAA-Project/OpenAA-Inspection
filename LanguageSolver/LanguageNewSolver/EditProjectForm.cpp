#include "EditProjectForm.h"
#include "ui_EditProjectForm.h"
#include <QFileDialog>

EditProjectForm::EditProjectForm(LSProjectItem *a,QWidget *parent) :
    QDialog(parent)
	,Project(a)
    ,ui(new Ui::EditProjectForm)
{
    ui->setupUi(this);

	ui->EditFolderReference	->setText(Project->ReferenceFolder);
	ui->EditProjectName		->setText(Project->ProjectItemName);

	if(Project->ProjectItemName==""){
		ui->pushButtonDelete->setVisible(false);
	}
	else{
		ui->pushButtonDelete->setVisible(true);
	}
}

EditProjectForm::~EditProjectForm()
{
    delete ui;
}

void EditProjectForm::on_pushButtonFolderReference_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Directory"));
	if(dir.isEmpty()==false){
		QDir	Dir(QDir::currentPath ());
		QFileInfo	Info(dir);
		ui->EditProjectName->setText(Info.baseName());
		ui->EditFolderReference->setText(Dir.relativeFilePath(dir));
	}
}

void EditProjectForm::on_pushButtonOK_clicked()
{
	Project->ReferenceFolder=ui->EditFolderReference	->text();
	Project->ProjectItemName=ui->EditProjectName		->text();
	done(true);
}

void EditProjectForm::on_pushButtonDelete_clicked()
{
	done(1000);
}

void EditProjectForm::on_pushButtonCancel_clicked()
{
	done(false);
}
