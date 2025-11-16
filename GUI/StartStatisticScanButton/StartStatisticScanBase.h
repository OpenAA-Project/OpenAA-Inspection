/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartStatisticScanButton\StartStatisticScanBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STARTSTATISTICSCANBASE_H
#define STARTSTATISTICSCANBASE_H

#include "XGUIFormBase.h"
#include <QToolButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class StartStatisticScanBase : public ServiceForLayers
{
	bool	Started;
public:
public:
	StartStatisticScanBase(LayersBase *Base);

	void	SlotToggledInside(bool checked);

protected:
	virtual	void OnIdleFunc(void);
	virtual	void OnIdleEnd(void){}
	virtual	void OnToggled(void){}

};
//==============================================================
class	GUICmdStartStatisticScan : public GUICmdPacketBase
{
public:
	int32		Layer;

	GUICmdStartStatisticScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdStartStatisticScan(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyStatisticScan : public GUICmdPacketBase
{
public:

	GUICmdReplyStatisticScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReplyStatisticScan(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif

