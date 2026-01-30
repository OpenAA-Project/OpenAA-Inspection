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

#if	!defined(XARArrangePacket_H)
#define	XARArrangePacket_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XLearningRegist.h"
#include "XARArrange.h"
#include "XDateTime.h"

//===========================================================================

class	ARItemList : public NPList<ARItemList>
{
public:
	int64						ItemID;
	XDateTime					CreatedTime;
	ARArrangeItem::ARResult		Result;
	DualIntClass				Position;

	ARItemList(void){}
	ARItemList(ARArrangeItem *p);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	
	ARItemList	&operator=(ARItemList &src);
};

class	ARItemListContainer : public NPListPack<ARItemList>
{
public:
	ARItemListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	ARItemListContainer	&operator+=(ARItemListContainer &src);
};

//===========================================================================

class	GUICmdReqARLearningList : public GUICmdPacketBase
{
public:
	GUICmdReqARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendARLearningList : public GUICmdPacketBase
{
public:
	LearningImagePointerContainer	LearningPointerContainer;

	GUICmdSendARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
class	GUICmdReqARArrangeList : public GUICmdPacketBase
{
public:
	XDateTime	CreatedTime;

	GUICmdReqARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendARArrangeList : public GUICmdPacketBase
{
public:
	ARItemListContainer		ItemContainer;

	GUICmdSendARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==================================================================================

class	GUICmdARArrangeDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	GUICmdARArrangeDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

//==================================================================================
class	GUICmdReqAddARArrange : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	XDateTime	CreatedTime;

	GUICmdReqAddARArrange(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqLearningThumnail : public GUICmdPacketBase
{
public:
	XDateTime	CreatedTime;
	int			ImageWidth;
	int			ImageHeight;

	GUICmdReqLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendLearningThumnail : public GUICmdPacketBase
{
public:
	QImage	*Img;

	GUICmdSendLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendLearningThumnail(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==================================================================================
#endif