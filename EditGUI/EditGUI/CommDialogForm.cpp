#include "CommDialogForm.h"
#include "ui_CommDialogForm.h"

CommDialogForm::CommDialogForm(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),FormComm(Base)
    ,ui(new Ui::CommDialogForm)
{
    ui->setupUi(this);
    FormComm.setParent(ui->frameFormComm);
    FormComm.move(0,0);
    ui->lineEditFileName->setText(GetLayersBase()->GetParamComm()->GetDefaultFileName());
}

CommDialogForm::~CommDialogForm()
{
    delete ui;
}

void CommDialogForm::on_pushButtonFileName_clicked()
{
    QString	FileName=QFileDialog::getOpenFileName(0
                                   ,/**/"File name for COMM file"
                                   ,QString()
                                   ,"*.dat(*.dat)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
    }
}

void CommDialogForm::on_pushButtonLoad_clicked()
{
    QString	FileName=ui->lineEditFileName->text();
    if(QFile::exists(FileName)==true){
        GetParamComm()->LoadFromFile(FileName);
        FormComm.Show();
    }
}

void CommDialogForm::on_pushButtonUpdate_clicked()
{
    FormComm.LoadFromWindow();
    QString	FileName=ui->lineEditFileName->text();
    GetParamComm()->SaveToFile(FileName);
}

void CommDialogForm::on_pushButtonSaveNew_clicked()
{
    QString	FileName=QFileDialog::getSaveFileName(0
                                   ,/**/"File name for COMM file"
                                   ,QString()
                                   ,"*.dat(*.dat)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
        FormComm.LoadFromWindow();
        GetParamComm()->SaveToFile(FileName);
    }
}

void CommDialogForm::on_pushButtonClose_clicked()
{
    close();
}
