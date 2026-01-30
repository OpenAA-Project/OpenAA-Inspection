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

#ifndef ROTRECTANGLEDIALOG_H
#define ROTRECTANGLEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class RotRectangleDialog;
}

class RotRectangleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RotRectangleDialog(LayersBase *base, QWidget *parent = 0);
    ~RotRectangleDialog();

	int		Cx,Cy;
	int		Width,Height;
	double	S;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RotRectangleDialog *ui;
};

#endif // ROTRECTANGLEDIALOG_H