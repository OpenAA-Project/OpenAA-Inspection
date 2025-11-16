#include "XRegulusWorld.h"
#include "XGeneralFunc.h"
#include "XRegulusWorldObject.h"

RegWorldObject::RegWorldObject(RegulusWorld *p,int id)
	:RegWorldObjectContainer(this)
{
	World=p;
	ID=id;
}
RegWorldObject::~RegWorldObject(void)
{
}
bool	RegWorldObject::Save(QIODevice *f)
{
	if(::Save(f,ID			)==false)	return false;
	if(::Save(f,ObjectName	)==false)	return false;
	return true;
}
bool	RegWorldObject::Load(QIODevice *f)
{
	if(::Load(f,ID			)==false)	return false;
	if(::Load(f,ObjectName	)==false)	return false;
	return true;
}

RegWorldObjectContainer::RegWorldObjectContainer(RegWorldObject *parent)
	:Parent(parent)
{}
RegWorldObject	*RegWorldObjectContainer::Create(void)
{
	return new RegWorldObject(nullptr);
}

//==================================================================================================

//===========================================================================================
RWMatrix3x3::RWMatrix3x3(void)
{}
RWMatrix3x3::RWMatrix3x3(const RWMatrix3x3 &src)
{
	Data=src.Data;
}

RWMatrix3x3	&RWMatrix3x3::operator=(const RWMatrix3x3 &src)
{
	Data=src.Data;
	return *this;
}
RWMatrix3x3	&RWMatrix3x3::operator=(float d)
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Data.Param[i][j]=d;
		}
	}
	return *this;
}
RWMatrix3x3	RWMatrix3x3::operator+()	const
{
	return *this;
}
RWMatrix3x3	RWMatrix3x3::operator-()	const
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=-Data.Param[i][j];
		}
	}
	return Ret;
}
RWMatrix3x3	RWMatrix3x3::operator+(const RWMatrix3x3 &src)	const
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]+src.Data.Param[i][j];
		}
	}
	return Ret;
}
RWMatrix3x3	RWMatrix3x3::operator-(const RWMatrix3x3 &src)	const
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]-src.Data.Param[i][j];
		}
	}
	return Ret;
}
RWMatrix3x3	RWMatrix3x3::operator*(const RWMatrix3x3 &src)	const
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=0;
			for(int ip=0;ip<3;ip++){
				for(int jp=0;jp<3;jp++){
					Ret.Data.Param[i][j]+=Data.Param[ip][j]*src.Data.Param[i][jp];
				}
			}
		}
	}
	return Ret;
}
RWMatrix3x3	RWMatrix3x3::operator*(float m)	const
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]*m;
		}
	}
	return Ret;
}
RWMatrix3x3	RWMatrix3x3::operator/(float m)	const
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]/m;
		}
	}
	return Ret;
}
RWMatrix3x3	&RWMatrix3x3::operator+=(const RWMatrix3x3 &src)
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Data.Param[i][j]+=src.Data.Param[i][j];
		}
	}
	return *this;
}
RWMatrix3x3	&RWMatrix3x3::operator-=(const RWMatrix3x3 &src)
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Data.Param[i][j]-=src.Data.Param[i][j];
		}
	}
	return *this;
}
RWMatrix3x3	&RWMatrix3x3::operator*=(float m)
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Data.Param[i][j]*=m;
		}
	}
	return *this;
}
RWMatrix3x3	&RWMatrix3x3::operator/=(float m)
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Data.Param[i][j]/=m;
		}
	}
	return *this;
}
RWMatrix3x3	&RWMatrix3x3::operator*=(const RWMatrix3x3 &src)
{
	RWMatrix3x3	Ret;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Ret.Data.Param[i][j]=0;
			for(int ip=0;ip<3;ip++){
				for(int jp=0;jp<3;jp++){
					Ret.Data.Param[i][j]+=Data.Param[ip][j]*src.Data.Param[i][jp];
				}
			}
		}
	}
	Data=Ret.Data;

	return *this;
}
bool	RWMatrix3x3::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}
bool	RWMatrix3x3::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}


//===========================================================================================
RWMatrix4x4::RWMatrix4x4(void)
{}
RWMatrix4x4::RWMatrix4x4(const RWMatrix4x4 &src)
{
	Data=src.Data;
}

RWMatrix4x4	&RWMatrix4x4::operator=(const RWMatrix4x4 &src)
{
	Data=src.Data;
	return *this;
}
RWMatrix4x4	&RWMatrix4x4::operator=(float d)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Data.Param[i][j]=d;
		}
	}
	return *this;
}
RWMatrix4x4	RWMatrix4x4::operator+()	const
{
	return *this;
}
RWMatrix4x4	RWMatrix4x4::operator-()	const
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=-Data.Param[i][j];
		}
	}
	return Ret;
}
RWMatrix4x4	RWMatrix4x4::operator+(const RWMatrix4x4 &src)	const
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]+src.Data.Param[i][j];
		}
	}
	return Ret;
}
RWMatrix4x4	RWMatrix4x4::operator-(const RWMatrix4x4 &src)	const
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]-src.Data.Param[i][j];
		}
	}
	return Ret;
}
RWMatrix4x4	RWMatrix4x4::operator*(const RWMatrix4x4 &src)	const
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=0;
			for(int ip=0;ip<4;ip++){
				for(int jp=0;jp<4;jp++){
					Ret.Data.Param[i][j]+=Data.Param[ip][j]*src.Data.Param[i][jp];
				}
			}
		}
	}
	return Ret;
}
RWMatrix4x4	RWMatrix4x4::operator*(float m)	const
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]*m;
		}
	}
	return Ret;
}
RWMatrix4x4	RWMatrix4x4::operator/(float m)	const
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=Data.Param[i][j]/m;
		}
	}
	return Ret;
}
RWMatrix4x4	&RWMatrix4x4::operator+=(const RWMatrix4x4 &src)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Data.Param[i][j]+=src.Data.Param[i][j];
		}
	}
	return *this;
}
RWMatrix4x4	&RWMatrix4x4::operator-=(const RWMatrix4x4 &src)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Data.Param[i][j]-=src.Data.Param[i][j];
		}
	}
	return *this;
}
RWMatrix4x4	&RWMatrix4x4::operator*=(float m)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Data.Param[i][j]*=m;
		}
	}
	return *this;
}
RWMatrix4x4	&RWMatrix4x4::operator/=(float m)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Data.Param[i][j]/=m;
		}
	}
	return *this;
}
RWMatrix4x4	&RWMatrix4x4::operator*=(const RWMatrix4x4 &src)
{
	RWMatrix4x4	Ret;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Ret.Data.Param[i][j]=0;
			for(int ip=0;ip<4;ip++){
				for(int jp=0;jp<4;jp++){
					Ret.Data.Param[i][j]+=Data.Param[ip][j]*src.Data.Param[i][jp];
				}
			}
		}
	}
	Data=Ret.Data;

	return *this;
}
bool	RWMatrix4x4::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}
bool	RWMatrix4x4::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}

//===========================================================================================
CameraView::CameraView(void)
{
	Point	=0;
	Radian	=0;
	Length		=0;
	ViewXLen	=0;
	ViewYLen	=0;
}
CameraView::CameraView(const CameraView &src)
{
	Point	=src.Point		;
	Radian	=src.Radian		;
	Length	=src.Length		;
	ViewXLen=src.ViewXLen	;
	ViewYLen=src.ViewYLen	;
}

bool	CameraView::Save(QIODevice *f)
{
	if(Point.Save(f)==false)		return false;
	if(Radian.Save(f)==false)		return false;
	if(::Save(f,Length)==false)		return false;
	if(::Save(f,ViewXLen)==false)	return false;
	if(::Save(f,ViewYLen)==false)	return false;
	return true;
}
bool	CameraView::Load(QIODevice *f)
{
	if(Point.Load(f)==false)		return false;
	if(Radian.Load(f)==false)		return false;
	if(::Load(f,Length)==false)		return false;
	if(::Load(f,ViewXLen)==false)	return false;
	if(::Load(f,ViewYLen)==false)	return false;
	return true;
}
//===========================================================================================
Surface3D::Surface3D(void)
{
	Reflection	=0.5;
	Diffusion	=0.5;
	Transparent	=0;
	Refraction	=0;
	Color		=Qt::gray;
}
Surface3D::Surface3D(const Surface3D &src)
{
	Reflection	=src.Reflection	;
	Diffusion	=src.Diffusion	;
	Transparent	=src.Transparent;	
	Refraction	=src.Refraction	;
}
Surface3D	&Surface3D::operator=(const Surface3D &src)
{
	Reflection	=src.Reflection	;
	Diffusion	=src.Diffusion	;
	Transparent	=src.Transparent;	
	Refraction	=src.Refraction	;
	Color		=src.Color;
	return *this;
}
bool	Surface3D::Save(QIODevice *f)
{
	if(::Save(f,Reflection	)==false)	return false;
	if(::Save(f,Diffusion	)==false)	return false;
	if(::Save(f,Transparent	)==false)	return false;
	if(::Save(f,Refraction	)==false)	return false;
	if(::Save(f,Color		)==false)	return false;
	return true;
}
bool	Surface3D::Load(QIODevice *f)
{
	if(::Load(f,Reflection	)==false)	return false;
	if(::Load(f,Diffusion	)==false)	return false;
	if(::Load(f,Transparent	)==false)	return false;
	if(::Load(f,Refraction	)==false)	return false;
	if(::Load(f,Color		)==false)	return false;
	return true;
}


QColor	Surface3D::GetSurfaceColor(RW3DInPageRoot *Ap
									,const PointVector3D &Line
									,const CrossInfo &Ray)
{
	float	C=Line.Vector.GetCos(Ray.NormalVector);
	PointVector3D	ReclectionRay;
	ReclectionRay.Point=Ray.Point;
	Vector3D	N=Ray.NormalVector;
	N.Normalize();
	ReclectionRay.Vector=-Line.Vector+N*(2.0*Line.Vector.InnerProduct(N));
	QColor	RColor=Ap->GetSurfaceColor(ReclectionRay);

	QColor	Ret;

	Ret.setRed	(Color.red()  *(C*(1.0-Reflection))+(RColor.red()  *((1.0-C)*Reflection)));
	Ret.setGreen(Color.green()*(C*(1.0-Reflection))+(RColor.green()*((1.0-C)*Reflection)));
	Ret.setBlue	(Color.blue() *(C*(1.0-Reflection))+(RColor.blue() *((1.0-C)*Reflection)));

	return Ret;
}

//===========================================================================================
Point3D::Point3D(void)
{}
Point3D::Point3D(const Point3D &src)
{
	Data=src.Data;
}
Point3D::Point3D(float x ,float y, float z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}
Point3D::~Point3D(void)
{
}

Point3D	&Point3D::operator=(const Point3D &src)
{
	Data=src.Data;
	return *this;
}
Point3D	&Point3D::operator=(float d)
{
	SetX(d);
	SetY(d);
	SetZ(d);
	return *this;
}
Point3D	Point3D::operator+()	const
{
	return *this;
}
Point3D	Point3D::operator-()	const
{
	Point3D	Ret(-GetX(),-GetY(),-GetZ());
	return Ret;
}

Point3D	Point3D::operator+(const Point3D &src)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()+src.GetX());
	Ret.SetY(GetY()+src.GetY());
	Ret.SetZ(GetZ()+src.GetZ());
	return Ret;
}
Point3D	Point3D::operator+(const Vector3D &src)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()+src.GetVx());
	Ret.SetY(GetY()+src.GetVy());
	Ret.SetZ(GetZ()+src.GetVz());
	return Ret;
}
Point3D	Point3D::operator-(const Point3D &src)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()-src.GetX());
	Ret.SetY(GetY()-src.GetY());
	Ret.SetZ(GetZ()-src.GetZ());
	return Ret;
}
Point3D	Point3D::operator-(const Vector3D &src)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()-src.GetVx());
	Ret.SetY(GetY()-src.GetVy());
	Ret.SetZ(GetZ()-src.GetVz());
	return Ret;
}
Point3D	Point3D::operator*(const Point3D &src)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()*src.GetX());
	Ret.SetY(GetY()*src.GetY());
	Ret.SetZ(GetZ()*src.GetZ());
	return Ret;
}
Point3D	Point3D::operator*(float m)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()*m);
	Ret.SetY(GetY()*m);
	Ret.SetZ(GetZ()*m);
	return Ret;
}
Point3D	Point3D::operator*(RWMatrix4x4 &src)	const
{
	Point3D	Ret;
	Ret.Data.X=  Data.X*src.Data.Param[0][0]
				+Data.Y*src.Data.Param[0][1]
				+Data.Z*src.Data.Param[0][2]
				+		src.Data.Param[0][3];

	Ret.Data.Y=  Data.X*src.Data.Param[1][0]
				+Data.Y*src.Data.Param[1][1]
				+Data.Z*src.Data.Param[1][2]
				+		src.Data.Param[1][3];

	Ret.Data.Z=  Data.X*src.Data.Param[2][0]
				+Data.Y*src.Data.Param[2][1]
				+Data.Z*src.Data.Param[2][2]
				+		src.Data.Param[2][3];
	return Ret;
}

Point3D	Point3D::operator/(float m)	const
{
	Point3D	Ret;
	Ret.SetX(GetX()/m);
	Ret.SetY(GetY()/m);
	Ret.SetZ(GetZ()/m);
	return Ret;
}
Point3D	&Point3D::operator+=(const Point3D &src)
{
	SetX(GetX()+src.GetX());
	SetY(GetY()+src.GetY());
	SetZ(GetZ()+src.GetZ());
	return *this;
}
Point3D	&Point3D::operator+=(const Vector3D &src)
{
	SetX(GetX()+src.GetVx());
	SetY(GetY()+src.GetVy());
	SetZ(GetZ()+src.GetVz());
	return *this;
}
Point3D	&Point3D::operator-=(const Point3D &src)
{
	SetX(GetX()-src.GetX());
	SetY(GetY()-src.GetY());
	SetZ(GetZ()-src.GetZ());
	return *this;
}
Point3D	&Point3D::operator-=(const Vector3D &src)
{
	SetX(GetX()-src.GetVx());
	SetY(GetY()-src.GetVy());
	SetZ(GetZ()-src.GetVz());
	return *this;
}
Point3D	&Point3D::operator*=(float m)
{
	SetX(GetX()*m);
	SetY(GetY()*m);
	SetZ(GetZ()*m);
	return *this;
}
Point3D	&Point3D::operator/=(float m)
{
	SetX(GetX()/m);
	SetY(GetY()/m);
	SetZ(GetZ()/m);
	return *this;
}
Point3D	&Point3D::operator*=(RWMatrix4x4 &src2)
{
	Point3D	Ret;
	Ret.Data.X=  Data.X*src2.Data.Param[0][0]
				+Data.Y*src2.Data.Param[0][1]
				+Data.Z*src2.Data.Param[0][2]
				+		src2.Data.Param[0][3];

	Ret.Data.Y=  Data.X*src2.Data.Param[1][0]
				+Data.Y*src2.Data.Param[1][1]
				+Data.Z*src2.Data.Param[1][2]
				+		src2.Data.Param[1][3];

	Ret.Data.Z=  Data.X*src2.Data.Param[2][0]
				+Data.Y*src2.Data.Param[2][1]
				+Data.Z*src2.Data.Param[2][2]
				+		src2.Data.Param[2][3];
	Data=Ret.Data;
	return *this;
}

void	Point3D::Set(float x ,float y, float z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}
bool	Point3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}
bool	Point3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}


Vector3D::Vector3D(void)
{}
Vector3D::Vector3D(const Vector3D &src)
{
	Data=src.Data;
}
Vector3D::Vector3D(float vx ,float vy, float vz)
{
	SetVx(vx);
	SetVy(vy);
	SetVz(vz);
}
Vector3D::~Vector3D(void)
{
}

Vector3D	&Vector3D::operator=(const Vector3D &src)
{
	Data=src.Data;
	return *this;
}
Vector3D	&Vector3D::operator=(float d)
{
	SetVx(d);
	SetVy(d);
	SetVx(d);
	return *this;
}
Vector3D	Vector3D::operator+()	const
{
	return *this;
}
Vector3D	Vector3D::operator-()	const
{
	Vector3D	Ret(-GetVx(),-GetVy(),-GetVz());
	return Ret;
}

Vector3D	Vector3D::operator+(const Vector3D &src)	const
{
	Vector3D	Ret;
	Ret.SetVx(GetVx()+src.GetVx());
	Ret.SetVy(GetVy()+src.GetVy());
	Ret.SetVz(GetVz()+src.GetVz());
	return Ret;
}
Vector3D	Vector3D::operator-(const Vector3D &src)	const
{
	Vector3D	Ret;
	Ret.SetVx(GetVx()-src.GetVx());
	Ret.SetVy(GetVy()-src.GetVy());
	Ret.SetVz(GetVz()-src.GetVz());
	return Ret;
}
Vector3D	Vector3D::operator*(const Vector3D &src)	const
//Cross product　外積
{
	Vector3D	Ret;
	Ret.SetVx(GetVy()*src.GetVz()-GetVz()*src.GetVy());
	Ret.SetVy(GetVz()*src.GetVx()-GetVx()*src.GetVz());
	Ret.SetVz(GetVx()*src.GetVy()-GetVy()*src.GetVx());
	return Ret;
}
Vector3D	Vector3D::operator*(float m)	const
{
	Vector3D	Ret;
	Ret.SetVx(GetVx()*m);
	Ret.SetVy(GetVy()*m);
	Ret.SetVz(GetVz()*m);
	return Ret;
}
Vector3D	Vector3D::operator*(RWMatrix4x4 &src)	const
{
	Vector3D	Ret;
	Ret.Data.Vx= Data.Vx*src.Data.Param[0][0]
				+Data.Vy*src.Data.Param[0][1]
				+Data.Vx*src.Data.Param[0][2]
				+		 src.Data.Param[0][3];

	Ret.Data.Vy= Data.Vx*src.Data.Param[1][0]
				+Data.Vy*src.Data.Param[1][1]
				+Data.Vx*src.Data.Param[1][2]
				+		 src.Data.Param[1][3];

	Ret.Data.Vz= Data.Vx*src.Data.Param[2][0]
				+Data.Vy*src.Data.Param[2][1]
				+Data.Vx*src.Data.Param[2][2]
				+		 src.Data.Param[2][3];
	return Ret;
}
Vector3D	Vector3D::operator/(float m)	const
{
	Vector3D	Ret;
	Ret.SetVx(GetVx()/m);
	Ret.SetVy(GetVy()/m);
	Ret.SetVz(GetVz()/m);
	return Ret;
}
Vector3D	&Vector3D::operator+=(const Vector3D &src)
{
	SetVx(GetVx()+src.GetVx());
	SetVy(GetVy()+src.GetVy());
	SetVz(GetVz()+src.GetVz());
	return *this;
}
Vector3D	&Vector3D::operator-=(const Vector3D &src)
{
	SetVx(GetVx()-src.GetVx());
	SetVy(GetVy()-src.GetVy());
	SetVz(GetVz()-src.GetVz());
	return *this;
}
Vector3D	&Vector3D::operator*=(float m)
{
	SetVx(GetVx()*m);
	SetVy(GetVy()*m);
	SetVz(GetVz()*m);
	return *this;
}
Vector3D	&Vector3D::operator*=(const Vector3D &src)
//Cross product　外積
{
	Vector3D	Ret;
	Ret.SetVx(GetVy()*src.GetVz()-GetVz()*src.GetVy());
	Ret.SetVy(GetVz()*src.GetVx()-GetVx()*src.GetVz());
	Ret.SetVz(GetVx()*src.GetVy()-GetVy()*src.GetVx());
	Data=Ret.Data;
	return *this;
}
Vector3D	&Vector3D::operator*=(RWMatrix4x4 &src2)
{
	Vector3D	Ret;
	Ret.Data.Vx= Data.Vx*src2.Data.Param[0][0]
				+Data.Vy*src2.Data.Param[0][1]
				+Data.Vx*src2.Data.Param[0][2]
				+		src2.Data.Param[0][3];

	Ret.Data.Vy= Data.Vx*src2.Data.Param[1][0]
				+Data.Vy*src2.Data.Param[1][1]
				+Data.Vx*src2.Data.Param[1][2]
				+		src2.Data.Param[1][3];

	Ret.Data.Vz= Data.Vx*src2.Data.Param[2][0]
				+Data.Vy*src2.Data.Param[2][1]
				+Data.Vx*src2.Data.Param[2][2]
				+		src2.Data.Param[2][3];
	Data=Ret.Data;
	return *this;
}
Vector3D	&Vector3D::operator/=(float m)
{
	SetVx(GetVx()/m);
	SetVy(GetVy()/m);
	SetVz(GetVz()/m);
	return *this;
}
float	Vector3D::InnerProduct(const Vector3D &src)	const
{
	return GetVx()*src.GetVx()+GetVy()*src.GetVy()+GetVz()*src.GetVz();
}
float	Vector3D::GetLength(void)	const
{
	return sqrt(GetVx()*GetVx()+GetVy()*GetVy()+GetVz()*GetVz());
}
float	Vector3D::GetAngle(const Vector3D &src)	const
{
	float	L1=GetLength();
	float	L2=src.GetLength();
	if(L1!=0 && L2!=0){
		float	M=GetVx()*src.GetVx()+GetVy()*src.GetVy()+GetVz()*src.GetVz();
		float	Cos=M/(L1*L2);
		if(-1.0<=Cos && Cos<=1.0){
			return acos(Cos);
		}
	}
	return 0;
}
float	Vector3D::GetCos(const Vector3D &src)	const
{
	float	L1=GetLength();
	float	L2=src.GetLength();
	if(L1!=0 && L2!=0){
		float	M=GetVx()*src.GetVx()+GetVy()*src.GetVy()+GetVz()*src.GetVz();
		float	Cos=M/(L1*L2);
		return Cos;
	}
	return 0;
}
void	Vector3D::Normalize(void)
{
	float	L=GetLength();
	if(L!=0){
		Set(GetVx()/L,GetVy()/L,GetVz()/L);
	}
}
void	Vector3D::Set(float vx ,float vy, float vz)
{
	SetVx(vx);
	SetVy(vy);
	SetVz(vz);
}
bool	Vector3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}
bool	Vector3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	return true;
}


PointVector3D::PointVector3D(void)
{
}
PointVector3D::PointVector3D(const PointVector3D &src)
{
	Point	=src.Point;
	Vector	=src.Vector;
}
PointVector3D::~PointVector3D(void)
{
}

PointVector3D	&PointVector3D::operator=(const PointVector3D &src)
{
	Point	=src.Point;
	Vector	=src.Vector;
	return *this;
}
bool	PointVector3D::Save(QIODevice *f)
{
	if(Point.Save(f)==false)	return false;
	if(Vector.Save(f)==false)	return false;
	return true;
}
bool	PointVector3D::Load(QIODevice *f)
{
	if(Point.Load(f)==false)	return false;
	if(Vector.Load(f)==false)	return false;
	return true;
}

//===========================================================================================
CrossInfo::CrossInfo(void)
{
	CrossT=0;
}
CrossInfo::CrossInfo(const CrossInfo &src)
{
	CrossT		=src.CrossT;
	Point		=src.Point;
	NormalVector=src.NormalVector;
}

CrossInfo	&CrossInfo::operator=(const CrossInfo &src)
{
	CrossT		=src.CrossT;
	Point		=src.Point;
	NormalVector=src.NormalVector;
	return *this;
}

CrossVolume::CrossVolume(void)
{
}
CrossVolume::CrossVolume(const CrossVolume &src)
{
	NearSide=src.NearSide;
	FarSide =src.FarSide ;
}

CrossVolume	&CrossVolume::operator=(const CrossVolume &src)
{
	NearSide=src.NearSide;
	FarSide =src.FarSide ;
	return *this;
}

int	CrossVolume::Compare(CrossVolume &src)
{
	if(NearSide.CrossT<src.NearSide.CrossT)
		return 1;
	if(NearSide.CrossT>src.NearSide.CrossT)
		return -1;
	return 0;
}

CrossCluster::CrossCluster(void)
{
	Surface=NULL;
}
CrossCluster::CrossCluster(const CrossCluster &src)
{
	Surface=src.Surface;
	for(CrossVolume *v=src.GetFirst();v!=NULL;v=v->GetNext()){
		CrossVolume *d=new CrossVolume(*v);
		AppendList(d);
	}
}

CrossCluster	&CrossCluster::operator=(const CrossCluster &src)
{
	Surface=src.Surface;
	RemoveAll();
	for(CrossVolume *v=src.GetFirst();v!=NULL;v=v->GetNext()){
		CrossVolume *d=new CrossVolume(*v);
		AppendList(d);
	}
	return *this;
}
void	CrossCluster::Bind(void)
{
	for(CrossVolume *d=GetFirst();d!=NULL;){
		CrossVolume *NextD=d->GetNext();
		if(NextD!=NULL){
			if(d->NearSide.CrossT<=NextD->NearSide.CrossT && NextD->NearSide.CrossT<=d->FarSide.CrossT){
				if(d->FarSide.CrossT<=NextD->FarSide.CrossT){
					d->FarSide=NextD->FarSide;
				}
				CrossVolume	*p=NextD->GetNext();
				RemoveList(NextD);
				delete	NextD;
			}
			else{
				d=NextD;
			}
		}
		else{
			break;
		}
	}
}

void	CrossCluster::OrBreak(CrossCluster &src)
{
	for(CrossVolume *d=GetFirst();d!=NULL;d=d->GetNext()){
		for(CrossVolume *s=src.GetFirst();s!=NULL;){
			CrossVolume	*SNext=s->GetNext();
			if(d->FarSide.CrossT<=s->NearSide.CrossT){
				break;
			}
			if(d->NearSide.CrossT<=s->NearSide.CrossT && s->NearSide.CrossT<=d->FarSide.CrossT){
				if(d->FarSide.CrossT<=s->FarSide.CrossT){
					d->FarSide=s->FarSide;
				}
				src.RemoveList(s);
				delete	s;
			}
			if(s->NearSide.CrossT<=d->NearSide.CrossT && d->NearSide.CrossT<=s->FarSide.CrossT){
				d->NearSide=s->NearSide;
				if(d->FarSide.CrossT<=s->FarSide.CrossT){
					d->FarSide=s->FarSide;
				}
				src.RemoveList(s);
				delete	s;
			}
			s=SNext;
		}
	}
	AddMove(src);
	Sort();
	Bind();
}

void	CrossCluster::NotAndBreak(CrossCluster &src)
{
	for(CrossVolume *d=GetFirst();d!=NULL;){
		CrossVolume	*NextD=d->GetNext();
		bool	Crossed=false;
		for(CrossVolume *s=src.GetFirst();s!=NULL;s=s->GetNext()){
			if(d->FarSide.CrossT<s->NearSide.CrossT){
				d=NextD;
				Crossed=true;
				break;
			}
			if(s->NearSide.CrossT<=d->NearSide.CrossT && d->NearSide.CrossT<=s->FarSide.CrossT){
				if(s->FarSide.CrossT<d->FarSide.CrossT){
					d->NearSide=s->FarSide;
				}
				else{
					RemoveList(d);
					delete	d;
					d=NextD;
					Crossed=true;
					break;
				}
			}
			else
			if(d->NearSide.CrossT<=s->NearSide.CrossT && s->NearSide.CrossT<=d->FarSide.CrossT){			
				if(s->FarSide.CrossT<=d->FarSide.CrossT){
					CrossVolume	*w=new CrossVolume();
					w->NearSide	=s->FarSide;
					w->FarSide	=d->FarSide;
					d->FarSide=s->NearSide;
					InsertLater(d,w);
					NextD=w;
				}
				else{
					d->FarSide=s->NearSide;
				}
			}
		}
		if(Crossed==false){
			d=NextD;
		}
	}
}
void	CrossCluster::AndBreak	(CrossCluster &src)
{
	CrossCluster	Tmp;
	for(CrossVolume *d=GetFirst();d!=NULL;d=d->GetNext()){
		for(CrossVolume *s=src.GetFirst();s!=NULL;){
			CrossVolume *SNext=s->GetNext();
			if(s->FarSide.CrossT<=d->NearSide.CrossT){
				src.RemoveList(s);
				delete	s;
			}
			else
			if(d->FarSide.CrossT<=s->NearSide.CrossT){
				break;
			}
			else
			if(d->NearSide.CrossT<=s->NearSide.CrossT && s->NearSide.CrossT<=d->FarSide.CrossT){
				CrossVolume	*V=new CrossVolume();
				V->NearSide=s->NearSide;
				if(d->FarSide.CrossT<=s->FarSide.CrossT){
					V->FarSide =d->FarSide;
					
				}
				else{
					V->FarSide =s->FarSide;
				}
				Tmp.AppendList(V);
				src.RemoveList(s);
				delete	s;
			}
			if(s->NearSide.CrossT<=d->NearSide.CrossT && d->NearSide.CrossT<=s->FarSide.CrossT){
				CrossVolume	*V=new CrossVolume();
				V->NearSide=d->NearSide;
				if(d->FarSide.CrossT<=s->FarSide.CrossT){
					V->FarSide=d->FarSide;
				}
				else{
					V->FarSide=s->FarSide;
				}
				Tmp.AppendList(V);
				src.RemoveList(s);
				delete	s;
			}
			s=SNext;
		}
	}
	RemoveAll();
	AddMove(Tmp);
}
void	CrossCluster::XorBreak	(CrossCluster &src)
{
	CrossCluster	Tmp;
	for(CrossVolume *d=GetFirst();d!=NULL;d=d->GetNext()){
		for(CrossVolume *s=src.GetFirst();s!=NULL;){
			CrossVolume *SNext=s->GetNext();
			if(s->FarSide.CrossT<=d->NearSide.CrossT){
				src.RemoveList(s);
				Tmp.AppendList(s);
			}
			else
			if(d->FarSide.CrossT<=s->NearSide.CrossT){
				break;
			}
			else
			if(d->NearSide.CrossT<=s->NearSide.CrossT && s->NearSide.CrossT<=d->FarSide.CrossT){
				CrossVolume	*V=new CrossVolume();
				V->NearSide=d->NearSide;
				if(d->FarSide.CrossT<=s->FarSide.CrossT){
					V->FarSide =s->NearSide;
					s->NearSide=d->FarSide;
				}
				else{
					V->FarSide =s->NearSide;
					Tmp.AppendList(V);
					d->NearSide=s->FarSide;
					src.RemoveList(s);
					delete	s;
					continue;
				}
				Tmp.AppendList(V);
			}
			if(s->NearSide.CrossT<=d->NearSide.CrossT && d->NearSide.CrossT<=s->FarSide.CrossT){
				CrossVolume	*V=new CrossVolume();
				V->NearSide	=s->NearSide;
				V->FarSide	=d->NearSide;
				Tmp.AppendList(V);

				if(d->FarSide.CrossT<=s->FarSide.CrossT){
					s->NearSide=d->FarSide;
				}
				else{
					V->FarSide=s->FarSide;
					d->NearSide=s->FarSide;
					src.RemoveList(s);
					delete	s;
					continue;
				}
			}
			s=SNext;
		}
	}
	RemoveAll();
	AddMove(Tmp);
}

//===========================================================================================
RWShapeBase::RWShapeBase(void)
{
	OC=OC_Or;
	Version=1;
}
void	RWShapeBase::Copy(RWShapeBase &src)
{
	OC		=src.OC;
	Name	=src.Name;
	Version	=src.Version;
}
bool	RWShapeBase::Save(QIODevice *f)
{
	if(::Save(f,Version)==false)	return false;
	BYTE	b=(BYTE)OC;
	if(::Save(f,b	)==false)		return false;
	if(::Save(f,Name)==false)		return false;
	return true;
}
bool	RWShapeBase::Load(QIODevice *f)
{
	if(::Load(f,Version)==false)	return false;
	BYTE	b=(BYTE)OC;
	if(::Load(f,b	)==false)		return false;
	if(::Load(f,Name)==false)		return false;
	return true;
}


RWShapeBaseContainer::RWShapeBaseContainer(void)
{
}
RWShapeBaseContainer::RWShapeBaseContainer(const RWShapeBaseContainer &src)
{
	for(RWShapeBase *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RWShapeBase *d=s->Clone();
		*d=*s;
		AppendList(d);
	}
}

RWShapeBaseContainer	&RWShapeBaseContainer::operator=(const RWShapeBaseContainer &src)
{
	for(RWShapeBase *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RWShapeBase *d=s->Clone();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	RWShapeBaseContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)	return false;
	for(RWShapeBase *s=GetFirst();s!=NULL;s=s->GetNext()){
		int32	t=s->GetShapeID();
		if(::Save(f,t)==false)	return false;
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	RWShapeBaseContainer::Load(QIODevice *f)
{
	int32	N;
	RemoveAll();
	if(::Load(f,N)==false)	return false;
	for(int i=0;i<N;i++){
		int32	t;
		if(::Load(f,t)==false)	return false;
		RWShapeBase	*d=Create(t);
		if(d->Load(f)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}

RWShapeBase		*RWShapeBaseContainer::Create(int d)
{
	switch(d)
	{
	case ShapeID_Shere		:
		return new RWShapeSphere();		break;
	case ShapeID_RectPlain	:
		return new RWShapeRectPlain();	break;
	case ShapeID_Box		:
		return new RWShapeBox();			break;
	case ShapeID_Composite	:
		return new RWShapeComposite();	break;
	}
	return NULL;
}
bool	RWShapeBaseContainer::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	bool	FirstOne=true;
	bool	Ret=false;
	for(RWShapeBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		Point3D tMinPoint ,tMaxPoint;
		switch(a->OC){
		case RWShapeBase::OC_Or		:
				if(a->GetArea(tMinPoint ,tMaxPoint)==true){
					if(FirstOne==true){
						MinPoint=tMinPoint;
						MaxPoint=tMaxPoint;
						FirstOne=false;
					}
					else{
						MinPoint=min(MinPoint,tMinPoint);
						MaxPoint=max(MaxPoint,tMaxPoint);
					}
					Ret=true;
				}
				break;
			case RWShapeBase::OC_NotAnd	:
				break;
			case RWShapeBase::OC_And		:
				if(FirstOne==true){
					if(a->GetArea(tMinPoint ,tMaxPoint)==true){
						MinPoint=tMinPoint;
						MaxPoint=tMaxPoint;
						FirstOne=false;
						Ret=true;
					}
				}
				break;
			case RWShapeBase::OC_Xor		:
				if(a->GetArea(tMinPoint ,tMaxPoint)==true){
					if(FirstOne==true){
						MinPoint=tMinPoint;
						MaxPoint=tMaxPoint;
						FirstOne=false;
					}
					else{
						MinPoint=min(MinPoint,tMinPoint);
						MaxPoint=max(MaxPoint,tMaxPoint);
					}
					Ret=true;
				}
				break;
		}
	}
	return Ret;
}
bool	RWShapeBaseContainer::GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)
{
	bool	Ret=false;
	for(RWShapeBase *s=GetFirst();s!=NULL;s=s->GetNext()){
		CrossCluster tCrossSides;
		bool	b=s->GetCrossPoint(Line ,tCrossSides);
		if(b==true){
			CrossSides.OrBreak(tCrossSides);
			Ret=true;
		}
	}
	return Ret;
}
//===========================================================================================

RWShapeSphere::RWShapeSphere(void)
{
}

RWShapeBase	*RWShapeSphere::Clone(void)
{
	RWShapeSphere	*d=new RWShapeSphere();
	d->Point	=Point;
	d->Radius	=Radius;
	return d;
}

bool	RWShapeSphere::Save(QIODevice *f)
{
	if(RWShapeBase::Save(f)==false)	return false;
	if(Point.Save(f)==false)		return false;
	if(Radius.Save(f)==false)		return false;
	return true;
}
bool	RWShapeSphere::Load(QIODevice *f)
{
	if(RWShapeBase::Load(f)==false)	return false;
	if(Point.Load(f)==false)	return false;
	if(Radius.Load(f)==false)	return false;
	return true;
}
bool	RWShapeSphere::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	MinPoint.Set(Point.GetX()-Radius.GetVx()
				,Point.GetY()-Radius.GetVy()
				,Point.GetZ()-Radius.GetVz());
	MaxPoint.Set(Point.GetX()+Radius.GetVx()
				,Point.GetY()+Radius.GetVy()
				,Point.GetZ()+Radius.GetVz());
	return true;
}
bool	RWShapeSphere::GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)
{
	//L=(ut+p,vt+q,wt+r)
	//((x-e)/a)^2+((y-f)/b)^2+((z-g)/c)^2=1
	//((ut+p-e)/a)^2+((vt+q-f)/b)^2+((wt+r-g)/c)^2=1

	float	u=Line.Vector.GetVx();
	float	v=Line.Vector.GetVy();
	float	w=Line.Vector.GetVz();
	float	p=Line.Point.GetX();
	float	q=Line.Point.GetY();
	float	r=Line.Point.GetZ();
	float	a=Radius.GetVx();
	float	b=Radius.GetVy();
	float	c=Radius.GetVz();
	float	e=Point.GetX();
	float	f=Point.GetY();
	float	g=Point.GetZ();

	if(a==0 || b==0 || c==0)
		return false;

	float	a2=a*a;
	float	b2=b*b;
	float	c2=c*c;
	float	u2=u*u;
	float	v2=v*v;
	float	w2=w*w;
	float	k=2*(-(e*u)/a2 + (p*u)/a2 - (f*v)/b2 + (q*v)/b2 - (g*w)/c2 + (r*w)/c2);
	float	k2=k*k;
	float	h=- 4*(u2/a2 + v2/b2 + w2/c2)*(e*e/a2 - (2*e*p)/a2 + p*p/a2 + f*f/b2 - (2*f*q)/b2 + q*q/b2 + g*g/c2 - (2*g*r)/c2 + r*r/c2 - 1);
	float	m=2*((e*u)/a2 - (p*u)/a2 + (f*v)/b2 - (q*v)/b2 + (g*w)/c2 - (r*w))/c2;
	float	n=2*(u2/a2 + v2/b2 + w2/c2);

	if(k2+h>=0 && n>0){
		//	x=a*cos(i)*cos(j)+e	=u*t+p
		//	y=b*cos(i)*sin(j)+f	=v*t+q
		//	z=c*sin(i)+g		=w*t+r
		//	dx/di	=-a*sin(i)*cos(j)
		//	dy/di	=-b*sin(i)*sin(j)
		//	dz/di	=c*cos(i)
		//	dx/dj	=-a*cos(i)*sin(j)
		//	dy/dj	= b*cos(i)*cos(j)
		//	dz/dj	=0
		//	外積Dx	=-b*sin(i)*sin(j)*0-c*cos(i)*b*cos(i)*cos(j)
		//			=-b*c*cos(i)^2*cos(j)
		//	外積Dy	=c*cos(i)*(-a*cos(i)*sin(j))*-(-a*sin(i)*cos(j))*0
		//			=-a*c*cos(i)^2*sin(j)
		//	外積Dz	=-a*sin(i)*cos(j)*b*cos(i)*cos(j) - (-a*cos(i)*sin(j))*(-b*sin(i)*sin(j))
		//			=-a*b*sin(i)*cos(i)*cos(j)^2 - a*b*sin(i)*cos(i)*sin(j)^2
		//			=-a*b*sin(i)*cos(i)
		//
		//	sin(i)=(w*t+r-g)/c
		//	cos(i)=+-sqrt(1-((w*t+r-g)/c)^2)

		float	t1 = (-sqrt(k2 +h) + m)/n;
		float	t2 = ( sqrt(k2 +h) + m)/n;
		CrossVolume	*V=new CrossVolume();
		if(t1>t2){
			swap(t1,t2);
		}
		{
			V->NearSide.CrossT=t1;
			float	sini=(w*t1+r-g)/c;
			float	cc=1-sini*sini;
			float	cosi=sqrt(cc);
			V->NearSide.Point.Set(u*t1+p,v*t1+q,w*t1+r);
			V->NearSide.NormalVector.Set(-b*c*cosi*cosi*(u*t1+p-e)/(a*cosi)
									, -a*c*cosi*cosi*(v*t1+q-f)/(b*cosi)
									, -a*b*sini*cosi);
		}
		{
			V->FarSide.CrossT=t2;
			float	sini=(w*t2+r-g)/c;
			float	cc=1-sini*sini;
			float	cosi=sqrt(cc);
			V->FarSide.Point.Set(u*t2+p,v*t2+q,w*t2+r);
			V->FarSide.NormalVector.Set(-b*c*cosi*cosi*(u*t2+p-e)/(a*cosi)
									, -a*c*cosi*cosi*(v*t2+q-f)/(b*cosi)
									, -a*b*sini*cosi);
		}
		CrossSides.AppendList(V);
		CrossSides.Surface=GetSurface();
		return true;
	}
	return false;
}
//===========================================================================================
RWShapeRectPlain::RWShapeRectPlain(void)
{
}

RWShapeBase	*RWShapeRectPlain::Clone(void)
{
	RWShapeRectPlain	*d=new RWShapeRectPlain();
	d->Point	=Point;
	d->Edge1	=Edge1;
	d->Edge2	=Edge2;
	return d;
}
bool	RWShapeRectPlain::Save(QIODevice *f)
{
	if(RWShapeBase::Save(f)==false)	return false;
	if(Point.Save(f)==false)	return false;
	if(Edge1.Save(f)==false)	return false;
	if(Edge2.Save(f)==false)	return false;
	return true;
}
bool	RWShapeRectPlain::Load(QIODevice *f)
{
	if(RWShapeBase::Load(f)==false)	return false;
	if(Point.Load(f)==false)	return false;
	if(Edge1.Load(f)==false)	return false;
	if(Edge2.Load(f)==false)	return false;
	return true;
}
bool	RWShapeRectPlain::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	MinPoint.Set(min(Point.GetX(),Point.GetX()+Edge1.GetVx(),Point.GetX()+Edge2.GetVx(),Point.GetX()+Edge1.GetVx()+Edge2.GetVx())
				,min(Point.GetY(),Point.GetY()+Edge1.GetVy(),Point.GetY()+Edge2.GetVy(),Point.GetY()+Edge1.GetVy()+Edge2.GetVy())
				,min(Point.GetZ(),Point.GetZ()+Edge1.GetVz(),Point.GetZ()+Edge2.GetVz(),Point.GetZ()+Edge1.GetVz()+Edge2.GetVz()));
	MaxPoint.Set(max(Point.GetX(),Point.GetX()+Edge1.GetVx(),Point.GetX()+Edge2.GetVx(),Point.GetX()+Edge1.GetVx()+Edge2.GetVx())
				,max(Point.GetY(),Point.GetY()+Edge1.GetVy(),Point.GetY()+Edge2.GetVy(),Point.GetY()+Edge1.GetVy()+Edge2.GetVy())
				,max(Point.GetZ(),Point.GetZ()+Edge1.GetVz(),Point.GetZ()+Edge2.GetVz(),Point.GetZ()+Edge1.GetVz()+Edge2.GetVz()));
	return true;
}
bool	MakePVinPlain(const Point3D &Point ,const Vector3D &Edge1 ,const Vector3D &Edge2
					,const PointVector3D &Line ,CrossInfo &Ret)
{
	//V=Point+Edge1*u+Edge2*v
	//V=Line.Point+Line.Vector*t
	//Edge1*u+Edge2*v-Line.Vector*t=Line.Point-Point
	//(a,b,c)*u+(d,e,f)*v-(g,h,k)*t=(p,q,r)
	//a*u+d*v-g*t=p
	//b*u+e*v-h*t=q
	//c*u+f*v-k*t=r

	float	a=Edge1.GetVx();
	float	b=Edge1.GetVy();
	float	c=Edge1.GetVz();
	float	d=Edge2.GetVx();
	float	e=Edge2.GetVy();
	float	f=Edge2.GetVz();
	float	g=Line.Vector.GetVx();
	float	h=Line.Vector.GetVy();
	float	k=Line.Vector.GetVz();
	float	p=Line.Point.GetX()-Point.GetX();
	float	q=Line.Point.GetY()-Point.GetY();
	float	r=Line.Point.GetZ()-Point.GetZ();
	float	m=-a*e*k + a*f*h + b*d*k - b*f*g - c*d*h + c*e*g;
	if(m!=0){
		float	u = -( d*h*r - d*k*q - e*g*r + e*k*p + f*g*q - f*h*p)/m;
		float	v = -(-a*h*r + a*k*q + b*g*r - b*k*p - c*g*q + c*h*p)/m;
		float	t = -(-a*e*r + a*f*q + b*d*r - b*f*p - c*d*q + c*e*p)/m;
		if(0<=u && u<=1.0 && 0<=v && v<=1.0){
			float	l=Point.GetX();
			float	m=Point.GetY();
			float	n=Point.GetZ();
			Ret.CrossT=t;
			//	ix+jy+kz+h=0
			//	a*s+b*w+c*n=0
			//	d*s+e*w*f*n=0
			//	s*s+w*w+n*n=1
			a+=l;
			b+=m;
			c+=n;
			d+=l;
			e+=m;
			f+=n;
			Ret.Point=Point+Edge1*u+Edge2*v;
			//float	W=-a*e*n + a*f*m + b*d*n - b*f*l - c*d*m + c*e*l;
			Ret.NormalVector.Set(-(-b*f + b*n + c*e - c*m - e*n + f*m)
									 ,-( a*f - a*n - c*d + c*l + d*n - f*l) 
									 ,-(-a*e + a*m + b*d - b*l - d*m + e*l));
			return true;
		}
	}
	return false;
}


bool	RWShapeRectPlain::GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)
{
	CrossInfo Ret;
	if(MakePVinPlain(Point ,Edge1 ,Edge2,Line ,Ret)==true){
		CrossVolume	*V=new CrossVolume();
		V->NearSide	=Ret;
		V->FarSide	=Ret;
		CrossSides.Surface=GetSurface();
		return true;
	}
	return false;
}
//===========================================================================================

RWShapeBox::RWShapeBox(void)
{
}

RWShapeBase	*RWShapeBox::Clone(void)
{
	RWShapeBox	*d=new RWShapeBox();
	d->Point	=Point;
	for(int i=0;i<3;i++){
		d->Edge[i]	=Edge[i];
	}
	return d;
}
bool	RWShapeBox::Save(QIODevice *f)
{
	if(RWShapeBase::Save(f)==false)	return false;
	if(Point.Save(f)==false)	return false;
	for(int i=0;i<3;i++){
		if(Edge[i].Save(f)==false)	return false;
	}
	return true;
}
bool	RWShapeBox::Load(QIODevice *f)
{
	if(RWShapeBase::Load(f)==false)	return false;
	if(Point.Load(f)==false)	return false;
	for(int i=0;i<3;i++){
		if(Edge[i].Load(f)==false)	return false;
	}
	return true;
}
bool	RWShapeBox::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	Point3D	P1=Point;
	Point3D	P2=Point+Edge[0];
	Point3D	P3=Point+Edge[1];
	Point3D	P4=Point+Edge[2];
	Point3D	P5=Point+Edge[0]+Edge[1];
	Point3D	P6=Point+Edge[1]+Edge[2];
	Point3D	P7=Point+Edge[2]+Edge[0];
	Point3D	P8=Point+Edge[0]+Edge[1]+Edge[2];

	MinPoint.Set(min(min(P1.GetX(),P2.GetX(),P3.GetX(),P4.GetX()),min(P5.GetX(),P6.GetX(),P7.GetX(),P8.GetX()))
				,min(min(P1.GetY(),P2.GetY(),P3.GetY(),P4.GetY()),min(P5.GetY(),P6.GetY(),P7.GetY(),P8.GetY()))
				,min(min(P1.GetZ(),P2.GetZ(),P3.GetZ(),P4.GetZ()),min(P5.GetZ(),P6.GetZ(),P7.GetZ(),P8.GetZ())));
	MaxPoint.Set(max(max(P1.GetX(),P2.GetX(),P3.GetX(),P4.GetX()),max(P5.GetX(),P6.GetX(),P7.GetX(),P8.GetX()))
				,max(max(P1.GetY(),P2.GetY(),P3.GetY(),P4.GetY()),max(P5.GetY(),P6.GetY(),P7.GetY(),P8.GetY()))
				,max(max(P1.GetZ(),P2.GetZ(),P3.GetZ(),P4.GetZ()),max(P5.GetZ(),P6.GetZ(),P7.GetZ(),P8.GetZ())));
	return true;
}

bool	RWShapeBox::GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)
{
	CrossInfo	NearSide;
	CrossInfo	FarSide ;
	NearSide.CrossT=FLT_MAX;
	FarSide.CrossT=0;
	CrossInfo Ret;
	bool	NearOK=false;
	bool	FarOK=false;
	if(MakePVinPlain(Point ,Edge[0] ,Edge[1],Line ,Ret)==true){
		if(Ret.CrossT>0){
			if(NearSide.CrossT>Ret.CrossT){
				NearSide=Ret;
				NearOK=true;
			}
			if(FarSide.CrossT<Ret.CrossT){
				FarSide=Ret;
				FarOK=true;
			}
		}
	}
	if(MakePVinPlain(Point ,Edge[1] ,Edge[2],Line ,Ret)==true){
		if(Ret.CrossT>0){
			if(NearSide.CrossT>Ret.CrossT){
				NearSide=Ret;
				NearOK=true;
			}
			if(FarSide.CrossT<Ret.CrossT){
				FarSide=Ret;
				FarOK=true;
			}
		}
	}
	if(MakePVinPlain(Point ,Edge[2] ,Edge[0],Line ,Ret)==true){
		if(Ret.CrossT>0){
			if(NearSide.CrossT>Ret.CrossT){
				NearSide=Ret;
				NearOK=true;
			}
			if(FarSide.CrossT<Ret.CrossT){
				FarSide=Ret;
				FarOK=true;
			}
		}
	}
	Point3D		Point2=Point+Edge[0]+Edge[1]+Edge[2];
	if(MakePVinPlain(Point2 ,-Edge[0] ,-Edge[1],Line ,Ret)==true){
		if(Ret.CrossT>0){
			if(NearSide.CrossT>Ret.CrossT){
				NearSide=Ret;
				NearOK=true;
			}
			if(FarSide.CrossT<Ret.CrossT){
				FarSide=Ret;
				FarOK=true;
			}
		}
	}
	if(MakePVinPlain(Point2 ,-Edge[1] ,-Edge[2],Line ,Ret)==true){
		if(Ret.CrossT>0){
			if(NearSide.CrossT>Ret.CrossT){
				NearSide=Ret;
				NearOK=true;
			}
			if(FarSide.CrossT<Ret.CrossT){
				FarSide=Ret;
				FarOK=true;
			}
		}
	}
	if(MakePVinPlain(Point2 ,-Edge[2] ,-Edge[0],Line ,Ret)==true){
		if(Ret.CrossT>0){
			if(NearSide.CrossT>Ret.CrossT){
				NearSide=Ret;
				NearOK=true;
			}
			if(FarSide.CrossT<Ret.CrossT){
				FarSide=Ret;
				FarOK=true;
			}
		}
	}
	if(NearOK==true && FarOK==true){
		CrossVolume	*V=new CrossVolume();
		V->NearSide	=NearSide;
		V->FarSide	=FarSide;
		CrossSides.AppendList(V);
		CrossSides.Surface=GetSurface();
		return true;
	}
	return false;
}
//===========================================================================================

RWShapeComposite::RWShapeComposite(void)
{
}


RWShapeBase	*RWShapeComposite::Clone(void)
{
	RWShapeComposite	*d=new RWShapeComposite();
	d->Items	=Items;
	return d;
}
bool	RWShapeComposite::Save(QIODevice *f)
{
	if(RWShapeBase::Save(f)==false)	return false;
	if(Items.Save(f)==false)		return false;
	return true;
}
bool	RWShapeComposite::Load(QIODevice *f)
{
	if(RWShapeBase::Load(f)==false)	return false;
	if(Items.Load(f)==false)		return false;
	return true;
}
bool	RWShapeComposite::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	return Items.GetArea(MinPoint ,MaxPoint);
}
bool	RWShapeComposite::GetCrossPoint(const PointVector3D &Line ,CrossCluster &CrossSides)
{
	for(RWShapeBase *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		CrossCluster	tCluster;
		a->GetCrossPoint(Line ,tCluster);
		switch(a->OC){
			case OC_Or		:
				CrossSides.OrBreak(tCluster);
				break;
			case OC_NotAnd	:
				CrossSides.NotAndBreak(tCluster);
				break;
			case OC_And		:
				CrossSides.AndBreak(tCluster);
				break;
			case OC_Xor		:
				CrossSides.XorBreak(tCluster);
				break;
		}
	}
	return false;
}