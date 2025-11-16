#include "GerberFast.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
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

TriangleArea::TriangleArea(void)
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
void	TriangleArea::GetCenter(double &Cx, double &Cy)
{
	Cx=(Cax+Cbx+Ccx)/3;
	Cy=(Cay+Cby+Ccy)/3;
}

void	TriangleArea::Calc(void)
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

bool	TriangleArea::Save(QIODevice *f)
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

bool	TriangleArea::Load(QIODevice *f)
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

void	TriangleAreaContainer::BuildTriangle(int CadImagePoints[256][4] ,int PointCount)
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
								TriangleArea	*Tr=new TriangleArea();
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
	for(TriangleArea *t=GetFirst();t!=NULL;t=t->GetNext()){
		t->Calc();
	}
}

TriangleArea	*TriangleAreaContainer::GetClosedTriangle(int x ,int y)
{
	double			MinD=DBL_MAX;
	TriangleArea	*MinPoint=NULL;
	for(TriangleArea *t=GetFirst();t!=NULL;t=t->GetNext()){
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

//==========================================================================
MultiInterpolationPole::MultiInterpolationPole(double x ,double y ,double dx ,double dy ,int xn ,int yn)
	:X(x),Y(y),dX(dx),dY(dy),Xn(xn),Yn(yn)
{
	MatchingRate=0.0;
}
bool	MultiInterpolationPole::Save(QIODevice *f)
{
	if(::Save(f,X)==false)
		return false;
	if(::Save(f,Y)==false)
		return false;
	if(::Save(f,dX)==false)
		return false;
	if(::Save(f,dY)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	if(::Save(f,Xn)==false)
		return false;
	if(::Save(f,Yn)==false)
		return false;
	return true;
}
bool	MultiInterpolationPole::Load(QIODevice *f)
{
	if(::Load(f,X)==false)
		return false;
	if(::Load(f,Y)==false)
		return false;
	if(::Load(f,dX)==false)
		return false;
	if(::Load(f,dY)==false)
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;
	if(::Load(f,Xn)==false)
		return false;
	if(::Load(f,Yn)==false)
		return false;
	return true;
}

MultiInterpolation::~MultiInterpolation(void)
{
	delete	[]Dim;
	Dim=NULL;
}

MultiInterpolationPole3::MultiInterpolationPole3(void)
{
	Dim[0]=NULL;
	Dim[1]=NULL;
	Dim[2]=NULL;
	m[0]=0.0;
	m[1]=0.0;
	m[2]=0.0;
	m[3]=0.0;
	m[4]=0.0;
	m[5]=0.0;
	LoadedXn0=LoadedYn0=0;
	LoadedXn1=LoadedYn1=0;
	LoadedXn2=LoadedYn2=0;
}

bool	MultiInterpolationPole3::IsEffective(void)
{
	if(Dim[0]->X==Dim[1]->X && Dim[1]->X==Dim[2]->X)
		return false;
	if(Dim[0]->Y==Dim[1]->Y && Dim[1]->Y==Dim[2]->Y)
		return false;
	return true;
}

void	MultiInterpolationPole3::Calc(void)
{
	XMultiEquSolve	Qx;
	XMultiEquSolve	Qy;

	Qx.AllocateMatrix(3);	//3個の変数
	Qx.SetMatrixValue(1,1,Dim[0]->X);
	Qx.SetMatrixValue(2,1,Dim[0]->Y);
	Qx.SetMatrixValue(3,1,1.0);
	Qx.SetMatrixValue(1,2,Dim[1]->X);
	Qx.SetMatrixValue(2,2,Dim[1]->Y);
	Qx.SetMatrixValue(3,2,1.0);
	Qx.SetMatrixValue(1,3,Dim[2]->X);
	Qx.SetMatrixValue(2,3,Dim[2]->Y);
	Qx.SetMatrixValue(3,3,1.0);
	Qx.SetMatrixValueBn(1,Dim[0]->X+Dim[0]->dX);
	Qx.SetMatrixValueBn(2,Dim[1]->X+Dim[1]->dX);
	Qx.SetMatrixValueBn(3,Dim[2]->X+Dim[2]->dX);
	Qx.ExecuteGaussianElimination();	//計算開始

	Qy.AllocateMatrix(3);	//3個の変数
	Qy.SetMatrixValue(1,1,Dim[0]->X);
	Qy.SetMatrixValue(2,1,Dim[0]->Y);
	Qy.SetMatrixValue(3,1,1.0);
	Qy.SetMatrixValue(1,2,Dim[1]->X);
	Qy.SetMatrixValue(2,2,Dim[1]->Y);
	Qy.SetMatrixValue(3,2,1.0);
	Qy.SetMatrixValue(1,3,Dim[2]->X);
	Qy.SetMatrixValue(2,3,Dim[2]->Y);
	Qy.SetMatrixValue(3,3,1.0);
	Qy.SetMatrixValueBn(1,Dim[0]->Y+Dim[0]->dY);
	Qy.SetMatrixValueBn(2,Dim[1]->Y+Dim[1]->dY);
	Qy.SetMatrixValueBn(3,Dim[2]->Y+Dim[2]->dY);
	Qy.ExecuteGaussianElimination();	//計算開始

	m[0]	=Qx.GetAnswer(1);	//答え
	m[1]	=Qx.GetAnswer(2);
	m[2]	=Qx.GetAnswer(3);
	m[3]	=Qy.GetAnswer(1);	//答え
	m[4]	=Qy.GetAnswer(2);
	m[5]	=Qy.GetAnswer(3);
}
double	MultiInterpolationPole3::GetDistance(double x ,double y)
{
	double	L=(x-Dim[0]->X)*(x-Dim[0]->X)+(y-Dim[0]->Y)*(y-Dim[0]->Y)
			+ (x-Dim[1]->X)*(x-Dim[1]->X)+(y-Dim[1]->Y)*(y-Dim[1]->Y)
			+ (x-Dim[2]->X)*(x-Dim[2]->X)+(y-Dim[2]->Y)*(y-Dim[2]->Y);
	double	D=GetAreaDot(Dim[0]->X,Dim[0]->Y
				,  Dim[1]->X,Dim[1]->Y
				,  Dim[2]->X,Dim[2]->Y);
	if(D<=0)
		return DBL_MAX;
	return L/D;
}

bool	MultiInterpolationPole3::Save(QIODevice *f)
{
	bool	DimEffective0=(Dim[0]!=NULL)?true:false;
	bool	DimEffective1=(Dim[1]!=NULL)?true:false;
	bool	DimEffective2=(Dim[2]!=NULL)?true:false;

	if(::Save(f,DimEffective0)==false)
		return false;
	if(DimEffective0==true){
		if(::Save(f,Dim[0]->Xn)==false)
			return false;
		if(::Save(f,Dim[0]->Yn)==false)
			return false;
	}
	if(::Save(f,DimEffective1)==false)
		return false;
	if(DimEffective1==true){
		if(::Save(f,Dim[1]->Xn)==false)
			return false;
		if(::Save(f,Dim[1]->Yn)==false)
			return false;
	}
	if(::Save(f,DimEffective2)==false)
		return false;
	if(DimEffective2==true){
		if(::Save(f,Dim[2]->Xn)==false)
			return false;
		if(::Save(f,Dim[2]->Yn)==false)
			return false;
	}

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
bool	MultiInterpolationPole3::Load(QIODevice *f)
{
	bool	DimEffective0;
	bool	DimEffective1;
	bool	DimEffective2;

	if(::Load(f,DimEffective0)==false)
		return false;
	if(DimEffective0==true){
		if(::Load(f,LoadedXn0)==false)
			return false;
		if(::Load(f,LoadedYn0)==false)
			return false;
	}
	if(::Load(f,DimEffective1)==false)
		return false;
	if(DimEffective1==true){
		if(::Load(f,LoadedXn1)==false)
			return false;
		if(::Load(f,LoadedYn1)==false)
			return false;
	}
	if(::Load(f,DimEffective2)==false)
		return false;
	if(DimEffective2==true){
		if(::Load(f,LoadedXn2)==false)
			return false;
		if(::Load(f,LoadedYn2)==false)
			return false;
	}

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

void	MultiInterpolation::Add(double x ,double y ,double dx ,double dy ,int xn ,int yn)
{
	MultiInterpolationPole	*a=new MultiInterpolationPole(x,y,dx,dy ,xn ,yn);
	AppendList(a);
}
void	MultiInterpolation::Build(void)
{
	int	Numb=0;
	for(MultiInterpolationPole *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(MultiInterpolationPole *b=a->GetNext();b!=NULL;b=b->GetNext()){
			for(MultiInterpolationPole *c=b->GetNext();c!=NULL;c=c->GetNext()){
				Numb++;
			}
		}
	}
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	Dim=new MultiInterpolationPole3[Numb];

	DimNumb=0;
	for(MultiInterpolationPole *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(MultiInterpolationPole *b=a->GetNext();b!=NULL;b=b->GetNext()){
			for(MultiInterpolationPole *c=b->GetNext();c!=NULL;c=c->GetNext()){
				//Omit 3 points on one line
				double	Dx1=a->X-b->X;
				double	Dy1=a->Y-b->Y;
				double	Dx2=b->X-c->X;
				double	Dy2=b->Y-c->Y;
				double	VLen1=hypot(Dx1,Dy1);
				double	VLen2=hypot(Dx2,Dy2);
				if(VLen1<0.0001 || VLen2<0.0001)
					continue;
				double	Vx1=Dx1/VLen1;
				double	Vy1=Dy1/VLen1;
				double	Vx2=Dx2/VLen2;
				double	Vy2=Dy2/VLen2;
				if(fabs(Vx1-Vx2)<0.00001 && fabs(Vy1-Vy2)<0.00001)
					continue;
				if(fabs(Vx1+Vx2)<0.00001 && fabs(Vy1+Vy2)<0.00001)
					continue;
				if(hypot(a->Xn-b->Xn,a->Yn-b->Yn)<4
				&& hypot(a->Xn-c->Xn,a->Yn-c->Yn)<4
				&& hypot(b->Xn-c->Xn,b->Yn-c->Yn)<4){
					Dim[DimNumb].Dim[0]=a;
					Dim[DimNumb].Dim[1]=b;
					Dim[DimNumb].Dim[2]=c;
					Dim[DimNumb].Calc();
					DimNumb++;
				}
			}
		}
	}
}
bool	MultiInterpolation::Calc(double x ,double y ,double &ResultX ,double &ResultY)
{
	double	MinL=DBL_MAX;
	int		Index=-1;
	for(int i=0;i<DimNumb;i++){
		if(Dim[i].IsEffective()==true){
			double	L=Dim[i].GetDistance(x,y);
			if(MinL>L){
				MinL=L;
				Index=i;
			}
		}
	}
	if(Index<0){
		return false;
	}
	ResultX=Dim[Index].m[0]*x + Dim[Index].m[1]*y + Dim[Index].m[2];
	ResultY=Dim[Index].m[3]*x + Dim[Index].m[4]*y + Dim[Index].m[5];
	return true;
}

double	*MultiInterpolation::Calc(double x ,double y)
{
	double	MinL=DBL_MAX;
	int		Index=0;
	for(int i=0;i<DimNumb;i++){
		if(Dim[i].IsEffective()==true){
			double	L=Dim[i].GetDistance(x,y);
			if(MinL>L){
				MinL=L;
				Index=i;
			}
		}
	}
	if(Index<0){
		return NULL;
	}
	bool	FlagInside=false;
	for(int yn=0;yn<Parent->ABoxYNum;yn++){
		for(int xn=0;xn<Parent->ABoxXNum;xn++){
			if(Parent->ABox[yn][xn].IsInclude(x,y)==true){
				FlagInside=true;
				goto	InsideLabel;
			}
		}
	}
InsideLabel:;
	if(FlagInside==false){
		return NULL;
	}
	return Dim[Index].m;
}

bool	MultiInterpolation::Save(QIODevice *f)
{
	if(NPListPackSaveLoad<MultiInterpolationPole>::Save(f)==false)
		return false;

	if(::Save(f,DimNumb)==false)
		return false;
	return true;
}

bool	MultiInterpolation::Load(QIODevice *f)
{
	if(NPListPackSaveLoad<MultiInterpolationPole>::Load(f)==false)
		return false;

	if(Dim!=NULL)
		delete	[]Dim;

	if(::Load(f,DimNumb)==false)
		return false;

	Dim=new MultiInterpolationPole3[DimNumb];
	for(int i=0;i<DimNumb;i++){
		for(MultiInterpolationPole *p=GetFirst();p!=NULL;p=p->GetNext()){
			if(Dim[i].LoadedXn0==p->Xn && Dim[i].LoadedYn0==p->Yn){
				Dim[i].Dim[0]=p;
			}
			if(Dim[i].LoadedXn1==p->Xn && Dim[i].LoadedYn1==p->Yn){
				Dim[i].Dim[1]=p;
			}
			if(Dim[i].LoadedXn2==p->Xn && Dim[i].LoadedYn2==p->Yn){
				Dim[i].Dim[2]=p;
			}
		}
	}

	return true;
}
