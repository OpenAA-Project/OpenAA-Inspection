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

#ifndef EXISTITEMAREADIALOG_H
#define EXISTITEMAREADIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ExistItemAreaDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationExistItemAreaThreshold;

class ExistItemAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;
public:
    explicit ExistItemAreaDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ExistItemAreaDialog();

	int32	SelectedLibType;
	int32	SelectedLibID;
	double	FilledPercentageInMask;
	bool	CheckExistence;

    void    SetCurrentItem(const CheckDataValidationExistItemAreaThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationExistItemAreaThreshold *WThr);

private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
private:
    Ui::ExistItemAreaDialog *ui;
};

#endif // EXISTITEMAREADIALOG_H