/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Process3D\XProcess3DItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XProcess3D.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XProcess3DLibrary.h"
#include "XImageProcess.h"
#include "swap.h"
#include <omp.h>
#include "XDisplayBitImage.h"
#include "XCrossObj.h"

//=========================================================================================

Process3DItem::XYLinesP3D::XYLinesP3D(void)
{
	MinX=0;
	MinY=0;
	MaxX=0;
	MaxY=0;
	coss =sins=C=0;
	Px1=Py1=Px2=Py2=0;
}
bool    Process3DItem::XYLinesP3D::Save(QIODevice  *file)
{
    int32 N=NPListPack<XYClass>::GetNumber();
	if(::Save(file,N)==false)
        return(false);
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(file)==false)
			return false;
    }

	if(::Save(file,coss)==false)
        return(false);
	if(::Save(file,sins)==false)
        return(false);
	if(::Save(file,C)==false)
        return(false);
	if(::Save(file,Px1)==false)
        return(false);
	if(::Save(file,Py1)==false)
        return(false);
	if(::Save(file,Px2)==false)
        return(false);
	if(::Save(file,Py2)==false)
        return(false);

    return(true);
}
bool    Process3DItem::XYLinesP3D::Load(QIODevice  *file)
{
    RemoveAll();
    int32 N;
    if(::Load(file,N)==false)
        return(false);
    for(int i=0;i<N;i++){
        XYClass *c=new XYClass();
		if(c->Load(file)==false)
			return false;
        AppendList(c);
    }
	if(::Load(file,coss)==false)
        return(false);
	if(::Load(file,sins)==false)
        return(false);
	if(::Load(file,C)==false)
        return(false);
	if(::Load(file,Px1)==false)
        return(false);
	if(::Load(file,Py1)==false)
        return(false);
	if(::Load(file,Px2)==false)
        return(false);
	if(::Load(file,Py2)==false)
        return(false);

	MinX=-99999999;
	MinY=-99999999;
	MaxX=99999999;
	MaxY=99999999;
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		MinX=min(MinX,c->x);
		MinY=min(MinY,c->y);
		MaxX=max(MaxX,c->x);
		MaxY=max(MaxY,c->y);
	}
    return(true);

}

bool    Process3DItem::XYLinesP3D::IsInclude(int x ,int y ,double AreaLength)
{
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		XYClass *d=c->GetNext();
		if(d==NULL){
			break;
		}
		int	X,Y;
		if(GetLinePointFoot(c->x,c->y,d->x,d->y ,x,y ,X,Y)==true){
			double	t=GetLengthLine2Point(c->x,c->y,d->x,d->y ,x,y);
			if(t<=AreaLength){
				return true;
			}
		}
	}
	return false;
}
void    Process3DItem::XYLinesP3D::Rotate(double angle ,int cx ,int cy)
{
    double  coss=cos(angle);
    double  sins=sin(angle);

    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        int x= (c->x-cx)*coss + (c->y-cy)*sins;
        int y=-(c->x-cx)*sins + (c->y-cy)*coss;
        c->x=x+cx;
        c->y=y+cy;
	}
}
bool    Process3DItem::XYLinesP3D::IsOverlapLine(int x1, int y1 ,int x2 ,int y2)
{
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		XYClass *d=c->GetNext();
		if(d==NULL){
			break;
		}
		long	X,Y;
		if(GetCrossInnerPoint(x1,y1,x2,y2	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
	}
	return false;
}
bool    Process3DItem::XYLinesP3D::IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2)
{
	int	X1=min(x1,x2);
	int	X2=max(x1,x2);
	int	Y1=min(y1,y2);
	int	Y2=max(y1,y2);
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		XYClass *d=c->GetNext();
		if(d==NULL){
			break;
		}
		long	X,Y;
		if(GetCrossInnerPoint(X1,Y1,X2,Y1	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
		if(GetCrossInnerPoint(X2,Y1,X2,Y2	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
		if(GetCrossInnerPoint(X2,Y2,X1,Y2	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
		if(GetCrossInnerPoint(X1,Y2,X1,Y1	,c->x,c->y,d->x,d->y, X ,Y)==true){
			return true;
		}
	}
	XYClass *e=NPListPack<XYClass>::GetFirst();
	if(e!=NULL){
		if(X1<=e->x && e->x<=X2 && Y1<=e->y && e->y<=Y2){
			return true;
		}
	}

	return false;
}
void    Process3DItem::XYLinesP3D::MoveTo(int dx ,int dy)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
        c->x+=dx;
        c->y+=dy;
	}
}

bool    Process3DItem::XYLinesP3D::GetXY(int &minx ,int &miny ,int &maxx ,int &maxy)
{
    minx=99999999;
    miny=99999999;
    maxx=-99999999;
    maxy=-99999999;
	bool	Ret=false;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		if(minx>c->x){
            minx=c->x;
		}
		if(miny>c->y){
            miny=c->y;
		}
		if(maxx<c->x){
            maxx=c->x;
		}
		if(maxy<c->y){
            maxy=c->y;
		}
		Ret=true;
    }
	return Ret;
}
void    Process3DItem::XYLinesP3D::GetCenter(int &cx ,int &cy)
{
    int minx;
    int miny;
    int maxx;
    int maxy;
    if(GetXY(minx ,miny ,maxx ,maxy)==true){
	    cx=(minx+maxx)/2;
		cy=(miny+maxy)/2;
	}
}
void    Process3DItem::XYLinesP3D::ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines)
{
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        c->ChangeXY(outlineOffset ,MaxPage,maxlines);
        }
}
bool    Process3DItem::XYLinesP3D::IsValid(void)
{
	if(NPListPack<XYClass>::GetNumber()<=1){
        return(false);
	}
    return(true);
}
void    Process3DItem::XYLinesP3D::Regulate(void)
{
	MinX=-99999999;
	MinY=-99999999;
	MaxX=99999999;
	MaxY=99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;){
        XYClass *c2=c->GetNext();
		if(c2==NULL){
            break;
		}
        if(c->x==c2->x
        && c->y==c2->y){
            NPListPack<XYClass>::RemoveList(c2);
			delete	c2;
		}
        else{
			MinX=min(MinX,c->x);
			MinY=min(MinY,c->y);
			MaxX=max(MaxX,c->x);
			MaxY=max(MaxY,c->y);
            c=c->GetNext();
		}
	}
}

Process3DItem::XYLinesP3D &Process3DItem::XYLinesP3D::operator=(Process3DItem::XYLinesP3D &src)
{
    NPListPack<XYClass>::RemoveAll();
    for(XYClass *c=src.NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
        XYClass *d=new XYClass();
        *d=*c;
        NPListPack<XYClass>::AppendList(d);
	}
 	MinX=src.MinX;
	MinY=src.MinY;
	MaxX=src.MaxX;
	MaxY=src.MaxY;

	coss=src.coss;
	sins=src.sins;
	C	=src.C;
	Px1	=src.Px1;
	Py1	=src.Py1;
	Px2	=src.Px2;
	Py2	=src.Py2;

	return(*this);
}

void	Process3DItem::XYLinesP3D::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
	int	Rx;
	int	Ry;
	XYClass *c=NPListPack<XYClass>::GetFirst();
	if(c!=NULL){
		Rx=(c->x+movx)*ZoomRate;
		Ry=(c->y+movy)*ZoomRate;

        for(c=(XYClass *)c->GetNext();c!=NULL;c=(XYClass *)c->GetNext()){
			int	Qx=(c->x+movx)*ZoomRate;
			int	Qy=(c->y+movy)*ZoomRate;
			if(Qx!=Rx || Qy!=Ry){
				pnt.drawLine(Rx,Ry,Qx,Qy);
				Rx=Qx;
				Ry=Qy;
			}
		}

		int	kx1=(Px1+movx)*ZoomRate;
		int	ky1=(Py1+movy)*ZoomRate;
		int	kx2=(Px2+movx)*ZoomRate;
		int	ky2=(Py2+movy)*ZoomRate;
		pnt.drawLine(kx1,ky1,kx2,ky2);
	}
}
	
void	Process3DItem::XYLinesP3D::GetMinY(int &x ,int &y)
{
	x=0;
	y=99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(c->y<y){
			y=c->y;
			x=c->x;
		}
	}
}

void	Process3DItem::XYLinesP3D::GetMaxY(int &x ,int &y)
{
	x=0;
	y=-99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		if(c->y>y){
			y=c->y;
			x=c->x;
		}
	}
}

double	Process3DItem::XYLinesP3D::GetDistance(int x,int y)
{
	double	MinD=99999999;
    for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		double	D=hypot(c->x-x,c->y-y);
		if(MinD>D){
			MinD=D;
		}
	}
	return MinD;
}

void	Process3DItem::XYLinesP3D::CreateOneLine(BYTE **BmpMap , int XLen ,int YLen
										,int x ,int y)
{
	SetBmpBit0(BmpMap,x,y);
	XYClass	*L=new XYClass();
	L->x=x;
	L->y=y;
	AppendList(L);

	if(0<y){
		if(0<x && GetBmpBit(BmpMap,x-1,y-1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x-1 ,y-1);
		if(GetBmpBit(BmpMap,x,y-1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x ,y-1);
		if((x+1)<XLen && GetBmpBit(BmpMap,x+1,y-1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x+1 ,y-1);
	}
		
	if(0<x && GetBmpBit(BmpMap,x-1,y)!=0)
		CreateOneLine(BmpMap , XLen ,YLen ,x-1 ,y);
	if((x+1)<XLen && GetBmpBit(BmpMap,x+1,y)!=0)
		CreateOneLine(BmpMap , XLen ,YLen ,x+1 ,y);

	if((y+1)<YLen){
		if(0<x && GetBmpBit(BmpMap,x-1,y+1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x-1 ,y+1);
		if(GetBmpBit(BmpMap,x,y+1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x ,y+1);
		if((x+1)<XLen && GetBmpBit(BmpMap,x+1,y+1)!=0)
			CreateOneLine(BmpMap , XLen ,YLen ,x+1 ,y+1);
	}
}

bool	Process3DItem::XYLinesP3D::CalcInterpolationLine(void)
{
	int Point[10000][2];
	int	PointNumb=0;
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		Point[PointNumb][0]=c->x;
		Point[PointNumb][1]=c->y;
		PointNumb++;
		if(PointNumb>=10000)
			break;
	}

	double coss1 ,sins1, c1;
	double coss2 ,sins2, c2;

	CalcLine(coss1 ,sins1, c1
			,coss2 ,sins2, c2
            ,Point ,PointNumb);

	double	D1=0;
	double	D2=0;
	for(XYClass *c=NPListPack<XYClass>::GetFirst();c!=NULL;c=(XYClass *)c->GetNext()){
		D1+=fabs(coss1*c->x+sins1*c->y+c1);
		D2+=fabs(coss2*c->x+sins2*c->y+c2);
	}
	if(D1<D2){
		coss=coss1;
		sins=sins1;
		C=c1;
	}
	else{
		coss=coss2;
		sins=sins2;
		C=c2;
	}

	int	x,y;
	GetMinY(x,y);
	Py1=y;
	Px1=(-C-coss*Py1)/sins;
	GetMaxY(x,y);
	Py2=y;
	Px2=(-C-coss*Py2)/sins;

	return true;
}

//=========================================================================================
bool    Process3DItem::XYLineP3DContainer::Save(QIODevice  *file)
{
	if(NPListPackSaveLoad<XYLinesP3D>::Save(file)==false)
		return false;
    return(true);
}
bool    Process3DItem::XYLineP3DContainer::Load(QIODevice  *file)
{
    if(NPListPackSaveLoad<XYLinesP3D>::Load(file)==false)
		return false;

    return(true);

}

void	Process3DItem::XYLineP3DContainer::CreateLines(BYTE **BmpMap , int XByte ,int YLen ,int MapXPos ,int MapYPos)
{
	for(int y=0;y<YLen;y++){
		BYTE	*s=BmpMap[y];
		for(int xb=0;xb<XByte;xb++){
			if(s[xb]!=NULL){
				int	X=xb*8;
				for(int i=0;i<8;i++){
					if(GetBmpBitOnY(s,X+i)!=0){
						XYLinesP3D	*L=new XYLinesP3D();
						L->CreateOneLine(BmpMap , XByte*8 ,YLen
										,X+i,y);
						L->MoveTo(MapXPos,MapYPos);
						AppendList(L);
					}
				}
			}
		}
	}
}
	
void	Process3DItem::XYLineP3DContainer::DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy)
{
    for(XYLinesP3D *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->DrawLines(pnt ,ZoomRate ,movx ,movy);
	}
}

void    Process3DItem::XYLineP3DContainer::Regulate(void)
{
    for(XYLinesP3D *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->Regulate();
	}
}
void	Process3DItem::XYLineP3DContainer::CalcInterpolationLine(void)
{
    for(XYLinesP3D *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->CalcInterpolationLine();
	}
}

//==============================================================================================

Process3DItem::Process3DItem(void)
{
	AVector=NULL;

	BmpMap	=NULL;
	MultTable	=NULL;;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	MapXPos=MapYPos=0;

	ResultLargeTile		=0;
	ResultLargeFlatness	=0;
	ResultSmallFlatness	=0;
}

Process3DItem::Process3DItem(FlexArea &area)
:AlgorithmItemPLITemplate<Process3DInLayer,Process3DInPage,Process3DBase>(area)
{
	AVector=NULL;

	BmpMap	=NULL;
	MultTable	=NULL;;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	MapXPos=MapYPos=0;

	ResultLargeTile		=0;
	ResultLargeFlatness	=0;
	ResultSmallFlatness	=0;
}
Process3DItem::~Process3DItem(void)
{
	if(BmpMap!=NULL){
		DeleteMatrixBuff(BmpMap,YLen);
		BmpMap	=NULL;
	}
	if(MultTable!=NULL){
		delete	[]MultTable;
		MultTable=NULL;
	}

	XLen	=0;
	XByte	=0;
	YLen	=0;
}

Process3DItem &Process3DItem::operator=(Process3DItem &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(src);
	return *this;
}

void	Process3DItem::CopyThreshold(Process3DItem &src)
{
	GetThresholdW()->CopyFrom(*((Process3DThreshold *)src.GetThresholdR()));
}

void	Process3DItem::CopyThresholdOnly(Process3DItem &src)
{
	GetThresholdW()->CopyFrom(*((Process3DThreshold *)src.GetThresholdR()));
}

bool    Process3DItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;

	return true;
}
bool    Process3DItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;

	return true;
}

void	Process3DItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((Process3DItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((Process3DItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((Process3DItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((Process3DItem *)Data)->GetLibID()){
			Process3DInLayer	*Ly=dynamic_cast<Process3DInLayer *>(GetParentInLayer());
			UndoElement<Process3DInLayer>	*UPointer=new UndoElement<Process3DInLayer>(Ly,&Process3DInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			Process3DItem *src=(Process3DItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}

void	Process3DItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	Process3DItem	*ASrc=dynamic_cast<Process3DItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((Process3DBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		ResultLargeTile		=ASrc->ResultLargeTile		;
		ResultLargeFlatness	=ASrc->ResultLargeFlatness	;
		ResultSmallFlatness	=ASrc->ResultSmallFlatness	;
	}
}

static	int	Mergin=8;

ExeResult	Process3DItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(BmpMap!=NULL){
		DeleteMatrixBuff(BmpMap,YLen);
		BmpMap	=NULL;
	}

	MapXPos = GetArea().GetMinX()-Mergin;
	MapYPos = GetArea().GetMinY()-Mergin;
	XLen=GetArea().GetWidth() +Mergin*2;
	YLen=GetArea().GetHeight()+Mergin*2;
	XByte=(XLen+7)/8;
	BmpMap =MakeMatrixBuff(XByte,YLen);

	GetArea().GetCenter(MasterCx,MasterCy);

	MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);

	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	Process3DItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);

	ResultLargeTile		=0;
	ResultLargeFlatness	=0;
	ResultSmallFlatness	=0;
		
	LineContainer.RemoveAll();

	return _ER_true;
}

ExeResult	Process3DItem::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AlgorithmItemPLI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);

	if(GetID()==DbgID)
		DbgNumer++;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	if(GetID()==DbgID && GetParent()->GetLayer()==DbgLayer)
		DbgNumer++;

	const Process3DThreshold	*RThr=GetThresholdR();
	MakeBitVLine(GetTargetBuff(),RThr->BaseCycleDot,mx,my);

	//Bind short line
	int	H=GetArea().GetHeight();
	LineContainer.CreateLines(BmpMap,XByte,YLen ,MapXPos ,MapYPos);
	LineContainer.Regulate();
	for(XYLinesP3D *L=LineContainer.GetFirst();L!=NULL;){
		XYLinesP3D *NextL=L->GetNext();
		if(L->MaxY-L->MinY<H*0.7){
			LineContainer.RemoveList(L);
			int	x,y;
			L->GetMinY(x,y);
			XYLinesP3D *E1=NULL;
			double	DMin=999999999;
			for(XYLinesP3D *e=LineContainer.GetFirst();e!=NULL;e=e->GetNext()){
				double	D=e->GetDistance(x,y);
				if(D<DMin){
					DMin=D;
					E1=e;
				}
			}
			if(DMin<RThr->BaseCycleDot*0.25){
				E1->AppendListPack(*L);
			}
			else{
				L->GetMaxY(x,y);
				XYLinesP3D *E2=NULL;
				double	DMin=999999999;
				for(XYLinesP3D *e=LineContainer.GetFirst();e!=NULL;e=e->GetNext()){
					double	D=e->GetDistance(x,y);
					if(D<DMin){
						DMin=D;
						E2=e;
					}
				}
				if(DMin<RThr->BaseCycleDot*0.25){
					E2->AppendListPack(*L);
				}
				else{
					delete	L;
				}
			}
		}
		else{
			L=NextL;
		}
	}
	LineContainer.CalcInterpolationLine();


	ExeResult	Ret=_ER_true;

	return Ret;
}

int		GetMaxCoeffPos(BYTE	*MultTable , int BaseCycleDot ,int A ,int AA ,int LeftX , int SearchLen
						,int VFilterLength
						,ImageBuffer &IBuff ,int x1 ,int y);

void	Process3DItem::MakeBitVLine(ImageBuffer	&IBuff ,int BaseCycleDot,int mx,int my)
{
	BaseCycleDot	=(BaseCycleDot/2)*2+1;
	if(MultTable!=NULL){
		delete	[]MultTable;
	}
	MultTable=new BYTE[BaseCycleDot];
	int	CenterPos=BaseCycleDot/2;
	for(int i=0;i<BaseCycleDot;i++){
		double	d=(i-CenterPos)/(double)BaseCycleDot*2.0*M_PI;
		MultTable[i]=(BYTE)((cos(d)+1.0)*127.0);
	}
	A=0;
	AA=0;
	for(int i=0;i<BaseCycleDot;i++){
		A +=MultTable[i];
		AA+=MultTable[i]*MultTable[i];
	}
	const Process3DThreshold	*RThr=GetThresholdR();
	int	VFilterLength=RThr->VFilterLength;
	double	SearechArea=0.3;
	int	SearchLen	=BaseCycleDot*SearechArea*2;
	int	AddedLen	=BaseCycleDot*(1.0-SearechArea);
	int	FLineLen	=GetArea().GetFLineLen();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<FLineLen;i++){
			int	y	=GetArea().GetFLineAbsY(i)	+my;
			int	x1	=GetArea().GetFLineLeftX(i)	+mx;
			int	Numb=GetArea().GetFLineNumb(i);

			//Search Left first
			int	FirstSearchLen=BaseCycleDot*1.5;
			int	MaxX=GetMaxCoeffPos(MultTable , BaseCycleDot ,A ,AA ,0, FirstSearchLen
							,VFilterLength
							,IBuff ,x1 ,y);
			int	Ky=y-my-MapYPos;
			int	Kx=x1+MaxX+BaseCycleDot/2 - mx - MapXPos;
			BYTE	*d=NULL;
			if(0<=Ky && Ky<YLen){
				d=BmpMap[Ky];
			}
			if(d!=NULL && 0<=Kx && Kx<XLen){
				SetBmpBitOnY1(d,Kx);
			}
			int	X=MaxX;
			while((X+SearchLen)<Numb){
				X=GetMaxCoeffPos(MultTable , BaseCycleDot ,A ,AA ,X+AddedLen, SearchLen
							,VFilterLength
							,IBuff ,x1 ,y);
				int	Kx=x1+X+BaseCycleDot/2 - mx - MapXPos;
				if(d!=NULL && 0<=Kx && Kx<XLen){
					SetBmpBitOnY1(d,Kx);
				}
			}
		}
	}
}

int		GetMaxCoeffPos(BYTE	*MultTable , int BaseCycleDot ,int A ,int AA ,int LeftX , int SearchLen
						,int VFilterLength
						,ImageBuffer &IBuff ,int x1 ,int y)
{
	double	MaxD=0;
	int	MaxX=-99999999;
	int	MerginY=VFilterLength/2;
	for(int x=LeftX;x<(LeftX+SearchLen);x++){
		int	B=0;
		int	BB=0;
		int	AB=0;
		for(int ty=-MerginY;ty<=MerginY;ty++){
			BYTE	*s=IBuff.GetY(y+ty);
			for(int k=0;k<BaseCycleDot;k++){
				int	c=s[x1+x+k];
				B += c;
				BB+=c*c;
				AB+=c*MultTable[k];
			}
		}
		int	N=(2*MerginY+1)*BaseCycleDot;

		double	DivL=1.0/(double)N;
		double	AvrS=((double)A)/BaseCycleDot;
		double	AvrD=((double)B)*DivL;

		double	K=AB-N*AvrS*AvrD;

		double	M=(2*MerginY+1)*(AA-BaseCycleDot*AvrS*AvrS)*(BB-N*AvrD*AvrD);
		if(M>0){
			M=sqrt(M);
			double	D=K/M;
			if(MaxD<D){
				MaxD=D;
				MaxX=x;
			}
		}
	}
	if(MaxX<0)
		return LeftX;
	return MaxX;
}

void	Process3DItem::CopyArea(Process3DItem &src)
{
	SetArea(src.GetArea());
}

void	Process3DItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	Process3DDrawAttr	*BAttr=dynamic_cast<Process3DDrawAttr *>(Attr);
	if(BAttr!=NULL){

		QColor	SavedColor;
		SavedColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	BAttr->NormalColor=BAttr->BlockColor0;	break;
			case 1:	BAttr->NormalColor=BAttr->BlockColor1;	break;
			case 2:	BAttr->NormalColor=BAttr->BlockColor2;	break;
			case 3:	BAttr->NormalColor=BAttr->BlockColor3;	break;
			case 4:	BAttr->NormalColor=BAttr->BlockColor4;	break;
			case 5:	BAttr->NormalColor=BAttr->BlockColor5;	break;
			case 6:	BAttr->NormalColor=BAttr->BlockColor6;	break;
			case 7:	BAttr->NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		BAttr->NormalColor=SavedColor;

		DrawBitImageOr(pnt, (const BYTE **)BmpMap ,XByte*8 ,XByte ,YLen
					,movx ,movy ,ZoomRate
					,-MapXPos ,-MapYPos
					,Qt::green);

		QPainter	PNT(&pnt);

		LineContainer.DrawLines(PNT,ZoomRate,movx,movy);

	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	Process3DItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false){
				QColor	d=Qt::yellow;
				d.setAlpha(150);
			}
		}
	}
}
