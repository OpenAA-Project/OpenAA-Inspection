#include "ButtonFeedbackResource.h"
#include "ButtonFeedbackForm.h"
#include "ui_ButtonFeedbackForm.h"

ButtonFeedbackForm::ButtonFeedbackForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ButtonFeedbackForm)
{
    ui->setupUi(this);
}

ButtonFeedbackForm::~ButtonFeedbackForm()
{
    delete ui;
}
