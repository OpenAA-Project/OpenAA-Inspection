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


#ifndef BUTTONCHANGEOVERLAP_H
#define BUTTONCHANGEOVERLAP_H

#include "XGUIFormBase.h"
#include <QToolButton>
#include <QColor>
#include <QFont>

class	ButtonChangeOverlap : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonChangeOverlap(LayersBase *Base ,QWidget *parent);
	~ButtonChangeOverlap(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};

#endif // BUTTONCHANGEOVERLAP_H