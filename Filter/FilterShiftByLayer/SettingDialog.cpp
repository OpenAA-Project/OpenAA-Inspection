#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XDataInLayer.h"

SettingDialog::SettingDialog(LayersBase *base ,ShiftXYInfo &_ShiftInfo,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    ShiftInfo=_ShiftInfo;

    for(int phase=0;phase<GetPhaseNumb();phase++){
        ShiftXYInPhaseContainer *s=ShiftInfo.Find(phase);
        if(s==NULL){
            s=new ShiftXYInPhaseContainer();
            s->Phase=phase;
            ShiftInfo.AppendList(s);
        }
        else{
            s->Phase=phase;
        }
        for(int page=0;page<GetPageNumb();page++){
            ShiftXYInPageContainer  *P=s->Find(page);
            if(P==NULL){
                P=new ShiftXYInPageContainer();
                P->Page=page;
                s->AppendList(P);
            }
            else{
                P->Page=page;
            }
            for(int layer=0;layer<GetLayerNumb(page);layer++){
                ShiftXYList *L=P->Find(layer);
                if(L==NULL){
                    L=new ShiftXYList();
                    L->Layer=layer;
                    P->AppendList(L);
                }
                else{
                    L->Layer=layer;
                }
            }
        }
    }
    for(int phase=0;phase<GetPhaseNumb();phase++){
        ui->listWidgetPhase->addItem(QString(/**/"Phase ")+QString::number(phase));
    }
    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPage->addItem(QString(/**/"Page ")+QString::number(page));
    }
    int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
    for(int layer=0;layer<LayerNumb;layer++){
        ui->listWidgetLayer->addItem(QString(/**/"Layer ")+QString::number(layer));
    }

    LastPhase   =0;
    LastPage    =0;
    LastLayer   =0;
    SetToWindow(LastPhase,LastPage,LastLayer);
    
    ui->listWidgetPhase ->setCurrentRow(0);
    ui->listWidgetPage  ->setCurrentRow(0);
    ui->listWidgetLayer ->setCurrentRow(0);

    //on_listWidgetPhase_itemSelectionChanged();
    //on_listWidgetPage_itemSelectionChanged();
    //on_listWidgetLayer_itemSelectionChanged();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void    SettingDialog::GetFromWindow   (int phase ,int page ,int layer)
{
    ShiftXYInPhaseContainer *s=ShiftInfo.Find(phase);
    if(s!=NULL){
        ShiftXYInPageContainer  *P=s->Find(page);
        if(P!=NULL){
            ShiftXYList *L=P->Find(layer);
            if(L!=NULL){
                L->ShiftX=ui->spinBoxShiftX->value();
                L->ShiftY=ui->spinBoxShiftY->value();
            }
        }
    }
}
void    SettingDialog::SetToWindow     (int phase ,int page ,int layer)
{
    ShiftXYInPhaseContainer *s=ShiftInfo.Find(phase);
    if(s!=NULL){
        ShiftXYInPageContainer  *P=s->Find(page);
        if(P!=NULL){
            ShiftXYList *L=P->Find(layer);
            if(L!=NULL){
                ui->spinBoxShiftX->setValue(L->ShiftX);
                ui->spinBoxShiftY->setValue(L->ShiftY);
            }
        }
    }
    LastPhase   =phase;
    LastPage    =page;
    LastLayer   =layer;
}
void SettingDialog::on_listWidgetPhase_itemSelectionChanged()
{
    GetFromWindow(LastPhase,LastPage ,LastLayer);
    SetToWindow( ui->listWidgetPhase->currentRow()
                ,ui->listWidgetPage ->currentRow()
                ,ui->listWidgetLayer->currentRow());
}

void SettingDialog::on_listWidgetPhase_itemClicked(QListWidgetItem *item)
{
    on_listWidgetPhase_itemSelectionChanged();
}


void SettingDialog::on_listWidgetPage_itemSelectionChanged()
{
    GetFromWindow(LastPhase,LastPage ,LastLayer);
    SetToWindow( ui->listWidgetPhase->currentRow()
                ,ui->listWidgetPage ->currentRow()
                ,ui->listWidgetLayer->currentRow());
}


void SettingDialog::on_listWidgetPage_itemClicked(QListWidgetItem *item)
{
    on_listWidgetPage_itemSelectionChanged();
}


void SettingDialog::on_listWidgetLayer_itemSelectionChanged()
{
    GetFromWindow(LastPhase,LastPage ,LastLayer);
    SetToWindow( ui->listWidgetPhase->currentRow()
                ,ui->listWidgetPage ->currentRow()
                ,ui->listWidgetLayer->currentRow());
}


void SettingDialog::on_listWidgetLayer_itemClicked(QListWidgetItem *item)
{
    on_listWidgetLayer_itemSelectionChanged();
}


void SettingDialog::on_pushButtonOK_clicked()
{
    GetFromWindow(LastPhase,LastPage ,LastLayer);
    done(true);
}


void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

