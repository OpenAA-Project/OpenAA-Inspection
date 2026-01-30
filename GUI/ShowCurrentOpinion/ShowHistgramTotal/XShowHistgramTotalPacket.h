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

#if	!defined(XShowHistgramTotalPacket_H)
#define	XShowHistgramTotalPacket_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XHistgramByParam.h"

//===========================================================================

class	HistgramTypeList : public NPList<HistgramTypeList>
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	int			HistID;
	QString		HistName;

	HistgramTypeList(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	HistgramTypeList	&operator=(HistgramTypeList &src);
	bool				operator==(HistgramTypeList &src);
};

class	HistgramTypeListContainer : public NPListPack<HistgramTypeList>
{
public:
	HistgramTypeListContainer(void){}

	HistgramTypeListContainer	&operator=(HistgramTypeListContainer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===========================================================================

class	GUICmdReqHistgramTypeList : public GUICmdPacketBase
{
public:
	GUICmdReqHistgramTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHistgramTypeList : public GUICmdPacketBase
{
public:
	HistgramTypeListContainer	HContainer;

	GUICmdSendHistgramTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeHistgramList(int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
class	LibraryItemList : public NPList<LibraryItemList>
{
public:
	int	LibID;
	int	ItemCount;

	LibraryItemList(void){	LibID=-1;	ItemCount=0;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LibraryItemList	&operator=(LibraryItemList &src);
};

class	LibraryItemListContainer : public NPListPack<LibraryItemList>
{
public:
	LibraryItemListContainer(void){}

	LibraryItemList	*GetLibraryItemList(int LibID);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	GUICmdReqHistgramLibrary : public GUICmdPacketBase
{
public:
	HistgramTypeList	PointData;

	GUICmdReqHistgramLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHistgramLibrary : public GUICmdPacketBase
{
public:
	LibraryItemListContainer	LibData;

	GUICmdSendHistgramLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeHistgramData(HistgramTypeList &Point,int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================
class	GUICmdReqHistgramTotalData : public GUICmdPacketBase
{
public:
	HistgramTypeList	PointData;
	LibraryItemList		LibData;

	GUICmdReqHistgramTotalData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHistgramTotalData : public GUICmdPacketBase
{
public:
	HistStepClass	Data;

	GUICmdSendHistgramTotalData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeHistgramData(HistgramTypeList &PointH,LibraryItemList &PointL,int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
#endif