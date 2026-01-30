/*
 * Copyright (C) 2018
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

#ifndef SETECTSEARCHITEMDIALOG_H
#define SETECTSEARCHITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SetectSearchItemDialog;
}
class	AlgorithmBase;

class SetectSearchItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	AlgorithmBase *Algo;
	int GlobalPage;
	ListPageLayerIDLibNamePack	ItemIDList;
public:
    explicit SetectSearchItemDialog(AlgorithmBase *Algo ,ListPageLayerIDLibNamePack &itemIDList ,QWidget *parent);
    ~SetectSearchItemDialog();

	ListPageLayerIDPack	SelectedItems;
private slots:
    void on_pushButtonSortByID_clicked();
    void on_pushButtonSortByLibID_clicked();
    void on_pushButtonSortByName_clicked();
    void on_ButtonSelectAndView_clicked();
    void on_ButtonOnlyView_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonSortByItemID_clicked();

private:
    Ui::SetectSearchItemDialog *ui;

	void	ShowList(void);
	void	SelectOnes(void);
};

#endif // SETECTSEARCHITEMDIALOG_H