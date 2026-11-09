/*
 * Copyright (C) 2024
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


#if	!defined(XPROPERTBLOCKYPACKET_H)
#define	XPROPERTBLOCKYPACKET_H


//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XBlockLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XPropertyBlockCommon.h"
#include "XBlockInspectionCommon.h"

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