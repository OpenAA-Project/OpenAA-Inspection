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

#ifndef DOCKMASTERWHOLE2_H
#define DOCKMASTERWHOLE2_H

#include "ui_DockMasterWhole2.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockMasterWhole2 : public WindowBase
{
//	Q_OBJECT

public:
	DockMasterWhole2(const QString &title=/**/"", QWidget *parent = 0);
	~DockMasterWhole2();

	void	SetTitle(bool Enabled);

	Ui::DockMasterWhole2Class ui;
	QLineEdit	*leMasterImage2Title;

private:
//	Ui::DockMasterWhole2Class ui;
};

#endif // DOCKMASTERWHOLE2_H