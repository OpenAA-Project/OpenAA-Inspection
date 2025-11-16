#if	!defined(XRegulation_h)
#define	XRegulation_h

#include "NListComp.h"
#include "XTypeDef.h"
#include <QIODevice>

class   XYRegPoint : public NPListSaveLoad<XYRegPoint>
{
  public:
	int32	ID;
    double	x,y;
	int32	NumX,NumY;

	XYRegPoint	*LinkTop;
	XYRegPoint	*LinkLeft;
	XYRegPoint	*LinkRight;
	XYRegPoint	*LinkBottom;

    XYRegPoint(void)
		:ID(-1),x(0),y(0),NumX(0),NumY(0),LinkTop(NULL),LinkLeft(NULL),LinkRight(NULL),LinkBottom(NULL){}
	XYRegPoint(double _x,double _y)
		:ID(-1),x(_x),y(_y),NumX(0),NumY(0),LinkTop(NULL),LinkLeft(NULL),LinkRight(NULL),LinkBottom(NULL){}
    XYRegPoint(double _x,double _y ,int nx ,int ny)
		:ID(-1),x(_x),y(_y),NumX(nx),NumY(ny),LinkTop(NULL),LinkLeft(NULL),LinkRight(NULL),LinkBottom(NULL){}
    XYRegPoint(const XYRegPoint &src)
		:ID(-1),LinkTop(NULL),LinkLeft(NULL),LinkRight(NULL),LinkBottom(NULL)
		{  x=src.x;    y=src.y;  NumX=src.NumX;	NumY=src.NumY;	  }

    XYRegPoint   &operator=(const XYRegPoint &src);

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	SaveLink(QIODevice *f);
	virtual	bool	Load(QIODevice *f)		override;
};

inline	XYRegPoint   &XYRegPoint::operator=(const XYRegPoint &src)
{ 
	ID=src.ID;
	x=src.x;
	y=src.y;
	NumX=src.NumX;
	NumY=src.NumY;
	LinkTop		=src.LinkTop	;
	LinkLeft	=src.LinkLeft	;
	LinkRight	=src.LinkRight	;
	LinkBottom	=src.LinkBottom	;
	return(*this);
}


class   XYRegPointLoader : public XYRegPoint
{
public:
	int32	IDLeft	;
	int32	IDTop	;
	int32	IDRight	;
	int32	IDBottom;

	XYRegPointLoader(void):XYRegPoint(){}

	virtual	bool	LoadLink(QIODevice *f);
};

class   XYRegPointContainer : public NPListPackSaveLoad<XYRegPoint>
{
public:
	double	RealXmm;
	double	RealYmm;
	double	OffsetRealX;
	double	OffsetRealY;
	double	MinLenX;
	double	MinLenY;
	int16	UnitIndex;	//-1:Ineffective	0:cm	1:mm	2:É m	3:m
	int16	UnitFigure;

	XYRegPointContainer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	IsEffective(void)	const				{	return (UnitIndex<0)?false:true;	}
	void	RemovePoint(XYRegPoint *p);

	XYRegPointContainer	&operator=(const XYRegPointContainer &src);

	virtual	XYRegPoint	*Create(void)	override	{	return new XYRegPoint();	}
	XYRegPoint	*GetClosedPoints(int imagex ,int imagey);

	bool	MakeNumerize(double	RealXmm, double RealYmm ,int ImageWidth ,int ImageHeight
						,double RotRate=0.3);

	bool	TransformImageToReal(int imagex ,int imagey ,double &realX ,double &realY)	const;
	bool	TransformRealToImage(double realX ,double realY ,int &imagex ,int &imagey)	const;
	bool	GetXY(double &MinImageX,double &MinImageY,double &MaxImageX,double &MaxImageY)	const;
	void	MakeLinkByLoader(void);
	QString	GetUnitName(void)	const;
};

#endif