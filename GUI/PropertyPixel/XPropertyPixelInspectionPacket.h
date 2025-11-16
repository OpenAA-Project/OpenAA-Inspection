/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\XPropertyPixelInspectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTPIXELINSPECTIONPACKET_H)
#define	XPROPERTPIXELINSPECTIONPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XPixelInspection.h"

class	GUICmdGeneratePixelInspection : public GUICmdPacketBase
{
public:
	GUICmdGeneratePixelInspection(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);
	~GUICmdGeneratePixelInspection(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdPixelInsMouseMove : public GUIDirectMessage
{
public:
	CmdPixelInsMouseMove(LayersBase *Base)
		:GUIDirectMessage(Base){};
public:
	int	GlobalX,GlobalY;
};

class	CmdPixelPickupArea : public GUIDirectMessage
{
public:
	CmdPixelPickupArea(LayersBase *Base)
		:GUIDirectMessage(Base){};
public:
	FlexArea	Area;
};

class	CmdGetPixelInsDataFromGlobalPoint: public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	int	CurrentIndex;
	PixelInsData	PData;
};
class	CmdGetPixelGenerateDataFromArea: public GUIDirectMessage
{
public:
	CmdGetPixelGenerateDataFromArea(LayersBase *Base)
		:GUIDirectMessage(Base){};
public:
	FlexArea	LocalArea;
	ColorLogic	ColorData;
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
