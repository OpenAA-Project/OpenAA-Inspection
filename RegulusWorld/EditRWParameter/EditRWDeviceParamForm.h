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

#ifndef EDITRWDEVICEPARAMFORM_H
#define EDITRWDEVICEPARAMFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
namespace Ui {
class EditRWDeviceParamForm;
}

class EditRWDeviceParamForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditRWDeviceParamForm(LayersBase *base,QWidget *parent = nullptr);
    ~EditRWDeviceParamForm();

    void	Show(void);
    void	LoadFromWindow(void);

private slots:
    void on_tableWidgetDeviceList_itemSelectionChanged();
    void on_tableWidgetDeviceList_clicked(const QModelIndex &index);
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonSelectFile_clicked();

    void on_pushButtonSet_clicked();

private:
    Ui::EditRWDeviceParamForm *ui;
};

#endif // EDITRWDEVICEPARAMFORM_H