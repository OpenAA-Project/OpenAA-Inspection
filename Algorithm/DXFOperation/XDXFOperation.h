#if	!defined(XDXFOperation_h)
#define	XDXFOperation_h

#include "XTypeDef.h"
#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include <QBuffer>
#include "XDoubleClass.h"
#include "XYCross.h"
#include "XDisplayImage.h"
#include "XFlexAreaImage.h"
#include "XDXFOperationCommon.h"

#define	DXFOperationVersion	2


class	DXFOperationItemBase;
class	DXFOperationInPage;
class	DXFOperationBase;
class	DXFLayerContainer;
class	TransformBase;

enum	DXFOperationMode
{
	OM_None					=0
	,OM_Move				=1
	,OM_Extend				=2
	,OM_Rotate				=3
	,OM_SlopeX				=4
	,OM_SlopeY				=5
	,OM_3PointAlignment		=6
	,OM_AddAlignmentPoint	=7
	,OM_Paint				=8
	,OM_Draw				=9
};

struct DxfStandardColor
{
	int	ColorCode;
	BYTE	R,G,B;
};
extern	struct DxfStandardColor	DxfStandardColorTable[256];

class	DXFOperationDrawAttr : public AlgorithmDrawAttr
{
public:
	IntListFast		ShownDXFLayerID;
	bool			ShowFilledArea;
	IntList			ListFileNo;

	DXFOperationDrawAttr(void){	ShowFilledArea=false;	}
	DXFOperationDrawAttr(QColor ncol,QColor scol ,QColor acol);
	DXFOperationDrawAttr(QColor ncol ,int ntranparentLevel
					, QColor scol ,int stranparentLevel
					, QColor acol ,int atranparentLevel);

	AlgorithmDrawAttr	&operator=(const AlgorithmDrawAttr &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	DXFOperationDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;
	if(ShownDXFLayerID.Save(f)==false)
		return false;
	if(::Save(f,ShowFilledArea)==false)
		return false;
	if(ListFileNo.Save(f)==false)
		return false;
	return true;
}

inline	bool	DXFOperationDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;
	if(ShownDXFLayerID.Load(f)==false)
		return false;
	if(::Load(f,ShowFilledArea)==false)
		return false;
	if(ListFileNo.Load(f)==false)
		return false;
	return true;
}
inline	AlgorithmDrawAttr	&DXFOperationDrawAttr::operator=(const AlgorithmDrawAttr &src)
{
	DXFOperationDrawAttr *s	=(DXFOperationDrawAttr *)&src;
	ShownDXFLayerID			=s->ShownDXFLayerID;
	ShowFilledArea			=s->ShowFilledArea;
	ListFileNo				=s->ListFileNo;
	return *this;
}

inline	DXFOperationDrawAttr::DXFOperationDrawAttr(QColor ncol,QColor scol ,QColor acol)
	:AlgorithmDrawAttr(ncol,scol ,acol)
{
	ShowFilledArea=false;
}
inline	DXFOperationDrawAttr::DXFOperationDrawAttr(QColor ncol ,int ntranparentLevel
											,  QColor scol ,int stranparentLevel
											,  QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				,  scol ,stranparentLevel
				,  acol ,atranparentLevel)
{
	ShowFilledArea=false;
}
	
enum	EnumDXFLineType
{
	CONTINUOUS	=1
	,HIDDEN		=2
	,CENTER		=3
	,PHANTOM	=4
};

//========================================================================================

class	DoubleForPolygonList : public NPList<DoubleForPolygonList>
{
public:
	double	X,Y;	//Next Point;
	double	LastX,LastY;
	double	CenterX, CenterY;
	double	StartAngle,EndAngle;
	int		Mode;	//0:Line	1:Arc
	bool	ClockWise;

	DoubleForPolygonList(void)	{	Mode=0;	}
	DoubleForPolygonList(double x ,double y ,double lastx ,double lasty):X(x),Y(y),LastX(lastx),LastY(lasty),Mode(0){}
	DoubleForPolygonList(double centerx ,double centery
						,double startS ,double endS
						,int mode
						,double x ,double y ,double lastx ,double lasty
						,bool clockwise)
						:X(x),Y(y),LastX(lastx),LastY(lasty),CenterX(centerx),CenterY(centery)
						,StartAngle(startS),EndAngle(endS),Mode(mode),ClockWise(clockwise){}
};


class	DXFLayer : public NPListSaveLoad<DXFLayer>
{
public:
	int				LayerID;
	QString			LayerName;
	EnumDXFLineType	LineType;
	int16			ColorCode;

	DXFLayer(DXFLayerContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	int32	GetFileLayerID(void)	{	return LayerID;	}
	void	SetFileLayerID(int m)	{	LayerID=m;		}

	DXFLayer	&operator=(const DXFLayer &src);

private:
};

class	DXFLayerContainer : public NPListPackSaveLoad<DXFLayer>
{
	DXFOperationInPage	*Parent;
public:
	DXFLayerContainer(DXFOperationInPage *parent):Parent(parent){}

	virtual	DXFLayer	*Create(void){	return new DXFLayer(this);	}

	int		GetMaxFileLayerID(void);
	DXFLayer	*Find(int ID);
	DXFOperationInPage	*GetParent(void)	{	return Parent;	}
	DXFLayer	*FindLayer(const QString &name);

	void	Merge(DXFLayerContainer &src);
};


//========================================================================================


class	DXFOperationThreshold : public AlgorithmThreshold
{
public:

	DXFOperationThreshold(DXFOperationItemBase *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override{}
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override{}
};


class	VLineOnDXF : public NPList<VLineOnDXF>
{
public:
	double	VUx,VUy;	//vertial unit vector
	double	PosX,PosY;
	double	Length;

	VLineOnDXF(void){}

	void	Draw(int dx ,int dy,QPainter &Pnt, int movx ,int movy ,double ZoomRate);
};

class   DXFOperationItemBase : public AlgorithmItemPI
{
protected:
	DXFLayer		*pLayer;

public:
  #pragma	pack(push,1)
	int32	FileNo;
	int32	LoadedFileID;
	int32	Version;

	double	CurrentX1,CurrentY1;
	double	CurrentX2,CurrentY2;
	double	AutoMatchA[6];	//for AutoMatching location
	int16	ColorCode;

	EnumDXFLineType	LineType;
	double	Width;	
  #pragma	pack(pop)

	NPListPack<VLineOnDXF>	VLineContainer;
	int		MatchingLayer;
public:

	DXFOperationItemBase(void);

	const	DXFOperationThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const DXFOperationThreshold *)GetThresholdBaseReadable(base);	}
	DXFOperationThreshold			*GetThresholdW(LayersBase *base=NULL){	return (DXFOperationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold		*CreateThresholdInstance(void)	override	{	return new DXFOperationThreshold(this);	}

	virtual	bool	Save(QIODevice *f)						override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)		override;
	virtual	bool	SaveOnlyShape(QIODevice *f)	=0;
	virtual	bool	LoadOnlyShape(QIODevice *f)	=0;

	virtual	int	GetDXFLayerID(void);
	int		GetLoadedFileID(void)					{	return LoadedFileID;		}
	DXFLayer		*GetDXFLayer(void)				{	return pLayer;				}
	void	SetDXFLayer(DXFLayer *L);
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)				const	override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override			=0;

	double	GetZoomRateY(double ZoomRateX);

	QColor	GetColor(AlgorithmDrawAttr *Attr);

	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY)	override;
	virtual	void	MoveToFloat(double dx, double dy)											=0;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							=0;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	=0;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				=0;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									=0;
	virtual	void	TransformByParam(double m[6])												=0;

	virtual	bool	IsInclude(int x ,int y)						const	override=0;
	virtual	bool	IsInclude(double x ,double y)				const			=0;
	virtual	bool	IsCrossed(FlexArea *b)						const	override=0;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override=0;

	virtual	bool	GetCenter(int &cx ,int &cy)			const	override;
	virtual	bool	GetCenter(double &cx ,double &cy)	const	override;

	virtual	void	MoveTo(int dx ,int dy)				override;
	virtual	void	ClipPage(void)						override;
	virtual	void	ClipPage(int DotPerLine ,int MaxLines)	override	=0;

	bool	IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2);
	bool	IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double AngleRadian ,double RCx ,double RCy);
	bool	IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY);
	bool	IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,bool XMode ,double ShearAngle ,double RCx ,double RCy);

	virtual	void	SetCurrentSize(void);
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)		=0;

	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)										override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)		override;

	//void	SelectMatchingLayer(ImageBuffer *IBuff[],int LayerNumb);
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot)	=0;

	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)				override;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)	override;
	virtual	QString	GetComment(Type_ItemComment t)														override;


	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	=0;
	//virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
	//							,AlgorithmDrawAttr *Attr)													=0;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)														=0;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)										=0;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)														=0;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)														=0;

	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	=0;
	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	{	return false;	}
	virtual	double	GetDistance(double x ,double y){	return -1;	}

	virtual	bool	SaveTransformParam(QIODevice *f);
	virtual	bool	LoadTransformParam(QIODevice *f);
protected:
	void	TransformXY(double x ,double y ,double &ResX,double &ResY)	const;
};

inline	void	DXFOperationItemBase::TransformXY(double x ,double y ,double &ResX,double &ResY)	const
{
	ResX=AutoMatchA[0]*x+AutoMatchA[1]*y+AutoMatchA[2];
	ResY=AutoMatchA[3]*x+AutoMatchA[4]*y+AutoMatchA[5];
}


class   DXFOperationItemDot : public DXFOperationItemBase
{
public:
	double	OrgPosX,OrgPosY;
	double	PosX,PosY;

	DXFOperationItemDot(void);
	~DXFOperationItemDot(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemDot();	}
	virtual	int32	GetItemClassType(void)	override	{		return 1;		}

	virtual	void	Draw	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;

	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)		override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)				override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)				override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)				override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;
	virtual	void	TransformByParam(double m[6])					override;


	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;

	virtual	bool	GetCenter(double &cx ,double &cy)			const	override
									{	cx=PosX;	cy=PosY;	return true;	}
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	QString	GetMessageStr(void)	{	return QString("X:")+QString::number(OrgPosX)+QString(",Y:")+QString::number(OrgPosY);	}
	virtual	QString	GetTypeStr(void)	{	return QString("Flash");	}
	virtual	double	GetDistance(double x ,double y)	override;
};

class   DXFOperationItemLine : public DXFOperationItemBase
{
public:
	double	OrgPosX1,OrgPosY1;
	double	OrgPosX2,OrgPosY2;

	double	PosX1,PosY1;
	double	PosX2,PosY2;

	DXFOperationItemLine(void);
	~DXFOperationItemLine(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemLine();	}
	virtual	int32	GetItemClassType(void)		override	{		return 2;		}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)						override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)				override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;
	virtual	void	TransformByParam(double m[6])					override;

	virtual	bool	GetCenter(double &cx ,double &cy)			const	override
							{	cx=(PosX1+PosX2)/2.0;	cy=(PosY1+PosY2)/2.0;	return true;	}
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	QString	GetMessageStr(void)	{	return QString("(")
													+QString::number(OrgPosX1)
													+QString(",")
													+QString::number(OrgPosY1)
													+QString(")-(")
													+QString::number(OrgPosX2)
													+QString(",")
													+QString::number(OrgPosY2)
													+QString(")");	}
	virtual	QString	GetTypeStr(void)	{	return QString("Line");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;

private:

};

class   DXFOperationItemArc : public DXFOperationItemBase
{
public:
	double	OrgCenterX,OrgCenterY ,OrgRadius;
	double	OrgStartAngle,OrgEndAngle;

	double	CenterX,CenterY ,Radius;
	double	StartAngle,EndAngle;

	DXFOperationItemArc(void);
	~DXFOperationItemArc(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemArc();	}
	virtual	int32	GetItemClassType(void)	override	{		return 3;		}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)						override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)		override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)			override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;
	virtual	void	TransformByParam(double m[6])												override;

	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	QString	GetMessageStr(void)	{	return QString("Center(")
												+ QString::number(OrgCenterX)
												+ QString(",")
												+ QString::number(OrgCenterY)
												+ QString(")-Radius(")
												+ QString::number(OrgRadius)
												+ QString(") Start(")
												+ QString::number(OrgRadius*cos(OrgStartAngle))
												+ QString("),End(")
												+ QString::number(OrgRadius*cos(OrgEndAngle))
												+ QString(")");	}
	virtual	QString	GetTypeStr(void)	{	return QString("Arc");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;

	bool	IsIncludeAngle(double angle);

private:

};

class   DXFOperationItemCircle : public DXFOperationItemBase
{
public:
	double	OrgCenterX,OrgCenterY ,OrgRadius;
	double	CenterX,CenterY ,Radius;

	DXFOperationItemCircle(void);
	~DXFOperationItemCircle(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemCircle();	}
	virtual	int32	GetItemClassType(void)	override	{		return 4;		}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)						override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)		override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)			override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;
	virtual	void	TransformByParam(double m[6])												override;

	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)	override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	QString	GetMessageStr(void)	{	return QString("Center(")
												+ QString::number(OrgCenterX)
												+ QString(",")
												+ QString::number(OrgCenterY)
												+ QString(")-Radius(")
												+ QString::number(OrgRadius);	}
	virtual	QString	GetTypeStr(void)	{	return QString("Arc");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;


private:

};

class   DXFOperationItemPolyLine: public DXFOperationItemBase
{
public:
	XYDoubleClassContainer	OrgPoints;		//Convert arc to short line
	XYDoubleClassContainer	Points;

	DXFOperationItemPolyLine(void);
	~DXFOperationItemPolyLine(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemPolyLine();	}
	virtual	int32	GetItemClassType(void)	override	{		return 6;		}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)						override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)		override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)		override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)		override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;
	virtual	void	TransformByParam(double m[6])												override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	bool	GetCenter(double &cx ,double &cy)			const	override;
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)	override;

	virtual	QString	GetMessageStr(void);
	virtual	QString	GetTypeStr(void)	{	return QString("Line");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;

	void	AddItemLine(double LastPosX,double LastPosY,double PosX,double PosY);
	void	AddItemArc (double LastPosX,double LastPosY,double PosX,double PosY,double Angle,double StepLen);
private:
	void	DrawBaseLine	(double	PosX1,double PosY1 ,double PosX2 ,double PosY2
							,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color);
	void	TransformByParam(double m[6] ,double &PosX ,double &PosY);
};

class   DXFOperationItemLWPolyLine: public DXFOperationItemBase
{
public:
	XYDoubleClassContainer	OrgPoints;
	XYDoubleClassContainer	Points;

	DXFOperationItemLWPolyLine(void);
	~DXFOperationItemLWPolyLine(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemLWPolyLine();	}
	virtual	int32	GetItemClassType(void)	override	{		return 5;		}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)						override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)		override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)		override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)		override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;
	virtual	void	TransformByParam(double m[6])												override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	bool	GetCenter(double &cx ,double &cy)			const	override;
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)	override;

	virtual	QString	GetMessageStr(void);
	virtual	QString	GetTypeStr(void)	{	return QString("Line");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;

private:
	void	DrawBaseLine	(double	PosX1,double PosY1 ,double PosX2 ,double PosY2
							,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color);
	void	TransformByParam(double m[6] ,double &PosX ,double &PosY);
};

class   DXFOperationItemFilledArea : public DXFOperationItemBase
{
public:
	//Use Area

	DXFOperationItemFilledArea(void);
	~DXFOperationItemFilledArea(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DXFOperationItemFilledArea();	}
	virtual	int32	GetItemClassType(void)		override	{		return 10;		}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)						override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
								,AlgorithmDrawAttr *Attr)				override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)					override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	void	ExecuteMatch(ImageBuffer *IBuff ,int SearchDot) override;

	virtual	void	MoveToFloat(double dx, double dy)											override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									override;
	virtual	void	TransformByParam(double m[6])												override;

	virtual	bool	GetCenter(double &cx ,double &cy)			const	override;
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const	override;

	virtual	QString	GetMessageStr(void);
	virtual	QString	GetTypeStr(void)	{		return QString("FilledArea");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;

private:

};
//=================================================================================
class	SectionClasses : public NPList<SectionClasses>
{
public:
	QString	RecordName;
	QString	ClassName;
	QString	ApplicationName;
	struct	__FunctionFlag
	{
		bool	EnableDelete			:1;
		bool	EnableTransform			:1;
		bool	EnableChangeColor		:1;
		bool	EnableChangeLayer		:1;
		bool	EnableChangeLineType	:1;
		bool	EnableChangeScale		:1;
		bool	EnableShow				:1;
		bool	EnableClone				:1;
		bool	EnableChangeLineWidth	:1;
		bool	EnableChangePrintStyle	:1;
		bool	IneffectiveWarningDialog:1;
		bool	R13J					:1;
	}FunctionFlag;
	int		CountInstance;

	SectionClasses(void);
};

//=================================================================================

class   DXFOperationInPage : public AlgorithmInPagePI
{
public:
	//View for slave
	bool	MoveMode;
	bool	RotateMode;
	bool	ExtendMode;
	bool	SlopeXMode;
	bool	SlopeYMode;
	DisplayImage::__DrawingMode	Mode;
	int		LastPosX,LastPosY;
	int		MoveStartPosX,MoveStartPosY;
	int		RotateCenterXOnData,RotateCenterYOnData;
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

	BYTE	**ImagingBmp;
	int		ImagingBmpXByte;
	int		ImagingBmpYLen;

	DXFLayerContainer	DXFLayerList;
	NPListPack<SectionClasses>	SectionClassesData;

	DXFOperationInPage(AlgorithmBase *parent);
	~DXFOperationInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	//virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect);
	
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	CreateImagingBmpBuff(void);
	bool	GetAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY);

	void	PickupItem(int globalX,int globalY ,AlgorithmItemPointerListContainer &Found);
	bool	CheckValidity(void);
	void	MakeAlgo		(int LibType,int LibID);
	void	MakeAlgoFillArea(int LibType,int LibID);
	void	MakeAlgoByColor(IntList &ColorCode ,QColor &Color ,int LibType,int LibID);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	void	UndoMove			(QIODevice *f);
	void	UndoRotate			(QIODevice *f);
	void	UndoZoom			(QIODevice *f);
	void	UndoShear			(QIODevice *f);
	void	UndoMirror			(QIODevice *f);
	void	UndoCenterize		(QIODevice *f);
	void	UndoCenterizeOnly	(QIODevice *f);
	void	UndoSetLineWidth	(QIODevice *f);

	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	override{}	//For skip	
	virtual	void	CopyItemsFormDispatcherForParts		(void)	override{}	//For skip

	bool	LoadDXF(FILE *f ,int &ErrorLine ,QStringList &SpecialGroupName,int FileNo);
	void	MatchAutomatic(ImageBuffer *IBuff[]);
public:
	void	MakeImage			(BYTE **CurrentBmp,BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);
	void	MakeImageEnlarge	(BYTE **CurrentBmp,BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);
	void	MakeImageShiftable	(BYTE **CurrentBmp,BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);
	void	MakeImageShrinked	(BYTE **CurrentBmp,BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);
	void	MakeImageUnstable	(BYTE **CurrentBmp,BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);
	void	MakeImageStable		(BYTE **CurrentBmp,BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);

	bool	MakePaintArea(int FileNo,int LocalX,int LocalY);
	void	MakeFilledAllArea(int ShrinkDot);
	void	PipeToSendEffectiveMask(void);
	bool	MakeInsideArea(void);

	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)	override;	//From AlgorithmInPagePI

private:
	int	LoadDXFParagram(FILE *f ,int FileNo ,int Code ,char text[],int &LineNumber,QStringList &SpecialGroupName);
	bool	LoadDXF(const QByteArray &DXFData,int FileNo);
};

class AllocationLibByColorContainerByLevel :public NPListSaveLoad<AllocationLibByColorContainerByLevel>
{
public:
	int								ThresholdLevelID;
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;

	AllocationLibByColorContainerByLevel(void)
		:AllocationLibByColorContainerInst(DXFCommonDataID)
		{	
			ThresholdLevelID=0;
		}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	AllocationLibByColorContainerByLevel	&operator=(const AllocationLibByColorContainerByLevel &src);
};

class AllocationLibByColorContainerByLevelContainer :public NPListPackSaveLoad<AllocationLibByColorContainerByLevel>
{
public:
	AllocationLibByColorContainerByLevelContainer(void)	{}
	virtual	AllocationLibByColorContainerByLevel	*Create(void)	override;
};

class	DXFOperationBase	: public AlgorithmBase
{
public:
	QColor		ColorNormal;
	QColor		ColorSelected;
	QColor		ColorActive;
	QColor		ColorImaging;

	int32		TransparentLevel;
	QColor		SelectedAdded;
	QColor		ActiveAdded;

	int32	TileCopiedSize;
	int32	TileOverlapDot;
	double	StartupZoomRateX;
	double	StartupZoomRateY;
	int32	SearchAreaInMatching;
	bool	CenterizeByArea;
	int32	DefaultMinDotsForAutoMatching;
	double	ThresholdSelfMatch;

	int		SwingDotInLastMatch;
	bool	LoadedCenterization;
	double	LoadedOffsetX;
	double	LoadedOffsetY;

	QColor	ColorVLine;
	double	VLineLength;
	double	VLineIsolation;
	double	SearchDot;

	//AllocationLibByColorContainer	AllocationLibByColorContainerInst;
	AllocationLibByColorContainerByLevelContainer	AllocationLibByColorPackInst;

	DXFOperationBase(LayersBase *Base);

	virtual	QString	GetDataText(void)	override	{	return QString("DXFOperation");				}
	QString	GetDefaultFileName(void)	override	{	return QString("ConfigDXFOperation.dat");	}

	virtual	bool	SaveOnlyBase(QIODevice *f)						override;
	virtual	bool	LoadOnlyBase(QIODevice *f,QString &ErrorMsg)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)						override;

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new DXFOperationInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QColor	GetLayerColor(int Number);
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste) override;

	AllocationLibByColorContainer	*FindAllocationLibByColor(int LevelID=-1);
	virtual	QString	GetNameByCurrentLanguage(void)	override;
private:

};

//======================================================================

class	AlignmentGeneralPipeInfo : public GeneralPipeInfo
{
	DXFOperationInPage	*Parent;
public:
	AlignmentGeneralPipeInfo(DXFOperationInPage *parent)
		: GeneralPipeInfo(parent->GetParentBase()),Parent(parent){}

	virtual	bool	RequireAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY);
};

//======================================================================

#endif