#include "SettingFormSmoothLarge.h"
#include "ui_SettingFormSmoothLarge.h"

SettingFormSmoothLarge::SettingFormSmoothLarge(LayersBase *base,int windowSize,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingFormSmoothLarge)
{
    ui->setupUi(this);

	WindowSize=windowSize;
	ui->spinBoxWindowSize->setValue(WindowSize);

	InstallOperationLog(this);
}

SettingFormSmoothLarge::~SettingFormSmoothLarge()
{
    delete ui;
}

void SettingFormSmoothLarge::on_pushButtonOK_clicked()
{
	WindowSize	=ui->spinBoxWindowSize->value();
	done(true);
}

void SettingFormSmoothLarge::on_pushButtonCancel_clicked()
{
	done(false);
}
