#pragma once
#include "XTypeDef.h"
#include "NListComp.h"
#include<QString>
#include<QObject>
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "swap.h"
#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XRegulusWorld.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithmList.h"
#include "XDataComponent.h"

class RegWorldObject;
class RegulusWorld;
class	RW3DInPageRoot;
class	Vector3D;
class	CrossInfo;

class RegWorldObjectContainer : public NPListPackSaveLoad<RegWorldObject>
{
	RegWorldObject	*Parent;
public:
	RegWorldObjectContainer(RegWorldObject *parent);

	virtual	RegWorldObject	*Create(void)	override;
};


class RegWorldObject : public NPListSaveLoad<RegWorldObject>
					  ,public RegWorldObjectContainer
{
	RegulusWorld	*World;
	QString			ObjectName;
	int32			ID;
public:
	RegWorldObject(RegulusWorld *p,int id=-1);
	virtual	~RegWorldObject(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	int		GetID(void)	const	{	return ID;	}
	void	SetID(int id)		{	ID=id;		}

	QString	GetObjectName(void)			const	{	return ObjectName;	}
	void	SetObjectName(const QString &src)	{	ObjectName=src;		}
};

//-------------------------------------------------------------------------------
class	RWMatrix3x3
{
public:
	struct
	{
		float	Param[3][3];	//Param[i][j]=Pij
	}Data;

	RWMatrix3x3(void);
	RWMatrix3x3(const RWMatrix3x3 &src);

	RWMatrix3x3	&operator=(const RWMatrix3x3 &src);
	RWMatrix3x3	&operator=(float d);
	RWMatrix3x3	operator+()	const;
	RWMatrix3x3	operator-()	const;
	RWMatrix3x3	operator+(const RWMatrix3x3 &src)	const;
	RWMatrix3x3	operator-(const RWMatrix3x3 &src)	const;
	RWMatrix3x3	operator*(const RWMatrix3x3 &src)	const;
	RWMatrix3x3	operator*(float m)	const;
	RWMatrix3x3	operator/(float m)	const;
	RWMatrix3x3	&operator+=(const RWMatrix3x3 &src);
	RWMatrix3x3	&operator-=(const RWMatrix3x3 &src);
	RWMatrix3x3	&operator*=(const RWMatrix3x3 &src);
	RWMatrix3x3	&operator*=(float m);
	RWMatrix3x3	&operator/=(float m);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	RWMatrix4x4
{
public:
	struct
	{
		float	Param[4][4];	//Param[i][j]=Pij
	}Data;

	RWMatrix4x4(void);
	RWMatrix4x4(const RWMatrix4x4 &src);

	RWMatrix4x4	&operator=(const RWMatrix4x4 &src);
	RWMatrix4x4	&operator=(float d);
	RWMatrix4x4	operator+()	const;
	RWMatrix4x4	operator-()	const;
	RWMatrix4x4	operator+(const RWMatrix4x4 &src)	const;
	RWMatrix4x4	operator-(const RWMatrix4x4 &src)	const;
	RWMatrix4x4	operator*(const RWMatrix4x4 &src)	const;
	RWMatrix4x4	operator*(float m)	const;
	RWMatrix4x4	operator/(float m)	const;
	RWMatrix4x4	&operator+=(const RWMatrix4x4 &src);
	RWMatrix4x4	&operator-=(const RWMatrix4x4 &src);
	RWMatrix4x4	&operator*=(const RWMatrix4x4 &src);
	RWMatrix4x4	&operator*=(float m);
	RWMatrix4x4	&operator/=(float m);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//-------------------------------------------------------------------------------


class Point3D
{
	struct
	{
		float	X,Y,Z;
	}Data;
public:
	Point3D(void);
	Point3D(const Point3D &src);
	Point3D(float x ,float y, float z);
	virtual~Point3D(void);

	Point3D	&operator=(const Point3D &src);
	Point3D	&operator=(float d);
	Point3D	operator+()	const;
	Point3D	operator-()	const;
	Point3D	operator+(const Point3D &src )	const;
	Point3D	operator+(const Vector3D &src)	const;
	Point3D	operator-(const Point3D &src )	const;
	Point3D	operator-(const Vector3D &src)	const;
	Point3D	operator*(const Point3D &src )	const;
	Point3D	operator*(float m)	const;
	Point3D	operator/(float m)	const;
	Point3D	operator*(RWMatrix4x4 &src)	const;
	Point3D	&operator+=(const Point3D &src);
	Point3D	&operator+=(const Vector3D &src);
	Point3D	&operator-=(const Point3D &src);
	Point3D	&operator-=(const Vector3D &src);
	Point3D	&operator*=(float m);
	Point3D	&operator*=(RWMatrix4x4 &src);
	Point3D	&operator/=(float m);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	float	GetX(void)	const	{	return Data.X;	}
	float	GetY(void)	const	{	return Data.Y;	}
	float	GetZ(void)	const	{	return Data.Z;	}
	void	SetX(float x)		{	Data.X=x;	}
	void	SetY(float y)		{	Data.Y=y;	}
	void	SetZ(float z)		{	Data.Z=z;	}
	void	Set(float x ,float y, float z);
};

inline	Point3D	min(const Point3D &s1 ,const Point3D &s2)
{
	return Point3D(min(s1.GetX(),s2.GetX()),min(s1.GetY(),s2.GetY()),min(s1.GetZ(),s2.GetZ()));
}
inline	Point3D	max(const Point3D &s1 ,const Point3D &s2)
{
	return Point3D(max(s1.GetX(),s2.GetX()),max(s1.GetY(),s2.GetY()),max(s1.GetZ(),s2.GetZ()));
}

class Vector3D
{
	struct
	{
		float	Vx,Vy,Vz;
	}Data;
public:
	Vector3D(void);
	Vector3D(const Vector3D &src);
	Vector3D(float vx ,float vy, float vz);
	virtual~Vector3D(void);

	Vector3D	&operator=(const Vector3D &src);
	Vector3D	&operator=(float d);
	Vector3D	operator+()	const;
	Vector3D	operator-()	const;
	Vector3D	operator+(const Vector3D &src)	const;
	Vector3D	operator-(const Vector3D &src)	const;
	Vector3D	operator*(const Vector3D &src)	const;	//Cross product　外積
	Vector3D	operator*(float m)	const;
	Vector3D	operator*(RWMatrix4x4 &src)	const;
	Vector3D	operator/(float m)	const;
	Vector3D	&operator+=(const Vector3D &src);
	Vector3D	&operator-=(const Vector3D &src);
	Vector3D	&operator*=(float m);
	Vector3D	&operator*=(const Vector3D &src);	//Cross product　外積
	Vector3D	&operator*=(RWMatrix4x4 &src);
	Vector3D	&operator/=(float m);

	float		InnerProduct(const Vector3D &src)	const;
	float		GetAngle(const Vector3D &src)		const;
	float		GetCos(const Vector3D &src)	const;
	float		GetLength(void)	const;
	void		Normalize(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	float	GetVx(void)	const	{	return Data.Vx;	}
	float	GetVy(void)	const	{	return Data.Vy;	}
	float	GetVz(void)	const	{	return Data.Vz;	}
	void	SetVx(float vx)		{	Data.Vx=vx;		}
	void	SetVy(float vy)		{	Data.Vy=vy;		}
	void	SetVz(float vz)		{	Data.Vz=vz;		}
	void	Set(float vx ,float vy, float vz);
};

class PointVector3D
{
public:
	Point3D		Point;
	Vector3D	Vector;
public:
	PointVector3D(void);
	PointVector3D(const PointVector3D &src);
	virtual~PointVector3D(void);

	PointVector3D	&operator=(const PointVector3D &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//-------------------------------------------------------------------------------
class   CameraView
{
public:
	Point3D		Point;
	Vector3D	Radian;
	float		Length	;
	int			ViewXLen;
	int			ViewYLen;
	/*
	* Point=0	Radian=0のとき、(x,y,z)=(Length,0,0)の位置に四角形を立てて置く
	* Radianは、各軸の周りに回転する角度を表す
	*/

	CameraView(void);
	CameraView(const CameraView &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

//-------------------------------------------------------------------------------
class   SurfaceBase
{
public:
	SurfaceBase(void){}

	virtual	int		GetSurfaceID(void)	=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;

	virtual	QColor	GetSurfaceColor(RW3DInPageRoot *Ap
									,const PointVector3D &Line
									,const CrossInfo &Ray)	=0;
	virtual	QColor	GetColor(void)	=0;
};

#define	SurfaceID_Surface3D	0x10001

class   Surface3D :public SurfaceBase
{
public:
	float	Reflection	;		//反射率	0-1.0
	float	Diffusion	;		//拡散率	0-1.0
	float	Transparent	;		//透過率	0-1.0
	float	Refraction	;		//屈折率
	QColor	Color;
	
	Surface3D(void);
	Surface3D(const Surface3D &src);

	Surface3D	&operator=(const Surface3D &src);
	virtual	int		GetSurfaceID(void)	override	{	return SurfaceID_Surface3D;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	QColor	GetSurfaceColor(RW3DInPageRoot *Ap
									,const PointVector3D &Line
									,const CrossInfo &Ray)	override;
	virtual	QColor	GetColor(void)	override	{	return Color;	}
};

//-------------------------------------------------------------------------------

class   CrossInfo
{
public:
	float		CrossT;
	Point3D		Point;
	Vector3D	NormalVector;

	CrossInfo(void);
	CrossInfo(const CrossInfo &src);

	CrossInfo	&operator=(const CrossInfo &src);
};

class   CrossVolume : public NPList<CrossVolume>
{
public:
	CrossInfo	NearSide;
	CrossInfo	FarSide ;

	CrossVolume(void);
	CrossVolume(const CrossVolume &src);

	CrossVolume	&operator=(const CrossVolume &src);

	virtual	int	Compare(CrossVolume &src)	override;
};

class   CrossCluster : public NPListPack<CrossVolume>
{
public:
	SurfaceBase *Surface;

	CrossCluster(void);
	CrossCluster(const CrossCluster &src);

	CrossCluster	&operator=(const CrossCluster &src);

	void	OrBreak		(CrossCluster &src);
	void	NotAndBreak	(CrossCluster &src);
	void	AndBreak	(CrossCluster &src);
	void	XorBreak	(CrossCluster &src);

	void	Bind(void);

	SurfaceBase	*GetSurface(void)	{	return Surface;	}
};

//-------------------------------------------------------------------------------

class   RWShapeBase : public NPList<RWShapeBase>
{
	SurfaceBase			*Surface;
	QString				Name;
public:
	enum OperateConnection
	{
		 OC_Or		=1	//Addition
		,OC_NotAnd	=2	//Subtract
		,OC_And		=3
		,OC_Xor		=4
	}OC;
	int32		Version;

	RWShapeBase(void);

	virtual	RWShapeBase	*Clone(void)	=0;
	virtual	int		GetShapeID(void)	=0;
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	
	void	Copy(RWShapeBase &src);
	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	=0;

	void	SetSurface(SurfaceBase *s)		{	Surface=s;		}
	SurfaceBase	*GetSurface(void)	const	{	return Surface;	}

	virtual	void	SetName(const QString &name)	{	Name=name;		}
	virtual	const QString	&GetName(void)			{	return Name;	}

	virtual	void	SetVersion(int32 d)	{	Version=d;		}
	virtual	int32	GetVersion(void)	{	return Version;	}

	void	SetOperation(OperateConnection oc)		{	OC=oc;		}
	OperateConnection	GetOperation(void)	const	{	return OC;	}

	virtual	bool	GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)	=0;
};

class   RWShapeBaseContainer : public NPListPack<RWShapeBase>
{
public:
	RWShapeBaseContainer(void);
	RWShapeBaseContainer(const RWShapeBaseContainer &src);

	RWShapeBaseContainer	&operator=(const RWShapeBaseContainer &src);
	RWShapeBase		*Create(int d);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint);
	virtual	bool	GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides);
};

#define	ShapeID_Shere		1
#define	ShapeID_RectPlain	2
#define	ShapeID_Box			3
#define	ShapeID_Composite	4

class   RWShapeSphere : public RWShapeBase
{
public:
	Point3D		Point;
	Vector3D	Radius;		

	RWShapeSphere(void);

	virtual	RWShapeBase	*Clone(void)	override;
	virtual	int		GetShapeID(void)	override	{	return ShapeID_Shere;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	override;
	virtual	bool	GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)	override;
};

class   RWShapeRectPlain : public RWShapeBase
{
public:
	Point3D		Point;
	Vector3D	Edge1;
	Vector3D	Edge2;

	RWShapeRectPlain(void);

	virtual	RWShapeBase	*Clone(void)	override;
	virtual	int		GetShapeID(void)	override	{	return ShapeID_RectPlain;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	override;
	virtual	bool	GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)	override;
};
class   RWShapeBox : public RWShapeBase
{
public:
	Point3D		Point;
	Vector3D	Edge[3];

	RWShapeBox(void);

	virtual	RWShapeBase	*Clone(void)	override;
	virtual	int		GetShapeID(void)	override	{	return ShapeID_Box;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	override;
	virtual	bool	GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)	override;
};

class   RWShapeComposite: public RWShapeBase
{
public:
	RWShapeBaseContainer	Items;

	RWShapeComposite(void);

	virtual	RWShapeBase	*Clone(void)	override;
	virtual	int		GetShapeID(void)	override	{	return ShapeID_Composite;	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	GetArea(Point3D &MinPoint ,Point3D &MaxPoint)	override;
	virtual	bool	GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)	override;
};

//-------------------------------------------------------------------------------
