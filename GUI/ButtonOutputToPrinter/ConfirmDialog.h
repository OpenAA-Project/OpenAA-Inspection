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

#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XPrinterManager.h"

namespace Ui {
class ConfirmDialog;
}
class	ButtonOutputToPrinter;

class ConfirmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ButtonOutputToPrinter	*Parent;

public:
    explicit ConfirmDialog(ButtonOutputToPrinter *p ,PrinterClass *PC ,LayersBase *pbase ,QWidget *parent = 0);
    ~ConfirmDialog();

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H