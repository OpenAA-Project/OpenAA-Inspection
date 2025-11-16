#include "SettingDeleteDialog.h"
#include "ui_SettingDeleteDialog.h"
#include "Maintainer.h"
#include<QFileDialog>
#include "SelectDirectoryDialog.h"

SettingDeleteDialog::SettingDeleteDialog(Maintainer *p ,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::SettingDeleteDialog)
{
    ui->setupUi(this);

	ui->listWidgetImageFileNames->clear();
	ui->listWidgetImageFileNames->addItems(Parent->DeleteData.FileNames);
	
	ui->listWidgetImageFolderNames->clear();
	ui->listWidgetImageFolderNames->addItems(Parent->DeleteData.FolderNames);

	ui->checkBoxImageKeepDays		->setChecked(Parent->DeleteData.UseDaysToKeepTerm);
	ui->checkBoxImageKeepMonths		->setChecked(Parent->DeleteData.UseMonthsToKeepTerm);

	ui->spinBoxImageKeepingDays		->setValue(Parent->DeleteData.TermDaysToKeep);
	ui->spinBoxImageKeepingMonths	->setValue(Parent->DeleteData.TermMonthsToKeep);
	ui->checkBoxImagePrioritySpace	->setChecked(Parent->DeleteData.PrioritySpace);
	ui->spinBoxImageKeepingSpace	->setValue(Parent->DeleteData.SpaceGBRemaining);

	ui->spinBoxCheckingHour			->setValue(Parent->DeleteData.CheckingHour);
	ui->spinBoxCheckingMinute		->setValue(Parent->DeleteData.CheckingMinute);

	on_checkBoxImageKeepDays_clicked();
}

SettingDeleteDialog::~SettingDeleteDialog()
{
    delete ui;
}

void SettingDeleteDialog::on_checkBoxImageKeepDays_clicked()
{
	ui->spinBoxImageKeepingDays		->setEnabled(ui->checkBoxImageKeepDays	->isChecked());
	ui->spinBoxImageKeepingMonths	->setEnabled(ui->checkBoxImageKeepMonths->isChecked());
}

void SettingDeleteDialog::on_checkBoxImageKeepMonths_clicked()
{
	ui->spinBoxImageKeepingDays		->setEnabled(ui->checkBoxImageKeepDays	->isChecked());
	ui->spinBoxImageKeepingMonths	->setEnabled(ui->checkBoxImageKeepMonths->isChecked());
}

void SettingDeleteDialog::on_listWidgetImageFileNames_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetImageFileNames->currentRow();
	if(Row<0)
		return;
	QFileInfo	FInfo(Parent->DeleteData.FileNames[Row]);
	QFileDialog	D (NULL,"Input file name",FInfo.filePath());
	D.selectFile(Parent->DeleteData.FileNames[Row]);
	if(D.exec()==QFileDialog::Accepted){
		QStringList s=D.selectedFiles ();
		if(s.count()>0){
			Parent->DeleteData.FileNames[Row]=s[0];
			ui->listWidgetImageFileNames->clear();
			ui->listWidgetImageFileNames->addItems(Parent->DeleteData.FileNames);
		}
	}
}

void SettingDeleteDialog::on_pushButtonImageAddFileName_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( NULL, /**/"File name", QString(), QString() );
	if(FileName.isEmpty()==false){
		Parent->DeleteData.FileNames.append(FileName);
		ui->listWidgetImageFileNames->clear();
		ui->listWidgetImageFileNames->addItems(Parent->DeleteData.FileNames);
	}
}

void SettingDeleteDialog::on_pushButtonImageSubLine_clicked()
{
	int	Row=ui->listWidgetImageFileNames->currentRow();
	if(Row<0)
		return;
	QListWidgetItem	*w=ui->listWidgetImageFileNames->item(Row);
	ui->listWidgetImageFileNames->removeItemWidget(w);
	delete	w;
	Parent->DeleteData.FileNames.removeAt(Row);
}

void SettingDeleteDialog::on_pushButtonImageAddFolderName_clicked()
{
	SelectDirectoryDialog	D(/**/"");
	if(D.exec()==(int)true){
		Parent->DeleteData.FolderNames.append(D.Directory);
		ui->listWidgetImageFolderNames->clear();
		ui->listWidgetImageFolderNames->addItems(Parent->DeleteData.FolderNames);
	}
}

void SettingDeleteDialog::on_pushButtonImageSubFolder_clicked()
{
	int	Row=ui->listWidgetImageFolderNames->currentRow();
	if(Row<0)
		return;
	QListWidgetItem	*w=ui->listWidgetImageFolderNames->item(Row);
	ui->listWidgetImageFolderNames->removeItemWidget(w);
	delete	w;
	Parent->DeleteData.FolderNames.removeAt(Row);
}

void SettingDeleteDialog::on_pushButtonOK_clicked()
{
	Parent->DeleteData.UseDaysToKeepTerm	=ui->checkBoxImageKeepDays		->isChecked();
	Parent->DeleteData.UseMonthsToKeepTerm	=ui->checkBoxImageKeepMonths	->isChecked();

	Parent->DeleteData.TermDaysToKeep		=ui->spinBoxImageKeepingDays	->value();
	Parent->DeleteData.TermMonthsToKeep		=ui->spinBoxImageKeepingMonths	->value();
	Parent->DeleteData.PrioritySpace		=ui->checkBoxImagePrioritySpace	->isChecked();
	Parent->DeleteData.SpaceGBRemaining		=ui->spinBoxImageKeepingSpace	->value();
	Parent->DeleteData.CheckingHour			=ui->spinBoxCheckingHour		->value();
	Parent->DeleteData.CheckingMinute		=ui->spinBoxCheckingMinute		->value();
	done(true);
}
