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

#ifndef ALGORITHMPARAMETERDIALOG_H
#define ALGORITHMPARAMETERDIALOG_H

#include <QDialog>

namespace Ui {
class AlgorithmParameterDialog;
}

class AlgorithmParameterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmParameterDialog(QWidget *parent = 0);
    ~AlgorithmParameterDialog();

private:
    Ui::AlgorithmParameterDialog *ui;
};

#endif // ALGORITHMPARAMETERDIALOG_H