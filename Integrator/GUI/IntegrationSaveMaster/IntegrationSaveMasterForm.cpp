#include "IntegrationSaveMasterResource.h"
#include "IntegrationSaveMasterForm.h"
#include "ui_IntegrationSaveMasterForm.h"

IntegrationSaveMasterForm::IntegrationSaveMasterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegrationSaveMasterForm)
{
    ui->setupUi(this);
}

IntegrationSaveMasterForm::~IntegrationSaveMasterForm()
{
    delete ui;
}
