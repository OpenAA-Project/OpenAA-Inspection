#include "SettingParamDialog.h"
#include "ui_SettingParamDialog.h"
#include "AutoReStart.h"
#include <QFileDialog>

SettingParamDialog::SettingParamDialog(AutoReStart *p ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingParamDialog)
{
    ui->setupUi(this);
    Parent=p;

    ui->lineEditExecuteFileName ->setText(Parent->ParamData.ExeFileName);
    ui->lineEditWorkingPath     ->setText(Parent->ParamData.WorkingPath);
    ui->lineEditParameter       ->setText(Parent->ParamData.Parameter);
    ui->spinBoxWaitingSecond    ->setValue(Parent->ParamData.WaitingSecond);
}

SettingParamDialog::~SettingParamDialog()
{
    delete ui;
}

void SettingParamDialog::on_pushButtonOK_clicked()
{
    Parent->ParamData.ExeFileName   =ui->lineEditExecuteFileName ->text();
    Parent->ParamData.WorkingPath   =ui->lineEditWorkingPath     ->text();
    Parent->ParamData.Parameter     =ui->lineEditParameter       ->text();
    Parent->ParamData.WaitingSecond =ui->spinBoxWaitingSecond    ->value();
    done(true);
}


void SettingParamDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void SettingParamDialog::on_pushButtonSelectFileName_clicked()
{
    QString ExeFileName=QFileDialog::getOpenFileName(nullptr
                                                    ,"Execute file name with parh"
                                                    , QString()
                                                    , "Exe file(*.exe);;All files(*.*)");
    if(ExeFileName.isEmpty()==false){
        ui->lineEditExecuteFileName->setText(ExeFileName);
    }
}


void SettingParamDialog::on_pushButtonSelectPath_clicked()
{
    QString Path=QFileDialog::getExistingDirectory(nullptr
                                                , "Working pah"
                                                , QString());
    if(Path.isEmpty()==false){
        ui->lineEditWorkingPath->setText(Path);
    }
}

