#include "ButtonShrinkImageResource.h"
#include "ShrinkImageDialog.h"

ShrinkImageDialog::ShrinkImageDialog(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

ShrinkImageDialog::~ShrinkImageDialog()
{

}


void ShrinkImageDialog::on_pushButtonOk_clicked()
{
	Rate		=ui.doubleSpinBoxRate->value();
	ExeMaster	=ui.checkBoxExeMaster->isChecked();
	ExeTarget	=ui.checkBoxExeTarget->isChecked();
	done(true);
}

void ShrinkImageDialog::on_pushButtonCancel_clicked()
{
	done(false);
}