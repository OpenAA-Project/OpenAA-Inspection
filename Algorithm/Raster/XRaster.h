#pragma once

#include <QImage>
#include <QColor>
#include <QIODevice>
#include <QByteArray>
#include "XTypeDef.h"
#include "XIntClass.h"
#include "XDataAlgorithm.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "NListComp.h"
#include <QBuffer>
#include "XDoubleClass.h"
#include "XYCross.h"
#include "XDisplayImage.h"
#include "XFlexAreaImage.h"
#include "XColorConvert.h"

#define	DefLibTypeRaster	36
#define	RasterVersion		6

#define	MaxRasterLayer		100
#define	MaxRasterPointNumb	100
#define	RasterMaxPhaseNumb	20

class	RasterItem;
class	RasterBase;
class	RasterInPage;
class	RotatedXYBuffer;
class	RasterFileLayerContainer;
class	RasterElementListContainer;
class	ColorSamplingAverager;

class	RasterDrawAttr : public AlgorithmDrawAttr
{
public:
	IntListFast		ShownFileID;
	IntListFast		MaskIDLsit;
	QColor			LayerColor[MaxRasterLayer];
	struct __DrawMode
	{	
		int				FileLayerIDTable[MaxRasterLayer];
		int				CurrentElementGlobalPage;
		int				CurrentElementID;
		bool	ShowPDF			:1;
		bool	MoveMode		:1;
		bool	MoveElementMode	:1;
		bool	RotateMode		:1;
		bool	ExtendMode		:1;
		bool	SlopeXMode		:1;
		bool	SlopeYMode		:1;
		bool	AlignmentMode	:1;
		bool	DrawPickUpArea	:1;
		bool	ShowReferenceItems:1;
		int		ReferenceID;
	}DrawMode;

	RasterDrawAttr(void);
	RasterDrawAttr(QColor ncol,QColor scol ,QColor acol);
	RasterDrawAttr(QColor ncol ,int ntranparentLevel
					, QColor scol ,int stranparentLevel
					, QColor acol ,int atranparentLevel);

	AlgorithmDrawAttr	&operator=(AlgorithmDrawAttr &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	RasterDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;
	if(ShownFileID.Save(f)==false)
		return false;
	if(MaskIDLsit.Save(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Save(f,LayerColor[i])==false){
			return false;
		}
	}
	if(f->write((const char *)&DrawMode,sizeof(DrawMode))!=sizeof(DrawMode))
		return false;

	return true;
}

inline	bool	RasterDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;
	if(ShownFileID.Load(f)==false)
		return false;
	if(MaskIDLsit.Load(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Load(f,LayerColor[i])==false){
			return false;
		}
	}
	if(f->read((char *)&DrawMode,sizeof(DrawMode))!=sizeof(DrawMode))
		return false;

	return true;
}
inline	AlgorithmDrawAttr	&RasterDrawAttr::operator=(AlgorithmDrawAttr &src)
{
	RasterDrawAttr	*s=(RasterDrawAttr *)&src;
	ShownFileID	=s->ShownFileID;
	MaskIDLsit	=s->MaskIDLsit;
	for(int i=0;i<MaxRasterLayer;i++){
		LayerColor[i]=s->LayerColor[i];
	}
	DrawMode	=s->DrawMode;
	return *this;
}
inline	RasterDrawAttr::RasterDrawAttr(void)
{	
	DrawMode.CurrentElementID=-1;
	DrawMode.MoveMode		=false;
	DrawMode.RotateMode		=false;
	DrawMode.ExtendMode		=false;
	DrawMode.SlopeXMode		=false;
	DrawMode.SlopeYMode		=false;
	DrawMode.AlignmentMode	=false;
	DrawMode.DrawPickUpArea	=false;
	DrawMode.ShowReferenceItems	=false;
	DrawMode.ReferenceID	=-1;
}
inline	RasterDrawAttr::RasterDrawAttr(QColor ncol,QColor scol ,QColor acol)
	:AlgorithmDrawAttr(ncol,scol ,acol)
{
	DrawMode.CurrentElementGlobalPage=-1;
	DrawMode.CurrentElementID=-1;
	DrawMode.MoveMode		=false;
	DrawMode.RotateMode		=false;
	DrawMode.ExtendMode		=false;
	DrawMode.SlopeXMode		=false;
	DrawMode.SlopeYMode		=false;
	DrawMode.AlignmentMode	=false;
	DrawMode.DrawPickUpArea	=false;
	DrawMode.ShowReferenceItems	=false;
	DrawMode.ReferenceID	=-1;
}
inline	RasterDrawAttr::RasterDrawAttr(QColor ncol ,int ntranparentLevel
									,  QColor scol ,int stranparentLevel
									,  QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				,  scol ,stranparentLevel
				,  acol ,atranparentLevel)
{
	DrawMode.CurrentElementGlobalPage=-1;
	DrawMode.CurrentElementID=-1;
	DrawMode.MoveMode		=false;
	DrawMode.RotateMode		=false;
	DrawMode.ExtendMode		=false;
	DrawMode.SlopeXMode		=false;
	DrawMode.SlopeYMode		=false;
	DrawMode.AlignmentMode	=false;
	DrawMode.DrawPickUpArea	=false;
	DrawMode.ShowReferenceItems	=false;
	DrawMode.ReferenceID	=-1;
}

class	RasterFileLayer : public NPListSaveLoad<RasterFileLayer>
{
	RasterFileLayerContainer	*Parent;

public:
	int32		FileLayerID;
	QString		FileName;
	int32		LibID;
	bool		Visible;

	RasterFileLayer(RasterFileLayerContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	int32	GetFileLayerID(void)	{	return FileLayerID;	}
	void	SetFileLayerID(int m)	{	FileLayerID=m;		}

	RasterFileLayer	&operator=(RasterFileLayer &src)
	{
		//NPListSaveLoad<RasterFileLayer>::operator=(*((NPListSaveLoad<RasterFileLayer> *)&src));
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		src.Save(&Buff);
		Buff.seek(0);
		Load(&Buff);
		return *this;
	}
private:

	RasterBase	*GetRasterBase(void);
};

class	RasterFileLayerContainer : public NPListPackSaveLoad<RasterFileLayer>
{
	RasterInPage	*Parent;
public:
	RasterFileLayerContainer(RasterInPage *parent);

	virtual	RasterFileLayer	*Create(void){	return new RasterFileLayer(this);	}

	RasterFileLayerContainer	&operator=(RasterFileLayerContainer &src);
	int		GetMaxFileLayerID(void);
	RasterFileLayer	*Find(int FileLayerID);
	RasterFileLayer	*FindByLibID(int LibID);
	RasterInPage	*GetParent(void)	{	return Parent;	}
};

//--------------------------------------------------------------------------------------------------------
class	RasterItemAbstract;
class	RasterThreshold : public AlgorithmThreshold
{
public:
	RasterThreshold(RasterItemAbstract *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)		override;
    virtual	bool	Load(QIODevice *f)		override;
    virtual	int		GetSize(void)	const 	override;
};
//--------------------------------------------------------------------------------------------------------

class RasterAreaElement : public NPListSaveLoad<RasterAreaElement>
{
public:
	int					ElementID;
	FlexArea			Area;
	FlexAreaColorImage	ResultArea;
	int			LibID;
	int			ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;

	RasterAreaElement(void);
	RasterAreaElement(const RasterAreaElement &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,RasterDrawAttr *GAttr);
	void	DrawColor(QImage &pnt, int movx ,int movy ,double ZoomRate ,int _ElementID,QRgb col);

	void	Move(int dx ,int dy);
};

class RasterAreaElementContainer :public NPListPackSaveLoad<RasterAreaElement>
{
public:
	RasterAreaElementContainer(void){}
	virtual	RasterAreaElement	*Create(void)	override;

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,RasterDrawAttr *GAttr);
	void	DrawColor(QImage &pnt, int movx ,int movy ,double ZoomRate ,int _ElementID,QRgb col);
	int		GetMaxElementID(void);
};

//--------------------------------------------------------------------------------------------------------

class	RasterMask : public NPListSaveLoad<RasterMask>
{
public:
	int			MaskID;
	FlexArea	MaskArea;

	RasterMask(void);
	RasterMask(const RasterMask &src);

	RasterMask	&operator=(const RasterMask &src);
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	RasterMaskContainer	: public NPListPackSaveLoad<RasterMask>
{
public:
	RasterMaskContainer(void){}
	RasterMaskContainer(const RasterMaskContainer &src);

	RasterMaskContainer	&operator=(const RasterMaskContainer &src);
	virtual	RasterMask	*Create(void);

	int	GetMaxMaskID(void);
	RasterMask	*GetRasterMask(int MaskID);
};

//--------------------------------------------------------------------------------------------------------

class	RasterItemAbstract : public AlgorithmItemPI
{
protected:
	RasterFileLayer		*pFileLayer;
	double		CurrentX1,CurrentY1;
	double		CurrentX2,CurrentY2;
	double		AreaX1,AreaY1,AreaX2,AreaY2;	//Return value for GetXY

	QImage		BaseImage;
	QImage		ImageForDraw;
	double		TransformParam[6];

public:
	RasterMaskContainer			RasterMaskList;
	RasterAreaElementContainer	Elements;
	int32	LoadedFileLayerID;

	RasterItemAbstract(void);

	const	RasterThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const RasterThreshold *)GetThresholdBaseReadable(base);	}
	RasterThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (RasterThreshold *)GetThresholdBaseWritable(base);	}
	virtual	RasterThreshold	*CreateThresholdInstance(void)	override{	return new RasterThreshold(this);	}

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			=0;
	virtual	bool	LoadOnlyShape(QIODevice *f)			=0;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	int		GetMasterNo(void)	override	{	return 0;	}

	virtual	int	GetFileLayerID(void)	;
	int		GetLoadedFileLayerID(void)					{	return LoadedFileLayerID;		}
	RasterFileLayer		*GetFileLayer(void)				{	return pFileLayer;				}
	void	SetFileLayer(RasterFileLayer *L);

	double	GetZoomRateY(double ZoomRateX);
	bool	BuildPointer(RasterFileLayerContainer &FileLayerList);
	QColor	GetColor(AlgorithmDrawAttr *Attr);
	QImage	&GetBaseImage(void)	{	return BaseImage;	}

	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY)	override;
	virtual	void	BuildShapeToArea(void){}

	virtual	bool	SaveTransformParam(QIODevice *f);
	virtual	bool	LoadTransformParam(QIODevice *f);

	bool	GetXY(double &x1,double &y1,double &x2,double &y2)	const	override{	x1=AreaX1;	y1=AreaY1;	x2=AreaX2;	y2=AreaY2;	return true;	}
	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)			const	override;
	virtual	void	MakeXY(void);

	virtual	void	MoveToFloat(double dx, double dy)											;
	virtual	void	Rotate	(double AngleRadian ,double RCx ,double RCy)						;
	virtual	void	Zoom	(double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	;
	virtual	void	Shear	(bool XMode ,double ShearAngle ,double RCx ,double RCy)				;
	virtual	void	Mirror	(bool XMode ,double RCx ,double RCy)								;
	virtual	void	TransformByParam(double m[6])													;
	
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	bool	GetCenter(int &cx ,int &cy)					const	override;
	virtual	bool	GetCenter(double &cx ,double &cy)			const	override;

	virtual	void	MoveTo(int dx ,int dy)						override;
	virtual	void	ClipPage(void)								override;
	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override{}

	virtual	QString	GetMessage(void)							=0;
	virtual	QString	GetTypeStr(void)							=0;

	virtual	void	AddMaskArea(const FlexArea &area);
	virtual	void	DelMaskArea(int MaskID);

	virtual	bool	IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2);
	virtual	bool	IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double AngleRadian ,double RCx ,double RCy);
	virtual	bool	IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY);
	virtual	bool	IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,bool XMode ,double ShearAngle ,double RCx ,double RCy);
	bool	DrawSimple(QImage &pnt, int &x1 ,int &y1 ,int &x2 ,int &y2 ,int ImageWidth ,int ImageHeight ,QRgb Col);

	virtual	void	SetCurrentSize(void);
	virtual	QColor	PickColor(int X ,int Y);
	virtual	QColor	PickColor(const FlexArea &area);
	virtual	QRgb	PickRgb(int X ,int Y);

	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)	override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)		override;


	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)				override;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)	override;

	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)		override;

	virtual	void	Draw		(QImage &pnt, int movx ,int movy ,double ZoomRate 
								,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate 
								,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Color);
	virtual	void	DrawRotate	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle);
	virtual	void	DrawZoom	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate);
	virtual	void	DrawShearX	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle);
	virtual	void	DrawShearY	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle);

	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	=0;
	virtual	void	MakeQImage(QImage *RImage ,int dx ,int dy);
	virtual	void	MakeProfileByImage(const BYTE **MaskBitmap,bool Mastered,ColorSamplingAverager *AveragerDim);

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)=0;

	int		GetMaxElementID(void)	{	return Elements.GetMaxElementID();	}
	void	MakeElementList(RasterElementListContainer *Elements);


	virtual	void	DrawShape(FlexArea &Area,const QColor &Color);
	virtual	void	PickupAddElements(int ElementID 
							,FlexArea	&LocalArea
							,int LocalX,int LocalY
							,int ShrinkDot
							,int InsideEdgeWidth
							,int OutsideEdgeWidth
							,AlgorithmLibraryListContainer &AllocatedStaticLib
							,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
							,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib);

	virtual	void	PickupAddElements(int ElementID 
							,FlexArea &LocalArea
							,FlexArea &ColorArea
							,int ShrinkDot
							,int InsideEdgeWidth
							,int OutsideEdgeWidth
							,AlgorithmLibraryListContainer &AllocatedStaticLib
							,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
							,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib);

	virtual	void	UpdateElement(int ElementID
								,int ShrinkDot 
								,int InsideEdgeWidth
								,int OutsideEdgeWidth
								,AlgorithmLibraryListContainer &AllocatedStaticLib
								,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
								,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib);

protected:
	void	TransformXY(double x ,double y ,double &ResX,double &ResY);
};


class	XpdfWidget;

class	RasterPDFItem : public RasterItemAbstract
{
	QByteArray	PDFDoc;
public:
	XpdfWidget	*Widget;
public:
	RasterPDFItem(void);
	~RasterPDFItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new RasterPDFItem();	}
	virtual	int32	GetItemClassType(void)	override	{	return 1;	}

	bool	LoadPDF(RasterFileLayer *f,const QByteArray &Data);

	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;

	virtual	bool	GetCenter(double &cx ,double &cy)	const	override;

	virtual	QString	GetMessage(void)	override;
	virtual	QString	GetTypeStr(void)	override	{	return QString("PDF");	}

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0
								, double ClipX2=-1.0 ,double ClipY2=-1.0)	override;

	void	MakeAutoRasterReference(BYTE **MaskMap,int XByte,int YLen
									,int ColorMergin ,int MinItemArea,int ShrinkSize);

private:
	void	PourFromImage(FlexArea &area
						,BYTE **Mask
						,int StartX, int StartY
						,BYTE **TmpBuff,int XByte,int YLen
						,QRgb Col ,int ColorMergin);
};

//--------------------------------------------------------------------------------------------------------
class	RasterReferenceItem;
class	RasterReferenceThreshold : public AlgorithmThreshold
{
public:
	RasterReferenceThreshold(RasterReferenceItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)		override;
    virtual	bool	Load(QIODevice *f)		override;
    virtual	int		GetSize(void)	const 	override;
};
//
class	RasterReferenceItem : public AlgorithmItemPI
{
protected:
	int		ColorID;
public:

	RasterReferenceItem(void);

	virtual	int32		GetItemClassType(void)	override	{	return 2;	}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new RasterReferenceItem();	}

	const	RasterReferenceThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const RasterReferenceThreshold *)GetThresholdBaseReadable(base);	}
	RasterReferenceThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (RasterReferenceThreshold *)GetThresholdBaseWritable(base);	}
	virtual	RasterReferenceThreshold	*CreateThresholdInstance(void)	override{	return new RasterReferenceThreshold(this);	}

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	
	virtual	void	Draw(QImage &pnt
						,int movx ,int movy ,double ZoomRate 
						,AlgorithmDrawAttr *Attr)	override;
	bool	GetReferenceColor(QColor &PDFColor ,QColor &ImgColor);
protected:

};

//--------------------------------------------------------------------------------------------------------


class	RasterTriangleArea : public NPListSaveLoad<RasterTriangleArea>
{
public:
	double	Cax,Cay;
	double	Cbx,Cby;
	double	Ccx,Ccy;

	int					Dax,Day;
	int					Dbx,Dby;
	int					Dcx,Dcy;
	double				m[6];

	RasterTriangleArea(void);
	void	GetCenter(double &Cx, double &Cy);

	void	Calc(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	RasterTriangleAreaContainer : public NPListPackSaveLoad<RasterTriangleArea>
{
public:
	RasterTriangleAreaContainer(void){}

	void	BuildTriangle(int CadImagePoints[256][4] ,int PointCount);

	RasterTriangleArea	*GetClosedTriangle(int x ,int y);
	virtual	RasterTriangleArea	*Create(void)	{	return new RasterTriangleArea();	}
};
//--------------------------------------------------------------------------------------------------------

class   RasterInPage : public AlgorithmInPagePI
{
	RasterTriangleAreaContainer			TriangleAreaData;
public:
	RasterFileLayerContainer		FileLayerList;

	//View for slave

	DisplayImage::__DrawingMode	Mode;
	int		LastPosX,LastPosY;
	int		MoveStartPosX,MoveStartPosY;
	int		LastElementPosX		,LastElementPosY;
	int		MoveStartElementPosX,MoveStartElementPosY;
	int		RotateCenterXOnData	,RotateCenterYOnData;
	int		RotateFirstX		,RotateFirstY;
	double	RotateAngle;
	int		ExtendCenterXOnData,ExtendCenterYOnData;
	int		ExtendFirstX		,ExtendFirstY;
	int		SlopeXCenterXOnData,SlopeXCenterYOnData;
	int		SlopeXFirstX	   ,SlopeXFirstY;
	double	SlopeXAngle;
	int		SlopeYCenterXOnData,SlopeYCenterYOnData;
	int		SlopeYFirstX	   ,SlopeYFirstY;
	double	SlopeYAngle;

	DoublePoint	ImagePoint[MaxRasterPointNumb];
	DoublePoint	CadPoint[MaxRasterPointNumb];

	FlexArea	LocalPickupArea;

	BYTE	**ImagingBmp;
	int		ImagingBmpXByte;
	int		ImagingBmpYLen;

	ImageBufferListContainer	RasterMapForMaster;
	int		MasterNo;

	RasterInPage(AlgorithmBase *parent);
	~RasterInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override;
	virtual	void		RemoveItem(AlgorithmItemRoot *item)			override;
	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	bool	BuildPointer(bool &Error);
	void	CreateImagingBmpBuff(void);

	bool	SaveTransformParam(QIODevice *f);
	bool	LoadTransformParam(QIODevice *f);

	int		GetOwnOrder(int FileLayerID);
	void	BuildShapeToArea(void);
	RasterFileLayer			*FindFileLayer(int FileLayerID);

	void	PickupItem(int globalX,int globalY ,AlgorithmItemPointerListContainer &Found);
	void	MakeXY(void);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	void	MakeDraw(int FileLayerID ,AlgorithmItemPointerListContainer &AddedItems);

	void	UndoMove			(QIODevice *f);
	void	UndoRotate			(QIODevice *f);
	void	UndoZoom			(QIODevice *f);
	void	UndoShear			(QIODevice *f);
	void	UndoMirror			(QIODevice *f);
	void	UndoCenterize		(QIODevice *f);
	void	UndoCenterizeOnly	(QIODevice *f);
	void	UndoMovePoints		(QIODevice *f);
	void	UndoRasterDraw		(QIODevice *f);
	void	UndoDrawAllSelected	(QIODevice *f);
	void	UndoRemoveLine		(QIODevice *f);
	void	UndoSwapNext		(QIODevice *f);
	void	UndoDuplicateLine	(QIODevice *f);
	void	UndoAddEmptyLayer	(QIODevice *f);

	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste) override;
	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	override{}	//For skip	
	virtual	void	CopyItemsFormDispatcherForParts		(void)	override{}	//For skip

	void	CopyFrom(AlgorithmBase *DestParent
					,AlgorithmInPageRoot *src 
					,int OffsetX,int OffsetY
					,int PartsMaster ,int PartsID
					,bool ReferedThresholdMode)		override;

	void	SetCurrentSize(void);
	bool	ConvertImageW(QImage &RasterImages ,ImagePointerContainer &DstImages ,RasterMaskContainer &RMaskList);
	bool	CopyRasterToImageByProfile(QImage &RasterImages 
										,ImagePointerContainer &DstImages 
										,const ColorProfileContainerWithTable &ColorProfiles);
	void	MakeProfileByImage(bool Mastered);
public:
	void	MakeImage	(BoolList &ButtonsToOperateLayer,QColor LayerColor[MaxRasterLayer]);
	void	MakeImage	(ImagePointerContainer &DestBuff);
	void	MakeImage	(void);
	void	MakeBitImage(BoolList &ButtonsToOperateLayer,QColor LayerColor[MaxRasterLayer]);
	void	MakeImage			(BYTE **CurrentBmp,int LayerID);
	void	MakeImageEnlarge	(BYTE **CurrentBmp,int LayerID);
	void	MakeImageShiftable	(BYTE **CurrentBmp,int LayerID);
	void	MakeImageShrinked	(BYTE **CurrentBmp,int LayerID);

	void	MakeAlgo(void);

	bool	MakePaintArea(double GlobalX,double GlobalY ,AlgorithmItemPointerListContainer &ItemList
									,AlgorithmItemPointerListContainer &CreatedItems);


	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)	override;	//From AlgorithmInPagePI

	void	SetFileLayerVisible(IntListFast &ShownFileID);

private:
	bool	LoadPDF(RasterFileLayer *f,const QByteArray &Data);
	void	RefreshFileLayerList(void);
};

class	RasterBase : public AlgorithmBase
{
public:
	QColor		ColorNormal;
	QColor		ColorSelected;
	QColor		ColorActive;
	QColor		ColorImaging;

	int32		TransparentLevel;
	QColor		SelectedAdded;
	QColor		ActiveAdded;

	bool	CenterizeByArea;

	int		SwingDotInLastMatch;
	bool	LoadedCenterization;
	double	LoadedOffsetX;
	double	LoadedOffsetY;
	int		MaxBindedAreaLength;
	int		OverlapPixelToCutBigArea;
	double	IsolationToSelect;
	bool	UseMasterImage;
	bool	ModeDeliverAllPhasesInLoadRaster;
	QString	PDFDefaultSize;
	int		MasterNoForImaging;
	double	ThresholdColorConvDistance;
	QString	DefaultTransformFileName;
	QString	DefaultColorProfileFileName;

	ColorProfileContainerWithTable		ColorProfiles;

	RasterBase(LayersBase *Base);

	virtual	void	InitialAfterParamLoaded(void)	override;
	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new RasterInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("Raster");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigRaster.dat");		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)						override;
	virtual	bool	LoadOnlyBase(QIODevice *f,QString &ErrorMsg)	override;

	void	SetPdfXYmm(double &PgSizeX,double &PgSizeY);
};
//==================================================================================
//==================================================================================
//#define	SetIndependentItemDataCommand_OnlyOne			1
//#define	SetIndependentItemDataCommand_All				2
//#define	RasterReqChangeShiftCommand						9
//#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================
//==================================================================================


class ColorSamplingAverager
{
public:
	int64	AddedImageR,AddedImageG,AddedImageB;
	int	Numb;

	ColorSamplingAverager(void){}
};
