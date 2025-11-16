#if	!defined(XGerberApertureMacro_H)
#define	XGerberApertureMacro_H

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "NListComp.h"
#include <QString>

class	InstGerberAperturePrimitiveBase;
class	InstGerberAperturePrimitiveContainer;
class	OutlineArea;
class	GerberDCodeMacro;
class	ApertureHole;

class	MacroGerberAperturePrimitiveBase : public NPList<MacroGerberAperturePrimitiveBase>
{
protected:
	double	Unit;
public:
	MacroGerberAperturePrimitiveBase(void){}

	virtual	int	GetClassID(void)=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	=0;
	virtual	bool	SetParam(QStringList &Param ,double Unit)=0;
	double	MakeValue(QString &Str ,DoubleList &Param);
};

class	InstGerberAperturePrimitiveBase : public NPList<InstGerberAperturePrimitiveBase>
{
public:
	virtual	int	GetClassID(void)=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;	

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	=0;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	=0;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	=0;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	=0;
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)=0;
};

//=====================================================================================

class	MacroGerberAperturePrimitiveCircle : public MacroGerberAperturePrimitiveBase
{
public:
	QString	Exposure;
	QString	Diameter;
	QString	CenterX;
	QString	CenterY;

	MacroGerberAperturePrimitiveCircle(void){}

	virtual	int	GetClassID(void){	return 1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);	

	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param);
	virtual	bool	SetParam(QStringList &Param ,double Unit);
};
class	InstGerberAperturePrimitiveCircle : public InstGerberAperturePrimitiveBase
{
public:
	int		Exposure;
	double	Diameter;
	double	CenterX;
	double	CenterY;

	InstGerberAperturePrimitiveCircle(void){}

	virtual	int	GetClassID(void)	override	{	return 1;	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;	

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

class	MacroGerberAperturePrimitiveLineVector : public MacroGerberAperturePrimitiveBase
{
public:
	QString	Exposure;
	QString	LineWidth;
	QString	StartX;
	QString	StartY;
	QString	EndX;
	QString	EndY;
	QString	Rotation;

	MacroGerberAperturePrimitiveLineVector(void){}

	virtual	int	GetClassID(void)		override	{	return 2;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;
};

class	InstGerberAperturePrimitiveLineVector : public InstGerberAperturePrimitiveBase
{
public:
	int		Exposure;
	double	LineWidth;
	double	StartX;
	double	StartY;
	double	EndX;
	double	EndY;
	double	Rotation;

	InstGerberAperturePrimitiveLineVector(void){}

	virtual	int	GetClassID(void)		override{	return 2;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

class	MacroGerberAperturePrimitiveLineCenter : public MacroGerberAperturePrimitiveBase
{
public:
	QString	Exposure;
	QString	Width;
	QString	Height;
	QString	CenterX;
	QString	CenterY;
	QString	Rotation;

	MacroGerberAperturePrimitiveLineCenter(void){}

	virtual	int	GetClassID(void)		override{	return 21;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;
};

class	InstGerberAperturePrimitiveLineCenter : public InstGerberAperturePrimitiveBase
{
public:
	int		Exposure;
	double	Width;
	double	Height;
	double	CenterX;
	double	CenterY;
	double	Rotation;

	InstGerberAperturePrimitiveLineCenter(void){}

	virtual	int	GetClassID(void)		override{	return 21;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

class	MacroGerberAperturePrimitiveLineLowerLeft : public MacroGerberAperturePrimitiveBase
{
public:
	QString	Exposure;
	QString	Width;
	QString	Height;
	QString	StartX;
	QString	StartY;
	QString	Rotation;

	MacroGerberAperturePrimitiveLineLowerLeft(void){}

	virtual	int	GetClassID(void)		override{	return 22;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;

};

class	InstGerberAperturePrimitiveLineLowerLeft : public InstGerberAperturePrimitiveBase
{
public:
	int		Exposure;
	double	Width;
	double	Height;
	double	StartX;
	double	StartY;
	double	Rotation;

	InstGerberAperturePrimitiveLineLowerLeft(void){}

	virtual	int	GetClassID(void)		override{	return 22;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

#define	PointCount_MacroGerberAperturePrimitiveOutline	500
class	MacroGerberAperturePrimitiveOutline : public MacroGerberAperturePrimitiveBase
{
public:
	QString	Exposure;
	QString	Count;
	QString	PointX[PointCount_MacroGerberAperturePrimitiveOutline];
	QString	PointY[PointCount_MacroGerberAperturePrimitiveOutline];
	QString	Rotation;

	MacroGerberAperturePrimitiveOutline(void){}

	virtual	int	GetClassID(void)		override{	return 4;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;
};

class	InstGerberAperturePrimitiveOutline : public InstGerberAperturePrimitiveBase
{
public:
	int		Exposure;
	int		Count;
	double	PointX[PointCount_MacroGerberAperturePrimitiveOutline];
	double	PointY[PointCount_MacroGerberAperturePrimitiveOutline];
	double	Rotation;

	InstGerberAperturePrimitiveOutline(void){}

	
	virtual	int	GetClassID(void)		override{	return 4;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

class	MacroGerberAperturePrimitivePolygon : public MacroGerberAperturePrimitiveBase
{
public:
	QString	Exposure;
	QString	Count;
	QString	CenterX;
	QString	CenterY;
	QString	Diameter;
	QString	Rotation;

	MacroGerberAperturePrimitivePolygon(void){}

	virtual	int	GetClassID(void)		override{	return 5;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;
};

class	InstGerberAperturePrimitivePolygon : public InstGerberAperturePrimitiveBase
{
public:
	int		Exposure;
	int		Count;
	double	CenterX;
	double	CenterY;
	double	Diameter;
	double	Rotation;

	InstGerberAperturePrimitivePolygon(void){}

	virtual	int	GetClassID(void)		override{	return 5;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

class	MacroGerberAperturePrimitiveMoire : public MacroGerberAperturePrimitiveBase
{
public:
	QString	CenterX;
	QString	CenterY;
	QString	Diameter;
	QString	LineWidth;
	QString	LineIsolation;
	QString	LineCount;
	QString	CrossLineWidth;
	QString	CrossLineLength;
	QString	Rotation;

	MacroGerberAperturePrimitiveMoire(void){}

	virtual	int	GetClassID(void)		override{	return 6;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;
};

class	InstGerberAperturePrimitiveMoire : public InstGerberAperturePrimitiveBase
{
public:
	double	CenterX;
	double	CenterY;
	double	Diameter;
	double	LineWidth;
	double	LineIsolation;
	int		LineCount;
	double	CrossLineWidth;
	double	CrossLineLength;
	double	Rotation;

	InstGerberAperturePrimitiveMoire(void){}

	virtual	int	GetClassID(void)		override{	return 6;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

class	MacroGerberAperturePrimitiveThermal : public MacroGerberAperturePrimitiveBase
{
public:
	QString	CenterX;
	QString	CenterY;
	QString	DiameterOut;
	QString	DiameterIn;
	QString	CrossLineWidth;
	QString	Rotation;

	MacroGerberAperturePrimitiveThermal(void){}

	virtual	int	GetClassID(void)		override{	return 7;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	InstGerberAperturePrimitiveBase	*MakeInst(DoubleList &Param)	override;
	virtual	bool	SetParam(QStringList &Param ,double Unit)	override;
};

class	InstGerberAperturePrimitiveThermal : public InstGerberAperturePrimitiveBase
{
public:
	double	CenterX;
	double	CenterY;
	double	DiameterOut;
	double	DiameterIn;
	double	CrossLineWidth;
	double	Rotation;

	InstGerberAperturePrimitiveThermal(void){}

	virtual	int	GetClassID(void)		override{	return 7;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)	override;
	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)	override;
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)	override;
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)	override{}

	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)	override;
};

//-------------------------------------------------------------------------

class	MacroGerberAperturePrimitiveContainer : public NPListPack<MacroGerberAperturePrimitiveBase>
{
public:
	MacroGerberAperturePrimitiveContainer(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	Make(InstGerberAperturePrimitiveContainer &RetContainer , DoubleList &Param);
	bool	LoadFromGerber(char Buff[] ,double Unit);
};

class	InstGerberAperturePrimitiveContainer : public NPListPack<InstGerberAperturePrimitiveBase>
{
public:
	InstGerberAperturePrimitiveContainer(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);	

	virtual	double	GetWidth(void);
	virtual	double	GetHeight(void)	;
	virtual	void	SetWidth(double w);
	virtual	void	SetHeight(double h);

	virtual	void	Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole);
	virtual	void	MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole);
	virtual	void	MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage);

	virtual	void	MakeApertureInfo(struct	ApertureInfo &Info);
	virtual	void	SetApertureInfo(struct	ApertureInfo &Info);
	virtual	bool	IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture);
};



class	GerberApertureMacro: public NPList<GerberApertureMacro>
{
public:
	QString	MacroName;
	MacroGerberAperturePrimitiveContainer	Primitives;
	
	GerberApertureMacro(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	LoadFromGerber(char Buff[] ,double Unit);
};



#endif