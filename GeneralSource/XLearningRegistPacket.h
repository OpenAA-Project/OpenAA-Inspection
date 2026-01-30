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

#if	!defined(XLEARNINGREGISTPACKET_H)
#define	XLEARNINGREGISTPACKET_H

#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "NList.h"
#include <QIODevice>
#include <QString>
#include "XTypeDef.h"
#include "XDataAlgorithm.h"
#include "XDateTime.h"
#include "XAlgorithmLibrary.h"

class	GUICmdReqPartialImageForLearn : public GUICmdPacketBase
{
public:
	int			LocalX1,LocalY1;
	int			LocalX2,LocalY2;
	int			LocalPage;
	int			Layer;
	XDateTime	CreatedTime;
	bool		Mastered;

	GUICmdReqPartialImageForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckPartialImageForLearn : public GUICmdPacketBase
{
public:
	QByteArray	IData;
	bool		ImageOK;

	GUICmdAckPartialImageForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}

	void	BuildData(int LocalX1,int LocalY1,int LocalX2,int LocalY2
					,int LocalPage,int Layer
					,bool Mastered);
};

class	GUICmdReqPartialItems: public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	AlgorithmLibraryListContainer LibList;
	QString		AlgoRoot;
	QString		AlgoName;
	int			AddedX,AddedY;
	bool		OkMode;

	GUICmdReqPartialItems(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAckPartialItems: public GUICmdPacketBase
{
public:
	ItemDataListWithIDContainer	CData;

	GUICmdAckPartialItems(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);

	void	BuildData(AlgorithmInPageRoot	*P
					,FlexArea &LocalArea
					,AlgorithmLibraryListContainer &LibList
					,int AddedX,int AddedY
					,bool OKMode);
};

class	GUICmdReqItemSize: public GUICmdPacketBase
{
public:
	int		LocalX,LocalY;

	GUICmdReqItemSize(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAckItemSize: public GUICmdPacketBase
{
public:
	int		AreaMinX,AreaMinY;
	int		AreaMaxX,AreaMaxY;

	GUICmdAckItemSize(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdRegImageForLearn : public GUICmdPacketBase
{
public:
	int			LocalX1,LocalY1;
	int			LocalX2,LocalY2;
	XDateTime	CreatedTime;

	GUICmdRegImageForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqAlignmentForLearn: public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqAlignmentForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAckAlignmentForLearn: public GUICmdPacketBase
{
public:
	int	ShiftX ,ShiftY;

	GUICmdAckAlignmentForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqLearningMenu: public GUICmdPacketBase
{
public:
	int	LibType;

	GUICmdReqLearningMenu(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAckLearningMenu: public GUICmdPacketBase
{
public:
	LearningMenu	LearningMenuDim[100];
	int32			MenuDimNumb;

	GUICmdAckLearningMenu(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqItemIData: public GUICmdPacketBase
{
public:
	AlgorithmItemIndex	Index;
	int			AddedX,AddedY;
	bool		OkMode;

	GUICmdReqItemIData(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckItemIData: public GUICmdPacketBase
{
public:
	QByteArray	IData;

	GUICmdAckItemIData(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif
