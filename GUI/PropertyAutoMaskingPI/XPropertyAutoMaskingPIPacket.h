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
#include "XAutoMaskingPI.h"


class	GUICmdAddAutoMaskingPIArea : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	FlexArea		MaskArea;
	bool			Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdAddAutoMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeAutoMaskingPIAttr : public GUICmdPacketBase
{
public:
	int				ItemID;
	int				GlobalPage;
	bool			Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdChangeAutoMaskingPIAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdAutoMaskingPIDrawModePacket : public GUIDirectMessage
{
public:

	CmdAutoMaskingPIDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

//=================================================================================

class	AutoMaskingPIListForPacket : public NPList<AutoMaskingPIListForPacket>
{
public:
	int		ItemID;
	int		Page;
	int		x1,y1,x2,y2;
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	
	AutoMaskingPIListForPacket(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AutoMaskingPIListForPacket	&operator=(AutoMaskingPIListForPacket &src);
};

class	AutoMaskingPIListForPacketPack : public NPListPack<AutoMaskingPIListForPacket>
{
public:
	AutoMaskingPIListForPacketPack(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AutoMaskingPIListForPacketPack	&operator= (AutoMaskingPIListForPacketPack &src);
	AutoMaskingPIListForPacketPack	&operator+=(AutoMaskingPIListForPacketPack &src);
};

//===========================================================================

class	GUICmdReqAutoMaskPIList : public GUICmdPacketBase
{
public:
	bool	IneffectiveMode;
	bool	EffectiveMode;
	GUICmdReqAutoMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAutoMaskPIList : public GUICmdPacketBase
{
public:
	AutoMaskingPIListForPacketPack	MaskInfo;

	GUICmdSendAutoMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeMaskList(bool EffectiveMode,bool IneffectiveMode,int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdGenerateAutoMaskPIInSameColor : public GUICmdPacketBase
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

	GUICmdGenerateAutoMaskPIInSameColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	CmdSetAutoMaskingPIShowingState : public GUIDirectMessage
{
public:
	enum	_ShowingButton
	{
		_AutoMask			=1
		,_EffectiveMask		=2
		,_IneffectiveMask	=3
	}ModeShowingButton;

	CmdSetAutoMaskingPIShowingState(LayersBase *base):GUIDirectMessage(base)
	{
		ModeShowingButton=_AutoMask;
	}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	GUICmdSetAutoMaskingPIShowingState : public GUICmdPacketBase
{
public:
	CmdSetAutoMaskingPIShowingState	State;

	GUICmdSetAutoMaskingPIShowingState(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif