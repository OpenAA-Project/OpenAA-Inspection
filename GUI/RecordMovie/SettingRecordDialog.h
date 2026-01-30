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

#ifndef SETTINGRECORDDIALOG_H
#define SETTINGRECORDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingRecordDialog;
}
class	RecordMovie;

class SettingRecordDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    RecordMovie *RecordParent;
public:
    QString AVFormatStr;
    int     MovieSizeMode;
	float	TargetFrameRate;
	bool	DivideMovieFile;

    explicit SettingRecordDialog(RecordMovie *p,QWidget *parent = nullptr);
    ~SettingRecordDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_radioButtonAVI_clicked();
    void on_radioButtonMPEG1_clicked();

private:
    Ui::SettingRecordDialog *ui;
};

#endif // SETTINGRECORDDIALOG_H