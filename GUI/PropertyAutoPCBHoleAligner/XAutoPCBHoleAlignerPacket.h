/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoPCBHoleAligner\XAutoPCBHoleAlignerPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XAutoPCBHoleAlignerPACKET_H
#define XAutoPCBHoleAlignerPACKET_H

#include "XGUIFormBase.h"
#include "ui_PropertyAutoPCBHoleAlignerForm.h"
#include "XAutoPCBHoleAligner.h"


class	GUICmdCreateAutoPCBHoleAligner : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;

	GUICmdCreateAutoPCBHoleAligner(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAutoPCBHoleAlignerInfo : public GUICmdPacketBase
{
public:
	GUICmdReqAutoPCBHoleAlignerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAutoPCBHoleAlignerInfo : public GUICmdPacketBase
{
public:
	AAHoleInfos		AAInfoData;

	GUICmdSendAutoPCBHoleAlignerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	CmdAutoPCBHoleAlignerExecuteDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;

	CmdAutoPCBHoleAlignerExecuteDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSetAutoPCBHoleAlignertLibColor : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	int			LibID;

	GUICmdSetAutoPCBHoleAlignertLibColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//===============================================================================
class	CmdSetAutoPCBHoleAlignerShowingState : public GUIDirectMessage
{
public:
	bool	ModeShowingHole;
	bool	ModeShowingFringe;

	IntList	ShowingLibIDs;

	CmdSetAutoPCBHoleAlignerShowingState(LayersBase *base)
		:GUIDirectMessage(base)
	{
		ModeShowingHole		=true;
		ModeShowingFringe	=false;
	}
};

#endif