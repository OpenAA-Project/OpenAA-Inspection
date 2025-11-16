#if	!defined(PropertyCheckBrightnessPacket_h)
#define	PropertyCheckBrightnessPacket_h


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XCheckBrightness.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"

class	CmdCreateCheckBrightnessManualPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	CmdCreateCheckBrightnessManualPacket(LayersBase *base):GUIDirectMessage(base){}
};

//----------------------------------------------------------------------------------


class	GUICmdReqGridList : public GUICmdPacketBase
{
public:
	GUICmdReqGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendGridList : public GUICmdPacketBase
{
public:
	CheckBrightnessInfoContainer		GridList;

	GUICmdSendGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdAddAreaManual : public GUICmdPacketBase
{
public:
	QString		ItemName;
	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		RegNumber;
	CheckBrightnessItem::_Condition	Condition;
	IntList		LayerList;
	FlexArea	Area;

	GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemInfo : public GUICmdPacketBase
{
public:
	int		ItemID;
	int		Layer;

	GUICmdReqItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemInfo : public GUICmdPacketBase
{
public:
	int			ItemID;
	QString		ItemName;
	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		RegNumber;
	CheckBrightnessItem::_Condition	Condition;

	GUICmdSendItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetItemInfo : public GUICmdPacketBase
{
public:
	int			ItemID;
	int			Layer;
	QString		ItemName;
	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		RegNumber;
	CheckBrightnessItem::_Condition	Condition;

	GUICmdSetItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


#endif