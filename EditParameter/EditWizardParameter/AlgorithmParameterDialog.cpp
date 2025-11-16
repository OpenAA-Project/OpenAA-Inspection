#include "AlgorithmParameterDialog.h"
#include "ui_AlgorithmParameterDialog.h"

AlgorithmParameterDialog::AlgorithmParameterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlgorithmParameterDialog)
{
    ui->setupUi(this);
}

AlgorithmParameterDialog::~AlgorithmParameterDialog()
{
    delete ui;
}
