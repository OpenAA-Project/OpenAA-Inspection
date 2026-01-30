/*
 * Copyright (C) 2023
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

#ifndef NEWMASTERDIALOG_H
#define NEWMASTERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QLabel>
#include "XIntegrationBase.h"

namespace Ui {
class NewMasterDialog;
}

class	IntegrationNewMaster;

class NewMasterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    IntegrationNewMaster    *Parent;
public:
	QString	ResultName	;
	QString	ResultRemark;
	QString	ResultNumber;
	IntegrationCommonData	CommonData;
	
	explicit NewMasterDialog(LayersBase *Base,IntegrationNewMaster *P,QWidget *parent = 0);
    ~NewMasterDialog();
    
private slots:
    void on_pushButtonInputPanelName_clicked();
    void on_pushButtonInputPanelRemark_clicked();
    void on_pushButtonInputPanelSizeX_clicked();
    void on_pushButtonInputPanelSizeY_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonInputPanelNumber_clicked();

private:
    Ui::NewMasterDialog *ui;
};

#endif // NEWMASTERDIALOG_H