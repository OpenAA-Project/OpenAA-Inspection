#include "EditEachPageLocalDialog.h"
#include "ui_EditEachPageLocalDialog.h"

EditEachPageLocalDialog::EditEachPageLocalDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditEachPageLocalDialog)
{
    ui->setupUi(this);

    OldPage=-1;

    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPageList->addItem(QString(/**/"Page ")+QString::number(page));
    }

    if(GetParamGlobal()->CountOfPageLocal!=GetPageNumb()){
        GetParamGlobal()->ReallocPageLocal(GetPageNumb());
    }


    WTab = new WEditParameterTab(&GetParamGlobal()->PageLocalData[0] ,-1,ui->frameEachPageLocal);
    WTab->ShowToWindow();

    if(GetPageNumb()>0){
        ui->listWidgetPageList->setCurrentRow(0);
    }
    OldPage=0;
}

EditEachPageLocalDialog::~EditEachPageLocalDialog()
{
    delete ui;
}

void EditEachPageLocalDialog::on_ButtonOK_clicked()
{
    if(OldPage>=0){
        WTab->LoadFromWindow();
    }
    done(true);
}


void EditEachPageLocalDialog::on_listWidgetPageList_itemSelectionChanged()
{
    if(OldPage>=0){
        WTab->LoadFromWindow();
    }
    int page=ui->listWidgetPageList->currentRow();
    if(page>=0){
        WTab->Set(&GetParamGlobal()->PageLocalData[page],-1);
        OldPage=page;
    }
}


void EditEachPageLocalDialog::on_listWidgetPageList_itemClicked(QListWidgetItem *item)
{
    on_listWidgetPageList_itemSelectionChanged();
}

