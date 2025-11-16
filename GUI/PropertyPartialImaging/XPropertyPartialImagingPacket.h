#if	!defined(XPropertyPartialImagingPacket_h)
#define	XPropertyPartialImagingPacket_h

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XPartialImaging.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"



//===================================================================================
class	GUICmdAddAreaManual : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int32		Priority;
	bool		SaveTargetImage;
	bool		SaveOnlyInNG;
	int32		BufferType;
	QString		ItemName;

	GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdEditAreaManual : public GUICmdPacketBase
{
public:
	int32		ItemID;
	int32		Priority;
	bool		SaveTargetImage;
	bool		SaveOnlyInNG;
	int32		BufferType;
	QString		ItemName;

	GUICmdEditAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdDeleteAreaManual : public GUICmdPacketBase
{
public:
	int32		ItemID;

	GUICmdDeleteAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

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



class	GUICmdReqPartialImagingInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqPartialImagingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendPartialImagingInfoList : public GUICmdPacketBase
{
public:
	PartialImagingInfoContainer	PInfoContainer;

	GUICmdSendPartialImagingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===================================================================================

class	CmdSelectBufferInItem : public GUIDirectMessage
{
public:
	WriteBufferInItem	*Point;

	CmdSelectBufferInItem(LayersBase *Base):GUIDirectMessage(Base){}
};

#endif
