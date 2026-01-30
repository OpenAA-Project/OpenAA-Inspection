/*
 * Copyright (C) 2021
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

#ifndef SHOWCONNECTIONINFOFORM_H
#define SHOWCONNECTIONINFOFORM_H

#include <QDialog>

namespace Ui {
    class ShowConnectionInfoForm;
}

class	GlueRunner;

class ShowConnectionInfoForm : public QDialog
{
    Q_OBJECT

	GlueRunner *Glue;
public:
    explicit ShowConnectionInfoForm(GlueRunner *G ,QWidget *parent = 0);
    ~ShowConnectionInfoForm();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonDelete_clicked();

private:
    Ui::ShowConnectionInfoForm *ui;
};

#endif // SHOWCONNECTIONINFOFORM_H