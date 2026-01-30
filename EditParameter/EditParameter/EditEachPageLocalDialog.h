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

#ifndef EDITEACHPAGELOCALDIALOG_H
#define EDITEACHPAGELOCALDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"

namespace Ui {
class EditEachPageLocalDialog;
}

class EditEachPageLocalDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int     OldPage;
    WEditParameterTab	*WTab;
public:
    explicit EditEachPageLocalDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditEachPageLocalDialog();

private slots:
    void on_ButtonOK_clicked();

    void on_listWidgetPageList_itemSelectionChanged();
    void on_listWidgetPageList_itemClicked(QListWidgetItem *item);

private:
    Ui::EditEachPageLocalDialog *ui;
};

#endif // EDITEACHPAGELOCALDIALOG_H