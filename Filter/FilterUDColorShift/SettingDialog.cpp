#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog),ServiceForLayers(base)
{
    ui->setupUi(this);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
void	SettingDialog::Initial(int	_ShiftR ,int _ShiftG ,int _ShiftB 
								,bool _CheckTime ,int _TimeRange,int _ShiftOffset)
{
	ui->spinBoxShiftR		->setValue(_ShiftR);
	ui->spinBoxShiftG		->setValue(_ShiftG);
	ui->spinBoxShiftB		->setValue(_ShiftB);
	ui->spinBoxTimeRange	->setValue(_TimeRange);
	ui->checkBoxCheckTime	->setChecked(_CheckTime);
	ui->spinBoxShiftOffset	->setValue(_ShiftOffset);
}

void SettingDialog::on_pushButtonOK_clicked()
{
	ShiftR		=ui->spinBoxShiftR		->value();
	ShiftG		=ui->spinBoxShiftG		->value();
	ShiftB		=ui->spinBoxShiftB		->value();
	TimeRange	=ui->spinBoxTimeRange	->value();
	CheckTime	=ui->checkBoxCheckTime	->isChecked();
	ShiftOffset	=ui->spinBoxShiftOffset	->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
