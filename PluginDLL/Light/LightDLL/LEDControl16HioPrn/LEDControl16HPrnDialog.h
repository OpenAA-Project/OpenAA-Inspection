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

#ifndef LEDCONTROL16HPRNDIALOG_H
#define LEDCONTROL16HPRNDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include "LEDControl16HioPrn.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16HPrnDialog;
}

class LEDControl16HioPanel;

class LEDControl16HPrnDialog : public QDialog
{
    Q_OBJECT
    
	LEDControl16HioPanel	*Panel;

public:
    explicit LEDControl16HPrnDialog(LEDControl16HioPanel *p,QWidget *parent = 0);
    ~LEDControl16HPrnDialog();
    
	void	ShowData(void);
	void	GetDataFromWindow(void);
private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonRequire_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonDefineSignals_clicked();
    void on_pushButtonShowTiming_clicked();

private:
    Ui::LEDControl16HPrnDialog *ui;
};

#endif // LEDCONTROL16HPRNDIALOG_H