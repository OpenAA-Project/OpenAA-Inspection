#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectImageFormatForm.h"
#include "ui_SelectImageFormatForm.h"
#include "XDisplayImage.h"

SelectImageFormatForm::SelectImageFormatForm(DisplayImage *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base->GetLayersBase())
    ,ui(new Ui::SelectImageFormatForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    ImageBase=Base;
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

SelectImageFormatForm::~SelectImageFormatForm()
{
    delete ui;
}

void SelectImageFormatForm::on_pushButtonOK_clicked()
{
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

void SelectImageFormatForm::on_pushButtonCancel_clicked()
{
    done(false);
}
