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

#ifndef EDITTIMELISTDIALOG_H
#define EDITTIMELISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "IntegrationCalibrateCamera.h"

namespace Ui {
class EditTimeListDialog;
}

class TimeListContainer;


class EditTimeListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    TimeListContainer   LContainer;

    explicit EditTimeListDialog(TimeListContainer &LList,LayersBase *Base,QWidget *parent = nullptr);
    ~EditTimeListDialog();

private slots:
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditTimeListDialog *ui;
};

#endif // EDITTIMELISTDIALOG_H