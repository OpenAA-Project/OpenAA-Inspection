//#include "XAlignmentFlexAreaResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentFlexArea.h"
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
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include "XPacketAlignmentFlexArea.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==========================================================================================

XAlignmentFlexAreaArea::XAlignmentFlexAreaArea(void)
{
	MaxSearchAreaFromItem=0;
    AreaID			=-1;
	Priority		=_PriorityMiddle;
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

	TestMap=NULL;
	MapXByte	=0;
	MapXLen		=0;
	MapYLen		=0;

    MVector		=NULL;
    MVectorXNumb=0;
    MVectorYNumb=0;
    MVectorXRes	=0;
    MVectorYRes	=0;
}
XAlignmentFlexAreaArea::XAlignmentFlexAreaArea(AlignmentFlexAreaInPage	*parentInPage)
{
	MaxSearchAreaFromItem=0;
	AreaID			=-1;
	Priority		=_PriorityMiddle;
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

	TestMap=NULL;
	MapXByte	=0;
	MapXLen		=0;
	MapYLen		=0;

    MVector		=NULL;
    MVectorXNumb=0;
    MVectorYNumb=0;
    MVectorXRes	=0;
    MVectorYRes	=0;
}
XAlignmentFlexAreaArea::~XAlignmentFlexAreaArea(void)
{
	if(TestMap!=NULL){
		DeleteMatrixBuff(TestMap,MapYLen);
	}
	TestMap=NULL;
	MapXByte	=0;
	MapXLen		=0;
	MapYLen		=0;

	if(ParentInPage!=NULL){
		if(ParentInPage->MVector!=NULL){
			for(int y=0;y<ParentInPage->MVectorYNumb;y++){
				for(int x=0;x<ParentInPage->MVectorXNumb;x++){
					if(ParentInPage->MVector[y*ParentInPage->MVectorXNumb+x].Global!=NULL
					&& ParentInPage->MVector[y*ParentInPage->MVectorXNumb+x].Global->AreaID==AreaID){
						ParentInPage->MVector[y*ParentInPage->MVectorXNumb+x].Global=NULL;
					}
					if(ParentInPage->MVector[y*ParentInPage->MVectorXNumb+x].Plain!=NULL
					&& ParentInPage->MVector[y*ParentInPage->MVectorXNumb+x].Plain->AreaID==AreaID){
						ParentInPage->MVector[y*ParentInPage->MVectorXNumb+x].Plain=NULL;
					}
				}
			}
		}
		for(AlgorithmItemPI *k= ParentInPage->GetFirstData();k!=NULL;){
			AlgorithmItemPI *NextK=k->GetNext();
			AlignmentFlexAreaItem	*item=dynamic_cast<AlignmentFlexAreaItem *>(k);
			if(item!=NULL){
				if(item->AreaID==AreaID){
					ParentInPage->RemoveItem(item);
					if(item->IsOriginParts()==true){
						delete	item;
					}
				}
			}
			k=NextK;
		}
	}
}

AlignmentFlexAreaBase	*XAlignmentFlexAreaArea::GetParentBase(void)
{
	return (AlignmentFlexAreaBase *)ParentInPage->GetParentBase();
}

XAlignmentFlexAreaArea	&XAlignmentFlexAreaArea::operator=(const XAlignmentFlexAreaArea &src)
{
	CopyWithoutItems(src,false);

	Priority		=src.Priority;
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

	if(TestMap!=NULL){
		DeleteMatrixBuff(TestMap,MapYLen);
	}
	TestMap=NULL;
	MapXByte	=0;
	MapXLen		=0;
	MapYLen		=0;

	if(src.TestMap!=NULL){
		MapXByte	=src.MapXByte;
		MapXLen		=src.MapXLen	;
		MapYLen		=src.MapYLen	;
		TestMap=MakeMatrixBuff(MapXByte,MapYLen);

		MatrixBuffCopy	(TestMap					,MapXByte	 ,MapYLen
						,(const BYTE **)src.TestMap ,src.MapXByte,src.MapYLen);
	}
	return(*this);
}

XAlignmentFlexAreaArea  &XAlignmentFlexAreaArea::CopyWithoutItems(const XAlignmentFlexAreaArea &src,bool ReferedMode)
{
	MaxSearchAreaFromItem	=src.MaxSearchAreaFromItem;
    AreaID		=src.AreaID;
	Priority	=src.Priority;
	if(ReferedMode==true)
		Area.SetRefereneFrom((FlexAreaBasePure *)&src.Area);
	else
		Area		=src.Area;

	Locked			=src.Locked;
	Selected		=src.Selected;
	Active			=src.Active;
	Visible			=src.Visible;
	ManualCreated	=src.ManualCreated;
	Origin			=src.Origin;

	if(src.TestMap!=NULL){
		MapXByte	=src.MapXByte;
		MapXLen		=src.MapXLen	;
		MapYLen		=src.MapYLen	;
		TestMap=MakeMatrixBuff(MapXByte,MapYLen);

		MatrixBuffCopy	(TestMap					,MapXByte	 ,MapYLen
						,(const BYTE **)src.TestMap ,src.MapXByte,src.MapYLen);
	}
	return(*this);
}

void    XAlignmentFlexAreaArea::MoveTo(int dx ,int dy)
{
	if(Locked==false){
		Area.MoveToNoClip(dx,dy);
	}
}

void	XAlignmentFlexAreaArea::DeleteAllItemsFromParent(void)
{
	for(AlgorithmItemPI *Item=ParentInPage->GetFirstData();Item!=NULL;){
		AlgorithmItemPI *NextItem=Item->GetNext();
		AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(Item);
		if(AItem!=NULL && AItem->AreaID==AreaID){
			ParentInPage->RemoveItem(AItem);
			delete	AItem;
		}
		Item=NextItem;
	}

	BuildGroupPack();
}

int	XAlignmentFlexAreaArea::GetPage(void)
{
	return ParentInPage->GetPage();
}

void    XAlignmentFlexAreaArea::GetCenter(int &cx, int &cy)
{
	Area.GetCenter(cx,cy);
}
void	XAlignmentFlexAreaArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentFlexAreaBase	*pbase=dynamic_cast<AlignmentFlexAreaBase *>(ParentInPage->GetParentBase());
	if(pbase!=NULL){
		AlignmentFlexAreaDrawAttr	*LAttr=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
		int	globalPage=ParentInPage->GetLayersBase()->GetGlobalPageFromLocal(ParentInPage->GetPage());
		if(LAttr!=NULL && LAttr->DrawGeneratedArea==true && (LAttr->SelectedArea.GetCount()==0 || LAttr->SelectedArea.IsInclude(AreaID)==true)){
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
		else{
			for(AlignmentGroup	*G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
				for(AlgorithmItemPointerList *p=G->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetItem()->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
		if(TestMap!=NULL){
			QColor Col=Qt::cyan;
			::DrawBitImageOr(pnt, (const BYTE **)TestMap ,MapXLen ,MapXByte ,MapYLen
					,movx+Area.GetMinX() ,movy+Area.GetMinY(),ZoomRate
					,0,0
					,Col);
		}
	}
}
void	XAlignmentFlexAreaArea::DrawGroup(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
		g->Draw(0 ,0,pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	XAlignmentFlexAreaArea::DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentFlexAreaBase	*pbase=dynamic_cast<AlignmentFlexAreaBase *>(ParentInPage->GetParentBase());
	if(pbase!=NULL){
		AlignmentFlexAreaDrawAttr	*LAttr=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
		if(LAttr!=NULL){
			Attr->NormalColor=pbase->ColorPoint;
			Attr->NormalColor.setAlpha(pbase->AlphaLevel);
			Attr->SelectedColor	=pbase->ColorPointSelected;
			Attr->SelectedColor.setAlpha(pbase->AlphaLevel);
			Attr->ActiveColor	=pbase->ColorPointActive;
			Attr->ActiveColor.setAlpha(pbase->AlphaLevel);

			for(AlignmentGroup	*G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
				for(AlgorithmItemPointerList *p=G->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetItem()->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
		else{
			for(AlignmentGroup	*G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
				for(AlgorithmItemPointerList *p=G->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetItem()->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
	}
}

void	XAlignmentFlexAreaArea::DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(Selected==true && Locked==false){
		Area.Draw(dx,dy ,&pnt ,Col.rgba(),ZoomRate ,movx ,movy);
	}
}

int	SortAlignmentShiftItemList(const void *a, const void *b)
{
	struct AlignmentFlexAreaShiftItemListStruct *ha=((struct AlignmentFlexAreaShiftItemListStruct **)a)[0];
	struct AlignmentFlexAreaShiftItemListStruct *hb=((struct AlignmentFlexAreaShiftItemListStruct **)b)[0];
	if(ha->Match>hb->Match)
		return -1;
	else if(ha->Match<hb->Match)
		return 1;
	return 0;
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


double	XAlignmentFlexAreaArea::GetClosedResultInPoint(int localX ,int localY)
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
static	int		DbgIndexForGroupIDMVectorList=296;
static	int		DbgIndexForGroup;

bool	XAlignmentFlexAreaArea::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	Area.ClipArea(0,0,ParentInPage->GetDotPerLine()-1,ParentInPage->GetMaxLines()-1);
	BuildGroupPack();
	RemoveRepeatableGroup();

	int		IndexForGroupIDMVectorList=0;
	MVectorList.RemoveAll();
    MVectorXRes=32;
    MVectorYRes=32;
    MVectorXNumb=(Area.GetWidth() +MVectorXRes-1)/MVectorXRes;
    MVectorYNumb=(Area.GetHeight()+MVectorYRes-1)/MVectorYRes;
	if(MVectorXNumb>256){
		MVectorXRes=Area.GetWidth()/256;
		MVectorXNumb=(Area.GetWidth() +MVectorXRes-1)/MVectorXRes;
	}
	if(MVectorYNumb>256){
		MVectorYRes=Area.GetHeight()/256;
		MVectorYNumb=(Area.GetHeight() +MVectorYRes-1)/MVectorYRes;
	}
    if(MVector!=NULL)
        delete []MVector;
    MVector=new IndexForGroup*[MVectorXNumb*MVectorYNumb];

	int	AreaLen=min(Area.GetWidth(),Area.GetHeight());
	int	MaxAreaLen=max(3000,AreaLen/5);

	int	AreaMinX=Area.GetMinX();
	int	AreaMinY=Area.GetMinY();

	//OpenMPÇæÇ∆Ç§Ç‹Ç≠Ç¢Ç©Ç»Ç¢Åiåãâ Ç™à·Ç§Åj
	#pragma omp parallel
	{
		#pragma omp for
		for(int yn=0;yn<MVectorYNumb;yn++){
			for(int xn=0;xn<MVectorXNumb;xn++){
				int	XPos=xn*MVectorXRes+AreaMinX;
				int	YPos=yn*MVectorYRes+AreaMinY;

				double	DMin=99999999;
				AlignmentGroup *MinGroup=NULL;
				AlignmentGroup *MinGroup2=NULL;
				AlignmentGroup *MinGroup3=NULL;
				for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
					int	cx,cy;
					G->GetCenter(cx,cy);
					double	DLen=hypot(cx-XPos,cy-YPos);
					if(DMin>DLen){
						DMin=DLen;
						MinGroup=G;
					}
				}
				if(MinGroup!=NULL){
					int	Gx1,Gy1;
					MinGroup->GetCenter(Gx1,Gy1);
					double	s1=GetSita(Gx1-XPos,Gy1-YPos);

					if(MinGroup!=NULL){
						DMin=99999999;				
						for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
							if(G==MinGroup)
								continue;
							int	cx,cy;
							G->GetCenter(cx,cy);
							double	DLen=hypot(cx-XPos,cy-YPos);
							double	s2=GetSita(cx-XPos,cy-YPos);
							double	DifS=DiffSita(s1,s2);
							if(DMin>DLen && DLen<MaxAreaLen && DifS>M_PI/3){
								DMin=DLen;
								MinGroup2=G;
							}
						}
						if(MinGroup2==NULL){
							DMin=99999999;
							for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
								if(G==MinGroup)
									continue;
								int	cx,cy;
								G->GetCenter(cx,cy);
								double	DLen=hypot(cx-XPos,cy-YPos);
								if(DMin>DLen){
									DMin=DLen;
									MinGroup2=G;
								}
							}
						}
						if(MinGroup2!=NULL){
							int	Gx2,Gy2;
							MinGroup2->GetCenter(Gx2,Gy2);
							double	s2=GetSita(Gx2-XPos,Gy2-YPos);

							int	cx1,cy1;
							MinGroup->GetCenter(cx1,cy1);
							int	cx2,cy2;
							MinGroup2->GetCenter(cx2,cy2);
							DMin=99999999;
							for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
								if(G==MinGroup2 || G==MinGroup)
									continue;
								int	cx,cy;
								G->GetCenter(cx,cy);
								double	DLen=hypot(cx-XPos,cy-YPos);
								double	s3=GetSita(cx-XPos,cy-YPos);
								double	DifS1=DiffSita(s2,s3);
								double	DifS2=DiffSita(s1,s3);
								if(DMin>DLen && DLen<MaxAreaLen && DifS1>M_PI/3 && DifS2>M_PI/3){
									DMin=DLen;
									MinGroup3=G;
								}
							}
							if(MinGroup3==NULL){
								DMin=99999999;
								for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
									if(G==MinGroup2 || G==MinGroup)
										continue;
									int	cx,cy;
									G->GetCenter(cx,cy);
									if(CheckInsideTriangle (cx1,cy1
															,cx2,cy2
															,cx,cy
															,XPos,YPos)==false)
										continue;
									double	DLen=hypot(cx-XPos,cy-YPos);
									if(DLen<MaxAreaLen){
										double	A=GetAreaDot(cx1,cy1
															,cx2,cy2
															,cx,cy);
										if(A<0.1)
											continue;
										double	Dh=DLen/A;
										if(DMin>Dh){
											DMin=Dh;
											MinGroup3=G;
										}
									}
								}
							}
							if(MinGroup3==NULL){
								DMin=99999999;
								for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
									if(G==MinGroup2 || G==MinGroup)
										continue;
									int	cx,cy;
									G->GetCenter(cx,cy);
									double	DLen=hypot(cx-XPos,cy-YPos);
									double	A=GetAreaDot(cx1,cy1
														,cx2,cy2
														,cx,cy);
									if(A<0.1)
										continue;
									if(DLen<MaxAreaLen){
										double	Dh=DLen/A;
										if(DMin>Dh){
											DMin=Dh;
											MinGroup3=G;
										}
									}
								}
							}
						}
					}
					bool	FoundM=false;
					for(IndexForGroupList *m=MVectorList.GetFirst();m!=NULL;m=m->GetNext()){
						if(m->CheckEqual(MinGroup,MinGroup2,MinGroup3)==true){
							#pragma omp critical
							{
								MVector[yn*MVectorXNumb+xn]=m;
								FoundM=true;
							}
							break;
						}
					}

					if(FoundM==false){
						if(IndexForGroupIDMVectorList==DbgIndexForGroupIDMVectorList)
							DbgIndexForGroup++;

						if(MinGroup!=NULL && MinGroup2!=NULL && MinGroup3!=NULL){
							int	cx1,cy1;
							int	cx2,cy2;
							int	cx3,cy3;
							MinGroup	->GetCenter(cx1,cy1);
							MinGroup2	->GetCenter(cx2,cy2);
							MinGroup3	->GetCenter(cx3,cy3);

							double	L1=hypot(cx2-cx1,cy2-cy1);
							double	L2=hypot(cx3-cx1,cy3-cy1);
							double	L3=hypot(cx3-cx2,cy3-cy2);
							double	MaxL=max(max(L1,L2),L3);
							double	MinL=min(min(L1,L2),L3);

							double	A=GetAreaDot(cx1,cy1
												,cx2,cy2
												,cx3,cy3);
							if(A/MaxL<MinL*0.2){
								MinGroup3=NULL;
							}
						}
						int	iIndexForGroupIDMVectorList;
						#pragma omp critical
						{
							iIndexForGroupIDMVectorList=IndexForGroupIDMVectorList;
							IndexForGroupIDMVectorList++;

							IndexForGroupList	*m=new IndexForGroupList(iIndexForGroupIDMVectorList,AreaID);
							m->Index[0]=MinGroup;
							m->Index[1]=MinGroup2;
							m->Index[2]=MinGroup3;
							MVector[yn*MVectorXNumb+xn]=m;
							MVectorList.AppendList(m);
						}
					}
				}
			}
		}
	}

	int		IndexForGroupID=0;
	NPListPack<AlignmentGroupList>	AlignmentGroupListContainer;
	for(AlignmentGroup *a=GroupPack.GetFirst();a!=NULL;a=a->GetNext()){
		AlignmentGroupListContainer.AppendList(new AlignmentGroupList(a));
	}

	for(AlignmentGroupList *a=AlignmentGroupListContainer.GetFirst();a!=NULL;a=a->GetNext()){
		int	cx1,cy1;
		a->Point->GetCenter(cx1,cy1);
		for(AlignmentGroupList *b=a->GetNext();b!=NULL;){
			AlignmentGroupList *bNext=b->GetNext();
			int	cx2,cy2;
			b->Point->GetCenter(cx2,cy2);
			if(cx1==cx2 && cy1==cy2){
				AlignmentGroupListContainer.RemoveList(b);
				delete	b;
			}
			b=bNext;
		}
	}

	IndexForGroupListContainer.RemoveAll();
	HNext:;
	for(AlignmentGroupList *a=AlignmentGroupListContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Effective==true){
			int	cx1,cy1;
			a->Point->GetCenter(cx1,cy1);

			double	MinLen=99999999;
			AlignmentGroupList *MinB=NULL;
			for(AlignmentGroupList *b=a->GetNext();b!=NULL;b=b->GetNext()){
				int	cx2,cy2;
				b->Point->GetCenter(cx2,cy2);
				double	Len=hypot(cx1-cx2,cy1-cy2);
				if(Len<MinLen){
					MinLen=Len;
					MinB=b;
				}
			}
			double	DMin=99999999;
			AlignmentGroupList	*G1=NULL;
			AlignmentGroupList	*G2=MinB;
			if(MinB!=NULL){
				int	cx2,cy2;
				MinB->Point->GetCenter(cx2,cy2);
				for(AlignmentGroupList *b=a->GetNext();b!=NULL;b=b->GetNext()){
					if(b!=MinB){
						int	cx3,cy3;
						b->Point->GetCenter(cx3,cy3);
						{
							int	Vx1=cx2-cx3;
							int	Vy1=cy2-cy3;
							int	Vx2=cx1-cx3;
							int	Vy2=cy1-cy3;
							if(Vx1*Vx2+Vy1*Vy2<0)
								continue;
						}
						{
							int	Vx1=cx2-cx1;
							int	Vy1=cy2-cy1;
							int	Vx2=cx3-cx1;
							int	Vy2=cy3-cy1;
							if(Vx1*Vx2+Vy1*Vy2<0)
								continue;
						}
						{
							int	Vx1=cx1-cx2;
							int	Vy1=cy1-cy2;
							int	Vx2=cx3-cx2;
							int	Vy2=cy3-cy2;
							if(Vx1*Vx2+Vy1*Vy2<0)
								continue;
						}
						double	A=GetAreaDot(cx1,cy1
											,cx2,cy2
											,cx3,cy3);
						if(DMin>A){
							DMin=A;
							G1=b;
						}
					}
				}
			}
			if(G1==NULL || DMin<=100){

				DMin=99999999;
				G1=NULL;
				G2=NULL;
				AlignmentGroupList *b; 
				#pragma omp parallel 
				#pragma omp single private(b) 
				for(b=a->GetNext();b!=NULL;b=b->GetNext()){
					#pragma omp task 
					{ 
						int	cx2,cy2;
						b->Point->GetCenter(cx2,cy2);
						for(AlignmentGroupList *c=b->GetNext();c!=NULL;c=c->GetNext()){
							int	cx3,cy3;
							c->Point->GetCenter(cx3,cy3);
							{
								int	Vx1=cx2-cx3;
								int	Vy1=cy2-cy3;
								int	Vx2=cx1-cx3;
								int	Vy2=cy1-cy3;
								if(Vx1*Vx2+Vy1*Vy2<0)
									continue;
							}
							{
								int	Vx1=cx2-cx1;
								int	Vy1=cy2-cy1;
								int	Vx2=cx3-cx1;
								int	Vy2=cy3-cy1;
								if(Vx1*Vx2+Vy1*Vy2<0)
									continue;
							}
							{
								int	Vx1=cx1-cx2;
								int	Vy1=cy1-cy2;
								int	Vx2=cx3-cx2;
								int	Vy2=cy3-cy2;
								if(Vx1*Vx2+Vy1*Vy2<0)
									continue;
							}
							double	A=GetAreaDot(cx1,cy1
												,cx2,cy2
												,cx3,cy3);
							#pragma omp critical
							{
								if(DMin>A){
									DMin=A;
									G1=b;
									G2=c;
								}
							}
						}
					}
				}
			}
			if(G1!=NULL && G2!=NULL && DMin>100){
				AlignmentGroupListContainer.RemoveList(a);
				AlignmentGroupListContainer.RemoveList(G1);
				AlignmentGroupListContainer.RemoveList(G2);
				IndexForGroupList	*h=new IndexForGroupList(IndexForGroupID,AreaID);
				IndexForGroupID++;
				h->Index[0]=a->Point;
				h->Index[1]=G1->Point;
				h->Index[2]=G2->Point;
				delete	a;
				delete	G1;
				delete	G2;
				IndexForGroupListContainer.AppendList(h);
				goto	HNext;
			}
			else{
				a->Effective=false;
			}
		}
	}
	for(AlignmentGroupList *a=AlignmentGroupListContainer.GetFirst();a!=NULL;a=a->GetNext()){
		int	cx1,cy1;
		a->Point->GetCenter(cx1,cy1);
		double	MinLen=99999999;
		IndexForGroupList *MinK=NULL;
		for(IndexForGroupList *k=IndexForGroupListContainer.GetFirst();k!=NULL;k=k->GetNext()){
			double	DLen=k->GetDistance(cx1,cy1);
			if(DLen<MinLen){
				MinLen=DLen;
				MinK=k;
			}
		}
		if(MinK!=NULL){
			IndexForGroupList	*h=new IndexForGroupList(IndexForGroupID,AreaID);
			IndexForGroupID++;
			h->Index[0]=a->Point;
			h->Index[1]=MinK->Index[0];
			h->Index[2]=NULL;	//MinK->Index[0];
			IndexForGroupListContainer.AppendList(h);
		}
		else{
			IndexForGroupList	*h=new IndexForGroupList(IndexForGroupID,AreaID);
			IndexForGroupID++;
			h->Index[0]=a->Point;
			h->Index[1]=NULL;
			h->Index[2]=NULL;
			IndexForGroupListContainer.AppendList(h);
		}
	}
	for(AlignmentGroup *a=GroupPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeShiftList();
	}

	return true;
}
bool	XAlignmentFlexAreaArea::BuildGroupPack(void)
{
	GroupPack.RemoveAll();

	AlgorithmItemPointerListContainer	ItemPack;
	IntList	LibIDList;
	for(AlgorithmItemPI *Item=ParentInPage->GetFirstData();Item!=NULL;Item=Item->GetNext()){
		AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(Item);
		if(Item->IsEffective()==true && AItem!=NULL && AItem->AreaID==AreaID){
			ItemPack.Add(Item);
			if(LibIDList.IsInclude(AItem->GetLibID())==false){
				LibIDList.Add(AItem->GetLibID());
			}
		}
	}
	//AlgorithmLibraryContainer	*ALib=GetParentBase()->GetLibraryContainer();
	for(IntClass *c=LibIDList.GetFirst();c!=NULL;c=c->GetNext()){
		GetParentBase()->LoadManagedCacheLib(c->GetValue());
	}

	int	MaxGroupSize=0;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaLibrary	*Lib=(AlignmentFlexAreaLibrary *)GetParentBase()->FindLibFromManagedCacheLib(p->GetItem()->GetLibID());

		if(Lib==NULL)
			return false;
		if(Lib->GroupAreaSize>MaxGroupSize){
			MaxGroupSize=Lib->GroupAreaSize;
		}
		bool	Added=false;
		for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
			if(g->AddItem(p->GetItem(),Lib->GroupAreaSize)==true){
				Added=true;
				break;
			}
		}
		if(Added==false){
			AlignmentGroup *gm=new AlignmentGroup(this);
			if(gm->AppendItem(p->GetItem())==true){
				GroupPack.AppendList(gm);
			}
			else{
				delete	gm;
			}
		}
	}
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
		g->CalcCenter();
	}
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->ItemPack.GetCount()<=2){
			int	Px,Py;
			g->GetCenter(Px,Py);
			double	MinD=99999999;
			AlignmentGroup *MinG=NULL;
			for(AlignmentGroup *h=GroupPack.GetFirst();h!=NULL;h=h->GetNext()){
				if(g==h)
					continue;
				int	Qx,Qy;
				h->GetCenter(Qx,Qy);
				double	D=hypot(Px-Qx,Py-Qy);
				if(MinD>D){
					MinD=D;
					MinG=h;
				}
			}
			if(MinG!=NULL && MinD<MaxGroupSize*1.5){
				MinG->ItemPack.AddMove(g->ItemPack);
				MinG->CalcCenter();
			}
		}
	}
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;){
		AlignmentGroup	*NextG=g->GetNext();
		if(g->ItemPack.GetCount()==0){
			GroupPack.RemoveList(g);
			delete	g;
		}
		g=NextG;
	}
	int		GroupID=0;
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext(),GroupID++){
		g->GroupID=GroupID;
		for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
			AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(p->GetItem());
			if(AItem!=NULL){
				AItem->GroupID=GroupID;
				AItem->ParentArea=this;
				AItem->ParentGroup=g;
			}
		}
	}
	return true;
}

bool	XAlignmentFlexAreaArea::HasItems(void)
{
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->HasItem()==true)
			return true;
	}
	return false;
}

int		XAlignmentFlexAreaArea::GetItemCount(void)
{
	int	ItemCount=0;
	if(ParentInPage!=NULL){
		for(AlgorithmItemPI *t=ParentInPage->GetFirstData();t!=NULL;t=t->GetNext()){
			AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(t);
			if(AItem!=NULL){
				if(AItem->AreaID==AreaID){
					ItemCount++;
				}
			}
		}
	}
	return ItemCount;
}
static	int	AreaDbgX=9328;
static	int	AreaDbgY=6153;
static	int	AreaDbg=0;

bool	XAlignmentFlexAreaArea::RemoveRepeatableGroup(void)
{
	ImagePointerContainer Images;
	ParentInPage->GetMasterBuffForMakeArea(true,Images);
	ImagePointerContainer TargetTRImages;
	ParentInPage->GetTargetTRImages	(TargetTRImages);
	if(Images[0]->IsBitBuff()==true){
		DataInPage	*DP=ParentInPage->GetDataInPage();
		DP->CopyBitBuffToTransposition();
		DP->GetTargetTRImages	(TargetTRImages);
	}

	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;){
		AlignmentGroup *NextG=g->GetNext();
		AlignmentFlexAreaItem	*Item=dynamic_cast<AlignmentFlexAreaItem *>(g->ItemPack.GetFirst()->GetItem());
		int	Shift=Item->GetThresholdR(ParentInPage->GetLayersBase())->SearchDot*2;
		int	OwnShiftX=Item->GetArea().GetWidth();
		int	OwnShiftY=Item->GetArea().GetHeight();
		if(OwnShiftX<4)
			OwnShiftX=4;
		if(OwnShiftY<4)
			OwnShiftY=4;

		if(g->IsInclude(AreaDbgX,AreaDbgY)==true)
			AreaDbg++;

		int	N=2*Shift+1;
		struct	AlignmentFlexAreaShiftListStruct	*ShiftCol=new struct AlignmentFlexAreaShiftListStruct[N*N];
		int	n=0;
		for(int x=-Shift;x<=Shift;x+=2){
			for(int y=-Shift;y<=Shift;y+=2){
				if(-OwnShiftX<=x && x<=OwnShiftX && -OwnShiftY<=y && y<=OwnShiftY){
					continue;
				}
				ShiftCol[n].Dx=x;
				ShiftCol[n].Dy=y;
				ShiftCol[n].Match=0;
				n++;
			}
		}
		if(n>0){
			#pragma omp parallel
			{
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					double	d=g->GetMaxMatchByMaster(Images ,TargetTRImages,ShiftCol[i].Dx,ShiftCol[i].Dy);
					ShiftCol[i].Match=d;
				}
			}
			double	MaxD=0;
			int	MaxDx=0;
			int	MaxDy=0;
			bool	Found=false;
			for(int i=0;i<n;i++){
				if(MaxD<ShiftCol[i].Match){
					Found	=true;
					MaxD	=ShiftCol[i].Match;
					MaxDx	=ShiftCol[i].Dx;
					MaxDy	=ShiftCol[i].Dy;
				}
			}
			if(Found==true){
				MaxD=0;
				int	rMaxDx=0;
				int	rMaxDy=0;
				for(int x=-2;x<=2;x++){
					for(int y=-2;y<=2;y++){
						int	rx=MaxDx+x;
						int	ry=MaxDy+y;
						if(-OwnShiftX<=rx && rx<=OwnShiftX && -OwnShiftY<=ry && ry<=OwnShiftY){
							continue;
						}
						double	d=g->GetMaxMatchByMaster(Images ,TargetTRImages,rx,ry);
						if(d>MaxD){
							MaxD=d;
							rMaxDx=rx;
							rMaxDy=ry;
						}
					}
				}
				double	d=g->GetMinMatchByMaster(Images ,TargetTRImages,rMaxDx,rMaxDy);
				if(d>((AlignmentFlexAreaBase *)ParentInPage->GetParentBase())->CutOffNearbyMatch){
					for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
						AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
						a->SetEffective(false);
					}
					GroupPack.RemoveList(g);
					delete	g;
				}
			}
		}
		delete	[]ShiftCol;
		g=NextG;
	}
	return true;
}

bool	XAlignmentFlexAreaArea::ExecuteStartByInspection(void)
{
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
		g->ExecuteStartByInspection();
	}
	return true;
}

bool    XAlignmentFlexAreaArea::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,AreaID)==false)
		return(false);
	int32	D=(int32)Priority;	//å„ï˚å›ä∑ê´ÇÃÇΩÇﬂint32
	if(::Save(file,D)==false)
		return(false);
	if(Area	.Write(file)==false)
		return(false);
	if(::Save(file,AreaName)==false)
		return false;

	if(LimitedLib.Save(file)==false)
		return false;
	if(LibToCreateItems.Save(file)==false)
		return false;

	if(::Save(file,PartsID)==false)
		return false;
	if(::Save(file,PartsAllocID)==false)
		return false;
	if(::Save(file,Locked)==false)
		return false;
	if(::Save(file,PartsAreaID)==false)
		return false;
	return true;
}
bool	XAlignmentFlexAreaArea::Load(QIODevice *file ,AlignmentFlexAreaInPage *parent)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;

	if(::Load(file,AreaID)==false)
		return(false);
	int32	D;
	if(::Load(file,D)==false)
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

	if(LimitedLib.Load(file)==false)
		return false;
	if(LibToCreateItems.Load(file)==false)
		return false;

	if(::Load(file,PartsID)==false)
		return false;
	if(::Load(file,PartsAllocID)==false)
		return false;

	if(::Load(file,Locked)==false)
		return false;

	if(::Load(file,PartsAreaID)==false)
			return false;

	ParentInPage=parent;
	ParentInPage->FastSearchIDItemStart();
		
	return(true);
}
bool    XAlignmentFlexAreaArea::SaveUnique(QIODevice *file)
{
	int32	D=(int32)Priority;	//å„ï˚å›ä∑ê´ÇÃÇΩÇﬂint32
	if(::Save(file,D)==false)
		return false;
	if(::Save(file,AreaName)==false)
		return false;

	return(true);
}
bool    XAlignmentFlexAreaArea::LoadUnique(QIODevice *file)
{
	int32	D;
	if(::Load(file,D)==false)
		return(false);
	Priority=(_EnumPriority)D;
	if(::Load(file,AreaName)==false)
		return false;

	return(true);
}
	
bool	XAlignmentFlexAreaArea::CalcAlignment(ImagePointerContainer &Images,ImagePointerContainer &TRImages,int offsetx,int offsety)
{
	if(GroupPack.GetCount()>=4){
		//AlignmentGroup *G;
		//#pragma omp parallel
		//#pragma omp single private(G)
		//for(G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
		//	#pragma omp task
		//	G->CalcAlignment(Images,TRImages, offsetx, offsety);
		//}
		AlignmentGroup	*GDim[10000];
		AlignmentGroup	**Gp;
		int	N=GroupPack.GetCount();
		if(N>=sizeof(GDim)/sizeof(GDim[0])){
			Gp=new AlignmentGroup*[N];
		}
		else{
			Gp=GDim;
		}
		int	k=0;
		for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext(),k++){
			Gp[k]=G;
		}
		if(ParentInPage->GetParamGlobal()->CalcSingleThread==true){
			for(int i=0;i<N;i++){
				Gp[i]->CalcAlignment(Images,TRImages, offsetx, offsety);
			}
		}
		else{
			#pragma omp parallel for schedule(dynamic)
			for(int i=0;i<N;i++){
				Gp[i]->CalcAlignment(Images,TRImages, offsetx, offsety);
			}
		}

		if(Gp!=GDim){
			delete	[]Gp;
		}
	}
	else{
		for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
			G->CalcAlignment(Images,TRImages, offsetx, offsety);
		}
	}
	for(IndexForGroupList *k=IndexForGroupListContainer.GetFirst();k!=NULL;k=k->GetNext()){
		k->MinimizeTransformation(0.7);
	}
	if(MVectorList.GetCount()>=4){
		IndexForGroupList *v;
		#pragma omp parallel
		#pragma omp single private(v)
		for(v=MVectorList.GetFirst();v!=NULL;v=v->GetNext()){
			#pragma omp task
			v->CalcParameter();
		}
	}
	else{
		for(IndexForGroupList *v=MVectorList.GetFirst();v!=NULL;v=v->GetNext()){
			v->CalcParameter();
		}
	}

	AlignmentFlexAreaItem	*ItemDim[10000];
	AlignmentFlexAreaItem	**ItemD;
	int	GItemCount=0;
	for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
		GItemCount+=g->ItemPack.GetCount();
	}
	if(GItemCount>=2){
		if(GItemCount>=sizeof(ItemDim)/sizeof(ItemDim[0])){
			ItemD=new AlignmentFlexAreaItem	*[GItemCount];
		}
		else{
			ItemD=ItemDim;
		}
		int	n=0;
		for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
			for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
				ItemD[n]=(AlignmentFlexAreaItem	*)p->GetItem();
				n++;
			}
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<n;i++){
				ItemD[i]->ExecuteSmallSearch(Images,TRImages);
				ItemD[i]->ExecutePreAlignment(0,NULL ,NULL);
			}
		}
		if(ItemD!=ItemDim){
			delete	[]ItemD;
		}
	}
	else{
		for(AlignmentGroup *g=GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
			for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
				AlignmentFlexAreaItem	*Item=(AlignmentFlexAreaItem	*)p->GetItem();
				Item->ExecuteSmallSearch(Images,TRImages);
				p->GetItem()->ExecutePreAlignment(0,NULL ,NULL);
			}
		}
	}
	return true;
}

IndexForGroupList	*XAlignmentFlexAreaArea::GetClosedIndexGroup(int XPos,int YPos)
{
	double	MinD=99999999;
	IndexForGroupList *MinV=NULL;
	//if(MVectorList.GetCount()<100){
		for(IndexForGroupList *v=MVectorList.GetFirst();v!=NULL;v=v->GetNext()){
			double	D=v->GetDistance(XPos,YPos);
			if(D<MinD){
				MinD=D;
				MinV=v;
			}
		}
	//}
	//else{
	//}
	return MinV;
}

void	XAlignmentFlexAreaArea::SetShiftByGlobal(void)
{
	for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
		G->SetShiftByGlobal();
	}
}
void	XAlignmentFlexAreaArea::SetShiftByGlobal(int dx ,int dy)
{
	for(AlignmentGroup *G=GroupPack.GetFirst();G!=NULL;G=G->GetNext()){
		G->SetShiftByGlobal(dx,dy);
	}
}

void	XAlignmentFlexAreaArea::AllocateTestMap(void)
{
	int		iXLen=Area.GetWidth();
	int		iYLen=Area.GetHeight();
	int		iXByte=(iXLen+7)/8;
	if(MapXByte!=iXByte || MapYLen!=iYLen){
		if(TestMap!=NULL){
			DeleteMatrixBuff(TestMap,MapYLen);
		}
		MapXByte=iXByte;
		MapXLen	=iXLen;
		MapYLen	=iYLen;
		TestMap=MakeMatrixBuff(MapXByte ,MapYLen);
	}
}

bool	XAlignmentFlexAreaArea::TestByLibID		(ImagePointerContainer &ImageList ,IntList &LibList)
{
	AllocateTestMap();


	BYTE	**TmpMap=MakeMatrixBuff(MapXByte ,MapYLen);

	int	XPos=Area.GetMinX();
	int	YPos=Area.GetMinY();
	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase	*)ParentInPage->GetParentBase();

	PureFlexAreaListContainer AllFPack;
	for(IntClass *L=LibList.GetFirst();L!=NULL;L=L->GetNext()){
		MatrixBuffClear	(TestMap ,0,MapXByte ,MapYLen);
		AlgorithmLibraryContainer	*Container=ParentInPage->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(ABase->GetLibraryContainer()->GetLibrary(L->GetValue() ,SrcLib)==false){
			DeleteMatrixBuff(TmpMap,MapYLen);
			return false;
		}

		AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(SrcLib.GetLibrary());
		if(ALib!=NULL){
			ConstMapBufferListContainer MaskMap;
			ParentInPage->GetReflectionMap(_Reflection_Mask,MaskMap,ALib);

			if(ALib->PickUpEdge==false){
				for(int Layer=0;Layer<ParentInPage->GetLayerNumb();Layer++){
					if(SrcLib.HasPickLayer(Layer)==false)
						continue;
					const BYTE	**M=MaskMap.GetBitMap(Layer);
					ImageBuffer	*IBuff=ImageList[Layer];
					if(IBuff->IsBitBuff()==false){
						for(int i=0;i<Area.GetFLineLen();i++){
							int	Y=Area.GetFLineAbsY(i);
							int	X=Area.GetFLineLeftX(i);
							int	Numb=Area.GetFLineNumb(i);
							BYTE	*s=IBuff->GetY(Y);
							BYTE	*d=TestMap[Y-YPos];
							const BYTE	*m=(M!=NULL)?M[Y]:NULL;
							for(int n=0;n<Numb;n++){
								if(m!=NULL && GetBmpBitOnY(m,X+n)!=0){
									int	c=s[X+n];
									if(ALib->PickupL<=c && c<=ALib->PickupH){
										int	x=X+n-XPos;
										SetBmpBitOnY1(d,x);
									}
								}
							}
						}
					}
					else{
						for(int i=0;i<Area.GetFLineLen();i++){
							int	Y=Area.GetFLineAbsY(i);
							int	X=Area.GetFLineLeftX(i);
							int	Numb=Area.GetFLineNumb(i);
							BYTE	*s=IBuff->GetY(Y);
							BYTE	*d=TestMap[Y-YPos];
							const BYTE	*m=(M!=NULL)?M[Y]:NULL;
							for(int n=0;n<Numb;n++){
								if(m!=NULL && GetBmpBitOnY(m,X+n)!=0){
									if(GetBmpBitOnY(s,X+n)!=0){
										int	x=X+n-XPos;
										SetBmpBitOnY1(d,x);
									}
								}
							}
						}
					}
				}
			}
			else{
				int	DLen=4;
				for(int Layer=0;Layer<ParentInPage->GetLayerNumb();Layer++){
					if(SrcLib.HasPickLayer(Layer)==false)
						continue;
					ImageBuffer	*IBuff=ImageList[Layer];
					const BYTE	**M=MaskMap.GetBitMap(Layer);
					int	XLen=IBuff->GetWidth();
					int	YLen=IBuff->GetHeight();
					
					int	BrTable[256];
					int	TotalCount=0;
					memset(BrTable,0,sizeof(BrTable));
					for(int i=0;i<Area.GetFLineLen();i++){
						int	Y=Area.GetFLineAbsY(i);
						if(Y<0 || YLen<=Y)
							continue;
						const BYTE	*m=(M!=NULL)?M[Y]:NULL;
						int	X=Area.GetFLineLeftX(i);
						int	Numb=Area.GetFLineNumb(i);
						if(XLen<=X+Numb)
							Numb=XLen-X;
						for(int n=0;n<Numb;n++){
							if(m!=NULL && GetBmpBitOnY(m,X+n)!=0){
								int	xm=X+n;
								int	A=0;
								int	AA=0;
								for(int Ly=-DLen;Ly<=DLen;Ly++){
									if(Y+Ly<0 || YLen<=Y+Ly)
										goto	DNext;
									BYTE	*s=IBuff->GetY(Y+Ly);
									for(int Lx=-DLen;Lx<=DLen;Lx++){
										if(xm+Lx<0 || XLen<=xm+Lx)
											goto	DNext;
										BYTE	c=s[xm+Lx];
										A+=c;
										AA+=c*c;
									}
								}
								int	N=(2*DLen+1)*(2*DLen+1);
								double	Avr=((double)A)/((double)N);
								double	Var=sqrt((AA-N*Avr*Avr)/N);
								int	iVar=(int)Var;
								if(iVar>255)
									iVar=255;
								BrTable[iVar]++;
								TotalCount++;
							}
							DNext:;
						}
					}

					int	Thre=-1;
					int	ThreCount=TotalCount*0.01;

					for(int t=0;t<5;t++){
						if(ThreCount<20)
							ThreCount=20;
						for(int i=255;i>=ALib->PickUpEdgeMinDiff;i--){
							if(BrTable[i]>ThreCount){
								Thre=i-1;
								break;
							}
						}
						if(Thre>0){
							break;
						}
						ThreCount=ThreCount*0.2;
					}
					if(Thre>0){
						for(int i=0;i<Area.GetFLineLen();i++){
							int	Y=Area.GetFLineAbsY(i);
							if(Y<0 || YLen<=Y)
								continue;
							const BYTE	*m=(M!=NULL)?M[Y]:NULL;
							int	X=Area.GetFLineLeftX(i);
							int	Numb=Area.GetFLineNumb(i);
							if(XLen<=X+Numb)
								Numb=XLen-X;

							BYTE	*d=TestMap[Y-YPos];
							for(int n=0;n<Numb;n++){
								if(m!=NULL && GetBmpBitOnY(m,X+n)!=0){
									int	xm=X+n;
									int	A=0;
									int	AA=0;
									for(int Ly=-DLen;Ly<=DLen;Ly++){
										if(Y+Ly<0 || YLen<=Y+Ly)
											goto	DNext2;
										BYTE	*s=IBuff->GetY(Y+Ly);
										for(int Lx=-DLen;Lx<=DLen;Lx++){
											if(xm+Lx<0 || XLen<=xm+Lx)
												goto	DNext2;
											BYTE	c=s[xm+Lx];
											A+=c;
											AA+=c*c;
										}
									}
									int	N=(2*DLen+1)*(2*DLen+1);
									double	Avr=((double)A)/((double)N);
									double	Var=sqrt((AA-N*Avr*Avr)/N);
									int	iVar=(int)Var;
									if(iVar>255)
										iVar=255;
									if(iVar>=Thre){
										SetBmpBitOnY1(d,xm-XPos);
									}
								}
								DNext2:;
							}
						}
					}
				}
			}
			ParentInPage->GetLayersBase()->FatAreaN(TestMap
					,TmpMap
					,MapXByte, MapYLen
					,ALib->ExpansionDot);

			PureFlexAreaListContainer FPack;
			PickupFlexArea(TestMap,MapXByte ,MapXLen,MapYLen ,FPack);
			for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
				PureFlexAreaList *NextF=f->GetNext();
				if((f->GetWidth()<ALib->MinAreaSize && f->GetHeight()<ALib->MinAreaSize)
				|| f->GetPatternByte()<ALib->MinAreaDots
				|| (f->GetWidth()>ALib->MaxAreaSize && f->GetHeight()>ALib->MaxAreaSize)
				|| f->GetPatternByte()>ALib->MaxAreaDots){
					FPack.RemoveList(f);
					delete	f;
				}
				f=NextF;
			}
			AllFPack.AddMove(FPack);
		}
	}
	FlexArea	CurrentArea;
	CurrentArea=Area;
	CurrentArea.MoveToNoClip(-XPos,-YPos);
	MatrixBuffClear	(TestMap ,0,MapXByte ,MapYLen);
	for(PureFlexAreaList *f=AllFPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->CheckOverlap(&CurrentArea)==true){
			f->MakeBitData(TestMap,MapXLen ,MapYLen);
		}
	}
	DeleteMatrixBuff(TmpMap,MapYLen);
	return true;
}

bool	XAlignmentFlexAreaArea::GenerateByLibID	(ImagePointerContainer &ImageList ,IntList &LibList)
{
	//_heapchk();
	Area.ClipArea(0,0,ParentInPage->GetDotPerLine()-1,ParentInPage->GetMaxLines()-1);
	AllocateTestMap();

	BYTE	**TmpMap=MakeMatrixBuff(MapXByte ,MapYLen);

	//int	XPos=Area.GetMinX();
	//int	YPos=Area.GetMinY();
	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase	*)ParentInPage->GetParentBase();
	AlgorithmLibrary	*Lib=ABase->GetLibraryContainer()->CreateNew();
	//AlignmentFlexAreaLibrary	*ALib=(AlignmentFlexAreaLibrary *)Lib;

	//_heapchk();
	for(IntClass *L=LibList.GetFirst();L!=NULL;L=L->GetNext()){
		IntList CurrentLibList;
		CurrentLibList.Add(L->GetValue());
		TestByLibID	(ImageList ,CurrentLibList);

		GenerateFromMap(TestMap,MapXByte ,MapYLen
						,L->GetValue()
						,_OriginType_FromLibrary
						,NULL
						,Area.GetMinX(),Area.GetMinY());
	}
	MatrixBuffClear	(TestMap ,0,MapXByte ,MapYLen);
	DeleteMatrixBuff(TmpMap,MapYLen);
	delete	Lib;

	return true;
}

bool	XAlignmentFlexAreaArea::GenerateFromMap(BYTE **BmpMap,int BmpXByte ,int BmpYLen
												,int LibID 
												,OriginType OType
												,AlgorithmBase *Origin
												,int offsetx ,int offsety)
{
	//_heapchk();
	
	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase	*)ParentInPage->GetParentBase();

	AlgorithmLibraryLevelContainer	SrcLib(ABase);
	if(ABase->GetLibraryContainer()->GetLibrary(LibID,SrcLib)==true){
		AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(SrcLib.GetLibrary());
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpMap,BmpXByte ,BmpXByte*8,BmpYLen ,FPack);
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
			PureFlexAreaList *NextF=f->GetNext();
			if((f->GetWidth()<ALib->MinAreaSize && f->GetHeight()<ALib->MinAreaSize)
			|| f->GetPatternByte()<ALib->MinAreaDots
			|| (f->GetWidth()>ALib->MaxAreaSize && f->GetHeight()>ALib->MaxAreaSize)
			|| f->GetPatternByte()>ALib->MaxAreaDots){
				FPack.RemoveList(f);
				delete	f;
			}
			else{
				f->MoveToNoClip(offsetx,offsety);
			}
			f=NextF;
		}
		
		//_heapchk();

		PureFlexAreaListContainer BlockPack;
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetWidth()>ALib->LimitSize || f->GetHeight()>ALib->LimitSize){
				PureFlexAreaListContainer Piece;
				f->ChopRect(Piece ,ALib->LimitSize);
				for(PureFlexAreaList *c=Piece.GetFirst();c!=NULL;c=c->GetNext()){
					PureFlexAreaList	*a=new PureFlexAreaList(*c);
					BlockPack.AppendList(a);
				}
			}
			else{
				PureFlexAreaList	*a=new PureFlexAreaList(*f);
				BlockPack.AppendList(a);
			}
		}
		for(PureFlexAreaList *f=BlockPack.GetFirst();f!=NULL;){
			PureFlexAreaList *NextF=f->GetNext();
			if(f->GetPatternByte()<ALib->MinAreaDots*0.25){
				for(PureFlexAreaList *g=BlockPack.GetFirst();g!=NULL;g=g->GetNext()){
					if(g==f)
						continue;
					if(f->CheckOverlapNeighbor(g)==true){
						BlockPack.RemoveList(f);
						*g+=*f;
					}
				}
			}
			f=NextF;
		}
		int	Layer=0;
		if(ALib->GetAdaptedGenLayers().GetCount()!=0){
			Layer=ALib->GetAdaptedGenLayers().GetFirst()->GetValue();
		}
		ImagePointerContainer	MBuff;
		ParentInPage->GetMasterImages(0,MBuff);
		ImageBuffer	*M=MBuff[Layer];
		for(PureFlexAreaList *f=BlockPack.GetFirst();f!=NULL;){
			PureFlexAreaList *NextF=f->GetNext();
			int	Len=10;
			int	Dx,Dy;
			bool	Matched=false;
			int	Step=2;
			if(Matched==false){
				Dy=-Len;
				for(Dx=-Len;Dx<=Len;Dx+=Step){
					double	D=f->GetCoeff	(*M ,Dx ,Dy ,*M);
					if(D>ALib->MaxCoeffInNeighbor){
						Matched=true;
						break;
					}
				}
			}
			if(Matched==false){
				Dx=Len;
				for(Dy=-Len;Dy<=Len;Dy+=Step){
					double	D=f->GetCoeff	(*M ,Dx ,Dy ,*M);
					if(D>ALib->MaxCoeffInNeighbor){
						Matched=true;
						break;
					}
				}
			}
			if(Matched==false){
				Dy=Len;
				for(Dx=-Len;Dx<=Len;Dx+=Step){
					double	D=f->GetCoeff	(*M ,Dx ,Dy ,*M);
					if(D>ALib->MaxCoeffInNeighbor){
						Matched=true;
						break;
					}
				}
			}
			if(Matched==false){
				Dx=-Len;
				for(Dy=-Len;Dy<=Len;Dy+=Step){
					double	D=f->GetCoeff	(*M ,Dx ,Dy ,*M);
					if(D>ALib->MaxCoeffInNeighbor){
						Matched=true;
						break;
					}
				}
			}
			if(Matched==true){
				BlockPack.RemoveList(f);
				delete	f;
			}
			f=NextF;
		}
		for(PureFlexAreaList *f=BlockPack.GetFirst();f!=NULL;){
			PureFlexAreaList *NextF=f->GetNext();
			if((f->GetWidth()<ALib->MinAreaSize && f->GetHeight()<ALib->MinAreaSize)
			|| f->GetPatternByte()<ALib->MinAreaDots){
				BlockPack.RemoveList(f);
				delete	f;
			}
			f=NextF;
		}

		for(PureFlexAreaList *f=BlockPack.GetFirst();f!=NULL;f=f->GetNext()){
			AlignmentFlexAreaItem	*Item=new AlignmentFlexAreaItem();
			Item->SetArea(*f);
			Item->SetLibID(LibID);
			Item->SetOriginType(OType);
			Item->AreaID=AreaID;
			Item->GeneratedFromBitMap=false;
			Item->CopyThresholdFromLibrary(&SrcLib);
			if(ParentInPage->AppendItem(Item)==false){
				delete	Item;
			}
		}
	}

	return true;
}


void	XAlignmentFlexAreaArea::ClearTestMap(void)
{
	if(TestMap!=NULL){
		MatrixBuffClear	(TestMap ,0,MapXByte,MapYLen);
	}
}
void	XAlignmentFlexAreaArea::DeleteSelectedItems(void)
{
	for(AlignmentGroup *a=GroupPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->DeleteSelectedItems();
	}
}
void	XAlignmentFlexAreaArea::ExecuteMoveItem(int GlobalDx,int GlobalDy,bool AllItems)
{
	for(AlignmentGroup *a=GroupPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->ExecuteMoveItem(GlobalDx,GlobalDy,AllItems);
	}
}