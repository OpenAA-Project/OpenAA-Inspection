#include "EditManualInterpolateDialog.h"
#include "ui_EditManualInterpolateDialog.h"
#include<QInputDialog>

EditManualInterpolateDialog::EditManualInterpolateDialog(AlgorithmItemRoot *item ,LayersBase *Base,QWidget *parent)
    : QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditManualInterpolateDialog)
{
    ui->setupUi(this);
    Item=item;
    ShowList();
}

EditManualInterpolateDialog::~EditManualInterpolateDialog()
{
    delete ui;
}

void	EditManualInterpolateDialog::ShowList(void)
{
    ColorDifferenceItem *E=dynamic_cast<ColorDifferenceItem *>(Item);
    if(E!=NULL){
        if(E->GetThresholdR()->JudgeMethod==1){
            int N=E->ManualDeltaEList.GetCount();
            ui->tableWidget->setRowCount(N);
            for(int row=0;row<N;row++){
                ManualAdjustmentList    *R=E->ManualDeltaEList.GetItem(row);
                ::SetDataToTable(ui->tableWidget, 0,row, R->RegisteredTime.toString(/**/"yy/MM/dd hh:mm:ss"));
                ::SetDataToTable(ui->tableWidget, 1,row, QString::number(R->ImageValue,'f',3));
                ::SetDataToTable(ui->tableWidget, 2,row, QString::number(R->ManualValue,'f',3));
            }
        }
        else
        if(E->GetThresholdR()->JudgeMethod==3){
            int N=E->ManualDenseList.GetCount();
            ui->tableWidget->setRowCount(N);
            for(int row=0;row<N;row++){
                ManualAdjustmentList    *R=E->ManualDenseList.GetItem(row);
                ::SetDataToTable(ui->tableWidget, 0,row, R->RegisteredTime.toString(/**/"yy/MM/dd hh:mm:ss"));
                ::SetDataToTable(ui->tableWidget, 1,row, QString::number(R->ImageValue,'f',3));
                ::SetDataToTable(ui->tableWidget, 2,row, QString::number(R->ManualValue,'f',3));
            }
        }
    }
}

void EditManualInterpolateDialog::on_pushButtonDeleteLine_clicked()
{
    int Row=ui->tableWidget->currentRow();
    ColorDifferenceItem *E=dynamic_cast<ColorDifferenceItem *>(Item);
    if(E!=NULL){
        if(E->GetThresholdR()->JudgeMethod==1){
            ManualAdjustmentList    *R=E->ManualDeltaEList.GetItem(Row);
            if(R!=NULL){
                E->ManualDeltaEList.RemoveList(R);
                delete  R;
            }
        }
        else
        if(E->GetThresholdR()->JudgeMethod==3){
            ManualAdjustmentList    *R=E->ManualDenseList.GetItem(Row);
            if(R!=NULL){
                E->ManualDenseList.RemoveList(R);
                delete  R;
            }
        }
        ShowList();
    }
}


void EditManualInterpolateDialog::on_pushButtonClose_clicked()
{
    done(true);
}


void EditManualInterpolateDialog::on_pushButtonAdd_clicked()
{
    bool    ok;
    double d=QInputDialog::getDouble(NULL, "Add Manual value"
                    , "測定値を追加します"
                    ,0, -2147483647, 2147483647, 3, &ok);
	if(ok==true){
        ColorDifferenceItem *E=dynamic_cast<ColorDifferenceItem *>(Item);
        if(E!=NULL){
            if(E->GetThresholdR()->JudgeMethod==1){
                E->AddManualDeltaE(d);
            }
            else
            if(E->GetThresholdR()->JudgeMethod==3){
                E->AddManualDense(d);
            }
            ShowList();
        }
	}
}
    
