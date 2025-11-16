#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectColorDialog.h"
#include "ui_SelectColorDialog.h"
#include "XDataInLayer.h"
#include<QColorDialog>

SelectColorDialog::SelectColorDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectColorDialog)
   
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

    if(GetLayerNumb(0)>=3){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else{
        ui->stackedWidget->setCurrentIndex(1);
    }
    base->InstallOperationLog(this);
}

SelectColorDialog::~SelectColorDialog()
{
    delete ui;
}

void SelectColorDialog::on_pushButtonOK_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        Color=QColor(ui->spinBoxRed->value()
                    ,ui->spinBoxGreen->value()
                    ,ui->spinBoxBlue->value());
    }
    else{
        Color=QColor(ui->spinBoxBrightness->value()
                    ,ui->spinBoxBrightness->value()
                    ,ui->spinBoxBrightness->value());
    }
    done(true);
}

void SelectColorDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

void SelectColorDialog::on_pushButtonColor_clicked()
{
    Color=QColorDialog::getColor (QColor(ui->spinBoxRed->value()
                                        ,ui->spinBoxGreen->value()
                                        ,ui->spinBoxBlue->value())
                                 , this);
    if(Color.isValid()==true){
        ui->spinBoxRed	->setValue(Color.red());
        ui->spinBoxGreen->setValue(Color.green());
        ui->spinBoxBlue	->setValue(Color.blue());
    }
}
