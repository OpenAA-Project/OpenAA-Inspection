/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPacketAlignmentFlexArea.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPACKETAlignmentFlexArea_H)
#define	XPACKETAlignmentFlexArea_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XIntClass.h"
//#include "XDisplayImage.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XYCross.h"


class	LibraryEfectivity : public NPList<LibraryEfectivity>
{
public:
	int32	LibID;
	bool	IncludedInMask;

	LibraryEfectivity(void);
	LibraryEfectivity(int libID ,bool mask):LibID(libID),IncludedInMask(mask){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LibraryEfectivityContainer : public NPListPack<LibraryEfectivity>
{
public:
	LibraryEfectivityContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsIncluded(int LibID);
};

//他のスレーブで限定マスクでライブラリを使用しているかどうか
class	SlaveCommReqLibraryInMaskOfBlock : public DirectCommPacketBase
{
public:
	IntList	UsedLibraries;

	SlaveCommReqLibraryInMaskOfBlock(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckLibraryInMaskOfBlock : public DirectCommPacketBase
{
public:
	LibraryEfectivityContainer	UsedLibraries;

	SlaveCommAckLibraryInMaskOfBlock(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	CmdIsModeItemEditingPacket : public GUIDirectMessage
{
public:
	enum{
		_ItemMode			=0
		,_AreaMode			=1
	}ItemMode;

	CmdIsModeItemEditingPacket(LayersBase *base):GUIDirectMessage(base)
			{	ItemMode=_ItemMode;	}
	CmdIsModeItemEditingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ItemMode=_ItemMode;	}
};
#endif