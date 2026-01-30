/*
 * Copyright (C) 2023
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

#ifndef DOCKHISTORYLIST_H
#define DOCKHISTORYLIST_H

#include "ui_DockHistoryList.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockHistoryList : public WindowBase
{
//	Q_OBJECT

public:
	DockHistoryList(const QString &title=/**/"", QWidget *parent = 0);
	~DockHistoryList();

	void SetTitle(bool Enabled);
	void SetFont	(QFont &f);

	bool Save(QIODevice *file);
	bool Load(QIODevice *file);

	Ui::DockHistoryListClass ui;
	QLineEdit	*leHistoryListTitle;

private:
//	Ui::DockHistoryListClass ui;
};

#endif // DOCKHISTORYLIST_H