/*
 * Copyright (C) 2022
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

#ifndef INPUTBELTSPEEDDIALOG_H
#define INPUTBELTSPEEDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputBeltSpeedDialog;
}
class CartonMenuForm;

class InputBeltSpeedDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    CartonMenuForm	*Parent;
public:
    explicit InputBeltSpeedDialog(LayersBase *Base ,CartonMenuForm	*p,QWidget *parent = 0);
    ~InputBeltSpeedDialog();
    
    int     TimeOutValue;

private slots:
    void on_PushButtonOK_clicked();
    void on_spinBoxBeltVelocity_valueChanged(int arg1);
    void on_pushButtonInputPanelVelocity_clicked();

private:
    Ui::InputBeltSpeedDialog *ui;

    int GetTimeOutValue(void);
};

#endif // INPUTBELTSPEEDDIALOG_H