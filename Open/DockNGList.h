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

#ifndef DOCKNGLIST_H
#define DOCKNGLIST_H

#include "ui_DockNGList.h"
#include "WindowBase.h"
#include "mtQTableWidget.h"
#include <QLineEdit>

class DockNGList : public WindowBase
{
//	Q_OBJECT

public:
	DockNGList(const QString &title=/**/"", QWidget *parent = 0);
	~DockNGList();

	void SetTitle(bool Enabled);
	void SetFont	(QFont &f);

	bool Save(QIODevice *file);
	bool Load(QIODevice *file);

	Ui::DockNGListClass ui;
	mtQTableWidget	*twNGList;
	QLineEdit		*leNGListTitle;

public slots:
	void selectNearNG(int x, int y);

private:
//	Ui::DockNGListClass ui;
};

#endif // DOCKNGLIST_H