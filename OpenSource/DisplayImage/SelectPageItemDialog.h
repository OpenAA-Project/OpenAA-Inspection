/*
 * Copyright (C) 2020
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

#ifndef SELECTPAGEITEMDIALOG_H
#define SELECTPAGEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include <QModelIndex>

namespace Ui {
class SelectPageItemDialog;
}
class	AlgorithmBase;

class SelectPageItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ListPageLayerIDLibNamePack	ItemIDList;
public:
    explicit SelectPageItemDialog(AlgorithmBase *Algo ,ListPageLayerIDLibNamePack &itemIDList ,QWidget *parent = 0);
    ~SelectPageItemDialog();
    
	ListPageLayerIDPack	SelectedItems;
private slots:
    void on_tableWidgetItem_clicked(const QModelIndex &index);
    void on_tableWidgetItem_doubleClicked(const QModelIndex &index);
    void on_ButtonOK_clicked();

private:
    Ui::SelectPageItemDialog *ui;
};

#endif // SELECTPAGEITEMDIALOG_H