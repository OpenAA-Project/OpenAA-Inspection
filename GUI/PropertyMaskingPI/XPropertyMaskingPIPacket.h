/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMaskingPI\XPropertyMaskingPIPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYMASKINGPIPACKET_H)
#define	XPROPERTYMASKINGPIPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMaskingPI.h"


class	GUICmdAddMaskingPIArea : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	FlexArea		MaskArea;
	bool			Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdAddMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeMaskingPIAttr : public GUICmdPacketBase
{
public:
	int				ItemID;
	int				GlobalPage;
	bool			Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdChangeMaskingPIAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdMaskingPIDrawModePacket : public GUIDirectMessage
{
public:

	CmdMaskingPIDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

//=================================================================================

class	MaskingPIListForPacket : public NPList<MaskingPIListForPacket>
{
public:
	int		ItemID;
	int		Page;
	int		x1,y1,x2,y2;
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	
	MaskingPIListForPacket(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	MaskingPIListForPacket	&operator=(MaskingPIListForPacket &src);
};

class	MaskingPIListForPacketPack : public NPListPack<MaskingPIListForPacket>
{
public:
	MaskingPIListForPacketPack(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	MaskingPIListForPacketPack	&operator= (MaskingPIListForPacketPack &src);
	MaskingPIListForPacketPack	&operator+=(MaskingPIListForPacketPack &src);
};

//===========================================================================

class	GUICmdReqMaskPIList : public GUICmdPacketBase
{
public:
	bool	IneffectiveMode;
	bool	EffectiveMode;
	GUICmdReqMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendMaskPIList : public GUICmdPacketBase
{
public:
	MaskingPIListForPacketPack	MaskInfo;

	GUICmdSendMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeMaskList(bool EffectiveMode,bool IneffectiveMode,int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdGenerateMaskPIInSameColor : public GUICmdPacketBase
{
public:
	int32	RPickupL;
	int32	RPickupH;
	int32	GPickupL;
	int32	GPickupH;
	int32	BPickupL;
	int32	BPickupH;
	bool	Effective;
	IntList	LayerList;

	GUICmdGenerateMaskPIInSameColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqRemoveMaskPI : public GUICmdPacketBase
{
public:
	int		ItemID	;
	int		Phase	;

	GUICmdReqRemoveMaskPI(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

#endif