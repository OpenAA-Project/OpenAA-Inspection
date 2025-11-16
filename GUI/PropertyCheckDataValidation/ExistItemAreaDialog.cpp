#include "ExistItemAreaDialog.h"
#include "ui_ExistItemAreaDialog.h"
#include "SelectLibForValidationForm.h"
#include "XCheckDataValidation.h"

ExistItemAreaDialog::ExistItemAreaDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ExistItemAreaDialog)
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

ExistItemAreaDialog::~ExistItemAreaDialog()
{
    delete ui;
}

void    ExistItemAreaDialog::SetCurrentItem(const CheckDataValidationExistItemAreaThreshold *RThr)
{
    ui->pushButtonModify    ->setVisible(true);
    ui->pushButtonDelete    ->setVisible(true);

    SelectedLibType =RThr->LibType;
    SelectedLibID   =RThr->LibID;
    
    SelectLibPanel->Initial(SelectedLibType, SelectedLibID);

    ui->doubleSpinBoxFilledPercentageInMask ->setValue(RThr->FilledPercentageInMask);
    ui->checkBoxCheckExistence              ->setChecked(RThr->CheckExistence);
    SlotSelectedLib(SelectedLibType,SelectedLibID);
}

void    ExistItemAreaDialog::GetCurrentItem(CheckDataValidationExistItemAreaThreshold *WThr)
{
    WThr->LibType=SelectedLibType;
    WThr->LibID  =SelectedLibID;
    WThr->FilledPercentageInMask    =ui->doubleSpinBoxFilledPercentageInMask ->value();
    WThr->CheckExistence            =ui->checkBoxCheckExistence ->isChecked();
}

void    ExistItemAreaDialog::SlotSelectedLib(int LibType,int LibID)
{
    ui->spinBoxLibID    ->setValue(LibID);
    QString LibName=GetLayersBase()->GetLibraryName(LibType,LibID);
    ui->lineEditLibName ->setText(LibName);

    SelectedLibType =LibType;
    SelectedLibID   =LibID;
}

void ExistItemAreaDialog::on_pushButtonCreateNew_clicked()
{
    FilledPercentageInMask  =ui->doubleSpinBoxFilledPercentageInMask->value();
    CheckExistence          =ui->checkBoxCheckExistence             ->isChecked();
    done(1);
}


void ExistItemAreaDialog::on_pushButtonModify_clicked()
{
    FilledPercentageInMask  =ui->doubleSpinBoxFilledPercentageInMask->value();
    CheckExistence          =ui->checkBoxCheckExistence             ->isChecked();
    done(2);
}


void ExistItemAreaDialog::on_pushButtonDelete_clicked()
{
    done(3);
}


void ExistItemAreaDialog::on_pushButtonClose_clicked()
{
    done(-1);
}

