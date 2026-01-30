/*
 * Copyright (C) 2022
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

#ifndef SELECTDELIVERED_H
#define SELECTDELIVERED_H

#include "selectdelivered_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include <QEvent>
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"



class	SelectDelivered: public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored		*Buttons[256];
public:
	QStringList				AttrMessages;			
	int						ButtonCount;
	QColor	CharColor;
	QFont	CFont;


	SelectDelivered(LayersBase *Base ,QWidget *parent);
	~SelectDelivered();

	virtual void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

#endif // SELECTDELIVERED_H