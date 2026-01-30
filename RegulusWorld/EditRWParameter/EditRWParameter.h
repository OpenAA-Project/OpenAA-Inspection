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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditRWParameter.h"
#include "XParamRegulusWorld.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTranslator>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"
#include "WMultiGrid.h"
#include "EditRWDeviceParamForm.h"

class EditRWParameter : public QMainWindow,public ServiceForLayers
{
    Q_OBJECT

    WEditParameterTab	    *WTab;
    EditRWDeviceParamForm   *WDeviceTab;
public:
    EditRWParameter(LayersBase *base,QWidget *parent = nullptr);
    ~EditRWParameter();

private slots:
    void on_SaveButton_clicked();
    void on_UpdateDefaultButton_clicked();
    void on_LoadButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::EditRWParameterClass ui;

    QString		RWParamLoadedFileName;

    virtual	void resizeEvent(QResizeEvent *e)	override;
};