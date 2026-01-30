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

#ifndef SELECTPAGES_H
#define SELECTPAGES_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectPages;
}

class SelectPages : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectPages(LayersBase *base ,QWidget *parent = 0);
             SelectPages(LayersBase *base ,const IntList &Pages ,QWidget *parent);
    ~SelectPages();

    IntList	SelectedPages;

private slots:
    void on_pushButtonSelect_clicked();
    void on_listWidgetSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonAll_clicked();
    void on_pushButtonRelease_clicked();

private:
    Ui::SelectPages *ui;
};

#endif // SELECTPAGES_H