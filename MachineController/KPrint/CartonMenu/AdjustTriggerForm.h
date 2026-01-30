/*
 * Copyright (C) 2022
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

#ifndef ADJUSTTRIGGERFORM_H
#define ADJUSTTRIGGERFORM_H

#include <QWidget>
#include "XCommToTrigger.h"

namespace Ui {
class AdjustTriggerForm;
}

class	CartonMenuForm;


class AdjustTriggerForm : public QWidget
{
    Q_OBJECT
    CartonMenuForm	*Parent;
	CommToTrigger	Trigger;

	struct	TriggerInfo	TriggerInfoData;
	struct	TriggerInfo	BackupTriggerInfoData;

public:
    explicit AdjustTriggerForm(CartonMenuForm *p ,QWidget *parent = 0);
    ~AdjustTriggerForm();
    
private slots:
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_spinBox1_valueChanged(int arg1);
    void on_spinBox2_valueChanged(int arg1);
    void on_horizontalSliderDrop_valueChanged(int value);
    void on_spinBoxDrop_valueChanged(int arg1);
    void on_horizontalSlider3_valueChanged(int value);
    void on_horizontalSlider4_valueChanged(int value);
    void on_spinBox3_valueChanged(int arg1);
    void on_spinBox4_valueChanged(int arg1);

private:
    Ui::AdjustTriggerForm *ui;


};

#endif // ADJUSTTRIGGERFORM_H