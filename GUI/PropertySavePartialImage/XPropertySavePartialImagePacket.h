#if	!defined(XPropertySavePartialImagePacket_H)
#define	XPropertySavePartialImagePacket_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XSavePartialImage.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"

class	CmdCreateSavePartialImageManualPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	CmdCreateSavePartialImageManualPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetDrawAttr : public GUIDirectMessage
{
public:
	SavePartialImageDrawAttr::SPI_DrawMode	DMode;
	CmdGetDrawAttr(LayersBase *base):GUIDirectMessage(base){}
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
	SavePartialImageInfoContainer		GridList;

	GUICmdSendGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdAddAreaManual : public GUICmdPacketBase
{
public:
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

	GUICmdReqItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemInfo : public GUICmdPacketBase
{
public:
	int			ItemID;

	GUICmdSendItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif