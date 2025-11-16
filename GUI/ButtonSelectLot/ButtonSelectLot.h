/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLot\ButtonSelectLot.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSELECTLOT_H
#define BUTTONSELECTLOT_H

#include "buttonselectlot_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSelectLot : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	LoadLastID;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxLines;

	ButtonSelectLot(LayersBase *Base ,QWidget *parent);
	~ButtonSelectLot(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	void	CreateNewLot(const QString &LotName,bool Synchronized);
	void	CreateNewLot(const QString &LotName,const QString &LotID,bool Synchronized);

	virtual	void	RxSync(QByteArray &f)	override;
private:
	void SetLotToSystem(int iLotAutoCount
						,QString iLotID
						,QString iLotName);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdSelectLot : public GUIDirectMessage
{
public:
	CmdSelectLot(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSelectLot : public GUICmdPacketBase
{
public:
	int			LotAutoCount;
	QString		LotID;
	QString		LotName;
	XDateTime	CurrentInspectTime;
	ExecuteInspectBase::AutoRepeatMode	AMode;

	GUICmdSelectLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONSELECTLOT_H
