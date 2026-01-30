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


#ifndef XAutoPCBHoleAlignerPACKET_H
#define XAutoPCBHoleAlignerPACKET_H

#include "XGUIFormBase.h"
#include "ui_PropertyAutoPCBHoleAlignerForm.h"
#include "XAutoPCBHoleAligner.h"


class	GUICmdCreateAutoPCBHoleAligner : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;

	GUICmdCreateAutoPCBHoleAligner(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAutoPCBHoleAlignerInfo : public GUICmdPacketBase
{
public:
	GUICmdReqAutoPCBHoleAlignerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAutoPCBHoleAlignerInfo : public GUICmdPacketBase
{
public:
	AAHoleInfos		AAInfoData;

	GUICmdSendAutoPCBHoleAlignerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	CmdAutoPCBHoleAlignerExecuteDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;

	CmdAutoPCBHoleAlignerExecuteDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSetAutoPCBHoleAlignertLibColor : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	int			LibID;

	GUICmdSetAutoPCBHoleAlignertLibColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//===============================================================================
class	CmdSetAutoPCBHoleAlignerShowingState : public GUIDirectMessage
{
public:
	bool	ModeShowingHole;
	bool	ModeShowingFringe;

	IntList	ShowingLibIDs;

	CmdSetAutoPCBHoleAlignerShowingState(LayersBase *base)
		:GUIDirectMessage(base)
	{
		ModeShowingHole		=true;
		ModeShowingFringe	=false;
	}
};

#endif