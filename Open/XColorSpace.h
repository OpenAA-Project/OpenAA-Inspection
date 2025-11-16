/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XColorSpace.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XCOLORSPACE_H)
#define	XCOLORSPACE_H

#include <QIODevice>
#include <QColor>
#include "XDateTime.h"
#include "XTypeDef.h"
#include "NListComp.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <QReadWriteLock>
#include "XFloatShort.h"

class	RGBStock;
class	ImagePointerContainer;

class	PreciseColor
{
public:
	UFloatShort		Red,Green,Blue;

	PreciseColor(void){}
	PreciseColor(double R, double G ,double B);

	double	GetRed(void);
	double	GetGreen(void);
	double	GetBlue(void);

	PreciseColor	&operator=(const PreciseColor& src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PreciseColorList : public PreciseColor ,public NPListSaveLoad<PreciseColorList>
{
public:
	PreciseColorList(void){}
	PreciseColorList(const PreciseColor &src);
	explicit	PreciseColorList(double R, double G ,double B) : PreciseColor(R,G,B){}

	PreciseColorList	& operator=(const PreciseColorList& src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	PreciseColorListConatiner : public NPListPackSaveLoad<PreciseColorList>
{
public:
	PreciseColorListConatiner(void){}
	PreciseColorListConatiner(const PreciseColorListConatiner &src);

	virtual	PreciseColorList	*Create(void)	override	{	return new PreciseColorList();	}

	PreciseColorListConatiner	&operator=(const PreciseColorListConatiner &src);
};

class	ColorPlane
{
	float	wr;
	float	wg;
	float	wb;
	float	wc;	//r*wr+g*wg+b*wb+wc>=0
public:

	ColorPlane(void){}
	ColorPlane(const ColorPlane &src);

	bool	operator==(ColorPlane &src)	const;
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	Calc(BYTE r ,BYTE g ,BYTE b){	return ((r*wr+g*wg+b*wb+wc)>0)?true:false;	}

	ColorPlane	&operator=(ColorPlane &src);
	ColorPlane	&operator=(const ColorPlane &src);

	void	Multiply(double m);
	void	ShiftColor(int dR ,int dG ,int dB);
};

class	ColorSpace : public NPList<ColorSpace>
{
public:
	ColorSpace(void){}

	virtual	bool	operator==(const ColorSpace &src)	const	=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;
	virtual	bool	Calc(BYTE r		,BYTE g		,BYTE b ,int Mergin)	=0;
	virtual	bool	Calc(double	r	,double g	,double b ,int Mergin)	=0;
	virtual	bool	Calc(int RGBM[4])									=0;
	virtual	BYTE	Calc8(BYTE *r ,BYTE *g ,BYTE   *b,int Mergin)		=0;
	virtual	double	GetLength(BYTE r ,BYTE g ,BYTE b)					=0;
	virtual	QRgb	GetCenter(void){	return qRgb(0,0,0);	}
	virtual	int		GetClassID(void)const						=0;
	static	ColorSpace	*GetNew(int classid);
	virtual	void	Multiply(double m)							=0;
	virtual	void	ShiftColor(int dR ,int dG ,int dB)			=0;
	virtual	void	AddMergin(int mergin){}
	virtual	void	MakeOrTable(BYTE *Table, int Mergin)		=0;
	virtual	void	MakeAndTable(BYTE *Table, int Mergin)		=0;
	virtual	void	GetMonoColorRange(int &ColL, int &ColH)		=0;
};

class	ColorCube : public ColorSpace
{
	ColorPlane	*Planes;
	int32		PlaneCounts;
public:
	ColorCube(void);
	ColorCube(const ColorCube &src);
	~ColorCube(void);

	virtual	bool	operator==(const ColorSpace &src)	const	override;
	virtual	int		GetClassID(void)const	override	{	return 1;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	Calc(BYTE r ,BYTE g ,BYTE b,int Mergin)				override;
	virtual	bool	Calc(double	r	,double g	,double b,int Mergin)	override	{	return true;	}
	virtual	bool	Calc(int RGBM[4])									override;
	virtual	BYTE	Calc8(BYTE *r ,BYTE *g ,BYTE *b,int Mergin)			override	{	return 0;	}
	virtual	double	GetLength(BYTE ,BYTE ,BYTE )						override	{	return 0;	}
	bool	Create(RGBStock &Inside ,RGBStock &Outside);

	ColorCube	&operator=(const ColorCube &src);

	virtual	void	Multiply(double m)						override;
	virtual	void	ShiftColor(int dR ,int dG ,int dB)		override;
	virtual	void	MakeOrTable(BYTE *Table, int Mergin)	override{}
	virtual	void	MakeAndTable(BYTE *Table,int Mergin)	override{}
	virtual	void	GetMonoColorRange(int &ColL, int &ColH)	override{}
};

class	ColorCubeBit
{
	BYTE	*CubeMap;
	bool	Active;
public:
	ColorCubeBit(void);
	ColorCubeBit(const ColorCubeBit &src);
	~ColorCubeBit(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsActive(void)	const{	return Active;	}
	bool	CalcOnMask(BYTE r ,BYTE g ,BYTE b);

	ColorCubeBit	&operator=(const ColorCubeBit &src);

	void	Clear(void);
	void	AppendMask(BYTE r ,BYTE g ,BYTE b,int Mergin=0);
};



class	ColorSphere : public ColorSpace
{
	QRgb	Center;
	WORD	Radius;

	int		CalcTable[4];	//r,g,b,-radius
	short	CalcTable16bitR[8];
	short	CalcTable16bitG[8];
	short	CalcTable16bitB[8];

public:
	ColorSphere(void){	Radius=0;	Center=0;	}
	ColorSphere(const ColorSphere &src);
	ColorSphere(int r ,int g ,int b, int radius);
	ColorSphere(QRgb &_Center,WORD _Radius);
	~ColorSphere(void);

	void	Set(int r ,int g ,int b, int radius);
	virtual	bool	operator==(const ColorSpace &src)	const	override;
	virtual	int		GetClassID(void)const	override	{	return 2;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	Calc(BYTE	r ,BYTE	  g ,BYTE   b,int Mergin)	override;
	virtual	bool	Calc(double	r ,double g ,double	b,int Mergin)	override;
	virtual	bool	Calc(int RGBM[4])								override;
	virtual	BYTE	Calc8(BYTE *r ,BYTE *g ,BYTE   *b,int Mergin)	override;
	virtual	QRgb	GetCenter(void)									override	{	return Center;	}
	bool	Create(RGBStock &Inside);
	virtual	double	GetLength(BYTE r ,BYTE g ,BYTE b)				override;
	virtual	void	Multiply(double m)								override;
	virtual	void	ShiftColor(int dR ,int dG ,int dB)				override;
	virtual	void	AddMergin(int mergin)							override;

	ColorSphere	&operator=(const ColorSphere &src);
	virtual	void	MakeOrTable(BYTE *Table, int Mergin)		override;
	virtual	void	MakeAndTable(BYTE *Table,int Mergin)		override;
	virtual	void	GetMonoColorRange(int &ColL, int &ColH)		override;
private:
	void	CreateCalcTable(void);
};

inline	ColorSphere::ColorSphere(int r ,int g ,int b, int radius)
:Center(qRgb(r,g,b)),Radius(radius)
{
	CreateCalcTable();
}
inline	ColorSphere::ColorSphere(QRgb &_Center,WORD _Radius)
:Center(_Center),Radius(_Radius)
{
	CreateCalcTable();
}


#define	OKTableByte			(256*256*256/8)

class	ColorBox : public ColorSpace
{
	short	ColRL,ColRH;
	short	ColGL,ColGH;
	short	ColBL,ColBH;
public:
	ColorBox(void){}

	void	Set( int colRL,int colRH
				,int colGL,int colGH
				,int colBL,int colBH);
	virtual	bool	operator==(const ColorSpace &src)	const	override;
	ColorBox &operator=(const ColorSpace &src);
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Calc(BYTE r		,BYTE g		,BYTE b ,int Mergin)	override;
	virtual	bool	Calc(double	r	,double g	,double b ,int Mergin)	override;
	virtual	bool	Calc(int RGBM[4])									override;
	virtual	BYTE	Calc8(BYTE *r ,BYTE *g ,BYTE   *b,int Mergin)		override;
	virtual	double	GetLength(BYTE r ,BYTE g ,BYTE b)					override;
	virtual	QRgb	GetCenter(void)			override	{	return qRgb((ColRL+ColRH)/2,(ColGL+ColGH)/2,(ColBL+ColBH)/2);	}
	virtual	int		GetClassID(void)const	override	{	return 3;	}
	virtual	void	Multiply(double m)							override;
	virtual	void	ShiftColor(int dR ,int dG ,int dB)			override;
	virtual	void	AddMergin(int mergin)						override;
	virtual	void	MakeOrTable(BYTE *Table, int Mergin)		override;
	virtual	void	MakeAndTable(BYTE *Table, int Mergin)		override;
	virtual	void	GetMonoColorRange(int &ColL, int &ColH)		override;
};

inline	ColorSpace	*ColorSpace::GetNew(int classid)
{
	ColorSpace	*Ret=NULL;
	switch(classid){
		case 1:	Ret=new ColorCube();
				break;
		case 2:	Ret=new ColorSphere();
				break;
		case 3:	Ret=new ColorBox();
				break;
		default:Ret=NULL;
	}
	return Ret;
}


class	ColorLogic : public NPList<ColorLogic>
{
protected:
	NPListPack<ColorSpace>	Base;
	NPListPack<ColorSpace>	Eliminated;
public:

	ColorLogic(void){}
	ColorLogic(ColorLogic &src);
	ColorLogic(const ColorLogic &src);
	virtual	~ColorLogic(void){}

	virtual	bool	Calc(BYTE	r ,BYTE	  g ,BYTE   b ,int Mergin);
	virtual	bool	Calc(double	r ,double g ,double	b ,int Mergin);
	virtual	BYTE	Calc8(BYTE *r ,BYTE *g ,BYTE   *b,int Mergin);
	void	Eliminate(ColorLogic &src ,int AdditionalMergin=0);
	void	Add(ColorLogic &src ,int AdditionalMergin=0);
	void	Add(ColorSpace *src);
	void	Eliminame(QRgb src ,int Mergin=10);
	void	Add(QRgb src ,int Mergin=10);
	
	ColorSpace	*GetFirstBase(void)			const	{	return Base.GetFirst();			}
	ColorSpace	*GetBase(int n)				const	{	return Base.GetItem(n);			}
	ColorSpace	*GetFirstEliminated(void)	const	{	return Eliminated.GetFirst();	}
	ColorSpace	*GetEliminated(int n)		const	{	return Eliminated.GetItem(n);	}
	void	RemoveBase(ColorSpace *c)				{	Base.RemoveList(c);				}
	void	RemoveEliminated(ColorSpace *c)			{	Eliminated.RemoveList(c);		}
	void	AddBase(ColorSpace *c)					{	Base.AppendList(c);				}
	void	AddEliminated(ColorSpace *c)			{	Eliminated.AppendList(c);		}

	void	ClearBase(void);
	void	ClearEliminate(void);
	void	ClearAll(void);

	int		GetBaseCount(void)			const	{	return Base.GetCount();			}
	int		GetEliminateCount(void)		const	{	return Eliminated.GetCount();	}

	void	AddMerginInBases(int mergin);
	void	AddMerginInEliminated(int mergin);
	bool	operator==(const ColorLogic &src)	const;
	bool	operator!=(const ColorLogic &src)	const	{	return !operator==(src);	}
	bool	IsEmpty(void)	const;
	ColorLogic	&operator=(ColorLogic &src);
	ColorLogic	&operator=(const ColorLogic &src);
	virtual	void	Multiply(double m);
	void	ShiftColor(int dR ,int dG ,int dB);

	bool	GetMonoColorRange(int &ColL, int &ColH)	const;
	void	SetMonoColorRange(int ColL, int ColH);
	void	SetMonoColorRange(int RColL, int RColH
							, int GColL, int GColH
							, int BColL, int BColH);
	bool	MakeBitmap(ImagePointerContainer &Images ,BYTE **DestMap ,int XLen ,int YLen);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


class	ColorLogicWithTable : public ColorLogic
{
	BYTE	*OKTable;
	bool	OriginTable;

	static	NPListPack<ColorLogic>	ColorLogicTable[256];
	static	QReadWriteLock	ColorLogicTableAccessor;
	static	int		ColorLogicTableCount;

#define	MaxColorLogicTableCount	100

public:

	ColorLogicWithTable(void){	OKTable=NULL;	}
	ColorLogicWithTable(const ColorLogicWithTable &src);
	virtual	~ColorLogicWithTable(void);

	virtual	bool	Calc(BYTE	r ,BYTE	  g ,BYTE   b ,int Mergin)	override;
	virtual	bool	Calc(double	r ,double g ,double	b ,int Mergin)	override;
	ColorLogicWithTable	&operator=(const ColorLogicWithTable &src);
	ColorLogicWithTable	&operator=(const ColorLogic &src);

	void	CreateTable(int Mergin);
	bool	IsEnableTable(void){	return (OKTable==NULL)?false:true;	}

	static	void	ClearTable(void);
};

extern	ColorLogic	QString2ColorLogic(const QString &str);
extern	QString		ColorLogic2QString(const ColorLogic &L);

//=================================================================

class	RgbList : public NPList<RgbList>
{
	QRgb	RGBData;
public:
	RgbList(void){}

	RgbList &operator=(const RgbList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	RgbStocker : public NPListPack<RgbList>
{
public:
	RgbStocker(void){}

	RgbStocker	&operator=(const RgbStocker &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


//=================================================================
class	RGBSample : public NPList<RGBSample>
{
	QRgb	rgbData;
	float	Weight;
public:
	RGBSample(void){	Weight=0;	}
	RGBSample(const RGBSample &src);
	explicit	RGBSample(QRgb col ,float weight=0.0){	rgbData=col;	Weight=weight;	}

	operator QRgb()	const	{	return rgbData;	}
	void	SetColor(QRgb col)	{	rgbData=col;	}
	int	GetRed()	const	{	return qRed(rgbData);		}
	int	GetGreen()	const	{	return qGreen(rgbData);		}
	int	GetBlue()	const	{	return qBlue(rgbData);		}
	float	GetWeight(void)	const	{	return Weight;	}
	void	SetWeight(float weight)	{	Weight=weight;	}
	bool	IsInclude(int r ,int g ,int b ,int Ext)	const;
	double	GetLength(const RGBSample &s)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	RGBSample	&operator=(const RGBSample &src);
	bool		operator==(const RGBSample &src)const	{	return (src.rgbData==rgbData)?true:false;	}
	bool		operator!=(const RGBSample &src)const	{	return (src.rgbData!=rgbData)?true:false;	}
	bool		operator==(const QRgb &src)		const	{	return (src==rgbData)?true:false;	}
	bool		operator!=(const QRgb &src)		const	{	return (src!=rgbData)?true:false;	}
};

class	RGBStock : public NPListPack<RGBSample>
{
public:
	RGBStock(void){}
	RGBStock(const RGBStock &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	RGBStock	&operator=(const RGBStock &src);
	RGBStock	&operator+=(const RGBStock &src);
	void	Clear(void){	RemoveAll();	}
	RGBSample	*SearchRGBSample(const QRgb &Col)			const;
	RGBSample	*SearchRGBSample(const QRgb &Col,int Ext)	const;

	QRgb	GetCenter(void)	const;
	void	GetCenter(double &r ,double &g ,double &b)	const;
	void	SetWeight(float w);

	bool		IsInclude(int r ,int g ,int b ,int Ext)	const;
	double		GetClosedLength(const RGBSample &Col)	const;
};

//=================================================================
class	ColorSampleList
{
	void	*Data;
	int		AutoCount;
	QString	Name;
public:
	enum	ColorDataType{
		TypeColorLogic=1
		,TypeRGBStock=2
	};
private:
	ColorDataType	DataType;
	XDateTime	UpdateTime;
	int32 SelectedColorFolder;	//保存されない

public:
	ColorSampleList(void){	AutoCount=-1;	Data=NULL;	}

	bool	SaveData(QIODevice *f);
	bool	LoadData(QIODevice *f);

	void	Set(ColorLogic &src);
	void	Set(RGBStock &src);
	void	Set(RGBStock &src ,float weight);

	RGBStock	*GetRGBStock(void)		const;
	ColorLogic	*GetColorLogic(void)	const;	//Thread-safeでない

	ColorSampleList	&operator=(ColorSampleList &src);

	int		GetAutoCount(void)	const	{	return AutoCount;	}
	void	SetAutoCount(int n)			{	AutoCount=n;		}
	QString	GetName(void)		const	{	return Name;		}
	void	SetName(const QString &s)	{	Name=s;		}
	const XDateTime	&GetUpdateTime(void)	const	{	return UpdateTime;	}
	void	SetUpdateTime(const XDateTime &s)		{	UpdateTime=s;	}
	ColorDataType	GetDataType(void)		const	{	return DataType;	}
	void	SetDataType(ColorDataType s)	{	DataType=s;	}

	void	SetSelectedColorFolder(int n)			{	SelectedColorFolder=n;			}
	int		GetSelectedColorFolder(void)	const	{	return SelectedColorFolder;		}
};

//========================================================================
class	RelativeThresholdColorBox
{
#pragma	pack(push,1)
	struct	{
		BYTE	rL,rH;
		BYTE	gL,gH;
		BYTE	bL,bH;
		}ColData;
#pragma	pack(pop)

public:
	RelativeThresholdColorBox(void){}

	RelativeThresholdColorBox	&operator=(const RelativeThresholdColorBox &src);
	bool	operator==(const RelativeThresholdColorBox &src)	const;
	bool	operator!=(const RelativeThresholdColorBox &src)	const	{	return !operator==(src);	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	GetColorRange(QRgb &center 
						,int &RL ,int &RH
						,int &GL ,int &GH
						,int &BL ,int &BH) const;
	void	GetRelColorRange(
						 int &RL ,int &RH
						,int &GL ,int &GH
						,int &BL ,int &BH) const;
	void	GetMonoRange(int center
						,int &L ,int &H) const;
	void	GetRelMonoRange(int &L ,int &H) const;

	void	SetAbsColorRange(QRgb &center 
						,int AbsRL ,int AbsRH
						,int AbsGL ,int AbsGH
						,int AbsBL ,int AbsBH);
	void	SetAbsMonoRange(int center
						,int AbsL ,int AbsH);
	void	SetRelColorRange(
						 int AbsRL ,int AbsRH
						,int AbsGL ,int AbsGH
						,int AbsBL ,int AbsBH);
	void	SetRelMonoRange(int AbsL ,int AbsH);
};
//=================================================================
class	FloatRGBColor
{
public:
	double	R,G,B;

	FloatRGBColor(void){}
	FloatRGBColor(const QColor &col);
	FloatRGBColor(const FloatRGBColor &src);

	FloatRGBColor	&operator=(const FloatRGBColor &src);
	bool	operator==(const FloatRGBColor &src);
	bool	operator!=(const FloatRGBColor &src);
	void	SetColor(double r ,double g ,double b)	{	R=r;	G=g;	B=b;	}
	double	GetRed(void)	{	return R;	}
	double	GetGreen(void)	{	return G;	}
	double	GetBlue(void)	{	return B;	}
	double	GetDistance(const FloatRGBColor &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//=================================================================
#pragma	pack(push,1)
struct HSVValue
{
	WORD	H;	//0-359
	BYTE	S;	//0-255
	BYTE	V;	//0-255
};
#pragma	pack(pop)
//------------------------------------------------------------------------------------
void	HSV2RGB(double h,double s ,double v ,int &R ,int &G ,int &B);
// HSV(HSB)色空間からRGB色空間へ変換する 
//  h(hue)       : 色相/色合い   0-360度の値
//  s(saturation): 彩度/鮮やかさ 0-255の値
//  v(Value)     : 明度/明るさ   0-255の値 
//  ※v は b(Brightness)と同様 


void	RGB2HSV(double &h,double &s ,double &v ,int r ,int g ,int b);
void	RGB2HSV(double &h,double &s ,double &v ,double r ,double g ,double b);
 // RGB色空間からHSV色空間へ変換する 
 //  r(red)  : 赤色 0-255の値
 //  g(green): 緑色 0-255の値
 //  b(blue) : 青色 0-255の値 

void	RGB2XYZ(double R,double G ,double B,double &X ,double &Y ,double &Z);
void	XYZ2RGB(double X ,double Y ,double Z,double &R,double &G ,double &B);

void	LAB2XYZ(double L,double A ,double B,double &X ,double &Y ,double &Z);
void	XYZ2LAB(double X ,double Y ,double Z,double &L,double &A ,double &B);

double	GetDeltaE76	 (double L1 ,double A1 ,double B1 ,double L2 ,double A2 ,double B2);
double	GetDeltaE2000(double L1 ,double A1 ,double B1 ,double L2 ,double A2 ,double B2);

#endif

