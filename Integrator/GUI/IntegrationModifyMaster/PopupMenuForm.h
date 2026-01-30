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

#ifndef POPUPMENUFORM_H
#define POPUPMENUFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
namespace Ui {
class PopupMenuForm;
}

class PopupMenuForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit PopupMenuForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PopupMenuForm();

private slots:
    void on_PushButtonMoveAll_clicked();
    void on_PushButtonChangeSize_clicked();
    void on_PushButtonClose_clicked();

private:
    Ui::PopupMenuForm *ui;
};

#endif // POPUPMENUFORM_H