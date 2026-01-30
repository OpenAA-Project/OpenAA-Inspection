/*
 * Copyright (C) 2017
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

#ifndef MODIFYITEMDIALOG_H
#define MODIFYITEMDIALOG_H

#include <QDialog>
#include "XMeasureHolePos.h"
#include "XMeasureHolePosPacket.h"
#include "XServiceForLayers.h"

namespace Ui {
    class ModifyItemDialog;
}

class ModifyItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	MeasureHolePosThreshold		*ThreData;
	QString						ItemName;

    explicit ModifyItemDialog(LayersBase *base, QString &itemName ,MeasureHolePosThreshold *_ThreData 
								,QWidget *parent = 0);
    ~ModifyItemDialog();

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ModifyItemDialog *ui;
};

#endif // MODIFYITEMDIALOG_H