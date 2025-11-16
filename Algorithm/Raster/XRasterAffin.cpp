#include "XRaster.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XMultiEquSolve.h"
#include <float.h>

class	LineStruct : public NPList<LineStruct>
{
public:
	int	X1,Y1,X2,Y2;
	int	Index1 ,Index2;

	LineStruct(void)	{	X1=Y1=X2=Y2=Index1=Index2=0;	}
	LineStruct(int x1, int y1 ,int index1 ,int x2, int y2 ,int index2)	{	X1=x1;	Y1=y1;	X2=x2;	Y2=y2;	Index1=index1;	Index2=index2;	}

	double	GetLength(void){	return hypot(X2-X1,Y2-Y1);	}
};

RasterTriangleArea::RasterTriangleArea(void)
{
	Cax=Cay=0;
	Cbx=Cby=0;
	Ccx=Ccy=0;

	Dax=Day=0;
	Dbx=Dby=0;
	Dcx=Dcy=0;

	m[0]	=0;
	m[1]	=0;
	m[2]	=0;
	m[3]	=0;
	m[4]	=0;
	m[5]	=0;
}
void	RasterTriangleArea::GetCenter(double &Cx, double &Cy)
{
	Cx=(Cax+Cbx+Ccx)/3;
	Cy=(Cay+Cby+Ccy)/3;
}

void	RasterTriangleArea::Calc(void)
{
	XMultiEquSolve	Qx;
	XMultiEquSolve	Qy;

	Qx.AllocateMatrix(3);	//3個の変数
	Qx.SetMatrixValue(1,1,Cax);
	Qx.SetMatrixValue(2,1,Cay);
	Qx.SetMatrixValue(3,1,1.0);
	Qx.SetMatrixValue(1,2,Cbx);
	Qx.SetMatrixValue(2,2,Cby);
	Qx.SetMatrixValue(3,2,1.0);
	Qx.SetMatrixValue(1,3,Ccx);
	Qx.SetMatrixValue(2,3,Ccy);
	Qx.SetMatrixValue(3,3,1.0);
	Qx.SetMatrixValueBn(1,Cax+Dax);
	Qx.SetMatrixValueBn(2,Cbx+Dbx);
	Qx.SetMatrixValueBn(3,Ccx+Dcx);
	Qx.ExecuteGaussianElimination();	//計算開始

	Qy.AllocateMatrix(3);	//3個の変数
	Qy.SetMatrixValue(1,1,Cax);
	Qy.SetMatrixValue(2,1,Cay);
	Qy.SetMatrixValue(3,1,1.0);
	Qy.SetMatrixValue(1,2,Cbx);
	Qy.SetMatrixValue(2,2,Cby);
	Qy.SetMatrixValue(3,2,1.0);
	Qy.SetMatrixValue(1,3,Ccx);
	Qy.SetMatrixValue(2,3,Ccy);
	Qy.SetMatrixValue(3,3,1.0);
	Qy.SetMatrixValueBn(1,Cay+Day);
	Qy.SetMatrixValueBn(2,Cby+Dby);
	Qy.SetMatrixValueBn(3,Ccy+Dcy);
	Qy.ExecuteGaussianElimination();	//計算開始

	m[0]	=Qx.GetAnswer(1);	//答え
	m[1]	=Qx.GetAnswer(2);
	m[2]	=Qx.GetAnswer(3);
	m[3]	=Qy.GetAnswer(1);	//答え
	m[4]	=Qy.GetAnswer(2);
	m[5]	=Qy.GetAnswer(3);
}

bool	RasterTriangleArea::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,Cax)==false)
		return false;
	if(::Save(f,Cay)==false)
		return false;
	if(::Save(f,Cbx)==false)
		return false;
	if(::Save(f,Cby)==false)
		return false;
	if(::Save(f,Ccx)==false)
		return false;
	if(::Save(f,Ccy)==false)
		return false;

	if(::Save(f,Dax)==false)
		return false;
	if(::Save(f,Day)==false)
		return false;
	if(::Save(f,Dbx)==false)
		return false;
	if(::Save(f,Dby)==false)
		return false;
	if(::Save(f,Dcx)==false)
		return false;
	if(::Save(f,Dcy)==false)
		return false;
	if(::Save(f,m[0])==false)
		return false;
	if(::Save(f,m[1])==false)
		return false;
	if(::Save(f,m[2])==false)
		return false;
	if(::Save(f,m[3])==false)
		return false;
	if(::Save(f,m[4])==false)
		return false;
	if(::Save(f,m[5])==false)
		return false;
	return true;
}

bool	RasterTriangleArea::Load(QIODevice *f)
{
	int32	Ver=1;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,Cax)==false)
		return false;
	if(::Load(f,Cay)==false)
		return false;
	if(::Load(f,Cbx)==false)
		return false;
	if(::Load(f,Cby)==false)
		return false;
	if(::Load(f,Ccx)==false)
		return false;
	if(::Load(f,Ccy)==false)
		return false;

	if(::Load(f,Dax)==false)
		return false;
	if(::Load(f,Day)==false)
		return false;
	if(::Load(f,Dbx)==false)
		return false;
	if(::Load(f,Dby)==false)
		return false;
	if(::Load(f,Dcx)==false)
		return false;
	if(::Load(f,Dcy)==false)
		return false;
	if(::Load(f,m[0])==false)
		return false;
	if(::Load(f,m[1])==false)
		return false;
	if(::Load(f,m[2])==false)
		return false;
	if(::Load(f,m[3])==false)
		return false;
	if(::Load(f,m[4])==false)
		return false;
	if(::Load(f,m[5])==false)
		return false;
	return true;
}

void	RasterTriangleAreaContainer::BuildTriangle(int CadImagePoints[256][4] ,int PointCount)
{
	NPListPack<LineStruct>	Lines;

	//全てをつなぐ線を生成する
	for(int i=0;i<PointCount;i++){
		for(int j=i+1;j<=PointCount;j++){
			if(j!=PointCount){
				LineStruct	*L=new LineStruct(CadImagePoints[i][0],CadImagePoints[i][1],i
											, CadImagePoints[j][0],CadImagePoints[j][1],j);
				Lines.AppendList(L);
			}
			/*
			else if(i!=0){
				LineStruct	*L=new LineStruct(CadImagePoints[i][0],CadImagePoints[i][1],i
											, CadImagePoints[0][0],CadImagePoints[0][1],j);
				Lines.AppendList(L);
			}
			*/
		}
	}
	//端点以外で交差する２線分を選び、長い方を削除する
	NextP:;
	for(LineStruct *a=Lines.GetFirst();a!=NULL;a=a->GetNext()){
		for(LineStruct *b=a->GetNext();b!=NULL;b=b->GetNext()){
			double	X,Y;
			if(GetCrossInnerPointWithoutEdge(a->X1,a->Y1,a->X2,a->Y2,b->X1,b->Y1,b->X2,b->Y2, X ,Y)==true){
				if(a->GetLength()>=b->GetLength()){
					Lines.RemoveList(a);
					delete	a;
				}
				else{
					Lines.RemoveList(b);
					delete	b;
				}
				goto	NextP;
			}
		}
	}
	RemoveAll();
	for(LineStruct *a=Lines.GetFirst();a!=NULL;a=a->GetNext()){
		for(LineStruct *b=a->GetNext();b!=NULL;b=b->GetNext()){
			if((a->X1==b->X1 && a->Y1==b->Y1)
			|| (a->X1==b->X2 && a->Y1==b->Y2)
			|| (a->X2==b->X1 && a->Y2==b->Y1)
			|| (a->X2==b->X2 && a->Y2==b->Y2)){
				for(LineStruct *c=b->GetNext();c!=NULL;c=c->GetNext()){
					if((c->X1==b->X1 && c->Y1==b->Y1)
					|| (c->X1==b->X2 && c->Y1==b->Y2)
					|| (c->X2==b->X1 && c->Y2==b->Y1)
					|| (c->X2==b->X2 && c->Y2==b->Y2)){
						if((c->X1==a->X1 && c->Y1==a->Y1)
						|| (c->X1==a->X2 && c->Y1==a->Y2)
						|| (c->X2==a->X1 && c->Y2==a->Y1)
						|| (c->X2==a->X2 && c->Y2==a->Y2)){
							int		P[3][3];
							P[0][0]=a->X1;
							P[0][1]=a->Y1;
							P[0][2]=a->Index1;
							P[1][0]=a->X2;
							P[1][1]=a->Y2;
							P[1][2]=a->Index2;
							bool	Available3Points=false;
							if(a->X1!=b->X1 || a->Y1!=b->Y1){
								P[2][0]=b->X1;
								P[2][1]=b->Y1;
								P[2][2]=b->Index1;
								Available3Points=true;
							}
							else if(a->X1!=b->X2 || a->Y1!=b->Y2){
								P[2][0]=b->X2;
								P[2][1]=b->Y2;
								P[2][2]=b->Index2;
								Available3Points=true;
							}
							else if(a->X1!=c->X1 || a->Y1!=c->Y1){
								P[2][0]=c->X1;
								P[2][1]=c->Y1;
								P[2][2]=c->Index1;
								Available3Points=true;
							}
							else if(a->X1!=c->X2 || a->Y1!=c->Y2){
								P[2][0]=c->X2;
								P[2][1]=c->Y2;
								P[2][2]=c->Index2;
								Available3Points=true;
							}
							if(Available3Points==true){
								RasterTriangleArea	*Tr=new RasterTriangleArea();
								Tr->Cax=P[0][0];
								Tr->Cay=P[0][1];
								Tr->Cbx=P[1][0];
								Tr->Cby=P[1][1];
								Tr->Ccx=P[2][0];
								Tr->Ccy=P[2][1];
								Tr->Dax=CadImagePoints[P[0][2]][2] - Tr->Cax;
								Tr->Day=CadImagePoints[P[0][2]][3] - Tr->Cay;
								Tr->Dbx=CadImagePoints[P[1][2]][2] - Tr->Cbx;
								Tr->Dby=CadImagePoints[P[1][2]][3] - Tr->Cby;
								Tr->Dcx=CadImagePoints[P[2][2]][2] - Tr->Ccx;
								Tr->Dcy=CadImagePoints[P[2][2]][3] - Tr->Ccy;
								AppendList(Tr);
							}
						}
					}
				}
			}
		}
	}
	for(RasterTriangleArea *t=GetFirst();t!=NULL;t=t->GetNext()){
		t->Calc();
	}
}

RasterTriangleArea	*RasterTriangleAreaContainer::GetClosedTriangle(int x ,int y)
{
	double			MinD=DBL_MAX;
	RasterTriangleArea	*MinPoint=NULL;
	for(RasterTriangleArea *t=GetFirst();t!=NULL;t=t->GetNext()){
		double Cx, Cy;
		t->GetCenter(Cx, Cy);
		double	Len=hypot(Cx-x ,Cy-y);
		if(Len<MinD){
			MinD=Len;
			MinPoint=t;
		}
	}
	return MinPoint;
}
