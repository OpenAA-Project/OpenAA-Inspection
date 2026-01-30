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

#ifndef COMMDIALOGFORM_H
#define COMMDIALOGFORM_H

#include <QDialog>
#include"XDataInExe.h"
#include "XServiceForLayers.h"
#include "FormCommSetting.h"

namespace Ui {
class CommDialogForm;
}

class CommDialogForm : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    FormCommSetting	FormComm;
public:
    explicit CommDialogForm(LayersBase *Base ,QWidget *parent = 0);
    ~CommDialogForm();
    
private slots:
    void on_pushButtonFileName_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::CommDialogForm *ui;
};

#endif // COMMDIALOGFORM_H