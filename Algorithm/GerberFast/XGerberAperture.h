#if	!defined(XGerberAperture_H)
#define	XGerberAperture_H


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

class   GerberFastItemBase;
class	GerberDCodeContainer;
class	OutlineAreaContainer;
class	OutlineArea;
class	SparsShape;

struct	ApertureInfo
{
	int32	ApertureNumber;
	BYTE	ApertureType;
	double	Data1;
	double	Data2;
	double	Data3;
};

class	ApertureHole
{
public:
	enum	__HoleType
	{
		_ApertureHole_None			=0
		,_ApertureHole_Circle		=1
		,_ApertureHole_Rectangle	=2
	}HoleType;
	double	HSize,WSize;

	ApertureHole(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	double	GetWidth(void)		{	return HSize;	}
	virtual	double	GetHeight(void)		{	return WSize;	}

	ApertureHole	&operator=(ApertureHole &src);
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
						,const QRgb &Col,double Angle);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle
							,bool PosiImage);
};



class	GerberDCodeBase : public NPList<GerberDCodeBase>
{
public:
	int32			DCode;
	ApertureHole	Hole;
	AlgorithmItemPointerListContainer	ItemPointerList;
	GerberDCodeContainer	*Parent;

	GerberDCodeBase(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	int32	GetDCode(void)	{	return DCode;	}
	virtual	int32		GetItemClassType(void)	=0;

	void	SetParent(GerberDCodeContainer *parent){	Parent=parent;	}

	virtual	double	GetWidth(void)			=0;
	virtual	double	GetHeight(void)			=0;
	virtual	void	SetWidth(double w)		=0;
	virtual	void	SetHeight(double h)		=0;

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage)=0;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,BYTE **Image ,int XByte ,int YLen
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)=0;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)=0;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)=0;

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info)=0;
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info)=0;
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	=0;
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture)	=0;

	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)=0;
};


class	GerberDCodeCircle : public GerberDCodeBase
{
public:
	double		HSize,WSize;

	GerberDCodeCircle(GerberDCodeContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	int32	GetItemClassType(void)		{		return 1;		}

	virtual	double	GetWidth(void)		{	return WSize;	}
	virtual	double	GetHeight(void)		{	return HSize;	}
	virtual	void	SetWidth(double w)	{	WSize=w;		}
	virtual	void	SetHeight(double h)	{	HSize=h;		}

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture);

	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);

private:
	void	MakeHairline(double Angle ,double &x1,double &y1,double &x2,double &y2, double HairlineLength ,double Radius);

};

class	GerberDCodeRectangle : public GerberDCodeBase
{
public:
	double		HSize,WSize;

	GerberDCodeRectangle(GerberDCodeContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	int32	GetItemClassType(void)		{		return 2;		}

	virtual	double	GetWidth(void)		{	return WSize;	}
	virtual	double	GetHeight(void)		{	return HSize;	}
	virtual	void	SetWidth(double w)	{	WSize=w;		}
	virtual	void	SetHeight(double h)	{	HSize=h;		}

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);
private:
	void	MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
						,OutlineArea &TransArea,double Isolation ,double HairlineLength);

};

class	GerberDCodeRectRCorner : public GerberDCodeBase		//For ODB++
{
public:
	double		HSize,WSize;
	double		Radius;
	struct __Attr{
		bool		Rounded:1;
		bool		TopRight:1;
		bool		TopLeft:1;
		bool		BottomLeft:1;
		bool		BottomRight:1;
	}Attr;

	GerberDCodeRectRCorner(GerberDCodeContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	int32	GetItemClassType(void)		{		return 12;		}

	virtual	double	GetWidth(void)		{	return WSize;	}
	virtual	double	GetHeight(void)		{	return HSize;	}
	virtual	void	SetWidth(double w)	{	WSize=w;		}
	virtual	void	SetHeight(double h)	{	HSize=h;		}

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY);
	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);
private:
	void	MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
						,OutlineArea &TransArea,double Isolation ,double HairlineLength);
};

class	GerberDCodeObround : public GerberDCodeBase
{
public:
	double		HSize,WSize;

	GerberDCodeObround(GerberDCodeContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	int32	GetItemClassType(void)		{		return 3;		}

	virtual	double	GetWidth(void)		{	return WSize;	}
	virtual	double	GetHeight(void)		{	return HSize;	}
	virtual	void	SetWidth(double w)	{	WSize=w;		}
	virtual	void	SetHeight(double h)	{	HSize=h;		}

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);
private:
	void	MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
						,OutlineArea &TransArea,double Isolation ,double HairlineLength);
	void	MakeHairline(double Angle ,double &x1,double &y1,double &x2,double &y2, double HairlineLength ,double Radius);
};

class	GerberDCodePolygon : public GerberDCodeBase
{
public:
	double		Diameter;
	int			Sides;

	GerberDCodePolygon(GerberDCodeContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	int32	GetItemClassType(void)		{		return 4;		}

	virtual	double	GetWidth(void);
	virtual	double	GetHeight(void);
	virtual	void	SetWidth(double w);
	virtual	void	SetHeight(double h);

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);
private:
	void	MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
						,OutlineArea &TransArea,double Isolation ,double HairlineLength);

};

class	GerberDCodeMacro : public GerberDCodeBase
{
public:
	GerberApertureMacro	*Macro;
	DoubleList			Param;
	InstGerberAperturePrimitiveContainer	InstMacro;

	GerberDCodeMacro(GerberDCodeContainer *parent);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	int32	GetItemClassType(void)		{		return 5;		}

	virtual	double	GetWidth(void);
	virtual	double	GetHeight(void)	;
	virtual	void	SetWidth(double w);
	virtual	void	SetHeight(double h);

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,SparsShape &OutlineShape
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	bool	IsCrossed(FlexArea *b
							, double PosX,double PosY,	double Angle,double ZoomAperture);
	virtual	double	GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);
};

class	GerberDCodeContainer : public NPListPack<GerberDCodeBase>
{
public:
	NPListPack<GerberApertureMacro>	Macros;

	GerberDCodeContainer(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	LoadWithoutClear(QIODevice *f);

	GerberDCodeContainer	&operator=(GerberDCodeContainer &src);
	GerberDCodeContainer	&operator+=(GerberDCodeContainer &src);

	GerberDCodeBase		*FindDCode(int dcode);
	GerberApertureMacro	*FindMacro(const QString &MacroName);

	static	QString	GetApertureName(int ApertureClassID);
};

#endif