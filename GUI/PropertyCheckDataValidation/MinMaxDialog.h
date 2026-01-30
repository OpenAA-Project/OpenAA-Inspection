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

#ifndef MINMAXDIALOG_H
#define MINMAXDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XPropertyCheckDataValidationPacket.h"

namespace Ui {
class MinMaxDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationCheckMinMaxThreshold;

class MinMaxDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;
    ThresholdMemberListContainer	LContainer;
public:
    explicit MinMaxDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~MinMaxDialog();

    int SelectedLibType ;
    int SelectedLibID   ;
	int32	ParamID;
	double	MinValue;
	double	MaxValue;

    void    SetCurrentItem(const CheckDataValidationCheckMinMaxThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationCheckMinMaxThreshold *WThr);

private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::MinMaxDialog *ui;
};

#endif // MINMAXDIALOG_H