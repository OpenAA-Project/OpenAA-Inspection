/*
 * Copyright (C) 2025
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

#ifndef EDITROBOTPARAMETERDIALOG_H
#define EDITROBOTPARAMETERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRobotAction.h"

namespace Ui {
class EditRobotParameterDialog;
}

class EditRobotParameterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    RobotActionBase *ABase;
    RobotClassPack  TmpPack;
public:
    explicit EditRobotParameterDialog(LayersBase *base,RobotActionBase *aBase,QWidget *parent = nullptr);
    ~EditRobotParameterDialog();

private slots:
    void on_listWidgetRobotList_currentRowChanged(int currentRow);
    void on_pushButtonAdd_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditRobotParameterDialog *ui;

    void ShowRobotList(void);
    void ShowRobotAccessList(RobotAccessList *a);

};

#endif // EDITROBOTPARAMETERDIALOG_H