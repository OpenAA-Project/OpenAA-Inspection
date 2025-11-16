/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageMasterButton\LoadImageMasterButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LOADIMAGEMASTERBUTTON_H
#define LOADIMAGEMASTERBUTTON_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	LoadImageMasterButton : public GUIFormBase
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

	LoadImageMasterButton(LayersBase *Base ,QWidget *parent);
	~LoadImageMasterButton(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	bool LoadImage(QString FileName1);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdSendLoadMasterImage : public GUICmdPacketBase
{
public:
	int	Phase;
	int	TopY;
	int	YCount;
	int	Layer;
	int	iDotPerLine;
	QByteArray	Data;

	GUICmdSendLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // LOADIMAGEMASTERBUTTON_H
