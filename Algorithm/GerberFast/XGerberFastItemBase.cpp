#include "XGerberAperture.h"
#include "XGerberFast.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <limits.h>
#include "swap.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include <omp.h>
#include "XImageProcess.h"
#include <float.h>

extern	int	DebugDCode;
extern	int	DbgPage	;
extern	int	DCodeDebug;
extern	int	DbgID;

HairLineList::HairLineList(void)
{
	Position.x1=0;
	Position.y1=0;
	Position.x2=0;
	Position.y2=0;
	Data	=NULL;
	SubAxis	=NULL;
	DataLen=0;
	AA=0;
	A=0;
}

HairLineList::~HairLineList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
	if(SubAxis!=NULL){
		delete	[]SubAxis;
		SubAxis=NULL;
	}
	DataLen=0;
	AA=0;
	A=0;
}

HairLineList	&HairLineList::operator=(const HairLineList &src)
{
	Position=src.Position;
	return *this;
}

bool	HairLineList::EditInitialAfterEdit(GerberFastItemBase *ParentItem ,int ShiftableDot,BYTE **ImagingBmp,int XByte,int YLen,bool MasterImaged)
{
	int	dx=Position.x2-Position.x1;
	int	dy=Position.y2-Position.y1;
	A=0;
	AA=0;
	ImageBuffer *ImageList[100];

	//bool	MasterImaged=false;
	if(ParentItem->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true){
		ParentItem->GetMasterBuffList(ImageList);
		//MasterImaged=true;
	}
	int	tx1=Position.x1;
	int	ty1=Position.y1;
	int	tx2=Position.x2;
	int	ty2=Position.y2;

	ImageBuffer	&Ibuff=*ImageList[0];
	if(abs(dx)>=abs(dy)){
		if(dx<0){
			swap(tx1,tx2);
			swap(ty1,ty2);
			dx=-dx;
			dy=-dy;
		}
		if(DataLen!=dx){
			if(Data!=NULL)
				delete	[]Data;
			if(SubAxis!=NULL)
				delete	[]SubAxis;
			DataLen=dx;
			Data=new char[DataLen];
			SubAxis=new int[DataLen];
		}
		if(tx1<ShiftableDot || (ParentItem->GetDotPerLine()-ShiftableDot)<=tx2
		|| ty1<ShiftableDot || (ParentItem->GetMaxLines()  -ShiftableDot)<=ty1
		|| ty2<ShiftableDot || (ParentItem->GetMaxLines()  -ShiftableDot)<=ty2){
			GerberFastBase	*ABase=(GerberFastBase *)ParentItem->GetParentBase();
			if(-ABase->AutoMatchingMerginDot<tx1 && tx2<(ParentItem->GetDotPerLine()+ABase->AutoMatchingMerginDot)
			&& -ABase->AutoMatchingMerginDot<ty1 && ty2<(ParentItem->GetMaxLines  ()+ABase->AutoMatchingMerginDot)){
				double	M=(double)dy/(double)dx;
				for(int t=0;t<dx;t++){
					int	Y=t*M+ty1;
					SubAxis[t]=Y;
					int	c=(t<dx/2)?100:-100;
					A+=c;
					AA+=c*c;
					Data[t]=c;
				}
			}
			else{
				return false;
			}
		}
		else{
			if(MasterImaged==true){
				double	M=(double)dy/(double)dx;
				for(int t=0;t<dx;t++){
					int	Y=t*M+ty1;
					int c=(Ibuff.GetY(Y)[t+tx1]>>1);
					SubAxis[t]=Y;
					A+=c;
					AA+=c*c;
					Data[t]=c;
				}
			}
			else{
				double	M=(double)dy/(double)dx;
				for(int t=0;t<dx;t++){
					int	Y=t*M+ty1;
					int	c;
					if(GetBmpBit(ImagingBmp,t+tx1,Y)!=0){
						c=100;
					}
					else{
						c=-100;
					}
					SubAxis[t]=Y;
					A+=c;
					AA+=c*c;
					Data[t]=c;
				}
			}
		}
	}
	else{
		if(dy<0){
			swap(tx1,tx2);
			swap(ty1,ty2);
			dx=-dx;
			dy=-dy;
		}
		if(DataLen!=dy){
			if(Data!=NULL)
				delete	[]Data;
			if(SubAxis!=NULL)
				delete	[]SubAxis;
			DataLen=dy;
			Data=new char[DataLen];
			SubAxis=new int[DataLen];
		}
		if(tx1<ShiftableDot || (ParentItem->GetDotPerLine()-ShiftableDot)<=tx1
		|| tx2<ShiftableDot || (ParentItem->GetDotPerLine()-ShiftableDot)<=tx2
		|| ty1<ShiftableDot || (ParentItem->GetMaxLines()  -ShiftableDot)<=ty2){
			GerberFastBase	*ABase=(GerberFastBase *)ParentItem->GetParentBase();
			if(-ABase->AutoMatchingMerginDot<tx1 && tx2<(ParentItem->GetDotPerLine()+ABase->AutoMatchingMerginDot)
			&& -ABase->AutoMatchingMerginDot<ty1 && ty2<(ParentItem->GetMaxLines  ()+ABase->AutoMatchingMerginDot)){
				double	M=(double)dx/(double)dy;
				for(int t=0;t<dy;t++){
					int	X=t*M+tx1;
					int c=(t<dy/2)?100:-100;
					SubAxis[t]=X;
					A+=c;
					AA+=c*c;
					Data[t]=c;
				}
			}
			else{
				return false;
			}
		}
		else{
			if(MasterImaged==true){
				double	M=(double)dx/(double)dy;
				for(int t=0;t<dy;t++){
					int	X=t*M+tx1;
					int c=(Ibuff.GetY(t+ty1)[X]>>1);
					SubAxis[t]=X;
					A+=c;
					AA+=c*c;
					Data[t]=c;
				}
			}
			else{
				double	M=(double)dx/(double)dy;
				for(int t=0;t<dy;t++){
					int	X=t*M+tx1;
					int	c;
					if(GetBmpBit(ImagingBmp,X,t+ty1)!=0){
						c=100;
					}
					else{
						c=-100;
					}
					SubAxis[t]=X;
					A+=c;
					AA+=c*c;
					Data[t]=c;
				}
			}
		}
	}
	if(DataLen==0)
		return false;
	double	R=(AA-A*A/DataLen)/(double)DataLen;
	GerberFastBase	*ABase=(GerberFastBase *)ParentItem->GetParentBase();
	if(R<ABase->HairlineCoeff)
		return false;

	return true;
}
double	HairLineList::MatchExecute(GerberFastItemBase *ParentItem ,int Dx ,int Dy ,bool &Permitted)
{
	int	dx=Position.x2-Position.x1;
	int	dy=Position.y2-Position.y1;
	double	B=0;
	double	BB=0;
	double	AB=0;
	Permitted	=true;

	ImageBuffer *ImageList[100];
	//Parent->GetTargetBuffList(ImageList);
	if(ParentItem->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		ParentItem->GetTargetBuffList(ImageList);
	else
		return 0;

	GerberFastBase	*ABase=(GerberFastBase *)ParentItem->GetParentBase();
	if((Position.x1+Dx)<ABase->AutoMatchMergin || (ParentItem->GetDotPerLine()-ABase->AutoMatchMergin)<=(Position.x1+Dx)
	|| (Position.x2+Dx)<ABase->AutoMatchMergin || (ParentItem->GetDotPerLine()-ABase->AutoMatchMergin)<=(Position.x2+Dx)
	|| (Position.y1+Dy)<ABase->AutoMatchMergin || (ParentItem->GetMaxLines()-ABase->AutoMatchMergin)<=(Position.y1+Dy)
	|| (Position.y2+Dy)<ABase->AutoMatchMergin || (ParentItem->GetMaxLines()-ABase->AutoMatchMergin)<=(Position.y2+Dy)){
		return 0;
	}

	int	tx1=Position.x1;
	int	ty1=Position.y1;
	int	tx2=Position.x2;
	int	ty2=Position.y2;
	ImageBuffer	&Ibuff=*ImageList[0];

	if(abs(dx)>=abs(dy)){
		if(dx<0){
			swap(tx1,tx2);
			swap(ty1,ty2);
			dx=-dx;
			dy=-dy;
		}
		for(int t=0;t<DataLen;t++){
			int	Y=SubAxis[t];
			int c=Ibuff.GetY(Y+Dy)[t+tx1+Dx];
			B  +=c;
			BB +=c*c;
			AB +=c*Data[t];
		}
	}
	else{
		if(dy<0){
			swap(tx1,tx2);
			swap(ty1,ty2);
			dx=-dx;
			dy=-dy;
		}
		for(int t=0;t<DataLen;t++){
			int	X=SubAxis[t];
			int c=Ibuff.GetY(t+ty1+Dy)[X+Dx];
			B  +=c;
			BB +=c*c;
			AB +=c*Data[t];
		}
	}
	double	As=A/DataLen;
	double	Bs=B/DataLen;
	double	Va=(AA-As*As*DataLen);
	double	Vb=(BB-Bs*Bs*DataLen);
	double	D=Va*Vb;
	if(D<=0)
		return 0;
	
	double	R=(BB-B*B/DataLen)/(double)DataLen;
	if(R<ABase->HairlineCoeff){
		Permitted=false;
	}

	double	P=(AB-As*Bs*DataLen)/sqrt(D);

	return P*Vb/DataLen;
}

bool	HairLineList::IsOutsideFromEdge(int MinX ,int MinY ,int MaxX ,int MaxY)
{
	if(Position.x1<MinX || MaxX<=Position.x1
	|| Position.x2<MinX || MaxX<=Position.x2
	|| Position.y1<MinY || MaxY<=Position.y1
	|| Position.y2<MinY || MaxY<=Position.y2)
		return true;
	return false;
}

void	HairLineList::Draw	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Color)
{
	int	X1=(Position.x1+movx+dx)*ZoomRate;
	int	Y1=(Position.y1+movy+dy)*ZoomRate;
	int	X2=(Position.x2+movx+dx)*ZoomRate;
	int	Y2=(Position.y2+movy+dy)*ZoomRate;

	DrawLine(pnt,Color.rgba() ,X1, Y1 ,X2 ,Y2);
}

void	HairLineList::MoveToFloat(double dx, double dy)
{
	Position.x1+=dx;
	Position.y1+=dy;
	Position.x2+=dx;
	Position.y2+=dy;
}
	
void	HairLineList::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	Dx1=Position.x1-RCx;
	double	Dy1=Position.y1-RCy;
	double	Dx2=Position.x2-RCx;
	double	Dy2=Position.y2-RCy;

	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	Position.x1= Dx1*CosS+Dy1*SinS+RCx;
	Position.y1=-Dx1*SinS+Dy1*CosS+RCy;
	Position.x2= Dx2*CosS+Dy2*SinS+RCx;
	Position.y2=-Dx2*SinS+Dy2*CosS+RCy;
}
void	HairLineList::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	Position.x1=(Position.x1-RCx)*XZoomDir+RCx;
	Position.y1=(Position.y1-RCy)*YZoomDir+RCy;
	Position.x2=(Position.x2-RCx)*XZoomDir+RCx;
	Position.y2=(Position.y2-RCy)*YZoomDir+RCy;
}

void	HairLineList::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(ShearAngle);
	if(XMode==true){
		Position.x1=Position.x1+(Position.y1-RCy)*TanS;
		Position.x2=Position.x2+(Position.y2-RCy)*TanS;
	}
	else{
		Position.y1=Position.y1-(Position.x1-RCx)*TanS;
		Position.y2=Position.y2-(Position.x2-RCx)*TanS;
	}
}
void	HairLineList::Mirror(bool XMode ,double RCx ,double RCy)	
{
	if(XMode==true){
		Position.x1=-(Position.x1-RCx)+RCx;
		Position.x2=-(Position.x2-RCx)+RCx;
	}
	else{
		Position.y1=-(Position.y1-RCy)+RCy;
		Position.y2=-(Position.y2-RCy)+RCy;
	}
}
bool	HairLineList::Save(QIODevice *f)
{
	if(f->write((const char *)&Position,sizeof(Position))!=sizeof(Position))
		return false;
	return true;
}
	
bool	HairLineList::Load(QIODevice *f)
{
	if(f->read((char *)&Position,sizeof(Position))!=sizeof(Position))
		return false;
	return true;
}

double	HairLineList::GetDistance(double Cx,double Cy)
{
	return hypot(Cx-(Position.x1+Position.x2)/2.0,Cy-(Position.y1+Position.y2)/2.0);
}

void	HairLineListContainer::MoveToFloat(double dx, double dy)
{
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToFloat(dx,dy);
	}
}
	
void	HairLineListContainer::Rotate(double AngleRadian ,double RCx ,double RCy)						
{
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Rotate(AngleRadian ,RCx ,RCy);
	}
}
void	HairLineListContainer::Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Zoom( XZoomDir ,YZoomDir ,CenterX ,CenterY);
	}
}

void	HairLineListContainer::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)		
{
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Shear(XMode ,ShearAngle ,RCx ,RCy)	;
	}
}

void	HairLineListContainer::Mirror(bool XMode ,double RCx ,double RCy)
{
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Mirror(XMode ,RCx ,RCy);
	}
}

void	HairLineListContainer::Restruct(int	N)
{
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		int	AllCx=a->GetCx();
		int	AllCy=a->GetCy();
		int	MinX=a->GetCx();
		int	MinY=a->GetCy();
		int	MaxX=a->GetCx();
		int	MaxY=a->GetCy();
		int	Numb=1;
		for(HairLineList *b=GetRingNext(a);b!=a;b=GetRingNext(b)){
			if(a->GetDx()!=b->GetDx() || a->GetDy()!=b->GetDy()){
				break;
			}
			AllCx+=b->GetCx();
			AllCy+=b->GetCy();
			MinX=min(MinX,b->GetCx());
			MinY=min(MinY,b->GetCy());
			MaxX=max(MaxX,b->GetCx());
			MaxY=max(MaxY,b->GetCy());
			Numb++;
		}
		if(Numb>=N){
			//AllCx/=Numb;
			//AllCy/=Numb;
			double	Px=MaxX-MinX;
			double	Py=MaxY-MinY;
			double	L=hypot(Px,Py);
			double	Ln=L/N;
			HairLineList *H=a;
			int		HNumb=0;
			for(int i=1;i<N;i++){
				double	Kx=MinX+Px/L*Ln*i;
				double	Ky=MinY+Py/L*Ln*i;
				H->MoveToFloat(Kx-H->GetCx(),Ky-H->GetCy());
				H=GetRingNext(H);
				HNumb++;
			}
			for(int i=HNumb;i<Numb;i++){
				HairLineList *b=GetRingNext(a);
				RemoveList(b);
				delete	b;
			}
		}
	}
}
double	HairLineListContainer::GetDistance(double Cx,double Cy)
{
	double	MinD=DBL_MAX;
	for(HairLineList *a=GetFirst();a!=NULL;a=a->GetNext()){
		double	D=a->GetDistance(Cx,Cy);
		if(D<MinD)
			MinD=D;
	}
	return MinD;
}

void	OutlineArea::Draw	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Color)
{
	for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}
void	OutlineArea::MoveToFloat(double dx, double dy)
{
	HairLineContaner.MoveToFloat(dx,dy);
}
	
void	OutlineArea::Rotate(double AngleRadian ,double RCx ,double RCy)	
{
	HairLineContaner.Rotate(AngleRadian ,RCx ,RCy)	;
}

void	OutlineArea::Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	HairLineContaner.Zoom(XZoomDir ,YZoomDir ,CenterX ,CenterY);
}

void	OutlineArea::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	HairLineContaner.Shear(XMode ,ShearAngle ,RCx ,RCy);
}

void	OutlineArea::Mirror(bool XMode ,double RCx ,double RCy)
{
	HairLineContaner.Mirror(XMode ,RCx ,RCy);
}
void	OutlineArea::Restruct(int N)
{
	HairLineContaner.Restruct(N);
}

OutlineArea	&OutlineArea::operator=(FlexArea &src)
{
	FlexArea::operator=(src);
	return *this;
}
void	OutlineArea::EditInitialAfterEdit(GerberFastItemBase *ParentItem ,int ShiftableDot,BYTE **ImagingBmp,int XByte,int YLen,bool UseMasterImage)
{
	for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;){
		if(a->EditInitialAfterEdit(ParentItem,ShiftableDot,ImagingBmp,XByte,YLen,UseMasterImage)==false){
			HairLineList *A=a->GetNext();
			HairLineContaner.RemoveList(a);
			delete	a;
			a=A;
		}
		else{
			a=a->GetNext();
		}
	}
}
	
bool	OutlineArea::Save(QIODevice *f)
{
	if(FlexArea::Save(f)==false)
		return false;
	if(HairLineContaner.Save(f)==false)
		return false;
	return true;
}
	
bool	OutlineArea::Load(QIODevice *f)
{
	if(FlexArea::Load(f)==false)
		return false;
	if(HairLineContaner.Load(f)==false)
		return false;
	return true;
}

double	OutlineArea::MatchExecuteEdge(GerberFastItemBase *ParentItem ,int Dx ,int Dy,bool &Permitted
										,bool UseBrighterInPattern,bool BrighterInPattern)
{
	double	Added=0;

	if(UseBrighterInPattern==false){
		for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
			bool	TmpPermitted;
			double	D=a->MatchExecute(ParentItem ,Dx ,Dy,TmpPermitted);
			if(TmpPermitted==false){
				Permitted=false;
				return 0;
			}
			double	t=sqrt(fabs(D));
			Added+=(D>=0)?t:-t;
		}
		Permitted=true;
		return fabs(Added);
	}
	else{
		for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
			bool	TmpPermitted;
			double	D=a->MatchExecute(ParentItem ,Dx ,Dy,TmpPermitted);
			if(TmpPermitted==false){
				Permitted=false;
				return 0;
			}
			if(BrighterInPattern==true){
				if(D<0)
					D=0;
				Added+=sqrt(D);
			}
			else{
				if(D>0)
					D=0;
				Added+=sqrt(-D);
			}
		}
		Permitted=true;
		return Added;
	}
}

double	OutlineArea::MatchExecute(GerberFastItemBase *ParentItem ,int Dx ,int Dy
									,bool UseBrighterInPattern,bool BrighterInPattern)
{
	double	Added=0;
	if(UseBrighterInPattern==false){
		for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
			bool	TmpPermitted;
			double	D=a->MatchExecute(ParentItem ,Dx ,Dy,TmpPermitted);
			double	t=sqrt(fabs(D));
			Added+=(D>=0)?t:-t;
		}
		return fabs(Added);
	}
	else{
		for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
			bool	TmpPermitted;
			double	D=a->MatchExecute(ParentItem ,Dx ,Dy,TmpPermitted);
			if(BrighterInPattern==true){
				if(D<0)
					D=0;
				Added+=sqrt(D);
			}
			else{
				if(D>0)
					D=0;
				Added+=sqrt(-D);
			}
		}
		return Added;
	}
}

bool	OutlineArea::IsOutsideFromEdge(int MinX ,int MinY ,int MaxX ,int MaxY)
{
	for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOutsideFromEdge(MinX ,MinY ,MaxX ,MaxY)==true){
			return true;
		}
	}
	return false;
}

void	OutlineArea::RestructInOut(GerberFastItemBase *Item)
{
	for(HairLineList *a=HairLineContaner.GetFirst();a!=NULL;a=a->GetNext()){
		if(Item->IsInclude(a->Position.x1,a->Position.y1)==false){
			swap(a->Position.x1,a->Position.x2);
			swap(a->Position.y1,a->Position.y2);
		}
	}
}
double	OutlineArea::GetDistance(double Cx,double Cy)
{
	return HairLineContaner.GetDistance(Cx,Cy);
}

void	OutlineAreaContainer::Draw	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Color)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}

void	OutlineAreaContainer::Restruct(int N)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Restruct(N);
	}
}

void	OutlineAreaContainer::EditInitialAfterEdit(GerberFastItemBase *ParentItem ,int ShiftableDot,BYTE **ImagingBmp,int XByte,int YLen
													,bool UseMasterImage)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->EditInitialAfterEdit(ParentItem,ShiftableDot,ImagingBmp,XByte,YLen,UseMasterImage);
	}
}

double	OutlineAreaContainer::MatchExecute(GerberFastItemBase *ParentItem ,int Dx ,int Dy
										, int MinX ,int MinY ,int MaxX ,int MaxY
										,bool UseBrighterInPattern,bool BrighterInPattern)
{
	double	Added=0;
	bool	IsOutsideFromEdge=false;

	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		bool	TmpPermitted;
		if(a->IsOutsideFromEdge(MinX ,MinY ,MaxX ,MaxY)==true){
			IsOutsideFromEdge=true;
			break;
		}
	}
	if(IsOutsideFromEdge==true){
		for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
			bool	TmpPermitted;
			double	D=a->MatchExecuteEdge(ParentItem ,Dx ,Dy,TmpPermitted
										,UseBrighterInPattern,BrighterInPattern);
			if(TmpPermitted==false){
				return 0;
			}
			Added+=D;
		}
	}
	else{
		for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
			bool	TmpPermitted;
			double	D=a->MatchExecute(ParentItem ,Dx ,Dy
									,UseBrighterInPattern,BrighterInPattern);
			Added+=D;
		}
	}
	return Added;
}
void	OutlineAreaContainer::MoveToFloat(double dx, double dy)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToFloat(dx,dy);
	}
}
	
void	OutlineAreaContainer::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Rotate(AngleRadian ,RCx ,RCy);
	}
}
void	OutlineAreaContainer::Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Zoom(XZoomDir ,YZoomDir ,CenterX ,CenterY);
	}
}
void	OutlineAreaContainer::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Shear(XMode ,ShearAngle ,RCx ,RCy);
	}
}
void	OutlineAreaContainer::Mirror(bool XMode ,double RCx ,double RCy)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Mirror(XMode ,RCx ,RCy);
	}
}
void	OutlineAreaContainer::RestructInOut(GerberFastItemBase *Item)
{
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->RestructInOut(Item);
	}
}
double	OutlineAreaContainer::GetDistance(double Cx,double Cy)
{
	double	MinD=DBL_MAX;
	for(OutlineArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		double	D=a->GetDistance(Cx,Cy);
		if(D<MinD)
			MinD=D;
	}
	return MinD;
}

//======================================================================
GerberFastItemBase::GerberFastItemBase(void)
{
	pDCode		=NULL;
	pFileLayer	=NULL;
	LoadedDCode			=-1;
	LoadedFileLayerID	=-1;
	CompositeID			=-1;
	PosiImage	=true;
	Nulled		=false;
	AllocatedLibType	=-1;
	AllocatedLibID		=-1;
	AutoMatchA[0]	=1.0;
	AutoMatchA[1]	=0.0;
	AutoMatchA[2]	=0.0;
	AutoMatchA[3]	=0.0;
	AutoMatchA[4]	=1.0;
	AutoMatchA[5]	=0.0;
	Version			=GerberFastVersion;
	CurrentX1=CurrentY1=0;
	CurrentX2=CurrentY2=0;
	RelationParent	=NULL;
	RelationParentID=-1;

	DetailShiftX	=0;
	DetailShiftY	=0;
	CxBefore		=0;
	CyBefore		=0;	//Center before AutoMatch
	EnabledAutomatch=false;
}

struct	GerberFastItemSaveLoadStruct
{
	int32	DCode;
	int32	FileLayerID;

	int32	LoadedDCode;
	int32	LoadedFileLayerID;
	int32	CompositeID;

	bool	PosiImage;
	int32	AllocatedLibType;
	int32	AllocatedLibID;
	double	AutoMatchA[6];
};


bool	GerberFastItemBase::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	int32	Ver=GerberFastVersion;
	if(::Save(f,Ver)==false)
		return false;

	struct	GerberFastItemSaveLoadStruct	ItemData1;

	ItemData1.DCode				=GetDCode();
	ItemData1.FileLayerID		=GetFileLayerID();
	ItemData1.CompositeID		=CompositeID;
	ItemData1.PosiImage			=PosiImage;
	ItemData1.AllocatedLibType	=AllocatedLibType;
	ItemData1.AllocatedLibID	=AllocatedLibID;
	ItemData1.AutoMatchA[0]		=AutoMatchA[0];
	ItemData1.AutoMatchA[1]		=AutoMatchA[1];
	ItemData1.AutoMatchA[2]		=AutoMatchA[2];
	ItemData1.AutoMatchA[3]		=AutoMatchA[3];
	ItemData1.AutoMatchA[4]		=AutoMatchA[4];
	ItemData1.AutoMatchA[5]		=AutoMatchA[5];

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;

	if(TransDetail.Save(f)==false)
		return false;

	bool	B=(RelationParent!=NULL)?true:false;
	if(::Save(f,B)==false)
		return false;
	if(B==true){
		int32	ID=RelationParent->GetID();
		if(::Save(f,ID)==false)
			return false;
	}

	return true;
}


bool	GerberFastItemBase::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	Version=Ver;
	if(Version>=1){
		struct	GerberFastItemSaveLoadStruct	ItemData1;

		if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
			return false;

		LoadedDCode				=ItemData1.DCode;
		LoadedFileLayerID		=ItemData1.FileLayerID;
		CompositeID				=ItemData1.CompositeID;
		PosiImage				=ItemData1.PosiImage	;
		AllocatedLibType		=ItemData1.AllocatedLibType;
		AllocatedLibID			=ItemData1.AllocatedLibID;
		AutoMatchA[0]			=ItemData1.AutoMatchA[0];
		AutoMatchA[1]			=ItemData1.AutoMatchA[1];
		AutoMatchA[2]			=ItemData1.AutoMatchA[2];
		AutoMatchA[3]			=ItemData1.AutoMatchA[3];
		AutoMatchA[4]			=ItemData1.AutoMatchA[4];
		AutoMatchA[5]			=ItemData1.AutoMatchA[5];
	}
	if(Ver>=7){
		if(TransDetail.Load(f)==false)
			return false;
	}
	RelationParentID=-1;
	if(Ver>=8){
		bool	B;
		if(::Load(f,B)==false)
			return false;
		if(B==true){
			if(::Load(f,RelationParentID)==false)
				return false;
		}
	}
	AlgorithmInPageRoot			*p=GetParentInPage();
	if(p!=NULL){
		GerberFastInPage	*APage=dynamic_cast<GerberFastInPage *>(p);
		if(APage!=NULL){
			GerberFileLayer		*g=APage->FindFileLayer(GetLoadedFileLayerID());
			if(g!=NULL){
				SetFileLayer(g);
				GerberDCodeBase	*dcode=g->FindDCode(GetLoadedDCode());
				if(dcode!=NULL){
					SetDCode(dcode);
				}
			}
		}
	}
	return true;
}

bool	GerberFastItemBase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	double	DX1,DY1,DX2,DY2;
	if(GetXY(DX1,DY1,DX2,DY2)==false){
		return false;
	}
	x1=floor(DX1);
	y1=floor(DY1);
	x2=ceil(DX2);
	y2=ceil(DY2);
	return true;
}

void	GerberFastItemBase::SetDCode(GerberDCodeBase *d)
{	
	pDCode=d;
	if(d!=NULL){
		LoadedDCode=d->DCode;
	}
}
void	GerberFastItemBase::SetFileLayer(GerberFileLayer *L)
{	
	pFileLayer=L;
	LoadedFileLayerID=L->FileLayerID;
}


bool	GerberFastItemBase::BuildPointer(GerberFileLayerContainer &FileLayerList)
{
	if(GetID()==DebugDCode && GetPage()==DbgPage)
		DCodeDebug++;
	GerberFileLayer	*f=FileLayerList.Find(LoadedFileLayerID);
	if(f==NULL)
		return false;
	pFileLayer	=f;

	if(LoadedDCode==-1)
		return true;
	GerberDCodeBase	*d=f->FindDCode(LoadedDCode);
	if(d==NULL)
		return false;
	pDCode=d;
	return true;
}

QColor	GerberFastItemBase::GetColor(AlgorithmDrawAttr *Attr)
{
	if(GetSelected()==true){
		return Attr->SelectedColor;
	}
	else if(GetActive()==true){
		return Attr->ActiveColor;
	}
	else{
		//GerberFastInPage	*P=(GerberFastInPage*)GetParentInPage();
		//int	Number=P->GetOwnOrder(GetFileLayerID());
		//GerberFastBase		*GBase=(GerberFastBase *)GetParentBase();
		//return GBase->GetLayerColor(Number);
		int	Number=GetFileLayerID();
		if(Number>=0){
			GerberFastDrawAttr	*a=(GerberFastDrawAttr *)Attr;
			return a->LayerColor[Number%MaxGerberLayer];
		}
		Number=GetCompositeID();
		if(Number>=0){
			GerberFastDrawAttr	*a=(GerberFastDrawAttr *)Attr;
			return a->CompColor[Number%MaxGerberLayer];
		}
		return Qt::darkGray;
	}
}

void	GerberFastItemBase::MakeConnection(GerberFastItemPointerContainer &AllItems)
{
	for(GerberFastItemPointer *p=AllItems.PointerList.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetPoint()==this)
			continue;
		if(IsConnected(p->GetPoint())==true){
			ConnectedItems.AppendList(new GerberFastItemBasePointerList(p->GetPoint()));
		}
	}
}

void	GerberFastItemBase::SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src ,OffsetX ,OffsetY);
	GerberFastItemBase	*s=dynamic_cast<GerberFastItemBase *>(src);
	if(s!=NULL){
		GerberFastInPage	*PPage=(GerberFastInPage *)GetParent();
		if(PPage!=NULL){
			PageInfoForParts	*PInfo=PPage->GetPartsInfo(GetPartsID());
			if(PInfo!=NULL){
				pFileLayer		=PInfo->FileLayerList.Find(s->pFileLayer->GetFileLayerID());
				if(s->pDCode!=NULL)
					pDCode		=pFileLayer->FindDCode(s->pDCode->GetDCode());
				else
					pDCode		=NULL;
			}
		}
		LoadedDCode			=s->LoadedDCode;
		LoadedFileLayerID	=s->LoadedFileLayerID;
		CompositeID			=s->CompositeID;
		Version				=s->Version;

		CurrentX1	=s->CurrentX1+OffsetX;
		CurrentY1	=s->CurrentY1+OffsetY;
		CurrentX2	=s->CurrentX2+OffsetX;
		CurrentY2	=s->CurrentY2+OffsetY;
	}
	SetSelected(true);
	//MoveTo(OffsetX ,OffsetY);
}
void	GerberFastItemBase::CopyFrom(AlgorithmItemRoot *src)
{
	AlgorithmItemPI::CopyFrom(src);

	GerberFastItemBase	*s=dynamic_cast<GerberFastItemBase *>(src);
	pDCode			=s->pDCode;
	pFileLayer		=s->pFileLayer;

	LoadedDCode		=s->LoadedDCode;
	LoadedFileLayerID	=s->LoadedFileLayerID;
	CompositeID			=s->CompositeID;

	PosiImage			=s->PosiImage;
	AllocatedLibType	=s->AllocatedLibType;
	AllocatedLibID		=s->AllocatedLibID;
	AutoMatchA[0]		=s->AutoMatchA[0];
	AutoMatchA[1]		=s->AutoMatchA[1];
	AutoMatchA[2]		=s->AutoMatchA[2];
	AutoMatchA[3]		=s->AutoMatchA[3];
	AutoMatchA[4]		=s->AutoMatchA[4];
	AutoMatchA[5]		=s->AutoMatchA[5];
}

int	GerberFastItemBase::SplitHorizontalCut(GerberFastItemBase *Obj[1000],int MaxCount)
{
	double x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==false)
		return false;

	int	gx1=x1-4;
	int	gy1=y1-4;
	int	gx2=x2+4;
	int	gy2=y2+4;
	int	XByte=(gx2-gx1+7)/8;
	int	XLen=gx2-gx1;
	int	YLen=gy2-gy1;
	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	int	Overlap=ABase->OverlapPixelToCutBigArea/2;

	BYTE	**BmpMap	=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpMap2	=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear	(BmpMap,0,XByte,YLen);

	bool	PosiImage=GetPosiImage();
	SetPosiImage(true);
	MakeImage(BmpMap,-gx1 ,-gy1,XByte ,YLen);
	SetPosiImage(PosiImage);

	MatrixBuffCopy	(BmpMap2,XByte,YLen
					,(const BYTE **)BmpMap ,XByte,YLen);

	PureFlexAreaListContainer FPackR;
	PureFlexAreaListContainer FPackL;

	//#pragma omp parallel
	//{
	//	#pragma omp sections
	//	{
	//		#pragma omp section
	//		{
				for(int y=0;y<YLen;y++){
					BYTE	*d=BmpMap[y];
					SetBitLine0(d,0,XLen/2-Overlap);
				}
				PickupFlexArea(BmpMap ,XByte ,XLen,YLen ,FPackR);
	//		}
	//		#pragma omp section
	//		{
				for(int y=0;y<YLen;y++){
					BYTE	*d=BmpMap2[y];
					SetBitLine0(d,XLen/2+Overlap,XLen-1);
				}
				PickupFlexArea(BmpMap2,XByte ,XLen,YLen ,FPackL);
	//		}
	//	}
	//}

	DeleteMatrixBuff(BmpMap ,YLen);
	DeleteMatrixBuff(BmpMap2,YLen);

	int	ObjNumb=0;
	if(FPackR.GetCount()!=1 || FPackL.GetCount()!=1){
		for(PureFlexAreaList *r=FPackR.GetFirst();r!=NULL;r=r->GetNext()){
			XYClassCluster aXY;
			r->MakeOutlineDot(aXY);
			XYClassArea	*R=aXY.GetFirst();
			if(R!=NULL){
				R->Simplize();
				int	Numb=R->GetCount();
				if(ObjNumb>=MaxCount)
					return ObjNumb;
				if(Numb>0){
					GerberFastItemPolygon	*p=MakePolygon(gx1,gy1,Numb,R);
					Obj[ObjNumb]=p;
					ObjNumb++;
				}
			}
		}
		for(PureFlexAreaList *r=FPackL.GetFirst();r!=NULL;r=r->GetNext()){
			XYClassCluster aXY;
			r->MakeOutlineDot(aXY);
			XYClassArea	*R=aXY.GetFirst();
			if(R!=NULL){
				R->Simplize();
				int	Numb=R->GetCount();
				if(ObjNumb>=MaxCount)
					return ObjNumb;
				if(Numb>0){
					GerberFastItemPolygon	*p=MakePolygon(gx1,gy1,Numb,R);
					Obj[ObjNumb]=p;
					ObjNumb++;
				}
			}
		}

		return ObjNumb;
	}

	XYClassCluster XYR;
	XYClassCluster XYL;
	XYClassArea	*R=NULL;
	XYClassArea	*L=NULL;
	int	NumbR=0;
	int	NumbL=0;
	GerberFastItemPolygon	*ItemR=NULL;
	GerberFastItemPolygon	*ItemL=NULL;
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				FPackR.GetFirst()->MakeOutlineDot(XYR);
				R=XYR.GetFirst();
				if(R!=NULL){
					R->Simplize();
					NumbR=R->GetCount();
					ItemR=MakePolygon(gx1,gy1,NumbR,R);
				}
			}
			#pragma omp section
			{
				FPackL.GetFirst()->MakeOutlineDot(XYL);
				L=XYL.GetFirst();
				if(L!=NULL){
					L->Simplize();
					NumbL=L->GetCount();
					ItemL=MakePolygon(gx1,gy1,NumbL,L);
				}
			}
		}
	}	

	if(R!=NULL){
		if(ObjNumb>=MaxCount)
			return ObjNumb;
		if(NumbR>0){
			Obj[ObjNumb]=ItemR;
			ObjNumb++;
		}
	}
	if(L!=NULL){
		if(ObjNumb>=MaxCount)
			return ObjNumb;
		if(NumbL>0){
			Obj[ObjNumb]=ItemL;
			ObjNumb++;
		}
	}
	return ObjNumb;
}

GerberFastItemPolygon	*GerberFastItemBase::MakePolygon(int gx ,int gy ,int Numb,XYClassArea *R)
{
	GerberFastItemPolygon	*ItemR=new GerberFastItemPolygon();
	GerberFastItemPolygon::PointStruct	*PointR=new GerberFastItemPolygon::PointStruct[Numb];
	int	n;
	n=0;
	XYClass	*a=R->GetFirstDot();
	int	LastX=gx+a->x;
	int	LastY=gy+a->y;
	for(a=a->GetNext();a!=NULL;a=a->GetNext(),n++){
		PointR[n].Data.PointType	=GerberFastItemPolygon::PointStruct::_Line;
		PointR[n].Data.LastX		=LastX;
		PointR[n].Data.LastY		=LastY;
		PointR[n].Data.PosX			=gx+a->x;
		PointR[n].Data.PosY			=gy+a->y;
		PointR[n].Data.CenterX		=0;
		PointR[n].Data.CenterY		=0;
		PointR[n].Data.RadiusX		=0;
		PointR[n].Data.RadiusY		=0;
		PointR[n].Data.Rotation		=0;
		PointR[n].Data.StartAngle	=0;
		PointR[n].Data.EndAngle		=0;
		LastX						=gx+a->x;
		LastY						=gy+a->y;
	}
	ItemR->SetFileLayer(GetFileLayer());
	ItemR->PosiImage	=PosiImage;
	ItemR->OrgPoints=new GerberFastItemPolygon::PointStruct[n];
	for(int i=0;i<n;i++){
		ItemR->OrgPoints[i]	=PointR[i];
	}
	ItemR->OrgPosCount=n;
	ItemR->InitialFromOrg();
	delete	[]PointR;
	ItemR->SetCurrentSize();
	return ItemR;
}

void	SaveText(int n ,FlexArea *a)
{
	QString	FileName=QString("TestSampleArea")+QString::number(n)+QString(".tst");
	QFile	File(FileName);
	File.open(QIODevice::WriteOnly);
	a->Save(&File);

}

int	GerberFastItemBase::SplitVerticalCut(GerberFastItemBase *Obj[1000],int MaxCount)
{
	double x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==false)
		return false;

	int	gx1=x1-4;
	int	gy1=y1-4;
	int	gx2=x2+4;
	int	gy2=y2+4;
	int	XByte=(gx2-gx1+7)/8;
	int	XLen=gx2-gx1;
	int	YLen=gy2-gy1;

	if(XLen>GetDotPerLine()*3 || YLen>GetMaxLines()*3)
		return 0;

	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	int	Overlap=ABase->OverlapPixelToCutBigArea/2;

	BYTE	**BmpMap	=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpMap2	=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear	(BmpMap,0,XByte,YLen);
	
	bool	PosiImage=GetPosiImage();
	SetPosiImage(true);	
	MakeImage(BmpMap,-gx1 ,-gy1,XByte ,YLen);
	SetPosiImage(PosiImage);

	int	DivNumb=ceil((double)YLen/(double)(ABase->TooBigSizeForCut-ABase->OverlapPixelToCutBigArea));
	int	DivYLen=ceil((double)YLen/(double)DivNumb);
	BYTE	**BmpPoint;
	BmpPoint=new BYTE *[YLen];
	int	ObjNumb=0;
	for(int h=0;h<DivNumb;h++){
		//MatrixBuffCopy	(BmpMap2,XByte,YLen
		//				,(const BYTE **)BmpMap ,XByte,YLen);

		int	StartY=DivYLen*h-Overlap;
		int	EndY  =StartY+DivYLen+Overlap;
		if(StartY<0)
			StartY=0;
		if(EndY>YLen)
			EndY=YLen;
		int	t=0;
		for(int y=StartY;y<EndY;y++,t++){
			BmpPoint[t]=BmpMap[y];
		}
		int	tYLen=EndY-StartY;
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte ,XLen,tYLen,FPack);

		for(PureFlexAreaList *r=FPack.GetFirst();r!=NULL;r=r->GetNext()){
			XYClassCluster aXY;
			r->MakeOutlineDot(aXY);
			XYClassArea	*R=aXY.GetFirst();
			if(R!=NULL){
				R->Simplize();
				int	Numb=R->GetCount();
				if(ObjNumb>=MaxCount)
					return ObjNumb;
				if(Numb>0){
					GerberFastItemPolygon	*p=MakePolygon(gx1,gy1+StartY,Numb,R);
					p->SetCurrentSize();
					Obj[ObjNumb]=p;
					ObjNumb++;

				}
			}
		}
	}
	delete	[]BmpPoint;
	DeleteMatrixBuff(BmpMap ,YLen);
	DeleteMatrixBuff(BmpMap2,YLen);

	return ObjNumb;
}

int	GerberFastItemBase::GetFileLayerID(void)
{	
	if(pFileLayer!=NULL){
		return pFileLayer->FileLayerID;	
	}
	return CompositeID;
}
bool	GerberFastItemBase::GetCenter(int &cx ,int &cy)	const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==true){
		cx=(x1+x2)/2;
		cy=(y1+y2)/2;
		return true;
	}
	return false;
}

bool	GerberFastItemBase::GetCenter(double &cx ,double &cy)	const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==true){
		cx=(x1+x2)/2;
		cy=(y1+y2)/2;
		return true;
	}
	return false;
}

bool	GerberFastItemBase::IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
									,int &x1 ,int &y1 ,int&x2 ,int &y2)
{
	x1=(CurrentX1+movx)*ZoomRate;
	y1=(CurrentY1+movy)*ZoomRate;
	x2=(CurrentX2+movx)*ZoomRate;
	y2=(CurrentY2+movy)*ZoomRate;
	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;
	return true;
}
bool	GerberFastItemBase::IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double AngleRadian ,double RCx ,double RCy)
{
	double	Dx1=CurrentX1-RCx;
	double	Dy1=CurrentY1-RCy;
	double	Dx2=CurrentX2-RCx;
	double	Dy2=CurrentY2-RCy;
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);
	double	tPosX1= Dx1*CosS + Dy1*SinS + RCx;
	double	tPosY1=-Dx1*SinS + Dy1*CosS + RCy;
	double	tPosX2= Dx2*CosS + Dy2*SinS + RCx;
	double	tPosY2=-Dx2*SinS + Dy2*CosS + RCy;

	int	tx1=(tPosX1+movx)*ZoomRate;
	int	ty1=(tPosY1+movy)*ZoomRate;
	int	tx2=(tPosX2+movx)*ZoomRate;
	int	ty2=(tPosY2+movy)*ZoomRate;
	x1=min(tx1,tx2);
	y1=min(ty1,ty2);
	x2=max(tx1,tx2);
	y2=max(ty1,ty2);

	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;
	return true;
}

bool	GerberFastItemBase::IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	double	Dx1=CurrentX1-CenterX;
	double	Dy1=CurrentY1-CenterY;
	double	Dx2=CurrentX2-CenterX;
	double	Dy2=CurrentY2-CenterY;
	double	tPosX1= Dx1*XZoomDir + CenterX;
	double	tPosY1= Dy1*YZoomDir + CenterY;
	double	tPosX2= Dx2*XZoomDir + CenterX;
	double	tPosY2= Dy2*YZoomDir + CenterY;

	int	tx1=(tPosX1+movx)*ZoomRate;
	int	ty1=(tPosY1+movy)*ZoomRate;
	int	tx2=(tPosX2+movx)*ZoomRate;
	int	ty2=(tPosY2+movy)*ZoomRate;
	x1=min(tx1,tx2);
	y1=min(ty1,ty2);
	x2=max(tx1,tx2);
	y2=max(ty1,ty2);
	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;
	return true;
}

bool	GerberFastItemBase::IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(ShearAngle);
	double	Dx1=CurrentX1-RCx;
	double	Dy1=CurrentY1-RCy;
	double	Dx2=CurrentX2-RCx;
	double	Dy2=CurrentY2-RCy;
	if(XMode==true){
		double	tPosX1=CurrentX1-Dy1*TanS;
		double	tPosY1=CurrentY1;
		double	tPosX2=CurrentX2-Dy2*TanS;
		double	tPosY2=CurrentY2;	
		int	tx1=(tPosX1+movx)*ZoomRate;
		int	ty1=(tPosY1+movy)*ZoomRate;
		int	tx2=(tPosX2+movx)*ZoomRate;
		int	ty2=(tPosY2+movy)*ZoomRate;
		x1=min(tx1,tx2);
		y1=min(ty1,ty2);
		x2=max(tx1,tx2);
		y2=max(ty1,ty2);
	}
	else{
		double	tPosX1=CurrentX1;
		double	tPosY1=CurrentY1+Dx1*TanS;
		double	tPosX2=CurrentX2;
		double	tPosY2=CurrentY2+Dx2*TanS;
		int	tx1=(tPosX1+movx)*ZoomRate;
		int	ty1=(tPosY1+movy)*ZoomRate;
		int	tx2=(tPosX2+movx)*ZoomRate;
		int	ty2=(tPosY2+movy)*ZoomRate;
		x1=min(tx1,tx2);
		y1=min(ty1,ty2);
		x2=max(tx1,tx2);
		y2=max(ty1,ty2);
	}
	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;

	return true;
}

void	GerberFastItemBase::MoveToFloat(double dx, double dy)
{
	TransDetail.MoveToFloat(dx,dy);
}
	
void	GerberFastItemBase::Rotate(double AngleRadian ,double RCx ,double RCy)			
{
	TransDetail.Rotate(AngleRadian ,RCx ,RCy)	;
}

void	GerberFastItemBase::Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	TransDetail.Zoom(XZoomDir ,YZoomDir ,CenterX ,CenterY);
}

void	GerberFastItemBase::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	TransDetail.Shear(XMode ,ShearAngle ,RCx ,RCy);
}

void	GerberFastItemBase::Mirror(bool XMode ,double RCx ,double RCy)
{
	TransDetail.Mirror(XMode ,RCx ,RCy);
}

bool	GerberFastItemBase::DrawSimple(QImage &pnt, int &x1 ,int &y1 ,int &x2 ,int &y2 ,int ImageWidth ,int ImageHeight ,QRgb col)
{
	int	dx=x2-x1;
	int	dy=y2-y1;
	if(dx==0 || dy==0)
		DrawLine(pnt,col ,x1, y1 ,x2 ,y2);
	else if(dy==1){
		DrawLine(pnt,col ,x1, y1 ,x2 ,y1);
		DrawLine(pnt,col ,x1, y2 ,x2 ,y2);
	}
	else if(dx==1){
		DrawLine(pnt,col ,x1, y1 ,x1 ,y2);
		DrawLine(pnt,col ,x2, y1 ,x2 ,y2);
	}
	else if(dy==2){
		DrawLine(pnt,col ,x1, y1   ,x2 ,y1  );
		DrawLine(pnt,col ,x1, y1+1 ,x2 ,y1+1);
		DrawLine(pnt,col ,x1, y2   ,x2 ,y2  );
	}
	else if(dx==2){
		DrawLine(pnt,col ,x1  , y1 ,x1   ,y2);
		DrawLine(pnt,col ,x1+1, y1 ,x1+1 ,y2);
		DrawLine(pnt,col ,x2  , y1 ,x2   ,y2);

	}
	else{
		return false;
	}
	return true;
}
void	GerberFastItemBase::SetCurrentSize(void)
{
	GetXY(CurrentX1,CurrentY1,CurrentX2,CurrentY2);
}

void	GerberFastItemBase::ClipPage(void)
{
	ClipPage(GetDotPerLine(),GetMaxLines());
}

void	GerberFastItemBase::MoveTo(int dx ,int dy)
{
	MoveToFloat(dx, dy);
	MakeXY();
	SetCurrentSize();
}
void	GerberFastItemBase::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	Rotate(2*M_PI*AngleDegree/360.0,Cx,Cy);
	MakeXY();
	SetCurrentSize();
}

void	GerberFastItemBase::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	if(MirrorMode==AlgorithmItemRoot::_XMirror){
		Mirror(true ,PointX,PointY);
		MakeXY();
		SetCurrentSize();
	}
}
void	GerberFastItemBase::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	MoveTo(GlobalDx,GlobalDy);
}
void	GerberFastItemBase::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	int	GloalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	if(PageList.IsInclude(GloalPage)==false){
		PageList.Add(GloalPage);
	}
}
ExeResult	GerberFastItemBase::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	MakeXY();
	SetCurrentSize();

	return Ret;
}
void	GerberFastItemBase::SetAutoMatchingM(double *m)
{
	AutoMatchA[0]=m[0];
	AutoMatchA[1]=m[1];
	AutoMatchA[2]=m[2];
	AutoMatchA[3]=m[3];
	AutoMatchA[4]=m[4];
	AutoMatchA[5]=m[5];
}

void	DrawPoly(QImage &pnt,QRgb &Col,XYDoubleClass *D ,int N)
{

}

void	DrawRectangle(QImage &pnt,QRgb &Col,XYDoubleClass D[4])
{
	int	TopY=min(min(D[0].y,D[1].y),min(D[2].y,D[3].y));
	int	BotY=max(max(D[0].y,D[1].y),max(D[2].y,D[3].y));
	if(TopY>pnt.height() || BotY<0){
		return;
	}

	int	LeftX	=min(min(D[0].x,D[1].x),min(D[2].x,D[3].x));
	int	RightX	=max(max(D[0].x,D[1].x),max(D[2].x,D[3].x));
	if(LeftX>pnt.width() || RightX<0){
		return;
	}

	int	YNumb=BotY-TopY+1;
	if(YNumb<8){
		//#pragma omp parallel
		//{
		//	#pragma omp for
			for(int t=0;t<YNumb;t++){
				int	y=t+TopY;
				if(0<=y && y<pnt.height()){
					double	X[4];
					int	N=0;
					if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,y,X[N])==true)
						N++;
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						if(MinX>X[i])
							MinX=X[i];
						if(MaxX<X[i])
							MaxX=X[i];
					}
					int	X1=max(MinX,0.0);
					int	X2=min(ceil(MaxX),(double)pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(y);
						if(pnt.depth()==32){
							BYTE	*ds=&d[X1<<2];
							for(int X=X1;X<=X2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*((QRgb *)ds)=Col;
								ds+=4;
							}
						}	
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		//}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for
			for(int t=0;t<YNumb;t++){
				int	y=t+TopY;
				if(0<=y && y<pnt.height()){
					double	X[4];
					int	N=0;
					if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,y,X[N])==true)
						N++;
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						if(MinX>X[i])
							MinX=X[i];
						if(MaxX<X[i])
							MaxX=X[i];
					}
					int	X1=max(MinX,0.0);
					int	X2=min(ceil(MaxX),(double)pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(y);
						if(pnt.depth()==32){
							BYTE	*ds=&d[X1<<2];
							for(int X=X1;X<=X2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*((QRgb *)ds)=Col;
								ds+=4;
							}
						}	
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}

void	MakeImageRectangle(BYTE **Image ,int XByte ,int YLen ,XYDoubleClass D[4]
						  ,bool PosiImage)
{
	int	TopY=min(min(D[0].y,D[1].y),min(D[2].y,D[3].y));
	int	BotY=max(max(D[0].y,D[1].y),max(D[2].y,D[3].y));
	if(TopY>=YLen || BotY<0){
		return;
	}

	int	XLen=XByte<<3;
	int	LeftX	=min(min(D[0].x,D[1].x),min(D[2].x,D[3].x));
	int	RightX	=max(max(D[0].x,D[1].x),max(D[2].x,D[3].x));
	if(LeftX>=XLen || RightX<0){
		return;
	}

	int	NLen=BotY-TopY+1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int t=0;t<NLen;t++){
			int	y=TopY+t;
		//for(int y=TopY;y<=BotY;y++){
			if(0<=y && y<YLen){
				double	X[4];
				int	N=0;
				if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,y,X[N])==true)
					N++;
				if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,y,X[N])==true)
					N++;
				if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,y,X[N])==true)
					N++;
				if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,y,X[N])==true)
					N++;
				if(N==0)
					continue;
				double	MinX=X[0];
				double	MaxX=X[0];
				for(int i=1;i<N;i++){
					if(MinX>X[i])
						MinX=X[i];
					if(MaxX<X[i])
						MaxX=X[i];
				}
				int	X1=max(floor(MinX),0.0);
				int	X2=min((int)ceil(MaxX),(int)XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
		}
	}
}
bool	IsInclude(XYDoubleClass D[4] ,FlexArea *b)
{
	int	TopY=min(min(D[0].y,D[1].y),min(D[2].y,D[3].y));
	int	BotY=max(max(D[0].y,D[1].y),max(D[2].y,D[3].y));
	int	LeftX	=min(min(D[0].x,D[1].x),min(D[2].x,D[3].x));
	int	RightX	=max(max(D[0].x,D[1].x),max(D[2].x,D[3].x));

	if(::CheckOverlapRectRect(b->GetMinX(),b->GetMinY(),b->GetMaxX(),b->GetMaxY()
							,LeftX,TopY,RightX,BotY)==false)
		return false;


	for(int i=0;i<b->GetFLineLen();i++){
		int	Y=b->GetFLineAbsY(i);
		double	X[4];
		int	N=0;
		if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,Y,X[N])==true)
			N++;
		if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,Y,X[N])==true)
			N++;
		if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,Y,X[N])==true)
			N++;
		if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,Y,X[N])==true)
			N++;
		if(N==0)
			continue;
		double	MinX=X[0];
		double	MaxX=X[0];
		for(int j=1;j<N;j++){
			if(MinX>X[j])
				MinX=X[j];
			if(MaxX<X[j])
				MaxX=X[j];
		}
		int	X1=b->GetFLineLeftX(i);
		int	X2=X1+b->GetFLineNumb(i);
		if((MinX<=X1 && X1<=MaxX) || (MinX<=X2 && X2<=MaxX)
		|| (X1<=MinX && MinX<=X2) || (X1<=MaxX && MaxX<=X2)){
			return true;
		}
	}
	return false;
}

static	int	FuncDouble(const void *a ,const void *b)
{
	double	*dba=(double *)a;
	double	*dbb=(double *)b;
	if(*dba<*dbb)
		return -1;
	if(*dba>*dbb)
		return 1;
	return 0;
}

void	DrawArc(QImage &pnt,QRgb &Col
				,double CenterX,double CenterY,double Radius,double StartAngle,double EndAngle
				,double D)
{
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>=pnt.height() || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>=pnt.width() || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	double	Sx1=R1*cos(StartAngle);
	double	Sy1=R1*sin(StartAngle);
	double	Sx2=R2*cos(StartAngle);
	double	Sy2=R2*sin(StartAngle);

	double	Ex1=R1*cos(EndAngle);
	double	Ey1=R1*sin(EndAngle);
	double	Ex2=R2*cos(EndAngle);
	double	Ey2=R2*sin(EndAngle);

	int	YNumb=Ri1*2+1;
	//#pragma omp parallel
	//{
	//	#pragma omp for
		//for(int y=-Ri1;y<=Ri1;y++){
		for(int t=0;t<YNumb;t++){
			int	y=t-Ri1;
			int	Y=y+CenterY;
			if(0<=Y && Y<pnt.height()){
				double	m1=sqrt(R1*R1-y*y);
				if(R2-abs(y)<0){
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(X1<=X2){
								BYTE	*d=pnt.scanLine(Y);
								if(pnt.depth()==32){
									for(int X=X1;X<=X2;X++){
										*((QRgb *)&d[X<<2])=Col;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
				}
				else{
					double	m2=sqrt(R2*R2-y*y);
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					L[N]=-m2;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(X1<=X2){
								BYTE	*d=pnt.scanLine(Y);
								if(pnt.depth()==32){
									for(int X=X1;X<=X2;X++){
										*((QRgb *)&d[X<<2])=Col;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
					L[0]=m2;
					N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(X1<=X2){
								BYTE	*d=pnt.scanLine(Y);
								if(pnt.depth()==32){
									for(int X=X1;X<=X2;X++){
										*((QRgb *)&d[X<<2])=Col;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
				}
			}
		}
	//}
}
void	MakeImageArc(BYTE **Image ,int XByte ,int YLen
				,double CenterX,double CenterY,double Radius,double StartAngle,double EndAngle
				,double D
				,bool PosiImage)
{
	int	XLen=XByte<<3;
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>=YLen || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>=XLen || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	double	Sx1=R1*cos(StartAngle);
	double	Sy1=R1*sin(StartAngle);
	double	Sx2=R2*cos(StartAngle);
	double	Sy2=R2*sin(StartAngle);

	double	Ex1=R1*cos(EndAngle);
	double	Ey1=R1*sin(EndAngle);
	double	Ex2=R2*cos(EndAngle);
	double	Ey2=R2*sin(EndAngle);

	int	NLen=Ri1*2+1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int t=0;t<NLen;t++){
		//for(int y=-Ri1;y<=Ri1;y++){
			int	y=-Ri1+t;
			int	Y=y+CenterY;
			if(0<=Y && Y<YLen){
				double	m1=sqrt(R1*R1-y*y);
				if(R2-abs(y)<0){
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,XLen-1);
							if(X1<=X2){
								BYTE	*d=Image[Y];
								if(PosiImage==true){
									SetBitLine1(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY1(d,X);
									//}
								}
								else{
									SetBitLine0(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY0(d,X);
									//}
								}
							}
						}
					}
				}
				else{
					double	m2=sqrt(R2*R2-y*y);
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					L[N]=-m2;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,XLen-1);
							if(X1<=X2){
								BYTE	*d=Image[Y];
								if(PosiImage==true){
									SetBitLine1(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY1(d,X);
									//}
								}
								else{
									SetBitLine0(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY0(d,X);
									//}
								}
							}
						}
					}
					L[0]=m2;
					N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,XLen-1);
							if(X1<=X2){
								BYTE	*d=Image[Y];
								if(PosiImage==true){
									SetBitLine1(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY1(d,X);
									//}
								}
								else{
									SetBitLine0(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY0(d,X);
									//}
								}
							}
						}
					}
				}
			}
		}
	}
}

void	DrawDonut(QImage &pnt,QRgb &Col
				,double CenterX,double CenterY,double Radius
				,double D)
{
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>pnt.height() || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>pnt.width() || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	int	YNumb=Ri1*2+1;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int y=-Ri1;y<=Ri1;y++){
		for(int t=0;t<YNumb;t++){
			int	y=t-Ri1;
			int	Y=y+CenterY;
			if(0<=Y && Y<pnt.height()){
				double	m1=sqrt(R1*R1-y*y);
				if(R2-abs(y)<0){
					int	X1=CenterX-m1;
					int	X2=CenterX+m1;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
				else{
					double	m2=sqrt(R2*R2-y*y);
					int	X1=CenterX-m1;
					int	X2=CenterX-m2;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					X1=CenterX+m2;
					X2=CenterX+m1;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}
void	MakeImageDonut(BYTE **Image ,int XByte ,int YLen
				,double CenterX,double CenterY,double Radius
				,double D
				,bool PosiImage)
{
	int	XLen=XByte<<3;
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>YLen || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>XLen || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	for(int y=-Ri1;y<=Ri1;y++){
		int	Y=y+CenterY;
		if(0<=Y && Y<YLen){
			double	m1=sqrt(R1*R1-y*y);
			if(R2-abs(y)<0){
				int	X1=CenterX-m1;
				int	X2=CenterX+m1;
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[Y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
			else{
				double	m2=sqrt(R2*R2-y*y);
				int	X1=CenterX-m1;
				int	X2=CenterX-m2;
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[Y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
				X1=CenterX+m2;
				X2=CenterX+m1;
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[Y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
		}
	}
}

int		GerberFastItemBase::GetCrossedCount(OutlineAreaContainer &SrcOutline)
{
	int	Count=0;
	for(OutlineArea *OL=SrcOutline.GetFirst();OL!=NULL;OL=OL->GetNext()){
		for(HairLineList *L=OL->HairLineContaner.GetFirst();L!=NULL;L=L->GetNext()){
			bool	b1=IsInclude(L->Position.x1,L->Position.y1);
			bool	b2=IsInclude(L->Position.x2,L->Position.y2);
			if((b1^b2)==true){
				Count++;
			}
		}
	}
	return Count;
}

void	GerberFastItemBase::SetDetailMatchRelation(IntList &FileLayerIDContainer)
{
	double	Sx1,Sy1,Sx2,Sy2;
	if(GetXY(Sx1,Sy1,Sx2,Sy2)==false)
		return;

	GerberFastInPage	*PData=(GerberFastInPage *)GetParentInPage();
	int	tx1=Sx1/PData->AccessDimXLen;
	int	ty1=Sy1/PData->AccessDimYLen;
	int	tx2=Sx2/PData->AccessDimXLen;
	int	ty2=Sy2/PData->AccessDimYLen;

	tx1=max(tx1,0);
	ty1=max(ty1,0);
	tx2=min(tx2,AccessDimNumbX-1);
	ty2=min(ty2,AccessDimNumbY-1);

	int	MaxN=0;
	RelationParent=NULL;

	for(int tx=tx1;tx<=tx2;tx++){
		for(int ty=ty1;ty<=ty2;ty++){
			for(AlgorithmItemPointerList *a=PData->AccessDim[tx][ty].GetFirst();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(a->GetItem());
				if(p!=NULL){
					if(p->TransDetail.IsEmpty()==false){
						int	N=GetCrossedCount(p->TransDetail);
						if(N>MaxN){
							MaxN=N;
							RelationParent=p;
						}
					}
				}
			}
		}
	}
	if(RelationParent==NULL){
		double	Cx=(Sx1+Sx2)/2.0;
		double	Cy=(Sy1+Sy2)/2.0;
		double	MinD=DBL_MAX;
		for(int tx=tx1;tx<=tx2;tx++){
			for(int ty=ty1;ty<=ty2;ty++){
				for(AlgorithmItemPointerList *a=PData->AccessDim[tx][ty].GetFirst();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(a->GetItem());
					if(p!=NULL){
						if(p->TransDetail.IsEmpty()==false){
							double	D=p->TransDetail.GetDistance(Cx,Cy);
							if(D<MinD){
								MinD=D;
								RelationParent=p;
							}
						}
					}
				}
			}
		}
	}
}

void	GerberFastItemBase::RestructHairline(void)
{
	TransDetail.Restruct(3);
	TransDetail.RestructInOut(this);
}


//Center is (0,0)
double	GetLeftAreaSize(double R ,double X)
{
	double	Y=sqrt(R*R-X*X);
	double	s=GetSita(X,Y);
	return M_PI*R*R-(M_PI-s)+X*Y;
}

double	GetCornerArea(double R ,double StartS ,double EndS)
{
	double	tx1=R-cos(StartS);
	double	tx2=R-cos(EndS);

	double	ty1=R-sin(StartS);
	double	ty2=R-sin(EndS);

	double	s=RegulateAngle(EndS-StartS);
	double	L=hypot(tx2-tx1,ty2-ty1);

	double	px=(tx1+tx2)/2;
	double	py=(ty1+ty2)/2;
	double	SubTriangle=hypot(px,py)*L/2;

	return R*R*s/2-SubTriangle+fabs((ty2-ty1)*(tx2-tx1)/2);
}
double	GetArchLineAreaSize(double R ,double StartS ,double EndS)
{
	double	tx1=R-cos(StartS);
	double	tx2=R-cos(EndS);

	double	ty1=R-sin(StartS);
	double	ty2=R-sin(EndS);

	double	s=RegulateAngle(EndS-StartS);
	double	L=hypot(tx2-tx1,ty2-ty1);

	double	px=(tx1+tx2)/2;
	double	py=(ty1+ty2)/2;
	double	SubTriangle=hypot(px,py)*L/2;
	if(s<M_PI)
		return R*R*s/2-SubTriangle;
	else
		return R*R*s/2+SubTriangle;
}

double	GetCircleAreaSize(double Cx,double Cy ,double R
						, double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	double	MinX=Cx-R;
	double	MinY=Cy-R;
	double	MaxX=Cx+R;
	double	MaxY=Cy+R;

	if(MaxX<ClipX1 || MaxY<ClipY1 || ClipX2<MinX || ClipY2<MinY)
		return 0.0;

	bool	InsideLeftSide	=(ClipX1<=MinX)?true:false;
	bool	InsideTopSide	=(ClipY1<=MinY)?true:false;
	bool	InsideRightSide	=(MaxX<=ClipX2)?true:false;
	bool	InsideBottomSide=(MaxY<=ClipY2)?true:false;

	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==true)
		//Inside completely
		return M_PI*R*R;

	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==true)
		//Only left side on ClipArea
		return M_PI*R*R - GetLeftAreaSize(R,Cx-ClipX1);
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==true)
		//Only top side on ClipArea
		return M_PI*R*R - GetLeftAreaSize(R,Cy-ClipY1);
	else
	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==true)
		//Only right side on ClipArea
		return GetLeftAreaSize(R,Cx-ClipX2);
	else
	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==false)
		//Only bottom side on ClipArea
		return GetLeftAreaSize(R,Cy-ClipY2);

	else
	if(InsideLeftSide==false && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==true){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return M_PI*R*R - GetLeftAreaSize(R,Cx-ClipX1) - GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==false && InsideBottomSide==true){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2) - GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==false){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2)+GetLeftAreaSize(R,Cy-ClipY2) - M_PI*R*R;
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==false){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cy-ClipY2) - GetLeftAreaSize(R,Cx-ClipX1);
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==true){
		return GetLeftAreaSize(R,Cx-ClipX2) - GetLeftAreaSize(R,Cx-ClipX1);
	}
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==false){
		return GetLeftAreaSize(R,Cy-ClipY2) - GetLeftAreaSize(R,Cy-ClipY1);
	}

	else
	if(InsideLeftSide==false && InsideTopSide==false && InsideRightSide==false && InsideBottomSide==true){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX1,ClipY1,ClipX2, ClipY1
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY1;
			Points[1][0]=ClipX2;	Points[1][1]=ClipY1;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2) - GetLeftAreaSize(R,Cx-ClipX1)- GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==false){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX1,ClipY1,ClipX1, ClipY2
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY1;
			Points[1][0]=ClipX1;	Points[1][1]=ClipY2;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cy-ClipY2) - GetLeftAreaSize(R,Cx-ClipX1)- GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==false){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX1,ClipY2,ClipX2, ClipY2
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY2;
			Points[1][0]=ClipX2;	Points[1][1]=ClipY2;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2)+ GetLeftAreaSize(R,Cy-ClipY2) -M_PI*R*R - GetLeftAreaSize(R,Cx-ClipX1);
		}
	}
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==false && InsideBottomSide==false){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX2,ClipY1,ClipX2, ClipY2
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX2;	Points[0][1]=ClipY2;
			Points[1][0]=ClipX2;	Points[1][1]=ClipY1;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2)+ GetLeftAreaSize(R,Cy-ClipY2) -M_PI*R*R - GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else{
		bool	InsideCornerX1Y1=(hypot(ClipX1-Cx,ClipY1-Cy)<R)?true:false;
		bool	InsideCornerX2Y1=(hypot(ClipX2-Cx,ClipY1-Cy)<R)?true:false;
		bool	InsideCornerX1Y2=(hypot(ClipX1-Cx,ClipY2-Cy)<R)?true:false;
		bool	InsideCornerX2Y2=(hypot(ClipX2-Cx,ClipY2-Cy)<R)?true:false;
		int		n;
		double	AreaDot=(ClipX1-ClipX1)*(ClipY2-ClipY1);
		if(InsideCornerX1Y1==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY1;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		if(InsideCornerX2Y1==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX2;	Points[0][1]=ClipY1;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		if(InsideCornerX1Y2==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY2;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		if(InsideCornerX2Y2==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX2;	Points[0][1]=ClipY2;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}

		return AreaDot;
	}
}

double	GetRectangleAreaSize(double MinX,double MinY,double MaxX,double MaxY	//Rectangle
						, double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	if(MaxX<ClipX1 || MaxY<ClipY1 || ClipX2<MinX || ClipY2<MinY)
		return 0.0;

	//bool	InsideLeftSide	=(ClipX1<=MinX)?true:false;
	//bool	InsideTopSide	=(ClipY1<=MinY)?true:false;
	//bool	InsideRightSide	=(MaxX<=ClipX2)?true:false;
	//bool	InsideBottomSide=(MaxY<=ClipY2)?true:false;

	MinX=max(MinX,ClipX1);
	MinY=max(MinY,ClipY1);
	MaxX=min(MaxX,ClipX2);
	MaxY=min(MaxY,ClipY2);
	double	W=MaxX-MinX;
	double	H=MaxY-MinY;
	return W*H;
}

double	GerberFastItemBase::GetZoomRateY(double ZoomRateX)
{
	return ZoomRateX*((double)GetParamGlobal()->ResolutionXNano)/((double)GetParamGlobal()->ResolutionYNano);
}