/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyVCutProperty\VCutImagePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(VCUTIMAGEPACKET_H)
#define	VCUTIMAGEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XVCutInspection.h"

class	GUICmdAddVCutInspectionArea : public GUICmdPacketBase
{
public:
	VectorLineBase	*Vector;
	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;
	int		LibID;

	GUICmdAddVCutInspectionArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	VCutInspectionList : public NPList<VCutInspectionList>
{
public:
	int		Page;
	int		x1,y1,x2,y2;
	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;

	VCutInspectionList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	VCutInspectionListForPacketPack: public NPListPack<VCutInspectionList>
{
public:
	VCutInspectionListForPacketPack(void){}

	VCutInspectionListForPacketPack	&operator+=(VCutInspectionListForPacketPack &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


class	GUICmdReqVCutInspectionList : public GUICmdPacketBase
{
public:
	GUICmdReqVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendVCutInspectionList : public GUICmdPacketBase
{
public:
	VCutInspectionListForPacketPack	VCutInfo;

	GUICmdSendVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeVCutList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
