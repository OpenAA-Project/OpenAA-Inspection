#include "ShowThumbnailResource.h"
#include "ChooseNextDialog.h"
#include "ui_ChooseNextDialog.h"
#include "XGeneralFunc.h"

ChooseNextDialog::ChooseNextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseNextDialog)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
}

ChooseNextDialog::~ChooseNextDialog()
{
    delete ui;
}

void ChooseNextDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void ChooseNextDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
