/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-Others\LoadImageInAnyPageLayer\LoadImageInAnyPageLayer.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LOADIMAGEINANYPAGELAYER_H
#define LOADIMAGEINANYPAGELAYER_H

//#include "loadimageinanypagelayer_global.h"


#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	LoadImageInAnyPageLayer : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ToMaster;
	int32	InPage;
	int32	InLayer;

	QString LoadedFileName;

	LoadImageInAnyPageLayer(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	LoadFile(QString &FileName,int CPage ,int CLayer,bool iToMaster);

private:
	void	LoadFile(QString &FileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSendLoadImageInAnyPagelayer : public GUICmdPacketBase
{
public:
	bool	ToMaster;
	int32	InLayer;

	int	TopY;
	int	YCount;
	int	Layer;
	int	iDotPerLine;
	QByteArray	Data;

	GUICmdSendLoadImageInAnyPagelayer(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdLoadImageInAnyPageLayerPacket : public GUIDirectMessage
{
public:
	QString FileName;
	CmdLoadImageInAnyPageLayerPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadImageInAnyPageLayerPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif // LOADIMAGEINANYPAGELAYER_H
