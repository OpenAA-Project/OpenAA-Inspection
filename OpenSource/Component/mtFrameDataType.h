#pragma once

typedef	enum    _DrawingMode{
        fdNone					=0
		,fdPoint				=1
        ,fdLine					=2
        ,fdHalfLine				=3
        ,fdChoppedLine			=4
        ,fdRectangle			=5
        ,fdRotRectangle			=6
        ,fdCircle				=7
		,fdCircle3				=20
        ,fdEllipse				=8
		,fdEllipse4				=19
        ,fdRotEllipse			=9
        ,fdArc					=10
		,fdArc3					=18
        ,fdFree					=11
        ,fdPoly					=12
        ,fdMove					=13
        ,fdRing					=14
        ,fdSingleArrow			=15
        ,fdDualArrow			=16
        ,fdSpoint				=17
		,fdVChoppedLine			=21
		,fdHChoppedLine			=22
		,fdLongCircle			=23
		,fdRingArc1				=24		//from Center
		,fdRingArc4				=25
}DrawingMode;

typedef	enum	_DisplayType
{
	__NoImage		=0
	,__Master		=0x0001
	,__Master2		=0x0080
	,__Target		=0x0002
	,__BackGround	=0x0100
	,__GrayLower	=3
	,__GrayUpper	=4
	,__DelayedView	=0x0004
	,__BitBuff		=0x0008
	,__RawTarget	=0x0010
	,__CamTarget	=0x0020
	,__TargetTR		=0x0040
	,__TrialTarget	=0x0100
}DisplayType;


class   ShapePoint : public NPList<ShapePoint>
{
public:
    double  x,y;
    ShapePoint(void){}
    explicit	ShapePoint(int _x ,int _y) : x(_x),y(_y){}
    explicit	ShapePoint(double _x ,double _y) : x(_x),y(_y){}
};

class   ColPoint : public NPList<ColPoint>
{
  public:
    double  x,y;
    QColor  col;
	bool	ColEffectiveMask;

    ColPoint(void){}
    explicit	ColPoint(int _x ,int _y ,QColor &c) : x(_x),y(_y),col(c){	ColEffectiveMask=false;}
    explicit	ColPoint(double _x ,double _y ,QColor &c) : x(_x),y(_y),col(c){	ColEffectiveMask=false;}
    explicit	ColPoint(double _x ,double _y ,bool mask) : x(_x),y(_y){	ColEffectiveMask=mask;}
    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

    short   X,Y;
    short   EffectiveMode;

};

struct  _ShapeData{
    DrawingMode dtype;
	union _UUU{
		struct  _PointData{
			double x;
            double y;
	        }PointData;
		struct  _LineData{
			double	x;
            double	y;
	        double  s;
		    }LineData;
        struct  _HalfLineData{
	        double	x;
		    double	y;
			double  s;
            }HalfLineData;
	    struct  _ChoppedLineData{
		    double x1,y1;
			double x2,y2;
            }ChoppedLineData;
	    struct  _RectangleData{
		    double x1,y1;
			double x2,y2;
            }RectangleData;
	    struct  _RotRectangleData{
		    double cx,cy;
			double rx,ry;
            double  s;
	        }RotRectangleData;
		struct  _CircleData{
			double cx,cy;
            double r;
	        }CircleData;
		struct  _EllipseData{
			double cx,cy;
            double rx,ry;
	        }EllipseData;
		struct  _RotEllipseData{
			double cx,cy;
            double rx,ry;
	        double  s;
		    }RotEllipseData;
        struct  _ArcData{
	        double cx,cy;
		    double r;
			double  s1,s2;
            }ArcData;
	    struct  _FreeData{
		    NPListPack<ShapePoint>  *points;
			}FreeData;
        struct  _PolyData{
	        NPListPack<ShapePoint>  *points;
		    }PolyData;
        struct  _MoveData{
	        NPListPack<ShapePoint>  *points;
		    }MoveData;
        struct  _ERingData{
	        double cx,cy;
		    double rx1,ry1;
			double rx2,ry2;
            }ERingData;
	    struct  _SingleArrowLineData{
		    double x1,y1;
			double x2,y2;
            }SingleArrowLineData;
	    struct  _DualArrowLineData{
		    double x1,y1;
			double x2,y2;
            }DualArrowLineData;
	    struct  _LongCircleData{
		    double cx1,cy1;
		    double cx2,cy2;
            double  r;
	        }LongCircleData;
        struct  _RingArcData{
	        double cx,cy;
		    double rx1,ry1;
			double rx2,ry2;
			double  s1,s2;
            }RingArcData;
	}UData;
	double	LineWidth;
	_ShapeData(void){   UData.FreeData.points=NULL;   UData.PolyData.points=NULL;   UData.MoveData.points=NULL;   LineWidth=0.0;	}
	~_ShapeData(void);

	bool    Save(QIODevice *file);
	bool    Load(QIODevice *file);
};