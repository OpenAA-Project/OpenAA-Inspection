/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDotMatching\XPropertyDotMatchingPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYDotMatchingPACKET_H)
#define	XPROPERTYDotMatchingPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDotMatchingLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//DotMatchingLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;

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

class	GUICmdGenerateDotMatchings : public GUICmdPacketBase
{
public:
	IntList			LibList;
	IntList			LayerList;

	GUICmdGenerateDotMatchings(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateDotMatchings(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdDotMatchingDrawModePacket : public GUIDirectMessage
{
public:

	CmdDotMatchingDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDotMatchingDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DotMatchingImagePanel;
class	CmdDotMatchingDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	DotMatchingImagePanel	*ImagePanelPoint;

	CmdDotMatchingDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdDotMatchingDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDotMatchingShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	IntList		LayerList;

	CmdDotMatchingShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDotMatchingShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DotMatchingDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QColor		ColorPickup;
	QColor		DotMatchingColor0;
	QColor		DotMatchingColor1;
	QColor		DotMatchingColor2;
	QColor		DotMatchingColor3;
	QColor		DotMatchingColor4;
	QColor		DotMatchingColor5;
	QColor		DotMatchingColor6;
	QColor		DotMatchingColor7;

	DotMatchingDrawAttr(void):ServiceForLayers(NULL){}
	DotMatchingDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	DotMatchingDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &DotMatchingColor0
				, QColor &DotMatchingColor1
				, QColor &DotMatchingColor2
				, QColor &DotMatchingColor3
				, QColor &DotMatchingColor4
				, QColor &DotMatchingColor5
				, QColor &DotMatchingColor6
				, QColor &DotMatchingColor7);

	void	Initial(void);

	DotMatchingDrawAttr	&operator=(DotMatchingDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	DotMatchingDrawAttr	&DotMatchingDrawAttr::operator=(DotMatchingDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	ColorPickup	=src.ColorPickup;
	DotMatchingColor0	=src.DotMatchingColor0;
	DotMatchingColor1	=src.DotMatchingColor1;
	DotMatchingColor2	=src.DotMatchingColor2;
	DotMatchingColor3	=src.DotMatchingColor3;
	DotMatchingColor4	=src.DotMatchingColor4;
	DotMatchingColor5	=src.DotMatchingColor5;
	DotMatchingColor6	=src.DotMatchingColor6;
	DotMatchingColor7	=src.DotMatchingColor7;
	return *this;
}
inline	bool	DotMatchingDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	DotMatchingDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,ColorPickup)==false)
		return false;
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

class	DotMatchingItem;
class	GUICmdSendAddManualDotMatching : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualDotMatching(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedDotMatching : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedDotMatching(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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

class	GUICmdReqSelectedDotMatchingItemAttr : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	GUICmdReqSelectedDotMatchingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedDotMatchingItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedDotMatchingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base ,IntList &LayerList);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================
class	DotMatchingInfoList : public NPList<DotMatchingInfoList>
{
public:
	int		LibID;
	IntList	DotMatchingCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	DotMatchingInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(DotMatchingCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	DotMatchingInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(DotMatchingCount.Load(f)==false)
		return false;
	return true;
}



class	GUICmdReqDotMatchingInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqDotMatchingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDotMatchingInfoList : public GUICmdPacketBase
{
public:
	NPListPack<DotMatchingInfoList>	DotMatchingInfos;

	GUICmdSendDotMatchingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqDotMatchingFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqDotMatchingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDotMatchingFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	DotMatchingItem	*DotMatchingInfoOnMouse[100];

	GUICmdAckDotMatchingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckDotMatchingFromList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSetButtonMode : public GUICmdPacketBase
{
public:
	enum	ButtonMode
	{
		_LibraryTest	=1
		,_CreateDotMatching	=2
	}Mode;
	QString	InstForm;

	GUICmdReqSetButtonMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

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


#endif
