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

#ifndef RWEDITOBJECTPROPERTYFORM_H
#define RWEDITOBJECTPROPERTYFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"

namespace Ui {
class RWEditObjectPropertyForm;
}

class RWEditObjectPropertyForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit RWEditObjectPropertyForm(LayersBase *Base,QWidget *parent = nullptr);
    ~RWEditObjectPropertyForm();

private slots:
    void on_pushButtonLoadStepFile_clicked();
    void on_pushButtonLoadFromServer_clicked();
    void on_listWidgetFileList_itemSelectionChanged();
    void on_listWidgetFileList_clicked(const QModelIndex &index);
    void on_listWidgetFileList_doubleClicked(const QModelIndex &index);
    void on_treeWidgetObject_itemSelectionChanged();
    void on_treeWidgetObject_clicked(const QModelIndex &index);
    void on_treeWidgetObject_doubleClicked(const QModelIndex &index);
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonToServer_clicked();

private:
    Ui::RWEditObjectPropertyForm *ui;
};

#endif // RWEDITOBJECTPROPERTYFORM_H