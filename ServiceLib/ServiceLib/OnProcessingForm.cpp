/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\OnProcessingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "OnProcessingForm.h"
#include "ui_OnProcessingForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"


OnProcessingForm::ProgressList::ProgressList(QWidget *parent)
{
    PBar	=new QProgressBar(parent);
    Label	=new QLabel(parent);

}
OnProcessingForm::ProgressList::~ProgressList(void)
{
    delete	PBar;
    delete	Label;
    PBar=NULL;
    Label=NULL;
}

void	OnProcessingForm::ProgressList::SetPage(int page ,int YPoint)
{
    Label->setObjectName(QString(/**/"LabelPage")+QString::number(page));
    Label->move(10,YPoint);
    Label->resize(62,15);
    Label->setText(LangLibSolver.GetString(OnProcessingForm_LS,LID_39)/*"Page "*/+QString::number(page));
    PBar->move(80,YPoint);
    PBar->resize(241,23);

}
void	OnProcessingForm::ProgressList::SetMaximum(int d)
{
    PBar->setMaximum(d);
}
void	OnProcessingForm::ProgressList::StepIt(void)
{
    int	d=PBar->value();
    d++;
    if(d>=PBar->maximum())
        d=PBar->maximum();
    PBar->setValue(d);
}
void	OnProcessingForm::ProgressList::SetValue(int d)
{
    if(d>=PBar->maximum())
        d=PBar->maximum();
    PBar->setValue(d);
}

int		OnProcessingForm::ProgressList::maximum(void)
{
    return PBar->maximum();
}
int		OnProcessingForm::ProgressList::value(void)
{
    return PBar->value();
}
void	OnProcessingForm::ProgressList::show(void)
{
    PBar->show();
    Label->show();
}

//============================================================================================

OnProcessingForm::OnProcessingForm(LayersBase *lbase ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::OnProcessingForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    LanguageCode=-1;
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    ModeShowing=true;

    delete	ui->label;
    ui->label=NULL;
    delete	ui->progressBarProcessing;
    ui->progressBarProcessing=NULL;

    AllocatedPageNumb	=0;
    ProgressListPointer	=NULL;
    CheckPageNumb();
    SetWidgetCenter(this);

    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotCheck()));
    TM.setSingleShot(false);
    TM.setInterval(2000);
    TM.start();
    update();
}

OnProcessingForm::~OnProcessingForm()
{
    delete ui;

    for(int page=0;page<AllocatedPageNumb;page++){
        delete	ProgressListPointer	[page];
    }
    delete	[]ProgressListPointer;
    ProgressListPointer=NULL;
}

void OnProcessingForm::on_pushButtonCancel_clicked()
{

}

void OnProcessingForm::showEvent( QShowEvent * event )
{
    QWidget::showEvent(event );
    if(LanguageCode<0){
        LanguageCode=GetLayersBase()->GetLanguageCode();
        LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
        LangLibSolver.SetUI(this);
    }
    TM.setSingleShot(false);
    TM.setInterval(2000);
    TM.start();
}

void OnProcessingForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void	OnProcessingForm::SetCancelMode(bool CancelMode)
{
    ui->pushButtonCancel->setVisible(CancelMode);
}
void	OnProcessingForm::SetMessage(QString message)
{
    if(message==/**/""){
        ui->labelMessage->setText(LangLibSolver.GetString(OnProcessingForm_LS,LID_13)/*"Going on ..."*/);
    }
    else{
        ui->labelMessage->setText(message);
    }
}

void	OnProcessingForm::Set(int page ,int currentValue ,int maxValue)
{
    CheckPageNumb();
    if(maxValue<0){
        if(currentValue==0){
            ProgressListPointer[page]->SetMaximum(100);
        }
        else if(ui->progressBarProcessing->maximum()<=currentValue){
            ProgressListPointer[page]->SetMaximum(currentValue+1);
        }
    }
    else{
        ProgressListPointer[page]->SetMaximum(maxValue);
    }
    ProgressListPointer[page]->SetValue(currentValue);
    Show();
}
void	OnProcessingForm::SetMax(int maxValue)
{
    CheckPageNumb();
    for(int page=0;page<AllocatedPageNumb;page++){
        if(maxValue<0){
            ProgressListPointer[page]->SetMaximum(0);
        }
        else{
            ProgressListPointer[page]->SetMaximum(maxValue);
        }
    }
}
void	OnProcessingForm::SetValue(int page ,int currentValue)
{
    ProgressListPointer[page]->SetValue(currentValue);
    Show();
}
void	OnProcessingForm::AddMax(int localpage ,int maxValue)
{
    CheckPageNumb();
    if(localpage>=0){
        ProgressListPointer[localpage]->SetMaximum(ProgressListPointer[localpage]->maximum()+maxValue);
    }
    else{
        for(int i=0;i<AllocatedPageNumb;i++){
            ProgressListPointer[i]->SetMaximum(ProgressListPointer[i]->maximum()+maxValue);
        }
    }
    Show();
}

void	OnProcessingForm::Step(int localpage )
{
    CheckPageNumb();
    if(localpage>=0 && localpage<AllocatedPageNumb){
        ProgressListPointer[localpage]->StepIt();
    }
    else{
        for(int page=0;page<AllocatedPageNumb;page++){
            ProgressListPointer[page]->StepIt();
        }
    }
    Show();
}

void	OnProcessingForm::CheckPageNumb(void)
{
    if(AllocatedPageNumb!=GetPageNumb()){
        if(ProgressListPointer!=NULL){
            for(int page=0;page<AllocatedPageNumb;page++){
                delete	ProgressListPointer	[page];
            }
            delete	[]ProgressListPointer;
        }

        AllocatedPageNumb	=GetPageNumb();
        int	Y=40;
        ProgressListPointer	=new ProgressList*[AllocatedPageNumb];
        for(int page=0;page<AllocatedPageNumb;page++){
            ProgressListPointer	[page]=new ProgressList(this);
            ProgressListPointer	[page]->SetPage(page,Y);
            Y+=28;
        }
        resize(338,133+(AllocatedPageNumb-1)*28);
        ui->frameBottom->move(0,133+(AllocatedPageNumb-1)*28-ui->frameBottom->height());
        ui->frameBottom->show();
    }
}


void OnProcessingForm::on_pushButtonClose_clicked()
{
    ModeShowing=false;
    hide();
}


void	OnProcessingForm::Show(void)
{
    ModeShowing=true;
    for(int page=0;page<AllocatedPageNumb;page++){
        ProgressListPointer	[page]->show();
    }
    show();
}

void	OnProcessingForm::Hide(void)
{
    ModeShowing=false;
    hide();
}

void	OnProcessingForm::DelayedHide(int sec)
{
    ModeShowing=false;
    TM.setSingleShot(false);
    TM.setInterval(sec*1000);
    TM.start();
}

void	OnProcessingForm::SlotCheck(void)
{
    if(ModeShowing==false){
        Hide();
    }
}
