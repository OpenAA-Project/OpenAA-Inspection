#include "SettingMoveImageForm.h"
#include "ui_SettingMoveImageForm.h"

SettingMoveImageForm::SettingMoveImageForm(LayersBase *base,int dx ,int dy ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingMoveImageForm)
{
    ui->setupUi(this);
	ui->spinBoxDx->setValue(dx);
	ui->spinBoxDy->setValue(dy);
	Dx=dx;
	Dy=dy;

	InstallOperationLog(this);
}

SettingMoveImageForm::~SettingMoveImageForm()
{
    delete ui;
}

void SettingMoveImageForm::on_pushButtonOK_clicked()
{
	Dx=ui->spinBoxDx->value();
	Dy=ui->spinBoxDy->value();
	done(true);
}

void SettingMoveImageForm::on_pushButtonCancel_clicked()
{
	done(false);
}
