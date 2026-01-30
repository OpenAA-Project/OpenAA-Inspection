/*
 * Copyright (C) 2019
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
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}
class	ImacControlByLAN;
class	ImacControlByLANParam;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ImacControlByLAN		*Panel;
	int					CurrentChannel;
public:
	ImacControlByLANParam	*Data;

    explicit SettingDialog(ImacControlByLAN *p ,LayersBase *base ,QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_comboBoxChannel_currentIndexChanged(int index);
    void on_horizontalSliderPower_valueChanged(int value);
    void on_spinBoxPower_valueChanged(int arg1);
    void on_pushButtonIPAddress_clicked();
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

	void	LoadFromWindow(int currentChannel);
	void	SetToWindow(int NewChannel);
};

#endif // SETTINGDIALOG_H