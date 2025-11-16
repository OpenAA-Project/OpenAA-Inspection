/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMatchShiftRotation\PropertyMatchShiftRotationPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(PROPERTYMatchShiftRotationPACKET_H)
#define	PROPERTYMatchShiftRotationPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XMatchShiftRotation.h"
#include "XServiceForLayers.h"
#include "NListComp.h"


class	CmdMatchShiftRotationDrawModePacket : public GUIDirectMessage
{
public:
	bool	DrawArea;
	bool	DrawMark;
	IntList	SelectedArea;		//Use for item view

	CmdMatchShiftRotationDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdMatchShiftRotationDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MatchShiftRotationImagePanel;
class	CmdMatchShiftRotationDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	MatchShiftRotationImagePanel	*ImagePanelPoint;

	CmdMatchShiftRotationDrawEnd(LayersBase *base):GUIDirectMessage(base){	ImagePanelPoint=NULL;	}
	CmdMatchShiftRotationDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ImagePanelPoint=NULL;	}
};

//===========================================================================

class	MatchShiftRotationAreaList : public NPList<MatchShiftRotationAreaList>
{
public:
	int		Number;
	int		AreaID;
	int		LibID;
	QString	AreaName;
	int		GlobalPage;
	int		XSize;
	int		YSize;
	
	MatchShiftRotationAreaList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	MatchShiftRotationAreaList	&operator=(MatchShiftRotationAreaList &src);
};

class	MatchShiftRotationAreaListPack : public NPListPack<MatchShiftRotationAreaList>
{
public:
	MatchShiftRotationAreaListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	MatchShiftRotationAreaListPack	&operator=(MatchShiftRotationAreaListPack &src);
	MatchShiftRotationAreaListPack	&operator+=(MatchShiftRotationAreaListPack &src);
};

//===========================================================================

class	BrightnessMapList : public NPList<BrightnessMapList>
{
public:
	int	Layer;
	int	BrightList[256];

	BrightnessMapList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	GUICmdReqAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	FlexArea	Area;

	GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
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
//===========================================================================

class	GUICmdReqMatchShiftRotationAreaList : public GUICmdPacketBase
{
public:
	GUICmdReqMatchShiftRotationAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendMatchShiftRotationAreaList : public GUICmdPacketBase
{
public:
	MatchShiftRotationAreaListPack	Area;

	GUICmdSendMatchShiftRotationAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaList(int localPage,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdDeleteArea : public GUICmdPacketBase
{
public:
	int	AreaID;

	GUICmdDeleteArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


//===========================================================================

class	GUICmdReqMatchShiftRotationPointList : public GUICmdPacketBase
{
public:
	int	AreaID;

	GUICmdReqMatchShiftRotationPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendMatchShiftRotationPointList : public GUICmdPacketBase
{
public:
	MatchShiftRotationInfoListPack	Points;

	GUICmdSendMatchShiftRotationPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//===========================================================================
class	GUICmdReqMatchShiftRotationPutArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	FlexArea	Area;
	QString		AreaName;
	int			LibID;

	GUICmdReqMatchShiftRotationPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyMatchShiftRotationAreaInfo : public GUICmdPacketBase
{
public:
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	int			LibID;
	bool		DeleteMode;

	GUICmdReqModifyMatchShiftRotationAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


/*
class	GUICmdReqMatchShiftRotationAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;

	GUICmdReqMatchShiftRotationAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendMatchShiftRotationAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	XMatchShiftRotationArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSendMatchShiftRotationAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage,int layer,int areaID,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


//===========================================================================

class	GUICmdSetActiveAreas : public GUICmdPacketBase
{
public:
	ReqMatchShiftRotationAreaListPack	ActiveAreas;
	QString						InstForm;

	GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdSetActiveAreas : public GUIDirectMessage
{
public:
	ReqMatchShiftRotationAreaListPack	ActiveAreas;

	CmdSetActiveAreas(LayersBase *base):GUIDirectMessage(base){}
	CmdSetActiveAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddArea: public GUIDirectMessage
{
public:
	CmdAddArea(LayersBase *base):GUIDirectMessage(base){}
	CmdAddArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//===========================================================================

class	GUICmdClickAreaButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickAreaButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdClickPointButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickPointButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdClickGroupButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickGroupButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
*/
//===========================================================================
class	GUICmdSendAddManualMatchShiftRotation : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			AreaID;
	QString		ItemName;
	int			LibID;

	GUICmdSendAddManualMatchShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdUpdateManualMatchShiftRotation : public GUICmdPacketBase
{
public:
	int			ItemID;
	QString		ItemName;
	int			LibID;

	GUICmdUpdateManualMatchShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdDeleteManualMatchShiftRotation : public GUICmdPacketBase
{
public:
	int			ItemID;

	GUICmdDeleteManualMatchShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdPickupTestList : public GUICmdPacketBase
{
public:
	IntList	LibList;
	int		AreaID;

	GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdGenerateMatchShiftRotations : public GUICmdPacketBase
{
public:
	IntList	LibList;
	int		AreaID;

	GUICmdGenerateMatchShiftRotations(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdGenerateMatchShiftRotationFromMask : public GUICmdPacketBase
{
public:
	int		ItemLibID;

	GUICmdGenerateMatchShiftRotationFromMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqMatchShiftRotationSetMode : public GUICmdPacketBase
{
public:
	bool	ModeFlexAreaArea;
	bool	ModeOutline;

	GUICmdReqMatchShiftRotationSetMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqMatchShiftRotationSetCurrentArea : public GUICmdPacketBase
{
public:
	int	AreaID;
	int	GlobalPage;

	GUICmdReqMatchShiftRotationSetCurrentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqMatchShiftRotationItemPack : public GUICmdPacketBase
{
public:
	int			AreaID;
	
	GUICmdReqMatchShiftRotationItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckMatchShiftRotationItemPack : public GUICmdPacketBase
{
public:
	MatchShiftRotationItemListPack	Items;

	GUICmdAckMatchShiftRotationItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================

class	GUICmdReqMatchShiftItemImages: public GUICmdPacketBase
{
public:
	int	AreaID;
	int	ItemID;

	GUICmdReqMatchShiftItemImages(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendMatchShiftItemImages : public GUICmdPacketBase
{
public:
	FlexAreaImageListCoeffAngleContainer	Patterns;

	GUICmdSendMatchShiftItemImages(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
#endif
