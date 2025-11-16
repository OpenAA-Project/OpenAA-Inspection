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

#include "XYCross.h"
#include "XFlexArea.h"
#include "XCrossObj.h"
#include<math.h>
#include "swap.h"
#include "XGeneralFunc.h"
#include "XPointer.h"

static	bool LinesRound(NPListPack<XYClass> &D ,XYClass  &P);

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
bool	XYClassContainer::operator==(XYClassContainer &src)
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
void    XYClassContainer::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;

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
    }
}

void    XYClassContainer::GetCenter(int &cx ,int &cy)
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    GetXY(minx ,miny ,maxx ,maxy);

    cx=(minx+maxx)/2;
    cy=(miny+maxy)/2;
}
bool	XYClassContainer::IsIsclude(int x ,int y)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(c->x==x && c->y==y){
			return true;
		}
	}
	return false;
}
bool	XYClassContainer::IsIsclude(int x ,int y ,int radius)
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

XYClassContainer &XYClassContainer::operator=(XYClassContainer &src)
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
	}
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


//============================================================================

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
void    XYDoubleClassContainer::GetXY(double &minx ,double &miny ,double &maxx ,double &maxy)
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;

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
    }
}

void    XYDoubleClassContainer::GetCenter(double &cx ,double &cy)
{
    double minx;
    double miny;
    double maxx;
    double maxy;
    GetXY(minx ,miny ,maxx ,maxy);

    cx=(minx+maxx)/2;
    cy=(miny+maxy)/2;
}
bool	XYDoubleClassContainer::IsIsclude(int x ,int y)
{
    for(XYDoubleClass *c=NPListPack<XYDoubleClass>::GetFirst();c!=NULL;c=(XYDoubleClass *)c->GetNext()){
		if(c->x==x && c->y==y){
			return true;
		}
	}
	return false;
}

XYDoubleClassContainer &XYDoubleClassContainer::operator=(XYDoubleClassContainer &src)
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
	}
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
    for(register XYClass *c1=NPListPack<XYClass>::GetFirst();c1!=NULL;c1=c1->GetNext()){
        register XYClass *c2=c1->GetNext();
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
    register struct  XYM_Data    *d=new struct XYM_Data[NPListPack<XYClass>::GetNumber()];

    int n=0;
    int LastX=-1,LastY=-1;
    for(register XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        if(LastY!=c->y || abs(LastX-c->x)>1){
            d[n].x1=c->x;
            d[n].x2=c->x;
            d[n].y =c->y;
            n++;
            }
        else{
            d[n-1].x2=c->x;
            }
        LastX=c->x;
        LastY=c->y;
        }
    for(register int i=0;i<n;i++){
		if(d[i].x1>d[i].x2){
            swap(d[i].x1,d[i].x2);
		}
	}
    if(NPListPack<XYClass>::GetFirst()!=NULL && NPListPack<XYClass>::GetLast()!=NULL){
        if(NPListPack<XYClass>::GetFirst()->y==d[n-1].y
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

    for(register int i=0;i<n;i++){
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

    for(register int i=1;i<n;i++){
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
    for(register int i=1;i<n;i++){
        if(d[i-1].y==d[i].y && d[i-1].x2==d[i].x1-1){
            d[i-1].x2=d[i].x2;
            memmove(&d[i],&d[i+1],(n-i)*sizeof(d[0]));
            n--;
            }
        }
    */
    for(register int i=1;i<n-1;i++){
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
    for(register int i=0;i<n;i++){
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
bool    XYClassArea::IsInclude(int x ,int y)
{
    XYClass key(x,y);

    return(LinesRound(*this ,key));
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
bool    XYClassArea::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)
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
	if(LinesRound(*this ,P)==true){
        return(true);
	}

    return(false);
}


bool    XYClassArea::IsValid(void)
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
bool    XYClassCluster::IsInclude(int x ,int y)
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
bool    XYClassCluster::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)
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
bool    XYClassCluster::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)
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

bool    XYClassArea::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)
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
	if(LinesRound(*this ,P)==true){
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

void    XYClassArea::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;

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
    }
}

XYClassArea &XYClassArea::operator=(XYClassArea &src)
{
    int LastX=-99999999;
    int LastY=-99999999;
    bool    SameX=false;
    bool    SameY=false;

    NPListPack<XYClass>::RemoveAll();
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
        }
	/*
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        if((XYClass *)c->GetNext()!=NULL){
            if(c->x==LastX && SameX==true){
                LastY=c->y;
                continue;
                }
            if(c->y==LastY && SameY==true){
                LastX=c->x;
                continue;
                }
            if(c->x==LastX && c->y==LastY)
                continue;
            }

        if((c->x!=LastX && SameX==true)
        || (c->y!=LastY && SameY==true)){
            XYClass *d=new XYClass();
            d->x=LastX;
            d->y=LastY;
            NPListPack<XYClass>::AppendList(d);
            }

        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
        if(LastX==c->x)
            SameX=true;
        else
            SameX=false;

        if(LastY==c->y)
            SameY=true;
        else
            SameY=false;

        LastX=c->x;
        LastY=c->y;
        }
	*/
    return(*this);
}

void    XYClassArea::GetCenter(int &cx ,int &cy)
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    GetXY(minx ,miny ,maxx ,maxy);

    cx=(minx+maxx)/2;
    cy=(miny+maxy)/2;
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
	}
    for(c=(XYClass *)c->GetNext();c!=NULL;c=(XYClass *)c->GetNext()){
		int	Qx=(c->x+movx)*ZoomRate;
		int	Qy=(c->y+movy)*ZoomRate;
		if(Qx!=Rx || Qy!=Ry){
			pnt.drawLine(Rx,Ry,Qx,Qy);
			Rx=Qx;
			Ry=Qy;
		}
	}
	c=NPListPack<XYClass>::GetFirst();
	int	Qx=(c->x+movx)*ZoomRate;
	int	Qy=(c->y+movy)*ZoomRate;
	if(Qx!=Rx || Qy!=Ry){
		pnt.drawLine(Rx,Ry,Qx,Qy);
		Rx=Qx;
		Ry=Qy;
	}
}


void    XYClassCluster::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)
{
    int nminx,nminy;
    int nmaxx,nmaxy;
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;

    for(XYClassArea *a=GetFirst();a!=NULL;a=a->GetNext()){
        a->GetXY(nminx,nminy,nmaxx,nmaxy);
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
    }
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


XYClassCluster &XYClassCluster::operator=(XYClassCluster &src)
{
    RemoveAll();
    for(XYClassArea *a=src.GetFirst();a!=NULL;a=a->GetNext()){
        XYClassArea *b=new XYClassArea();
        *b=*a;
        AppendList(b);
        }
    return(*this);
}

RectClass::RectClass(RectClass &src)
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


static	bool LinesRound(NPListPack<XYClass> &D ,XYClass  &P)
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
	if(N>=sizeof(Y)/sizeof(Y[0])){
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

bool    XYLines::IsInclude(int x ,int y ,double AreaLength)
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
bool    XYLines::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)
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
bool    XYLines::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)
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

void    XYLines::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;

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
    }
}
void    XYLines::GetCenter(int &cx ,int &cy)
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    GetXY(minx ,miny ,maxx ,maxy);

    cx=(minx+maxx)/2;
    cy=(miny+maxy)/2;
}
void    XYLines::ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        c->ChangeXY(outlineOffset ,MaxPage,maxlines);
        }
}
bool    XYLines::IsValid(void)
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

XYLines &XYLines::operator=(XYLines &src)
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
	}
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
	
void	XYLines::GetMinY(int &x ,int &y)
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

void	XYLines::GetMaxY(int &x ,int &y)
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

double	XYLines::GetDistance(int x,int y)
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