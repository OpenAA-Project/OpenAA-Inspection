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

#ifndef GENERALMENU_H
#define GENERALMENU_H

#include "generalmenu_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QMenuBar>

class	GeneralMenu : public GUIFormBase
{
	Q_OBJECT

	QMenuBar	MenuBar;
	NPListPack<MenuInfoContainer>	AllMenus;
public:
	GeneralMenu(LayersBase *Base ,QWidget *parent);
	~GeneralMenu(void);

	virtual	void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	TabChanged(void)	override;

	virtual void	StartPage	(void)	override;
};


#endif // GENERALMENU_H