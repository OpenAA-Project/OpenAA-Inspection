/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorDifference\XPropertyColorDifferencePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYColorDifferencePACKET_H)
#define	XPROPERTYColorDifferencePACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XColorDifference.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	CmdColorDifferenceDrawModePacket : public GUIDirectMessage
{
public:
	bool	ModeShowItem;
	bool	ModeShowRegulation;
	CmdColorDifferenceDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdColorDifferenceDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ColorDifferenceImagePanel;
class	CmdColorDifferenceDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	ColorDifferenceImagePanel	*ImagePanelPoint;

	CmdColorDifferenceDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdColorDifferenceDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdColorDifferenceShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	IntList		LayerList;

	CmdColorDifferenceShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdColorDifferenceShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

class	ColorDifferenceItem;
class	GUICmdSendAddManualColorDifference : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	IntList		LayerList;
	int			LibID;

	GUICmdSendAddManualColorDifference(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedColorDifference : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedColorDifference(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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

class	GUICmdReqSelectedColorDifferenceItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedColorDifferenceItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedColorDifferenceItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedColorDifferenceItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================
class	ColorDifferenceInfoList : public NPList<ColorDifferenceInfoList>
{
public:
	int		LibID;
	IntList	ColorDifferenceCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	ColorDifferenceInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(ColorDifferenceCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	ColorDifferenceInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(ColorDifferenceCount.Load(f)==false)
		return false;
	return true;
}



class	GUICmdReqColorDifferenceInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqColorDifferenceInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendColorDifferenceInfoList : public GUICmdPacketBase
{
public:
	NPListPack<ColorDifferenceInfoList>	ColorDifferenceInfos;

	GUICmdSendColorDifferenceInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqColorDifferenceFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqColorDifferenceFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckColorDifferenceFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	ColorDifferenceItem	*ColorDifferenceInfoOnMouse[100];

	GUICmdAckColorDifferenceFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckColorDifferenceFromList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


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


class	GUICmdAddColorDifferenceOK : public GUICmdPacketBase
{
public:
	GUICmdAddColorDifferenceOK(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAddColorDifferenceNG : public GUICmdPacketBase
{
public:
	GUICmdAddColorDifferenceNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdRegistInFlowON : public GUICmdPacketBase
{
public:
	GUICmdRegistInFlowON(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdRegistInFlowOFF : public GUICmdPacketBase
{
public:
	GUICmdRegistInFlowOFF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetStatisticThreshold : public GUICmdPacketBase
{
public:
	double	SigmaH;
	double	SigmaS;
	double	SigmaV;

	GUICmdSetStatisticThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdClearFlowStack : public GUICmdPacketBase
{
public:
	GUICmdClearFlowStack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqFlowData : public GUICmdPacketBase
{
public:
	GUICmdReqFlowData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckFlowData : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdAckFlowData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSendFlowData : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendFlowData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdAutoGenerate : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;

	GUICmdAutoGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
