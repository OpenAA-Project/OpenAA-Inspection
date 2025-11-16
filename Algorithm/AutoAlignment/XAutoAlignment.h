/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoAlignment\XAutoAlignment.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAUTOALIGNMENT_H)
#define	XAUTOALIGNMENT_H

#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XServiceForLayers.h"
#include "XDataModelPageItem.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"
#include "XAutoAlignmentCommon.h"
#include "XStandardCommand.h"

#define	AutoAlignmentVersion	2
//#define	NeedFringeBit
#define	DefLibTypeAutoAlignment			12

class	AutoAlignmentInPico;
class	AutoAlignmentSheet;
class	AutoAlignmentBase;
class	AutoAlignmentInPage;
class	AASheetInfos;
class	ClusteredPicoDim;

class	AutoAlignmentDrawAttr : public AlgorithmDrawAttr
{
public:
	int		DrawSheetMode;
	bool	DrawMono;
	int		MonoLevel;
	bool	Mastered;
	int		DrawPico;
	AAListAttrContainer	SelectedLDList;

	AutoAlignmentDrawAttr(void)
		: AlgorithmDrawAttr(Qt::green,100,Qt::yellow,100,Qt::red,100){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


inline	bool	AutoAlignmentDrawAttr::Save(QIODevice *f)
{	
	if(::Save(f,DrawSheetMode)==false)
		return false;
	if(::Save(f,DrawMono)==false)
		return false;
	if(::Save(f,MonoLevel)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,DrawPico)==false)
		return false;
	if(SelectedLDList.Save(f)==false){
		return false;
	}
	return true;
}
inline	bool	AutoAlignmentDrawAttr::Load(QIODevice *f)
{	
	if(::Load(f,DrawSheetMode)==false)
		return false;
	if(::Load(f,DrawMono)==false)
		return false;
	if(::Load(f,MonoLevel)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,DrawPico)==false)
		return false;
	if(SelectedLDList.Load(f)==false){
		return false;
	}
	return true;
}

class	AlignmentPacketWithColor : public AlignmentPacket2D
{
public:
	int	R,G,B;

	AlignmentPacketWithColor(void){}
};


//----------------------------------------------------------------------

class	AutoAlignmentLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	ColorLogic	PickupColor;
	int			PicoShift;
	bool		StartupExecute;
	int			Priority;
	int			PickupExpansion;
	int			NoiseShrink;
	int			ExpandForPickup;
	int			MinDot;			//各領域の最小ドット数
	int			FringeWidth;	//遷移ビットにする周辺幅
	double		AdptedMatchingRate;
	double		CompletelyMatchingRate;
public:

	AutoAlignmentLibrary(int LibType,LayersBase *Base);
	virtual	~AutoAlignmentLibrary(void){}

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AutoAlignmentLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	AutoAlignmentLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AutoAlignmentLibraryContainer(LayersBase *base);
	virtual	~AutoAlignmentLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAutoAlignment;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AutoAlignment Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AutoAlignmentLibrary(GetLibType(),GetLayersBase());	}
};

class	AutoAlignmentThreshold : public AlgorithmThreshold
{
public:
	ColorLogic	PickupColor;
	int			ExpandForPickup;
	int			PicoShift;
	int			NoiseShrink;
	int			PickupExpansion;
	int			Priority;
	int			MinDot;
	int			FringeWidth;
	double		AdptedMatchingRate;
	double		CompletelyMatchingRate;

	AutoAlignmentThreshold(AutoAlignmentSheet *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};



class	AutoAlignmentInPico : public NPList<AutoAlignmentInPico>,public AlignmentPacket2D
{
	friend	class	AutoAlignmentSheet;
	friend	class	ClusteredPicoDim;

	AutoAlignmentSheet	*Parent;

	FlexArea	TransArea;
	FlexArea	FringeArea;
	int			SelectFirst;
	int			Xn,Yn;
	int			CenterX,CenterY;
	AutoAlignmentInPico	*BasePointer;	//優先度の最も高い同一箇所のPICOへのポインタ

	class	CalcedData
	{
		double	MasterAddA;
		double	MasterAddA2;
		int		DotCount;
		int		StepX;
		int		StepY;

		double	IndexMasterAddA;
		double	IndexMasterAddA2;

	public:
		CalcedData(void);

		void	SetStep(int xs ,int ys);
		void	InitialCalc(ImageBuffer &Buff ,FlexArea &Area);
		double	GetMasterVar(void);
		double	CoefCalc(ImageBuffer &MasterBuff ,ImageBuffer &TargetBuff ,FlexArea &Area,int dx ,int dy);
	};
	ClusteredPicoDim	*DimPoint;

	CalcedData	CalcFirstR,CalcDetailR;
	CalcedData	CalcFirstG,CalcDetailG;
	CalcedData	CalcFirstB,CalcDetailB;

	FlexArea	OtherArea;	//優先度が２番目以降のときに生成される。
							//自身のPICO探索ドット＋抽出領域を他の最大のPICO探索範囲分膨張させ、自身の領域を除去したエリア
	FlexArea	OMasterArea;	//OtherArea-PickupArea
	FlexArea	OTargetArea;	//OtherArea-PickupAreaTarget

public:
	class	CalcedIndexData
	{
	public:
	#pragma	pack(push,1)
		struct	XYStruct
		{
			int32	X,Y;
		};
		struct	XYStruct	*XYIndex;
		int					XYIndexCount;
	#pragma	pack(pop)
	
		int		MinX,MinY,MaxX,MaxY;
		BYTE	*MasterData;
		double	MasterAddA;
		double	MasterAddA2;

	public:
		CalcedIndexData(void);
		virtual	~CalcedIndexData(void);

		void Initial(FlexArea &TransArea
					,ImageBuffer &Buff
					,int MinTransDot);
		double	CoefCalc(int dx ,int dy
						,ImageBuffer &MasterBuff ,ImageBuffer &TargetBuff);
	}IndexDataR,IndexDataG,IndexDataB;

public:
	FlexArea	PickupArea;	
	FlexArea	PickupAreaTarget;	
	double	MatchResult;

	FlexArea		Area;
	double		SelfCoef;
	bool		Effective;
	//bool		Appended;
	bool		Adopted;
	bool		NeedAdjust;

	AutoAlignmentInPico	*ConnectedPico[2];

	AutoAlignmentInPico(AutoAlignmentSheet *parent ,int xn ,int yn);
	virtual	~AutoAlignmentInPico(void);
	
	bool	ExecuteInitialAfterEdit(BYTE **MasterMap ,int MasterXByte ,int MasterYLen,ExecuteInitialAfterEditInfo &EInfo);
	bool	ExecuteStartByInspection(void);
	bool	ExecuteAlignment(double Dx, double Dy,double Theta);

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG);
	FlexArea	&GetArea(void)	{	return Area;	}

	void	CalcFromSurround(void);
	void	CalcAdjust(void);
	bool	CalcAdjustAll(void);
	int		GetLayerNumb(void);

	void	PutShiftMapAll(char **ResultPerPixXFromTarget,
							char **ResultPerPixYFromTarget,
							char **ResultPerPixXFromMaster,
							char **ResultPerPixYFromMaster,
							int XLen,
							int YLen);
	void	PutShiftMap(char **ResultPerPixXFromTarget,
						 char **ResultPerPixYFromTarget,
						 char **ResultPerPixXFromMaster,
						 char **ResultPerPixYFromMaster,
						 char **ResultRelativeXFromTarget,
						 char **ResultRelativeYFromTarget,
						 char **ResultRelativeXFromMaster,
						 char **ResultRelativeYFromMaster,
						 int XLen,
						 int YLen);
	void	AvoidOverlap(void);

	void	MakeXYIndex(void);

#if	defined(NeedFringeBit)
	void	SetTransBit(void);
	void	SetFirstTransBit(void);
#endif
	void	SetPickupBit(void);
	void	SetFirstPickupBit(void);

	void	SetBasePointer(AutoAlignmentInPico	*base){	BasePointer=base;	}
	void	MakePickupAreaFromPico(BYTE **BMap,int XByte ,int YLen);
private:

	double	ExecuteAlignmentInside(double Dx, double Dy,double Theta ,int	PicoShift,int turn);
	double	ExecuteAlignmentIndex(int Dx, int Dy
								,ImageBuffer *RMasterBuff
								,ImageBuffer *GMasterBuff
								,ImageBuffer *BMasterBuff
								,ImageBuffer *RTargetBuff
								,ImageBuffer *GTargetBuff
								,ImageBuffer *BTargetBuff
								,int &ResMx,int &ResMy);
	double	ExecuteAlignmentInside2(double Dx, double Dy,double Theta 
									,int PLen ,int Step
									,double CompletelyMatchingRate
									,ImageBuffer *RMasterBuff,ImageBuffer *GMasterBuff,ImageBuffer *BMasterBuff
									,ImageBuffer *RTargetBuff,ImageBuffer *GTargetBuff,ImageBuffer *BTargetBuff
									,double &MaxRoughMatch,int &ResMx,int &ResMy);
	double	ExecuteAlignmentInside3(double mx, double my
									,int	LStep
									,double CompletelyMatchingRate
									,ImageBuffer *RMasterBuff,ImageBuffer *GMasterBuff,ImageBuffer *BMasterBuff
									,ImageBuffer *RTargetBuff,ImageBuffer *GTargetBuff,ImageBuffer *BTargetBuff);

	void	DrawInfo(QPainter &PData ,int MovX ,int MovY ,double ZoomRate);
	bool	AvoidOverlapMaster( int MasterX ,int MasterY 
								,int MasterShiftX ,int MasterShiftY 
								,double Len ,int &ResultX ,int &ResultY);
	bool	AvoidOverlapTarget( int TargetX ,int TargetY 
								,int TargetShiftX ,int TargetShiftY 
								,double Len ,int &ResultX ,int &ResultY);
	void	CalcAdjustInner(int x ,int y);
	bool	CalcAdjustAllInner(int x ,int y);

};

class	AutoAlignmentInPageMonoMiniSize : public NPList<AutoAlignmentInPageMonoMiniSize>
{
	AutoAlignmentInPage	*Parent;
	int	sDotPerLine;
	int	sMaxLines;
	int	sXByte;
	int	LeftMergin;
	int	XCalcNumb;
	int	TopMergin;
	int	YCalcNumb;
	double	MasterAddA;
	double	MasterAddA2;

	double	AlignedDx;
	double	AlignedDy;
	double	AlignedTheta;
	double	MatchResult;

	BYTE	**MasterMap;
	BYTE	**TargetMap;

public:
	int	SparseDot;

	AutoAlignmentInPageMonoMiniSize(AutoAlignmentInPage *parent);
	~AutoAlignmentInPageMonoMiniSize(void);

	void	InitialAlloc(int sparseDot);
	void	CreateMasterMap(const BYTE **Mask);
	void	CreateTargetMap(void);

	void	FirstMatch(double &dx ,double &dy ,double &Theta
					, int SearchDot ,double MaxTheta);
	void	FirstMatch(double &Dx ,double &Dy
					, int SearchDot);
	void	SlightMatch(double &dx ,double &dy ,double &Theta
						,double RealDx ,double RealDy ,double RealTheta);
	void	SlightMatch(double &Dx ,double &Dy
						,double RealDx ,double RealDy);
	
	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	void	DrawResult(ResultInItemRoot &Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG);
private:
	void	CreateMap(ImagePointerContainer &SrcImg ,BYTE **Map);
	void	CreateMap(ImagePointerContainer &SrcImg ,BYTE **Map,const BYTE **Mask);

	double	Match(double Dx ,double Dy ,double Theta);
	double	Match(double Dx ,double Dy);
	void	CalcMaster(void);
};

class	ClusteredPicoDim : public NPList<ClusteredPicoDim>
{
	friend	class	AutoAlignmentSheet;
	friend	class	AutoAlignmentInPico;

	//	マスクで領域化された１エリア分のＰＩＣＯ領域群を表す
public:
	AutoAlignmentInPico	***PicoDim;	//別参照
	int	PicoDimXNumb;
	int	PicoDimYNumb;
	int	XByte;
	AutoAlignmentSheet	*Parent;

	ClusteredPicoDim(AutoAlignmentSheet *parent);
	~ClusteredPicoDim(void);

	void	CheckAbnormalVector(void);
	void	CheckAbnormalVector(int KxNumb ,int KyNumb ,int xn ,int yn ,int DivN);
};

class	AutoAlignmentSheet : public AlgorithmItemPI
{
	friend	class	AutoAlignmentInPico;
	friend	class	ClusteredPicoDim;

	AutoAlignmentInPico	**Picos;
	int					PicosCount;

	NPListPack<ClusteredPicoDim>	CPicoDim;

	BYTE		**MasterMap;
	int			XByte;
	QMutex		CalcMutex;

	FlexArea RetFlexArea;	//GetArea(int UniqueAreaType_Code)のreturn用

	BYTE		**PickupBmp;

public:
	bool		CreatedManual;

	AutoAlignmentSheet(void);
	~AutoAlignmentSheet(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AutoAlignmentSheet();	}
	const	AutoAlignmentThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AutoAlignmentThreshold *)GetThresholdBaseReadable(base);	}
	AutoAlignmentThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AutoAlignmentThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold		*CreateThresholdInstance(void)	override{	return new AutoAlignmentThreshold(this);	}

    bool    Save(QIODevice *file)					override;
    bool    Load(QIODevice *file,LayersBase *LBase)	override;

	bool	ColorIsIncluded(AlignmentPacketWithColor *c,int Mergin);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)		override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)		override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	void	PickupMaster(BYTE **TmpMap);
	void	PutShiftMapAll(void);
	void	PutShiftMap(void);
	void	AvoidOverlap(void);

	BYTE	**GetPickupBmp(void)	{	return PickupBmp;	}

#if	defined(NeedFringeBit)
	void	SetTransBit(void);
	void	SetFirstTransBit(void);
#endif
	void	SetPickupBit(void);
	void	SetFirstPickupBit(void);

	bool	GetAlignment(AlignmentPacketWithColor *Packet);
	void	SetBasePointer(AutoAlignmentSheet	*BaseSheet);

	void	MakePickupAreaFromPico(BYTE **BMap,int XByte ,int YLen);
	bool	ExistArea(int localX ,int localY);

	virtual	FlexArea	&GetArea(void)	override	{	return AlgorithmItemRoot::GetArea();	}
	virtual	FlexArea	&GetArea(int UniqueAreaType_Code)	override;

	void	MakePickupTest(BYTE ***TmpMap,BYTE ***TmpMap2,int &TransW,int &NoiseShrink);

private:
	void	PickupBitmap(ImagePointerContainer &SrcImg ,BYTE **Map);
	void	CheckAbnormalVector(int KxNumb ,int KyNumb ,int xn ,int yn ,int DivN);
};

class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
{
public:
	AlignmentPacket2DList(void){}
};
class	AutoAlignmentInPage : public AlgorithmInPagePI
{
	NPListPack<AutoAlignmentInPageMonoMiniSize>		AutoAlignmentInPageMonoMiniSizeContainer;
	QMutex	AlignmentPacket2DCreaterMutex;
	NPListPack<AlignmentPacket2DList>	AlignmentPacket2DContainer;

public:
	bool	NoAdjustMode;

	double	AlignedDx;
	double	AlignedDy;
	double	AlignedTheta;
	QMutex	CommonMutex;

	int		XLen;
	int		YLen;
	int		XByte;

	char	**ResultPerPixXFromTarget;		//絶対系での位置ずれ量
	char	**ResultPerPixYFromTarget;		//絶対系での位置ずれ量
	char	**ResultPerPixXFromMaster;		//絶対系での位置ずれ量
	char	**ResultPerPixYFromMaster;		//絶対系での位置ずれ量
	char	**ResultRelativeXFromTarget;	//ベース位置ずれに対する相対的な位置ずれ量
	char	**ResultRelativeYFromTarget;	//ベース位置ずれに対する相対的な位置ずれ量
	char	**ResultRelativeXFromMaster;	//ベース位置ずれに対する相対的な位置ずれ量
	char	**ResultRelativeYFromMaster;	//ベース位置ずれに対する相対的な位置ずれ量

#if	defined(NeedFringeBit)
	BYTE	**ResultBitTransFromMaster;		//２番目以降の周縁の時、１
	BYTE	**ResultBitTransFromTarget;		//２番目以降の周縁の時、１
	BYTE	**ResultBitFirstTransFromMaster;		//１番目の周縁の時、１
	BYTE	**ResultBitFirstTransFromTarget;		//１番目の周縁の時、１
#endif

	BYTE	**ResultBitPickupFromMaster;		//２番目以降の抽出領域の時、１
	BYTE	**ResultBitPickupFromTarget;		//２番目以降の抽出領域の時、１
	BYTE	**ResultBitFirstPickupFromMaster;		//１番目の抽出領域の時、１
	BYTE	**ResultBitFirstPickupFromTarget;		//１番目の抽出領域の時、１

	AutoAlignmentInPage(AlgorithmBase *parent);
	~AutoAlignmentInPage(void);

	void	InitialAlloc(void);
	virtual	void	Release(void)	override;

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	void	GetAlignment(AlignmentPacketWithColor *Packet);

	int		GetShiftXFromMaster(int x ,int y){	return ResultPerPixXFromMaster[y][x];	}
	int		GetShiftYFromMaster(int x ,int y){	return ResultPerPixYFromMaster[y][x];	}
	int		GetShiftXFromTarget(int x ,int y){	return ResultPerPixXFromTarget[y][x];	}
	int		GetShiftYFromTarget(int x ,int y){	return ResultPerPixYFromTarget[y][x];	}

	int		GetRelativeShiftXFromMaster(int x ,int y){	return ResultRelativeXFromMaster[y][x];	}
	int		GetRelativeShiftYFromMaster(int x ,int y){	return ResultRelativeYFromMaster[y][x];	}
	int		GetRelativeShiftXFromTarget(int x ,int y){	return ResultRelativeXFromTarget[y][x];	}
	int		GetRelativeShiftYFromTarget(int x ,int y){	return ResultRelativeYFromTarget[y][x];	}

#if	defined(NeedFringeBit)
	bool	GetBitTransFromMaster(int x ,int y)	{	return (ResultBitTransFromMaster[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}
	bool	GetBitTransFromTarget(int x ,int y)	{	return (ResultBitTransFromTarget[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}

	bool	GetBitFirstTransFromMaster(int x ,int y)	{	return (ResultBitFirstTransFromMaster[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}
	bool	GetBitFirstTransFromTarget(int x ,int y)	{	return (ResultBitFirstTransFromTarget[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}
#endif
	bool	GetBitPickupFromMaster(int x ,int y)	{	return (ResultBitPickupFromMaster[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}
	bool	GetBitPickupFromTarget(int x ,int y)	{	return (ResultBitPickupFromTarget[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}

	bool	GetBitFirstPickupFromMaster(int x ,int y)	{	return (ResultBitFirstPickupFromMaster[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}
	bool	GetBitFirstPickupFromTarget(int x ,int y)	{	return (ResultBitFirstPickupFromTarget[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	CreateSheet(AlgorithmLibraryListContainer &SelectedLibList);
	int		GetMaxSearchDot(void);

	//BYTE	**GetMaskBitmap(void);

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)			override;
	virtual	bool	DrawResult	  (ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;

	AlignmentPacket2D	*AppendAlignmentPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal);

///	void	PickupTest(AutoAlignmentLibrary &LibData);
///	void	PickupTest(int LibID);
	void	PickupTest(void);

private:
	bool	InnerSearchEffectiveDot(int L,int x ,int y,int &kx ,int &ky);
	bool	IsLocalCamera(void);
	bool	ExistArea(int localX ,int localY);
	void	PhaseProcess(void);
};

inline	AlgorithmItemRoot	*AutoAlignmentInPage::CreateItem(int ItemClassType)
{	
	AutoAlignmentSheet	*a=new AutoAlignmentSheet();	
	a->SetParent(this);
	return a;
}

class	AutoAlignmentBase : public AlgorithmBase
{
	AutoAlignmentInPage	**PageData;
	int		AllocPageDataNumb;
public:
	int			SearchDot;
	int			MaxThetaDegree;
	int			PicoSize;
	int			SelectedLayer;
	int			MinTransDot;
	double		DetailThreshold;
	int			MaxHoleSize;
	int			TransDot;
	int			VectorMergin;
	bool		Enabled;

	AutoAlignmentBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new AutoAlignmentInPage(((AutoAlignmentBase *)parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	QString	GetDataText(void)			override{	return QString("AutoAlignment");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigAutoAlignment.dat");	}

///	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultBaseForAlgorithmRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;
};
//==================================================================================
class	CmdCreateTempAutoAlignmentLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoAlignmentLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAutoAlignmentLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAutoAlignmentLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdUpdateAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetAutoAlignmentLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdCreateAutoAlignmentSheetPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;

	CmdCreateAutoAlignmentSheetPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAutoAlignmentSheetPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetSheetLevel: public GUIDirectMessage
{
public:
	IntList	SheetLevels;
	int		LocalPage;
	CmdGetSheetLevel(LayersBase *base):GUIDirectMessage(base){}
	CmdGetSheetLevel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqAutoAlignmentDrawMode: public GUIDirectMessage
{
public:
	int		DrawSheetMode;
	bool	DrawMono;
	int		MonoLevel;
	int		DrawPico;
	AAListAttrContainer	SelectedLDList;

	GUICmdReqAutoAlignmentDrawMode(LayersBase *base):GUIDirectMessage(base){}
	GUICmdReqAutoAlignmentDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentSheetPacket : public GUIDirectMessage
{
public:
	AASheetInfos	*Point;

	CmdGetAutoAlignmentSheetPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentSheetPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentResult : public GUIDirectMessage
{
public:
	int	LocalX,LocalY;
	int	ShiftXFromMaster,ShiftYFromMaster;
	int	ShiftXFromTarget,ShiftYFromTarget;
	int	ShiftRelativeXFromMaster,ShiftRelativeYFromMaster;
	int	ShiftRelativeXFromTarget,ShiftRelativeYFromTarget;

	CmdGetAutoAlignmentResult(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoAlignmentNoAdjustPacket : public GUIDirectMessage
{
public:

	CmdAutoAlignmentNoAdjustPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoAlignmentNoAdjustPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetAutoAlignmentLibColor : public GUIDirectMessage
{
public:
	FlexArea	LocalArea;
	int			LibID;

	CmdSetAutoAlignmentLibColor(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAutoAlignmentLibColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddAutoAlignmentSheet : public GUIDirectMessage
{
public:
	FlexArea	LocalArea;
	int			LibID;

	CmdAddAutoAlignmentSheet(LayersBase *base):GUIDirectMessage(base){}
	CmdAddAutoAlignmentSheet(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdReqAutoAlignmentEnumLibs: public GUIDirectMessage
//	StartupExecute=trueのライブラリのLibIDリストコンテナを外部から所得する
{
public:
	IntList	LibIDList;
	CmdReqAutoAlignmentEnumLibs(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAutoAlignmentEnumLibs(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdPickupTestAutoAlignmentPacket : public GUIDirectMessage
{
public:
///	int						LibID;
///	AutoAlignmentLibrary	*LibPoint;
	int				PhaseNumb;
	int				Page;

	CmdPickupTestAutoAlignmentPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestAutoAlignmentPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


//=========================================================================
inline	int		AutoAlignmentInPico::GetLayerNumb(void){		return Parent->GetLayerNumb();	}

#endif