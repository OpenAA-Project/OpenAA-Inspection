#include "DisplayImageResource.h"
#include "PourImageDialog.h"
#include "ui_PourImageDialog.h"
#include "XRememberer.h"
#include "XDataInLayer.h"

PourImageDialog::PourImageDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::PourImageDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

    ui->spinBoxPickup	->setValue(ControlRememberer::GetInt(ui->spinBoxPickup));
    ui->spinBoxExpand	->setValue(ControlRememberer::GetInt(ui->spinBoxExpand));
}

PourImageDialog::~PourImageDialog()
{
    delete ui;
}

void PourImageDialog::on_pushButtonGo_clicked()
{
    PickupBrightness    =ControlRememberer::SetValue(ui->spinBoxPickup);
    ExpandedDot         =ControlRememberer::SetValue(ui->spinBoxExpand);
    done(true);
}


void PourImageDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

