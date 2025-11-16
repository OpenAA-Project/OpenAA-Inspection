/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\DisplayThumbnailImage\DisplayThumbnailImagePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef DISPLAYTHUMBNAILIMAGEPACKET_H
#define DISPLAYTHUMBNAILIMAGEPACKET_H

#include "XGUIFormBase.h"
#include "XResult.h"

//===============================================================================
class	CmdSetNGInformation : public GUIDirectMessage
{
public:
	int			ErrorGroupTableCount;
	ErrorGroup	**ErrorGroupTable;
	int			NGWidth,NGHeight;

	CmdSetNGInformation(LayersBase *base)
		:GUIDirectMessage(base)
	{
		ErrorGroupTableCount=0;
		ErrorGroupTable		=NULL;;
		NGWidth	=NGHeight	=0;
	}

	~CmdSetNGInformation()
	{
		delete	[]ErrorGroupTable;
	}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};

//===============================================================================
class	CmdSetThumbnailInformation : public GUIDirectMessage
{
public:
	int	ThumbnailCount;

	CmdSetThumbnailInformation(LayersBase *base)
		:GUIDirectMessage(base)
	{
		ThumbnailCount=1;
	}

	~CmdSetThumbnailInformation(){}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};

//===============================================================================
class	CmdSetCurrentRow : public GUIDirectMessage
{
public:
	int	CurrentRow;

	CmdSetCurrentRow(LayersBase *base)
		:GUIDirectMessage(base)
	{
		CurrentRow=-1;
	}

	~CmdSetCurrentRow(){}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};

//===============================================================================
class	CmdShowThumbnailDialog : public GUIDirectMessage
{
public:
	int	CurrentRow;

	CmdShowThumbnailDialog(LayersBase *base)
		:GUIDirectMessage(base)
	{
		CurrentRow=-1;
	}

	~CmdShowThumbnailDialog(){}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};
/*
//===============================================================================
class	CmdSetCurrentFocus : public GUIDirectMessage
{
public:
	CmdSetCurrentFocus(LayersBase *base)
		:GUIDirectMessage(base){}

	~CmdSetCurrentFocus(){}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};
*/
#endif