//#include "XAlignmentLargeResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentLarge.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XMultiEquSolve.h"
#include "XCrossObj.h"
#include "XAffin.h"
#include "XImageProcess.h"
#include "XPacketAlignmentLarge.h"
#include<omp.h>

extern	const	char	*sRoot;
extern	const	char	*sName;


//==========================================================================================


XAlignmentLargeArea::XAlignmentLargeArea(void)
{
	LibID			=-1;
	MaxSearchAreaFromItem=0;
    AreaID			=-1;
	MasterNo		=0;
	Priority		=_PriorityMiddle;
	ParentInLayer	=NULL;
	PartsID			=-1;
	PartsAllocID	=-1;
	PartsAreaID		=-1;
	Locked			=false;
	Selected		=false;
	Active			=false;
	ManualCreated	=false;
	MultiSelection	=false;
	Visible			=true;
	Origin			=NULL;
	ALResultNumb	=0;
	ALResultAllocatedNumb	=MaxGPackNumb;
	ALResult		=new AlignmentLargeResultClass[MaxGPackNumb];
	DependingGlobal	=NULL;
	GroupMode		=false;
	GPackClassNumb	=0;
	GPackClass		=new XAlignmentLargePointerContainer[MaxGPackNumb];
	ResultPointCounts=_Aligned0;

	NearestTriangleTableDim	=NULL;
	NearestTriangleTableXRes=10;
	NearestTriangleTableYRes=10;

}
XAlignmentLargeArea::XAlignmentLargeArea(AlignmentLargeInLayer	*parentInLayer)
{
	LibID			=-1;
	MaxSearchAreaFromItem=0;
	AreaID			=-1;
	MasterNo		=0;
	Priority		=_PriorityMiddle;
	ParentInLayer	=parentInLayer;
	PartsID			=-1;
	PartsAllocID	=-1;
	PartsAreaID		=-1;
	Locked			=false;
	Selected		=false;
	Active			=false;
	ManualCreated	=false;
	MultiSelection	=false;
	Visible			=true;
	Origin			=NULL;
	ALResultNumb	=0;
	ALResultAllocatedNumb	=MaxGPackNumb;
	ALResult		=new AlignmentLargeResultClass[MaxGPackNumb];
	DependingGlobal	=NULL;
	GroupMode		=false;
	GPackClassNumb	=0;
	GPackClass		=new XAlignmentLargePointerContainer[MaxGPackNumb];
	ResultPointCounts=_Aligned0;
	NearestTriangleTableDim	=NULL;
	NearestTriangleTableXRes=10;
	NearestTriangleTableYRes=10;
}
XAlignmentLargeArea::~XAlignmentLargeArea(void)
{
	if(ALResult!=NULL){
		delete	[]ALResult;
		ALResult=NULL;
		ALResultAllocatedNumb=0;
	}
	if(GPackClass!=NULL){
		delete	[]GPackClass;
		GPackClass=NULL;
	}
	if(NearestTriangleTableDim!=NULL){
		delete	[]NearestTriangleTableDim;
		NearestTriangleTableDim=NULL;
	}
}

XAlignmentLargePointerContainer	&XAlignmentLargePointerContainer::operator=(const XAlignmentLargePointerContainer &src)
{
	if(this!=&src){
		RemoveAll();
		for(XAlignmentLargePointer *g=src.GetFirst();g!=NULL;g=g->GetNext()){
			XAlignmentLargePointer *h=new XAlignmentLargePointer();
			//h->Parent=this;
			h->Point=new XAlignmentLarge();
			*h->Point = *g->Point;
			AppendList(h);
		}
	}
	return *this;
}

XAlignmentLargeArea	&XAlignmentLargeArea::operator=(const XAlignmentLargeArea &src)
{
	if(this!=&src){
		CopyWithoutItems(src,false);
		GPack=src.GPack;
		for(int i=0;i<MaxGPackNumb;i++){
			GPackClass[i]=src.GPackClass[i];
		}
		GPackClassNumb	=src.GPackClassNumb;

		LibID			=src.LibID;
		MasterNo		=src.MasterNo;
		Priority		=src.Priority;
		ParentInLayer	=src.ParentInLayer;
		PartsID			=src.PartsID;
		PartsAllocID	=src.PartsAllocID;
		PartsAreaID		=src.PartsAreaID;
		Locked			=src.Locked;
		Selected		=src.Selected;
		Active			=src.Active;
		ManualCreated	=src.ManualCreated;
		Visible			=src.Visible;
		Origin			=src.Origin;
	}
	return(*this);
}

XAlignmentLargeArea  &XAlignmentLargeArea::CopyWithoutItems(const XAlignmentLargeArea &src,bool ReferedMode)
{
	MaxSearchAreaFromItem	=src.MaxSearchAreaFromItem;
    AreaID		=src.AreaID;
	MasterNo	=src.MasterNo;
	Priority	=src.Priority;
	if(ReferedMode==true)
		Area.SetRefereneFrom(&src.Area);
	else
		Area		=src.Area;

	ALResultNumb=src.ALResultNumb;
	ALResultAllocatedNumb	=src.ALResultAllocatedNumb;
	delete	[]ALResult;
	ALResult=new AlignmentLargeResultClass[ALResultAllocatedNumb];
	for(int i=0;i<MaxGPackNumb && i<ALResultNumb && i<src.ALResultNumb && i<ALResultAllocatedNumb;i++){
		ALResult[i]	=src.ALResult[i];
	}
	//ParentInLayer	=src.ParentInLayer;
	LimitedLib		=src.LimitedLib;
	Locked			=src.Locked;
	Selected		=src.Selected;
	Active			=src.Active;
	Visible			=src.Visible;
	ManualCreated	=src.ManualCreated;
	Origin			=src.Origin;
	return(*this);
}

void    XAlignmentLargeArea::MoveTo(int dx ,int dy)
{
	if(Locked==false){
		Area.MoveToNoClip(dx,dy);
		for(XAlignmentLargePointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
			g->Point->MoveTo(dx,dy);
		}
	}
}
void    XAlignmentLargeArea::Initial(ImageBuffer &IBuff)
{
	for(XAlignmentLargePointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
		g->Point->MakeArea(IBuff);
	}
}

void	XAlignmentLargeArea::RemoveItem(AlgorithmItemPLI *item)
{
	XAlignmentLarge	*L=dynamic_cast<XAlignmentLarge *>(item);
	if(L!=NULL){
QNext:;
		for(XAlignmentLargePointer *a=GPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Point==L){
				GPack.RemoveList(a);
				delete	a;
				goto	QNext;
			}
		}
	}
}

int	XAlignmentLargeArea::GetPage(void)
{
	return ParentInLayer->GetPage();
}

int	XAlignmentLargeArea::GetLayer(void)
{
	return ParentInLayer->GetLayer();
}


XAlignmentLargeArea::AlignmentLargeResultClass	&XAlignmentLargeArea::AlignmentLargeResultClass::operator=(XAlignmentLargeArea::AlignmentLargeResultClass &src)
{
	AlignmentLargeResult[0]=src.AlignmentLargeResult[0];
	AlignmentLargeResult[1]=src.AlignmentLargeResult[1];
	AlignmentLargeResult[2]=src.AlignmentLargeResult[2];
	AlignmentLargeResult[3]=src.AlignmentLargeResult[3];
	AlignmentLargeResult[4]=src.AlignmentLargeResult[4];
	AlignmentLargeResult[5]=src.AlignmentLargeResult[5];
	Cx=src.Cx;
	Cy=src.Cy;
	return *this;
}

void    XAlignmentLargeArea::GetCenter(int &cx, int &cy)
{
	Area.GetCenter(cx,cy);
}
void	XAlignmentLargeArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentLargeBase	*pbase=dynamic_cast<AlignmentLargeBase *>(ParentInLayer->GetParentBase());
	if(pbase!=NULL){
		AlignmentLargeDrawAttr	*LAttr=dynamic_cast<AlignmentLargeDrawAttr *>(Attr);
		int	globalPage=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(ParentInLayer->GetPage());
		if(LAttr!=NULL //&& LAttr->DrawKind==AlignmentLargeDrawAttr::_Area
		&& LAttr->Priority.IsInclude(Priority)==true
		&& (LAttr->AList.GetNumber()==0 || LAttr->AList.Exists(globalPage,ParentInLayer->GetLayer(),AreaID)==true)){
			Attr->NormalColor	=pbase->ColorArea;
			Attr->NormalColor.setAlpha(pbase->AlphaLevel);
			Attr->SelectedColor	=pbase->ColorAreaSelected;
			Attr->SelectedColor.setAlpha(pbase->AlphaLevel);
			Attr->ActiveColor	=pbase->ColorAreaActive;
			Attr->ActiveColor.setAlpha(pbase->AlphaLevel);
			if(Selected==true)
				Area.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
			else if(Active==true)
				Area.Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
			else{
				if(Priority==_PriorityHigh){
					Area.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
				}
				else if(Priority==_PriorityMiddle){
					QColor	C(Attr->NormalColor.red()*0.8
							, Attr->NormalColor.green()*0.8
							, Attr->NormalColor.blue()*0.8
							, Attr->NormalColor.alpha());
					Area.Draw(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
				}
				else if(Priority==_PriorityLow){
					QColor	C(Attr->NormalColor.red()*0.6
							, Attr->NormalColor.green()*0.6
							, Attr->NormalColor.blue()*0.6
							, Attr->NormalColor.alpha());
					Area.Draw(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
				}
				else if(Priority==_PriorityGlobal){
					QColor	C(Attr->NormalColor.red()
							, Attr->NormalColor.green()
							, Attr->NormalColor.blue()
							, Attr->NormalColor.alpha()*0.6);
					Area.Draw(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
				}
			}
		}
		else if(LAttr!=NULL){
			if((LAttr->AList.GetNumber()==0 && LAttr->Priority.IsInclude(XAlignmentLargeArea::_PriorityNone)==true)
			|| LAttr->AList.Exists(globalPage,ParentInLayer->GetLayer(),AreaID)==true){
				Attr->NormalColor=pbase->ColorArea;
				Attr->NormalColor.setAlpha(pbase->AlphaLevel);
				Attr->SelectedColor	=pbase->ColorAreaSelected;
				Attr->SelectedColor.setAlpha(pbase->AlphaLevel);
				Attr->ActiveColor	=pbase->ColorAreaActive;
				Attr->ActiveColor.setAlpha(pbase->AlphaLevel);
				if(Selected==true)
					Area.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				else if(Active==true)
					Area.Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
				else{
					if(Priority==_PriorityHigh){
						Area.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
					}
					else if(Priority==_PriorityMiddle){
						QColor	C(Attr->NormalColor.red()*0.8
								, Attr->NormalColor.green()*0.8
								, Attr->NormalColor.blue()*0.8
								, Attr->NormalColor.alpha());
						Area.Draw(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
					}
					else if(Priority==_PriorityLow){
						QColor	C(Attr->NormalColor.red()*0.6
								, Attr->NormalColor.green()*0.6
								, Attr->NormalColor.blue()*0.6
								, Attr->NormalColor.alpha());
						Area.Draw(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
					}
					else if(Priority==_PriorityGlobal){
						QColor	C(Attr->NormalColor.red()
								, Attr->NormalColor.green()
								, Attr->NormalColor.blue()
								, Attr->NormalColor.alpha()*0.6);
						Area.Draw(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
					}
				}
			}
		}
		else{
			for(XAlignmentLargePointer *p=GPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
	QPainter	Pnt(&pnt);
	Pnt.setPen(Qt::cyan);
	for(RectClass *s=GenerationAreas.GetFirst();s!=NULL;s=s->GetNext()){
		s->DrawRect(Pnt ,ZoomRate ,movx ,movy);
	}
}

void	XAlignmentLargeArea::DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentLargeBase	*pbase=dynamic_cast<AlignmentLargeBase *>(ParentInLayer->GetParentBase());
	if(pbase!=NULL){
		AlignmentLargeDrawAttr	*LAttr=dynamic_cast<AlignmentLargeDrawAttr *>(Attr);
		if(LAttr!=NULL && LAttr->DrawKind==AlignmentLargeDrawAttr::_Area){
		}
		else if(LAttr!=NULL){
			if(LAttr->AList.ExistsAreaID(AreaID)==true){
				Attr->NormalColor=pbase->ColorPoint;
				Attr->NormalColor.setAlpha(pbase->AlphaLevel);
				Attr->SelectedColor	=pbase->ColorPointSelected;
				Attr->SelectedColor.setAlpha(pbase->AlphaLevel);
				Attr->ActiveColor	=pbase->ColorPointActive;
				Attr->ActiveColor.setAlpha(pbase->AlphaLevel);
				for(XAlignmentLargePointer *p=GPack.GetFirst();p!=NULL;p=p->GetNext()){
					p->Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
		else{
			for(XAlignmentLargePointer *p=GPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
}

void	XAlignmentLargeArea::DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(Selected==true && Locked==false){
		Area.Draw(dx,dy ,&pnt ,Col.rgba(),ZoomRate ,movx ,movy);
	}
}

int	SortAlignmentLargeShiftItemListStruct(const void *a, const void *b)
{
	struct AlignmentLargeShiftItemListStruct *ha=((struct AlignmentLargeShiftItemListStruct **)a)[0];
	struct AlignmentLargeShiftItemListStruct *hb=((struct AlignmentLargeShiftItemListStruct **)b)[0];
	if(ha->Match>hb->Match)
		return -1;
	else if(ha->Match<hb->Match)
		return 1;
	return 0;
}

void	XAlignmentLargePointerContainer::GetCenter(double &Cx, double &Cy)
{
	int	N=0;
	Cx=Cy=0;
	for(XAlignmentLargePointer *p=GetFirst();p!=NULL;p=p->GetNext()){
		double	MCx,MCy;
		p->Point->GetCenter(MCx,MCy);
		Cx+=MCx;
		Cy+=MCy;
		N++;
	}
	if(N>1){
		Cx/=N;
		Cy/=N;
	}
}

void	XAlignmentLargePointerContainer::SetAdopted(struct AlignmentLargeShiftItemListStruct &s)
{
	for(int i=0;i<3;i++){
		if(s.Item->BestMatch[i].Dx==s.Dx && s.Item->BestMatch[i].Dy==s.Dy
		&& s.Item->BestMatch[i].Match==s.Match){
			s.Item->BestMatch[i].Adopted=true;
		}
	}
}

int	XAlignmentLargePointerContainer::GetMachingPoint(struct	AlignmentLargeShiftItemListStruct BestMatch[3])
{
	if(GetCount()==1){
		int	N=0;
		for(int i=0;i<3 && i<GetFirst()->Point->CountOfBestMatch;i++){
			BestMatch[i]=GetFirst()->Point->BestMatch[i];
			N++;
		}
		return N;
	}
	int	N=0;
	for(XAlignmentLargePointer *p=GetFirst();p!=NULL;p=p->GetNext()){
		N+=p->Point->CountOfBestMatch;
	}
	int	R=0;
	struct	AlignmentLargeShiftItemListStruct	**Dim=new struct AlignmentLargeShiftItemListStruct *[N];
	for(XAlignmentLargePointer *p=GetFirst();p!=NULL;p=p->GetNext()){
		for(int i=0;i<p->Point->CountOfBestMatch;i++){
			Dim[R]=&p->Point->BestMatch[i];
			R++;
		}
	}
	QSort(Dim,R,sizeof(Dim[0]),SortAlignmentLargeShiftItemListStruct);
	int	RetNumb=0;
	for(int i=0;i<R && i<3;i++){
		BestMatch[i]=*Dim[i];
		RetNumb++;
	}
	delete	[]Dim;
	return RetNumb;
}

struct	M3Class
{
	int	ia,ib,ic;
	double	TotalMatch;
	double	TransformingRate;
};

int	SortFuncSDim(const void *a ,const void *b)
{
	struct	M3Class	*pa=(struct	M3Class *)a;
	struct	M3Class	*pb=(struct	M3Class *)b;
	if(pa->TotalMatch > pb->TotalMatch)
		return 1;
	if(pa->TotalMatch < pb->TotalMatch)
		return -1;
	return 0;
}

double	MakeTransformingRate(struct AlignmentLargeShiftItemListStruct &Pa
							,struct AlignmentLargeShiftItemListStruct &Pb
							,struct AlignmentLargeShiftItemListStruct &Pc);

int	XAlignmentLargeArea::SelectAlignmentPoint(struct AlignmentLargeShiftItemListStruct BestMatch[10])
{
	if(GPackClassNumb==2){
		struct	AlignmentLargeShiftItemListStruct BestMatchA[3];
		struct	AlignmentLargeShiftItemListStruct BestMatchB[3];
		int	NA=GPackClass[0].GetMachingPoint(BestMatchA);
		int	NB=GPackClass[1].GetMachingPoint(BestMatchB);
		return SelectAlignmentPoint2(BestMatch
									, NA ,BestMatchA
									, NB ,BestMatchB);
	}
	else if(GPackClassNumb==3){
		struct	AlignmentLargeShiftItemListStruct BestMatchA[3];
		struct	AlignmentLargeShiftItemListStruct BestMatchB[3];
		struct	AlignmentLargeShiftItemListStruct BestMatchC[3];
		int	NA=GPackClass[0].GetMachingPoint(BestMatchA);
		int	NB=GPackClass[1].GetMachingPoint(BestMatchB);
		int	NC=GPackClass[2].GetMachingPoint(BestMatchC);

		return SelectAlignmentPoint3(BestMatch
									, NA ,BestMatchA
									, NB ,BestMatchB
									, NC ,BestMatchC);
	}
	else if(GPackClassNumb>3){
		for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
			struct	AlignmentLargeShiftItemListStruct BestMatchA[3];
			struct	AlignmentLargeShiftItemListStruct BestMatchB[3];
			struct	AlignmentLargeShiftItemListStruct BestMatchC[3];
			int	NA=a->Pa->GetMachingPoint(BestMatchA);
			int	NB=a->Pb->GetMachingPoint(BestMatchB);
			int	NC=a->Pc->GetMachingPoint(BestMatchC);
		}
	}

	return 0;
}
double	MakeTransformingRate(struct AlignmentLargeShiftItemListStruct &Pa
							,struct AlignmentLargeShiftItemListStruct &Pb
							,struct AlignmentLargeShiftItemListStruct &Pc)
{
	//Ax+By+mx=X
	//Cx+Dy+my=Y
	double	Cax,Cay;
	double	Cbx,Cby;
	double	Ccx,Ccy;

	if(Pa.Item==NULL || Pb.Item!=NULL || Pc.Item!=NULL)
		return 0.0;

	Pa.Item->GetCenter(Cax,Cay);
	Pb.Item->GetCenter(Cbx,Cby);
	Pc.Item->GetCenter(Ccx,Ccy);

	XMultiEquSolve	Qx;
	XMultiEquSolve	Qy;

	Qx.AllocateMatrix(3);	//3 parameters
	Qx.SetMatrixValue(1,1,Cax);
	Qx.SetMatrixValue(2,1,Cay);
	Qx.SetMatrixValue(3,1,1.0);
	Qx.SetMatrixValue(1,2,Cbx);
	Qx.SetMatrixValue(2,2,Cby);
	Qx.SetMatrixValue(3,2,1.0);
	Qx.SetMatrixValue(1,3,Ccx);
	Qx.SetMatrixValue(2,3,Ccy);
	Qx.SetMatrixValue(3,3,1.0);
	Qx.SetMatrixValueBn(1,Cax+Pa.Dx);
	Qx.SetMatrixValueBn(2,Cbx+Pb.Dx);
	Qx.SetMatrixValueBn(3,Ccx+Pc.Dx);
	Qx.ExecuteGaussianElimination();	//計算開始

	Qy.AllocateMatrix(3);	//3 parameters
	Qy.SetMatrixValue(1,1,Cax);
	Qy.SetMatrixValue(2,1,Cay);
	Qy.SetMatrixValue(3,1,1.0);
	Qy.SetMatrixValue(1,2,Cbx);
	Qy.SetMatrixValue(2,2,Cby);
	Qy.SetMatrixValue(3,2,1.0);
	Qy.SetMatrixValue(1,3,Ccx);
	Qy.SetMatrixValue(2,3,Ccy);
	Qy.SetMatrixValue(3,3,1.0);
	Qy.SetMatrixValueBn(1,Cay+Pa.Dy);
	Qy.SetMatrixValueBn(2,Cby+Pb.Dy);
	Qy.SetMatrixValueBn(3,Ccy+Pc.Dy);
	Qy.ExecuteGaussianElimination();	//計算開始

	double	A	=Qx.GetAnswer(1);	//答え
	double	B	=Qx.GetAnswer(2);
	double	mx	=Qx.GetAnswer(3);
	double	C	=Qy.GetAnswer(1);
	double	D	=Qy.GetAnswer(2);
	double	my	=Qy.GetAnswer(3);

	if(fabs(A)<0.0000001)
		return A;
	double	Sita=atan(C/A);

	double	a=A/cos(Sita);
	//double	b=B/sin(Sita);
	double	d=D/cos(Sita);

	return (1.0-a)*(1.0-a) + (1.0-d)*(1.0-d);
}

int	XAlignmentLargeArea::SelectAlignmentPoint2(struct AlignmentLargeShiftItemListStruct RetBestMatch[10]
											 , int NA ,struct AlignmentLargeShiftItemListStruct BestMatchA[3]
											 , int NB ,struct AlignmentLargeShiftItemListStruct BestMatchB[3])
{
	if(NA==0){
		if(NB!=0){
			RetBestMatch[0]=BestMatchB[0];
			return 1;
		}
		return 0;
	}
	if(NB==0){
		if(NA!=0){
			RetBestMatch[0]=BestMatchA[0];
			return 1;
		}
		return 0;
	}
	int	MasterCxa,MasterCya;
	int	MasterCxb,MasterCyb;
	BestMatchA[0].Item->GetCenter(MasterCxa,MasterCya);
	BestMatchB[0].Item->GetCenter(MasterCxb,MasterCyb);
	double	MasterLen=hypot(MasterCxa-MasterCxb,MasterCya-MasterCyb);
	double	Len2=-99999999;
	double	Len3=-99999999;
	double	Len1=hypot((MasterCxa+BestMatchA[0].Dx)-(MasterCxb+BestMatchB[0].Dx)
					  ,(MasterCya+BestMatchA[0].Dy)-(MasterCyb+BestMatchB[0].Dy));
	if(NA>=2 && NB>=1){
		Len2=hypot((MasterCxa+BestMatchA[1].Dx)-(MasterCxb+BestMatchB[0].Dx)
				  ,(MasterCya+BestMatchA[1].Dy)-(MasterCyb+BestMatchB[0].Dy));
	}
	if(NA>=1 && NB>=2){
		Len3=hypot((MasterCxa+BestMatchA[0].Dx)-(MasterCxb+BestMatchB[1].Dx)
				  ,(MasterCya+BestMatchA[0].Dy)-(MasterCyb+BestMatchB[1].Dy));
	}
	double	V1=fabs(MasterLen-Len1);
	double	V2=fabs(MasterLen-Len2);
	double	V3=fabs(MasterLen-Len3);
	if(V1<=V2 && V1<=V3){
		RetBestMatch[0]=BestMatchA[0];
		RetBestMatch[1]=BestMatchB[0];
		return 2;
	}
	else if(V2<=V1 && V2<=V3){
		RetBestMatch[0]=BestMatchA[1];
		RetBestMatch[1]=BestMatchB[0];
		return 2;
	}
	else{
		RetBestMatch[0]=BestMatchA[0];
		RetBestMatch[1]=BestMatchB[1];
		return 2;
	}
}

int	XAlignmentLargeArea::SelectAlignmentPoint3(struct AlignmentLargeShiftItemListStruct RetBestMatch[10]
											 , int NA ,struct AlignmentLargeShiftItemListStruct BestMatchA[3]
											 , int NB ,struct AlignmentLargeShiftItemListStruct BestMatchB[3]
											 , int NC ,struct AlignmentLargeShiftItemListStruct BestMatchC[3])
{
	if(NA==0){
		return SelectAlignmentPoint2(RetBestMatch
								, NB ,BestMatchB
								, NC ,BestMatchC);
	}
	else if(NB==0){
		return SelectAlignmentPoint2(RetBestMatch
								, NA ,BestMatchA
								, NC ,BestMatchC);
	}
	else if(NC==0){
		return SelectAlignmentPoint2(RetBestMatch
								, NA ,BestMatchA
								, NB ,BestMatchB);
	}
	struct	M3Class	SDim[100];
	int	SDimNumb=0;
	for(int ia=0;ia<NA;ia++){
		for(int ib=0;ib<NB;ib++){
			for(int ic=0;ic<NC;ic++){
				SDim[SDimNumb].ia=ia;
				SDim[SDimNumb].ib=ib;
				SDim[SDimNumb].ic=ic;
				SDim[SDimNumb].TotalMatch=BestMatchA[ia].Match + BestMatchB[ib].Match + BestMatchA[ic].Match;
				SDimNumb++;
			}
		}
	}
	QSort(SDim ,SDimNumb,sizeof(SDim[0]),SortFuncSDim);

	double	MinTransformingRate=99999999;
	int		MinIndex=0;
	for(int i=0;i<10 && i<SDimNumb;i++){
		SDim[i].TransformingRate=MakeTransformingRate(BestMatchA[SDim[i].ia]
													 ,BestMatchB[SDim[i].ib]
													 ,BestMatchC[SDim[i].ic]);
		if(SDim[i].TransformingRate<MinTransformingRate){
			MinTransformingRate=SDim[i].TransformingRate;
			MinIndex=i;
		}
	}
	RetBestMatch[0]=BestMatchA[SDim[MinIndex].ia];
	RetBestMatch[1]=BestMatchB[SDim[MinIndex].ib];
	RetBestMatch[2]=BestMatchC[SDim[MinIndex].ic];
	return 3;
}


void	XAlignmentLargeArea::Calc(ImageBuffer &IData
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	if(GPackClassNumb==0){
		ResultPointCounts=_Aligned0;
		Calc0(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
    else if(GPackClassNumb==1){
		ResultPointCounts=_Aligned1;
		Calc1(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
    else if(GPackClassNumb==2){
		Calc2(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
    else{
		//if(GPackClassNumb>=3){
		if(Calc3(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes)==true){
		}
	}
	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Effective==true){
			a->GetCenter(a->TotalCx,a->TotalCy);
		}
	}
}

void	XAlignmentLargeArea::CalcAllocateOnly(ImageBuffer &IData
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	if(GPackClassNumb==0){
		ResultPointCounts=_Aligned0;
		CalcAllocateOnly0(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
    else if(GPackClassNumb==1){
		ResultPointCounts=_Aligned1;
		CalcAllocateOnly1(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
    else if(GPackClassNumb==2){
		CalcAllocateOnly2(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
    else{
		//if(GPackClassNumb>=3){
		if(CalcAllocateOnly3(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes)==true){
		}
	}
	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Effective==true){
			a->GetCenter(a->TotalCx,a->TotalCy);
		}
	}
}
int		XAlignmentLargeArea::GetCalcedItemCount(void)
{
	int	N=0;
	for(XAlignmentLargePointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->Point->IsProcessDone()==true)
			N++;
	}
	return N;
}

XAlignmentLargeArea::AlignmentLargePointCount	XAlignmentLargeArea::GetResultInPoint(int localX ,int localY)
{
	if(Area.IsInclude(localX ,localY)==true)
		return ResultPointCounts;
	return _Aligned0;
}

double	XAlignmentLargeArea::GetClosedResultInPoint(int localX ,int localY)
{
	int		x1 ,y1 ,x2 ,y2;
	GetXY(x1 ,y1 ,x2 ,y2);

	double	L1=GetLengthLine2Point(x1,y1,x2,y1,localX,localY);
	double	L2=GetLengthLine2Point(x2,y1,x2,y2,localX,localY);
	double	L3=GetLengthLine2Point(x2,y2,x1,y2,localX,localY);
	double	L4=GetLengthLine2Point(x1,y2,x1,y1,localX,localY);

	return min(min(L1,L2),min(L3,L4));
	/*
	int	x,y;
	GetCenter(x ,y);
	return hypot(x-localX,y-localY);
	*/
}
AlignmentLargeBase	*XAlignmentLargeArea::GetParentBase(void)
{
	return (AlignmentLargeBase *)ParentInLayer->GetParentBase();
}
DataInPage	*XAlignmentLargeArea::GetDataInPage(void)
{
	return ParentInLayer->GetDataInPage();
}
bool	XAlignmentLargeArea::GetAlignment(AlignmentPacket2D &AData)
{
    if(GPackClassNumb==0){
		AData.ShiftX=AData.ShiftY=0;
		AData.Calculated=true;
		return true;
	}
    //if(GPackClassNumb==1){
	if(ResultPointCounts==_Aligned1){
		struct	AlignmentLargeShiftItemListStruct BestMatch[3];
		int	N=GPackClass[0].GetMachingPoint(BestMatch);

		AData.ShiftX=(N>0)?BestMatch[0].Dx:0;
		AData.ShiftY=(N>0)?BestMatch[0].Dy:0;

		if(AData.ShiftX<-MaxSearchAreaFromItem)
			AData.ShiftX=-MaxSearchAreaFromItem;
		if(AData.ShiftX>MaxSearchAreaFromItem)
			AData.ShiftX= MaxSearchAreaFromItem;
		if(AData.ShiftY<-MaxSearchAreaFromItem)
			AData.ShiftY=-MaxSearchAreaFromItem;
		if(AData.ShiftY>MaxSearchAreaFromItem)
			AData.ShiftY= MaxSearchAreaFromItem;
		AData.Calculated=true;
		return true;
	}
    //else if(GPackClassNumb==2){
	else if(ResultPointCounts==_Aligned2){
		AData.ShiftX	=AData.PosXOnTarget*ALResult[0].AlignmentLargeResult[0]+AData.PosYOnTarget*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2]-AData.PosXOnTarget;
		AData.ShiftY	=AData.PosXOnTarget*ALResult[0].AlignmentLargeResult[3]+AData.PosYOnTarget*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5]-AData.PosYOnTarget;
		AData.Rotation=ALRotation;
		if(AData.ShiftX<-MaxSearchAreaFromItem)
			AData.ShiftX=-MaxSearchAreaFromItem;
		if(AData.ShiftX>MaxSearchAreaFromItem)
			AData.ShiftX= MaxSearchAreaFromItem;
		if(AData.ShiftY<-MaxSearchAreaFromItem)
			AData.ShiftY=-MaxSearchAreaFromItem;
		if(AData.ShiftY>MaxSearchAreaFromItem)
			AData.ShiftY= MaxSearchAreaFromItem;
		AData.Calculated=true;
		return true;
	}
	else if(ResultPointCounts==_Aligned3 || ResultPointCounts==_Aligned4){
    //else if(GPackClassNumb>=3){
		TriangleArea	*A=GetNearestTriangleInTable(AData.PosXOnTarget,AData.PosYOnTarget);
		if(A!=NULL){
			AData.ShiftX=AData.PosXOnTarget*A->m[0]+AData.PosYOnTarget*A->m[1]+A->m[2]-AData.PosXOnTarget;
			AData.ShiftY=AData.PosXOnTarget*A->m[3]+AData.PosYOnTarget*A->m[4]+A->m[5]-AData.PosYOnTarget;
			AData.Rotation	=A->GetRotation();
			AData.Handle=A;
		}
		if(AData.ShiftX<-MaxSearchAreaFromItem)
			AData.ShiftX=-MaxSearchAreaFromItem;
		if(AData.ShiftX>MaxSearchAreaFromItem)
			AData.ShiftX= MaxSearchAreaFromItem;
		if(AData.ShiftY<-MaxSearchAreaFromItem)
			AData.ShiftY=-MaxSearchAreaFromItem;
		if(AData.ShiftY>MaxSearchAreaFromItem)
			AData.ShiftY= MaxSearchAreaFromItem;
		AData.Calculated=true;
		return true;
	}
	return false;
}

bool	XAlignmentLargeArea::GetAlignmentByHandle(AlignmentPacket2D &AData ,void *Handle)
{
    if(GPackClassNumb==0){
		AData.ShiftX=AData.ShiftY=0;
		AData.Calculated=true;
		return true;
	}
    //if(GPackClassNumb==1){
	if(ResultPointCounts==_Aligned1){
		struct	AlignmentLargeShiftItemListStruct BestMatch[3];
		int	N=GPackClass[0].GetMachingPoint(BestMatch);

		AData.ShiftX=(N>0)?BestMatch[0].Dx:0;
		AData.ShiftY=(N>0)?BestMatch[0].Dy:0;

		if(AData.ShiftX<-MaxSearchAreaFromItem)
			AData.ShiftX=-MaxSearchAreaFromItem;
		if(AData.ShiftX>MaxSearchAreaFromItem)
			AData.ShiftX= MaxSearchAreaFromItem;
		if(AData.ShiftY<-MaxSearchAreaFromItem)
			AData.ShiftY=-MaxSearchAreaFromItem;
		if(AData.ShiftY>MaxSearchAreaFromItem)
			AData.ShiftY= MaxSearchAreaFromItem;
		AData.Calculated=true;
		return true;
	}
    //else if(GPackClassNumb==2){
	else if(ResultPointCounts==_Aligned2){
		AData.ShiftX	=AData.PosXOnTarget*ALResult[0].AlignmentLargeResult[0]+AData.PosYOnTarget*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2]-AData.PosXOnTarget;
		AData.ShiftY	=AData.PosXOnTarget*ALResult[0].AlignmentLargeResult[3]+AData.PosYOnTarget*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5]-AData.PosYOnTarget;
		AData.Rotation=ALRotation;
		if(AData.ShiftX<-MaxSearchAreaFromItem)
			AData.ShiftX=-MaxSearchAreaFromItem;
		if(AData.ShiftX>MaxSearchAreaFromItem)
			AData.ShiftX= MaxSearchAreaFromItem;
		if(AData.ShiftY<-MaxSearchAreaFromItem)
			AData.ShiftY=-MaxSearchAreaFromItem;
		if(AData.ShiftY>MaxSearchAreaFromItem)
			AData.ShiftY= MaxSearchAreaFromItem;
		AData.Calculated=true;
		return true;
	}
	else if(ResultPointCounts==_Aligned3 || ResultPointCounts==_Aligned4){
    //else if(GPackClassNumb>=3){
		TriangleArea	*A;
		if(Handle!=NULL){
			A=(TriangleArea *)Handle;
		}
		else{
			A=GetNearestTriangleInTable(AData.PosXOnTarget,AData.PosYOnTarget);
		}
		if(A!=NULL){
			AData.ShiftX=AData.PosXOnTarget*A->m[0]+AData.PosYOnTarget*A->m[1]+A->m[2]-AData.PosXOnTarget;
			AData.ShiftY=AData.PosXOnTarget*A->m[3]+AData.PosYOnTarget*A->m[4]+A->m[5]-AData.PosYOnTarget;
			AData.Rotation	=A->GetRotation();
		}
		if(AData.ShiftX<-MaxSearchAreaFromItem)
			AData.ShiftX=-MaxSearchAreaFromItem;
		if(AData.ShiftX>MaxSearchAreaFromItem)
			AData.ShiftX= MaxSearchAreaFromItem;
		if(AData.ShiftY<-MaxSearchAreaFromItem)
			AData.ShiftY=-MaxSearchAreaFromItem;
		if(AData.ShiftY>MaxSearchAreaFromItem)
			AData.ShiftY= MaxSearchAreaFromItem;
		AData.Calculated=true;
		return true;
	}
	return false;
}
bool	XAlignmentLargeArea::Calc0(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	if(MVector!=NULL){
		for(int i=0;i<Area.GetFLineLen();i++){
			int y =Area.GetFLineAbsY  (i);
			if((y%MVectorYRes)!=0)
				continue;
			y=y/MVectorYRes;
			if(y>=MVectorYNumb)
				continue;
			int x1=Area.GetFLineLeftX (i);
			int x2=Area.GetFLineRightX(i);
			x1=x1/MVectorXRes;
			x2=(x2+MVectorXRes-1)/MVectorXRes;
			if(x1<0)
				x1=0;
			if(x2>=MVectorXNumb)
				x2=MVectorXNumb;
			for(int x=x1;x<x2;x++){
                MVector[y*MVectorXNumb+x].setX(0);
                MVector[y*MVectorXNumb+x].setY(0);
			}
		}
	}
	ALResult[0].AlignmentLargeResult[0]=1;
	ALResult[0].AlignmentLargeResult[1]=0;
	ALResult[0].AlignmentLargeResult[2]=0;
	ALResult[0].AlignmentLargeResult[3]=0;
	ALResult[0].AlignmentLargeResult[4]=1;
	ALResult[0].AlignmentLargeResult[5]=0;
	ALResultNumb=1;
	return(true);
}
bool	XAlignmentLargeArea::Calc1(
				QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	Index)
{
	struct	AlignmentLargeShiftItemListStruct BestMatch[3];
	int	N=GPackClass[Index].GetMachingPoint(BestMatch);
	if(N==0){
		return Calc0(MVector
				,MVectorXNumb	,MVectorYNumb
				,MVectorXRes	,MVectorYRes);
	}
	GPackClass[Index].SetAdopted(BestMatch[0]);

	int Mx=(N>0)?BestMatch[0].Dx:0;
	int My=(N>0)?BestMatch[0].Dy:0;

	if(MVector!=NULL){
		for(int i=0;i<Area.GetFLineLen();i++){
			int y =Area.GetFLineAbsY  (i);
			if((y%MVectorYRes)!=0)
				continue;
			y=y/MVectorYRes;
			if(y>=MVectorYNumb)
				continue;
			int x1=Area.GetFLineLeftX (i);
			int x2=Area.GetFLineRightX(i);
			x1=x1/MVectorXRes;
			x2=(x2+MVectorXRes-1)/MVectorXRes;
			if(x1<0)
				x1=0;
			if(x2>=MVectorXNumb)
				x2=MVectorXNumb;
			for(int x=x1;x<x2;x++){
				MVector[y*MVectorXNumb+x].setX(Mx);
				MVector[y*MVectorXNumb+x].setY(My);
			}
		}
	}
	AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999){
			//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
			//	&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
			if(p->Area==this
			&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
				p->ShiftX=Mx;
				p->ShiftY=My;
				if(p->ShiftX<-MaxSearchAreaFromItem)
					p->ShiftX=-MaxSearchAreaFromItem;
				if(p->ShiftX>MaxSearchAreaFromItem)
					p->ShiftX= MaxSearchAreaFromItem;
				if(p->ShiftY<-MaxSearchAreaFromItem)
					p->ShiftY=-MaxSearchAreaFromItem;
				if(p->ShiftY>MaxSearchAreaFromItem)
					p->ShiftY= MaxSearchAreaFromItem;
				p->Calculated=true;
			}
		}
	}
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999){
			//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
			if(p->Area!=NULL && p->Area==this){
				p->ShiftX=Mx;
				p->ShiftY=My;
				if(p->ShiftX<-MaxSearchAreaFromItem)
					p->ShiftX=-MaxSearchAreaFromItem;
				if(p->ShiftX>MaxSearchAreaFromItem)
					p->ShiftX= MaxSearchAreaFromItem;
				if(p->ShiftY<-MaxSearchAreaFromItem)
					p->ShiftY=-MaxSearchAreaFromItem;
				if(p->ShiftY>MaxSearchAreaFromItem)
					p->ShiftY= MaxSearchAreaFromItem;
				p->Calculated=true;
			}
		}
	}

	ALResult[0].AlignmentLargeResult[0]=1;
	ALResult[0].AlignmentLargeResult[1]=0;
	ALResult[0].AlignmentLargeResult[2]=Mx;
	ALResult[0].AlignmentLargeResult[3]=0;
	ALResult[0].AlignmentLargeResult[4]=1;
	ALResult[0].AlignmentLargeResult[5]=My;
	ALResultNumb=1;
	return(true);
}
bool	XAlignmentLargeArea::Calc2(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	IndexA		,int	IndexB)
{
	struct	AlignmentLargeShiftItemListStruct BestMatch1[3];
	int	N1=GPackClass[IndexA].GetMachingPoint(BestMatch1);
	struct	AlignmentLargeShiftItemListStruct BestMatch2[3];
	int	N2=GPackClass[IndexB].GetMachingPoint(BestMatch2);

	if(N1==0 && N2==0){
		ResultPointCounts=_Aligned0;
		return Calc0(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
	if(N1>0 && N2==0){
		ResultPointCounts=_Aligned1;
		return Calc1(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes
				,0);
	}
	else if(N1==0 && N2>0){
		ResultPointCounts=_Aligned1;
		return Calc1(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes
				,1);
	}

	//AlignmentLargeBase	*PBase=(AlignmentLargeBase *)BestMatch1[0].Item->GetParentBase();
	AlignmentLargeBase	*PBase=dynamic_cast<AlignmentLargeBase *>(ParentInLayer->GetParentBase());

	double  qx1=0;
	double  qy1=0;
	double  qx2=0;
	double  qy2=0;
	double  qX1=0;
	double  qY1=0;
	double  qX2=0;
	double  qY2=0;

	double  dx;
	double  dy;
	double  dX;
	double  dY;
	double	mA=0;
	int		IndexI=0;
	int		IndexJ=0;

	for(int i=0;i<3 && i<N1;i++){
		if(i>0){
			if(BestMatch1[0].Match - BestMatch1[i].Match>PBase->AdoptedMinD){
				break;
			}
		}
		for(int j=0;j<3 && j<N2;j++){
			if(j>0){
				if(BestMatch2[0].Match - BestMatch2[j].Match>PBase->AdoptedMinD){
					break;
				}
			}
			double  tqx1=BestMatch1[i].Item->MasterX;
			double  tqy1=BestMatch1[i].Item->MasterY;
			double  tqx2=BestMatch2[j].Item->MasterX;
			double  tqy2=BestMatch2[j].Item->MasterY;
			double  tqX1=BestMatch1[i].Item->MasterX + BestMatch1[i].Dx;
			double  tqY1=BestMatch1[i].Item->MasterY + BestMatch1[i].Dy;
			double  tqX2=BestMatch2[j].Item->MasterX + BestMatch2[j].Dx;
			double  tqY2=BestMatch2[j].Item->MasterY + BestMatch2[j].Dy;

			double	tdx=tqx1-tqx2;
			double	tdy=tqy1-tqy2;
			double	tdX=tqX1-tqX2;
			double	tdY=tqY1-tqY2;
			double	tmA=0;
			double	m=tdx*tdx+tdy*tdy;
			if(fabs(m)>0){
				double	K=(tdX*tdX+tdY*tdY)/m;
				if(K>=0){
					tmA=	sqrt(K);
				}
			}
			if(fabs(tmA-1.0) <=fabs(mA-1.0)){
				IndexI=i;
				IndexJ=j;
				qx1=tqx1;
				qy1=tqy1;
				qx2=tqx2;
				qy2=tqy2;
				qX1=tqX1;
				qY1=tqY1;
				qX2=tqX2;
				qY2=tqY2;
				dx=tdx;
				dy=tdy;
				dX=tdX;
				dY=tdY;
				mA=tmA;
			}
		}
	}
	GPackClass[IndexA].SetAdopted(BestMatch1[IndexI]);
	GPackClass[IndexB].SetAdopted(BestMatch2[IndexJ]);

	//qX1= mA*cos(s)*qx1+mA*sin(s)*qy1+c
	//qY1=-mA*sin(s)+qx1+mA*cos(s)*qy1+f
	//qX2= mA*cos(s)*qx2+mA*sin(s)*qy2+c
	//qY2=-mA*sin(s)+qx2+mA*cos(s)*qy2+f

	//dX= mA*cos(s)*dx+mA*sin(s)*dy
	//dY=-mA*sin(s)*dx+mA*cos(s)*dy

	//dX*dX+dY*dY= mA2*c2*dx2+2*mA2*s*c*dx*dy+mA2*s2*dy2
	//			  +mA2*s2*dx2-2*mA2*c*s*dx*dy+mA2*c2*dy2
	//			=mA2*(dx2+dy2)

	AlignmentLargeBase	*ABase=GetParentBase();
	if(ABase->NotExpandX==false){
		double	DX=dX/mA;
		double	DY=dY/mA;
		//DX= c*dx+s*dy
		//DY=-s*dx+c*dy
		//c=(DX-s*dy)/dx
		//DY=-s*dx+(DX-s*dy)/dx*dy
		//DY*dx=-s*dx*dx+DX*dy-s*dy*dy
		//DY*dx-DX*dy=-(dx*dx+dy*dy)*s
		double	s=-(DY*dx-DX*dy)/(dx*dx+dy*dy);
		//s=(DX-c*dx)/dy
		//DY=-(DX-c*dx)/dy*dx+c*dy
		//DY*dy=-DX*dx+c*dx*dx+c*dy*dy
		//(DY*dy+DX*dx)=c*(dx*dx+dy*dy)
		double	c=(DY*dy+DX*dx)/(dx*dx+dy*dy);
		ALRotation=asin(-s);
		ALResult[0].AlignmentLargeResult[0]=mA*c;
		ALResult[0].AlignmentLargeResult[1]=mA*s;
		ALResult[0].AlignmentLargeResult[2]=qX1-mA*qx1*c-mA*qy1*s;
		ALResult[0].AlignmentLargeResult[3]=-mA*s;
		ALResult[0].AlignmentLargeResult[4]=mA*c;
		ALResult[0].AlignmentLargeResult[5]=qY1+mA*qx1*s-mA*qy1*c;
		ALResultNumb=1;
	}
	/*
	(x1,y1)->(X1,Y1)
	(x2,y2)->(X2,Y2)

	X=x
	Y=ty
	|1 0 0||x| |X|
	|0 t 0||y|=|Y|
	|0 0 1||1| |1|

	X=xcos-ysin+c
	Y=xsin+ycos+f
	|cos -sin c||x| |X|
	|sin  cos f||y|=|Y|
	|0    0   1||1| |1|

	|cos -sin c||1 0 0||x| |X|
	|sin  cos f||0 t 0||y|=|Y|
	|0    0   1||0 0 1||1| |0|	
	
	|cos -tsin c||x| |X|
	|sin  tcos f||y|=|Y| 
	|0    0    1||1| |1|

	xcos-ytsin+c=X
	xsin+ytcos+f=Y

	xcos^2-ytsincos+ccos=Xcos
	xsin^2+ytsincos+fsin=Ysin

	x+ccos+fsin=Xcos+Ysin

	x1cos-y1tsin+c=X1
	x2cos-y2tsin+c=X2

		(x1y2-x2y1)cos+c(y2-y1)=X1y2-X2y1

	x1sin+y1tcos+f=Y1
	x2sin+y2tcos+f=Y2

	(x1-x2)cos-(y1-y2)tsin=X1-X2
	(x1-x2)sin+(y1-y2)tcos=Y1-Y2

	(x1-x2)cos^2-(y1-y2)tsincos=(X1-X2)cos
	(x1-x2)sin-2+(y1-y2)tsincos=(Y1-Y2)sin
		x1-x2=(X1-X2)cos+(Y1-Y2)sin

		a=x1-x2
		A=X1-X2
		B=Y1-Y2

		a=Acos+Bsin
		(a-Acos)^2=B^2sin^2
		aa-2aAcos+AAcos^2=BB(1-cos^2)
		(AA+BB)cos^2-2aAcos+aa-BB=0

	*/
	else
	if(ABase->NotExpandX==true){
		double	x1,y1,x2,y2;
		BestMatch1[IndexI].Item->GetCenter(x1,y1);
		BestMatch2[IndexJ].Item->GetCenter(x2,y2);
		double	X1=x1+BestMatch1[IndexI].Dx;
		double	Y1=y1+BestMatch1[IndexI].Dy;
		double	X2=x2+BestMatch2[IndexJ].Dx;
		double	Y2=y2+BestMatch2[IndexJ].Dy;

		double	a=x1-x2;
		double	A=X1-X2;
		double	B=Y1-Y2;
		double	K=A*A+B*B;
		if(K==0.0)
			return false;
		double	D=sqrt(a*a*A*A-K*(a*a-B*B));
		double	Cos1=(a*A+D)/K;
		double	Cos2=(a*A-D)/K;
		if(B==0)
			return false;
		double	Sin1=(a-A*Cos1)/B;
		double	Sin2=(a-A*Cos2)/B;
		double	Sin,Cos;
		if(fabs(Cos1)<=1.0 && fabs(Sin1)<=1.0){
			Cos=Cos1;
			Sin=Sin1;
		}
		else
		if(fabs(Cos2)<=1.0 && fabs(Sin2)<=1.0){
			Cos=Cos2;
			Sin=Sin2;
		}
		else{
			return false;
		}
		//(x1-x2)sin+(y1-y2)tcos=Y1-Y2
		double	t=((Y1-Y2)-(x1-x2)*Sin)/((y1-y2)*Cos);

		//x1cos-y1tsin+c=X1
		double	c=X1-x1*Cos+y1*t*Sin;
		//x1sin+y1tcos+f=Y1
		double	f=Y1-x1*Sin-y1*t*Cos;

		ALRotation=asin(Sin);
		ALResult[0].AlignmentLargeResult[0]=Cos;
		ALResult[0].AlignmentLargeResult[1]=-t*Sin;
		ALResult[0].AlignmentLargeResult[2]=c;
		ALResult[0].AlignmentLargeResult[3]=Sin;
		ALResult[0].AlignmentLargeResult[4]=t*Cos;
		ALResult[0].AlignmentLargeResult[5]=f;
		ALResultNumb=1;
	}



	/*

	double	K=dX*dy-dY*dx;
	double	H=dY*dy+dX*dx;
	double	s=atan(K/H);
	mA=dX/(dx*cos(s)+dy*sin(s));

	AlignmentLargeResult[0]=mA*cos(s);
	AlignmentLargeResult[1]=mA*sin(s);
	AlignmentLargeResult[2]=qX1-mA*qx1*cos(s)-mA*qy1*sin(s);
	AlignmentLargeResult[3]=-mA*sin(s);
	AlignmentLargeResult[4]=mA*cos(s);
	AlignmentLargeResult[5]=qY1+mA*qx1*sin(s)-mA*qy1*cos(s);
	*/

	if(MVector!=NULL){
		for(int i=0;i<Area.GetFLineLen();i++){
			int y =Area.GetFLineAbsY  (i);
			if((y%MVectorYRes)!=0)
				continue;
			y=y/MVectorYRes;
			if(y>=MVectorYNumb)
				continue;
			int x1=Area.GetFLineLeftX (i);
			int x2=Area.GetFLineRightX(i);
			x1=x1/MVectorXRes;
			x2=(x2+MVectorXRes-1)/MVectorXRes;
			if(x1<0)
				x1=0;
			if(x2>=MVectorXNumb)
				x2=MVectorXNumb;
			int my=y*MVectorYRes+MVectorYRes/2;
			for(int x=x1;x<x2;x++){
				int mx=x*MVectorXRes+MVectorXRes/2;
				MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*ALResult[0].AlignmentLargeResult[0]+my*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2])-mx);
				MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*ALResult[0].AlignmentLargeResult[3]+my*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5])-my);
			}
		}
	}
	AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();

	int	AlignmentLargePacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList *PListDim[10000];
	AlignmentPacket2DList **PList;

	if(AlignmentLargePacket2ContainerNumb>sizeof(PListDim)/sizeof(PListDim[0])){
		PList=new AlignmentPacket2DList *[AlignmentLargePacket2ContainerNumb];
	}
	else{
		PList=PListDim;
	}
	int	N=0;
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
				//	&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
				if(p->Area==this
				&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
					p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[0]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[3]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5]-p->PosYOnTarget;
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Rotation=ALRotation;
					p->Calculated=true;
				}
			}
		}
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			//if(p->PosXOnTarget==1919 && p->PosYOnTarget==1376){
			//	p->Calculated=false;
			//}
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
				if(p->Area==this){
					p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[0]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[3]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5]-p->PosYOnTarget;
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Rotation=ALRotation;
					p->Calculated=true;
				}
			}
		}
	}
	if(PListDim!=PList){
		delete	[]PList;
		PList=NULL;
	}
	ResultPointCounts=_Aligned2;
	return true;
}

static	int	ALDbgPage=2;
static	int	ALDbgLayer=1;
static	int	ALDbgID	=2;
static	int	ALDbg	=0;
static	int	ALDPosXTarget=773;
static	int	ALDPosYTarget=17492;

bool	XAlignmentLargeArea::Calc3( QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	if(GetPage()==ALDbgPage && GetLayer()==ALDbgLayer && GetID()==ALDbgID)
		ALDbg++;

	int	fN1,fN2,fN3;
	struct	AlignmentLargeShiftItemListStruct fBestMatch1[3];
	struct	AlignmentLargeShiftItemListStruct fBestMatch2[3];
	struct	AlignmentLargeShiftItemListStruct fBestMatch3[3];
	TriangleArea *fA=TriangleContainer.GetFirst();
	int		MaxN=0;
	int		MaxTotalN=0;
	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		fN1=a->Pa->GetMachingPoint(fBestMatch1);
		fN2=a->Pb->GetMachingPoint(fBestMatch2);
		fN3=a->Pc->GetMachingPoint(fBestMatch3);
		int	n=0;
		if(fN1!=0)
			n++;
		if(fN2!=0)
			n++;
		if(fN3!=0)
			n++;
		if(n>MaxN){
			fA=a;
			MaxN=n;
			MaxTotalN=fN1+fN2+fN3;
		}
		else if(n==MaxN){
			int	d=fN1+fN2+fN3;
			if(d>MaxTotalN){
				MaxTotalN=d;
				fA=a;
			}
		}
	}
	fN1=fA->Pa->GetMachingPoint(fBestMatch1);
	fN2=fA->Pb->GetMachingPoint(fBestMatch2);
	fN3=fA->Pc->GetMachingPoint(fBestMatch3);

	if(fN1==0 && fN2==0 && fN3==0){
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned0;
		return Calc0(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes);
	}
	if(fN1>0 && fN2==0 && fN3==0){
		int	k1=GetGPackClassNumber(fA->Pa);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned1;
		return Calc1(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1);
	}
	if(fN1==0 && fN2>0 && fN3==0){
		int	k1=GetGPackClassNumber(fA->Pb);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned1;
		return Calc1(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1);
	}
	if(fN1==0 && fN2==0 && fN3>0){
		int	k1=GetGPackClassNumber(fA->Pc);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned1;
		return Calc1(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1);
	}
	if(fN1>0 && fN2>0 && fN3==0){
		int	k1=GetGPackClassNumber(fA->Pa);
		int	k2=GetGPackClassNumber(fA->Pb);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned2;
		return Calc2(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1,k2);
	}
	if(fN1>0 && fN2==0 && fN3>0){
		int	k1=GetGPackClassNumber(fA->Pa);
		int	k2=GetGPackClassNumber(fA->Pc);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned2;
		return Calc2(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1,k2);
	}
	if(fN1==0 && fN2>0 && fN3>0){
		int	k1=GetGPackClassNumber(fA->Pb);
		int	k2=GetGPackClassNumber(fA->Pc);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned2;
		return Calc2(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1,k2);
	}
	
	for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
		struct	AlignmentLargeShiftItemListStruct BestMatch1[3];
		int	N1=A->Pa->GetMachingPoint(BestMatch1);
		struct	AlignmentLargeShiftItemListStruct BestMatch2[3];
		int	N2=A->Pb->GetMachingPoint(BestMatch2);
		struct	AlignmentLargeShiftItemListStruct BestMatch3[3];
		int	N3=A->Pc->GetMachingPoint(BestMatch3);
		
		if(N1==0 || N2==0 || N3==0){
			A->Effective=false;
			continue;
		}
		A->Effective=true;

		AlignmentLargeBase	*PBase=dynamic_cast<AlignmentLargeBase *>(ParentInLayer->GetParentBase());

		int	IndexI=0;
		int	IndexJ=0;
		int	IndexK=0;
		double	MinTransformingRate=99999999;
		for(int i=0;i<3 && i<N1;i++){
			if(i>0){
				if(BestMatch1[0].Match - BestMatch1[i].Match>PBase->AdoptedMinD){
					break;
				}
			}
			for(int j=0;j<3 && j<N2;j++){
				if(j>0){
					if(BestMatch2[0].Match - BestMatch2[j].Match>PBase->AdoptedMinD){
						break;
					}
				}
				for(int k=0;k<3 && k<N3;k++){
					if(k>0){
						if(BestMatch3[0].Match - BestMatch3[k].Match>PBase->AdoptedMinD){
							break;
						}
					}
					double	TransformingRate=MakeTransformingRate(BestMatch1[i],BestMatch2[j],BestMatch3[k]);
					if(TransformingRate<MinTransformingRate){
						MinTransformingRate=TransformingRate;
						IndexI=i;
						IndexJ=j;
						IndexK=k;
					}
				}
			}
		}

		A->Pa->SetAdopted(BestMatch1[IndexI]);
		A->Pb->SetAdopted(BestMatch2[IndexJ]);
		A->Pc->SetAdopted(BestMatch3[IndexK]);

		double  PP[3][2];
		double  PQ[3][2];
		PP[0][0]=BestMatch1[IndexI].Item->MasterX;
		PP[0][1]=BestMatch1[IndexI].Item->MasterY;
		PP[1][0]=BestMatch2[IndexJ].Item->MasterX;
		PP[1][1]=BestMatch2[IndexJ].Item->MasterY;
		PP[2][0]=BestMatch3[IndexK].Item->MasterX;
		PP[2][1]=BestMatch3[IndexK].Item->MasterY;

		PQ[0][0]=BestMatch1[IndexI].Item->MasterX+BestMatch1[IndexI].Dx;
		PQ[0][1]=BestMatch1[IndexI].Item->MasterY+BestMatch1[IndexI].Dy;
		PQ[1][0]=BestMatch2[IndexJ].Item->MasterX+BestMatch2[IndexJ].Dx;
		PQ[1][1]=BestMatch2[IndexJ].Item->MasterY+BestMatch2[IndexJ].Dy;
		PQ[2][0]=BestMatch3[IndexK].Item->MasterX+BestMatch3[IndexK].Dx;
		PQ[2][1]=BestMatch3[IndexK].Item->MasterY+BestMatch3[IndexK].Dy;
		if(Get3LevelResolve(PP , PQ ,A->m)==false)
			return(false);
	}
	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Effective==true){
			a->GetCenter(a->TotalCx,a->TotalCy);
		}
	}

	if(MVector!=NULL){
		int	ALen=Area.GetFLineLen();
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<ALen;i++){
				int y =Area.GetFLineAbsY  (i);
				if((y%MVectorYRes)==0){
					y=y/MVectorYRes;
					if(0<=y && y<MVectorYNumb){
						int x1=Area.GetFLineLeftX (i);
						int x2=Area.GetFLineRightX(i);
						x1=x1/MVectorXRes;
						x2=(x2+MVectorXRes-1)/MVectorXRes;
						if(x1<0)
							x1=0;
						if(x2>=MVectorXNumb)
							x2=MVectorXNumb;
						int my=y*MVectorYRes+MVectorYRes/2;
						for(int x=x1;x<x2;x++){
							int mx=x*MVectorXRes+MVectorXRes/2;
							TriangleArea	*h=GetNearestTriangleInTable(mx,my);
							if(h!=NULL){
								MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*h->m[0]+my*h->m[1]+h->m[2])-mx);
								MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*h->m[3]+my*h->m[4]+h->m[5])-my);
							}
							else{
								MVector[y*MVectorXNumb+x].setX(0);
								MVector[y*MVectorXNumb+x].setY(0);
							}
						}
					}
				}
			}
		}
	}
	AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();

	int	AlignmentLargePacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList *PListDim[10000];
	AlignmentPacket2DList **PList;

	if(AlignmentLargePacket2ContainerNumb>sizeof(PListDim)/sizeof(PListDim[0])){
		PList=new AlignmentPacket2DList *[AlignmentLargePacket2ContainerNumb];
	}
	else{
		PList=PListDim;
	}
	int	N=0;
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}

	static	TriangleArea	*DbgH;
	#pragma omp parallel                             
	{                                                
		#pragma omp for schedule(dynamic)
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
				if(p->Area==this
				&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
					TriangleArea	*h=GetNearestTriangleInTable(p->PosXOnTarget,p->PosYOnTarget);
					if(h!=NULL){
						p->ShiftX	=p->PosXOnTarget*h->m[0]+p->PosYOnTarget*h->m[1]+h->m[2]-p->PosXOnTarget;
						p->ShiftY	=p->PosXOnTarget*h->m[3]+p->PosYOnTarget*h->m[4]+h->m[5]-p->PosYOnTarget;
						p->Rotation	=h->GetRotation();
						p->Handle	=h;
					}
					else{
						p->ShiftX=0;
						p->ShiftY=0;
						p->Handle=NULL;
					}
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Calculated=true;
				}
			}
		}

		#pragma omp for schedule(dynamic)
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->PosXOnTarget==7141 && p->PosYOnTarget==459){
				ALDbg++;
			}
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				//if(p->PosXOnTarget==ALDPosXTarget && p->PosYOnTarget==ALDPosYTarget)
				//	ALDbg++;
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
				if(p->Area==this){
					TriangleArea	*h=GetNearestTriangleInTable(p->PosXOnTarget,p->PosYOnTarget);
					DbgH=h;
					if(h!=NULL){
						p->ShiftX	=p->PosXOnTarget*h->m[0]+p->PosYOnTarget*h->m[1]+h->m[2]-p->PosXOnTarget;
						p->ShiftY	=p->PosXOnTarget*h->m[3]+p->PosYOnTarget*h->m[4]+h->m[5]-p->PosYOnTarget;
						p->Rotation	=h->GetRotation();
						p->Handle	=h;
					}
					else{
						p->ShiftX=0;
						p->ShiftY=0;
						p->Handle=NULL;
					}
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Calculated=true;
				}
			}
		}
	}
	if(PListDim!=PList){
		delete	[]PList;
		PList=NULL;
	}

	int	nn=0;
	for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
		if(A->Effective==true){
			nn++;
		}
	}
	if(ALResultAllocatedNumb<nn){
		delete	[]ALResult;
		ALResultAllocatedNumb=nn;
		ALResult=new AlignmentLargeResultClass[ALResultAllocatedNumb];
	}
	ALResultNumb=0;
	for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
		if(A->Effective==true){
			ALResult[ALResultNumb].AlignmentLargeResult[0]=A->m[0];
			ALResult[ALResultNumb].AlignmentLargeResult[1]=A->m[1];
			ALResult[ALResultNumb].AlignmentLargeResult[2]=A->m[2];
			ALResult[ALResultNumb].AlignmentLargeResult[3]=A->m[3];
			ALResult[ALResultNumb].AlignmentLargeResult[4]=A->m[4];
			ALResult[ALResultNumb].AlignmentLargeResult[5]=A->m[5];
			ALResultNumb++;
		}
	}
	ResultPointCounts=_Aligned3;
	return(true);
}

int		XAlignmentLargeArea::GetItemCount(void)
{
	int	ItemCount=0;
	if(ParentInLayer!=NULL){
		for(AlgorithmItemPLI *t=ParentInLayer->GetFirstData();t!=NULL;t=t->GetNext()){
			XAlignmentLarge	*AItem=dynamic_cast<XAlignmentLarge *>(t);
			if(AItem!=NULL){
				if(AItem->AreaID==AreaID){
					ItemCount++;
				}
			}
		}
	}
	return ItemCount;
}

bool	XAlignmentLargeArea::CalcAllocateOnly0(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	return(true);
}
bool	XAlignmentLargeArea::CalcAllocateOnly1(
				QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	Index)
{
	struct	AlignmentLargeShiftItemListStruct BestMatch[3];
	int	N=GPackClass[Index].GetMachingPoint(BestMatch);
	if(N==0){
		return CalcAllocateOnly0(MVector
				,MVectorXNumb	,MVectorYNumb
				,MVectorXRes	,MVectorYRes);
	}

	int Mx=(N>0)?BestMatch[0].Dx:0;
	int My=(N>0)?BestMatch[0].Dy:0;

	AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999 && p->Calculated==false){
			//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
			if(p->Area==this
			&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
				p->ShiftX=Mx;
				p->ShiftY=My;
				if(p->ShiftX<-MaxSearchAreaFromItem)
					p->ShiftX=-MaxSearchAreaFromItem;
				if(p->ShiftX>MaxSearchAreaFromItem)
					p->ShiftX= MaxSearchAreaFromItem;
				if(p->ShiftY<-MaxSearchAreaFromItem)
					p->ShiftY=-MaxSearchAreaFromItem;
				if(p->ShiftY>MaxSearchAreaFromItem)
					p->ShiftY= MaxSearchAreaFromItem;
				p->Calculated=true;
			}
		}
	}
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999 && p->Calculated==false){
			//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
			if(p->Area==this){
				p->ShiftX=Mx;
				p->ShiftY=My;
				if(p->ShiftX<-MaxSearchAreaFromItem)
					p->ShiftX=-MaxSearchAreaFromItem;
				if(p->ShiftX>MaxSearchAreaFromItem)
					p->ShiftX= MaxSearchAreaFromItem;
				if(p->ShiftY<-MaxSearchAreaFromItem)
					p->ShiftY=-MaxSearchAreaFromItem;
				if(p->ShiftY>MaxSearchAreaFromItem)
					p->ShiftY= MaxSearchAreaFromItem;
				p->Calculated=true;
			}
		}
	}

	return(true);
}

bool	XAlignmentLargeArea::CalcAllocateOnly2(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	IndexA		,int	IndexB)
{
	struct	AlignmentLargeShiftItemListStruct BestMatch1[3];
	int	N1=GPackClass[IndexA].GetMachingPoint(BestMatch1);
	struct	AlignmentLargeShiftItemListStruct BestMatch2[3];
	int	N2=GPackClass[IndexB].GetMachingPoint(BestMatch2);

	if(N1==0 && N2==0){
		ResultPointCounts=_Aligned0;
		return CalcAllocateOnly0(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
	}
	if(N1>0 && N2==0){
		ResultPointCounts=_Aligned1;
		return CalcAllocateOnly1(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes
				,0);
	}
	else if(N1==0 && N2>0){
		ResultPointCounts=_Aligned1;
		return CalcAllocateOnly1(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes
				,1);
	}

	AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();

	int	AlignmentLargePacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList *PListDim[10000];
	AlignmentPacket2DList **PList;

	if(AlignmentLargePacket2ContainerNumb>sizeof(PListDim)/sizeof(PListDim[0])){
		PList=new AlignmentPacket2DList *[AlignmentLargePacket2ContainerNumb];
	}
	else{
		PList=PListDim;
	}
	int	N=0;
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999 && p->Calculated==false){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
				if(p->Area==this
				&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
					p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[0]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[3]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5]-p->PosYOnTarget;
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Calculated=true;
				}
			}
		}
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			//if(p->PosXOnTarget==1919 && p->PosYOnTarget==1376){
			//	p->Calculated=false;
			//}
			if(p->ShiftX==99999999 && p->ShiftY==99999999 && p->Calculated==false){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
				if(p->Area==this){
					p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[0]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[1]+ALResult[0].AlignmentLargeResult[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentLargeResult[3]+p->PosYOnTarget*ALResult[0].AlignmentLargeResult[4]+ALResult[0].AlignmentLargeResult[5]-p->PosYOnTarget;
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Calculated=true;
				}
			}
		}
	}
	if(PListDim!=PList){
		delete	[]PList;
		PList=NULL;
	}

	return true;
}


bool	XAlignmentLargeArea::CalcAllocateOnly3( QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	if(GetPage()==ALDbgPage && GetLayer()==ALDbgLayer && GetID()==ALDbgID)
		ALDbg++;

	int	fN1,fN2,fN3;
	struct	AlignmentLargeShiftItemListStruct fBestMatch1[3];
	struct	AlignmentLargeShiftItemListStruct fBestMatch2[3];
	struct	AlignmentLargeShiftItemListStruct fBestMatch3[3];
	TriangleArea *fA=TriangleContainer.GetFirst();
	int		MaxN=0;
	int		MaxTotalN=0;
	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		fN1=a->Pa->GetMachingPoint(fBestMatch1);
		fN2=a->Pb->GetMachingPoint(fBestMatch2);
		fN3=a->Pc->GetMachingPoint(fBestMatch3);
		int	n=0;
		if(fN1!=0)
			n++;
		if(fN2!=0)
			n++;
		if(fN3!=0)
			n++;
		if(n>MaxN){
			fA=a;
			MaxN=n;
			MaxTotalN=fN1+fN2+fN3;
		}
		else if(n==MaxN){
			int	d=fN1+fN2+fN3;
			if(d>MaxTotalN){
				MaxTotalN=d;
				fA=a;
			}
		}
	}
	fN1=fA->Pa->GetMachingPoint(fBestMatch1);
	fN2=fA->Pb->GetMachingPoint(fBestMatch2);
	fN3=fA->Pc->GetMachingPoint(fBestMatch3);

	if(fN1==0 && fN2==0 && fN3==0){
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned0;
		return CalcAllocateOnly0(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes);
	}
	if(fN1>0 && fN2==0 && fN3==0){
		int	k1=GetGPackClassNumber(fA->Pa);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned1;
		return CalcAllocateOnly1(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1);
	}
	if(fN1==0 && fN2>0 && fN3==0){
		int	k1=GetGPackClassNumber(fA->Pb);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned1;
		return CalcAllocateOnly1(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1);
	}
	if(fN1==0 && fN2==0 && fN3>0){
		int	k1=GetGPackClassNumber(fA->Pc);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned1;
		return CalcAllocateOnly1(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1);
	}
	if(fN1>0 && fN2>0 && fN3==0){
		int	k1=GetGPackClassNumber(fA->Pa);
		int	k2=GetGPackClassNumber(fA->Pb);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned2;
		return CalcAllocateOnly2(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1,k2);
	}
	if(fN1>0 && fN2==0 && fN3>0){
		int	k1=GetGPackClassNumber(fA->Pa);
		int	k2=GetGPackClassNumber(fA->Pc);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned2;
		return CalcAllocateOnly2(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1,k2);
	}
	if(fN1==0 && fN2>0 && fN3>0){
		int	k1=GetGPackClassNumber(fA->Pb);
		int	k2=GetGPackClassNumber(fA->Pc);
		for(TriangleArea *A=TriangleContainer.GetFirst();A!=NULL;A=A->GetNext()){
			A->Effective=false;
		}
		ResultPointCounts=_Aligned2;
		return CalcAllocateOnly2(MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes	,MVectorYRes
			,k1,k2);
	}
	
	AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();
	int	AlignmentLargePacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList *PListDim[10000];
	AlignmentPacket2DList **PList;

	if(AlignmentLargePacket2ContainerNumb>sizeof(PListDim)/sizeof(PListDim[0])){
		PList=new AlignmentPacket2DList *[AlignmentLargePacket2ContainerNumb];
	}
	else{
		PList=PListDim;
	}
	int	N=0;
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}

	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Effective==true){
			a->GetCenter(a->TotalCx,a->TotalCy);
		}
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999 && p->Calculated==false){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
				if(p->Area==this
				&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
					TriangleArea	*h=GetNearestTriangleInTable(p->PosXOnTarget,p->PosYOnTarget);
					if(h!=NULL){
						p->ShiftX	=p->PosXOnTarget*h->m[0]+p->PosYOnTarget*h->m[1]+h->m[2]-p->PosXOnTarget;
						p->ShiftY	=p->PosXOnTarget*h->m[3]+p->PosYOnTarget*h->m[4]+h->m[5]-p->PosYOnTarget;
						p->Rotation	=h->GetRotation();
						p->Handle	=h;
					}
					else{
						p->ShiftX=0;
						p->ShiftY=0;
						p->Handle=NULL;
					}
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Calculated=true;
				}
			}
		}
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentLargePacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999 && p->Calculated==false){
				//if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
				if(p->Area==this){
					TriangleArea	*h=GetNearestTriangleInTable(p->PosXOnTarget,p->PosYOnTarget);
					if(h!=NULL){
						p->ShiftX	=p->PosXOnTarget*h->m[0]+p->PosYOnTarget*h->m[1]+h->m[2]-p->PosXOnTarget;
						p->ShiftY	=p->PosXOnTarget*h->m[3]+p->PosYOnTarget*h->m[4]+h->m[5]-p->PosYOnTarget;
						p->Rotation	=h->GetRotation();
						p->Handle	=h;
					}
					else{
						p->ShiftX=0;
						p->ShiftY=0;
						p->Handle=NULL;
					}
					if(p->ShiftX<-MaxSearchAreaFromItem)
						p->ShiftX=-MaxSearchAreaFromItem;
					if(p->ShiftX>MaxSearchAreaFromItem)
						p->ShiftX= MaxSearchAreaFromItem;
					if(p->ShiftY<-MaxSearchAreaFromItem)
						p->ShiftY=-MaxSearchAreaFromItem;
					if(p->ShiftY>MaxSearchAreaFromItem)
						p->ShiftY= MaxSearchAreaFromItem;
					p->Calculated=true;
				}
			}
		}
	}
	if(PListDim!=PList){
		delete	[]PList;
		PList=NULL;
	}


	return(true);
}

void	XAlignmentLargeArea::SetGroup(FlexArea &area ,int groupNumber)
{
	for(XAlignmentLargePointer *a=GPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(area.IsInclude(&a->Point->GetArea())==true){
			a->Point->GroupNumber=groupNumber;
		}
	}
}

int		XAlignmentLargeArea::GetGPackClassNumber(XAlignmentLargePointerContainer *p)
{
	for(int i=0;i<GPackClassNumb;i++){
		if(p==&GPackClass[i])
			return i;
	}
	return -1;
}
XAlignmentLarge	*XAlignmentLargeArea::GetItemInPriority(int priority)
{
	for(XAlignmentLargePointer *a=GPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Point->Priority==priority)
			return a->Point;
	}
	return NULL;
}

struct	FrameLineBetweenPoint
{
	XAlignmentLargePointerContainer	*Pa;
	XAlignmentLargePointerContainer	*Pb;
	double	Len;
};

int	SortFuncLFrame(const void *a ,const void *b)
{
	struct	FrameLineBetweenPoint	*pa=(struct	FrameLineBetweenPoint *)a;
	struct	FrameLineBetweenPoint	*pb=(struct	FrameLineBetweenPoint *)b;
	if(pa->Len<pb->Len)
		return -1;
	if(pa->Len>pb->Len)
		return 1;
	return 0;
}

bool IsCross(struct	FrameLineBetweenPoint &A 
			,struct	FrameLineBetweenPoint &B)
{
	double	Cx11,Cy11;
	double	Cx12,Cy12;
	double	Cx21,Cy21;
	double	Cx22,Cy22;
	double	X, Y;

	A.Pa->GetCenter(Cx11,Cy11);
	A.Pb->GetCenter(Cx12,Cy12);
	B.Pa->GetCenter(Cx21,Cy21);
	B.Pb->GetCenter(Cx22,Cy22);
	
	if(GetCrossInnerPointWithoutEdge(Cx11,Cy11 ,Cx12,Cy12
									,Cx21,Cy21 ,Cx22,Cy22
									,X, Y)==true){
		return true;
	}
	return false;
}

TriangleArea::TriangleArea(void)
{
	Cax=Cay=0;
	Cbx=Cby=0;
	Ccx=Ccy=0;

	Pa=NULL;
	Pb=NULL;
	Pc=NULL;

	Dax=Day=0;
	Dbx=Dby=0;
	Dcx=Dcy=0;

	m[0]=0;
	m[1]=0;
	m[2]=0;
	m[3]=0;
	m[4]=0;
	m[5]=0;
	TotalCx=TotalCy=0;

	Effective=true;
}

void	TriangleArea::GetCenter(double &Cx, double &Cy)
{
	/*
	double Cxa, Cya;
	double Cxb, Cyb;
	double Cxc, Cyc;
	Pa->GetCenter(Cxa, Cya);
	Pb->GetCenter(Cxb, Cyb);
	Pc->GetCenter(Cxc, Cyc);
	Cx=(Cxa+Cxb+Cxc)/3;
	Cy=(Cya+Cyb+Cyc)/3;
	*/

	Cax=Cay=0;
	Cbx=Cby=0;
	Ccx=Ccy=0;
	if(Pa!=NULL){
		Pa->GetCenter(Cax, Cay);
	}
	if(Pb!=NULL){
		Pb->GetCenter(Cbx, Cby);
	}
	if(Pc!=NULL){
		Pc->GetCenter(Ccx, Ccy);
	}
	Cx=(Cax+Cbx+Ccx)/3;
	Cy=(Cay+Cby+Ccy)/3;
}

double	TriangleArea::GetRotation(void)
{
	double	A ,B, Tx ,Ty ,S ,R;
	if(GetAffinDecompose(m 
					,A ,B, Tx ,Ty ,S ,R)==true){
		return R;
	}
	return 0.0;
}

struct	TmpTriangle
{
	XAlignmentLargePointerContainer	*Pa;
	XAlignmentLargePointerContainer	*Pb;
	XAlignmentLargePointerContainer	*Pc;
	double	R;
};
int	SorTmpTriangleData(const void *a ,const void *b)
{
	struct	TmpTriangle	*pa=(struct	TmpTriangle *)a;
	struct	TmpTriangle	*pb=(struct	TmpTriangle *)b;
	if(pa->R<pb->R)
		return -1;
	if(pa->R>pb->R)
		return 1;
	return 0;
}


bool	XAlignmentLargeArea::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	if(EInfo.HasChangedOnlyImage==false){
		for(int i=0;i<MaxGPackNumb;i++){
			GPackClass[i].RemoveAll();
		}
		GPackClassNumb=0;
		for(XAlignmentLargePointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Point->GroupNumber>0){
				int	k;
				for(k=0;k<GPackClassNumb;k++){
					if(GPackClass[k].GetFirst()!=NULL 
					&& GPackClass[k].GetFirst()->Point->GroupNumber==g->Point->GroupNumber){
						XAlignmentLargePointer	*t=new XAlignmentLargePointer(g->Point);
						GPackClass[k].AppendList(t);
						break;
					}
				}
				if(k>=GPackClassNumb){
					XAlignmentLargePointer	*t=new XAlignmentLargePointer(g->Point);
					GPackClass[GPackClassNumb].AppendList(t);
					GPackClassNumb++;
					if(GPackClassNumb>=MaxGPackNumb){
						break;
					}
				}
			}
			else{
				XAlignmentLargePointer	*t=new XAlignmentLargePointer(g->Point);
				GPackClass[GPackClassNumb].AppendList(t);
				GPackClassNumb++;
				if(GPackClassNumb>=MaxGPackNumb){
					break;
				}
			}
		}

		if(GPackClassNumb>=3){
			struct	TmpTriangle	*TmpTriangleData=new struct	TmpTriangle[GPackClassNumb*(GPackClassNumb-1)*(GPackClassNumb-2)];
			int	HNumb=0;
			for(int i=0;i<GPackClassNumb;i++){
				for(int j=i+1;j<GPackClassNumb;j++){
					for(int k=j+1;k<GPackClassNumb;k++){
						double	Cx1,Cy1;
						double	Cx2,Cy2;
						double	Cx3,Cy3;
						GPackClass[i].GetCenter(Cx1,Cy1);
						GPackClass[j].GetCenter(Cx2,Cy2);
						GPackClass[k].GetCenter(Cx3,Cy3);
						TmpTriangleData[HNumb].Pa=&GPackClass[i];
						TmpTriangleData[HNumb].Pb=&GPackClass[j];
						TmpTriangleData[HNumb].Pc=&GPackClass[k];
						double	Cx,Cy,R;
						if(CalcCircleFrom3Points(Cx1,Cy1
												,Cx2,Cy2
												,Cx3,Cy3
												,Cx, Cy ,R)==true){
							TmpTriangleData[HNumb].R=R;
							HNumb++;
						}
					}
				}
			}
			QSort(TmpTriangleData,HNumb,sizeof(TmpTriangleData[0]),SorTmpTriangleData);

			TriangleContainer.RemoveAll();
			for(int i=0;i<HNumb;i++){
				bool	ExistAB=false;
				bool	ExistBC=false;
				bool	ExistCA=false;
				for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
					if((TmpTriangleData[i].Pa==a->Pa && TmpTriangleData[i].Pb==a->Pb)
					|| (TmpTriangleData[i].Pa==a->Pb && TmpTriangleData[i].Pb==a->Pa)
					|| (TmpTriangleData[i].Pa==a->Pb && TmpTriangleData[i].Pb==a->Pc)
					|| (TmpTriangleData[i].Pa==a->Pc && TmpTriangleData[i].Pb==a->Pb)
					|| (TmpTriangleData[i].Pa==a->Pc && TmpTriangleData[i].Pb==a->Pa)
					|| (TmpTriangleData[i].Pa==a->Pa && TmpTriangleData[i].Pb==a->Pc)){
						ExistAB=true;
						break;
					}
				}
				for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
					if((TmpTriangleData[i].Pb==a->Pa && TmpTriangleData[i].Pc==a->Pb)
					|| (TmpTriangleData[i].Pb==a->Pb && TmpTriangleData[i].Pc==a->Pa)
					|| (TmpTriangleData[i].Pb==a->Pb && TmpTriangleData[i].Pc==a->Pc)
					|| (TmpTriangleData[i].Pb==a->Pc && TmpTriangleData[i].Pc==a->Pb)
					|| (TmpTriangleData[i].Pb==a->Pc && TmpTriangleData[i].Pc==a->Pa)
					|| (TmpTriangleData[i].Pb==a->Pa && TmpTriangleData[i].Pc==a->Pc)){
						ExistBC=true;
						break;
					}
				}
				for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
					if((TmpTriangleData[i].Pc==a->Pa && TmpTriangleData[i].Pa==a->Pb)
					|| (TmpTriangleData[i].Pc==a->Pb && TmpTriangleData[i].Pa==a->Pa)
					|| (TmpTriangleData[i].Pc==a->Pb && TmpTriangleData[i].Pa==a->Pc)
					|| (TmpTriangleData[i].Pc==a->Pc && TmpTriangleData[i].Pa==a->Pb)
					|| (TmpTriangleData[i].Pc==a->Pc && TmpTriangleData[i].Pa==a->Pa)
					|| (TmpTriangleData[i].Pc==a->Pa && TmpTriangleData[i].Pa==a->Pc)){
						ExistCA=true;
						break;
					}
				}
				if(ExistAB==false || ExistBC==false || ExistCA==false){
					TriangleArea	*H=new TriangleArea();
					H->Pa=TmpTriangleData[i].Pa;
					H->Pb=TmpTriangleData[i].Pb;
					H->Pc=TmpTriangleData[i].Pc;
					TriangleContainer.AppendList(H);
				}
			}
			delete	[]TmpTriangleData;
		}

		/*
			To divide triangle ideally
				1: Connect to each points from closer, and remove line which crosses without own line
				2: Register triangle when these any 3 lines make triangle
		*/
		/*
		if(GPackClassNumb>=3){
			struct	FrameLineBetweenPoint	*LFrame=new struct	FrameLineBetweenPoint[GPackClassNumb*(GPackClassNumb-1)/2];
			int	HNumb=0;
			for(int i=0;i<GPackClassNumb;i++){
				for(int j=i+1;j<GPackClassNumb;j++){
					double	Cx1,Cy1;
					double	Cx2,Cy2;
					GPackClass[i].GetCenter(Cx1,Cy1);
					GPackClass[j].GetCenter(Cx2,Cy2);
					LFrame[HNumb].Pa=&GPackClass[i];
					LFrame[HNumb].Pb=&GPackClass[j];
					LFrame[HNumb].Len	=hypot(Cx1-Cx2,Cy1-Cy2);
					HNumb++;
				}
			}
			QSort(LFrame,HNumb,sizeof(LFrame[0]),SortFuncLFrame);
			for(int i=0;i<HNumb;i++){
				for(int j=0;j<i;j++){
					if(LFrame[j].Len>0 
					&& (LFrame[i].Pa!=LFrame[j].Pa)
					&& (LFrame[i].Pa!=LFrame[j].Pb)
					&& (LFrame[i].Pb!=LFrame[j].Pa)
					&& (LFrame[i].Pb!=LFrame[j].Pb)){
						if(IsCross(LFrame[i],LFrame[j])==true){
							LFrame[i].Len=-1;
						}
					}
				}
			}
			for(int i=0;i<HNumb;i++){
				if(LFrame[i].Len<0)	continue;
				for(int j=i+1;j<HNumb;j++){
					if(LFrame[j].Len<0)	continue;
					if(LFrame[i].Pa==LFrame[j].Pa){
						for(int k=j+1;k<HNumb;k++){
							if(LFrame[k].Len<0)	continue;
							if((LFrame[i].Pb==LFrame[k].Pa && LFrame[j].Pb==LFrame[k].Pb)
							|| (LFrame[i].Pb==LFrame[k].Pb && LFrame[j].Pb==LFrame[k].Pa)){
								TriangleArea	*H=new TriangleArea();
								H->Pa=LFrame[i].Pa;
								H->Pb=LFrame[i].Pb;
								H->Pc=LFrame[j].Pb;
								TriangleContainer.AppendList(H);
							}
						}
					}
					else if(LFrame[i].Pa==LFrame[j].Pb){
						for(int k=j+1;k<HNumb;k++){
							if(LFrame[k].Len<0)	continue;
							if((LFrame[i].Pb==LFrame[k].Pa && LFrame[j].Pa==LFrame[k].Pb)
							|| (LFrame[i].Pb==LFrame[k].Pb && LFrame[j].Pa==LFrame[k].Pa)){
								TriangleArea	*H=new TriangleArea();
								H->Pa=LFrame[i].Pa;
								H->Pb=LFrame[i].Pb;
								H->Pc=LFrame[j].Pa;
								TriangleContainer.AppendList(H);
							}
						}
					}
					else if(LFrame[i].Pb==LFrame[j].Pa){
						for(int k=j+1;k<HNumb;k++){
							if(LFrame[k].Len<0)	continue;
							if((LFrame[i].Pa==LFrame[k].Pa && LFrame[j].Pb==LFrame[k].Pb)
							|| (LFrame[i].Pa==LFrame[k].Pb && LFrame[j].Pb==LFrame[k].Pa)){
								TriangleArea	*H=new TriangleArea();
								H->Pa=LFrame[i].Pb;
								H->Pb=LFrame[i].Pa;
								H->Pc=LFrame[j].Pb;
								TriangleContainer.AppendList(H);
							}
						}
					}
					else if(LFrame[i].Pb==LFrame[j].Pb){
						for(int k=j+1;k<HNumb;k++){
							if(LFrame[k].Len<0)	continue;
							if((LFrame[i].Pa==LFrame[k].Pa && LFrame[j].Pa==LFrame[k].Pb)
							|| (LFrame[i].Pa==LFrame[k].Pb && LFrame[j].Pa==LFrame[k].Pa)){
								TriangleArea	*H=new TriangleArea();
								H->Pa=LFrame[i].Pb;
								H->Pb=LFrame[i].Pa;
								H->Pc=LFrame[j].Pa;
								TriangleContainer.AppendList(H);
							}
						}
					}
				}
			}
			delete	[]LFrame;
		}
		*/



		AlignmentLargeInPage	*ap=(AlignmentLargeInPage *)ParentInLayer->GetParentInPage();
		AlignmentLargeBase		*ABase=(AlignmentLargeBase *)ap->GetParentBase();
		MaxSearchAreaFromItem	=ABase->MaxSearchAreaFromItem;
		
		if(ABase->UseOtherPage==true && GPackClassNumb<=ABase->PointsToUseOtherPage){
			OtherPack.RemoveAll();
			int	page=ParentInLayer->GetPage();
			int	CurrentGlobalPage	=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(page);

			//Search from closer page from own page
			for(int PageLen=1;PageLen<ParentInLayer->GetLayersBase()->GetGlobalPageNumb();PageLen++){
				int globalpage=CurrentGlobalPage-PageLen;
				if(0<=globalpage && globalpage<ParentInLayer->GetLayersBase()->GetGlobalPageNumb()){
					SlaveCommReqAlignmentLargePoint	RCmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
					SlaveCommAckAlignmentLargePoint	ACmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
					RCmd.Layer	=ParentInLayer->GetLayer();
					RCmd.AreaID	=AreaID;
					RCmd.AreaName	=AreaName;
					if(RCmd.Send(globalpage,0,ACmd)==true){
						if(ACmd.AlignmentLargePointData.IsEmpty()==false){
							OtherPack+=ACmd.AlignmentLargePointData;
						}
					}
					if(GPackClassNumb+OtherPack.GetCount()>=3){
						break;
					}
				}
				globalpage=CurrentGlobalPage+PageLen;
				if(0<=globalpage && globalpage<ParentInLayer->GetLayersBase()->GetGlobalPageNumb()){
					SlaveCommReqAlignmentLargePoint	RCmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
					SlaveCommAckAlignmentLargePoint	ACmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
					RCmd.Layer	=ParentInLayer->GetLayer();
					RCmd.AreaID	=AreaID;
					RCmd.AreaName	=AreaName;
					if(RCmd.Send(globalpage,0,ACmd)==true){
						if(ACmd.AlignmentLargePointData.IsEmpty()==false){
							OtherPack+=ACmd.AlignmentLargePointData;
						}
					}
					if(GPackClassNumb+OtherPack.GetCount()>=3){
						break;
					}
				}
			}
		}

		//Building depending global pointer
		DependingGlobal=NULL;
		if(Priority!=_PriorityGlobal){
			if(DependingGlobal==NULL){
				for(int Layer=0;Layer<ParentInLayer->GetLayerNumb();Layer++){
					AlgorithmInPageRoot	*Pg=ParentInLayer->GetParentInPage();
					AlgorithmInLayerRoot *AL=Pg->GetLayerData(Layer);
					AlignmentLargeInLayer	*A=(AlignmentLargeInLayer *)AL;
					for(XAlignmentLargeArea *a=A->Areas.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Priority==_PriorityGlobal){
							if(a->GPack.GetNumber()>0 && a->Area.CheckOverlap(&Area)==true){
								DependingGlobal=a;
								goto	Found;
							}
						}
					}
				}
			}
	Found:;
		}
	
		for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
			XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
			if(AItem->AreaID==AreaID){
				AItem->Priority=-1;
			}
		}
		double	MostEdgeLen=99999999;
		XAlignmentLarge	*MostEdgeItem=NULL;
		for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
			XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
			if(AItem->AreaID==AreaID){
				double	D1=hypot(AItem->MasterX-0								,AItem->MasterY-0);
				double	D2=hypot(AItem->MasterX-ParentInLayer->GetDotPerLine()	,AItem->MasterY-0);
				double	D3=hypot(AItem->MasterX-0								,AItem->MasterY-ParentInLayer->GetMaxLines());
				double	D4=hypot(AItem->MasterX-ParentInLayer->GetDotPerLine()	,AItem->MasterY-ParentInLayer->GetMaxLines());
				double	D=min(min(D1,D2),min(D3,D4));
				if(D<MostEdgeLen){
					MostEdgeLen=D;
					MostEdgeItem=AItem;
				}
			}
		}
		if(MostEdgeItem!=NULL){
			if(MostEdgeItem->GroupNumber==0){
				MostEdgeItem->Priority=0;
			}
			else{
				for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
					XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
					if(AItem->AreaID==AreaID){
						if(AItem->GroupNumber==MostEdgeItem->GroupNumber){
							AItem->Priority=0;
						}
					}
				}
			}
			double	FarthestLen=0;
			XAlignmentLarge	*FarthestItem=NULL;
			for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
				XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
				if(AItem->AreaID==AreaID && AItem->Priority<0){
					double	D=hypot(AItem->MasterX-MostEdgeItem->MasterX,AItem->MasterY-MostEdgeItem->MasterY);
					if(FarthestLen<D){
						FarthestLen=D;
						FarthestItem=AItem;
					}
				}
			}
			if(FarthestItem!=NULL){
				if(FarthestItem->GroupNumber==0){
					FarthestItem->Priority=1;
				}
				else{
					for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
						XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
						if(AItem->AreaID==AreaID){
							if(AItem->GroupNumber==FarthestItem->GroupNumber){
								AItem->Priority=1;
							}
						}
					}
				}
			}
			for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
				XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
				if(AItem->AreaID==AreaID && AItem->Priority<0){
					AItem->Priority=2;
				}
			}
		}

		for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
			double	Cx,Cy;
			a->GetCenter(Cx,Cy);
		}

		if(NearestTriangleTableDim!=NULL){
			delete	[]NearestTriangleTableDim;
			NearestTriangleTableDim=NULL;
		}
		NearestTriangleTableXRes	=ParentInLayer->GetDotPerLine()/200;
		NearestTriangleTableYRes	=ParentInLayer->GetMaxLines()/200;
		if(NearestTriangleTableXRes==0){
			NearestTriangleTableXRes=1;
		}
		if(NearestTriangleTableYRes==0)
			NearestTriangleTableYRes=1;
		NearestTriangleTableXNumb=ParentInLayer->GetDotPerLine()/NearestTriangleTableXRes;
		NearestTriangleTableYNumb=ParentInLayer->GetMaxLines  ()/NearestTriangleTableYRes;
		NearestTriangleTableDim=new TriangleArea*[NearestTriangleTableXNumb*NearestTriangleTableYNumb];
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int ny=0;ny<NearestTriangleTableYNumb;ny++){
				for(int nx=0;nx<NearestTriangleTableXNumb;nx++){
					int	mx=nx*NearestTriangleTableXRes;
					int	my=ny*NearestTriangleTableYRes;
					NearestTriangleTableDim[ny*NearestTriangleTableXNumb+nx]=GetNearestTriangle(mx ,my);
				}
			}
		}

		return true;
	}
	return true;
}

bool	XAlignmentLargeArea::ExecuteStartByInspection(void)
{
	for(AlignmentLargeShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
		d->CalcDone=false;
	}
	return true;
}

bool	XAlignmentLargeArea::ReqOtherAlignmentLarge(void)
{
	int	page=ParentInLayer->GetPage();
	int	CurrentGlobalPage	=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(page);
	for(int globalpage=0;globalpage<ParentInLayer->GetLayersBase()->GetGlobalPageNumb();globalpage++){
		SlaveCommReqAlignmentLargeShift	RCmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckAlignmentLargeShift	ACmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.Layer=ParentInLayer->GetLayer();
		for(AlignmentLargeShiftList *a=OtherPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GlobalPage==globalpage){
				if(a->CalcDone==false){
					RCmd.ItemID.Add(a->ItemID);
				}
			}
		}
		if(RCmd.Send(globalpage,0,ACmd)==true){
			for(AlignmentLargeShiftList *s=ACmd.ShiftData.GetFirst();s!=NULL;s=s->GetNext()){
				for(AlignmentLargeShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
					if(d->GlobalPage==s->GlobalPage && d->ItemID==s->ItemID){
						d->CalcDone	=s->CalcDone;
						d->ShiftX	=s->ShiftX;
						d->ShiftY	=s->ShiftY;
						d->MasterX	=s->MasterX;
						d->MasterY	=s->MasterY;
					}
				}
			}
		}
	}
	for(AlignmentLargeShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->CalcDone==false){
			return false;
		}
	}
	return true;
}

bool    XAlignmentLargeArea::Save(QIODevice *file)
{
	WORD	Ver=7;

    if(file->write((const char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(::Save(file,LibID)==false)
		return false;

	if(file->write((const char *)&AreaID,sizeof(AreaID))!=sizeof(AreaID))
		return(false);
	int32	D=(int32)Priority;	//後方互換性のためint32
	if(file->write((const char *)&D,sizeof(D))!=sizeof(D))
		return(false);
	if(Area	.Write(file)==false)
		return(false);
	if(::Save(file,AreaName)==false)
		return false;

	int32	Numb=GPack.GetNumber();
	if(file->write((const char *)&Numb,sizeof(Numb))!=sizeof(Numb))
		return(false);
	for(XAlignmentLargePointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->Save(file)==false)
			return(false);
	}
	if(LimitedLib.Save(file)==false)
		return false;
	if(::Save(file,PartsID)==false)
		return false;
	if(::Save(file,PartsAllocID)==false)
		return false;
	if(::Save(file,Locked)==false)
		return false;
	if(::Save(file,PartsAreaID)==false)
		return false;
	if(::Save(file,MasterNo)==false)
		return false;
	return true;
}
bool	XAlignmentLargeArea::Load(QIODevice *file ,AlignmentLargeInLayer *parent)
{
	WORD	Ver;

    if(file->read((char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(Ver>=6){
		if(::Load(file,LibID)==false)
			return false;
	}
	if(file->read((char *)&AreaID,sizeof(AreaID))!=sizeof(AreaID))
		return(false);
	int32	D;
	if(file->read((char *)&D,sizeof(D))!=sizeof(D))
		return(false);
	if(D==0){
		Priority=_PriorityMiddle;
	}
	else{
		Priority=(_EnumPriority)D;
	}

	if(Area	.Read(file)==false)
		return(false);
	if(::Load(file,AreaName)==false)
		return false;

	int32	Numb;
    if(file->read((char *)&Numb	,sizeof(Numb))!=sizeof(Numb))
		return(false);
	GPack.RemoveAll();
	for(int i=0;i<Numb;i++){
		XAlignmentLargePointer *g=new XAlignmentLargePointer();
		if(g->Load(file,this)==false)
			return(false);
		if(g->Point!=NULL){
			g->Point->AreaID=AreaID;
		}
		GPack.AppendList(g);
	}
	if(LimitedLib.Load(file)==false)
		return false;
	if(Ver>=3){
		if(::Load(file,PartsID)==false)
			return false;
		if(::Load(file,PartsAllocID)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(file,Locked)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(file,PartsAreaID)==false)
			return false;
	}
	if(Ver>=7){
		if(::Load(file,MasterNo)==false)
			return false;
	}
	ParentInLayer=parent;
	return(true);
}
bool    XAlignmentLargeArea::SaveUnique(QIODevice *file)
{
	int32	D=(int32)Priority;	//後方互換性のためint32
	if(file->write((const char *)&D,sizeof(D))!=sizeof(D))
		return(false);
	if(::Save(file,AreaName)==false)
		return false;
	if(LimitedLib.Save(file)==false)
		return false;
	return(true);
}
bool    XAlignmentLargeArea::LoadUnique(QIODevice *file)
{
	int32	D;
	if(file->read((char *)&D,sizeof(D))!=sizeof(D))
		return(false);
	Priority=(_EnumPriority)D;
	if(::Load(file,AreaName)==false)
		return false;
	if(LimitedLib.Load(file)==false)
		return false;
	return(true);
}
bool    XAlignmentLargeArea::Transform(TransformBase &Param)
{
	FlexArea	tArea=Area.Transform(Param);
	Area=tArea;
	return true;
}
void	XAlignmentLargeArea::GetMultiSelectOrign(int &cx ,int &cy)
{
	cx=Area.GetMinX();
	cy=Area.GetMinY();
}

#define	mul2Add(x,y)	((x)*(x)+(y)*(y))

TriangleArea	*XAlignmentLargeArea::GetNearestTriangle(int x ,int y)
{
	TriangleArea *Index=NULL;
	double		MinD=999999999999.0;
	for(TriangleArea *a=TriangleContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Effective==true){
			//double	Cx, Cy;
			//a->GetCenter(Cx, Cy);
			//double	Len=hypot(x-Cx,y-Cy);
			if(a->Pa!=NULL && a->Pb!=NULL && a->Pc!=NULL){
				double	Len=0;
				Len =mul2Add(x-a->Cax,y-a->Cay)
					+mul2Add(x-a->Cbx,y-a->Cby)
					+mul2Add(x-a->Ccx,y-a->Ccy);

				if(MinD>Len){
					MinD=Len;
					Index=a;
				}
			}
			/*
			double	Len=hypot(x-a->TotalCx,y-a->TotalCy);
			if(MinD>Len){
				MinD=Len;
				Index=a;
			}
			*/
		}
	}
	return Index;
}
TriangleArea	*XAlignmentLargeArea::GetNearestTriangleInTable(int x ,int y)
{
	if(NearestTriangleTableDim==NULL){
		return GetNearestTriangle(x,y);
	}
	int	nx=x/NearestTriangleTableXRes;
	int	ny=y/NearestTriangleTableYRes;
	if(0<=nx && nx<NearestTriangleTableXNumb
	&& 0<=ny && ny<NearestTriangleTableYNumb){
		return NearestTriangleTableDim[ny*NearestTriangleTableXNumb+nx];
	}
	return NULL;
}

void	XAlignmentLargeArea::MatchCombination(ImageBuffer &TargetData,ImageBuffer &TRTargetData)
{
	for(int i=0;i<GPackClassNumb;i++){
		XAlignmentLargePointer	*a=GPackClass[i].GetFirst();
		if(a!=NULL && a->Point->GroupNumber>0 && a->Point->Combination==true){
			MatchCombination(GPackClass[i],TargetData ,TRTargetData);
		}
	}
}

int	FuncShiftList(const void *a ,const void *b);

void	XAlignmentLargeArea::MatchCombination(XAlignmentLargePointerContainer &Combinations,ImageBuffer &TargetData ,ImageBuffer &TRTargetData)
{
	int	MovDotX=99999999;
	int	MovDotY=99999999;
	for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
		const	AlignmentLargeThreshold	*RThr=a->Point->GetThresholdR(ParentInLayer->GetLayersBase());
		MovDotX=min(MovDotX,RThr->MoveDotX);
		MovDotY=min(MovDotY,RThr->MoveDotY);
	}
	int	OutlineWidth	=((AlignmentLargeBase *)ParentInLayer->GetParentBase())->DefaultOutlineWidth;

	struct	AlignmentLargeShiftItemListStruct	*SList=new struct	AlignmentLargeShiftItemListStruct[(MovDotX/2+1)*(MovDotY/2+1)];
	int	N=0;
	for(int dx=-MovDotX;dx<=MovDotX;dx+=4){
		for(int dy=-MovDotY;dy<=MovDotY;dy+=4){
			SList[N].Dx=dx;
			SList[N].Dy=dy;
			SList[N].Item=NULL;
			N++;
		}
	}

	//#pragma omp parallel                             
	//{                                                
	//	#pragma omp for
		for(int i=0;i<N;i++){
			double	MaxD=0;
			for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
				int	mx,my;
				a->Point->GetGlobalShift(mx,my);
				MaxD+=a->Point->MatchCross(TargetData ,TRTargetData ,mx+SList[i].Dx,my+SList[i].Dy);
			}
			SList[i].Match=MaxD;
		}
	//}
	QSort(SList,N,sizeof(SList[0]),FuncShiftList);

	int	NN=N/16;
	while(NN<100){
		NN++;
		NN*=2;
	}
	if(NN>=N){
		NN=N;
	}
	if(NN>100)
		NN=100;
	struct	AlignmentLargeShiftItemListStruct	SortedList[100];
	
	for(int i=0;i<NN;i++){
		double	MaxD=0;
		int		MaxDx=0;
		int		MaxDy=0;

		for(int x=-4;x<=4;x+=2){
			for(int y=-4;y<=4;y+=2){
				double	MaxMatch=0;
				for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
					int	mx,my;
					a->Point->GetGlobalShift(mx,my);
					MaxMatch+=a->Point->MatchCross(TargetData,TRTargetData,SList[i].Dx+mx+x,SList[i].Dy+my+y);
				}
				if(MaxD<MaxMatch){
					MaxD=MaxMatch;
					MaxDx=SList[i].Dx+x;
					MaxDy=SList[i].Dy+y;
				}
			}
		}
		SortedList[i].Dx=MaxDx;
		SortedList[i].Dy=MaxDy;
		SortedList[i].Match=MaxD;
	}
	delete	[]SList;
	QSort(SortedList,NN,sizeof(SortedList[0]),FuncShiftList);


	int	MinDiffBrightness=((AlignmentLargeBase *)ParentInLayer->GetParentBase())->MinDiffBrightness;
	int	CountOfBestMatch=0;
	struct	AlignmentLargeShiftItemListStruct	BestMatch[3];
	for(int i=0;i<NN;i++){
		int	j;
		for(j=0;j<CountOfBestMatch;j++){
			if(BestMatch[j].Dx==SortedList[i].Dx && BestMatch[j].Dy==SortedList[i].Dy){
				break;
			}
			for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
				int	Cx,Cy;
				GetCenter(Cx,Cy);
				int	hx=Cx+SortedList[i].Dx - BestMatch[j].Dx;
				int	hy=Cy+SortedList[i].Dy - BestMatch[j].Dy;
				if(a->Point->GetArea().IsInclude(hx,hy)==true){
					goto	PBreak;
				}
			}
		}
		PBreak:;
		if(j>=CountOfBestMatch){
			bool	OK=true;
			for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
				int	mx,my;
				a->Point->GetGlobalShift(mx,my);
				if(a->Point->GetDifferenceTransArea(TargetData,mx+SortedList[i].Dx,my+SortedList[i].Dy)<MinDiffBrightness){
					OK=false;
					break;
				}
			}
			if(OK==true){
				BestMatch[CountOfBestMatch].Dx	=SortedList[i].Dx;
				BestMatch[CountOfBestMatch].Dy	=SortedList[i].Dy;
				BestMatch[CountOfBestMatch].Match=SortedList[i].Match;
				BestMatch[CountOfBestMatch].Adopted=false;
				CountOfBestMatch++;
				if(CountOfBestMatch>=3){
					break;
				}
			}
		}
	}


	for(int K=0;K<CountOfBestMatch;K++){
		int		MaxDx=BestMatch[K].Dx;
		int		MaxDy=BestMatch[K].Dy;
		double	hMaxD=0;
		int		hMaxDX;
		int		hMaxDY;
		for(int y=-OutlineWidth;y<=OutlineWidth;y+=2){
			for(int x=-OutlineWidth;x<=OutlineWidth;x+=2){
				double	d=0;
				for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
					int	mx,my;
					a->Point->GetGlobalShift(mx,my);
					d+=a->Point->CalcTransAreaCalcCoeff(MaxDx+mx+x,MaxDy+my+y	,TargetData);
				}
				if(d>=hMaxD){
					hMaxD=d;
					hMaxDX=x;
					hMaxDY=y;
				}
			}
		}
		double	qMaxD=0;
		int		qMaxDX;
		int		qMaxDY;
		for(int y=-1;y<=1;y++){
			for(int x=-1;x<=1;x++){
				double	d=0;
				for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
					int	mx,my;
					a->Point->GetGlobalShift(mx,my);
					d+=a->Point->CalcTransAreaCalcCoeff(MaxDx+hMaxDX+mx+x,MaxDy+hMaxDY+my+y	,TargetData);
				}
				if(d>=hMaxD){
					qMaxD=d;
					qMaxDX=x;
					qMaxDY=y;
					}
			}
		}
		BestMatch[K].Dx =MaxDx+hMaxDX+qMaxDX;
		BestMatch[K].Dy =MaxDy+hMaxDY+qMaxDY;
		BestMatch[K].Match=qMaxD;
	}

	for(XAlignmentLargePointer *a=Combinations.GetFirst();a!=NULL;a=a->GetNext()){
		int	mx,my;
		a->Point->GetGlobalShift(mx,my);
		a->Point->CountOfBestMatch=CountOfBestMatch;
		for(int K=0;K<a->Point->CountOfBestMatch;K++){
			a->Point->BestMatch[K].Dx		=BestMatch[K].Dx+mx;
			a->Point->BestMatch[K].Dy		=BestMatch[K].Dy+my;
			a->Point->BestMatch[K].Match	=BestMatch[K].Match;
			a->Point->BestMatch[K].Item	=a->Point;
			a->Point->BestMatch[K].Adopted=false;
		}
		a->Point->CurrentResultDx=BestMatch[0].Dx+mx;
		a->Point->CurrentResultDy=BestMatch[0].Dy+my;
		a->Point->LastResultDx=a->Point->CurrentResultDx;
		a->Point->LastResultDy=a->Point->CurrentResultDy;
		a->Point->SetProcessDone(true);
	}

}

bool	XAlignmentLargeArea::FindClosedPoint(BYTE **BmpMap ,int XLen ,int YLen
											,int Cx, int Cy
											,int &RetX ,int &RetY)
{
	double	s2=sqrt(2.0);
	for(int L=0;L<max(XLen,YLen);L++){
		double	r=L*s2/2.0;
		int		ir=(int)r;
		for(int dx=0;dx<=ir;dx++){
			int dy=sqrt((double)(r*r-dx*dx));
			int	X1=Cx+dx;
			int	Y1=Cy+dy;
			if(0<=X1 && X1<XLen && 0<=Y1 && Y1<YLen){
				if(GetBmpBit(BmpMap,X1,Y1)!=0){
					RetX=X1;
					RetY=Y1;
					return true;
				}
			}
			int	X2=Cx+dx;
			int	Y2=Cy-dy;
			if(0<=X2 && X2<XLen && 0<=Y2 && Y2<YLen){
				if(GetBmpBit(BmpMap,X2,Y2)!=0){
					RetX=X2;
					RetY=Y2;
					return true;
				}
			}
			int	X3=Cx-dx;
			int	Y3=Cy+dy;
			if(0<=X3 && X3<XLen && 0<=Y3 && Y3<YLen){
				if(GetBmpBit(BmpMap,X3,Y3)!=0){
					RetX=X3;
					RetY=Y3;
					return true;
				}
			}
			int	X4=Cx-dx;
			int	Y4=Cy-dy;
			if(0<=X4 && X4<XLen && 0<=Y4 && Y4<YLen){
				if(GetBmpBit(BmpMap,X4,Y4)!=0){
					RetX=X4;
					RetY=Y4;
					return true;
				}
			}
		}
		for(int dy=0;dy<ir;dy++){
			int dx=sqrt((double)(r*r-dy*dy));
			int	X1=Cx+dx;
			int	Y1=Cy+dy;
			if(0<=X1 && X1<XLen && 0<=Y1 && Y1<YLen){
				if(GetBmpBit(BmpMap,X1,Y1)!=0){
					RetX=X1;
					RetY=Y1;
					return true;
				}
			}
			int	X2=Cx+dx;
			int	Y2=Cy-dy;
			if(0<=X2 && X2<XLen && 0<=Y2 && Y2<YLen){
				if(GetBmpBit(BmpMap,X2,Y2)!=0){
					RetX=X2;
					RetY=Y2;
					return true;
				}
			}
			int	X3=Cx-dx;
			int	Y3=Cy+dy;
			if(0<=X3 && X3<XLen && 0<=Y3 && Y3<YLen){
				if(GetBmpBit(BmpMap,X3,Y3)!=0){
					RetX=X3;
					RetY=Y3;
					return true;
				}
			}
			int	X4=Cx-dx;
			int	Y4=Cy-dy;
			if(0<=X4 && X4<XLen && 0<=Y4 && Y4<YLen){
				if(GetBmpBit(BmpMap,X4,Y4)!=0){
					RetX=X4;
					RetY=Y4;
					return true;
				}
			}
		}
	}
	return false;
}

void	XAlignmentLargeArea::AutoCreatePointInEdge(int AlignmntPointSize
											,int AlignmntSearchAreaDotX	,int AlignmntSearchAreaDotY	
											,int AlignmntSearchAreaDot2X,int AlignmntSearchAreaDot2Y
											,int LimitedLibType ,int LimitedLibID
											,bool AlignmntJudgeWithBrDif)
{
	LimitedLib.RemoveAll();
	if(LimitedLibType>0 && LimitedLibID>0){
		AlgorithmBase	*ALib=ParentInLayer->GetLayersBase()->GetAlgorithmBase(LimitedLibType);
		if(ALib!=NULL){
			AlgorithmLibraryLevelContainer ALibDest(ALib);
			ALib->GetLibraryContainer()->GetLibrary(LimitedLibID ,ALibDest);
			LimitedLib.Add(LimitedLibType,ALibDest);
		}
	}

	int	XLen=ParentInLayer->GetDotPerLine();
	int	YLen=ParentInLayer->GetMaxLines();

	ConstMapBuffer MaskMap;
	AlgorithmLibrary *Lib=NULL;
	ParentInLayer->GetReflectionMap(_Reflection_Mask,MaskMap,Lib);

	PureFlexAreaListContainer FPack;
	::PickupFlexArea(MaskMap.GetBitMap(),MaskMap.GetXByte(),MaskMap.GetXLen(),MaskMap.GetYLen(),FPack);
	if(FPack.GetCount()==0)
		return;

	PureFlexAreaList	*MaxF=NULL;
	int	MaxAreaDots=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		int	d=f->GetPatternByte();
		if(d>MaxAreaDots){
			MaxAreaDots=d;
			MaxF=f;
		}
	}
	int		XByte	=(XLen+7)/8;
	BYTE	**BmpMap=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear	(BmpMap ,0 ,XByte,YLen);
	if(MaxF!=NULL){
		MaxF->MakeBitData(BmpMap ,0,0 ,XLen,YLen);
	}

	int	MinX=Area.GetMinX();
	int	MaxX=Area.GetMaxX();
	int	MinY=Area.GetMinY();
	int	MaxY=Area.GetMaxY();
	int RetX ,RetY;
	{
		if(FindClosedPoint(BmpMap ,XLen ,YLen
									,MinX, MinY
									,RetX ,RetY)==true){
			FlexArea	RectArea;
			int	tRetX=RetX;
			int	tRetY=RetY;
			if(SearchAroundCorner(AlignmntPointSize ,max(AlignmntSearchAreaDotX,AlignmntSearchAreaDotY)
					,RetX,RetY
					,false,false,false,true
					,tRetX ,tRetY)==true){
				RetX=tRetX;
				RetY=tRetY;
			}
			RectArea.SetRectangle(RetX-AlignmntPointSize/2,RetY-AlignmntPointSize/2,RetX+AlignmntPointSize/2,RetY+AlignmntPointSize/2);
			XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(ParentInLayer->CreateItem(0));
			AlignmentLargeThreshold	*Thr=Item->GetThresholdW();
			Item->AreaID		=AreaID;
			Thr->MoveDotX		=AlignmntSearchAreaDotX;
			Thr->MoveDotY		=AlignmntSearchAreaDotY;
			Thr->MoveDotX2		=AlignmntSearchAreaDot2X;
			Thr->MoveDotY2		=AlignmntSearchAreaDot2Y;
			Thr->SearchAround	=0;
			Thr->JudgeWithBrDif	=AlignmntJudgeWithBrDif;
			Item->GroupNumber	=0;
			Thr->UsageGlobal	=0;
			Item->SetArea(RectArea);
			Item->SetManualCreated(false);
			ParentInLayer->AppendItem(Item);
		}
	}
	{
		if(FindClosedPoint(BmpMap ,XLen ,YLen
									,MaxX, MinY
									,RetX ,RetY)==true){
			FlexArea	RectArea;
			int	tRetX=RetX;
			int	tRetY=RetY;
			if(SearchAroundCorner(AlignmntPointSize ,max(AlignmntSearchAreaDotX,AlignmntSearchAreaDotY)
					,RetX,RetY
					,false,true,false,false
					,tRetX ,tRetY)==true){
				RetX=tRetX;
				RetY=tRetY;
			}
			RectArea.SetRectangle(RetX-AlignmntPointSize/2,RetY-AlignmntPointSize/2,RetX+AlignmntPointSize/2,RetY+AlignmntPointSize/2);
			XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(ParentInLayer->CreateItem(0));
			AlignmentLargeThreshold	*Thr=Item->GetThresholdW();
			Item->AreaID		=AreaID;
			Thr->MoveDotX		=AlignmntSearchAreaDotX;
			Thr->MoveDotY		=AlignmntSearchAreaDotY;
			Thr->MoveDotX2		=AlignmntSearchAreaDot2X;
			Thr->MoveDotY2		=AlignmntSearchAreaDot2Y;
			Thr->SearchAround	=0;
			Item->GroupNumber	=0;
			Thr->UsageGlobal	=0;
			Thr->JudgeWithBrDif	=AlignmntJudgeWithBrDif;
			Item->SetArea(RectArea);
			Item->SetManualCreated(false);
			ParentInLayer->AppendItem(Item);
		}
	}
	{
		if(FindClosedPoint(BmpMap ,XLen ,YLen
									,MinX, MaxY
									,RetX ,RetY)==true){
			FlexArea	RectArea;
			int	tRetX=RetX;
			int	tRetY=RetY;
			if(SearchAroundCorner(AlignmntPointSize ,max(AlignmntSearchAreaDotX,AlignmntSearchAreaDotY)
					,RetX,RetY
					,false,false,true,false
					,tRetX ,tRetY)==true){
				RetX=tRetX;
				RetY=tRetY;
			}
			RectArea.SetRectangle(RetX-AlignmntPointSize/2,RetY-AlignmntPointSize/2,RetX+AlignmntPointSize/2,RetY+AlignmntPointSize/2);
			XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(ParentInLayer->CreateItem(0));
			AlignmentLargeThreshold	*Thr=Item->GetThresholdW();
			Item->AreaID		=AreaID;
			Thr->MoveDotX		=AlignmntSearchAreaDotX;
			Thr->MoveDotY		=AlignmntSearchAreaDotY;
			Thr->MoveDotX2		=AlignmntSearchAreaDot2X;
			Thr->MoveDotY2		=AlignmntSearchAreaDot2Y;
			Thr->SearchAround	=0;
			Item->GroupNumber	=0;
			Thr->UsageGlobal	=0;
			Thr->JudgeWithBrDif	=AlignmntJudgeWithBrDif;
			Item->SetArea(RectArea);
			Item->SetManualCreated(false);
			ParentInLayer->AppendItem(Item);
		}
	}
	{
		if(FindClosedPoint(BmpMap ,XLen ,YLen
									,MaxX, MaxY
									,RetX ,RetY)==true){
			FlexArea	RectArea;
			int	tRetX=RetX;
			int	tRetY=RetY;
			if(SearchAroundCorner(AlignmntPointSize ,max(AlignmntSearchAreaDotX,AlignmntSearchAreaDotY)
					,RetX,RetY
					,true,false,false,false
					,tRetX ,tRetY)==true){
				RetX=tRetX;
				RetY=tRetY;
			}
			RectArea.SetRectangle(RetX-AlignmntPointSize/2,RetY-AlignmntPointSize/2,RetX+AlignmntPointSize/2,RetY+AlignmntPointSize/2);
			XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(ParentInLayer->CreateItem(0));
			AlignmentLargeThreshold	*Thr=Item->GetThresholdW();
			Item->AreaID		=AreaID;
			Thr->MoveDotX		=AlignmntSearchAreaDotX;
			Thr->MoveDotY		=AlignmntSearchAreaDotY;
			Thr->MoveDotX2		=AlignmntSearchAreaDot2X;
			Thr->MoveDotY2		=AlignmntSearchAreaDot2Y;
			Thr->SearchAround	=0;
			Item->GroupNumber	=0;
			Thr->UsageGlobal	=0;
			Thr->JudgeWithBrDif	=AlignmntJudgeWithBrDif;
			Item->SetArea(RectArea);
			Item->SetManualCreated(false);
			ParentInLayer->AppendItem(Item);
		}
	}
	DeleteMatrixBuff(BmpMap,YLen);

}

struct RectAdoption
{
	int	xn,yn;
	double	Value;
};

int	SortRDim(const void *a ,const void *b)
{
	struct RectAdoption	*pa=(struct RectAdoption *)a;
	struct RectAdoption	*pb=(struct RectAdoption *)b;
	if(pa->Value<pb->Value)
		return 1;
	if(pa->Value>pb->Value)
		return -1;
	return 0;
}

void	XAlignmentLargeArea::AutoCreatePointInInside(int AlignmntPointSize
											,int AlignmntSearchAreaDotX	,int AlignmntSearchAreaDotY	
											,int AlignmntSearchAreaDot2X,int AlignmntSearchAreaDot2Y
											,int LimitedLibType ,int LimitedLibID
											,bool AlignmntJudgeWithBrDif)
{
	LimitedLib.RemoveAll();
	if(LimitedLibType>0 && LimitedLibID>0){
		AlgorithmBase	*ALib=ParentInLayer->GetLayersBase()->GetAlgorithmBase(LimitedLibType);
		if(ALib!=NULL){
			AlgorithmLibraryLevelContainer ALibDest(ALib);
			ALib->GetLibraryContainer()->GetLibrary(LimitedLibID ,ALibDest);
			LimitedLib.Add(LimitedLibType,ALibDest);
		}
	}

	int	XLen=ParentInLayer->GetDotPerLine();
	int	YLen=ParentInLayer->GetMaxLines();

	ConstMapBuffer MaskMap;
	AlgorithmLibrary *Lib=NULL;
	ParentInLayer->GetReflectionMap(_Reflection_Mask,MaskMap,Lib);

	PureFlexAreaListContainer FPack;
	::PickupFlexArea(MaskMap.GetBitMap(),MaskMap.GetXByte(),MaskMap.GetXLen(),MaskMap.GetYLen(),FPack);
	if(FPack.GetCount()==0)
		return;

	PureFlexAreaList	*MaxF=NULL;
	int	MaxAreaDots=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		int	d=f->GetPatternByte();
		if(d>MaxAreaDots){
			MaxAreaDots=d;
			MaxF=f;
		}
	}
	int		XByte	=(XLen+7)/8;
	BYTE	**BmpMap=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear	(BmpMap ,0 ,XByte,YLen);
	if(MaxF!=NULL){
		MaxF->MakeBitData(BmpMap ,0,0 ,XLen,YLen);
	}

	int	MinX=Area.GetMinX();
	int	MaxX=Area.GetMaxX();
	int	MinY=Area.GetMinY();
	int	MaxY=Area.GetMaxY();

	int	XNumb=(MaxX-MinX)/AlignmntPointSize;
	int	YNumb=(MaxY-MinY)/AlignmntPointSize;
	DataInLayer	*Ly=ParentInLayer->GetDataInLayer();

	struct RectAdoption	*RDim=new struct RectAdoption[XNumb*YNumb/8];
	int		iAreaID=AreaID;
	AlignmentLargeInLayer	*iParentInLayer=ParentInLayer;
	auto	f=[MinX,MinY,MaxX,MaxY,RDim,AlignmntPointSize,MaxF,Ly
				,iParentInLayer
				,AlignmntSearchAreaDotX,AlignmntSearchAreaDotY
				,AlignmntSearchAreaDot2X,AlignmntSearchAreaDot2Y,iAreaID
				,AlignmntJudgeWithBrDif]
				(int StartXn,int StartYn,int EndXn,int EndYn){
		int	RDimNumb=0;
		for(int yn=StartYn;yn<EndYn;yn++){
			for(int xn=StartXn;xn<EndXn;xn++){
				FlexArea	A;
				A.SetRectangle(	 MinX+AlignmntPointSize*xn,MinY+AlignmntPointSize*yn
								,MinX+AlignmntPointSize*(xn+1),MinY+AlignmntPointSize*(yn+1));
				if(MaxF->IsInclude(&A)==true){
					FlexArea	A11;
					A11.SetRectangle(MinX+AlignmntPointSize*xn						,MinY+AlignmntPointSize*yn
									,MinX+AlignmntPointSize*xn+AlignmntPointSize/3	,MinY+AlignmntPointSize*yn+AlignmntPointSize/3);
					FlexArea	A21;
					A21.SetRectangle(MinX+AlignmntPointSize*xn+2*AlignmntPointSize/3,MinY+AlignmntPointSize*yn
									,MinX+AlignmntPointSize*xn+AlignmntPointSize	,MinY+AlignmntPointSize*yn+AlignmntPointSize/3);
					FlexArea	A12;
					A12.SetRectangle(MinX+AlignmntPointSize*xn						,MinY+AlignmntPointSize*yn+2*AlignmntPointSize/3
									,MinX+AlignmntPointSize*xn+AlignmntPointSize/3	,MinY+AlignmntPointSize*yn+AlignmntPointSize);
					FlexArea	A22;
					A22.SetRectangle(MinX+AlignmntPointSize*xn+2*AlignmntPointSize/3,MinY+AlignmntPointSize*yn+2*AlignmntPointSize/3
									,MinX+AlignmntPointSize*xn+AlignmntPointSize	,MinY+AlignmntPointSize*yn+AlignmntPointSize);
					double DAvr;
					double	V=A.GetVar(0 ,0 ,Ly->GetMasterBuff() ,DAvr);
					double DAvr11;
					double	V11=A11.GetVar(0 ,0 ,Ly->GetMasterBuff() ,DAvr11);
					double DAvr21;
					double	V21=A21.GetVar(0 ,0 ,Ly->GetMasterBuff() ,DAvr21);
					double DAvr12;
					double	V12=A12.GetVar(0 ,0 ,Ly->GetMasterBuff() ,DAvr12);
					double DAvr22;
					double	V22=A22.GetVar(0 ,0 ,Ly->GetMasterBuff() ,DAvr22);
					double	MaxAvr=max(max(DAvr11,DAvr21),max(DAvr12,DAvr22));
					double	MinAvr=min(min(DAvr11,DAvr21),min(DAvr12,DAvr22));
					double	DifAvr=MaxAvr-MinAvr;
					if(DifAvr>=10){
						double	L=V*DifAvr/(V11+V21+V12+V22+1.0);
						RDim[RDimNumb].xn=xn;
						RDim[RDimNumb].yn=yn;
						RDim[RDimNumb].Value=L;
						RDimNumb++;
					}
				}
			}
		}
		QSort(RDim,RDimNumb,sizeof(RDim[0]),SortRDim);
		for(int i=0;i<RDimNumb && i<20;i++){
			FlexArea	RectArea;
			RectArea.SetRectangle(MinX+AlignmntPointSize*RDim[i].xn		,MinY+AlignmntPointSize*RDim[i].yn
								, MinX+AlignmntPointSize*(RDim[i].xn+1)	,MinY+AlignmntPointSize*(RDim[i].yn+1));
			XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(iParentInLayer->CreateItem(0));
			AlignmentLargeThreshold	*Thr=Item->GetThresholdW();
			Item->AreaID		=iAreaID;
			Thr->MoveDotX		=AlignmntSearchAreaDotX;
			Thr->MoveDotY		=AlignmntSearchAreaDotY;
			Thr->MoveDotX2		=AlignmntSearchAreaDot2X;
			Thr->MoveDotY2		=AlignmntSearchAreaDot2Y;
			Thr->SearchAround	=0;
			Item->GroupNumber	=0;
			Thr->UsageGlobal	=0;
			Thr->JudgeWithBrDif	=AlignmntJudgeWithBrDif;
			Item->SetArea(RectArea);
			Item->SetManualCreated(false);
			iParentInLayer->AppendItem(Item);
			Item->MakeArea(Ly->GetMasterBuff());
			int		HLineCount ,VLineCount;
			Item->GetHVCount(HLineCount ,VLineCount);
			if(HLineCount<=1 || VLineCount<=1){
				iParentInLayer->RemoveItem(Item);
				delete	Item;
			}
			else{
				break;
			}
		}
	};
	f(0			,0			,XNumb/3,YNumb/3);
	f(2*XNumb/3	,0			,XNumb	,YNumb/3);
	f(0			,2*YNumb/3	,XNumb/3,YNumb);
	f(2*XNumb/3	,2*YNumb/3	,XNumb	,YNumb);

	delete	[]RDim;

	DeleteMatrixBuff(BmpMap,YLen);

}

bool	XAlignmentLargeArea::SearchAroundCorner(int AlignmntPointSize ,int AlignmntSearchAreaDot
					,int X,int Y
					,bool t1 ,bool t2 ,bool t3 ,bool t4
					,int &RetX ,int &RetY)
{
	for(int L=0;L<AlignmntSearchAreaDot;L++){
		int	dx;
		int	dy;
		dy=-L;
		for(dx=-L;dx<=L;dx++){
			if(CheckCorner(AlignmntPointSize,X+dx,Y+dy,t1,t2,t3,t4)==true){
				RetX=X+dx;
				RetY=Y+dy;
				return true;
			}
		}
		dx=L;
		for(dy=-L;dy<L;dy++){
			if(CheckCorner(AlignmntPointSize,X+dx,Y+dy,t1,t2,t3,t4)==true){
				RetX=X+dx;
				RetY=Y+dy;
				return true;
			}
		}
		dy=L;
		for(dx=L;dx>-L;dx--){
			if(CheckCorner(AlignmntPointSize,X+dx,Y+dy,t1,t2,t3,t4)==true){
				RetX=X+dx;
				RetY=Y+dy;
				return true;
			}
		}
		dx=-L;
		for(dy=L;dy>-L;dy--){
			if(CheckCorner(AlignmntPointSize,X+dx,Y+dy,t1,t2,t3,t4)==true){
				RetX=X+dx;
				RetY=Y+dy;
				return true;
			}
		}
	}
	return false;
}

bool	XAlignmentLargeArea::CheckCorner(int AlignmntPointSize
										,int X,int Y 
										,bool t1 ,bool t2 ,bool t3 ,bool t4)
{
	if(Area.IsInclude(X,Y)==false)
		return false;

	int	x1=X-AlignmntPointSize/2;
	int	y1=Y-AlignmntPointSize/2;
	int	x2=X+AlignmntPointSize/2;
	int	y2=Y+AlignmntPointSize/2;
	int	TestSize=AlignmntPointSize/4;
	bool	b1=Area.CheckOverlapRectangle(x1
										, y1
										, x1+TestSize
										, y1+TestSize);
	bool	b2=Area.CheckOverlapRectangle(x1
										, y2-TestSize
										, x1+TestSize
										, y2);
	bool	b3=Area.CheckOverlapRectangle(x2-TestSize
										, y1
										, x2
										, y1+TestSize);
	bool	b4=Area.CheckOverlapRectangle(x2-TestSize
										, y2-TestSize
										, x2
										, y2);
	if(b1==t1 && b2==t2 && b3==t3 && b4==t4)
		return true;
	return false;
}

void	XAlignmentLargeArea::MoveForAlignment(void)
{
	AlignmentPacket2D	V;
	int	cx,cy;
	GetCenter(cx,cy);
	V.PosXOnTarget=cx;
	V.PosYOnTarget=cy;
	V.ShiftX=0;
	V.ShiftY=0;
	ParentInLayer->GetAlignmentForProcessing(V);
	int	Mx=V.ShiftX;
	int	My=V.ShiftY;
	double	s=V.Rotation;

	Area.Rotate(-s*180.0/M_PI,cx,cy);
	Area.MoveToNoClip(Mx,My);
}