#include "PropertyCheckEverydayFormResource.h"
#include "CreateManualFocusDialog.h"
#include "ui_CreateManualFocusDialog.h"
#include "XRememberer.h"

CreateManualFocusDialog::CreateManualFocusDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CreateManualFocusDialog)
{
    ui->setupUi(this);

	ui->lineEditItemName		->setText (ControlRememberer::GetString(ui->lineEditItemName ,/**/""));	
	ui->doubleSpinBoxFocusLow	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxFocusLow ,0));
	InstallOperationLog(this);
}

CreateManualFocusDialog::~CreateManualFocusDialog()
{
    delete ui;
}

void	CreateManualFocusDialog::Reflect(void)
{
	ui->lineEditItemName		->setText(ItemName);
	ui->doubleSpinBoxFocusLow	->setValue(FocusLow);
}

void CreateManualFocusDialog::on_pushButtonOK_clicked()
{
	ItemName	=ui->lineEditItemName		->text();
	FocusLow	=ui->doubleSpinBoxFocusLow	->value();

	ControlRememberer::SetValue(ui->lineEditItemName		,ui->lineEditItemName->text());
	ControlRememberer::SetValue(ui->doubleSpinBoxFocusLow	,ui->doubleSpinBoxFocusLow->value());

	accept();
}

void CreateManualFocusDialog::on_pushButtonCancel_clicked()
{
    reject();
}
