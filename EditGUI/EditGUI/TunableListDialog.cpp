#include "TunableListDialog.h"
#include "ui_TunableListDialog.h"
#include "swap.h"

TunableListDialog::TunableListDialog(QStringList &mList,QWidget *parent) :
    QDialog(parent),MList(mList),
    ui(new Ui::TunableListDialog)
{
    ui->setupUi(this);
    ShowList();
}

TunableListDialog::~TunableListDialog()
{
    delete ui;
}

void TunableListDialog::ShowList(void)
{
    ui->listWidgetTunable->clear();
    for(int i=0;i<MList.count();i++){
        ui->listWidgetTunable->addItem(MList.value(i));
    }
}

void TunableListDialog::on_pushButtonUp_clicked()
{
    int	r=ui->listWidgetTunable->currentRow();
    if(r>0){
        Swap(MList,r,r-1);
        ShowList();
        ui->listWidgetTunable->setCurrentRow(r-1);
    }
}

void TunableListDialog::on_pushButtonDown_clicked()
{
    int	r=ui->listWidgetTunable->currentRow();
    if(r<MList.count()-1){
        Swap(MList,r,r+1);
        ShowList();
        ui->listWidgetTunable->setCurrentRow(r+1);
    }
}

void TunableListDialog::on_pushButtonClose_clicked()
{
    close();
}
