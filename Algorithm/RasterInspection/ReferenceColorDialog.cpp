#include "ReferenceColorDialog.h"
#include "ui_ReferenceColorDialog.h"
#include "EditWaveGraphDialog.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRasterInspection.h"
#include <QDir>
#include <QFile>

ReferenceColorDialog::ReferenceColorDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::ReferenceColorDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 25);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 75);

    ShowGrid();
}

ReferenceColorDialog::~ReferenceColorDialog()
{
    delete ui;
}
RasterInspectionBase	*ReferenceColorDialog::GetRasterInspectionBase(void)
{
	return (RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
}

void ReferenceColorDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    int Row=ui->tableWidget->currentRow();
    if(Row<0)
        return;
    ReferencePDF    *R=GetRasterInspectionBase()->RContainer[Row];
    if(R!=NULL){
        EditWaveGraphDialog D(R,GetLayersBase());
        int Ret=D.exec();
        if(Ret==1){
            GetRasterInspectionBase()->RContainer.RemoveList(R);
            delete  R;
            ShowGrid();
        }
        else if(Ret==3){
            R->ReferenceName=D.ReferenceName;
            ShowGrid();
        }
    }
}

void ReferenceColorDialog::ShowGrid(void)
{
    ui->tableWidget->setRowCount(GetRasterInspectionBase()->RContainer.GetCount());
    int Row=0;
    for(ReferencePDF *r=GetRasterInspectionBase()->RContainer.GetFirst();r!=NULL;r=r->GetNext(),Row++){
        QColor  Col=r->PDFColor;
        ::SetDataColorToTable(ui->tableWidget, 0, Row, Col);
        ::SetDataToTable     (ui->tableWidget, 1, Row, r->ReferenceName);
    }
}

void ReferenceColorDialog::on_pushButtonUpdateClose_clicked()
{
    GetRasterInspectionBase()->SaveDefault(GetLayersBase()->GetUserPath());
    done(true);
}


void ReferenceColorDialog::on_pushButtonCancel_clicked()
{
    done(true);
}

