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

#ifndef SELECTSLAVEMACHINEDIALOG_H
#define SELECTSLAVEMACHINEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include "XIntClass.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectSlaveMachineDialog;
}

class SelectSlaveMachineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    QCheckBox   *CBoxDim[100];
    QCheckBox   *CBoxDimRGen[100];
    QCheckBox   *CBoxDimKeepMark[100];
public:
    explicit SelectSlaveMachineDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~SelectSlaveMachineDialog();

    bool    ResetSwitchPhase;
    bool    ResetMakeAverage;
    IntList SelectedSlaveNoList;
    IntList ReGenList;
    IntList KeepMarkList;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectSlaveMachineDialog *ui;
};

#endif // SELECTSLAVEMACHINEDIALOG_H