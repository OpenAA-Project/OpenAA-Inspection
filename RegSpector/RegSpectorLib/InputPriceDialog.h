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

#ifndef INPUTPRICEDIALOG_H
#define INPUTPRICEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include "XCSV.h"
#include "NList.h"
#include "XServiceRegSpector.h"

namespace Ui {
class InputPriceDialog;
}




class InputPriceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputPriceDialog(PriceContainer &prices ,QWidget *parent = 0);
    ~InputPriceDialog();
    
    PriceContainer  Prices;

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputPriceDialog *ui;
};

#endif // INPUTPRICEDIALOG_H