#include "ChoicePhaseDialog.h"
#include "ui_ChoicePhaseDialog.h"

//ChoicePhaseDialog::ChoicePhaseDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::ChoicePhaseDialog)
ChoicePhaseDialog::ChoicePhaseDialog(ChosenPhase *chosenPhase,LayersBase *LBase,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoicePhaseDialog)
{
    ui->setupUi(this);
	_LBase = LBase;
	_isQuit = true;
	_chosenPhase = chosenPhase;
}

ChoicePhaseDialog::~ChoicePhaseDialog()
{
    delete ui;
}

void ChoicePhaseDialog::on_pbFront_clicked()
{
	_isQuit = false;
	_chosenPhase->setPhaseNumber(0);
	//_LBase->TF_SetCurrentScanPhaseNumber(0);
	close();
}

void ChoicePhaseDialog::on_pbBack_clicked()
{
	_isQuit = false;
	_chosenPhase->setPhaseNumber(1);
	//_LBase->TF_SetCurrentScanPhaseNumber(1);
	close();
}

void ChoicePhaseDialog::on_pbClose_clicked()
{
	close();
}
