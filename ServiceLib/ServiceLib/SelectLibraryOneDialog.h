/*
 * Copyright (C) 2022
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

#ifndef SELECTLIBRARYONEDIALOG_H
#define SELECTLIBRARYONEDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include <QModelIndex>
#include "XIntClass.h"

namespace Ui {
class SelectLibraryOneDialog;
}

class SelectLibraryOneDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	IntList	LibList;
public:
    explicit SelectLibraryOneDialog(LayersBase *Base,int LibType,const IntList &_LibList ,QWidget *parent = 0);
    ~SelectLibraryOneDialog();

	int	SelectedLibID;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectLibraryOneDialog *ui;
};

#endif // SELECTLIBRARYONEDIALOG_H