/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaShader\XAreaShader.h
** Author : YYYYYYYYYY
*******************************************************************************/

#if	!defined(XAREASHADER_H)
#define	XAREASHADER_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"

#define	AreaShaderVersion	2
#define	DefLibTypeAreaShader	7

class	AreaShaderItem;

class	AreaShaderLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	MaxDot;
	int32	MinDot;
	int32	MaxSize;
	int32	MinSize;
	int16	ShrinkDot;
	int16	PickupColorL,PickupColorH;
	int16	Priority;
	bool	GenerateOverlap;

	int		CellSize;
	double	AdoptRate;	//採用率
	bool	Fixed;
	double	Average;
	double	Sigma;		//標準偏差
	bool	PreProcessingMode;

	AreaShaderLibrary(int LibType,LayersBase *Base);
	virtual	~AreaShaderLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AreaShaderLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer *MasterImage
						 ,const BYTE **MaskBitmap
						 ,BYTE **BmpPoint 
						 ,BYTE **OcupyMap
						 ,int XByte ,int XLen ,int YLen
						 ,int OmitZoneDot);
	void	MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList);
};

class	AreaShaderLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AreaShaderLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~AreaShaderLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeAreaShader;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AreaShader Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AreaShaderLibrary(GetLibType(),GetLayersBase());	}
};

//--------------------------------------------------------------------------------------------------------

class AreaShaderItem;
class	AreaShaderThreshold : public AlgorithmThreshold
{
public:
	int		CellSize;
	double	AdoptRate;	//採用率
	bool	Fixed;
	double	Average;
	double	Sigma;		//標準偏差
	bool	PreProcessingMode;

	AreaShaderThreshold(AreaShaderItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};


class	AreaShaderItem : public AlgorithmItemPLI
{
	int	WCount;
	int	HCount;
	int	LCellSize;
	int	LCalcSize;
	struct	ShaderStruct
	{
		double	Avr;
		double	Var;
		int		Ax1,Ay1,Ax2,Ay2;
	};
	struct	ShaderStruct	*SDim;

	double	Avr,Var;	//目標
	AlignmentPacket2D	*AVector;
public:
	AreaShaderItem(void);
	~AreaShaderItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaShaderItem();	}
	const	AreaShaderThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AreaShaderThreshold *)GetThresholdBaseReadable(base);	}
	AreaShaderThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AreaShaderThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AreaShaderThreshold(this);	}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
								   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

protected:
private:
	void	CalcAvrVar(FlexArea &Area,ImageBuffer &buff,double &Avr ,double &Var
					 ,double AdoptRate
					 ,int AreaX1,int AreaY1 ,int AreaX2 ,int AreaY2
					 ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	bool	PPProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res);
};

//--------------------------------------------------------------------------------------------------------

class   AreaShaderInLayer : public AlgorithmInLayerPLI
{
	class	ItemPointerList : public NPList<ItemPointerList>
	{
	public:
		AlgorithmItemRoot	*Pointer;
		int					Index;
		ItemPointerList(int index ,AlgorithmItemRoot *item)
			:Pointer(item),Index(index){}
	};

	class	ItemPointerListContainer : public NPListPack<ItemPointerList>
	{
	public:
		ItemPointerListContainer(void){}
		~ItemPointerListContainer(void){}

		void	Add(int index ,AlgorithmItemRoot *item);
	};

	class	ItemByLibContainerList : public NPList<ItemByLibContainerList>,public ItemPointerListContainer
	{
	public:
		int					LibID;
		AreaShaderInLayer	*Parent;

		ItemByLibContainerList(int libID,AreaShaderInLayer *parent):LibID(libID),Parent(parent){}
	};
	NPListPack<ItemByLibContainerList>	ExecutingList;

public:
	BYTE	**DynamicMaskMap;
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;
	int		XByte;
	int		YLen;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;


	AreaShaderInLayer(AlgorithmInPageRoot *parent);
	~AreaShaderInLayer(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override;
	virtual	AlgorithmItemRoot		*CreateItem(AreaShaderLibrary &Lib);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	//void	AddMask(MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,ResultInLayerRoot *Res)	override;

	void	GenerateBlocks(AreaShaderLibrary *LibDim[],int LibDimNumb);

private:
	void	PickupTest(AreaShaderLibrary &LibData);
	void	CreateItems(IntList &LayerList ,AlgorithmLibraryListContainer &LibList);
	void	CreatePickupBmpBuff(void);
	bool	PPProcessing	(int ExeID ,ResultInLayerRoot *Res);

};

inline	AlgorithmItemRoot		*AreaShaderInLayer::CreateItem(int ItemClassType)
{
	AreaShaderItem	*a=new AreaShaderItem();	
	a->SetParent(this);
	return a;
}

class   AreaShaderInPage : public AlgorithmInPagePLI
{
public:
	AreaShaderInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new AreaShaderInLayer(parent);	}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	void	GenerateBlocks(IntList &LayerList, AreaShaderLibrary *LibDim[],int LibDimNumb);
};

class	AreaShaderBase : public AlgorithmBase
{
public:
	QColor	ColorPickup;
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;
	int32	TransparentLevel;
	int32	OmitZoneDot;

	AreaShaderBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new AreaShaderInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	QString	GetDataText(void)		override{		return QString("AreaShader");	}
	QString	GetDefaultFileName(void)		override{	return QString("ConfigAreaShader.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//==================================================================================

#define	AreaShaderReqThresholdReqCommand		1
#define	AreaShaderReqThresholdSendCommand		2
#define	SetIndependentItemDataCommand_OnlyOne	3
#define	SetIndependentItemDataCommand_All		4


class	AreaShaderThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	AreaShaderThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AreaShaderThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	int32	Dx,Dy;
	int		CellSize;
	double	AdoptRate;	//採用率
	bool	Fixed;
	double	Average;
	double	Sigma;		//標準偏差

	AreaShaderThresholdSend(void);

	void	ConstructList(AreaShaderThresholdReq *reqPacket,AreaShaderBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//===================================================================================

class	AreaShaderDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;
	bool	Generated;

	AreaShaderDrawAttr(void){	Generated=true;	}
	AreaShaderDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){	Generated=true;		}
	AreaShaderDrawAttr(  QColor ncol ,int ntranparentLevel
						,QColor scol ,int stranparentLevel
						,QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		AreaColor			=ncol;	
		NegAreaColor		=acol;	
		NegAreaColorSelected=scol;	
		AreaColor			.setAlpha(ntranparentLevel);
		NegAreaColor		.setAlpha(atranparentLevel);
		NegAreaColorSelected.setAlpha(stranparentLevel);
		Generated=true;	
	}
};

//===================================================================================

class	CmdGetAreaShaderLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAreaShaderLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAreaShaderLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAreaShaderLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetAreaShaderLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAreaShaderLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempAreaShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAreaShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAreaShaderLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAreaShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAreaShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAreaShaderLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAreaShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAreaShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAreaShaderLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadAreaShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadAreaShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAreaShaderLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAreaShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAreaShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAreaShaderLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAreaShaderDrawModePacket : public GUIDirectMessage
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedBlock
	}Mode;
	enum	DrawType{
		_Area
		,_Edge
		,_Inside
	}DType;

	CmdAreaShaderDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAreaShaderDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AreaShaderImagePanel;
class	CmdAreaShaderDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	AreaShaderImagePanel	*ImagePanelPoint;

	CmdAreaShaderDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdAreaShaderDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddAreaShaderItemPacket: public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			LocalPage;
	IntList		LayerList;
	int		CellSize;
	double	AdoptRate;	//採用率
	bool	Fixed;
	double	Average;
	double	Sigma;		//標準偏差

	CmdAddAreaShaderItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddAreaShaderItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearAreaShaderLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAreaShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAreaShaderLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


//=============================================================================================

class	AreaShaderListForPacket : public NPList<AreaShaderListForPacket>
{
public:
	int		ItemID;
	int		Layer;
	int		Page;
	int		x1,y1,x2,y2;
	int		CellSize;
	double	AdoptRate;	//採用率
	bool	Fixed;
	double	Average;
	double	Sigma;		//標準偏差
	
	AreaShaderListForPacket(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AreaShaderListForPacket	&operator=(AreaShaderListForPacket &src);
};

class	AreaShaderListForPacketPack : public NPListPack<AreaShaderListForPacket>
{
public:
	AreaShaderListForPacketPack(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AreaShaderListForPacketPack	&operator=(AreaShaderListForPacketPack &src);
	AreaShaderListForPacketPack	&operator+=(AreaShaderListForPacketPack &src);
};

inline	bool	AreaShaderListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;

	if(::Save(f,CellSize)==false)
		return false;
	if(::Save(f,AdoptRate)==false)
		return false;
	if(::Save(f,Fixed)==false)
		return false;
	if(::Save(f,Average)==false)
		return false;
	if(::Save(f,Sigma)==false)
		return false;

	return true;
}
inline	bool	AreaShaderListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;

	if(::Load(f,CellSize)==false)
		return false;
	if(::Load(f,AdoptRate)==false)
		return false;
	if(::Load(f,Fixed)==false)
		return false;
	if(::Load(f,Average)==false)
		return false;
	if(::Load(f,Sigma)==false)
		return false;

	return true;
}
inline	AreaShaderListForPacket	&AreaShaderListForPacket::operator=(AreaShaderListForPacket &src)
{
	ItemID	=src.ItemID;
	Layer	=src.Layer;
	Page	=src.Page;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;

	CellSize	=src.CellSize;
	AdoptRate	=src.AdoptRate;	//採用率
	Fixed		=src.Fixed;
	Average		=src.Average;
	Sigma		=src.Sigma;		//標準偏差

	return *this;
}


inline	bool	AreaShaderListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AreaShaderListForPacket *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
inline	bool	AreaShaderListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		AreaShaderListForPacket	*c=new AreaShaderListForPacket();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
inline	AreaShaderListForPacketPack	&AreaShaderListForPacketPack::operator=(AreaShaderListForPacketPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
inline	AreaShaderListForPacketPack	&AreaShaderListForPacketPack::operator+=(AreaShaderListForPacketPack &src)
{
	for(AreaShaderListForPacket *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		AreaShaderListForPacket *d=new AreaShaderListForPacket();
		*d=*c;
		AppendList(d);
	}
	return *this;
}

#endif