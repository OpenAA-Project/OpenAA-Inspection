#include "SelectPriorityInAreaDialog.h"
#include "ui_SelectPriorityInAreaDialog.h"

SelectPriorityInAreaDialog::SelectPriorityInAreaDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectPriorityInAreaDialog)
{
    ui->setupUi(this);
}

SelectPriorityInAreaDialog::~SelectPriorityInAreaDialog()
{
    delete ui;
}

void SelectPriorityInAreaDialog::on_pushButtonOK_clicked()
{
	if(ui->radioButtonPriorityHigh->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityHigh;
	}
	else if(ui->radioButtonPriorityMiddle->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityMiddle;
	}
	else if(ui->radioButtonPriorityLow->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityLow;
	}
	else if(ui->radioButtonPriorityLGlobal->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityGlobal;
	}
	done(true);
}


void SelectPriorityInAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

