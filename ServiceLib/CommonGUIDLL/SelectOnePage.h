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

#ifndef SELECTONEPAGE_H
#define SELECTONEPAGE_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
    class SelectOnePage;
}

class SelectOnePage : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectOnePage(LayersBase *pbase ,QWidget *parent = 0);
	explicit SelectOnePage(LayersBase *pbase ,const IntList &pageList,QWidget *parent = 0);
    ~SelectOnePage();

	int	SelectedPage;
private slots:
    void on_listWidgetPage_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();

private:
    Ui::SelectOnePage *ui;

	IntList		PageList;
};

#endif // SELECTONEPAGE_H