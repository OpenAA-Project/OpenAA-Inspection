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

#ifndef EXPANDMAININTAB_H
#define EXPANDMAININTAB_H

#include "expandmainintab_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"



class	ExpandMainInTab : public GUIFormBase
{
	Q_OBJECT

	int	SavedX1;
	int	SavedY1;
	int	SavedX2;
	int	SavedY2;

public:

	ExpandMainInTab(LayersBase *Base ,QWidget *parent);
	~ExpandMainInTab(void);

	virtual	void	Prepare(void)		override;
	virtual void	StartPage	(void)	override;
	virtual void	LeavePage	(void)	override;

private slots:
};
#endif // EXPANDMAININTAB_H