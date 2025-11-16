/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFlexArea.h
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#ifndef XFlexAreaH
#define XFlexAreaH
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
#include <QReadWriteLock>
#include <QIODevice>
#include <QImage>

#include "XTypeDef.h"
#include "NListComp.h"
#include "XIntClass.h"
#include "XYCross.h"
#include "XColorSpace.h"
#include "XDualIntList.h"

class   FlexAreaBaseMinMax;
class   FlexAreaBasePointerList;
class	ImageBuffer;
class	ImagePointerContainer;
class	PureFlexAreaListContainer;
class	PureFlexAreaList;
class   FlexAreaBasePure;
class   TransformBase;

#define	MAXFLINESBUFF	100000

struct ClearClusterFuncStruct
{
    BYTE           *BmpData;
    int             NGBmpX;
    int             LCount;
	int				DotPerLine;
	int				MaxLines;
};

#pragma	pack(push)
#pragma	pack(1)

struct   FlexLine
{
    friend  class  FlexAreaBasePure;

    int32   _LeftX;
    int32   _Numb;
    int32   _AbsY;
	int32	Dummy;
	/*
	struct{
		int   _LeftID	:8;						// 左側依存ID
		int   _RightID	:8;					// 右側依存ID
		int   _AbsYID	:8;						// Ｙ依存ID
		int   _Dummy	:8;
	};
	*/

	FlexLine(void){ }
    void    _Set(int x1, int x2 ,int y);

    int		GetNumb(void)	const   {  return(_Numb);   }
    void	SetNumb(int numb)	    {      (numb!=0)?_Numb=numb:_Numb=1;     }

    int		_GetAbsY(void)	const   {	return(_AbsY);			}
    int		_GetLeftX(void)	const   {	return(_LeftX);			}
    int		_GetRightX(void)const   {	return(_LeftX+_Numb);	}
    void	_SetAbsY(int absY)	    {		_AbsY=absY;			}
    void	_SetLeftX(int leftX)    {		_LeftX=leftX;		}
    int		_GetAbsY(FlexAreaBasePure *f)   const ;
    int		_GetLeftX(FlexAreaBasePure *f)  const ;
    int		_GetRightX(FlexAreaBasePure*f)  const ;
    int		_GetAbsY(const FlexAreaBasePure *f)   const ;
    int		_GetLeftX(const FlexAreaBasePure *f)  const ;
    int		_GetRightX(const FlexAreaBasePure*f)  const ;
    void	_SetAbsY(FlexAreaBasePure *f,int absY);
    void	_SetLeftX(FlexAreaBasePure *f,int leftX);
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
struct  FlexData
{
    uint    D;
    ulong   L;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
struct  BlockShape
{
    enum BlockShapeKind{
         _sNone				=0
        ,_sRectangle		=1
        ,_sEllipse			=2
        ,_sRotEllipse		=3
		,_sRotRectangle		=4
        ,_sRing				=5
        ,_sFree				=6
		,_sPoly				=7
		,_sLongCircle		=8
		,_sRingArc			=9
        }Kind;

    union{
        struct{
            int32  X1,Y1,X2,Y2;
            }bsRectangle;
        struct{
            int32  Cx,Cy;
            int32  Rx,Ry;
            }bsEllipse;
        struct{
            int32  Cx,Cy;
            int32  Rx,Ry;
            double  Angle;
            }bsRotEllipse;
        struct{
            int32  Cx,Cy;
            int32  Rx1,Ry1;
            int32  Rx2,Ry2;
            }bsRing;
        struct{
            int32  X1,Y1,X2,Y2;
            double  Angle;
            }bsRotRectangle;
        struct{
            int32	PointCount;
            XYData	*XY;
            }bsPoly;
         struct{
            int32  Cx1,Cy1;
			int32  Cx2,Cy2;
            int32  R;
            }bsLongCircle;
        struct{
            int32  Cx,Cy;
            unsigned short  Rx1,Ry1;
            unsigned short  Rx2,Ry2;
			float	StartAngle;
			float	EndAngle;
            }bsRingArc;
	}Shape;

	BlockShape(void){	Kind=_sNone;	}
	~BlockShape(void){	if(Kind==_sPoly)	delete	[]Shape.bsPoly.XY;	Shape.bsPoly.XY=NULL;	}
    struct BlockShape   &operator=(const struct BlockShape &src);
    bool    operator==(const struct BlockShape &src)    const;
    bool    operator!=(const struct BlockShape &src)    const;

    void    MoveTo(int dx ,int dy);
	void	Rotate(int AngleDegree ,int Cx, int Cy);	//度
	void	MirrorX(int PointY);
	void	MirrorY(int PointX);
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   FlexLineList : public NPList<FlexLineList>
{
  public:
    int x1,x2;
    int y;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FlexLineList(void){};
    FlexLineList(int _x1 ,int _x2 ,int _y);
	void	Set(int _x1 ,int _x2 ,int _y){	x1=_x1;	x2=_x2;	y=_y;	}
};

class   RFlexAreaList;

struct  ColSortedTable
{
    unsigned int    Numb;
    unsigned short  ColNumb;
};

class  FlexAreaBasePure
{
    friend struct   FlexLine;

    struct  FlexLine    *FLines;		// AbsYの小さい順に並べる

    uint32				Len;

    int32		AddX,AddY;
    int32		MinX,MaxX;
	int64		PatternByte;
protected:
    struct  BlockShape  *AShape;
	//int32     DotPerLine,MaxLines;
	//bool		OwningFLines;

    void    SetFLine(struct FlexLine *FL,int len ,unsigned short mIndexPoint);
    void    PointerCopy(const FlexAreaBasePure *src);

public:
    FlexAreaBasePure(void);
    FlexAreaBasePure(int tDotPerLine,int tMaxLines);
    virtual ~FlexAreaBasePure(void);

	void	SetRefereneFrom(const FlexAreaBasePure *src);
 
	int     GetWidth(void)  const   {     return(MaxX-MinX);  }
    int     GetHeight(void) const;
    int     GetMinX(void)   const   {      return(MinX);       }
    int     GetMinY(void)   const;
    int     GetMaxX(void)   const   {      return(MaxX);       }
    int     GetMaxY(void)   const;
    void    SetMinX(int d)          {     MinX=d; }
    void    SetMaxX(int d)          {     MaxX=d; }
    double  GetLength(void) const;

	int		GetFLineLen(void)		const {		return(Len);					}
    int		GetFLineNumb(int n)		const {		return(FLines[n].GetNumb());	}
    int		GetFLineAbsY(int n)		const {		return(FLines[n]._GetAbsY()+AddY);	}
    int		GetFLineLeftX(int n)	const {		return(FLines[n]._GetLeftX()+AddX);	}
    int		GetFLineRightX(int n)	const {		return(FLines[n]._GetLeftX()+AddX+FLines[n].GetNumb());  }
	int		GetFLineAddX(void)		const {		return AddX;	}
	int		GetFLineAddY(void)		const {		return AddY;	}

    void    SetShape(struct BlockShape &bshape);
    struct  BlockShape  &GetShape(void) const ;

    void    SetFLine(struct FlexLine *FL,int len);
    void    SetFLineOnly(struct FlexLine *FL,int len);
    void    SuckFrom(FlexAreaBasePure &src);

    struct  FlexLine    *GetFLinePoint(void)const   {    return(FLines); }
	bool	ShrinkLen(int sLen)				{	if(Len>=sLen){	Len=sLen;	return true;}	return false;	}
    void    Regulate(void);
    virtual	void    Clear(void);
    virtual	void    MoveToNoClip(int dx, int dy);

    int		DirectCopyTo(struct FlexLine dest[] ,int destnumb ,int startIndex=0);
    int     SearchNearBy(struct FlexLine Key);
    struct FlexLine GetFlexLine(int index);
	bool	GetFlexLine(int index , struct FlexLine &Ret)   const;
	int		FindIndex(int AbsY ,int &IndexStart ,int &IndexEnd);

    bool    WriteBase(QIODevice *str);
	bool	WriteBaseVer105(QIODevice *str);
    bool    ReadBase(QIODevice *str);
	bool	ReadBaseVer105(QIODevice *str);
	bool	WriteBaseVer106(QIODevice *str);
	bool	ReadBaseVer106(QIODevice *str);
	bool	WriteBaseVer107(QIODevice *str);
	bool	ReadBaseVer107(QIODevice *str);
	void	SortFLine(struct FlexLine *FL ,int FLNumb);
	void	SortFLine(void);
	int64   GetPatternByte(void)	const 	{	return PatternByte;	}
	void	Swap(FlexAreaBasePure &dest);
private:
	void	Begin(void);

};

#pragma	pack(pop)


inline  int FlexLine::_GetAbsY(FlexAreaBasePure *f)			const   {	return(f->AddY+_AbsY);		}
inline  int FlexLine::_GetLeftX(FlexAreaBasePure *f)		const   {	return(f->AddX+_LeftX);		}
inline  int FlexLine::_GetRightX(FlexAreaBasePure *f)		const   {	return(f->AddX+_LeftX+_Numb);	}
inline  int FlexLine::_GetAbsY(const FlexAreaBasePure *f)	const   {	return(f->AddY+_AbsY);		}
inline  int FlexLine::_GetLeftX(const FlexAreaBasePure *f)	const   {	return(f->AddX+_LeftX);		}
inline  int FlexLine::_GetRightX(const FlexAreaBasePure *f)	const   {	return(f->AddX+_LeftX+_Numb);	}
inline  void FlexLine::_SetAbsY(FlexAreaBasePure *f,int absY)	    {    _AbsY=absY-f->AddY;	}
inline  void FlexLine::_SetLeftX(FlexAreaBasePure *f,int leftX)	    {    _LeftX=leftX-f->AddX;  }


class  FlexArea : public FlexAreaBasePure
{
  public:
    FlexArea(void);
	FlexArea(const FlexArea &src);
    FlexArea(int tDotPerLine,int tMaxLines);
    ~FlexArea(void);

    bool    IsNull(void)                    const ;
    bool    IsInclude(int x ,int y)         const ;
    bool    IsOvered(int DotPerLine, int MaxLines)  const ;
    //void    __fastcall  Initial(int NoZone=DefaultNoZone);
    void    Initial(int NoZone,int DotPerLine, int MaxLines);
    bool    IsInRectangle(int x1 ,int y1 ,int x2 ,int y2)   const ;
    bool    CheckOverlap(const FlexArea *b)           const ;
    bool    CheckOverlap(const FlexArea *src ,int srcDx, int srcDy) const ;
    bool    CheckOverlapNeighbor(const FlexArea *b)   const ;
    bool    IsInclude(const FlexArea *b)  const ;
    bool    CheckOverlapRectangle(int x1 ,int y1 ,int x2 ,int y2)   const ;
    bool    CheckOverlapLine(int x1 ,int y1 ,int x2 ,int y2)        const ;
    bool    CheckOverlapLine(double x1 ,double y1 ,double x2 ,double y2)    const ;
    int     SearchFirst(int y) const;     //ｙは絶対値
    bool    NearBy(struct FlexLine &L);
    void    EatArea(const FlexArea *food);
    void    Restruct(void);
    void    BindArea(void);
    int     GetByte(void);
    void    CopyFrom(FlexArea &src ,int dx ,int dy);
    void    GetWeightCenter(double &cx, double &cy);  //重心の計算
	void	CreateZoom(double ZoomRate ,int Cx,int Cy);
	void	Swap(FlexArea &dest);

    virtual	void     MoveToClip(int dx, int dy
                                  ,int x1 ,int y1 ,int x2 ,int y2);
	FlexArea	MakeSkipYArea(int SkipY);

    void     ChangeWidth(int newW);
    void     ChangeHeight(int newH);

    int      GetClippedPatternByte(int DotPerLine, int MaxLines);
    uchar    *GetPattern(ImageBuffer &data ,int64 *BuffBytes=NULL);
	BYTE	 *GetZoomPattern(double ZoomRate,int Cx,int Cy
								,ImageBuffer &Buff,int &BuffBytes);

    uchar   *MakeBitData(int &Px ,int &Py ,int &Lx ,int &Ly ,int &xbyte,int DotPerLine, int MaxLines);
    void     MakeBitData(BYTE *data ,int xbyte,int DotPerLine, int MaxLines)            const;
    void     MakeBitData(BYTE **data ,int XDotLen ,int YDotLen ,bool EnableThread=true) const;
    void     MakeNotBitData(BYTE **data ,int XDotLen ,int YDotLen ,int mx=0 ,int my=0)  const;
    void     MakeBitData(BYTE **data 
                        ,int dx ,int dy
                        ,int XDotLen, int YDotLen)                      const;
	void	 MakeBitData(ImageBuffer &BitImg ,int dx, int dy)           const;
    void     MakeMaskBitData(BYTE **data,int DotPerLine, int MaxLines)  const;

    bool     CheckOverlapBit(BYTE *data  ,int xbyte,int DotPerLine, int MaxLines)   const;
    bool     CheckOverlapBit(BYTE **data , int XDot ,int YDot)  const;
	int64	 GetCrossBitCount(BYTE **data)  const;
	int64	 GetCrossBitCount(BYTE **data,int dx ,int dy,int srcxbyte ,int srcylen ,int LineIsolation=1)    const;
    void     RestorePattern(ImageBuffer &data ,uchar *ptn);
    void     BuildFromRaster(uchar  *srcdata ,int srcxbyte ,int srcylen
                                        ,int px ,int py);
    void     BuildFromRaster(uchar **srcdata ,int srcxbyte ,int srcylen
                                        ,int OffsetX ,int OffsetY);
    void     BuildFromRaster(uchar **srcdata ,int srcxbyte ,int srcylen
                                        ,int px ,int py
                                        ,int minx ,int miny ,int maxx ,int maxy
										,int DotPerLine, int MaxLines);
    void    Sub(const FlexArea &src1 , const FlexArea &src2);
    void    Sub(const FlexArea &src1 , int dx ,int dy);
	void    Add(const FlexArea &src1 , const FlexArea &src2);
    void    CopyMove(const FlexArea &src , int dx ,int dy);

    void    MaskRemove(BYTE *bitmapmaskpattern ,int xbyte,int DotPerLine, int MaxLines);
    void    MaskRemove(BYTE **bitmapmaskpattern ,int xbyte
                            ,int XDot ,int YDot);
	void		SetFLineFromDirty(struct FlexLine *Src, int SrcLen);
	bool		ChopRect(PureFlexAreaListContainer &Piece ,int ChopSize);
	bool		ChopRect(PureFlexAreaListContainer &Piece ,int ChopSize ,int OverlapSize);
	void		Clusterize(PureFlexAreaListContainer &Piece);

    FlexArea    &operator=(const FlexArea &src);
    FlexArea    &operator=(const RFlexAreaList &src);
    FlexArea    &operator+=(const FlexArea &src);
	FlexArea    &operator-=(const FlexArea &src)    {   Sub(src,0,0);	return *this;	}
    FlexArea    &operator&=(const FlexArea &src);
    FlexArea    &operator|=(const FlexArea &src);
    bool        operator==(const FlexArea &src) const;
    bool        operator!=(const FlexArea &src) const;

	qint64		GetCrossCount(FlexArea &src ,int dx ,int dy)    const;
	qint64		GetCrossCount(int x1,int y1 ,int x2,int y2)     const;

    virtual void    ClipArea(int Left ,int Top ,int Right ,int Bottom);
	void    ClipArea(FlexArea &BoundArea);
    void    ClipByMask(BYTE **data,int DotPerLine, int MaxLines);
    void    MaskEllipse(int ra ,int rb ,int cx ,int cy);
    void    ClipInEllipse(int ra ,int rb ,int cx ,int cy);

    void     _AddPoint(struct FlexLine &b);           //ｂは絶対値
    void     _AddPoints(struct FlexLine b[] ,int Numb);//ｂは絶対値
    double  GetVar(int dx ,int dy
                                    ,ImageBuffer &bufftop
                                    ,double &DAvr)          const;
    double  GetVarByDiffMaster(int dx ,int dy
                                    ,ImageBuffer &TargetBuff
                                    ,ImageBuffer &MasterBuff
                                    ,double &DAvr)          const;
    double  GetAverage(int dx ,int dy ,ImageBuffer &Data
						,double AdoptRateL=0.9,double AdoptRateH=0.9)   const;
    double  GetVar(int mx1 ,int my1 ,int mx2 ,int my2
                    ,ImageBuffer &bufftop ,double &DAvr)    const;
	bool	CalcAvrVar(int dx,int dy,ImageBuffer &buff,double &Avr ,double &Var
					,double AdoptRateL=0.9,double AdoptRateH=0.9
					,  int AreaX1=0,int AreaY1=0 ,int AreaX2=99999999 ,int AreaY2=99999999) const;
	bool	CalcAvrVar(int dx,int dy,ImageBuffer &buff,double &Avr ,double &Var
					, BYTE **EffectiveMaskMap
					, double AdoptRateL=0.9,double AdoptRateH=0.9
					, int AreaX1=0,int AreaY1=0 ,int AreaX2=99999999 ,int AreaY2=99999999)  const;
    QColor  MakeAverage(QImage &Image)  const;

    double  GetAverage		(ImageBuffer &Data,int dx ,int dy)  const;
	double  GetAverage		(ImageBuffer &Data,int dx ,int dy,int CenterX ,int CenterY ,double radian)  const;
    double  GetAverageRough	(ImageBuffer &Data,int dx ,int dy)  const;
    double  GetAverageHalf	(ImageBuffer &Data,int dx ,int dy ,bool SkippingMode=true)  const;
    double  GetAverageClipped(ImageBuffer &Data,int dx ,int dy
                                              ,int X1,int Y1,int X2,int Y2) const;
	void	GetMinMaxBrightness(ImageBuffer &Data,int dx ,int dy ,int &MinBrightness,int &MaxBrightness)        const;
    double  GetBunsan	(ImageBuffer &Data ,double avr,int dx ,int dy,int CenterX ,int CenterY ,double radian)  const;
    double  GetBunsan	(ImageBuffer &Data ,double avr,int dx ,int dy)      const;
	double	GetCoeff	(ImageBuffer &Src ,int dx ,int dy ,ImageBuffer &Dest,int Isolation=1,bool ThreadMode=true)  const;	//相互相関の計算
	double	GetCoeff	(ImageBuffer &Src ,int dx ,int dy ,int CenterX ,int CenterY ,double radian 
                               ,ImageBuffer &Dest,int Isolation=1,bool ThreadMode=true) const;	//相互相関の計算
	bool	GetPeak		(ImageBuffer &Buffer ,int dx ,int dy , int &PeakL ,int &PeakH)  const;

    bool    GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)   const;

    void    GetCenter(int &x ,int &y)       const;
	void	GetCenterOrOnIt(int &x ,int &y) const;
    void    GetCenter(double &x ,double &y) const;
    void    GetCenter(DualIntClass &xy)     const;
    double  GetDistance(const FlexArea &src)    const;
    double  GetDistance(int X ,int Y)           const;
    
	void    SetRectangle(int x1 ,int y1 ,int x2 ,int y2);
    void    SetEllipse(int cx ,int cy ,int rx ,int ry);
    void    SetRotRectangle(int cx ,int cy, int rx ,int ry ,double SRadian);
    void    SetRotEllipse(int cx ,int cy ,int rx ,int ry,double SRadian);
    void    SetRing(int cx ,int cy ,int rx1 ,int ry1 ,int rx2 ,int ry2);
	void    SetRingArc(int cx ,int cy ,int rx1 ,int ry1 ,int rx2 ,int ry2 ,double s1 ,double s2);
	void	SetLongCircle(int cx1 ,int cy1 ,int cx2 ,int cy2 ,int r);
	void	MakeConvexPolygon(XYClassContainer &P);

    bool    Write(QIODevice *str);
    bool    Read(QIODevice *str);
	virtual bool    Save(QIODevice *str){	return Write(str);	}
	virtual bool    Load(QIODevice *str){	return Read(str);	}
    void    MakeOutlineDot(XYClassCluster &XY);
    int     GetSearch(int absY);
    void    FillData(BYTE col ,ImageBuffer &data);
    void    FillData(BYTE col ,BYTE **Image);

	int		GetPatternWidth(void)   const;
	int		GetPatternHeight(void)  const;

    int     GetTopY(void)       const   {   return(GetMinY());   }
    int     GetBottomY(void)    const   {   return(GetMaxY());   }

    void    EnSmoothing( ImageBuffer &dstbuff);
    void    EnLogtrans  (ImageBuffer &dstbuff);

    void    CopyPattern(uchar *data,ImageBuffer &PBuff, int YLen ,int DotPerLine, int MaxLines ,int dx ,int dy);
    void    CopyPartial(ImageBuffer &Dst,ImageBuffer &Src, int dx=0 ,int dy=0);
    int     GetSumColor	(int dx,int dy,ImageBuffer &src ,int xdotperline ,int ymaxlines)    const;
	int 	GetSumColorSep4(int dx,int dy,ImageBuffer &src ,int xdotperline ,int ymaxlines) const;

    int     MakeBrightList(int *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx=0 ,int dy=0,int Isolation=1);
	int     MakeBrightList(unsigned int   *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx=0 ,int dy=0,int Isolation=1);
	int     MakeBrightList(unsigned short *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx=0 ,int dy=0,int Isolation=1);
    int     MakeShadeList(double *BrRate ,ImageBuffer &Img ,double Angle);
			/*	Angle=0: Vertical shade*/

    void    PaintWithColor(BYTE **data, int col,int dx ,int dy ,int DotPerLine, int MaxLines);
    void    PaintWithColor(ImageBuffer &data, int col,int dx ,int dy);
	void    PaintWithColor(QImage &Dest, const QRgb &Col,int dx ,int dy);

	FlexArea	Transform(TransformBase &d);

    int		ClusterDivide(NPListPack<RFlexAreaList> &dst);
    bool    GetClusterCenter(BYTE *data ,double &X ,double &Y,int searchdot ,int ThrLevel,int DotPerLine, int MaxLines);
    void    ThinAreaPartial(uchar **bmpdata,uchar **tmpdata,int xbyte ,int YLen=-1);
    void    FatAreaPartial (int turn ,uchar **bmpdata,uchar **tmpdata,int xbyte ,int YLen=-1);
    void    ThinAreaN(int TurnN);
    void    FatAreaN (int TurnN);
	void    ThinArea1(void);	//1画素収縮して切れる場合、残す

    void    GetLowHightColor(int dx,int dy,ImageBuffer &src	,int &LColor ,int &HColor ,int xdotperline ,int ymaxlines);
    void    GetLowHightColor(int dx,int dy,BYTE **src		,int &LColor ,int &HColor ,int xdotperline ,int ymaxlines);
    bool    MazeBool(int index);
                         //indexの番号のFlexLineの要素が、0番目の要素に経路でたどり着くときtrue
    int     MazeBool2(int index1 ,int index2);
        //  ０：接触している
        //  １：Ｙで離れている
        //  ２：Ｘで離れている
    bool    Clusterize(FlexArea &Remaining);

	bool   Draw(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);
	bool   DrawOutline(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);
	bool   DrawAlpha(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);

	bool   Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,int alpha=0xFF);

	bool   Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,BYTE ColorTable[3][256]
									,int alpha=0xFF);
	void	CreateRGBStock(ImagePointerContainer &Images, RGBStock &Stocker ,int movx=0 ,int movy=0);
	void	CreateColorLogic(ImagePointerContainer &Images, ColorLogic &CLogic ,int movx=0 ,int movy=0);
	void	RegulateBrightness(ImageBuffer &IBuff ,double Average ,double Deviation , int BlockSize
								,double AdoptRateL=0.9,double AdoptRateH=0.9);

	void	Multiply(double m);

	void	Rotate(double AngleDegree ,double Cx, double Cy);	//度
	void	MirrorX(int PointY);
	void	MirrorY(int PointX);

	void	PourFromImage(ImageBuffer &Img 
						,BYTE **Mask
						,int StartX, int StartY
						,int PickupL ,int PickupH
						,void (*func)(void)
						,int MaxBuffCount=1000000
						,int MaxSizeXLen=30000,int MaxSizeYLen=30000
						,BYTE **TmpMap=NULL);	//Tmp should be cleared before call
	void	PourFromImage(ImagePointerContainer &Images
						,BYTE **Mask
						,int StartX, int StartY
						,ColorLogic &Color
						,void (*func)(void)
						,int MaxBuffCount=1000000
						,int MaxSize=30000);
	void	PourFromImage(ImageBuffer &Img 
					,BYTE **Mask
					,int StartX, int StartY
					,int PickupL ,int PickupH
					,void (*func)(void)
					,int MaxBuffCount,struct   FlexLine	*BuffLines
					,int MaxSizeXLen,int MaxSizeYLen
					,BYTE **TmpMap);
	void	PourFromImageLimitless(ImageBuffer &Image
						,BYTE **Mask
						,int StartX, int StartY
						,int PickupL ,int PickupH
						,void (*func)(void)
						,int MaxSize=-1) ;
	void	PourFromImageLimitless(ImagePointerContainer &Images
						,BYTE **Mask
						,int StartX, int StartY
						,ColorLogic &Color
						,void (*func)(void)
						,int MaxSize=-1);
	void	PourFromImage(BYTE **SrcBitImage ,int XByte ,int YLen
						,int StartX, int StartY
						,void (*func)(void)
						,int MaxBuffCount=1000000
						,int MaxSize=30000);
	void	MakeBitmap(ColorLogic &Color ,int Mergin ,ImagePointerContainer &Images 
					,int MapDx ,int MapDy ,BYTE **DestMap ,int XLen ,int YLen)  const;

private:
    bool    PickOutlineDot(XYClassArea *w ,int n ,BYTE *Dummy);
    static  bool  ClearClusterFunc(struct ClearClusterFuncStruct *LData ,int x ,int y);
    static  void SearchAdd(struct FlexAreaFuncData *D
                                    ,int x1 ,int x2 ,int y
                                    ,int NowPoint);
	bool    SubInside(const FlexArea &src, int dx ,int dy ,float Multiply);
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   RFlexAreaList : public NPList<RFlexAreaList>,public FlexArea
{
  public:
    NPListPack<FlexLineList>    FLineList;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    RFlexAreaList(void){}
    ~RFlexAreaList(void){}

    int64 GetPatternByte(void)  const;
};

class   PureFlexAreaList : public NPListSaveLoad<PureFlexAreaList> ,public FlexArea
{
  public:
    PureFlexAreaList(void){}
    PureFlexAreaList(const PureFlexAreaList &src);
    PureFlexAreaList(const FlexArea &src);
    ~PureFlexAreaList(void){}

    PureFlexAreaList    &operator=(const PureFlexAreaList &src);
    PureFlexAreaList    &operator=(const FlexArea &src);

	virtual	bool	Save(QIODevice *f)  override;
	virtual	bool	Load(QIODevice *f)  override;
};

class	PureFlexAreaListContainer : public NPListPackSaveLoad<PureFlexAreaList>
{
public:
	PureFlexAreaListContainer(void){}
    PureFlexAreaListContainer(const PureFlexAreaListContainer &src);

	virtual bool    Save(QIODevice *str)    override;
	virtual bool    Load(QIODevice *str)    override;
	PureFlexAreaListContainer	&operator=(const PureFlexAreaListContainer &src);
	PureFlexAreaListContainer	&operator+=(const PureFlexAreaListContainer &src);

	virtual	PureFlexAreaList	*Create(void)	override    {	return new PureFlexAreaList();	}
	bool	IsInclude(int x ,int y)     const;
	void	MoveNoClip(int dx ,int dy);
	void	MoveClip(int dx ,int dy ,int Left ,int Top ,int Right ,int Bottom);

    FlexArea    Bind(void);

    int     GetWidth(void)  const;
    int     GetHeight(void) const;
    int     GetMinX(void)   const;
    int     GetMinY(void)   const;
    int     GetMaxX(void)   const;
    int     GetMaxY(void)   const;
};

class	FlexAreaPointerList : public NPList<FlexAreaPointerList>
{
	FlexArea	*Pointer;
public:
	FlexAreaPointerList(void)		    {	Pointer=NULL;	}
	FlexAreaPointerList(FlexArea *P)    {	Pointer=P;		}

	FlexArea	*GetArea(void)	const   {	return Pointer;	}
};

class	FlexAreaPointerContainer : public NPListPack<FlexAreaPointerList>
{
public:
	FlexAreaPointerContainer(void){}
	void	Add(FlexArea *a);
};


#endif
