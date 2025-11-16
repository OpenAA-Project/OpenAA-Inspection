#include "NoComponentDialog.h"
#include "ui_NoComponentDialog.h"
#include "XGeneralFunc.h"

NoComponentDialog::NoComponentDialog(ComponentListContainer &NoComponentList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoComponentDialog)
{
    ui->setupUi(this);

    QStringList StrList;
    NoComponentList.GetPropertyStringList(StrList);
    ui->listWidget->clear();
    ui->listWidget->addItems(StrList);
}

NoComponentDialog::~NoComponentDialog()
{
    delete ui;
}

void NoComponentDialog::on_pushButtonOK_clicked()
{
    done(true);
}
