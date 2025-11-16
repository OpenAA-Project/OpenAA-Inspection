/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XYCross.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	 !defined(XYCrossH)

#define XYCrossH
#include <QIODevice>
#include <QRect>

#include "XTypeDef.h"
#include "NList.h"


class   FlexArea;
class	QPainter;
class	ImagePointerContainer;


typedef struct  _XYData
{
    int32 x,y;

	_XYData(void){}
	_XYData(const _XYData &src):x(src.x),	y(src.y)	{}

	bool	operator==(const struct _XYData &src)	const{	return (x==src.x && y==src.y)?true:false;	}
	bool	operator!=(const struct _XYData &src)	const{	return !operator==(src);	}
}XYData;

struct  XYM_Data{
    int     x1,x2,y;
    bool    YPole;
};

class	DoublePoint
{
public:
	double	x,y;

	DoublePoint(void)	{	x=0.0;	y=0.0;	}
	DoublePoint(const DoublePoint &src)	{	x=src.x;	y=src.y;	}
	DoublePoint(double _x,double _y):x(_x),y(_y){}

	DoublePoint	&operator=(const DoublePoint &src)	{	x=src.x;	y=src.y;	return *this;	}

	bool	operator==(const DoublePoint &src)	const{	return (x==src.x && y==src.y)?true:false;	}
	bool	operator!=(const DoublePoint &src)	const{	return !operator==(src);	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class   XYClass : public NPList<XYClass>
{
  public:
    int x,y;

    XYClass(void):x(0),y(0){}
    XYClass(int _x,int _y):x(_x),y(_y){}
    XYClass(const XYClass &src)	{  x=src.x;    y=src.y;    }

    XYClass   &operator=(const XYClass &src){ x=src.x; y=src.y;   return(*this);  }
	bool	operator==(const XYClass &src)	const;
	bool	operator!=(const XYClass &src)	const;

    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	XYClass::operator==(const XYClass &src)	const
{
	if(x==src.x && y==src.y){
		return true;
	}
	return false;
}
inline	bool	XYClass::operator!=(const XYClass &src)	const
{
	if(x!=src.x || y!=src.y){
		return true;
	}
	return false;
}

inline	double	hypot(const XYClass &a1 ,const XYClass &a2)
{
	return hypot(a1.x-a2.x,a1.y-a2.y);
}

class   RectClass : public NPList<RectClass>
{
  public:
    int x1,y1,x2,y2;
    int attr;

    RectClass(void){}
	RectClass(const RectClass &src);
    RectClass(int _x1,int _y1 ,int _x2 ,int _y2 ,int _attr=0)
        :x1(_x1),y1(_y1),x2(_x2),y2(_y2),attr(_attr){}

    RectClass   &operator=(const RectClass &src);
	bool	operator==(const RectClass &src)	const{	return (x1==src.x1 && y1==src.y1 && x2==src.x2 && y2==src.y2 && attr==src.attr)?true:false;	}
	bool	operator!=(const RectClass &src)	const{	return !operator==(src);	}

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
	bool	IsInclude(int x ,int y)		const;
	void	GetCenter(int &x,int &y)	const{	x=(x1+x2)/2;	y=(y1+y2)/2;	}

	void	DrawRect(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
};

class RectClassContainer : public NPListPack<RectClass>
{
public:
	RectClassContainer(void){}
	RectClassContainer(const RectClassContainer &src);
	virtual	~RectClassContainer(void){}

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

	RectClassContainer	&operator=(const RectClassContainer &src);
};


class   XYDoubleClass : public NPList<XYDoubleClass>
{
  public:
    double x,y;

    XYDoubleClass(void):x(0.0),y(0.0){}
    XYDoubleClass(double _x,double _y):x(_x),y(_y){}
    XYDoubleClass(const XYDoubleClass &src)	{  x=src.x;    y=src.y;    }

	void	Set(double _x, double _y)	{	x=_x;	y=_y;	}
    XYDoubleClass   &operator=(const XYDoubleClass &src){ x=src.x; y=src.y;   return(*this);  }
	bool	operator==(const XYDoubleClass &src)	const;
	bool	operator!=(const XYDoubleClass &src)	const;

    void    ChangeXY(XYDoubleClass *outlineOffset ,int MaxPage,int maxlines);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	XYDoubleClass::operator==(const XYDoubleClass &src)	const
{
	if(x==src.x && y==src.y){
		return true;
	}
	return false;
}
inline	bool	XYDoubleClass::operator!=(const XYDoubleClass &src)	const
{
	if(x!=src.x || y!=src.y){
		return true;
	}
	return false;
}

class	XYClassContainer : public NPListPack<XYClass>
{
 public:
	XYClassContainer(void){}
	XYClassContainer(const XYClassContainer &src);

	bool    Save(QIODevice  *file);
	bool    Load(QIODevice  *file);
	void    MoveTo(int dx ,int dy);
	void	Add(int x ,int y);
	bool    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const;
	void    GetCenter(int &cx ,int &cy)	const;
	int		GetDotCount(void)	const{	return NPListPack<XYClass>::GetNumber();	}
	XYClass	*GetFirstDot(void)	const{	return NPListPack<XYClass>::GetFirst();		}

	XYClassContainer &operator=(const XYClassContainer &src);
	bool	operator==(const XYClassContainer &src)	const;

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
	bool	IsIsclude(int x ,int y)				const;
	bool	IsIsclude(int x ,int y ,int radius)	const;
	double	GetDistance(int x, int y)	const;
};

class	XYDoubleClassContainer : public NPListPack<XYDoubleClass>
{
 public:
	XYDoubleClassContainer(void){}
	XYDoubleClassContainer(const XYDoubleClassContainer &src);

	bool    Save(QIODevice  *file);
	bool    Load(QIODevice  *file);
	void    MoveTo(int dx ,int dy);
	bool    GetXY(double &minx ,double &miny ,double &maxx ,double &maxy)	const;
	void    GetCenter(double &cx ,double &cy)	const;
	int		GetDotCount(void)			const	{	return NPListPack<XYDoubleClass>::GetNumber();	}
	XYDoubleClass	*GetFirstDot(void)	const	{	return NPListPack<XYDoubleClass>::GetFirst();		}

	XYDoubleClassContainer &operator=(const XYDoubleClassContainer &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
	bool	IsIsclude(int x ,int y)		const;
	double	GetDistance(int x, int y)	const;
};

struct XYAreaWithWeight
{
	int	X,Y;
	int	Weight;
};


class   XYClassArea : public NPList<XYClassArea> ,public NPListPack<XYClass>
{
  public:
    bool    Positive;

    XYClassArea(void){	Positive=true;	}
	XYClassArea(const XYClassArea &src);

    bool    Write(QIODevice  *file);
    bool    Read(QIODevice  *file);
    void    SetRectangle(QRect &rect);
    bool    IsInclude(int x ,int y)	const;
    void    TransTo(FlexArea &area);
    void    Rotate(double angle ,int cx ,int cy);
    bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2)		const;
    bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)	const;
    void    MoveTo(int dx ,int dy);
    bool    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const;
    void    GetCenter(int &cx ,int &cy)							const;
    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);
    bool    IsValid(void)	const;
	void    Regulate(void);
	void	Simplize(void);

	void	GenerateEdge(ImagePointerContainer &ImageList ,int FirstX ,int FirstY,int SearchDot,int MaxLength);

	void	SearchOutline(const ImagePointerContainer &ImageList,const XYClassArea &sOutline,int SearchDot);
	double	CalcEdge(const ImagePointerContainer &ImageList,int dx,int dy)	const;
	void	ClosedEdge(const ImagePointerContainer &ImageList ,const XYClassArea *s ,int dx,int dy,int SearchDot);

	int		GetDotCount(void)	const	{	return NPListPack<XYClass>::GetNumber();	}
	XYClass	*GetFirstDot(void)	const	{	return NPListPack<XYClass>::GetFirst();		}

    XYClassArea &operator=(const XYClassArea &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

private:
    void    TransToInner(FlexArea &area);
    static  int transtofunc(const void *a ,const void *b);

	bool	CalcWeight(ImagePointerContainer &ImageList ,struct XYAreaWithWeight &Ret,int Lastx ,int Lasty);
	void	FindMaxWeight(ImagePointerContainer &ImageList ,int cx,int cy ,int &tx ,int &ty,int SearchDot);
	bool	FindMaxWeightNext(ImagePointerContainer &ImageList ,int cx,int cy ,int &tx ,int &ty,int SearchDot);
	bool	CheckClosed(int x ,int y, int Length ,int Isolation);
};

class   XYClassCluster : public NPListPack<XYClassArea>
{
  public:
    XYClassCluster(void){}

    bool    Write(QIODevice  *file);
    bool    Read(QIODevice  *file);
    void    SetRectangle(QRect &rect);
    bool    IsInclude(int x ,int y)							const;
    bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2)	const;
    void    TransTo(FlexArea &area);
    void    MoveTo(int dx ,int dy);
    bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)	const;
    XYClassCluster &operator=(const XYClassCluster &src);
    bool    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const;

    void    Rotate(double angle ,int cx ,int cy);
    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);

    bool    Validate(void); //ñ≥å¯Ç»óÃàÊÇçÌèúÇ∑ÇÈ
	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

	void	SearchOutline(const ImagePointerContainer &ImageList,const XYClassCluster &sOutline,int SearchDot);
};

//========================================================================================
class   XYLines : public NPList<XYLines> ,public NPListPack<XYClass>
{
  public:
	int	MinX,MinY,MaxX,MaxY;

    XYLines(void);
	XYLines(const XYLines &src);

    bool    Write(QIODevice  *file);
    bool    Read(QIODevice  *file);
    bool    IsInclude(int x ,int y,double AreaLength=5)	const;
    void    Rotate(double angle ,int cx ,int cy);
    bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2)		const;
    bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)	const;
    void    MoveTo(int dx ,int dy);
    bool    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const;
    void    GetCenter(int &cx ,int &cy)							const;
    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);
    bool    IsValid(void)	const;
	void    Regulate(void);

	int		GetDotCount(void)	const	{	return NPListPack<XYClass>::GetNumber();	}
	XYClass	*GetFirstDot(void)	const	{	return NPListPack<XYClass>::GetFirst();		}

    XYLines &operator=(const XYLines &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

	void	CreateOneLine(BYTE **BmpMap , int XLen ,int YLen
										,int x ,int y);
	void	GetMinY(int &x ,int &y)		const;
	void	GetMaxY(int &x ,int &y)		const;
	double	GetDistance(int x,int y)	const;
	bool	CalcInterpolationLine(double &a ,double &b ,double &c);
};

class	XYLineContainer : public NPListPack<XYLines>
{
public:
	XYLineContainer(void){}

	void	CreateLines(BYTE **BmpMap , int XByte ,int YLen);	//Clear BmpMap inside
    bool    Save(QIODevice  *file);
    bool    Load(QIODevice  *file);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
	void    Regulate(void);
};

#endif
