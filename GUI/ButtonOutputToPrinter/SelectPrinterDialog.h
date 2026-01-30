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

#ifndef SELECTPRINTERDIALOG_H
#define SELECTPRINTERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QModelIndex>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectPrinterDialog;
}
class	ButtonOutputToPrinter;

class	PrinterButton : public QPushButton
{
	Q_OBJECT
public:
	int	ID;

	PrinterButton(int id, QWidget *parent);

signals:
	void	SignalClicked(int id);
protected:
	void	SlotClicked();
};


class SelectPrinterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ButtonOutputToPrinter	*Parent;

	int		CountOfButton;
	PrinterButton	**Button;

public:
	int	SelectedPrinterNo;

    explicit SelectPrinterDialog(ButtonOutputToPrinter *p ,LayersBase *pbase ,QWidget *parent = 0);
    ~SelectPrinterDialog();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonPrinter1_clicked();
	void	SlotClicked(int id);
private:
    Ui::SelectPrinterDialog *ui;
};

#endif // SELECTPRINTERDIALOG_H