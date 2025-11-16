#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "RegistColorLibForm.h"
#include "ui_RegistColorLibForm.h"
#include "XDataInLayer.h"

RegistColorLibForm::RegistColorLibForm(RGBStock *data ,LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,RegistPanel(Base)
    ,ui(new Ui::RegistColorLibForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);

    RGBPanel.setParent(ui->frameRGBPanel);
    RGBPanel.Fit(ui->frameRGBPanel);
    RGBPanel.Cube=*data;
    RGBPanel.InitializedDoneCube();

    ColorPanel.setParent(ui->frameColorPanel);
    ColorPanel.Fit(ui->frameColorPanel);
    ColorPanel.Set(*data);

    RegistPanel.setParent(ui->frameRegistPanel);
    RegistPanel.move(0,0);

    connect(&RegistPanel,SIGNAL(SignalSelectCData()),this,SLOT(SlotSelectCData()));
    connect(&RegistPanel,SIGNAL(SignalBeforeSave()) ,this,SLOT(SlotBeforeSave()));

    InstallOperationLog(this);
}

RegistColorLibForm::~RegistColorLibForm()
{
    delete ui;
}
void	RegistColorLibForm::SlotSelectCData()
{
    if(RegistPanel.CData.GetDataType()==ColorSampleList::TypeRGBStock){
        RGBStock	*g=RegistPanel.CData.GetRGBStock();
        if(g!=NULL){
            ui->stackedWidget->setCurrentIndex(0);
            RGBPanel.Cube=*g;
            RGBPanel.InitializedDoneCube();
            RGBPanel.Repaint();
        }
    }
    else if(RegistPanel.CData.GetDataType()==ColorSampleList::TypeColorLogic){
        ColorLogic	*c=RegistPanel.CData.GetColorLogic();
        if(c!=NULL){
            ui->stackedWidget->setCurrentIndex(1);
            ColorPanel.Cube=*c;
            ColorPanel.InitializedDoneCube();
            ColorPanel.Repaint();
        }
    }
}
void	RegistColorLibForm::SlotBeforeSave()
{
    if(ui->stackedWidget->currentIndex()==0){
        RegistPanel.CData.Set(RGBPanel.Cube,RGBPanel.Ext);
    }
    else if(ui->stackedWidget->currentIndex()==1){
        RegistPanel.CData.Set(ColorPanel.Cube);
    }
}
void RegistColorLibForm::on_pushButtonClose_clicked()
{
    emit	SignalClose();
}
