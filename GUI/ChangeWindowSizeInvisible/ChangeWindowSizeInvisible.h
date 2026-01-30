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

#ifndef CHANGEWINDOWSIZEINVISIBLE_H
#define CHANGEWINDOWSIZEINVISIBLE_H

#include "changewindowsizeinvisible_global.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

class	ChangeWindowSizeInvisible : public GUIFormBase
{
	Q_OBJECT

	int		CurrentMaxSizeW;
	int		CurrentMaxSizeH;
public:

	bool	MaximizeWindowOnStartPage;
	bool	ReturnWindowSizewOnStartPage;
	bool	MaximizeWindowOnLeavePage;
	bool	ReturnWindowSizewOnLeavePage;

	ChangeWindowSizeInvisible(LayersBase *Base ,QWidget *parent);
	~ChangeWindowSizeInvisible(void);

	virtual void	Prepare(void)	override;

	virtual void	StartPage	(void)	override;
	virtual void	LeavePage	(void)	override;


private slots:

};
#endif // CHANGEWINDOWSIZEINVISIBLE_H