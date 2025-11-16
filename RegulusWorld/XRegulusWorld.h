#pragma once

#include "XTypeDef.h"
#include "NListComp.h"
#include<QString>
#include<QTcpSocket>
#include<QTcpServer>
#include<QObject>
#include<QMutex>
#include "XParamRegulusWorld.h"
#include "XSocketComm.h"
#include "XAnyData.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"

class RegWorldObject;
class RegulusWorld;
class RWPacketBase;
class RWClientSocket;
class RWRecList;
class RWDeviceAccessPack;
class RWDeviceBaseClass;

#define		DLLPathRWDevice		"RegulusWorld/RWDevice"

class	Point3D;
class	PointVector3D;
class	RW3DInPageRoot;
class	RW3DBaseRoot;
class	RWLogicDLL;
class	RWLogicDLLBaseClass;
class	RWAlgorithmDLLContainer;
class	CameraView;

RegulusWorld	*GetRegulusWorld(LayersBase *d);

//==========================================================================================

class   RW3DItemRoot : public NPList<RW3DItemRoot>,public IdentifiedClass
{
	RW3DInPageRoot	*Parent;
	int64			ItemID;
	QString			ItemName;

	struct BitAttrVer1{
		bool	Effective:1;
		bool	Selected:1;
		bool	Active:1;
		bool	EditLocked:1;
		bool	Changed:1;
		bool	CalcDone:1;
		bool	Visible:1;
		bool	Editable:1;
		bool	ManualCreated:1;
	}BitAttr;
public:
	RW3DItemRoot(RW3DInPageRoot *p);
	virtual	~RW3DItemRoot(void){}

	virtual	RW3DItemRoot	*Clone(void)	=0;

	ParamRegulusWorld	*GetParamRegulusWorld(void)	const;
	RegulusWorld		*GetRegulusWorld(void)		const;

	virtual	int32	GetItemClassType(void)	const	{	return 0;	}

	int64	GetItemID(void)	const		{	return ItemID;	}
	void	SetItemID(int64 d)			{	ItemID=d;		}
	virtual	bool	IsEffective(void)	const	{	return BitAttr.Effective;	}
	virtual	void	SetEffective(bool b)		{	BitAttr.Effective=b;		}
	virtual	void	SetSelected(bool b)			{	BitAttr.Selected=b;			}
	virtual	bool	IsSelected(void)	const	{	return BitAttr.Selected;	}
	virtual	void	SetEditLocked(bool b)		{	BitAttr.EditLocked=b;		}
	virtual	bool	IsEditLocked(void)	const	{	return BitAttr.EditLocked;	}
	virtual	void	SetActive(bool b)			{	BitAttr.Active=b;			}
	virtual	bool	IsActive(void)		const	{	return BitAttr.Active;		}
	virtual	void	SetVisible(bool b)			{	BitAttr.Visible=b;			}
	virtual	bool	IsVisible(void)		const	{	return BitAttr.Visible;		}
	virtual	void	SetManualCreated(bool b)	{	BitAttr.ManualCreated=b;	}
	virtual	bool	IsManualCreated(void)const	{	return BitAttr.ManualCreated;	}
	virtual	bool	IsEditable(void)	const	{	return BitAttr.Editable;		}
	virtual	void	SetEditable(bool b)			{	BitAttr.Editable=b;			}
	virtual	bool	IsEdited(void)		const	{	return BitAttr.Changed;		}
	virtual	void	SetEdited(bool b)			{	BitAttr.Changed=b;			}
	virtual	bool	IsCalcDone(void)	const	{	return BitAttr.CalcDone;	}
	virtual	void	SetCalcDone(bool b)			{	BitAttr.CalcDone=b;			}
	virtual	void	SetItemName(const QString &name)	{	ItemName=name;		}
	virtual	QString GetItemName(void)	const			{	return ItemName;	}

	RW3DInPageRoot	*GetParentInPage(void)	const;
	RW3DBaseRoot	*GetParentBase(void)	const;

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	=0;
	virtual	void	Draw(QImage &pnt, CameraView &CamView,AlgorithmDrawAttr *Attr)	=0;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	RW3DInPageRoot : public NPList<RW3DInPageRoot>,public IdentifiedClass
{
	NPListPack<RW3DItemRoot>	Data;
	QMutex						MutexData;
	RW3DBaseRoot				*Parent;
	int							Page;
public:
	RW3DInPageRoot(RW3DBaseRoot *parent);
	virtual	~RW3DInPageRoot(void);

	void	AppendItem(RW3DItemRoot *item);
	void	RemoveItem(RW3DItemRoot *item);

	RW3DBaseRoot	*GetParentBase(void)	const;
	virtual	RW3DItemRoot	*CreateItem(int ItemClassType)	=0;
	RW3DItemRoot	*GetFirstData(void)		{	return Data.GetFirst();	}
	RW3DItemRoot	*SearchIDItem(int64 ItemID);

	int		GetPage(void)	const	{	return Page;	}
	void	SetPage(int page)		{	Page=page;		}
	ParamRegulusWorld	*GetParamRegulusWorld(void)	const;
	RegulusWorld		*GetRegulusWorld(void)		const;

	virtual	void	Draw(QImage &pnt, CameraView &CamView,AlgorithmDrawAttr *Attr);
	virtual	QColor	GetSurfaceColor(const PointVector3D &Line)	=0;
	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	RW3DBaseRoot :   public ParamBaseForAlgorithm 
						,public NPList<AlgorithmBase>
						,public IdentifiedClass
{
	NPListPack<RW3DInPageRoot>	Data;
	RegulusWorld				*RBase;
	int64						BaseID;
	QMutex						MutexBaseID;
public:
	WORD		LoadedVersion;
	RWLogicDLL	*LogicDLLPoint;

	RW3DBaseRoot(RegulusWorld *Base);

	virtual	void	Initial(RegulusWorld *Base);
	virtual	void	InitialAfterParamLoaded(void);
	virtual	void	InitialCreate(void);

	int64	GetNewID(void);
	ParamRegulusWorld	*GetParamRegulusWorld(void)	const;
	RegulusWorld		*GetRegulusWorld(void)		const	{	return RBase;	}

	virtual	RW3DInPageRoot	*CreateChild(void)			=0;
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)	=0;
	RW3DInPageRoot	*GetFirstData(void)		{	return Data.GetFirst();	}
	RW3DInPageRoot	*GetPageData(int page);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

//-------------------------------------------------------------------

class AccessSocket : public QObject ,public NPList<AccessSocket>
{
	Q_OBJECT

	int				ID;
	int				ClientID;
	QTcpSocket		*Sock;
	RegulusWorld	*Parent;

	NPListPack<RWRecList>	RecData;
	QMutex					MuteRecData;
	int32					LastPacketLoadedSize;
	struct	RWTxRxLowPacket	Pct;
	int32					FastCommLeafRxReEntrant;

	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	RWRecList	*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		NowCmd;

	NPListPack<RWTxList>	TxQueueBuff;

public:
	AccessSocket(int id,RegulusWorld *p,QTcpSocket *s,QObject *parent);
	virtual	~AccessSocket(void);

	int		GetID(void)			const	{	return ID;			}
	int		GetClientID(void)	const	{	return ClientID;	}

	bool	TxData(int32 cmd ,const QString &EmitterName,const QString &CmdClass 
					,QBuffer *f,int32 IDForUndo,ErrorCodeList &ErrorData);

	RWRecList	*UnpackTopRxBuff(void);
	bool	WaitForReadyRead(int milisec);
signals:
	void	SignalReceived(int ID,int Cmd);
	void	SignalDisconnected(int id);
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};


class	RWPacketBasePointerList : public NPList<RWPacketBasePointerList>
{
	RWPacketBase	*Base;
public:

	explicit	RWPacketBasePointerList(RWPacketBase *base){	Base=base;	}
	~RWPacketBasePointerList(void)			{	delete	Base;	}

	RWPacketBase	*GetBase(void)	const	{	return Base;	}
};

class	RWPacketBasePointerListContainer : public NPListPack<RWPacketBasePointerList>
{
public:
	RWPacketBasePointerListContainer(void){}

	RWPacketBasePointerListContainer	&operator=(RWPacketBase *a){	AppendList(new RWPacketBasePointerList(a));	return *this;	}
};

class	RWPacketBaseContainer : public NPListPack<RWPacketBase>
{
public:
	RWPacketBaseContainer(void){}
};

//========================================================================

class	RWReceiverList : public NPList<RWReceiverList>
{
public:
	QString				EmitterName;
	QString				ClassName;
	struct{
		RWPacketBase	*Point;
	};

	RWReceiverList(void)	{	Point=NULL;	}
	~RWReceiverList(void)
	{	
		Point=NULL;
	}
	RWReceiverList(const QString &emitterName ,const QString &classname , RWPacketBase *p)
	{	
		EmitterName	=emitterName;	
		ClassName	=classname;	
		Point		=p;
	}
};

//========================================================================
class RegulusWorld : public QObject ,public ServiceForLayers,public AnyDataList
{
	Q_OBJECT

	bool	ServerMode;
	int		ClientCommNo;

	NPListPack<AccessSocket>	ServerSocket;
	QTcpServer					Server;
	NPListPack<RWClientSocket>	ClientSocketPackInst;
	RegWorldObject				*Objects;
	ParamRegulusWorld			RParam;

	RWPacketBasePointerListContainer	PacketBase;
	NPListPack<RWReceiverList>			RCmdBase;
	QMutex								PacketMutex;

	QMutex							ErrorMutex;
	ErrorCodeListContainer			ErrorContainer;

	RWDeviceAccessPack				*RWDeviceAccessPackInst;
	RWAlgorithmDLLContainer			*RWAlgorithmDLLContainerInst;
	RWLogicDLLBaseClass				*RWLogicDLLBaseClassInst;
public:

	RegulusWorld(LayersBase *base,bool ServerMode=false);
	virtual	~RegulusWorld(void);

	bool	InitialLoadParam(void);
	bool	InitialLoadDevice(void);
	bool	InitialAlgorithm(const QStringList &AlgorithmPathList);

	void	InitialServer(int Port);
	QString	GetDataFileName(void);
	bool	GetServerMode(void)		const	{	return ServerMode;		}
	int		GetClientCommNo(void)	const	{	return ClientCommNo;	}

	ParamRegulusWorld	*GetParamRegulusWorld(void);

	void	AddError(ErrorCodeList *e);
	void	AppendPacket(RWPacketBase *PSrc ,const QString &emitterName ,const QString &className);
	bool	RemovePacket(RWPacketBase *PSrc);
	void	PopupPacketPriority(RWPacketBase *PSrc);
	RWPacketBase *FindPacket(const QString &ClassName);
	RWPacketBase *FindPacket(const QString &ClassName, QString &emitterName);

	AccessSocket	*GetServerSocket			(int ID);
	RWClientSocket	*GetClientSocket			(int ID);
	int		GetQueuedCount(void);

	RWDeviceAccessPack	*GetRWDeviceAccessPack(void);
	RWDeviceBaseClass	*FindByDeviceID(int deviceID);


	RWAlgorithmDLLContainer	*GetAlgoDLLContPointer(void)	const	{	return RWAlgorithmDLLContainerInst;	}
	RW3DBaseRoot			*GetRW3DBaseRoot(const QString &DLLRoot ,const QString DLLName);

private slots:
	void	SlotNewConnection();
	void	SlotReceived(int ID,int Cmd);
	void	SlotDisconnected(int id);

private:
	void	MiscatchPacket(const char	*EmitterName 
							,const char	*CmdClass 
							,const QString &Msg);
};

//=========================================================================================

#define	Error_Device_DLL_Initial1					0x0010001
#define	Error_RWDevice_NotLoaded					0x0010002
#define	Error_RWDevice_NoFunc_DLL_GetDLLType		0x0010003
#define	Error_RWDevice_NoFunc_DLL_GetName			0x0010004
#define	Error_RWDevice_NoFunc_DLL_GetVersion		0x0010005
#define	Error_RWDevice_NoFunc_DLL_GetSystemVersion	0x0010006
#define	Error_RWDevice_NoFunc_DLL_Initial			0x0010007
#define	Error_RWDevice_NoFunc_DLL_Close				0x0010008
#define	Error_RWDevice_NoFunc_DLL_Load				0x0010009
#define	Error_RWDevice_NoFunc_DLL_Save				0x001000a
#define	Error_RWDevice_NoFunc_DLL_ShowSetting		0x001000b