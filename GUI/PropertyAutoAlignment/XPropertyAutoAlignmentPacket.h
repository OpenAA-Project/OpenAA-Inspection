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


#ifndef XAUTOALIGNMENTPACKET_H
#define XAUTOALIGNMENTPACKET_H

#include "XGUIFormBase.h"
//#include "ui_PropertyAutoAlignmentForm.h"
#include "XAutoAlignment.h"
#include "XAutoAlignmentCommon.h"



class	GUICmdCreateAutoAlignmentSheet : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;

	GUICmdCreateAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAutoAlignmentInfo : public GUICmdPacketBase
{
public:
	GUICmdReqAutoAlignmentInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAutoAlignmentInfo : public GUICmdPacketBase
{
public:
	IntList		SheetLevels;

	GUICmdSendAutoAlignmentInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};



class	GUICmdReqAutoAlignmentSheet : public GUICmdPacketBase
{
public:
	GUICmdReqAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendAutoAlignmentSheet : public GUICmdPacketBase
{
public:
	AASheetInfos	AASheetInfoData;

	GUICmdSendAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdAutoAlignmentExecuteDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;

	CmdAutoAlignmentExecuteDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSetAutoAlignmentLibColor : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	int			LibID;

	GUICmdSetAutoAlignmentLibColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	CmdAutoAlignmentAddManualSheetDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;

	CmdAutoAlignmentAddManualSheetDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddAutoAlignmentSheet : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	int			LibID;

	GUICmdAddAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};	

//===============================================================================
class	CmdSetAutoAlignmentShowingState : public GUIDirectMessage
{
public:
	enum	_ShowingSheet
	{
		_Default		=0
		,_None			=1
		,_Area			=2
		,_PickupArea	=3
		,_PickupAreaTest=4
	}ModeShowingSheet;

	bool	ModeShowingMono;
	int		MonoLevel;

	bool	ModeShowingPicoTransArea;
	bool	ModeShowingPicoPickupArea;
	bool	ModeShowingPicoOtherArea;
	bool	ModeShowingPicoFringeArea;
	bool	ModeShowingPicoInfo;
	bool	ModeClickPickupAreaTest;

	AAListAttrContainer	ShowingLibIDs;

	CmdSetAutoAlignmentShowingState(LayersBase *base)
		:GUIDirectMessage(base)
	{
		ModeShowingSheet=_None;

		ModeShowingMono=false;
		MonoLevel=16;
		ModeShowingPicoTransArea	=false;
		ModeShowingPicoPickupArea	=true;
		ModeShowingPicoOtherArea	=false;
		ModeShowingPicoFringeArea	=false;
		ModeShowingPicoInfo			=true;
		ModeClickPickupAreaTest		=false;
	}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

inline	bool	CmdSetAutoAlignmentShowingState::Load(QIODevice *f)
{
	int	d;
	if(::Load(f,d)==false)
		return false;
	ModeShowingSheet=(_ShowingSheet)d;
	if(::Load(f,ModeShowingMono)==false)
		return false;
	if(::Load(f,MonoLevel)==false)
		return false;

	if(::Load(f,ModeShowingPicoTransArea)==false)
		return false;
	if(::Load(f,ModeShowingPicoPickupArea)==false)
		return false;
	if(::Load(f,ModeShowingPicoOtherArea)==false)
		return false;
	if(::Load(f,ModeShowingPicoFringeArea)==false)
		return false;
	if(::Load(f,ModeShowingPicoInfo)==false)
		return false;
	if(ShowingLibIDs.Load(f)==false)
		return false;
	return true;
}

inline	bool	CmdSetAutoAlignmentShowingState::Save(QIODevice *f)
{
	int	d=(int)ModeShowingSheet;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,ModeShowingMono)==false)
		return false;
	if(::Save(f,MonoLevel)==false)
		return false;

	if(::Save(f,ModeShowingPicoTransArea)==false)
		return false;
	if(::Save(f,ModeShowingPicoPickupArea)==false)
		return false;
	if(::Save(f,ModeShowingPicoOtherArea)==false)
		return false;
	if(::Save(f,ModeShowingPicoFringeArea)==false)
		return false;
	if(::Save(f,ModeShowingPicoInfo)==false)
		return false;
	if(ShowingLibIDs.Save(f)==false)
		return false;
	return true;
}

class	GUICmdSetAutoAlignmentShowingState : public GUICmdPacketBase
{
public:
	CmdSetAutoAlignmentShowingState	State;

	GUICmdSetAutoAlignmentShowingState(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//===============================================================================
class	GUICmdPickupTest : public GUICmdPacketBase
{
///	bool			CreatedInside;
public:
///	int						LibID;
///	AutoAlignmentLibrary	*LibPoint;

	int				PhaseNumb;

	GUICmdPickupTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdPickupTest(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif