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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}
class  CameraXtiumMitsubishiCIS;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	CameraXtiumMitsubishiCIS	*Cam;

	QString			ConfigFileName;
	int				CameraType;	/*	0:KD6R309AX3
									1:KD6R617AX3
									2:KD6R926AX3
								*/
	int				LineClock;
	int				BoardCount;
	int				Resolution;
	bool			OuterTrigger;
	int				LEDControl;
	double			LEDDutyFull;
	double			LEDDutyA;
	double			LEDDutyB;
	int				LEDDivide;
	bool			Gain;
	double			GainR;
	double			GainG;
	double			GainB;
	bool			YDirection;
	bool			Gamma;

	int				EvenOffsetY	;
	int				OddOffsetY	;
	bool			ModeAdjustWhite;

public:
    explicit SettingDialog(CameraXtiumMitsubishiCIS *cam ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_pushButtonConfigFileName_clicked();
    void on_checkBoxGainMode_clicked();
    void on_comboBoxType_currentIndexChanged(int index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonAdjustBlack_clicked();
    void on_pushButtonAdjustWhite_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H