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