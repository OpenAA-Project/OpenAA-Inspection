/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\XPropertyBlockPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTBLOCKYPACKET_H)
#define	XPROPERTBLOCKYPACKET_H


//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XBlockLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XPropertyBlockCommon.h"

class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//BlockLibrary	*LibPoint;
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

class	GUICmdGenerateBlocks : public GUICmdPacketBase
{
public:
	IntList			LibList;
	IntList			LayerList;

	GUICmdGenerateBlocks(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateBlocks(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdBlockDrawModePacket : public GUIDirectMessage
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
		,_BeforeShrink
	}DType;
	bool	DrawDirUp;
	bool	DrawDirLeft;
	bool	DrawDirRight;
	bool	DrawDirBottom;
	bool	DrawDirSkip;
	bool	DrawOmitMatchLineArea;

	CmdBlockDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdBlockDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	BlockImagePanel;
class	CmdBlockDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	BlockImagePanel	*ImagePanelPoint;

	CmdBlockDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdBlockDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdBlockShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	IntList		LayerList;
	enum{
		_Block 	}Mode;

	CmdBlockShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdBlockShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	BlockDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CmdBlockDrawModePacket::DrawMode	Mode;
	CmdBlockDrawModePacket::DrawType	DType;
	bool	DrawDirUp;
	bool	DrawDirLeft;
	bool	DrawDirRight;
	bool	DrawDirBottom;
	bool	DrawDirSkip;
	bool	DrawOmitMatchLineArea;

	QColor		ColorPickup;
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;

	BlockDrawAttr(void):ServiceForLayers(NULL){}
	BlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	BlockDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &blockColor0
				, QColor &blockColor1
				, QColor &blockColor2
				, QColor &blockColor3
				, QColor &blockColor4
				, QColor &blockColor5
				, QColor &blockColor6
				, QColor &blockColor7);

	void	Initial(void);

	BlockDrawAttr	&operator=(BlockDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	BlockDrawAttr	&BlockDrawAttr::operator=(BlockDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode			=src.Mode;
	DrawDirUp		=src.DrawDirUp		;
	DrawDirLeft		=src.DrawDirLeft	;	
	DrawDirRight	=src.DrawDirRight	;
	DrawDirBottom	=src.DrawDirBottom	;
	DrawDirSkip		=src.DrawDirSkip	;
	ColorPickup		=src.ColorPickup;
	BlockColor0		=src.BlockColor0;
	BlockColor1		=src.BlockColor1;
	BlockColor2		=src.BlockColor2;
	BlockColor3		=src.BlockColor3;
	BlockColor4		=src.BlockColor4;
	BlockColor5		=src.BlockColor5;
	BlockColor6		=src.BlockColor6;
	BlockColor7		=src.BlockColor7;
	return *this;
}
inline	bool	BlockDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	if(::Save(f,DrawDirUp)==false)
		return false;
	if(::Save(f,DrawDirLeft)==false)
		return false;
	if(::Save(f,DrawDirRight)==false)
		return false;
	if(::Save(f,DrawDirBottom)==false)
		return false;
	if(::Save(f,DrawDirSkip)==false)
		return false;
	return true;
}
inline	bool	BlockDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	if(::Load(f,DrawDirUp)==false)
		return false;
	if(::Load(f,DrawDirLeft)==false)
		return false;
	if(::Load(f,DrawDirRight)==false)
		return false;
	if(::Load(f,DrawDirBottom)==false)
		return false;
	if(::Load(f,DrawDirSkip)==false)
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

class	BlockItem;
class	GUICmdSendAddManualBlock : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedBlock : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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

class	GUICmdReqSelectedBlockItemAttr : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	GUICmdReqSelectedBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedBlockItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base ,IntList &LayerList);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqShrinkArea : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	int			ShrinkDot;

	GUICmdReqShrinkArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqShrinkHalf : public GUICmdPacketBase
{
public:
	IntList		LayerList;

	GUICmdReqShrinkHalf(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqExpandHalf : public GUICmdPacketBase
{
public:
	IntList		LayerList;

	GUICmdReqExpandHalf(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================
class	BlockInfoList : public NPList<BlockInfoList>
{
public:
	int		LibID;
	IntList	BlockCount;
	int		Page;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	BlockInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(BlockCount.Save(f)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	return true;
}
inline	bool	BlockInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(BlockCount.Load(f)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	return true;
}



class	GUICmdReqBlockInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendBlockInfoList : public GUICmdPacketBase
{
public:
	NPListPack<BlockInfoList>	BlockInfos;

	GUICmdSendBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqBlockFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBlockFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	BlockItem	*BlockInfoOnMouse[100];

	GUICmdAckBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckBlockFromList(void);

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

class	GUICmdSetNGSizeInBlock : public GUICmdPacketBase
{
public:
	int LibID;
	int BlockType;
	int NGSize;

	GUICmdSetNGSizeInBlock(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetSearchDotInBlock : public GUICmdPacketBase
{
public:
	int LibID;
	int SearchDot;

	GUICmdSetSearchDotInBlock(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdUpdateBlockCommon : public GUICmdPacketBase
{
public:
	int		LibID;
	SetThresholdBlockInfo	ThresholdInfo;

	GUICmdUpdateBlockCommon(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdGenerateBlockCommon : public GUICmdPacketBase
{
public:
	BlockLibraryWithThresholdContainer	Infos;

	GUICmdGenerateBlockCommon(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

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

class	GUICmdChangeBlocksThreshold : public GUICmdPacketBase
{
public:
	int			BlockLibID;
	QByteArray	InfosData;

	GUICmdChangeBlocksThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
