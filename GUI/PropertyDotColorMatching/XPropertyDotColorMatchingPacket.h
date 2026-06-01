/*
 * Copyright (C) 2025
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


#if	!defined(XPROPERTYDotColorMatchingPACKET_H)
#define	XPROPERTYDotColorMatchingPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDotColorMatchingLibrary.h"
#include "XDotColorMatching.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	AlgorithmLibraryLevelContainer	*LibPoint;

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

class	GUICmdGenerateDotColorMatchings : public GUICmdPacketBase
{
public:
	IntList			LibList;

	GUICmdGenerateDotColorMatchings(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateDotColorMatchings(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdGenerateDotColorMatchings : public GUICmdPacketBase
{
public:
	IntList			LibList;

	CmdGenerateDotColorMatchings(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~CmdGenerateDotColorMatchings(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAddDotColorMatching : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;
	QString		ItemName;

	GUICmdAddDotColorMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdDeleteDotColorMatchingByName : public GUICmdPacketBase
{
public:
	QString		ItemName;

	GUICmdDeleteDotColorMatchingByName(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdDotColorMatchingDrawModePacket : public GUIDirectMessage
{
public:
	bool	ModeShowArea;
	bool	ModeShowRotation;
	bool	ModeShowDiv	;
	bool	ModeShowFlat;
	bool	ModeShowBackGround;
	CmdDotColorMatchingDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDotColorMatchingDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DotColorMatchingImagePanel;
class	CmdDotColorMatchingDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	DotColorMatchingImagePanel	*ImagePanelPoint;

	CmdDotColorMatchingDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdDotColorMatchingDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDotColorMatchingShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	IntList		LayerList;

	CmdDotColorMatchingShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDotColorMatchingShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DotColorMatchingDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ModeShowArea;
	bool	ModeShowRotation;
	bool	ModeShowDiv	;
	bool	ModeShowFlat;
	bool	ModeShowBackGround;
	QColor	ColorPickup;
	QColor	DotColorMatchingColor0;
	QColor	DotColorMatchingColor1;
	QColor	DotColorMatchingColor2;
	QColor	DotColorMatchingColor3;
	QColor	DotColorMatchingColor4;
	QColor	DotColorMatchingColor5;
	QColor	DotColorMatchingColor6;
	QColor	DotColorMatchingColor7;

	DotColorMatchingDrawAttr(void):ServiceForLayers(NULL){	ModeShowBackGround=false;}
	DotColorMatchingDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	DotColorMatchingDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, const QColor &pickupcol ,int ptranparentLevel
				, const QColor &DotColorMatchingColor0
				, const QColor &DotColorMatchingColor1
				, const QColor &DotColorMatchingColor2
				, const QColor &DotColorMatchingColor3
				, const QColor &DotColorMatchingColor4
				, const QColor &DotColorMatchingColor5
				, const QColor &DotColorMatchingColor6
				, const QColor &DotColorMatchingColor7);

	void	Initial(void);

	DotColorMatchingDrawAttr	&operator=(DotColorMatchingDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	DotColorMatchingDrawAttr	&DotColorMatchingDrawAttr::operator=(DotColorMatchingDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	ModeShowArea		=src.ModeShowArea		;
	ModeShowRotation	=src.ModeShowRotation	;
	ModeShowDiv			=src.ModeShowDiv		;
	ModeShowFlat		=src.ModeShowFlat		;
	ModeShowBackGround	=src.ModeShowBackGround	;
	ColorPickup		=src.ColorPickup;
	DotColorMatchingColor0	=src.DotColorMatchingColor0;
	DotColorMatchingColor1	=src.DotColorMatchingColor1;
	DotColorMatchingColor2	=src.DotColorMatchingColor2;
	DotColorMatchingColor3	=src.DotColorMatchingColor3;
	DotColorMatchingColor4	=src.DotColorMatchingColor4;
	DotColorMatchingColor5	=src.DotColorMatchingColor5;
	DotColorMatchingColor6	=src.DotColorMatchingColor6;
	DotColorMatchingColor7	=src.DotColorMatchingColor7;
	return *this;
}
inline	bool	DotColorMatchingDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,ModeShowArea	)==false)		return false;
	if(::Save(f,ModeShowRotation)==false)		return false;
	if(::Save(f,ModeShowDiv		)==false)		return false;
	if(::Save(f,ModeShowFlat	)==false)		return false;
	if(::Save(f,ModeShowBackGround	)==false)	return false;
	if(::Save(f,ColorPickup		)==false)		return false;
	if(::Save(f,DotColorMatchingColor0)==false)	return false;
	if(::Save(f,DotColorMatchingColor1)==false)	return false;
	if(::Save(f,DotColorMatchingColor2)==false)	return false;
	if(::Save(f,DotColorMatchingColor3)==false)	return false;
	if(::Save(f,DotColorMatchingColor4)==false)	return false;
	if(::Save(f,DotColorMatchingColor5)==false)	return false;
	if(::Save(f,DotColorMatchingColor6)==false)	return false;
	if(::Save(f,DotColorMatchingColor7)==false)	return false;
	return true;
}
inline	bool	DotColorMatchingDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,ModeShowArea	)==false)		return false;
	if(::Load(f,ModeShowRotation)==false)		return false;
	if(::Load(f,ModeShowDiv		)==false)		return false;
	if(::Load(f,ModeShowFlat	)==false)		return false;
	if(::Load(f,ModeShowBackGround	)==false)	return false;
	if(::Load(f,ColorPickup		)==false)		return false;
	if(::Load(f,DotColorMatchingColor0)==false)	return false;
	if(::Load(f,DotColorMatchingColor1)==false)	return false;
	if(::Load(f,DotColorMatchingColor2)==false)	return false;
	if(::Load(f,DotColorMatchingColor3)==false)	return false;
	if(::Load(f,DotColorMatchingColor4)==false)	return false;
	if(::Load(f,DotColorMatchingColor5)==false)	return false;
	if(::Load(f,DotColorMatchingColor6)==false)	return false;
	if(::Load(f,DotColorMatchingColor7)==false)	return false;
	return true;
}

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

class	BrightnessMapList : public NPList<BrightnessMapList>
{
public:
	int	Layer;
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

class	DotColorMatchingItem;
class	GUICmdSendAddManualDotColorMatching : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualDotColorMatching(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedDotColorMatching : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedDotColorMatching(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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
	CmdExecuteMouseLDown(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteMouseRDownWithShift : public GUIDirectMessage
{
public:
	IntList		LayerList;
	CmdExecuteMouseRDownWithShift(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteMouseRDownWithShift(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqSelectedDotColorMatchingItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedDotColorMatchingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedDotColorMatchingItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedDotColorMatchingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================
class	DotColorMatchingInfoList : public NPList<DotColorMatchingInfoList>
{
public:
	int		LibID;
	IntList	DotColorMatchingCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	DotColorMatchingInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(DotColorMatchingCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	DotColorMatchingInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(DotColorMatchingCount.Load(f)==false)
		return false;
	return true;
}



class	GUICmdReqDotColorMatchingInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqDotColorMatchingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDotColorMatchingInfoList : public GUICmdPacketBase
{
public:
	NPListPack<DotColorMatchingInfoList>	DotColorMatchingInfos;

	GUICmdSendDotColorMatchingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqDotColorMatchingFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqDotColorMatchingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDotColorMatchingFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	DotColorMatchingItem	*DotColorMatchingInfoOnMouse[100];

	GUICmdAckDotColorMatchingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckDotColorMatchingFromList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
/*
class	GUICmdReqSetButtonMode : public GUICmdPacketBase
{
public:
	enum	ButtonMode
	{
		_LibraryTest	=1
		,_CreateDotColorMatching	=2
	}Mode;
	QString	InstForm;

	GUICmdReqSetButtonMode(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqSetButtonMode : public GUIDirectMessage
{
public:
	GUICmdReqSetButtonMode::ButtonMode	Mode;

	CmdReqSetButtonMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSetButtonMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
*/

class	GUICmdReqItemListForPageContainer : public GUICmdPacketBase
{
public:
	GUICmdReqItemListForPageContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemListForPageContainer : public GUICmdPacketBase
{
public:
	ItemListForPageContainer	ItemListForPageData;

	GUICmdAckItemListForPageContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//================================================================================================

class	GUICmdReqBlockListInfo : public GUICmdPacketBase
{
public:
	BlockListInfoContainer	*BlockListInfoContainerData;

	GUICmdReqBlockListInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBlockListInfo : public GUICmdPacketBase
{
public:
	BlockListInfoContainer	BlockListInfoContainerData;

	GUICmdAckBlockListInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//================================================================================================

class	GUICmdSelectByLibOutline : public GUICmdPacketBase	//���C�u�����ɂ����A�C�e���I���v���R�}���h
{
public:
	bool					OutlineMode;
	SelectLibListContainer	SelectedList;

	GUICmdSelectByLibOutline(LayersBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//================================================================================================

class	GUICmdSetItemsByLibID : public GUICmdPacketBase	//���C�u�����ɂ����A�C�e���I���v���R�}���h
{
public:
	int		ItemID;		//-1: All Item with LibID
	int		LibID;
    bool    AvailableMasterNo;
    int     MasterNoOriginCode;

    bool    AvailableSubBlock;
    AlgorithmLibraryListContainer	SubBlockList;
	int		ExpandToSubBlock;

	GUICmdSetItemsByLibID(LayersBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqItemsByLibID : public GUICmdPacketBase
{
public:
	int	Page;
	int	ItemID;	//-1: All items with LibID
	int	LibID;

    int     MasterNoOriginCode;
    AlgorithmLibraryListContainer	SubLibIDs;
	int		ExpandToSubBlock;

	GUICmdReqItemsByLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemsByLibID : public GUICmdPacketBase
{
public:
    int     MasterNoOriginCode;
    AlgorithmLibraryListContainer	SubLibIDs;
	int		ExpandToSubBlock;

	GUICmdAckItemsByLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	SetData(DotColorMatchingItem *Item);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================

class	GUICmdSetSpecialData : public GUICmdPacketBase
{
public:
	QByteArray	SpecialData;

	GUICmdSetSpecialData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//==============================================================

class	GUICmdReqSelectedItemLib : public GUICmdPacketBase
{
public:
	IntList	*SelectedItemLibID;

	GUICmdReqSelectedItemLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSelectedItemLib : public GUICmdPacketBase
{
public:
	IntList	SelectedItemLibID;

	GUICmdAckSelectedItemLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif