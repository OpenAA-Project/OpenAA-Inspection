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

#ifndef DOCKMASTERWHOLE1_H
#define DOCKMASTERWHOLE1_H

#include "ui_DockMasterWhole1.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockMasterWhole1 : public WindowBase
{
//	Q_OBJECT

public:
	DockMasterWhole1(const QString &title=/**/"", QWidget *parent = 0);
	~DockMasterWhole1();

	void	SetTitle(bool Enabled);

	Ui::DockMasterWhole1Class ui;
	QLineEdit	*leMasterImage1Title;

private:
//	Ui::DockMasterWhole1Class ui;
};

#endif // DOCKMASTERWHOLE1_H