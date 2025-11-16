#include "ChangeDialog.h"
#include "ui_ChangeDialog.h"
#include "XDataInLayer.h"

ChangeDialog::ChangeDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ChangeDialog)
{
    ui->setupUi(this);

	NewPhaseCount	=GetPhaseNumb();
	NewPageCount	=GetPageNumb();
	NewLayerCount	=GetLayersBase()->GetMaxLayerNumb();
	NewLineCount	=GetMaxLines(-1);

	ui->spinBoxPhaseCount	->setValue(NewPhaseCount	);
	ui->spinBoxPageCount	->setValue(NewPageCount		);
	ui->spinBoxLayerCount	->setValue(NewLayerCount	);
	ui->spinBoxLineCount	->setValue(NewLineCount		);
}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}

void ChangeDialog::on_pushButtonExecute_clicked()
{
	NewPhaseCount	=ui->spinBoxPhaseCount	->value();
	NewPageCount	=ui->spinBoxPageCount	->value();
	NewLayerCount	=ui->spinBoxLayerCount	->value();
	NewLineCount	=ui->spinBoxLineCount	->value();
	done(true);
}

void ChangeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
