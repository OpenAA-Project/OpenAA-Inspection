#if	!defined(XPROPERTYFrameDEFPACKET_H)	
#define	XPROPERTYFrameDEFPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XFrameDef.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"

class	CmdReqDrawAttrPacket : public GUIDirectMessage
{
public:
	bool	Overlapped;

	CmdReqDrawAttrPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateFrameDefManualPacket : public GUIDirectMessage
{
public:
	FlexArea		Area;

	CmdCreateFrameDefManualPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddFrameAreaManual : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			GroupNumber;
	int			FrameNumber;
	bool		Original;

	GUICmdAddFrameAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------------------------------------------

class	GUICmdReqFrameContainer : public GUICmdPacketBase
{
public:

	GUICmdReqFrameContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckFrameContainer : public GUICmdPacketBase
{
public:
	FrameContainer	ItemContainer;

	GUICmdAckFrameContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//----------------------------------------------------------------------------------

class	GUICmdReqMaxFrameNumber : public GUICmdPacketBase
{
public:
	int		GroupNumber;

	GUICmdReqMaxFrameNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMaxFrameNumber : public GUICmdPacketBase
{
public:
	int		FrameNumber;
	bool	OriginExists;

	GUICmdAckMaxFrameNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//----------------------------------------------------------------------------------

class	GUICmdSetItemNumber : public GUICmdPacketBase
{
public:
	int		ItemID;
	int		GroupNumber;
	int		FrameNumber;
	bool	Original;

	GUICmdSetItemNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif