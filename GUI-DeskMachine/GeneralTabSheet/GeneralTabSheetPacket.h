/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\GeneralTabSheet\GeneralTabSheetPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALTABSHEETPACKET_H
#define GENERALTABSHEETPACKET_H

#include "XGUIFormBase.h"

//===============================================================================
class	CmdExecNormalColor : public GUIDirectMessage
{
public:
	CmdExecNormalColor(LayersBase *base)
		:GUIDirectMessage(base){}

	~CmdExecNormalColor(){}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};

//===============================================================================
class	CmdExecNGSizeColor : public GUIDirectMessage
{
public:
	CmdExecNGSizeColor(LayersBase *base)
		:GUIDirectMessage(base){}

	~CmdExecNGSizeColor(){}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};

#endif