/*
 * Copyright (C) 2021
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

#ifndef LEDCONTROL16GPRNDIALOG_H
#define LEDCONTROL16GPRNDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include "LEDControl16GPrn.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16GPrnDialog;
}

class LEDControl16GPanel;

class LEDControl16GPrnDialog : public QDialog
{
    Q_OBJECT
    
	LEDControl16GPanel	*Panel;

public:
    explicit LEDControl16GPrnDialog(LEDControl16GPanel *p,QWidget *parent = 0);
    ~LEDControl16GPrnDialog();
    
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
    Ui::LEDControl16GPrnDialog *ui;
};

#endif // LEDCONTROL16GPRNDIALOG_H