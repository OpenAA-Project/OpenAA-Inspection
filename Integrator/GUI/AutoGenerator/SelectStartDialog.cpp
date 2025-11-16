#include "SelectStartDialog.h"
#include "ui_SelectStartDialog.h"
#include "AutoGeneratorForm.h"
#include "AutoGeneratorButtonForm.h"
#include "XGeneralFunc.h"

SelectStartDialog::SelectStartDialog(LayersBase *base,AutoGeneratorButtonForm *p ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,Parent(p)
    ,ui(new Ui::SelectStartDialog)
{
    ui->setupUi(this);
    Selected=NULL;

    ::SetColumnWidthInTable(ui->tableWidgetStoredList ,0, 20);
    ::SetColumnWidthInTable(ui->tableWidgetStoredList ,1, 20);
    ::SetColumnWidthInTable(ui->tableWidgetStoredList ,2, 25);
    ::SetColumnWidthInTable(ui->tableWidgetStoredList ,3, 25);

    ::SetColumnWidthInTable(ui->tableWidget,0,95);

    ShowStoredGrid();
}

SelectStartDialog::~SelectStartDialog()
{
    delete ui;
}

void    SelectStartDialog::ShowStoredGrid(void)
{
    int N=Parent->ListContainer.GetCount();
    ui->tableWidgetStoredList->setRowCount(N);
    int Row=0;
    for(ListAutoGenerator *s=Parent->ListContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidgetStoredList, 0, Row, s->Code       );
        ::SetDataToTable(ui->tableWidgetStoredList, 1, Row, s->Name       );
        ::SetDataToTable(ui->tableWidgetStoredList, 2, Row, s->DXFFileName);
		::SetDataToTable(ui->tableWidgetStoredList, 3, Row, s->PDFFileName);
	}
}

void SelectStartDialog::on_tableWidgetStoredList_itemSelectionChanged()
{
    static  bool    ReEntrant=false;

    if(ReEntrant==true)
        return;
    ReEntrant=true;
    int Row=ui->tableWidgetStoredList->currentRow();
    ListAutoGenerator *s=Parent->ListContainer.GetItem(Row);
    if(s!=NULL){
        ui->lineEditCode    ->setText(s->Code);

        ::SetDataToTable(ui->tableWidget, 0, 0, s->Code       );
        ::SetDataToTable(ui->tableWidget, 0, 1, s->Name       );
        ::SetDataToTable(ui->tableWidget, 0, 2, s->DXFFileName    );
        ::SetDataToTable(ui->tableWidget, 0, 3, s->PDFFileName    );
        ::SetDataToTable(ui->tableWidget, 0, 4, s->AlignFileName  );
        ::SetDataToTable(ui->tableWidget, 0, 5, s->SpecialFileName);
    }
    ReEntrant=false;
}


void SelectStartDialog::on_tableWidgetStoredList_clicked(const QModelIndex &index)
{
    on_tableWidgetStoredList_itemSelectionChanged();
}


void SelectStartDialog::on_lineEditCode_textChanged(const QString &arg1)
{
    QString str=ui->lineEditCode->text();
    int Row=0;
    for(ListAutoGenerator *s=Parent->ListContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        if(s->Code==str){
            SetCurrentRow(ui->tableWidgetStoredList,Row);
            on_tableWidgetStoredList_itemSelectionChanged();
        }
    }
}


void SelectStartDialog::on_pushButtonGenerate_clicked()
{
    QString str=ui->lineEditCode->text();
    for(ListAutoGenerator *s=Parent->ListContainer.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->Code==str){
            Selected=s;
            break;
        }
    }
    done(1);
}


void SelectStartDialog::on_tableWidgetStoredList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonGenerate_clicked();
}

