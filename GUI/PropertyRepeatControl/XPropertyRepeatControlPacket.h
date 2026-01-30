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

#pragma once

#include "XGUIPacketForDLL.h"
#include "XRepeatControl.h"
#include "XIntClass.h"

class	LayersBase;

class	CmdRepeatControlDrawAttr: public GUIDirectMessage
{
public:
	QColor	BlockColor0;
	QColor	BlockColor1;
	QColor	BlockColor2;
	QColor	BlockColor3;
	QColor	BlockColor4;
	QColor	BlockColor5;
	QColor	BlockColor6;
	QColor	BlockColor7;
	int		ShowingItemID;

	CmdRepeatControlDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdRepeatControlDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdRepeatControlDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdRepeatControlDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdRepeatControlDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class	GUICmdSendAddManualRepeatControl : public GUICmdPacketBase
{
public:
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;
	FlexArea	Area;

	GUICmdSendAddManualRepeatControl(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendModifyRepeatControl : public GUICmdPacketBase
{
public:
	ListPhasePageLayerItem	Index;
	int		RepeatCount	;
	int		MeshSize	;
	int		SequenceOffset	;
	bool	GatherAllPhase;

	GUICmdSendModifyRepeatControl(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//=====================================================================

class	GUICmdReqRepeatControlInfoList : public GUICmdPacketBase
{
public:
	int	Phase;
	GUICmdReqRepeatControlInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRepeatControlInfoList : public GUICmdPacketBase
{
public:
	RepeatControlInfoListContainer	RepeatControlInfos;

	GUICmdAckRepeatControlInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
//=================================================================

class	GUICmdCreateWholeRepeatControl : public GUICmdPacketBase
{
public:
	int		Phase		;
	int		RepeatCount	;

	GUICmdCreateWholeRepeatControl(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};