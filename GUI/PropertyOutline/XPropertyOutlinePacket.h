/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOutline\XPropertyOutlinePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYOUTLINEPACKET_H)
#define	XPROPERTYOUTLINEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"

class	OutlineInspectLibrary;
class	OutlineItem;


class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//OutlineInspectLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList					LayerList;

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

class	GUICmdGenerateOutlines : public GUICmdPacketBase
{
public:
	IntList			LayerList;
	IntList			LibList;

	GUICmdGenerateOutlines(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateOutlines(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	OutlineImagePanel;
class	CmdOutlineDrawEnd : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	OutlineImagePanel	*ImagePanelPoint;

	CmdOutlineDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdOutlineDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdOutlineShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	enum{
		_Block 	}Mode;

	CmdOutlineShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdOutlineShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdOutlineDrawModePacket : public GUIDirectMessage
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedBlock
	}Mode;
	enum	DrawType{
		_Area
		,_Edge
		,_Inside
	}DType;

	CmdOutlineDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdOutlineDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	OutlineDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CmdOutlineDrawModePacket::DrawMode	Mode;
	CmdOutlineDrawModePacket::DrawType	DType;
	QColor		ColorPickup	;

	OutlineDrawAttr(void):ServiceForLayers(NULL){}
	OutlineDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	OutlineDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel);

	void	Initial(void);

	OutlineDrawAttr	&operator=(OutlineDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	OutlineDrawAttr	&OutlineDrawAttr::operator=(OutlineDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	ColorPickup	=src.ColorPickup;
	return *this;
}
inline	bool	OutlineDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	OutlineDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}

//========================================================================================


class	GUICmdReqAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	FlexArea	Area;

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
	void	MakeLists(FlexArea &area ,int localPage,LayersBase *Base);
};

class	GUICmdSendAddManualOutline : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;

	GUICmdSendAddManualOutline(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedOutline : public GUICmdPacketBase
{
public:
	QByteArray	BItem;

	GUICmdSendModifySelectedOutline(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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
	CmdExecuteMouseRDownWithShift(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteMouseRDownWithShift(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqSelectedOutlineItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedOutlineItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedOutlineItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedOutlineItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================
class	OutlineInfoList : public NPList<OutlineInfoList>
{
public:
	int		LibID;
	IntList	OutlineCount;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	OutlineInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(OutlineCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	OutlineInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(OutlineCount.Load(f)==false)
		return false;
	return true;
}



class	GUICmdReqOutlineInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqOutlineInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOutlineInfoList : public GUICmdPacketBase
{
public:
	NPListPack<OutlineInfoList>	OutlineInfos;

	GUICmdSendOutlineInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqOutlineFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqOutlineFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckOutlineFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	OutlineItem	*OutlineInfoOnMouse[100];

	GUICmdAckOutlineFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckOutlineFromList(void);

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
		,_CreateBlock	=2
	}Mode;
	enum	DrawType{
		_Area
		,_Edge
		,_Inside
	}DType;
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
	GUICmdReqSetButtonMode::DrawType	DType;

	CmdReqSetButtonMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSetButtonMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	GUICmdReqRGBStockFromArea : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	FlexArea	Area;

	GUICmdReqRGBStockFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendRGBStockFromArea : public GUICmdPacketBase
{
public:
	RGBStock	RGBColors;

	GUICmdSendRGBStockFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif

