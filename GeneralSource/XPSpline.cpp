/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPSpline.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

/*
	リリース版で最適化をかけると動作が不安定になる
*/

/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#include "XTypeDef.h"
#include "XPSpline.h"
#include "swap.h"

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
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


XSplineBase::XSplineBase(void)
{
    Count=0;
    x=NULL;
    y=NULL;
    p=NULL;
    a=NULL;
    b=NULL;
}

XSplineBase::XSplineBase(XSplineBase &src)
{
    Count=0;
    x=NULL;
    y=NULL;
    p=NULL;
    a=NULL;
    b=NULL;
    operator=(src);
}
XSplineBase &XSplineBase::operator=(XSplineBase &src)
{
	if(&src!=this){
	    Initial();
		Count=src.Count;
	    x=new double[Count+1];
		y=new double[Count+1];
	    p=new double[Count+1];
		a=new double[Count+1];
	    b=new double[Count+1];

	    memcpy(x,src.x,sizeof(double)*Count);
		memcpy(y,src.y,sizeof(double)*Count);
	}
    return(*this);
}

XSplineBase::~XSplineBase(void)
{
    Initial();
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
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
void    XSplineBase::Initial(void)
{
	if(x!=NULL){
        delete  []x;
	}
	if(y!=NULL){
        delete  []y;
	}
	if(p!=NULL){
        delete  []p;
	}
	if(a!=NULL){
        delete  []a;
	}
	if(b!=NULL){
        delete  []b;
	}
    Count=0;
    x=NULL;
    y=NULL;
    p=NULL;
    a=NULL;
    b=NULL;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    count
//    X
//    Y
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
bool XSplineBase::SetPoints(int count ,double X[] ,double Y[])
{
    Initial();

    Count=count;
    x=new double[Count+1];
    y=new double[Count+1];
    p=new double[Count+1];
    a=new double[Count+1];
    b=new double[Count+1];

    memcpy(x,X,sizeof(double)*Count);
    memcpy(y,Y,sizeof(double)*Count);

    return(CalcSetPoints());
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    count
//    Dot
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
bool XSplineBase::SetPoints(int count ,QPoint Dot[])
{
	if(x!=NULL){
        delete  []x;
	}
	if(y!=NULL){
        delete  []y;
	}
	if(p!=NULL){
        delete  []p;
	}
	if(a!=NULL){
        delete  []a;
	}
	if(b!=NULL){
        delete  []b;
	}
    Count=count;
    x=new double[Count+1];
    y=new double[Count+1];
    p=new double[Count+1];
    a=new double[Count+1];
    b=new double[Count+1];

    for(int i=0;i<Count;i++){
        x[i]=Dot[i].x();
        y[i]=Dot[i].y();
        }

    return(CalcSetPoints());
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
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
bool XCloseSpline::CalcSetPoints(void)
{
	if(Count<2){
        return(false);
	}
	int i;
	double t1, t2;

    x[Count]=x[0];
    y[Count]=y[0];
	p[0] = 0;
	for (i = 1; i <= Count; i++) {
		t1 = x[i] - x[i - 1];
		t2 = y[i] - y[i - 1];
		p[i] = p[i - 1] + sqrt(t1 * t1 + t2 * t2);
	}
	for (i = 1; i <= Count; i++){
        p[i] /= p[Count];
	}
	if(maketable(x, a)==false){
        return(false);
	}
	if(maketable(y, b)==false){
        return(false);
	}
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
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
bool XOpenSpline::CalcSetPoints(void)
{
	if(Count<2){
        return(false);
	}
	int i;
	double t1, t2;

    x[Count]=x[Count-1];
    y[Count]=y[Count-1];
	p[0] = 0;
	for (i = 1; i <= Count; i++) {
		t1 = x[i] - x[i - 1];
		t2 = y[i] - y[i - 1];
		p[i] = p[i - 1] + sqrt(t1 * t1 + t2 * t2);
	}
	for (i = 1; i <= Count; i++){
        p[i] /= p[Count];
	}
	if(maketable(x, a)==false){
        return(false);
	}
	if(maketable(y, b)==false){
        return(false);
	}
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    t
//    px
//    py
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
void XSplineBase::CalcSpline(double t ,double &px, double &py)
{
	px = spline1(t, x, a);
	py = spline1(t, y, b);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    t
//    onPx
//    onPy
//    Vx
//    Vy
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
void XSplineBase::CalcSplineV(double t ,double &onPx,double &onPy
                                     ,double &Vx  ,double &Vy)   //0<=t<=1.0
{
    CalcSpline(t ,onPx,onPy);
    double  kx1,ky1,kx2,ky2;
    double  tL=t-0.00001;
	if(tL<0){
        tL+=1.0;
	}
    CalcSpline(tL ,kx1,ky1);
    double  tH=t+0.00001;
	if(tH>=1.0){
        tH-=1.0;
	}
    CalcSpline(tH ,kx2,ky2);

    double  hx=kx2-kx1;
    double  hy=ky2-ky1;
    Vx= hy;
    Vy=-hx;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    m
//    z
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
bool XCloseSpline::maketable(double m[], double z[])
{

	int i;
	double t;

	if(Count<2){
        return(false);
	}

    //double h[N + 1], d[N + 1], w[N + 1];
    double  *h=new double[Count+1];
    double  *d=new double[Count+1];
    double  *w=new double[Count+1];

	for (i = 0; i <Count ; i++) {
		h[i] = p[i + 1] - p[i];
        if(fabs(h[i])>MinSplineData){
    		w[i] = (m[i + 1] - m[i]) / h[i];
            }
		else{
            w[i] =0.0;
		}
    }
	w[Count] = w[0];
	for (i = 1; i <Count; i++){
        d[i] = 2 * (p[i + 1] - p[i - 1]);
        }
	d[Count] = 2 * (h[Count - 1] + h[0]);
	for (i = 1; i <= Count; i++){
        z[i] = w[i] - w[i - 1];
	}
	w[1] = h[0];
    w[Count - 1] = h[Count - 1];
    w[Count] = d[Count];
	for (i = 2; i < Count - 1; i++){
        w[i] = 0;
        }
	for (i = 1; i < Count; i++) {
		if(d[i]>MinSplineData){
    		t = h[i] / d[i];
		}
		else{
            t=0.0;
		}
		z[i + 1] = z[i + 1] - z[i] * t;
		d[i + 1] = d[i + 1] - h[i] * t;
		w[i + 1] = w[i + 1] - w[i] * t;
	    }
	w[0] = w[Count];
    z[0] = z[Count];
	for (i = Count - 2; i >= 0; i--) {
		if(d[i+1]>MinSplineData){
    		t = h[i] / d[i + 1];
		}
		else{
            t=0.0;
		}
		z[i] = z[i] - z[i + 1] * t;
		w[i] = w[i] - w[i + 1] * t;
	    }
	t = z[0] / w[0];
    z[0] = t;
    z[Count] = t;
	for (i = 1; i < Count; i++){
		if(d[i+1]>MinSplineData){
    		z[i] = (z[i] - w[i] * t) / d[i];
		}
		else{
            z[i] =0.0;
        }
	}

    delete []h;
    delete []d;
    delete []w;

    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    m
//    z
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
bool XOpenSpline::maketable(double m[], double z[])
{

	int i;
	double t;

	if(Count<2){
        return(false);
	}
    double  *h=new double[Count+1];
    double  *d=new double[Count+1];

	z[0] = 0;
    z[Count - 1] = 0;  /* 両端点での y''(x) / 6 */
    for (i = 0; i < Count - 1; i++) {
		h[i    ] =  p[i + 1] - p[i];
		if(fabs(h[i])>MinSplineData){
    		d[i + 1] = (m[i + 1] - m[i]) / h[i];
		}
		else{
            d[i + 1] =0.0;
    	}
	}
	z[1] = d[2] - d[1];
	d[1] = 2 * (p[2] - p[0]);
	for (i = 1; i < Count - 2; i++) {
		if(fabs(h[i])>MinSplineData){
    		t = h[i] / d[i];
		}
		else{
            t=0.0;
		}
		z[i + 1] = d[i + 2] - d[i + 1] - z[i] * t;
		d[i + 1] = 2 * (p[i + 2] - p[i]) - h[i] * t;
   	}

	z[Count - 2] -= h[Count - 2] * z[Count - 1];
	for (i = Count - 2; i > 0; i--){
		if(fabs(h[i])>MinSplineData){
    		z[i] = (z[i] - h[i] * z[i + 1]) / d[i];
		}
		else{
            z[i]=0.0;
        }
	}

    delete []h;
    delete []d;

    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    t
//    m
//    z
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
double XSplineBase::spline1(double t, double m[], double z[])
{
	int i, j, k;
	double d, h, period;

	if(Count<=2){
		return(0);
	}

	period = p[Count] - p[0];
	while (t > p[Count]){
        t -= period;
	}
	while (t < p[0]){
        t += period;
	}
	i = 0;
    j = Count;
	while (i < j) {
		k = (i + j) / 2;
		if (p[k] < t){
            i = k + 1;
		}
		else{
			j = k;
		}
	}
	if (i > 0){
        i--;
	}
	h = p[i + 1] - p[i];
	d = t - p[i];
	return (((z[i + 1] - z[i]) * d / h + z[i] * 3) * d
		+ ((m[i + 1] - m[i]) / h
		- (z[i] * 2 + z[i + 1]) * h)) * d + m[i];
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    OutX
//    OutY
//    px
//    py
//    t
//    mint
//    maxt
//    kt
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
double XSplineBase::FindNearPointInner(int OutX,int OutY
                                  ,double &px, double &py
                                  ,double t ,double mint ,double maxt
                                  ,double &kt)
{
    double  ld=(t-mint)/2.0;
    double  hd=(maxt-t)/2.0;
    double  L1,L2,L3;
    double  px1,py1;
    double  px2,py2;
    double  px3,py3;

    for(int i=0;i<10;i++){
        CalcSpline(t-ld ,px1, py1);
        CalcSpline(t    ,px2, py2);
        CalcSpline(t+hd ,px3, py3);

        L1=(px1-OutX)*(px1-OutX) + (py1-OutY)*(py1-OutY);
        L2=(px2-OutX)*(px2-OutX) + (py2-OutY)*(py2-OutY);
        L3=(px3-OutX)*(px3-OutX) + (py3-OutY)*(py3-OutY);

        if(L1<=L2 && L1<=L3){
            t=t-ld;
            ld=(t-mint)/2.0;
            hd=ld;
			if(t+hd>maxt){
                hd=maxt;
            }
		}
        else if(L1>=L2 && L2<=L3){
            ld=ld/2.0;
            hd=hd/2.0;
            }
        else if(L1>=L3 && L2>=L3){
            t=t+hd;
            hd=(maxt-t)/2.0;
            ld=hd;
			if(t-ld<mint){
                ld=mint;
            }
        }
	}
    kt=t;
    if(L1<=L2 && L1<=L3){
        px=px1;
        py=py1;
        return(L1);
        }
    else if(L1>=L2 && L2<=L3){
        px=px2;
        py=py2;
        return(L2);
        }
    else if(L1>=L3 && L2>=L3){
        px=px3;
        py=py3;
        return(L3);
        }
    return(0.0);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    OutX
//    OutY
//    px
//    py
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
double XSplineBase::FindNearPoint(int OutX,int OutY
                                  ,double &px, double &py)
{
    double  MinD=99999999;
    double  kx;
    double  ky;
    double  k;
    double  MinK=0;

    for(int i=1;i<Count-1;i+=2){
        double L=FindNearPointInner(OutX,OutY
                                  ,kx, ky
                                  ,p[i] ,p[i-1],p[i+1]
                                  ,k);
        if(L<MinD){
            px=kx;
            py=ky;
            MinD=L;
            MinK=k;
            }
        }

    double L=FindNearPointInner(OutX,OutY
                                  ,kx, ky
                                  ,p[Count-1] ,p[Count-2],p[0]
                                  ,k);
    if(L<MinD){
        px=kx;
        py=ky;
        MinD=L;
        MinK=k;
        }
    return(MinK);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    px
//    py
//    ma
//    mb
//    mc
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
void XSplineBase::PalLine(double px, double py
                                     ,double &ma,double &mb,double &mc)
{
    double qx;
    double qy;

    FindNearPoint(px, py ,qx, qy);

    ma=py-qy;
    mb=-(px-qx);
    mc=-px*ma-py*mb;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Y
//    startt
//    mint
//    maxt
//    rett
//    x
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
bool   XSplineBase::FindYPointInner(double Y ,double startt ,double mint ,double maxt
                                                ,double &rett ,double &x)
{
    double  dt1=startt-mint;
    double  dt2=maxt-startt;
	if(dt2<0){
        dt2+=1.0;
	}
    double  dt=(dt1<dt2)?dt1:dt2;
    dt/=2.0;
    double  kx1,ky1;
    double  kx2,ky2;
    double  kx3,ky3;

    for(int i=0;i<10;i++){
        if(mint<maxt){
			if(startt<mint || maxt<startt){
                return(false);
			}
        }
        else{
			if(startt<mint || maxt>startt){
                return(false);
            }
		}
        CalcSpline(startt ,kx1,ky1);
        double  kt1=startt;
        double  kt2=startt-dt;
		if(kt2<0){
            kt2+=1.0;
		}
        CalcSpline(kt2 ,kx2,ky2);
        double  kt3=startt+dt;
		if(kt3>1.0){
            kt3-=1.0;
		}
        CalcSpline(kt3 ,kx3,ky3);

        if(fabs(ky1-Y)<0.001){
            rett=startt;
            x=kx1;
            return(true);
            }
        if(Y<=ky1 && Y<=ky2 && Y<=ky3){
			if(ky1<=ky2 && ky1<=ky3){
                dt/=2.0;
			}
			else if(ky2<=ky1 && ky2<=ky3){
                startt=kt2;
			}
			else{
                startt=kt3;
            }
		}
        else if(Y>=ky1 && Y>=ky2 && Y>=ky3){
			if(ky1>=ky2 && ky1>=ky3){
                dt/=2.0;
			}
			else if(ky2>=ky1 && ky2>=ky3){
                startt=kt2;
			}
			else{
                startt=kt3;
            }
		}
        else{
            bool    Flag;
            do{
                Flag=false;
                if(ky2>=ky1){
                    swap(ky2,ky1);
                    swap(kt2,kt1);
                    Flag=true;
                    }
                if(ky1>=ky3){
                    swap(ky3,ky1);
                    swap(kt3,kt1);
                    Flag=true;
                    }
                }while(Flag==true);


            if(ky2<=Y && Y<=ky1 && ky1<=ky3){
                startt=(kt1+kt2)/2.0;
                dt/=2.0;
				if(startt<0){
                    startt+=1.0;
				}
				else if(startt>1.0){
                    startt-=1.0;
                }
			}
            else if(ky2<=ky1 && ky1<=Y && Y<=ky3){
                startt=(kt1+kt3)/2.0;
                dt/=2.0;
				if(startt<0){
                    startt+=1.0;
				}
				else if(startt>1.0){
                    startt-=1.0;
                }
            }
        }
	}
    return(false);
}

bool    XSplineBase::FindXPointInner(double X ,double startt ,double mint ,double maxt
                                                ,double &rett ,double &y)
{
    double  dt1=startt-mint;
    double  dt2=maxt-startt;
	if(dt2<0){
        dt2+=1.0;
	}
    double  dt=(dt1<dt2)?dt1:dt2;
    dt/=2.0;
    double  kx1,ky1;
    double  kx2,ky2;
    double  kx3,ky3;

    for(int i=0;i<10;i++){
        if(mint<maxt){
			if(startt<mint || maxt<startt){
                return(false);
			}
        }
        else{
			if(startt<mint || maxt>startt){
                return(false);
            }
		}
        CalcSpline(startt ,kx1,ky1);
        double  kt1=startt;
        double  kt2=startt-dt;
		if(kt2<0){
            kt2+=1.0;
		}
        CalcSpline(kt2 ,kx2,ky2);
        double  kt3=startt+dt;
		if(kt3>1.0){
            kt3-=1.0;
		}
        CalcSpline(kt3 ,kx3,ky3);

        if(fabs(kx1-X)<0.001){
            rett=startt;
            y=ky1;
            return(true);
            }
        if(X<=kx1 && X<=kx2 && X<=kx3){
			if(kx1<=kx2 && kx1<=kx3){
                dt/=2.0;
			}
			else if(kx2<=kx1 && kx2<=kx3){
                startt=kt2;
			}
			else{
                startt=kt3;
            }
		}
        else if(X>=kx1 && X>=kx2 && X>=kx3){
			if(kx1>=kx2 && kx1>=kx3){
                dt/=2.0;
			}
			else if(kx2>=kx1 && kx2>=kx3){
                startt=kt2;
			}
			else{
                startt=kt3;
            }
		}
        else{
            bool    Flag;
            do{
                Flag=false;
                if(kx2>=kx1){
                    swap(kx2,kx1);
                    swap(kt2,kt1);
                    Flag=true;
                    }
                if(kx1>=kx3){
                    swap(kx3,kx1);
                    swap(kt3,kt1);
                    Flag=true;
                    }
                }while(Flag==true);


            if(kx2<=X && X<=kx1 && kx1<=kx3){
                startt=(kt1+kt2)/2.0;
                dt/=2.0;
				if(startt<0){
                    startt+=1.0;
				}
				else if(startt>1.0){
                    startt-=1.0;
                }
			}
            else if(kx2<=kx1 && kx1<=X && X<=kx3){
                startt=(kt1+kt3)/2.0;
                dt/=2.0;
				if(startt<0){
                    startt+=1.0;
				}
				else if(startt>1.0){
                    startt-=1.0;
                }
            }
        }
	}
    return(false);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Y
//    tdim
//    xdim
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
int  XSplineBase::GetCrossYList(double Y ,double tdim[] ,double xdim[])
{
    int Numb=0;
    double  t;
    double  x;
    for(int i=1;i<Count-1;i++){
        if((y[i-1]<=Y && Y<=y[i+1])
        || (y[i+1]<=Y && Y<=y[i-1])){
            if(FindYPointInner(Y ,p[i] ,p[i-1],p[i+1] ,t,x)==true){
                tdim[Numb]=t;
                xdim[Numb]=x;
                Numb++;
                }
            }
        }
    if((y[Count-2]<=Y && Y<=y[0])
    || (y[0]<=Y && Y<=y[Count-2])){
        if(FindYPointInner(Y ,p[Count-1] ,p[Count-2],p[0] ,t,x)==true){
            tdim[Numb]=t;
            xdim[Numb]=x;
            Numb++;
            }
        }

    for(int i=1;i<Count-1;i++){
        if((y[i-1]<=y[i] && y[i]>=y[i+1] && Y-y[i]>=0 && Y-y[i]<=2)
        || (y[i-1]>=y[i] && y[i]<=y[i+1] && y[i]-Y>=0 && y[i]-Y<=2)){
            if(FindYPointInner(Y ,p[i] ,p[i-1],p[i+1] ,t,x)==true){
                tdim[Numb]=t;
                xdim[Numb]=x;
                Numb++;
                }
            }
        }
    if((y[Count-2]<=y[Count-1] && y[Count-1]>=y[0] && Y-y[Count-1]>=0 && Y-y[Count-1]<=2)
    || (y[Count-2]>=y[Count-1] && y[Count-1]<=y[0] && y[Count-1]-Y>=0 && y[Count-1]-Y<=2)){
        if(FindYPointInner(Y ,p[Count-1] ,p[Count-2],p[0] ,t,x)==true){
            tdim[Numb]=t;
            xdim[Numb]=x;
            Numb++;
            }
        }
    return(Numb);
}


int  XSplineBase::GetCrossXList(double X ,double tdim[] ,double ydim[])
{
    int Numb=0;
    double  t;
    double  y;
    for(int i=1;i<Count-1;i++){
        if((x[i-1]<=X && X<=x[i+1])
        || (x[i+1]<=X && X<=x[i-1])){
            if(FindXPointInner(X ,p[i] ,p[i-1],p[i+1] ,t,y)==true){
                tdim[Numb]=t;
                ydim[Numb]=y;
                Numb++;
                }
            }
        }
    if((x[Count-2]<=X && X<=x[0])
    || (x[0]<=X && X<=x[Count-2])){
        if(FindXPointInner(X ,p[Count-1] ,p[Count-2],p[0] ,t,y)==true){
            tdim[Numb]=t;
            ydim[Numb]=y;
            Numb++;
            }
        }

    for(int i=1;i<Count-1;i++){
        if((x[i-1]<=x[i] && x[i]>=x[i+1] && X-x[i]>=0 && X-x[i]<=2)
        || (x[i-1]>=x[i] && x[i]<=x[i+1] && x[i]-X>=0 && x[i]-X<=2)){
            if(FindXPointInner(X ,p[i] ,p[i-1],p[i+1] ,t,y)==true){
                tdim[Numb]=t;
                ydim[Numb]=y;
                Numb++;
                }
            }
        }
    if((x[Count-2]<=x[Count-1] && x[Count-1]>=x[0] && X-x[Count-1]>=0 && X-x[Count-1]<=2)
    || (x[Count-2]>=x[Count-1] && x[Count-1]<=x[0] && x[Count-1]-X>=0 && x[Count-1]-X<=2)){
        if(FindXPointInner(X ,p[Count-1] ,p[Count-2],p[0] ,t,y)==true){
            tdim[Numb]=t;
            ydim[Numb]=y;
            Numb++;
            }
        }
    return(Numb);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    t
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
bool XSplineBase::IsTopY(double t)
   //Y方向の極点か否かを調べる
{
    double  onPx,onPy;

    CalcSpline(t ,onPx,onPy);
    double  kx1,ky1,kx2,ky2;
    double  tL=t-0.00001;
	if(tL<0){
        tL+=1.0;
	}
    CalcSpline(tL ,kx1,ky1);
    double  tH=t+0.00001;
	if(tH>=1.0){
        tH-=1.0;
	}
    CalcSpline(tH ,kx2,ky2);

	if(onPy>=ky1 && onPy>=ky2){
        return(true);
	}
	if(onPy<=ky1 && onPy<=ky2){
        return(true);
	}
    return(false);
}



