#if	!defined(XSHOWOLDNGNAMINGPACKET_H)
#define	XSHOWOLDNGNAMINGPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XNaming.h"
#include "XIntClass.h"

//-----------------------------------------------------------------

class	GUICmdReqOlderNGList : public GUICmdPacketBase
{
public:
	int		CurrentInspectionID;
	int		GenerationLevel;
	int		Phase;

	GUICmdReqOlderNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOlderNGList : public GUICmdPacketBase
{
public:
	NamingNGContainer	NGNaming;

	GUICmdSendOlderNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//-----------------------------------------------------------------

class	GUICmdReqNamingAreaList : public GUICmdPacketBase
{
public:
	int		Phase;

	GUICmdReqNamingAreaList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingAreaList : public GUICmdPacketBase
{
public:
	NamingPointerStock		NamingArea;

	GUICmdSendNamingAreaList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
#endif