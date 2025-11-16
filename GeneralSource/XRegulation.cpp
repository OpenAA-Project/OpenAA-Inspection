#include "XTypeDef.h"
#include "XRegulation.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "swap.h"
#include <Dense>
using namespace Eigen;

bool	XYRegPoint::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;
	if(::Save(f,NumX)==false)
		return false;
	if(::Save(f,NumY)==false)
		return false;

	return true;
}

bool	XYRegPoint::SaveLink(QIODevice *f)
{
	int32	IDLeft	=(LinkLeft	==NULL)?-1:LinkLeft	 ->ID;
	int32	IDTop	=(LinkTop	==NULL)?-1:LinkTop	 ->ID;
	int32	IDRight	=(LinkRight	==NULL)?-1:LinkRight ->ID;
	int32	IDBottom=(LinkBottom==NULL)?-1:LinkBottom->ID;

	if(::Save(f,IDLeft)==false)
		return false;
	if(::Save(f,IDTop)==false)
		return false;
	if(::Save(f,IDRight)==false)
		return false;
	if(::Save(f,IDBottom)==false)
		return false;

	return true;
}

bool	XYRegPoint::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	if(::Load(f,NumX)==false)
		return false;
	if(::Load(f,NumY)==false)
		return false;
	return true;
}
bool	XYRegPointLoader::LoadLink(QIODevice *f)
{
	if(::Load(f,IDLeft)==false)
		return false;
	if(::Load(f,IDTop)==false)
		return false;
	if(::Load(f,IDRight)==false)
		return false;
	if(::Load(f,IDBottom)==false)
		return false;
	return true;
}

class	XYRegPointPointer : public NPList<XYRegPointPointer>
{
public:
	XYRegPoint	*Pointer;

	XYRegPointPointer(XYRegPoint *p):Pointer(p){}

	virtual	int	Compare(XYRegPointPointer &src)
	{
		if(Pointer->y<src.Pointer->y)
			return -1;
		if(Pointer->y>src.Pointer->y)
			return 1;
		if(Pointer->x<src.Pointer->x)
			return -1;
		if(Pointer->x>src.Pointer->x)
			return 1;
		return 0;

	}
};

class	XYRegPointPointerChain : public NPList<XYRegPointPointerChain> , public NPListPack<XYRegPointPointer>
{
public:
};
static	int SortFuncX(const XYRegPointPointer **a,const XYRegPointPointer **b)
{
	if(a[0]->Pointer->x<b[0]->Pointer->x)
		return -1;
	if(a[0]->Pointer->x>b[0]->Pointer->x)
		return 1;
	return 0;
}

class	XYRegPointPointerXPointer : public NPList<XYRegPointPointerXPointer>
{
public:
	XYRegPointPointer	*Pointer;

	XYRegPointPointerXPointer(XYRegPointPointer *p):Pointer(p){}

	virtual	int	Compare(XYRegPointPointerXPointer &src)
	{
		if(Pointer->Pointer->x<src.Pointer->Pointer->x)
			return -1;
		if(Pointer->Pointer->x>src.Pointer->Pointer->x)
			return 1;
		return 0;
	}
};

XYRegPointContainer::XYRegPointContainer(void)
{
	RealXmm		=0.0;
	RealYmm		=0.0;
	OffsetRealX	=0.0;
	OffsetRealY	=0.0;
	MinLenX		=0;
	MinLenY		=0;
	UnitIndex	=-1;
	UnitFigure	=2;
}

static	int	DoubleSortFunc(const void *a , const void *b)
{
	double	*ap=(double *)a;
	double	*bp=(double *)b;
	if(*ap<*bp)
		return -1;
	if(*ap>*bp)
		return 1;
	return 0;
}

bool	XYRegPointContainer::MakeNumerize(double _RealXmm, double _RealYmm ,int ImageWidth ,int ImageHeight 
										 ,double RotRate)
{
	int	N=GetCount()*GetCount()*0.5;
	double	*XLenDim=new double[N];
	double	*YLenDim=new double[N];
	int	XLenNumb=0;
	int	YLenNumb=0;
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(XYRegPoint *b=a->GetNext();b!=NULL;b=b->GetNext()){
			double	LenX=fabs(a->x-b->x);
			double	LenY=fabs(a->y-b->y);
			if(LenX>LenY){
				XLenDim[XLenNumb]=LenX;
				XLenNumb++;
			}
			if(LenY>LenX){
				YLenDim[YLenNumb]=LenY;
				YLenNumb++;
			}
		}
	}
	QSort(XLenDim,XLenNumb,sizeof(double),DoubleSortFunc);
	QSort(YLenDim,YLenNumb,sizeof(double),DoubleSortFunc);

	int	XPoint=XLenNumb/100;
	if(XPoint<5)
		XPoint=min(4,XLenNumb-1);
	if(XPoint>20)
		XPoint=20;
	int	YPoint=YLenNumb/100;
	if(YPoint<5)
		YPoint=min(4,YLenNumb-1);
	if(YPoint>20)
		YPoint=20;
	MinLenX=XLenDim[XPoint];
	MinLenY=YLenDim[YPoint];;

	delete	[]XLenDim;
	delete	[]YLenDim;

	/*
	MinLenX=99999999;
	MinLenY=99999999;
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(XYRegPoint *b=a->GetNext();b!=NULL;b=b->GetNext()){
			double	LenX=fabs(a->x-b->x);
			double	LenY=fabs(a->y-b->y);
			if(LenX<MinLenX && LenX>LenY){
				MinLenX=LenX;
			}
			if(LenY<MinLenY && LenY>LenX){
				MinLenY=LenY;
			}
		}
	}
	*/

	double	ClosedX=MinLenX*RotRate;
	double	ClosedY=MinLenY*RotRate;
	double	ClosedMaxX=MinLenX/RotRate;
	//double	ClosedMaxY=MinLenY/RotRate;

	NPListPack<XYRegPointPointerChain>	ChainContainer;

	XYRegPointPointerChain	ListH;
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->NumX=-10000;
		a->NumY=-10000;
		ListH.AppendList(new XYRegPointPointer(a));
	}
	ListH.Sort();	//Sort by Y

	while(ListH.GetCount()!=0){
		XYRegPointPointer	*ah=ListH.NPListPack<XYRegPointPointer>::GetFirst();
		ListH.RemoveList(ah);
		XYRegPointPointerChain	*YLine=new XYRegPointPointerChain();
		YLine->AppendList(ah);

		XYRegPointPointerXPointer	*m;
		//LeftSide
		XYRegPointPointer	*A=ah;
		do{
			double	ty2=A->Pointer->y+ClosedY;
			double	rx1=A->Pointer->x-(ClosedMaxX-ClosedX);
			NPListPack<XYRegPointPointerXPointer>	TmpPack;
			for(XYRegPointPointer *b=ListH.NPListPack<XYRegPointPointer>::GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Pointer->y>ty2)
					break;
				if(rx1<=b->Pointer->x && b->Pointer->x<=(A->Pointer->x+ClosedX)){
					TmpPack.AppendList(new XYRegPointPointerXPointer(b));
				}
			}
			TmpPack.Sort();	//Sort by X
			m=TmpPack.GetLast();
			if(m!=NULL){
				XYRegPointPointer	*t=m->Pointer;
				ListH.RemoveList(t);
				YLine->AppendList(t);
				A=t;
			}
		}while(m!=NULL);

		//RightSide
		A=ah;
		do{
			double	ty2=A->Pointer->y+ClosedY;
			double	rx2=A->Pointer->x+(ClosedMaxX-ClosedX);
			NPListPack<XYRegPointPointerXPointer>	TmpPack;
			for(XYRegPointPointer *b=ListH.NPListPack<XYRegPointPointer>::GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Pointer->y>ty2)
					break;
				if((A->Pointer->x-ClosedX)<=b->Pointer->x && b->Pointer->x<rx2){
					TmpPack.AppendList(new XYRegPointPointerXPointer(b));
				}
			}
			TmpPack.Sort();	//Sort by X
			m=TmpPack.GetFirst();
			if(m!=NULL){
				XYRegPointPointer	*t=m->Pointer;
				ListH.RemoveList(t);
				YLine->AppendList(t);
				A=t;
			}
		}while(m!=NULL);

		YLine->Sort(SortFuncX);	//Sort by X
		ChainContainer.AppendList(YLine);
	}

	int	NumY=0;
	XYRegPointPointerChain *am=ChainContainer.GetFirst();
	if(am!=NULL){
		for(XYRegPointPointer *p=am->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
			p->Pointer->NumY=NumY;
		}
		XYRegPointPointer *pFirst=am->NPListPack<XYRegPointPointer>::GetFirst();
		if(pFirst!=NULL){
			pFirst->Pointer->NumX=0;
		
			int	NumX=0;
			for(XYRegPointPointer *p=pFirst->GetNext();p!=NULL;p=p->GetNext()){
				double	XLen=p->Pointer->x - p->GetPrev()->Pointer->x;
				int	XN= (XLen+ClosedX)/MinLenX;
				NumX+=XN;
				p->Pointer->NumX = NumX;
			}
		}

		for(XYRegPointPointer *p=am->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
			XYRegPointPointer *q=p->GetNext();
			if(q!=NULL){
				p->Pointer->LinkRight=q->Pointer;
				q->Pointer->LinkLeft =p->Pointer;
			}
		}

		for(XYRegPointPointerChain *L=am->GetNext();L!=NULL;L=L->GetNext()){
			XYRegPointPointerChain *LastLine=NULL;
			double	MinLen=99999999;
			for(XYRegPointPointerChain *r=ChainContainer.GetFirst();r!=L;r=r->GetNext()){
				for(XYRegPointPointer *p=r->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
					for(XYRegPointPointer *q=L->NPListPack<XYRegPointPointer>::GetFirst();q!=NULL;q=q->GetNext()){
						//double	YLen=fabs(p->Pointer->y - q->Pointer->y);
						//double	XLen=fabs(p->Pointer->x - q->Pointer->x);
						//if((XLen<ClosedX && YLen<ClosedMaxY) || (YLen<ClosedY && XLen<ClosedMaxX)){
							double	DLen=hypot(p->Pointer->x - q->Pointer->x ,p->Pointer->y - q->Pointer->y);
							if(MinLen>DLen){
								MinLen=DLen;
								LastLine=r;
							}
						//}
					}
				}
			}
			if(LastLine==NULL){
				LastLine=L->GetPrev();
			}
			double	MinY=99999999;
			for(XYRegPointPointer *p=LastLine->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
				NumY=p->Pointer->NumY;
				for(XYRegPointPointer *q=L->NPListPack<XYRegPointPointer>::GetFirst();q!=NULL;q=q->GetNext()){
					double	XLen=fabs(p->Pointer->x - q->Pointer->x);
					if(XLen<ClosedX){
						double	YLen=q->Pointer->y - p->Pointer->y;
						if(MinY>YLen && YLen>0){
							MinY=YLen;
						}
					}
				}
			}
			int	YN=(MinY+ClosedY)/MinLenY;
			NumY+=YN;
			for(XYRegPointPointer *p=L->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
				p->Pointer->NumY=NumY;
			}
			for(XYRegPointPointer *p=L->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
				XYRegPointPointer *q=p->GetNext();
				if(q!=NULL){
					p->Pointer->LinkRight=q->Pointer;
					q->Pointer->LinkLeft =p->Pointer;
				}
			}

			for(XYRegPointPointer *p=LastLine->NPListPack<XYRegPointPointer>::GetFirst();p!=NULL;p=p->GetNext()){
				double	MinX=99999999;
				XYRegPointPointer *h=NULL;
				for(XYRegPointPointer *q=L->NPListPack<XYRegPointPointer>::GetFirst();q!=NULL;q=q->GetNext()){
					double	XLen=fabs(p->Pointer->x - q->Pointer->x);
					if(XLen<ClosedX && MinX>XLen){
						MinX=XLen;
						h=q;
					}
				}
				if(h!=NULL){
					p->Pointer->LinkBottom=h->Pointer;
					h->Pointer->LinkTop	  =p->Pointer;
					h->Pointer->NumX=p->Pointer->NumX;
				}
			}
		}

		bool	TotolFound;
		do{
			TotolFound=false;
			bool	Found;
			do{
				Found=false;
				for(XYRegPoint *t=GetFirst();t!=NULL;t=t->GetNext()){
					if(t->NumX<=-10000){
						if(t->LinkTop!=NULL && t->LinkTop->NumX>=0){
							t->NumX=t->LinkTop->NumX;
							Found=true;
							TotolFound=true;
						}
					}
				}
			}while(Found==true);

			do{
				Found=false;
				for(XYRegPoint *t=GetFirst();t!=NULL;t=t->GetNext()){
					if(t->NumX<=-10000){
						if(t->LinkBottom!=NULL && t->LinkBottom->NumX>=0){
							t->NumX=t->LinkBottom->NumX;
							Found=true;
							TotolFound=true;
						}
					}
				}
			}while(Found==true);

			do{
				Found=false;
				for(XYRegPoint *t=GetFirst();t!=NULL;t=t->GetNext()){
					if(t->NumX<=-10000){
						if(t->LinkLeft!=NULL && t->LinkLeft->NumX>=0){
							double	XLen=t->x - t->LinkLeft->x;
							int	XN= (XLen+ClosedX)/MinLenX;
							t->NumX = t->LinkLeft->NumX+XN;
							Found=true;
							TotolFound=true;
						}
					}
				}
			}while(Found==true);

			do{
				Found=false;
				for(XYRegPoint *t=GetFirst();t!=NULL;t=t->GetNext()){
					if(t->NumX<=-10000){
						if(t->LinkRight!=NULL && t->LinkRight->NumX>=0){
							double	XLen=t->LinkRight->x - t->x;
							int	XN= (XLen+ClosedX)/MinLenX;
							t->NumX = t->LinkRight->NumX-XN;
							Found=true;
							TotolFound=true;
						}
					}
				}
			}while(Found==true);
		}while(TotolFound==true);

		for(XYRegPoint *t=GetFirst();t!=NULL;){
			XYRegPoint *NextT=t->GetNext();
			if(t->NumX<=-10000){
				RemoveList(t);
				delete	t;
			}
			t=NextT;
		}
		int	MinX=99999999;
		for(XYRegPoint *t=GetFirst();t!=NULL;t=t->GetNext()){
			if(t->NumX<MinX){
				MinX=t->NumX;
			}
		}
		if(MinX<=-10000){
			return false;
		}
		int32	ID=0;
		for(XYRegPoint *t=GetFirst();t!=NULL;t=t->GetNext()){
			t->NumX-=MinX;
			t->ID=ID++;
		}

		RealXmm	=_RealXmm;
		RealYmm	=_RealYmm;

		OffsetRealX	=0.0;
		OffsetRealY	=0.0;
		double	MinOffsetRealX=99999999;
		double	MinOffsetRealY=99999999;
		for(int y=0;y<ImageHeight;y++){
			double realX ,realY;
			TransformImageToReal(0 ,y ,realX ,realY);
			if(realX<MinOffsetRealX)
				MinOffsetRealX=realX;
			if(realY<MinOffsetRealY)
				MinOffsetRealY=realY;
		}
		for(int x=0;x<ImageWidth;x++){
			double realX ,realY;
			TransformImageToReal(x ,0 ,realX ,realY);
			if(realX<MinOffsetRealX)
				MinOffsetRealX=realX;
			if(realY<MinOffsetRealY)
				MinOffsetRealY=realY;
		}
		OffsetRealX=-MinOffsetRealX;
		OffsetRealY=-MinOffsetRealY;
		return true;
	}
	return false;
}

bool	XYRegPointContainer::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,RealXmm)==false)
		return false;
	if(::Save(f,RealYmm)==false)
		return false;
	if(::Save(f,OffsetRealX)==false)
		return false;
	if(::Save(f,OffsetRealY)==false)
		return false;

	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
		if(a->SaveLink(f)==false){
			return false;
		}
	}
	if(::Save(f,UnitIndex)==false)
		return false;
	if(::Save(f,UnitFigure)==false)
		return false;
	return true;
}
bool	XYRegPointContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,RealXmm)==false)
		return false;
	if(::Load(f,RealYmm)==false)
		return false;
	if(::Load(f,OffsetRealX)==false)
		return false;
	if(::Load(f,OffsetRealY)==false)
		return false;

	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;

	for(int i=0;i<N;i++){
		XYRegPointLoader	*a=new XYRegPointLoader();
		if(a->Load(f)==false){
			return false;
		}
		if(a->LoadLink(f)==false){
			return false;
		}
		AppendList(a);
	}
	if(::Load(f,UnitIndex)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,UnitFigure)==false)
			return false;
	}
	MakeLinkByLoader();
	return true;
}

void	XYRegPointContainer::MakeLinkByLoader(void)
{
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		XYRegPointLoader	*t=(XYRegPointLoader *)a;
		if(t->IDLeft>=0){
			for(XYRegPoint *b=GetFirst();b!=NULL;b=b->GetNext()){
				if(b->ID==t->IDLeft){
					a->LinkLeft=b;
					break;
				}
			}
		}
		if(t->IDTop>=0){
			for(XYRegPoint *b=GetFirst();b!=NULL;b=b->GetNext()){
				if(b->ID==t->IDTop){
					a->LinkTop=b;
					break;
				}
			}
		}
		if(t->IDRight>=0){
			for(XYRegPoint *b=GetFirst();b!=NULL;b=b->GetNext()){
				if(b->ID==t->IDRight){
					a->LinkRight=b;
					break;
				}
			}
		}
		if(t->IDBottom>=0){
			for(XYRegPoint *b=GetFirst();b!=NULL;b=b->GetNext()){
				if(b->ID==t->IDBottom){
					a->LinkBottom=b;
					break;
				}
			}
		}
	}
}

bool	XYRegPointContainer::TransformImageToReal(int imagex ,int imagey ,double &realX ,double &realY)	const
{
	/*
		RX1 RX2 RX3		a b c	x1 x2 x3
		RY1 RY2 RY3   =	d e f * y1 y2 y3
		C1  C2  C3		g h i	1  1  1
	*/

	if(GetCount()>=3){
		XYRegPoint	*L1=NULL;
		XYRegPoint	*L2=NULL;
		double	MinL1=99999999;
		double	MinL2=99999999;
		for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
			double	L=hypot(a->x-imagex,a->y-imagey);
			if(MinL1>L){
				L2=L1;
				MinL2=MinL1;
				MinL1=L;
				L1=a;
			}
			else if(MinL2>L){
				MinL2=L;
				L2=a;
			}
		}
		if(L1!=NULL && L2!=NULL){
			XYRegPoint	*L3=NULL;
			double	MinL3=99999999;
			double	vlen=hypot(L1->x-L2->x,L1->y-L2->y);
			double	HLen=vlen*0.3;

			for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
				double	L=hypot(a->x-imagex,a->y-imagey);
				if(MinL3>L
				&& GetLengthLimitlessLine2Point(L1->x,L1->y,L2->x,L2->y,a->x,a->y)>HLen){
				//&& GetLengthLimitlessLine2Point(L1->NumX,L1->NumY,L2->NumX,L2->NumY,a->NumX,a->NumY)>5){
					MinL3=L;
					L3=a;
				}
			}
			if(L3!=NULL){
				MatrixXd R(3,3);
				MatrixXd I(3,3);
				MatrixXd A(3,3);

				R(0,0)=L1->NumX*RealXmm+OffsetRealX;
				R(1,0)=L1->NumY*RealYmm+OffsetRealY;
				R(2,0)=1.0;
				R(0,1)=L2->NumX*RealXmm+OffsetRealX;
				R(1,1)=L2->NumY*RealYmm+OffsetRealY;
				R(2,1)=1.0;
				R(0,2)=L3->NumX*RealXmm+OffsetRealX;
				R(1,2)=L3->NumY*RealYmm+OffsetRealY;
				R(2,2)=1.0;

				I(0,0)=L1->x;
				I(1,0)=L1->y;
				I(2,0)=1.0;
				I(0,1)=L2->x;
				I(1,1)=L2->y;
				I(2,1)=1.0;
				I(0,2)=L3->x;
				I(1,2)=L3->y;
				I(2,2)=1.0;

				A=R*I.inverse();
				
				MatrixXd X(3,1);
				MatrixXd Ret(3,1);

				X(0,0)=imagex;
				X(1,0)=imagey;
				X(2,0)=1;
				Ret=A*X;
				realX=Ret(0,0);
				realY=Ret(1,0);
				return true;
			}
		}
	}
	return false;
}

bool	XYRegPointContainer::TransformRealToImage(double realX ,double realY ,int &imagex ,int &imagey)	const
{
	double MinImageX,MinImageY,MaxImageX,MaxImageY;
	if(GetXY(MinImageX,MinImageY,MaxImageX,MaxImageY)==false){
		return false;
	}
	double	realX00,realY00;
	double	realX01,realY01;
	double	realX10,realY10;
	double	realX11,realY11;

	for(int i=0;i<20;i++){
		double	W=MaxImageX-MinImageX;
		double	H=MaxImageY-MinImageY;
		double	ImageX00=MinImageX+W/4;
		double	ImageY00=MinImageY+H/4;
		double	ImageX01=MaxImageX-W/4;
		double	ImageY01=MinImageY+H/4;
		double	ImageX10=MinImageX+W/4;
		double	ImageY10=MaxImageY-H/4;
		double	ImageX11=MaxImageX-W/4;
		double	ImageY11=MaxImageY-H/4;

		if(TransformImageToReal(ImageX00,ImageY00,realX00,realY00)==false){	return false;	}
		if(TransformImageToReal(ImageX01,ImageY01,realX01,realY01)==false){	return false;	}
		if(TransformImageToReal(ImageX10,ImageY10,realX10,realY10)==false){	return false;	}
		if(TransformImageToReal(ImageX11,ImageY11,realX11,realY11)==false){	return false;	}

		double	D00=hypot(realX00-realX,realY00-realY);
		double	D01=hypot(realX01-realX,realY01-realY);
		double	D10=hypot(realX10-realX,realY10-realY);
		double	D11=hypot(realX11-realX,realY11-realY);

		if(D00<=D01 && D00<=D10 && D00<=D11){
			MaxImageX=MinImageX+W/2;
			MaxImageY=MinImageY+H/2;
		}
		if(D01<=D00 && D01<=D10 && D01<=D11){
			MinImageX=MinImageX+W/2;
			MaxImageY=MinImageY+H/2;
		}
		if(D10<=D01 && D10<=D00 && D10<=D11){
			MaxImageX=MinImageX+W/2;
			MinImageY=MinImageY+H/2;
		}
		else{
			MinImageX=MinImageX+W/2;
			MinImageY=MinImageY+H/2;
		}
	}
	realX=(realX00+realX01+realX10+realX11)/4;
	realY=(realY00+realY01+realY10+realY11)/4;
	
	return true;
}

bool	XYRegPointContainer::GetXY(double &MinImageX,double &MinImageY,double &MaxImageX,double &MaxImageY)	const
{
	if(GetCount()==0){
		return false;
	}
	MinImageX=99999999;
	MinImageY=99999999;
	MaxImageX=-99999999;
	MaxImageY=-99999999;
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->x<MinImageX){
			MinImageX=a->x;
		}
		if (a->y<MinImageY) {
			MinImageY=a->y;
		}
		if (a->x>MaxImageX) {
			MaxImageX=a->x;
		}
		if(a->y>MaxImageY){
			MaxImageY=a->y;
		}
	}
	return true;
}

XYRegPoint	*XYRegPointContainer::GetClosedPoints(int imagex ,int imagey)
{
	XYRegPoint *Ret=NULL;
	double		MinLen=9999999999;
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		double	D=hypot(a->x-imagex,a->y-imagey);
		if(D<MinLen){
			MinLen=D;
			Ret=a;
		}
	}
	return Ret;
}

XYRegPointContainer	&XYRegPointContainer::operator=(const XYRegPointContainer &src)
{
	RealXmm		=src.RealXmm	;	
	RealYmm		=src.RealYmm	;
	OffsetRealX	=src.OffsetRealX;
	OffsetRealY	=src.OffsetRealY;
	UnitIndex	=src.UnitIndex;
	UnitFigure	=src.UnitFigure;
	RemoveAll();
	for(XYRegPoint *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		XYRegPointLoader	*b=new XYRegPointLoader();
		b->XYRegPoint::operator=(*a);
		b->IDLeft	=(a->LinkLeft	==NULL)?-1:a->LinkLeft	->ID;
		b->IDTop	=(a->LinkTop	==NULL)?-1:a->LinkTop	->ID;
		b->IDRight	=(a->LinkRight	==NULL)?-1:a->LinkRight	->ID;
		b->IDBottom	=(a->LinkBottom	==NULL)?-1:a->LinkBottom->ID;
		AppendList(b);
	}
	MakeLinkByLoader();
	
	return *this;
}

void	XYRegPointContainer::RemovePoint(XYRegPoint *p)
{
	for(XYRegPoint *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LinkTop==p){
			a->LinkTop=p->LinkTop;
		}
		if(a->LinkBottom==p){
			a->LinkBottom=p->LinkBottom;
		}
		if(a->LinkLeft==p){
			a->LinkLeft=p->LinkLeft;
		}
		if(a->LinkRight==p){
			a->LinkRight=p->LinkRight;
		}
	}
	RemoveList(p);
}

QString	XYRegPointContainer::GetUnitName(void)	const
{
	if(UnitIndex==0)	return /**/"cm";
	if(UnitIndex==1)	return /**/"mm";
	if(UnitIndex==2)	return /**/"um";
	if(UnitIndex==3)	return /**/"m";
	return /**/"";
}