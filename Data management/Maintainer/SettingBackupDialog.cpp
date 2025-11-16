#include "SettingBackupDialog.h"
#include "ui_SettingBackupDialog.h"
#include "Maintainer.h"
#include<QFileDialog>
#include "SelectDirectoryDialog.h"

SettingBackupDialog::SettingBackupDialog(Maintainer *p ,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::SettingBackupDialog)
{
    ui->setupUi(this);

	ui->listWidgetImageFileNames->clear();
	ui->listWidgetImageFileNames->addItems(Parent->BackupData.FileNames);
	
	ui->listWidgetImageFolderNames->clear();
	ui->listWidgetImageFolderNames->addItems(Parent->BackupData.FolderNames);

	ui->checkBoxImageKeepDays		->setChecked(Parent->BackupData.UseDaysToKeepTerm);
	ui->checkBoxImageKeepMonths		->setChecked(Parent->BackupData.UseMonthsToKeepTerm);

	ui->spinBoxImageKeepingDays		->setValue(Parent->BackupData.TermDaysToKeep);
	ui->spinBoxImageKeepingMonths	->setValue(Parent->BackupData.TermMonthsToKeep);
	ui->checkBoxImagePrioritySpace	->setChecked(Parent->BackupData.PrioritySpace);
	ui->spinBoxImageKeepingSpace	->setValue(Parent->BackupData.SpaceGBRemaining);

	ui->spinBoxCheckingHour			->setValue(Parent->BackupData.CheckingHour);
	ui->spinBoxCheckingMinute		->setValue(Parent->BackupData.CheckingMinute);

	ui->lineEditDestinationPath		->setText(Parent->BackupData.DestinationPath);

	on_checkBoxImageKeepDays_clicked();
}

SettingBackupDialog::~SettingBackupDialog()
{
    delete ui;
}

void SettingBackupDialog::on_checkBoxImageKeepDays_clicked()
{
	ui->spinBoxImageKeepingDays		->setEnabled(ui->checkBoxImageKeepDays	->isChecked());
	ui->spinBoxImageKeepingMonths	->setEnabled(ui->checkBoxImageKeepMonths->isChecked());
}

void SettingBackupDialog::on_checkBoxImageKeepMonths_clicked()
{
	ui->spinBoxImageKeepingDays		->setEnabled(ui->checkBoxImageKeepDays	->isChecked());
	ui->spinBoxImageKeepingMonths	->setEnabled(ui->checkBoxImageKeepMonths->isChecked());
}

void SettingBackupDialog::on_listWidgetImageFileNames_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetImageFileNames->currentRow();
	if(Row<0)
		return;
	QFileInfo	FInfo(Parent->BackupData.FileNames[Row]);
	QFileDialog	D (NULL,"Input file name",FInfo.filePath());
	D.selectFile(Parent->BackupData.FileNames[Row]);
	if(D.exec()==QFileDialog::Accepted){
		QStringList s=D.selectedFiles ();
		if(s.count()>0){
			Parent->BackupData.FileNames[Row]=s[0];
			ui->listWidgetImageFileNames->clear();
			ui->listWidgetImageFileNames->addItems(Parent->BackupData.FileNames);
		}
	}
}

void SettingBackupDialog::on_pushButtonImageAddFileName_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( NULL, /**/"File name", QString(), QString() );
	if(FileName.isEmpty()==false){
		Parent->BackupData.FileNames.append(FileName);
		ui->listWidgetImageFileNames->clear();
		ui->listWidgetImageFileNames->addItems(Parent->BackupData.FileNames);
	}
}

void SettingBackupDialog::on_pushButtonImageSubLine_clicked()
{
	int	Row=ui->listWidgetImageFileNames->currentRow();
	if(Row<0)
		return;
	QListWidgetItem	*w=ui->listWidgetImageFileNames->item(Row);
	ui->listWidgetImageFileNames->removeItemWidget(w);
	delete	w;
	Parent->BackupData.FileNames.removeAt(Row);
}

void SettingBackupDialog::on_pushButtonSelectDestinationPath_clicked()
{
	QString	Folder=QFileDialog::getExistingDirectory(NULL,"Destination folder to back up");
	if(Folder.isEmpty()==false){
		ui->lineEditDestinationPath	->setText(Folder);
	}
}

void SettingBackupDialog::on_pushButtonOK_clicked()
{
	Parent->BackupData.UseDaysToKeepTerm	=ui->checkBoxImageKeepDays		->isChecked();
	Parent->BackupData.UseMonthsToKeepTerm	=ui->checkBoxImageKeepMonths	->isChecked();

	Parent->BackupData.TermDaysToKeep		=ui->spinBoxImageKeepingDays	->value();
	Parent->BackupData.TermMonthsToKeep		=ui->spinBoxImageKeepingMonths	->value();
	Parent->BackupData.PrioritySpace		=ui->checkBoxImagePrioritySpace	->isChecked();
	Parent->BackupData.SpaceGBRemaining		=ui->spinBoxImageKeepingSpace	->value();
	Parent->BackupData.CheckingHour			=ui->spinBoxCheckingHour		->value();
	Parent->BackupData.CheckingMinute		=ui->spinBoxCheckingMinute		->value();
	Parent->BackupData.DestinationPath		=ui->lineEditDestinationPath	->text();
	done(true);
}
