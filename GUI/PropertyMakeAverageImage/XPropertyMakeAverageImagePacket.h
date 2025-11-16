#if	!defined(XPropertyMakeAverageImagePacket_h)
#define	XPropertyMakeAverageImagePacket_h

#include "XGUIPacketForDLL.h"
#include "XMakeAverageImage.h"

class	CmdMakeAverageImageDrawAttr: public GUIDirectMessage
{
public:
	MakeAverageImageDrawAttr::_DrawMode	DrawMode;
	bool	ModeShowItems;
	int		VariableStrength;

	CmdMakeAverageImageDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAverageImageDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdMakeAverageImageDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdMakeAverageImageDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdMakeAverageImageDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class GUICmdSendAddMakeAverageImageUsageAreaItem : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;

	GUICmdSendAddMakeAverageImageUsageAreaItem(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};



class	GUICmdSetAverageToMaster: public GUICmdPacketBase
{
public:

	GUICmdSetAverageToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqAverageCount: public GUICmdPacketBase
{
public:
	GUICmdReqAverageCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAverageCount: public GUICmdPacketBase
{
public:
	int		AddedCount;

	GUICmdAckAverageCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdResetAverage: public GUICmdPacketBase
{
public:

	GUICmdResetAverage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdReqReset: public GUIDirectMessage
{
public:
	CmdReqReset(LayersBase *base) :GUIDirectMessage(base) {}
	CmdReqReset(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};


#endif