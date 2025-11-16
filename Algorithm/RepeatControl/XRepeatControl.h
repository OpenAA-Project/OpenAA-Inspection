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

#define	RepeatControlVersion	1

class   RepeatControlItem;
class	RepeatControlInPage;
class	RepeatControlBase;


//----------------------------------------------------------------------
class	RepeatControlThreshold : public AlgorithmThreshold
{
public:
	int		RepeatCount	;
	int		MeshSize	;
	int		SequenceOffset	;
	bool	GatherAllPhase;

	RepeatControlThreshold(RepeatControlItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class   RepeatControlItem : public AlgorithmItemPITemplate<RepeatControlInPage,RepeatControlBase>
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

		MeshIndex	&operator=(const RepeatControlItem::MeshIndex &src);
	};


	MeshIndex	**RepeatCounter;
	int		Left,Top;
	int		MeshXn,MeshYn;
	int		MeshXLen,MeshYLen;

	RepeatControlItem(void);
	virtual	~RepeatControlItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new RepeatControlItem();	}
	const	RepeatControlThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const RepeatControlThreshold *)GetThresholdBaseReadable(base);	}
	RepeatControlThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (RepeatControlThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override		{	return new RepeatControlThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	RepeatControlItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(RepeatControlItem &src);
	void	CopyThresholdOnly(RepeatControlItem &src);
	void	CopyArea(RepeatControlItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

private:

};

class	RepeatControlInPage : public AlgorithmInPagePITemplate<RepeatControlItem,RepeatControlBase>
{
public:

	RepeatControlInPage(AlgorithmBase *parent);
	~RepeatControlInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return new RepeatControlItem();	}
	void	TransmitDirectly(GUIDirectMessage *packet)	override;

};

class	RepeatControlBase : public AlgorithmBase
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

	RepeatControlBase(LayersBase *Base);

	virtual	RepeatControlInPage	*NewChild(AlgorithmBase *parent)override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("RepeatControl");			}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigRepeatControl.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition=-1)			override;
	virtual	void	ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)	override;

private:

};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	RepeatControlHistogramListReqCommand		3
#define	RepeatControlHistogramListSendCommand		4
#define	RepeatControlReqThresholdReqCommand			5
#define	RepeatControlReqThresholdSendCommand		6
#define	RepeatControlReqTryThresholdCommand			7
#define	RepeatControlSendTryThresholdCommand		8
#define	RepeatControlReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================
class	RepeatControlDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
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

	RepeatControlDrawAttr(void):ServiceForLayers(NULL){	ShowingItemID=-1;	}
	RepeatControlDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	RepeatControlDrawAttr(LayersBase *Base
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

	RepeatControlDrawAttr	&operator=(RepeatControlDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	RepeatControlDrawAttr::RepeatControlDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base),ShowingItemID(-1)
{
}

inline	RepeatControlDrawAttr::RepeatControlDrawAttr(LayersBase *Base
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
inline	RepeatControlDrawAttr	&RepeatControlDrawAttr::operator=(RepeatControlDrawAttr &src)
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
inline	bool	RepeatControlDrawAttr::Save(QIODevice *f)
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
inline	bool	RepeatControlDrawAttr::Load(QIODevice *f)
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

class	RepeatControlInfoList : public NPListSaveLoad<RepeatControlInfoList>
{
public:
	ListPhasePageLayerItem		Index;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;
	int		x1,y1,x2,y2;

	RepeatControlInfoList(void){}
	RepeatControlInfoList(const RepeatControlInfoList &src);

	RepeatControlInfoList	&operator=(const RepeatControlInfoList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	RepeatControlInfoList::RepeatControlInfoList(const RepeatControlInfoList &src)
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

inline	RepeatControlInfoList	&RepeatControlInfoList::operator=(const RepeatControlInfoList &src)
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

inline	bool	RepeatControlInfoList::Save(QIODevice *f)
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
inline	bool	RepeatControlInfoList::Load(QIODevice *f)
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

class	RepeatControlInfoListContainer : public NPListPackSaveLoad<RepeatControlInfoList>
{
public:
	RepeatControlInfoListContainer(void){}

	virtual	RepeatControlInfoList	*Create(void)	override;

	RepeatControlInfoListContainer	&operator+=(const RepeatControlInfoListContainer &src);
};
	
inline	RepeatControlInfoList	*RepeatControlInfoListContainer::Create(void)
{
	return new RepeatControlInfoList();
}
inline	RepeatControlInfoListContainer	&RepeatControlInfoListContainer::operator+=(const RepeatControlInfoListContainer &src)
{
	for(RepeatControlInfoList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RepeatControlInfoList *d=new RepeatControlInfoList(*s);
		AppendList(d);
	}
	return *this;
}

//==================================================================================

class	RepeatControlThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	RepeatControlThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	RepeatControlThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	RepeatControlThresholdSend(void);

	void	ConstructList(RepeatControlThresholdReq *reqPacket,RepeatControlBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdCreateTempRepeatControlItemPacket : public GUIDirectMessage
{
public:
	RepeatControlItem	*Point;
	CmdCreateTempRepeatControlItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRepeatControlItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromRepeatControlItemPacket : public GUIDirectMessage
{
public:
	RepeatControlItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromRepeatControlItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromRepeatControlItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRepeatControlItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdAddRepeatControlItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRepeatControlItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdModifyRepeatControlItemPacket : public GUIDirectMessage
{
public:
	int		ItemID			;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdModifyRepeatControlItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdModifyRepeatControlItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRepeatControlItemPacketFromByteArray : public GUIDirectMessage
{
public:
	RepeatControlItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadRepeatControlItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRepeatControlItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqRepeatControlInfoList : public GUIDirectMessage
{
public:
	RepeatControlInfoListContainer	RepeatControlInfos;

	CmdReqRepeatControlInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRepeatControlInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateWholeRepeatControl : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdCreateWholeRepeatControl(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateWholeRepeatControl(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqWholeRepeatControl : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdReqWholeRepeatControl(LayersBase *base):GUIDirectMessage(base){}
	CmdReqWholeRepeatControl(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	CmdRepeatControlItemIDList: public GUIDirectMessage
{
public:
	IntList	LibIDList;

	CmdRepeatControlItemIDList(LayersBase *base):GUIDirectMessage(base){}
};

