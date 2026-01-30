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


#ifndef BUTTONCLOSEONLY_H
#define BUTTONCLOSEONLY_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QColor>
#include <QFont>

class	ButtonCloseOnly : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ConfirmAfterEdit;

	ButtonCloseOnly(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

//=========================================================================

#endif // BUTTONCLOSEONLY_H