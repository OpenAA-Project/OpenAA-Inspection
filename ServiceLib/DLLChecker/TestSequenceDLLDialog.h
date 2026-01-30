/*
 * Copyright (C) 2012
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

#ifndef TESTSEQUENCEDLLDIALOG_H
#define TESTSEQUENCEDLLDIALOG_H

#include <QDialog>
#include "XSequence.h"

namespace Ui {
    class TestSequenceDLLDialog;
}


class TestSequenceDLLDialog : public QDialog
{
    Q_OBJECT

	DLLVarOperand	*Var;

public:
    explicit TestSequenceDLLDialog(DLLVarOperand *D,QWidget *parent = 0);
    ~TestSequenceDLLDialog();

private slots:
    void on_pushButtonTest_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::TestSequenceDLLDialog *ui;
};

#endif // TESTSEQUENCEDLLDIALOG_H