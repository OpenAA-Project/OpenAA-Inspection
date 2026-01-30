/*
 * Copyright (C) 2015
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

#ifndef SHOWFILTERLISTDIALOG_H
#define SHOWFILTERLISTDIALOG_H

#include <QDialog>
#include "ButtonToSetFilterForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class ShowFilterListDialog;
}

class ShowFilterListDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
	int						GlobalPage;
	GUIFilterListContainer	FList;

    explicit ShowFilterListDialog(LayersBase *base ,QWidget *parent = 0);
    ~ShowFilterListDialog();

	void	Init(int globalPage ,GUIFilterListContainer &_FList);

private slots:
    void on_pushButtonClose_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowFilterListDialog *ui;
};

#endif // SHOWFILTERLISTDIALOG_H