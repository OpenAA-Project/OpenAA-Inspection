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

#ifndef SHOWIOFORM_H
#define SHOWIOFORM_H

#include <QDialog>
#include "DummyPIO.h"
#include <QTableWidgetItem>
#include "XIODLL.h"

namespace Ui {
    class ShowIOForm;
}

class ShowIOForm : public QDialog,public PIODLLBaseClass
{
    Q_OBJECT

public:
    explicit ShowIOForm(QWidget *parent = 0);
    ~ShowIOForm();

	bool	InBit[DummyBitCount];
	bool	OutBit[DummyBitCount];

	void	ShowOut(void);

private slots:
        void on_twIN_itemChanged(QTableWidgetItem *item);

        void on_twOUT_itemChanged(QTableWidgetItem *item);

private:
    Ui::ShowIOForm *ui;
};

#endif // SHOWIOFORM_H