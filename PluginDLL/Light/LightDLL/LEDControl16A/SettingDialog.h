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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include "LEDControl16A.h"

namespace Ui {
class SettingDialog;
}


class SettingDialog : public QDialog
{
    Q_OBJECT
	LEDControl16APanel	*Panel;
	QTimer	TM;

	class	LineWindow
	{
	public:
		QLabel		Label;
		QSpinBox	EditValue;
		QLineEdit	EditComment;

		LineWindow(QWidget *parent);
		void	SetY(int n);
		void	Show(void);
	};

	LineWindow	*LineData[256];

	int	LastLight;

public:
    explicit SettingDialog(LEDControl16APanel *p,QWidget *parent = 0);
    ~SettingDialog();

	QProgressBar	*GetBar(void);

private slots:
    void on_toolButtonRed_clicked();
    void on_toolButtonGreen_clicked();
    void on_toolButtonBlue_clicked();
    void on_pushButtonTransfer_clicked();
    void on_toolButtonON_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonSetAll_clicked();

    void on_pushButtonWriteEPROM_clicked();
    void on_pushButtonShowIO_clicked();
    void on_pushButtonTemporaryON_clicked();

private:
    Ui::SettingDialog *ui;


	int	GetCurrentPortNumber(void);
	void	InitialWindow	 (LEDControl16APanel::PortData &Data);
	void	ShowData		 (int n,LEDControl16APanel::PortData &Data ,int PatternNumber);
	void	GetDataFromWindow(int n,LEDControl16APanel::PortData &Data ,int PatternNumber);
	QString	GetColorStr(int ColorType);
};

#endif // SETTINGDIALOG_H