#include "SelectGerberAlgoTYpeDialog.h"
#include "ui_SelectGerberAlgoTYpeDialog.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"

SelectGerberAlgoTYpeDialog::SelectGerberAlgoTYpeDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectGerberAlgoTYpeDialog)
{
    ui->setupUi(this);

	GerberAlgoType=-1;

	InstallOperationLog(this);
}

SelectGerberAlgoTYpeDialog::~SelectGerberAlgoTYpeDialog()
{
    delete ui;
}

void SelectGerberAlgoTYpeDialog::on_pushButtonOK_clicked()
{
	if(ui->checkBoxMakeAlgoShiftable->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromShiftable;
	}
	if(ui->checkBoxMakeAlgoSeparate->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromStable;
	}
	if(ui->checkBoxMakeAlgoEnlarge->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromEnlarge;
	}
	if(ui->checkBoxMakeAlgoShrinked->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromShrinked;
	}
	done(true);
}

void SelectGerberAlgoTYpeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
