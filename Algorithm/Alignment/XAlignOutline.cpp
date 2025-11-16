#include "XAlignmentResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignment.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XAlignOutline.h"
#include "XImageProcess.h"
#include "XInterpolation.h"
#include "XPickupPad.h"

VectorOutlineNode::VectorOutlineNode(void)
{	
	Px=0;
	Py=0;
	Vx=0;
	Vy=0;
	CurrentVLen=0;
}

void	VectorOutlineNode::SetPxy(int px,int py)
{
	Px=px;
	Py=py;
}
void	VectorOutlineNode::SetVxy(double vx,double vy)
{	
	Vx=vx;
	Vy=vy;	
	double	H=hypot(Vx,Vy);
	if(H>=0.00001){
		Vx=Vx/H;
		Vy=Vy/H;
	}
}

bool	VectorOutlineNode::CheckValidity(void)
{
	if(Vx<-1.0 || 1.0<Vx || Vy<-1.0 || 1.0<Vy){
		return false;
	}
	return true;
}

void	VectorOutlineNode::Initial(void)
{
	BYTE	*d=GetData();
	
	AddS=0;
	AddS2=0;
	for(int i=0;i<GetFLineLen();i++){
		int Numb=GetFLineNumb(i);
		int	iD=0;
		int	iD2=0;
		for(int k=0;k<Numb;k++){
			iD+=*d;
			iD2+=(*d)*(*d);
			d++;
		}
		AddS+=iD;
		AddS2+=iD2;
	}
	if(GetWidth()>10 && GetHeight()>10){
		d=GetData();
		XSep=2;
		YSep=2;
		Add2S=0;
		Add2S2=0;
		for(int i=0;i<GetFLineLen();i++){
			int Numb=GetFLineNumb(i);
			int	iD=0;
			int	iD2=0;
			if((GetFLineAbsY(i)&1)==0){
				int	x1=GetFLineLeftX(i);
				for(int k=0;k<Numb;k++){
					if((x1&1)==0){
						iD+=*d;
						iD2+=(*d)*(*d);
					}
					d++;
					x1++;
				}
			}
			else{
				d+=Numb;
			}
			Add2S+=iD;
			Add2S2+=iD2;
		}
	}
	else{
		d=GetData();
		Add2S=0;
		Add2S2=0;
		XSep=1;
		YSep=1;
		for(int i=0;i<GetFLineLen();i++){
			int Numb=GetFLineNumb(i);
			int	iD=0;
			int	iD2=0;
			int	x1=GetFLineLeftX(i);
			for(int k=0;k<Numb;k++){
				iD+=*d;
				iD2+=(*d)*(*d);
				d++;
				x1++;
			}
			Add2S+=iD;
			Add2S2+=iD2;
		}
	}
}

double	VectorOutlineNode::Match(ImageBuffer &Img ,int dx ,int dy, double VLen)
{
	dx+=Vx*VLen;
	dy+=Vy*VLen;

	int	N=0;
	BYTE	*s=GetData();
	double	AddD=0;
	double	AddD2=0;
	double	AddSD=0;

	int	LoopCount=GetFLineLen();

	for(int i=0;i<LoopCount;i++){
		int x1	=GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		int	y	=GetFLineAbsY(i);
		BYTE	*d=Img.GetY(y+dy)+x1+dx;
		int	iD=0;
		int	iD2=0;
		int	iSD=0;
		for(int k=0;k<Numb;k++){
			iD+=*d;
			iD2+=(*d)*(*d);
			iSD+=(*s)*(*d);
			s++;
			d++;
		}
		AddD+=iD;
		AddD2+=iD2;
		AddSD+=iSD;
		N+=Numb;
	}
	//?(ai-A)*(ai-A)=?ai*ai-N*A*A
	//?(ai-A)*(bi-B)=?ai*bi-N*A*B

	if(N==0){
		return 0;
	}
	double	A=AddS/N;
	double	B=AddD/N;
	double	K=(AddS2-N*A*A)*(AddD2-N*B*B);
	if(K<0.000001){
		return 0;
	}
	K=sqrt(K);
	return (AddSD-N*A*B)/K;
}

int	GBError;

double	VectorOutlineNode::MatchSep(ImageBuffer &Img ,int dx ,int dy, double VLen)
{
	if(dx<-100 || dx>100 || dy<-100 || dy>100){
		GBError++;
	}

	if(XSep==1 && YSep==1){
		return Match(Img ,dx ,dy, VLen);
	}
	dx+=Vx*VLen;
	dy+=Vy*VLen;

	int	N=0;
	BYTE	*s=GetData();
	double	AddD=0;
	double	AddD2=0;
	double	AddSD=0;

	int	LoopCount=GetFLineLen();

	for(int i=0;i<LoopCount;i++){
		int x1	=GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		int	y	=GetFLineAbsY(i);
		if((y&1)==0){
			BYTE	*d=Img.GetY(y+dy)+x1+dx;
			int	iD=0;
			int	iD2=0;
			int	iSD=0;
			for(int k=0;k<Numb;k++){
				if((x1&1)==0){
					iD+=*d;
					iD2+=(*d)*(*d);
					iSD+=(*s)*(*d);
					N++;
				}
				s++;
				d++;
				x1++;
			}
			AddD+=iD;
			AddD2+=iD2;
			AddSD+=iSD;
		}
		else{
			s+=Numb;
		}
	}
	//?(ai-A)*(ai-A)=?ai*ai-N*A*A
	//?(ai-A)*(bi-B)=?ai*bi-N*A*B

	double	A=Add2S/N;
	double	B=AddD/N;
	double	K=(Add2S2-N*A*A)*(AddD2-N*B*B);
	if(K<0.000001){
		return 0;
	}
	K=sqrt(K);
	return (AddSD-N*A*B)/K;
}

void	VectorOutlineNode::Draw(QImage &pnt,QRgb c, int movx ,int movy ,double ZoomRate)
{
	DrawAlpha(0,0,&pnt,c,ZoomRate ,movx ,movy);
	if(ZoomRate>=1.0){
		double	VLen=6;
		int	Lx=Px+Vx*VLen;
		int	Ly=Py+Vy*VLen;

		int	LocalX1=(Px+movx)*ZoomRate;
		int	LocalY1=(Py+movy)*ZoomRate;
		int	LocalX2=(Lx+movx)*ZoomRate;
		int	LocalY2=(Ly+movy)*ZoomRate;
		QPainter	Pnt(&pnt);

		Pnt.setPen(Qt::yellow);
		QBrush	Br(Qt::yellow);
		Pnt.setBrush(Br);
		Pnt.drawLine(LocalX1,LocalY1,LocalX2,LocalY2);

		double s=GetSita(LocalX1-LocalX2,LocalY1-LocalY2);
		QPoint	APoint[4];
		APoint[0].setX(LocalX2);
		APoint[0].setY(LocalY2);
		APoint[1].setX(LocalX2+20*cos(s+M_PI/6));
		APoint[1].setY(LocalY2+20*sin(s+M_PI/6));
		APoint[2].setX(LocalX2+10*cos(s));
		APoint[2].setY(LocalY2+10*sin(s));
		APoint[3].setX(LocalX2+20*cos(s-M_PI/6));
		APoint[3].setY(LocalY2+20*sin(s-M_PI/6));
		Pnt.drawPolygon (APoint,4);
	}
}
void	VectorOutlineNode::Draw(int dx ,int dy,QImage &pnt,QRgb c, int movx ,int movy ,double ZoomRate)
{
	DrawAlpha(dx+Vx*CurrentVLen,dy+Vy*CurrentVLen,&pnt,c,ZoomRate ,movx ,movy);
}

bool	VectorOutlineNode::Save(QIODevice *f)
{
	if(FlexAreaImage::Save(f)==false){
		return false;
	}
	if(::Save(f,Px)==false){
		return false;
	}
	if(::Save(f,Py)==false){
		return false;
	}
	if(::Save(f,Vx)==false){
		return false;
	}
	if(::Save(f,Vy)==false){
		return false;
	}
	return true;
}
bool	VectorOutlineNode::Load(QIODevice *f)
{
	if(FlexAreaImage::Load(f)==false){
		return false;
	}
	if(::Load(f,Px)==false){
		return false;
	}
	if(::Load(f,Py)==false){
		return false;
	}
	if(::Load(f,Vx)==false){
		return false;
	}
	if(::Load(f,Vy)==false){
		return false;
	}
	return true;
}
VectorOutlineNode	&VectorOutlineNode::operator=(VectorOutlineNode &src)
{
	FlexAreaImage::operator=(*((FlexAreaImage *)&src));
	AddS	=src.AddS;
	AddS2	=src.AddS2;
	Add2S	=src.Add2S	;
	Add2S2	=src.Add2S2	;
	XSep	=src.XSep	;
	YSep	=src.YSep	;
	Px		=src.Px;
	Py		=src.Py;
	Vx		=src.Vx;
	Vy		=src.Vy;
	CurrentVLen=src.CurrentVLen;
	return *this;
}

//======================================================================================

bool	VectorAlignmentItem::Set(FlexArea &Area
								,ImageBuffer &Img
								,int	DivCount
								,int	OutlineWidth
								)
{
	int BrList[256];
	int	XLen=Area.GetWidth();
	int	YLen=Area.GetHeight();

	RemoveAll();
	int	XBitLen	=XLen+2+OutlineWidth*2;
	int	YBitLen	=YLen+2+OutlineWidth*2;
	int	XByte	=(XBitLen+7)/8+1;
	BYTE	**RMap=MakeMatrixBuff(XByte,YBitLen);
	int	Mx=Area.GetMinX();
	int	My=Area.GetMinY();

	int	XNumb;
	int	YNumb;
	if(XLen>400 && YLen>400){
		for(int	Cell=100;Cell>=5;Cell/=2){
			XNumb=(XLen-Cell-1)/Cell;
			YNumb=(YLen-Cell-1)/Cell;
			if(XNumb>=2 && YNumb>=2){
				break;
			}
		}
	}
	else{
		XNumb=1;
		YNumb=1;
	}
	int	XCell=XLen/XNumb;
	int	YCell=YLen/YNumb;

	MatrixBuffClear(RMap,0,XByte,YBitLen);
	for(int yn=0;yn<YNumb;yn++){
		for(int xn=0;xn<XNumb;xn++){
			for(int i=0;i<sizeof(BrList)/sizeof(BrList[0]);i++){
				BrList[i]=0;
			}
			FlexArea	A=Area;
			A.ClipArea(Mx+xn*XCell,My+yn*YCell,Mx+(xn+1)*XCell,My+(yn+1)*YCell);
			A.MakeBrightList(BrList ,Img.GetWidth(),Img.GetHeight(),Img ,0,0);

			int	Col=MakeColorCenter(BrList);
			for(int i=0;i<A.GetFLineLen();i++){
				int	x1	=A.GetFLineLeftX(i);
				int	Numb=A.GetFLineNumb(i);
				int	y	=A.GetFLineAbsY(i);
				BYTE	*s=Img.GetY(y)+x1;
				int	ky=y-My+OutlineWidth+1;
				for(int x=0;x<Numb;x++){
					if(*s>=Col){
						int	kx=x1+x-Mx+OutlineWidth+1;
						SetBmpBit1(RMap,kx,ky);
					}
					s++;
				}
			}
		}
	}
	PureFlexAreaListContainer FPack;
	PickupFlexArea(RMap ,XByte ,XBitLen,YBitLen ,FPack);
	PureFlexAreaList	*MaxAreaPoint=NULL;
	int64				MaxDots=0;
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		int64	Dots=p->GetPatternByte();
		if(Dots>MaxDots){
			MaxDots=Dots;
			MaxAreaPoint=p;
		}
	}
		
	XYClassCluster	XY;
	XYClassArea	*C=NULL;
	if(MaxAreaPoint!=NULL){
		MaxAreaPoint->MakeOutlineDot(XY);
		int64		MaxDotCount=0;
		for(XYClassArea	*k=XY.GetFirst();k!=NULL;k=k->XYClassArea::GetNext()){
			//if(k->Positive==true){
				int64	dcount=k->GetDotCount();
				if(MaxDotCount<dcount){
					C=k;
					MaxDotCount=dcount;
				}
			//}
		}
	}
	if(C==NULL){
		C=XY.GetFirst();
	}
	if(C==NULL){
		return false;
	}

	BYTE	**RMap2=MakeMatrixBuff(XByte,YBitLen);
	/*
	MatrixBuffClear(RMap,0,XByte,YBitLen);
	MaxAreaPoint->MakeBitData(RMap,XBitLen,YBitLen);
	BYTE	**RMap3=MakeMatrixBuff(XByte,YBitLen);
	MatrixBuffCopy(RMap3,XByte,YBitLen
					,RMap,XByte,YBitLen);

	ThinArea(RMap3,RMap2,XByte,YBitLen);
	MatrixBuffNotAnd(RMap,RMap3,XByte,YBitLen);
	DeleteMatrixBuff(RMap3,YBitLen);
	*/

	int	CNumb=C->GetDotCount();
	if(CNumb<60){
		return false;
	}


	int	COneNumb=(CNumb+DivCount-1)/DivCount;

	XYClass	*c=C->GetFirstDot();
	for(int divcount=0;divcount<DivCount;divcount++){
		MatrixBuffClear(RMap,0,XByte,YBitLen);
		double	AddA=0;
		double	AddB=0;
		int	AddCount=0;
		int	Px=0;
		int	Py=0;
		for(int i=0;i<COneNumb && c!=NULL;i++){
			SetBmpBit1(RMap,c->x,c->y);
			if(i==COneNumb/2){
				Px+=c->x;
				Py+=c->y;
			}

			XYClass	*e=c;
			double x[16];
			double y[16];
			int	n=0;
			int	NAvr=4;
			for(int k=0;k<NAvr;k++){
				if(e==NULL){
					break;
				}
				x[n]=e->x;
				y[n]=e->y;
				n++;
				e=e->GetNext();
			}
			if(n<NAvr){
				break;
			}

			double A=0.0;
			double B=0.0;
			double C=0.0;
			if(MakeInterpolatedLine(x,y,n,A,B,C)==true){
				//(A,B)?I?@?u?x?N?g??
				int	mx=x[0]-x[n-1];
				int	my=y[0]-y[n-1];
				if(mx*B-my*A<=0){
					AddA+=A;
					AddB+=B;
				}
				else{
					AddA+=-A;
					AddB+=-B;
				}
				AddCount++;
			}
			c=c->GetNext();
		}

		if(AddCount>0){
			GetLayersBase()->FatAreaN(RMap,RMap2,XByte,YBitLen,OutlineWidth);
			
			VectorOutlineNode	*v=new VectorOutlineNode();
			v->SetPxy(Px+(Mx-OutlineWidth-1),Py+(My-OutlineWidth-1));
			v->SetVxy(AddA/AddCount,AddB/AddCount);
			v->BuildFromRaster(RMap,XByte,YBitLen,Mx-OutlineWidth-1,My-OutlineWidth-1);
			v->SetAndCalc(Img);
			AppendList(v);
		}
	}

	DeleteMatrixBuff(RMap2,YBitLen);
	DeleteMatrixBuff(RMap ,YBitLen);
	return true;
}


void	VectorAlignmentItem::Initial(void)
{
	for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->Initial();
	}
}

#define	VLenCount	100
struct	MatchingParamList
{
	int	dx,dy;
	double	VList[VLenCount];
	double	MatchRate;
};

double	VectorAlignmentItem::Match(ImageBuffer &Img 
								,int &Retdx ,int &Retdy
								,int SearchArea
								,int EachSearchDot)
{
	int	NMax=max(EachSearchDot,SearchArea);
	if(SearchArea>10){
		struct	MatchingParamList	*MatchingParam=new struct	MatchingParamList[(NMax+2)*(NMax+2)];
		int	N=0;
		for(int dy=-SearchArea;dy<=SearchArea;dy+=2){
			for(int dx=-SearchArea;dx<=SearchArea;dx+=2){
				MatchingParam[N].dx=dx;
				MatchingParam[N].dy=dy;
				N++;
			}
		}
		#pragma omp parallel for
		for(int i=0;i<N;i++){
			MatchingParam[i].MatchRate=MatchSepInside(Img
										,MatchingParam[i].dx ,MatchingParam[i].dy
										,EachSearchDot
										,MatchingParam[i].VList);
		}
		int	MaxPos=0;
		double	MaxRate=0;
		for(int i=0;i<N;i++){
			if(MaxRate<MatchingParam[i].MatchRate){
				MaxRate=MatchingParam[i].MatchRate;
				MaxPos=i;
			}
		}
		if(MaxRate<0.6){
			int	NN=0;
			if(MaxPos<N){
				for(int dy=MatchingParam[MaxPos].dy-EachSearchDot;dy<=MatchingParam[MaxPos].dy+EachSearchDot;dy++){
					for(int dx=MatchingParam[MaxPos].dx-EachSearchDot;dx<=MatchingParam[MaxPos].dx+EachSearchDot;dx++){
						MatchingParam[NN].dx=dx;
						MatchingParam[NN].dy=dy;
						NN++;
					}
				}
				N=NN;
			}
			#pragma omp parallel for
			for(int i=0;i<N;i++){
				MatchingParam[i].MatchRate=MatchSepInside(Img
											,MatchingParam[i].dx ,MatchingParam[i].dy
											,EachSearchDot
											,MatchingParam[i].VList);
			}
			MaxRate=0;
			for(int i=0;i<N;i++){
				if(MaxRate<MatchingParam[i].MatchRate){
					MaxRate=MatchingParam[i].MatchRate;
					MaxPos=i;
				}
			}
		}
		if(MaxPos<N){
			int	NN=0;
			for(int dy=MatchingParam[MaxPos].dy-1;dy<=MatchingParam[MaxPos].dy+1;dy++){
				for(int dx=MatchingParam[MaxPos].dx-1;dx<=MatchingParam[MaxPos].dx+1;dx++){
					MatchingParam[NN].dx=dx;
					MatchingParam[NN].dy=dy;
					NN++;
				}
			}
			N=NN;
		}
		#pragma omp parallel for
		for(int i=0;i<N;i++){
			MatchingParam[i].MatchRate=MatchInside(Img
										,MatchingParam[i].dx ,MatchingParam[i].dy
										,EachSearchDot
										,MatchingParam[i].VList);
		}
		MaxRate=0;
		for(int i=0;i<N;i++){
			if(MaxRate<MatchingParam[i].MatchRate){
				MaxRate=MatchingParam[i].MatchRate;
				MaxPos=i;
			}
		}
		Retdx=MatchingParam[MaxPos].dx;
		Retdy=MatchingParam[MaxPos].dy;
		N=0;
		for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
			c->CurrentVLen=MatchingParam[MaxPos].VList[N];
			N++;
		}
		double	Result=MatchingParam[MaxPos].MatchRate;
		delete	[]MatchingParam;
		return Result;
	}
	else{
		struct	MatchingParamList	*MatchingParam=new struct	MatchingParamList[(2*NMax+2)*(2*NMax+2)];
		int	N=0;
		for(int dy=-SearchArea;dy<=SearchArea;dy++){
			for(int dx=-SearchArea;dx<=SearchArea;dx++){
				MatchingParam[N].dx=dx;
				MatchingParam[N].dy=dy;
				N++;
			}
		}
		#pragma omp parallel for
		for(int i=0;i<N;i++){
			MatchingParam[i].MatchRate=MatchSepInside(Img
										,MatchingParam[i].dx ,MatchingParam[i].dy
										,EachSearchDot
										,MatchingParam[i].VList);
		}
		int	MaxPos;
		double	MaxRate=0;
		for(int i=0;i<N;i++){
			if(MaxRate<MatchingParam[i].MatchRate){
				MaxRate=MatchingParam[i].MatchRate;
				MaxPos=i;
			}
		}
		Retdx=MatchingParam[MaxPos].dx;
		Retdy=MatchingParam[MaxPos].dy;
		N=0;
		for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
			c->CurrentVLen=MatchingParam[MaxPos].VList[N];
			N++;
		}
		double	Result=MatchingParam[MaxPos].MatchRate;
		delete	[]MatchingParam;
		return Result;
	}
}
double	VectorAlignmentItem::MatchInside(ImageBuffer &Img
										,int dx ,int dy
										,int EachSearchDot
										,double VList[])
{
	double	MatchRate=1.0;
	int	n=0;
	for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
		double	MaxM=0;
		int		VPos=0;
		for(double v=-EachSearchDot;v<=EachSearchDot;v+=1.4142){
			double	M=c->Match(Img ,dx ,dy, v);
			if(MaxM<M){
				MaxM=M;
				VPos=v;
			}
		}
		VList[n]=VPos;
		n++;
		if(MaxM<0){
			MaxM=0;
		}
		MatchRate*=MaxM;
		if(n>=VLenCount){
			break;
		}
	}
	return MatchRate;
}

double	VectorAlignmentItem::MatchSepInside(ImageBuffer &Img
										,int dx ,int dy
										,int EachSearchDot
										,double VList[])
{
	double	MatchRate=1.0;
	int	n=0;
	for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
		double	MaxM=0;
		int		VPos=0;
		for(double v=-EachSearchDot;v<=EachSearchDot;v+=1.4142){
			double	M=c->MatchSep(Img ,dx ,dy, v);
			if(MaxM<M){
				MaxM=M;
				VPos=v;
			}
		}
		VList[n]=VPos;
		n++;
		if(MaxM<0){
			MaxM=0;
		}
		MatchRate*=MaxM;
	}
	return MatchRate;
}

bool	VectorAlignmentItem::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	VectorAlignmentItem::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		VectorOutlineNode	*v=new VectorOutlineNode();
		if(v->Load(f)==false){
			return false;
		}
		if(v->CheckValidity()==false){
			delete	v;
			continue;
		}
		AppendList(v);
	}
	return true;
}
	
void	VectorAlignmentItem::Draw(QImage &pnt ,QRgb col, int movx ,int movy ,double ZoomRate)
{
	for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->Draw(pnt,col, movx ,movy ,ZoomRate);
	}
}
void	VectorAlignmentItem::Draw(int dx ,int dy,QImage &pnt ,QRgb col, int movx ,int movy ,double ZoomRate)
{
	for(VectorOutlineNode *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->Draw(dx ,dy,pnt,col, movx ,movy ,ZoomRate);
	}
}
VectorAlignmentItem	&VectorAlignmentItem::operator=(VectorAlignmentItem &src)
{
	RemoveAll();
	for(VectorOutlineNode *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		VectorOutlineNode *v=new VectorOutlineNode();
		*v=*c;
		AppendList(v);
	}
	return *this;
}

void	VectorAlignmentItem::SetRefereneFrom(LayersBase *Base,VectorAlignmentItem *src,int OffsetX,int OffsetY)
{
	RemoveAll();
	for(VectorOutlineNode *c=src->GetFirst();c!=NULL;c=c->GetNext()){
		VectorOutlineNode *v=new VectorOutlineNode();
		v->SetRefereneFrom(c);
		int	Page=Parent->GetPage();
		v->MoveToClip(OffsetX,OffsetY,0,0,Base->GetDotPerLine(Page),Base->GetMaxLines(Page));
		AppendList(v);
	}
}
