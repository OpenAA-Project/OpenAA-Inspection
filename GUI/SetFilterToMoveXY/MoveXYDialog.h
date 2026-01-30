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

#ifndef MOVEXYDIALOG_H
#define MOVEXYDIALOG_H

#include <QDialog>
#include "NList.h"
#include "XServiceForLayers.h"

namespace Ui {
class MoveXYDialog;
}

class	MoveXYList : public NPList<MoveXYList>
{
public:
	int		GlobalPage;
	int		Dx,Dy;

	MoveXYList	&operator=(MoveXYList &src);
};

class MoveXYDialog : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

	NPListPack<MoveXYList>	SavedMoveXYListContainer;
public:
	NPListPack<MoveXYList>	MoveXYListContainer;

	explicit MoveXYDialog(LayersBase *pbase,QWidget *parent = 0);
    ~MoveXYDialog();

	void	Init(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSet_clicked();

private:
    Ui::MoveXYDialog *ui;
};



#endif // MOVEXYDIALOG_H