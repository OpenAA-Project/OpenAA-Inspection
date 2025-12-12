#include "ActivationDialog.h"
#include "ui_ActivationDialog.h"
#include "XGeneralFunc.h"
#include "TypeDefinition.h"
#include <QFileDialog>
#include <QMessageBox>

ActivationDialog::ActivationDialog(TypeDefinition *p,QWidget *parent) :
    QDialog(parent)
    ,Parent(p)
    ,ui(new Ui::ActivationDialog)
{
    ui->setupUi(this);

    ::SetWidgetCenter(this);

    //ui->lineEditPCCode->setText(Parent->GetPCCode());
    ShowResult();
    SetFrame();
}

ActivationDialog::~ActivationDialog()
{
    delete ui;
}
void    ActivationDialog::ShowResult(void)
{
    if(Parent->IsActivated()==TypeDefinition::_AR_ActivatedOK){
        ui->pushButtonOK->setText("Already activated! OK");
    }
    else{
        ui->pushButtonOK->setText("OK");
    }
}
void ActivationDialog::on_checkBoxOrderCode_clicked()
{
    SetFrame();
}

void ActivationDialog::on_checkBoxLicenseFile_clicked()
{
    SetFrame();
}

void ActivationDialog::on_checkBoxActivationCode_clicked()
{
    SetFrame();
}
void ActivationDialog::SetFrame(void)
{
     ui->frameOrderCode      ->setEnabled(ui->checkBoxOrderCode->isChecked());
     ui->frameLicenseFile    ->setEnabled(ui->checkBoxLicenseFile->isChecked());
     ui->frameActivationCode->setEnabled(ui->checkBoxActivationCode->isChecked());
}

void ActivationDialog::on_pushButtonActivateByOrderCode_clicked()
{
    if(Parent->ActivateByOrderCode(ui->lineEditOrderCode->text())==true){
        ShowResult();
        QMessageBox::information(NULL, "Activation OK"
                                ,"認証されました" );
    }
}

void ActivationDialog::on_pushButtonSelectLicenseFiile_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(nullptr, QString("Select License file")
                                                , QString()
                                                , QString("Lic file(*.lic);;All files(*.*)"));
    if(FileName.isEmpty()==false){
        ui->lineEditLicenseFileName->setText(FileName);
    }
}

void ActivationDialog::on_pushButtonActivateByLicenseFile_clicked()
{
    if(Parent->ActivateByLicenseFile(ui->lineEditLicenseFileName->text())==true){
        ShowResult();
        QMessageBox::information(NULL, "Activation OK"
                                ,"認証されました" );
    }
}

void ActivationDialog::on_pushButtonOK_clicked()
{
    done(true);
}

void ActivationDialog::on_pushButtonLoadLicenseFiile_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(nullptr, QString("Select License file")
                                                , QString()
                                                , QString("Lic file(*.lic);;All files(*.*)"));
    if(FileName.isEmpty()==false){
	    QFile	File(FileName);
	    if(File.open(QIODevice::ReadOnly)==false){
	    	return;
	    }
	    QByteArray	LicenseKey=File.readAll();
        ui->lineEditLicenseKey->setText(LicenseKey);
    }
}

void ActivationDialog::on_pushButtonWriteReqActivationFile_clicked()
{
    QString FileName=QFileDialog::getSaveFileName(nullptr, QString("Write ReqActivation file")
                                                , QString()
                                                , QString("ReqActivation file(*.req);;All files(*.*)"));
    if(FileName.isEmpty()==false){
        Parent->SavePCInfo(ui->lineEditLicenseKey->text(),FileName);
    }
}

void ActivationDialog::on_pushButtonLoadActivationFile_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(nullptr, QString("Load Activation file")
                                                , QString()
                                                , QString("Activation file(*.act);;All files(*.*)"));
    if(FileName.isEmpty()==false){
        Parent->LoadActivation(FileName);
        ShowResult();
    }
}
