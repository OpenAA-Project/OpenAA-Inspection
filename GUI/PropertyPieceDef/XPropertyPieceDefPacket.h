#if	!defined(XPROPERTYPIECEDEFPACKET_H)	
#define	XPROPERTYPIECEDEFPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XPieceDef.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"

class	CmdCreatePieceDefManualPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	CmdCreatePieceDefManualPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddPieceAreaManual : public GUICmdPacketBase
{
public:
	FlexArea		Area;

	GUICmdAddPieceAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSeed : public GUICmdPacketBase
{
public:
	GUICmdReqSeed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{		return true;	}
	virtual	bool	Save(QIODevice *f)	{		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSeed : public GUICmdPacketBase
{
public:
	FlexAreaImageBuffer		Seed;
	FlexArea				OriginalArea;
	int						SweepNumber;
	GUICmdAckSeed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSweepSeed : public GUICmdPacketBase
{
public:
	FlexAreaImageBuffer		Seed;
	FlexArea				OriginalArea;
	int						SweepNumber;
	
	GUICmdSweepSeed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------------------------------------------


class	GUICmdReqDefList : public GUICmdPacketBase
{
public:
	GUICmdReqDefList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDefList : public GUICmdPacketBase
{
public:
	PieceDefInfoContainer		DefList;

	GUICmdSendDefList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdCopyItemFromOrg : public GUICmdPacketBase
{
public:
	int			OrgGlobalPage;
	QByteArray	SeedData;
	int				SweepNumber;
	FlexArea		OriginalArea;
	int				SeedCount;

	GUICmdCopyItemFromOrg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



class	GUICmdReqSeedData : public GUICmdPacketBase
{
public:
	GUICmdReqSeedData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{		return true;	}
	virtual	bool	Save(QIODevice *f)	{		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSeedData : public GUICmdPacketBase
{
public:
	QByteArray		SeedData;
	int				SeedCount;
	int				SweepNumber;
	FlexArea		OriginalArea;

	GUICmdAckSeedData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//----------------------------------------------------------------------------------

class	GUICmdMatchItems : public GUICmdPacketBase
{
public:
	GUICmdMatchItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
#endif