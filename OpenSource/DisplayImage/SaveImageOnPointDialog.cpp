#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SaveImageOnPointDialog.h"
#include "ui_SaveImageOnPointDialog.h"
#include "XDisplayImage.h"

SaveImageOnPointDialog::SaveImageOnPointDialog(DisplayImage *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base->GetLayersBase())
    ,ui(new Ui::SaveImageOnPointDialog)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    ImageBase=Base;

    ui->spinBoxXDot->setValue(ImageBase->SaveImageSizeXDot);
    ui->spinBoxYDot->setValue(ImageBase->SaveImageSizeYDot);
    ui->comboBoxXCount	->setCurrentIndex(ui->comboBoxXCount->findText(QString::number(ImageBase->SaveImageXCount)));
    ui->comboBoxYCount	->setCurrentIndex(ui->comboBoxYCount->findText(QString::number(ImageBase->SaveImageYCount)));
    if(ImageBase->ImgFormat==/**/"BMP"){
        ui->comboBoxFormat->setCurrentIndex(0);
    }
    else if(ImageBase->ImgFormat==/**/"JPG"){
        ui->comboBoxFormat->setCurrentIndex(1);
    }
    else if(ImageBase->ImgFormat==/**/"PNG"){
        ui->comboBoxFormat->setCurrentIndex(2);
    }
}

SaveImageOnPointDialog::~SaveImageOnPointDialog()
{
    delete ui;
}

void SaveImageOnPointDialog::on_pushButtonOK_clicked()
{
    ImageBase->SaveImageSizeXDot	=ui->spinBoxXDot->value();
    ImageBase->SaveImageSizeYDot	=ui->spinBoxYDot->value();
    ImageBase->SaveImageXCount		=ui->comboBoxXCount	->currentText ().toInt();
    ImageBase->SaveImageYCount		=ui->comboBoxYCount	->currentText ().toInt();
    switch(ui->comboBoxFormat->currentIndex()){
        case 0:	ImageBase->ImgFormat=/**/"BMP";
                break;
        case 1:	ImageBase->ImgFormat=/**/"JPG";
                break;
        case 2:	ImageBase->ImgFormat=/**/"PNG";
                break;
    }
    done(true);
}

void SaveImageOnPointDialog::on_pushButton_2_clicked()
{
    done(false);
}
