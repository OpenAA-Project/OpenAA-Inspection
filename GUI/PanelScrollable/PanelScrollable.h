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

#ifndef PANELSCROLLABLE_H
#define PANELSCROLLABLE_H

#include "panelscrollable_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include <QScrollBar>
#include <QColor>

class	PanelScrollable : public GUIFormBase
{
	Q_OBJECT

	QScrollBar	HBar;
public:
	QColor	BaseCol;
	bool	HBarTop;

	PanelScrollable(LayersBase *Base ,QWidget *parent);
	~PanelScrollable(void);

	virtual	void	Prepare(void) override;
	virtual	void	ReadyParam(void) override;
public slots:
	void	ResizeAction();
};

#endif // PANELSCROLLABLE_H