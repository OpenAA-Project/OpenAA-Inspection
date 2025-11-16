/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowBarCode\ShowBarCode.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWBARCODE_H
#define SHOWBARCODE_H

#include "showbarcode_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XGUIFormBase.h"
#include "XBCRInspection.h"
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

class	SignalOperandString;
class	SignalOperandInt;

class	ShowBarCode :public GUIFormBase
{
    Q_OBJECT

	QStringList		ResultBarcode;
	QPushButton		ManualButton;

	SignalOperandString *ioCurrentBarcode;

public:
	QFont	MessageSize;
	QColor	ColorBarcode;
	QColor	ColorNoBarcode;
	int32	SysNoCurrentBarcode;

	ShowBarCode(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private slots:
	virtual	void paintEvent ( QPaintEvent * event )	override;
	void	ResizeAction();
	 void on_pushButtonManual_clicked();
};


class	GUICmdReqBarcode : public GUICmdPacketBase
{
public:

	GUICmdReqBarcode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBarcode : public GUICmdPacketBase
{
public:
	QStringList	ResultBarcode;

	GUICmdAckBarcode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif // SHOWBARCODE_H
