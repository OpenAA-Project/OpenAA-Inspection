/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceProperty\XPiecePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPIECEPACKET_H)
#define	XPIECEPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"

class	CmdPieceSetCutPacket : public GUIDirectMessage
{
public:

	CmdPieceSetCutPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPieceSetCutPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPieceSetArrangePacket : public GUIDirectMessage
{
public:

	CmdPieceSetArrangePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPieceSetArrangePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCheckPiecePropertyButtonPacket : public GUIDirectMessage
{
public:
	enum{
		ModeNone		=0
		,ModeCutArea	=1
		,ModeArrange	=2
	}Mode;

	CmdCheckPiecePropertyButtonPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCheckPiecePropertyButtonPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreatePiecePacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	CmdCreatePiecePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreatePiecePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPieceSelectedAlgorithm : public GUIDirectMessage
{
public:
	QString	DLLRoot;
	QString	DLLName;
	ListPageIDPack	SelectedLines;
	CmdPieceSelectedAlgorithm(LayersBase *base):GUIDirectMessage(base){}
	CmdPieceSelectedAlgorithm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPieceSelectedMaster : public GUIDirectMessage
{
public:
	int	MasterCode;
	CmdPieceSelectedMaster(LayersBase *base):GUIDirectMessage(base){}
	CmdPieceSelectedMaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteAlignmentPiece : public GUIDirectMessage
{
public:
	int	LocalPage;
	int	SearchDot;
	CmdExecuteAlignmentPiece(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteAlignmentPiece(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteAutoAlignmentPiece : public GUIDirectMessage
{
public:
	int		LocalPage;
	IntList	AutoSelectedMasterList;

	CmdExecuteAutoAlignmentPiece(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteAutoAlignmentPiece(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateParts : public GUIDirectMessage
{
public:
	CmdUpdateParts(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateParts(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//============================================================================
class	GUICmdExecuteAlignmentPiece : public GUICmdPacketBase
{
public:
	int		SearchDot;
	GUICmdExecuteAlignmentPiece(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqPieceItemMasterCode: public GUICmdPacketBase
{
public:
	int	ItemID;
	
	GUICmdReqPieceItemMasterCode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendPieceItemMasterCode: public GUICmdPacketBase
{
public:
	int	MasterCode;
	
	GUICmdSendPieceItemMasterCode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------

class	GetCountPacket: public GUIDirectMessage
{
public:
	bool	EnabledCountMode;
	int		CountX;
	int		CountY;

	GetCountPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	ChangeToCountModePacket: public GUIDirectMessage
{
public:
	ChangeToCountModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CancelCountPacket: public GUIDirectMessage
{
public:
	CancelCountPacket(LayersBase *base):GUIDirectMessage(base){}
};

//============================================================================

class	GUICmdReqPieceGrid: public GUICmdPacketBase
{
public:
	GUICmdReqPieceGrid(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendPieceGrid: public GUICmdPacketBase
{
public:
	PieceGridContainer	PieceGridInfo;
	
	GUICmdSendPieceGrid(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//============================================================================

class	GUICmdReqSelectPiece: public GUICmdPacketBase
{
public:
	int	PieceID;

	GUICmdReqSelectPiece(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif