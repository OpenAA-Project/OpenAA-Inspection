/*
 * Copyright (C) 2016
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

#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>

namespace Ui {
class EditLibraryDialog;
}

class EditLibraryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLibraryDialog(QWidget *parent = 0);
    ~EditLibraryDialog();

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);

    void on_ButtonLibNew_clicked();

    void on_ButtonLibDelete_clicked();

    void on_ButtonLibSaveNew_clicked();

    void on_ButtonLibSave_clicked();

    void on_pushButton_clicked();

private:
    Ui::EditLibraryDialog *ui;
};

#endif // EDITLIBRARYDIALOG_H