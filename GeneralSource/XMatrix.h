/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMatrix.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XMatrixH
#define XMatrixH
//---------------------------------------------------------------------------
#include <iostream>
#define	_USE_MATH_DEFINES
#include <math.h>
#include <new.h>
#include <process.h>
#include <QMessageBox>

#define DEFPREC 10e-6

//===================================================================
// GENERIC, INTELLIGENT MATRIX TYPE
//===================================================================

#define uabs(x) fabs(x)

void    CError(const QString &msg)
{
    QMessageBox::warning(NULL, "Warning", msg);
}
//--------------------------------------------------------------------------
template <class T>
class Vector {
//--------------------------------------------------------------------------
private:
     T*      pVector;
     int     size;
public:
             Vector();                          // Default constructor
             Vector(int);                       // Constructor
             ~Vector(void);                     // Destructor
     T&      operator[](int)    const;                   // index operator
     void    Resize(int);                       // change the vector length
     // (compiler didn't accep constructor calling)
};

//--------------------------------------------------------------------------
template <class T>
Vector<T> :: Vector()                           // Default constructor
//--------------------------------------------------------------------------
{
        size=0;
        pVector=NULL;
}

//--------------------------------------------------------------------------
template <class T>
Vector<T> :: Vector(int x)                      // Constructor
//--------------------------------------------------------------------------
{
     if (x>0) {
          size=x;
          pVector=new T[size];
     }
     else {
          CError("Invalid initialization");
          //exit(1);
     }
}

//--------------------------------------------------------------------------
template <class T>
Vector<T> :: ~Vector()                          // Destructor
//--------------------------------------------------------------------------
{
     delete [] pVector;
}

//--------------------------------------------------------------------------
template <class T>
T&      Vector<T> :: operator[](int x)  const        // Index
//--------------------------------------------------------------------------
{
     if (x<0 || x>=size) {
          CError("Second index out of range.");
          //exit(1);
     }
     return pVector[x];
}

//--------------------------------------------------------------------------
template <class T>
void    Vector<T> :: Resize(int x)              // Resizer constructor
//--------------------------------------------------------------------------
{
     if (x>0) {
          size=x;
          pVector=new T[size];
     }
     else {
          CError("Invalid Resizeing index.");
          //exit(1);
     }
}

//--------------------------------------------------------------------------
template <class R>
class Matrix {
//--------------------------------------------------------------------------
private:
     Vector<R>* pMatrix;                        // pointer of matrix array
     int     xsize, ysize;                      // sizes of matrix array
     void    incomperr(const char*, const char*) const;           // matrix operands incomptbl
     void    precerr(const char*) const;                    // Precision error

public:
// Constuctors & Destructor
    Matrix();                          // Default constructor
    Matrix(int, int);                  // Constructor
    Matrix(const Matrix&);                   // Copy Constructor
    ~Matrix(void);                     // Destructor
// Operator overloads
   // Unary operators
     Matrix  operator!();                       // Invert matrix
     Matrix  operator~();                       // matrix Transponate
     Matrix  operator-();                       // Unary minus
     Matrix  operator+();                       // Unary plus
   // Binary operators
     Vector<R>& operator[](int) const;                // Array subscript
     Matrix  operator+(const Matrix&)   const;                // Binary plus (add)
     Matrix  operator-(const Matrix&)   const;                // Binary minus (subtract)
     Matrix  operator*(const Matrix&)   const;                // matrix matrix multiply
     Matrix  operator*(R)               const;                      // matrix scalar multiply
     Matrix  operator/(const Matrix&)   const;                // matrix * inverted matrix
     Matrix  operator/(R)               const;                      // matrix scalar divide
     //Matrix& operator=(const Matrix&);                // Assignment
     Matrix& operator=(const Matrix );                // Assignment
     Matrix  operator*=(const Matrix&);               // Assign product (matrix)
     Matrix  operator*=(R);                     // Assign product (scalar)
     Matrix  operator/=(const Matrix&);               // Assign quotient
     Matrix  operator/=(R);                     // Assign quotient
     Matrix  operator+=(const Matrix&);               // Assign sum
     Matrix  operator-=(const Matrix&);               // Assign difference
     int     operator==(const Matrix&)  const;               // Equal to
     int     operator!=(const Matrix&)  const;               // Not equal to
// Common Methods
     void    Print(void);                       // print matrix
     void    Set(int, int, R);                  // Set an element of matrix
     R       Get(int, int);                     // Get an element of matrix
     bool    Subm(int,int,int,int);             // Submatrix of a matrix
     Matrix  Leave(int,int);                    // Leave one row and column
     Matrix  Adj();                             // A matrix adjungalt matrixa
   // Numeric algorythms from Lajos Szandi
     Matrix  Inv(double precision=DEFPREC)  const;     // matrix invertion
     Matrix  LU_decomp(double prec=DEFPREC) const;    // LU decomposition
     void    LU_takeapart(const Matrix&,const Matrix&);     // Take apart LU matrix into L and U matrixes
     R       Det(double precision=DEFPREC);     // matrix determinant
     void    LU_solve(const Matrix&,const Matrix&,double prec=DEFPREC);  // Solve with LU matrix
     bool    GJ_Elim(const Matrix&,const Matrix&,double prec=DEFPREC);   // Gauss-Jordan eliminacio
     bool    G_Elim(const Matrix&,const Matrix&,double prec=DEFPREC);    // Gauss eliminacio
     bool    G_Elim_RF(const Matrix&,const Matrix&,double prec=DEFPREC); // Gauss eliminacio reszleges foelemkivalasztassal
     bool    G_Elim_TF(const Matrix&,const Matrix&,double prec=DEFPREC); // Gauss eliminacio teljes foelemkivalasztassal
};

// private:
//--------------------------------------------------------------------------
template <class R>
void    Matrix<R>::incomperr(const char* op, const char* descr)     const// matrix operands incomp
//--------------------------------------------------------------------------
{
    QString Msg=QString("The operands of ")+QString(op) +QString(" operator (")+QString(descr)+QString(") are incompatible.");

    QMessageBox::warning(NULL, "Warning", Msg);
     //exit(1);
}

//--------------------------------------------------------------------------
template <class R>
void    Matrix<R>::precerr(const char* algo)  const        // Precision error
//--------------------------------------------------------------------------
{
    QString Msg=QString("Precision error in ")+QString(algo) +QString(" algorythm.");

    QMessageBox::warning(NULL, "Warning", Msg);
    //exit(1);
}

// Constuctors & Destructor
//--------------------------------------------------------------------------
template <class R>
Matrix<R>::Matrix()                             // Default constructor
//--------------------------------------------------------------------------
{
     xsize=ysize=1;
     pMatrix=new Vector<R>(1);
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R>::Matrix(int y, int x)               // Constructor
//--------------------------------------------------------------------------
{
     int i=0;
     if (x<1 || y<1) {
          CError("Invalid initialization index.");
          //exit(1);
     }
     xsize=x;
     ysize=y;
     pMatrix=new Vector<R>[ysize];
     for(;i<ysize;i++)
          pMatrix[i].Resize(xsize);
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R>::Matrix(const Matrix<R>& m)                 // Copy constructor
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     xsize=m.xsize;
     ysize=m.ysize;
     pMatrix=new Vector<R>[ysize];
     for(;i<ysize;i++)
          pMatrix[i].Resize(xsize);
     for(i=0;i<ysize;i++)
          for(j=0;j<xsize;j++)
               pMatrix[i][j]=m[i][j];
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R>::~Matrix()                            // Destructor
//--------------------------------------------------------------------------
{
     delete [] pMatrix;
}

// Operator overloads
// Unary operators
//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator!()                // Invert matrix
//--------------------------------------------------------------------------
{
     return ((*this).Inv());
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator~()                // matrix Transponate
//--------------------------------------------------------------------------
{
     if (xsize!=ysize)
          incomperr("~","transponate matrix");
     Matrix trn(xsize,ysize);
     int i=0,j=0;
     for(;i<xsize;i++)
          for(j=0;j<ysize;j++)
               trn[i][j]=(*this)[j][i];
     return trn;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator-()                // Unary minus
//--------------------------------------------------------------------------
{
     Matrix neg(ysize,xsize);
     int i=0,j=0;
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               neg[i][j]=-pMatrix[i][j];
     return neg;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator+()                // Unary plus
//--------------------------------------------------------------------------
{
     return *this;
}

// Binary operators
//--------------------------------------------------------------------------
template <class R>
Vector<R>& Matrix<R>::operator[](int y) const        // Array subscript
//--------------------------------------------------------------------------
{
     if (y<0 || y>=ysize) {
          CError("First index out of range.");
          //exit(1);
     }
     return pMatrix[y];
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator+(const Matrix<R>& m) const   // Binary plus (add)
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("+","Binary plus (add)");
     Matrix sum(ysize, xsize);
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               sum[i][j]=pMatrix[i][j]+m[i][j];
     return sum;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator-(const Matrix<R>& m) const   // Binary minus (substract)
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("-","Binary minus (substract)");
     Matrix sub(ysize, xsize);
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               sub[i][j]=pMatrix[i][j]-m[i][j];
     return sub;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator*(const Matrix<R>& m) const   // matrix matrix multiply
//--------------------------------------------------------------------------
{
     int x=0,y=0,i=0;
     if (xsize!=m.ysize)
          incomperr("*","matrix matrix multiply");
     R sum;
     Matrix<R> res(ysize, m.xsize);
     for(;y<ysize;y++)
          for(x=0;x<m.xsize;x++) {
               sum=0;
               for(i=0;i<xsize;i++)
                    sum+=pMatrix[y][i]*m[i][x];
               res[y][x]=sum;
          }
     return res;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator*(R d)   const          // matrix scalar multiply
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     Matrix mul(ysize, xsize);
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               mul[i][j]=pMatrix[i][j]*d;
     return mul;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator/(const Matrix<R>& m)  const  // matrix * inverted matrix
//--------------------------------------------------------------------------
{
     if (!(m.xsize==m.ysize && xsize==m.ysize))
          incomperr("/","matrix * inverted matrix");
     return ((*this)*m.Inv());
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator/(R d1)  const          // matrix scalar divide
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     R d2=1/d1;
     Matrix div(ysize, xsize);
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               div[i][j]=pMatrix[i][j]*d2;
     return div;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R>& Matrix<R>::operator=(const Matrix<R> m)   // Assignment
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (this==&m) return *this;                // s = s type nop operation
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("=","Assignment");
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               pMatrix[i][j]=m[i][j];
     return *this;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator*=(const Matrix<R>& m)   // Assign product (matrix)
//--------------------------------------------------------------------------
{
     (*this)=((*this)*m);
     return *this;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator*=(R d)            // Assign product (scalar)
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               pMatrix[i][j]*=d;
     return *this;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator/=(const Matrix<R>& m)   // Assign quotient (matrix)
//--------------------------------------------------------------------------
{
     return ((*this)=((*this)*m.Inv()));
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator/=(R d1)           // Assign quotient (scalar)
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     R d2=1/d1;
     for(;i<xsize;i++)
          for(j=0;j<ysize;j++)
               pMatrix[i][j]*=d2;
     return *this;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator+=(const Matrix<R>& m)   // Assign sum
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("+=","Assign sum");
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               pMatrix[i][j]+=m[i][j];
     return *this;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::operator-=(const Matrix<R>& m)   // Assign difference
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("-=","Assign difference");
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               pMatrix[i][j]-=m[i][j];
     return *this;
}

//--------------------------------------------------------------------------
template <class R>
int     Matrix<R>::operator==(const Matrix<R>& m)   const  // Equal to
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("==","Equal to");
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               if (pMatrix[i][j]!=m[i][j])
                    return 0;
     return 1;
}

//--------------------------------------------------------------------------
template <class R>
int     Matrix<R>::operator!=(const Matrix<R>& m)  const   // Not equal to
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (xsize!=m.xsize || ysize!=m.ysize)
          incomperr("!=","Not equal to");
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               if (pMatrix[i][j]!=m[i][j])
                    return 1;
     return 0;
}

// Common methods
//--------------------------------------------------------------------------
template <class R>
void    Matrix<R>::Print()                      // Print matrix
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     for(;i<ysize;i++) {
          cout << "|\t";
          for(j=0;j<xsize;j++)
               cout << pMatrix[i][j] << "\t";
          cout << "|\n";
     }
     cout << "\n";
}

//--------------------------------------------------------------------------
template <class R>
void    Matrix<R>::Set(int y, int x, R num)     // Set an element of matrix
//--------------------------------------------------------------------------
{
     if (x<0 || x>=xsize || y<0 || y>=ysize) {
          CError("Index out of range during Set.");
          //exit(1);
     }
     pMatrix[y][x]=num;
}

//--------------------------------------------------------------------------
template <class R>
R       Matrix<R>::Get(int y, int x)            // Get an element of matrix
//--------------------------------------------------------------------------
{
     if (x<0 || x>=xsize || y<0 || y>=ysize) {
          CError("Index out of range during Get.");
          //exit(1);
     }
     return pMatrix[y][x];
}

//--------------------------------------------------------------------------
template <class R>
bool Matrix<R>::Subm(int y1,int x1,int y2,int x2) // Submatrix of a matrix
//--------------------------------------------------------------------------
{
     int i=0,j=0;
     if (!(x1<=x2 && x1>=0 && x2<xsize && y1<=y2 && y1>=0 && y2<ysize)) {
        return(false);
        }
     Matrix subm(y2-y1+1,x2-x1+1);
     for(i=y1; i<=y2; i++)
          for(j=x1; j<=x2; j++)
               subm[i-y1][j-x1]=pMatrix[i][j];
     return true;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::Leave(int row, int column) // Leave one row and column
//--------------------------------------------------------------------------
{
     if (row<0 || row>=ysize || column<0 || column>=xsize) {
          CError("Parameters out of range.");
          //exit(0);
     }
     Matrix leave(ysize-1,xsize-1);
     int i=0,j=0;
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++) {
               if (i<row) {
                    if (j<column)
                         leave[i][j]=pMatrix[i][j];
                    if (j>column)
                         leave[i][j-1]=pMatrix[i][j];
               }
               if (i>row) {
                    if (j<column)
                         leave[i-1][j]=pMatrix[i][j];
                    if (j>column)
                         leave[i-1][j-1]=pMatrix[i][j];
               }
     }
     return leave;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::Adj()                      // matrix adjungalt matrixa
//--------------------------------------------------------------------------
{
     Matrix adj(ysize,xsize);
     int i=0,j=0;
     for(;i<ysize;i++)
          for(j=0;j<xsize;j++)
               if ((i+j)%2==0)
                    adj[i][j]=((*this).Leave(i,j)).Det();
               else
                    adj[i][j]=-((*this).Leave(i,j)).Det();
     return (~adj);
}

// Numeric algorythms from Lajos Szandi
//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::Inv(double precision)  const    // matrix invertalasa
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (ysize!=n)
          incomperr("! or /=","Contains matrix invertation");
     R s;                                       // munka valtozo
     int i=0,j=0,k=0;                           // ciklusvaltozok
     Matrix a(n,n);                             // munka matrix
     Matrix ai(n,n);                            // inverz matrix

     for(i=0;i<n;i++)                           // az atadott matrix...
          for(j=0;j<n;j++)                      // munkavaltozoba masolasa
               a[i][j]=pMatrix[i][j];
     for(i=0;i<n;i++) {                         // egysegmatrix feltoltese
          for(k=0;k<n;k++)
               ai[i][k]=0.0;                    // nulla mindenutt,
          ai[i][i]=1.0;                         // kiveve a foatloban
     }
     for(i=0;i<n;i++) {                         // az i-edik sorral eliminalunk
         if(uabs(a[i][i])<precision)
             return ai;
          s=1.0/a[i][i];
          if (uabs(1/s)<precision)              // ha tul kicsi
               precerr("matrix invert");
          for(k=i+1; k<n; k++)
               a[i][k]*=s;                      // invertalando matrix
          for(k=0; k<n; k++)
               ai[i][k]*=s;                     // inverz matrix
          for(j=0; j<n; j++)                    // i-edik oszlop eliminalasa
               if (j!=i) {                      // a j-edik sorban
                    s=a[j][i];
                    for(k=i+1; k<n; k++)
                         a[j][k]-=s*a[i][k];
                    for(k=0; k<n; k++)
                         ai[j][k]-=s*ai[i][k];
               }
     }
     return ai;
}

//--------------------------------------------------------------------------
template <class R>
Matrix<R> Matrix<R>::LU_decomp(double prec)   const  // L-U felbontas
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (ysize!=n)
          incomperr("LU_decomp","LU decomposition");
     int i,j,k;                                 // ciklus valtozok
     R si,sj;                                   // munka valtozok
     Matrix m(n,n);                             // munka matrix
     for(i=0;i<n;i++)                           // az atadott matrix...
          for(j=0;j<n;j++)                      // munkavaltozoba masolasa
               m[i][j]=pMatrix[i][j];
     for(i=0; i<n; i++) {
          si=m[i][i];                           // foatlobeli elem
          if (uabs(si)<prec)                    // tul kicsi
               precerr("LU_decomp");
          for(j=i+1; j<n; j++) {
               sj=m[j][i]/si;                   // eliminalando elem
               for(k=i+1; k<n; k++)
                    m[j][k]-=sj*m[i][k];
// a[j,k]-=a[j,i]*a[i,k]/a[i,i] : ez az ertek lenne a [j,i] helyen, ha az
// i. sort a[i][i]-vel elosztottuk volna
               m[j][i]=sj;
          }
     }
     return m;
}

//--------------------------------------------------------------------------
template <class R>
void    Matrix<R>::LU_takeapart(const Matrix<R>& L,const Matrix<R>& U)
// LU matrix szetszedese 2 matrixba
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (ysize!=n)
          incomperr("LU_takepart","Takeapart LU to L and U");
     int x,y;
     Matrix& LU=*this;                          // az LU szeteszedett matrix
     for(x=0; x<n; x++) {                       // sor
          for(y=0; y<n; y++)                    // oszlop
               if (y<x) {                       // foatlo alatt
                    L[x][y]=LU[x][y];
                    U[x][y]=0.0;
               }
               else {                           // foatlo es felette
                    L[x][y]=0.0;
                    U[x][y]=LU[x][y];
               }
          L[x][x]=1.0;                          // foatlo
     }
}

//--------------------------------------------------------------------------
template <class R>
R       Matrix<R>::Det(double precision)        // Gauss eliminacio
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (ysize!=n)
          incomperr("det","matrix's determinant");
     Matrix m(n,n);                             // munka matrix
     int i,j,k;                                 // ciklus valtozok
     R s,det;                                   // munka valtozo, determinans

     for(i=0; i<n; i++)                         // az atadott matrix...
          for(j=0; j<n; j++)                    // munkavaltozoba masolasa
               m[i][j]=pMatrix[i][j];
     det=1.0;
     for(i=0; i<n; i++) {                       // i-edik sorral eliminalunk
          s=m[i][i];                            // foatlobeli elem
          det*=s;
          if (uabs(s)<precision)                // tul kicsi
               precerr("det");
          s=1/s;                                // szorozni gyorsabb
          for(k=i+1; k<n; k++)
               m[i][k]*=s;                      // foatloban elvileg 1 lett
          for(j=i+1; j<n; j++) {                // i. oszlop eliminalasa
               s=m[j][i];
               for(k=i+1; k<n; k++)             // j. sor elemei i. oszloptol
                    m[j][k]-=s*m[i][k];
          }
     };   // most elvileg foatloban 1, alatta 0 van
     return det;
}

//--------------------------------------------------------------------------
// Egyenletrendszer megoldasa L-U felbontott matrix-szal
template <class R>
void    Matrix<R>::LU_solve(const Matrix<R>& x, const Matrix<R>& b, double prec)
// jobb oldal: L*U*x = b
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (!(ysize==n && x.ysize==b.ysize && x.ysize==n))
          incomperr("LU_solve","Solving with LU matrix");

     int i,k;                                   // ciklus valtozok
     R s,w;                                     // munka valtozok
     Matrix& LU=*this;                          // actual matrix is LU

     // 1. lepes:  L * (Ux) = b  megoldasa Ux -re, ez x-be kerul
     for(i=0; i<n; i++) {                       // x[i] meghatarozasa
          s=b[i][0];
          for(k=0; k<i; k++)
               s-=LU[i][k]*x[k][0];
          x[i][0]=s;                            // eredmeny tarolasa
     }

     // 2. lepes:  Ux = y  megoldasa x -re, y most x-ben van
     for(i=n-1; i>=0; i--) {                    // x[i] meghatarozasa
          if (uabs(w=LU[i][i])<prec)            // foatloban tul kicsi
               precerr("LU_solve");
          s=x[i][0];                            // =y[i]
          for(k=i+1; k<n; k++)
               s-=LU[i][k]*x[k][0];
          x[i][0]=s/w;                          // eredmeny tarolasa
     }
}

//--------------------------------------------------------------------------
// Gauss-Jordan eliminacio
template <class R>
bool Matrix<R>::GJ_Elim(const Matrix<R>& x, const Matrix<R>& b, double prec)
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (!(ysize==n && x.ysize==b.ysize && x.ysize==n))
        return(false);

     int i,j,k;                                 // ciklus valtozo
     R s;                                       // munkavaltozo
     Matrix a(n,n+1);                           // munka matrix

     for(i=0; i<n; i++) {                       // az atadott matrix...
          for(j=0; j<n; j++)                    // munkavaltozoba masolasa
               a[i][j]=pMatrix[i][j];
          a[i][n]=b[i][0];
     }

     for(i=0; i<n; i++) {                       // i-edik sorral eliminalunk
          s=a[i][i];                            // foatlobeli elem
          if (uabs(s)<prec){
               return(false);              // tul kicsi
               }
          s=1/s;                                // szorozni gyorsabb lesz
          for(k=i+1; k<n+1; k++)
               a[i][k]*=s;                      // foatloban elvileg 1 lett
          for(j=0; j<n; j++)
               if (j!=i) {                      // i. oszlop eliminalasa
                    s=a[j][i];
                    for(k=i+1; k<n+1; k++)      // j. sor elemei i. oszloptol
                         a[j][k]-=s*a[i][k];
               }
     };     // most elvileg foatloban 1, masutt 0 van
     for(i=0; i<n; i++)
          x[i][0]=a[i][n];                      // megoldas atrakasa
     return true;
}

//--------------------------------------------------------------------------
// Gauss eliminacio
template <class R>
bool Matrix<R>::G_Elim(const Matrix<R>& x, const Matrix<R>& b, double prec)
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (!(ysize==n && x.ysize==b.ysize && x.ysize==n))
          incomperr("G_Elim","Gauss elimination");

     int i,j,k;                                 // ciklus valtozok
     R s;                                       // munkavaltozo
     Matrix a(n,n+1);                           // munka matrix

     for(i=0; i<n; i++) {                       // az atadott matrix...
          for(j=0; j<n; j++)                    // munkavaltozoba masolasa
               a[i][j]=pMatrix[i][j];
          a[i][n]=b[i][0];
     }
     for(i=0; i<n; i++) {                       // i-edik sorral eliminalunk
          s=a[i][i];                            // foatlobeli elem
          if (uabs(s)<prec)                     // tul kicsi
               precerr("G_Elim");
          s=1/s;                                // szorozni gyorsabb
          for(k=i+1; k<n+1; k++)
               a[i][k]*=s;                      // foatloban elvileg 1 lett
          for(j=i+1; j<n; j++) {                // i. oszlop eliminalasa
               s=a[j][i];
               for(k=i+1; k<n+1; k++)           // j. sor elemei i. oszloptol
                    a[j][k]-=s*a[i][k];
          }
     };   // most elvileg foatloban 1, alatta 0 van

     x[n-1][0]=a[n-1][n];                       // x[] meghat.
     for(i=n-2; i>=0; i--) {
          s=a[i][n];
          for(k=i+1; k<n; k++)
               s-=a[i][k]*x[k][0];
          x[i][0]=s;
     }
     return true;
}

//--------------------------------------------------------------------------
// Gauss eliminacio reszleges foelemkivalasztassal
template <class R>
bool Matrix<R>::G_Elim_RF(const Matrix<R>& x, const Matrix<R>& b, double prec)
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (!(ysize==n && x.ysize==b.ysize && x.ysize==n))
          incomperr("G_Elim_RF","Gauss elimination with partial mainelement selection");

     int i,j,k;                                 // ciklus valtozok
     R s;                                       // munkavaltozo
     double s2;                                 // munka valtozo
     Matrix a(n,n+1);                           // munka matrix

     for(i=0; i<n; i++) {                       // az atadott matrix...
          for(j=0; j<n; j++)                    // munkavaltozoba masolasa
               a[i][j]=pMatrix[i][j];
          a[i][n]=b[i][0];
     }
     for(i=0; i<n; i++) {                       // i-edik sorral eliminalunk
          s2=uabs(a[i][i]);
          j=i;                                  // legnagyobb absz.ert. elem...
          for(k=i+1; k<n; k++)                  // keresese az i. oszlopban
               if (uabs(a[k][i])>s2) {
                    j=k;
                    s2=uabs(a[j][i]);
               }
          if (uabs(s2)<prec)                    // tul kicsi
               precerr("G_Elim_RF");
          if (j!=i)                             // i. es j. sor csereje
               for(k=i; k<n+1; k++) {
                    s=a[i][k];
                    a[i][k]=a[j][k];
                    a[j][k]=s;
               }
          // Innen ugyanaz, mint G_Elim
          s=1.0/a[i][i];                        // foatlobeli elem reciproka
          for(k=i+1; k<n+1; k++)
               a[i][k]*=s;                      // foatloban elvileg 1 lett
          for(j=i+1; j<n; j++) {                // i. oszlop eliminalasa
               s=a[j][i];
               for(k=i+1; k<n+1; k++)           // j. sor elemei i. oszloptol
                    a[j][k]-=s*a[i][k];
          }
     };      // most elvileg foatloban 1, alatta 0 van

     x[n-1][0]=a[n-1][n];                       // x[] meghat.
     for(i=n-2; i>=0; i--) {
          s=a[i][n];
          for(k=i+1; k<n; k++)
               s-=a[i][k]*x[k][0];
          x[i][0]=s;
     }
     return true;
}

//--------------------------------------------------------------------------
// Gauss eliminacio teljes foelemkivalasztassal
template <class R>
bool Matrix<R>::G_Elim_TF(const Matrix<R>& x, const Matrix<R>& b, double prec)
//--------------------------------------------------------------------------
{
     int n=xsize;
     if (!(ysize==n && x.ysize==b.ysize && x.ysize==n))
          incomperr("G_Elim_TF","Gauss elimination with total mainelement selection");

     int i,j,k,h,m;                             // ciklus valtozok
     R s;                                       // munka valtozo
     double s2;                                 // munka valtozo 2
     int *hely;                                 // melyik oszlop hova kerul
     Matrix a(n,n+1);                           // munka matrix
     hely=new int[n];
     for(i=0; i<n; i++) {                       // az atadott matrix...
          for(j=0; j<n; j++)                    // munkavaltozoba masolasa
               a[i][j]=pMatrix[i][j];
          a[i][n]=b[i][0];
     }
     for(k=0; k<n; k++)
          hely[k]=k;                            // eredeti hely
     for(i=0; i<n; i++) {                       // i-edik sorral eliminalunk
          s2=0.0;                               // legnagyobb absz.ert. elem...
          for(m=i; m<n; m++)                    // keresese az i-n almatrixban
               for(k=i; k<n; k++)               // m=sorindex, k=oszlopindex
                    if (uabs(a[m][k])>s2) {
                         j=m;
                         h=k;
                         s2=uabs(a[m][k]);
                    }
          if (uabs(s2)<prec) {                  // tul kicsi
               delete [] hely;
               precerr("G_Elim_TF");
          }
          if (j!=i)                             // i. es j. sor csereje
               for(k=i; k<n+1; k++) {
                    s=a[i][k];
                    a[i][k]=a[j][k];
                    a[j][k]=s;
               }
          if (h!=i) {                           // h. es i. oszlop csereje
               for(m=0; m<n; m++) {
                    s=a[m][i];
                    a[m][i]=a[m][h];
                    a[m][h]=s;
               }
               m=hely[i];
               hely[i]=hely[h];
               hely[h]=m;                       // oszlopindexek csereje
          }
          // --- Innen egy darabig ugyanaz, mint G_Elim ---
          s=1.0/a[i][i];                        // foatlobeli elem reciproka
          for(k=i+1; k<n+1; k++)
               a[i][k]*=s;                      // foatloban elvileg 1 lett
          for(j=i+1; j<n; j++) {                // i. oszlop eliminalasa
               s=a[j][i];                       // a j. sorban
               for(k=i+1; k<n+1; k++)           // j. sor elemei i. oszloptol
                    a[j][k]-=s*a[i][k];
          }
     }   // most elvileg foatloban 1, alatta 0 van

     for(i=n-2; i>=0; i--) {                    // ismeretlenek a[*][n]-be
          s=a[i][n];
          for(k=i+1; k<n; k++)
               s-=a[i][k]*a[k][n];              // itt kicsit mas
          a[i][n]=s;
     }
     for(i=0; i<n; i++)
          x[hely[i]][0]=a[i][n];                // megoldas az eredeti helyre
     delete [] hely;
     return true;
}

#endif

