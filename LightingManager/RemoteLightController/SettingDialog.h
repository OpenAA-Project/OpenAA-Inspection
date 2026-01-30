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
#include "XRemoteLightController.h"
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
	RemoteLightContainer	RemoteLightData;

	explicit SettingDialog(LayersBase *Base ,RemoteLightContainer &src ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_listWidgetLightDLL_clicked(const QModelIndex &index);
    void on_listWidgetRegisteredItemList_clicked(const QModelIndex &index);
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SettingDialog *ui;

	void	ShowRegisteredItemList(void);
};

#endif // SETTINGDIALOG_H