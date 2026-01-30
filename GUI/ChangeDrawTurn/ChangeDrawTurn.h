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


#ifndef CHANGEDRAWTURN_H
#define CHANGEDRAWTURN_H

#include <QListWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ChangeDrawTurn : public GUIFormBase
{
	Q_OBJECT

	QListWidget		List;	

public:
	ChangeDrawTurn(LayersBase *Base ,QWidget *parent = 0);
	~ChangeDrawTurn();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;
private:

private slots:
	void	ListClicked(const QModelIndex index);
	void	ResizeAction();
};
#endif // CHANGEDRAWTURN_H