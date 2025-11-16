/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowNGCount\ShowNGCount.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWNGCOUNT_H
#define SHOWNGCOUNT_H

#include "showngcount_global.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ShowNGCount : public GUIFormBase
{
	Q_OBJECT

	QLabel	LabelMsg;
	QLabel	LabelCount;
	QLabel	LabelOkNg;

public:
	QString	Msg;
	QColor	MsgColor;
	QColor	CountColor;
	QColor	OkNgColor;

	ShowNGCount(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;

private slots:
	void	ResizeAction();
};


class	GUICmdReqNGCount : public GUICmdPacketBase
{
public:
	int64 ShownInspectionID;

	GUICmdReqNGCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGCount : public GUICmdPacketBase
{
public:
	int64	NGCount;

	GUICmdSendNGCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SHOWNGCOUNT_H
