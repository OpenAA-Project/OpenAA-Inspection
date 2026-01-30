/*
 * Copyright (C) 2024
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

#ifndef SETTINGCARTONDIALOG_H
#define SETTINGCARTONDIALOG_H

#include <QDialog>
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingCartonDialog;
}
class CartonMenuForm;

class SettingCartonDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
	WEditParameterTab	*WTabGeneral;
	CartonMenuForm	*Parent;
public:
    explicit SettingCartonDialog(LayersBase *Base ,CartonMenuForm *PForm,QWidget *parent = 0);
    ~SettingCartonDialog();
    
    void	AdjustTrigger(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonTrigger_clicked();
    void on_pushButtonUsageLibrary_clicked();

private:
    Ui::SettingCartonDialog *ui;
};

#endif // SETTINGCARTONDIALOG_H