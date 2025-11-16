#if	!defined(PropertySkipMarkPacket_h)
#define	PropertySkipMarkPacket_h


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XSkipMark.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"

class	CmdCreateSkipMarkManualPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	CmdCreateSkipMarkManualPacket(LayersBase *base):GUIDirectMessage(base){}
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
	SkipMarkInfoContainer		GridList;

	GUICmdSendGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdAddAreaManual : public GUICmdPacketBase
{
public:
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	int32		Layer;
	FlexArea	Area;
	QString		ItemName;

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
	int32		ItemID;
	int32		Layer;
		
	QString		ItemName;

	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	GUICmdSendItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetItemInfo : public GUICmdPacketBase
{
public:
	int32		ItemID;
	int32		Layer;
		
	QString		ItemName;

	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	GUICmdSetItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	NamingInfoList : public NPListSaveLoad<NamingInfoList>
{
public:
	int32	ItemID;
	QString	ItemName;
	int		x1,y1,x2,y2;

	NamingInfoList(void){	ItemID=-1;	}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	NamingInfoListContainer : public NPListPackSaveLoad<NamingInfoList>
{
public:
	NamingInfoListContainer(void){}
	virtual	NamingInfoList	*Create(void)	{	return new NamingInfoList();	}
};


class	GUICmdReqNamingList : public GUICmdPacketBase
{
public:
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int			Layer;

	GUICmdReqNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingList : public GUICmdPacketBase
{
public:
	NamingInfoListContainer		NamingContainer;

	GUICmdSendNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqSource : public GUICmdPacketBase
{
public:
	int	Layer;
	int	ItemID;

	GUICmdReqSource(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSource : public GUICmdPacketBase
{
public:
	SkipMarkSourceAlgoContainer		Sources;

	GUICmdSendSource(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqSourceItemInfo : public GUICmdPacketBase
{
public:
	int		Layer;
	QString	AlgoRoot;
	QString	AlgoName;
	IntList	IDList;

	GUICmdReqSourceItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSourceItemInfo : public GUICmdPacketBase
{
public:
	ItemInfoContainer		ItemInfos;

	GUICmdSendSourceItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdModifySourceItems : public GUICmdPacketBase
{
public:
	int		Layer;
	int		ItemID;
	SkipMarkSourceAlgoContainer		Sources;

	GUICmdModifySourceItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqSourceAllItemsInfo : public GUICmdPacketBase
{
public:
	int		Layer;
	QString	AlgoRoot;
	QString	AlgoName;

	GUICmdReqSourceAllItemsInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSourceAllItemsInfo : public GUICmdPacketBase
{
public:
	ItemInfoContainer		ItemInfos;

	GUICmdSendSourceAllItemsInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif