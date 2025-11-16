#include "MakeOutlineItemDialog.h"
#include "ui_MakeOutlineItemDialog.h"
#include "XRememberer.h"

MakeOutlineItemDialog::MakeOutlineItemDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::MakeOutlineItemDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    ui->spinBoxOutlineWidth	->setValue(ControlRememberer::GetInt(ui->spinBoxOutlineWidth));
}

MakeOutlineItemDialog::~MakeOutlineItemDialog()
{
    delete ui;
}

void MakeOutlineItemDialog::on_pushButtonGenerate_clicked()
{
     OutlineWidth=ControlRememberer::SetValue(ui->spinBoxOutlineWidth);
     done(true);
}


void MakeOutlineItemDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

