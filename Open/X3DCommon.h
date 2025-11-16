#pragma once

#include <QIODevice>
#include <QColor>
#include "XTypeDef.h"

class	Vector3D;
class	Point3D;
class	Box3D;
class	VectorLine;
class	FlatPlain3D;

class	UVector3D
{
public:
	struct{
		double	Ux,Uy,Uz;	//Length=1
	}Data;

	UVector3D(void){}
	UVector3D(double ux,double uy,double uz);
	UVector3D(const UVector3D &src);
	UVector3D(const Vector3D &src);

	UVector3D &operator=(const UVector3D &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	UVector3D	operator-()		const;
	Vector3D	operator+(const Vector3D &s)	const;
	Vector3D	operator-(const Vector3D &s)	const;
	double		operator*(const Vector3D &s)	const;
	Vector3D	operator+(const UVector3D &s)	const;
	Vector3D	operator-(const UVector3D &s)	const;
	double		operator*(const UVector3D &s)	const;
	Vector3D	operator*(double L)		const;
	Vector3D	operator/(double L)		const;

	bool	operator==(const UVector3D &src)	const;
};

class	Vector3D
{
public:
	struct{
		double	Vx,Vy,Vz;
	}Data;

	Vector3D(void){}
	Vector3D(double vx,double vy,double vz);
	Vector3D(const Vector3D &src);
	Vector3D(const UVector3D &src);

	Vector3D &operator=(const Vector3D &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	double	GetLength(void)		const;
	UVector3D	GetUnit(void)	const;

	Vector3D	operator-();
	Vector3D	operator+(const Vector3D &s)	const;
	Vector3D	operator-(const Vector3D &s)	const;
	double		operator*(const Vector3D &s)	const;
	Vector3D	operator+(const UVector3D &s)	const;
	Vector3D	operator-(const UVector3D &s)	const;
	double		operator*(const UVector3D &s)	const;
	Vector3D	operator*(double L)	const;
	Vector3D	operator/(double L)	const;
	Vector3D	&operator+=(const Vector3D &s);
	Vector3D	&operator-=(const Vector3D &s);
	Vector3D	&operator+=(const UVector3D &s);
	Vector3D	&operator-=(const UVector3D &s);
	Vector3D	&operator*=(double L);
	Vector3D	&operator/=(double L);

	static	Vector3D	CrossProduct(const Vector3D &a,const Vector3D &b);

	bool	operator==(const Vector3D &src)	const;
};

class	Point3D
{
public:
	struct{
		double	X,Y,Z;
	}Data;

	Point3D(void){}
	Point3D(double x,double y,double z);
	Point3D(const Point3D &src);

	Point3D &operator=(const Point3D &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	Point3D		operator+(const Vector3D &s)	const;
	Point3D		operator-(const Vector3D &s)	const;
	Vector3D	operator-(const Point3D &s)		const;
	Point3D		&operator+=(const Vector3D &s);
	Point3D		&operator-=(const Vector3D &s);

	bool	operator==(const Point3D &src)	const;
};


class	Angle3D
{
public:
	struct{
		double	Rx,Ry,Rs;
	}Data;

	Angle3D(void){}
	Angle3D(double rx,double ry,double rs);
	Angle3D(const Angle3D &src);

	Angle3D &operator=(const Angle3D &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	Angle3D		operator+(const Angle3D &s)	const;
	Angle3D		operator-(const Angle3D &s)	const;
	Angle3D		&operator+=(const Angle3D &s);
	Angle3D		&operator-=(const Angle3D &s);

	bool	operator==(const Angle3D &src)	const;
};

class	Box3D
{
public:
	struct{
		double	X1,Y1,Z1;
		double	X2,Y2,Z2;
	}Data;

	Box3D(void){}
	Box3D(double x1,double y1,double z1,double x2,double y2,double z2);
	Box3D(const Box3D &src);

	Box3D &operator=(const Box3D &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	Box3D	operator*(double v)	const;
	Box3D	operator/(double v)	const;
	Box3D	operator+(const Vector3D &s)	const;
	Box3D	operator-(const Vector3D &s)	const;
	Box3D	&operator+=(const Vector3D &s);
	Box3D	&operator-=(const Vector3D &s);
	Box3D	&operator*=(double v);
	Box3D	&operator/=(double v);

	bool	operator==(const Box3D &src)	const;

	bool	GetCross(const VectorLine &s ,double &RetLineRate)	const;
};

class VectorLine
{
public:
	Point3D		Point;
	UVector3D	Vector;

	VectorLine(void){}
	VectorLine(const Point3D &P ,const UVector3D &V)
		:Point(P),Vector(V){}
	VectorLine(const VectorLine &src);

	VectorLine	&operator=(const VectorLine &src);
	bool	operator==(const VectorLine &src)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class FlatPlain3D
{
public:
	Point3D		Point;
	UVector3D	Sx;
	UVector3D	Sy;

	FlatPlain3D(void){}
	FlatPlain3D(const Point3D &P,const UVector3D &sx,const UVector3D &sy)
		:Point(P),Sx(sx),Sy(sy){}
	FlatPlain3D(const FlatPlain3D &src);

	FlatPlain3D	&operator=(const FlatPlain3D &src);

	bool	GetCross(const VectorLine &L
					,double &RetLineParam
					,double &RetPlainParamX
					,double &RetPlainParamY)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



//==================================================================

class	Canvas3D
{
public:
	enum _EyeType
	{
		_Centerize	=0
		,_Parallel	=1
	};

	struct Canvas3DStruct
	{
		int32		CanvasWidth,CanvasHeight;
		Point3D		CanvasOrigin;
		Vector3D	CanvasXAxis,CanvasYAxis;
		_EyeType	EyeType;
	}Data;

	Canvas3D(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	GetMovXY(double &Mx ,double &My)	const;
	void	GetZoomRate(double &Zx,double &Zy)	const;
};


class	Reflection3D
{
public:
	struct Reflection3DStruct
	{
		QRgb	SurfaceColor;
		double	DiffusionRate;		//0.0 - 1.0
		double	TransparentRate;	//0.0 - 1.0
		double	Refractive;
		QRgb	TransparentColor;
	}Data;

	Reflection3D(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class Surface3D
{
public:
	Point3D		Point;
	UVector3D	ForCamVector;
	UVector3D	Sx;
	UVector3D	Sy;

	Surface3D(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

