/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\PropertyAlignmentLargePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(PROPERTYAlignmentLargePACKET_H)
#define	PROPERTYAlignmentLargePACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XPacketAlignmentLarge.h"
#include "XAlignmentLarge.h"
#include "NListComp.h"
#include "XPropertyAlignmentLargeCommon.h"

//===========================================================================

class	AlignmentLargePointList : public NPList<AlignmentLargePointList>
{
public:
	int		ID;
	int		GroupNumber;
	int		Layer;
	int		AreaID;
	int		ItemID;
	int		Phase;
	int		Page;
	int		Cx,Cy;
	int		XSize;
	int		YSize;
	bool	AlignmentLargeOnOutline;
	int		MoveDotX;
	int		MoveDotY;
	int		MoveDotX2;
	int		MoveDotY2;
	int		SearchAround;
	bool	UsageGlobal;
	bool	JudgeWithBrDif;
	bool	CharacterMode;
	int		Threshold;
	int		UseLayer		;	//-1:Automatic select layer
	int		ThresholdColor	;	//-1:Automatic colc threshold brightness

	AlignmentLargePointList(void){}
	AlignmentLargePointList(const AlignmentLargePointList &src);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargePointList	&operator=(AlignmentLargePointList &src);
};

class	AlignmentLargePointListPack : public NPListPack<AlignmentLargePointList>
{
public:
	AlignmentLargePointListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargePointListPack	&operator=(AlignmentLargePointListPack &src);
	AlignmentLargePointListPack	&operator+=(AlignmentLargePointListPack &src);
};

//===========================================================================

class	GUICmdReqAlignmentLargeAreaList : public GUICmdPacketBase
{
public:
	int	CurrentLayer;

	GUICmdReqAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentLargeAreaList : public GUICmdPacketBase
{
public:
	AlignmentLargeAreaListPack	Area;

	GUICmdSendAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaList(int localPage,int CurrentLayer ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdReqAlignmentLargePointList : public GUICmdPacketBase
{
public:
	int	GlobalPage;
	int	Layer;
	int	Number;

	GUICmdReqAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentLargePointList : public GUICmdPacketBase
{
public:
	AlignmentLargePointListPack	Points;

	GUICmdSendAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakePointList(LayersBase *PBase ,int Layer ,int Number);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqAlignmentLargePutArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			MasterNo;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqAlignmentLargePutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckAlignmentLargePutArea : public GUICmdPacketBase
{
public:
	int			GeneratedAreaID;

	GUICmdAckAlignmentLargePutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqAlignmentLargePutPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	IntList		AreaID;
	FlexArea	PointArea;
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	WORD		SearchAround;
	bool		UsageGlobal;
	WORD		GroupNumber;
	bool		MultiSelect;
	bool		UseBitBuff;
	bool		JudgeWithBrDif;
	bool		CharacterMode ;
	int			UseLayer		;	//-1:Automatic select layer
	int			ThresholdColor	;	//-1:Automatic colc threshold brightness

	GUICmdReqAlignmentLargePutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeModifyPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	int			ItemID;
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	WORD		SearchAround;
	bool		UsageGlobal;
	WORD		GroupNumber;
	bool		JudgeWithBrDif;
	bool		CharacterMode ;
	int			UseLayer		;	//-1:Automatic select layer
	int			ThresholdColor	;	//-1:Automatic colc threshold brightness

	GUICmdReqAlignmentLargeModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeRemovePoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	int			ItemID;

	GUICmdReqAlignmentLargeRemovePoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeMakeGroup : public GUICmdPacketBase
{
public:

	GUICmdReqAlignmentLargeMakeGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeRemoveGroup : public GUICmdPacketBase
{
public:

	GUICmdReqAlignmentLargeRemoveGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;

	GUICmdReqAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAlignmentLargeAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSendAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage,int layer,int areaID,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyAlignmentLargeAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	int			MasterNo;
	FlexArea	Area;
	QString		AreaName;
	bool		DeleteMode;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqModifyAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdSetActiveAreas : public GUICmdPacketBase
{
public:
	ReqAlignmentLargeAreaListPack	ActiveAreas;
	QString						InstForm;

	GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdSetActiveAreas : public GUIDirectMessage
{
public:
	ReqAlignmentLargeAreaListPack	ActiveAreas;

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

class	CmdClickAreaButton : public GUIDirectMessage
{
public:
	CmdClickAreaButton(LayersBase *base):GUIDirectMessage(base){}
	CmdClickAreaButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}	
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

class	CmdClickPointButton : public GUIDirectMessage
{
public:
	CmdClickPointButton(LayersBase *base):GUIDirectMessage(base){}
	CmdClickPointButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}	
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

//===========================================================================

class	GUICmdClearAllAreas : public GUICmdPacketBase
{
public:

	GUICmdClearAllAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdClearAllPoints : public GUICmdPacketBase
{
public:
	int	Priority;

	GUICmdClearAllPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCreateAreaInMask : public GUICmdPacketBase
{
public:
	int		Priority;
	int		Erosion;
	GUICmdCreateAreaInMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAutoCreatePoint : public GUICmdPacketBase
{
public:
	bool	GeneratePartialAlignment;
	int		AlignmntPointSize		;
	int		AlignmntSearchAreaDotX	;
	int		AlignmntSearchAreaDotY	;
	int		AlignmntSearchAreaDot2X	;
	int		AlignmntSearchAreaDot2Y	;
	int		Layer;
	int		AreaPriority;
	int		LimitedLibType;
	int		LimitedLibID;
	bool	AlignmntJudgeWithBrDif	;

	GUICmdAutoCreatePoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqHeadAlignment : public GUICmdPacketBase
{
public:
	GUICmdReqHeadAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckHeadAlignment : public GUICmdPacketBase
{
public:
	struct _HeadData
	{
		bool		UseHeadAlignment	 ;
		int			MaxHeadAlignmentX	 ;
		int			MaxHeadAlignmentY	 ;
		int			SkipHeadAlignmentX	 ;
		int			SkipHeadAlignmentY	 ;
		int			HeadAlignmentDifColor;
		int			HeadAlignmentMinSize ;
	}HeadData;

	GUICmdAckHeadAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetHeadAlignment : public GUICmdPacketBase
{
public:
	struct _HeadData
	{	
		bool		UseHeadAlignment;
		int			MaxHeadAlignmentX;
		int			MaxHeadAlignmentY;
		int			SkipHeadAlignmentX;
		int			SkipHeadAlignmentY;
		int			HeadAlignmentDifColor;
		int			HeadAlignmentMinSize ;
	}HeadData;

	GUICmdSetHeadAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSetAlignmentData : public GUICmdPacketBase
{
public:
	QByteArray	AlignData;

	GUICmdSetAlignmentData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdDeleteAreaExceptGlobal : public GUICmdPacketBase
{
public:
	GUICmdDeleteAreaExceptGlobal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdDeleteItemsExceptGlobal : public GUICmdPacketBase
{
public:
	GUICmdDeleteItemsExceptGlobal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqDelAlignmentArea : public GUICmdPacketBase
{
public:
    QString			AreaName;

	GUICmdReqDelAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

};

class	GUICmdGenerateAuto : public GUICmdPacketBase
{
public:
	int	AreaID;
	int	Layer;

	GUICmdGenerateAuto(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqMakeAreaFromMask : public GUICmdPacketBase
{
public:
	IntList	AreaPriority;	//XAlignmentLargeArea::_EnumPriority

	GUICmdReqMakeAreaFromMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);
};



#endif
