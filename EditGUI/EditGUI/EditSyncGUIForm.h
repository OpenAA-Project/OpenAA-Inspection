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

#ifndef EDITSYNCGUIFORM_H
#define EDITSYNCGUIFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class EditSyncGUIForm;
}

class EditSyncGUIForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditSyncGUIForm(LayersBase *base ,QWidget *parent = 0);
    ~EditSyncGUIForm();

    void	SetFileNameFromGlobalParam(void);
    void	Show(void);
    void	LoadFromWindow(void);

private slots:
    void on_pushButtonFileName_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::EditSyncGUIForm *ui;
};

#endif // EDITSYNCGUIFORM_H