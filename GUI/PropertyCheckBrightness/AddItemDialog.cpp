#include "AddItemDialogResource.h"
#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"

AddItemDialog::AddItemDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void	AddItemDialog::Reflect(void)
{
	ui->lineEditItemName->setText(ItemName);
	if(Condition	==CheckBrightnessItem::_AverageMustBeInside)
		ui->comboBoxCondition->setCurrentIndex(0);
	else if(Condition	==CheckBrightnessItem::_AllMustBeInside)
		ui->comboBoxCondition->setCurrentIndex(1);
	else if(Condition	==CheckBrightnessItem::_OneMustBeInsideAtLeast)
		ui->comboBoxCondition->setCurrentIndex(2);
	else if(Condition	==CheckBrightnessItem::_AverageMustBeOutside)
		ui->comboBoxCondition->setCurrentIndex(3);
	else if(Condition	==CheckBrightnessItem::_AllMustBeOutside)
		ui->comboBoxCondition->setCurrentIndex(4);
	else if(Condition	==CheckBrightnessItem::_OneMustBeOutsideAtLeast)
		ui->comboBoxCondition->setCurrentIndex(5);

	ui->spinBoxThreshL	->setValue(ThreshL);
	ui->spinBoxThreshH	->setValue(ThreshH);
	ui->spinBoxRegNumber->setValue(RegNumber);
	ui->spinBoxRepeatableCount	->setValue(RepeatableCount);
}

void AddItemDialog::on_pushButtonOK_clicked()
{
	ItemName	=ui->lineEditItemName->text();
	if(ui->comboBoxCondition->currentIndex()==0)
		Condition	=CheckBrightnessItem::_AverageMustBeInside;
	else if(ui->comboBoxCondition->currentIndex()==1)
		Condition	=CheckBrightnessItem::_AllMustBeInside;
	else if(ui->comboBoxCondition->currentIndex()==2)
		Condition	=CheckBrightnessItem::_OneMustBeInsideAtLeast;
	else if(ui->comboBoxCondition->currentIndex()==3)
		Condition	=CheckBrightnessItem::_AverageMustBeOutside;
	else if(ui->comboBoxCondition->currentIndex()==4)
		Condition	=CheckBrightnessItem::_AllMustBeOutside;
	else if(ui->comboBoxCondition->currentIndex()==5)
		Condition	=CheckBrightnessItem::_OneMustBeOutsideAtLeast;
	ThreshL	=ui->spinBoxThreshL->value();
	ThreshH	=ui->spinBoxThreshH->value();
	RegNumber		=ui->spinBoxRegNumber		->value();
	RepeatableCount	=ui->spinBoxRepeatableCount	->value();
	done(true);
}

void AddItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
