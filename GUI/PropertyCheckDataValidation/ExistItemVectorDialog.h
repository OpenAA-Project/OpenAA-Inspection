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

#ifndef EXISTITEMVECTORDIALOG_H
#define EXISTITEMVECTORDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ExistItemVectorDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationExistItemVectorThreshold;

class ExistItemVectorDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;
public:
    explicit ExistItemVectorDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ExistItemVectorDialog();

    int SelectedLibType ;
    int SelectedLibID   ;

    void    SetCurrentItem(const CheckDataValidationExistItemVectorThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationExistItemVectorThreshold *WThr);

private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
private:
    Ui::ExistItemVectorDialog *ui;
};

#endif // EXISTITEMVECTORDIALOG_H