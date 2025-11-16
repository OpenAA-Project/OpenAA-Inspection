#include "SignalProveForm.h"
#include "ui_SignalProveForm.h"
#include "ControllerAccessor.h"

SignalProveForm::SignalProveForm(ControllerAccessor *p ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignalProveForm)
	,Parent(p)
{
    ui->setupUi(this);
}

SignalProveForm::~SignalProveForm()
{
    delete ui;
}
