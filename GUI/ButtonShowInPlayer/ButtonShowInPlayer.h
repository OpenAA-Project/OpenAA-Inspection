/*
 * Copyright (C) 2024
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

#pragma once

#include "buttonshowinplayer_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonShowInPlayer : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	int64	LastShownInspectionID;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIcon;
	QString	GUIInst;

	ButtonShowInPlayer(LayersBase *Base ,QWidget *parent);
	~ButtonShowInPlayer(void);
	virtual void	Prepare(void)	override;

	void	ShowInPlayer(int64 shownInspectionID)	override;

public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};