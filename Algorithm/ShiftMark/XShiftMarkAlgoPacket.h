#pragma once

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XYCross.h"
#include "XFlexAreaImage.h"
#include "XStandardCommand.h"

class	ShiftMarkThresholdReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	int32	Dx,Dy;

	ShiftMarkThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ShiftMarkThresholdSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	int32	Dx,Dy;
	int		SearchDotEdge;
	int		SearchDotMarkMin;
	int		SearchDotMarkMax;
	bool	NGByLosingMark;
	int		ThresholdLost;		//è¡é∏îªíËÇµÇ´Ç¢ílÅi0-100)
	
	ShiftMarkThresholdSend(void);

	void	ConstructList(ShiftMarkThresholdReq *reqPacket,ShiftMarkBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ShiftMarkReqTryThreshold
{
public:
	int32	GlobalPage;
	int		BlockItemID;	
	ShiftMarkItem	Threshold;

	ShiftMarkReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	ShiftMarkSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;

	double	ResultMPos;
	double	ResultMatchMark;
	double	ResultMarkAngle;
	bool	ResultOK;

	ShiftMarkSendTryThreshold(void);
	~ShiftMarkSendTryThreshold(void);

	void	ConstructList(ShiftMarkReqTryThreshold *reqPacket,ShiftMarkBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CmdGetShiftMarkLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetShiftMarkLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetShiftMarkLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetShiftMarkLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetShiftMarkLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetShiftMarkLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempShiftMarkLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempShiftMarkLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempShiftMarkLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearShiftMarkLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearShiftMarkLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearShiftMarkLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertShiftMarkLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertShiftMarkLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertShiftMarkLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateShiftMarkLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateShiftMarkLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateShiftMarkLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadShiftMarkLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadShiftMarkLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadShiftMarkLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteShiftMarkLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteShiftMarkLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteShiftMarkLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempShiftMarkItemPacket : public GUIDirectMessage
{
public:
	ShiftMarkItem	*Point;
	CmdCreateTempShiftMarkItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempShiftMarkItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromShiftMarkItemPacket : public GUIDirectMessage
{
public:
	ShiftMarkItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromShiftMarkItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromShiftMarkItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddShiftMarkItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			Layer;
	QString		ItemName;
	int			LibID;

	CmdAddShiftMarkItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddShiftMarkItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadShiftMarkItemPacketFromByteArray : public GUIDirectMessage
{
public:
	ShiftMarkItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadShiftMarkItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadShiftMarkItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================

class	ShiftMarkListForPacket : public NPListSaveLoad<ShiftMarkListForPacket>
{
public:
	int		ItemID;
	int		LibID;
	QString	ItemName;
	int		Page;
	int		x1,y1,x2,y2;
	int		SearchDotEdge;
	
	ShiftMarkListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	ShiftMarkListForPacket	&operator=(ShiftMarkListForPacket &src);
};

class	ShiftMarkListForPacketPackForPhase : public NPListPackSaveLoad<ShiftMarkListForPacket>
											,public NPListSaveLoad<ShiftMarkListForPacketPackForPhase>
{
public:
	int	Phase;
	ShiftMarkListForPacketPackForPhase(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	ShiftMarkListForPacket	*Create(void);

	ShiftMarkListForPacketPackForPhase	&operator=(ShiftMarkListForPacketPackForPhase &src);
};

class	ShiftMarkListForPacketPack : public NPListPackSaveLoad<ShiftMarkListForPacketPackForPhase>
{
public:
	ShiftMarkListForPacketPack(void){}

	virtual	ShiftMarkListForPacketPackForPhase	*Create(void);
};
//=================================================================================

class	CmdAddByteShiftMarkItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	VectorLineBase	*Vector;
	int			LocalPage;
	int			SelectedLibID;
	QString		ItemName;

	//These are for Distance between scans
	bool		NoCalc;
	int			GlobalPage1;
	int			ClosedItemID1;
	int			GlobalPage2;
	int			ClosedItemID2;

	CmdAddByteShiftMarkItemPacket(LayersBase *base):GUIDirectMessage(base)		{	Vector=NULL;	}
	CmdAddByteShiftMarkItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Vector=NULL;	}

	~CmdAddByteShiftMarkItemPacket(void)	{	if(Vector!=NULL){	delete	Vector; Vector=NULL;	}	}	
};


class	CmdSendAddEdgeMark :public GUIDirectMessage
{
public:
	int			ItemID;
	FlexArea	Area;
	bool		ModeAddEdge;
	bool		ModeAddMark;

	CmdSendAddEdgeMark(LayersBase *base):GUIDirectMessage(base)			{}
	CmdSendAddEdgeMark(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};
