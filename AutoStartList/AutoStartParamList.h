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

#ifndef AUTOSTARTPARAMLIST_H
#define AUTOSTARTPARAMLIST_H

#include <QDialog>
#include "ui_AutoStartParamList.h"
#include "XAutoStart.h"

class AutoStartParamList : public QDialog
{
	Q_OBJECT

public:
	AutoStartParamList(AutoStartExeList &List ,QWidget *parent = 0);
	~AutoStartParamList();

	AutoStartExeList	TmpData;

private:
	Ui::AutoStartParamListClass ui;
	void	ShowList(void);

private slots:
	void on_pushButtonOK_clicked();
    void on_pushButtonAdd_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
};

#endif // AUTOSTARTPARAMLIST_H