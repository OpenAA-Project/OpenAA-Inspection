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