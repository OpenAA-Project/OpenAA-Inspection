/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\XPropertyEulerRingPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYEULERRINGPACKET_H)
#define	XPROPERTYEULERRINGPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XEulerRingLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XEulerRing.h"

class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//EulerRingLibrary	*LibPoint;
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

class	GUICmdGenerateEulerRings : public GUICmdPacketBase
{
public:
	IntList			LibList;

	GUICmdGenerateEulerRings(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateEulerRings(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdEulerRingDrawModePacket : public GUIDirectMessage
{
public:
	EulerRingDrawAttr::DrawMode	Mode;

	CmdEulerRingDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	EulerRingImagePanel;
class	CmdEulerRingDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	EulerRingImagePanel	*ImagePanelPoint;

	CmdEulerRingDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdEulerRingShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	enum{
		_Block 	}Mode;

	CmdEulerRingShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
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

class	EulerRingItem;
class	GUICmdSendAddManualEulerRing : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;

	GUICmdSendAddManualEulerRing(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedEulerRing : public GUICmdPacketBase
{
public:
	QByteArray	BItem;

	GUICmdSendModifySelectedEulerRing(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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
};

class	CmdExecuteMouseRDownWithShift : public GUIDirectMessage
{
public:
	CmdExecuteMouseRDownWithShift(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdReqSelectedEulerRingItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedEulerRingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedEulerRingItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedEulerRingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================


class	GUICmdReqEulerRingInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqEulerRingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendEulerRingInfoList : public GUICmdPacketBase
{
public:
	NPListPack<EulerRingInfoList>	EulerRingInfos;

	GUICmdSendEulerRingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqEulerRingFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqEulerRingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckEulerRingFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	EulerRingItem	*EulerRingInfoOnMouse[100];

	GUICmdAckEulerRingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckEulerRingFromList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif
