#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include <QMessageBox>

EditLibraryDialog::EditLibraryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}

void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &index)
{

}

void EditLibraryDialog::on_ButtonLibNew_clicked()
{

}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
{

}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
{

}

void EditLibraryDialog::on_ButtonLibSave_clicked()
{

}

void EditLibraryDialog::on_pushButton_clicked()
{

}
