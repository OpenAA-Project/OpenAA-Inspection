/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCalcFinalization\ButtonCalcFinalization.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONCALCFINALIZATION_H
#define BUTTONCALCFINALIZATION_H

#include "buttoncalcfinalization_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonCalcFinalization : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonCalcFinalization(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	void	ExecuteByOnlyImage(void);
public slots:
	void	SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};

class	GUICmdReqCalcFinalization : public GUICmdPacketBase
{
public:

	GUICmdReqCalcFinalization(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqCalcFinalizationOnlyByImage: public GUICmdPacketBase
{
public:

	GUICmdReqCalcFinalizationOnlyByImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCALCFINALIZATION_H
