/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonRewindInspection\ButtonRewindInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef BUTTONREWINDINSPECTION_H
#define BUTTONREWINDINSPECTION_H

#include "buttonrewindinspection_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	ButtonRewindInspection : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;


	ButtonRewindInspection(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

public slots:
	void	SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

//-------------------------------------------------------------------------

class	GUICmdRewindInspection : public GUICmdPacketBase
{
public:

	GUICmdRewindInspection(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONREWINDINSPECTION_H
