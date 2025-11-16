/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAffin.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------
#include "XTypeDef.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAffin.h"
#include "swap.h"

//---------------------------------------------------------------------------

bool Gaujor(double a[], int l, int m, int n, double eps);
/* 連立１次方程式(高精度版）*/
bool    Leqacc( double a[] , double x[] ,double b[] , int n);


bool    GetAffin(int x1,int y1
                ,int x2,int y2          //マスター画像上のアライメント基準位置
                ,double cx, double cy   //回転中心
                ,int X1 ,int Y1
                ,int X2 ,int Y2     //探索した結果のアラインメント位置
                ,double &ResultPx,double &ResultPy  //平行移動量
                ,double &ResultS                    //回転量（ラジアン）
                ,double &ResultAlpha)               //拡大率
{
    double  mx1=x1-cx;
    double  my1=y1-cy;
    double  mx2=x2-cx;
    double  my2=y2-cy;
    double  Mx1=X1-cx;
    double  My1=Y1-cy;
    double  Mx2=X2-cx;
    double  My2=Y2-cy;

    double  A=(mx1-mx2)*(Mx2-Mx1)-(My2-My1)*(my2-my1);
    double  B=(My2-My1)*(mx2-mx1)-(Mx2-Mx1)*(my2-my1);

    double  C=sqrt(A*A+B*B);
	if(C<0.00000001){
        return(false);
	}
    double	c;
	double	s;

    c=A/C;
    s=B/C;
    double  mm=c*mx2+s*my2-c*mx1-s*my1;
	if(fabs(mm)<0.0000001){
        return(false);
	}
    ResultAlpha=(Mx2-Mx1)/mm;
    if(ResultAlpha<0){
        c= -A/C;
        s= -B/C;
        mm=c*mx2+s*my2-c*mx1-s*my1;
		if(fabs(mm)<0.0000001){
            return(false);
		}
        ResultAlpha=(Mx2-Mx1)/mm;
        }
	if((c>=0.0) && (s<=c) && (s>=-c)){
        ResultS=asin(s);
	}
    else if((s>=0.0) && (s>=-c) && (s>=c)){
        ResultS=acos(c);
		}
    else if((c<=0.0) && (s<=-c) && (s>=c)){
        ResultS=asin(s);
		}
	else{
        ResultS=acos(c)+M_PI;
	}

    ResultPx=Mx1*c-ResultAlpha*mx1-s*My1;
    ResultPy=My1*c-ResultAlpha*my1+s*Mx1;
    return(true);
}


bool	GetAffinDecompose(double m[6] 
						,double &A ,double &B, double &Tx ,double &Ty ,double &S ,double &R)
{
/*
	X	 |A 0 0||CosR -SinR 0||1 0 Tx||1 0 0| |m[0] m[1] m[2]| x
	Y	=|0 B 0||SinR  CosR 0||0 1 Ty||S 1 0|=|m[3] m[4] m[5]| y
	1	 |0 0 1||  0    0   1||0 0 1 ||0 0 1| |0    0    1   | 1

	      ACosR -ASinR ACosRTx-ASinRTy
		  BSinR BCosR  BSinRTx+BCosRTy
		  0     0      1

		  ACosR-ASSinR -ASinR ACosRTx-ASinRTy
		  BSinR+BSCosR  BCosR BSinRTx+BCosRTy
		  0             0     1

		  m[1]=-ASinR	(m[1]/A)(m[1]/A)+(m[4]/B)(m[4]/B)=1		A=-m[1]/SinR
		  m[4]= BCosR
		  m[0]=ACosR+Sm[1]
		  m[3]=BSinR+Sm[4]

		  m[0]-Sm[1]=ACosR	=-m[1]/TanR
		  m[3]-Sm[4]=BSinR	=m[4]TanR

		  Sm[1]=m[0]+m[1]/TanR
		  Sm[4]=m[3]-m[4]TanR

		  m[0]/m[1]+1/TanR=m[3]/m[4]-TanR

		  TanR*TanR+(m[0]/m[1]-m[3]/m[4])TanR+1=0
		  m[1]m[4]*TanR*TanR+(m[0]m[4]-m[3]m[1])TanR+m[1]m[4]=0
			->TanR
			
			h1=ACosR
			h2=ASinR
			h3=BSinR
			h4=BCosR
		  h1Tx-h2Ty=m[2]
		  h3Tx+h4Ty=m[5]

		  (h1h4+h2h3)Tx=m[2]h4+m[5]h2
		  (h1h4+h2h3)Ty=m[5]h1-m[2]h3
*/
	double	V=m[1]*m[4];
	double	W=(m[0]*m[4]-m[3]*m[1]);
	double	H=m[1]*m[4];

	double	kb=W*W-4*V*H;
	if(kb<0)
		return false;
	kb=sqrt(kb);
	if(V==0)
		return false;
	double	TanR1=(-W+kb)/(2*V);
	double	TanR2=(-W-kb)/(2*V);
	double	TanR=(fabs(TanR1)<fabs(TanR2))?TanR1:TanR2;
	R=atan(TanR);
	double	CosR=cos(R);
	double	SinR=sin(R);
	B=m[4]/CosR;
	S=(m[3]-m[4]*TanR)/m[4];
	A=(m[0]-S*m[1])/CosR;

	double	h1=A*CosR;
	double	h2=A*SinR;
	double	h3=B*SinR;
	double	h4=B*CosR;

	double	G=(h1*h4+h2*h3);
	if(G==0)
		return false;
	Tx=(m[2]*h4+m[5]*h2)/G;
	Ty=(m[5]*h1-m[2]*h3)/G;

	return true;
}



bool Gaujor(double a[], int l, int m, int n, double eps)
{
	int c, i, iw, j, k, kp1, mm1, r, s, t, u, v, x;
    int work[sizeof(int)*20];
	double api, pivot, w, wmax;

	if((l < n) || (m < 2) || (m >= n) || (eps <= 0.0)){
		return(false);
    	}

	for(i = 0; i < m; i++){
        work[i] = i;
	}
	for(k = 0; k < m; k++){
		x = k * l;
		wmax = 0.;
		for(i = 0; i < m; i++){
			s = i * l;
			for(j = k; j < m; j++){
				w = fabs(a[s + j]);
				if(w > wmax){
					wmax = w;
					r = i;
					c = j;
    				}
	    		}
		    }
		s = r * l;
		pivot = a[s + c];
		api = fabs(pivot);
		if(api < eps){
			return(false);
    		}
		if(c != k){
			iw = work[k];
			work[k] = work[c];
			work[c] = iw;
			for(i = 0; i < m; i++){
				t = i * l;
				u = t + k;
				v = t + c;
				w = a[u];
				a[u] = a[v];
				a[v] = w;
    			}
	    	}
		if(r != k){
			for(j = k; j < n; j++){
				t = s + j;
				u = x + j;
				w = a[t];
				a[t] = a[u];
				a[u] = w;
    			}
	    	}
		kp1 = k + 1;
		for(i = kp1; i < n; i++)
            a[x + i] /= pivot;
		for(i = 0; i < m; i++){
			t = i * l;
			if(i != k){
				w = a[t + k];
				for(j = kp1; j < n; j++){
                    a[t + j] -= w * a[x + j];
					}
    			}
	    	}
    	}
	mm1 = m - 1;
	for(i = 0; i < mm1; i++){
		for(;;){
			k = work[i];
			if(k == i)	break;
			iw = work[k];
			work[k] = work[i];
			work[i] = iw;
			s = k * l;
			t = i * l;
			for(j = m; j < n; j++){
				u = s + j;
				v = t + j;
				w = a[u];
				a[u] = a[v];
				a[v] = w;
    			}
	    	}
    	}
	return(true);
}


void cpm( double a[] , double b[] , int n , int nn );
void predec( double a[] , double aa[] , double b[] , int n , int nn , int jun[] );
void solacc( double a[] , double x[] , double b[] , int n , int nn );
void racc( double a[] , double x[] , double b[] , double r[] , int n , int nn );
void decacc(double a[] ,int n, int nn);


/* 連立１次方程式(高精度版）*/
bool    Leqacc( double a[] , double x[] ,double b[] , int n)
{
    int nn=n;
    int     i,j,k;
    double  p,q,r,d,rmax,dmax ;
    double  *ai,*aj,*aij ;
    int  jun[8];
    double  aa[8*8*8],sf[8],rr[8],dx[8];


   /* 前処理(行) */
   for ( i=0 , ai=a ; i<n ; ++i , ai+=nn )
   {
      p=0.0;
      for ( j=0 ; j<n ; ++j )
      {
		  if ( (q=fabs(ai[j]))>p ){
            p=q;
		  }
      }
	  for ( j=0 ; j<n ; ++j ){
         ai[j]/=p;
	  }
      b[i]/=p;
   }
   /* 前処理(列) */
   for ( j=0 , aj=a ; j<n ; ++j , ++aj )
   {
      p=0.0;
      for ( i=0 , aij=aj ; i<n ; ++i , aij+=nn )
      {
		  if ( (q=fabs(*aij))>p ){
            p=q;
		  }
      }
	  for ( i=0 , aij=aj ; i<n ; ++i , aij+=nn ){
         (*aij)/=p;
	  }
      sf[j]=p;
   }
   /* Ａを待避 */
   cpm( a , aa , n , nn );
   /* 予備的ＬＵ分解 */
   predec( a , aa , b , n , nn , jun );
   //printf( "L[n-1][n-1]=%15.8e\n",*(a+(n-1)*nn+n-1));

   /* Ａを復元 */
   cpm( aa , a , n , nn );
   /* 精密ＬＵ分解 */
   decacc( a , n , nn );
   /* ひとまず解く */
   solacc( a , x , b , n , nn );
   /* 反復改良 */
   for ( k=0 ; k<3 ; ++k )
   {
      /* 残差計算 */
      racc( aa , x , b , rr , n , nn );
      /* 補正量算定 */
      solacc( a , dx , rr , n , nn );
      /* 補正 */
      for ( i=0 ; i<n ; ++i )
         x[i]+=dx[i];
      /* 中間出力 */
      rmax=0.0; dmax=0.0;
      for ( i=0 ; i<n ; ++i )
      {
		  if ( (r=fabs(rr[i]))>rmax ){	rmax=r;	}
		  if ( (d=fabs(dx[i]))>dmax ){ dmax=d;	}
      }
      /*
      printf ( "rmax=%15.8e dmax=%15.8e\n" ,
               rmax , dmax );
      */
   }
   /* 順序復元 */
   for ( k=n-2 ; k>=0 ; --k )
   {
      swap(x[k],x[jun[k]]);
   }

   /* スケーリングの復元 */
   for ( k=0 ; k<n ; ++k ){
      x[k]/=sf[k];
   }
   return(true);
}

/* 行列の複写 */
void cpm( double a[] , double b[] , int n , int nn )
{
   int     i,j ;
   double  *ai,*bi ;
   for ( i=0 , ai=a , bi=b ; i<n ;
	   ++i , ai+=nn , bi+=nn ){
		 for ( j=0 ; j<n ; ++j ){
         bi[j]=ai[j];
		 }
   }
}

/* 予備的ＬＵ分解 */
void predec( double a[] , double aa[] , double b[] , int n , int nn , int jun[] )
{
   int     i,j,k,k1,imax,jmax ;
   double  p,q;
   double  *ai,*ak,*aik,*aij ;
   double  *aai,*aak,*aaik,*aaij ;

   /* 前進消去 */
   for ( k=0 , ak=a , aak=aa ; k<n-1 ;
         ++k , ak+=nn , aak+=nn )
   {
      k1=k+1 ;
      /* ピボット選択 */
      imax=k;
      jmax=k;
      p=0.0;
      for ( i=k , ai=ak ; i<n ; ++i , ai+=nn )
      {
         for ( j=k ; j<n ; ++j )
         {
            if ( (q=fabs(ai[j]))>p )
            {
               p=q;
               imax=i;
               jmax=j;
            }
         }
      }
      jun[k]=jmax;
      /* 行の入れ換え */
      if ( imax!=k )
      {
          ai=a+imax*nn;
          aai=aa+imax*nn;
          for ( j=0 ; j<n ; ++j )
          {
             swap(ak[j],ai[j]);
             swap(aak[j],aai[j]);
          }
          swap(b[imax],b[k]);
      }
      /* 列の入れ換え */
      if ( jmax!=k )
      {
          for ( i=0 , aik=a+k , aij=a+jmax
                     , aaik=aa+k , aaij=aa+jmax ; i<n ;
                ++i , aik+=nn , aij+=nn
                    , aaik+=nn , aaij+=nn )
          {
         swap((*aik),(*aij));
         swap((*aaik),(*aaij));
          }
      }
      /*  消去 */
      p=ak[k] ;
	  for ( j=k1 ; j<n ; ++j ){
         ak[j]/=p ;
	  }
      for ( i=k1 , ai=ak+nn ; i<n ; ++i , ai+=nn )
      {
         q=ai[k] ;
		 for ( j=k1 ; j<n ; ++j ){
            ai[j]-=q*ak[j] ;
			}
      }
   }
}


#define   adon(ax)  qs=s; s+=(ax)+t; ds=s-qs; t=(ax)+t-ds;


/* 求解 */
void solacc( double a[] , double x[] , double b[] , int n , int nn )
{
   int     j,k,k1;
   double  s;
   double  qs,ds,t;
   double  *ak;

   /* 前進消去 */
   for ( k=0 , ak=a ; k<n ; ++k , ak+=nn )
   {
      s=b[k] ;
      t=0.0 ;
      for ( j=0 ; j<k ; ++j )
      {
         adon(-ak[j]*x[j]);
      }
      x[k]=s/ak[k] ;
   }
   /* 精密後退代入 */
   for ( k=n-2 , ak=a+nn*(n-2) ; k>=0 ; --k , ak-=nn )
   {
      k1=k+1 ;
      s=x[k] ;
      t=0.0 ;
      for ( j=k1 ; j<n ; ++j )
      {
         adon(-ak[j]*x[j]) ;
      }
      x[k]=s ;
   }
}


/* 残差計算（高精度版）*/
void racc( double a[] , double x[] , double b[] , double r[] , int n , int nn )
{
    int    i, j;
   double s,qs,ds,t;
   double *ai ;
   for ( i=0 , ai=a ; i<n ; ++i , ai+=nn )
   {
      s=b[i];     /* 部分和 */
      t=0.0;      /* 積み残し */
      for ( j=0 ; j<n ; ++j )
      {
         adon(-ai[j]*x[j]);
      }
      r[i]=s;
   }
}

/* 精密ＬＵ分解 */
void decacc(double a[] ,int n, int nn)
{
   int   i,j,k;
   double   p,s,t;
   double   qs,ds;
   double   *ai,*aj,*ak;

   /* 第０行をa[0][0]で割る */
   ai=a;
   p=ai[0];
   for ( j=1 ; j<n ; ++j )
      ai[j]/=p;
   /* ｉのループ */
   for ( i=1 , ai=a+nn ; i<n ; ++i , ai+=nn )
   {
      /* 対角要素 */
      s=ai[i];
      t=0.0;
      for ( k=0 , ak=a ; k<i ; ++k , ak+=nn )
      {
         adon(-ai[k]*ak[i]);
      }
      ai[i]=p=s;
      /* 非対角要素 */
      for ( j=i+1 ; j<n ; ++j )
      {
         aj=a+j*nn;
         s=aj[i];
         t=0.0;
         for ( k=0 , ak=a ; k<i ;
                ++k , ak+=nn )
         {
            adon(-aj[k]*ak[i]);
         }
         aj[i]=s;
         s=ai[j];
         t=0.0;
         for ( k=0 , ak=a ; k<i ;
                ++k , ak+=nn )
         {
            adon(-ai[k]*ak[j]);
         }
         ai[j]=s/p;
      }
   }
}


