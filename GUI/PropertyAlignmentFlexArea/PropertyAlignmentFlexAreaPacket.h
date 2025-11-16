/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentFlexArea\PropertyAlignmentFlexAreaPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(PROPERTYAlignmentFlexAreaPACKET_H)
#define	PROPERTYAlignmentFlexAreaPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XPacketAlignmentFlexArea.h"
#include "XAlignmentFlexArea.h"
#include "XServiceForLayers.h"
#include "XPacketAlignmentFlexArea.h"
#include "NListComp.h"


class	CmdAlignmentFlexAreaDrawModePacket : public GUIDirectMessage
{
public:
	bool	DrawGeneratedArea;
	bool	DrawOutlineArea;
	bool	DrawWholeMatch;
	bool	DrawBaseMatch;
	IntList	SelectedArea;		//Use for item view
	IntList	SelectWholeMatch;
	int		CurrentBaseMatchRow;

	CmdAlignmentFlexAreaDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAlignmentFlexAreaDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AlignmentFlexAreaImagePanel;
class	CmdAlignmentFlexAreaDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	AlignmentFlexAreaImagePanel	*ImagePanelPoint;

	CmdAlignmentFlexAreaDrawEnd(LayersBase *base):GUIDirectMessage(base){	ImagePanelPoint=NULL;	}
	CmdAlignmentFlexAreaDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ImagePanelPoint=NULL;	}
};

//===========================================================================

class	AlignmentFlexAreaAreaList : public NPList<AlignmentFlexAreaAreaList>
{
public:
	int		Number;
	int		AreaID;
	int		LibID;
	QString	AreaName;
	int		GlobalPage;
	int		XSize;
	int		YSize;
	AlgorithmLibraryListContainer		LimitedLib;
	AlgorithmLibraryListContainer		LibToCreateItems;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	
	AlignmentFlexAreaAreaList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentFlexAreaAreaList	&operator=(AlignmentFlexAreaAreaList &src);
};

class	AlignmentFlexAreaAreaListPack : public NPListPack<AlignmentFlexAreaAreaList>
{
public:
	AlignmentFlexAreaAreaListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentFlexAreaAreaListPack	&operator=(AlignmentFlexAreaAreaListPack &src);
	AlignmentFlexAreaAreaListPack	&operator+=(AlignmentFlexAreaAreaListPack &src);
};

class	AlignmentWholeMatchList : public NPList<AlignmentWholeMatchList>
{
public:
	int		GlobalPage;
	int		ID;
	int		Division;

	AlignmentWholeMatchList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentWholeMatchList	&operator=(AlignmentWholeMatchList &src);
};

class	AlignmentWholeMatchListPack : public NPListPack<AlignmentWholeMatchList>
{
public:
	AlignmentWholeMatchListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentWholeMatchListPack	&operator=(AlignmentWholeMatchListPack &src);
	AlignmentWholeMatchListPack	&operator+=(AlignmentWholeMatchListPack &src);
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

class	GUICmdReqAlignmentFlexAreaAreaList : public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentFlexAreaAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentFlexAreaAreaList : public GUICmdPacketBase
{
public:
	AlignmentFlexAreaAreaListPack	Area;

	GUICmdSendAlignmentFlexAreaAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaList(int localPage,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdReqWholeMatchList : public GUICmdPacketBase
{
public:
	GUICmdReqWholeMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendWholeMatchList : public GUICmdPacketBase
{
public:
	AlignmentWholeMatchListPack	WholeMatchInfo;

	GUICmdSendWholeMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeWholeMatchList(int localPage,LayersBase *PBase);
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

class	GUICmdReqAlignmentFlexAreaPointList : public GUICmdPacketBase
{
public:
	int	AreaID;

	GUICmdReqAlignmentFlexAreaPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentFlexAreaPointList : public GUICmdPacketBase
{
public:
	AlignmentFlexAreaInfoListPack	Points;

	GUICmdSendAlignmentFlexAreaPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//===========================================================================
class	GUICmdReqAlignmentFlexAreaPutArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;
	AlgorithmLibraryListContainer	LibToCreateItems;

	GUICmdReqAlignmentFlexAreaPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyAlignmentFlexAreaAreaInfo : public GUICmdPacketBase
{
public:
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	bool		DeleteMode;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;
	AlgorithmLibraryListContainer	LibToCreateItems;

	GUICmdReqModifyAlignmentFlexAreaAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

/*
class	GUICmdReqAlignmentFlexAreaAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;

	GUICmdReqAlignmentFlexAreaAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAlignmentFlexAreaAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSendAlignmentFlexAreaAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage,int layer,int areaID,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


//===========================================================================

class	GUICmdSetActiveAreas : public GUICmdPacketBase
{
public:
	ReqAlignmentFlexAreaAreaListPack	ActiveAreas;
	QString						InstForm;

	GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdSetActiveAreas : public GUIDirectMessage
{
public:
	ReqAlignmentFlexAreaAreaListPack	ActiveAreas;

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
class	GUICmdSendAddManualAlignmentFlexArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			AreaID;
	int			LibID;

	GUICmdSendAddManualAlignmentFlexArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

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

class	GUICmdGenerateAlignmentFlexAreas : public GUICmdPacketBase
{
public:
	IntList	LibList;
	int		AreaID;

	GUICmdGenerateAlignmentFlexAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdGenerateAlignmentFlexAreaFromMask : public GUICmdPacketBase
{
public:
	int		Priority;
	int		ItemLibID;

	GUICmdGenerateAlignmentFlexAreaFromMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdTestClear : public GUICmdPacketBase
{
public:
	GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqAlignmentFlexAreaSetMode : public GUICmdPacketBase
{
public:
	bool	ModeFlexAreaArea;
	bool	ModeWholeMatch;
	bool	ModeOutline;

	GUICmdReqAlignmentFlexAreaSetMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqAlignmentFlexAreaSetCurrentArea : public GUICmdPacketBase
{
public:
	int	AreaID;
	int	GlobalPage;

	GUICmdReqAlignmentFlexAreaSetCurrentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqAlignmentFlexAreaItemPack : public GUICmdPacketBase
{
public:
	int			LibID;
	int			AreaID;
	
	GUICmdReqAlignmentFlexAreaItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckAlignmentFlexAreaItemPack : public GUICmdPacketBase
{
public:
	AlignmentFlexAreaItemListPack	Items;

	GUICmdAckAlignmentFlexAreaItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================

class	GUICmdChangeAlignmentFlexAreaThreshold : public GUICmdPacketBase
{
public:
	int			LibID;
	QByteArray	InfosData;

	GUICmdChangeAlignmentFlexAreaThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqRemoveAllOriginal : public GUICmdPacketBase
{
public:
	int32		GeneratedOrigin;

	GUICmdReqRemoveAllOriginal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================
class	GUICmdGenerateBaseMatch : public GUICmdPacketBase
{
public:
	GUICmdGenerateBaseMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================
class	GUICmdExecBaseMatch : public GUICmdPacketBase
{
public:
	GUICmdExecBaseMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqBaseMatchList : public GUICmdPacketBase
{
public:
	
	GUICmdReqBaseMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckBaseMatchList : public GUICmdPacketBase
{
public:
	MatchAngleListContainer	ListData;

	GUICmdAckBaseMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================

class	GUICmdCreateAreaInMaskingArea : public GUICmdPacketBase
{
public:
	int Priority;

	GUICmdCreateAreaInMaskingArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================
class	GUICmdReqAlignmentPointList: public GUICmdPacketBase
{
public:
	int		AreaID;
	GUICmdReqAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckAlignmentPointList : public GUICmdPacketBase
{
public:
	AlignmentPointListContainer	PointList;

	GUICmdAckAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif
