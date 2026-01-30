/*
 * Copyright (C) 2012
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

#if	!defined(XGUIPIECEFORREVIEW_H)
#define	XGUIPIECEFORREVIEW_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPieceForReview.h"
#include "XColorSpace.h"
#include "XAlgorithmLibrary.h"
#include "XGUIPacketForDLL.h"
#include "XPieceForReviewPacket.h"


class	CmdPieceForReviewDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	CmdPieceForReviewDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdPieceForReviewDrawAttr : public GUIDirectMessage
{
public:
	PieceForReviewDrawAttr	*Attr;

	CmdPieceForReviewDrawAttr(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddItemPieceForReview : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	GUICmdAddItemPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemListPieceForReview : public GUICmdPacketBase
{
public:
	GUICmdReqItemListPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemListPieceForReview : public GUICmdPacketBase
{
public:
	ItemsContainerPieceForReview	ListData;

	GUICmdAckItemListPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeList(int localPage);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//======================================================================================

class	GUICmdChangeItemPieceForReview : public GUICmdPacketBase
{
public:
	int			ItemID;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	GUICmdChangeItemPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif