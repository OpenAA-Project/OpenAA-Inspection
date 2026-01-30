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

#ifndef SETTINGBARCODEFORMDIALOG_H
#define SETTINGBARCODEFORMDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QImage>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include "XIntegrationComm.h"
#include "XIntegrationPacketComm.h"
#include "XBCRInspection.h"

namespace Ui {
class SettingBarcodeFormDialog;
}

class ButtonSettingBarcodeForm;

class SettingBarcodeFormDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
	ButtonSettingBarcodeForm *Parent;

public:
    explicit SettingBarcodeFormDialog(LayersBase *base, ButtonSettingBarcodeForm *p, QWidget *parent = 0);
    ~SettingBarcodeFormDialog();
    
private slots:
    void on_tableWidgetItemList_clicked(const QModelIndex &index);
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::SettingBarcodeFormDialog *ui;
};

#endif // SETTINGBARCODEFORMDIALOG_H