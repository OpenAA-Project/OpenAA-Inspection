#include "FilterSettingDialog.h"
#include "ui_FilterSettingDialog.h"

FilterSettingDialog::FilterSettingDialog(int position ,double strength ,LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::FilterSettingDialog)
{
    ui->setupUi(this);
	Position	=position;
	Strength	=strength;
	ui->spinBoxPosition			->setValue(Position);
	ui->doubleSpinBoxStrength	->setValue(Strength);
}

FilterSettingDialog::~FilterSettingDialog()
{
    delete ui;
}

void FilterSettingDialog::on_pushButtonOK_clicked()
{
	Position	=ui->spinBoxPosition		->value();
	Strength	=ui->doubleSpinBoxStrength	->value();
	done(true);
}

void FilterSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
