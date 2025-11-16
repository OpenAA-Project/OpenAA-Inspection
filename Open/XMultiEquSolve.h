/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XMultiEquSolve.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef XMultiEquSolveH
#define XMultiEquSolveH
//---------------------------------------------------------------------------
#include "XTypeDef.h"

#define MaxDimMultiEqu  10

class   XMultiEquSolve
{
    double  a[MaxDimMultiEqu*MaxDimMultiEqu];
    double  b[MaxDimMultiEqu];
    double  x[MaxDimMultiEqu];
    int     n;
  public:

	XMultiEquSolve();
	virtual ~XMultiEquSolve();

	bool AllocateMatrix(int nMatrix);
	void ReleaseMatrix(void);
	void FillZero(void);

	void	SetMatrixValue(int x, int y, double value);
                                //x,yは１から始まる数値
	double	GetMatrixValue(int x, int y)	const;
                                //x,yは１から始まる数値

	void	SetMatrixValueBn(int n, double value);
                                //ｎは１から始まる数値
	double	GetMatrixValueBn(int n)	const;
                                //ｎは１から始まる数値


	void ExecuteGaussianElimination(void);

	double	GetAnswer(int n)	const;
                                //ｎは１から始まる数値

};

/*
	連立式
	a1*x1+a2*x2+a3*x3+a4*x4=M1
	b1*x1+b2*x2+b3*x3+b4*x4=M2
	c1*x1+c2*x2+c3*x3+c4*x4=M3
	d1*x1+d2*x2+d3*x3+d4*x4=M4
	で、a1～a4,b1～b4,c1～c4,d1～d4,M1～M4がわかっている場合、解ける

	XMultiEquSolve	A;
	A.AllocateMatrix(4);	//４個の変数
	A.SetMatrixValue(1,1,a1);
	A.SetMatrixValue(2,1,a2);
	A.SetMatrixValue(3,1,a3);
	A.SetMatrixValue(4,1,a4);
	A.SetMatrixValue(1,2,b1);
	A.SetMatrixValue(2,2,b2);
	A.SetMatrixValue(3,2,b3);
	A.SetMatrixValue(4,2,b4);
	A.SetMatrixValue(1,3,c1);
	A.SetMatrixValue(2,3,c2);
	A.SetMatrixValue(3,3,c3);
	A.SetMatrixValue(4,3,c4);
	A.SetMatrixValue(1,4,d1);
	A.SetMatrixValue(2,4,d2);
	A.SetMatrixValue(3,4,d3);
	A.SetMatrixValue(4,4,d4);
	A.SetMatrixValueBn(1,M1);
	A.SetMatrixValueBn(2,M2);
	A.SetMatrixValueBn(3,M3);
	A.SetMatrixValueBn(4,M4);
	A.ExecuteGaussianElimination();	//計算開始

	x1=A.GetAnswer(1);	//答え
	x2=A.GetAnswer(2);
	x3=A.GetAnswer(3);
	x4=A.GetAnswer(4);
*/



#endif
 