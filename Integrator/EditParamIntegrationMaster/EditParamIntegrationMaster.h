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

#ifndef EDITPARAMINTEGRATIONMASTER_H
#define EDITPARAMINTEGRATIONMASTER_H

#include <QMainWindow>
#include "ui_EditParamIntegrationMaster.h"
#include "WEditParameterTab.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

class	ParamIntegrationMaster;

class EditParamIntegrationMaster : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QString	GlobalParamLoadedFileName;
	int	LastRowInSlave;
public:
	WEditParameterTab	*WTab;
	ParamIntegrationMaster *Param;

	EditParamIntegrationMaster(LayersBase *base,ParamIntegrationMaster *param,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditParamIntegrationMaster();

private slots:
    void on_SaveButton_clicked();
    void on_UpdateDefaultButton_clicked();
    void on_LoadButton_clicked();
    void on_CancelButton_clicked();

    void on_listWidgetSlaveList_clicked(const QModelIndex &index);
    void on_pushButtonSlaveListPlus_clicked();
    void on_pushButtonSlaveListMinus_clicked();
    void on_pushButtonShooseSharedFolder_clicked();
    void on_pushButtonImagePathPlus_clicked();
    void on_pushButtonImagePathMinus_clicked();

private:
	Ui::EditParamIntegrationMasterClass ui;

	void	ShowSlaveList(void);
	void	ShowIntegrationSlave(int Row);
	void	GetIntegrationSlave(int Row);
	void	ClearIntegrationSlave(void);
};

#endif // EDITPARAMINTEGRATIONMASTER_H