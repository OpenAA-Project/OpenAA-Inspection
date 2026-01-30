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


#ifndef BUTTONSELECTLIGHTDB_H
#define BUTTONSELECTLIGHTDB_H

#include "buttonselectlightdb_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSelectLightDB : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	int		SelectedLightID;

	ButtonSelectLightDB(LayersBase *Base ,QWidget *parent);
	~ButtonSelectLightDB(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdReqCurrentSelectedLightID : public GUIDirectMessage
{
public:
	int		SelectedLightID;

	CmdReqCurrentSelectedLightID(LayersBase *base):GUIDirectMessage(base)		{	SelectedLightID=-1;	}
	CmdReqCurrentSelectedLightID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	SelectedLightID=-1;	}
};


#endif // BUTTONSELECTLIGHTDB_H