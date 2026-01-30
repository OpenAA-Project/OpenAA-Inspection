/*
 * Copyright (C) 2025
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

#ifndef EDITORDERDIALOG_H
#define EDITORDERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class EditOrderDialog;
}

class GUIFormBase;

class EditOrderDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

    GUIFormBase **GDim;
    int         GDimCount;
public:
    explicit EditOrderDialog(LayersBase *base,QWidget *parent = nullptr);
    ~EditOrderDialog();

private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::EditOrderDialog *ui;

    void    ShowDim(void);

};

#endif // EDITORDERDIALOG_H