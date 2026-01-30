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


#ifndef GENERALLABEL_H
#define GENERALLABEL_H

#include "generallabel_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GeneralLabel : public GUIFormBase
{
	Q_OBJECT

	QLabel	Label;

public:
	QTranslator Translator;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlignAttr;

	enum	CAlignment{
		AlignLeft
		,AlignCenter
	};

	GeneralLabel(LayersBase *Base ,QWidget *parent);
	~GeneralLabel(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
};

#endif // GENERALLABEL_H