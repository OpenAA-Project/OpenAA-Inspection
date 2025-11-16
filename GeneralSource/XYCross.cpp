/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XYCross.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#include "XTypeDef.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XCrossObj.h"
#define	_USE_MATH_DEFINES
#include<math.h>
#include "swap.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include<QPainter>
#include "XMainSchemeMemory.h"

static	bool LinesRound(const NPListPack<XYClass> &D ,const XYClass  &P);

bool	DoublePoint::Save(QIODevice *f)
{
	if(::Save(f,x)==false){
		return false;
	}
	if(::Save(f,y)==false){
		return false;
	}
	return true;
}
bool	DoublePoint::Load(QIODevice *f)
{
	if(::Load(f,x)==false){
		return false;
	}
	if(::Load(f,y)==false){
		return false;
	}
	return true;
}

bool	XYClass::Save(QIODevice *f)
{
	if(::Save(f,x)==false){
		return false;
	}
	if(::Save(f,y)==false){
		return false;
	}
	return true;
}
bool	XYClass::Load(QIODevice *f)
{
	if(::Load(f,x)==false){
		return false;
	}
	if(::Load(f,y)==false){
		return false;
	}
	return true;
}

bool	XYDoubleClass::Save(QIODevice *f)
{
	if(::Save(f,x)==false){
		return false;
	}
	if(::Save(f,y)==false){
		return false;
	}
	return true;
}
bool	XYDoubleClass::Load(QIODevice *f)
{
	if(::Load(f,x)==false){
		return false;
	}
	if(::Load(f,y)==false){
		return false;
	}
	return true;
}

//============================================================================
XYClassContainer::XYClassContainer(const XYClassContainer &src)
{
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
	}
}
bool    XYClassContainer::Save(QIODevice  *file)
{
    int N=NPListPack<XYClass>::GetNumber();
    if(file->write((const char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(file->write((const char *)&(c->x),sizeof(c->x))!=sizeof(c->x)){
            return(false);
		}
		if(file->write((const char *)&(c->y),sizeof(c->y))!=sizeof(c->y)){
            return(false);
		}
    }
    return(true);
}
bool    XYClassContainer::Load(QIODevice  *file)
{
    RemoveAll();
    int N;
    if(file->read((char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(int i=0;i<N;i++){
        int mx,my;
		if(file->read((char *)&mx,sizeof(mx))!=sizeof(mx)){
            return(false);
		}
		if(file->read((char *)&my,sizeof(my))!=sizeof(my)){
            return(false);
		}
        XYClass *c=new XYClass(mx,my);
        AppendList(c);
    }
    return(true);
}
void    XYClassContainer::MoveTo(int dx ,int dy)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		c->x+=dx;
		c->y+=dy;
	}
}
bool	XYClassContainer::operator==(const XYClassContainer &src)	const
{
	XYClass *c1;
	XYClass *c2;
	for(c1=NPListPack<XYClass>::GetFirst(),c2=src.NPListPack<XYClass>::GetFirst()
	;c1!=NULL && c2!=NULL;c1=c1->GetNext(),c2=c2->GetNext()){
		if(*c1!=*c2){
			return false;
		}
	}
	if(c1==NULL && c2==NULL){
		return true;
	}
	return false;
}
void	XYClassContainer::Add(int x ,int y)
{
	AppendList(new XYClass(x,y));
}
bool    XYClassContainer::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;
	bool	Ret=false;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(minx>c->x){
            minx=c->x;
		}
		if(miny>c->y){
            miny=c->y;
		}
		if(maxx<c->x){
            maxx=c->x;
		}
		if(maxy<c->y){
            maxy=c->y;
		}
		Ret=true;
    }
	return Ret;
}

void    XYClassContainer::GetCenter(int &cx ,int &cy)	const
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    if(GetXY(minx ,miny ,maxx ,maxy)==true){
	    cx=(minx+maxx)/2;
		cy=(miny+maxy)/2;
	}
}
bool	XYClassContainer::IsIsclude(int x ,int y)	const
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(c->x==x && c->y==y){
			return true;
		}
	}
	return false;
}
bool	XYClassContainer::IsIsclude(int x ,int y ,int radius)	const
{
	int	x1=x-radius;
	int	y1=y-radius;
	int	x2=x+radius;
	int	y2=y+radius;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(x1<=c->x && c->x<=x2 && y1<=c->y && c->y<=y2){
			return true;
		}
	}
	return false;
}

XYClassContainer &XYClassContainer::operator=(const XYClassContainer &src)
{
    NPListPack<XYClass>::RemoveAll();
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
	}
    return(*this);
}

void	XYClassContainer::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	Rx;
	int	Ry;
	XYClass *c=NPListPack<XYClass>::GetFirst();
	if(c!=NULL){
		Rx=(c->x+movx)*ZoomRate;
		Ry=(c->y+movy)*ZoomRate;
	
		for(c=(XYClass *)c->GetNext();c!=NULL;c=(XYClass *)c->GetNext()){
			int	Qx=(c->x+movx)*ZoomRate;
			int	Qy=(c->y+movy)*ZoomRate;
			if(Qx!=Rx || Qy!=Ry){
				pnt.drawLine(Rx,Ry,Qx,Qy);
				Rx=Qx;
				Ry=Qy;
			}
		}
	}
}
double	XYClassContainer::GetDistance(int x, int y)	const
{
	double	MinLen=99999999;
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		double	Len=hypot(c->x-x,c->y-y);
		if(MinLen>Len){
			MinLen=Len;
		}
	}
	return MinLen;
}

//============================================================================
XYDoubleClassContainer::XYDoubleClassContainer(const XYDoubleClassContainer &src)
{
    for(XYDoubleClass *c=src.NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=(XYDoubleClass *)c->GetNext()){
        XYDoubleClass *d=new XYDoubleClass();
        *d=*c;
        NPListPack<XYDoubleClass>::AppendList(d);
	}
}
bool    XYDoubleClassContainer::Save(QIODevice  *file)
{
    int N=NPListPack<XYDoubleClass>::GetNumber();
    if(file->write((const char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(file)==false){
			return false;
		}
    }
    return(true);
}
bool    XYDoubleClassContainer::Load(QIODevice  *file)
{
    RemoveAll();
    int N;
    if(file->read((char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(int i=0;i<N;i++){
        XYDoubleClass *c=new XYDoubleClass();
		if(c->Load(file)==false){
			delete	c;
			return false;
		}
        AppendList(c);
    }
    return(true);
}
void    XYDoubleClassContainer::MoveTo(int dx ,int dy)
{
    for(XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=c->GetNext()){
		c->x+=dx;
		c->y+=dy;
	}
}
bool    XYDoubleClassContainer::GetXY(double &minx ,double &miny ,double &maxx ,double &maxy)	const
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;
	bool	Ret=false;
    for(XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(minx>c->x){
            minx=c->x;
		}
		if(miny>c->y){
            miny=c->y;
		}
		if(maxx<c->x){
            maxx=c->x;
		}
		if(maxy<c->y){
            maxy=c->y;
		}
		Ret=true;
    }
	return Ret;
}

void    XYDoubleClassContainer::GetCenter(double &cx ,double &cy)	const
{
    double minx;
    double miny;
    double maxx;
    double maxy;
    if(GetXY(minx ,miny ,maxx ,maxy)==true){
	    cx=(minx+maxx)/2;
		cy=(miny+maxy)/2;
	}
}
bool	XYDoubleClassContainer::IsIsclude(int x ,int y)	const
{
    for(XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=(XYDoubleClass *)c->GetNext()){
		if(c->x==x && c->y==y){
			return true;
		}
	}
	return false;
}
double	XYDoubleClassContainer::GetDistance(int x, int y)	const
{
	double	MinLen=99999999;
	for(XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=(XYDoubleClass *)c->GetNext()){
		double	Len=hypot(c->x-x,c->y-y);
		if(MinLen>Len){
			MinLen=Len;
		}
	}
	return MinLen;
}


XYDoubleClassContainer &XYDoubleClassContainer::operator=(const XYDoubleClassContainer &src)
{
    NPListPack<XYDoubleClass>::RemoveAll();
    for(XYDoubleClass *c=src.NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=(XYDoubleClass *)c->GetNext()){
        XYDoubleClass *d=new XYDoubleClass();
        *d=*c;
        NPListPack<XYDoubleClass>::AppendList(d);
	}
    return(*this);
}

void	XYDoubleClassContainer::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	double	Rx;
	double	Ry;
	XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();
	if(c!=NULL){
		Rx=(c->x+movx)*ZoomRate;
		Ry=(c->y+movy)*ZoomRate;
	
		for(c=(XYDoubleClass *)c->GetNext();c!=NULL;c=(XYDoubleClass *)c->GetNext()){
			double	Qx=(c->x+movx)*ZoomRate;
			double	Qy=(c->y+movy)*ZoomRate;
			if(Qx!=Rx || Qy!=Ry){
				pnt.drawLine(Rx,Ry,Qx,Qy);
				Rx=Qx;
				Ry=Qy;
			}
		}
	}
}


//============================================================================
bool    XYClassArea::Write(QIODevice *file)
{
    int N=NPListPack<XYClass>::GetNumber();
    if(file->write((const char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(file->write((const char *)&(c->x),sizeof(c->x))!=sizeof(c->x)){
            return(false);
		}
		if(file->write((const char *)&(c->y),sizeof(c->y))!=sizeof(c->y)){
            return(false);
		}
    }
    return(true);
}
bool    XYClassArea::Read(QIODevice  *file)
{
    RemoveAll();
    int N;
    if(file->read((char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(int i=0;i<N;i++){
        int mx,my;
		if(file->read((char *)&mx,sizeof(mx))!=sizeof(mx)){
            return(false);
		}
		if(file->read((char *)&my,sizeof(my))!=sizeof(my)){
            return(false);
		}
        XYClass *c=new XYClass(mx,my);
        AppendList(c);
    }
    return(true);

}

void    XYClass::ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines)
{
    swap(x,y);
    y=-y;
    y+=outlineOffset[MaxPage-1].y+maxlines;
}

void    XYDoubleClass::ChangeXY(XYDoubleClass *outlineOffset ,int MaxPage,int maxlines)
{
    swap(x,y);
    y=-y;
    y+=outlineOffset[MaxPage-1].y+maxlines;
}

void    XYClassArea::SetRectangle(QRect &rect)
{
    RemoveAll();

    for(int i=rect.top();i<rect.bottom();i++){
        XYClass *c=new XYClass(rect.left(),i);
        AppendList(c);
        }
    for(int i=rect.left();i<rect.right();i++){
        XYClass *c=new XYClass(i,rect.bottom());
        AppendList(c);
        }
    for(int i=rect.bottom();i>rect.top();i--){
        XYClass *c=new XYClass(rect.right(),i);
        AppendList(c);
        }
    for(int i=rect.right();i>=rect.left();i--){
        XYClass *c=new XYClass(i,rect.top());
        AppendList(c);
        }
}

int XYClassArea::transtofunc(const void *a ,const void *b)
{
	if(((struct XYM_Data *)a)->y>((struct XYM_Data *)b)->y){
        return(1);
	}
	if(((struct XYM_Data *)a)->y<((struct XYM_Data *)b)->y){
        return(-1);
	}
	if(((struct XYM_Data *)a)->x1>((struct XYM_Data *)b)->x1){
        return(1);
	}
	if(((struct XYM_Data *)a)->x1<((struct XYM_Data *)b)->x1){
        return(-1);
	}
    return(0);
}

void    XYClassArea::TransTo(FlexArea &area)
{
    XYClassArea TmpArea;
    for(XYClass *c1=NPListPack<XYClass>::GetFirst();c1!=NULL;c1=c1->GetNext()){
        XYClass *c2=c1->GetNext();
		if(c2==NULL){
            c2=NPListPack<XYClass>::GetFirst();
		}
        int dx=c2->x - c1->x;
        int dy=c2->y - c1->y;
        int ldx=abs(dx);
        int ldy=abs(dy);
		if(ldx==0 && ldy==0){
            continue;
		}
        if(ldx>=ldy){
            for(int i=0;i<ldx;i++){
                XYClass *d=new XYClass();
                d->x=c1->x+dx*i/ldx;
                d->y=c1->y+dy*i/ldx;
                TmpArea.AppendList(d);
                }
            }
        else{
            for(int i=0;i<ldy;i++){
                XYClass *d=new XYClass();
                d->x=c1->x+dx*i/ldy;
                d->y=c1->y+dy*i/ldy;
                TmpArea.AppendList(d);
                }
            }
        }
    TmpArea.TransToInner(area);
    area.Regulate();
}

void    XYClassArea::TransToInner(FlexArea &area)
{
    struct  XYM_Data    *d=new struct XYM_Data[NPListPack<XYClass>::GetNumber()];

    int n=0;
    int LastX=-1,LastY=-1;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        if(LastY!=c->y || abs(LastX-c->x)>1){
            d[n].x1=c->x;
            d[n].x2=c->x;
            d[n].y =c->y;
            n++;
            }
        else if(n>=1){
            d[n-1].x2=c->x;
        }
        LastX=c->x;
        LastY=c->y;
    }
    for(int i=0;i<n;i++){
		if(d[i].x1>d[i].x2){
            swap(d[i].x1,d[i].x2);
		}
	}
    if(NPListPack<XYClass>::GetFirst()!=NULL && NPListPack<XYClass>::GetLast()!=NULL){
        if(n>=2
		&& NPListPack<XYClass>::GetFirst()->y==d[n-1].y
        && NPListPack<XYClass>::GetFirst()->x!=NPListPack<XYClass>::GetLast()->x){
			if(d[0].x1>d[n-1].x2){
                d[0].x1=d[n-1].x1;
			}
			else if(d[0].x2<d[n-1].x1){
                d[0].x2=d[n-1].x2;
			}
            d[n-2].x2=d[n-1].x2;
            n--;
            }
        }

    for(int i=0;i<n;i++){
		//if(d[i].x1>d[i].x2){
        //    swap(d[i].x1,d[i].x2);
		//}
        d[i].YPole=false;
        if(i>=1 && i<n-1){
			if(d[i-1].y<d[i].y && d[i].y>d[i+1].y){
                d[i].YPole=true;
			}
			else if(d[i-1].y>d[i].y && d[i].y<d[i+1].y){
                d[i].YPole=true;
			}
        }
    }
    if(n>=3){
		if(d[n-1].y<d[0].y && d[0].y>d[1].y){
            d[0].YPole=true;
		}
		else if(d[n-1].y>d[0].y && d[0].y<d[1].y){
            d[0].YPole=true;
		}
    }

    QSort(d,n,sizeof(d[0]),transtofunc);
	if(n>=2 && d[0].y!=d[1].y){
        d[0].YPole=true;
	}
	if(n>=2 && d[0].y==d[1].y && d[1].YPole==true){
        d[0].YPole=true;
	}

    for(int i=1;i<n;i++){
        bool    NoPile=true;
        int j;
        for(j=i-1;j>=0 && (d[j].y==d[i].y);j--);
        for(;j>=0 && (d[j].y==d[i].y-1);j--){
            if((d[j].x1-2<=d[i].x1 && d[i].x1-2<=d[j].x2)
            || (d[j].x1-2<=d[i].x2 && d[i].x2-2<=d[j].x2)
            || (d[i].x1-2<=d[j].x1 && d[j].x1-2<=d[i].x2)
            || (d[i].x1-2<=d[j].x2 && d[j].x2-2<=d[i].x2)){
                NoPile=false;
                break;
                }
            }
        if(NoPile==true)
            d[i].YPole=true;
        }
    /*
    for(int i=1;i<n;i++){
        if(d[i-1].y==d[i].y && d[i-1].x2==d[i].x1-1){
            d[i-1].x2=d[i].x2;
            memmove(&d[i],&d[i+1],(n-i)*sizeof(d[0]));
            n--;
            }
        }
    */
    for(int i=1;i<n-1;i++){
        if(d[i-1].y!=d[i].y && d[i].y!=d[i+1].y && d[i].YPole==false){
            memmove(&d[i+1],&d[i],(n-i)*sizeof(d[0]));
            n++;
            d[i].x2=d[i].x1;
            d[i+1].x1=d[i+1].x2;
            }
        }

    struct FlexLine *Tmp=new struct FlexLine[n+1];
    int TmpNumb=0;

    area.Clear();
    int NowY=-1;
    int NowX=-1;
    int NowX2;
    bool    LineMode=false;
    for(int i=0;i<n;i++){
        if(NowY!=d[i].y){
            if(LineMode==true && NowX!=NowX2){
                if(TmpNumb==0
                || Tmp[TmpNumb-1]._GetAbsY()!=NowY
                || Tmp[TmpNumb-1]._GetLeftX()+Tmp[TmpNumb-1].GetNumb()<NowX){
                    Tmp[TmpNumb]._Set(NowX,NowX2,NowY);
                    TmpNumb++;
                    }
                else{
                    Tmp[TmpNumb-1].SetNumb(NowX2-Tmp[TmpNumb-1]._GetLeftX());
                    if(Tmp[TmpNumb-1].GetNumb()==0)
                        Tmp[TmpNumb-1].SetNumb(1);
                    }
                }
            LineMode=false;
            }
        /*
        else if(LineMode==true && NowX!=NowX2){
            for(int j=TmpNumb-1;j>=0;j--){
                if(Tmp[j].AbsY<NowY-1)
                    break;
                if(Tmp[j].AbsY==NowY-1){
                    if((Tmp[j].LeftX-1<=NowX  && NowX <=Tmp[j].LeftX+Tmp[j].Numb+1)
                    || (Tmp[j].LeftX-1<=NowX2 && NowX2<=Tmp[j].LeftX+Tmp[j].Numb+1)){
                        if(d[i].x2<Tmp[j].LeftX-1 || Tmp[j].LeftX+Tmp[j].Numb+1<d[i].x2){
                            if(TmpNumb==0
                            || Tmp[TmpNumb-1].AbsY!=NowY
                            || Tmp[TmpNumb-1].LeftX+Tmp[TmpNumb-1].Numb<NowX){
                                Tmp[TmpNumb].Set(NowX,NowX2,NowY);
                                TmpNumb++;
                                LineMode=false;
                                }
                            else{
                                Tmp[TmpNumb-1].Numb=NowX2-Tmp[TmpNumb-1].LeftX;
                                }
                            }
                        break;
                        }
                    }
                }
            }
        */

        if(LineMode==true){
            if(d[i].YPole==true){
                if(TmpNumb==0
                || Tmp[TmpNumb-1]._GetAbsY()!=d[i].y
                || Tmp[TmpNumb-1]._GetLeftX()!=NowX
                || Tmp[TmpNumb-1].GetNumb()!=1){
                    Tmp[TmpNumb]._Set(NowX,d[i].x2,d[i].y);
                    TmpNumb++;
                    }
                else{
                    Tmp[TmpNumb-1]._Set(NowX,d[i].x2,d[i].y);
                    }

                LineMode=true;
                NowX=d[i].x2;
                NowX2=d[i].x2;
                }
            else{
                if(TmpNumb==0
                || Tmp[TmpNumb-1]._GetAbsY ()!=d[i].y
                || Tmp[TmpNumb-1]._GetLeftX()!=NowX
                || Tmp[TmpNumb-1].GetNumb ()!=1){
                    Tmp[TmpNumb]._Set(NowX,d[i].x2,d[i].y);
                    TmpNumb++;
                    }
                else{
                    Tmp[TmpNumb-1]._Set(NowX,d[i].x2,d[i].y);
                    }

                LineMode=false;
                NowX=d[i].x2;
                }
            }
        else{
            if(d[i].YPole==true){
                if(d[i].x1!=d[i].x2){
                    //FlexLine    m(d[i].x1,d[i].x2,d[i].y);
                    //area.AddPoint(m);
                    if(TmpNumb==0
                    || Tmp[TmpNumb-1]._GetAbsY ()!=d[i].y
                    || Tmp[TmpNumb-1]._GetLeftX()!=d[i].x1
                    || Tmp[TmpNumb-1].GetNumb ()!=1){
                        Tmp[TmpNumb]._Set(d[i].x1,d[i].x2,d[i].y);
                        TmpNumb++;
                        }
                    else{
                        Tmp[TmpNumb-1]._Set(d[i].x1,d[i].x2,d[i].y);
                        }
                    }
                LineMode=false;
                NowX=d[i].x2;
                }
            else{
                LineMode=true;
                NowX=d[i].x1;
                NowX2=d[i].x2;
                }
            }
        NowY=d[i].y;
        }

    delete  []d;

    area._AddPoints(Tmp,TmpNumb);
    delete  []Tmp;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x
//    y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassArea::IsInclude(int x ,int y)	const
{
    XYClass key(x,y);

    return(LinesRound(*((const NPListPack<XYClass> *)this) ,key));
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x1
//    y1
//    x2
//    y2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassArea::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)	const
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        XYClass *d=c->GetNext();
		if(d==NULL){
            d=NPListPack<XYClass>::GetFirst();
		}
        if(CheckOverlapRectLine(x1, y1, x2, y2
			,c->x,c->y,d->x,d->y)==true){
            return(true);
		}
    }
    XYClass  P;
    P.x=(x1+x2)/2;
    P.y=(y1+y2)/2;
	if(LinesRound(*((const NPListPack<XYClass> *)this) ,P)==true){
        return(true);
	}

    return(false);
}


bool    XYClassArea::IsValid(void)	const
{
	if(NPListPack<XYClass>::GetNumber()<=2){
        return(false);
	}
    return(true);
}

bool    XYClassCluster::Validate(void)
 //無効な領域を削除する
{
    for(XYClassArea *a=GetFirst();a!=NULL;){
		if(a->IsValid()==true){
            a=a->GetNext();
		}
        else{
            XYClassArea *NextA=a->GetNext();
            RemoveList(a);
            delete  a;
            a=NextA;
            }
        }
	if(GetNumber()==0){
        return(false);
	}
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    file
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassCluster::Write(QIODevice *file)
{
    int N=GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
        return(false);
	}
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Write(file)==false){
            return(false);
		}
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    file
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassCluster::Read(QIODevice *file)
{
    int N;
	RemoveAll();
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
        return(false);
	}
    for(int i=0;i<N;i++){
        XYClassArea *a=new XYClassArea();
		if(a->Read(file)==false){
            return(false);
		}
        AppendList(a);
     }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    rect
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    XYClassCluster::SetRectangle(QRect &rect)
{
    RemoveAll();
    XYClassArea *a=new XYClassArea();
    a->SetRectangle(rect);
    AppendList(a);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x
//    y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassCluster::IsInclude(int x ,int y)	const
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y)==true){
            return(true);
		}
    }
    return(false);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x1
//    y1
//    x2
//    y2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassCluster::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)	const
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOverlapLine(x1, y1 ,x2 ,y2)==true){
            return(true);
		}
    }
    return(false);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    area
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    XYClassCluster::TransTo(FlexArea &area)
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
        FlexArea m;
        a->TransTo(m);
        area+=m;
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    dx
//    dy
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    XYClassCluster::MoveTo(int dx ,int dy)
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
        a->MoveTo(dx,dy);
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    angle
//    cx
//    cy
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    XYClassCluster::Rotate(double angle ,int cx ,int cy)
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
        a->Rotate(angle ,cx ,cy);
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x1
//    y1
//    x2
//    y2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    XYClassCluster::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)	const
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOverlapRectangle(x1, y1 ,x2 ,y2)==true){
            return(true);
		}
    }
    return(false);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    dx
//    dy
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    XYClassArea::MoveTo(int dx ,int dy)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        c->x+=dx;
        c->y+=dy;
        }
}

bool    XYClassArea::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)	const
{
    long X;
    long Y;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        XYClass *d=c->GetNext();
		if(d!=NULL){
            d=NPListPack<XYClass>::GetFirst();
		}
        if(d!=NULL && GetCrossInnerPoint(x1,y1,x2,y2
			,c->x,c->y,d->x,d->y, X ,Y)==true){
            return(true);
		}
    }
    XYClass  P;
    P.x=x1;
    P.y=y1;
	if(LinesRound(*((const NPListPack<XYClass> *)this) ,P)==true){
        return(true);
	}

    return(false);
}

void    XYClassArea::Regulate(void)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;){
        XYClass *c2=c->GetNext();
		if(c2==NULL){
            break;
		}
        if(c->x==c2->x
        && c->y==c2->y){
            NPListPack<XYClass>::RemoveList(c2);
			delete	c2;
            }
        else{
            c=c->GetNext();
            }
        }
}
void	XYClassArea::Simplize(void)
{
	Regulate();
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;){
        XYClass *c2=c->GetNext();
		if(c2==NULL)
			break;
		XYClass *c3=c2->GetNext();
		if(c3==NULL){
            break;
		}
		double	L1=hypot(c->x-c2->x,c->y-c2->y);
		double	L2=hypot(c2->x-c3->x,c2->y-c3->y);
		if(fabs(L1)<0.00001 || fabs(L2)==0.00001){
			c=c->GetNext();
			continue;
		}
		double	V1x=(c2->x-c->x)/L1;
		double	V1y=(c2->y-c->y)/L1;

		double	V2x=(c3->x-c2->x)/L2;
		double	V2y=(c3->y-c2->y)/L2;

		double	Dx=V1x-V2x;
		double	Dy=V1y-V2y;

		if((0<=Dx && Dx<0.00001 && 0<=Dy && Dy<0.00001) || (0<=(-Dx) && (-Dx)<0.00001 && 0<=(-Dy) && (-Dy)<0.00001)){
			NPListPack<XYClass>::RemoveList(c2);
			delete	c2;
		}
		else{
			c=c->GetNext();
		}
	}
}

void    XYClassArea::Rotate(double angle ,int cx ,int cy)
{
    double  coss=cos(angle);
    double  sins=sin(angle);

    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        int x= (c->x-cx)*coss + (c->y-cy)*sins;
        int y=-(c->x-cx)*sins + (c->y-cy)*coss;
        c->x=x+cx;
        c->y=y+cy;
        }
}

bool    XYClassArea::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;
	bool	Ret=false;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(minx>c->x){
            minx=c->x;
		}
		if(miny>c->y){
            miny=c->y;
		}
		if(maxx<c->x){
            maxx=c->x;
		}
		if(maxy<c->y){
            maxy=c->y;
		}
		Ret=true;
    }
	return Ret;
}

XYClassArea &XYClassArea::operator=(const XYClassArea &src)
{
    NPListPack<XYClass>::RemoveAll();
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
    }
    return(*this);
}

void    XYClassArea::GetCenter(int &cx ,int &cy)	const
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    if(GetXY(minx ,miny ,maxx ,maxy)==true){
	    cx=(minx+maxx)/2;
		cy=(miny+maxy)/2;
	}
}

void    XYClassArea::ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        c->ChangeXY(outlineOffset ,MaxPage,maxlines);
        }
}

void	XYClassArea::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	Rx;
	int	Ry;
	XYClass *c=NPListPack<XYClass>::GetFirst();
	if(c!=NULL){
		Rx=(c->x+movx)*ZoomRate;
		Ry=(c->y+movy)*ZoomRate;
	
		for(c=(XYClass *)c->GetNext();c!=NULL;c=(XYClass *)c->GetNext()){
			int	Qx=(c->x+movx)*ZoomRate;
			int	Qy=(c->y+movy)*ZoomRate;
			if(Qx!=Rx || Qy!=Ry){
				pnt.drawLine(Rx,Ry,Qx,Qy);
				Rx=Qx;
				Ry=Qy;
			}
		}
	}
	c=NPListPack<XYClass>::GetFirst();
	if(c!=NULL){
		int	Qx=(c->x+movx)*ZoomRate;
		int	Qy=(c->y+movy)*ZoomRate;
		if(Qx!=Rx || Qy!=Ry){
			pnt.drawLine(Rx,Ry,Qx,Qy);
			Rx=Qx;
			Ry=Qy;
		}
	}
}

void	XYClassArea::GenerateEdge(ImagePointerContainer &ImageList ,int FirstX ,int FirstY,int SearchDot ,int MaxLength)
{
	int tx ,ty;
	RemoveAll();

	FindMaxWeight(ImageList ,FirstX,FirstY ,tx ,ty,SearchDot);
	XYClass	*a=new XYClass(tx,ty);
	AppendList(a);
	FirstX=tx;
	FirstY=ty;
	int	MaxLength2=MaxLength/2;

	for(int i=0;i<MaxLength2;i++){
		int LastX=tx;
		int	LastY=ty;
		if(FindMaxWeightNext(ImageList ,LastX,LastY ,tx ,ty,SearchDot)==false){
			break;
		}
		XYClass	*f1=NPListPack<XYClass>::GetFirst();
		if(f1!=NULL){
			XYClass	*f2=f1->GetNext();
			if(f2!=NULL){
				if(GetLengthLine2Point(f1->x,f1->y,f2->x,f2->y,tx,ty)<=2){
					//Loop pixels
					return;
				}
			}
		}
		XYClass	*b=new XYClass(tx,ty);
		AppendList(b);
	}
	/*
	if(GetCount()>3){
		XYClassArea	t;
		XYClass	*f1=NPListPack<XYClass>::GetFirst();
		XYClass	*f2=f1->GetNext();
		t.AppendList(new XYClass(*f2));
		t.AppendList(new XYClass(*f1));

		tx=FirstX;
		ty=FirstY;
		while((t.GetCount())<MaxLength2){
			int LastX=tx;
			int	LastY=ty;
			if(t.FindMaxWeightNext(ImageList ,LastX,LastY ,tx ,ty,SearchDot)==false){
				break;
			}
			if(tx==FirstX && ty==FirstY){
				//Loop pixels
				Move(t);
				return;
			}
			XYClass	*b=new XYClass(tx,ty);
			t.AppendList(b);
		}
		XYClassArea	R;
		XYClass	*r;
		while((r=t.NPListPack<XYClass>::GetLast())!=NULL){
			t.RemoveList(r);
			R.AppendList(r);
		}
		R.AddMove(*this);
		Move(R);
	}
	*/
}

bool	XYClassArea::CalcWeight(ImagePointerContainer &ImageList ,struct XYAreaWithWeight &Ret ,int Lastx ,int Lasty)
{
	int	Lx=Ret.X-Lastx;
	int	Ly=Ret.Y-Lasty;
	double	Len=hypot(Lx,Ly);
	double	Vx=-Ly/Len;
	double	Vy= Lx/Len;

	int	x1=Ret.X+Vx*3.5;
	int	y1=Ret.Y+Vy*3.5;
	int	x2=Ret.X-Vx*3.5;
	int	y2=Ret.Y-Vy*3.5;

	int	W=ImageList.GetWidth();
	int	H=ImageList.GetHeight();

	if(0<=(x1-1) && (x1+1)<W && 0<=(y1-1) && (y1+1)<H
	&& 0<=(x2-1) && (x2+1)<W && 0<=(y2-1) && (y2+1)<H){
		QRgb	s11=ImageList.GetColorRgb(x1-1,y1-1);
		QRgb	s12=ImageList.GetColorRgb(x1  ,y1-1);
		QRgb	s13=ImageList.GetColorRgb(x1+1,y1-1);
		QRgb	s21=ImageList.GetColorRgb(x1-1,y1  );
		QRgb	s22=ImageList.GetColorRgb(x1  ,y1  );
		QRgb	s23=ImageList.GetColorRgb(x1+1,y1  );
		QRgb	s31=ImageList.GetColorRgb(x1-1,y1+1);
		QRgb	s32=ImageList.GetColorRgb(x1  ,y1+1);
		QRgb	s33=ImageList.GetColorRgb(x1+1,y1+1);
		QRgb	t11=ImageList.GetColorRgb(x2-1,y2-1);
		QRgb	t12=ImageList.GetColorRgb(x2  ,y2-1);
		QRgb	t13=ImageList.GetColorRgb(x2+1,y2-1);
		QRgb	t21=ImageList.GetColorRgb(x2-1,y2  );
		QRgb	t22=ImageList.GetColorRgb(x2  ,y2  );
		QRgb	t23=ImageList.GetColorRgb(x2+1,y2  );
		QRgb	t31=ImageList.GetColorRgb(x2-1,y2+1);
		QRgb	t32=ImageList.GetColorRgb(x2  ,y2+1);
		QRgb	t33=ImageList.GetColorRgb(x2+1,y2+1);
		int	dR=	 qRed(s11)+qRed(s12)+qRed(s13)
				+qRed(s21)+qRed(s22)+qRed(s23)
				+qRed(s31)+qRed(s32)+qRed(s33)
			   -(qRed(t11)+qRed(t12)+qRed(t13)
				+qRed(t21)+qRed(t22)+qRed(t23)
				+qRed(t31)+qRed(t32)+qRed(t33));
		int	dG=	 qGreen(s11)+qGreen(s12)+qGreen(s13)
				+qGreen(s21)+qGreen(s22)+qGreen(s23)
				+qGreen(s31)+qGreen(s32)+qGreen(s33)
			   -(qGreen(t11)+qGreen(t12)+qGreen(t13)
				+qGreen(t21)+qGreen(t22)+qGreen(t23)
				+qGreen(t31)+qGreen(t32)+qGreen(t33));
		int	dB=	 qBlue(s11)+qBlue(s12)+qBlue(s13)
				+qBlue(s21)+qBlue(s22)+qBlue(s23)
				+qBlue(s31)+qBlue(s32)+qBlue(s33)
			   -(qBlue(t11)+qBlue(t12)+qBlue(t13)
				+qBlue(t21)+qBlue(t22)+qBlue(t23)
				+qBlue(t31)+qBlue(t32)+qBlue(t33));
		Ret.Weight=dR*dR+dG*dG+dB*dB;
		return true;
	}
	return false;
}

void	XYClassArea::FindMaxWeight(ImagePointerContainer &ImageList ,int cx,int cy ,int &MaxDx ,int &MaxDy,int SearchDot)
{
	int		dx,dy;
	double	MaxD=0;

	dy=-SearchDot;
	for(dx=-SearchDot;dx<SearchDot;dx++){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
			if(MaxD<Ret.Weight){
				MaxD=Ret.Weight;
				MaxDx=Ret.X;
				MaxDy=Ret.Y;
			}
		}
	}
	for(dy=-SearchDot;dy<=SearchDot;dy++){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
			if(MaxD<Ret.Weight){
				MaxD=Ret.Weight;
				MaxDx=Ret.X;
				MaxDy=Ret.Y;
			}
		}
	}
	for(dx=SearchDot;dx>-SearchDot;dx--){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
			if(MaxD<Ret.Weight){
				MaxD=Ret.Weight;
				MaxDx=Ret.X;
				MaxDy=Ret.Y;
			}
		}
	}
	for(dy=SearchDot;dy>-SearchDot;dy--){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
			if(MaxD<Ret.Weight){
				MaxD=Ret.Weight;
				MaxDx=Ret.X;
				MaxDy=Ret.Y;
			}
		}
	}
}

bool	XYClassArea::CheckClosed(int x ,int y, int Length ,int Isolation)
{
	XYClass *a1=NPListPack<XYClass>::GetLast();
	if(a1==NULL)
		return false;
	for(int n=0;;n++){
		XYClass *a2=a1->GetPrev();
		if(a2==NULL)
			return false;
		if(hypot(a1->x-x,a1->y-y)<Isolation
		|| hypot(a2->x-x,a2->y-y)<Isolation){
			if(GetLengthLine2Point(a1->x,a1->y,a2->x,a2->y,x,y)<=Length){
				return true;
			}
		}
		a1=a2;
	}
	return false;
}

bool	XYClassArea::FindMaxWeightNext(ImagePointerContainer &ImageList ,int cx,int cy ,int &MaxDx ,int &MaxDy,int SearchDot)
{
	int		dx,dy;
	double	MaxD=0;
	int		Dif=SearchDot/2;
	bool	R=false;
	int		MinWeight=9*20*20*2;

	dy=-SearchDot;
	for(dx=-SearchDot;dx<SearchDot;dx++){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CheckClosed(Ret.X ,Ret.Y, Dif,SearchDot)==false){
			if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
				if(MaxD<Ret.Weight && Ret.Weight>MinWeight){
					struct XYAreaWithWeight Ret2;
					Ret2.X=cx+dx/2;
					Ret2.Y=cy+dy/2;
					if(CalcWeight(ImageList ,Ret2 ,cx ,cy)==true){
						if(Ret.Weight*0.6<Ret2.Weight){
							MaxD=Ret.Weight;
							MaxDx=Ret.X;
							MaxDy=Ret.Y;
							R=true;
						}
					}
				}
			}
		}
	}
	for(dy=-SearchDot;dy<=SearchDot;dy++){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CheckClosed(Ret.X ,Ret.Y, Dif,SearchDot)==false){
			if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
				if(MaxD<Ret.Weight && Ret.Weight>MinWeight){
					struct XYAreaWithWeight Ret2;
					Ret2.X=cx+dx/2;
					Ret2.Y=cy+dy/2;
					if(CalcWeight(ImageList ,Ret2 ,cx ,cy)==true){
						if(Ret.Weight*0.6<Ret2.Weight){
							MaxD=Ret.Weight;
							MaxDx=Ret.X;
							MaxDy=Ret.Y;
							R=true;
						}
					}
				}
			}
		}
	}
	for(dx=SearchDot;dx>-SearchDot;dx--){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CheckClosed(Ret.X ,Ret.Y, Dif,SearchDot)==false){
			if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
				if(MaxD<Ret.Weight && Ret.Weight>MinWeight){
					struct XYAreaWithWeight Ret2;
					Ret2.X=cx+dx/2;
					Ret2.Y=cy+dy/2;
					if(CalcWeight(ImageList ,Ret2 ,cx ,cy)==true){
						if(Ret.Weight*0.6<Ret2.Weight){
							MaxD=Ret.Weight;
							MaxDx=Ret.X;
							MaxDy=Ret.Y;
							R=true;
						}
					}
				}
			}
		}
	}
	for(dy=SearchDot;dy>-SearchDot;dy--){
		struct XYAreaWithWeight Ret;
		Ret.X=cx+dx;
		Ret.Y=cy+dy;
		if(CheckClosed(Ret.X ,Ret.Y, Dif,SearchDot)==false){
			if(CalcWeight(ImageList ,Ret ,cx ,cy)==true){
				if(MaxD<Ret.Weight && Ret.Weight>MinWeight){
					struct XYAreaWithWeight Ret2;
					Ret2.X=cx+dx/2;
					Ret2.Y=cy+dy/2;
					if(CalcWeight(ImageList ,Ret2 ,cx ,cy)==true){
						if(Ret.Weight*0.6<Ret2.Weight){
							MaxD=Ret.Weight;
							MaxDx=Ret.X;
							MaxDy=Ret.Y;
							R=true;
						}
					}
				}
			}
		}
	}
	return R;
}
void	XYClassArea::SearchOutline(const ImagePointerContainer &ImageList,const XYClassArea &sOutline,int SearchDot)
{
	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	for(int dy=-SearchDot;dy<=SearchDot;dy++){
		for(int dx=-SearchDot;dx<=SearchDot;dx++){
			double	D=sOutline.CalcEdge(ImageList,dx,dy);
			if(D>=MaxD){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	XYClassArea *b=new XYClassArea();
	b->ClosedEdge(ImageList,&sOutline,MaxDx,MaxDy,SearchDot/2);
	Move(*b);
}

double	XYClassArea::CalcEdge(const ImagePointerContainer &ImageList,int dx,int dy)	const
{
	int	W=ImageList.GetWidth();
	int	H=ImageList.GetHeight();

	double	Ret=0;
	int		Numb=0;
	for(XYClass *a=NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		XYClass *aPrev=GetRingPrev(a);
		XYClass *aNext=GetRingNext(a);
		int	Lx=aNext->x - aPrev->x;
		int	Ly=aNext->y - aPrev->y;
		if(Lx==0 && Ly==0){
			continue;
		}
		double	Len=hypot(Lx,Ly);
		double	Vx=-Ly/Len;
		double	Vy= Lx/Len;

		int	x1=a->x+Vx*3.5+dx;
		int	y1=a->y+Vy*3.5+dy;
		int	x2=a->x-Vx*3.5+dx;
		int	y2=a->y-Vy*3.5+dy;

		if(0<=(x1-1) && (x1+1)<W && 0<=(y1-1) && (y1+1)<H
		&& 0<=(x2-1) && (x2+1)<W && 0<=(y2-1) && (y2+1)<H){
			QRgb	s11=ImageList.GetColorRgb(x1-1,y1-1);
			QRgb	s12=ImageList.GetColorRgb(x1  ,y1-1);
			QRgb	s13=ImageList.GetColorRgb(x1+1,y1-1);
			QRgb	s21=ImageList.GetColorRgb(x1-1,y1  );
			QRgb	s22=ImageList.GetColorRgb(x1  ,y1  );
			QRgb	s23=ImageList.GetColorRgb(x1+1,y1  );
			QRgb	s31=ImageList.GetColorRgb(x1-1,y1+1);
			QRgb	s32=ImageList.GetColorRgb(x1  ,y1+1);
			QRgb	s33=ImageList.GetColorRgb(x1+1,y1+1);
			QRgb	t11=ImageList.GetColorRgb(x2-1,y2-1);
			QRgb	t12=ImageList.GetColorRgb(x2  ,y2-1);
			QRgb	t13=ImageList.GetColorRgb(x2+1,y2-1);
			QRgb	t21=ImageList.GetColorRgb(x2-1,y2  );
			QRgb	t22=ImageList.GetColorRgb(x2  ,y2  );
			QRgb	t23=ImageList.GetColorRgb(x2+1,y2  );
			QRgb	t31=ImageList.GetColorRgb(x2-1,y2+1);
			QRgb	t32=ImageList.GetColorRgb(x2  ,y2+1);
			QRgb	t33=ImageList.GetColorRgb(x2+1,y2+1);
			int	dR=	 qRed(s11)+qRed(s12)+qRed(s13)
					+qRed(s21)+qRed(s22)+qRed(s23)
					+qRed(s31)+qRed(s32)+qRed(s33)
				   -(qRed(t11)+qRed(t12)+qRed(t13)
					+qRed(t21)+qRed(t22)+qRed(t23)
					+qRed(t31)+qRed(t32)+qRed(t33));
			int	dG=	 qGreen(s11)+qGreen(s12)+qGreen(s13)
					+qGreen(s21)+qGreen(s22)+qGreen(s23)
					+qGreen(s31)+qGreen(s32)+qGreen(s33)
				   -(qGreen(t11)+qGreen(t12)+qGreen(t13)
					+qGreen(t21)+qGreen(t22)+qGreen(t23)
					+qGreen(t31)+qGreen(t32)+qGreen(t33));
			int	dB=	 qBlue(s11)+qBlue(s12)+qBlue(s13)
					+qBlue(s21)+qBlue(s22)+qBlue(s23)
					+qBlue(s31)+qBlue(s32)+qBlue(s33)
				   -(qBlue(t11)+qBlue(t12)+qBlue(t13)
					+qBlue(t21)+qBlue(t22)+qBlue(t23)
					+qBlue(t31)+qBlue(t32)+qBlue(t33));
			Ret+=dR*dR+dG*dG+dB*dB;
			Numb++;
		}
	}
	if(Numb!=0){
		return Ret/Numb;
	}
	return 0;
}


void	XYClassArea::ClosedEdge(const ImagePointerContainer &ImageList ,const XYClassArea *s ,int dx,int dy,int SearchDot)
{
	int	W=ImageList.GetWidth();
	int	H=ImageList.GetHeight();
	XYClassArea	Ret;

	for(XYClass *a=s->NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		XYClass *aPrev=s->GetRingPrev(a);
		XYClass *aNext=s->GetRingNext(a);
		int	Lx=aNext->x - aPrev->x;
		int	Ly=aNext->y - aPrev->y;
		if(Lx==0 && Ly==0){
			continue;
		}
		double	Len=hypot(Lx,Ly);
		double	Vx=-Ly/Len;
		double	Vy= Lx/Len;

		int	MaxM=0;
		XYClass	*b=new XYClass(*a);
		for(int k=-SearchDot;k<=SearchDot;k++){
			int	x1=a->x+Vx*(k+3.5)+dx;
			int	y1=a->y+Vy*(k+3.5)+dy;
			int	x2=a->x+Vx*(k-3.5)+dx;
			int	y2=a->y+Vy*(k-3.5)+dy;

			if(0<=(x1-1) && (x1+1)<W && 0<=(y1-1) && (y1+1)<H
			&& 0<=(x2-1) && (x2+1)<W && 0<=(y2-1) && (y2+1)<H){
				QRgb	s11=ImageList.GetColorRgb(x1-1,y1-1);
				QRgb	s12=ImageList.GetColorRgb(x1  ,y1-1);
				QRgb	s13=ImageList.GetColorRgb(x1+1,y1-1);
				QRgb	s21=ImageList.GetColorRgb(x1-1,y1  );
				QRgb	s22=ImageList.GetColorRgb(x1  ,y1  );
				QRgb	s23=ImageList.GetColorRgb(x1+1,y1  );
				QRgb	s31=ImageList.GetColorRgb(x1-1,y1+1);
				QRgb	s32=ImageList.GetColorRgb(x1  ,y1+1);
				QRgb	s33=ImageList.GetColorRgb(x1+1,y1+1);
				QRgb	t11=ImageList.GetColorRgb(x2-1,y2-1);
				QRgb	t12=ImageList.GetColorRgb(x2  ,y2-1);
				QRgb	t13=ImageList.GetColorRgb(x2+1,y2-1);
				QRgb	t21=ImageList.GetColorRgb(x2-1,y2  );
				QRgb	t22=ImageList.GetColorRgb(x2  ,y2  );
				QRgb	t23=ImageList.GetColorRgb(x2+1,y2  );
				QRgb	t31=ImageList.GetColorRgb(x2-1,y2+1);
				QRgb	t32=ImageList.GetColorRgb(x2  ,y2+1);
				QRgb	t33=ImageList.GetColorRgb(x2+1,y2+1);
				int	dR=	 qRed(s11)+qRed(s12)+qRed(s13)
						+qRed(s21)+qRed(s22)+qRed(s23)
						+qRed(s31)+qRed(s32)+qRed(s33)
					   -(qRed(t11)+qRed(t12)+qRed(t13)
						+qRed(t21)+qRed(t22)+qRed(t23)
						+qRed(t31)+qRed(t32)+qRed(t33));
				int	dG=	 qGreen(s11)+qGreen(s12)+qGreen(s13)
						+qGreen(s21)+qGreen(s22)+qGreen(s23)
						+qGreen(s31)+qGreen(s32)+qGreen(s33)
					   -(qGreen(t11)+qGreen(t12)+qGreen(t13)
						+qGreen(t21)+qGreen(t22)+qGreen(t23)
						+qGreen(t31)+qGreen(t32)+qGreen(t33));
				int	dB=	 qBlue(s11)+qBlue(s12)+qBlue(s13)
						+qBlue(s21)+qBlue(s22)+qBlue(s23)
						+qBlue(s31)+qBlue(s32)+qBlue(s33)
					   -(qBlue(t11)+qBlue(t12)+qBlue(t13)
						+qBlue(t21)+qBlue(t22)+qBlue(t23)
						+qBlue(t31)+qBlue(t32)+qBlue(t33));
				int	M=dR*dR+dG*dG+dB*dB;
				if(MaxM<M){
					MaxM=M;
					b->x=a->x+Vx*k+dx;
					b->y=a->y+Vy*k+dy;
				}
			}
		}
		Ret.AppendList(b);
	}
	Move(Ret);
}

bool    XYClassCluster::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const
{
    int nminx,nminy;
    int nmaxx,nmaxy;
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;
	bool	Ret=false;
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
        if(a->GetXY(nminx,nminy,nmaxx,nmaxy)==true){
			if(nminx<minx){
		        minx=nminx;
			}
			if(nminy<miny){
		        miny=nminy;
			}
			if(nmaxx>maxx){
		        maxx=nmaxx;
			}
			if(nmaxy>maxy){
		        maxy=nmaxy;
			}
			Ret=true;
		}
    }
	return Ret;
}

void	XYClassCluster::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawLines(pnt ,ZoomRate ,movx ,movy);
	}
}

void    XYClassCluster::ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines)
{
    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
        a->ChangeXY(outlineOffset ,MaxPage,maxlines);
        }
}


XYClassCluster &XYClassCluster::operator=(const XYClassCluster &src)
{
    RemoveAll();
    for(XYClassArea *a=src.GetFirst();a!=NULL;a=a->GetNext()){
        XYClassArea *b=new XYClassArea();
        *b=*a;
        AppendList(b);
        }
    return(*this);
}

void	XYClassCluster::SearchOutline(const ImagePointerContainer &ImageList,const XYClassCluster &sOutline,int SearchDot)
{
	XYClassCluster	Ret;
	for(XYClassArea *a=sOutline.GetFirst();a!=NULL;a=a->GetNext()){
		XYClassArea	*b=new XYClassArea();
		b->SearchOutline(ImageList,*a,SearchDot);
		Ret.AppendList(b);
	}
	RemoveAll();
	Move(Ret);
}

RectClass::RectClass(const RectClass &src)
{
    x1	=src.x1;
	y1	=src.y1;
	x2	=src.x2;
	y2	=src.y2;
    attr=src.attr;
}
bool    RectClass::Save(QIODevice *f)
{
	if(f->write((const char *)&x1,sizeof(x1))!=sizeof(x1)){
        return(false);
	}
	if(f->write((const char *)&y1,sizeof(y1))!=sizeof(y1)){
        return(false);
	}
	if(f->write((const char *)&x2,sizeof(x2))!=sizeof(x2)){
        return(false);
	}
	if(f->write((const char *)&y2,sizeof(y2))!=sizeof(y2)){
        return(false);
	}

	if(f->write((const char *)&attr,sizeof(attr))!=sizeof(attr)){
        return(false);
	}
    return(true);
}
bool    RectClass::Load(QIODevice *f)
{
	if(f->read((char *)&x1,sizeof(x1))!=sizeof(x1)){
        return(false);
	}
	if(f->read((char *)&y1,sizeof(y1))!=sizeof(y1)){
        return(false);
	}
	if(f->read((char *)&x2,sizeof(x2))!=sizeof(x2)){
        return(false);
	}
	if(f->read((char *)&y2,sizeof(y2))!=sizeof(y2)){
        return(false);
	}

	if(f->read((char *)&attr,sizeof(attr))!=sizeof(attr)){
        return(false);
	}
    return(true);
}

bool	RectClass::IsInclude(int x ,int y)	const
{
	if(x1<=x && x<=x2 && y1<=y && y<=y2)
		return true;
	return false;
}
void	RectClass::DrawRect(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	X1=(x1+movx)*ZoomRate;
	int	Y1=(y1+movy)*ZoomRate;
	int	X2=(x2+movx)*ZoomRate;
	int	Y2=(y2+movy)*ZoomRate;
	pnt.drawLine(X1,Y1,X2,Y1);
	pnt.drawLine(X2,Y1,X2,Y2);
	pnt.drawLine(X2,Y2,X1,Y2);
	pnt.drawLine(X1,Y2,X1,Y1);
}

RectClassContainer::RectClassContainer(const RectClassContainer &src)
{
	for(RectClass *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RectClass *d=new RectClass(*s);
		AppendList(d);
	}
}
bool    RectClassContainer::Save(QIODevice *f)
{
    int32 N=GetCount();
    if(::Save(f,N)==false)
        return false;
    for(RectClass *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false){
			return false;
		}
    }
    return true;
}
bool	RectClassContainer::Load(QIODevice *f)
{
	int32	N;
    if(::Load(f,N)==false){
        return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		RectClass	*s=new RectClass();
		if(s->Load(f)==false){
			return false;
		}
		AppendList(s);
	}
	return true;
}


inline bool CheckCrossInnerPoint(int ax1,int bx1,int by1,int bx2,int by2 ,int &Y)
/*	２線分の交点を求める	これは、端点内に交点が存在しないとき、False が返る
							finish debug
	(bx1,by1) - (bx2,by2) に線分２の端点を入れる

	正常に交点が求められたとき、True が返る
	False が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		少なくとも一方が線分をなしていないとき
		２線分が重なるとき	  */
{
	if( (ax1<bx1 && ax1<bx2) || (bx1<ax1 && bx2<ax1) ){
		return(false);
	}
	if(ax1==bx1){
		Y=by1;
	}
	else if(ax1==bx2){
		Y=by2;
	}
	else{
		Y = (long)((double)(by1-by2)*(double)(ax1-bx1)/(double)(bx1-bx2)) + by1;
	}
	return(true);
}

int	static	dqfunc(const void *a ,const void *b)
{
	if(*((long *)a) - *((long *)b)<0){
		return(-1);
	}
	if(*((long *)a) - *((long *)b)>0){
		return(1);
	}
	return(0);

}


static	bool LinesRound(const NPListPack<XYClass> &D ,const XYClass  &P)
/*	P が線分で囲まれた範囲の内部の点かを調べる	finish debug

	D[0] D[1] .....D[n-1] に線分座標を入れる
	*/
{
	XYClass		*Dn,*Dn1;
	XYClass		*G1,*G2;
	int		i,numb;
	int		YDim[2000];
	int		*Y;

	int N=D.GetCount();
	N=2*N;
	if(N>=sizeof(YDim)/sizeof(YDim[0])){
		Y=new int[N];
	}
	else{
		Y=YDim;
	}

	numb=0;
	if((Dn=D.GetFirst())==NULL){
		if(Y!=YDim){
			delete	[]Y;
		}
		return(false);
	}
	Dn1=Dn->GetNext();
	for(;Dn1!=NULL ; Dn=Dn->GetNext(),Dn1=Dn1->GetNext()){
		if(Dn->x==P.x && Dn1->x==P.x){
			Y[numb]=Dn->y;
			Y[numb+1]=Dn1->y;
			numb+=2;
			}
		else if(CheckCrossInnerPoint(P.x
				     ,Dn->x ,Dn->y
					 ,Dn1->x,Dn1->y,Y[numb])==true){
			numb++;
		}
	}
	if(Dn->x==P.x && D.GetFirst()->x==P.x){
		Y[numb]=Dn->y;
		Y[numb+1]=D.GetFirst()->y;
		numb+=2;
		}
	if(CheckCrossInnerPoint(P.x
			     ,Dn->x ,Dn->y
				 ,D.GetFirst()->x ,D.GetFirst()->y,Y[numb])==true){
		numb++;
	}
	if(numb==0){
		if(Y!=YDim){
			delete	[]Y;
		}
		return(false);
	}
	QSort(Y,numb,sizeof(long) ,dqfunc);

	if(P.y<Y[0] || Y[numb-1]<P.y){
		if(Y!=YDim){
			delete	[]Y;
		}
		return(false);
	}
	for(i=0;i<numb-1;i++){
		if(Y[i]==Y[i+1]){
			for(Dn=D.GetFirst();Dn!=NULL;Dn=Dn->GetNext()){
				if(Dn->x==P.x && Dn->y==Y[i]){
					G1=Dn->GetPrev();
					if(G1==NULL){
						G1=D.GetLast();
					}
					G2=Dn->GetNext();
					if(G2==NULL){
						G2=D.GetFirst();
					}
					if(G2->x==P.x){
						while(G2->x==P.x){
							G2=G2->GetNext();
							if(G2==NULL){
								G2=D.GetFirst();
							}
						}
						if( (G1->x<P.x && P.x<G2->x)
						 || (G2->x<P.x && P.x<G1->x) ){
							memmove(&Y[i],&Y[i+1],(numb-i-1)*sizeof(long));
							numb--;
							break;
							}
						}
					if( (G1->x<P.x && P.x<G2->x)
					 || (G2->x<P.x && P.x<G1->x) ){
						memmove(&Y[i],&Y[i+1],(numb-i-1)*sizeof(long));
						numb--;
						break;
						}

					}
				}
			}
		}
	for(i=0;i<numb;i++){
		if(P.y<Y[i]){
			break;
		}
	}
	if(Y!=YDim){
		delete	[]Y;
	}

	if((i&1)==0){
		return(false);
	}
	return(true);
}
//=========================================================================================

XYLines::XYLines(void)
{
	MinX=0;
	MinY=0;
	MaxX=0;
	MaxY=0;
}
XYLines::XYLines(const XYLines &src)
{
	MinX=src.MinX;
	MinY=src.MinY;
	MaxX=src.MaxX;
	MaxY=src.MaxY;
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
	}
}
bool    XYLines::Write(QIODevice  *file)
{
    int N=NPListPack<XYClass>::GetNumber();
    if(file->write((const char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(file->write((const char *)&(c->x),sizeof(c->x))!=sizeof(c->x)){
            return(false);
		}
		if(file->write((const char *)&(c->y),sizeof(c->y))!=sizeof(c->y)){
            return(false);
		}
    }
    return(true);
}
bool    XYLines::Read(QIODevice  *file)
{
    RemoveAll();
    int N;
    if(file->read((char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(int i=0;i<N;i++){
        int mx,my;
		if(file->read((char *)&mx,sizeof(mx))!=sizeof(mx)){
            return(false);
		}
		if(file->read((char *)&my,sizeof(my))!=sizeof(my)){
            return(false);
		}
        XYClass *c=new XYClass(mx,my);
        AppendList(c);
    }

	MinX=-99999999;
	MinY=-99999999;
	MaxX=99999999;
	MaxY=99999999;
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		MinX=min(MinX,c->x);
		MinY=min(MinY,c->y);
		MaxX=max(MaxX,c->x);
		MaxY=max(MaxY,c->y);
	}
    return(true);

}

bool    XYLines::IsInclude(int x ,int y ,double AreaLength)	const
{
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		XYClass *d=c->GetNext();
		if(d==NULL){
			break;
		}
		int	X,Y;
		if(GetLinePointFoot(c->x,c->y,d->x,d->y ,x,y ,X,Y)==true){
			double	t=GetLengthLine2Point(c->x,c->y,d->x,d->y ,x,y);
			if(t<=AreaLength){
				return true;
			}
		}
	}
	return false;
}
void    XYLines::Rotate(double angle ,int cx ,int cy)
{
    double  coss=cos(angle);
    double  sins=sin(angle);

    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        int x= (c->x-cx)*coss + (c->y-cy)*sins;
        int y=-(c->x-cx)*sins + (c->y-cy)*coss;
        c->x=x+cx;
        c->y=y+cy;
	}
}
bool    XYLines::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)	const
{
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		XYClass *d=c->GetNext();
		if(d==NULL){
			break;
		}
		long	X,Y;
		if(GetCrossInnerPoint(x1,y1,x2,y2	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
	}
	return false;
}
bool    XYLines::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)	const
{
	int	X1=min(x1,x2);
	int	X2=max(x1,x2);
	int	Y1=min(y1,y2);
	int	Y2=max(y1,y2);
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		XYClass *d=c->GetNext();
		if(d==NULL){
			break;
		}
		long	X,Y;
		if(GetCrossInnerPoint(X1,Y1,X2,Y1	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
		if(GetCrossInnerPoint(X2,Y1,X2,Y2	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
		if(GetCrossInnerPoint(X2,Y2,X1,Y2	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
		if(GetCrossInnerPoint(X1,Y2,X1,Y1	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
	}
	XYClass *e=NPListPack<XYClass>::GetFirst();
	if(e!=NULL){
		if(X1<=e->x && e->x<=X2 && Y1<=e->y && e->y<=Y2){
			return true;
		}
	}

	return false;
}
void    XYLines::MoveTo(int dx ,int dy)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        c->x+=dx;
        c->y+=dy;
	}
}

bool    XYLines::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)	const
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;
	bool	Ret=false;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(minx>c->x){
            minx=c->x;
		}
		if(miny>c->y){
            miny=c->y;
		}
		if(maxx<c->x){
            maxx=c->x;
		}
		if(maxy<c->y){
            maxy=c->y;
		}
		Ret=true;
    }
	return Ret;
}
void    XYLines::GetCenter(int &cx ,int &cy)	const
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    if(GetXY(minx ,miny ,maxx ,maxy)==true){
	    cx=(minx+maxx)/2;
		cy=(miny+maxy)/2;
	}
}
void    XYLines::ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        c->ChangeXY(outlineOffset ,MaxPage,maxlines);
        }
}
bool    XYLines::IsValid(void)	const
{
	if(NPListPack<XYClass>::GetNumber()<=1){
        return(false);
	}
    return(true);
}
void    XYLines::Regulate(void)
{
	MinX=-99999999;
	MinY=-99999999;
	MaxX=99999999;
	MaxY=99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;){
        XYClass *c2=c->GetNext();
		if(c2==NULL){
            break;
		}
        if(c->x==c2->x
        && c->y==c2->y){
            NPListPack<XYClass>::RemoveList(c2);
			delete	c2;
		}
        else{
			MinX=min(MinX,c->x);
			MinY=min(MinY,c->y);
			MaxX=max(MaxX,c->x);
			MaxY=max(MaxY,c->y);
            c=c->GetNext();
		}
	}
}

XYLines &XYLines::operator=(const XYLines &src)
{
    NPListPack<XYClass>::RemoveAll();
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
	}
 	MinX=src.MinX;
	MinY=src.MinY;
	MaxX=src.MaxX;
	MaxY=src.MaxY;
	return(*this);
}

void	XYLines::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	Rx;
	int	Ry;
	XYClass *c=NPListPack<XYClass>::GetFirst();
	if(c!=NULL){
		Rx=(c->x+movx)*ZoomRate;
		Ry=(c->y+movy)*ZoomRate;
	
	    for(c=(XYClass *)c->GetNext();c!=NULL;c=(XYClass *)c->GetNext()){
			int	Qx=(c->x+movx)*ZoomRate;
			int	Qy=(c->y+movy)*ZoomRate;
			if(Qx!=Rx || Qy!=Ry){
				pnt.drawLine(Rx,Ry,Qx,Qy);
				Rx=Qx;
				Ry=Qy;
			}
		}
	}
}
	
void	XYLines::GetMinY(int &x ,int &y)	const
{
	x=0;
	y=99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(c->y<y){
			y=c->y;
			x=c->x;
		}
	}
}

void	XYLines::GetMaxY(int &x ,int &y)	const
{
	x=0;
	y=-99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(c->y>y){
			y=c->y;
			x=c->x;
		}
	}
}

double	XYLines::GetDistance(int x,int y)	const
{
	double	MinD=99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		double	D=hypot(c->x-x,c->y-y);
		if(MinD>D){
			MinD=D;
		}
	}
	return MinD;
}

void	XYLines::CreateOneLine(BYTE **BmpMap , int XLen ,int YLen
										,int x ,int y)
{
	SetBmpBit0(BmpMap,x,y);

	if(0<y){
		if(0<x && GetBmpBit(BmpMap,x-1,y-1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x-1 ,y-1);
		if(GetBmpBit(BmpMap,x,y-1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x ,y-1);
		if((x+1)<XLen && GetBmpBit(BmpMap,x+1,y-1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x+1 ,y-1);
	}
		
	if(0<x && GetBmpBit(BmpMap,x-1,y)!=0)
		CreateOneLine(BmpMap , XLen ,YLen ,x-1 ,y);
	if((x+1)<XLen && GetBmpBit(BmpMap,x+1,y)!=0)
		CreateOneLine(BmpMap , XLen ,YLen ,x+1 ,y);

	if((y+1)<YLen){
		if(0<x && GetBmpBit(BmpMap,x-1,y+1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x-1 ,y+1);
		if(GetBmpBit(BmpMap,x,y+1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x ,y+1);
		if((x+1)<XLen && GetBmpBit(BmpMap,x+1,y+1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x+1 ,y+1);
	}
}

bool	XYLines::CalcInterpolationLine(double &a ,double &b ,double &c)
{
	/*
		a=cos(s)
		b=sin(s)

		L=S(a*x+b*y+c)^2
		 =S(a*a*x^2 + b*b*y^2 + c*c + 2*a*b*x*y + 2*a*c*x +2*b*c*y 
		dL/da=2a*S(x^2) + 2b*S(x*y) + 2c*S(x)
		dL/db=2b*S(y^2) + 2a*S(x*y) + 2c*S(y)
		dL/dc=2cN + 2a*S(x) + 2b*S(y)

		c=-(aSx+bSy)/N
		aSx2+bSxy-(aSx+bSy)*Sx/N=0
		bSy2+aSxy-(aSx+bSy)*Sy/N=0

		a(Sx2-Sx*Sx/N)=b(Sx*Sy/N-Sxy)
		a=b(Sx*Sy/N-Sxy)/(Sx2-Sx*Sx/N)

		b*b*(Sx*Sy/N-Sxy)^2+b*b*(Sx2-Sx*Sx/N)^2=(Sx2-Sx*Sx/N)^2
	*/
	double	Sx=0;
	double	Sy=0;
	double	Sxy=0;
	double	Sx2=0;
	double	Sy2=0;
	int	N=0;
    for(XYClass *kc=NPListPack<XYClass>::GetFirst();kc!=NULL;kc=(XYClass *)kc->GetNext()){
		Sx +=kc->x;
		Sy +=kc->y;
		Sxy+=kc->x*kc->y;
		Sx2+=kc->x*kc->x;
		Sy2+=kc->y*kc->y;
		N++;
	}
	double	A=(Sx*Sy/N-Sxy);
	double	B=(Sx2-Sx*Sx/N);
	double	M=sqrt(A*A+B*B);
	if(M==0.0)
		return false;
	b=B/M;
	if(B==0)
		return false;
	a=b*A/B;
	c=-(a*Sx+b*Sy)/N;

	return true;
}

//=========================================================================================

bool    XYLineContainer::Save(QIODevice  *file)
{
    int32 N=NPListPack<XYLines>::GetNumber();
    if(file->write((const char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(XYLines *c=NPListPack<XYLines>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Write(file)==false){
            return(false);
		}
    }
    return(true);
}
bool    XYLineContainer::Load(QIODevice  *file)
{
    RemoveAll();
    int32 N;
    if(file->read((char *)&N,sizeof(N))!=sizeof(N))
        return(false);
    for(int i=0;i<N;i++){
        XYLines *c=new XYLines();
        AppendList(c);
    }
    return(true);

}

void	XYLineContainer::CreateLines(BYTE **BmpMap , int XByte ,int YLen)
{
	for(int y=0;y<YLen;y++){
		BYTE	*s=BmpMap[y];
		for(int xb=0;xb<XByte;xb++){
			if(s[xb]!=NULL){
				int	X=xb*8;
				for(int i=0;i<8;i++){
					if(GetBmpBitOnY(s,X+i)!=0){
						XYLines	*L=new XYLines();
						L->CreateOneLine(BmpMap , XByte*8 ,YLen
										,X+i,y);
					}
				}
			}
		}
	}
}
	
void	XYLineContainer::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
    for(XYLines *c=NPListPack<XYLines>::GetFirst();c!=NULL;c=c->GetNext()){
		c->DrawLines(pnt ,ZoomRate ,movx ,movy);
	}
}

void    XYLineContainer::Regulate(void)
{
    for(XYLines *c=NPListPack<XYLines>::GetFirst();c!=NULL;c=c->GetNext()){
		c->Regulate();
	}
}

 //=========================================================================================
