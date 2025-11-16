/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveAlgorithmWithMachine\SaveAlgorithmWithMachine.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SAVEALGORITHMWITHMACHINE_H
#define SAVEALGORITHMWITHMACHINE_H

#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSaveAlgorithmWithMachine : public GUIFormBase
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

	ButtonSaveAlgorithmWithMachine(LayersBase *Base ,QWidget *parent);
	~ButtonSaveAlgorithmWithMachine(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqAlgorithmDataWithMachine : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;


	GUICmdReqAlgorithmDataWithMachine(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmDataWithMachine : public GUICmdPacketBase
{
public:
	QBuffer	Data;

	GUICmdSendAlgorithmDataWithMachine(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // SAVEALGORITHMWITHMACHINE_H
