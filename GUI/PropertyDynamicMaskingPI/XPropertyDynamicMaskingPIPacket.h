/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\XPropertyDynamicMaskingPIPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYDYNAMICMASKINGPIPACKET_H)
#define	XPROPERTYDYNAMICMASKINGPIPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDynamicMaskingPI.h"


class	GUICmdAddDynamicMaskingPIArea : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	FlexArea	MaskArea;
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	BYTE		DrawColG;
	BYTE		DrawColB;

	int32		AbsLR2, AbsHR2;
	int32		AbsLG2, AbsHG2;
	int32		AbsLB2, AbsHB2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	BYTE		DrawColG2;
	BYTE		DrawColB2;
	int32		Mergin;
	ColorLogic	MaskingColor;
	int32		Layer;
	int32		ParentItemID;
	IntList		AdaptedPickupLayers;

	GUICmdAddDynamicMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdModDynamicMaskingPIArea : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	int32		ID;

	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	BYTE		DrawColG;
	BYTE		DrawColB;

	int32		AbsLR2, AbsHR2;
	int32		AbsLG2, AbsHG2;
	int32		AbsLB2, AbsHB2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	BYTE		DrawColG2;
	BYTE		DrawColB2;
	int32		Mergin;
	ColorLogic	MaskingColor;
	int32		Layer;
	IntList		AdaptedPickupLayers;

	GUICmdModDynamicMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqDMaskingPIAreaInfoList : public GUICmdPacketBase
{
public:

	GUICmdReqDMaskingPIAreaInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDMaskingPIAreaInfoList : public GUICmdPacketBase
{
public:
	DynamicMaskingPIInfoListContainer	Data;

	GUICmdAckDMaskingPIAreaInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif