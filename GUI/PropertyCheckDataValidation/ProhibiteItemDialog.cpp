#include "ProhibiteItemDialog.h"
#include "ui_ProhibiteItemDialog.h"
#include "SelectLibForValidationForm.h"
#include "XCheckDataValidation.h"

ProhibiteItemDialog::ProhibiteItemDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ProhibiteItemDialog)
{
    ui->setupUi(this);


    SelectedLibType =-1;
    SelectedLibID   =-1;

    SelectLibPanel=new SelectLibForValidationForm(Base);
    SelectLibPanel->setParent(ui->frame);
    SelectLibPanel->move(0,0);
    connect(SelectLibPanel,SIGNAL(SignalSelectedLib(int ,int)),this,SLOT(SlotSelectedLib(int,int)));

    ui->pushButtonModify    ->setVisible(false);
    ui->pushButtonDelete    ->setVisible(false);
}

ProhibiteItemDialog::~ProhibiteItemDialog()
{
    delete ui;
}

void    ProhibiteItemDialog::SetCurrentItem(const CheckDataValidationProhibiteItemThreshold *RThr)
{
    ui->pushButtonModify    ->setVisible(true);
    ui->pushButtonDelete    ->setVisible(true);

    SelectedLibType =RThr->LibType;
    SelectedLibID   =RThr->LibID;

    SelectLibPanel->Initial(SelectedLibType, SelectedLibID);
    SlotSelectedLib(SelectedLibType,SelectedLibID);
}

void    ProhibiteItemDialog::GetCurrentItem(CheckDataValidationProhibiteItemThreshold *WThr)
{
    WThr->LibType=SelectedLibType;
    WThr->LibID  =SelectedLibID;
}

void    ProhibiteItemDialog::SlotSelectedLib(int LibType,int LibID)
{
    ui->spinBoxLibID    ->setValue(LibID);
    QString LibName=GetLayersBase()->GetLibraryName(LibType,LibID);
    ui->lineEditLibName ->setText(LibName);
    SelectedLibType =LibType;
    SelectedLibID   =LibID;
}

void ProhibiteItemDialog::on_pushButtonCreateNew_clicked()
{
    done(1);
}


void ProhibiteItemDialog::on_pushButtonModify_clicked()
{
    done(2);
}


void ProhibiteItemDialog::on_pushButtonDelete_clicked()
{
    done(3);
}


void ProhibiteItemDialog::on_pushButtonClose_clicked()
{
    done(-1);
}

