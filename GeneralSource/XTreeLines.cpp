#include "XTypeDef.h"
#include <cmath>
#include "XTreeLines.h"
#include "XGeneralFunc.h"
#include "swap.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XCrossObj.h"


bool	TreeLine::Save(QIODevice *f)
{
	int32	N=NPListPack<TreePointList>::GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	TreeLine::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		TreePointList *a=new TreePointList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

void	TreeLine::DeleteNoise(int NoiseDot)
{
	//端部が短いノードを消す
	int32	N=NPListPack<TreePointList>::GetNumber();
	if(N<=NoiseDot){
		RemoveAll();
	}
	//２こ進んでも隣のピクセルの時、次のノードを削除
	/*
	bool	Changed;
	do{
		Changed=false;
		for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
			TreePointList *b=a->GetNext();
			if(b!=NULL){
				TreePointList *c=b->GetNext();
				if(c!=NULL){
					if(abs(a->GetX()-c->GetX())<=1 && abs(a->GetY()-c->GetY())<=1){
						if(b->GetOtherNode().NPListPack<TreePointList>::GetFirst()==NULL){
							RemoveList(b);
							delete	b;
							//Changed=true;
						}
						else{
							RemoveList(b);
							a->GetOtherNode().AppendList(b);
							//Changed=true;
						}
					}
				}
			}
		}
	}while(Changed==true);
	*/

	for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		a->GetOtherNode().DeleteNoise(NoiseDot);
	}

	if((NPListPack<TreePointList>::GetFirst())!=NULL && (NPListPack<TreePointList>::GetFirst())->GetOtherNode().NPListPack<TreePointList>::GetFirst()!=NULL){
		TreeLine	Tmp;
		for(;;){
			TreePointList *a=(NPListPack<TreePointList>::GetFirst())->GetOtherNode().NPListPack<TreePointList>::GetLast();
			if(a==NULL){
				break;
			}
			(NPListPack<TreePointList>::GetFirst())->GetOtherNode().RemoveList(a);
			Tmp.AppendList(a);
		}
		InsertTop(Tmp);
	}
}
double	TreeLine::GetMaxLength(void)	const
{
	TreePointList *a=NPListPack<TreePointList>::GetFirst();
	if(a==NULL){
		return 0;
	}
	return a->GetMaxLength();
}
double	TreeLine::GetTotalLength(void)	const
{
	TreePointList *a=NPListPack<TreePointList>::GetFirst();
	if(a==NULL){
		return 0;
	}
	return a->GetTotalLength();
}

double	TreeLine::GetDistance(double x ,double y)	const
{
	double	MinLen=9999999999;
	for(TreePointList *t=NPListPack<TreePointList>::GetFirst();t!=NULL;t=t->GetNext()){
		TreePointList *s=t->GetNext();
		if(s!=NULL){
			double	D=GetLengthLine2Point((double)t->GetX(),(double)t->GetY(),(double)s->GetX(),(double)s->GetY()
						,x  ,y);
			if(MinLen>D){
				MinLen=D;
			}
		}
	}
	for(TreePointList *t=NPListPack<TreePointList>::GetFirst();t!=NULL;t=t->GetNext()){
		double	D=t->GetOtherNode().GetDistance(x,y);
		if(MinLen>D){
			MinLen=D;
		}
	}
	return MinLen;
}

bool	TreeLine::GetXY(int &x1,int &y1,int &x2,int &y2)	const
{
	x1=99999999;
	y1=99999999;
	x2=-99999999;
	y2=-99999999;
	bool	Ret=false;
	for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetXY(x1,y1,x2,y2)==true){
			Ret=true;
		}
	}
	return Ret;
}

bool	TreeLine::IsNull(void)	const
{
	TreePointList *a=NPListPack<TreePointList>::GetFirst();
	if(a==NULL){
		return true;
	}
	return false;
}

void	TreeLine::Draw(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate)
{
	int	x1,y1,x2,y2;
	for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		QColor	VCol(qRed(Col)*a->GetLevel()/255,qGreen(Col)*a->GetLevel()/255,qBlue(Col)*a->GetLevel()/255);
		PData.setPen(VCol);
		if(a->GetLevel()>0){
			TreePointList *b=a->GetNext();
			if(b==NULL){
				break;
			}
			x1=(a->GetX()+MovX)*ZoomRate;
			y1=(a->GetY()+MovY)*ZoomRate;
			x2=(b->GetX()+MovX)*ZoomRate;
			y2=(b->GetY()+MovY)*ZoomRate;
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
		}
		if(a->GetOtherNode().IsNull()==false){
			a->Draw(IData ,PData ,Col,MovX ,MovY ,ZoomRate);
		}
	}
}
void	TreeLine::DrawCircleOnLine(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate,int R)
{
	int	x1,y1,x2,y2;
	int	R2=R+R;
	if(R2==0)
		R2=1;
	PData.setPen(QColor(Col));
	for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLevel()>0){
			QColor	VCol(qRed(Col)*a->GetLevel()/255,qGreen(Col)*a->GetLevel()/255,qBlue(Col)*a->GetLevel()/255);
			PData.setPen(VCol);
			TreePointList *b=a->GetNext();
			if(b==NULL){
				break;
			}
			x1=(a->GetX()+MovX)*ZoomRate;
			y1=(a->GetY()+MovY)*ZoomRate;
			x2=(b->GetX()+MovX)*ZoomRate;
			y2=(b->GetY()+MovY)*ZoomRate;

			int	dx=b->GetX()-a->GetX();
			int	dy=b->GetY()-a->GetY();
			double	L=hypot(dx,dy);
			if(L<0.000001)
				continue;
			double	hx=dx/L;
			double	hy=dy/L;
			int	N=(L*ZoomRate+R2-1)/R2;
			for(int i=0;i<N;i++){
				int	x=x1+hx*i*R2;
				int	y=y1+hy*i*R2;
				if(0<=(x-R) && (x+R)<IData.width() && 0<=(y-R) && (y+R)<IData.height()){
					PData.drawEllipse(x-R,y-R,R2,R2);
				}
			}
		}
	}
}

void	TreeLine::MoveTo(int dx ,int dy)
{
	for(TreePointList *a=NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveTo(dx ,dy);
	}
}

TreeLine	&TreeLine::operator=(TreeLine &src)
{
	RemoveAll();
	return operator+=(src);
}

TreeLine	&TreeLine::operator=(const TreeLine &src)
{
	RemoveAll();
	return operator+=(*((TreeLine *)&src));
}
TreeLine	&TreeLine::operator=(VectorLineBase &src)
{
	RemoveAll();
	for(VectorItemBase	*a=src.GetFirstItem();a!=NULL;a=a->GetNext()){
		TreePointList *b=new TreePointList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
TreeLine	&TreeLine::operator+=(TreeLine &src)
{
	for(TreePointList *a=src.NPListPack<TreePointList>::GetFirst();a!=NULL;a=a->GetNext()){
		TreePointList *b=new TreePointList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

TreePointList::TreePointList(const TreePointList &src)
{	
	X			=src.X;
	Y			=src.Y;
	Level		=src.Level;
	OtherNode	=src.OtherNode;
}

bool	TreePointList::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	if(::Save(f,Level)==false){
		return false;
	}
	if(OtherNode.Save(f)==false){
		return false;
	}
	return true;
}

bool	TreePointList::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	if(::Load(f,Level)==false){
		return false;
	}
	if(OtherNode.Load(f)==false){
		return false;
	}
	return true;
}

double	TreePointList::GetMaxLength(void)	const
{
	double	Ret=0;
	if(Level>0){
		TreePointList *a=GetNext();
		if(a!=NULL){
			Ret=mhypot(X-a->GetX(),Y-a->GetY())+a->GetMaxLength();
		}
	}
	if(OtherNode.NPListPack<TreePointList>::GetFirst()!=NULL){
		double	CRet=OtherNode.GetMaxLength();
		if(Ret>CRet){
			return Ret;
		}
		else{
			return CRet;
		}
	}
	return Ret;
}
double	TreePointList::GetTotalLength(void)	const
{
	double	Ret=0;
	if(Level>0){
		TreePointList *a=GetNext();
		if(a!=NULL){
			Ret=mhypot(X-a->GetX(),Y-a->GetY())+a->GetTotalLength();
		}
	}
	if(OtherNode.NPListPack<TreePointList>::GetFirst()!=NULL){
		double	CRet=OtherNode.GetTotalLength();
		return CRet+Ret;
	}
	return Ret;
}

bool	TreePointList::GetXY(int &x1,int &y1,int &x2,int &y2)	const
{
	x1=min(x1,X);
	y1=min(y1,Y);
	x2=max(x2,X);
	y2=max(y2,Y);
	int rx1,ry1,rx2,ry2;
	if(OtherNode.NPListPack<TreePointList>::GetFirst()!=NULL){
		if(OtherNode.GetXY(rx1,ry1,rx2,ry2)==true){
			x1=min(x1,rx1);
			y1=min(y1,ry1);
			x2=max(x2,rx2);
			y2=max(y2,ry2);
		}
	}
	return true;
}

void	TreePointList::MoveTo(int dx ,int dy)
{
	X+=dx;
	Y+=dy;
	OtherNode.MoveTo(dx ,dy);
}

void	TreePointList::Draw(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate)
{
	OtherNode.Draw(IData ,PData ,Col,MovX ,MovY ,ZoomRate);
}

void	TreePointList::DrawCircleOnLine(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate,int R)
{
	OtherNode.DrawCircleOnLine(IData ,PData ,Col,MovX ,MovY ,ZoomRate,R);
}

TreePointList	&TreePointList::operator=(const TreePointList &src)
{
	X=((TreePointList *)&src)->GetX();
	Y=((TreePointList *)&src)->GetY();
	Level=src.Level;

	OtherNode=((TreePointList *)&src)->GetOtherNode();
	return *this;
}

TreePointList	&TreePointList::operator=(const VectorItemBase &src)
{
	X=((VectorItemBase *)&src)->GetXInt();
	Y=((VectorItemBase *)&src)->GetYInt();
	return *this;
}

bool	TreesContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	TreesContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		TreeLine *a=new TreeLine();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}


TreesContainer	&TreesContainer::operator=(const TreesContainer &src)
{
	RemoveAll();
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		TreeLine *b=new TreeLine();
		*b=*a;
		AppendList(b);
	}
	return *this;
}


double	TreesContainer::GetTotalLength(void)	const
{
	double	Ret=0;
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		Ret+=a->GetTotalLength();
	}
	return Ret;
}

bool	TreesContainer::GetXY(int &x1,int &y1,int &x2,int &y2)	const
{
	x1=99999999;
	y1=99999999;
	x2=-99999999;
	y2=-99999999;
	bool	Ret=false;
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		int	rx1,ry1,rx2,ry2;
		if(a->GetXY(rx1,ry1,rx2,ry2)==true){
			x1=min(x1,rx1);
			y1=min(y1,ry1);
			x2=max(x2,rx2);
			y2=max(y2,ry2);
			Ret=true;
		}
	}
	return Ret;
}

void	TreesContainer::MoveTo(int dx ,int dy)
{
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveTo(dx,dy);
	}
}

bool	TreesContainer::IsNull(void)	const
{
	TreeLine *a=GetFirst();
	if(a==NULL){
		return true;
	}
	return false;
}
void	TreesContainer::Draw(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate)
{
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(IData ,PData ,Col,MovX ,MovY ,ZoomRate);
	}
}
void	TreesContainer::DrawCircleOnLine(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate,int R)
{
	for(TreeLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawCircleOnLine(IData ,PData ,Col,MovX ,MovY ,ZoomRate,R);
	}
}