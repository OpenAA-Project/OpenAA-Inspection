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

#if	!defined(XPIECEFORREVIEWPACKET_H)
#define	XPIECEFORREVIEWPACKET_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPieceForReview.h"
#include "XAlgorithmLibrary.h"
#include "XGUIPacketForDLL.h"


class	ItemsListPieceForReview : public NPList<ItemsListPieceForReview>
{
public:
	int			GlobalPage;
	int			ItemID;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;
	int			X1,Y1,X2,Y2;

	ItemsListPieceForReview(void);

	ItemsListPieceForReview	&operator=(ItemsListPieceForReview &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ItemsContainerPieceForReview : public NPListPack<ItemsListPieceForReview>
{
public:
	ItemsContainerPieceForReview(void){}

	ItemsContainerPieceForReview	&operator+=(ItemsContainerPieceForReview &src);
	ItemsContainerPieceForReview	&operator=(ItemsContainerPieceForReview &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//====================================================================================
class	CmdAddItemPieceForReview : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	CmdAddItemPieceForReview(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdMakePieceForReviewList : public GUIDirectMessage
{
public:
	ItemsContainerPieceForReview	*ListData;

	CmdMakePieceForReviewList(LayersBase *base):GUIDirectMessage(base){	ListData=NULL;	}
};

class	CmdChangeItemPieceForReview : public GUIDirectMessage
{
public:
	int			ItemID;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	CmdChangeItemPieceForReview(LayersBase *base):GUIDirectMessage(base){}
};

#endif