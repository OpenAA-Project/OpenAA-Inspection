/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAppendAlgorithm\ButtonAppendAlgorithm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONAPPENDALGORITHM_H
#define BUTTONAPPENDALGORITHM_H

#include "buttonappendalgorithm_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonAppendAlgorithm : public GUIFormBase
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

	ButtonAppendAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonAppendAlgorithm(void);
	
	virtual void	Prepare(void)	override;

	bool ExecuteLoad(QIODevice &F
				  ,QString _AlgorithmRoot ,QString _AlgorithmName);
				  
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


//============================================================================================

class	GUICmdWriteAlgorithmData : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QBuffer	Data;

	GUICmdWriteAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUIAckWriteAlgorithmData : public GUICmdPacketBase
{
public:
	bool	Ok;
	QString	ErrorMsg;

	GUIAckWriteAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	ExecuteAppendAlgorithm : public GUIDirectMessage
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QString	FileName;

	ExecuteAppendAlgorithm(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONAPPENDALGORITHM_H
