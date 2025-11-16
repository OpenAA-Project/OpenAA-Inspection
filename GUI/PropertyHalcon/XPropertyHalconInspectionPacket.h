/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\XPropertyHalconInspectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYHALCONINSPECTIONPACKET_H)
#define	XPROPERTYHALCONINSPECTIONPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XHalconInspection.h"

class	GUICmdGenerateHalconInspection : public GUICmdPacketBase
{
public:
	GUICmdGenerateHalconInspection(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateHalconInspection(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdHalconInsMouseMove : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
};

class	CmdGetHalconInsDataFromGlobalPoint: public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	int	CurrentIndex;
//	HalconInsData	PData;
};

class	CmdAddItem : public GUIDirectMessage
{
public:
};

class	CmdDelItem : public GUIDirectMessage
{
public:
	int	CurrentIndex;
};

#endif
