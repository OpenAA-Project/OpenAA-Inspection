/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartProcessAgainButton\StartProcessAgainButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
