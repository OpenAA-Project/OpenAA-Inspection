/*
 * Copyright (C) 2024
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

#ifndef SELECTLIBRARYINLISTDIALOG_H
#define SELECTLIBRARYINLISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectLibraryInListDialog;
}

class SelectLibraryInListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int     LibType;
    IntList LibList;
public:
    explicit SelectLibraryInListDialog(int libType ,IntList &LibList
                                        ,LayersBase *Base,QWidget *parent = nullptr);
    ~SelectLibraryInListDialog();

    int     SelectedLibID;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectLibraryInListDialog *ui;
};

#endif // SELECTLIBRARYINLISTDIALOG_H