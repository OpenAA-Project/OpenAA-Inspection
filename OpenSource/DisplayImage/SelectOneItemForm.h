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

#ifndef SELECTONEITEMFORM_H
#define SELECTONEITEMFORM_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectOneItemForm;
}

class	AlgorithmBase;

class SelectOneItemForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    ListLayerIDLibNamePack	ItemIDList;
    int GlobalPage;
public:
    explicit SelectOneItemForm(AlgorithmBase *Algo ,ListLayerIDLibNamePack &itemIDList ,QWidget *parent ,int _GlobalPage=-1);
    ~SelectOneItemForm();

    ListLayerAndID	SelectedItem;

private slots:
    void on_pushButtonOK_clicked();
    void on_tableWidgetItem_clicked(const QModelIndex &index);
    void on_tableWidgetItem_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectOneItemForm *ui;
};

#endif // SELECTONEITEMFORM_H