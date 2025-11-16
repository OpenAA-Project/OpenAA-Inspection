#include "EditItemDialog.h"
#include "ui_EditItemDialog.h"
#include "XColorCorrector.h"

EditItemDialog::EditItemDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}

    
void    EditItemDialog::SetCurrentItem(const ColorShiftVThreshold *RThr)
{
    ui->spinBoxSearchXDot->setValue(RThr->SearchXDot);
    ui->spinBoxSearchYDot->setValue(RThr->SearchYDot);

    ui->checkBoxLayer0  ->setChecked((RThr->RegularLayer==0)?true:false);
    ui->checkBoxLayer1  ->setChecked((RThr->RegularLayer==1)?true:false);
    ui->checkBoxLayer2  ->setChecked((RThr->RegularLayer==2)?true:false);
}

void    EditItemDialog::GetCurrentItem(ColorShiftVThreshold *WThr)
{
    WThr->SearchXDot    =ui->spinBoxSearchXDot->value();
    WThr->SearchYDot    =ui->spinBoxSearchYDot->value();

    if(ui->checkBoxLayer0->isChecked()==true)
        WThr->RegularLayer=0;
    else
    if(ui->checkBoxLayer1->isChecked()==true)
        WThr->RegularLayer=1;
    else
    if(ui->checkBoxLayer2->isChecked()==true)
        WThr->RegularLayer=2;
}


