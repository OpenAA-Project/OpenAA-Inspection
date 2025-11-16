/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XVector.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XVector.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XFlexArea.h"
#include "XPointer.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "XTransform.h"

bool	VectorItemBase::IsEqual(VectorItemBase *src)	const
{
	if(GetX()==src->GetX() && GetY()==src->GetY()){
		return true;
	}
	return false;
}

VectorLineBase::VectorLineBase(VectorLineBase &src)
{
	for(VectorItemBase *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		VectorItemBase *b=a->CreateItem();
		*b=*a;
		Items.AppendList(b);
	}
}
bool	VectorLineBase::Save(QIODevice *f)
{
	int64	N=Items.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(VectorItemBase *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	VectorLineBase::Load(QIODevice *f)
{
	int64	N;
	if(::Load(f,N)==false){
		return false;
	}
	Items.RemoveAll();
	for(int i=0;i<N;i++){
		VectorItemBase *c=CreateItem();
		if(c->Load(f)==false){
			return false;
		}
		Items.AppendList(c);
	}
	return true;
}

void	VectorLineBase::MoveTo(double dx ,double dy)
{
	for(VectorItemBase *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
		c->MoveTo(dx,dy);
	}
}

VectorLineBase	&VectorLineBase::operator=(VectorLineBase &src)
{
	Items.RemoveAll();
	for(VectorItemBase *s=src.Items.GetFirst();s!=NULL;s=s->GetNext()){
		VectorItemBase *d=src.CreateItem();
		d->Copy(s);
		Items.AppendList(d);
	}
	return *this;
}

bool	VectorLineBase::operator==(VectorLineBase &src)	const
{
	VectorItemBase *e=Items.GetFirst();
	VectorItemBase *s=src.Items.GetFirst();
	for(;s!=NULL && e!=NULL;s=s->GetNext(),e=e->GetNext()){
		if(s->IsEqual(e)==false){
			return false;
		}
	}
	if(s==NULL && e==NULL){
		return true;
	}
	return false;
}

bool	VectorLineBase::GetXY(int &x1,int &y1,int &x2,int &y2)	const
{
	x1=99999999;
	y1=99999999;
	x2=-99999999;
	y2=-99999999;
	bool	Flag=false;
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		if(x1>s->GetXInt()){
			x1=s->GetXInt();
		}
		if(y1>s->GetYInt()){
			y1=s->GetYInt();
		}
		if(x2<s->GetXInt()){
			x2=s->GetXInt();
		}
		if(y2<s->GetYInt()){
			y2=s->GetYInt();
		}
		Flag=true;
	}
	return Flag;
}

bool	VectorLineBase::GetXY(double &x1,double &y1,double &x2,double &y2)	const
{
	x1=99999999;
	y1=99999999;
	x2=-99999999;
	y2=-99999999;
	bool	Flag=false;
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		if(x1>s->GetXInt()){
			x1=s->GetX();
		}
		if(y1>s->GetYInt()){
			y1=s->GetY();
		}
		if(x2<s->GetXInt()){
			x2=s->GetX();
		}
		if(y2<s->GetYInt()){
			y2=s->GetY();
		}
		Flag=true;
	}
	return Flag;
}
bool	VectorLineBase::GetCenter(int &cx ,int &cy)	const
{
	int	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==false)
		return false;
	cx=(x1+x2)/2;
	cy=(y1+y2)/2;
	return true;
}
bool	VectorLineBase::GetCenter(double &cx ,double &cy)	const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==false)
		return false;
	cx=(x1+x2)/2.0;
	cy=(y1+y2)/2.0;
	return true;
}


bool	VectorLineBase::DrawImage(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate)
{
	bool	Ret=false;
	PData.setPen(Col);
	int	x1,y1,x2,y2;
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		VectorItemBase *t=s->GetNext();
		if(t==NULL){
			break;
		}
		x1=(s->GetX()+MovX)*ZoomRate;
		y1=(s->GetY()+MovY)*ZoomRate;
		x2=(t->GetX()+MovX)*ZoomRate;
		y2=(t->GetY()+MovY)*ZoomRate;
		if(x1<0 && x2<0){
			continue;
		}
		if(y1<0 && y2<0){
			continue;
		}
		if(x1>=IData.width() && x2>=IData.width()){
			continue;
		}
		if(y1>=IData.height() && y2>=IData.height()){
			continue;
		}
		PData.drawLine(x1,y1,x2,y2);
		Ret=true;
	}
	return Ret;
}

bool	VectorLineBase::DrawShift(int dx,int dy ,QImage &pnt ,QRgb Col	,double ZoomRate ,int movx ,int movy)
{
	QPainter PData(&pnt);
	return DrawImage(pnt ,PData ,Col,movx+dx ,movy+dy,ZoomRate);
}

VectorLineBase	*VectorLineBase::Create(int ID)
{
	if(ID==1){
		return new VectorLineDouble();
	}
	else if(ID==2){
		return new VectorLineVDouble();
	}
	else if(ID==3){
		return new VectorLineArc();
	}
	else if(ID==4){
		return new VectorLineEllipse();
	}
	else{
		return NULL;
	}
}

VectorLineBase	*VectorLineBase::CreateDup(void)
{
	int	id=GetID();
	VectorLineBase	*V=Create(id);
	*V=*this;
	return V;
}

double	VectorLineBase::GetLength(void)
{
	double	Sum=0.0;
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		VectorItemBase *t=s->GetNext();
		if(t==NULL){
			break;
		}
		double	x1=s->GetX();
		double	y1=s->GetY();
		double	x2=t->GetX();
		double	y2=t->GetY();
		Sum+=hypot(x1-x2,y1-y2);
	}
	return Sum;
}
void	VectorLineBase::MakeMap(BYTE **MaskBitmap ,int XByte ,int YLen)
{
	int	XLen=XByte*8;

	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		VectorItemBase *t=s->GetNext();
		if(t==NULL){
			break;
		}
		double	x1=s->GetX();
		double	y1=s->GetY();
		double	x2=t->GetX();
		double	y2=t->GetY();

		double	dx=x2-x1;
		double	dy=y2-y1;
		if(fabs(dx)>fabs(dy)){
			if(dx>0){
				int	ndx=dx;
				double	a=dy/dx;
				for(int i=0;i<=ndx;i++){
					int	x=x1+i;
					int	y=y1+a*i;
					if(0<=x && x<XLen && 0<=y && y<YLen){
						SetBmpBit1(MaskBitmap,x,y);
					}
				}
			}
			else if(dx<0){
				int	ndx=dx;
				double	a=dy/dx;
				for(int i=0;i>=ndx;i--){
					int	x=x1+i;
					int	y=y1+a*i;
					if(0<=x && x<XLen && 0<=y && y<YLen){
						SetBmpBit1(MaskBitmap,x,y);
					}
				}
			}
			else{
				return;
			}
		}
		else{
			if(dy>0){
				int	ndy=dy;
				double	a=dx/dy;
				for(int i=0;i<=ndy;i++){
					int	x=x1+a*i;
					int	y=y1+i;
					if(0<=x && x<XLen && 0<=y && y<YLen){
						SetBmpBit1(MaskBitmap,x,y);
					}
				}
			}
			else if(dy<0){
				int	ndy=dy;
				double	a=dx/dy;
				for(int i=0;i>=ndy;i--){
					int	x=x1+a*i;
					int	y=y1+i;
					if(0<=x && x<XLen && 0<=y && y<YLen){
						SetBmpBit1(MaskBitmap,x,y);
					}
				}
			}
		}
	}
}
bool	VectorLineBase::CheckOverlap(FlexArea &area)	const
{
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		VectorItemBase *t=s->GetNext();
		if(t==NULL){
			break;
		}
		double	x1=s->GetX();
		double	y1=s->GetY();
		double	x2=t->GetX();
		double	y2=t->GetY();

		if(area.CheckOverlapLine(x1,y1,x2,y2)==true){
			return true;
		}
	}
	return false;
}

double	VectorLineBase::GetDistance(int x ,int y)
{
	double	MinL=99999999.0;
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		VectorItemBase *t=s->GetNext();
		if(t==NULL){
			break;
		}
		double	x1=s->GetX();
		double	y1=s->GetY();
		double	x2=t->GetX();
		double	y2=t->GetY();

		double	L=::GetLengthLine2Point(x1,y1,x2,y2 ,(double)x,(double)y);
		if(L<MinL){
			MinL=L;
		}
	}
	return MinL;
}

void	VectorLineBase::AppendMoveBase(VectorLineBase *base)
{
	VectorItemBase	*b;
	while((b=base->Items.GetFirst())!=NULL){
		base->Items.RemoveList(b);
		Items.AppendList(b);
	}
}

void	VectorLineBase::Transform(TransformBase &Param)
{
	for(VectorItemBase *s=Items.GetFirst();s!=NULL;s=s->GetNext()){
		s->Transform(Param);
	}
}

//==============================================================
VectorItemInt::VectorItemInt(const VectorItemInt &src)
	:VectorItemBase(*((const VectorItemBase *)&src))
{
	X =src.X ;	
	Y =src.Y ;
}
VectorItemBase	*VectorItemInt::Clone(void)
{
	VectorItemInt	*c=new VectorItemInt(*this);
	return c;
}

bool	VectorItemInt::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	return true;
}
bool	VectorItemInt::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	return true;
}
VectorItemInt	&VectorItemInt::operator=(const VectorItemInt &src)
{
	VectorItemBase::operator=(*((VectorItemBase *)&src));
	X =src.X ;	
	Y =src.Y ;
	return *this;
}
void	VectorItemInt::Copy(VectorItemBase *src)
{
	VectorItemInt	*d=dynamic_cast<VectorItemInt *>(src);
	if(d!=NULL){
		X=d->GetX();
		Y=d->GetY();
	}
}
void	VectorItemInt::Transform(TransformBase &Param)
{
	double	tX;
	double	tY;
	Param.Transform(X,Y,tX ,tY);
	X=tX;
	Y=tY;
}
	
VectorLineInt::VectorLineInt(const VectorLineInt &src)
	:VectorLineBase(*((VectorLineBase *)&src))
{
}
VectorLineBase	*VectorLineInt::Clone(void)
{
	VectorLineInt	*c=new VectorLineInt();
	*c=*this;
	return c;
}

VectorLineInt	&VectorLineInt::operator=(const VectorLineInt &src)
{
	VectorLineBase::operator=(*((VectorLineBase *)&src));
	return *this;
}
bool	VectorLineInt::IsNull(void)	const
{
	if(VectorLineBase::IsNull()==true){
		return true;
	}

	VectorItemBase *d=Items.GetFirst();
	for(VectorItemBase *e=d->GetNext();e!=NULL;e=e->GetNext()){
		if(d->IsEqual(e)==true){
			return true;
		}
	}
	return false;
}

bool	VectorLineInt::CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const
{
	for(VectorItemBase *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		VectorItemBase *e=d->GetNext();
		if(e==NULL){
			break;
		}
		if(CheckOverlapRectLine(x1,y1,x2,y2
			,d->GetX(),d->GetY(),e->GetX(),e->GetY())==true){
			return true;
		}
	}
	return false;
}

bool	VectorLineInt::ClipArea(double rx1, double ry1 ,double rx2, double ry2)
{
	double	X1;
	double	Y1;
	double	X2;
	double	Y2;
	VectorItemInt	*dh;
	VectorItemInt	*eh;
	bool	Ret=false;
ReStart:;
	for(VectorItemBase *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		VectorItemBase *e=d->GetNext();
		if(e==NULL){
			break;
		}
		dh=dynamic_cast<VectorItemInt *>(d);
		eh=dynamic_cast<VectorItemInt *>(e);

		X1=dh->GetX();
		Y1=dh->GetY();
		X2=eh->GetX();
		Y2=eh->GetY();

		double	X[4],Y[4];
		int		Numb=0;

		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx1,ry1,rx1,ry2, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx1,ry2,rx2,ry2, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx2,ry2,rx2,ry1, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx2,ry1,rx1,ry1, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(rx1<=X1 && X1<rx2 && ry1<=Y1 && Y1<ry2){
			if(Numb==0){
				continue;
			}
			else if(Numb>=1){
				eh->SetXY(X[0],Y[0]);
				Ret=true;
				continue;
			}
		}
		else{
			if(Numb==0){
				Items.RemoveList(e);
				Ret=true;
				delete	e;
				goto	ReStart;
			}
			else if(Numb==1){
				dh->SetXY(X[0],Y[0]);
				Ret=true;
				continue;
			}
			else if(Numb==2){
				dh->SetXY(X[0],Y[0]);
				eh->SetXY(X[1],Y[1]);
				Ret=true;
			}
			else if(Numb>=3){
				dh->SetXY(X[0],Y[0]);
				for(int i=1;i<Numb;i++){
					if(X[0]!=X[i] || Y[0]!=Y[i]){
						eh->SetXY(X[i],Y[i]);
					}
				}
				Ret=true;
			}
		}
	}
	return Ret;
}
void	VectorLineInt::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)
{
	double	X1;
	double	Y1;
	double	X2;
	double	Y2;
	VectorItemInt	*dh;
	VectorItemInt	*eh;

	for(VectorItemBase *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		VectorItemBase *e=d->GetNext();
		if(e==NULL){
			break;
		}
		dh=dynamic_cast<VectorItemInt *>(d);
		eh=dynamic_cast<VectorItemInt *>(e);

		X1=(dh->GetX()+movx)*ZoomRate;
		Y1=(dh->GetY()+movy)*ZoomRate;
		X2=(eh->GetX()+movx)*ZoomRate;
		Y2=(eh->GetY()+movy)*ZoomRate;
		pnt.drawLine(X1,Y1,X2,Y2);
	}
}

//==============================================================
VectorItemDouble::VectorItemDouble(const VectorItemDouble &src)
	:VectorItemBase(*((const VectorItemBase *)&src))
{
	X =src.X ;	
	Y =src.Y ;
}

VectorItemBase	*VectorItemDouble::Clone(void)
{
	VectorItemDouble	*c=new VectorItemDouble(*this);
	return c;
}
bool	VectorItemDouble::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	return true;
}
bool	VectorItemDouble::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	return true;
}
VectorItemDouble	&VectorItemDouble::operator=(const VectorItemDouble &src)
{
	VectorItemBase::operator=(*((VectorItemBase *)&src));
	X =src.X ;	
	Y =src.Y ;
	return *this;
}
void	VectorItemDouble::Copy(VectorItemBase *src)
{
	VectorItemDouble	*d=dynamic_cast<VectorItemDouble *>(src);
	if(d!=NULL){
		X=d->GetX();
		Y=d->GetY();
	}
}
void	VectorItemDouble::Transform(TransformBase &Param)
{
	double	tX;
	double	tY;
	Param.Transform(X,Y,tX ,tY);
	X=tX;
	Y=tY;
}
	
VectorLineDouble::VectorLineDouble(const VectorLineDouble &src)
	:VectorLineBase(*((VectorLineBase *)&src))
{
}
VectorLineBase	*VectorLineDouble::Clone(void)
{
	VectorLineDouble	*c=new VectorLineDouble();
	*c=*this;
	return c;
}

VectorLineDouble	&VectorLineDouble::operator=(const VectorLineDouble &src)
{
	VectorLineBase::operator=(*((VectorLineBase *)&src));
	return *this;
}
bool	VectorLineDouble::IsNull(void)	const
{
	if(VectorLineBase::IsNull()==true){
		return true;
	}

	VectorItemBase *d=Items.GetFirst();
	for(VectorItemBase *e=d->GetNext();e!=NULL;e=e->GetNext()){
		if(d->IsEqual(e)==true){
			return true;
		}
	}
	return false;
}

bool	VectorLineDouble::CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const
{
	for(VectorItemBase *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		VectorItemBase *e=d->GetNext();
		if(e==NULL){
			break;
		}
		if(CheckOverlapRectLine(x1,y1,x2,y2
			,d->GetX(),d->GetY(),e->GetX(),e->GetY())==true){
			return true;
		}
	}
	return false;
}

bool	VectorLineDouble::ClipArea(double rx1, double ry1 ,double rx2, double ry2)
{
	double	X1;
	double	Y1;
	double	X2;
	double	Y2;
	VectorItemDouble	*dh;
	VectorItemDouble	*eh;
	bool	Ret=false;
ReStart:;
	for(VectorItemBase *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		VectorItemBase *e=d->GetNext();
		if(e==NULL){
			break;
		}
		dh=dynamic_cast<VectorItemDouble *>(d);
		eh=dynamic_cast<VectorItemDouble *>(e);

		X1=dh->GetX();
		Y1=dh->GetY();
		X2=eh->GetX();
		Y2=eh->GetY();

		double	X[4],Y[4];
		int		Numb=0;

		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx1,ry1,rx1,ry2, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx1,ry2,rx2,ry2, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx2,ry2,rx2,ry1, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(GetCrossInnerPoint(X1,Y1,X2,Y2,rx2,ry1,rx1,ry1, X[Numb] ,Y[Numb])==true){
			Numb++;
		}
		if(rx1<=X1 && X1<rx2 && ry1<=Y1 && Y1<ry2){
			if(Numb==0){
				continue;
			}
			else if(Numb>=1){
				eh->SetXY(X[0],Y[0]);
				Ret=true;
				continue;
			}
		}
		else{
			if(Numb==0){
				Items.RemoveList(e);
				Ret=true;
				delete	e;
				goto	ReStart;
			}
			else if(Numb==1){
				dh->SetXY(X[0],Y[0]);
				Ret=true;
				continue;
			}
			else if(Numb==2){
				dh->SetXY(X[0],Y[0]);
				eh->SetXY(X[1],Y[1]);
				Ret=true;
			}
			else if(Numb>=3){
				dh->SetXY(X[0],Y[0]);
				for(int i=1;i<Numb;i++){
					if(X[0]!=X[i] || Y[0]!=Y[i]){
						eh->SetXY(X[i],Y[i]);
					}
				}
				Ret=true;
			}
		}
	}
	return Ret;
}
void	VectorLineDouble::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)
{
	double	X1;
	double	Y1;
	double	X2;
	double	Y2;
	VectorItemDouble	*dh;
	VectorItemDouble	*eh;

	for(VectorItemBase *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		VectorItemBase *e=d->GetNext();
		if(e==NULL){
			break;
		}
		dh=dynamic_cast<VectorItemDouble *>(d);
		eh=dynamic_cast<VectorItemDouble *>(e);

		X1=(dh->GetX()+movx)*ZoomRate;
		Y1=(dh->GetY()+movy)*ZoomRate;
		X2=(eh->GetX()+movx)*ZoomRate;
		Y2=(eh->GetY()+movy)*ZoomRate;
		pnt.drawLine(X1,Y1,X2,Y2);
	}
}


VectorLineVDouble::VectorLineVDouble(const VectorLineVDouble &src)
	:VectorLineBase(*((VectorLineBase *)&src))
{
}
VectorLineBase	*VectorLineVDouble::Clone(void)
{
	VectorLineVDouble	*c=new VectorLineVDouble();
	*c=*this;
	return c;
}

//==============================================================
VectorItemVDouble::VectorItemVDouble(const VectorItemVDouble &src)
	:VectorItemBase(*((const VectorItemBase *)&src))
{
	X =src.X ;	
	Y =src.Y ;
	Vx=src.Vx;
	Vy=src.Vy;
}
VectorItemBase	*VectorItemVDouble::Clone(void)
{
	VectorItemVDouble	*c=new VectorItemVDouble(*this);
	return c;
}
bool	VectorItemVDouble::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	if(::Save(f,Vx)==false){
		return false;
	}
	if(::Save(f,Vy)==false){
		return false;
	}
	return true;
}
bool	VectorItemVDouble::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	if(::Load(f,Vx)==false){
		return false;
	}
	if(::Load(f,Vy)==false){
		return false;
	}
	return true;
}

void	VectorItemVDouble::Copy(VectorItemBase *src)
{
	VectorItemVDouble	*d=dynamic_cast<VectorItemVDouble *>(src);
	if(d!=NULL){
		X=d->GetX();
		Y=d->GetY();
		Vx=d->Vx;
		Vy=d->Vy;
	}
}
void	VectorItemVDouble::Transform(TransformBase &Param)
{
	double	tX;
	double	tY;
	Param.Transform(X,Y,tX,tY);
	X=tX;
	Y=tY;

	double	tVx;
	double	tVy;
	Param.Transform(Vx,Vy,tVx,tVy);
	double	Len=hypot(tVx,tVy);
	if(Len>0){
		Vx=tVx/Len;
		Vy=tVy/Len;
	}
}
VectorItemVDouble	&VectorItemVDouble::operator=(const VectorItemVDouble &src)
{
	VectorItemBase::operator=(*((VectorItemBase *)&src));
	X =src.X ;	
	Y =src.Y ;
	Vx=src.Vx;
	Vy=src.Vy;
	return *this;
}
//==============================================================
VectorItemArc::VectorItemArc(const VectorItemArc &src)
	:VectorItemBase(*((const VectorItemBase *)&src))
{
	X =src.X ;	
	Y =src.Y ;
}
VectorItemBase	*VectorItemArc::Clone(void)
{
	VectorItemArc	*c=new VectorItemArc(*this);
	return c;
}
bool	VectorItemArc::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	return true;
}
bool	VectorItemArc::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	return true;
}
void	VectorItemArc::Copy(VectorItemBase *src)
{
	VectorItemArc	*d=dynamic_cast<VectorItemArc *>(src);
	if(d!=NULL){
		X=d->GetX();
		Y=d->GetY();
	}
}
VectorItemArc	&VectorItemArc::operator=(const VectorItemArc &src)
{
	VectorItemBase::operator=(*((VectorItemBase *)&src));
	X =src.X ;	
	Y =src.Y ;
	return *this;
}
void	VectorItemArc::Transform(TransformBase &Param)
{
	double	tX;
	double	tY;
	Param.Transform(X,Y,tX,tY);
	X=tX;
	Y=tY;
}
VectorLineBase	*VectorLineArc::Clone(void)
{
	VectorLineArc	*c=new VectorLineArc();
	*c=*this;
	return c;
}
void	VectorLineArc::SetPoints(double x1, double y1 ,double x2, double y2 ,double x3, double y3)
{
	VectorItemArc	*d1=new VectorItemArc(x1,y1);
	VectorItemArc	*d2=new VectorItemArc(x2,y2);
	VectorItemArc	*d3=new VectorItemArc(x3,y3);
	AppendItemBase(d1);
	AppendItemBase(d2);
	AppendItemBase(d3);
}
bool	VectorLineArc::CheckOverlapRectangle(double px1 ,double py1 ,double px2 ,double py2)	const
{
	VectorItemBase	*d1=Items[0];
	VectorItemBase	*d2=Items[1];
	VectorItemBase	*d3=Items[2];
	if(d1==NULL || d2==NULL || d3==NULL){
		return false;
	}
	double	x1=d1->GetX();
	double	y1=d1->GetY();
	double	x2=d2->GetX();
	double	y2=d2->GetY();
	double	x3=d3->GetX();
	double	y3=d3->GetY();

	if(px1<=x1 && x1<=px2 && py1<=y1 && y1<=py2){
		return true;
	}
	if(px1<=x2 && x2<=px2 && py1<=y2 && y2<=py2){
		return true;
	}
	if(px1<=x3 && x3<=px2 && py1<=y3 && y3<=py2){
		return true;
	}
	return false;
}

bool	VectorLineArc::IsNull(void)	const
{
	if(VectorLineBase::IsNull()==true){
		return true;
	}

	VectorItemBase *d=Items.GetFirst();
	for(VectorItemBase *e=d->GetNext();e!=NULL;e=e->GetNext()){
		if(d->IsEqual(e)==true){
			return true;
		}
	}
	return false;
}

bool	VectorLineArc::ClipArea(double x1, double y1 ,double x2, double y2)
{
	return false;
}

void	VectorLineArc::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)
{
	double Cx, Cy ,R;
	double StartS ,EndS;

	if(GetArc(Cx, Cy ,R, StartS ,EndS)==false){
		return;
	}
	double	s=EndS-StartS;
	while(s<0){
		s+=2.0*M_PI;
	}
	pnt.drawArc ( (Cx-R+movx)*ZoomRate, (Cy-R+movy)*ZoomRate, R*2.0*ZoomRate, R*2.0*ZoomRate
		,(int)16*360*(1.0-EndS/(2.0*M_PI)) 
		,(int)(s*16*360/(2.0*M_PI)));

}
	
void	VectorLineArc::SetArc(double Cx, double Cy ,double R
							, double StartS ,double EndS)
{
	Items.RemoveAll();

	double	CosS1=cos(StartS);
	double	SinS1=sin(StartS);
	double	CosS2=cos((StartS+EndS)/2.0);
	double	SinS2=sin((StartS+EndS)/2.0);
	double	CosS3=cos(EndS);
	double	SinS3=sin(EndS);

	double	x1=Cx+R*CosS1;
	double	y1=Cy+R*SinS1;
	double	x2=Cx+R*CosS2;
	double	y2=Cy+R*SinS2;
	double	x3=Cx+R*CosS3;
	double	y3=Cy+R*SinS3;

	VectorItemArc	*d1=(VectorItemArc *)CreateItem();
	VectorItemArc	*d2=(VectorItemArc *)CreateItem();
	VectorItemArc	*d3=(VectorItemArc *)CreateItem();
	d1->SetXY(x1,y1);
	d2->SetXY(x2,y2);
	d3->SetXY(x3,y3);

	AppendItemBase(d1);
	AppendItemBase(d2);
	AppendItemBase(d3);
}

bool	VectorLineArc::GetArc(double &Cx, double &Cy ,double &R
							, double &StartS ,double &EndS)
{
	VectorItemBase	*d1=Items[0];
	VectorItemBase	*d2=Items[1];
	VectorItemBase	*d3=Items[2];
	if(d1==NULL || d2==NULL || d3==NULL){
		return false;
	}
	double	x1=d1->GetX();
	double	y1=d1->GetY();
	double	x2=d2->GetX();
	double	y2=d2->GetY();
	double	x3=d3->GetX();
	double	y3=d3->GetY();

	double	Dx12	=x2-x1;
	double	Dy12	=y2-y1;
	double	E12		=x2*x2 - x1*x1 + y2*y2 - y1*y1;
	double	Dx23	=x3-x2;
	double	Dy23	=y3-y2;
	double	E23		=x3*x3 - x2*x2 + y3*y3 - y2*y2;

	double	M=Dx12*Dy23-Dx23*Dy12;

	if(fabs(M)<0.00001){
		return false;
	}
	Cx=(E12*Dy23-E23*Dy12)/(2.0*M);
	Cy=(E12*Dx23-E23*Dx12)/(-2.0*M);
	R=hypot(x1-Cx,y1-Cy);

	StartS	=GetSita(x1-Cx ,y1-Cy);
	EndS	=GetSita(x3-Cx ,y3-Cy);

	return true;
}

//==============================================================
VectorItemEllipse::VectorItemEllipse(const VectorItemEllipse &src)
	:VectorItemBase(*((const VectorItemBase *)&src))
{
	X =src.X ;	
	Y =src.Y ;
}
VectorItemBase	*VectorItemEllipse::Clone(void)
{
	VectorItemEllipse	*c=new VectorItemEllipse(*this);
	return c;
}
bool	VectorItemEllipse::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	return true;
}
bool	VectorItemEllipse::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	return true;
}
void	VectorItemEllipse::Copy(VectorItemBase *src)
{
	VectorItemEllipse	*d=dynamic_cast<VectorItemEllipse *>(src);
	if(d!=NULL){
		X=d->GetX();
		Y=d->GetY();
	}
}
VectorItemEllipse	&VectorItemEllipse::operator=(const VectorItemEllipse &src)
{
	VectorItemBase::operator=(*((VectorItemBase *)&src));
	X =src.X ;	
	Y =src.Y ;
	return *this;
}
void	VectorItemEllipse::Transform(TransformBase &Param)
{
	double	tX;
	double	tY;
	Param.Transform(X,Y,tX,tY);
	X=tX;
	Y=tY;
}
VectorLineBase	*VectorLineEllipse::Clone(void)
{
	VectorLineEllipse	*c=new VectorLineEllipse();
	*c=*this;
	return c;
}
void	VectorLineEllipse::SetPoints(double x1, double y1 ,double x2, double y2 ,double x3, double y3 ,double x4, double y4)
{
	double	Top		=min(min(y1,y2),min(y3,y4));
	double	Bottom	=max(max(y1,y2),max(y3,y4));
	double	Left	=min(min(x1,x2),min(x3,x4));
	double	Right	=max(max(x1,x2),max(x3,x4));

	double	Cx=(Left+Right)/2.0;
	double	Cy=(Top+Bottom)/2.0;

	VectorItemArc	*d1=new VectorItemArc(Cx,Top);
	VectorItemArc	*d2=new VectorItemArc(Cx,Bottom);
	VectorItemArc	*d3=new VectorItemArc(Left,Cy);
	VectorItemArc	*d4=new VectorItemArc(Right,Cy);
	AppendItemBase(d1);
	AppendItemBase(d2);
	AppendItemBase(d3);
	AppendItemBase(d4);
}
bool	VectorLineEllipse::CheckOverlapRectangle(double px1 ,double py1 ,double px2 ,double py2)	const
{
	VectorItemBase	*d1=Items[0];
	VectorItemBase	*d2=Items[1];
	VectorItemBase	*d3=Items[2];
	VectorItemBase	*d4=Items[3];
	if(d1==NULL || d2==NULL || d3==NULL || d4==NULL){
		return false;
	}
	double	x1=d1->GetX();
	double	y1=d1->GetY();
	double	x2=d2->GetX();
	double	y2=d2->GetY();
	double	x3=d3->GetX();
	double	y3=d3->GetY();
	double	x4=d4->GetX();
	double	y4=d4->GetY();

	if(px1<=x1 && x1<=px2 && py1<=y1 && y1<=py2){
		return true;
	}
	if(px1<=x2 && x2<=px2 && py1<=y2 && y2<=py2){
		return true;
	}
	if(px1<=x3 && x3<=px2 && py1<=y3 && y3<=py2){
		return true;
	}
	if(px1<=x4 && x4<=px2 && py1<=y4 && y4<=py2){
		return true;
	}
	return false;
}

bool	VectorLineEllipse::IsNull(void)	const
{
	if(VectorLineBase::IsNull()==true){
		return true;
	}

	VectorItemBase *d=Items.GetFirst();
	for(VectorItemBase *e=d->GetNext();e!=NULL;e=e->GetNext()){
		if(d->IsEqual(e)==true){
			return true;
		}
	}
	return false;
}

bool	VectorLineEllipse::ClipArea(double x1, double y1 ,double x2, double y2)
{
	return false;
}

void	VectorLineEllipse::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)
{
	double Cx, Cy ,Rx ,Ry;

	if(GetEllipse(Cx, Cy ,Rx ,Ry)==false){
		return;
	}
	pnt.drawArc ( (Cx-Rx+movx)*ZoomRate, (Cy-Ry+movy)*ZoomRate, Rx*2.0*ZoomRate, Ry*2.0*ZoomRate
		,0
		,16*360-1);

}
	
void	VectorLineEllipse::SetEllipse(	double Cx, double Cy ,double Rx ,double Ry)
{
	Items.RemoveAll();


	VectorItemArc	*d1=(VectorItemArc *)CreateItem();
	VectorItemArc	*d2=(VectorItemArc *)CreateItem();
	VectorItemArc	*d3=(VectorItemArc *)CreateItem();
	VectorItemArc	*d4=(VectorItemArc *)CreateItem();
	d1->SetXY(Cx-Rx	,Cy);
	d2->SetXY(Cx	,Cy-Ry);
	d3->SetXY(Cx+Rx	,Cy);
	d4->SetXY(Cx	,Cy+Ry);

	AppendItemBase(d1);
	AppendItemBase(d2);
	AppendItemBase(d3);
	AppendItemBase(d4);
}

bool	VectorLineEllipse::GetEllipse(	double &Cx, double &Cy ,double &Rx ,double &Ry)
{
	VectorItemBase	*d1=Items[0];
	VectorItemBase	*d2=Items[1];
	VectorItemBase	*d3=Items[2];
	VectorItemBase	*d4=Items[3];
	if(d1==NULL || d2==NULL || d3==NULL || d4==NULL){
		return false;
	}
	double	x1=d1->GetX();
	double	y1=d1->GetY();
	double	x2=d2->GetX();
	double	y2=d2->GetY();
	double	x3=d3->GetX();
	double	y3=d3->GetY();
	double	x4=d4->GetX();
	double	y4=d4->GetY();

	double	Top		=min(min(y1,y2),min(y3,y4));
	double	Bottom	=max(max(y1,y2),max(y3,y4));
	double	Left	=min(min(x1,x2),min(x3,x4));
	double	Right	=max(max(x1,x2),max(x3,x4));

	Cx=(Left+Right)/2.0;
	Cy=(Top+Bottom)/2.0;
	Rx=Right-Cx;
	Ry=Bottom-Cy;
	return true;
}
