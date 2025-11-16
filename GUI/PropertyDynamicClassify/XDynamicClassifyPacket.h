
#if	!defined(XDYNAMICCLASSIFFYPACKET_H)
#define	XDYNAMICCLASSIFFYPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDynamicClassify.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XFlexArea.h"
#include "XDynamicClassify.h"

class	GUICmdReqDynamicClassifyDrawMode : public GUIDirectMessage
{
public:
	bool	ShowTestBitmap;
	bool	ShowCore;
	bool	ShowMaxZone;
	bool	ShowMinZone;
	bool	ShowBare;
	bool	ShowInside;
	bool	ShowOutlineI;
	bool	ShowOutlineT;
	bool	ShowOutlineO;

	GUICmdReqDynamicClassifyDrawMode(LayersBase *base):GUIDirectMessage(base){}
};

class	DynamicClassifyImagePanel;

class	CmdDynamicClassifyDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;
	DynamicClassifyImagePanel	*ImagePanelPoint;

	CmdDynamicClassifyDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};


class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//DynamicClassifyLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;

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

class	GUICmdGenerateDynamicClassifys : public GUICmdPacketBase
{
public:
	IntList			LibList;

	GUICmdGenerateDynamicClassifys(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateDynamicClassifys(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//==========================================================================

class	GUICmdReqRGBStockFromArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReqRGBStockFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendRGBStockFromArea : public GUICmdPacketBase
{
public:
	RGBStock	RGBColors;

	GUICmdSendRGBStockFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================

class	GUICmdReqAreaHistgramInMaster : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	BrightnessMapList : public NPList<BrightnessMapList>
{
public:
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
	void	MakeLists(FlexArea &area ,int localPage,LayersBase *Base);
};

//===============================================================================
class	CmdSetDynamicClassifyShowingState : public GUIDirectMessage
{
public:
	bool	ModeCoreArea;
	bool	ModeMaxZone;
	bool	ModeMinZone;
	bool	ModeBareArea;
	bool	ModeInsideArea;
	bool	ModeOutlineIArea;
	bool	ModeOutlineTArea;
	bool	ModeOutlineOArea;

	IntList	ShowingLibIDs;

	CmdSetDynamicClassifyShowingState(LayersBase *base):GUIDirectMessage(base)
	{
		ModeCoreArea	=true;
		ModeMaxZone		=false;
		ModeMinZone		=false;
		ModeBareArea	=false;
		ModeInsideArea	=false;
		ModeOutlineIArea=false;
		ModeOutlineTArea=false;
		ModeOutlineOArea=false;
	}

	//bool	Load(QIODevice *f);
	//bool	Save(QIODevice *f);
};
/*
class	GUICmdSetDynamicClassifyShowingState : public GUICmdPacketBase
{
public:
	CmdSetDynamicClassifyShowingState	State;

	GUICmdSetDynamicClassifyShowingState(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
*/
//===============================================================================
class	GUICmdReqDynamicClassifyInfo : public GUICmdPacketBase
{
public:
	GUICmdReqDynamicClassifyInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDynamicClassifyInfo : public GUICmdPacketBase
{
public:
	DClassifyInfos		DCInfoData;

	GUICmdSendDynamicClassifyInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===============================================================================
class	CmdDynamicClassifyGenerate : public GUIDirectMessage
{
public:
	CmdDynamicClassifyGenerate(LayersBase *base):GUIDirectMessage(base){}
};

#endif
