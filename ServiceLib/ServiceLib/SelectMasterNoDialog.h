/*
 * Copyright (C) 2023
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

#ifndef SELECTMASTERNODIALOG_H
#define SELECTMASTERNODIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"
namespace Ui {
class SelectMasterNoDialog;
}

class SelectMasterNoDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    IntList     LibTypeList;
public:
    explicit SelectMasterNoDialog(LayersBase *Base,int OriginCode ,QWidget *parent = nullptr);
    ~SelectMasterNoDialog();

    int MasterNoOriginCode;

private slots:
    void on_groupBoxMasterNo_clicked();
    void on_groupBoxAlgorithm_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectMasterNoDialog *ui;
};

#endif // SELECTMASTERNODIALOG_H