#include "ChooseItemTypeFormResource.h"
#include "ChooseItemTypeForm.h"

ChooseItemTypeForm::ChooseItemTypeForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

ChooseItemTypeForm::~ChooseItemTypeForm()
{

}


void ChooseItemTypeForm::on_toolButtonPad_clicked()
{
	done((int)Type_Pad);
}

void ChooseItemTypeForm::on_toolButtonLine_clicked()
{
	done((int)Type_Line);
}

void ChooseItemTypeForm::on_toolButtonMatchingLine_clicked()
{
	done((int)Type_Matching);
}