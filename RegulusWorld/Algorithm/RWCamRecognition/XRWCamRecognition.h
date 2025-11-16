#pragma once

#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"

#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithmList.h"
#include "XDataComponent.h"

#define	RWCamRecognitionVersion	1

class   RWCamRecognitionItem;
class	RWCamRecognitionInPage;
class	RWCamRecognitionBase;


//----------------------------------------------------------------------
class	RWCamRecognitionThreshold : public AlgorithmThreshold
{
public:
	int		RepeatCount	;
	int		MeshSize	;
	int		SequenceOffset	;
	bool	GatherAllPhase;

	RWCamRecognitionThreshold(RWCamRecognitionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class   RWCamRecognitionItem : public AlgorithmItemPITemplate<RWCamRecognitionInPage,RWCamRecognitionBase>
{
public:
	class MeshIndex
	{
	public:
		WORD	Count;
		AlgorithmItemPointerListContainer	AlgorithmItemIndex;
		bool	OK;
		MeshIndex();
		~MeshIndex();

		MeshIndex	&operator=(const RWCamRecognitionItem::MeshIndex &src);
	};


	MeshIndex	**RepeatCounter;
	int		Left,Top;
	int		MeshXn,MeshYn;
	int		MeshXLen,MeshYLen;

	RWCamRecognitionItem(void);
	virtual	~RWCamRecognitionItem(void);

	const	RWCamRecognitionThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const RWCamRecognitionThreshold *)GetThresholdBaseReadable(base);	}
	RWCamRecognitionThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (RWCamRecognitionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override		{	return new RWCamRecognitionThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	RWCamRecognitionItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(RWCamRecognitionItem &src);
	void	CopyThresholdOnly(RWCamRecognitionItem &src);
	void	CopyArea(RWCamRecognitionItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

private:

};

class	RWCamRecognitionInPage : public AlgorithmInPagePITemplate<RWCamRecognitionItem,RWCamRecognitionBase>
{
public:

	RWCamRecognitionInPage(AlgorithmBase *parent);
	~RWCamRecognitionInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return new RWCamRecognitionItem();	}
	void	TransmitDirectly(GUIDirectMessage *packet)	override;

};

class	RWCamRecognitionBase : public AlgorithmBase
{
public:
	QColor		ColorNormal		;
	QColor		ColorSelected	;
	QColor		ColorActive		;
	QColor		Color0;
	QColor		Color1;
	QColor		Color2;
	QColor		Color3;
	QColor		Color4;
	QColor		Color5;
	QColor		Color6;
	QColor		Color7;
	QByteArray	OperationAlgorithmData;
	RootNameListContainer	OperationAlgorithmDim;
	int			SequenceBaseNo;
	int			SequenceRegCount;
	int			DefaultRepeatCount;
	int			WholeMeshSize		;
	int			WholeSequenceOffset	;
	bool		WholeGatherAllPhase	;

	RWCamRecognitionBase(LayersBase *Base);

	virtual	RWCamRecognitionInPage	*NewChild(AlgorithmBase *parent)override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("RWCamRecognition");			}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigRWCamRecognition.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition=-1)			override;
private:

};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	RWCamRecognitionHistogramListReqCommand		3
#define	RWCamRecognitionHistogramListSendCommand		4
#define	RWCamRecognitionReqThresholdReqCommand			5
#define	RWCamRecognitionReqThresholdSendCommand		6
#define	RWCamRecognitionReqTryThresholdCommand			7
#define	RWCamRecognitionSendTryThresholdCommand		8
#define	RWCamRecognitionReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================
class	RWCamRecognitionDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			ShowingItemID;

	RWCamRecognitionDrawAttr(void):ServiceForLayers(NULL){	ShowingItemID=-1;	}
	RWCamRecognitionDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	RWCamRecognitionDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, int ptranparentLevel
				, const QColor &blockColor0
				, const QColor &blockColor1
				, const QColor &blockColor2
				, const QColor &blockColor3
				, const QColor &blockColor4
				, const QColor &blockColor5
				, const QColor &blockColor6
				, const QColor &blockColor7);

	void	Initial(void);

	RWCamRecognitionDrawAttr	&operator=(RWCamRecognitionDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	RWCamRecognitionDrawAttr::RWCamRecognitionDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base),ShowingItemID(-1)
{
}

inline	RWCamRecognitionDrawAttr::RWCamRecognitionDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, int ptranparentLevel
				, const QColor &blockColor0
				, const QColor &blockColor1
				, const QColor &blockColor2
				, const QColor &blockColor3
				, const QColor &blockColor4
				, const QColor &blockColor5
				, const QColor &blockColor6
				, const QColor &blockColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel,scol,stranparentLevel,acol,atranparentLevel)
,ServiceForLayers(Base)
,BlockColor0(blockColor0)
,BlockColor1(blockColor1)
,BlockColor2(blockColor2)
,BlockColor3(blockColor3)
,BlockColor4(blockColor4)
,BlockColor5(blockColor5)
,BlockColor6(blockColor6)
,BlockColor7(blockColor7)
,ShowingItemID(-1)
{
	BlockColor0.setAlpha(ptranparentLevel);
	BlockColor1.setAlpha(ptranparentLevel);
	BlockColor2.setAlpha(ptranparentLevel);
	BlockColor3.setAlpha(ptranparentLevel);
	BlockColor4.setAlpha(ptranparentLevel);
	BlockColor5.setAlpha(ptranparentLevel);
	BlockColor6.setAlpha(ptranparentLevel);
	BlockColor7.setAlpha(ptranparentLevel);
}
inline	RWCamRecognitionDrawAttr	&RWCamRecognitionDrawAttr::operator=(RWCamRecognitionDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	ShowingItemID	=src.ShowingItemID;
	return *this;
}
inline	bool	RWCamRecognitionDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,BlockColor0)==false)	return false;
	if(::Save(f,BlockColor1)==false)	return false;
	if(::Save(f,BlockColor2)==false)	return false;
	if(::Save(f,BlockColor3)==false)	return false;
	if(::Save(f,BlockColor4)==false)	return false;
	if(::Save(f,BlockColor5)==false)	return false;
	if(::Save(f,BlockColor6)==false)	return false;
	if(::Save(f,BlockColor7)==false)	return false;
	if(::Save(f,ShowingItemID)==false)	return false;
	return true;
}
inline	bool	RWCamRecognitionDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,BlockColor0)==false)	return false;
	if(::Load(f,BlockColor1)==false)	return false;
	if(::Load(f,BlockColor2)==false)	return false;
	if(::Load(f,BlockColor3)==false)	return false;
	if(::Load(f,BlockColor4)==false)	return false;
	if(::Load(f,BlockColor5)==false)	return false;
	if(::Load(f,BlockColor6)==false)	return false;
	if(::Load(f,BlockColor7)==false)	return false;
	if(::Load(f,ShowingItemID)==false)	return false;
	return true;
}

//==================================================================================

class	RWCamRecognitionInfoList : public NPListSaveLoad<RWCamRecognitionInfoList>
{
public:
	ListPhasePageLayerItem		Index;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;
	int		x1,y1,x2,y2;

	RWCamRecognitionInfoList(void){}
	RWCamRecognitionInfoList(const RWCamRecognitionInfoList &src);

	RWCamRecognitionInfoList	&operator=(const RWCamRecognitionInfoList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	RWCamRecognitionInfoList::RWCamRecognitionInfoList(const RWCamRecognitionInfoList &src)
{
	Index			=src.Index			;
	RepeatCount		=src.RepeatCount	;
	MeshSize		=src.MeshSize		;
	SequenceOffset	=src.SequenceOffset	;
	GatherAllPhase	=src.GatherAllPhase	;
	x1				=src.x1				;
	y1				=src.y1				;
	x2				=src.x2				;
	y2				=src.y2				;
}

inline	RWCamRecognitionInfoList	&RWCamRecognitionInfoList::operator=(const RWCamRecognitionInfoList &src)
{
	Index			=src.Index			;
	RepeatCount		=src.RepeatCount	;
	MeshSize		=src.MeshSize		;
	SequenceOffset	=src.SequenceOffset	;
	GatherAllPhase	=src.GatherAllPhase	;
	x1				=src.x1				;
	y1				=src.y1				;
	x2				=src.x2				;
	y2				=src.y2				;
	return *this;
}

inline	bool	RWCamRecognitionInfoList::Save(QIODevice *f)
{
	if(Index.Save(f)==false)
		return false;
	if(::Save(f,RepeatCount)==false)
		return false;
	if(::Save(f,MeshSize)==false)
		return false;
	if(::Save(f,SequenceOffset)==false)
		return false;
	if(::Save(f,GatherAllPhase)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;

	return true;
}
inline	bool	RWCamRecognitionInfoList::Load(QIODevice *f)
{
	if(Index.Load(f)==false)
		return false;
	if(::Load(f,RepeatCount)==false)
		return false;
	if(::Load(f,MeshSize)==false)
		return false;
	if(::Load(f,SequenceOffset)==false)
		return false;
	if(::Load(f,GatherAllPhase)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	return true;
}

class	RWCamRecognitionInfoListContainer : public NPListPackSaveLoad<RWCamRecognitionInfoList>
{
public:
	RWCamRecognitionInfoListContainer(void){}

	virtual	RWCamRecognitionInfoList	*Create(void)	override;

	RWCamRecognitionInfoListContainer	&operator+=(const RWCamRecognitionInfoListContainer &src);
};
	
inline	RWCamRecognitionInfoList	*RWCamRecognitionInfoListContainer::Create(void)
{
	return new RWCamRecognitionInfoList();
}
inline	RWCamRecognitionInfoListContainer	&RWCamRecognitionInfoListContainer::operator+=(const RWCamRecognitionInfoListContainer &src)
{
	for(RWCamRecognitionInfoList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RWCamRecognitionInfoList *d=new RWCamRecognitionInfoList(*s);
		AppendList(d);
	}
	return *this;
}

//==================================================================================

class	RWCamRecognitionThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	RWCamRecognitionThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	RWCamRecognitionThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	RWCamRecognitionThresholdSend(void);

	void	ConstructList(RWCamRecognitionThresholdReq *reqPacket,RWCamRecognitionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdCreateTempRWCamRecognitionItemPacket : public GUIDirectMessage
{
public:
	RWCamRecognitionItem	*Point;
	CmdCreateTempRWCamRecognitionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRWCamRecognitionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromRWCamRecognitionItemPacket : public GUIDirectMessage
{
public:
	RWCamRecognitionItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromRWCamRecognitionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromRWCamRecognitionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRWCamRecognitionItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdAddRWCamRecognitionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRWCamRecognitionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdModifyRWCamRecognitionItemPacket : public GUIDirectMessage
{
public:
	int		ItemID			;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdModifyRWCamRecognitionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdModifyRWCamRecognitionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRWCamRecognitionItemPacketFromByteArray : public GUIDirectMessage
{
public:
	RWCamRecognitionItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadRWCamRecognitionItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRWCamRecognitionItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqRWCamRecognitionInfoList : public GUIDirectMessage
{
public:
	RWCamRecognitionInfoListContainer	RWCamRecognitionInfos;

	CmdReqRWCamRecognitionInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRWCamRecognitionInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateWholeRWCamRecognition : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdCreateWholeRWCamRecognition(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateWholeRWCamRecognition(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqWholeRWCamRecognition : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdReqWholeRWCamRecognition(LayersBase *base):GUIDirectMessage(base){}
	CmdReqWholeRWCamRecognition(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	CmdRWCamRecognitionItemIDList: public GUIDirectMessage
{
public:
	IntList	LibIDList;

	CmdRWCamRecognitionItemIDList(LayersBase *base):GUIDirectMessage(base){}
};

