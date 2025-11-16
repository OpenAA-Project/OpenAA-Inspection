/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveAlgorithm\ButtonSaveAlgorithm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSAVEALGORITHM_H
#define BUTTONSAVEALGORITHM_H

#include "buttonsavealgorithm_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSaveAlgorithm : public GUIFormBase
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
	int32	WaitingMilisec;

	ButtonSaveAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonSaveAlgorithm(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 

	bool	SaveAlgo(const QString &AlgoRoot ,const QString &AlgoName
					,QIODevice *Buff);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqAlgorithmData : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;


	GUICmdReqAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmData : public GUICmdPacketBase
{
public:
	QBuffer	Data;

	GUICmdSendAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class CmdReqAlgorithmData: public GUIDirectMessage
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QIODevice	*Data;
	bool	RetSuccessful;

	CmdReqAlgorithmData(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqAlgorithmData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};


#endif // BUTTONSAVEALGORITHM_H
