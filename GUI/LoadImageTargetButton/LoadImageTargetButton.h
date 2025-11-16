/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageTargetButton\LoadImageTargetButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LOADIMAGETARGETBUTTON_H
#define LOADIMAGETARGETBUTTON_H

#include "loadimagetargetbutton_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	LoadImageTargetButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	QString		LastSelectedFile;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	SkipPage;

	LoadImageTargetButton(LayersBase *Base ,QWidget *parent);
	~LoadImageTargetButton(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	bool LoadImageFile(QString FileName);
	bool LoadImageFile	(QIODevice *f);
	bool LoadImageFileV3(QIODevice *f);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSendLoadTargetImage : public GUICmdPacketBase
{
public:
	int	Phase;
	int	TopY;
	int	YCount;
	int	Layer;
	int	iDotPerLine;
	QByteArray	Data;

	GUICmdSendLoadTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdFinalizeLoadTargetImage : public GUICmdPacketBase
{
public:
	int	Layer;

	GUICmdFinalizeLoadTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqLoadImage : public GUIDirectMessage
{
public:
	QString	FileName;
	bool	Success;

	CmdReqLoadImage(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLoadImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

	
#endif // LOADIMAGETARGETBUTTON_H
