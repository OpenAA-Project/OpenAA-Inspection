/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureButton\XCmdPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XCmdPacket)
#define	XCmdPacket

#include "XGUIPacketForDLL.h"

class	EntryPointBase;
class	LayersBase;

class	GUICmdPushed : public GUICmdPacketBase
{
public:
	QString	ImageType;	//"Master" "Target"

	GUICmdPushed(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif