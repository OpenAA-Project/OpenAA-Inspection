/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoMaskingPI\XAutoMaskingPI.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XAutoMaskingPI_H
#define XAutoMaskingPI_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"

#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"
#include "XAutoPCBHoleAligner.h"
#include "XAutoAlignment.h"

class	AutoMaskingPIItem;
#define	DefLibTypeAutoMaskingPI			14

class	AutoMaskingPIDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	AutoGenMode;
	bool	EffectiveMode;
	bool	IneffectiveMode;
	bool	CompositeMask;

	AutoMaskingPIDrawAttr(void)
		: AlgorithmDrawAttr(Qt::green,100,Qt::yellow,100,Qt::red,100){}

	AutoMaskingPIDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	AutoMaskingPIDrawAttr( QColor ncol ,int ntranparentLevel
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

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

inline	bool	AutoMaskingPIDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,NegColorMask)==false)
		return false;
	if(::Save(f,NegColorSelected)==false)
		return false;
	if(::Save(f,AutoGenMode)==false)
		return false;
	if(::Save(f,EffectiveMode)==false)
		return false;
	if(::Save(f,IneffectiveMode)==false)
		return false;
	if(::Save(f,CompositeMask)==false)
		return false;
	return true;
}
inline	bool	AutoMaskingPIDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,NegColorMask)==false)
		return false;
	if(::Load(f,NegColorSelected)==false)
		return false;
	if(::Load(f,AutoGenMode)==false)
		return false;
	if(::Load(f,EffectiveMode)==false)
		return false;
	if(::Load(f,IneffectiveMode)==false)
		return false;
	if(::Load(f,CompositeMask)==false)
		return false;
	return true;
}

//----------------------------------------------------------------------

class	AutoMaskingPILibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		ColDiffRate;
	int		EnLargeDot;
	int		EnSmallDot;
	int		MinSlitDot;
	int		MinSlitSize;
	bool	DefaultMask;

	int		MinSlitWidth;
	int		MaxLakeSize;

	int		MinClusterSize;
	int		MinClusterArea;
	bool	PickupDarker;
	int		NoiseSize;
	int		StageShadeColor;

	bool	chkEnLargeDot;

public:

	AutoMaskingPILibrary(int LibType ,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AutoMaskingPILibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeMask(ImageBuffer *MasterBuff[]
					,ImageBuffer *TargetBuff[]
					,int LayerCount
					,BYTE **MaskBitmap
					,int XByte ,int XLen ,int YLen);

private:
	AlgorithmLibraryLevelContainer *GetFirstAutoAlignmentLibrary();
	bool	ComparePickupPadColor(PureFlexAreaList *AreaList,AutoAlignmentLibrary *Lib,ImageBuffer *MImageList[]);
};

class	AutoMaskingPILibraryContainer : public AlgorithmLibraryContainer
{
public:
	AutoMaskingPILibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeAutoMaskingPI;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AutoMaskingPI Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AutoMaskingPILibrary(GetLibType(),GetLayersBase());	}
};

//----------------------------------------------------------------------

class	AutoMaskingPIThreshold : public AlgorithmThreshold
{
public:
	bool							Effective;		// true=有効エリア
	AlgorithmLibraryListContainer	SelAreaID;		// 限定マスク

	AutoMaskingPIThreshold(AutoMaskingPIItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	AutoMaskingPIItem : public AlgorithmItemPI
{
public:

	AutoMaskingPIItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AutoMaskingPIItem();	}
	const	AutoMaskingPIThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const AutoMaskingPIThreshold *)GetThresholdBaseReadable(base);	}
	AutoMaskingPIThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (AutoMaskingPIThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new AutoMaskingPIThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool	IsEffective(void)	const override;
	virtual	void	SetEffective(bool effective)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};


class	AutoMaskingPIInPage : public AlgorithmInPagePI
{
	int		XByte;
	int		XLen,YLen;
	BYTE	**AutoMaskMap;

	BYTE	**MaskMap;

public:

	AutoMaskingPIInPage(AlgorithmBase *parent);
	~AutoMaskingPIInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			AutoMaskingPIItem	*a=new AutoMaskingPIItem();
			a->SetParent(this);
			return a;
		}

	void	GenerateMaskInSameColor(int PickupL ,int PickupH ,bool Effective);
	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)	override;
	BYTE	**GetItemBitmap(void);
	BYTE	**GetItemAutoBitmap(void);
	void	GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen
						,bool GenerateOnlyLimitMask=false);
	void	SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen);
	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,void *Anything=NULL)	override;

	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);
	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);

private:
	QString	sNoPCBImagePath;
	bool	SaveTargetImage(QString FileName);
	bool	LoadTargetImage(QString FileName,int localX1,int localY1,int localX2,int localY2);
/*
	void	Clusterize(void);
	AutoPCBHoleAlignerLibrary *GetFirstAutoPCBHoleAlignerLibrary();
	bool	ComparePickupHoleColor(PureFlexAreaList *AreaList,AutoPCBHoleAlignerLibrary *Lib,ImageBuffer *MImageList[]);
	AutoAlignmentLibrary *GetFirstAutoAlignmentLibrary();
	bool	ComparePickupPadColor(PureFlexAreaList *AreaList,AutoAlignmentLibrary *Lib,ImageBuffer *MImageList[]);
*/
};

class	AutoMaskingPIBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	ColorLogic PickupSideBarColor;
	ColorLogic BaseColor	;
	int PickupSideBarColorMergin;
	int BaseColorMergin;
	int	LeftRightMerginDot;
	int	TopBottomMerginDot;
	int NoiseSize;
	int	MaxHoleSize;
	int	ExpansionSlitDot;
	QString NoPCBImagePath;
	AlgorithmLibraryListContainer	AdoptedLib;

	AutoMaskingPIBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new AutoMaskingPIInPage((AutoMaskingPIBase*)parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)		override{	return QString("AutoMaskingPI");				}
	QString	GetDefaultFileName(void)		override{	return QString("ConfigAutoMaskingPI.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	HasReflection(ReflectionMode mode)	override	{	return ((mode & _Reflection_Mask)!=0)?true:false;	}

	virtual	ExeResult	ExecuteInitialAfterEdit(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	override;
	virtual	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	override;

private:
	void	SetAdopted(void);

};
//==================================================================================
//===================================================================================
class	AddAutoMaskingPIAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	bool		Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	AddAutoMaskingPIAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAutoMaskingPIAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoMaskingPIDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdAutoMaskingPIDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdAutoMaskingPIDeleteItemPacket : public GUIDirectMessage
{
public:

	CmdAutoMaskingPIDeleteItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoMaskingPIDeleteItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateAutoMaskPIInSameColor : public GUIDirectMessage
{
public:
	int32	RPickupL;
	int32	RPickupH;
	int32	GPickupL;
	int32	GPickupH;
	int32	BPickupL;
	int32	BPickupH;
	bool	Effective;

	CmdGenerateAutoMaskPIInSameColor(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateAutoMaskPIInSameColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoMaskingPIDrawOnOffPacket : public GUIDirectMessage
{
public:
	bool	AutoGenMode;
	bool	Effective;
	bool	Ineffective;
	bool	CompositeMask;

	CmdAutoMaskingPIDrawOnOffPacket(LayersBase *base)
		:GUIDirectMessage(base)
	{	AutoGenMode=true;	Effective=false;	Ineffective=false;	CompositeMask=false;	}

};

class	CmdCreateAutoMaskingPIBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**BmpMap;
	CmdCreateAutoMaskingPIBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAutoMaskingPIBitmapWithLibPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateAutoMaskingPIAutoBitmapWithLibPacket : public GUIDirectMessage
{
public:
	int		XByte;
	int		YLen;
	int		LibType;
	int		LibID;
	BYTE	**AutoBmpMap;
	CmdCreateAutoMaskingPIAutoBitmapWithLibPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAutoMaskingPIAutoBitmapWithLibPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateAutoMaskForDesktop : public GUIDirectMessage
{
public:
	int	LocalPage;
	CmdGenerateAutoMaskForDesktop(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateAutoMaskForDesktop(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdExecuteAutoPickup : public GUIDirectMessage
{
public:
	GUICmdExecuteAutoPickup(LayersBase *base):GUIDirectMessage(base){}
	GUICmdExecuteAutoPickup(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDCGetOtherPageAutoMask :public DirectCommPacketBase
{
public:
	CmdDCGetOtherPageAutoMask(LayersBase *base, int globalPageOwn
						,const QString &EmitterRoot ,const QString &EmitterName ,const QString &className);
};


class	CmdGetAutoMaskingPILibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoMaskingPILibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoMaskingPILibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoMaskingPILibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoMaskingPILibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoMaskingPILibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempAutoMaskingPILibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAutoMaskingPILibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAutoMaskingPILibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAutoMaskingPILibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertAutoMaskingPILibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAutoMaskingPILibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAutoMaskingPILibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAutoMaskingPILibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadAutoMaskingPILibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAutoMaskingPILibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAutoMaskingPILibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAutoMaskingPILibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAutoMaskingPILibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqSaveTargetImageForAutoMaskingPI : public GUICmdPacketBase
{
public:
	int	TopY;
	int	YCount;
	int	Layer;

	GUICmdReqSaveTargetImageForAutoMaskingPI(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveTargetImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveTargetImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendLoadTargetImageForAutoMaskingPI : public GUICmdPacketBase
{
public:
	int	TopY;
	int	YCount;
	int	Layer;
	int	iDotPerLine;
	QByteArray	Data;

	int localX1,localY1,localX2,localY2;

	GUICmdSendLoadTargetImageForAutoMaskingPI(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdFinalizeLoadTargetImageForAutoMaskingPI : public GUICmdPacketBase
{
public:
	int	Layer;

	GUICmdFinalizeLoadTargetImageForAutoMaskingPI(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif