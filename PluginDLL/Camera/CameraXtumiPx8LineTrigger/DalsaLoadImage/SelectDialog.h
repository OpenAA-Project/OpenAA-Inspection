/*
 * Copyright (C) 2019
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

#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QModelIndex>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectDialog();

private slots:
    void on_listWidget_currentRowChanged(int currentRow);
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButtonSelect_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonSaveAll_clicked();

    void on_pushButtonLoadAppend_clicked();

    void on_pushButtonClear_clicked();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H