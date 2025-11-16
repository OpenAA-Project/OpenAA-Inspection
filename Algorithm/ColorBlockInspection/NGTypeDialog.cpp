#include "NGTypeDialog.h"
#include "ui_NGTypeDialog.h"
#include "XColorBlockLibrary.h"

NGTypeDialog::NGTypeDialog(LayersBase *base, ColorBlockLibNGTypeItem *item ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Item(item)
    ,ui(new Ui::NGTypeDialog)
{
    ui->setupUi(this);

	ui->spinBoxMinColorR	->setValue(Item->MinColorR);
	ui->spinBoxMaxColorR	->setValue(Item->MaxColorR);

	ui->spinBoxMinColorG	->setValue(Item->MinColorG);
	ui->spinBoxMaxColorG	->setValue(Item->MaxColorG);

	ui->spinBoxMinColorB	->setValue(Item->MinColorB);
	ui->spinBoxMaxColorB	->setValue(Item->MaxColorB);

	ui->spinBoxMinSize		->setValue(Item->MinSize);
	ui->spinBoxMaxSize		->setValue(Item->MaxSize);
	ui->spinBoxMinRoundRate	->setValue(Item->MinRoundRate);
	ui->spinBoxMaxRoundRate	->setValue(Item->MaxRoundRate);

	InstallOperationLog(this);
}

NGTypeDialog::~NGTypeDialog()
{
    delete ui;
}

void NGTypeDialog::on_pushButtonOK_clicked()
{
	Item->MinColorR		=ui->spinBoxMinColorR->value();
	Item->MaxColorR		=ui->spinBoxMaxColorR->value();

	Item->MinColorG		=ui->spinBoxMinColorG->value();
	Item->MaxColorG		=ui->spinBoxMaxColorG->value();

	Item->MinColorB		=ui->spinBoxMinColorB->value();
	Item->MaxColorB		=ui->spinBoxMaxColorB->value();

	Item->MinSize		=ui->spinBoxMinSize->value();
	Item->MaxSize		=ui->spinBoxMaxSize->value();
	Item->MinRoundRate	=ui->spinBoxMinRoundRate->value();
	Item->MaxRoundRate	=ui->spinBoxMaxRoundRate->value();
	done(true);
}
