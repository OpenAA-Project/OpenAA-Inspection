/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveImageMasterButton\SaveImageMasterButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef AUTOSAVEIMAGEMASTERBUTTON_H
#define AUTOSAVEIMAGEMASTERBUTTON_H

#include "autosaveimagemasterbutton_global.h"
#include <QLabel>
#include <QTranslator>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QIODevice>
#include <QByteArray>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	AutoSaveImageMasterButton : public GUIFormBase
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

	AutoSaveImageMasterButton(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageMasterButton(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	bool SaveImage(QString FileName);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqSaveMasterImage : public GUICmdPacketBase
{
public:
	int	TopY;
	int	YCount;
	int	Layer;

	GUICmdReqSaveMasterImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveMasterImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveMasterImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // AUTOSAVEIMAGEMASTERBUTTON_H
