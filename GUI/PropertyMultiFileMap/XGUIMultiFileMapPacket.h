#if	!defined(XGUIMultiFileMapPacket_H)
#define	XGUIMultiFileMapPacket_H

#include "XGUIPacketForDLL.h"
#include "XMultiFileMap.h"
#include "XBoolList.h"
#include "XIntClass.h"

class	GUICmdSetMultiFileMapHeader : public GUIDirectMessage
{
public:
	QString	GlobalPath;
	int32	NumbX;
	int32	NumbY;
	QString	ProductName;
	QString	PathName;

	GUICmdSetMultiFileMapHeader(LayersBase *base):GUIDirectMessage(base)			{	NumbX=NumbY=-1;	}
	GUICmdSetMultiFileMapHeader(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	NumbX=NumbY=-1;	}
};

class	GUICmdReqMultiFileMapInfo : public GUICmdPacketBase
{
public:
	int GlobalX ,GlobalY;

	GUICmdReqMultiFileMapInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckMultiFileMapInfo : public GUICmdPacketBase
{
public:
	int	PosX,PosY;
	QString	FileName;

	GUICmdAckMultiFileMapInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif