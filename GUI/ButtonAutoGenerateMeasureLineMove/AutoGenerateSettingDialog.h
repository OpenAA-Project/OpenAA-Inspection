/*
 * Copyright (C) 2020
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

#ifndef AUTOGENERATESETTINGDIALOG_H
#define AUTOGENERATESETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QPushButton>
#include "XMeasureLineMove.h"

namespace Ui {
class AutoGenerateSettingDialog;
}

class AutoGenerateSettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	BladeMeasure &BladeMeasureData;
public:
    explicit AutoGenerateSettingDialog(LayersBase *Base ,BladeMeasure &BladeMeasureData ,QWidget *parent = 0);
    ~AutoGenerateSettingDialog();
    
private slots:
    void on_PushButtonSaveBladePos_clicked();
    void on_PushButtonLoadBladePos_clicked();
    void on_PushButtonClose_clicked();
	void	SlotBladeListIndexChanged ( int index );
private:
    Ui::AutoGenerateSettingDialog *ui;

	void	ShowList(void);
	void	ShwListInner(int row, int Index );
	void	GetDataFromList(void);
};

#endif // AUTOGENERATESETTINGDIALOG_H