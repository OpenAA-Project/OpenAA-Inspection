#pragma once

#include "XGUIPacketForDLL.h"
#include "XAlignmentShiftRotation.h"
#include "XPacketAlignmentShiftRotation.h"

class	CmdAlignmentShiftRotationDrawModePacket : public GUIDirectMessage
{
public:
	bool	DrawModeArea;
	bool	DrawModeHVLines;
	int		HVLinesPage			;
	int		HVLinesPhase		;
	int		HVLinesItemID		;
	int		HVLinesAngleIndex	;

	CmdAlignmentShiftRotationDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAlignmentShiftRotationDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AlignmentShiftRotationImagePanel;
class	CmdAlignmentShiftRotationDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	AlignmentShiftRotationImagePanel	*ImagePanelPoint;

	CmdAlignmentShiftRotationDrawEnd(LayersBase *base):GUIDirectMessage(base){	ImagePanelPoint=NULL;	}
	CmdAlignmentShiftRotationDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ImagePanelPoint=NULL;	}
};

class	GUICmdAddAlignmentShiftRotation : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;

	GUICmdAddAlignmentShiftRotation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAlignmentShiftRotation : public GUICmdPacketBase
{
public:
	int			ItemID;

	GUICmdSendAlignmentShiftRotation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdReqModifyAlignmentShiftRotation : public GUICmdPacketBase
{
public:
	int	ItemID;

	GUICmdReqModifyAlignmentShiftRotation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================================

class GUICmdReqAlignmentShiftRotationItemList: public GUICmdPacketBase
{
public:
	int		Phase;
	GUICmdReqAlignmentShiftRotationItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class GUICmdSendAlignmentShiftRotationItemList: public GUICmdPacketBase
{
public:
	AlignmentShiftRotationItemListPack	ItemList;

	GUICmdSendAlignmentShiftRotationItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================

class GUICmdReqAlignmentShiftRotationItemAngleList: public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;

	GUICmdReqAlignmentShiftRotationItemAngleList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class GUICmdSendAlignmentShiftRotationItemAngleList: public GUICmdPacketBase
{
public:
	DoubleList	AngleList;

	GUICmdSendAlignmentShiftRotationItemAngleList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
