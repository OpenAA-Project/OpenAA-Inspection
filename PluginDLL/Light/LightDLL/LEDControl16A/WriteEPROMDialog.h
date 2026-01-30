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

#ifndef WRITEEPROMDIALOG_H
#define WRITEEPROMDIALOG_H

#include <QDialog>
#include "LightUnitStruct.h"

namespace Ui {
class WriteEPROMDialog;
}
class	LEDControl16APanel;
class WriteEPROMDialog : public QDialog
{
    Q_OBJECT

	LEDControl16APanel	*Panel;
	struct        LightUnit   EPROMData;

public:
    explicit WriteEPROMDialog(LEDControl16APanel *p,QWidget *parent = 0);
    ~WriteEPROMDialog();

private slots:
    void on_comboBoxSelectBoard_currentIndexChanged(int index);
    void on_comboBoxSelectPort_currentIndexChanged(int index);
    void on_spinBoxLineCount_valueChanged(int arg1);
    void on_comboBoxLineNumber_currentIndexChanged(int index);
    void on_comboBoxColorType_currentIndexChanged(int index);
    void on_spinBoxMaxCurrent_valueChanged(int arg1);
    void on_pushButtonRead_clicked();
    void on_pushButtonWrite_clicked();

    void on_pushButtonSetAll_clicked();

    void on_pushButtonReadStatus_clicked();

private:
    Ui::WriteEPROMDialog *ui;

	void ShowData(void);
};

#endif // WRITEEPROMDIALOG_H