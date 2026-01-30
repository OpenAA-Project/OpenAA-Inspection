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

#ifndef SELECTBYORIGIN_H
#define SELECTBYORIGIN_H

#include <QDialog>
#include "XDisplayImage.h"

namespace Ui {
class SelectByOrigin;
}

class SelectByOrigin : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectByOrigin(LayersBase *Base,NPListPack<OriginNames> &originNameList,QWidget *parent = 0);
    ~SelectByOrigin();

    NPListPack<OriginNames>	OriginNameList;
    OriginNames				*Selected;

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectByOrigin *ui;
};

#endif // SELECTBYORIGIN_H