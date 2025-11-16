#include "X3DCommon.h"
#include "XGeneralFunc.h"


UVector3D::UVector3D(double ux,double uy,double uz)
{
	Data.Ux=ux;
	Data.Uy=uy;
	Data.Uz=uz;
}
UVector3D::UVector3D(const UVector3D &src)
{
	Data.Ux=src.Data.Ux;
	Data.Uy=src.Data.Uy;
	Data.Uz=src.Data.Uz;
}
UVector3D::UVector3D(const Vector3D &src)
{
	Data.Ux=src.Data.Vx;
	Data.Uy=src.Data.Vy;
	Data.Uz=src.Data.Vz;
}
UVector3D &UVector3D::operator=(const UVector3D &src)
{
	Data.Ux=src.Data.Ux;
	Data.Uy=src.Data.Uy;
	Data.Uz=src.Data.Uz;
	return *this;
}
bool	UVector3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	UVector3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
UVector3D	UVector3D::operator-()	const
{
	return UVector3D(-Data.Ux ,-Data.Uy ,-Data.Uz);
}
Vector3D	UVector3D::operator+(const Vector3D &s)	const
{
	return Vector3D(Data.Ux+s.Data.Vx ,Data.Uy+s.Data.Vy ,Data.Uz+s.Data.Vz);
}
Vector3D	UVector3D::operator-(const Vector3D &s)	const
{
	return Vector3D(Data.Ux-s.Data.Vx ,Data.Uy-s.Data.Vy ,Data.Uz-s.Data.Vz);
}
double		UVector3D::operator*(const Vector3D &s)	const
{
	return Data.Ux*s.Data.Vx+Data.Uy*s.Data.Vy+Data.Uz*s.Data.Vz;
}

Vector3D	UVector3D::operator+(const UVector3D &s)	const
{
	return Vector3D(Data.Ux+s.Data.Ux ,Data.Uy+s.Data.Uy ,Data.Uz+s.Data.Uz);
}
Vector3D	UVector3D::operator-(const UVector3D &s)	const
{
	return Vector3D(Data.Ux-s.Data.Ux ,Data.Uy-s.Data.Uy ,Data.Uz-s.Data.Uz);
}
double		UVector3D::operator*(const UVector3D &s)	const
{
	return Data.Ux*s.Data.Ux+Data.Uy*s.Data.Uy+Data.Uz*s.Data.Uz;
}
Vector3D	UVector3D::operator*(double L)	const
{
	return Vector3D(Data.Ux*L,Data.Uy*L,Data.Uz*L);
}
Vector3D	UVector3D::operator/(double L)	const
{
	return Vector3D(Data.Ux/L,Data.Uy/L,Data.Uz/L);
}


bool	UVector3D::operator==(const UVector3D &s)	const
{
	if(Data.Ux	==s.Data.Ux
	&& Data.Uy	==s.Data.Uy
	&& Data.Uz	==s.Data.Uz){
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------

Vector3D::Vector3D(double vx,double vy,double vz)
{
	Data.Vx=vx;
	Data.Vy=vy;
	Data.Vz=vz;
}
Vector3D::Vector3D(const Vector3D &src)
{
	Data.Vx=src.Data.Vx;
	Data.Vy=src.Data.Vy;
	Data.Vz=src.Data.Vz;
}
Vector3D::Vector3D(const UVector3D &src)
{
	Data.Vx=src.Data.Ux;
	Data.Vy=src.Data.Uy;
	Data.Vz=src.Data.Uz;
}

Vector3D &Vector3D::operator=(const Vector3D &src)
{
	Data.Vx=src.Data.Vx;
	Data.Vy=src.Data.Vy;
	Data.Vz=src.Data.Vz;
	return *this;
}
bool	Vector3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	Vector3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

double	Vector3D::GetLength(void)	const
{
	return sqrt(Data.Vx*Data.Vx+Data.Vy*Data.Vy+Data.Vz*Data.Vz);
}
UVector3D	Vector3D::GetUnit(void)	const
{
	double	Len=GetLength();
	if(Len>0){
		return UVector3D(Data.Vx/Len,Data.Vy/Len,Data.Vz/Len);
	}
	return UVector3D(0.0,0.0,0.0);
}
Vector3D	Vector3D::operator-()
{
	return Vector3D(-Data.Vx,-Data.Vy,-Data.Vz);
}
Vector3D	Vector3D::operator+(const Vector3D &s)	const
{
	return Vector3D(Data.Vx+s.Data.Vx,Data.Vy+s.Data.Vy,Data.Vz+s.Data.Vz);
}
Vector3D	Vector3D::operator-(const Vector3D &s)	const
{
	return Vector3D(Data.Vx-s.Data.Vx,Data.Vy-s.Data.Vy,Data.Vz-s.Data.Vz);
}
double	Vector3D::operator*(const Vector3D &s)	const
{
	return Data.Vx*s.Data.Vx+Data.Vy*s.Data.Vy+Data.Vz*s.Data.Vz;
}
Vector3D	Vector3D::operator+(const UVector3D &s)	const
{
	return Vector3D(Data.Vx+s.Data.Ux,Data.Vy+s.Data.Uy,Data.Vz+s.Data.Uz);
}
Vector3D	Vector3D::operator-(const UVector3D &s)	const
{
	return Vector3D(Data.Vx-s.Data.Ux,Data.Vy-s.Data.Uy,Data.Vz-s.Data.Uz);
}
double		Vector3D::operator*(const UVector3D &s)	const
{
	return Data.Vx*s.Data.Ux+Data.Vy*s.Data.Uy+Data.Vz*s.Data.Uz;
}
Vector3D	Vector3D::operator*(double L)	const
{
	return Vector3D(Data.Vx*L,Data.Vy*L,Data.Vz*L);
}
Vector3D	Vector3D::operator/(double L)	const
{
	return Vector3D(Data.Vx/L,Data.Vy/L,Data.Vz/L);
}
Vector3D	&Vector3D::operator+=(const Vector3D &s)
{
	Data.Vx	+=s.Data.Vx;
	Data.Vy	+=s.Data.Vy;
	Data.Vz	+=s.Data.Vz;
	return *this;
}
Vector3D	&Vector3D::operator-=(const Vector3D &s)
{
	Data.Vx	-=s.Data.Vx;
	Data.Vy	-=s.Data.Vy;
	Data.Vz	-=s.Data.Vz;
	return *this;
}
Vector3D	&Vector3D::operator+=(const UVector3D &s)
{
	Data.Vx	+=s.Data.Ux;
	Data.Vy	+=s.Data.Uy;
	Data.Vz	+=s.Data.Uz;
	return *this;
}
Vector3D	&Vector3D::operator-=(const UVector3D &s)
{
	Data.Vx	-=s.Data.Ux;
	Data.Vy	-=s.Data.Uy;
	Data.Vz	-=s.Data.Uz;
	return *this;
}
Vector3D	&Vector3D::operator*=(double L)
{
	Data.Vx	*=L;
	Data.Vy	*=L;
	Data.Vz	*=L;
	return *this;
}

Vector3D	&Vector3D::operator/=(double L)
{
	Data.Vx	/=L;
	Data.Vy	/=L;
	Data.Vz	/=L;
	return *this;
}
bool	Vector3D::operator==(const Vector3D &s)	const
{
	if(Data.Vx	==s.Data.Vx
	&& Data.Vy	==s.Data.Vy
	&& Data.Vz	==s.Data.Vz){
		return true;
	}
	return false;
}

Vector3D	Vector3D::CrossProduct(const Vector3D &a,const Vector3D &b)
{
	return Vector3D( a.Data.Vy*b.Data.Vz-a.Data.Vz*b.Data.Vy
					,a.Data.Vz*b.Data.Vx-a.Data.Vx*b.Data.Vz
					,a.Data.Vx*b.Data.Vy-a.Data.Vy*b.Data.Vx);
}

//----------------------------------------------------------------------------

Point3D::Point3D(double x,double y,double z)
{
	Data.X=x;
	Data.Y=y;
	Data.Z=z;
}
Point3D::Point3D(const Point3D &src)
{
	Data.X=src.Data.X;
	Data.Y=src.Data.Y;
	Data.Z=src.Data.Z;
}

Point3D &Point3D::operator=(const Point3D &src)
{
	Data.X=src.Data.X;
	Data.Y=src.Data.Y;
	Data.Z=src.Data.Z;
	return *this;
}
bool	Point3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	Point3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

Point3D	Point3D::operator+(const Vector3D &s)	const
{
	return Point3D(Data.X+s.Data.Vx ,Data.Y+s.Data.Vy ,Data.Z+s.Data.Vz);
}
Point3D	Point3D::operator-(const Vector3D &s)	const
{
	return Point3D(Data.X-s.Data.Vx ,Data.Y-s.Data.Vy ,Data.Z-s.Data.Vz);
}
Vector3D	Point3D::operator-(const Point3D &s)	const
{
	return Vector3D(Data.X-s.Data.X ,Data.Y-s.Data.Y ,Data.Z-s.Data.Z);
}
Point3D	&Point3D::operator+=(const Vector3D &s)
{
	Data.X=+s.Data.Vx;
	Data.Y=+s.Data.Vy;
	Data.Z=+s.Data.Vz;
	return *this;
}

Point3D	&Point3D::operator-=(const Vector3D &s)
{
	Data.X=-s.Data.Vx;
	Data.Y=-s.Data.Vy;
	Data.Z=-s.Data.Vz;
	return *this;
}
bool	Point3D::operator==(const Point3D &s)	const
{
	if(Data.X==s.Data.X
	&& Data.Y==s.Data.Y
	&& Data.Z==s.Data.Z){
		return true;
	}
	return false;
}


//----------------------------------------------------------------------------

Angle3D::Angle3D(double rx,double ry,double rs)
{
	Data.Rx=rx;
	Data.Ry=ry;
	Data.Rs=rs;
}
Angle3D::Angle3D(const Angle3D &src)
{
	Data.Rx=src.Data.Rx;
	Data.Ry=src.Data.Ry;
	Data.Rs=src.Data.Rs;
}

Angle3D &Angle3D::operator=(const Angle3D &src)
{
	Data.Rx=src.Data.Rx;
	Data.Ry=src.Data.Ry;
	Data.Rs=src.Data.Rs;
	return *this;
}
bool	Angle3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	Angle3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
Angle3D		Angle3D::operator+(const Angle3D &s)	const
{
	return Angle3D(Data.Rx+s.Data.Rx ,Data.Ry+s.Data.Ry ,Data.Rs+s.Data.Rs);
}
Angle3D		Angle3D::operator-(const Angle3D &s)	const
{
	return Angle3D(Data.Rx-s.Data.Rx ,Data.Ry-s.Data.Ry ,Data.Rs-s.Data.Rs);
}
Angle3D		&Angle3D::operator+=(const Angle3D &s)
{
	Data.Rx+=s.Data.Rx;
	Data.Ry+=s.Data.Ry;
	Data.Rs+=s.Data.Rs;
	return *this;
}
Angle3D		&Angle3D::operator-=(const Angle3D &s)
{
	Data.Rx-=s.Data.Rx;
	Data.Ry-=s.Data.Ry;
	Data.Rs-=s.Data.Rs;
	return *this;
}

bool	Angle3D::operator==(const Angle3D &src)	const
{
	if(Data.Rx==src.Data.Rx
	&& Data.Ry==src.Data.Ry
	&& Data.Rs==src.Data.Rs){
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------

Box3D::Box3D(double x1,double y1,double z1,double x2,double y2,double z2)
{
	Data.X1=x1;
	Data.Y1=y1;
	Data.Z1=z1;
	Data.X2=x2;
	Data.Y2=y2;
	Data.Z2=z2;
}
Box3D::Box3D(const Box3D &src)
{
	Data.X1=src.Data.X1;
	Data.Y1=src.Data.Y1;
	Data.Z1=src.Data.Z1;
	Data.X2=src.Data.X2;
	Data.Y2=src.Data.Y2;
	Data.Z2=src.Data.Z2;
}

Box3D &Box3D::operator=(const Box3D &src)
{
	Data.X1=src.Data.X1;
	Data.Y1=src.Data.Y1;
	Data.Z1=src.Data.Z1;
	Data.X2=src.Data.X2;
	Data.Y2=src.Data.Y2;
	Data.Z2=src.Data.Z2;
	return *this;
}
bool	Box3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	Box3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
Box3D	Box3D::operator*(double v)	const
{
	return Box3D(Data.X1*v ,Data.Y1*v ,Data.Z1*v
				,Data.X2*v ,Data.Y2*v ,Data.Z2*v);
}
Box3D	Box3D::operator/(double v)	const
{
	return Box3D(Data.X1/v ,Data.Y1/v ,Data.Z1/v
				,Data.X2/v ,Data.Y2/v ,Data.Z2/v);
}
Box3D	Box3D::operator+(const Vector3D &s)	const
{
	return Box3D(Data.X1+s.Data.Vx ,Data.Y1+s.Data.Vy ,Data.Z1+s.Data.Vz
				,Data.X2+s.Data.Vx ,Data.Y2+s.Data.Vy ,Data.Z2+s.Data.Vz);
}
Box3D	Box3D::operator-(const Vector3D &s)	const
{
	return Box3D(Data.X1-s.Data.Vx ,Data.Y1-s.Data.Vy ,Data.Z1-s.Data.Vz
				,Data.X2-s.Data.Vx ,Data.Y2-s.Data.Vy ,Data.Z2-s.Data.Vz);
}
Box3D	&Box3D::operator+=(const Vector3D &s)
{
	Data.X1+=s.Data.Vx;
	Data.Y1+=s.Data.Vy;
	Data.Z1+=s.Data.Vz;
	Data.X2+=s.Data.Vx;
	Data.Y2+=s.Data.Vy;
	Data.Z2+=s.Data.Vz;
	return *this;
}
Box3D	&Box3D::operator-=(const Vector3D &s)
{
	Data.X1-=s.Data.Vx;
	Data.Y1-=s.Data.Vy;
	Data.Z1-=s.Data.Vz;
	Data.X2-=s.Data.Vx;
	Data.Y2-=s.Data.Vy;
	Data.Z2-=s.Data.Vz;
	return *this;
}
Box3D	&Box3D::operator*=(double v)
{
	Data.X1+=v;
	Data.Y1+=v;
	Data.Z1+=v;
	Data.X2+=v;
	Data.Y2+=v;
	Data.Z2+=v;
	return *this;
}
Box3D	&Box3D::operator/=(double v)
{
	Data.X1/=v;
	Data.Y1/=v;
	Data.Z1/=v;
	Data.X2/=v;
	Data.Y2/=v;
	Data.Z2/=v;
	return *this;
}

bool	Box3D::operator==(const Box3D &s)	const
{
	if(Data.X1==s.Data.X1
	&& Data.Y1==s.Data.Y1
	&& Data.Z1==s.Data.Z1
	&& Data.X2==s.Data.X2
	&& Data.Y2==s.Data.Y2
	&& Data.Z2==s.Data.Z2){
		return true;
	}
	return false;
}

bool	Box3D::GetCross(const VectorLine &s ,double &RetLineRate)	const
{
	Point3D	P1(Data.X1,Data.Y1,Data.Z1);
	Vector3D	Vx(Data.X2-Data.X1,0,0);
	Vector3D	Vy(0,Data.Y2-Data.Y1,0);
	Vector3D	Vz(0,0,Data.Z2-Data.Z1);
	double		Lenx=Vx.GetLength();
	double		Leny=Vy.GetLength();
	double		Lenz=Vz.GetLength();
	if(Lenx==0.0 || Leny==0.0 || Lenz==0.0)
		return false;
	UVector3D	Ux=Vx/Lenx;
	UVector3D	Uy=Vy/Leny;
	UVector3D	Uz=Vz/Lenz;
	FlatPlain3D	Lxy(P1,Ux,Uy);
	FlatPlain3D	Lyz(P1,Uy,Uz);
	FlatPlain3D	Lzx(P1,Uz,Ux);

	double RetLineParam  ;
	double RetPlainParamX;
	double RetPlainParamY;
	double	MinP=99999999;
	bool	Ret=false;
	if(Lxy.GetCross(s
				, RetLineParam
				, RetPlainParamX
				, RetPlainParamY)==true){
		double	f=fabs(RetPlainParamY);
		if(f<MinP
		&& 0<=RetPlainParamX && RetPlainParamX<Lenx
		&& 0<=RetPlainParamY && RetPlainParamY<Leny){
			MinP=f;
			RetLineRate=RetPlainParamY;
			Ret=true;
		}
	}
	if(Lyz.GetCross(s
				, RetLineParam
				, RetPlainParamX
				, RetPlainParamY)==true){
		double	f=fabs(RetPlainParamY);
		if(f<MinP
		&& 0<=RetPlainParamX && RetPlainParamX<Leny
		&& 0<=RetPlainParamY && RetPlainParamY<Lenz){
			MinP=f;
			RetLineRate=RetPlainParamY;
			Ret=true;
		}
	}
	if(Lzx.GetCross(s
				, RetLineParam
				, RetPlainParamX
				, RetPlainParamY)==true){
		double	f=fabs(RetPlainParamY);
		if(f<MinP
		&& 0<=RetPlainParamX && RetPlainParamX<Lenz
		&& 0<=RetPlainParamY && RetPlainParamY<Lenx){
			MinP=f;
			RetLineRate=RetPlainParamY;
			Ret=true;
		}
	}
	Point3D	P2(Data.X2,Data.Y2,Data.Z2);
	FlatPlain3D	Mxy(P2,-Ux,-Uy);
	FlatPlain3D	Myz(P2,-Uy,-Uz);
	FlatPlain3D	Mzx(P2,-Uz,-Ux);
	if(Mxy.GetCross(s
				, RetLineParam
				, RetPlainParamX
				, RetPlainParamY)==true){
		double	f=fabs(RetPlainParamY);
		if(f<MinP
		&& 0<=RetPlainParamX && RetPlainParamX<Lenx
		&& 0<=RetPlainParamY && RetPlainParamY<Leny){
			MinP=f;
			RetLineRate=RetPlainParamY;
			Ret=true;
		}
	}
	if(Myz.GetCross(s
				, RetLineParam
				, RetPlainParamX
				, RetPlainParamY)==true){
		double	f=fabs(RetPlainParamY);
		if(f<MinP
		&& 0<=RetPlainParamX && RetPlainParamX<Leny
		&& 0<=RetPlainParamY && RetPlainParamY<Lenz){
			MinP=f;
			RetLineRate=RetPlainParamY;
			Ret=true;
		}
	}
	if(Mzx.GetCross(s
				, RetLineParam
				, RetPlainParamX
				, RetPlainParamY)==true){
		double	f=fabs(RetPlainParamY);
		if(f<MinP
		&& 0<=RetPlainParamX && RetPlainParamX<Lenz
		&& 0<=RetPlainParamY && RetPlainParamY<Lenx){
			MinP=f;
			RetLineRate=RetPlainParamY;
			Ret=true;
		}
	}
	return Ret;
}

//----------------------------------------------------------------------------
	/*
	*	|a b c||t|		|X|
	*	|d e f||s|	=	|Y|
	*	|g h i||u|		|Z|
	* 
	*	at+bs+cu=X
	*	dt+es+fu=Y
	*	gt+hs+iu=Z
	* 
	*	adt+bds+cdu=Xd
	*	adt+aes+afu=Ya
	*		(bd-ae)s+(cd-af)u=Xd-Ya
	*	agt+bgs+cgu=Xg
	*	agt+ahs+aiu=Za
	*		(bg-ah)s+(cg-ai)u=Xg-Za
	*	(bd-ae)(bg-ah)s+(cd-af)(bg-ah)u=(Xd-Ya)(bg-ah)
	*	(bg-ah)(bd-ae)s+(cg-ai)(bd-ae)u=(Xg-Za)(bd-ae)
	*	{(cd-af)(bg-ah)-(cg-ai)(bd-ae)}u=(Xd-Ya)(bg-ah)-(Xg-Za)(bd-ae)
	*	(aafh-abfg-acdh-aaei+abdi+aceg)u=-Xadh-Yabg+Yaah+Xaeg+Zabd-Zaae
	*	(afh-bfg-cdh-aei+bdi+ceg)u=-Xdh-Ybg+Yah+Xeg+Zbd-Zae
	*	{a(fh-ei)+b(di-fg)+c(eg-dh)}u=X(eg-dh)+Y(ah-bg)+Z(bd-ae)
	*	{f(ah-bg)+i(bd-ae)+c(eg-dh)}u=X(eg-dh)+Y(ah-bg)+Z(bd-ae)
	* 
	*	aft+bfs+cfu=Xf
	*	dct+ces+cfu=Yc
	*		(af-dc)t+(bf-ce)s=Xf-Yc
	*	ait+bis+ciu=Xi
	*	cgt+chs+ciu=Zc
	*		(ai-cg)t+(bi-ch)s=Xi-Zc
	*	(af-dc)(bi-ch)t+(bf-ce)(bi-ch)s=(Xf-Yc)(bi-ch)
	*	(ai-cg)(bf-ce)t+(bf-ce)(bi-ch)s=(Xi-Zc)(bf-ce)	
	*	(cdh-bdi-afh+bfg-ceg+aei)t=-Xfh-Ybi+Ych+Xei+Zbf-Zce
	*	{c(dh-eg)+f(bg-ah)+i(ae-bd)}t=X(ei-fh)+Y(ch-bi)+Z(bf-ce)
	* 	{f(ah-bg)+i(bd-ae)+c(eg-dh)}t=X(fh-ei)+Y(bi-ch)+Z(ce-bf)
	* 
	*	(af-dc)(ai-cg)t+(bf-ce)(ai-cg)s=(Xf-Yc)(ai-cg)
	*	(ai-cg)(af-dc)t+(bi-ch)(af-dc)s=(Xi-Zc)(af-dc)
	*	(-aei-bfg+ceg+afh+bdi-cdh)s=-Xfg-Yai+Ycg+Xdi+Zaf-Zcd
	*	{f(ah-bg)+i(bd-ae)+c(eg-dh)}s=X(di-fg)+Y(cg-ai)+Z(af-cd)
	*/
inline	bool	Solve3x3(double a
						,double b
						,double c
						,double d
						,double e
						,double f
						,double g
						,double h
						,double i
						,double X
						,double Y
						,double Z
						,double &t
						,double &s
						,double &u)
{
	double	p=a*h-b*g;
	double	q=b*d-a*e;
	double	r=e*g-d*h;

	double	K=f*p+i*q+c*r;
	if(K==0.0)
		return false;
	u	=(X*r+Y*p+Z*q)/K;
	t	=(X*(f*h-e*i)+Y*(b*i-c*h)+Z*(c*e-b*f))/K;
	s	=(X*(d*i-f*g)+Y*(c*g-a*i)+Z*(a*f-c*d))/K;
	return true;
}

	/*
	*	|a b ||t|		|X|
	*	|c d ||s|	=	|Y|
	* 
	*	at+bs=X
	*	ct+ds=Y
	* 
	*	adt+bds=Xd
	*	bct+bds=Yb
	*		(ad-bc)t=Xd-Yb
	* 
	*	act+bcs=Xc
	*	act+ads=Ya
	*		(bc-ad)s=Xc-Ya
	*		(ad-bc)s=Ya-Xc
	*/
inline	bool	Solve2x2(double a
						,double b
						,double c
						,double d
						,double X
						,double Y
						,double &t
						,double &s)
{
	double	K=b*c-a*d;
	if(K==0.0)
		return false;
	t	=(X*d-Y*b)/K;
	s	=(Y*a-X*c)/K;
	return true;
}

//----------------------------------------------------------------------------

bool	FlatPlain3D::GetCross(const VectorLine &L
							, double &RetLineParam
							, double &RetPlainParamX
							, double &RetPlainParamY)	const
{
	/*	Point+Sx*t+Sy*s=L.Point+L.Vector*u
	*	Sx*t+Sy*s-L.Vector*u=L.Point-Point
	*	|a b c||t|		|X|
	*	|d e f||s|	=	|Y|
	*	|g h i||u|		|Z|
	* 
	*/

	if(Solve3x3(Sx.Data.Ux
				,Sy.Data.Ux
				,L.Vector.Data.Ux
				,Sx.Data.Uy
				,Sy.Data.Uy
				,L.Vector.Data.Uy
				,Sx.Data.Uz
				,Sy.Data.Uz
				,L.Vector.Data.Uz
				,L.Point.Data.X-Point.Data.X
				,L.Point.Data.Y-Point.Data.Y
				,L.Point.Data.Z-Point.Data.Z
				,RetPlainParamX
				,RetPlainParamY
				,RetLineParam)==false){
		return false;
	}
	return true;
}
//----------------------------------------------------------------------------
VectorLine::VectorLine(const VectorLine &src)
{
	Point	=src.Point;
	Vector	=src.Vector;
}

VectorLine	&VectorLine::operator=(const VectorLine &src)
{
	Point	=src.Point;
	Vector	=src.Vector;
	return *this;
}
bool	VectorLine::operator==(const VectorLine &src)	const
{
	if(Point==src.Point
	&& Vector==src.Vector)
		return true;
	return false;
}
	
bool	VectorLine::Save(QIODevice *f)
{
	if(Point.Save(f)==false)	return false;
	if(Vector.Save(f)==false)	return false;
	return true;
}

bool	VectorLine::Load(QIODevice *f)
{
	if(Point.Load(f)==false)	return false;
	if(Vector.Load(f)==false)	return false;
	return true;
}

//----------------------------------------------------------------------------
FlatPlain3D::FlatPlain3D(const FlatPlain3D &src)
{
	Point	=src.Point	;
	Sx		=src.Sx		;
	Sy		=src.Sy		;
}

FlatPlain3D	&FlatPlain3D::operator=(const FlatPlain3D &src)
{
	Point	=src.Point	;
	Sx		=src.Sx		;
	Sy		=src.Sy		;
	return *this;
}
	
bool	FlatPlain3D::Save(QIODevice *f)
{
	if(Point.Save(f)==false)	return false;
	if(Sx.Save(f)==false)		return false;
	if(Sy.Save(f)==false)		return false;
	return true;
}

bool	FlatPlain3D::Load(QIODevice *f)
{
	if(Point.Load(f)==false)	return false;
	if(Sx.Load(f)==false)		return false;
	if(Sy.Load(f)==false)		return false;
	return true;
}

//----------------------------------------------------------------------------

Canvas3D::Canvas3D(void)
{
	Data.CanvasWidth=0;
	Data.CanvasHeight=0;
	Data.EyeType	=_Parallel;
}

bool	Canvas3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

bool	Canvas3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

bool	Canvas3D::GetMovXY(double &Mx ,double &My)	const
{
	/*	CanvasXAxis	:	A=(Ax,Ay,Az)
	*	CanvasBAxis	:	B=(Bx,By,Bz)
	*	Q=P+At+Bs
	*	Q=(A~B)u=Cu
	*	P+At+Bs=Cu
	*	At+Bs-Cu=-P
	*	|a b c||t|		|X|
	*	|d e f||s|	=	|Y|
	*	|g h i||u|		|Z|
	*/
	Vector3D	C=Vector3D::CrossProduct(Data.CanvasXAxis,Data.CanvasYAxis);

	double	t,s,u;
	if(Solve3x3( Data.CanvasXAxis.Data.Vx
				,Data.CanvasYAxis.Data.Vx
				,-C.Data.Vx
				,Data.CanvasXAxis.Data.Vy
				,Data.CanvasYAxis.Data.Vy
				,-C.Data.Vy
				,Data.CanvasXAxis.Data.Vz
				,Data.CanvasYAxis.Data.Vz
				,-C.Data.Vz
				,-Data.CanvasOrigin.Data.X
				,-Data.CanvasOrigin.Data.Y
				,-Data.CanvasOrigin.Data.Z
				,t,s,u)==true){
		Mx=t;
		My=s;
		return true;
	}
	/*
	*	At+Bs=-P
	*/
	if(Solve2x2( Data.CanvasXAxis.Data.Vx
				,Data.CanvasYAxis.Data.Vx
				,Data.CanvasXAxis.Data.Vy
				,Data.CanvasYAxis.Data.Vy
				,-Data.CanvasOrigin.Data.X
				,-Data.CanvasOrigin.Data.Y
				,t,s)==true){
		Mx=t;
		My=s;
		return true;
	}
	Mx=0;
	My=0;
	return false;
}
void	Canvas3D::GetZoomRate(double &Zx,double &Zy)	const
{
	Zx=Data.CanvasXAxis.GetLength()/((double)Data.CanvasWidth);
	Zy=Data.CanvasYAxis.GetLength()/((double)Data.CanvasHeight);
}

//----------------------------------------------------------------------------

Reflection3D::Reflection3D(void)
{
	Data.DiffusionRate		=0.5;
	Data.TransparentRate	=0;
	Data.Refractive			=1.0;
	Data.TransparentColor=QColor(Qt::white).rgba();
}

bool	Reflection3D::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

bool	Reflection3D::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
	
bool	Surface3D::Save(QIODevice *f)
{
	if(Point.Save(f)==false)		return false;
	if(ForCamVector.Save(f)==false)	return false;
	if(Sx.Save(f)==false)			return false;
	if(Sy.Save(f)==false)			return false;
	return true;
}

bool	Surface3D::Load(QIODevice *f)
{
	if(Point.Load(f)==false)		return false;
	if(ForCamVector.Load(f)==false)	return false;
	if(Sx.Load(f)==false)			return false;
	if(Sy.Load(f)==false)			return false;
	return true;
}