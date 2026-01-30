/*
 * Copyright (C) 2014
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

#ifndef ADDAREADIALOG_H
#define ADDAREADIALOG_H

#include <QDialog>
#include <QColor>
#include "XServiceForLayers.h"
#include "mtColorFrame.h"

namespace Ui {
    class AddAreaDialog;
}

class AddAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit AddAreaDialog(LayersBase *Base,QWidget *parent = 0);
	AddAreaDialog(QColor Color, LayersBase *Base, QWidget *parent = 0);
    ~AddAreaDialog();

	QColor	Color;
	QColor	PickupColor;

private slots:
    void on_spinBoxR_valueChanged(int arg1);
    void on_spinBoxG_valueChanged(int arg1);
    void on_spinBoxB_valueChanged(int arg1);
    void on_pushButtonAddPickupColor_clicked();
    void on_pushButtonSubPickupColor_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddAreaDialog *ui;

	mtColorFrame	PickupColorFrame;
	mtColorFrame	ColorFrame;

	void ShowPanel(void);
};

#endif // ADDAREADIALOG_H