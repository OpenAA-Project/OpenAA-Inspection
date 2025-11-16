#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "SelectShadowTreeDialog.h"
#include "XDataInLayer.h"
#include "XShadowTree.h"
#include "XGeneralFunc.h"

SettingDialog::SettingDialog(LayersBase *base ,FromToClass &Data,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPageSrc->addItem(QString("Page ")+QString::number(page));
        ui->listWidgetPageDst->addItem(QString("Page ")+QString::number(page));
    }

    if(Data.SrcType==FromToClass::Info_AllPages){
        ui->radioButtonAllPagesSrc->setChecked(true);
        on_radioButtonAllPagesSrc_clicked();
    }
    else
    if(Data.SrcType==FromToClass::Info_File){
        ui->radioButtonFileSrc->setChecked(true);
        ui->lineEditFileNameSrc->setText(Data.SrcFileName);
        on_radioButtonFileSrc_clicked();
    }
    else
    if(Data.SrcType==FromToClass::Info_Page){
        ui->radioButtonPageSrc->setChecked(true);
        ::SetSelectedRows(ui->listWidgetPageSrc, Data.SrcPage);
        on_radioButtonPageSrc_clicked();
    }
    else
    if(Data.SrcType==FromToClass::Info_Shadow){
        ui->radioButtonShadowSrc->setChecked(true);
        on_radioButtonShadowSrc_clicked();
    }

    if(Data.DstType==FromToClass::Info_AllPages){
        ui->radioButtonAllPagesDst->setChecked(true);
        on_radioButtonAllPagesDst_clicked();
    }
    else
    if(Data.DstType==FromToClass::Info_File){
        ui->radioButtonFileDst->setChecked(true);
        ui->lineEditFileNameDst->setText(Data.DstFileName);
        on_radioButtonFileDst_clicked();
    }
    else
    if(Data.DstType==FromToClass::Info_Page){
        ui->radioButtonPageDst->setChecked(true);
        ::SetSelectedRows(ui->listWidgetPageDst, Data.DstPage);
        on_radioButtonPageDst_clicked();
    }
    else
    if(Data.DstType==FromToClass::Info_Shadow){
        ui->radioButtonShadowDst->setChecked(true);
        on_radioButtonShadowDst_clicked();
    }
}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::on_radioButtonAllPagesSrc_clicked()
{
    ui->stackedWidgetSrc->setCurrentIndex(0);
}


void SettingDialog::on_radioButtonFileSrc_clicked()
{
    ui->stackedWidgetSrc->setCurrentIndex(1);
}


void SettingDialog::on_radioButtonPageSrc_clicked()
{
    ui->stackedWidgetSrc->setCurrentIndex(2);
}


void SettingDialog::on_radioButtonShadowSrc_clicked()
{
    ui->stackedWidgetSrc->setCurrentIndex(3);
}

void SettingDialog::on_radioButtonAllPagesDst_clicked()
{
    ui->stackedWidgetDst->setCurrentIndex(0);
}


void SettingDialog::on_radioButtonFileDst_clicked()
{
    ui->stackedWidgetDst->setCurrentIndex(1);
}


void SettingDialog::on_radioButtonPageDst_clicked()
{
    ui->stackedWidgetDst->setCurrentIndex(2);
}


void SettingDialog::on_radioButtonShadowDst_clicked()
{
    ui->stackedWidgetDst->setCurrentIndex(3);
}


void SettingDialog::on_pushButtonShadowTreeSrc_clicked()
{
    SelectShadowTreeDialog  D(GetLayersBase());
    D.Initial(InfoData.SrcShadowLevel,InfoData.SrcShadowNumber);
    if(D.exec()==true){
        InfoData.SrcShadowLevel =D.ShadowTreePoint->GetShadowLevel();
        InfoData.SrcShadowNumber=D.ShadowTreePoint->GetShadowNumber();
    }
}


void SettingDialog::on_pushButtonShadowTreeDst_clicked()
{
    SelectShadowTreeDialog  D(GetLayersBase());
    D.Initial(InfoData.SrcShadowLevel,InfoData.SrcShadowNumber);
    if(D.exec()==true){
        InfoData.DstShadowLevel =D.ShadowTreePoint->GetShadowLevel();
        InfoData.DstShadowNumber=D.ShadowTreePoint->GetShadowNumber();
    }
}


void SettingDialog::on_pushButtonOK_clicked()
{
    if(ui->radioButtonAllPagesSrc->isChecked()==true)
        InfoData.SrcType=FromToClass::Info_AllPages;
    else
    if(ui->radioButtonFileSrc->isChecked()==true){
        InfoData.SrcType=FromToClass::Info_File;
        InfoData.SrcFileName=ui->lineEditFileNameSrc->text();
    }
    else
    if(ui->radioButtonPageSrc->isChecked()==true){
         InfoData.SrcType=FromToClass::Info_Page;
        ::GetSelectedRows(ui->listWidgetPageSrc, InfoData.SrcPage);
    }
    else
    if(ui->radioButtonShadowSrc->isChecked()==true){
        InfoData.SrcType=FromToClass::Info_Shadow;
    }

    if(ui->radioButtonAllPagesDst->isChecked()==true)
        InfoData.DstType=FromToClass::Info_AllPages;
    else
    if(ui->radioButtonFileDst->isChecked()==true){
        InfoData.DstType=FromToClass::Info_File;
        InfoData.DstFileName=ui->lineEditFileNameDst->text();
    }
    else
    if(ui->radioButtonPageDst->isChecked()==true){
         InfoData.DstType=FromToClass::Info_Page;
        ::GetSelectedRows(ui->listWidgetPageDst, InfoData.DstPage);
    }
    else
    if(ui->radioButtonShadowDst->isChecked()==true){
        InfoData.DstType=FromToClass::Info_Shadow;
    }
    done(true);
}

