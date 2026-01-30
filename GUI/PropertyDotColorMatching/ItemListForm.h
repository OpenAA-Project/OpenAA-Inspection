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

#ifndef ITEMLISTFORM_H
#define ITEMLISTFORM_H

#include <QWidget>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XPropertyDotColorMatchingPacket.h"
namespace Ui {
class ItemListForm;
}

class ItemListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    BlockListInfoContainer	BlockListInfoContainerData;
    int     SortType;   //0:ItemID, 1:AreaSearch    ,2:SelfSearch ,3:OKDot
    bool    Decendant;
public:
    explicit ItemListForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ItemListForm();

    void    Initial(void);

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void    SlotTableSectionClicked(int logicalIndex);
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::ItemListForm *ui;
    void    ShowGrid(void);
    void    resizeEvent(QResizeEvent *)     override;
    void	closeEvent(QCloseEvent *event)  override;
};

#endif // ITEMLISTFORM_H