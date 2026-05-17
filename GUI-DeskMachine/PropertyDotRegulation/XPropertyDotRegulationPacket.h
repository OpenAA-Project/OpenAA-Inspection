#if	!defined(XPropertyDotRegulationPacket_h)
#define	XPropertyDotRegulationPacket_h
#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDateTime.h"
#include "XCSV.h"

class	AddDotRegulationAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		Layers;

	AddDotRegulationAreaPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqLayersListPacket : public GUIDirectMessage
{
public:
	IntList		Layers;

	CmdReqLayersListPacket(LayersBase *base):GUIDirectMessage(base){}
};

//==================================================================================
class	GUICmdReqAddDotRegulationArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	IntList		Layers;

	GUICmdReqAddDotRegulationArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqPickup  : public GUICmdPacketBase
{
public:
	int			Threshold;
	int			Layer;

	GUICmdReqPickup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqXPosList : public GUICmdPacketBase
{
public:
	int			Layer;

	GUICmdReqXPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckXPosList : public GUICmdPacketBase
{
public:
	DoubleList		List;

	GUICmdAckXPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqYPosList : public GUICmdPacketBase
{
public:
	int			Layer;

	GUICmdReqYPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckYPosList : public GUICmdPacketBase
{
public:
	DoubleList		List;

	GUICmdAckYPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqBrightnessList : public GUICmdPacketBase
{
public:
	int			Layer;

	GUICmdReqBrightnessList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBrightnessList : public GUICmdPacketBase
{
public:
	QStringListListCSV		List;

	GUICmdAckBrightnessList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif
