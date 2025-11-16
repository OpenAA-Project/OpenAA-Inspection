/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadAlgorithmWithMachine\LoadAlgorithmWithMachine.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef LOADALGORITHMWITHMACHINE_H
#define LOADALGORITHMWITHMACHINE_H

#include "loadalgorithmwithmachine_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonLoadAlgorithmWithMachine : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	ButtonLoadAlgorithmWithMachine(LayersBase *Base ,QWidget *parent);
	~ButtonLoadAlgorithmWithMachine(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


//============================================================================================

class	GUICmdWriteAlgorithmDataWithMachine : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QBuffer	Data;

	GUICmdWriteAlgorithmDataWithMachine(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // LOADALGORITHMWITHMACHINE_H
