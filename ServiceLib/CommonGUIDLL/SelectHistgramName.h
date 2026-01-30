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

#ifndef SELECTHISTGRAMNAME_H
#define SELECTHISTGRAMNAME_H

#include <QDialog>
#include "XDataAlgorithm.h"

namespace Ui {
    class SelectHistgramName;
}

class SelectHistgramName : public QDialog
{
    Q_OBJECT

	AlgorithmBase *ABase;

public:
    explicit SelectHistgramName(AlgorithmBase *base ,QWidget *parent = 0);
    ~SelectHistgramName();

	int	HistgramID;

private slots:
    void on_pushButtonSelect_clicked();

    void on_listWidgetHistName_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectHistgramName *ui;
};

#endif // SELECTHISTGRAMNAME_H