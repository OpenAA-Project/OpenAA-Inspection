/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDent\XPropertyDentPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYDentPACKET_H)
#define	XPROPERTYDentPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDentLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XDentInspection.h"


class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	int	LibID;

	GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdPickupTestList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdTestClear: public GUICmdPacketBase
{
public:
	GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdGenerateDents : public GUICmdPacketBase
{
public:
	IntList			LibList;

	GUICmdGenerateDents(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateDents(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdDentDrawModePacket : public GUIDirectMessage
{
public:
	CmdDentDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	DentImagePanel;
class	CmdDentDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	DentImagePanel	*ImagePanelPoint;

	CmdDentDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdDentShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;

	CmdDentShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
};


class	GUICmdReqAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	IntList		LayerList;

	GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	BrightnessMapList : public NPList<BrightnessMapList>
{
public:
	int	BrightList[256];

	BrightnessMapList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	GUICmdSendAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	NPListPack<BrightnessMapList>	MapList;

	GUICmdSendAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
	void	MakeLists(FlexArea &area ,IntList &LayerList ,int localPage,LayersBase *Base);
};

class	DentItem;
class	GUICmdSendAddManualDent : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			Layer;
	QString		ItemName;
	int			LibID;

	GUICmdSendAddManualDent(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdExecuteMouseLDown: public GUIDirectMessage
{
public:
	IntList	PageList;
	ListPageLayerIDPack	CurrentItem;

	CmdExecuteMouseLDown(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdExecuteMouseRDownWithShift : public GUIDirectMessage
{
public:
	CmdExecuteMouseRDownWithShift(LayersBase *base):GUIDirectMessage(base){}
};

//==========================================================================


class	GUICmdReqDentInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqDentInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDentInfoList : public GUICmdPacketBase
{
public:
	NPListPack<DentInfoList>	DentInfos;

	GUICmdSendDentInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdDentGenerate : public GUICmdPacketBase
{
public:
	IntList	ItemLibIDs;
	GUICmdDentGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqMeasureItemInfo: public GUICmdPacketBase
{
public:
	int		ItemID;

	GUICmdReqMeasureItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMeasureItemInfo: public GUICmdPacketBase
{
public:
	int		Page;
	int		x1,y1,x2,y2;

	GUICmdAckMeasureItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
