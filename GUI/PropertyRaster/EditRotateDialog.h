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

#ifndef EDITROTATEDIALOG_H
#define EDITROTATEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditRotateDialog;
}

class EditRotateDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditRotateDialog(LayersBase *base, QWidget *parent = 0);
    ~EditRotateDialog();

	double	Angle;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButton90_clicked();
    void on_pushButton180_clicked();
    void on_pushButton270_clicked();

private:
    Ui::EditRotateDialog *ui;
};

#endif // EDITROTATEDIALOG_H