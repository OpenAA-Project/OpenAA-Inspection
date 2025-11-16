#if	!defined(XGerberFast_h)
#define	XGerberFast_h

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include <QBuffer>
#include "XGerberFastComposite.h"
#include "XDoubleClass.h"
#include "XYCross.h"
#include "XDisplayImage.h"
#include "XFlexAreaImage.h"
#include "XGerberApertureMacro.h"
#include "XPropertyGerberFastCommon.h"

#define	GerberFastVersion	10

class	GerberFastItemBase;
class	GerberFileLayerContainer;
class	GerberFastInPage;
class	GerberFastItemPointer;
class	GerberFastItemPointerContainer;
class	GerberFastItemPointerContainerContainer;
class	GerberApertureMacro;
class	GerberFastBase;
class	GerberFastItemPolygon;
class	ODBLayerContainer;
class	GerberDCodeBase;


#define	MaxGerberLayer	100
#define	MaxGerberPointNumb	100

extern	QColor	NegaColor;


class	GerberFastDrawAttr : public AlgorithmDrawAttr
{
public:
	IntListFast		ShownFileID;
	bool		SimpleMode;
	bool		VectorMode;
	IntListFast		ShownCompositeID;
	bool		DrawAutoMatchingArea;
	bool		DrawAutoMatchingImage;
	QColor		LayerColor[MaxGerberLayer];
	int			FileLayerIDTable[MaxGerberLayer];
	QColor		CompColor[MaxGerberLayer];

	GerberFastDrawAttr(void)
	{	
		SimpleMode=true;
		VectorMode=true;
		DrawAutoMatchingArea=false;
		DrawAutoMatchingImage=false;
	}
	GerberFastDrawAttr(QColor ncol,QColor scol ,QColor acol);
	GerberFastDrawAttr(QColor ncol ,int ntranparentLevel
					, QColor scol ,int stranparentLevel
					, QColor acol ,int atranparentLevel);

	AlgorithmDrawAttr	&operator=(AlgorithmDrawAttr &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	GerberFastDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;
	if(ShownFileID.Save(f)==false)
		return false;
	if(::Save(f,SimpleMode)==false)
		return false;
	if(ShownCompositeID.Save(f)==false)
		return false;
	if(::Save(f,DrawAutoMatchingArea)==false)
		return false;
	if(::Save(f,DrawAutoMatchingImage)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,LayerColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,CompColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,FileLayerIDTable[i])==false){
			return false;
		}
	}
	return true;
}

inline	bool	GerberFastDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;
	if(ShownFileID.Load(f)==false)
		return false;
	if(::Load(f,SimpleMode)==false)
		return false;
	if(ShownCompositeID.Load(f)==false)
		return false;
	if(::Load(f,DrawAutoMatchingArea)==false)
		return false;
	if(::Load(f,DrawAutoMatchingImage)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,LayerColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,CompColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,FileLayerIDTable[i])==false){
			return false;
		}
	}
	return true;
}
inline	AlgorithmDrawAttr	&GerberFastDrawAttr::operator=(AlgorithmDrawAttr &src)
{
	GerberFastDrawAttr	*s=(GerberFastDrawAttr *)&src;
	ShownFileID			=s->ShownFileID;
	SimpleMode			=s->SimpleMode;
	VectorMode			=s->VectorMode;
	ShownCompositeID	=s->ShownCompositeID;
	DrawAutoMatchingArea=s->DrawAutoMatchingArea;
	DrawAutoMatchingImage=s->DrawAutoMatchingImage;

	for(int i=0;i<MaxGerberLayer;i++){
		LayerColor[i]		=s->LayerColor[i];
		CompColor[i]		=s->CompColor[i];
		FileLayerIDTable[i]	=s->FileLayerIDTable[i];
	}
	return *this;
}

inline	GerberFastDrawAttr::GerberFastDrawAttr(QColor ncol,QColor scol ,QColor acol)
	:AlgorithmDrawAttr(ncol,scol ,acol)
{
	VectorMode=true;
	DrawAutoMatchingArea=false;
}
inline	GerberFastDrawAttr::GerberFastDrawAttr(QColor ncol ,int ntranparentLevel
											,  QColor scol ,int stranparentLevel
											,  QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				,  scol ,stranparentLevel
				,  acol ,atranparentLevel)
{
	VectorMode=true;
	DrawAutoMatchingArea	=false;
}

//========================================================================================

class	ODBStepList : public NPListSaveLoad<ODBStepList>
{
public:
	int	Col;
	QString	Name;
	bool	Usage;

	ODBStepList(void){	Col=-1;		Usage=false;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

};

class	ODBStepContainer : public NPListPackSaveLoad<ODBStepList>
{
public:
	ODBStepContainer(void){}

	virtual	ODBStepList	*Create(void){	return new ODBStepList();	}
};

	
inline	bool	ODBStepList::Save(QIODevice *f)
{
	if(::Save(f,Usage)==false)
		return false;
	if(::Save(f,Col)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	return true;
}

inline	bool	ODBStepList::Load(QIODevice *f)
{
	if(::Load(f,Usage)==false)
		return false;
	if(::Load(f,Col)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	return true;
}

class	ODBLayer : public NPListSaveLoad<ODBLayer>
{
public:
	int	Row;
	QString	Context;
	QString	Type;
	QString	Name;
	bool	Polarity;	//true:Positive
	QString	Start_Name;
	QString	End_Name;

	ODBLayer(void)	{	Row=-1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ODBLayerContainer : public NPListPackSaveLoad<ODBLayer>
{
public:
	virtual	ODBLayer	*Create(void)	{	return new ODBLayer();	}
};

inline	bool	ODBLayer::Save(QIODevice *f)
{
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Context)==false)
		return false;
	if(::Save(f,Type)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,Polarity)==false)
		return false;
	if(::Save(f,Start_Name)==false)
		return false;
	if(::Save(f,End_Name)==false)
		return false;
	return true;
}
inline	bool	ODBLayer::Load(QIODevice *f)
{
	if(::Load(f,Row)==false)
		return false;
	if(::Load(f,Context)==false)
		return false;
	if(::Load(f,Type)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,Polarity)==false)
		return false;
	if(::Load(f,Start_Name)==false)
		return false;
	if(::Load(f,End_Name)==false)
		return false;
	return true;
}

//----------------------------------

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
						:X(x),Y(y)
						,LastX(lastx),LastY(lasty)
						,CenterX(centerx),CenterY(centery)
						,StartAngle(startS),EndAngle(endS)
						,Mode(mode),ClockWise(clockwise){}
};


class	GerberFileLayer : public NPListSaveLoad<GerberFileLayer>
{
	GerberFileLayerContainer	*Parent;

	int		XNum;
	int		XPNum;
	int		YNum;
	int		YPNum;
	double	Unit;
	double	XMultiply;
	double	YMultiply;

	int		RepeatCountX;
	int		RepeatCountY;
	double	RepeatDistanceX;
	double	RepeatDistanceY;
	bool	Interporate360;
	bool	Polarity;

public:
	bool		LeadingZero;
	bool		TrailingZero;
	bool		AbsMode;
	QString		LayerName;
	QString		ImageName;

	int32		FileLayerID;
	QString		FileName;
	QString		Remark;
	int32		LibID;
	GerberDCodeContainer	DCodeList;
	int32		ShrinkDot;

	bool		Visible;
	bool		Operational;
	bool		ViewInvert;

	GerberFileLayer(GerberFileLayerContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	int32	GetFileLayerID(void)	{	return FileLayerID;	}
	void	SetFileLayerID(int m)	{	FileLayerID=m;		}

	GerberDCodeBase	*FindDCode(int dcode);
	bool	LoadGerberData(GerberFastBase *GBase ,FILE *f,bool TestMode);
	bool	LoadNCData(GerberFastBase *GBase ,FILE *f,bool TestMode);
	bool	LoadODBPP(GerberFastBase *GBase ,FILE *file,int &LineNumber);

	void	ReqApertureList(struct	ApertureInfo *Dim ,int DimCount);
	void	SetApertureList(struct	ApertureInfo *Dim ,int DimCount);
	bool	GetPolarity(void)		{	return Polarity;	}
	void	SetPolarity(bool b)		{	Polarity=b;			}
	GerberFileLayer	&operator=(GerberFileLayer &src)
	{
		//NPListSaveLoad<GerberFileLayer>::operator=(*((NPListSaveLoad<GerberFileLayer> *)&src));
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		src.Save(&Buff);
		Buff.seek(0);
		Load(&Buff);
		return *this;
	}
private:
	int		CurrentGCode;
	int		CurrentDCode;
	int		LastGCode;
	int		LastSelectedD;
	double	CurrentX;
	double	CurrentY;
	bool	Shutter;
	bool	PolygonMode;
	NPListPack<DoubleForPolygonList>	PolygonPoints;
	bool	GetLine(char *Buff,int &G,double &X,double &Y,double &I,double &J,int &D,int &M);
	bool	LoadApertureHole(char *fp ,ApertureHole &Hole);

	GerberFastBase	*GetGerberBase(void);
};

class	GerberFileLayerContainer : public NPListPackSaveLoad<GerberFileLayer>
{
	GerberFastInPage	*Parent;
public:
	GerberFileLayerContainer(GerberFastInPage *parent);

	virtual	GerberFileLayer	*Create(void){	return new GerberFileLayer(this);	}

	GerberFileLayerContainer	&operator=(const GerberFileLayerContainer &src);
	int		GetMaxFileLayerID(void);
	GerberFileLayer	*Find(int ID);
	GerberFileLayer	*FindByLibID(int LibID);
	GerberFastInPage	*GetParent(void)	{	return Parent;	}
};

//========================================================================================


class	GerberFastThreshold : public AlgorithmThreshold
{
public:

	GerberFastThreshold(GerberFastItemBase *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
	
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override{}
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override{}
};

//=================================================================================
const int SparsDivCountX=100;
const int SparsDivCountY=100;
class	SparsLineBasePointer;
class	SparsOutline;
class	SparsLineBaseListContainer;

class	SparsLineBase : public NPList<SparsLineBase>
{
public:
	bool	ConnInfo[2];	//Connected at end ?

	SparsLineBase(void){}
	virtual ~SparsLineBase(void){}

	virtual	int		GetClassType(void)	=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;

	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY)	=0;
	virtual	double	GetLength2Point(double x ,double y)																	=0;
	virtual	bool	IsInclude(GerberFastInPage *APage)																	=0;
	virtual	bool	IsIncludeOnBmp		(BYTE **TmpMap1,int XByte ,int YLen)											=0;
	virtual	bool	IsIncludeOnBmpAny	(BYTE **TmpMap1,int XByte ,int YLen)											=0;
	virtual	bool	IsRealEdge(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY])	=0;
	virtual	void	RegisterOnTable(GerberFastInPage *APage ,int ItemID ,SparsOutline *parent,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY])	=0;
	virtual	int		GetEndPoint(double Point[][2])																		=0;
	void	ClearConnInfo(void);
	virtual	void	GetEndVector(int N,double &Dx,double &Dy)															=0;
	virtual	double	GetMinEndY(void)																					=0;
	virtual	double	GetEndXInMinY(void)																					=0;
	virtual	void	GetEndPoint1(double &x,double &y)	=0;
	virtual	void	GetEndPoint2(double &x,double &y)	=0;
	virtual	bool	IsChecked(void)						=0;
	virtual	SparsLineBase	*MakeCenterLine(double MaxWidth,SparsLineBaseListContainer &Container)	=0;

	virtual	SparsLineBase &operator=(const SparsLineBase &src)
			{	ConnInfo[0]=src.ConnInfo[0];
				ConnInfo[1]=src.ConnInfo[1];	return *this;	}
};

class	SparsLine : public SparsLineBase
{
public:
	double	X1,Y1,X2,Y2;

	SparsLine(void){}
	SparsLine(SparsLine &src){	X1=src.X1;	Y1=src.Y1;	X2=src.X2;	Y2=src.Y2;	}

	virtual	int		GetClassType(void)	{	return 1;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	bool	operator==(SparsLine &src);
	bool	OnOneLine(SparsLine &src);

	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY);
	virtual	double	GetLength2Point(double x ,double y);
	virtual	bool	IsInclude(GerberFastInPage *APage);
	virtual	bool	IsIncludeOnBmp		(BYTE **TmpMap1,int XByte ,int YLen);
	virtual	bool	IsIncludeOnBmpAny	(BYTE **TmpMap1,int XByte ,int YLen);
	virtual	bool	IsRealEdge(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY]);
	virtual	void	RegisterOnTable(GerberFastInPage *APage ,int ItemID ,SparsOutline *parent,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY]);
	virtual	int		GetEndPoint(double Point[][2]);
	virtual	void	GetEndVector(int N,double &Dx,double &Dy);
	virtual	double	GetMinEndY(void);
	virtual	double	GetEndXInMinY(void);
	virtual	void	GetEndPoint1(double &x,double &y);
	virtual	void	GetEndPoint2(double &x,double &y);
	virtual	bool	IsChecked(void);
	virtual	SparsLineBase	*MakeCenterLine(double MaxWidth,SparsLineBaseListContainer &Container);
	virtual	SparsLine	&operator=(const SparsLine &src)
						{	SparsLineBase::operator=(*((SparsLineBase *)&src));	
							X1=src.X1;	Y1=src.Y1;
							X2=src.X2;	Y2=src.Y2;	return *this;	}
};

class	SparsArc : public SparsLineBase
{
public:
	double	Cx,Cy,R;
	double	StartAngle,EndAngle;	//clockwise

	SparsArc(void){}
	SparsArc(SparsArc &src)	{	Cx=src.Cx;	Cy=src.Cy;	R=src.R;	StartAngle=src.StartAngle;	EndAngle=src.EndAngle;	}

	virtual	int		GetClassType(void)	{	return 2;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	bool	operator==(SparsArc &src);
	bool	OnOneArc(SparsArc &src);

	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY);
	virtual	double	GetLength2Point(double x ,double y);
	virtual	bool	IsInclude(GerberFastInPage *APage);
	virtual	bool	IsIncludeOnBmp		(BYTE **TmpMap1,int XByte ,int YLen);
	virtual	bool	IsIncludeOnBmpAny	(BYTE **TmpMap1,int XByte ,int YLen);
	virtual	bool	IsRealEdge(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY]);
	virtual	void	RegisterOnTable(GerberFastInPage *APage ,int ItemID ,SparsOutline *parent ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY]);
	virtual	int		GetEndPoint(double Point[][2]);
	virtual	void	GetEndVector(int N,double &Dx,double &Dy);
	virtual	double	GetMinEndY(void);
	virtual	double	GetEndXInMinY(void);
	virtual	void	GetEndPoint1(double &x,double &y);
	virtual	void	GetEndPoint2(double &x,double &y);
	virtual	bool	IsChecked(void);
	virtual	SparsLineBase	*MakeCenterLine(double MaxWidth,SparsLineBaseListContainer &Container);
	virtual	SparsArc	&operator=(const SparsArc &src)
						{	SparsLineBase::operator=(*((SparsLineBase *)&src));	
							Cx=src.Cx;	Cy=src.Cy;
							R=src.R;
							StartAngle=src.StartAngle;
							EndAngle=src.EndAngle;	return *this;	}
};

class	SparsOutline : public NPListPack<SparsLineBase> ,public NPListSaveLoad<SparsOutline>
{
public:
	int		OutlineID;
	bool	Selected;

	SparsOutline(void)				{	OutlineID=-1;	Selected=false;	}
	SparsOutline(SparsOutline &src)	{	OutlineID=src.OutlineID;	Selected=src.Selected;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY);

	void	RemoveSparsWithoutOnBmp	(BYTE **TmpMap1,int XByte ,int YLen);
	void	RemoveSparsWithOnBmp	(BYTE **TmpMap1,int XByte ,int YLen);
	void	RemoveSpars(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY]);
	void	RegisterOnTable(GerberFastInPage *APage ,int ItemID ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY]);
	void	ClearConnInfo(void);

	void	SetID(int id){	OutlineID=id;	}
	bool	IsSelected(double X ,double Y ,double Isolation);

	void	MakePointerList(SparsLineBaseListContainer &Container);
	static	SparsLineBase	*Create(short ClassType);
	virtual	SparsOutline &operator=(const SparsOutline &src);
};

class	SparsShape : public NPListPackSaveLoad<SparsOutline> ,public NPListSaveLoad<SparsShape>
{
	int		ItemID;
public:
	
	SparsShape(void)	{	ItemID=-1;	}
	SparsShape(int itemid):ItemID(itemid){}

	virtual	SparsOutline	*Create(void)	{	return new SparsOutline();	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY);
	void	RemoveSparsWithoutOnBmp	(BYTE **TmpMap1,int XByte ,int YLen);
	void	RemoveSparsWithOnBmp	(BYTE **TmpMap1,int XByte ,int YLen);
	void	RemoveSpars(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY]);
	void	RegisterOnTable(GerberFastInPage *APage ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY]);
	void	ClearConnInfo(void);

	void	SetID(int id){	ItemID=id;	}
	void	MakeID(void);
	void	SetSelected(double X ,double Y ,double Isolation);

	void	MakePointerList(SparsLineBaseListContainer &Container);
};

class	SparsContainer : public NPListPackSaveLoad<SparsShape>
{
public:
	SparsContainer(void){}

	virtual	SparsShape	*Create(void)	{	return new SparsShape();	}
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY);

	void	RemoveSparsWithoutOnBmp	(BYTE **TmpMap1,int XByte ,int YLen);
	void	RemoveSparsWithOnBmp	(BYTE **TmpMap1,int XByte ,int YLen);
	void	RemoveSpars(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY]);
	void	RegisterOnTable(GerberFastInPage *APage ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY]);
	void	ClearConnInfo(void);

	void	MakeID(void);
	void	SetSelected(double X ,double Y ,double Isolation);
	void	RestructConnection(void);
	void	MakeCenterize(double MaxWidth,SparsOutline	&CenterLines);

	void	MakePointerList(SparsLineBaseListContainer &Container);
};

class	SparsNode : public NPList<SparsNode>
{
public:
	SparsLineBase	*P1;
	SparsLineBase	*P2;
	GerberFileLayer	*FLayer;
	int				ConnInfo[2];

	SparsNode(void){	P1=NULL;	P2=NULL;	}

	void	MakeEchingFactor(AlgorithmItemPointerListContainer &AdditionalItems,double EFactor
							,AlgorithmItemPointerListContainer	DPoint[SparsDivCountX][SparsDivCountY]);
};

class	SparsLineBaseList : public NPList<SparsLineBaseList>
{
public:
	SparsLineBase	*Pointer;

	SparsLineBaseList(SparsLineBase *p):Pointer(p){}
};

class	SparsLineBaseListContainer : public NPListPack<SparsLineBaseList>
{
public:
	SparsLineBaseListContainer(void){}
};

//=================================================================================

class	GerberFastItemBasePointerList : public NPList<GerberFastItemBasePointerList>
{
	GerberFastItemBase	*Point;
public:
	GerberFastItemBasePointerList(GerberFastItemBase *p):Point(p){}

	GerberFastItemBase	*GetItem(void)	{	return Point;	}
};

class	GerberFastItemBasePointerContainer : public NPListPack<GerberFastItemBasePointerList>
{
public:
	GerberFastItemBasePointerContainer(void){}
	void	Add(GerberFastItemBase *item);
};

inline	void	GerberFastItemBasePointerContainer::Add(GerberFastItemBase *item)
{
	AppendList(new GerberFastItemBasePointerList(item));
}

class	GerberControlPoint
{
public:
	int	SrcX,SrcY;
	double	*m;
};


class	HairLineList : public NPListSaveLoad<HairLineList>
{
public:
	struct{
		int32	x1,y1;	//Inside of pattern
		int32	x2,y2;	//Outside of pattern
	}Position;

	char	*Data;
	int		*SubAxis;
	int		DataLen;
	double	AA,A;

	HairLineList(void);
	~HairLineList(void);

	HairLineList	&operator=(const HairLineList &src);

	bool	EditInitialAfterEdit(GerberFastItemBase *ParentItem ,int ShiftableDot,BYTE **ImagingBmp,int XByte,int YLen,bool UseMasterImage);
	void	Draw	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Color);
	double	MatchExecute(GerberFastItemBase *ParentItem ,int dx ,int dy,bool &Permitted);
	bool	IsOutsideFromEdge(int MinX ,int MinY ,int MaxX ,int MaxY);
	void	MoveToFloat(double dx, double dy);
	void	Rotate(double AngleRadian ,double RCx ,double RCy)							;
	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	;
	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				;
	void	Mirror(bool XMode ,double RCx ,double RCy);
	double	GetDistance(double Cx,double Cy);

	int		GetDx(void)	{	return Position.x2-Position.x1;	}
	int		GetDy(void)	{	return Position.y2-Position.y1;	}
	int		GetCx(void)	{	return (Position.x2+Position.x1)/2;	}
	int		GetCy(void)	{	return (Position.y2+Position.y1)/2;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	HairLineListContainer : public NPListPackSaveLoad<HairLineList>
{
public:
	virtual	HairLineList	*Create(void)	{	return new HairLineList();	}
	void	MoveToFloat(double dx, double dy);
	void	Rotate(double AngleRadian ,double RCx ,double RCy)							;
	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	;
	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				;
	void	Mirror(bool XMode ,double RCx ,double RCy);
	void	Restruct(int N);
	double	GetDistance(double Cx,double Cy);
};

class	OutlineArea : public FlexArea , public NPListSaveLoad<OutlineArea>
{
public:
	HairLineListContainer	HairLineContaner;

	OutlineArea(void){}

	OutlineArea	&operator=(FlexArea &src);
	void	Draw	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Color);
	void	EditInitialAfterEdit(GerberFastItemBase *ParentItem ,int ShiftableDot,BYTE **ImagingBmp,int XByte,int YLen,bool UseMasterImage);
	double	MatchExecuteEdge(GerberFastItemBase *ParentItem ,int dx ,int dy,bool &Permitted
							,bool UseBrighterInPattern,bool BrighterInPattern);
	double	MatchExecute(GerberFastItemBase *ParentItem ,int dx ,int dy
						,bool UseBrighterInPattern,bool BrighterInPattern);
	bool	IsOutsideFromEdge(int MinX ,int MinY ,int MaxX ,int MaxY);
	void	MoveToFloat(double dx, double dy);
	void	Rotate(double AngleRadian ,double RCx ,double RCy)							;
	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	;
	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				;
	void	Mirror(bool XMode ,double RCx ,double RCy);
	void	Restruct(int N);
	void	RestructInOut(GerberFastItemBase *Item);
	double	GetDistance(double Cx,double Cy);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	OutlineAreaContainer : public NPListPackSaveLoad<OutlineArea>
{
public:
	virtual	OutlineArea	*Create(void)	{	return new OutlineArea();	}

	void	Draw	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Color);
	void	EditInitialAfterEdit(GerberFastItemBase *ParentItem ,int ShiftableDot,BYTE **ImagingBmp,int XByte,int YLen,bool UseMasterImage);
	double	MatchExecute(GerberFastItemBase *ParentItem ,int dx ,int dy
						,int MinX ,int MinY ,int MaxX ,int MaxY
						,bool UseBrighterInPattern,bool BrighterInPattern);
	void	MoveToFloat(double dx, double dy);
	void	Rotate(double AngleRadian ,double RCx ,double RCy)							;
	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	;
	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				;
	void	Mirror(bool XMode ,double RCx ,double RCy);
	void	Restruct(int N);
	void	RestructInOut(GerberFastItemBase *Item);
	double	GetDistance(double Cx,double Cy);
};


class   GerberFastItemBase : public AlgorithmItemPI
{
protected:
	GerberDCodeBase		*pDCode;
	GerberFileLayer		*pFileLayer;

	GerberFastItemBasePointerContainer	ConnectedItems;
  #pragma	pack(push,1)
	int32	LoadedDCode;
	int32	LoadedFileLayerID;
	int32	CompositeID;
	int32	Version;

	double	CurrentX1,CurrentY1;
	double	CurrentX2,CurrentY2;
public:
	int32	AllocatedLibType;
	int32	AllocatedLibID;
	double	AutoMatchA[6];	//for AutoMatching location
	bool	PosiImage;
	bool	EnabledAutomatch;	//If this is outside of image area, this is fales
	bool	Nulled;
	int32	DetailShiftX,DetailShiftY;
	double	CxBefore,CyBefore;	//Center before AutoMatch

	double	AreaX1,AreaY1,AreaX2,AreaY2;	//Return value for GetXY

  #pragma	pack(pop)

public:
	//FlexAreaImageListCoeffContainer		TransDetail;
	OutlineAreaContainer				TransDetail;
	AlgorithmItemPointerListContainer	RelatedItems;
	GerberFastItemBase					*RelationParent;
	int32								RelationParentID;
public:

	GerberFastItemBase(void);

	const	GerberFastThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const GerberFastThreshold *)GetThresholdBaseReadable(base);	}
	GerberFastThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (GerberFastThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new GerberFastThreshold(this);	}

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)	=0;
	virtual	bool	LoadOnlyShape(QIODevice *f)	=0;

	virtual	bool	IsNull(void)	const	override{	return Nulled;	}

	int		GetLoadedDCode(void)						{	return LoadedDCode;				}
	virtual	int	GetDCode(void)							{	return (pDCode!=NULL)?pDCode->DCode:-1;		}
	virtual	GerberDCodeBase		*GetDCodePointer(void)	const	{	return pDCode;					}
	virtual	int	GetFileLayerID(void)	;
	int		GetLoadedFileLayerID(void)					{	return LoadedFileLayerID;		}
	GerberFileLayer		*GetFileLayer(void)				{	return pFileLayer;				}
	void	SetDCode(GerberDCodeBase *d);
	void	SetFileLayer(GerberFileLayer *L);
	int32	GetCompositeID(void)						{	return CompositeID;				}
	void	SetCompositeID(int id)						{	CompositeID=id;					}

	double	GetZoomRateY(double ZoomRateX);

	bool	BuildPointer(GerberFileLayerContainer &FileLayerList);
	virtual	bool	CheckValidity(void){	return true;	}

	QColor	GetColor(AlgorithmDrawAttr *Attr);
	void	MakeConnection(GerberFastItemPointerContainer &AllItems);

	virtual	int	SplitHorizontalCut(GerberFastItemBase *Obj[1000],int MaxCount);
	virtual	int	SplitVerticalCut(GerberFastItemBase *Obj[1000],int MaxCount);
	GerberFastItemPolygon	*MakePolygon(int gx ,int gy ,int Numb,XYClassArea *R);

	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY)	override;
	virtual	void	BuildShapeToArea(void)	=0;
	virtual	bool	GetXY(double &x1,double &y1,double &x2,double &y2)	const	override	{	x1=AreaX1;	y1=AreaY1;	x2=AreaX2;	y2=AreaY2;	return true;	}
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)			const	override;
	virtual	void	MakeXY(void)										=0;
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)=0;

	virtual	void	MoveToFloat(double dx, double dy);
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)							;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)				;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)									;
	virtual	void	TransformParam(double m[6])													=0;

	virtual	bool	IsInclude(int x ,int y)						const	override=0;
	virtual	bool	IsInclude(double x ,double y)				const			=0;
	virtual	bool	IsCrossed(FlexArea *b)						const	override=0;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override=0;
	virtual	bool	IsConnected(GerberFastItemBase *s)						=0;

	virtual	bool	GetCenter(int &cx ,int &cy)			const	override;
	virtual	bool	GetCenter(double &cx ,double &cy)	const	override;
	virtual	int		GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)		{	return 0;	}
	virtual	void	TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)	{}

	virtual	void	MoveTo(int dx ,int dy)	override;
	virtual	void	ClipPage(void)			override;
	virtual	void	ClipPage(int DotPerLine ,int MaxLines)	override	=0;
	virtual	QString	GetMessage(void)							=0;
	virtual	QString	GetTypeStr(void)							=0;

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

	virtual	void	MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength,int dx ,int dy)	=0;
	virtual	void	MakeOutline(SparsShape &OutlineShape)	=0;

	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)	override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;
	//virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage);


	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;


	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)				override;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)	override;

	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override	=0;

	//virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	=0;
	//virtual	HistgramByParamBase	*GetHistgramBase(int HistID);
	//virtual	void	ClearHistgram(void);

	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Color)	=0;
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
	void	SetAutoMatchingM(double *m);
	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	{	return false;	}
	virtual	double	GetDistance(double x ,double y){	return -1;	}

	void	MakeTransDetailArea(ConstMapBuffer &MaskMap ,int TransDot);
	void	MatchClosed(ImageBuffer &IBuff ,int SearchDotX1 ,int SearchDotY1 ,int SearchDotX2 ,int SearchDotY2 ,int &Dx ,int &Dy);
	bool	GetPosiImage(void)	{	return PosiImage;	}
	void	SetPosiImage(bool b){	PosiImage=b;		}
	void	SetDetailMatchRelation(IntList &FileLayerIDContainer);
	int		GetCrossedCount(OutlineAreaContainer &SrcOutline);
	void	RestructHairline(void);
	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)=0;

	void	FuncEachSearchDot(ImageBuffer &Ibuff,int EachSearchDot
							,int Mx,int My,int &OffsetX ,int &OffsetY
							,int DotPerLine ,int MaxLines ,int EdgeMergin
							,bool UseBrighterInPattern,bool BrighterInPattern);
protected:
	void	TransformXY(double x ,double y ,double &ResX,double &ResY)	const;
};

inline	void	GerberFastItemBase::TransformXY(double x ,double y ,double &ResX,double &ResY)	const
{
	ResX=AutoMatchA[0]*x+AutoMatchA[1]*y+AutoMatchA[2];
	ResY=AutoMatchA[3]*x+AutoMatchA[4]*y+AutoMatchA[5];
}



class   GerberFastItemFlash : public GerberFastItemBase
{
public:
	double	OrgPosX,OrgPosY;
	double	PosX,PosY;
	double	Angle;		//Radian
	double	ZoomAperture;
	bool	ModeMirrorX;
	bool	ModeMirrorY;

	GerberFastItemFlash(void);
	~GerberFastItemFlash(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new GerberFastItemFlash();	}
	virtual	int32	GetItemClassType(void)		override	{		return 1;		}

	virtual	void	Draw		(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;

	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;
	virtual	void	TransformParam(double m[6])	override;
	virtual	int		GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)	override;
	virtual	void	TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)	override;
	virtual	bool	LoadOnlyShape(QIODevice *f)	override;

	virtual	void	BuildShapeToArea(void)	override;
	virtual	void	MakeXY(void)	override;
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;

	virtual	void	MoveToFloat(double dx, double dy)	override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)	override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)	override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)	override;

	virtual	bool	GetCenter(double &cx ,double &cy)	const override	{	cx=PosX;	cy=PosY;	return true;	}
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;
	virtual	bool	IsConnected(GerberFastItemBase *s)					override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	void	CutArea(FlexArea &localArea,bool &_Change)	override;

	virtual	QString	GetMessage(void)	override{	return QString("X:")+QString::number(OrgPosX)+QString(",Y:")+QString::number(OrgPosY);	}
	virtual	QString	GetTypeStr(void)	override{	return QString("Flash");	}
	virtual	double	GetDistance(double x ,double y)	override;

	virtual	void	MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)	override;
	virtual	void	MakeOutline(SparsShape &OutlineShape)	override;

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)	override;
};

class   GerberFastItemLine : public GerberFastItemBase
{
public:
	double	OrgPosX1,OrgPosY1;
	double	OrgPosX2,OrgPosY2;

	double	PosX1,PosY1;
	double	PosX2,PosY2;
	double	ZoomAperture;

	GerberFastItemLine(void);
	~GerberFastItemLine(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new GerberFastItemLine();	}
	virtual	int32	GetItemClassType(void)		override	{		return 2;		}

	virtual	void	Draw		(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;

	virtual	void	BuildShapeToArea(void)	override;
	virtual	void	MakeXY(void)			override;
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;

	virtual	void	MoveToFloat(double dx, double dy)	override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)	override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)	override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)	override;
	virtual	void	TransformParam(double m[6])	override;
	virtual	int		GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)		override;
	virtual	void	TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)	override;

	virtual	bool	GetCenter(double &cx ,double &cy)	const	override	{	cx=(PosX1+PosX2)/2.0;	cy=(PosY1+PosY2)/2.0;	return true;	}
	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;
	virtual	bool	IsConnected(GerberFastItemBase *s)			override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override;

	virtual	QString	GetMessage(void)	override{	return QString("(")
													+QString::number(OrgPosX1)
													+QString(",")
													+QString::number(OrgPosY1)
													+QString(")-(")
													+QString::number(OrgPosX2)
													+QString(",")
													+QString::number(OrgPosY2)
													+QString(")");	}
	virtual	QString	GetTypeStr(void)	override	{	return QString("Line");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;
	virtual	void	MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)	override;
	virtual	void	MakeOutline(SparsShape &OutlineShape)	override;

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)	override;

private:
	void	MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
						,OutlineArea &TransArea,double Isolation ,double HairlineLength);
	void	MakeHairline(double Angle ,double &x1,double &y1,double &x2,double &y2, double HairlineLength ,double Radius);

};

class   GerberFastItemArc : public GerberFastItemBase
{
public:
	double	OrgCenterX,OrgCenterY ,OrgRadius;
	double	OrgStartAngle,OrgEndAngle;

	double	CenterX,CenterY ,Radius;
	double	StartAngle,EndAngle;
	double	ZoomAperture;

	GerberFastItemArc(void);
	~GerberFastItemArc(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new GerberFastItemArc();	}
	virtual	int32	GetItemClassType(void)		override	{		return 3;		}

	virtual	void	Draw		(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)		override;
	virtual	bool	SaveOnlyShape(QIODevice *f)				override;
	virtual	bool	LoadOnlyShape(QIODevice *f)				override;

	virtual	void	BuildShapeToArea(void)	override;
	virtual	void	MakeXY(void)			override;
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;

	virtual	void	MoveToFloat(double dx, double dy)	override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)	override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)	override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)	override;
	virtual	void	TransformParam(double m[6])	override;
	virtual	int		GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)		override;
	virtual	void	TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)	override;

	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;
	virtual	bool	IsConnected(GerberFastItemBase *s)			override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override;

	virtual	QString	GetMessage(void)	override{	return QString("Center(")
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
	virtual	QString	GetTypeStr(void)	override	{	return QString("Arc");	}

	virtual	bool	GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)	override;
	virtual	double	GetDistance(double x ,double y)	override;
	virtual	void	MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)		override;
	virtual	void	MakeOutline(SparsShape &OutlineShape)	override;

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)	override;

	bool	IsIncludeAngle(double angle);

private:
	void	MakeOutlineWithHairlineArc(OutlineArea &TransArea,double Isolation ,double HairlineLength
					,double  Cx,double  Cy
					,double Radius,bool PosiImage
					,double StartAngle ,double EndAngle ,bool Clockwise);


};


class   GerberFastItemPolygon : public GerberFastItemBase
{
public:
	class	PointStruct
	{
	public:
		enum	EnumPointType{
			_Line	=1
			,_Arc	=2
		};
		union{
			struct{
				EnumPointType	PointType;
				double	PosX,PosY;			//Next point
				double	LastX,LastY;
				double	CenterX,CenterY;
				double	RadiusX,RadiusY;
				double	Rotation;
				double	StartAngle;
				double	EndAngle;
				bool	ReverseStartEnd;
			}Data;
			//struct __OldData{
			struct{
				EnumPointType	PointType;
				double	PosX,PosY;			//Next point
				double	LastX,LastY;
				double	CenterX,CenterY;
				double	RadiusX,RadiusY;
				double	Rotation;
				double	StartAngle;
				double	EndAngle;
			}DataOld;
		};

		PointStruct(void){	Data.ReverseStartEnd=false;	}


		void	Initial(void);
		void	Initial(double LastX ,double LastY);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f ,int Version);
		PointStruct	&operator=(PointStruct &src);
		PointStruct	&operator=(DoubleForPolygonList &src);
		bool	operator==(PointStruct &src);
		bool	operator!=(PointStruct &src);
		int		GetCrossed(double Y ,double RetX[2]);
		int		GetCrossedX(double X ,double RetY[2]);
		void	CreateConnection(void);

		void	MakeXY(double &x1,double &y1,double &x2,double &y2);
		void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY);
		void	MoveToFloat(double dx, double dy);
		void	Rotate(double SinS ,double CosS ,double Angle ,double RCx ,double RCy);
		void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY);
		void	Shear(bool XMode ,double TanS ,double Angle ,double RCx ,double RCy);
		void	Mirror(bool XMode ,double RCx ,double RCy);
		void	TransformParam(double m[6]);
		void	MakeRadius(double Px,double Py ,double Qx,double Qy ,double Cx,double Cy ,double &Rx,double &Ry);
		bool	IsIncludeAngle(double angle);
	};

	PointStruct	*OrgPoints;
	int		OrgPosCount;

	PointStruct	*Points;
	int		PosCount;
	PointStruct	*TrPoints;

	GerberFastItemPolygon(void);
	~GerberFastItemPolygon(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new GerberFastItemPolygon();	}
	virtual	int32	GetItemClassType(void)		override	{		return 4;		}
	void	InitialFromOrg(void);
	void	Initial(PointStruct	*P,int PNumb);

	virtual	int	GetDCode(void)		override	{	return -1;	}

	virtual	void	Draw		(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override;
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;

	virtual	bool	CheckValidity(void)		override;

	virtual	bool	Save(QIODevice *f)						override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)		override;
	virtual	bool	SaveOnlyShape(QIODevice *f)				override;
	virtual	bool	LoadOnlyShape(QIODevice *f)				override;

	virtual	void	BuildShapeToArea(void)	override;
	virtual	void	MakeXY(void)			override;
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override;
	virtual	void	SetCurrentSize(void)	override;

	virtual	void	MoveToFloat(double dx, double dy)	override;
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)	override;
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)	override;
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)	override;
	virtual	void	TransformParam(double m[6])	override;
	virtual	int		GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)		override;
	virtual	void	TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)	override;
	void			RegulateConnection(PointStruct	*P,int PNumb);

	virtual	bool	IsInclude(int x ,int y)						const	override;
	virtual	bool	IsInclude(double x ,double y)				const	override;
	virtual	bool	IsCrossed(FlexArea *b)						const	override;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override;
	virtual	bool	IsConnected(GerberFastItemBase *s)			override;

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override;
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override;

	virtual	QString	GetMessage(void)	override	{	return QString("Points:")
															+  QString::number(OrgPosCount);	}
	virtual	QString	GetTypeStr(void)	override	{	return QString("Polygon");	}
	virtual	double	GetDistance(double x ,double y)	override;

	virtual	void	MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)	override;
	virtual	void	MakeOutline(SparsShape &OutlineShape)	override;

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)	override;
private:
	bool	MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
						,OutlineArea &TransArea,double Isolation ,double HairlineLength
						, double ThresholdLen);
	bool	MakeHairlineArc (double CenterX	,double CenterY
							,double RadiusX		,double RadiusY
							,double StartAngle	,double EndAngle
							,OutlineArea &TransArea,double Isolation ,double HairlineLength
							, double ThresholdLen);
	bool	IsIncludeYDim(int X ,int Y);
	bool	IsIncludeYDimDouble(double X ,double Y)	const;
};

class   GerberFastItemComposite : public GerberFastItemBase	//１レイヤ?で１個のインス?ンス
{
	QImage	*TmpImage;
	QImage	*SrcImage;
public:
	GerberCompositeDefLayer	*CompositeLayer;

	GerberFastItemComposite(void);
	~GerberFastItemComposite(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new GerberFastItemComposite();	}
	virtual	int32	GetItemClassType(void)		override	{		return 5;		}

	virtual	int	GetDCode(void)			override	{	return -1;	}
	virtual	int	GetFileLayerID(void)	override	{	return -1;	}
	virtual	bool	GetSelected(void)	override	{	return false;	}

	virtual	void	Draw		(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)	override{}
	virtual	void	DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)	override;
	virtual	void	DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)	override;
	virtual	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)	override;
	void	MakeImage(GerberGenerationFileContainer &GFileContainer,BYTE **Image ,int dx ,int dy ,int XByte ,int YLen);

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;
	virtual	bool	SaveOnlyShape(QIODevice *f)			override;
	virtual	bool	LoadOnlyShape(QIODevice *f)			override;

	virtual	int	SplitHorizontalCut(GerberFastItemBase *Obj[1000],int MaxCount)	override	{	return 0;	}
	virtual	int	SplitVerticalCut(GerberFastItemBase *Obj[1000],int MaxCount)	override	{	return 0;	}

	virtual	void	BuildShapeToArea(void)	override;
	virtual	void	MakeXY(void)			override;
	virtual	void	RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)	override	{}

	virtual	void	MoveToFloat(double dx, double dy)	override	{}
	virtual	void	Rotate(double AngleRadian ,double RCx ,double RCy)	override	{}
	virtual	void	Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override	{}
	virtual	void	Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)	override	{}
	virtual	void	Mirror(bool XMode ,double RCx ,double RCy)	override	{}
	virtual	void	TransformParam(double m[6])	override	{}
	virtual	int		GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)		override;
	virtual	void	TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)	override;

	virtual	bool	IsInclude(int x ,int y)						const	override	{	return false;	}
	virtual	bool	IsInclude(double x ,double y)				const	override	{	return true;	}
	virtual	bool	IsCrossed(FlexArea *b)						const	override	{	return false;	}
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const	override	{	return false;	}
	virtual	bool	IsConnected(GerberFastItemBase *s)					override	{	return false;	}

	virtual	void	ClipPage(int DotPerLine ,int MaxLines)		override	{}
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override	{}

	virtual	QString	GetMessage(void)	override	{	return QString("Composite");	}
	virtual	QString	GetTypeStr(void)	override	{	return QString("Composite");	}
	virtual	void	MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)	override	{}
	virtual	void	MakeOutline(SparsShape &OutlineShape)	override	{}

	virtual	double	GetAreaSize(bool EnableClip , bool &Clipped
								,double ClipX1=0.0 ,double ClipY1=0.0, double ClipX2=-1.0 ,double ClipY2=-1.0)	override	{	return 0;	}

	virtual	bool	IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2)	override;
	virtual	bool	IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double AngleRadian ,double RCx ,double RCy)	override;
	virtual	bool	IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)	override;
	virtual	bool	IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,bool XMode ,double ShearAngle ,double RCx ,double RCy)	override;

private:
	void	MakeNegImage(QImage &SrcImage,QRgb Col);

};

//=========================================================================

class	AutomatchingBox
{
	GerberFastInPage	*Parent;
public:
	int32		X1,Y1,X2,Y2;
	int32		AdoptedLayer;

	int32		XAddr,YAddr;
	double		ResultMatch;
	int32		ResultDx,ResultDy;
	bool		Enabled;
	bool		Adopted;
	double		AreaDots;
	int32		CalcDx,CalcDy;
	bool		DoneAutoMatch;

	FlexAreaImageListCoeffContainer		MatchingZones;

	AutomatchingBox(void);

	void	GetCenter(int &cx ,int &cy);
	void	GetCenter(double &cx ,double &cy);
	bool	IsInclude(int x,int y);
	void	SetParent(GerberFastInPage *p){	Parent=p;	}
	void	ExpandBitImage(BYTE **SrcImage ,BYTE Col ,int XByte,int YLen);
	void	Draw(QPainter &Pnt ,QImage &pnt ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	double	SelfSearch(BYTE **ImagingBmp,int XLen ,int YLen ,int SearchAreaInMatching,int Farther);
	double	ExecuteMatching(int &dx ,int &dy);
	void	Clear(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	int		GetWidth(void)	{	return X2-X1;	}
	int		GetHeight(void)	{	return Y2-Y1;	}
private:
	double	CalcSelfCoef(BYTE **ImagingBmp,int XLen ,int YLen ,int dx,int dy);
};

//=========================================================================
/*
class	FlexAreaImageListCoeffLineH : public NPListSaveLoad<FlexAreaImageListCoeffLineH>
{
	double	HSAvr;
	double	HSS;
public:
	int		Cy;
	BYTE	*HData;
	int		HStart,HLen;

	FlexAreaImageListCoeffLineH(void);
	~FlexAreaImageListCoeffLineH(void);

	virtual	void    MoveToNoClip(int dx, int dy);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	void	SetCross(int X1,int Len ,int Y ,BYTE **CurrentBmp ,int XByte ,int YLen);
	double	CalcCross(int dx ,int dy ,ImageBuffer &Buff);
};

class	FlexAreaImageListCoeffLineHContainer	:public NPListPackSaveLoad<FlexAreaImageListCoeffLineH>
{
public:
	FlexAreaImageListCoeffLineHContainer(void){}

	FlexAreaImageListCoeffLineH *Create(void){	return new FlexAreaImageListCoeffLineH();	}
};

class	FlexAreaImageListCoeffLineV : public NPListSaveLoad<FlexAreaImageListCoeffLineV>
{
	double	VSAvr;
	double	VSS;
public:
	int		Cx;
	BYTE	*VData;
	int		VStart,VLen;

	FlexAreaImageListCoeffLineV(void);
	~FlexAreaImageListCoeffLineV(void);

	virtual	void    MoveToNoClip(int dx, int dy);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	void	SetCross(int X1,int Len ,int Y ,BYTE **CurrentBmp ,int XByte ,int YLen);
	double	CalcCross(int dx ,int dy ,ImageBuffer &Buff);
};

class	FlexAreaImageListCoeffLineVContainer	:public NPListPackSaveLoad<FlexAreaImageListCoeffLineV>
{
public:
	FlexAreaImageListCoeffLineVContainer(void){}

	FlexAreaImageListCoeffLineV *Create(void){	return new FlexAreaImageListCoeffLineV();	}
};
*/
class	MatchAutoLikeManual;
class	FlexAreaImageListCoeffAndResult : public FlexAreaImageListCoeff
{
public:
	int	Dx,Dy;
	int		Cx,Cy;
	BYTE	*HData;		//0,1,2		2:Ignore
	int		HStart,HLen;
	BYTE	*VData;
	int		VStart,VLen;
	double	HSAvr;
	double	HSS;
	double	VSAvr;
	double	VSS;

	FlexAreaImageListCoeffAndResult(void);
	~FlexAreaImageListCoeffAndResult(void);

	FlexAreaImageListCoeffAndResult	&operator=(FlexArea &src);
	FlexAreaImageListCoeffAndResult	&operator=(FlexAreaImageListCoeffAndResult &src);
	virtual	void    MoveToNoClip(int dx, int dy);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	SetCross(FlexAreaPointerContainer &Container,BYTE **CurrentBmp ,int XByte ,int YLen);
	double	CalcCross(int dx ,int dy ,ImageBuffer &Buff);

	void	DrawCross(QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &col);

};
class	FlexAreaImageListCoeffAndResultContainer : public FlexAreaImageListCoeffContainer
{
public:
	FlexAreaImageListCoeffAndResultContainer(void){}

	virtual	FlexAreaImageList *CreateNew(void){		return new FlexAreaImageListCoeffAndResult();	}
};

class	ParallelRoughMatch
{
	MatchAutoLikeManual *Parent;
public:
	FlexAreaImageListCoeffAndResultContainer	TransZone;
	PureFlexAreaListContainer				InsideZone;
	PureFlexAreaListContainer				OutsideZone;

	ParallelRoughMatch(MatchAutoLikeManual *parent);

	void	MakeArea(BYTE **CurrentBmp ,int XByte ,int YLen ,FlexAreaPointerContainer &Container);
	void	RoughMatch(ImageBuffer &IBuff ,int SearchAreaRoughMatch ,int &Mx,int &My);
	void	MoveTo(int dx ,int dy);
	void	Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &col);
	void	Clear(void);
	void	RemoveArea(int localX,int localY);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ParallelDetalMatch	//Normally LeftTop
{
	MatchAutoLikeManual *Parent;
public:
	FlexAreaImageListCoeffAndResultContainer	TransZone;

	ParallelDetalMatch(MatchAutoLikeManual *Parent);
	void	MakeArea(BYTE **CurrentBmp ,int XByte ,int YLen ,FlexAreaPointerContainer &Container);
	void	Match(ImageBuffer &IBuff ,int SearchArea ,int &Mx,int &My);
	void	MoveTo(int dx ,int dy);
	void	GetCenter(double &Cx,double &Cy);
	void	Rotate(double Angle,double Cx,double Cy);
	void	Zoom(double ZoomX, double ZoomY ,double Cx,double Cy);
	void	Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &col);
	bool	IsEmpty(void);
	void	Clear(void);
	void	RemoveArea(int localX,int localY);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	MatchAutoLikeManualContainer;
class	MatchAutoLikeManual : public ServiceForLayers ,public NPList<MatchAutoLikeManual>
{
	FlexArea			MaskArea;
	ParallelRoughMatch	AreaForRough;
	ParallelDetalMatch	AreaForParallel;
	ParallelDetalMatch	AreaForRotate;
	ParallelDetalMatch	AreaForZoom;
	
public:
	GerberFastInPage	*Parent;
	MatchAutoLikeManualContainer	*ParamParent;

	MatchAutoLikeManual(MatchAutoLikeManualContainer *parent);
	MatchAutoLikeManual(LayersBase *p);

	void	Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	bool	CreateArea(FlexArea *Mask,BYTE **CurrentBmp,int XByte ,int YLen);
	void	Clear(void);

	void	ExecuteMatchFirst(void);
	void	MatchAutoLikeManualMove		(int Mx,int My);
	void	MatchAutoLikeManualRotation	(double	Cx ,double Cy ,double Angle);
	void	MatchAutoLikeManualZoom		(double Cx,double Cy ,double XZoomDir,double YZoomDir);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	RemoveArea(int localX,int localY);

private:
	double	SelfMatch(BYTE **CurrentBmp,int XByte ,int YLen ,FlexAreaPointerContainer &Container ,int SearchDot);
	void	PickupArea(int x1,int y1,int W,int H ,FlexAreaPointerContainer &Container,PureFlexAreaListContainer &ItemPack);

};

class	MatchAutoLikeManualContainer : public NPListPack<MatchAutoLikeManual>
{
	PureFlexAreaListContainer PartialPack;
public:
	GerberFastInPage	*Parent;
	int		AdpptedLayer;		//0-9999: Normal layer   10000-:Composite layer
	int		TransDot;
	double	RoughMatchAreaWidthRate;
	double	RoughMatchAreaHeightRate;
	int		SearchAreaRoughMatch;
	int		SearchAreaParallelMatch;
	int		SearchAreaRotateMatch;
	int		SearchAreaZoomMatch;
	int		SearchAreaMatchDetail;
	int		DataIsolation;
	int		NearByPattern;
	double	MatchingRateToNeighbor;

	MatchAutoLikeManualContainer(GerberFastInPage *parent);
	//MatchAutoLikeManualContainer(void);

	LayersBase	*GetLayersBase(void);

	bool	SaveParam(QIODevice *f);
	bool	LoadParam(QIODevice *f);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	bool	CreateArea(void);
	bool	CreateDetail(void);
	void	Clear(void);

	void	PartiallyMatch(ConstMapBuffer &MaskMap ,int SesarchDot
						, BoolList &ButtonsToOperateLayer
						, IntList  &OperateCompositeIDList);

	void	ExecuteMatchFirst(void);
	void	ExecuteMatchDetail(bool BrighterInPattern);
	void	ExecuteMatchDetail2(void);
	void	ExecuteMatchDetail3(bool BrighterInPattern);
	void	ExecuteMatchDetail4(bool BrighterInPattern);

private:
	FlexAreaImageListCoeffAndResult	*GetClosed(AlgorithmItemPI *c 
											  ,FlexAreaImagePointerListContainer &PointMap);
	void	PartiallyMatchSlight(ImageBuffer &Ibuff
								,PureFlexAreaListContainer &FPack,BYTE **BaseMap,int XByte,int YLen
								,int AreaX1,int AreaY1,int AreaX2,int AreaY2
								,int dx,int dy,int &Mx,int &My
								,int TransDot ,int Sep);
	double	PartiallyMatchSlight(ImageBuffer &Ibuff
								,FlexArea *A,BYTE **BaseMap,int XByte,int YLen
								,int AreaX1,int AreaY1,int AreaX2,int AreaY2
								,int dx,int dy);
};

class	MatchAlignmentArea : public NPList<MatchAlignmentArea>
{
	GerberFastInPage	*Parent;
public:
	FlexArea			Area;
	int					PointType;
	IntList				LayerList;

	MatchAlignmentArea(GerberFastInPage	*parent);

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &col);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int localX,int localY)	{	return Area.IsInclude(localX,localY);	}
};

class	MatchAlignmentAreaContainer : public NPListPack<MatchAlignmentArea>
{
	GerberFastInPage	*Parent;
public:
	MatchAlignmentAreaContainer(GerberFastInPage *parent);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	RemoveArea(int localX,int localY);
};

//*******************************************************************************

class	TriangleArea : public NPListSaveLoad<TriangleArea>
{
public:
	double	Cax,Cay;
	double	Cbx,Cby;
	double	Ccx,Ccy;

	int					Dax,Day;
	int					Dbx,Dby;
	int					Dcx,Dcy;
	double				m[6];

	TriangleArea(void);
	void	GetCenter(double &Cx, double &Cy);

	void	Calc(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	TriangleAreaContainer : public NPListPackSaveLoad<TriangleArea>
{
public:
	TriangleAreaContainer(void){}

	void	BuildTriangle(int CadImagePoints[256][4] ,int PointCount);

	TriangleArea	*GetClosedTriangle(int x ,int y);
	virtual	TriangleArea	*Create(void)	{	return new TriangleArea();	}
};

class	MultiInterpolationPole : public NPListSaveLoad<MultiInterpolationPole>
{
public:
	double	X,Y;
	double	dX,dY;
	double	MatchingRate;
	int32	Xn,Yn;

	MultiInterpolationPole(void){}
	MultiInterpolationPole(double x ,double y ,double dx ,double dy ,int xn ,int yn);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
class	MultiInterpolation;

class	MultiInterpolationPole3
{
	friend	class	MultiInterpolation;
public:
	MultiInterpolationPole	*Dim[3];
	double	m[6];

	MultiInterpolationPole3(void);

	bool	IsEffective(void);
	void	Calc(void);
	double	GetDistance(double x ,double y);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

private:
	int32	LoadedXn0,LoadedYn0;
	int32	LoadedXn1,LoadedYn1;
	int32	LoadedXn2,LoadedYn2;
};

class	MultiInterpolation : public NPListPackSaveLoad<MultiInterpolationPole>
{
	friend	class	MultiInterpolationPole3;

	MultiInterpolationPole3	*Dim;
	int32					DimNumb;
	GerberFastInPage		*Parent;
public:
	MultiInterpolation(GerberFastInPage *parent){	Parent=parent;	Dim=NULL;	DimNumb=0;	}
	virtual	~MultiInterpolation(void);

	void	Add(double x ,double y ,double dx ,double dy ,int xn ,int yn);
	void	Build(void);
	bool	Calc(double x ,double y ,double &ResultX ,double &ResultY);
	double	*Calc(double x ,double y);

	virtual	MultiInterpolationPole	*Create(void)	{	return new MultiInterpolationPole();	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AlgoGenerationalContainer;

class	AlgoGenerationalLine : public NPList<AlgoGenerationalLine>
{
public:
	int		AlgoGenID;
	int		BaseLayerID;
	AlgoGenerationalContainer	*UpperLayers;

	enum	GenType
	{
		_Gen_FromLayer					=1
		,_GenFromShiftable				=2
		,_GenFromEnlarge				=3
		,_GenFromShrinked				=4
		,_GenFromUnstable				=5
		,_GenFromStable					=6
		,_GenFromComposite				=7
		,_GenFromCompositeShiftable		=8
		,_GenFromCompositeEnlarge		=9
		,_GenFromCompositeShrinked		=10
		,_GenFromCompositeUnstable		=11
		,_GenFromCompositeStable		=12
	}AutoGenType;

	AlgorithmLibraryListContainer	Libraries;	

	AlgoGenerationalLine(int id);
	~AlgoGenerationalLine(void);

	static	bool	IsLayer(AlgoGenerationalLine::GenType e);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	AlgoGenerationalLine	&operator=(AlgoGenerationalLine &src);

	bool	SaveEssence(QIODevice *f);
	bool	LoadEssence(QIODevice *f);
};

class	AlgoGenEssenseContainer;

class	AlgoGenerationalContainer : public NPListPack<AlgoGenerationalLine>
{
public:
	AlgoGenerationalContainer(void);

	int		GetMaxID(void);
	AlgoGenerationalContainer	&operator=(AlgoGenerationalContainer &src);
	bool	DoAllChildHaveLibrary(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	CreateEssense	(GerberFastInPage *PPage, AlgoGenEssenseContainer &E);
	void	AllocateEssense	(GerberFastInPage *PPage, AlgoGenEssenseContainer &E);

	void	Merge(AlgoGenerationalContainer &t);
	void	ClearLibrary(void);
};

class	AlgoGenEssense : public NPListSaveLoad<AlgoGenEssense>
{
public:
	int32	BaseLibID;
	AlgoGenerationalLine::GenType	BaseType;

	int32	CoverLibID;
	AlgoGenerationalLine::GenType	CoverType;

	AlgorithmLibraryListContainer	Libraries;

	AlgoGenEssense(void){}

	AlgoGenEssense	&operator=(AlgoGenEssense &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AlgoGenEssenseContainer : public NPListPackSaveLoad<AlgoGenEssense>
{
public:
	AlgoGenEssenseContainer(void){}
	AlgoGenEssense	*Create(void){	return new AlgoGenEssense();	}
};

class	GerberFastItemPointer : public NPList<GerberFastItemPointer>
{
	GerberFastItemBase	*Point;
public:
	GerberFastItemPointer(GerberFastItemBase *p){	Point=p;	}

	GerberFastItemBase	*GetPoint(void)	{	return Point;	}
};

struct	WPriorityMapClass
{
	AlgorithmItemPI *Point;
	int			DrawingPriority;
};

struct	ItemBaseAndPointer
{
	GerberFastItemBase		*Item;
	GerberFastItemPointer	*Pointer;
};

class	GerberFastItemPointerContainer : public NPList<GerberFastItemPointerContainer>
{
	struct	ItemBaseAndPointer	*FastPointer;
public:

	NPListPack<GerberFastItemPointer>	PointerList;
	int		FileLayerID;
	int		CompositeID;

	GerberFastItemPointerContainer(bool FileLayerMode ,int ID);
	~GerberFastItemPointerContainer(void);

	void	AddItem(GerberFastItemBase *p);
	bool	InsertBehind(GerberFastItemBase *Key , GerberFastItemBase *addItem);
	void	RemoveItem(GerberFastItemBase *p);
	void	RemoveItemFast(GerberFastItemBase *p);
	int		GetFileLayerID(void)	{	return FileLayerID;	}
	int		GetCompositeID(void)	{	return CompositeID;	}
	GerberFileLayer	*GetFileLayer(GerberFastInPage &PageData); 
	GerberFastItemBase	*GetFirst(void);
	void	BuildFastIndex(void);

	int		Draw(int page ,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr ,QImage &hpnt,struct WPriorityMapClass	*PriorityMap ,int KNumb);
	void	DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,bool ThreadMode=true);
	QColor	GetColor(AlgorithmDrawAttr *Attr);

	void	MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen);
};

class	GerberFastItemPointerContainerContainer:public NPListPack<GerberFastItemPointerContainer>
{
public:
	GerberFastItemPointerContainerContainer(void){}

	GerberFastItemPointerContainer	*Search			(int FileLayerID);
	GerberFastItemPointerContainer	*SearchComposite(int CompositeID);
};


//=================================================================================
//	This is for Naming, result binding
class	GerberFastClusterItemList : public NPList<GerberFastClusterItemList>
{
public:
	int			ClusterID;
	FlexArea	Area;
	bool		NG;
	AlgorithmItemPointerListContainer	ItemPointer;

	GerberFastClusterItemList(void){	ClusterID=-1;	}
};

const int	XDivClusterNumb=20;
const int	YDivClusterNumb=20;

class	GerberFastClusterItemPointer : public NPList<GerberFastClusterItemPointer>
{
public:
	GerberFastClusterItemList	*Pointer;

	GerberFastClusterItemPointer(GerberFastClusterItemList *p):Pointer(p){}
};

class	GerberFastClusterItemContainer : public NPListPack<GerberFastClusterItemList>
{
	GerberFastInPage	*Parent;
public:
	int	XDivClusterLen;
	int	YDivClusterLen;
	NPListPack<GerberFastClusterItemPointer>	PointerInArea[XDivClusterNumb][YDivClusterNumb];

	int32	PinholeCount;

	GerberFastClusterItemContainer(GerberFastInPage *parent):Parent(parent){	XDivClusterLen=YDivClusterLen=0;	}

	void	BuildPointerInArea(void);
};

//=================================================================================

class	PatternList : public NPListSaveLoad<PatternList>
{
public:
	int			PatternID;	//ItemID or CompositeID
	int			ApertureType;
	double		GerberArea;
	double		GerberPosX;
	double		GerberPosY;
	bool		ClippedGerber;
	double		GerberXLen;
	double		GerberYLen;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	PatternList::Save(QIODevice *f)
{
	if(::Save(f,PatternID)==false)
		return false;
	if(::Save(f,ApertureType)==false)
		return false;
	if(::Save(f,GerberArea)==false)
		return false;
	if(::Save(f,GerberPosX)==false)
		return false;
	if(::Save(f,GerberPosY)==false)
		return false;
	if(::Save(f,ClippedGerber)==false)
		return false;
	if(::Save(f,GerberXLen)==false)
		return false;
	if(::Save(f,GerberYLen)==false)
		return false;

	return true;
}
inline	bool	PatternList::Load(QIODevice *f)
{
	if(::Load(f,PatternID)==false)
		return false;
	if(::Load(f,ApertureType)==false)
		return false;
	if(::Load(f,GerberArea)==false)
		return false;
	if(::Load(f,GerberPosX)==false)
		return false;
	if(::Load(f,GerberPosY)==false)
		return false;
	if(::Load(f,ClippedGerber)==false)
		return false;
	if(::Load(f,GerberXLen)==false)
		return false;
	if(::Load(f,GerberYLen)==false)
		return false;

	return true;
}


class	PatternListContainer : public NPListPackSaveLoad<PatternList>
{
public:
	PatternListContainer(void){}

	virtual	PatternList	*Create(void)	{	return new PatternList();	}
};


//=================================================================================

#define		AccessDimNumbX	20
#define		AccessDimNumbY	80

class	PageInfoForParts : public NPList<PageInfoForParts>
{
	GerberFastInPage	*Parent;
public:
	int		PartsMaster;
	GerberFileLayerContainer		FileLayerList;

	PageInfoForParts(GerberFastInPage *parent):Parent(parent),FileLayerList(parent){}
};

class   GerberFastInPage : public AlgorithmInPagePI
{
	TriangleAreaContainer		TriangleAreaData;
	MultiInterpolation			AutoInterpolation;
public:
	GerberFileLayerContainer		FileLayerList;
	GerberCompositeLayerContainer	CompositeLayer;
	MatchAutoLikeManualContainer	AutoLikeManualData;

	NPListPack<PageInfoForParts>	PageInfoForPartsData;

	GerberFastItemPointerContainerContainer		GerberFastItemPointerContainerContainerList;
	MatchAlignmentAreaContainer					MatchAlignmentArea1;
	MatchAlignmentAreaContainer					MatchAlignmentArea2;
	MatchAlignmentAreaContainer					MatchAlignmentArea3;

	GerberFastItemBasePointerContainer			ItemListInside;

	//View for slave
	bool	MoveMode;
	bool	RotateMode;
	bool	ExtendMode;
	bool	SlopeXMode;
	bool	SlopeYMode;
	bool	AlignmentMode;
	bool	AutoMatchingMode;
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
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];

	BYTE	**ImagingBmp;
	int		ImagingBmpXByte;
	int		ImagingBmpYLen;

	AutomatchingBox		ABox[10][10];
	int		ABoxXNum;
	int		ABoxYNum;
	DoublePoint	AMImagePoint[100];
	DoublePoint	AMCadPoint[100];

	AlgorithmItemPointerListContainer	AccessDim[AccessDimNumbX][AccessDimNumbY];
	int									AccessDimXLen;
	int									AccessDimYLen;

	SparsContainer		SparsContainerData;
	SparsOutline		CenterLines;

	GerberFastClusterItemContainer		ClusterItemContainer;

	GerberFastInPage(AlgorithmBase *parent);
	~GerberFastInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override;
	virtual	bool	AppendItem(AlgorithmItemRoot *item)				override;
	virtual	bool	AppendItem(int Layer ,AlgorithmItemRoot *item)	override;
	virtual	bool	AppendItemFromLoad(AlgorithmItemRoot *item)		override;
	virtual	void	RemoveItem(AlgorithmItemRoot *item)				override;
	virtual	bool	AppendItem(AlgorithmItemRoot *item ,int64 itemID)override;
	virtual	void	RemoveAllDatas(void)							override;
	virtual	void	InsertItem(AlgorithmItemRoot *item,AlgorithmItemRoot *Key)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	//virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect);
	
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	bool	BuildPointer(bool &Error);
	void	CreateImagingBmpBuff(void);

	int		GetOwnOrder(int FileLayerID);
	void	BuildShapeToArea(void);
	GerberFileLayer			*FindFileLayer(int FileLayerID);
	GerberFastItemComposite	*FindCompositeItem(int CompositeID);
	GerberCompositeLayer	*GetCompositeLayer(int N)	{	return CompositeLayer[N];	}
	GerberCompositeLayer	*SearchCompositeLayer(int CompositeID);
	bool	GetAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY);

	void	PickupItem(int globalX,int globalY ,AlgorithmItemPointerListContainer &Found);
	bool	CheckValidity(void);
	void	RestructTooBig(double TooBigSizeForCut);
	bool	CheckAndSplitBySize(GerberFastItemBase *item,double TooBigSizeForCut ,AlgorithmItemPointerListContainer &Container);
	void	MakeXY(void);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	void	MakeDraw(int FileLayerID ,AlgorithmItemPointerListContainer &AddedItems);
	void	MakeItemListInside(void);

	/*
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false);
	virtual	void	ExecuteZoom(double RateX ,double RateY);
	virtual	void	ExecuteRotate(double Radian);
	virtual	void	ExecuteShearX(double Radian);
	virtual	void	ExecuteShearY(double Radian);
	virtual	void	ExecuteMirrorX(void);
	virtual	void	ExecuteMirrorY(void);
	virtual void	Transform(double AffinParam[3][3]);
	*/

	void	UndoMove			(QIODevice *f);
	void	UndoRotate			(QIODevice *f);
	void	UndoZoom			(QIODevice *f);
	void	UndoShear			(QIODevice *f);
	void	UndoMirror			(QIODevice *f);
	void	UndoCenterize		(QIODevice *f);
	void	UndoCenterizeOnly	(QIODevice *f);
	void	UndoMovePoints		(QIODevice *f);
	void	UndoAutoMatch		(QIODevice *f);
	void	UndoMatchingRoughly	(QIODevice *f);
	void	UndoGerberDraw		(QIODevice *f);
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

	void	MakeAccessDim(void);
	void	AddAccessDim(GerberFastItemBase *p);
	void	ClearAccessDim(void);
	void	SetCurrentSize(void);
public:
	void	MakeImage(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
					, QColor LayerColor[MaxGerberLayer] ,QColor CompColor[MaxGerberLayer]);
	void	MakeBitImage(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
						,QColor LayerColor[MaxGerberLayer] ,QColor CompColor[MaxGerberLayer]);
	void	MakeImage			(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode);
	void	MakeImageEnlarge	(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode);
	void	MakeImageShiftable	(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode);
	void	MakeImageShrinked	(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode);
	void	MakeImageUnstable	(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode);
	void	MakeImageStable		(BYTE **CurrentBmp,int LayerCompositeID ,bool LayerMode);

	void	MakeLayerImage			(int LayerID	,GerberGenerationFileContainer &GFileContainer,BYTE **CurrentBmp,int XByte,int YLen);
	void	MakeCompositeImage		(int CompositeID,GerberGenerationFileContainer &GFileContainer,BYTE **CurrentBmp,int XByte,int YLen);
	void	MakeCompositeImageShrink(int CompositeID,GerberGenerationFileContainer &GFileContainer,BYTE **CurrentBmp,int XByte,int YLen);

	void	MakeAutoMatchingBox(bool UsageLayer ,int UsageLayerID
								,bool RemoveShiftable
								,BoolList &ButtonsToRemoveShiftableLayer ,IntList &OperateCompositeIDList
								,int32 MinDotsForAutoMatching
								,int32 ShrinkDotForAutoMatchingArea);
	void	ClearAutoMatchInfo(void);
	void	ExecuteMatching(void);
	void	ExecuteAllocateMatching(void);
	void	ExecuteAllocateForOthers(void);

	void	MakeAlgo(AlgoGenerationalContainer &MakeAlgoAllList ,int ExecutedLine);
	void	MakeAlgoImage(BYTE **Image ,AlgoGenerationalLine *a);

	bool	MatchRough(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
						,bool &MirrorMode
						,double &MovX ,double &MovY
						,double &ZoomX,double &ZoomY
						,double &Rotation);

	bool	MakePaintArea(double GlobalX,double GlobalY ,AlgorithmItemPointerListContainer &ItemList
									,AlgorithmItemPointerListContainer &CreatedItems);

	void	MakeShrinkImage(BYTE **TmpImage ,int ImageXLen ,int ImageYLen
							,double ShrinkRate
							,ImageBuffer &IBuff);
	void	MakePattern(BYTE **TmpPattern ,int PatternXLen ,int PatternYLen
							,double ShrinkRate
							,int StartXPointX ,int StartXPointY
							,BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList);

	void	MakeMatchShrinked(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
									,double ShrinkedRate
									,QByteArray	&ImageData
									,QByteArray	&GerberData);

	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)	override;	//From AlgorithmInPagePI
	void	MakeTransArea(bool UsageLayer ,int UsageLayerID);
	void	MakeRelatedInOtherLayerItems(bool UsageLayer ,int UsageLayerID);
	void	InitialTransArea			(bool UsageLayer ,int UsageLayerID);
	void	PushCenter(void);
	void	MakeABox(void);

	void	MakeOutline(BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite);
	void	MakeOutline(int LayerLibID);
	void	MakeEchingFactor(BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite
							,double EFactor);
	void	SetFileLayerVisible(IntListFast &ShownFileID,IntListFast &ShownCompositeID);

	virtual	void	InitializeFromParts(void)	override;
	PageInfoForParts	*GetPartsInfo(int PartsMaster);

	void	GenerateBlocks(int LayerOrComposite
						,  int LayerCompositeID
						,  int GeneratedLibType
						,  int GeneratedLibID
						,  int OmitLayerOrComposite
						,  int OmitLayerCompositeID
						,  GerberGenerationFileContainer &GFileContainer
						,  QByteArray &ThresholdData);
	void	MakeClusterContainer(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList);
	void	SetResultInCluster(void);

	void	ExecuteClusterMatchDetail(bool UsageLayer ,int UsageLayerID
									, bool BrighterInPattern);
	
private:
	void	SetABox(int ix,int iy,AutomatchingBox &AB,NPListPack<GerberFastItemPointer> &PointerList);
	void	MakeEnabledAutomatchFlag(void);
};

class	GerberFastBase	: public AlgorithmBase
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
	//QString	CompositeDefFileName;
	QString	LayerTypeFileName;
	double	StartupZoomRateX;
	double	StartupZoomRateY;
	int32	SearchAreaInMatching;
	bool	CenterizeByArea;
	int32	DefaultMinDotsForAutoMatching;
	int32	AutoMatchingOutsideDot;
	int32	AutoMatchingInsideDot;
	int32	AutoMatchingMerginDot;
	int32	AutoMatchingEdgeOmitDot;
	double	ThresholdSelfMatch;
	int		AutoMatchMethod;
	bool	CutLargeGetber;
	double	TooBigSizeForCut;
	bool	ExecuteFinalEachMatch;

	bool	NCUnitInchi;
	int		NCIntegerNum;
	int		NCSmallNum;		//SmallNumber
	int		SwingDotInLastMatch;
	bool	LoadedCenterization;
	double	LoadedOffsetX;
	double	LoadedOffsetY;
	double	AutoMatchMinWidthForPartial;
	QColor	AutoMatchManualColorParallel;
	QColor	AutoMatchManualColorRotation;
	QColor	AutoMatchManualColorZooming;
	int		MaxBindedAreaLength;
	int		OverlapPixelToCutBigArea;
	QString	ODBArchiverExeFile;
	QString	ODBArchiverParameter;
	double	HairlineIsolation;
	double	HairlineLength;
	double	HairlineCoeff;
	int		AutoMatchMergin;
	bool	UseBrighterInPattern;
	double	IsolationToSelect;
	bool	UseMasterImage;
	int		AutoMatchAreaSize;
	bool	ModeDeliverAllPhasesInLoadGerber;
	bool	AutoMatchExecuteLargeArea;
	int		EachSearchDot;

	//GerberLayerAttrContainer		LayerAttr;
	GerberCompositeDefPack			CompositeDef;
	//GerberFileLayerContainer		FileLayerList;
	AlgoGenerationalContainer		MakeAlgoData;

	GerberFastBase(LayersBase *Base);

	void	InitialAfterParamLoaded(void)	override;
	bool	LoadCompositeDef(void);
	bool	SaveCompositeDef(void);

	virtual	QString	GetDataText(void)	override	{	return QString("GerberFast");				}
	QString	GetDefaultFileName(void)	override	{	return QString("ConfigGerberFast.dat");		}

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override	{	return new GerberFastInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual void	SetupLibFolder(int LibFolderID ,int originalLibFolder)  override;

	QColor	GetLayerColor(int Number);
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste) override;

	bool	SaveOnly(QIODevice *f);
	bool	LoadOnly(QIODevice *f);

	bool	LoadODBPPDirectories(const QString &TopPath, bool OnlyFile ,ODBStepContainer &StepContainer
																		,QStringList &LayerPathList
																		,ODBLayerContainer	&MatrixLayers);
	bool	LoadODBFeatureDirectories(bool OnlyFile
									, ODBStepContainer &StepContainer 
									, QStringList &LayerPathList
									, QStringList &FileList
									,ODBLayerContainer	&MatrixLayers);
	bool	LoadMatrixFile(const QString &AbsFileName,ODBStepContainer &StepContainer , ODBLayerContainer &MatrixLayers);

	void	MatchGlobal(double ShrinkedRate ,QByteArray ImageData[],QByteArray GerberData[]
						,int &Dx,int &Dy ,double &ZoomX ,double &ZoomY);

	QString	UnzipInTemp(const QString &FeatureFileNameZ);

private:
	//QString	MakeCompositeDefFileName(void);

};

//======================================================================

class	AlignmentGeneralPipeInfo : public GeneralPipeInfo
{
	GerberFastInPage	*Parent;
public:
	AlignmentGeneralPipeInfo(GerberFastInPage *parent);

	virtual	bool	RequireAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY);
};

//======================================================================

inline	MatchAutoLikeManualContainer::MatchAutoLikeManualContainer(GerberFastInPage *parent)
	:Parent(parent)
{
	AdpptedLayer	=0;
	TransDot		=6;
	RoughMatchAreaWidthRate	=0.1;
	RoughMatchAreaHeightRate=0.03;
	SearchAreaRoughMatch	=1200;
	SearchAreaParallelMatch	=50;
	SearchAreaRotateMatch	=1500;
	SearchAreaZoomMatch		=1500;
	SearchAreaMatchDetail	=40;
	DataIsolation			=16;
	NearByPattern			=60;
	MatchingRateToNeighbor	=0.9;
}

inline	FlexAreaImageListCoeffAndResult::FlexAreaImageListCoeffAndResult(void)
{	
	Dx=Dy=0;
	HData=NULL;
	HStart=HLen=0;
	VData=NULL;
	VStart=VLen=0;
	HSAvr=0;
	HSS=0;
	VSAvr=0;
	VSS=0;
}
inline	FlexAreaImageListCoeffAndResult::~FlexAreaImageListCoeffAndResult(void)
{
	if(HData!=NULL){
		delete	[]HData;
		HData=NULL;
	}
	if(VData!=NULL){
		delete	[]VData;
		VData=NULL;
	}
	HLen=0;
	VLen=0;
}

inline	void    FlexAreaImageListCoeffAndResult::MoveToNoClip(int dx, int dy)
{
	FlexAreaImageListCoeff::MoveToNoClip(dx,dy);
	Cx+=dx;
	Cy+=dy;
	HStart+=dx;
	VStart+=dy;
}

inline	bool	FlexAreaImageListCoeffAndResult::Save(QIODevice *f)
{
	if(FlexAreaImageListCoeff::Save(f)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,HStart)==false)
		return false;
	if(::Save(f,HLen)==false)
		return false;
	if(::Save(f,VStart)==false)
		return false;
	if(::Save(f,VLen)==false)
		return false;
	if(::Save(f,HSAvr)==false)
		return false;
	if(::Save(f,HSS)==false)
		return false;
	if(::Save(f,VSAvr)==false)
		return false;
	if(::Save(f,VSS)==false)
		return false;
	if(f->write((const char *)HData,HLen)!=HLen)
		return false;
	if(f->write((const char *)VData,VLen)!=VLen)
		return false;
	return true;
}
inline	bool	FlexAreaImageListCoeffAndResult::Load(QIODevice *f)
{
	if(FlexAreaImageListCoeff::Load(f)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,HStart)==false)
		return false;
	if(::Load(f,HLen)==false)
		return false;
	if(::Load(f,VStart)==false)
		return false;
	if(::Load(f,VLen)==false)
		return false;
	if(::Load(f,HSAvr)==false)
		return false;
	if(::Load(f,HSS)==false)
		return false;
	if(::Load(f,VSAvr)==false)
		return false;
	if(::Load(f,VSS)==false)
		return false;
	if(HData!=NULL){
		delete	[]HData;
	}
	HData=new BYTE[HLen];
	
	if(f->read((char *)HData,HLen)!=HLen)
		return false;
	if(VData!=NULL){
		delete	[]VData;
	}
	VData=new BYTE[VLen];
	if(f->read((char *)VData,VLen)!=VLen)
		return false;
	return true;
}

//-------------------------------------------------
class	ItemsDataOutsideList : public NPListSaveLoad<ItemsDataOutsideList>
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	QByteArray	ItemsData;

	ItemsDataOutsideList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ItemDataOutsideContaner : public NPListPackSaveLoad<ItemsDataOutsideList>
{
public:
	virtual	ItemsDataOutsideList	*Create(void){	return new ItemsDataOutsideList();	}
};

inline	bool	ItemsDataOutsideList::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,ItemsData)==false)
		return false;
	return true;
}
inline	bool	ItemsDataOutsideList::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,ItemsData)==false)
		return false;
	return true;
}

#endif