/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadBmpJpg\ButtonLoadBmpJpg.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONLOADBMPJPG_H
#define BUTTONLOADBMPJPG_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonLoadBmpJpg : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ToMaster;
	int32	LoadedPage;

	QString LoadedFileName;

	ButtonLoadBmpJpg(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)								override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QString	LoadFileWithDialog(void);
	bool	LoadFile(QString &FileName,bool iToMaster);
	bool	LoadFile(QString &FileName ,QImage &Img);
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)							override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqLoadBmpJpg : public GUICmdPacketBase
{
public:
	QImage	Img;
	bool	ToMaster;

	GUICmdReqLoadBmpJpg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdLoadBmpJpgPacket : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBmpJpgPacketMaster : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgPacketMaster(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBmpJpgPacketTarget : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgPacketTarget(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBmpJpgPacketQImage : public GUIDirectMessage
{
public:
	QString FileName;
	QImage	Image;
	bool	Success;
	CmdLoadBmpJpgPacketQImage(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdLoadBmpJpgWithDialogPacket : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgWithDialogPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONLOADBMPJPG_H
