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

#ifndef SELECTPAGELAYER_H
#define SELECTPAGELAYER_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SelectPageLayer;
}

class SelectPageLayer : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectPageLayer(LayersBase *pbase ,QWidget *parent = 0);
    ~SelectPageLayer();

    int	Page;
    int	Layer;

private slots:
    void on_listWidgetPage_clicked(const QModelIndex &index);
    void on_listWidgetPage_doubleClicked(const QModelIndex &index);
    void on_listWidgetLayer_clicked(const QModelIndex &index);
    void on_listWidgetLayer_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectPageLayer *ui;

    void ShowLayerList(int page);
};

#endif // SELECTPAGELAYER_H