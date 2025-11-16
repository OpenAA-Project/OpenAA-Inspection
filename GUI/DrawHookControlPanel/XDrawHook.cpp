#include "DrawHookControlPanelForm.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XCrossObj.h"

void	DrawPolyDoubleLine(QPainter &pnt ,QPoint P[],int PointNumb ,int Sep);

bool	DrawerItemBase::GetWindowArea(DisplayImage *Target ,int &Width ,int &Height)
{
	Width	=Target->GetCanvasWidth();
	Height	=Target->GetCanvasHeight();
	return true;
}
double	DrawerItemBase::GetWindowZoomRate(DisplayImage *Target)
{
	return Target->GetZoomRate();
}

bool	DrawerItemContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(DrawerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	ClassType=a->GetClassType();
		if(::Save(f,ClassType)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	DrawerItemContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	CurrentMaxID=0;
	for(int i=0;i<N;i++){
		int32	ClassType;
		if(::Load(f,ClassType)==false)
			return false;
		DrawerItemBase	*a=NewClass(ClassType);
		if(a->Load(f)==false)
			return false;
		AppendList(a);
		CurrentMaxID=max(CurrentMaxID,a->ID);
	}
	CurrentMaxID++;
	return true;
}

void	DrawLineWithWidth(QPainter &Pnt ,int x1, int y1 ,int x2 ,int y2 ,int LineWidth)
{
	double	Len=hypot(x1-x2,y1-y2);
	int	dx=LineWidth*(x2-x1)/Len/2;
	int	dy=LineWidth*(y2-y1)/Len/2;

	Pnt.drawLine(x1+dx,y1+dy,x2-dx,y2-dy);
}


DrawerItemBase	*DrawerItemContainer::NewClass(int ClassType)
{
	switch(ClassType){
	case 1:	return new DrawItemLine(Parent);
	case 2:	return new DrawItemDraw(Parent);
	case 3:	return new DrawItemText(Parent);
	}
	return NULL;
}

void	DrawerItemContainer::ReleaseSelect(void)
{
	for(DrawerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Selected=false;
		a->OnCreating=false;
	}
}
void	DrawerItemContainer::RemoveCreating(void)
{
	for(DrawerItemBase *a=GetFirst();a!=NULL;){
		DrawerItemBase *NextA=a->GetNext();
		if(a->OnCreating==true && a->CreatingNew==true){
			RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
}
DrawerItemBase	*DrawerItemContainer::GetCreating(void)
{
	for(DrawerItemBase *a=GetLast();a!=NULL;a=a->GetPrev()){
		if(a->OnCreating==true){
			return a;
		}
	}
	return NULL;
}
DrawerItemBase	*DrawerItemContainer::GetSelected(void)
{
	for(DrawerItemBase *a=GetLast();a!=NULL;a=a->GetPrev()){
		if(a->Selected==true){
			return a;
		}
	}
	return NULL;
}
DrawerItemBase	*DrawerItemContainer::GetSelectedOnCreating(void)
{
	for(DrawerItemBase *a=GetLast();a!=NULL;a=a->GetPrev()){
		if(a->Selected==true && a->OnCreating==true){
			return a;
		}
	}
	return NULL;
}
DrawerItemContainer	&DrawerItemContainer::operator=(DrawerItemContainer &src)
{
	RemoveAll();
	for(DrawerItemBase *a=GetLast();a!=NULL;a=a->GetPrev()){
		DrawerItemBase	*b=NewClass(a->GetClassType());
		AppendList(b);
	}
	return *this;
}
//=============================================================================
DrawItemLine::DrawItemLine(DrawHookControlPanelForm *p)
	: DrawerItemBase(p)
{
	x1=y1=x2=y2=0;

	LineWidth	=1;
	LineType	=0;
	LineColor=Qt::green;
	LineStartType	=0;
	LineEndType		=0;
}
bool	DrawItemLine::GetXY(int &_x1 ,int &_y1 , int &_x2 ,int &_y2)
{
	_x1=min(x1,x2);
	_y1=min(y1,y2);
	_x2=max(x1,x2);
	_y2=max(y1,y2);
	return true;
}

bool	DrawItemLine::IsNear(DisplayImage *Target ,int GlobalX ,int GlobalY)
{
	double	Len=GetLengthLine2Point(x1 + OffsetX,y1 + OffsetY,x2 + OffsetX,y2 + OffsetY ,GlobalX ,GlobalY);
	if(Len<10)
		return true;
	return false;
}

void	DrawItemLine::Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame)
{
	int	X1,Y1,X2,Y2;

	int		ArrowLen		=LineWidth+10;
	int		RoundDiameter	=LineWidth+10;
	int		BarWidth		=3;
	int		BarLen			=LineWidth+5;

	if(LineStartType==0){
		X1=(x1+OffsetX+movx)*ZoomRate;
		Y1=(y1+OffsetY+movy)*ZoomRate;
	}
	else if(LineStartType==2){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);		
		double	Hx= hx/Len;
		double	Hy= hy/Len;

		X1=(x1-Hx*ArrowLen+OffsetX+movx)*ZoomRate;
		Y1=(y1-Hy*ArrowLen+OffsetY+movy)*ZoomRate;
	}
	else if(LineStartType==3){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);		
		double	Hx= hx/Len;
		double	Hy= hy/Len;

		X1=(x1-Hx*RoundDiameter/2+OffsetX+movx)*ZoomRate;
		Y1=(y1-Hy*RoundDiameter/2+OffsetY+movy)*ZoomRate;
	}
	else if(LineStartType==4){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);		
		double	Hx= hx/Len;
		double	Hy= hy/Len;

		X1=(x1-Hx*BarWidth+OffsetX+movx)*ZoomRate;
		Y1=(y1-Hy*BarWidth+OffsetY+movy)*ZoomRate;

	}
	else if(LineStartType==1){
		int		Width ,Height;
		GetWindowArea(Target,Width ,Height);
		double	Len=hypot(x2+OffsetX-x1,y2+OffsetY-y1);
		if(Len<1.0)
			return;
		double	Hx=x2-x1;
		double	Hy=y2-y1;
		//double	X1=(x2+movx)*ZoomRate-Hx/Len*t;
		//double	Y1=(y2+movy)*ZoomRate-Hy/Len*t;

		if(Hx==0.0){
			double	t1= (y2+ OffsetX + movy)*ZoomRate*Len/Hy;
			double	t2=((y2+ OffsetY + movy)*ZoomRate-Height)*Len/Hy;
			if((t1>0 && t2<0) || (t1>0 && t2>0 && t1>t2)){
				X1=(x2+ OffsetX + movx)*ZoomRate;
				Y1=(y2+ OffsetY + movy)*ZoomRate-Hy/Len*t1;
			}
			else if((t1<0 && t2>0) || (t1>0 && t2>0 && t1<t2)){
				X1=(x2+ OffsetX + movx)*ZoomRate;
				Y1=(y2+ OffsetY + movy)*ZoomRate-Hy/Len*t2;
			}
			return;
		}
		else if(Hy==0){
			double	t1= (x2+ OffsetX + movx)*ZoomRate*Len/Hx;
			double	t2=((x2+ OffsetY + movx)*ZoomRate-Width)*Len/Hx;
			if((t1>0 && t2<0) || (t1>0 && t2>0 && t1>t2)){
				X1=(x2+ OffsetX + movx)*ZoomRate-Hx/Len*t1;
				Y1=(y2+ OffsetY + movy)*ZoomRate;
			}
			else if((t1<0 && t2>0) || (t1>0 && t2>0 && t1<t2)){
				X1=(x2+ OffsetX + movx)*ZoomRate-Hx/Len*t2;
				Y1=(y2+ OffsetY + movy)*ZoomRate;
			}
			return;
		}
		else{
			double	t1= (x2+ OffsetX + movx)*ZoomRate*Len/Hx;	//X1==0
			double	t2= (y2+ OffsetY + movy)*ZoomRate*Len/Hy;	//Y1==0
			double	t3=((x2+ OffsetX + movx)*ZoomRate-Width )*Len/Hx;	//X1==Width
			double	t4=((y2+ OffsetY + movy)*ZoomRate-Height)*Len/Hy;	//Y1==Height
			double	MaxT=max(max(t1,t2),max(t3,t4));
			if(MaxT<0)
				return;
			X1=(x2+ OffsetX + movx)*ZoomRate-Hx/Len*MaxT;
			Y1=(y2+ OffsetY + movy)*ZoomRate-Hy/Len*MaxT;
		}
	}
	if(LineEndType==0){
		X2=(x2+ OffsetX + movx)*ZoomRate;
		Y2=(y2+ OffsetY + movy)*ZoomRate;
	}
	else if(LineEndType==2){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);		
		double	Hx= hx/Len;
		double	Hy= hy/Len;

		X2=(x2+Hx*ArrowLen+OffsetX+movx)*ZoomRate;
		Y2=(y2+Hy*ArrowLen+OffsetY+movy)*ZoomRate;
	}
	else if(LineEndType==3){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);		
		double	Hx= hx/Len;
		double	Hy= hy/Len;

		X2=(x2+Hx*RoundDiameter/2+OffsetX+movx)*ZoomRate;
		Y2=(y2+Hy*RoundDiameter/2+OffsetY+movy)*ZoomRate;
	}
	else if(LineEndType==4){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);		
		double	Hx= hx/Len;
		double	Hy= hy/Len;

		X2=(x2+Hx*BarWidth+OffsetX+movx)*ZoomRate;
		Y2=(y2+Hy*BarWidth+OffsetY+movy)*ZoomRate;

	}
	else if(LineEndType==1){
		int		Width ,Height;
		GetWindowArea(Target,Width ,Height);
		double	Len=hypot(x2-x1,y2-y1);
		if(Len<1.0)
			return;
		double	Hx=x2-x1;
		double	Hy=y2-y1;
		//double	X2=(x1+movx)*ZoomRate+Hx/Len*t;
		//double	Y2=(y1+movy)*ZoomRate+Hy/Len*t;

		if(Hx==0.0){
			double	t1=-(y1+ OffsetY + movy)*ZoomRate*Len/Hy;
			double	t2=(Height-(y1+ OffsetY + movy)*ZoomRate)*Len/Hy;
			if((t1>0 && t2<0) || (t1>0 && t2>0 && t1>t2)){
				X2=(x1+ OffsetX + movx)*ZoomRate;
				Y2=(y1+ OffsetY + movy)*ZoomRate+Hy/Len*t1;
			}
			else if((t1<0 && t2>0) || (t1>0 && t2>0 && t1<t2)){
				X2=(x1+ OffsetX + movx)*ZoomRate;
				Y2=(y1+ OffsetY + movy)*ZoomRate+Hy/Len*t2;
			}
			return;
		}
		else if(Hy==0){
			double	t1= (x1+ OffsetX + movx)*ZoomRate*Len/Hx;
			double	t2=((x1+ OffsetY + movx)*ZoomRate-Width)*Len/Hx;
			if((t1>0 && t2<0) || (t1>0 && t2>0 && t1>t2)){
				X2=(x1+ OffsetX + movx)*ZoomRate+Hx/Len*t1;
				Y2=(y1+ OffsetY + movy)*ZoomRate;
			}
			else if((t1<0 && t2>0) || (t1>0 && t2>0 && t1<t2)){
				X2=(x1+ OffsetX + movx)*ZoomRate+Hx/Len*t2;
				Y2=(y1+ OffsetY + movy)*ZoomRate;
			}
			return;
		}
		else{
			double	t1=-(x1+ OffsetX + movx)*ZoomRate*Len/Hx;	//X1==0
			double	t2=-(y1+ OffsetY + movy)*ZoomRate*Len/Hy;	//Y1==0
			double	t3=(Width -(x1+ OffsetX + movx)*ZoomRate)*Len/Hx;	//X1==Width
			double	t4=(Height-(y1+ OffsetY + movy)*ZoomRate)*Len/Hy;	//Y1==Height
			double	MaxT=max(max(t1,t2),max(t3,t4));
			if(MaxT<0)
				return;
			X2=(x1+ OffsetX + movx)*ZoomRate+Hx/Len*MaxT;
			Y2=(y1+ OffsetY + movy)*ZoomRate+Hy/Len*MaxT;
		}
	}


	if(LineType==0){
		QBrush	B((Selected==false)?LineColor:Qt::red);
		int	tLineWidth=LineWidth*ZoomRate;
		if(tLineWidth<=0)	tLineWidth=1;
		QPen Pen( B, tLineWidth, Qt::SolidLine);
		pnt.setPen(Pen);

		//pnt.drawLine(X1,Y1,X2,Y2);
		DrawLineWithWidth(pnt ,X1, Y1 ,X2 ,Y2 ,tLineWidth);
	}
	else if(LineType==1){
		QBrush	B((Selected==false)?LineColor:Qt::red);
		int	tLineWidth=LineWidth*ZoomRate;
		if(tLineWidth<=0)	tLineWidth=1;
		QPen Pen( B, tLineWidth, Qt::DotLine);
		pnt.setPen(Pen);

		//pnt.drawLine(X1,Y1,X2,Y2);
		DrawLineWithWidth(pnt ,X1, Y1 ,X2 ,Y2 ,tLineWidth);
	}
	else if(LineType==2){
		QBrush	B((Selected==false)?LineColor:Qt::red);
		int	tLineWidth=LineWidth*ZoomRate;
		if(tLineWidth<=0)	tLineWidth=1;
		QPen Pen( B, tLineWidth, Qt::SolidLine);
		pnt.setPen(Pen);

		double	Len=hypot(x2-x1,y2-y1);
		double	rx=(x2-x1)/Len;
		double	ry=(y2-y1)/Len;
		double	vx=ry;
		double	vy=-rx;

		int	Lx=ceil(vx*LineWidth*ZoomRate);
		int	Ly=ceil(vy*LineWidth*ZoomRate);

		//pnt.drawLine(X1+Lx,Y1+Ly,X2+Lx,Y2+Ly);
		//pnt.drawLine(X1-Lx,Y1-Ly,X2-Lx,Y2-Ly);
		DrawLineWithWidth(pnt ,X1+Lx,Y1+Ly,X2+Lx,Y2+Ly,tLineWidth);
		DrawLineWithWidth(pnt ,X1-Lx,Y1-Ly,X2-Lx,Y2-Ly,tLineWidth);
	}
	if(LineStartType==2){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);
		if(Len==0)
			return;
		double	Vx= hy/Len;
		double	Vy=-hx/Len;
		double	Hx= hx/Len;
		double	Hy= hy/Len;
		QPoint	P[4];
		P[0].setX(X1+Hx*ArrowLen*ZoomRate);
		P[0].setY(Y1+Hy*ArrowLen*ZoomRate);
		P[1].setX(X1+(Vx*ArrowLen/3-Hx*ArrowLen/6)*ZoomRate);
		P[1].setY(Y1+(Vy*ArrowLen/3-Hy*ArrowLen/6)*ZoomRate);
		P[2].setX(X1);
		P[2].setY(Y1);
		P[3].setX(X1+(-Vx*ArrowLen/3-Hx*ArrowLen/6)*ZoomRate);
		P[3].setY(Y1+(-Vy*ArrowLen/3-Hy*ArrowLen/6)*ZoomRate);
		QBrush	B((Selected==false)?LineColor:Qt::red);
		pnt.setBrush(B);
		pnt.drawPolygon (P, 4);
	}
	else if(LineStartType==3){
		QBrush	B((Selected==false)?LineColor:Qt::red);
		pnt.setBrush(B);
		pnt.drawEllipse (X1-RoundDiameter/2*ZoomRate,Y1-RoundDiameter/2*ZoomRate
						,RoundDiameter*ZoomRate,RoundDiameter*ZoomRate);
	}
	else if(LineStartType==4){
		int	hx=x1-x2;
		int	hy=y1-y2;
		double	Len=hypot(hx,hy);
		if(Len==0)
			return;
		double	Vx= hy/Len;
		double	Vy=-hx/Len;
		
		QBrush	B((Selected==false)?LineColor:Qt::red);
		QPen Pen( B, BarWidth*ZoomRate, Qt::SolidLine);
		pnt.setPen(Pen);
		pnt.drawLine(X1-Vx*BarLen*ZoomRate,Y1-Vy*BarLen*ZoomRate
					,X1+Vx*BarLen*ZoomRate,Y1+Vy*BarLen*ZoomRate);
	}
	if(LineEndType==2){
		int	hx=x2-x1;
		int	hy=y2-y1;
		double	Len=hypot(hx,hy);
		if(Len==0)
			return;
		double	Vx= hy/Len;
		double	Vy=-hx/Len;
		double	Hx= hx/Len;
		double	Hy= hy/Len;
		QPoint	P[4];
		P[0].setX(X2+Hx*ArrowLen*ZoomRate);
		P[0].setY(Y2+Hy*ArrowLen*ZoomRate);
		P[1].setX(X2+(Vx*ArrowLen/3-Hx*ArrowLen/6)*ZoomRate);
		P[1].setY(Y2+(Vy*ArrowLen/3-Hy*ArrowLen/6)*ZoomRate);
		P[2].setX(X2);
		P[2].setY(Y2);
		P[3].setX(X2+(-Vx*ArrowLen/3-Hx*ArrowLen/6)*ZoomRate);
		P[3].setY(Y2+(-Vy*ArrowLen/3-Hy*ArrowLen/6)*ZoomRate);
		QBrush	B((Selected==false)?LineColor:Qt::red);
		pnt.setBrush(B);
		pnt.drawPolygon (P, 4);
	}
	else if(LineEndType==3){
		QBrush	B((Selected==false)?LineColor:Qt::red);
		pnt.setBrush(B);
		pnt.drawEllipse (X2-RoundDiameter/2*ZoomRate,Y2-RoundDiameter/2*ZoomRate
						,RoundDiameter*ZoomRate,RoundDiameter*ZoomRate);
	}
	else if(LineEndType==4){
		int	hx=x2-x1;
		int	hy=y2-y1;
		double	Len=hypot(hx,hy);
		if(Len==0)
			return;
		double	Vx=hy/Len;
		double	Vy=-hx/Len;
		
		QBrush	B((Selected==false)?LineColor:Qt::red);
		QPen Pen( B, BarWidth*ZoomRate, Qt::SolidLine);
		pnt.setPen(Pen);
		pnt.drawLine(X2-Vx*BarLen*ZoomRate,Y2-Vy*BarLen*ZoomRate
					,X2+Vx*BarLen*ZoomRate,Y2+Vy*BarLen*ZoomRate);
	}

	if(DrawFrame==true && Selected==true){
		if(LineStartType==0 || LineStartType==2 || LineStartType==3 || LineStartType==4){
			X1=(x1+OffsetX+movx)*ZoomRate;
			Y1=(y1+OffsetY+movy)*ZoomRate;
		}
		if(LineEndType==0 || LineEndType==2 || LineEndType==3 || LineEndType==4){
			X2=(x2+OffsetX+movx)*ZoomRate;
			Y2=(y2+OffsetY+movy)*ZoomRate;
		}
		QBrush	B(Qt::yellow);
		QPen Pen( B, 5, Qt::SolidLine);
		pnt.setPen(Pen);

		int	hx=x2-x1;
		int	hy=y2-y1;
		double	Len=hypot(hx,hy);
		if(Len==0)
			return;
		double	Vx= hy/Len;
		double	Vy=-hx/Len;

		int	W=LineWidth/2+5;
		if(LineType==2){
			W=LineWidth*2+5;
		}

		pnt.drawLine(X2-Vx*W*ZoomRate,Y2-Vy*W*ZoomRate,X2+Vx*W*ZoomRate,Y2+Vy*W*ZoomRate);
		pnt.drawLine(X1-Vx*W*ZoomRate,Y1-Vy*W*ZoomRate,X1+Vx*W*ZoomRate,Y1+Vy*W*ZoomRate);
		pnt.drawLine(X1-Vx*W*ZoomRate,Y1-Vy*W*ZoomRate,X2-Vx*W*ZoomRate,Y2-Vy*W*ZoomRate);
		pnt.drawLine(X1+Vx*W*ZoomRate,Y1+Vy*W*ZoomRate,X2+Vx*W*ZoomRate,Y2+Vy*W*ZoomRate);
	}
}

bool	DrawItemLine::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,LineWidth)==false)
		return false;
	if(::Save(f,LineType)==false)
		return false;
	if(::Save(f,LineColor)==false)
		return false;
	if(::Save(f,LineStartType)==false)
		return false;
	if(::Save(f,LineEndType)==false)
		return false;
	return true;
}
bool	DrawItemLine::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,ID)==false)
			return false;
	}
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,LineWidth)==false)
		return false;
	if(::Load(f,LineType)==false)
		return false;
	if(::Load(f,LineColor)==false)
		return false;
	if(::Load(f,LineStartType)==false)
		return false;
	if(::Load(f,LineEndType)==false)
		return false;
	return true;
}
void	DrawItemLine::MoveTo(int dx, int dy)
{
	x1+=dx;
	y1+=dy;
	x2+=dx;
	y2+=dy;
}
void	DrawItemLine::CopyToLast(void)
{
	lastx1	=x1;
	lasty1	=y1;
	lastx2	=x2;
	lasty2	=y2;
}
void	DrawItemLine::RestoreFromLast(void)
{
	SetOffset(0, 0);
	x1	=lastx1;
	y1	=lasty1;
	x2	=lastx2;
	y2	=lasty2;
}
bool	DrawItemLine::operator==(DrawItemLine &src)
{
	if(x1			==src.x1
	&& y1			==src.y1
	&& x2			==src.x2
	&& y2			==src.y2
	&& LineWidth	==src.LineWidth
	&& LineType		==src.LineType
	&& LineColor	==src.LineColor
	&& LineStartType==src.LineStartType
	&& LineEndType	==src.LineEndType	){
		return true;
	}
	return false;
}
void	DrawItemLine::Transform(double m[6])
{
	int	X1=m[0]*x1+m[1]*y1+m[2];
	int	Y1=m[3]*x1+m[4]*y1+m[5];
	int	X2=m[0]*x2+m[1]*y2+m[2];
	int	Y2=m[3]*x2+m[4]*y2+m[5];
	x1=X1;
	y1=Y1;
	x2=X2;
	y2=Y2;
}

FlexArea	DrawItemLine::MakeArea(void)
{
	return FlexArea();
}

//=============================================================================
DrawItemDraw::DrawItemDraw(DrawHookControlPanelForm *p)
	: DrawerItemBase(p)
{
	DrawType	=0;		//0:Rectangle	1:Round	2:Polygon
	DrawLineWidth=1;
	DrawLineColor=Qt::black;
	DrawInsideType	=1;	//0:No draw	1:Solid	2:Hatch
	DrawInsideColor	=Qt::green;	
}
bool	DrawItemDraw::GetXY(int &x1 ,int &y1 , int &x2 ,int &y2)
{
	int	MinX=99999999,MinY=99999999,MaxX=-99999999,MaxY=-99999999;
	for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
		int	x=a->x;
		int	y=a->y;
		MinX=min(MinX,x);
		MinY=min(MinY,y);
		MaxX=max(MaxX,x);
		MaxY=max(MaxY,y);
	}
	x1=MinX;
	y1=MinY;
	x2=MaxX;
	y2=MaxY;
	return true;
}
bool	DrawItemDraw::IsNear(DisplayImage *Target ,int GlobalX ,int GlobalY)
{
	double PointsDim[10000][2];

	int	N=0;
	for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
		PointsDim[N][0]=a->x+OffsetX;
		PointsDim[N][1]=a->y+OffsetY;
		N++;
	}
	if(DrawType==0){
		int	MinX=99999999,MinY=99999999,MaxX=-99999999,MaxY=-99999999;
		for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
			MinX = min(MinX, a->x + OffsetX);
			MinY = min(MinY, a->y + OffsetY);
			MaxX = max(MaxX, a->x + OffsetX);
			MaxY = max(MaxY, a->y + OffsetY);
		}
		MinX-=2;
		MinY-=2;
		MaxX+=2;
		MaxY+=2;
		if(MinX<=GlobalX && GlobalX<=MaxX && MinY<=GlobalY && GlobalY<=MaxY){
			return true;
		}
	}
	else if(DrawType==1){
		int	MinX=99999999,MinY=99999999,MaxX=-99999999,MaxY=-99999999;
		for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
			MinX = min(MinX, a->x + OffsetX);
			MinY = min(MinY, a->y + OffsetY);
			MaxX = max(MaxX, a->x + OffsetX);
			MaxY = max(MaxY, a->y + OffsetY);
		}
		double	Cx=(MinX+MaxX)/2.0;
		double	Cy=(MinY+MaxY)/2.0;
		double	Rx=(MaxX-MinX)/2.0;
		double	Ry=(MaxY-MinY)/2.0;
		double	D=(GlobalX-Cx)*(GlobalX-Cx)/(Rx*Rx)+(GlobalY-Cy)*(GlobalY-Cy)/(Ry*Ry);
		if(D<=2.0){
			return true;
		}
	}
	else{
		if(N==2){
			XYClass *a=Points.GetFirst();
			XYClass *b=a->GetNext();
			int	x1 = a->x + OffsetX;
			int	y1 = a->y + OffsetY;
			int	x2 = b->x + OffsetX;
			int	y2 = b->y + OffsetY;
			double	Len=GetLengthLine2Point(x1,y1,x2,y2	,GlobalX ,GlobalY);
			if(Len<10)
				return true;
		}
		else
		if(CheckInsidePolygon  (PointsDim,N	//Convex
								,GlobalX ,GlobalY)==true){
			return true;
		}
	}
	return false;
}

void	DrawItemDraw::Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame)
{
	int	MinX=99999999,MinY=99999999,MaxX=-99999999,MaxY=-99999999;
	int	tDrawLineWidth=DrawLineWidth*ZoomRate;
	if(tDrawLineWidth<=0)	tDrawLineWidth=1;
	if(DrawType==0){
		for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
			int	x=(a->x + OffsetX +movx)*ZoomRate;
			int	y=(a->y + OffsetY +movy)*ZoomRate;
			MinX=min(MinX,x);
			MinY=min(MinY,y);
			MaxX=max(MaxX,x);
			MaxY=max(MaxY,y);
		}
		if(DrawLineWidth>0){
			QPen	Pen(DrawLineColor);
			Pen.setWidth(DrawLineWidth);
			pnt.setPen(Pen);
		}
		QPoint	P[5];
		P[0].setX(MinX);
		P[0].setY(MinY);
		P[1].setX(MinX);
		P[1].setY(MaxY);
		P[2].setX(MaxX);
		P[2].setY(MaxY);
		P[3].setX(MaxX);
		P[3].setY(MinY);
		P[4].setX(MinX);
		P[4].setY(MinY);

		if(LineType==0){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, tDrawLineWidth, Qt::SolidLine);
			pnt.setPen(Pen);
		}
		else if(LineType==1){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, tDrawLineWidth, Qt::DotLine);
			pnt.setPen(Pen);
		}
		else if(LineType==2){
			QPen Pen(Qt::NoPen);
			pnt.setPen(Pen);
		}

		if(DrawInsideType==0){
			pnt.drawPolyline(P,5);
		}
		else if(DrawInsideType==1){
			QBrush	B((Selected==false)?DrawInsideColor:Qt::red);
			pnt.setBrush(B);
			pnt.drawPolygon(P,5);
		}
		else if(DrawInsideType==2){
			QBrush	B((Selected==false)?DrawInsideColor:Qt::red,Qt::DiagCrossPattern);
			pnt.setBrush(B);
			pnt.drawPolygon(P,5);
		}
		
		if(LineType==2){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, DrawLineWidth, Qt::SolidLine);
			pnt.setPen(Pen);
			DrawPolyDoubleLine(pnt ,P,5,DrawLineWidth);
		}
	}
	else if(DrawType==2){
		QPoint	*P=new QPoint[Points.GetCount()+1];
		int	N=0;
		for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
			int	x=(a->x + OffsetX +movx)*ZoomRate;
			int	y=(a->y + OffsetY +movy)*ZoomRate;
			MinX=min(MinX,x);
			MinY=min(MinY,y);
			MaxX=max(MaxX,x);
			MaxY=max(MaxY,y);
			P[N].setX(x);
			P[N].setY(y);
			N++;
		}
		P[N]=P[0];
		N++;

		if(LineType==0){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, DrawLineWidth, Qt::SolidLine);
			pnt.setPen(Pen);
		}
		else if(LineType==1){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, DrawLineWidth, Qt::DotLine);
			pnt.setPen(Pen);
		}
		else if(LineType==2){
			QPen Pen(Qt::NoPen);
			pnt.setPen(Pen);
		}

		//if(DrawLineWidth>0){
		//	QPen	Pen((Selected==false)?DrawLineColor:Qt::red);
		//	Pen.setWidth(DrawLineWidth);
		//	pnt.setPen(Pen);
		//}
		if(DrawInsideType==0){
			pnt.drawPolyline(P,N);
		}
		else if(DrawInsideType==1){
			QBrush	B((Selected==false)?DrawInsideColor:Qt::red);
			pnt.setBrush(B);
			pnt.drawPolygon(P,N);
		}
		else if(DrawInsideType==2){
			QBrush	B((Selected==false)?DrawInsideColor:Qt::red,Qt::DiagCrossPattern);
			pnt.setBrush(B);
			pnt.drawPolygon(P,N);
		}

		if(LineType==2){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, tDrawLineWidth, Qt::SolidLine);
			pnt.setPen(Pen);
			DrawPolyDoubleLine(pnt ,P,N,DrawLineWidth);
		}
		delete	[]P;
	}
	else if(DrawType==1){
		if(Points.GetCount()==0)
			return;
		for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
			int	x=(a->x + OffsetX +movx)*ZoomRate;
			int	y=(a->y + OffsetY +movy)*ZoomRate;
			MinX=min(MinX,x);
			MinY=min(MinY,y);
			MaxX=max(MaxX,x);
			MaxY=max(MaxY,y);
		}

		if(DrawLineWidth>0){
			QPen	Pen((Selected==false)?DrawLineColor:Qt::red);
			Pen.setWidth(tDrawLineWidth);
			pnt.setPen(Pen);
		}
		if(LineType==0){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, tDrawLineWidth, Qt::SolidLine);
			pnt.setPen(Pen);
		}
		else if(LineType==1){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, tDrawLineWidth, Qt::DotLine);
			pnt.setPen(Pen);
		}
		else if(LineType==2){
			QBrush	B((Selected==false)?DrawLineColor:Qt::red);
			QPen Pen( B, tDrawLineWidth, Qt::SolidLine);
			pnt.setPen(Pen);
		}

		if(DrawInsideType==0){
			pnt.drawArc(MinX,MinY,MaxX-MinX,MaxY-MinY,0,5760);
			if(LineType==2){
				pnt.drawArc(MinX+2,MinY+2,MaxX-MinX-4,MaxY-MinY-4,0,5760);
			}
		}
		else if(DrawInsideType==1){
			QBrush	B((Selected==false)?DrawInsideColor:Qt::red);
			pnt.setBrush(B);
			pnt.drawEllipse(MinX,MinY,MaxX-MinX,MaxY-MinY);
			if(LineType==2){
				pnt.drawEllipse(MinX+2,MinY+2,MaxX-MinX-4,MaxY-MinY-4);
			}
		}
		else if(DrawInsideType==2){
			QBrush	B((Selected==false)?DrawInsideColor:Qt::red,Qt::DiagCrossPattern);
			pnt.setBrush(B);
			pnt.drawEllipse(MinX,MinY,MaxX-MinX,MaxY-MinY);
			if(LineType==2){
				pnt.drawEllipse(MinX+2,MinY+2,MaxX-MinX-4,MaxY-MinY-4);
			}
		}
	}
	if(DrawFrame==true && Selected==true){
		QBrush	B(Qt::yellow);
		QPen Pen( B, 5, Qt::SolidLine);
		pnt.setPen(Pen);

		int	W=DrawLineWidth*0.5+5;
		if(LineType==2){
			W=DrawLineWidth*1.5+5;
		}
		pnt.drawLine(MinX-W,MinY-W,MaxX+W,MinY-W);
		pnt.drawLine(MinX-W,MaxY+W,MaxX+W,MaxY+W);
		pnt.drawLine(MinX-W,MinY-W,MinX-W,MaxY+W);
		pnt.drawLine(MaxX+W,MinY-W,MaxX+W,MaxY+W);
	}
}
bool	DrawItemDraw::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;
	if(Points.Save(f)==false)
		return false;
	if(::Save(f,DrawType)==false)
		return false;
	if(::Save(f,DrawLineWidth)==false)
		return false;
	if(::Save(f,DrawLineColor)==false)
		return false;
	if(::Save(f,DrawInsideType)==false)
		return false;
	if(::Save(f,DrawInsideColor)==false)
		return false;
	if(::Save(f,LineType)==false)
		return false;
	return true;
}
bool	DrawItemDraw::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,ID)==false)
			return false;
	}
	if(Points.Load(f)==false)
		return false;
	if(::Load(f,DrawType)==false)
		return false;
	if(::Load(f,DrawLineWidth)==false)
		return false;
	if(::Load(f,DrawLineColor)==false)
		return false;
	if(::Load(f,DrawInsideType)==false)
		return false;
	if(::Load(f,DrawInsideColor)==false)
		return false;
	if(::Load(f,LineType)==false)
		return false;
	return true;
}
void	DrawItemDraw::MoveTo(int dx, int dy)
{
	Points.MoveTo(dx,dy);
}
void	DrawItemDraw::CopyToLast(void)
{
	LastPoints=Points;
}
void	DrawItemDraw::RestoreFromLast(void)
{
	SetOffset(0, 0);
	Points=LastPoints;
}
bool	GetParallelLine(double X1 ,double Y1 ,double X2 ,double Y2 ,double Sep ,double &x1,double &y1,double &x2,double &y2)
{
	double	dx=X2-X1;
	double	dy=Y2-Y1;
	double	L=hypot(dx,dy);
	if(L<0.000000001)
		return false;
	double	vx=-dy/L*Sep;
	double	vy= dx/L*Sep;
	x1=X1+vx;
	y1=Y1+vy;
	x2=X2+vx;
	y2=Y2+vy;
	return true;
}

void	DrawPolyDoubleLine(QPainter &pnt ,QPoint P[],int PointNumb ,int Sep)
{
	if(PointNumb>0){
		if(P[0].x()==P[PointNumb-1].x() && P[0].y()==P[PointNumb-1].y()){
			PointNumb--;
		}
	}
	if(PointNumb==2){
		double	x11,y11,x12,y12;
		bool	b1=GetParallelLine(P[0].x(),P[0].y(),P[1].x(),P[1].y(), Sep ,x11,y11,x12,y12);
		double	x21,y21,x22,y22;
		bool	b2=GetParallelLine(P[0].x(),P[0].y(),P[1].x(),P[1].y(),-Sep ,x21,y21,x22,y22);
		if(b1==true && b2==true){
			pnt.drawLine(x11,y11,x12,y12);
			pnt.drawLine(x21,y21,x22,y22);
		}
	}
	else if(PointNumb>2){
		for(int i=0;i<PointNumb;i++){
			int	i2=((i-1)>=0)?i-1:PointNumb-1;
			double	x11,y11,x12,y12;
			bool	b1=GetParallelLine(P[i2].x(),P[i2].y(),P[i].x(),P[i].y(), Sep ,x11,y11,x12,y12);
			double	x21,y21,x22,y22;
			bool	b2=GetParallelLine(P[i2].x(),P[i2].y(),P[i].x(),P[i].y(),-Sep ,x21,y21,x22,y22);

			int	j=i2;
			double	xs11,ys11,xs12,ys12;
			int	j2=((j-1)>=0)?j-1:PointNumb-1;
			bool	bs1=GetParallelLine(P[j2].x(),P[j2].y(),P[j].x(),P[j].y(), Sep ,xs11,ys11,xs12,ys12);
			double	xs21,ys21,xs22,ys22;
			bool	bs2=GetParallelLine(P[j2].x(),P[j2].y(),P[j].x(),P[j].y(),-Sep ,xs21,ys21,xs22,ys22);
			
			int	k=i+1;
			double	xt11,yt11,xt12,yt12;
			int	k2=(k<PointNumb)?k:0;
			bool	bt1=GetParallelLine(P[i].x(),P[i].y(),P[k].x(),P[k].y(), Sep ,xt11,yt11,xt12,yt12);
			double	xt21,yt21,xt22,yt22;
			bool	bt2=GetParallelLine(P[i].x(),P[i].y(),P[k].x(),P[k].y(),-Sep ,xt21,yt21,xt22,yt22);
			
			if(b1==true && bs1==true && bt1==true){
				double	X11,Y11;
				bool	b11=GetCrossPoint(x11,y11,x12,y12,xs11,ys11,xs12,ys12 , X11 ,Y11);
				double	X12,Y12;
				bool	b12=GetCrossPoint(x11,y11,x12,y12,xt11,yt11,xt12,yt12 , X12 ,Y12);
				if(b11==true && b12==true){
					pnt.drawLine(X11,Y11,X12,Y12);
				}
			}
			if(b2==true && bs2==true && bt2==true){
				double	X21,Y21;
				bool	b21=GetCrossPoint(x21,y21,x22,y22,xs21,ys21,xs22,ys22 , X21 ,Y21);
				double	X22,Y22;
				bool	b22=GetCrossPoint(x21,y21,x22,y22,xt21,yt21,xt22,yt22 , X22 ,Y22);
				if(b21==true && b22==true){
					pnt.drawLine(X21,Y21,X22,Y22);
				}
			}
		}
	}
}

bool	DrawItemDraw::operator==(DrawItemDraw &src)
{
	if(Points			==src.Points
	&& DrawType			==src.DrawType		
	&& LineType			==src.LineType
	&& DrawLineWidth	==src.DrawLineWidth
	&& DrawLineColor	==src.DrawLineColor
	&& DrawInsideType	==src.DrawInsideType
	&& DrawInsideColor	==src.DrawInsideColor){
		return true;
	}
	return false;
}

void	DrawItemDraw::Transform(double m[6])
{
	for(XYClass *a=Points.GetFirst();a!=NULL;a=a->GetNext()){
		int	X=m[0]*a->x+m[1]*a->y+m[2];
		int	Y=m[3]*a->x+m[4]*a->y+m[5];
		a->x=X;
		a->y=Y;
	}
}

FlexArea	DrawItemDraw::MakeArea(void)
{
	if(DrawType==0 && DrawInsideType==0){
		FlexArea	Area;
		int		x1 ,y1 , x2 ,y2;
		GetXY(x1 ,y1 , x2 ,y2);
		Area.SetRectangle(x1 ,y1 , x2 ,y2);
		return Area;
	}
	else
	if(DrawType==1 && DrawInsideType==0){
		FlexArea	Area;
		int		x1 ,y1 , x2 ,y2;
		GetXY(x1 ,y1 , x2 ,y2);
		Area.SetEllipse(x1 ,y1 , x2 ,y2);
		return Area;
	}
	else
	if(DrawType==1 && DrawInsideType==0){
		FlexArea	Area;
		Area.MakeConvexPolygon(Points);
		return Area;
	}
	return FlexArea();
}


//=============================================================================

DrawItemText::DrawItemText(DrawHookControlPanelForm *p)
	: DrawerItemBase(p)
{
	X=Y=0;
	TextHeight=12;
	//TextFont;
	TextColor=Qt::red;
}

bool	DrawItemText::GetXY(int &x1 ,int &y1 , int &x2 ,int &y2)
{
	return true;
}
bool	DrawItemText::IsNear(DisplayImage *Target,int GlobalX ,int GlobalY)
{
	TextFont.setPointSize(TextHeight*GetWindowZoomRate(Target));
	QFontMetrics fm(TextFont);
	QRect R=fm.tightBoundingRect(Text);
	int width	=R.width ()/Target->GetZoomRate();
	int height	=R.height()/Target->GetZoomRate();

	if(CheckInsideRectangle(X-5 ,Y-height-5 ,X+width+5 ,Y+5
							,GlobalX ,GlobalY)==true){
		return true;
	}
	return false;
}

void	DrawItemText::Draw(DisplayImage *Target ,QPainter &pnt,double ZoomRate,int movx ,int movy ,bool DrawFrame)
{
	TextFont.setPointSize(TextHeight*ZoomRate);
	pnt.setFont(TextFont);
	QBrush	B((Selected==false)?TextColor:Qt::red);
	pnt.setBrush(B);
	pnt.setPen((Selected==false)?TextColor:Qt::red);
	int	X1=(X + OffsetX +movx)*ZoomRate;
	int	Y1=(Y + OffsetY +movy)*ZoomRate;
	pnt.drawText(X1,Y1,Text);

	if(DrawFrame==true && Selected==true){
		QFontMetrics fm(TextFont);
		QString	TmpText=Text;	//+QString(/**/"W");
		QRect R=fm.tightBoundingRect(TmpText);
		int	X2=X1+R.width();
		int	Y2=Y1-R.height();
		swap(Y1,Y2);

		QBrush	B(Qt::yellow);
		QPen Pen( B, 5, Qt::SolidLine);
		pnt.setPen(Pen);

		pnt.drawLine(X1-5,Y1-5,X2+5,Y1-5);
		pnt.drawLine(X1-5,Y2+5,X2+5,Y2+5);
		pnt.drawLine(X1-5,Y1-5,X1-5,Y2+5);
		pnt.drawLine(X2+5,Y1-5,X2+5,Y2+5);
	}
}

bool	DrawItemText::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,X)==false)
		return false;
	if(::Save(f,Y)==false)
		return false;
	if(::Save(f,TextHeight)==false)
		return false;
	if(::Save(f,TextFont.toString())==false)
		return false;
	if(::Save(f,TextColor)==false)
		return false;
	if(::Save(f,Text)==false)
		return false;
	return true;
}
bool	DrawItemText::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,ID)==false)
			return false;
	}
	if(::Load(f,X)==false)
		return false;
	if(::Load(f,Y)==false)
		return false;
	if(::Load(f,TextHeight)==false)
		return false;
	QString	FontStr;
	if(::Load(f,FontStr)==false)
		return false;
	TextFont.fromString(FontStr);
	if(::Load(f,TextColor)==false)
		return false;
	if(::Load(f,Text)==false)
		return false;
	return true;
}
void	DrawItemText::MoveTo(int dx, int dy)
{
	X+=dx;
	Y+=dy;
}
void	DrawItemText::CopyToLast(void)
{
	LastX=X;
	LastY=Y;
}
void	DrawItemText::RestoreFromLast(void)
{
	SetOffset(0, 0);
	X=LastX;
	Y=LastY;
}

bool	DrawItemText::operator==(DrawItemText &src)
{
	if(X			==src.X
	&& Y			==src.Y
	&& Text			==src.Text
	&& TextHeight	==src.TextHeight
	&& TextFont		==src.TextFont
	&& TextColor	==src.TextColor){
		return true;
	}
	return false;
}
void	DrawItemText::Transform(double m[6])
{
	int	X1=m[0]*X+m[1]*Y+m[2];
	int	Y1=m[3]*X+m[4]*Y+m[5];
	X=X1;
	Y=Y1;
}
FlexArea	DrawItemText::MakeArea(void)
{
	return FlexArea();
}