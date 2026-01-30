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

#ifndef SELECTALIGNMENTAREAFORM_H
#define SELECTALIGNMENTAREAFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectAlignmentAreaForm;
}
class EasyPropertyAlignmentForm;

class SelectAlignmentAreaForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    EasyPropertyAlignmentForm   *Parent;
    ListPhasePageLayerItemPack		AreaID;
    IntList	AreaIDList;
public:
    explicit SelectAlignmentAreaForm(LayersBase *base
                                    ,EasyPropertyAlignmentForm *P
                                    ,QWidget *parent = nullptr);
    ~SelectAlignmentAreaForm();
    void    Initial(void);

    int     SelectedAreaID;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonSelect_clicked();
    void on_toolButtonCancel_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::SelectAlignmentAreaForm *ui;
};

#endif // SELECTALIGNMENTAREAFORM_H