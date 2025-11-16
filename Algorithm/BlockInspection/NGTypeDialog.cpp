#include "BlockFormResource.h"
#include "NGTypeDialog.h"
#include "XBlockLibrary.h"

NGTypeDialog::NGTypeDialog(LayersBase *base, BlockLibNGTypeItem *item ,QWidget *parent)
	: QDialog(parent)
	,ServiceForLayers(base)
	,Item(item)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	ui.spinBoxMinColor	->setValue(Item->MinColor);
	ui.spinBoxMaxColor	->setValue(Item->MaxColor);
	ui.spinBoxMinSize	->setValue(Item->MinSize);
	ui.spinBoxMaxSize	->setValue(Item->MaxSize);
	ui.spinBoxMinRoundRate->setValue(Item->MinRoundRate);
	ui.spinBoxMaxRoundRate->setValue(Item->MaxRoundRate);

	InstallOperationLog(this);
}

NGTypeDialog::~NGTypeDialog()
{

}


void NGTypeDialog::on_pushButtonOK_clicked()
{
	Item->MinColor	=ui.spinBoxMinColor->value();
	Item->MaxColor	=ui.spinBoxMaxColor->value();
	Item->MinSize	=ui.spinBoxMinSize->value();
	Item->MaxSize	=ui.spinBoxMaxSize->value();
	Item->MinRoundRate	=ui.spinBoxMinRoundRate->value();
	Item->MaxRoundRate	=ui.spinBoxMaxRoundRate->value();
	done(true);
}