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

#ifndef CONFIRMITEMLISTFORM_H
#define CONFIRMITEMLISTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XDataAlgorithmConfirm.h"
#include "NList.h"

namespace Ui {
class ConfirmItemListForm;
}
class ConfirmForm;
class ConfirmAlgorithm;

class ComfirmItemListPointer : public NPList<ComfirmItemListPointer>
{
public:
    ConfirmItemList     *CItem;
    ConfirmAlgorithm    *CAlgorithm;

    virtual	int	Compare(ComfirmItemListPointer &src)    override;
};


class ConfirmItemListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    friend  class ConfirmForm;

    ConfirmForm *Parent;
    NPListPack<ComfirmItemListPointer>  ComfirmItems;
public:
    explicit ConfirmItemListForm(LayersBase *Base,ConfirmForm *p,QWidget *parent = nullptr);
    ~ConfirmItemListForm();

    void    BuildShowItemList(void);
    
private slots:
    void on_tableWidgetCause_itemSelectionChanged();

    void on_tableWidgetCause_clicked(const QModelIndex &index);

private:
    Ui::ConfirmItemListForm *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // CONFIRMITEMLISTFORM_H