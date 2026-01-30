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

#ifndef LONGCIRCLEDIALOG_H
#define LONGCIRCLEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class LongCircleDialog;
}

class LongCircleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit LongCircleDialog(LayersBase *base, QWidget *parent = 0);
    ~LongCircleDialog();

	int		Cx1,Cy1;
	int		Cx2,Cy2;
	int		R;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::LongCircleDialog *ui;
};

#endif // LONGCIRCLEDIALOG_H