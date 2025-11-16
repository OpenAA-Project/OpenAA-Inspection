#if	!defined(XCHECKEVERYDAYGUIPACKET_H)
#define	XCHECKEVERYDAYGUIPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XCheckEveryday.h"

class	CheckEverydayImagePanel;

class	CmdCheckEverydayDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	CheckEverydayImagePanel	*ImagePanelPoint;

	CmdCheckEverydayDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdCheckEverydayDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqAddManualLight : public GUICmdPacketBase
{
public:
	QString		ItemName;
	int			BrightnessLow;
	int			BrightnessHigh;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdReqAddManualLight(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAddManualFocus : public GUICmdPacketBase
{
public:
	QString		ItemName;
	double		FocusLow;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdReqAddManualFocus(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqModifyManualLight : public GUICmdPacketBase
{
public:
	QString		ItemName;
	int			BrightnessLow;
	int			BrightnessHigh;
	int			Layer;
	int			ItemID;

	GUICmdReqModifyManualLight(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyManualFocus : public GUICmdPacketBase
{
public:
	QString		ItemName;
	double		FocusLow;
	int			Layer;
	int			ItemID;

	GUICmdReqModifyManualFocus(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//------------------------------------------------------------------------------------------------------------


class	GUICmdReqInfo : public GUICmdPacketBase
{
public:

	GUICmdReqInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckInfo : public GUICmdPacketBase
{
public:
	CheckEverydayLightInfoContainer	InfoLight;
	CheckEverydayFocusInfoContainer	InfoFocus;

	GUICmdAckInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	void	Make(int localPage);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif