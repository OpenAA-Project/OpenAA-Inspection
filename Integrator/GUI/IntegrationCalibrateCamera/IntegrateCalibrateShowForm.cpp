#include "IntegrateCalibrateShowForm.h"
#include "ui_IntegrateCalibrateShowForm.h"
#include "XCriticalFunc.h"
#include "IntegrationCalibrateCamera.h"

IntegrateCalibrateShowForm::IntegrateCalibrateShowForm(LayersBase *Base 
                                                        ,IntegrationCalibrateCamera *p
                                                        ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::IntegrateCalibrateShowForm)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);
    StartTime   =::GetComputerMiliSec();

    TM.setSingleShot(false);
    TM.setInterval(300);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}

IntegrateCalibrateShowForm::~IntegrateCalibrateShowForm()
{
    delete ui;
}

void    IntegrateCalibrateShowForm::Start(void)
{
    ui->progressBar->setValue(0);
    StartTime   =::GetComputerMiliSec();
    TM.start();
}
void    IntegrateCalibrateShowForm::SlotTimeOut(void)
{
    DWORD   D=::GetComputerMiliSec();
    DWORD   s=(D-StartTime)/1000;
    if(ui->progressBar->maximum()<s){
        ui->progressBar->setValue(ui->progressBar->maximum());
    }
    else{
        ui->progressBar->setValue(s);
    }
    if(ui->progressBar->maximum()<=ui->progressBar->value()){
        ExecuteCalibrate();
        TM.stop();
        close();
    }
}

void IntegrateCalibrateShowForm::on_pushButtonStop_clicked()
{
    TM.stop();
    close();
}

void IntegrateCalibrateShowForm::ExecuteCalibrate(void)
{
    Parent->SlotClicked();
}
