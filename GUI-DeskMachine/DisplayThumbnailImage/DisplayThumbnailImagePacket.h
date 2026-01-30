/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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