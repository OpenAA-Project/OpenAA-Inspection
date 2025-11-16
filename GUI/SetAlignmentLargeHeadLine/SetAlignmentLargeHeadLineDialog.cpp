#include "SetAlignmentLargeHeadLineDialog.h"
#include "ui_SetAlignmentLargeHeadLineDialog.h"

SetAlignmentLargeHeadLineDialog::SetAlignmentLargeHeadLineDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SetAlignmentLargeHeadLineDialog)
{
    ui->setupUi(this);
}

SetAlignmentLargeHeadLineDialog::~SetAlignmentLargeHeadLineDialog()
{
    delete ui;
}

void	SetAlignmentLargeHeadLineDialog::SetInitial(void)
{
    ui->checkBoxUseHeadAlignment    ->setChecked(UseHeadAlignment   );
    ui->spinBoxSkipHeadAlignmentX   ->setValue(SkipHeadAlignmentX   );
    ui->spinBoxMaxHeadAlignmentX    ->setValue(MaxHeadAlignmentX    );
    ui->spinBoxSkipHeadAlignmentY   ->setValue(SkipHeadAlignmentY   );
    ui->spinBoxMaxHeadAlignmentY    ->setValue(MaxHeadAlignmentY    );
    ui->spinBoxHeadAlignmentDifColor->setValue(HeadAlignmentDifColor);
    ui->spinBoxHeadAlignmentMinSize ->setValue(HeadAlignmentMinSize );
    ui->spinBoxHeadAlignmentStep    ->setValue(HeadAlignmentStep    );
}
void SetAlignmentLargeHeadLineDialog::on_pushButtonOK_clicked()
{
    UseHeadAlignment        =ui->checkBoxUseHeadAlignment    ->isChecked();
    SkipHeadAlignmentX      =ui->spinBoxSkipHeadAlignmentX   ->value();
    MaxHeadAlignmentX       =ui->spinBoxMaxHeadAlignmentX    ->value();
    SkipHeadAlignmentY      =ui->spinBoxSkipHeadAlignmentY   ->value();
    MaxHeadAlignmentY       =ui->spinBoxMaxHeadAlignmentY    ->value();
    HeadAlignmentDifColor   =ui->spinBoxHeadAlignmentDifColor->value();
    HeadAlignmentMinSize    =ui->spinBoxHeadAlignmentMinSize ->value();
    HeadAlignmentStep       =ui->spinBoxHeadAlignmentStep    ->value();
    done(true);
}


void SetAlignmentLargeHeadLineDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

