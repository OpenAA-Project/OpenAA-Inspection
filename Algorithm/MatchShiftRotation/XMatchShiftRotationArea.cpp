//#include "XMatchShiftRotationResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XMatchShiftRotation.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
//#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XMultiEquSolve.h"
#include "XCrossObj.h"
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include <stdlib.h>

extern	const	char	*sRoot;
extern	const	char	*sName;

//==========================================================================================

XMatchShiftRotationArea::XMatchShiftRotationArea(void)
{
    AreaID			=-1;
	LibID			=-1;
	ParentInPage	=NULL;
	PartsID			=-1;
	PartsAllocID	=-1;
	PartsAreaID		=-1;
	Locked			=false;
	Selected		=false;
	Active			=false;
	ManualCreated	=false;
	Visible			=true;
	Origin			=NULL;

	SearchDimPointer=NULL;
	SearchDimNumb	=0;
	SearchArea		=0;	
	SearchAngle		=0;
}

XMatchShiftRotationArea::XMatchShiftRotationArea(MatchShiftRotationInPage	*parentInPage)
{
	AreaID			=-1;
	LibID			=-1;
	ParentInPage	=parentInPage;
	PartsID			=-1;
	PartsAllocID	=-1;
	PartsAreaID		=-1;
	Locked			=false;
	Selected		=false;
	Active			=false;
	ManualCreated	=false;
	Visible			=true;
	Origin			=NULL;
	SearchDimPointer=NULL;
	SearchDimNumb	=0;
	SearchArea		=0;	
	SearchAngle		=0;
}
XMatchShiftRotationArea::~XMatchShiftRotationArea(void)
{
	if(ParentInPage!=NULL){
		for(AlgorithmItemPI *k= ParentInPage->GetFirstData();k!=NULL;){
			AlgorithmItemPI *NextK=k->GetNext();
			MatchShiftRotationItem	*item=dynamic_cast<MatchShiftRotationItem *>(k);
			if(item!=NULL){
				if(item->AreaID==AreaID){
					ParentInPage->RemoveItem(item);
					delete	item;
				}
			}
			k=NextK;
		}
	}
	if(SearchDimPointer!=NULL){
		delete	[]SearchDimPointer;
		SearchDimPointer=NULL;
		SearchDimNumb=0;
	}
}

MatchShiftRotationBase	*XMatchShiftRotationArea::GetParentBase(void)
{
	return (MatchShiftRotationBase *)ParentInPage->GetParentBase();
}

XMatchShiftRotationArea	&XMatchShiftRotationArea::operator=(XMatchShiftRotationArea &src)
{
	CopyWithoutItems(src,false);

	LibID			=src.LibID;
	ParentInPage	=src.ParentInPage;
	PartsID			=src.PartsID;
	PartsAllocID	=src.PartsAllocID;
	PartsAreaID		=src.PartsAreaID;
	Locked			=src.Locked;
	Selected		=src.Selected;
	Active			=src.Active;
	ManualCreated	=src.ManualCreated;
	Visible			=src.Visible;
	Origin			=src.Origin;
	SearchArea		=src.SearchArea		;	
	SearchAngle		=src.SearchAngle	;

	return(*this);
}

XMatchShiftRotationArea  &XMatchShiftRotationArea::CopyWithoutItems(XMatchShiftRotationArea &src,bool ReferedMode)
{
    AreaID		=src.AreaID;
	LibID		=src.LibID;

	if(ReferedMode==true)
		Area.SetRefereneFrom(&src.Area);
	else
		Area		=src.Area;

	Locked			=src.Locked;
	Selected		=src.Selected;
	Active			=src.Active;
	Visible			=src.Visible;
	ManualCreated	=src.ManualCreated;
	Origin			=src.Origin;
	SearchArea		=src.SearchArea		;	
	SearchAngle		=src.SearchAngle	;

	return(*this);
}

void    XMatchShiftRotationArea::MoveTo(int dx ,int dy)
{
	if(Locked==false){
		Area.MoveToNoClip(dx,dy);
	}
}

void	XMatchShiftRotationArea::DeleteAllItemsFromParent(void)
{
	for(AlgorithmItemPI *Item=ParentInPage->GetFirstData();Item!=NULL;){
		AlgorithmItemPI *NextItem=Item->GetNext();
		MatchShiftRotationItem	*AItem=dynamic_cast<MatchShiftRotationItem *>(Item);
		if(AItem!=NULL && AItem->AreaID==AreaID){
			ParentInPage->RemoveItem(AItem);
			delete	AItem;
		}
		Item=NextItem;
	}
}

int	XMatchShiftRotationArea::GetPage(void)
{
	return ParentInPage->GetPage();
}

void    XMatchShiftRotationArea::GetCenter(int &cx, int &cy)
{
	Area.GetCenter(cx,cy);
}
void	XMatchShiftRotationArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MatchShiftRotationBase	*pbase=dynamic_cast<MatchShiftRotationBase *>(ParentInPage->GetParentBase());
	if(pbase!=NULL){
		MatchShiftRotationDrawAttr	*LAttr=dynamic_cast<MatchShiftRotationDrawAttr *>(Attr);
		if((LAttr!=NULL) && ((LAttr->ModeDrawArea==true) || (LAttr->SelectedArea.GetCount()==0 || LAttr->SelectedArea.IsInclude(AreaID)==true))){
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
				QColor	C(Attr->NormalColor.red()*0.8
						, Attr->NormalColor.green()*0.8
						, Attr->NormalColor.blue()*0.8
						, Attr->NormalColor.alpha());
				Area.DrawAlpha(0,0 ,&pnt ,C.rgba()	,ZoomRate ,movx ,movy);
			}
		}
	}
}

void	XMatchShiftRotationArea::DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MatchShiftRotationBase	*pbase=dynamic_cast<MatchShiftRotationBase *>(ParentInPage->GetParentBase());
	if(pbase!=NULL){
		MatchShiftRotationDrawAttr	*LAttr=dynamic_cast<MatchShiftRotationDrawAttr *>(Attr);
		if(LAttr!=NULL){
			Attr->NormalColor=pbase->ColorPoint;
			Attr->NormalColor.setAlpha(pbase->AlphaLevel);
			Attr->SelectedColor	=pbase->ColorPointSelected;
			Attr->SelectedColor.setAlpha(pbase->AlphaLevel);
			Attr->ActiveColor	=pbase->ColorPointActive;
			Attr->ActiveColor.setAlpha(pbase->AlphaLevel);

			for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->GetItem()->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
		else{
			for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->GetItem()->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
}

void	XMatchShiftRotationArea::DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(Selected==true && Locked==false){
		Area.Draw(dx,dy ,&pnt ,Col.rgba(),ZoomRate ,movx ,movy);
	}
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

static	int		DbgIndexForGroupIDMVectorList=296;
static	int		DbgIndexForGroup;

bool	XMatchShiftRotationArea::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	MatchShiftRotationLibrary	*TmpLib=(MatchShiftRotationLibrary *)GetParentBase()->FindLibFromManagedCacheLib(LibID);
	if(TmpLib!=NULL && SearchArea==0 && SearchAngle==0){
		SearchArea	=TmpLib->SearchArea;
		SearchAngle	=TmpLib->SearchAngle;
	}

	int	W=Area.GetWidth();
	int	H=Area.GetHeight();
	int	D=hypot(W,H);

	StepAngle=2.0*atan(2.0/((double)D));
	AngleRange=SearchAngle*M_PI/180;

	RoughSepAngle	=StepAngle*GetParentBase()->RoughSeparationAngle;
	RoughStepMove	=GetParentBase()->RoughSeparationShift;
	RoughIsolation	=GetParentBase()->RoughSeparationIsolation;

	if(SearchDimPointer!=NULL){
		delete	[]SearchDimPointer;
	}
	SearchDimNumb=0;
	for(double da=-AngleRange;da<=AngleRange;da+=RoughSepAngle){
		for(int dy=-SearchArea;dy<=SearchArea;dy+=RoughStepMove){
			for(int dx=-SearchArea;dx<=SearchArea;dx+=RoughStepMove){
				SearchDimNumb++;
			}
		}
	}
	SearchDimPointer=new struct	SearchDim[SearchDimNumb];
	SearchDimNumb=0;
	for(double da=-AngleRange;da<=AngleRange;da+=RoughSepAngle){
		double	CosS=cos(da);
		double	SinS=sin(da);
		for(int dy=-SearchArea;dy<=SearchArea;dy+=RoughStepMove){
			for(int dx=-SearchArea;dx<=SearchArea;dx+=RoughStepMove){
				SearchDimPointer[SearchDimNumb].Angle=da;
				SearchDimPointer[SearchDimNumb].CosS=CosS;
				SearchDimPointer[SearchDimNumb].SinS=SinS;
				SearchDimPointer[SearchDimNumb].Dx=dx;
				SearchDimPointer[SearchDimNumb].Dy=dy;
				SearchDimNumb++;
			}
		}
	}

	return true;
}

static	int	AreaDbgX=9328;
static	int	AreaDbgY=6153;
static	int	AreaDbg=0;

bool	XMatchShiftRotationArea::ExecuteStartByInspection(void)
{
	return true;
}

int	SearchDimFunc(const void *a ,const void *b)
{
	struct	XMatchShiftRotationArea::SearchDim	*pa=(struct	XMatchShiftRotationArea::SearchDim *)a;
	struct	XMatchShiftRotationArea::SearchDim	*pb=(struct	XMatchShiftRotationArea::SearchDim *)b;
	if(pa->CalcD>pb->CalcD)
		return -1;
	if(pa->CalcD<pb->CalcD)
		return 1;
	return 0;
}

void	XMatchShiftRotationArea::ExecuteProcessingMakeCalc(AlgorithmItemPI* FirstData)
{
	int	Cx, Cy;
	Area.GetCenter(Cx, Cy);

	#pragma omp parallel                             
	{
		#pragma omp for
		for (int i = 0; i < SearchDimNumb; i++) {
			double	da = SearchDimPointer[i].Angle;
			double	CosS = SearchDimPointer[i].CosS;
			double	SinS = SearchDimPointer[i].SinS;
			int		dx = SearchDimPointer[i].Dx;
			int		dy = SearchDimPointer[i].Dy;

			double	TmpD = 0;
			for (AlgorithmItemPI* a = FirstData; a != NULL; a = a->GetNext()) {
				MatchShiftRotationItem* Item = dynamic_cast<MatchShiftRotationItem*>(a);
				if (Item->AreaID == AreaID) {
					int	ItemCx, ItemCy;
					Item->GetCenter(ItemCx, ItemCy);
					double	X = (ItemCx - Cx) * CosS + (ItemCy - Cy) * SinS + Cx;
					double	Y = -(ItemCx - Cx) * SinS + (ItemCy - Cy) * CosS + Cy;
					int	kx = X - ItemCx + dx;
					int	ky = Y - ItemCy + dy;
					double	m = Item->CalcRough(kx, ky, da, 2);
					TmpD += m * m;
				}
			}
			SearchDimPointer[i].CalcD = TmpD;
		}
	}
}
bool	XMatchShiftRotationArea::ExecuteProcessing(AlgorithmItemPI *FirstData)
{
	int	Cx,Cy;
	Area.GetCenter(Cx,Cy);


	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	double	MaxDa=0;

	ExecuteProcessingMakeCalc(FirstData);

	qsort(SearchDimPointer,SearchDimNumb,sizeof(struct	SearchDim),SearchDimFunc);

	int	NN=500;
	if(NN>SearchDimNumb)
		NN=SearchDimNumb/2;


	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<NN;i++){
			double	da	=SearchDimPointer[i].Angle;
			double	CosS=SearchDimPointer[i].CosS;
			double	SinS=SearchDimPointer[i].SinS;
			int		dx	=SearchDimPointer[i].Dx;
			int		dy	=SearchDimPointer[i].Dy;

			double	TmpD=0;
			for(AlgorithmItemPI *a=FirstData;a!=NULL;a=a->GetNext()){
				MatchShiftRotationItem	*Item=dynamic_cast<MatchShiftRotationItem	*>(a);
				if(Item->AreaID==AreaID){
					int	ItemCx,ItemCy;
					Item->GetCenter(ItemCx,ItemCy);
					double	X= (ItemCx-Cx)*CosS + (ItemCy-Cy)*SinS + Cx;
					double	Y=-(ItemCx-Cx)*SinS + (ItemCy-Cy)*CosS + Cy;
					int	kx=X-ItemCx+dx;
					int	ky=Y-ItemCy+dy;
					int	SearchedDx,SearchedDy;
					double	m=Item->Calc(kx,ky,da,SearchedDx,SearchedDy,2);
					TmpD+=m*m;
				}
			}
			#pragma omp critical
			{
				if(MaxD<TmpD){
					MaxD=TmpD;
					MaxDa=da;
					MaxDx=dx;
					MaxDy=dy;
				}
			}
		}
	}
	MaxD=0;
	int		RMaxDx=0;
	int		RMaxDy=0;
	double	RMaxDa=0;
	for(double ds=-RoughSepAngle;ds<=RoughSepAngle;ds+=StepAngle){
		double	da=MaxDa+ds;
		double	CosS=cos(da);
		double	SinS=sin(da);
		for(int dy=-RoughStepMove;dy<=RoughStepMove;dy++){
			for(int dx=-RoughStepMove;dx<=RoughStepMove;dx++){
				double	TmpD=0;

				for(AlgorithmItemPI *a=FirstData;a!=NULL;a=a->GetNext()){
					MatchShiftRotationItem	*Item=dynamic_cast<MatchShiftRotationItem	*>(a);
					if(Item->AreaID==AreaID){
						int	ItemCx,ItemCy;
						Item->GetCenter(ItemCx,ItemCy);
						double	X= (ItemCx-Cx)*CosS + (ItemCy-Cy)*SinS + Cx;
						double	Y=-(ItemCx-Cx)*SinS + (ItemCy-Cy)*CosS + Cy;
						int	kx=X-ItemCx+dx+MaxDx;
						int	ky=Y-ItemCy+dy+MaxDy;
						int	SearchedDx,SearchedDy;
						double	m=Item->Calc(kx,ky,da,SearchedDx,SearchedDy,1);
						TmpD+=m*m;
					}
				}
				if(MaxD<TmpD){
					MaxD=TmpD;
					RMaxDa=ds;
					RMaxDx=dx;
					RMaxDy=dy;
				}
			}
		}
	}
	ResultDx	=RMaxDx+MaxDx;
	ResultDy	=RMaxDy+MaxDy;
	ResultAngle	=RMaxDa+MaxDa;

	double	CosS=cos(ResultAngle);
	double	SinS=sin(ResultAngle);
	for(AlgorithmItemPI *a=FirstData;a!=NULL;a=a->GetNext()){
		MatchShiftRotationItem	*Item=dynamic_cast<MatchShiftRotationItem	*>(a);
		if(Item->AreaID==AreaID){
			int	ItemCx,ItemCy;
			Item->GetCenter(ItemCx,ItemCy);
			double	X= (ItemCx-Cx)*CosS + (ItemCy-Cy)*SinS + Cx;
			double	Y=-(ItemCx-Cx)*SinS + (ItemCy-Cy)*CosS + Cy;
			int	kx=X-ItemCx+ResultDx;
			int	ky=Y-ItemCy+ResultDy;
			int	SearchedDx,SearchedDy;
			double	m=Item->Calc(kx,ky,ResultAngle,SearchedDx,SearchedDy,1);
			Item->ResultLittleDx	=SearchedDx;
			Item->ResultLittleDy	=SearchedDy;
			Item->MatchingRate		=m;
		}
	}

	return true;
}

bool    XMatchShiftRotationArea::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,AreaID)==false)
		return(false);
	if(::Save(file,LibID)==false)
		return(false);

	if(Area	.Write(file)==false)
		return(false);
	if(::Save(file,AreaName)==false)
		return false;


	if(::Save(file,PartsID)==false)
		return false;
	if(::Save(file,PartsAllocID)==false)
		return false;
	if(::Save(file,Locked)==false)
		return false;
	if(::Save(file,PartsAreaID)==false)
		return false;
	if(::Save(file,SearchArea)==false)
		return false;
	if(::Save(file,SearchAngle)==false)
		return false;
	return true;
}
bool	XMatchShiftRotationArea::Load(QIODevice *file ,MatchShiftRotationInPage *parent)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;

	if(::Load(file,AreaID)==false)
		return(false);
	if(::Load(file,LibID)==false)
		return(false);

	if(Area	.Read(file)==false)
		return(false);
	if(::Load(file,AreaName)==false)
		return false;

	if(::Load(file,PartsID)==false)
		return false;
	if(::Load(file,PartsAllocID)==false)
		return false;

	if(::Load(file,Locked)==false)
		return false;

	if(::Load(file,PartsAreaID)==false)
			return false;
	if(Ver>=2){
		if(::Load(file,SearchArea)==false)
			return false;
		if(::Load(file,SearchAngle)==false)
			return false;
	}

	ParentInPage=parent;
	ParentInPage->FastSearchIDItemStart();
		
	return(true);
}
bool    XMatchShiftRotationArea::SaveUnique(QIODevice *file)
{
	if(::Save(file,AreaName)==false)
		return false;

	return(true);
}
bool    XMatchShiftRotationArea::LoadUnique(QIODevice *file)
{
	if(::Load(file,AreaName)==false)
		return false;

	return(true);
}


void	XMatchShiftRotationArea::DeleteSelectedItems(void)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;){
		AlgorithmItemPointerList *NextP=p->GetNext();
		AlgorithmItemRoot	*Item=p->GetItem();
		if(Item->GetSelected()==true && Item->GetEditLocked()==false){
			ItemPack.RemoveList(p);
			ParentInPage->RemoveItem(Item);
			delete	p;
			delete	Item;
		}
		p=NextP;
	}
}
void	XMatchShiftRotationArea::ExecuteMoveItem(int GlobalDx,int GlobalDy,bool AllItems)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		p->GetItem()->ExecuteMove(GlobalDx,GlobalDy, AllItems);
	}
}
