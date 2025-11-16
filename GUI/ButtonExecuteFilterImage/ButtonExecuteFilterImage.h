/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExecuteFilterImage\ButtonExecuteFilterImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONEXECUTEFILTERIMAGE_H
#define BUTTONEXECUTEFILTERIMAGE_H


#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonExecuteFilterImage : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	Mastered;

	ButtonExecuteFilterImage(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqExecuteFilterImage : public GUICmdPacketBase
{
public:
	bool	Mastered;

	GUICmdReqExecuteFilterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONEXECUTEFILTERIMAGE_H
