#pragma once

#include "XDirectComm.h"
#include "swap.h"
#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XRegulusWorld.h"
#include "XGeneralFunc.h"
#include "XDataComponent.h"
#include "XRegulusWorldObject.h"

#define	RWAlgorithm3DVersion	1

class   RWAlgorithm3DItem;
class	RWAlgorithm3DInPage;
class	RWAlgorithm3DBase;
class	Vector3D;

class   CrossCluster;
class   CrossInfo;

//----------------------------------------------------------------------

class   RWAlgorithm3DItem : public RW3DItemRoot
{
public:
	RWShapeBaseContainer	Items;

	RWAlgorithm3DItem(RW3DInPageRoot *p);
	virtual	~RWAlgorithm3DItem(void);

	virtual	RW3DItemRoot	*Clone(void)	override;
	RWAlgorithm3DItem &operator=(const RW3DItemRoot &src);

	virtual	void	Draw(QImage &pnt, CameraView &CamView,AlgorithmDrawAttr *Attr)	override;

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	override;
private:

};

class	RWAlgorithm3DInPage : public RW3DInPageRoot
{
public:

	RWAlgorithm3DInPage(RW3DBaseRoot *parent);
	~RWAlgorithm3DInPage(void);

	virtual	RW3DItemRoot	*CreateItem(int ItemClassType)	override	{	return new RWAlgorithm3DItem(this);	}
	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QColor	GetSurfaceColor(const PointVector3D &Line);
};

class	RWAlgorithm3DBase : public RW3DBaseRoot
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

	RWAlgorithm3DBase(RegulusWorld *Base);

	virtual	RW3DInPageRoot	*CreateChild(void)						override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("RWAlgorithm3D");			}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigRWAlgorithm3D.dat");	}


private:

};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	RWAlgorithm3DHistogramListReqCommand		3
#define	RWAlgorithm3DHistogramListSendCommand		4
#define	RWAlgorithm3DReqThresholdReqCommand			5
#define	RWAlgorithm3DReqThresholdSendCommand		6
#define	RWAlgorithm3DReqTryThresholdCommand			7
#define	RWAlgorithm3DSendTryThresholdCommand		8
#define	RWAlgorithm3DReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================
class	RWAlgorithm3DDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
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

	RWAlgorithm3DDrawAttr(void):ServiceForLayers(NULL){	ShowingItemID=-1;	}
	RWAlgorithm3DDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	RWAlgorithm3DDrawAttr(LayersBase *Base
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

	RWAlgorithm3DDrawAttr	&operator=(RWAlgorithm3DDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	RWAlgorithm3DDrawAttr::RWAlgorithm3DDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base),ShowingItemID(-1)
{
}

inline	RWAlgorithm3DDrawAttr::RWAlgorithm3DDrawAttr(LayersBase *Base
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
inline	RWAlgorithm3DDrawAttr	&RWAlgorithm3DDrawAttr::operator=(RWAlgorithm3DDrawAttr &src)
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
inline	bool	RWAlgorithm3DDrawAttr::Save(QIODevice *f)
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
inline	bool	RWAlgorithm3DDrawAttr::Load(QIODevice *f)
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

class	RWAlgorithm3DInfoList : public NPListSaveLoad<RWAlgorithm3DInfoList>
{
public:
	ListPhasePageLayerItem		Index;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;
	int		x1,y1,x2,y2;

	RWAlgorithm3DInfoList(void){}
	RWAlgorithm3DInfoList(const RWAlgorithm3DInfoList &src);

	RWAlgorithm3DInfoList	&operator=(const RWAlgorithm3DInfoList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	RWAlgorithm3DInfoList::RWAlgorithm3DInfoList(const RWAlgorithm3DInfoList &src)
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

inline	RWAlgorithm3DInfoList	&RWAlgorithm3DInfoList::operator=(const RWAlgorithm3DInfoList &src)
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

inline	bool	RWAlgorithm3DInfoList::Save(QIODevice *f)
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
inline	bool	RWAlgorithm3DInfoList::Load(QIODevice *f)
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

class	RWAlgorithm3DInfoListContainer : public NPListPackSaveLoad<RWAlgorithm3DInfoList>
{
public:
	RWAlgorithm3DInfoListContainer(void){}

	virtual	RWAlgorithm3DInfoList	*Create(void)	override;

	RWAlgorithm3DInfoListContainer	&operator+=(const RWAlgorithm3DInfoListContainer &src);
};
	
inline	RWAlgorithm3DInfoList	*RWAlgorithm3DInfoListContainer::Create(void)
{
	return new RWAlgorithm3DInfoList();
}
inline	RWAlgorithm3DInfoListContainer	&RWAlgorithm3DInfoListContainer::operator+=(const RWAlgorithm3DInfoListContainer &src)
{
	for(RWAlgorithm3DInfoList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RWAlgorithm3DInfoList *d=new RWAlgorithm3DInfoList(*s);
		AppendList(d);
	}
	return *this;
}

//==================================================================================

class	RWAlgorithm3DThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	RWAlgorithm3DThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	RWAlgorithm3DThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	RWAlgorithm3DThresholdSend(void);

	void	ConstructList(RWAlgorithm3DThresholdReq *reqPacket,RWAlgorithm3DBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdCreateTempRWAlgorithm3DItemPacket : public GUIDirectMessage
{
public:
	RWAlgorithm3DItem	*Point;
	CmdCreateTempRWAlgorithm3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRWAlgorithm3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromRWAlgorithm3DItemPacket : public GUIDirectMessage
{
public:
	RWAlgorithm3DItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromRWAlgorithm3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromRWAlgorithm3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRWAlgorithm3DItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdAddRWAlgorithm3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRWAlgorithm3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdModifyRWAlgorithm3DItemPacket : public GUIDirectMessage
{
public:
	int		ItemID			;
	int		RepeatCount		;
	int		MeshSize		;
	int		SequenceOffset	;
	bool	GatherAllPhase	;

	CmdModifyRWAlgorithm3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdModifyRWAlgorithm3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRWAlgorithm3DItemPacketFromByteArray : public GUIDirectMessage
{
public:
	RWAlgorithm3DItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadRWAlgorithm3DItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRWAlgorithm3DItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqRWAlgorithm3DInfoList : public GUIDirectMessage
{
public:
	RWAlgorithm3DInfoListContainer	RWAlgorithm3DInfos;

	CmdReqRWAlgorithm3DInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRWAlgorithm3DInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateWholeRWAlgorithm3D : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdCreateWholeRWAlgorithm3D(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateWholeRWAlgorithm3D(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqWholeRWAlgorithm3D : public GUIDirectMessage
{
public:
	int		RepeatCount	;

	CmdReqWholeRWAlgorithm3D(LayersBase *base):GUIDirectMessage(base){}
	CmdReqWholeRWAlgorithm3D(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	CmdRWAlgorithm3DItemIDList: public GUIDirectMessage
{
public:
	IntList	LibIDList;

	CmdRWAlgorithm3DItemIDList(LayersBase *base):GUIDirectMessage(base){}
};

