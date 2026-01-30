/*
 * Copyright (C) 2023
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


#ifndef ALGORITHMITEMPROPERTYGRID_H
#define ALGORITHMITEMPROPERTYGRID_H

#include <QWidget>
#include "XDataAlgorithm.h"

namespace Ui {
class AlgorithmItemPropertyGrid;
}

class	AlgorithmItemPropertyLine : public NPList<AlgorithmItemPropertyLine>
{
public:
    QString		CategoryName;
    QString		PropertyName;
    QStringList	Values;
};

class AlgorithmItemPropertyGrid : public QWidget
{
    Q_OBJECT
    
public:
    explicit AlgorithmItemPropertyGrid(QWidget *parent = 0);
    ~AlgorithmItemPropertyGrid();

    AlgorithmItemPropertyContainer			AlgorithmItemPropertyData;
    NPListPack<AlgorithmItemPropertyLine>	ItemLines;

    void	ShowGrid(const AlgorithmItemPropertyContainer &_AlgorithmItemPropertyData);
protected:
    virtual void closeEvent ( QCloseEvent * event ) override;
private:
    Ui::AlgorithmItemPropertyGrid *ui;
};

#endif // ALGORITHMITEMPROPERTYGRID_H