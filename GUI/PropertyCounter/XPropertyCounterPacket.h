#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyCounter\XPropertyCounterPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYCounterPACKET_H)
#define	XPROPERTYCounterPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XCounter.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>


class	CmdCounterDrawModePacket : public GUIDirectMessage
{
public:
	bool	ShowExecuteMap;
	bool	ShowItems;
	CmdCounterDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCounterDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CounterImagePanel;
class	CmdCounterDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	CounterImagePanel	*ImagePanelPoint;

	CmdCounterDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdCounterDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

//=============================================================================

class	GUICmdReqItemImage : public GUICmdPacketBase
{
public:
	int	Width,Height;

	GUICmdReqItemImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckItemImage : public GUICmdPacketBase
{
public:
	QImage		ItemImage;
	QImage		ItemBackGround;
	QImage		ItemImageWithMask;
	DoubleList	Angles;
	QList<QImage>	RotatedImages;

	GUICmdAckItemImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdAddAreaManual : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;

	GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=============================================================================

class	GUICmdAddMaskForCounter: public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;

	GUICmdAddMaskForCounter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRemoveMask: public GUICmdPacketBase
{
public:
	GUICmdRemoveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=============================================================================

class	GUICmdRegisterBackGround : public GUICmdPacketBase
{
public:
	bool	SetBackGround;

	GUICmdRegisterBackGround(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//=============================================================================

class	GUICmdReqResultCounter : public GUICmdPacketBase
{
public:

	GUICmdReqResultCounter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);


	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckResultCounter : public GUICmdPacketBase
{
public:
	int		Count;
	bool	TimeOut;
	GUICmdAckResultCounter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqAdoptedRate: public GUICmdPacketBase
{
public:

	GUICmdReqAdoptedRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckAdoptedRate : public GUICmdPacketBase
{
public:
	double		AdoptedRate;

	GUICmdAckAdoptedRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSendAdoptedRate : public GUICmdPacketBase
{
public:
	double		AdoptedRate;

	GUICmdSendAdoptedRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdReqAdoptPixelsRate: public GUICmdPacketBase
{
public:

	GUICmdReqAdoptPixelsRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckAdoptPixelsRate : public GUICmdPacketBase
{
public:
	double		AdoptPixelsRate;

	GUICmdAckAdoptPixelsRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSendAdoptPixelsRate : public GUICmdPacketBase
{
public:
	double		AdoptPixelsRate;

	GUICmdSendAdoptPixelsRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};






class	GUICmdReqFocusLevel: public GUICmdPacketBase
{
public:

	GUICmdReqFocusLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckFocusLevel : public GUICmdPacketBase
{
public:
	int		FocusLevel;

	GUICmdAckFocusLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSendFocusLevel : public GUICmdPacketBase
{
public:
	int		FocusLevel;

	GUICmdSendFocusLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendOutsideCalc : public GUICmdPacketBase
{
public:
	bool		OutsideCalc;

	GUICmdSendOutsideCalc(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//=============================================================================

class	GUICmdReqItemArea : public GUICmdPacketBase
{
public:
	GUICmdReqItemArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckItemArea : public GUICmdPacketBase
{
public:
	PureFlexAreaListContainer	Areas;

	GUICmdAckItemArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//=============================================================================

class	GUICmdSetFilterMode : public GUICmdPacketBase
{
public:
	bool	FilterON;

	GUICmdSetFilterMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//=============================================================================

class	GUICmdReqMaskCount : public GUICmdPacketBase
{
public:
	GUICmdReqMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckMaskCount : public GUICmdPacketBase
{
public:
	int	MaskCount;

	GUICmdAckMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
#endif
