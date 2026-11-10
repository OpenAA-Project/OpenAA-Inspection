/*
 * Copyright (C) 2023
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


#if	!defined(XPROPERTYCOLORBLOCKYPACKET_H)
#define	XPROPERTYCOLORBLOCKYPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XTrueColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XTrueColorCommon.h"

class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//TrueColorBlockLibrary	*LibPoint;
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

class	GUICmdGenerateTrueColorBlocks : public GUICmdPacketBase
{
public:
	IntList			LibList;

	GUICmdGenerateTrueColorBlocks(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateTrueColorBlocks(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	TrueColorBlockImagePanel;
class	CmdTrueColorBlockDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	TrueColorBlockImagePanel	*ImagePanelPoint;

	CmdTrueColorBlockDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdTrueColorBlockDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdTrueColorBlockShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	enum{
		_Block 	}Mode;

	CmdTrueColorBlockShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdTrueColorBlockShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

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

class	TrueColorBlockItem;
class	GUICmdSendAddManualTrueColorBlock : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;

	GUICmdSendAddManualTrueColorBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedTrueColorBlock : public GUICmdPacketBase
{
public:
	QByteArray	BItem;

	GUICmdSendModifySelectedTrueColorBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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

class	GUICmdReqSelectedTrueColorBlockItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedTrueColorBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedTrueColorBlockItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedTrueColorBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================


class	GUICmdReqTrueColorBlockInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqTrueColorBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendTrueColorBlockInfoList : public GUICmdPacketBase
{
public:
	NPListPack<TrueColorBlockInfoList>	TrueColorBlockInfos;

	GUICmdSendTrueColorBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqTrueColorBlockFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqTrueColorBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckTrueColorBlockFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	TrueColorBlockItem	*TrueColorBlockInfoOnMouse[100];

	GUICmdAckTrueColorBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckTrueColorBlockFromList(void);

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

//==========================================================================

class	GUICmdReqRGBStockFromArea : public GUICmdPacketBase
{
public:
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