/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMonoBmpInAnyPageLayer\ButtonLoadMonoBmpInAnyPageLayer.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONLOADMONOBMPINANYPAGELAYER_H
#define BUTTONLOADMONOBMPINANYPAGELAYER_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonLoadMonoBmpInAnyPageLayer : public GUIFormBase
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

	ButtonLoadMonoBmpInAnyPageLayer(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	LoadFile(QString &FileName,int CPage ,int CLayer,bool iToMaster);

private:
	void	LoadFile(QString &FileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqLoadBmpInAnyPageLayer : public GUICmdPacketBase
{
public:
	QImage	Img;
	bool	ToMaster;
	int32	InPage;
	int32	InLayer;

	GUICmdReqLoadBmpInAnyPageLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdLoadBmpInAnyPageLayerPacket : public GUIDirectMessage
{
public:
	QString FileName;
	CmdLoadBmpInAnyPageLayerPacket(LayersBase *base):GUIDirectMessage(base){}
};


#endif // BUTTONLOADMONOBMPINANYPAGELAYER_H
