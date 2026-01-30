/*
 * Copyright (C) 2014
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

#ifndef SETTINGSERVERINFODIALOG_H
#define SETTINGSERVERINFODIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XChangeServerInfo.h"

namespace Ui {
class SettingServerInfoDialog;
}

class SettingServerInfoDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ChangeServerContainer	ServerList;
public:
    explicit SettingServerInfoDialog(LayersBase *base,QWidget *parent = 0);
    ~SettingServerInfoDialog();
    
private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_listWidgetServer_clicked(const QModelIndex &index);

private:
    Ui::SettingServerInfoDialog *ui;

	void	DrawList(void);
};

#endif // SETTINGSERVERINFODIALOG_H