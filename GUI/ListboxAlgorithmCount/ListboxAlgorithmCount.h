/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxAlgorithmCount\ListboxAlgorithmCount.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTBOXALGORITHMCOUNT_H
#define LISTBOXALGORITHMCOUNT_H

#include "listboxalgorithmcount_global.h"
#include <QTableWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ListboxAlgorithmCount : public GUIFormBase
{
	Q_OBJECT

	QTableWidget	MainList;
public:

	ListboxAlgorithmCount(LayersBase *Base ,QWidget *parent);
	~ListboxAlgorithmCount(void);
	
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
	void	ResizeAction();
};

//===============================================================================


class	GUICmdReqAlgorithmItemCount : public GUICmdPacketBase
{
public:

	GUICmdReqAlgorithmItemCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmItemCount : public GUICmdPacketBase
{
public:
	NPListPack<AlgorithmItemCountInBase>	CountInBases;

	GUICmdSendAlgorithmItemCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	void	MakeLists(int localPage ,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // LISTBOXALGORITHMCOUNT_H
