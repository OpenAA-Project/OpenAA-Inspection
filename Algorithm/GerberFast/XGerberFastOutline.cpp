#include "XGerberAperture.h"
#include "GerberFast.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XGeneralFunc.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XGerberFastLibrary.h"
#include "XImageProcess.h"
#include "XCrossObj.h"
#include <omp.h>

extern	int	DebugDCode	;
extern	int	DbgPage		;
extern	int	DCodeDebug	;
extern	int	DbgID		;

const	double	SmallSigma=0.000001;
const	double	OuterRate=0.01;
const	double	Pi2=2*M_PI;
int	DbgCrossX=4306;
int	DbgCrossY=16297;


int		MakeCornerArcLineLine(double px ,double py ,double jx ,double jy	//(jx,jy)=Junction
							, double qx ,double qy
							, double CornerR
							, double &rcx,double &rcy,double &rr,double &rstartangle,double &rendangle)
{
	if(CornerR<=0)
		return 0;
	double	dx1=px-jx;
	double	dy1=py-jy;
	double	dx2=qx-jx;
	double	dy2=qy-jy;

	double	L1=hypot(dx1,dy1);
	double	L2=hypot(dx2,dy2);
	if(L1==0.0 || L2==0.0)
		return 0;
	dx1/=L1;
	dy1/=L1;
	dx2/=L2;
	dy2/=L2;
	double	Pax=jx+dx1*CornerR;
	double	Pay=jy+dy1*CornerR;
	double	Pbx=jx+dx2*CornerR;
	double	Pby=jy+dy2*CornerR;

	double	A=-dx2*dy1+dx2*dy1;
	double	B=-Pax*dx1*dy2+dy1*dy2*(Pby-Pay)+Pbx*dx2*dy1;
	if(A==0.0)
		return 0;
	rcx=B/A;
	if(fabs(dy1)>fabs(dy2)){
		rcy=-dx1*(rcx-Pax)/dy1+Pay;
	}
	else{
		rcy=-dx2*(rcx-Pbx)/dy2+Pby;
	}
	rstartangle=GetSita(Pax-rcx,Pay-rcy);
	rendangle  =GetSita(Pbx-rcx,Pby-rcy);
	double	s  =GetSita(jx -rcx,jy -rcy);
	if(rstartangle<=rendangle && (rstartangle<=s && s<=rendangle))
		return 1;
	if(rstartangle<=rendangle && (rstartangle<=s || s<=rendangle))
		return 1;
	swap(rstartangle,rendangle);
	return 1;
}

int		MakeCornerArcLineArc(double x1 ,double y1 ,double x2 ,double y2
							,double cx ,double cy ,double r ,double startangle ,double endangle
							,double CornerR
							,double &rcx,double &rcy,double &rr,double &rstartangle,double &rendangle)
{
	return 1;
}

//------------------------------------------------------------

class	SparsLineBasePointer : public NPList<SparsLineBasePointer>
{
public:
	int	ItemID;
	SparsLineBase	*Pointer;
	SparsOutline	*Parent;

	SparsLineBasePointer(SparsLineBase *p ,int id ,SparsOutline *parent)
		:ItemID(id),Pointer(p),Parent(parent){}
};

class	SparsLineBasePointerList : public NPList<SparsLineBasePointerList>
{
public:
	SparsLineBasePointer	*Pointer;

	SparsLineBasePointerList(SparsLineBasePointer *p):Pointer(p){}
};


void	SparsLineBase::ClearConnInfo(void)
{
	ConnInfo[0]=false;
	ConnInfo[1]=false;
}
bool	SparsLine::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}
	
bool	SparsLine::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}
bool	SparsLine::operator==(SparsLine &src)
{
	if(fabs(X1-src.X1)<SmallSigma && fabs(Y1-src.Y1)<SmallSigma 
	&& fabs(X2-src.X2)<SmallSigma && fabs(Y2-src.Y2)<SmallSigma){
		return true;
	}
	return false;
}
bool	SparsLine::OnOneLine(SparsLine &src)
{
	double	sdx=X2-X1;
	double	sdy=Y2-Y1;
	double	ddx=src.X2-src.X1;
	double	ddy=src.Y2-src.Y1;
	double	Ls=hypot(sdx,sdy);
	double	Ld=hypot(ddx,ddy);
	if(Ls<SmallSigma || Ld<SmallSigma)
		return true;
	sdx/=Ls;
	sdy/=Ls;
	ddx/=Ld;
	ddy/=Ld;
	if(sdx<0){
		sdx =-sdx;
		sdy =-sdy;
	}
	if(ddx<0){
		ddx =-ddx;
		ddy =-ddy;
	}
	if(fabs(sdx-ddx)<SmallSigma && fabs(sdy-ddy)<SmallSigma)
		return true;
	return false;
}
void	SparsLine::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY)
{
	int	x1=(X1+movx)*ZoomRate;
	int	y1=(Y1+movy)*ZoomRate;
	int	x2=(X2+movx)*ZoomRate;
	int	y2=(Y2+movy)*ZoomRate;

	if(x1<0 && x2<0)
		return;
	if(y1<0 && y2<0)
		return;
	if(MaxWindowX<=x1 && MaxWindowX<=x2)
		return;
	if(MaxWindowY<=y1 && MaxWindowY<=y2)
		return;
	pnt.setPen(Col);
	pnt.drawLine(x1,y1,x2,y2);
	pnt.drawLine(x1-2,y1-2,x1+2,y1+2);
	pnt.drawLine(x1+2,y1-2,x1-2,y1+2);
	pnt.drawLine(x2-2,y2-2,x2+2,y2+2);
	pnt.drawLine(x2+2,y2-2,x2-2,y2+2);
}
double	SparsLine::GetLength2Point(double x ,double y)
{
	return GetLengthLine2Point(X1,Y1,X2,Y2 ,x,y);
}
bool	SparsLine::IsInclude(GerberFastInPage *APage)
{
	if(X1<0 && X2<0)
		return false;
	if(Y1<0 && Y2<0)
		return false;
	if(X1>=APage->GetDotPerLine() && X2>=APage->GetDotPerLine())
		return false;
	if(Y1>=APage->GetMaxLines() && Y2>=APage->GetMaxLines())
		return false;
	return true;
}
bool	SparsLine::IsIncludeOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	int	iX=X1;
	int	iY=Y1;
	if(0<=iX && iX<(XByte*8) && 0<=iY && iY<YLen){
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
	}
	return false;
}
bool	SparsLine::IsIncludeOnBmpAny(BYTE **TmpMap1,int XByte ,int YLen)
{
	int	iX=X1;
	int	iY=Y1;
	if(GetBmpBit(TmpMap1,iX,iY)!=0)
		return true;
	iX=X2;
	iY=Y2;
	if(GetBmpBit(TmpMap1,iX,iY)!=0)
		return true;
	iX=(X1+X2)/2.0;
	iY=(Y1+Y2)/2.0;
	if(GetBmpBit(TmpMap1,iX,iY)!=0)
		return true;
	return false;
}

bool	IsIncludeItem(AlgorithmItemPointerListContainer &ItemStack,double x, double y)
{
	bool	Included=false;
	for(AlgorithmItemPointerList *a=ItemStack.GetFirst();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*g=dynamic_cast<GerberFastItemBase *>(a->GetItem());
		if(g!=NULL){
			if(g->IsInclude(x,y)==true){
				if(g->PosiImage==true){
					Included=true;
				}
				else{
					Included=false;
				}
			}
		}
	}
	return Included;
}

bool	SparsLine::IsRealEdge(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY])
{
	double	Dx=X2-X1;
	double	Dy=Y2-Y1;
	double	L=hypot(Dx,Dy);
	if(L<SmallSigma)
		return false;
	double	Mx=X1+Dx/2.0;
	double	My=Y1+Dy/2.0;
	double	Vx=Dx/L;
	double	Vy=Dy/L;
	double	Kx1=Mx-Vy*OuterRate;
	double	Ky1=My+Vx*OuterRate;
	double	Kx2=Mx+Vy*OuterRate;
	double	Ky2=My-Vx*OuterRate;

	int	TableXLen=APage->GetDotPerLine()/SparsDivCountX;
	int	TableYLen=APage->GetMaxLines()/SparsDivCountY;
	int	iPx1=Kx1/TableXLen;
	int	iPy1=Ky1/TableYLen;
	int	iPx2=Kx2/TableXLen;
	int	iPy2=Ky2/TableYLen;
	if(0<=iPx1 && iPx1<SparsDivCountX && 0<=iPx2 && iPx2<SparsDivCountX
	&& 0<=iPy1 && iPy1<SparsDivCountY && 0<=iPy2 && iPy2<SparsDivCountY){
		bool	b1=IsIncludeItem(DPoint[iPx1][iPy1],Kx1,Ky1);
		bool	b2=IsIncludeItem(DPoint[iPx2][iPy2],Kx2,Ky2);
		if((b1==true && b2==false) || (b1==false && b2==true)){
			return true;
		}
	}
	return false;
}
void	SparsLine::RegisterOnTable(GerberFastInPage *APage ,int ItemID ,SparsOutline *parent ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY])
{
	if(IsInclude(APage)==false)
		return;
	int	TableXLen=APage->GetDotPerLine()/SparsDivCountX;
	int	TableYLen=APage->GetMaxLines()/SparsDivCountY;

	int	iPx1=floor(X1/TableXLen);
	int	iPy1=floor(Y1/TableYLen);
	int	iPx2=ceil(X2/TableXLen);
	int	iPy2=ceil(Y2/TableYLen);

	iPx1=Clipping(iPx1 ,0 ,SparsDivCountX-1);
	iPy1=Clipping(iPy1 ,0 ,SparsDivCountY-1);
	iPx2=Clipping(iPx2 ,0 ,SparsDivCountX-1);
	iPy2=Clipping(iPy2 ,0 ,SparsDivCountY-1);
	if(iPx1>iPx2)
		swap(iPx1,iPx2);
	if(iPy1>iPy2)
		swap(iPy1,iPy2);
	for(int y=iPy1;y<=iPy2;y++){
		for(int x=iPx1;x<=iPx2;x++){
			if(CheckOverlapRectLine((double)(x*TableXLen) ,(double)(y*TableYLen) ,(double)((x+1)*TableXLen) ,(double)((y+1)*TableYLen)
									,X1,Y1,X2,Y2)==true){
				SparsLineBasePointer	*c=new SparsLineBasePointer(this,ItemID ,parent);
				SparsListTable[x][y].AppendList(c);
			}
		}
	}
}
int		SparsLine::GetEndPoint(double Point[][2])
{
	Point[0][0]=X1;
	Point[0][1]=Y1;
	Point[1][0]=X2;
	Point[1][1]=Y2;
	return 2;
}
void	SparsLine::GetEndVector(int N,double &Dx,double &Dy)
{
	Dx=X2-X1;
	Dy=Y2-Y1;
	double	L=hypot(Dx,Dy);
	if(L==0)
		return;
	Dx/=L;
	Dy/=L;
}
	
double	SparsLine::GetMinEndY(void)
{
	return min(Y1,Y2);
}
	
double	SparsLine::GetEndXInMinY(void)
{
	if(Y1<Y2){
		return X1;
	}
	return X2;
}
	
void	SparsLine::GetEndPoint1(double &x,double &y)
{
	x=X1;
	y=Y1;
}
	
void	SparsLine::GetEndPoint2(double &x,double &y)
{
	x=X2;
	y=Y2;
}
bool	SparsLine::IsChecked(void)
{
	if(fabs(X1-5649.0021625845848)<0.001 && fabs(Y1-18055.644216896522)<0.001 
	&& fabs(X2-4298.7872934822190)<0.001 && fabs(Y2-16287.855068854202)<0.001)
		return true;
	return false;
}

SparsLineBase	*SparsLine::MakeCenterLine(double MaxWidth,SparsLineBaseListContainer &Container)
{
	double	sx1,sy1;
	double	sx2,sy2;
	GetEndPoint1(sx1,sy1);
	GetEndPoint1(sx2,sy2);
	for(SparsLineBaseList *a=Container.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Pointer==this)
			continue;
		SparsLine	*dL=dynamic_cast<SparsLine *>(a->Pointer);
		if(dL!=NULL){
			double	dx1,dy1;
			double	dx2,dy2;
			dL->GetEndPoint1(dx1,dy1);
			dL->GetEndPoint1(dx2,dy2);
			double	L11=GetLength2Point(dx1,dy1);
			double	L12=GetLength2Point(dx2,dy2);
			double	L21=dL->GetLength2Point(sx1,sy1);
			double	L22=dL->GetLength2Point(sx2,sy2);
			double	L=min(min(L11,L12),min(L21,L22));
			if(L<MaxWidth){
				if(hypot(dx1-sx1,dy1-sy1)<SmallSigma || hypot(dx1-sx2,dy1-sy2)<SmallSigma
				|| hypot(dx2-sx1,dy2-sy1)<SmallSigma || hypot(dx2-sx2,dy2-sy2)<SmallSigma){
					double	s1=GetSita(X2-X1,Y2-Y1);
					double	s2=GetSita(dL->X2-dL->X1,dL->Y2-dL->Y1);
					if(DiffSita(s1,s2)<M_PI/4){
					}
				}
			}
		}
	}
	return NULL;
}
//============================================================================
bool	SparsArc::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,R)==false)
		return false;
	if(::Save(f,StartAngle)==false)
		return false;
	if(::Save(f,EndAngle)==false)
		return false;
	return true;
}
	
bool	SparsArc::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,R)==false)
		return false;
	if(::Load(f,StartAngle)==false)
		return false;
	if(::Load(f,EndAngle)==false)
		return false;
	return true;
}
bool	SparsArc::operator==(SparsArc &src)
{
	if(fabs(Cx-src.Cx)<SmallSigma && fabs(Cy-src.Cy)<SmallSigma
	&& fabs(R-src.R)<SmallSigma 
	&& fabs(StartAngle-src.StartAngle)<SmallSigma && fabs(EndAngle-src.EndAngle)<SmallSigma){
		return true;
	}
	return false;
}
bool	SparsArc::OnOneArc(SparsArc &src)
{
	if(fabs(Cx-src.Cx)<SmallSigma && fabs(Cy-src.Cy)<SmallSigma
	&& fabs(R-src.R)<SmallSigma){
		return true;
	}
	return false;
}
void	SparsArc::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY)
{
	int	cx=(Cx+movx)*ZoomRate;
	int	cy=(Cy+movy)*ZoomRate;
	int	r =R*ZoomRate;

	if((cx+r)<0)
		return;
	if((cy+r)<0)
		return;
	if(MaxWindowX<=(cx-r))
		return;
	if(MaxWindowY<=(cy-r))
		return;

	if(5671<Cx-R && Cx-R<5675 && 23250<=Cy-R && Cy-R<23255){
		DCodeDebug++;
	}

	pnt.setPen(Col);
	double	k=RegulateAngle(EndAngle-StartAngle);
	
	if(SmallSigma<=k && k<(Pi2-SmallSigma)){
		double	s=RegulateAngle(Pi2-EndAngle);
		double	d=RegulateAngle(EndAngle-StartAngle);

		pnt.drawArc(cx-r,cy-r,r+r,r+r,s/Pi2*5760,d/Pi2*5760);

		int	x1=((Cx+R*cos(StartAngle))+movx)*ZoomRate;
		int	y1=((Cy+R*sin(StartAngle))+movy)*ZoomRate;
		int	x2=((Cx+R*cos(EndAngle  ))+movx)*ZoomRate;
		int	y2=((Cy+R*sin(EndAngle  ))+movy)*ZoomRate;

		pnt.drawLine(x1-2,y1-2,x1+2,y1+2);
		pnt.drawLine(x1+2,y1-2,x1-2,y1+2);
		pnt.drawLine(x2-2,y2-2,x2+2,y2+2);
		pnt.drawLine(x2+2,y2-2,x2-2,y2+2);
	}
	else{
		pnt.drawArc(cx-r,cy-r,r+r,r+r,0,5759);
	}
}
double	SparsArc::GetLength2Point(double x ,double y)
{
	return GetLengthArc2Point(Cx,Cy,R,StartAngle,EndAngle,x,y);
}
bool	SparsArc::IsInclude(GerberFastInPage *APage)
{
	if((Cx+R)<0)
		return false;
	if((Cy+R)<0)
		return false;
	if((Cx-R)>=APage->GetDotPerLine())
		return false;
	if((Cy-R)>=APage->GetMaxLines())
		return false;
	return true;
}

bool	SparsArc::IsRealEdge(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY])
{
	double	MidAngle;
	if(StartAngle<=EndAngle)
		MidAngle=(StartAngle+EndAngle)/2.0;
	else
		MidAngle=RegulateAngle((StartAngle-Pi2+EndAngle)/2.0);

	double	Mx=Cx+R*cos(MidAngle);
	double	My=Cy+R*sin(MidAngle);
	double	Dx=Mx-Cx;
	double	Dy=My-Cy;
	double	L =hypot(Dx,Dy);
	double	Vx=Dx/L;
	double	Vy=Dy/L;
	double	Kx1=Mx+Vx*OuterRate;
	double	Ky1=My+Vy*OuterRate;
	double	Kx2=Mx-Vx*OuterRate;
	double	Ky2=My-Vy*OuterRate;

	int	TableXLen=APage->GetDotPerLine()/SparsDivCountX;
	int	TableYLen=APage->GetMaxLines()/SparsDivCountY;
	int	iPx1=Kx1/TableXLen;
	int	iPy1=Ky1/TableYLen;
	int	iPx2=Kx2/TableXLen;
	int	iPy2=Ky2/TableYLen;
	if(0<=iPx1 && iPx1<SparsDivCountX && 0<=iPx2 && iPx2<SparsDivCountX
	&& 0<=iPy1 && iPy1<SparsDivCountY && 0<=iPy2 && iPy2<SparsDivCountY){
		bool	b1=IsIncludeItem(DPoint[iPx1][iPy1],Kx1,Ky1);
		bool	b2=IsIncludeItem(DPoint[iPx2][iPy2],Kx2,Ky2);
		if((b1==true && b2==false) || (b1==false && b2==true)){
			return true;
		}
	}
	return false;
}
bool	SparsArc::IsIncludeOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	int	iX=Cx+R*cos(StartAngle);
	int	iY=Cy+R*sin(StartAngle);
	if(0<=iX && iX<(XByte*8) && 0<=iY && iY<YLen){
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
	}
	return false;
}
bool	SparsArc::IsIncludeOnBmpAny(BYTE **TmpMap1,int XByte ,int YLen)
{
	double	MidAngle;
	if(StartAngle<=EndAngle)
		MidAngle=(StartAngle+EndAngle)/2.0;
	else
		MidAngle=RegulateAngle((StartAngle-Pi2+EndAngle)/2.0);

	double	k=RegulateAngle(EndAngle-StartAngle);
	if(SmallSigma<=k && k<(Pi2-SmallSigma)){
		int	iX=Cx+R*cos(StartAngle);
		int	iY=Cy+R*sin(StartAngle);
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
		iX=Cx+R*cos(EndAngle);
		iY=Cy+R*sin(EndAngle);
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
		iX=Cx+R*cos(MidAngle);
		iY=Cy+R*sin(MidAngle);
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
	}
	else{
		int	iX=Cx+R;
		int	iY=Cy;
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
		iX=Cx;
		iY=Cy+R;
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
		iX=Cx-R;
		iY=Cy;
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
		iX=Cx;
		iY=Cy-R;
		if(GetBmpBit(TmpMap1,iX,iY)!=0)
			return true;
	}

	return false;
}
void	SparsArc::RegisterOnTable(GerberFastInPage *APage ,int ItemID ,SparsOutline *parent ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY])
{
	if(IsInclude(APage)==false)
		return;
	int	TableXLen=APage->GetDotPerLine()/SparsDivCountX;
	int	TableYLen=APage->GetMaxLines()/SparsDivCountY;

	int	iPx1=floor((Cx-R)/TableXLen);
	int	iPy1=floor((Cy-R)/TableYLen);
	int	iPx2=ceil ((Cx+R)/TableXLen);
	int	iPy2=ceil ((Cy+R)/TableYLen);

	iPx1=Clipping(iPx1 ,0 ,SparsDivCountX-1);
	iPy1=Clipping(iPy1 ,0 ,SparsDivCountY-1);
	iPx2=Clipping(iPx2 ,0 ,SparsDivCountX-1);
	iPy2=Clipping(iPy2 ,0 ,SparsDivCountY-1);
	if(iPx1>iPx2)
		swap(iPx1,iPx2);
	if(iPy1>iPy2)
		swap(iPy1,iPy2);
	for(int y=iPy1;y<=iPy2;y++){
		for(int x=iPx1;x<=iPx2;x++){
			if(CheckOverlapRectArc(x*TableXLen ,y*TableYLen ,(x+1)*TableXLen ,(y+1)*TableYLen			//Box
							,Cx ,Cy ,R,StartAngle ,EndAngle)==true){
				SparsLineBasePointer	*c=new SparsLineBasePointer(this,ItemID ,parent);
				SparsListTable[x][y].AppendList(c);
			}
		}
	}
}
int		SparsArc::GetEndPoint(double Point[][2])
{
	Point[0][0]=Cx+R*cos(StartAngle);
	Point[0][1]=Cy+R*sin(StartAngle);
	Point[1][0]=Cx+R*cos(EndAngle);
	Point[1][1]=Cy+R*sin(EndAngle);
	return 2;
}
void	SparsArc::GetEndVector(int N,double &Dx,double &Dy)
{
	if(N==0){
		Dx=sin(StartAngle);
		Dy=-cos(StartAngle);
	}
	else if(N==1){
		Dx=sin(EndAngle);
		Dy=-cos(EndAngle);
	}
}
double	SparsArc::GetMinEndY(void)
{
	double	y1=Cy+R*sin(StartAngle);
	double	y2=Cy+R*sin(EndAngle);
	return min(y1,y2);
}
	
double	SparsArc::GetEndXInMinY(void)
{
	double	Y1=Cy+R*sin(StartAngle);
	double	Y2=Cy+R*sin(EndAngle);

	if(Y1<Y2){
		return Cx+R*cos(StartAngle);
	}
	return Cx+R*cos(EndAngle);
}
	
void	SparsArc::GetEndPoint1(double &x,double &y)
{
	x=Cx+R*cos(StartAngle);
	y=Cy+R*sin(StartAngle);
}
	
void	SparsArc::GetEndPoint2(double &x,double &y)
{
	x=Cx+R*cos(EndAngle);
	y=Cy+R*sin(EndAngle);
}
bool	SparsArc::IsChecked(void)
{
	if(fabs(Cx-3187.5555432062456)<0.001 && fabs(Cy-15308.381101350436)<0.001 
	&& fabs(R-1493.2556719034196)<0.001 
	&& fabs(StartAngle-0.00040342103670902037)<0.001 && fabs(EndAngle-0.73228188896739366)<0.001)
		return true;
	return false;
}
SparsLineBase	*SparsArc::MakeCenterLine(double MaxWidth,SparsLineBaseListContainer &Container)
{
	return NULL;
}
//============================================================================	
bool	SparsOutline::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,OutlineID)==false)
		return false;
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;	
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		short	ClassType=a->GetClassType();
		if(::Save(f,ClassType)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
	
bool	SparsOutline::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,OutlineID)==false)
		return false;

	int32	N;
	if(::Load(f,N)==false)
		return false;
	NPListPack<SparsLineBase>::RemoveAll();
	for(int i=0;i<N;i++){
		short	ClassType;
		if(::Load(f,ClassType)==false)
			return false;
		SparsLineBase *a=Create(ClassType);
		if(a==NULL){
			return false;
		}
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
SparsLineBase	*SparsOutline::Create(short ClassType)
{
	SparsLineBase *a=NULL;
	if(ClassType==1)
		a=new SparsLine();
	else if(ClassType==2)
		a=new SparsArc();
	else{
		a=NULL;
	}
	return a;
}
void	SparsOutline::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY)
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt, movx ,movy ,ZoomRate ,Col ,MaxWindowX ,MaxWindowY);
	}
}

void	SparsOutline::RemoveSparsWithoutOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;){
		SparsLineBase *NextA=a->GetNext();
		if(a->IsIncludeOnBmp(TmpMap1,XByte ,YLen)==false){
			NPListPack<SparsLineBase>::RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
}
void	SparsOutline::RemoveSparsWithOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;){
		if(a->GetLength2Point(DbgCrossX,DbgCrossY)<2){
			DCodeDebug++;
		}
		SparsLineBase *NextA=a->GetNext();
		if(a->IsIncludeOnBmpAny(TmpMap1,XByte ,YLen)==true){
			NPListPack<SparsLineBase>::RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
}
void	SparsOutline::RemoveSpars(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY])
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;){
		if(a->GetLength2Point(DbgCrossX,DbgCrossY)<2){
			DCodeDebug++;
		}
		SparsLineBase *NextA=a->GetNext();
		if(a->IsRealEdge(APage,DPoint)==false){
			NPListPack<SparsLineBase>::RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
}
void	SparsOutline::RegisterOnTable(GerberFastInPage *APage ,int ItemID ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY])
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		a->RegisterOnTable(APage,ItemID ,this,SparsListTable);
	}
}
void	SparsOutline::ClearConnInfo(void)
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		a->ClearConnInfo();
	}
}
bool	SparsOutline::IsSelected(double X ,double Y ,double Isolation)
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLength2Point(X ,Y)<=Isolation){
			return true;
		}
	}
	return false;
}
void	SparsOutline::MakePointerList(SparsLineBaseListContainer &Container)
{
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		Container.AppendList(new SparsLineBaseList(a));
	}
}
SparsOutline &SparsOutline::operator=(const SparsOutline &src)
{
	OutlineID=src.OutlineID;
	Selected=src.Selected;
	for(SparsLineBase *a=NPListPack<SparsLineBase>::GetFirst();a!=NULL;a=a->GetNext()){
		SparsLineBase	*b=Create(a->GetClassType());
		*b=*a;
		NPListPack<SparsLineBase>::AppendList(b);
	}
	return *this;
}
//============================================================================	
bool	SparsShape::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return NPListPackSaveLoad<SparsOutline>::Save(f);
}

bool	SparsShape::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return NPListPackSaveLoad<SparsOutline>::Load(f);
}

void	SparsShape::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY)
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Selected==false)
			a->Draw(pnt, movx ,movy ,ZoomRate ,Col ,MaxWindowX ,MaxWindowY);
		else
			a->Draw(pnt, movx ,movy ,ZoomRate ,qRgb(255,0,0) ,MaxWindowX ,MaxWindowY);
	}
}

void	SparsShape::RemoveSparsWithoutOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		a->RemoveSparsWithoutOnBmp(TmpMap1,XByte ,YLen);
	}
}

void	SparsShape::RemoveSparsWithOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		a->RemoveSparsWithOnBmp(TmpMap1,XByte ,YLen);
	}
}
void	SparsShape::RemoveSpars(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY])
{
	if(ItemID==DbgID)
		DCodeDebug=1;
						
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		a->RemoveSpars(APage,DPoint);
	}
}
void	SparsShape::RegisterOnTable(GerberFastInPage *APage ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY])
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		a->RegisterOnTable(APage,ItemID ,SparsListTable);
	}
}
void	SparsShape::ClearConnInfo(void)
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		a->ClearConnInfo();
	}
}
void	SparsShape::MakeID(void)
{
	int	OutlineID=0;
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext(),OutlineID++){
		a->SetID(OutlineID);
	}
}
void	SparsShape::SetSelected(double X ,double Y ,double Isolation)
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsSelected(X,Y,Isolation)==true){
			a->Selected=true;
		}
		else{
			a->Selected=false;
		}
	}
}
void	SparsShape::MakePointerList(SparsLineBaseListContainer &Container)
{
	for(SparsOutline *a=NPListPackSaveLoad<SparsOutline>::GetFirst();a!=NULL;a=a->GetNext()){
		a->MakePointerList(Container);
	}
}

//============================================================================
void	SparsContainer::Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,QRgb Col ,int MaxWindowX ,int MaxWindowY)
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt, movx ,movy ,ZoomRate ,Col ,MaxWindowX ,MaxWindowY);
	}
}
void	SparsContainer::RemoveSparsWithoutOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->RemoveSparsWithoutOnBmp(TmpMap1,XByte ,YLen);
	}
}
void	SparsContainer::RemoveSparsWithOnBmp(BYTE **TmpMap1,int XByte ,int YLen)
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->RemoveSparsWithOnBmp(TmpMap1,XByte ,YLen);
	}
}
void	SparsContainer::RemoveSpars(GerberFastInPage *APage ,AlgorithmItemPointerListContainer DPoint[SparsDivCountX][SparsDivCountY])
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->RemoveSpars(APage,DPoint);
	}
}
void	SparsContainer::RegisterOnTable(GerberFastInPage *APage ,NPListPack<SparsLineBasePointer> SparsListTable[SparsDivCountX][SparsDivCountY])
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->RegisterOnTable(APage,SparsListTable);
	}
}
void	SparsContainer::ClearConnInfo(void)
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->ClearConnInfo();
	}
}
void	SparsContainer::MakeID(void)
{
	int	ItemID=0;
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext(),ItemID++){
		a->SetID(ItemID);
		a->MakeID();
	}
}
void	SparsContainer::SetSelected(double X ,double Y ,double Isolation)
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetSelected(X ,Y ,Isolation);
	}
}

int	SortTableFunc(const void *a, const void *b)
{
	SparsLineBase	*pa=((SparsLineBase **)a)[0];
	SparsLineBase	*pb=((SparsLineBase **)b)[0];

	double	L=pa->GetMinEndY() - pb->GetMinEndY();
	if(L<0)
		return -1;
	if(L>0)
		return 1;
	double	H=pa->GetEndXInMinY() - pb->GetEndXInMinY();
	if(H<0)
		return -1;
	if(H>0)
		return 1;
	return 0;
}

void	SparsContainer::RestructConnection(void)
{
	int	N=0;
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(SparsOutline *b=a->NPListPackSaveLoad<SparsOutline>::GetFirst();b!=NULL;b=b->GetNext()){
			N+=b->NPListPack<SparsLineBase>::GetCount();
		}
	}
	SparsLineBase	**Table=new SparsLineBase*[N];
	int	k=0;
	SparsShape		*a;
	SparsOutline	*b;
	SparsLineBase	*c;
	while((a=GetFirst())!=NULL){
		RemoveList(a);
		while((b=a->NPListPackSaveLoad<SparsOutline>::GetFirst())!=NULL){
			a->NPListPackSaveLoad<SparsOutline>::RemoveList(b);
			while((c=b->NPListPack<SparsLineBase>::GetFirst())!=NULL){
				b->NPListPack<SparsLineBase>::RemoveList(c);
				Table[k]=c;
				k++;
			}
			delete	b;
		}
		delete	a;
	}
	QSort(Table,N,sizeof(Table[0]),SortTableFunc);

	SparsShape	*ShapeP=new SparsShape();
	AppendList(ShapeP);
	double	Isolation=0.5;

	for(;;){
		SparsLineBase	*Top=NULL;
		for(int i=0;i<N;i++){
			if(Table[i]!=NULL){
				Top=Table[i];
				Table[i]=NULL;
				break;
			}
		}
		if(Top==NULL)
			break;
		if(Top->GetLength2Point(DbgCrossX,DbgCrossY)<2)
			DCodeDebug++;

		SparsOutline	*s=new SparsOutline();
		ShapeP->AppendList(s);
		s->AppendList(Top);
		double	x,y;
		Top->GetEndPoint1(x,y);

		bool	Found;
		do{
			Found=false;
			double	px,py;
			for(int i=0;i<N;i++){
				if(Table[i]!=NULL){
					Table[i]->GetEndPoint1(px,py);
					if(hypot(px-x,py-y)<Isolation){
						s->AppendList(Table[i]);
						Table[i]->GetEndPoint2(x,y);
						Table[i]=NULL;
						Found=true;
						break;
					}
					Table[i]->GetEndPoint2(px,py);
					if(hypot(px-x,py-y)<Isolation){
						s->AppendList(Table[i]);
						Table[i]->GetEndPoint1(x,y);
						Table[i]=NULL;
						Found=true;
						break;
					}
				}
			}
		}while(Found==true);

		Top->GetEndPoint2(x,y);
		do{
			Found=false;
			double	px,py;
			for(int i=0;i<N;i++){
				if(Table[i]!=NULL){
					Table[i]->GetEndPoint1(px,py);
					if(hypot(px-x,py-y)<Isolation){
						s->InsertList(0,Table[i]);
						Table[i]->GetEndPoint2(x,y);
						Table[i]=NULL;
						Found=true;
						break;
					}
					Table[i]->GetEndPoint2(px,py);
					if(hypot(px-x,py-y)<Isolation){
						s->InsertList(0,Table[i]);
						Table[i]->GetEndPoint1(x,y);
						Table[i]=NULL;
						Found=true;
						break;
					}
				}
			}
		}while(Found==true);
	}
	delete	[]Table;
}

void	SparsContainer::MakeCenterize(double MaxWidth ,SparsOutline	&CenterLines)
{
	SparsLineBaseListContainer Container;
	MakePointerList(Container);

	for(SparsLineBaseList *a=Container.GetFirst();a!=NULL;a=a->GetNext()){
		SparsLineBase	*C=a->Pointer->MakeCenterLine(MaxWidth,Container);
		if(C!=NULL){
			CenterLines.AppendList(C);
		}
	}
}

void	SparsContainer::MakePointerList(SparsLineBaseListContainer &Container)
{
	for(SparsShape *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MakePointerList(Container);
	}
}

//============================================================================
void	SparsNode::MakeEchingFactor( AlgorithmItemPointerListContainer &AdditionalItems,double EFactor
									,AlgorithmItemPointerListContainer	DPoint[SparsDivCountX][SparsDivCountY])
{
	double	Dx1,Dy1;
	P1->GetEndVector(ConnInfo[0],Dx1,Dy1);
	double	Dx2,Dy2;
	P2->GetEndVector(ConnInfo[1],Dx2,Dy2);
}
//============================================================================

bool	ChopCross(NPListPack<SparsLineBasePointer> &SparsListTable)
{
	bool	Changed=false;

	for(SparsLineBasePointer *s=SparsListTable.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Pointer->IsChecked()==true){
			DCodeDebug++;
		}
		for(SparsLineBasePointer *d=s->GetNext();d!=NULL;d=d->GetNext()){
			if(d->Pointer->IsChecked()==true){
				DCodeDebug++;
			}
			if(s->ItemID==d->ItemID && s->Pointer->GetClassType()==d->Pointer->GetClassType())
				continue;
			if(s->Pointer->GetClassType()==1){
				SparsLine	*sL=dynamic_cast<SparsLine *>(s->Pointer);
				if(d->Pointer->GetClassType()==1){
					SparsLine	*dL=dynamic_cast<SparsLine *>(d->Pointer);
					if(sL->OnOneLine(*dL)==true)
						continue;

					double	X,Y;
					if(GetCrossInnerPoint(sL->X1,sL->Y1,sL->X2,sL->Y2
										, dL->X1,dL->Y1,dL->X2,dL->Y2
										 ,X ,Y)==true){
						if(sL->GetLength2Point(DbgCrossX,DbgCrossY)<2
						&& dL->GetLength2Point(DbgCrossX,DbgCrossY)<2){
							DCodeDebug++;
						}
						if((fabs(sL->X1-X)>SmallSigma || fabs(sL->Y1-Y)>SmallSigma)
						&& (fabs(sL->X2-X)>SmallSigma || fabs(sL->Y2-Y)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X;
							L1->Y1=Y;
							L1->X2=sL->X2;
							L1->Y2=sL->Y2;
							sL->X2=X;
							sL->Y2=Y;
							s->Parent->InsertLater(sL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}
						if((fabs(dL->X1-X)>SmallSigma || fabs(dL->Y1-Y)>SmallSigma)
						&& (fabs(dL->X2-X)>SmallSigma || fabs(dL->Y2-Y)>SmallSigma)){
							SparsLine	*L2=new SparsLine();
							L2->X1=X;
							L2->Y1=Y;
							L2->X2=dL->X2;
							L2->Y2=dL->Y2;
							dL->X2=X;
							dL->Y2=Y;
							d->Parent->InsertLater(dL,L2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(L2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
				}
				else if(d->Pointer->GetClassType()==2){
					SparsArc	*dA=dynamic_cast<SparsArc *>(d->Pointer);
					double	X1,Y1,X2,Y2;
					double	Angle1,Angle2;
						if(sL->GetLength2Point(DbgCrossX,DbgCrossY)<3
						&& dA->GetLength2Point(DbgCrossX,DbgCrossY)<3){
							DCodeDebug++;
						}
					int	n=CrossLineArc(  sL->X1,sL->Y1,sL->X2,sL->Y2
										,dA->Cx ,dA->Cy ,dA->R,dA->StartAngle ,dA->EndAngle
										,X1,Y1,X2,Y2
										,Angle1,Angle2);
					if(n==1){
						if((fabs(sL->X1-X1)>SmallSigma || fabs(sL->Y1-Y1)>SmallSigma)
						&& (fabs(sL->X2-X1)>SmallSigma || fabs(sL->Y2-Y1)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X1;
							L1->Y1=Y1;
							L1->X2=sL->X2;
							L1->Y2=sL->Y2;
							sL->X2=X1;
							sL->Y2=Y1;
							s->Parent->InsertLater(sL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}
						if(fabs(dA->StartAngle-Angle1)>SmallSigma && fabs(dA->EndAngle-Angle1)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle=Angle1;
							A2->EndAngle=dA->EndAngle;
							dA->EndAngle=Angle1;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
					else if(n==2){
						if(((fabs(sL->X1-X1)>SmallSigma || fabs(sL->Y1-Y1)>SmallSigma)
						&&  (fabs(sL->X2-X1)>SmallSigma || fabs(sL->Y2-Y1)>SmallSigma))
						&& ((fabs(sL->X1-X2)>SmallSigma || fabs(sL->Y1-Y2)>SmallSigma)
						&&  (fabs(sL->X2-X2)>SmallSigma || fabs(sL->Y2-Y2)>SmallSigma))){
							SparsLine	*L1=new SparsLine();
							L1->X1=X1;
							L1->Y1=Y1;
							L1->X2=X2;
							L1->Y2=Y2;
							s->Parent->InsertLater(sL,L1);
							SparsLineBasePointer	*sH1=new SparsLineBasePointer(L1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH1);
							
							SparsLine	*L2=new SparsLine();
							L2->X1=X2;
							L2->Y1=Y2;
							L2->X2=sL->X2;
							L2->Y2=sL->Y2;
							sL->X2=X1;
							sL->Y2=Y1;
							s->Parent->InsertLater(L1,L2);
							SparsLineBasePointer	*sH2=new SparsLineBasePointer(L2,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH2);
							Changed=true;
						}
						else if((fabs(sL->X1-X1)>SmallSigma || fabs(sL->Y1-Y1)>SmallSigma)
						     && (fabs(sL->X2-X1)>SmallSigma || fabs(sL->Y2-Y1)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X1;
							L1->Y1=Y1;
							L1->X2=sL->X2;
							L1->Y2=sL->Y2;
							sL->X2=X1;
							sL->Y2=Y1;
							s->Parent->InsertLater(sL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}
						else if((fabs(sL->X1-X2)>SmallSigma || fabs(sL->Y1-Y2)>SmallSigma)
						    && (fabs(sL->X2-X2)>SmallSigma || fabs(sL->Y2-Y2)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X2;
							L1->Y1=Y2;
							L1->X2=sL->X2;
							L1->Y2=sL->Y2;
							sL->X2=X2;
							sL->Y2=Y2;
							s->Parent->InsertLater(sL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}

						if(fabs(dA->StartAngle-Angle1)>SmallSigma && fabs(dA->EndAngle-Angle1)>SmallSigma
						&& fabs(dA->StartAngle-Angle2)>SmallSigma && fabs(dA->EndAngle-Angle2)>SmallSigma){
							if(dA->StartAngle>dA->EndAngle){
								if((Angle1<dA->EndAngle && Angle2<dA->EndAngle) || (Angle1>dA->StartAngle && Angle2>dA->StartAngle)){
									if(Angle1>Angle2)
										swap(Angle1,Angle2);
								}
								else{
									if(Angle1<Angle2)
										swap(Angle1,Angle2);
								}
							}
							else{
								if(Angle1>Angle2)
									swap(Angle1,Angle2);
							}
							SparsArc	*A1=new SparsArc();
							A1->Cx=dA->Cx;
							A1->Cy=dA->Cy;
							A1->R =dA->R;
							A1->StartAngle	=Angle1;
							A1->EndAngle	=Angle2;
							d->Parent->InsertLater(dA,A1);
							SparsLineBasePointer	*dH1=new SparsLineBasePointer(A1,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH1);
									
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle=Angle2;
							A2->EndAngle=dA->EndAngle;
							dA->EndAngle=Angle1;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH2=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH2);
							Changed=true;
						}
						else if(fabs(dA->StartAngle-Angle1)>SmallSigma && fabs(dA->EndAngle-Angle1)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle=Angle1;
							A2->EndAngle=dA->EndAngle;
							dA->EndAngle=Angle1;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
						else if(fabs(dA->StartAngle-Angle2)>SmallSigma && fabs(dA->EndAngle-Angle2)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle=Angle2;
							A2->EndAngle=dA->EndAngle;
							dA->EndAngle=Angle2;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
				}
			}
			else if(s->Pointer->GetClassType()==2){
				SparsArc	*sA=dynamic_cast<SparsArc *>(s->Pointer);
				if(d->Pointer->GetClassType()==1){
					SparsLine	*dL=dynamic_cast<SparsLine *>(d->Pointer);
					double	X1,Y1,X2,Y2;
					double	Angle1,Angle2;
						if(dL->GetLength2Point(DbgCrossX,DbgCrossY)<3
						&& sA->GetLength2Point(DbgCrossX,DbgCrossY)<3){
							DCodeDebug++;
						}
					int	n=CrossLineArc(  dL->X1,dL->Y1,dL->X2,dL->Y2
										,sA->Cx ,sA->Cy ,sA->R,sA->StartAngle ,sA->EndAngle
										,X1,Y1,X2,Y2
										,Angle1,Angle2);
					if(n==1){
						if((fabs(dL->X1-X1)>SmallSigma || fabs(dL->Y1-Y1)>SmallSigma)
						&& (fabs(dL->X2-X1)>SmallSigma || fabs(dL->Y2-Y1)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X1;
							L1->Y1=Y1;
							L1->X2=dL->X2;
							L1->Y2=dL->Y2;
							dL->X2=X1;
							dL->Y2=Y1;
							s->Parent->InsertLater(dL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,d->ItemID,d->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}

						if(fabs(sA->StartAngle-Angle1)>SmallSigma && fabs(sA->EndAngle-Angle1)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=sA->Cx;
							A2->Cy=sA->Cy;
							A2->R =sA->R;
							A2->StartAngle=Angle1;
							A2->EndAngle=sA->EndAngle;
							sA->EndAngle=Angle1;
							d->Parent->InsertLater(sA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,s->ItemID,s->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
					else if(n==2){
						if(((fabs(dL->X1-X1)>SmallSigma || fabs(dL->Y1-Y1)>SmallSigma)
						&&  (fabs(dL->X2-X1)>SmallSigma || fabs(dL->Y2-Y1)>SmallSigma))
						&& ((fabs(dL->X1-X2)>SmallSigma || fabs(dL->Y1-Y2)>SmallSigma)
						&&  (fabs(dL->X2-X2)>SmallSigma || fabs(dL->Y2-Y2)>SmallSigma))){
							SparsLine	*L1=new SparsLine();
							L1->X1=X1;
							L1->Y1=Y1;
							L1->X2=X2;
							L1->Y2=Y2;
							d->Parent->InsertLater(dL,L1);
							SparsLineBasePointer	*sH1=new SparsLineBasePointer(L1,d->ItemID,d->Parent);
							SparsListTable.AppendList(sH1);

							SparsLine	*L2=new SparsLine();
							L2->X1=X2;
							L2->Y1=Y2;
							L2->X2=dL->X2;
							L2->Y2=dL->Y2;
							dL->X2=X1;
							dL->Y2=Y1;
							d->Parent->InsertLater(L1,L2);
							SparsLineBasePointer	*sH2=new SparsLineBasePointer(L2,d->ItemID,d->Parent);
							SparsListTable.AppendList(sH2);
							Changed=true;
						}
						else if((fabs(dL->X1-X1)>SmallSigma || fabs(dL->Y1-Y1)>SmallSigma)
						     && (fabs(dL->X2-X1)>SmallSigma || fabs(dL->Y2-Y1)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X1;
							L1->Y1=Y1;
							L1->X2=dL->X2;
							L1->Y2=dL->Y2;
							dL->X2=X1;
							dL->Y2=Y1;
							s->Parent->InsertLater(dL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,d->ItemID,d->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}
						else if((fabs(dL->X1-X2)>SmallSigma || fabs(dL->Y1-Y2)>SmallSigma)
						     && (fabs(dL->X2-X2)>SmallSigma || fabs(dL->Y2-Y2)>SmallSigma)){
							SparsLine	*L1=new SparsLine();
							L1->X1=X2;
							L1->Y1=Y2;
							L1->X2=dL->X2;
							L1->Y2=dL->Y2;
							dL->X2=X2;
							dL->Y2=Y2;
							s->Parent->InsertLater(dL,L1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(L1,d->ItemID,d->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}

						if(fabs(sA->StartAngle-Angle1)>SmallSigma && fabs(sA->EndAngle-Angle1)>SmallSigma
						&& fabs(sA->StartAngle-Angle2)>SmallSigma && fabs(sA->EndAngle-Angle2)>SmallSigma){
							if(sA->StartAngle>sA->EndAngle){
								if((Angle1<sA->EndAngle && Angle2<sA->EndAngle) || (Angle1>sA->StartAngle && Angle2>sA->StartAngle)){
									if(Angle1>Angle2)
										swap(Angle1,Angle2);
								}
								else{
									if(Angle1<Angle2)
										swap(Angle1,Angle2);
								}
							}
							else{
								if(Angle1>Angle2)
									swap(Angle1,Angle2);
							}

							SparsArc	*A1=new SparsArc();
							A1->Cx=sA->Cx;
							A1->Cy=sA->Cy;
							A1->R =sA->R;
							A1->StartAngle	=Angle1;
							A1->EndAngle	=Angle2;
							s->Parent->InsertLater(sA,A1);
							SparsLineBasePointer	*dH1=new SparsLineBasePointer(A1,s->ItemID,s->Parent);
							SparsListTable.AppendList(dH1);

							SparsArc	*A2=new SparsArc();
							A2->Cx=sA->Cx;
							A2->Cy=sA->Cy;
							A2->R =sA->R;
							A2->StartAngle=Angle2;
							A2->EndAngle=sA->EndAngle;
							sA->EndAngle=Angle1;
							s->Parent->InsertLater(sA,A2);
							SparsLineBasePointer	*dH2=new SparsLineBasePointer(A2,s->ItemID,s->Parent);
							SparsListTable.AppendList(dH2);
							Changed=true;
						}
						else if(fabs(sA->StartAngle-Angle1)>SmallSigma && fabs(sA->EndAngle-Angle1)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=sA->Cx;
							A2->Cy=sA->Cy;
							A2->R =sA->R;
							A2->StartAngle=Angle1;
							A2->EndAngle=sA->EndAngle;
							sA->EndAngle=Angle1;
							d->Parent->InsertLater(sA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,s->ItemID,s->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
						else if(fabs(sA->StartAngle-Angle2)>SmallSigma && fabs(sA->EndAngle-Angle2)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=sA->Cx;
							A2->Cy=sA->Cy;
							A2->R =sA->R;
							A2->StartAngle=Angle2;
							A2->EndAngle=sA->EndAngle;
							sA->EndAngle=Angle2;
							d->Parent->InsertLater(sA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,s->ItemID,s->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
				}
				else if(d->Pointer->GetClassType()==2){
					SparsArc	*dA=dynamic_cast<SparsArc *>(d->Pointer);
					if(sA->OnOneArc(*dA)==true)
						continue;

					double	X1,Y1,X2,Y2;
					double	sAngle1,sAngle2;
					double	dAngle1,dAngle2;
					int	n=CrossArcArc(   sA->Cx ,sA->Cy ,sA->R,sA->StartAngle ,sA->EndAngle
										,dA->Cx ,dA->Cy ,dA->R,dA->StartAngle ,dA->EndAngle
										,sAngle1,sAngle2
										,dAngle1,dAngle2);
						if(sA->GetLength2Point(DbgCrossX,DbgCrossY)<2
						&& dA->GetLength2Point(DbgCrossX,DbgCrossY)<2){
							DCodeDebug++;
						}
					if(n==1){
						if(fabs(sA->StartAngle-sAngle1)>SmallSigma && fabs(sA->EndAngle-sAngle1)>SmallSigma){
							SparsArc	*A1=new SparsArc();
							A1->Cx=sA->Cx;
							A1->Cy=sA->Cy;
							A1->R =sA->R;
							A1->StartAngle	=sAngle1;
							A1->EndAngle	=sA->EndAngle;
							sA->EndAngle	=sAngle1;
							s->Parent->InsertLater(sA,A1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(A1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}
						if(fabs(dA->StartAngle-dAngle1)>SmallSigma && fabs(dA->EndAngle-dAngle1)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle	=dAngle1;
							A2->EndAngle	=dA->EndAngle;
							dA->EndAngle	=dAngle1;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
					else if(n==2){
						if(fabs(sA->StartAngle-sAngle1)>SmallSigma && fabs(sA->EndAngle-sAngle1)>SmallSigma
						&& fabs(sA->StartAngle-sAngle2)>SmallSigma && fabs(sA->EndAngle-sAngle2)>SmallSigma){
							if(sA->StartAngle>sA->EndAngle){
								if((sAngle1<sA->EndAngle && sAngle2<sA->EndAngle) || (sAngle1>sA->StartAngle && sAngle2>sA->StartAngle)){
									if(sAngle1>sAngle2)
										swap(sAngle1,sAngle2);
								}
								else{
									if(sAngle1<sAngle2)
										swap(sAngle1,sAngle2);
								}
							}
							else{
								if(sAngle1>sAngle2)
									swap(sAngle1,sAngle2);
							}

							SparsArc	*A11=new SparsArc();
							A11->Cx=sA->Cx;
							A11->Cy=sA->Cy;
							A11->R =sA->R;
							A11->StartAngle	=sAngle1;
							A11->EndAngle	=sAngle2;
							s->Parent->InsertLater(sA,A11);
							SparsLineBasePointer	*sH1=new SparsLineBasePointer(A11,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH1);

							SparsArc	*A12=new SparsArc();
							A12->Cx=sA->Cx;
							A12->Cy=sA->Cy;
							A12->R =sA->R;
							A12->StartAngle	=sAngle2;
							A12->EndAngle	=sA->EndAngle;
							sA->EndAngle	=sAngle1;
							s->Parent->InsertLater(sA,A12);
							SparsLineBasePointer	*sH2=new SparsLineBasePointer(A12,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH2);
							Changed=true;
						}
						else if(fabs(sA->StartAngle-sAngle1)>SmallSigma && fabs(sA->EndAngle-sAngle1)>SmallSigma){
							SparsArc	*A1=new SparsArc();
							A1->Cx=sA->Cx;
							A1->Cy=sA->Cy;
							A1->R =sA->R;
							A1->StartAngle	=sAngle1;
							A1->EndAngle	=sA->EndAngle;
							sA->EndAngle	=sAngle1;
							s->Parent->InsertLater(sA,A1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(A1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}
						else if(fabs(sA->StartAngle-sAngle2)>SmallSigma && fabs(sA->EndAngle-sAngle2)>SmallSigma){
							SparsArc	*A1=new SparsArc();
							A1->Cx=sA->Cx;
							A1->Cy=sA->Cy;
							A1->R =sA->R;
							A1->StartAngle	=sAngle2;
							A1->EndAngle	=sA->EndAngle;
							sA->EndAngle	=sAngle2;
							s->Parent->InsertLater(sA,A1);
							SparsLineBasePointer	*sH=new SparsLineBasePointer(A1,s->ItemID,s->Parent);
							SparsListTable.AppendList(sH);
							Changed=true;
						}

						if(fabs(dA->StartAngle-dAngle1)>SmallSigma && fabs(dA->EndAngle-dAngle1)>SmallSigma
						&& fabs(dA->StartAngle-dAngle2)>SmallSigma && fabs(dA->EndAngle-dAngle2)>SmallSigma){
							if(dA->StartAngle>dA->EndAngle){
								if((dAngle1<dA->EndAngle && dAngle2<dA->EndAngle) || (dAngle1>dA->StartAngle && dAngle2>dA->StartAngle)){
									if(dAngle1>dAngle2)
										swap(dAngle1,dAngle2);
								}
								else{
									if(dAngle1<dAngle2)
										swap(dAngle1,dAngle2);
								}
							}
							else{
								if(dAngle1>dAngle2)
									swap(dAngle1,dAngle2);
							}

							SparsArc	*A21=new SparsArc();
							A21->Cx=dA->Cx;
							A21->Cy=dA->Cy;
							A21->R =dA->R;
							A21->StartAngle	=dAngle1;
							A21->EndAngle	=dAngle2;
							d->Parent->InsertLater(dA,A21);
							SparsLineBasePointer	*dH1=new SparsLineBasePointer(A21,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH1);

							SparsArc	*A22=new SparsArc();
							A22->Cx=dA->Cx;
							A22->Cy=dA->Cy;
							A22->R =dA->R;
							A22->StartAngle	=dAngle2;
							A22->EndAngle	=dA->EndAngle;
							dA->EndAngle	=dAngle1;
							d->Parent->InsertLater(dA,A22);
							SparsLineBasePointer	*dH2=new SparsLineBasePointer(A22,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH2);
							Changed=true;
						}
						else if(fabs(dA->StartAngle-dAngle1)>SmallSigma && fabs(dA->EndAngle-dAngle1)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle	=dAngle1;
							A2->EndAngle	=dA->EndAngle;
							dA->EndAngle	=dAngle1;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
						else if(fabs(dA->StartAngle-dAngle2)>SmallSigma && fabs(dA->EndAngle-dAngle2)>SmallSigma){
							SparsArc	*A2=new SparsArc();
							A2->Cx=dA->Cx;
							A2->Cy=dA->Cy;
							A2->R =dA->R;
							A2->StartAngle	=dAngle2;
							A2->EndAngle	=dA->EndAngle;
							dA->EndAngle	=dAngle2;
							d->Parent->InsertLater(dA,A2);
							SparsLineBasePointer	*dH=new SparsLineBasePointer(A2,d->ItemID,d->Parent);
							SparsListTable.AppendList(dH);
							Changed=true;
						}
					}
				}
			}
		}
	}
	return Changed;
}

void	GerberFastInPage::MakeOutline(BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite)
{
	SparsContainerData.RemoveAll();

	int	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		GerberFileLayer	*F=FileLayerList[N];
		if(b->GetValue()==true && F!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						if(Item->GetID()==DbgID)
							DCodeDebug=1;
						SparsShape *OutlineShape=new SparsShape(Item->GetID());
						Item->MakeOutline(*OutlineShape);
						SparsContainerData.AppendList(OutlineShape);
					}
				}
			}
		}
	}

	bool	Changed;
	do{
		Changed=false;
		NPListPack<SparsLineBasePointer>  SparsListTable[SparsDivCountX][SparsDivCountY];

		SparsContainerData.RegisterOnTable(this,SparsListTable);
		for(int y=0;y<SparsDivCountY;y++){
			for(int x=0;x<SparsDivCountX;x++){
				if(ChopCross(SparsListTable[x][y])==true)
					Changed=true;
			}
		}
	}while(Changed==true);


	AlgorithmItemPointerListContainer	DPoint[SparsDivCountX][SparsDivCountY];

	int	TableXLen=GetDotPerLine()/SparsDivCountX;
	int	TableYLen=GetMaxLines()	 /SparsDivCountY;

	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		GerberFileLayer	*F=FileLayerList[N];
		if(b->GetValue()==true && F!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						if(Item->GetID()==DbgID)
							DCodeDebug=1;
						double	Lx1,Ly1,Lx2,Ly2;
						Item->GetXY(Lx1,Ly1,Lx2,Ly2);
						if(Lx2<0 || GetDotPerLine()<Lx1
						|| Ly2<0 || GetMaxLines()<Ly1)
							continue;
						int	iPx1=floor(Lx1/TableXLen);
						int	iPy1=floor(Ly1/TableYLen);
						int	iPx2=ceil (Lx2/TableXLen);
						int	iPy2=ceil (Ly2/TableYLen);
						iPx1	=Clipping(iPx1 ,0,SparsDivCountX-1);
						iPy1	=Clipping(iPy1 ,0,SparsDivCountY-1);
						iPx2	=Clipping(iPx2 ,0,SparsDivCountX-1);
						iPy2	=Clipping(iPy2 ,0,SparsDivCountY-1);
						for(int y=iPy1;y<=iPy2;y++){
							for(int x=iPx1;x<=iPx2;x++){
								if(Item->IsCrossed(x*TableXLen	 ,y*TableYLen
												 ,(x+1)*TableXLen,(y+1)*TableYLen)==true){
									DPoint[x][y].Add(Item);
								}
							}
						}
					}
				}
			}
		}
	}
	SparsContainerData.RemoveSpars(this,DPoint);
	SparsContainerData.RestructConnection();
	SparsContainerData.MakeID();

}

void	GerberFastInPage::MakeOutline(int LayerLibID)
{
	SparsContainerData.RemoveAll();

	int	N=0;
	for(GerberFileLayer	*F=FileLayerList.GetFirst();F!=NULL;F=F->GetNext(),N++){
		if(F->GetFileLayerID()==LayerLibID){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==LayerLibID){
						if(Item->GetID()==DbgID)
							DCodeDebug=1;
						SparsShape *OutlineShape=new SparsShape(Item->GetID());
						Item->MakeOutline(*OutlineShape);
						SparsContainerData.AppendList(OutlineShape);
					}
				}
			}
		}
	}

	bool	Changed;
	do{
		Changed=false;
		NPListPack<SparsLineBasePointer>  SparsListTable[SparsDivCountX][SparsDivCountY];

		SparsContainerData.RegisterOnTable(this,SparsListTable);
		for(int y=0;y<SparsDivCountY;y++){
			for(int x=0;x<SparsDivCountX;x++){
				if(ChopCross(SparsListTable[x][y])==true)
					Changed=true;
			}
		}
	}while(Changed==true);


	AlgorithmItemPointerListContainer	DPoint[SparsDivCountX][SparsDivCountY];

	int	TableXLen=GetDotPerLine()/SparsDivCountX;
	int	TableYLen=GetMaxLines()	 /SparsDivCountY;

	N=0;
	for(GerberFileLayer	*F=FileLayerList.GetFirst();F!=NULL;F=F->GetNext(),N++){
		if(F->GetFileLayerID()==LayerLibID){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==LayerLibID){
						if(Item->GetID()==DbgID)
							DCodeDebug=1;
						double	Lx1,Ly1,Lx2,Ly2;
						Item->GetXY(Lx1,Ly1,Lx2,Ly2);
						if(Lx2<0 || GetDotPerLine()<Lx1
						|| Ly2<0 || GetMaxLines()<Ly1)
							continue;
						int	iPx1=floor(Lx1/TableXLen);
						int	iPy1=floor(Ly1/TableYLen);
						int	iPx2=ceil (Lx2/TableXLen);
						int	iPy2=ceil (Ly2/TableYLen);
						iPx1	=Clipping(iPx1 ,0,SparsDivCountX-1);
						iPy1	=Clipping(iPy1 ,0,SparsDivCountY-1);
						iPx2	=Clipping(iPx2 ,0,SparsDivCountX-1);
						iPy2	=Clipping(iPy2 ,0,SparsDivCountY-1);
						for(int y=iPy1;y<=iPy2;y++){
							for(int x=iPx1;x<=iPx2;x++){
								if(Item->IsCrossed(x*TableXLen	 ,y*TableYLen
												 ,(x+1)*TableXLen,(y+1)*TableYLen)==true){
									DPoint[x][y].Add(Item);
								}
							}
						}
					}
				}
			}
		}
	}
	SparsContainerData.RemoveSpars(this,DPoint);
	SparsContainerData.RestructConnection();
	SparsContainerData.MakeID();

}
bool	IsClosed(double SPoint[][2],int ns ,double DPoint[][2],int nd ,int ConnInfo[2])
{
	for(int i=0;i<ns;i++){
		for(int j=0;j<nd;j++){
			double	dx=SPoint[i][0]-DPoint[j][0];
			double	dy=SPoint[i][1]-DPoint[j][1];
			if(dx*dx+dy*dy<OuterRate*OuterRate){
				ConnInfo[0]=i;
				ConnInfo[1]=j;
				return true;
			}
		}
	}
	return false;
}

void	MakeNode(GerberFastInPage *APage,NPListPack<SparsNode> &SparsNodeData,NPListPack<SparsLineBasePointer> &SparsListTable)
{
	APage->FastSearchIDItemStart();
	for(SparsLineBasePointer *s=SparsListTable.GetFirst();s!=NULL;s=s->GetNext()){
		double	SPoint[10][2];
		int ns=s->Pointer->GetEndPoint(SPoint);
		for(SparsLineBasePointer *d=s->GetNext();d!=NULL;d=d->GetNext()){
			double	DPoint[10][2];
			int nd=d->Pointer->GetEndPoint(DPoint);
			int ConnInfo[2];
			if(IsClosed(SPoint,ns ,DPoint,nd ,ConnInfo)==true){
				if(s->Pointer->ConnInfo[ConnInfo[0]]==false
				&& d->Pointer->ConnInfo[ConnInfo[1]]==false){
					AlgorithmItemRoot	*st=APage->FastSearchIDItem(s->ItemID);
					AlgorithmItemRoot	*dt=APage->FastSearchIDItem(d->ItemID);
					if(st!=NULL && dt!=NULL){
						GerberFastItemBase	*sItem=dynamic_cast<GerberFastItemBase *>(st);
						GerberFastItemBase	*dItem=dynamic_cast<GerberFastItemBase *>(dt);
						if(sItem!=NULL && dItem!=NULL){
							GerberFileLayer		*sFL=sItem->GetFileLayer();
							GerberFileLayer		*dFL=dItem->GetFileLayer();
							if(sFL!=NULL && dFL!=NULL && sFL->GetFileLayerID()==dFL->GetFileLayerID()){
								SparsNode	*a=new SparsNode();
								a->P1=s->Pointer;
								a->P2=d->Pointer;
								a->FLayer=sFL;
								a->ConnInfo[0]=ConnInfo[0];
								a->ConnInfo[1]=ConnInfo[1];
								s->Pointer->ConnInfo[ConnInfo[0]]=true;
								d->Pointer->ConnInfo[ConnInfo[1]]=true;
								SparsNodeData.AppendList(a);
							}
						}
					}
				}
			}
		}
	}
}

void	GerberFastInPage::MakeEchingFactor(BoolList &ButtonsToOperateLayer ,BoolList &ButtonsToOperateComposite
										  ,double EFactor)
{
	SparsContainerData.ClearConnInfo();

	NPListPack<SparsLineBasePointer>  SparsListTable[SparsDivCountX][SparsDivCountY];
	NPListPack<SparsNode>	SparsNodeData;

	SparsContainerData.RegisterOnTable(this,SparsListTable);
	for(int y=0;y<SparsDivCountY;y++){
		for(int x=0;x<SparsDivCountX;x++){
			MakeNode(this,SparsNodeData,SparsListTable[x][y]);
		}
	}

	AlgorithmItemPointerListContainer	DPoint[SparsDivCountX][SparsDivCountY];

	int	TableXLen=GetDotPerLine()/SparsDivCountX;
	int	TableYLen=GetMaxLines()	 /SparsDivCountY;

	int	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		GerberFileLayer	*F=FileLayerList[N];
		if(b->GetValue()==true && F!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						if(Item->GetID()==DbgID)
							DCodeDebug=1;
						double	Lx1,Ly1,Lx2,Ly2;
						Item->GetXY(Lx1,Ly1,Lx2,Ly2);
						if(Lx2<0 || GetDotPerLine()<Lx1
						|| Ly2<0 || GetMaxLines()<Ly1)
							continue;
						int	iPx1=floor(Lx1/TableXLen);
						int	iPy1=floor(Ly1/TableYLen);
						int	iPx2=ceil (Lx2/TableXLen);
						int	iPy2=ceil (Ly2/TableYLen);
						iPx1	=Clipping(iPx1 ,0,SparsDivCountX-1);
						iPy1	=Clipping(iPy1 ,0,SparsDivCountY-1);
						iPx2	=Clipping(iPx2 ,0,SparsDivCountX-1);
						iPy2	=Clipping(iPy2 ,0,SparsDivCountY-1);
						for(int y=iPy1;y<=iPy2;y++){
							for(int x=iPx1;x<=iPx2;x++){
								if(Item->IsCrossed(x*TableXLen	 ,y*TableYLen
												 ,(x+1)*TableXLen,(y+1)*TableYLen)==true){
									DPoint[x][y].Add(Item);
								}
							}
						}
					}
				}
			}
		}
	}
	AlgorithmItemPointerListContainer	AdditionalItems;
	for(SparsNode *s=SparsNodeData.GetFirst();s!=NULL;s=s->GetNext()){
		s->MakeEchingFactor(AdditionalItems,EFactor,DPoint);
	}
}


