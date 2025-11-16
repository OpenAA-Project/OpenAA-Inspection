#include "PropertyGerberFastFormResource.h"
#include "SelectStepInODBDialog.h"
#include "ui_SelectStepInODBDialog.h"

SelectStepInODBDialog::SelectStepInODBDialog(LayersBase *base, ODBStepContainer &stepdata,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectStepInODBDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	StepData=stepdata;

	ui->tableWidget	->setColumnWidth(0,ui->tableWidget->width()-24);
	ui->tableWidget	->setRowCount(StepData.GetCount());
	int	Row=0;
	for(ODBStepList *L=StepData.GetFirst();L!=NULL;L=L->GetNext()){
		::SetDataToTableCheckable(ui->tableWidget,0,Row ,L->Name,L->Usage);
		Row++;
	}

	InstallOperationLog(this);
}

SelectStepInODBDialog::~SelectStepInODBDialog()
{
    delete ui;
}

void SelectStepInODBDialog::on_pushButtonOK_clicked()
{
	int	Row=0;
	for(ODBStepList *L=StepData.GetFirst();L!=NULL;L=L->GetNext()){
		L->Usage=::GetCheckedFromTable(ui->tableWidget,0,Row);
		Row++;
	}
	done(true);
}

void SelectStepInODBDialog::on_pushButtonClose_clicked()
{
	done(false);
}
