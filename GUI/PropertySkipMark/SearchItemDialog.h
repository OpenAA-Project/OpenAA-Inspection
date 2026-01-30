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

#ifndef SEARCHITEMDIALOG_H
#define SEARCHITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class SearchItemDialog;
}

class	LibIDList : public NPList<LibIDList>
{
public:
	int		LibID;
	QString	LibName;

	LibIDList(void){	LibID=-1;	}
};

class	LibIDContainer : public NPListPack<LibIDList>
{
public:
	LibIDContainer(void){}

	LibIDList	*IsInclude(int LibID);
};


class SearchItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int GlobalPage;
	int Layer;
	AlgorithmBase *ABase;
	ItemInfoContainer	ItemList;
	LibIDContainer		LibIDStock;
public:
    explicit SearchItemDialog(LayersBase *Base,AlgorithmBase *ABase,int GlobalPage ,int _Layer,QWidget *parent = 0);
    ~SearchItemDialog();

	int	ItemID;
private slots:
    void on_pushButtonSortByID_clicked();
    void on_pushButtonSortByName_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonSortByLibID_clicked();

private:
    Ui::SearchItemDialog *ui;

	void	ShowList(void);
};

#endif // SEARCHITEMDIALOG_H