/*
 * Copyright (C) 2021
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

#ifndef DALSALOADIMAGE_H
#define DALSALOADIMAGE_H

#include "dalsaloadimage_global.h"
#include <QPushButton>
#include <QTranslator>
#include <QToolButton>
#include <QColor>
#include <QFont>
#include <QString>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	DalsaLoadImage : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	DalsaLoadImage(LayersBase *Base ,QWidget *parent);
	~DalsaLoadImage(void);
	virtual void	Prepare(void);

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // DALSALOADIMAGE_H