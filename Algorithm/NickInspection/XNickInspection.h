#if	!defined(XNickInspectionINSPECTION_H)
#define	XNickInspectionINSPECTION_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "NListComp.h"

#define	NickInspectionVersion		2
#define	DefLibTypeNickInspection	53
class	NickInspectionItem;
class	NickInspectionBase;
//==================================================================================

class	AlgorithmLibraryListWithResult : public NPListSaveLoad<AlgorithmLibraryListWithResult>
{
	int32	LibType;
	int32	LibID;
	bool	ResultOk;
public:
	AlgorithmLibraryListWithResult(void){}
	AlgorithmLibraryListWithResult(const AlgorithmLibraryList &src);
	virtual	bool	Save(QIODevice *f) override;
	virtual	bool	Load(QIODevice *f) override;

	bool	operator==(AlgorithmLibraryListWithResult &src);
	AlgorithmLibraryListWithResult	&operator=(const AlgorithmLibraryListWithResult &src);

	int32	GetLibType(void)	{	return LibType;		}
	void	SetLibType(int32 b)	{	LibType=b;			}
	int32	GetLibID(void)		{	return LibID;		}
	void	SetLibID(int32 b)	{	LibID=b;			}
	bool	GetResultOk(void)	{	return ResultOk;	}
	void	SetResultOk(bool b)	{	ResultOk=b;			}

	QString	GetLibName(LayersBase *base);
};

class	AlgorithmLibraryListWithResultContainer : public NPListPackSaveLoad<AlgorithmLibraryListWithResult>
{
public:
	AlgorithmLibraryListWithResultContainer(AlgorithmLibraryListContainer &src);
	AlgorithmLibraryListWithResultContainer(void){}

	virtual	AlgorithmLibraryListWithResult	*Create(void){	return new AlgorithmLibraryListWithResult();	}
	AlgorithmLibraryListWithResultContainer	&operator=(const AlgorithmLibraryListContainer &src);
	bool	GetResultOk(void) const;
	bool	IsIncludeLibType(int LibType) const;
	void	MakeLibList(int LibType,IntList &LibList) const;

	AlgorithmLibraryListWithResult	*Find(int LibType, int LibID);

	bool	operator==(const AlgorithmLibraryListWithResultContainer &src)	const ;
	bool	operator!=(const AlgorithmLibraryListWithResultContainer &src)	const {	return !operator==(src);	}
};


inline	AlgorithmLibraryListWithResult::AlgorithmLibraryListWithResult(const AlgorithmLibraryList &src)
{
	const AlgorithmLibraryListWithResult	*s=dynamic_cast<const AlgorithmLibraryListWithResult *>(&src);
	LibType	=s->LibType;
	LibID	=s->LibID	;
	ResultOk=s->ResultOk;
}
inline	bool	AlgorithmLibraryListWithResult::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ResultOk)==false)
		return false;
	return true;
}
inline	bool	AlgorithmLibraryListWithResult::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ResultOk)==false)
		return false;
	return true;
}

inline	bool	AlgorithmLibraryListWithResult::operator==(AlgorithmLibraryListWithResult &src)
{
	if(LibType	!=src.LibType
	|| LibID	!=src.LibID	
	|| ResultOk	!=src.ResultOk)
		return false;
	return true;

}
inline	AlgorithmLibraryListWithResult	&AlgorithmLibraryListWithResult::operator=(const AlgorithmLibraryListWithResult &src)
{
	LibType	=src.LibType;
	LibID	=src.LibID	;
	ResultOk=src.ResultOk;
	return *this;
}
inline	AlgorithmLibraryListWithResultContainer	&AlgorithmLibraryListWithResultContainer::operator=(const AlgorithmLibraryListContainer &src)
{
	RemoveAll();
	for(AlgorithmLibraryList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		AlgorithmLibraryListWithResult	*d=new AlgorithmLibraryListWithResult();
		d->SetLibType	(s->GetLibType());
		d->SetLibID		(s->GetLibID());
		d->SetResultOk	(true);
		AppendList(d);
	}
	return *this;
}
inline	bool	AlgorithmLibraryListWithResultContainer::GetResultOk(void) const
{
	for(AlgorithmLibraryListWithResult *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetResultOk()==false)
			return false;
	}
	return true;
}
inline	AlgorithmLibraryListWithResult	*AlgorithmLibraryListWithResultContainer::Find(int LibType, int LibID)
{
	for(AlgorithmLibraryListWithResult *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return a;
		}
	}
	return NULL;
}

//==================================================================================
class	NickInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	AlgorithmLibraryListContainer	LibList;
	int			NGPercentage;
	int			RefBrightness;
	bool		EnableWhite;
	int			LimitSize;

	NickInspectionLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	NickInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeBlocks(PureFlexAreaListContainer &Blocks
						,const BYTE **MaskMap
						,int Page);
private:
};

class	NickInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	NickInspectionLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeNickInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "NickInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new NickInspectionLibrary(GetLibType(),GetLayersBase());	}
};

class	NickInspectionThreshold : public AlgorithmThreshold
{
public:
	AlgorithmLibraryListWithResultContainer	LibList;
	int			NGPercentage;
	int			RefBrightness;
	bool		EnableWhite;
	int			Layer;

	NickInspectionThreshold(NickInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};


class	NickInspectionItem : public AlgorithmItemPI
{
	BYTE	**BMap;
	BYTE	**TmpMap;
	int		X1,Y1;
	int		BMapXByte;
	int		BMapXLen;
	int		BMapYLen;

	AlgorithmItemPointerListContainer	TargetItems;

public:

	NickInspectionItem(void);
	NickInspectionItem(FlexArea *area);
	~NickInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new NickInspectionItem();	}
	const	NickInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const NickInspectionThreshold *)GetThresholdBaseReadable(base);	}
	NickInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (NickInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new NickInspectionThreshold(this);	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	CopyThresholdOnly(NickInspectionItem &src);
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
private:
	void	MakePartialBinaryBit(ImageBuffer *IBuff, BYTE **TmpMap,int mx,int my);
};

class   NickInspectionInPage : public AlgorithmInPagePI
{
public:

	NickInspectionInPage(AlgorithmBase *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			NickInspectionItem	*a=new NickInspectionItem();
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	GenerateBlocks(IntList &LibList,AlgorithmBase *Origin);
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
};

class	NickInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;		
	int		MaxNSize;

	NickInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new NickInspectionInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("NickInspection");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigNickInspection.dat");		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};


//===================================================================================

class	AddNickInspectionAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int32		Angle;

	AddNickInspectionAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddNickInspectionAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	NickInspectionDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;

	NickInspectionDrawAttr(void){}
	NickInspectionDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	NickInspectionDrawAttr( 
					 QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdNickInspectionDrawPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;

	CmdNickInspectionDrawPacket(LayersBase *base)
		:GUIDirectMessage(base)
		{}
};

class	CmdCreateTempNickInspectionItemPacket :public GUIDirectMessage
{
public:
	NickInspectionItem	*Point;

	CmdCreateTempNickInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempNickInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempNickInspectionLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempNickInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempNickInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetNickInspectionLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetNickInspectionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetNickInspectionLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadNickInspectionLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadNickInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadNickInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearNickInspectionLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearNickInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearNickInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteNickInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteNickInspectionLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteNickInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateByteArrayFromNickInspectionItemPacket : public GUIDirectMessage
{
public:
	NickInspectionItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromNickInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromNickInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddByteNickInspectionItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteNickInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteNickInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAddNickInspectionItemPacket :public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	CmdAddNickInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddNickInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertNickInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertNickInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertNickInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateNickInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateNickInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateNickInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetNickInspectionLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetNickInspectionLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetNickInspectionLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqChangeItemAttr : public GUIDirectMessage
{
public:
	int			ItemID;
	int32		Angle;
	CmdReqChangeItemAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReqChangeItemAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateNickInspectionPacket: public GUIDirectMessage
{
public:
	IntList	LibList;
	IntList	LayerList;
	CmdGenerateNickInspectionPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateNickInspectionPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdTestNickInspectionPacket: public GUIDirectMessage
{
public:
	IntList	LayerList;
	CmdTestNickInspectionPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdTestNickInspectionPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearNickInspectionPacket: public GUIDirectMessage
{
public:
	CmdClearNickInspectionPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearNickInspectionPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================

class	NickInspectionListForPacket : public NPListSaveLoad<NickInspectionListForPacket>
{
public:
	int		LibID;
	int		ItemCount;
	
	NickInspectionListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	NickInspectionListForPacket	&operator=(NickInspectionListForPacket &src)
	{
		LibID		=src.LibID;
		ItemCount	=src.ItemCount;
		return *this;
	}
};

class	NickInspectionListForPacketPack : public NPListPackSaveLoad<NickInspectionListForPacket>
{
public:
	NickInspectionListForPacketPack(void){}

	virtual	NickInspectionListForPacket	*Create(void){	return new NickInspectionListForPacket();	}
};

inline	NickInspectionListForPacket::NickInspectionListForPacket(void)
{
	LibID		=-1;
	ItemCount	=0;
}

inline	bool	NickInspectionListForPacket::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ItemCount)==false)
		return false;

	return true;
}
inline	bool	NickInspectionListForPacket::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ItemCount)==false)
		return false;

	return true;
}

class	MakeListPacket : public GUIDirectMessage
{
public:
	NickInspectionListForPacketPack	*ListInfo;

	MakeListPacket(LayersBase *base):GUIDirectMessage(base){}
};
//===================================================================================
#define	NickInspectionReqThresholdReqCommand			1
#define	NickInspectionReqThresholdSendCommand			2
#define	SetIndependentItemDataCommand_OnlyOne	3
#define	SetIndependentItemDataCommand_All		4


class	NickInspectionThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	NickInspectionThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	NickInspectionThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	int32	Dx,Dy;

	int			NGPercentage;	
	int			RefBrightness;
	bool		EnableWhite;
	AlgorithmLibraryListWithResultContainer	Result;

	NickInspectionThresholdSend(void);

	void	ConstructList(NickInspectionThresholdReq *reqPacket,NickInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif