/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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