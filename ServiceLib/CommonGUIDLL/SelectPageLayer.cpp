#include "CommonGUIDLLResource.h"
#include "SelectPageLayer.h"
#include "ui_SelectPageLayer.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"

SelectPageLayer::SelectPageLayer(LayersBase *pbase ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(pbase)
    ,ui(new Ui::SelectPageLayer)
	
{
    ui->setupUi(this);
    LangCGSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangCGSolver.SetUI(this);

    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPage->addItem(LangCGSolver.GetString(SelectPageLayer_LS,LID_4)/*"Page "*/+QString::number(page));
    }
    //if(GetPageNumb()==1){
    //    ui->listWidgetPage->setCurrentRow(0);
    //}
    //for(int layer=0;layer<GetLayerNumb(0);layer++){
    //    ui->listWidgetLayer->addItem(GetParamGlobal()->GetLayerName(layer));
    //}
    //if(GetLayerNumb(0)==1){
    //    ui->listWidgetLayer->setCurrentRow(0);
    //}
    //
    //if(GetPageNumb()!=1 || GetLayerNumb()!=1){
    //    ui->pushButtonSelect->setEnabled(false);
    //}
    InstallOperationLog(this);
}

SelectPageLayer::~SelectPageLayer()
{
    delete ui;
}

void SelectPageLayer::ShowLayerList(int page)
{
    ui->listWidgetLayer->clear();
    for(int layer=0;layer<GetLayerNumb(page);layer++){
        ui->listWidgetLayer->addItem(GetParamGlobal()->GetLayerName(layer));
    }
    if(GetLayerNumb(page)==1){
        ui->listWidgetLayer->setCurrentRow(0);
    }

    if(GetPageNumb()!=1 || GetLayerNumb(page)!=1){
        ui->pushButtonSelect->setEnabled(false);
    }
    else{
        ui->pushButtonSelect->setEnabled(true);
    }
}

void SelectPageLayer::on_listWidgetPage_clicked(const QModelIndex &index)
{
    int page=ui->listWidgetPage->currentRow();
    if(page>=0 && ui->listWidgetLayer->currentRow()>=0){
        ui->pushButtonSelect->setEnabled(true);
    }
    if(page>=0){
        ShowLayerList(page);
    }
}

void SelectPageLayer::on_listWidgetPage_doubleClicked(const QModelIndex &index)
{
    int page=ui->listWidgetPage->currentRow();
    if(page>=0 && ui->listWidgetLayer->currentRow()>=0){
        ui->pushButtonSelect->setEnabled(true);
        on_pushButtonSelect_clicked();
    }
}

void SelectPageLayer::on_listWidgetLayer_clicked(const QModelIndex &index)
{
    int page=ui->listWidgetPage->currentRow();
    if(page>=0 && ui->listWidgetLayer->currentRow()>=0){
        ui->pushButtonSelect->setEnabled(true);
    }
}

void SelectPageLayer::on_listWidgetLayer_doubleClicked(const QModelIndex &index)
{
    int page=ui->listWidgetPage->currentRow();
    if(page>=0 && ui->listWidgetLayer->currentRow()>=0){
        ui->pushButtonSelect->setEnabled(true);
        on_pushButtonSelect_clicked();
    }
}

void SelectPageLayer::on_pushButtonSelect_clicked()
{
    Page	=ui->listWidgetPage->currentRow();
    Layer	=ui->listWidgetLayer->currentRow();
    done(true);
}

void SelectPageLayer::on_pushButtonCancel_clicked()
{
    done(false);
}
