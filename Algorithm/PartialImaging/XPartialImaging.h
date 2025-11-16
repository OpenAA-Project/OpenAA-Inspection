/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PartialImaging\PartialImaging.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPartialImaging_h)
#define	XPartialImaging_h

#define	PartialImagingVersion	1


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

class	PartialImagingItem;
class	PartialImagingInLayer;
class	PartialImagingInPage;
class	PartialImagingBase;
class	FileEntryListContainer;
class   SaveImageFileListContainer;
class   CmdImageFileList;
class	WriteBufferInItem;

class	PartialImagingThreshold : public AlgorithmThreshold
{
public:
	int32			Priority;
	bool			SaveTargetImage;
	bool			SaveOnlyInNG;
	int32			BufferType;

	PartialImagingThreshold(PartialImagingItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	PartialImagingItem : public AlgorithmItemPI
{
	AlignmentPacket2D	*AVector;
	WriteBufferInItem	*Buffer;
public:

	PartialImagingItem(void);
	~PartialImagingItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new PartialImagingItem();	}
	const	PartialImagingThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const PartialImagingThreshold *)GetThresholdBaseReadable(base);	}
	PartialImagingThreshold			*GetThresholdW(LayersBase *base=NULL){	return (PartialImagingThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new PartialImagingThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	void	SetBufferPoint(WriteBufferInItem *b){	Buffer=b;	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

private:
	bool	CopyImageData(BYTE *DataPointer,int DataByte,ImageBuffer &IBuff,int dx,int dy);
};

class	WriteBufferInItem
{
	int32		Priority;
public:
	int32		ItemID;
	QString		ItemName;
	FlexArea	Area;
	int32		LayerNumb;
	int32		AreaByte;
	BYTE		**ImageData;

	WriteBufferInItem(void);
	virtual	~WriteBufferInItem(void);

	int		GetPriority(void)	{	return Priority;	}
	void	SetPriority(int p)	{	Priority=p;			}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	
	void	Allocate(PartialImagingItem *parent);
};

class	WriteBufferInPage
{
public:
	int32				MasterCode;
	QString				LotID;
	int32				InspectionID;
	int32				WriteBufferNumb;
	WriteBufferInItem	*BufferDim;
	volatile	bool	Empty; 	

	WriteBufferInPage(void);
	virtual	~WriteBufferInPage(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Save(PartialImagingInPage *parent);

	WriteBufferInItem	*GetPoint(int ItemID);
	void	Allocate(PartialImagingInPage *parent);
};

class	WriteBufferThread : public QThread
{
public:
	PartialImagingInPage	*Parent;

	int					WriteBufferNumb;
	WriteBufferInPage	*BuffDim;
	volatile	bool	Terminated;
	QMutex		Mutex;

	WriteBufferThread(QObject *parent,PartialImagingInPage *p);
	virtual ~WriteBufferThread(void);

	virtual	void	run();

	WriteBufferInPage	*GetWritePoint();
	WriteBufferInPage	*GetBufferStorePoint();
	int	GetStackedCount(void);
	void	SetEmptyFlag(bool flag ,WriteBufferInPage *point);
	void	Allocate(void);
};

class   PartialImagingInPage : public AlgorithmInPagePI
{
	WriteBufferThread	*Thread;
public:
	PartialImagingInPage(AlgorithmBase *parent);
	~PartialImagingInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{		return new PartialImagingItem;		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;
};

class	PartialImagingBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	QString	SavedPathFormat;
	int		WriteBufferNumb;

	PartialImagingBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new PartialImagingInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("PartialImaging");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigPartialImaging.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QString	MakeSavedFileName(int MasterCode, const QString &LotID,int InspectionID ,int page);
};

//==================================================================================

class	PartialImagingDrawAttr : public AlgorithmDrawAttr
{
public:
	PartialImagingDrawAttr(void){}
	PartialImagingDrawAttr(PartialImagingBase *Base);
	PartialImagingDrawAttr(PartialImagingBase *Base,QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
};

inline	PartialImagingDrawAttr::PartialImagingDrawAttr(PartialImagingBase *Base)
	:AlgorithmDrawAttr(Base->ColorArea,Base->TransparentLevel ,Base->ColorSelected,Base->TransparentLevel ,Base->ColorActive,Base->TransparentLevel)
{
}


//===================================================================================

class	PartialImagingInfo : public NPListSaveLoad<PartialImagingInfo>
{
public:
	int		GlobalPage;
	int		ItemID;
	int		x1,y1,x2,y2;
	int32	Priority;
	bool	SaveTargetImage;
	bool	SaveOnlyInNG;
	int32	BufferType;
	QString	ItemName;

	PartialImagingInfo(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	PartialImagingInfoContainer : public NPListPackSaveLoad<PartialImagingInfo>
{
public:
	PartialImagingInfoContainer(void){}
	virtual	PartialImagingInfo	*Create(void)	{	return new PartialImagingInfo();	}
	void	SetPage(int page);
};


inline	bool	PartialImagingInfo::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,SaveTargetImage)==false)
		return false;
	if(::Load(f,SaveOnlyInNG)==false)
		return false;
	if(::Load(f,BufferType)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
inline	bool	PartialImagingInfo::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,SaveTargetImage)==false)
		return false;
	if(::Save(f,SaveOnlyInNG)==false)
		return false;
	if(::Save(f,BufferType)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}
//==================================================================================
class	CmdAddAreaManualInPanel : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddAreaManualInPanel(LayersBase *Base):GUIDirectMessage(Base){}
};
class	CmdAddAreaPartialImaging : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int32	Priority;
	bool	SaveTargetImage;
	bool	SaveOnlyInNG;
	int32	BufferType;
	QString	ItemName;

	CmdAddAreaPartialImaging(LayersBase *Base):GUIDirectMessage(Base){}
};
class	CmdEditAreaPartialImaging : public GUIDirectMessage
{
public:
	int32	ItemID;
	int32	Priority;
	bool	SaveTargetImage;
	bool	SaveOnlyInNG;
	int32	BufferType;
	QString	ItemName;

	CmdEditAreaPartialImaging(LayersBase *Base):GUIDirectMessage(Base){}
};
class	CmdDeletePartialImaging : public GUIDirectMessage
{
public:
	int32	ItemID;

	CmdDeletePartialImaging(LayersBase *Base):GUIDirectMessage(Base){}
};

class	PartialImagingInfoContainer;

class	CmdReqPartialImagingInfo : public GUIDirectMessage
{
public:
	PartialImagingInfoContainer	*Info;

	CmdReqPartialImagingInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemInfo : public GUIDirectMessage
{
public:
	int			ItemID;

	CmdReqItemInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqEnumInfo : public GUIDirectMessage
{
public:
	PartialImagingInfoContainer		PInfoContainer;

	CmdReqEnumInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqBufferedData: public GUIDirectMessage
{
public:
	WriteBufferInPage	*PointDim;
	int					PageNumb;

	CmdReqBufferedData(LayersBase *Base):GUIDirectMessage(Base){	PointDim=NULL;	PageNumb=0;	}
};

class	CmdReleaseBufferedData: public GUIDirectMessage
{
public:
	WriteBufferInPage	*PointDim;

	CmdReleaseBufferedData(LayersBase *Base):GUIDirectMessage(Base){	PointDim=NULL;	}
};

#endif