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


#ifndef STARTPROCESSAGAINBUTTON_H
#define STARTPROCESSAGAINBUTTON_H

#include "startprocessagainbutton_global.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	StartProcessAgainButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

	int	RepeatCount_StartByInspection;
	int	RepeatCount_Captured;
	int	RepeatCount_PreAlignent;
	int	RepeatCount_Alignent;
	int	RepeatCount_PreProcessing;
	int	RepeatCount_Processing;
	int	RepeatCount_PostProcessing;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ExecInitialAfterEdit;
	int32	MaxInspectMilisec;
	bool	OutputResult;
	bool	ForceBindAllPhase;
	bool	NowOnRunning;

	StartProcessAgainButton(LayersBase *Base ,QWidget *parent);
	~StartProcessAgainButton(void);

	virtual void	Prepare(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

public slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


class	CmdReqPush : public GUIDirectMessage
{
public:
	CmdReqPush(LayersBase *base):GUIDirectMessage(base){	}
	CmdReqPush(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	}
};

#endif // STARTPROCESSAGAINBUTTON_H