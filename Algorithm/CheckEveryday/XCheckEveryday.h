#if	!defined(XCheckEveryday_h)
#define	XCheckEveryday_h


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XCheckEverydayCommon.h"

#define	CheckEverydayVersion	1
#define	DefLibTypeCheckEverydayInspect	42
class	CheckEverydayBase;

class	CheckEverydayLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	CheckEverydayLibrary(int LibType,LayersBase *Base);
private:
};

class	CheckEverydayLibraryContainer : public AlgorithmLibraryContainer
{
public:
	CheckEverydayLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeCheckEverydayInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "CheckEveryday Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new CheckEverydayLibrary(GetLibType(),GetLayersBase());	}
};

class	CheckEverydayThreshold : public AlgorithmThreshold
{
public:
	CheckEverydayThreshold(AlgorithmItemPLI *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
    virtual	bool	Load(QIODevice *f)					override{	return true;	}
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override{}
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override{}
};

class	CheckEverydayItemBase : public AlgorithmItemPLI
{
public:
	bool	Result;
	AlignmentPacket2D	*AVector;

public:
	int16		RegNumber;

	CheckEverydayItemBase(void);
	~CheckEverydayItemBase(void);

	const	CheckEverydayThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const CheckEverydayThreshold *)GetThresholdBaseReadable(base);	}
	CheckEverydayThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (CheckEverydayThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new CheckEverydayThreshold(this);	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)override	=0;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override	=0;

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)		override	=0;
	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override	=0;

	virtual	bool	Save(QIODevice *f)						override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)	override;

private:
};


class	CheckEverydayLightItem : public CheckEverydayItemBase
{
public:
	int		BrightnessLow;
	int		BrightnessHigh;
	double	Average;

	CheckEverydayLightItem(void);
	~CheckEverydayLightItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckEverydayLightItem();	}
	virtual	int32		GetItemClassType(void)		override{		return 0;		}
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;

private:
};

class	CheckEverydayFocusItem : public CheckEverydayItemBase
{
public:
	int		LineCount;
	double	VCoeff;
	double	FocusLow;

	CheckEverydayFocusItem(void);
	~CheckEverydayFocusItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckEverydayFocusItem();	}
	virtual	int32		GetItemClassType(void)		override	{		return 1;		}
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;

private:
};


class   CheckEverydayInLayer : public AlgorithmInLayerPLI
{
  public:
	CheckEverydayInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
private:
	void	CreatePickupBmpBuff(void);
};

class   CheckEverydayInPage : public AlgorithmInPagePLI
{
public:

	CheckEverydayInPage(AlgorithmBase *parent);

	virtual	CheckEverydayInLayer	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new CheckEverydayInLayer(parent));	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	CheckEverydayBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	int32	UseFocusLayer;

	CheckEverydayBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new CheckEverydayInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("CheckEveryday");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigCheckEveryday.dat");		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};
//==================================================================================
//===================================================================================

class	AddCheckEverydayAreaLightPacket : public GUIDirectMessage
{
public:
	QString		ItemName;
	FlexArea	Area;
	int			BrightnessLow,BrightnessHigh;
	IntList		LayerList;

	AddCheckEverydayAreaLightPacket(LayersBase *base):GUIDirectMessage(base){}
	AddCheckEverydayAreaLightPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AddCheckEverydayAreaFocusPacket : public GUIDirectMessage
{
public:
	QString		ItemName;
	double		FocusLow;
	FlexArea	Area;
	IntList		LayerList;

	AddCheckEverydayAreaFocusPacket(LayersBase *base):GUIDirectMessage(base){}
	AddCheckEverydayAreaFocusPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	ModifyCheckEverydayAreaLightPacket : public GUIDirectMessage
{
public:
	QString		ItemName;
	int			BrightnessLow,BrightnessHigh;
	int			Layer;
	int			ItemID;

	ModifyCheckEverydayAreaLightPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyCheckEverydayAreaLightPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ModifyCheckEverydayAreaFocusPacket : public GUIDirectMessage
{
public:
	QString		ItemName;
	double		FocusLow;
	int			Layer;
	int			ItemID;

	ModifyCheckEverydayAreaFocusPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyCheckEverydayAreaFocusPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	ReqCheckEverydayInfo : public GUIDirectMessage
{
public:
	CheckEverydayLightInfoContainer	*pInfoLight;
	CheckEverydayFocusInfoContainer	*pInfoFocus;

	ReqCheckEverydayInfo(LayersBase *base):GUIDirectMessage(base){}
	ReqCheckEverydayInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CheckEverydayDrawAttr : public AlgorithmDrawAttr
{
public:

	CheckEverydayDrawAttr(void){}
	CheckEverydayDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	CheckEverydayDrawAttr(LayersBase *base 
					,QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
	}
};

class	CmdCheckEverydayDrawPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;
	enum	__DMode{
		__Mode_PickupArea			=1
		,__Mode_ItemArea			=2
	}DMode;

	CmdCheckEverydayDrawPacket(LayersBase *base)
		:GUIDirectMessage(base)
		{}
};
/*
class	CmdCreateTempCheckEverydayItemPacket :public GUIDirectMessage
{
public:
	CheckEverydayItem	*Point;

	CmdCreateTempCheckEverydayItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempCheckEverydayItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempCheckEverydayLibraryPacket :public GUIDirectMessage
{
public:
	CheckEverydayLibrary	*Point;

	CmdCreateTempCheckEverydayLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempCheckEverydayLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
*/
class	CmdGetCheckEverydayLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetCheckEverydayLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetCheckEverydayLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadCheckEverydayLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadCheckEverydayLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadCheckEverydayLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearCheckEverydayLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearCheckEverydayLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearCheckEverydayLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteCheckEverydayLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteCheckEverydayLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteCheckEverydayLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
/*
class	CmdCreateByteArrayFromCheckEverydayItemPacket : public GUIDirectMessage
{
public:
	CheckEverydayItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromCheckEverydayItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromCheckEverydayItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
*/

class	CmdAddByteCheckEverydayItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteCheckEverydayItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteCheckEverydayItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAddCheckEverydayItemPacket :public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	CmdAddCheckEverydayItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddCheckEverydayItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertCheckEverydayLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertCheckEverydayLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertCheckEverydayLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateCheckEverydayLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateCheckEverydayLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateCheckEverydayLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetCheckEverydayLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetCheckEverydayLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetCheckEverydayLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqChangeItemAttr : public GUIDirectMessage
{
public:
	int			ItemID;
	int32		Angle;
	CmdReqChangeItemAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReqChangeItemAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================


	

#endif