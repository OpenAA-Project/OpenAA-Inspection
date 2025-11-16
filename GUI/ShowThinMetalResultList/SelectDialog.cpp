#include "SelectDialog.h"
#include "ui_SelectDialog.h"

SelectDialog::SelectDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::on_toolButtonDelete_clicked()
{
	done(1);
}

void SelectDialog::on_toolButtonLoad_clicked()
{
	done(2);
}

void SelectDialog::on_toolButtonCancel_clicked()
{
	done(-1);
}
