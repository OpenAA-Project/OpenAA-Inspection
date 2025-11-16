#if	!defined(XPropertyThinMetalPacket_H)
#define	XPropertyThinMetalPacket_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XThinMetalLibrary.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XThinMetal.h"

class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	AlgorithmLibraryLevelContainer		*LibPoint;
	IntList			LayerList;

	GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdPickupTestList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdTestClear: public GUICmdPacketBase
{
public:
	GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdGenerateThinMetals : public GUICmdPacketBase
{
public:
	IntList			LibList;
	IntList			LayerList;

	GUICmdGenerateThinMetals(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateThinMetals(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdThinMetalDrawModePacket : public GUIDirectMessage
{
public:
	ThinMetalDrawAttr::DrawType	Mode;

	CmdThinMetalDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdThinMetalDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ThinMetalImagePanel;
class	CmdThinMetalDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	ThinMetalImagePanel	*ImagePanelPoint;

	CmdThinMetalDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdThinMetalDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdThinMetalShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	IntList		LayerList;
	enum{
		_ThinMetal 	}Mode;

	CmdThinMetalShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdThinMetalShowAttrPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	FlexArea	Area;

	GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	BrightnessMapList : public NPList<BrightnessMapList>
{
public:
	int	Layer;
	int	BrightList[256];

	BrightnessMapList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	GUICmdSendAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	NPListPack<BrightnessMapList>	MapList;

	GUICmdSendAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
	void	MakeLists(FlexArea &area ,IntList &LayerList ,int localPage,LayersBase *Base);
};

class	ThinMetalItem;
class	GUICmdSendAddManualThinMetal : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualThinMetal(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedThinMetal : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedThinMetal(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdExecuteMouseLDown: public GUIDirectMessage
{
public:
	IntList	PageList;
	ListPageLayerIDPack	CurrentItem;

	CmdExecuteMouseLDown(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteMouseLDown(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteMouseRDownWithShift : public GUIDirectMessage
{
public:
	IntList		LayerList;
	CmdExecuteMouseRDownWithShift(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteMouseRDownWithShift(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqSelectedThinMetalItemAttr : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	GUICmdReqSelectedThinMetalItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedThinMetalItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedThinMetalItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base ,IntList &LayerList);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================


class	GUICmdReqThinMetalInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqThinMetalInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendThinMetalInfoList : public GUICmdPacketBase
{
public:
	ThinMetalInfoContainer	ThinMetalInfos;

	GUICmdSendThinMetalInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqThinMetalFromList : public GUICmdPacketBase
{
public:
	ListLayerAndIDPack	CurrentItem;

	GUICmdReqThinMetalFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckThinMetalFromList : public GUICmdPacketBase
{
	bool	Created;
public:
	ThinMetalItem	*ThinMetalInfoOnMouse[100];

	GUICmdAckThinMetalFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdAckThinMetalFromList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSetButtonMode : public GUICmdPacketBase
{
public:
	enum	ButtonMode
	{
		_LibraryTest	=1
		,_CreateThinMetal	=2
	}Mode;
	QString	InstForm;

	GUICmdReqSetButtonMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqSetButtonMode : public GUIDirectMessage
{
public:
	GUICmdReqSetButtonMode::ButtonMode	Mode;

	CmdReqSetButtonMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSetButtonMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	GUICmdReqThinMetalSampleList: public GUICmdPacketBase
{
public:
	int		Layer;
	int		ItemID;

	GUICmdReqThinMetalSampleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendThinMetalSampleList : public GUICmdPacketBase
{
public:
	IntList		Judgements;

	GUICmdSendThinMetalSampleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqThinMetalSampleDetail: public GUICmdPacketBase
{
public:
	int		Layer;
	int		ItemID;
	int		Number;

	GUICmdReqThinMetalSampleDetail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendThinMetalSampleDetail : public GUICmdPacketBase
{
public:
	CoeffImageList	DetailSample;

	GUICmdSendThinMetalSampleDetail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqThinMetalDeleteSamples: public GUICmdPacketBase
{
public:
	int		Layer;
	int		ItemID;
	IntList	Numbers;

	GUICmdReqThinMetalDeleteSamples(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};	

#endif