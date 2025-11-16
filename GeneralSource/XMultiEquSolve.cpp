/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMultiEquSolve.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
//---------------------------------------------------------------------------
#include "XMultiEquSolve.h"
#include <stdio.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"

//---------------------------------------------------------------------------


#define	 adon(ax)  qs=s; s+=(ax)+t; ds=s-qs; t=(ax)+t-ds;



/* 予備的ＬＵ分解 */
static	void predec( double *a , double *aa , double *b , int n , int jun[] );
/* 求解 */
static	void    solacc( double *a , double *x , double *b , int n);
/* 精密ＬＵ分解 */
static	void    decacc(double *a ,int n);
/* 行列の複写 */
static	void    cpm( double *a , double *b , int n);
/* 残差計算（高精度版）*/
static	void    racc( double *a , double *x , double *b , double *r , int n);


XMultiEquSolve::XMultiEquSolve()
{
    n=0;
}
XMultiEquSolve::~XMultiEquSolve()
{
    ReleaseMatrix();
}

bool XMultiEquSolve::AllocateMatrix(int nMatrix)
{
    n=nMatrix;

    FillZero();
    return(true);
}
void XMultiEquSolve::ReleaseMatrix(void)
{
    n=0;
}
void XMultiEquSolve::FillZero(void)
{
    for(int i=0;i<=(n+1)*(n+1);i++){
        a[i]=0.0;
        }
    for(int i=0;i<=n;i++){
        b[i]=0;
        x[i]=0;
        }
}

void	XMultiEquSolve::SetMatrixValue(int kx, int ky, double value)
{
	int	v=(ky-1)*n+kx-1;
    if((v<sizeof(a)/sizeof(a[0])) && (1<=kx) && (kx<=n) && (1<=ky) && (ky<=n)){
        a[v]=value;
        }
}
double	XMultiEquSolve::GetMatrixValue(int kx, int ky)	const
{
	int	v=(ky-1)*n+kx-1;
	if((v<sizeof(a)/sizeof(a[0])) && (1<=kx) && (kx<=n) && (1<=ky) && (ky<=n)){
        return(a[v]);
	}
    return(0);
}

void	XMultiEquSolve::SetMatrixValueBn(int i, double value)
{
	int	v=i-1;
	if((v<sizeof(b)/sizeof(b[0])) && (1<=i) && (i<=n)){
        b[v]=value;
	}
}

double	XMultiEquSolve::GetMatrixValueBn(int i)	const
{
	int	v=i-1;
	if((v<sizeof(b)/sizeof(b[0])) && (1<=i) && (i<=n)){
        return(b[v]);
	}
    return(0);
}

double	XMultiEquSolve::GetAnswer(int i)	const
{
	int	v=i-1;
	if((v<sizeof(x)/sizeof(x[0])) && (1<=i) && (i<=n)){
        return(x[v]);
	}
    return(0);
}

/* 連立１次方程式(高精度版）*/
void XMultiEquSolve::ExecuteGaussianElimination(void)
{
    if(n==2){
        double  d=a[1]*a[2]-a[0]*a[3];
		if(fabs(d)<1.0E-300){
            return;
		}
        x[0]=(a[1]*b[1]-a[3]*b[0])/d;
        x[1]=(a[2]*b[0]-a[0]*b[1])/d;
        return;
        }

	int     i,j,k;
	double  p,q;
	double  *ai,*aj,*aij ;

	int	jun[MaxDimMultiEqu];
	double	aa[MaxDimMultiEqu*MaxDimMultiEqu];
    double  sf[MaxDimMultiEqu];

	/* 前処理(行) */
	for ( i=0 , ai=a ; i<n ; ++i , ai+=n )
	{
		p=0.0;
		for ( j=0 ; j<n ; ++j )
		{
			if ( (q=fabs(ai[j]))>p ){
				p=q;
			}
		}
		for ( j=0 ; j<n ; ++j ){
			if(p==0.0){
                ai[j]=ai[j];
			}
			else{
			    ai[j]/=p;
			}
        }
		b[i]/=p;
	}
	/* 前処理(列) */
	for ( j=0 , aj=a ; j<n ; ++j , ++aj )
	{
		p=0.0;
		for ( i=0 , aij=aj ; i<n ; ++i , aij+=n )
		{
			if ( (q=fabs(*aij))>p ){
				p=q;
			}
		}
		for ( i=0 , aij=aj ; i<n ; ++i , aij+=n ){
			if(p==0.0){
                (*aij)=0.0;
			}
            else{
				if(p!=0.0){
    			    (*aij)/=p;
				}
            }
        }
		sf[j]=p;
	}
	/* Ａを待避 */
	cpm( a , aa , n );
	/* 予備的ＬＵ分解 */
	predec( a , aa , b , n , jun );
	//printf( "L[n-1][n-1]=%15.8e\n",*(a+(n-1)*n+n-1));
    
	/* Ａを復元 */
	cpm( aa , a , n);
	/* 精密ＬＵ分解 */
	decacc( a , n );
	/* 右辺の精密計算 */
	solacc( a , x , b , n );
	/* 順序復元 */
	for ( k=n-2 ; k>=0 ; --k )
	{
		swap(x[k],x[jun[k]]);
	}
	/* スケーリングの復元 */
	for ( k=0 ; k<n ; ++k ){
		if(sf[k]!=0.0){
		    x[k]/=sf[k];
        }
	}
}

/* 予備的ＬＵ分解 */
static void predec( double *a , double *aa , double *b , int n , int jun[] )
{
	int     i,j,k,k1,imax,jmax ;
	double  p,q;
	double  *ai,*ak,*aik,*aij ;
	double  *aai,*aak,*aaik,*aaij ;

	/* 前進消去 */
	for ( k=0 , ak=a , aak=aa ; k<n-1 ;
	      ++k , ak+=n , aak+=n )
	{
		k1=k+1 ;
		/* ピボット選択 */
		imax=k;
		jmax=k;
		p=0.0;
		for ( i=k , ai=ak ; i<n ; ++i , ai+=n )
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
		    ai=a+imax*n;
		    aai=aa+imax*n;
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
		          ++i , aik+=n , aij+=n
		              , aaik+=n , aaij+=n )
		    {
			swap((*aik),(*aij));
			swap((*aaik),(*aaij));
		    }
		}
		/*  消去 */
		p=ak[k] ;
		for ( j=k1 ; j<n ; ++j ){
			if(p==0.0){
                ak[j]=0.0;
			}
            else{
				if(p==0.0){
                    ak[j]=0.0;
				}
				else{
			        ak[j]/=p ;
                }
            }
		}
		for ( i=k1 , ai=ak+n ; i<n ; ++i , ai+=n )
		{
			q=ai[k] ;
			for ( j=k1 ; j<n ; ++j ){
				ai[j]-=q*ak[j] ;
			}
		}
	}
}

/* 求解 */
static  void    solacc( double *a , double *x , double *b , int n )
{
	int     j,k,k1;
	double  s;
	double  qs,ds,t;
	double  *ak;

	/* 前進消去 */
	for ( k=0 , ak=a ; k<n ; ++k , ak+=n )
	{
		s=b[k] ;
		t=0.0 ;
		for ( j=0 ; j<k ; ++j )
		{
			adon(-ak[j]*x[j]);
		}
		if(ak[k]==0.0){
            x[k]=0.0;
		}
        else{
			if(ak[k]==0.0){
    		    x[k]=0.0;
			}
			else{
		        x[k]=s/ak[k] ;
            }
		}
	}
	/* 精密後退代入 */
	//for ( k=n-2 , ak=a+n*(n-2) ; k>=0 ; --k , ak-=n )
    for ( k=n-2 , ak=a+n*(n-2) ; k>=0 ; k-- , ak-=n )
	{
		k1=k+1 ;
		s=x[k] ;
		t=0.0 ;
		for ( j=k1 ; j<n ; ++j )
		{
			adon(-ak[j]*x[j]) ;
		}
        if(k>=0){
    		x[k]=s ;
            }
	}
}

/* 精密ＬＵ分解 */
static void decacc(double *a ,int n )
{
	int	i,j,k;
	double	p,s,t;
	double	qs,ds;
	double	*ai,*aj,*ak;

	/* 第０行をa[0][0]で割る */
	ai=a;
	p=ai[0];
	for ( j=1 ; j<n ; ++j ){
		if(p==0.0){
		    ai[j]=0.0;
		}
		else{
            ai[j]/=p;
        }
	}
	/* ｉのループ */
	for ( i=1 , ai=a+n ; i<n ; ++i , ai+=n )
	{
		/* 対角要素 */
		s=ai[i];
		t=0.0;
		for ( k=0 , ak=a ; k<i ; ++k , ak+=n )
		{
			adon(-ai[k]*ak[i]);
		}
		ai[i]=p=s;
		/* 非対角要素 */
		for ( j=i+1 ; j<n ; ++j )
		{
			aj=a+j*n;
			s=aj[i];
			t=0.0;
			for ( k=0 , ak=a ; k<i ;
					 ++k , ak+=n )
			{
				adon(-aj[k]*ak[i]);
			}
			aj[i]=s;
			s=ai[j];
			t=0.0;
			for ( k=0 , ak=a ; k<i ;
					 ++k , ak+=n )
			{
				adon(-ai[k]*ak[j]);
			}
            if(p==0.0){
                ai[j]=0.0;
                }
            else{
			    ai[j]=s/p;
                }

		}
	}
}

/* 行列の複写 */
static  void    cpm( double *a , double *b , int n )
{
	int     i,j ;
	double  *ai,*bi ;
	for ( i=0 , ai=a , bi=b ; i<n ;
		++i , ai+=n , bi+=n ){
		  for ( j=0 ; j<n ; ++j ){
			bi[j]=ai[j];
		  }
	}
}

/* 残差計算（高精度版）*/
static  void    racc( double *a , double *x , double *b , double *r , int n )
{
	int    i,j;
	double s,qs,ds,t;
	double *ai ;
	for ( i=0 , ai=a ; i<n ; ++i , ai+=n )
	{
		s=b[i];		/* 部分和 */
		t=0.0;		/* 積み残し */
		for ( j=0 ; j<n ; ++j )
		{
			adon(-ai[j]*x[j]);
		}
		r[i]=s;
	}
}
