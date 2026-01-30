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

#ifndef SHOWADDIALOG_H
#define SHOWADDIALOG_H

#include <QDialog>

namespace Ui {
class ShowADDialog;
}

class	LEDControl16BPanel;

class ShowADDialog : public QDialog
{
    Q_OBJECT

	LEDControl16BPanel	*Panel;
public:
    explicit ShowADDialog(LEDControl16BPanel *p,QWidget *parent = 0);
    ~ShowADDialog();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonReqAD_clicked();

private:
    Ui::ShowADDialog *ui;
};

#endif // SHOWADDIALOG_H