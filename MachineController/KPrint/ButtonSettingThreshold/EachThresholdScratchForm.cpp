#include "ButtonSettingThresholdResource.h"
#include "EachThresholdScratchForm.h"
#include "ui_EachThresholdScratchForm.h"

EachThresholdScratchForm::EachThresholdScratchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EachThresholdScratchForm)
{
    ui->setupUi(this);
}

EachThresholdScratchForm::~EachThresholdScratchForm()
{
    delete ui;
}
