/*
 * Copyright (C) 2012
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

#ifndef SHOWHISTGRAMSELECTFORM_H
#define SHOWHISTGRAMSELECTFORM_H

#include "XGUIFormBase.h"
#include "XShowHistgramTotalPacket.h"

namespace Ui {
    class ShowHistgramSelectForm;
}

class ShowHistgramSelectForm : public GUIFormBase
{
    Q_OBJECT

	HistgramTypeListContainer	HContainer;
	LibraryItemListContainer	LibContainer;
public:
    explicit ShowHistgramSelectForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowHistgramSelectForm();

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonReDraw_clicked();
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_tableWidget_2_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowHistgramSelectForm *ui;
};

#endif // SHOWHISTGRAMSELECTFORM_H