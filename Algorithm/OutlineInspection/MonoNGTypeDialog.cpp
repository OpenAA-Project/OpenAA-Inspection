#include "MonoNGTypeDialog.h"
#include "ui_MonoNGTypeDialog.h"
#include "XOutlineLibrary.h"

MonoNGTypeDialog::MonoNGTypeDialog(LayersBase *base, OutlineInspectLibNGTypeItem *item ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Item(item)
    ,ui(new Ui::MonoNGTypeDialog)
{
    ui->setupUi(this);

	int ColL,ColH;
	Item->ColorZone.GetMonoColorRange(ColL,ColH);
	ui->spinBoxMinColor		->setValue(ColL);
	ui->spinBoxMaxColor		->setValue(ColH);
	ui->spinBoxMinSize		->setValue(Item->MinSize);
	ui->spinBoxMaxSize		->setValue(Item->MaxSize);
	ui->spinBoxMinRoundRate	->setValue(Item->MinRoundRate);
	ui->spinBoxMaxRoundRate	->setValue(Item->MaxRoundRate);

	InstallOperationLog(this);
}

MonoNGTypeDialog::~MonoNGTypeDialog()
{
    delete ui;
}

void MonoNGTypeDialog::on_pushButtonOK_clicked()
{
	int	ColL			=ui->spinBoxMinColor->value();
	int	ColH			=ui->spinBoxMaxColor->value();
	Item->ColorZone.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	Item->MinSize		=ui->spinBoxMinSize->value();
	Item->MaxSize		=ui->spinBoxMaxSize->value();
	Item->MinRoundRate	=ui->spinBoxMinRoundRate->value();
	Item->MaxRoundRate	=ui->spinBoxMaxRoundRate->value();
	done(true);
}
