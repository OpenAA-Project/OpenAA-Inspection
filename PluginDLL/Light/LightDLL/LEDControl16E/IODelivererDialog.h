/*
 * Copyright (C) 2019
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

#ifndef IODELIVERERDIALOG_H
#define IODELIVERERDIALOG_H

#include <QDialog>

namespace Ui {
class IODelivererDialog;
}

class	LEDControl16EPanel;

class IODelivererDialog : public QDialog
{
    Q_OBJECT

	LEDControl16EPanel	*Panel;
public:
    explicit IODelivererDialog(LEDControl16EPanel *p,QWidget *parent = 0);
    ~IODelivererDialog();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::IODelivererDialog *ui;
};

#endif // IODELIVERERDIALOG_H