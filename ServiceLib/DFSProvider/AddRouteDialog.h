/*
 * Copyright (C) 2016
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

#ifndef ADDROUTEDIALOG_H
#define ADDROUTEDIALOG_H

#include <QDialog>
#include "XDFSProvider.h"

namespace Ui {
class AddRouteDialog;
}

class AddRouteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRouteDialog(QWidget *parent = 0);
    ~AddRouteDialog();

	void	Initial(PathClass &d);

	QString	Path;
	int		Priority;
	QString	NetworkPath;
	QString	DFSFilterDLLFileName;
	QString	DFSFilterParameter;

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSearchDLL_clicked();

private:
    Ui::AddRouteDialog *ui;
};

#endif // ADDROUTEDIALOG_H