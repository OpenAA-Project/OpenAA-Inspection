#include "XTypeDef.h"
#include "EditOutlineOffsetAddDialog.h"
#include "ui_EditOutlineOffsetAddDialog.h"

EditOutlineOffsetAddDialog::EditOutlineOffsetAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditOutlineOffsetAddDialog)
{
    ui->setupUi(this);
}

EditOutlineOffsetAddDialog::~EditOutlineOffsetAddDialog()
{
    delete ui;
}

void EditOutlineOffsetAddDialog::on_pushButtonOK_clicked()
{
	AddedOffset=ui->spinBox->value();
	done(true);
}

void EditOutlineOffsetAddDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
