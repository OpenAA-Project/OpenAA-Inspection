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

#ifndef CHANGESERVERFORMASTERDIALOG_H
#define CHANGESERVERFORMASTERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XChangeServerInfo.h"

namespace Ui {
class ChangeServerForMasterDialog;
}

class ChangeServerForMasterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ChangeServerContainer	ServerList;
public:
    explicit ChangeServerForMasterDialog(LayersBase *base,QWidget *parent = 0);
    ~ChangeServerForMasterDialog();
    
	ChangeServerInfo		*Selected;
private slots:
    void on_listWidgetServer_doubleClicked(const QModelIndex &index);
    void on_pushButtonChange_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonEdit_clicked();

private:
    Ui::ChangeServerForMasterDialog *ui;

	void	DrawList(void);
};

#endif // CHANGESERVERFORMASTERDIALOG_H