#include "XTransform.h"
#include "XGeneralFunc.h"
#include "XDataComponent.h"
#include "XControlPoints.h"

TransformBase::TransformBase(void)
{
}
TransformBase::~TransformBase()
{
}

TransformBase	*TransformBase::MakeTransformParamControlPoints(const XYPointContainerWithName &Dst ,const XYPointContainerWithName &Src)
{
	if(Dst.GetCount()>=3 && Src.GetCount()>=3){
		const	XYPointWithName	*s1=Src[0];
		const	XYPointWithName	*s2=Src[1];
		const	XYPointWithName	*s3=Src[2];
		const	XYPointWithName	*d1=Dst[0];
		const	XYPointWithName	*d2=Dst[1];
		const	XYPointWithName	*d3=Dst[2];
		int	x1=s1->X;
		int	y1=s1->Y;
		int	x2=s2->X;
		int	y2=s2->Y;
		int	x3=s3->X;
		int	y3=s3->Y;
		int	X1=d1->X;
		int	Y1=d1->Y;
		int	X2=d2->X;
		int	Y2=d2->Y;
		int	X3=d3->X;
		int	Y3=d3->Y;

		double	M=(x2-x1)*(y3-y2)-(x3-x2)*(y2-y1);
		if(M==0.0)
			return NULL;
		TransformAffin	*f=new TransformAffin;
		f->Param[0]= ((X2-X1)*(y3-y2)-(X3-X2)*(y2-y1))/M;
		f->Param[1]=-((X2-X1)*(x3-x2)-(X3-X2)*(x2-x1))/M;
		f->Param[2]=X1-f->Param[0]*x1-f->Param[1]*y1;
		f->Param[3]= ((Y2-Y1)*(y3-y2)-(Y3-Y2)*(y2-y1))/M;
		f->Param[4]=-((Y2-Y1)*(x3-x2)-(Y3-Y2)*(x2-x1))/M;
		f->Param[5]=Y1-f->Param[3]*x1-f->Param[4]*y1;
		return f;
	}
	else
	if(Dst.GetCount()>=0 && Src.GetCount()>=0){
		TransformAffin	*f=new TransformAffin;
		f->Param[0]=1.0;
		f->Param[1]=0.0;
		f->Param[2]=0.0;
		f->Param[3]=0.0;
		f->Param[4]=1.0;
		f->Param[5]=0.0;
		return f;
	}
	
	return NULL;
}

TransformAffin::TransformAffin(void)
{
	Param[0]=1.0;
	Param[1]=0.0;
	Param[2]=0.0;
	Param[3]=0.0;
	Param[4]=1.0;
	Param[5]=0.0;
}
TransformAffin::TransformAffin(const TransformAffin &src)
{
	Param[0]=src.Param[0];
	Param[1]=src.Param[1];
	Param[2]=src.Param[2];
	Param[3]=src.Param[3];
	Param[4]=src.Param[4];
	Param[5]=src.Param[5];
}
TransformAffin::TransformAffin(double _Param[6])
{
	Param[0]=_Param[0];
	Param[1]=_Param[1];
	Param[2]=_Param[2];
	Param[3]=_Param[3];
	Param[4]=_Param[4];
	Param[5]=_Param[5];
}
TransformAffin::TransformAffin(double a ,double b ,double c ,double d ,double e ,double f)
{
	Param[0]=a;
	Param[1]=b;
	Param[2]=c;
	Param[3]=d;
	Param[4]=e;
	Param[5]=f;
}
TransformBase	*TransformAffin::clone(void)
{
	TransformAffin	*f=new TransformAffin(*this);
	return f;
}
TransformAffin	&TransformAffin::operator=(const TransformAffin &src)
{
	Param[0]=src.Param[0];
	Param[1]=src.Param[1];
	Param[2]=src.Param[2];
	Param[3]=src.Param[3];
	Param[4]=src.Param[4];
	Param[5]=src.Param[5];
	return *this;
}
TransformBase &TransformAffin::operator*=(const TransformBase &src)
{
	const	TransformAffin	*d=dynamic_cast<const TransformAffin *>(&src);

	if(d!=NULL){
		//ax+by+c
		//dx+ey+g
		//A(ax+by+c)+B(dx+ey+g)+C=(Aa+Bd)x+(Ab+Be)y+Ac+Bg+C
		//D(ax+by+c)+E(dx+ey+g)+G=(Da+Ed)x+(Db+Ee)y+Dc+Eg+G
		
		double	P[6];
		P[0]=Param[0]*d->Param[0]+Param[1]*d->Param[3];
		P[1]=Param[0]*d->Param[1]+Param[1]*d->Param[4];
		P[2]=Param[0]*d->Param[2]+Param[1]*d->Param[5]+Param[2];
		P[3]=Param[3]*d->Param[0]+Param[4]*d->Param[3];
		P[4]=Param[3]*d->Param[1]+Param[4]*d->Param[4];
		P[5]=Param[3]*d->Param[2]+Param[4]*d->Param[5]+Param[5];

		Param[0]=P[0];
		Param[1]=P[1];
		Param[2]=P[2];
		Param[3]=P[3];
		Param[4]=P[4];
		Param[5]=P[5];
	}
	return *this;
}
bool	TransformAffin::Reverse(void)
{
	double	M=Param[0]*Param[4]-Param[1]*Param[3];
	if(M!=0){
		double	P[6];
		P[0]=Param[4]/M;
		P[1]=-Param[1]/M;
		P[2]=(Param[1]*Param[5]-Param[2]*Param[4])/M;
		P[3]=-Param[3]/M;
		P[4]=Param[0]/M;
		P[5]=(Param[2]*Param[3]-Param[0]*Param[5])/M;

		Param[0]=P[0];
		Param[1]=P[1];
		Param[2]=P[2];
		Param[3]=P[3];
		Param[4]=P[4];
		Param[5]=P[5];
		return true;
	}
	return false;
}
bool	TransformAffin::Save(QIODevice *f)
{
	if(f->write((const char *)Param,sizeof(Param))!=sizeof(Param))
		return false;
	return true;
}
bool	TransformAffin::Load(QIODevice *f)
{
	if(f->read((char *)Param,sizeof(Param))!=sizeof(Param))
		return false;
	return true;
}
bool	TransformAffin::Transform(double X,double Y,double &RetX ,double &RetY)
{
	RetX=Param[0]*X+Param[1]*Y+Param[2];
	RetY=Param[3]*X+Param[4]*Y+Param[5];
	return true;
}
bool	TransformAffin::ReverseTransform(double X,double Y,double &RetX ,double &RetY)
{
	double	M=Param[0]*Param[4]-Param[1]*Param[3];
	if(M!=0){
		double	P[6];
		P[0]=Param[4]/M;
		P[1]=-Param[1]/M;
		P[2]=(Param[1]*Param[5]-Param[2]*Param[4])/M;
		P[3]=-Param[3]/M;
		P[4]=Param[0]/M;
		P[5]=(Param[2]*Param[3]-Param[0]*Param[5])/M;
		RetX=P[0]*X+P[1]*Y+P[2];
		RetY=P[3]*X+P[4]*Y+P[5];
		return true;
	}
	return false;
}
