/*
 * Copyright (C) 2017
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

#ifndef EDITCONNECTIONDIALOG_H
#define EDITCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class EditConnectionDialog;
}

class EditConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditConnectionDialog(QWidget *parent = 0);
    ~EditConnectionDialog();

private slots:
    void on_pushButtonSet_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::EditConnectionDialog *ui;
};

#endif // EDITCONNECTIONDIALOG_H