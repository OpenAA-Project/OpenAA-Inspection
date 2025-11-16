/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelSaveImage\PanelSaveImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PANELSAVEIMAGE_H
#define PANELSAVEIMAGE_H

#include "panelsaveimage_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QIODevice>
#include <QFont>

class	PanelSaveImage :public GUIFormBase
{
    Q_OBJECT

	QListWidget	MainList;
public:
	QFont	MessageSize;

	PanelSaveImage(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
	void	ResizeAction();
	void itemDoubleClicked ( QListWidgetItem * item );
};


class	GUICmdChangeCurrentFolder : public GUICmdPacketBase
{
public:
	int		FolderNumber;

	GUICmdChangeCurrentFolder(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // PANELSAVEIMAGE_H
