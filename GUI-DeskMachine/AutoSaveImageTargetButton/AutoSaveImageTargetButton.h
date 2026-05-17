/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveImageTargetButton\SaveImageTargetButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef AUTOSAVEIMAGETARGETBUTTON_H
#define AUTOSAVEIMAGETARGETBUTTON_H

#include "autosaveimagetargetbutton_global.h"
#include <QLabel>
#include <QTranslator>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QLabel>
#include <QPushButton>
#include <QColor>
#include <QFont>
#include <QString>
#include <QIODevice>
#include <QByteArray>

class	AutoSaveImageTargetButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	QString		ButtonObjectName;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	DirectoryNameForSaving;

	AutoSaveImageTargetButton(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageTargetButton(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	bool SaveImage(QString FileName);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqSaveTargetImage : public GUICmdPacketBase
{
public:
	int	TopY;
	int	YCount;
	int	Layer;

	GUICmdReqSaveTargetImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveTargetImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveTargetImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // AUTOSAVEIMAGETARGETBUTTON_H
