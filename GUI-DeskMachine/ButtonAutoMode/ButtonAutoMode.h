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


#ifndef BUTTONAUTOMODE_H
#define BUTTONAUTOMODE_H

#include "buttonautomode_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButtonColored.h"
//#include "mtImageButtonColored.h"

class	ButtonAutoMode : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButtonColored	Button;
//	mtImageButtonColored	Button;

public:
	QColor	PushedColor;
	bool	IsNecessaryLot;

	ButtonAutoMode(LayersBase *Base ,QWidget *parent);
	~ButtonAutoMode(void);
	
	virtual void	Prepare(void)	override;
	QTranslator Translator;

public slots:
	void	SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

#endif // BUTTONAUTOMODE_H