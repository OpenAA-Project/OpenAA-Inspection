#if	!defined(XDISPALYOLDIMAGEPANEL_H)
#define	XDISPALYOLDIMAGEPANEL_H

#include "NListComp.h"
#include "XFlexArea.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	NamingInfo : public NPListSaveLoad<NamingInfo>
{
public:
	FlexArea		NamingArea;
	//XYClassCluster	NamingOutline;
	QString			AreaName;
	int				GlobalPage;
	int				ItemID;

	NamingInfo(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	NamingInfoContainer : public NPListPackSaveLoad<NamingInfo>
{
public:
	NamingInfoContainer(void){}

	virtual	NamingInfo	*Create(void)	{	return new NamingInfo();	}
};

//============================================================================

class	GUICmdReqNamingInfo : public GUICmdPacketBase
{
public:
	int	Phase;

	GUICmdReqNamingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingInfo : public GUICmdPacketBase
{
public:
	NamingInfoContainer	NamingData;

	GUICmdSendNamingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
//===========================================================================


#endif
