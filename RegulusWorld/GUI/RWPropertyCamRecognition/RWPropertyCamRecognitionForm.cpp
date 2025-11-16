#include "RWPropertyCamRecognitionForm.h"
#include "ui_RWPropertyCamRecognitionForm.h"

RWPropertyCamRecognitionForm::RWPropertyCamRecognitionForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::RWPropertyCamRecognitionForm)
{
    ui->setupUi(this);
}

RWPropertyCamRecognitionForm::~RWPropertyCamRecognitionForm()
{
    delete ui;
}
