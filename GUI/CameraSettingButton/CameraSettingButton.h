/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CameraSettingButton\CameraSettingButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef CAMERASETTINGBUTTON_H
#define CAMERASETTINGBUTTON_H

#include "camerasettingbutton_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	CameraSettingButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	CameraSettingButton(LayersBase *Base ,QWidget *parent);
	~CameraSettingButton(void);
	virtual void	Prepare(void)							override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)						override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


class	CmdOpenCameraSetting: public GUIDirectMessage
{
public:
	CmdOpenCameraSetting(LayersBase *base):GUIDirectMessage(base){}
};

#endif // CAMERASETTINGBUTTON_H
