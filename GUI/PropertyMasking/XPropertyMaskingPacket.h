/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\XPropertyMaskingPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYMASKINGPACKET_H)
#define	XPROPERTYMASKINGPACKET_H

#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMasking.h"
#include "XFlexArea.h"
#include "XIntClass.h"
#include <QString>
#include "XVector.h"
#include "NListComp.h"
#include "XAlgorithmLibrary.h"
#include "XColorSpace.h"

class	GUICmdAddMaskingArea : public GUICmdPacketBase
{
	//bool			CreatedInside;
public:
	FlexArea		MaskArea;
	bool			Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	IntList			LayerList;

	GUICmdAddMaskingArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdAddMaskingLine : public GUICmdPacketBase
{
	//bool			CreatedInside;
public:
	VectorLineBase	*Vector;
	IntList			LayerList;

	GUICmdAddMaskingLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdChangeMaskingAttr : public GUICmdPacketBase
{
public:
	int				ItemID;
	int				GlobalPage;
	int				Layer;
	bool			Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdChangeMaskingAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

#define	Button_Effective			1
#define	Button_NotEffective			2
#define	Button_LimitedEffective		4
#define	Button_LimitedNotEffective	8
#define	Button_CutLine				16

class	GUICmdReqSetButtonMode : public GUICmdPacketBase
{
public:
	BYTE		Mode;
	QString		InstForm;

	GUICmdReqSetButtonMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	CmdReqSetButtonMode : public GUIDirectMessage
{
public:
	BYTE	Mode;

	CmdReqSetButtonMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSetButtonMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMaskingDrawModePacket : public GUIDirectMessage
{
public:

	CmdMaskingDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdMaskingDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================

class	MaskingListForPacket : public NPList<MaskingListForPacket>
{
public:
	struct{
		int		ItemID;
		int		Layer;
		int		Page;
		int		x1,y1,x2,y2;
		bool	Effective;
	}Data;
	AlgorithmLibraryListContainer	LimitedLib;
	
	MaskingListForPacket(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	MaskingListForPacket	&operator=(MaskingListForPacket &src);
};

class	MaskingListForPacketPack : public NPListPack<MaskingListForPacket>
{
public:
	MaskingListForPacketPack(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	MaskingListForPacketPack	&operator=(MaskingListForPacketPack &src);
	MaskingListForPacketPack	&operator+=(MaskingListForPacketPack &src);
};

//===========================================================================

class	GUICmdReqMaskList : public GUICmdPacketBase
{
public:
	bool	IneffectiveMode;
	bool	EffectiveMode;
	bool	IneffectiveLimitedMode;
	bool	EffectiveLimitedMode;

	GUICmdReqMaskList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdSendMaskList : public GUICmdPacketBase
{
public:
	MaskingListForPacketPack	MaskInfo;

	GUICmdSendMaskList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeMaskList(bool EffectiveMode,bool IneffectiveMode
						,bool EffectiveLimitedMode,bool IneffectiveLimitedMode 
						,int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	

private:
	void	MakeMaskListLayer1(AlgorithmBase* MaskingBase
		,bool EffectiveMode, bool IneffectiveMode
		, bool EffectiveLimitedMode, bool IneffectiveLimitedMode
		, int localPage, LayersBase* PBase);
	void	MakeMaskListLayers(AlgorithmBase* MaskingBase
		,bool EffectiveMode, bool IneffectiveMode
		, bool EffectiveLimitedMode, bool IneffectiveLimitedMode
		, int localPage, LayersBase* PBase);

};

//===========================================================================

class	GUICmdGenerateMaskInSameColor : public GUICmdPacketBase
{
public:
	int32	PickupL;
	int32	PickupH;
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	IntList	LayerList;

	ColorLogic	PickupColor;
	int		MinPickupSize;
	int		MaxPickupSize;
	int		MinPickupDots;
	int		MaxPickupDots;
	int		Erosion;
	bool	TestMode;

	GUICmdGenerateMaskInSameColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

class	CmdExecuteMouseLDownPacket : public GUIDirectMessage
{
public:
	int		globalX;
	int		globalY;
	QColor	Color;
	IntList	LayerList;

	CmdExecuteMouseLDownPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteMouseLDownPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdPourOnMouseLDown : public GUICmdPacketBase
{
public:
	int		LocalX,LocalY;
	int32	PickupRL,PickupRH;
	int32	PickupGL,PickupGH;
	int32	PickupBL,PickupBH;
	bool	Effective;
	bool	Exclusive;
	int		ExpandedDot;
	int		MinSize;
	int64	MinDots;
	IntList	LayerList;
	int		OmitX1,OmitY1,OmitX2,OmitY2;
	int		NoisePinhole ;
	int		NoiseSmallDot;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdPourOnMouseLDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	CmdSetMouseMoveForPour : public GUIDirectMessage
{
public:
	CmdSetMouseMoveForPour(LayersBase *base):GUIDirectMessage(base){}
	CmdSetMouseMoveForPour(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdPickupArea : public GUICmdPacketBase
{
public:
	int32	PickupRL,PickupRH;
	int32	PickupGL,PickupGH;
	int32	PickupBL,PickupBH;
	bool	Effective;
	int		ExpandedDot;
	int		MinSize;
	IntList	LayerList;
	AlgorithmLibraryListContainer	LimitedLib;
	int32	HoleMinArea		;
	int32	HoleErosionDot	;
	int32	AreaX1,AreaY1,AreaX2,AreaY2;

	GUICmdPickupArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

class	GUICmdExpandMask : public GUICmdPacketBase
{
public:
	int32	PixelCount;

	GUICmdExpandMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

class	GUICmdReplaceInclusiveMask : public GUICmdPacketBase
{
public:

	GUICmdReplaceInclusiveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

class	GUICmdReqLimitedLibMask : public GUICmdPacketBase
{
public:
	GUICmdReqLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdAckLimitedLibMask : public GUICmdPacketBase
{
public:
	IntList	LimitedLib;

	GUICmdAckLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override{}
};
//===========================================================================

class	GUICmdMaskingMakeBackGround : public GUICmdPacketBase
{
public:
	bool	MasterMode;

	GUICmdMaskingMakeBackGround(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};
//===========================================================================

class	GUICmdClearMakeBackGround : public GUICmdPacketBase
{
public:

	GUICmdClearMakeBackGround(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override{	return true;	}
	virtual	bool	Save(QIODevice *f)	override{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

class	MaskingBindedList : public NPListSaveLoad<MaskingBindedList>
{
public:
	class BindedInPage : public NPListSaveLoad<BindedInPage>
	{
	public:
		int	Page;

		class BindedInLayer : public NPListSaveLoad<BindedInLayer>
		{
		public:
			MaskingBindedList::BindedInPage	*Parent;
			int		Layer;
			IntList	ItemIDs;

			BindedInLayer(MaskingBindedList::BindedInPage *p):Parent(p){}
			BindedInLayer(const BindedInLayer &src);

			virtual	bool	Save(QIODevice *f)	override;
			virtual	bool	Load(QIODevice *f)	override;

			BindedInLayer &operator=(const BindedInLayer &src);
		};
		class BindedInLayerContainer : public NPListPackSaveLoad<BindedInLayer>
		{
		public:
			MaskingBindedList::BindedInPage	*Parent;

			BindedInLayerContainer(MaskingBindedList::BindedInPage	*p):Parent(p){}

			virtual	BindedInLayer	*Create(void)	{	return new BindedInLayer(Parent);	}
			void	Merge(BindedInLayerContainer &s);
			BindedInLayerContainer &operator=(const BindedInLayerContainer &src);
			MaskingBindedList::BindedInPage::BindedInLayer	*FindByLayer(int layer);
		};
		BindedInLayerContainer	BindedInLayerContainerInst;
		MaskingBindedList		*Parent;

		BindedInPage(MaskingBindedList *p):BindedInLayerContainerInst(this),Parent(p){}
		BindedInPage(const BindedInPage &src);

		virtual	bool	Save(QIODevice *f)	override;
		virtual	bool	Load(QIODevice *f)	override;
		BindedInPage &operator=(const BindedInPage &src);
	};
	class BindedInPageContainer : public NPListPackSaveLoad<BindedInPage>
	{
	public:
		MaskingBindedList	*Parent;

		BindedInPageContainer(MaskingBindedList *p):Parent(p){}
		virtual	BindedInPage	*Create(void)	{	return new BindedInPage(Parent);	}
		BindedInPageContainer &operator=(const BindedInPageContainer &src);
		void	Merge(BindedInPageContainer &s);
	};
	BindedInPageContainer			BindedInPageContainerInst;
	AlgorithmLibraryListContainer	LimitedLib;
	
	MaskingBindedList(void):BindedInPageContainerInst(this){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	MaskingBindedList &operator=(const MaskingBindedList &src);
};

class	MaskingBindedListContainer : public NPListPackSaveLoad<MaskingBindedList>
{
public:
	MaskingBindedListContainer(void){}
	virtual	MaskingBindedList	*Create(void)	{	return new MaskingBindedList();	}
};



class	GUICmdReqBindedLimitedLibMask : public GUICmdPacketBase
{
public:
	GUICmdReqBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdAckBindedLimitedLibMask : public GUICmdPacketBase
{
public:
	MaskingBindedListContainer	InstList;

	GUICmdAckBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override{}
};

class	GUICmdSetBindedLimitedLibMask : public GUICmdPacketBase
{
public:
	MaskingBindedListContainer	InstList;

	GUICmdSetBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdSelectBindedLimitedLibMask : public GUICmdPacketBase
{
public:
	int		Layer;
	IntList	ItemIDs;

	GUICmdSelectBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};


class	GUICmdReqMaskCount: public GUICmdPacketBase
{
public:
	GUICmdReqMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

class	GUICmdAckMaskCount: public GUICmdPacketBase
{
public:
	UsedLimitedMaskContainer	MaskContainer;

	GUICmdAckMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override{}
};

//===========================================================================
class	GUICmdGenerateMaskOnSelectedItemsEdge: public GUICmdPacketBase
{
public:
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int								Expansion ;
    int								InsideDot ;
    int								OutsideDot;

	GUICmdGenerateMaskOnSelectedItemsEdge(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;
};

//===========================================================================
class	GUICmdGeneratePatternEdgeOnSelected: public GUICmdPacketBase
{
public:
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int								BoundaryDiff ;
    int								WidthDot ;

	GUICmdGeneratePatternEdgeOnSelected(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;
};
//===========================================================================

class	GUICmdReflectSelection : public GUICmdPacketBase
{
public:
	int		Layer;
	IntList	Items;

	GUICmdReflectSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};
//===========================================================================

class	GUICmdReqRemoveMask : public GUICmdPacketBase
{
public:
	int		ItemID	;
	int		Layer	;
	int		Phase	;

	GUICmdReqRemoveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;	
};

//===========================================================================

class	GUICmdSetItemSelection: public GUICmdPacketBase
{
public:
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSetItemSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;
};


#endif