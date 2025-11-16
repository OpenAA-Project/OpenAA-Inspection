#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectLibraryOneDialog.h"
#include "ui_SelectLibraryOneDialog.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"

SelectLibraryOneDialog::SelectLibraryOneDialog(LayersBase *Base
												,int LibType,const IntList &_LibList
												,QWidget *parent) :
    QDialog(parent),
	ServiceForLayers(Base),
    ui(new Ui::SelectLibraryOneDialog)
{
    ui->setupUi(this);
	LangLibSolver.SetUI(this);

	ui->tableWidget->setColumnWidth (0, 64);
	ui->tableWidget->setColumnWidth (1, 220);

	SelectedLibID=-1;
	LibList=_LibList;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmLibraryContainer	*ALibC=ABase->GetLibraryContainer();
		if(ALibC!=NULL){
			ui->tableWidget->setRowCount(LibList.GetCount());
			int	Row=0;
			for(IntClass *d=LibList.GetFirst();d!=NULL;d=d->GetNext(),Row++){
				int	LibID=d->GetValue();
				QString	LibName=ALibC->GetLibraryName(LibID);
				SetDataToTable(ui->tableWidget,0 ,Row ,QString::number(LibID));
				SetDataToTable(ui->tableWidget,1 ,Row ,LibName);
			}
		}
	}

	InstallOperationLog(this);
}

SelectLibraryOneDialog::~SelectLibraryOneDialog()
{
    delete ui;
}

void SelectLibraryOneDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectLibraryOneDialog::on_pushButtonSelect_clicked()
{
	int	n=ui->tableWidget->currentRow();
	if(n<0)
		return;
	SelectedLibID=LibList[n];
	done(true);
}

void SelectLibraryOneDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
