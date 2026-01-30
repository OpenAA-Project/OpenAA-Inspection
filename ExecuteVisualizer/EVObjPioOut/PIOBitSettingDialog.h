/*
 * Copyright (C) 2012
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

#ifndef PIOBITSETTINGDIALOG_H
#define PIOBITSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
    class PIOBitSettingDialog;
}

class	RunnerPIOOut;

class PIOBitSettingDialog : public QDialog
{
    Q_OBJECT

	RunnerPIOOut		*Obj;
public:
    explicit PIOBitSettingDialog(RunnerPIOOut *obj, QWidget *parent = 0);
    ~PIOBitSettingDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_spinBoxBoardNumber_valueChanged(int arg1);

private:
    Ui::PIOBitSettingDialog *ui;
};

#endif // PIOBITSETTINGDIALOG_H