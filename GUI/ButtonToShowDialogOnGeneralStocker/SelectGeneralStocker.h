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

#ifndef SELECTGENERALSTOCKER_H
#define SELECTGENERALSTOCKER_H

#include <QDialog>
#include <QModelIndex>
#include "NList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectGeneralStocker;
}
class	GeneralStocker;
class	GeneralStockerPointerList;

class SelectGeneralStocker : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    NPListPack<GeneralStockerPointerList>	Dim;

public:
    explicit SelectGeneralStocker(LayersBase *base,NPListPack<GeneralStockerPointerList> &Dim,QWidget *parent = 0);
    ~SelectGeneralStocker();

    GeneralStocker	*Selected;

private slots:
    void on_pushButtonSelect_clicked();
    void on_tableWidgetGeneralStocker_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectGeneralStocker *ui;
};

#endif // SELECTGENERALSTOCKER_H