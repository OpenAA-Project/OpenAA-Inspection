#include "PropertyGerberFastFormResource.h"
#include "ConfirmLayersDialog.h"
#include "ui_ConfirmLayersDialog.h"
#include "PropertyGerberFastForm.h"
#include "XGeneralFunc.h"

ConfirmLayersDialog::ConfirmLayersDialog(PropertyGerberFastForm *p, bool _CompositeMode ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(p->GetLayersBase())
    ,ui(new Ui::ConfirmLayersDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	Parent=p;
	CompositeMode=_CompositeMode;

	int	Count=0;
	for(int i=0;i<MaxGerberLayer;i++){
		IndexChild[i]=Parent->child[i];
		if(IndexChild[i]->IsValidLine()==true){
			Count++;
		}
	}
	if(CompositeMode==true){
		for(int i=0;i<MaxGerberLayer;i++){
			IndexCompChild[i]=Parent->CompChild[i];
			if(IndexCompChild[i]->IsValidLine()==true){
				Count++;
			}
		}
	}

	ui->tableWidget->setRowCount(Count);
	ui->tableWidget->setColumnWidth(0,30);
	ui->tableWidget->setColumnWidth(1,120);
	ui->tableWidget->setColumnWidth(2,900);
	int	Row=0;
	for(int i=0;i<MaxGerberLayer;i++){
		if(IndexChild[i]->IsValidLine()==true){
			::SetDataToTableCheckable(ui->tableWidget ,0 ,Row ,/**/"",IndexChild[i]->IsOperational());
			::SetDataToTable(ui->tableWidget ,1,Row ,IndexChild[i]->GetTypeName());
			::SetDataToTable(ui->tableWidget ,2,Row ,IndexChild[i]->GetFileName());
			Row++;
		}
	}
	if(CompositeMode==true){
		for(int i=0;i<MaxGerberLayer;i++){
			IndexCompChild[i]=Parent->CompChild[i];
			if(IndexCompChild[i]->IsValidLine()==true){
				::SetDataToTableCheckable(ui->tableWidget ,0 ,Row ,/**/"",IndexCompChild[i]->IsOperational());
				::SetDataToTable(ui->tableWidget ,1,Row ,/**/"Composite");
				::SetDataToTable(ui->tableWidget ,2,Row ,IndexCompChild[i]->GetCompositeName());
				Row++;
			}
		}
	}

	InstallOperationLog(this);
}

ConfirmLayersDialog::~ConfirmLayersDialog()
{
    delete ui;

}

void ConfirmLayersDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	r=ui->tableWidget->currentRow();
	int	Row=0;
	for(int i=0;i<MaxGerberLayer;i++){
		if(IndexChild[i]->IsValidLine()==true){
			if(r==Row){
				bool	b=GetCheckedFromTable(ui->tableWidget ,0 ,Row);
				::SetDataToTableCheckable(ui->tableWidget ,0 ,Row ,/**/"",!b);
			}
			Row++;
		}
	}
	if(CompositeMode==true){
		for(int i=0;i<MaxGerberLayer;i++){
			IndexCompChild[i]=Parent->CompChild[i];
			if(IndexCompChild[i]->IsValidLine()==true){
				if(r==Row){
					bool	b=GetCheckedFromTable(ui->tableWidget ,0 ,Row);
					::SetDataToTableCheckable(ui->tableWidget ,0 ,Row ,/**/"",!b);
				}
				Row++;
			}
		}
	}
}

void ConfirmLayersDialog::on_pushButtonOK_clicked()
{
	int	Row=0;
	for(int i=0;i<MaxGerberLayer;i++){
		if(IndexChild[i]->IsValidLine()==true){
			bool	b=GetCheckedFromTable(ui->tableWidget ,0 ,Row);
			IndexChild[i]->SetOperational(b);
			Row++;
		}
	}
	if(CompositeMode==true){
		for(int i=0;i<MaxGerberLayer;i++){
			IndexCompChild[i]=Parent->CompChild[i];
			if(IndexCompChild[i]->IsValidLine()==true){
				bool	b=GetCheckedFromTable(ui->tableWidget ,0 ,Row);
				IndexCompChild[i]->SetOperational(b);
				Row++;
			}
		}
	}
	done(true);
}

void ConfirmLayersDialog::on_pushButtonClearAll_clicked()
{
	int	Row=0;
	for(int i=0;i<MaxGerberLayer;i++){
		if(IndexChild[i]->IsValidLine()==true){
			::SetDataToTableCheckable(ui->tableWidget ,0 ,Row ,/**/"",false);
			Row++;
		}
	}
	if(CompositeMode==true){
		for(int i=0;i<MaxGerberLayer;i++){
			IndexCompChild[i]=Parent->CompChild[i];
			if(IndexCompChild[i]->IsValidLine()==true){
				::SetDataToTableCheckable(ui->tableWidget ,0 ,Row ,/**/"",false);
				Row++;
			}
		}
	}
}

void ConfirmLayersDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
