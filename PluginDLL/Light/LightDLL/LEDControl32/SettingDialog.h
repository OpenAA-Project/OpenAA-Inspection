/*
 * Copyright (C) 2015
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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QLineEdit>
#include "LEDControl32.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

	QSpinBox	*pEditBrightnrss[LEDCountInSheet];
	QLineEdit	*pEditText[LEDCountInSheet];
	LEDControl32	*Panel;
	LEDControl32::LEDDataStruct	LEDData;

	int	LastPatternNo;
	int	LastBoardNo;

public:
    explicit SettingDialog(LEDControl32 *Src ,QWidget *parent = 0);
    ~SettingDialog();

	void	ShowCurrent();
	void	StoreCurrent(int BoardNo ,int PatternNo);

private slots:
    void on_comboBoxPattern_currentIndexChanged(int index);
    void on_comboBoxBoard_currentIndexChanged(int index);
    void on_verticalSliderBrightnrss_valueChanged(int value);
    void on_spinBoxBrightness_valueChanged(int arg1);
    void on_pushButtonTransfer_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_toolButtonLightON_clicked();

    void on_radioButtonOutputA_clicked();

    void on_radioButtonOutputB_clicked();

    void on_comboBoxPatternBuffA_currentIndexChanged(int index);

    void on_comboBoxPatternBuffB_currentIndexChanged(int index);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H