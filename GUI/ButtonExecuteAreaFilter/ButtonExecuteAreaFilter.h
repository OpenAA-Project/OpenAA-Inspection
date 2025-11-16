/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExecuteAreaFilter\ButtonExecuteAreaFilter.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONEXECUTEAREAFILTER_H
#define BUTTONEXECUTEAREAFILTER_H

#include "buttonexecuteareafilter_global.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonExecuteAreaFilter : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonExecuteAreaFilter(LayersBase *Base ,QWidget *parent);
	~ButtonExecuteAreaFilter(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdExecuteAreaFilterPushed : public GUICmdPacketBase
{
public:

	GUICmdExecuteAreaFilterPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdExecuteAreaFilterReplied : public GUICmdPacketBase
{
public:

	CmdExecuteAreaFilterReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONEXECUTEAREAFILTER_H
