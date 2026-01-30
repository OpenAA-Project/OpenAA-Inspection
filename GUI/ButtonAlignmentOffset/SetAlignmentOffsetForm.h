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

#ifndef SETALIGNMENTOFFSETFORM_H
#define SETALIGNMENTOFFSETFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SetAlignmentOffsetForm;
}
class	ButtonAlignmentOffset;

class SetAlignmentOffsetForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    ButtonAlignmentOffset   *Parent;
public:
    explicit SetAlignmentOffsetForm(LayersBase *base ,ButtonAlignmentOffset *p,QWidget *parent = nullptr);
    ~SetAlignmentOffsetForm();

private slots:
    void on_horizontalSliderX_valueChanged(int value);
    void on_spinBoxOffsetX_valueChanged(int arg1);
    void on_doubleSpinBoxOffsetXMM_valueChanged(double arg1);
    void on_verticalSliderY_valueChanged(int value);
    void on_spinBoxOffsetY_valueChanged(int arg1);
    void on_doubleSpinBoxOffsetYMM_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_listWidgetPageList_itemSelectionChanged();
    void on_listWidgetPageList_clicked(const QModelIndex &index);

private:
    Ui::SetAlignmentOffsetForm *ui;

    void    ReqOffset(int Page);
    void    SendOffset(void);
    void    SendOffset(int Page);
};

#endif // SETALIGNMENTOFFSETFORM_H