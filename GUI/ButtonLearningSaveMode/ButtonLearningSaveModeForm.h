/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLearningSaveMode\ButtonLearningSaveModeForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef BUTTONLEARNINGSAVEMODEFORM_H
#define BUTTONLEARNINGSAVEMODEFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonLearningSaveModeForm.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class ButtonLearningSaveModeForm : public GUIFormBase
{
	Q_OBJECT

public:
	QString	Msg;
	QFont	CFont;

	bool	DefaultPushed;	ButtonLearningSaveModeForm(LayersBase *Base,QWidget *parent = 0);
	~ButtonLearningSaveModeForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	Ui::ButtonLearningSaveModeFormClass ui;

private slots:
	void on_toolButton_toggled(bool checked);
	void	ResizeAction();
};

//--------------------------------------------------------------------

class	GUICmdReqLearningSaveMode : public GUICmdPacketBase
{
public:

	GUICmdReqLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{		return true;	}
	virtual	bool	Save(QIODevice *f)	{		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLearningSaveMode : public GUICmdPacketBase
{
public:
	bool	Mode;

	GUICmdAckLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUISetLearningSaveMode : public GUICmdPacketBase
{
public:
	bool	Mode;

	GUISetLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};




#endif // BUTTONLEARNINGSAVEMODEFORM_H
