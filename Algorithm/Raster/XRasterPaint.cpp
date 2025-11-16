#include "XRaster.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XRasterPacket.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XGUIRasterPacket.h"
#include "XPickupPad.h"
#include "XUndo.h"
#include "XImageProcess.h"
#include "XYCross.h"
#include "XCrossObj.h"

bool	RasterInPage::MakePaintArea(double GlobalX,double GlobalY 
								,AlgorithmItemPointerListContainer &ItemList
								,AlgorithmItemPointerListContainer &CreatedItems)
{
	/*
	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE	**CurrentMap=::MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(CurrentMap ,0 ,XByte ,YLen);

	for(AlgorithmItemPointerList *a=ItemList.GetFirst();a!=NULL;a=a->GetNext()){
		RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a->GetItem());
		Item->MakeImage(CurrentMap,0,0,XByte ,YLen);
	}
	int		localX ,localY;
	GetDataInPage()->GetLocalMatrixFromGlobalInMaster(GlobalX,GlobalY ,localX ,localY);
	::MatrixBuffNot	(CurrentMap ,XByte ,YLen);

	FlexArea FArea;
	if(PickupFlexOneArea(CurrentMap ,XByte ,XByte<<3,YLen 
						,localX ,localY
						,FArea)==false){
		DeleteMatrixBuff(CurrentMap,YLen);
		return false;
	}
	BYTE	**TmpMap=::MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(CurrentMap ,0 ,XByte ,YLen);
	FArea.MakeBitData(CurrentMap,GetDotPerLine(),GetMaxLines());
	FatArea(CurrentMap 
			,TmpMap
			,XByte,YLen);
	if(PickupFlexOneArea(CurrentMap ,XByte ,XByte<<3,YLen 
						,localX ,localY
						,FArea)==false){
		DeleteMatrixBuff(TmpMap		,YLen);
		DeleteMatrixBuff(CurrentMap,YLen);
		return false;
	}

	DeleteMatrixBuff(TmpMap		,YLen);
	DeleteMatrixBuff(CurrentMap	,YLen);

	XYClassCluster XY;
	FArea.MakeOutlineDot(XY);
	XYClassArea	*a=XY.GetFirst();
	if(a==NULL)
		return false;

	a->Simplize();
	RasterItemPolygon	*PolygonItem=new RasterItemPolygon();
	int	N=a->NPListPack<XYClass>::GetCount();
	PolygonItem->Points		=new RasterItemPolygon::PointStruct[N+1];
	PolygonItem->PosCount	=0;
	PolygonItem->OrgPosCount=0;
	int	n=0;
	for(XYClass *p=a->NPListPack<XYClass>::GetFirst();p!=NULL;p=p->GetNext(),n++){
		PolygonItem->Points[n].Initial();
		PolygonItem->Points[n].Data.PosX	=p->x;
		PolygonItem->Points[n].Data.PosY	=p->y;
		PolygonItem->Points[n].Data.PointType	=RasterItemPolygon::PointStruct::_Line;
	}
	PolygonItem->Points[n]=PolygonItem->Points[0];
	n++;
	PolygonItem->PosCount=n;
	PolygonItem->PosiImage=true;

	PolygonItem->OrgPosCount=PolygonItem->PosCount;
	if(PolygonItem->OrgPoints!=NULL)
		delete	[]PolygonItem->OrgPoints;
	PolygonItem->OrgPoints=new RasterItemPolygon::PointStruct[PolygonItem->OrgPosCount+2];
	for(int i=0;i<PolygonItem->OrgPosCount;i++){
		PolygonItem->OrgPoints[i]=PolygonItem->Points[i];
	}
	PolygonItem->TrPoints=new RasterItemPolygon::PointStruct[PolygonItem->PosCount+2];
	PolygonItem->Initial(PolygonItem->Points,PolygonItem->PosCount);

	RasterItemAbstract	*ItemNow=dynamic_cast<RasterItemAbstract *>(ItemList.GetFirst()->GetItem());
	PolygonItem->SetFileLayer(ItemNow->GetFileLayer());
	PolygonItem->MakeXY();

	AppendItem(PolygonItem);
	CreatedItems.Add(PolygonItem);

	for(XYClassArea *b=a->GetNext();b!=NULL;b=b->GetNext()){
		b->Simplize();
		RasterItemPolygon	*PolygonInsideItem=new RasterItemPolygon();
		int	N=b->NPListPack<XYClass>::GetCount();
		PolygonInsideItem->Points		=new RasterItemPolygon::PointStruct[N+1];
		PolygonInsideItem->PosCount	=0;
		PolygonInsideItem->OrgPosCount=0;
		int	n=0;
		for(XYClass *p=b->NPListPack<XYClass>::GetFirst();p!=NULL;p=p->GetNext(),n++){
			PolygonInsideItem->Points[n].Data.PosX	=p->x;
			PolygonInsideItem->Points[n].Data.PosY	=p->y;
			PolygonInsideItem->Points[n].Data.PointType	=RasterItemPolygon::PointStruct::_Line;
		}
		PolygonInsideItem->Points[n]=PolygonItem->Points[0];
		n++;
		PolygonInsideItem->PosCount=n;
		PolygonInsideItem->PosiImage=false;

		PolygonInsideItem->OrgPosCount=PolygonInsideItem->PosCount;
		if(PolygonInsideItem->OrgPoints!=NULL)
			delete	[]PolygonInsideItem->OrgPoints;
		PolygonInsideItem->OrgPoints=new RasterItemPolygon::PointStruct[PolygonInsideItem->OrgPosCount+2];
		for(int i=0;i<PolygonInsideItem->OrgPosCount;i++){
			PolygonInsideItem->OrgPoints[i]=PolygonInsideItem->Points[i];
		}
		PolygonInsideItem->TrPoints=new RasterItemPolygon::PointStruct[PolygonInsideItem->PosCount+2];

		RasterItemAbstract	*ItemNow=dynamic_cast<RasterItemAbstract *>(ItemList.GetFirst()->GetItem());
		PolygonInsideItem->SetFileLayer(ItemNow->GetFileLayer());
		PolygonInsideItem->Initial(PolygonInsideItem->Points,PolygonInsideItem->PosCount);
		AppendItem(PolygonInsideItem);
		CreatedItems.Add(PolygonInsideItem);
	}
	*/
	return true;
}

static	int	FPackSortFunc(const void *a,const void *b)
{
	PureFlexAreaList	*ka=((PureFlexAreaList **)a)[0];
	PureFlexAreaList	*kb=((PureFlexAreaList **)b)[0];
	int	Na=ka->GetPatternByte();
	int	Nb=kb->GetPatternByte();
	return Nb-Na;
}

class	FlexAreaPointerListReEntrant;

class	FlexAreaPointerListReEntrantContainer : public NPListPack<FlexAreaPointerListReEntrant>
{
public:
};
class	FlexAreaPointerListReEntrant : public NPList<FlexAreaPointerListReEntrant>
{
public:
	FlexArea *Item;
	FlexAreaPointerListReEntrantContainer	Children;

	FlexAreaPointerListReEntrant(FlexArea *item)	{	Item=item;	}
};

static	void	MakeReEntrant(FlexAreaPointerListReEntrantContainer &ClassifiedItems ,PureFlexAreaListContainer &IncludedItems ,PureFlexAreaListContainer &FPack)
{
	PureFlexAreaList *a;
	while((a=IncludedItems.GetFirst())!=NULL){
		IncludedItems.RemoveList(a);
		FlexAreaPointerListReEntrant	*ka=new FlexAreaPointerListReEntrant(a);

		XYClassCluster XY;
		a->MakeOutlineDot(XY);
		int	n=XY.GetCount();
		if(n>1){
			XYClassArea	*p;
			while((p=XY.GetFirst()->NPList<XYClassArea>::GetNext())!=NULL){
				XY.RemoveList(p);
				delete	p;
			}
			FlexArea Area;
			XY.TransTo(Area);

			PureFlexAreaListContainer IncludedItems;
			for(PureFlexAreaList *b=FPack.GetFirst();b!=NULL;){
				PureFlexAreaList *NextB=b->GetNext();
				if(Area.IsInclude(b)==true){
					FPack.RemoveList(b);
					IncludedItems.AppendList(b);
				}
				b=NextB;
			}
			if(IncludedItems.GetCount()>0){
				MakeReEntrant(ka->Children,IncludedItems,FPack);
			}
		}
		ClassifiedItems.AppendList(ka);
	}
}
static	void	MakeReEntrant(FlexAreaPointerListReEntrantContainer &ClassifiedItems ,PureFlexAreaListContainer &FPack)
{
	PureFlexAreaList *a;
	while((a=FPack.GetFirst())!=NULL){
		FPack.RemoveList(a);
		FlexAreaPointerListReEntrant	*ka=new FlexAreaPointerListReEntrant(a);

		XYClassCluster XY;
		a->MakeOutlineDot(XY);
		int	n=XY.GetCount();
		if(n>1){
			XYClassArea	*p;
			while((p=XY.GetFirst()->NPList<XYClassArea>::GetNext())!=NULL){
				XY.RemoveList(p);
				delete	p;
			}
			FlexArea Area;
			XY.TransTo(Area);

			PureFlexAreaListContainer IncludedItems;
			for(PureFlexAreaList *b=FPack.GetFirst();b!=NULL;){
				PureFlexAreaList *NextB=b->GetNext();
				if(Area.IsInclude(b)==true){
					FPack.RemoveList(b);
					IncludedItems.AppendList(b);
				}
				b=NextB;
			}
			if(IncludedItems.GetCount()>0){
				MakeReEntrant(ka->Children,IncludedItems,FPack);
			}
		}
		ClassifiedItems.AppendList(ka);
	}
}

static	void	AddItemReEntrant(RasterInPage *APage ,AlgorithmItemPointerListContainer &AddedItems
								,FlexAreaPointerListReEntrantContainer &ClassifiedItems
								,bool PosiImage)
{
	for(FlexAreaPointerListReEntrant *k=ClassifiedItems.GetFirst();k!=NULL;k=k->GetNext()){
		FlexArea *f=k->Item;
		XYClassCluster XY;
		f->MakeOutlineDot(XY);
		XYClassArea	*a=XY.GetFirst();
		if(a==NULL)
			continue;

		a->Simplize();
		//RasterItemPolygon	*PolygonItem=new RasterItemPolygon();
		//int	N=a->NPListPack<XYClass>::GetCount();
		//PolygonItem->Points		=new RasterItemPolygon::PointStruct[N+1];
		//PolygonItem->PosCount	=0;
		//PolygonItem->OrgPosCount=0;
		//int	n=0;
		//for(XYClass *p=a->NPListPack<XYClass>::GetFirst();p!=NULL;p=p->GetNext(),n++){
		//	PolygonItem->Points[n].Initial();
		//	PolygonItem->Points[n].Data.PosX	=p->x;
		//	PolygonItem->Points[n].Data.PosY	=p->y;
		//	PolygonItem->Points[n].Data.PointType	=RasterItemPolygon::PointStruct::_Line;
		//}
		//PolygonItem->Points[n]=PolygonItem->Points[0];
		//
		//n++;
		//PolygonItem->PosCount=n;
		//PolygonItem->PosiImage=PosiImage;
		//AddedItems.Add(PolygonItem);
	}
	for(FlexAreaPointerListReEntrant *k=ClassifiedItems.GetFirst();k!=NULL;k=k->GetNext()){
		AddItemReEntrant(APage ,AddedItems
							,k->Children
							,!PosiImage);
	}
}

void	RasterInPage::MakeDraw(int FileLayerID ,AlgorithmItemPointerListContainer &AddedItems)
{
	RasterFileLayer	*gf=FileLayerList.Find(FileLayerID);
	if(gf==NULL)
		return;

	double	MinX=999999999;
	double	MinY=999999999;
	double	MaxX=-9999999999;
	double	MaxY=-9999999999;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetSelected()==true){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				if(Item->GetFileLayerID()==FileLayerID){
					double	x1,y1,x2,y2;
					Item->GetXY(x1,y1,x2,y2);
					if(CheckOverlapRectRect(x1,y1,x2,y2 , 0.0,0.0,(double)GetDotPerLine(),(double)GetMaxLines())==true){
						MinX=min(MinX,x1);
						MinY=min(MinY,y1);
						MaxX=max(MaxX,x2);
						MaxY=max(MaxY,y2);
					}
				}
			}
		}
	}
	if(MinX>MaxX || MinY>MaxY){
		return;
	}
	MinX-=10;
	MinY-=10;
	MaxX+=10;
	MaxY+=10;

	int	XLen=ceil(MaxX-MinX);
	int	XByte=(XLen+7)/8;
	int	YLen=ceil(MaxY-MinY);
	BYTE	**TmpImage=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetSelected()==true){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				if(Item->GetFileLayerID()==FileLayerID){
					Item->MakeImage(TmpImage,-MinX,-MinY,XByte,YLen);
				}
			}
		}
	}
	::MatrixBuffNot	(TmpImage ,XByte ,YLen);
	PureFlexAreaListContainer FPack;
	if(	PickupFlexArea(TmpImage,XByte ,XLen,YLen ,FPack)==false)
		return;
	DeleteMatrixBuff(TmpImage		,YLen);

	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
		PureFlexAreaList *NextA=a->GetNext();
		if(a->GetMinX()<10 || a->GetMaxX()>=XLen-10
		|| a->GetMinY()<10 || a->GetMaxX()>=YLen-10){
			FPack.RemoveList(a);
			delete	a;
		}
		else {
			a->MoveToClip(MinX,MinY ,0,0,GetDotPerLine(),GetMaxLines());
			if(a->GetPatternByte()==0){
				FPack.RemoveList(a);
				delete	a;
			}
		}
		a=NextA;
	}
	FPack.Sort(FPackSortFunc);
	FlexAreaPointerListReEntrantContainer ClassifiedItems;
	MakeReEntrant(ClassifiedItems ,FPack);

	AddItemReEntrant(this,AddedItems,ClassifiedItems,true);
	for(AlgorithmItemPointerList *k=AddedItems.GetFirst();k!=NULL;k=k->GetNext()){
		//RasterItemPolygon	*Item=dynamic_cast<RasterItemPolygon *>(k->GetItem());
		//if(Item!=NULL){
		//	Item->SetFileLayer(gf);
		//	Item->MakeXY();
		//	Item->SetCurrentSize();
		//}
	}
}

