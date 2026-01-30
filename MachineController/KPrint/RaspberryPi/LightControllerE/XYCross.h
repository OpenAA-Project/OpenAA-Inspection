/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#if	 !defined(XYCrossH)

#define XYCrossH
#include <QIODevice>
#include <QRect>
#include <QPainter>

#include "XTypeDef.h"
#include "NList.h"


class   FlexArea;

typedef struct  _XYData
{
    int32 x,y;

	_XYData(){}
	_XYData(_XYData &src){	x=src.x;	y=src.y;	}
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
	DoublePoint(double _x,double _y):x(_x),y(_y){}

	DoublePoint	&operator=(DoublePoint &src){	x=src.x;	y=src.y;	return *this;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class   XYClass : public NPList<XYClass>
{
  public:
    int x,y;

    XYClass(void):x(0),y(0){}
    XYClass(int _x,int _y):x(_x),y(_y){}
    XYClass(XYClass &src){  x=src.x;    y=src.y;    }

    XYClass   &operator=(XYClass &src){ x=src.x; y=src.y;   return(*this);  }
	bool	operator==(XYClass &src);
	bool	operator!=(XYClass &src);

    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	XYClass::operator==(XYClass &src)
{
	if(x==src.x && y==src.y){
		return true;
	}
	return false;
}
inline	bool	XYClass::operator!=(XYClass &src)
{
	if(x!=src.x || y!=src.y){
		return true;
	}
	return false;
}

class   RectClass : public NPList<RectClass>
{
  public:
    int x1,y1,x2,y2;
    int attr;

    RectClass(void){}
    RectClass(int _x1,int _y1 ,int _x2 ,int _y2 ,int _attr=0)
        :x1(_x1),y1(_y1),x2(_x2),y2(_y2),attr(_attr){}

    RectClass   &operator=(RectClass &src);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
	bool	IsInclude(int x ,int y);
	void	GetCenter(int &x,int &y){	x=(x1+x2)/2;	y=(y1+y2)/2;	}
};


class   XYDoubleClass : public NPList<XYDoubleClass>
{
  public:
    double x,y;

    XYDoubleClass(void):x(0.0),y(0.0){}
    XYDoubleClass(double _x,double _y):x(_x),y(_y){}
    XYDoubleClass(XYDoubleClass &src){  x=src.x;    y=src.y;    }

	void	Set(double _x, double _y)	{	x=_x;	y=_y;	}
    XYDoubleClass   &operator=(XYDoubleClass &src){ x=src.x; y=src.y;   return(*this);  }
	bool	operator==(XYDoubleClass &src);
	bool	operator!=(XYDoubleClass &src);

    void    ChangeXY(XYDoubleClass *outlineOffset ,int MaxPage,int maxlines);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	XYDoubleClass::operator==(XYDoubleClass &src)
{
	if(x==src.x && y==src.y){
		return true;
	}
	return false;
}
inline	bool	XYDoubleClass::operator!=(XYDoubleClass &src)
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

	bool    Save(QIODevice  *file);
	bool    Load(QIODevice  *file);
	void    MoveTo(int dx ,int dy);
	void	Add(int x ,int y);
	void    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy);
	void    GetCenter(int &cx ,int &cy);
	int		GetDotCount(void){	return NPListPack<XYClass>::GetNumber();	}
	XYClass	*GetFirstDot(void){	return NPListPack<XYClass>::GetFirst();		}

	XYClassContainer &operator=(XYClassContainer &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
	bool	IsIsclude(int x ,int y);

};

class	XYDoubleClassContainer : public NPListPack<XYDoubleClass>
{
 public:
	XYDoubleClassContainer(void){}

	bool    Save(QIODevice  *file);
	bool    Load(QIODevice  *file);
	void    MoveTo(int dx ,int dy);
	void    GetXY(double &minx ,double &miny ,double &maxx ,double &maxy);
	void    GetCenter(double &cx ,double &cy);
	int		GetDotCount(void){	return NPListPack<XYDoubleClass>::GetNumber();	}
	XYDoubleClass	*GetFirstDot(void){	return NPListPack<XYDoubleClass>::GetFirst();		}

	XYDoubleClassContainer &operator=(XYDoubleClassContainer &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
	bool	IsIsclude(int x ,int y);
};

class   XYClassArea : public NPList<XYClassArea> ,public NPListPack<XYClass>
{
  public:
    bool    Positive;

    XYClassArea(void){	Positive=true;	}

    bool    Write(QIODevice  *file);
    bool    Read(QIODevice  *file);
    void    SetRectangle(QRect &rect);
    bool    IsInclude(int x ,int y);
    void    TransTo(FlexArea &area);
    void    Rotate(double angle ,int cx ,int cy);
    bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2);
    bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2);
    void    MoveTo(int dx ,int dy);
    void    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy);
    void    GetCenter(int &cx ,int &cy);
    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);
    bool    IsValid(void);
	void    Regulate(void);
	void	Simplize(void);

	int		GetDotCount(void){	return NPListPack<XYClass>::GetNumber();	}
	XYClass	*GetFirstDot(void){	return NPListPack<XYClass>::GetFirst();		}

    XYClassArea &operator=(XYClassArea &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

  private:
    void    TransToInner(FlexArea &area);
    static  int transtofunc(const void *a ,const void *b);
};

class   XYClassCluster : public NPListPack<XYClassArea>
{
  public:
    XYClassCluster(void){}

    bool    Write(QIODevice  *file);
    bool    Read(QIODevice  *file);
    void    SetRectangle(QRect &rect);
    bool    IsInclude(int x ,int y);
    bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2);
    void    TransTo(FlexArea &area);
    void    MoveTo(int dx ,int dy);
    bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2);
    XYClassCluster &operator=(XYClassCluster &src);
    void    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy);

    void    Rotate(double angle ,int cx ,int cy);
    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);

    bool    Validate(void); //�����ȗ̈����폜����
	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
};

//========================================================================================
class   XYLines : public NPList<XYLines> ,public NPListPack<XYClass>
{
  public:
	int	MinX,MinY,MaxX,MaxY;

    XYLines(void);

    bool    Write(QIODevice  *file);
    bool    Read(QIODevice  *file);
    bool    IsInclude(int x ,int y,double AreaLength=5);
    void    Rotate(double angle ,int cx ,int cy);
    bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2);
    bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2);
    void    MoveTo(int dx ,int dy);
    void    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy);
    void    GetCenter(int &cx ,int &cy);
    void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);
    bool    IsValid(void);
	void    Regulate(void);

	int		GetDotCount(void){	return NPListPack<XYClass>::GetNumber();	}
	XYClass	*GetFirstDot(void){	return NPListPack<XYClass>::GetFirst();		}

    XYLines &operator=(XYLines &src);

	void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

	void	CreateOneLine(BYTE **BmpMap , int XLen ,int YLen
										,int x ,int y);
	void	GetMinY(int &x ,int &y);
	void	GetMaxY(int &x ,int &y);
	double	GetDistance(int x,int y);
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

inline	bool	RectClass::IsInclude(int x ,int y)
{
	if(x1<=x && x<=x2 && y1<=y && y<=y2)
		return true;
	return false;
}


#endif