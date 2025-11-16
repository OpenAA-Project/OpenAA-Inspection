/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
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
#include "XYCross.h"
#include "XAlignmentCommon.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==========================================================================================
XAlignmentPointer::XAlignmentPointer(void)
{
	Point=NULL;
	Parent=NULL;
}

XAlignmentPointer &XAlignmentPointer::operator=(XAlignmentPointer &src)
{
	Point	=src.Point;
	Parent	=src.Parent;
	return(*this);
}

bool    XAlignmentPointer::Save(QIODevice *file)
{
	int32	ID=-1;
	if(Point!=NULL)
		ID=Point->GetID();
    if(file->write((const char *)&ID ,sizeof(ID))!=sizeof(ID))
		return(false);
	return(true);
}
bool    XAlignmentPointer::Load(QIODevice *file ,XAlignmentArea *parent)
{
	int32	ID;
    if(file->read((char *)&ID ,sizeof(ID))!=sizeof(ID))
		return(false);
	if(ID!=-1){
		Parent=parent;
		Point=dynamic_cast<XAlignment *>(Parent->ParentInLayer->SearchIDItem(ID));
	}
	return(true);
}

DataInLayer	*XAlignmentPointer::GetDataInLayer(void)
{
	return(Point->GetDataInLayer());
}
//==========================================================================================
XAlignmentArea::XAlignmentArea(void)
{
	MaxSearchAreaFromItem=0;
    AreaID			=-1;
	Priority		=_PriorityMiddle;
	ParentInLayer	=NULL;
	PartsID			=-1;
	PartsAllocID	=-1;
	PartsAreaID		=-1;
	Locked			=false;
	Selected		=false;
	Active			=false;
	ManualCreated	=false;
	Visible			=true;
	Origin			=NULL;
}
XAlignmentArea::XAlignmentArea(AlignmentInLayer	*parentInLayer)
{
	MaxSearchAreaFromItem=0;
	AreaID			=-1;
	Priority		=_PriorityMiddle;
	ParentInLayer	=parentInLayer;
	PartsID			=-1;
	PartsAllocID	=-1;
	PartsAreaID		=-1;
	Locked			=false;
	Selected		=false;
	Active			=false;
	ManualCreated	=false;
	Visible			=true;
	Origin			=NULL;
}

XAlignmentArea	&XAlignmentArea::operator=(XAlignmentArea &src)
{
	if(this!=&src){
		CopyWithoutItems(src,false);
		GPack.RemoveAll();
		for(XAlignmentPointer *g=src.GPack.GetFirst();g!=NULL;g=g->GetNext()){
			XAlignmentPointer *h=new XAlignmentPointer();
			h->Parent=this;
			h->Point=new XAlignment();
			*h->Point = *g->Point;
			GPack.AppendList(h);
		}
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

XAlignmentArea  &XAlignmentArea::CopyWithoutItems(XAlignmentArea &src,bool ReferedMode)
{
	MaxSearchAreaFromItem	=src.MaxSearchAreaFromItem;
    AreaID		=src.AreaID;
	Priority	=src.Priority;
	if(ReferedMode==true)
		Area.SetRefereneFrom(&src.Area);
	else
		Area		=src.Area;

	for(int i=0;i<sizeof(CalcedParam)/sizeof(CalcedParam[0]);i++){
		CalcedParam[i]	=src.CalcedParam[i];
	}
	for(int i=0;i<sizeof(ALResult)/sizeof(ALResult[0]);i++){
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

void    XAlignmentArea::MoveTo(int dx ,int dy)
{
	if(Locked==false){
		Area.MoveToNoClip(dx,dy);
		for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
			g->Point->MoveTo(dx,dy);
		}
	}
}
void    XAlignmentArea::Initial(ImageBuffer &IBuff)
{
	for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
		g->Point->MakeArea(g->Point->GetThresholdR(ParentInLayer->GetLayersBase())->Threshold ,IBuff);
	}
}

void	XAlignmentArea::RemoveItem(AlgorithmItemPLI *item)
{
	XAlignment	*L=dynamic_cast<XAlignment *>(item);
	if(L!=NULL){
QNext:;
		for(XAlignmentPointer *a=GPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Point==L){
				GPack.RemoveList(a);
				delete	a;
				goto	QNext;
			}
		}
	}
}

XAlignmentArea::AlignmentResultClass	&XAlignmentArea::AlignmentResultClass::operator=(XAlignmentArea::AlignmentResultClass &src)
{
	AlignmentResult[0]=src.AlignmentResult[0];
	AlignmentResult[1]=src.AlignmentResult[1];
	AlignmentResult[2]=src.AlignmentResult[2];
	AlignmentResult[3]=src.AlignmentResult[3];
	AlignmentResult[4]=src.AlignmentResult[4];
	AlignmentResult[5]=src.AlignmentResult[5];
	Cx=src.Cx;
	Cy=src.Cy;
	return *this;
}

void    XAlignmentArea::GetCenter(int &cx, int &cy)
{
	Area.GetCenter(cx,cy);
}
void	XAlignmentArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentBase	*pbase=dynamic_cast<AlignmentBase *>(ParentInLayer->GetParentBase());
	if(pbase!=NULL){
		AlignmentDrawAttr	*LAttr=dynamic_cast<AlignmentDrawAttr *>(Attr);
		int	globalPage=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(ParentInLayer->GetPage());
		if(LAttr!=NULL && LAttr->DrawKind==AlignmentDrawAttr::_Area
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
			}
		}
		else if(LAttr!=NULL){
			if(LAttr->AList.GetNumber()==0 || LAttr->AList.Exists(globalPage,ParentInLayer->GetLayer(),AreaID)==true){
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
				}
			}
		}
		else{
			for(XAlignmentPointer *p=GPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
}
void	XAlignmentArea::DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentBase	*pbase=dynamic_cast<AlignmentBase *>(ParentInLayer->GetParentBase());
	if(pbase!=NULL){
		AlignmentDrawAttr	*LAttr=dynamic_cast<AlignmentDrawAttr *>(Attr);
		if(LAttr!=NULL && LAttr->DrawKind==AlignmentDrawAttr::_Area){
		}
		else if(LAttr!=NULL){
			Attr->NormalColor=pbase->ColorPoint;
			Attr->NormalColor.setAlpha(pbase->AlphaLevel);
			Attr->SelectedColor	=pbase->ColorPointSelected;
			Attr->SelectedColor.setAlpha(pbase->AlphaLevel);
			Attr->ActiveColor	=pbase->ColorPointActive;
			Attr->ActiveColor.setAlpha(pbase->AlphaLevel);
			for(XAlignmentPointer *p=GPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
		else{
			for(XAlignmentPointer *p=GPack.GetFirst();p!=NULL;p=p->GetNext()){
				p->Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
}

void	XAlignmentArea::DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(Selected==true && Locked==false){
		Area.Draw(dx,dy ,&pnt ,Col.rgba(),ZoomRate ,movx ,movy);
	}
}

void	XAlignmentArea::Calc(ImageBuffer &IData
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	GInfoCount=0;
	GroupMode=false;
	MaxSearchAreaFromItem=0;
	for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->Point->GroupNumber>0)
			GroupMode=true;
		if(g->Point->GetThresholdR(ParentInLayer->GetLayersBase())->MoveDot*2>MaxSearchAreaFromItem)
			MaxSearchAreaFromItem=g->Point->GetThresholdR(ParentInLayer->GetLayersBase())->MoveDot*2;
	}
	if(GroupMode==true){
		for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
			int	i;
			for(i=0;i<GInfoCount;i++){
				if(GInfo[i].GroupNumber==g->Point->GroupNumber){
					GInfo[i].SrcX+=g->Point->MasterX;
					GInfo[i].SrcY+=g->Point->MasterY;
					GInfo[i].GroupCount++;
					GInfo[i].Dx	+=g->Point->CalcedX - g->Point->MasterX;
					GInfo[i].Dy	+=g->Point->CalcedY - g->Point->MasterY;
					break;
				}
			}
			if(i>=GInfoCount){
				if(GInfoCount>=sizeof(GInfo)/sizeof(GInfo[0]))
					return;
				GInfo[GInfoCount].SrcX=g->Point->MasterX;
				GInfo[GInfoCount].SrcY=g->Point->MasterY;
				GInfo[GInfoCount].GroupCount=1;
				GInfo[GInfoCount].Dx	=g->Point->CalcedX - g->Point->MasterX;
				GInfo[GInfoCount].Dy	=g->Point->CalcedY - g->Point->MasterY;
				GInfoCount++;
			}
		}
	}
	else{
		for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
			if(GInfoCount>=sizeof(GInfo)/sizeof(GInfo[0]))
				return;
			GInfo[GInfoCount].SrcX=g->Point->MasterX;
			GInfo[GInfoCount].SrcY=g->Point->MasterY;
			GInfo[GInfoCount].GroupCount=1;
			GInfo[GInfoCount].Dx	=g->Point->CalcedX - g->Point->MasterX;
			GInfo[GInfoCount].Dy	=g->Point->CalcedY - g->Point->MasterY;
			GInfoCount++;
		}
	}
	int	page=ParentInLayer->GetPage();
	int	CurrentGlobalPage	=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(page);
	for(AlignmentShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
		if(GInfoCount>=sizeof(GInfo)/sizeof(GInfo[0]))
			return;
		if(MaxSearchAreaFromItem==0){
			MaxSearchAreaFromItem=1000;
		}
		GInfo[GInfoCount].SrcX=d->MasterX	+ParentInLayer->GetLayersBase()->GetGlobalOutlineOffset(d->GlobalPage)->x 
											-ParentInLayer->GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->x;
		GInfo[GInfoCount].SrcY=d->MasterY	+ParentInLayer->GetLayersBase()->GetGlobalOutlineOffset(d->GlobalPage)->y 
											-ParentInLayer->GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->y;
		GInfo[GInfoCount].GroupCount=1;
		GInfo[GInfoCount].Dx	=d->ShiftX;
		GInfo[GInfoCount].Dy	=d->ShiftY;
		GInfoCount++;
	}

	for(int i=0;i<GInfoCount;i++){
		GInfo[i].SrcX/=GInfo[i].GroupCount;
		GInfo[i].SrcY/=GInfo[i].GroupCount;
		GInfo[i].Dx/=GInfo[i].GroupCount;
		GInfo[i].Dy/=GInfo[i].GroupCount;
	}
    if(GInfoCount==0){
		Calc0(MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
		ResultPointCounts=_Aligned0;
	}
    if(GInfoCount==1){
		Calc1(GInfo ,MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
		ResultPointCounts=_Aligned1;
	}
    else if(GInfoCount==2){
		Calc2(GInfo ,MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes);
		ResultPointCounts=_Aligned2;
	}
    else if(GInfoCount>=3){
		if(Calc3(GInfo ,MVector
				,MVectorXNumb,MVectorYNumb
				,MVectorXRes ,MVectorYRes)==true){
			ResultPointCounts=_Aligned3;
		}
	}
    else if(GInfoCount>=4){
		Calc4(GInfo ,MVector
			,MVectorXNumb,MVectorYNumb
			,MVectorXRes ,MVectorYRes);
		ResultPointCounts=_Aligned4;
	}
}

int		XAlignmentArea::GetCalcedItemCount(void)
{
	int	N=0;
	for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->Point->CalcedX!=0.0 || g->Point->CalcedY!=0.0)
			N++;
	}
	return N;
}

XAlignmentArea::AlignmentPointCount	XAlignmentArea::GetResultInPoint(int localX ,int localY)
{
	if(Area.IsInclude(localX ,localY)==true)
		return ResultPointCounts;
	return _Aligned0;
}

bool	XAlignmentArea::GetAlignment(AlignmentPacket2D &AData)
{
    if(GInfoCount==0){
		AData.ShiftX=AData.ShiftY=0;
		AData.Calculated=true;
		return true;
	}
    if(GInfoCount==1){
		AData.ShiftX=GInfo[0].Dx/2;
		AData.ShiftY=GInfo[0].Dy/2;
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
    else if(GInfoCount==2){
		double  s1=GetSita(GInfo[1].SrcX-GInfo[0].SrcX
		                  ,GInfo[1].SrcY-GInfo[0].SrcY);
	    double  s2=GetSita(GInfo[1].SrcX+GInfo[1].Dx-(GInfo[0].SrcX+GInfo[0].Dx)
						  ,GInfo[1].SrcY+GInfo[1].Dy-(GInfo[0].SrcY+GInfo[0].Dy));

		double  s=s2-s1;
		double  cx=(GInfo[1].SrcX+GInfo[0].SrcX)/2;
		double  cy=(GInfo[1].SrcY+GInfo[0].SrcY)/2;
		double	dx=(GInfo[1].Dx-GInfo[0].Dx)/2;
		double	dy=(GInfo[1].Dy-GInfo[0].Dy)/2;

		double  sins=sin(s);
		double  coss=cos(s);

		double  ix= (AData.PosXOnTarget-cx)*coss-(AData.PosYOnTarget-cy)*sins+cx+dx;
		double  iy= (AData.PosXOnTarget-cx)*sins+(AData.PosYOnTarget-cy)*coss+cy+dy;
		AData.ShiftX=ix-AData.PosXOnTarget;
		AData.ShiftY=iy-AData.PosYOnTarget;
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
    else if(GInfoCount>=3){
		AData.ShiftX=AData.PosXOnTarget*ALResult[0].AlignmentResult[0]+AData.PosYOnTarget*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2]-AData.PosXOnTarget;
		AData.ShiftY=AData.PosXOnTarget*ALResult[0].AlignmentResult[3]+AData.PosYOnTarget*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5]-AData.PosYOnTarget;
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
    else if(GInfoCount>=4){
		double	L1=hypot(AData.PosXOnTarget-ALResult[0].Cx,AData.PosYOnTarget-ALResult[0].Cy);
		double	L2=hypot(AData.PosXOnTarget-ALResult[1].Cx,AData.PosYOnTarget-ALResult[1].Cy);
		double	L3=hypot(AData.PosXOnTarget-ALResult[2].Cx,AData.PosYOnTarget-ALResult[2].Cy);
		double	L4=hypot(AData.PosXOnTarget-ALResult[3].Cx,AData.PosYOnTarget-ALResult[3].Cy);
		if(L1<=L2 && L1<=L3 && L1<=L4){
			AData.ShiftX=AData.PosXOnTarget*ALResult[0].AlignmentResult[0]+AData.PosYOnTarget*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2]-AData.PosXOnTarget;
			AData.ShiftY=AData.PosXOnTarget*ALResult[0].AlignmentResult[3]+AData.PosYOnTarget*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5]-AData.PosYOnTarget;
		}
		else if(L2<=L1 && L2<=L3 && L2<=L4){
			AData.ShiftX=AData.PosXOnTarget*ALResult[1].AlignmentResult[0]+AData.PosYOnTarget*ALResult[1].AlignmentResult[1]+ALResult[1].AlignmentResult[2]-AData.PosXOnTarget;
			AData.ShiftY=AData.PosXOnTarget*ALResult[1].AlignmentResult[3]+AData.PosYOnTarget*ALResult[1].AlignmentResult[4]+ALResult[1].AlignmentResult[5]-AData.PosYOnTarget;
		}
		else if(L3<=L1 && L3<=L2 && L3<=L4){
			AData.ShiftX=AData.PosXOnTarget*ALResult[2].AlignmentResult[0]+AData.PosYOnTarget*ALResult[2].AlignmentResult[1]+ALResult[2].AlignmentResult[2]-AData.PosXOnTarget;
			AData.ShiftY=AData.PosXOnTarget*ALResult[2].AlignmentResult[3]+AData.PosYOnTarget*ALResult[2].AlignmentResult[4]+ALResult[2].AlignmentResult[5]-AData.PosYOnTarget;
		}
		else if(L4<=L1 && L4<=L2 && L4<=L3){
			AData.ShiftX=AData.PosXOnTarget*ALResult[3].AlignmentResult[0]+AData.PosYOnTarget*ALResult[3].AlignmentResult[1]+ALResult[3].AlignmentResult[2]-AData.PosXOnTarget;
			AData.ShiftY=AData.PosXOnTarget*ALResult[3].AlignmentResult[3]+AData.PosYOnTarget*ALResult[3].AlignmentResult[4]+ALResult[3].AlignmentResult[5]-AData.PosYOnTarget;
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

bool	XAlignmentArea::Calc0(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	if(MVector!=NULL){
		for(int i=0;i<Area.GetFLineLen();i++){
			int y =Area.GetFLineAbsY  (i);
			if((y%MVectorYRes)!=0)
				continue;
			y=y/MVectorYRes;
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
	ALResult[0].AlignmentResult[0]=1;
	ALResult[0].AlignmentResult[1]=0;
	ALResult[0].AlignmentResult[2]=0;
	ALResult[0].AlignmentResult[3]=0;
	ALResult[0].AlignmentResult[4]=1;
	ALResult[0].AlignmentResult[5]=0;
	return(true);
}
bool	XAlignmentArea::Calc1(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	int Mx=GInfo[0].Dx;
	int My=GInfo[0].Dy;

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
	AlignmentInPage	*ap=(AlignmentInPage *)ParentInLayer->GetParentInPage();
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999){
			if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
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
			if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
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
CNext:;
	ALResult[0].AlignmentResult[0]=1;
	ALResult[0].AlignmentResult[1]=0;
	ALResult[0].AlignmentResult[2]=Mx;
	ALResult[0].AlignmentResult[3]=0;
	ALResult[0].AlignmentResult[4]=1;
	ALResult[0].AlignmentResult[5]=My;
	return(true);
}
bool	XAlignmentArea::Calc2(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	double  qx1=GInfo[0].SrcX;
	double  qy1=GInfo[0].SrcY;
	double  qX1=GInfo[0].SrcX+GInfo[0].Dx;
	double  qY1=GInfo[0].SrcY+GInfo[0].Dy;
	double  qx2=GInfo[1].SrcX;
	double  qy2=GInfo[1].SrcY;
	double  qX2=GInfo[1].SrcX+GInfo[1].Dx;
	double  qY2=GInfo[1].SrcY+GInfo[1].Dy;

	double  dx=qx1-qx2;
	double  dy=qy1-qy2;
	double  dX=qX1-qX2;
	double  dY=qY1-qY2;

	double	K=dX*dy-dY*dx;
	double	H=dY*dy+dX*dx;
	double	s=atan(K/H);
	double	mA=dX/(dx*cos(s)+dy*sin(s));

	ALResult[0].AlignmentResult[0]=mA*cos(s);
	ALResult[0].AlignmentResult[1]=mA*sin(s);
	ALResult[0].AlignmentResult[2]=qX1-mA*qx1*cos(s)-mA*qy1*sin(s);
	ALResult[0].AlignmentResult[3]=-mA*sin(s);
	ALResult[0].AlignmentResult[4]=mA*cos(s);
	ALResult[0].AlignmentResult[5]=qY1+mA*qx1*sin(s)-mA*qy1*cos(s);

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
				MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*ALResult[0].AlignmentResult[0]+my*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2])-mx);
				MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*ALResult[0].AlignmentResult[3]+my*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5])-my);
			}
		}
	}
	AlignmentInPage	*ap=(AlignmentInPage *)ParentInLayer->GetParentInPage();

	int	AlignmentPacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList **PList=new AlignmentPacket2DList *[AlignmentPacket2ContainerNumb];
	int	N=0;
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentPacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
					&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
					p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentResult[0]+p->PosYOnTarget*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentResult[3]+p->PosYOnTarget*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5]-p->PosYOnTarget;
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
		for(int i=0;i<AlignmentPacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
					p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentResult[0]+p->PosYOnTarget*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentResult[3]+p->PosYOnTarget*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5]-p->PosYOnTarget;
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
	delete	[]PList;

	/*
	double  s1=GetSita(GInfo[1].SrcX-GInfo[0].SrcX
                      ,GInfo[1].SrcY-GInfo[0].SrcY);
    double  s2=GetSita(GInfo[1].SrcX+GInfo[1].Dx-(GInfo[0].SrcX+GInfo[0].Dx)
					  ,GInfo[1].SrcY+GInfo[1].Dy-(GInfo[0].SrcY+GInfo[0].Dy));

	double  s=s2-s1;
	double  cx=(GInfo[1].SrcX+GInfo[0].SrcX)/2;
	double  cy=(GInfo[1].SrcY+GInfo[0].SrcY)/2;
	double	dx=(GInfo[1].Dx+GInfo[0].Dx)/2;
	double	dy=(GInfo[1].Dy+GInfo[0].Dy)/2;

	double  sins=sin(s);
	double  coss=cos(s);

	if(MVector!=NULL){
		for(int i=0;i<Area.GetFLineLen();i++){
			int y =Area.GetFLineAbsY  (i);
			if((y%MVectorYRes)!=0)
				continue;
			y=y/MVectorYRes;
			int x1=Area.GetFLineLeftX (i);
			int x2=Area.GetFLineRightX(i);
			x1=x1/MVectorXRes;
			x2=(x2+MVectorXRes-1)/MVectorXRes;
			if(x1<0)
				x1=0;
			if(x2>=MVectorXNumb)
				x2=MVectorXNumb;
			for(int x=x1;x<x2;x++){
				int	mx=x*MVectorXRes;
				int	my=x*MVectorXRes;
				double  ix= (mx-cx)*coss-(my-cy)*sins+cx+dx;
				double  iy= (mx-cx)*sins+(my-cy)*coss+cy+dy;
				MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(ix-mx));
				MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(iy-my));
			}
		}
	}
	AlignmentInPage	*ap=(AlignmentInPage *)ParentInLayer->GetParentInPage();
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999){
			if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
				&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
				p->ShiftX=(p->PosXOnTarget-cx)*coss-(p->PosYOnTarget-cy)*sins+cx+dx - p->PosXOnTarget;
				p->ShiftY=(p->PosXOnTarget-cx)*sins+(p->PosYOnTarget-cy)*coss+cy+dy - p->PosYOnTarget;
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
			if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
				p->ShiftX=(p->PosXOnTarget-cx)*coss-(p->PosYOnTarget-cy)*sins+cx+dx - p->PosXOnTarget;
				p->ShiftY=(p->PosXOnTarget-cx)*sins+(p->PosYOnTarget-cy)*coss+cy+dy - p->PosYOnTarget;
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
CNext:;
	AlignmentResult[0]=cos(s);
	AlignmentResult[1]=sin(s);
	AlignmentResult[2]=GInfo[0].Dx;
	AlignmentResult[3]=-sin(s);
	AlignmentResult[4]=cos(s);
	AlignmentResult[5]=GInfo[0].Dy;
	*/
	return true;
}
bool	XAlignmentArea::Calc3(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	double  PP[3][2];
	double  PQ[3][2];
	PP[0][0]=GInfo[0].SrcX;
	PP[0][1]=GInfo[0].SrcY;
	PP[1][0]=GInfo[1].SrcX;
	PP[1][1]=GInfo[1].SrcY;
	PP[2][0]=GInfo[2].SrcX;
	PP[2][1]=GInfo[2].SrcY;

	PQ[0][0]=GInfo[0].SrcX+GInfo[0].Dx;
	PQ[0][1]=GInfo[0].SrcY+GInfo[0].Dy;
	PQ[1][0]=GInfo[1].SrcX+GInfo[1].Dx;
	PQ[1][1]=GInfo[1].SrcY+GInfo[1].Dy;
	PQ[2][0]=GInfo[2].SrcX+GInfo[2].Dx;
	PQ[2][1]=GInfo[2].SrcY+GInfo[2].Dy;
	double  m[6];
	if(Get3LevelResolve(PP , PQ ,m)==false)
		return(false);

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
				MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*m[0]+my*m[1]+m[2])-mx);
				MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*m[3]+my*m[4]+m[5])-my);
			}
		}
	}
	AlignmentInPage	*ap=(AlignmentInPage *)ParentInLayer->GetParentInPage();

	int	AlignmentPacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList **PList=new AlignmentPacket2DList *[AlignmentPacket2ContainerNumb];
	int	N=0;
	for(AlignmentPacket2DList *p=ap->AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext(),N++){
		PList[N]=p;
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<AlignmentPacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
					&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){
					p->ShiftX=p->PosXOnTarget*m[0]+p->PosYOnTarget*m[1]+m[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*m[3]+p->PosYOnTarget*m[4]+m[5]-p->PosYOnTarget;
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
		for(int i=0;i<AlignmentPacket2ContainerNumb;i++){
			AlignmentPacket2DList *p=PList[i];
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
					p->ShiftX=p->PosXOnTarget*m[0]+p->PosYOnTarget*m[1]+m[2]-p->PosXOnTarget;
					p->ShiftY=p->PosXOnTarget*m[3]+p->PosYOnTarget*m[4]+m[5]-p->PosYOnTarget;
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
	delete	[]PList;
CNext:;
	ALResult[0].AlignmentResult[0]=m[0];
	ALResult[0].AlignmentResult[1]=m[1];
	ALResult[0].AlignmentResult[2]=m[2];
	ALResult[0].AlignmentResult[3]=m[3];
	ALResult[0].AlignmentResult[4]=m[4];
	ALResult[0].AlignmentResult[5]=m[5];
	return(true);
}
	
bool	XAlignmentArea::Calc4(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes)
{
	double  PP[3][2];
	double  PQ[3][2];
	double  m[6];

	PP[0][0]=GInfo[0].SrcX;
	PP[0][1]=GInfo[0].SrcY;
	PP[1][0]=GInfo[1].SrcX;
	PP[1][1]=GInfo[1].SrcY;
	PP[2][0]=GInfo[2].SrcX;
	PP[2][1]=GInfo[2].SrcY;

	PQ[0][0]=GInfo[0].SrcX+GInfo[0].Dx;
	PQ[0][1]=GInfo[0].SrcY+GInfo[0].Dy;
	PQ[1][0]=GInfo[1].SrcX+GInfo[1].Dx;
	PQ[1][1]=GInfo[1].SrcY+GInfo[1].Dy;
	PQ[2][0]=GInfo[2].SrcX+GInfo[2].Dx;
	PQ[2][1]=GInfo[2].SrcY+GInfo[2].Dy;
	if(Get3LevelResolve(PP , PQ ,m)==false)
		return(false);

	ALResult[0].AlignmentResult[0]=m[0];
	ALResult[0].AlignmentResult[1]=m[1];
	ALResult[0].AlignmentResult[2]=m[2];
	ALResult[0].AlignmentResult[3]=m[3];
	ALResult[0].AlignmentResult[4]=m[4];
	ALResult[0].AlignmentResult[5]=m[5];
	ALResult[0].Cx=(GInfo[0].SrcX+GInfo[1].SrcX+GInfo[2].SrcX)/3;
	ALResult[0].Cy=(GInfo[0].SrcY+GInfo[1].SrcY+GInfo[2].SrcY)/3;


	PP[0][0]=GInfo[1].SrcX;
	PP[0][1]=GInfo[1].SrcY;
	PP[1][0]=GInfo[2].SrcX;
	PP[1][1]=GInfo[2].SrcY;
	PP[2][0]=GInfo[3].SrcX;
	PP[2][1]=GInfo[3].SrcY;

	PQ[0][0]=GInfo[1].SrcX+GInfo[1].Dx;
	PQ[0][1]=GInfo[1].SrcY+GInfo[1].Dy;
	PQ[1][0]=GInfo[2].SrcX+GInfo[2].Dx;
	PQ[1][1]=GInfo[2].SrcY+GInfo[2].Dy;
	PQ[2][0]=GInfo[3].SrcX+GInfo[3].Dx;
	PQ[2][1]=GInfo[3].SrcY+GInfo[3].Dy;
	if(Get3LevelResolve(PP , PQ ,m)==false)
		return(false);

	ALResult[1].AlignmentResult[0]=m[0];
	ALResult[1].AlignmentResult[1]=m[1];
	ALResult[1].AlignmentResult[2]=m[2];
	ALResult[1].AlignmentResult[3]=m[3];
	ALResult[1].AlignmentResult[4]=m[4];
	ALResult[1].AlignmentResult[5]=m[5];
	ALResult[1].Cx=(GInfo[1].SrcX+GInfo[2].SrcX+GInfo[3].SrcX)/3;
	ALResult[1].Cy=(GInfo[1].SrcY+GInfo[2].SrcY+GInfo[3].SrcY)/3;

	PP[0][0]=GInfo[0].SrcX;
	PP[0][1]=GInfo[0].SrcY;
	PP[1][0]=GInfo[2].SrcX;
	PP[1][1]=GInfo[2].SrcY;
	PP[2][0]=GInfo[3].SrcX;
	PP[2][1]=GInfo[3].SrcY;

	PQ[0][0]=GInfo[0].SrcX+GInfo[0].Dx;
	PQ[0][1]=GInfo[0].SrcY+GInfo[0].Dy;
	PQ[1][0]=GInfo[2].SrcX+GInfo[2].Dx;
	PQ[1][1]=GInfo[2].SrcY+GInfo[2].Dy;
	PQ[2][0]=GInfo[3].SrcX+GInfo[3].Dx;
	PQ[2][1]=GInfo[3].SrcY+GInfo[3].Dy;
	if(Get3LevelResolve(PP , PQ ,m)==false)
		return(false);

	ALResult[2].AlignmentResult[0]=m[0];
	ALResult[2].AlignmentResult[1]=m[1];
	ALResult[2].AlignmentResult[2]=m[2];
	ALResult[2].AlignmentResult[3]=m[3];
	ALResult[2].AlignmentResult[4]=m[4];
	ALResult[2].AlignmentResult[5]=m[5];
	ALResult[2].Cx=(GInfo[0].SrcX+GInfo[2].SrcX+GInfo[3].SrcX)/3;
	ALResult[2].Cy=(GInfo[0].SrcY+GInfo[2].SrcY+GInfo[3].SrcY)/3;


	PP[0][0]=GInfo[0].SrcX;
	PP[0][1]=GInfo[0].SrcY;
	PP[1][0]=GInfo[1].SrcX;
	PP[1][1]=GInfo[1].SrcY;
	PP[2][0]=GInfo[3].SrcX;
	PP[2][1]=GInfo[3].SrcY;

	PQ[0][0]=GInfo[0].SrcX+GInfo[0].Dx;
	PQ[0][1]=GInfo[0].SrcY+GInfo[0].Dy;
	PQ[1][0]=GInfo[1].SrcX+GInfo[1].Dx;
	PQ[1][1]=GInfo[1].SrcY+GInfo[1].Dy;
	PQ[2][0]=GInfo[3].SrcX+GInfo[3].Dx;
	PQ[2][1]=GInfo[3].SrcY+GInfo[3].Dy;
	if(Get3LevelResolve(PP , PQ ,m)==false)
		return(false);

	ALResult[3].AlignmentResult[0]=m[0];
	ALResult[3].AlignmentResult[1]=m[1];
	ALResult[3].AlignmentResult[2]=m[2];
	ALResult[3].AlignmentResult[3]=m[3];
	ALResult[3].AlignmentResult[4]=m[4];
	ALResult[3].AlignmentResult[5]=m[5];
	ALResult[3].Cx=(GInfo[0].SrcX+GInfo[1].SrcX+GInfo[3].SrcX)/3;
	ALResult[3].Cy=(GInfo[0].SrcY+GInfo[1].SrcY+GInfo[3].SrcY)/3;


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

				double	L1=hypot(mx-ALResult[0].Cx,my-ALResult[0].Cy);
				double	L2=hypot(mx-ALResult[1].Cx,my-ALResult[1].Cy);
				double	L3=hypot(mx-ALResult[2].Cx,my-ALResult[2].Cy);
				double	L4=hypot(mx-ALResult[3].Cx,my-ALResult[3].Cy);
				if(L1<=L2 && L1<=L3 && L1<=L4){
					MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*ALResult[0].AlignmentResult[0]+my*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2])-mx);
					MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*ALResult[0].AlignmentResult[3]+my*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5])-my);
				}
				else if(L2<=L1 && L2<=L3 && L2<=L4){
					MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*ALResult[1].AlignmentResult[0]+my*ALResult[1].AlignmentResult[1]+ALResult[1].AlignmentResult[2])-mx);
					MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*ALResult[1].AlignmentResult[3]+my*ALResult[1].AlignmentResult[4]+ALResult[1].AlignmentResult[5])-my);
				}
				else if(L3<=L1 && L3<=L2 && L3<=L4){
					MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*ALResult[2].AlignmentResult[0]+my*ALResult[2].AlignmentResult[1]+ALResult[2].AlignmentResult[2])-mx);
					MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*ALResult[2].AlignmentResult[3]+my*ALResult[2].AlignmentResult[4]+ALResult[2].AlignmentResult[5])-my);
				}
				else if(L4<=L1 && L4<=L2 && L4<=L3){
					MVector[y*MVectorXNumb+x].setX(GetHalfUpDown(mx*ALResult[3].AlignmentResult[0]+my*ALResult[3].AlignmentResult[1]+ALResult[3].AlignmentResult[2])-mx);
					MVector[y*MVectorXNumb+x].setY(GetHalfUpDown(mx*ALResult[3].AlignmentResult[3]+my*ALResult[3].AlignmentResult[4]+ALResult[3].AlignmentResult[5])-my);
				}
			}
		}
	}
	AlignmentInPage	*ap=(AlignmentInPage *)ParentInLayer->GetParentInPage();

	int	AlignmentLargePacket2ContainerNumb=ap->AlignmentPacket2DContainer.GetNumber();
	AlignmentPacket2DList **PList=new AlignmentPacket2DList *[AlignmentLargePacket2ContainerNumb];
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
				if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true
					&& LimitedLib.SearchLibrary(p->LibType,p->LibID)!=NULL){

					double	L1=hypot(p->PosXOnTarget-ALResult[0].Cx,p->PosYOnTarget-ALResult[0].Cy);
					double	L2=hypot(p->PosXOnTarget-ALResult[1].Cx,p->PosYOnTarget-ALResult[1].Cy);
					double	L3=hypot(p->PosXOnTarget-ALResult[2].Cx,p->PosYOnTarget-ALResult[2].Cy);
					double	L4=hypot(p->PosXOnTarget-ALResult[3].Cx,p->PosYOnTarget-ALResult[3].Cy);
					if(L1<=L2 && L1<=L3 && L1<=L4){
						p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentResult[0]+p->PosYOnTarget*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentResult[3]+p->PosYOnTarget*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5]-p->PosYOnTarget;
					}
					else if(L2<=L1 && L2<=L3 && L2<=L4){
						p->ShiftX=p->PosXOnTarget*ALResult[1].AlignmentResult[0]+p->PosYOnTarget*ALResult[1].AlignmentResult[1]+ALResult[1].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[1].AlignmentResult[3]+p->PosYOnTarget*ALResult[1].AlignmentResult[4]+ALResult[1].AlignmentResult[5]-p->PosYOnTarget;
					}
					else if(L3<=L1 && L3<=L2 && L3<=L4){
						p->ShiftX=p->PosXOnTarget*ALResult[2].AlignmentResult[0]+p->PosYOnTarget*ALResult[2].AlignmentResult[1]+ALResult[2].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[2].AlignmentResult[3]+p->PosYOnTarget*ALResult[2].AlignmentResult[4]+ALResult[2].AlignmentResult[5]-p->PosYOnTarget;
					}
					else if(L4<=L1 && L4<=L2 && L4<=L3){
						p->ShiftX=p->PosXOnTarget*ALResult[3].AlignmentResult[0]+p->PosYOnTarget*ALResult[3].AlignmentResult[1]+ALResult[3].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[3].AlignmentResult[3]+p->PosYOnTarget*ALResult[3].AlignmentResult[4]+ALResult[3].AlignmentResult[5]-p->PosYOnTarget;
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
			if(p->ShiftX==99999999 && p->ShiftY==99999999){
				if(Area.IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
					double	L1=hypot(p->PosXOnTarget-ALResult[0].Cx,p->PosYOnTarget-ALResult[0].Cy);
					double	L2=hypot(p->PosXOnTarget-ALResult[1].Cx,p->PosYOnTarget-ALResult[1].Cy);
					double	L3=hypot(p->PosXOnTarget-ALResult[2].Cx,p->PosYOnTarget-ALResult[2].Cy);
					double	L4=hypot(p->PosXOnTarget-ALResult[3].Cx,p->PosYOnTarget-ALResult[3].Cy);
					if(L1<=L2 && L1<=L3 && L1<=L4){
						p->ShiftX=p->PosXOnTarget*ALResult[0].AlignmentResult[0]+p->PosYOnTarget*ALResult[0].AlignmentResult[1]+ALResult[0].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[0].AlignmentResult[3]+p->PosYOnTarget*ALResult[0].AlignmentResult[4]+ALResult[0].AlignmentResult[5]-p->PosYOnTarget;
					}
					else if(L2<=L1 && L2<=L3 && L2<=L4){
						p->ShiftX=p->PosXOnTarget*ALResult[1].AlignmentResult[0]+p->PosYOnTarget*ALResult[1].AlignmentResult[1]+ALResult[1].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[1].AlignmentResult[3]+p->PosYOnTarget*ALResult[1].AlignmentResult[4]+ALResult[1].AlignmentResult[5]-p->PosYOnTarget;
					}
					else if(L3<=L1 && L3<=L2 && L3<=L4){
						p->ShiftX=p->PosXOnTarget*ALResult[2].AlignmentResult[0]+p->PosYOnTarget*ALResult[2].AlignmentResult[1]+ALResult[2].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[2].AlignmentResult[3]+p->PosYOnTarget*ALResult[2].AlignmentResult[4]+ALResult[2].AlignmentResult[5]-p->PosYOnTarget;
					}
					else if(L4<=L1 && L4<=L2 && L4<=L3){
						p->ShiftX=p->PosXOnTarget*ALResult[3].AlignmentResult[0]+p->PosYOnTarget*ALResult[3].AlignmentResult[1]+ALResult[3].AlignmentResult[2]-p->PosXOnTarget;
						p->ShiftY=p->PosXOnTarget*ALResult[3].AlignmentResult[3]+p->PosYOnTarget*ALResult[3].AlignmentResult[4]+ALResult[3].AlignmentResult[5]-p->PosYOnTarget;
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
	delete	[]PList;
CNext:;
	return(true);
}

void	XAlignmentArea::SetGroup(FlexArea &area ,int groupNumber)
{
	for(XAlignmentPointer *a=GPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(area.IsInclude(&a->Point->GetArea())==true){
			a->Point->GroupNumber=groupNumber;
		}
	}
}

bool	XAlignmentArea::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	if(GPack.GetCount()<3){
		OtherPack.RemoveAll();
		int	page=ParentInLayer->GetPage();
		int	CurrentGlobalPage	=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(page);
		for(int globalpage=0;globalpage<ParentInLayer->GetLayersBase()->GetGlobalPageNumb();globalpage++){
			if(CurrentGlobalPage==globalpage){
				continue;
			}
			SlaveCommReqAlignmentPoint	RCmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
			SlaveCommAckAlignmentPoint	ACmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
			RCmd.Layer	=ParentInLayer->GetLayer();
			RCmd.AreaID	=AreaID;
			RCmd.AreaName	=AreaName;
			if(RCmd.Send(globalpage,0,ACmd)==true){
				if(ACmd.AlignmentPointData.IsEmpty()==false){
					OtherPack+=ACmd.AlignmentPointData;
				}
			}
		}
	}
	return true;
}

bool	XAlignmentArea::ExecuteStartByInspection(void)
{
	for(AlignmentShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
		d->CalcDone=false;
	}
	return true;
}

bool	XAlignmentArea::ReqOtherAlignment(void)
{
	int	page=ParentInLayer->GetPage();
	int	CurrentGlobalPage	=ParentInLayer->GetLayersBase()->GetGlobalPageFromLocal(page);
	for(int globalpage=0;globalpage<ParentInLayer->GetLayersBase()->GetGlobalPageNumb();globalpage++){
		SlaveCommReqAlignmentShift	RCmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckAlignmentShift	ACmd(ParentInLayer->GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.Layer=ParentInLayer->GetLayer();
		for(AlignmentShiftList *a=OtherPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GlobalPage==globalpage){
				if(a->CalcDone==false){
					RCmd.ItemID.Add(a->ItemID);
				}
			}
		}
		if(RCmd.Send(globalpage,0,ACmd)==true){
			for(AlignmentShiftList *s=ACmd.ShiftData.GetFirst();s!=NULL;s=s->GetNext()){
				for(AlignmentShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
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
	for(AlignmentShiftList *d=OtherPack.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->CalcDone==false){
			return false;
		}
	}
	return true;
}

bool    XAlignmentArea::Save(QIODevice *file)
{
	WORD	Ver=5;

    if(file->write((const char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

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
	for(XAlignmentPointer *g=GPack.GetFirst();g!=NULL;g=g->GetNext()){
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
	return true;
}
bool	XAlignmentArea::Load(QIODevice *file ,AlignmentInLayer *parent)
{
	WORD	Ver;

    if(file->read((char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

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
		XAlignmentPointer *g=new XAlignmentPointer();
		if(g->Load(file,this)==false)
			return(false);
		g->Point->AreaID=AreaID;
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

	ParentInLayer=parent;
	return(true);
}
bool    XAlignmentArea::SaveUnique(QIODevice *file)
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
bool    XAlignmentArea::LoadUnique(QIODevice *file)
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
//==========================================================================================

AlignmentInLayer::AlignmentInLayer(AlgorithmInPageRoot *parent) : AlgorithmInLayerPLI(parent)
{
	ResultShiftX=ResultShiftY=0;	//平行移動量
	ResultAngle=0;					//回転量（ラジアン）
	ResultExtend=1.0;				//拡大率
    MVector		=NULL;
    MVectorXNumb=0;
    MVectorYNumb=0;
    MVectorXRes	=0;
    MVectorYRes	=0;
}
AlignmentInLayer::~AlignmentInLayer(void)
{
	Release();
}

bool    AlignmentInLayer::ClearAll(void)
{
	Areas.RemoveAll();
	return(true);
}
void	AlignmentInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentDrawAttr	*LAttr=dynamic_cast<AlignmentDrawAttr *>(Attr);
	if(LAttr!=NULL){
		if(LAttr->AList.GetNumber()==0){
			for(XAlignmentArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
				c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
		else{
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			for(XAlignmentArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
				if(LAttr->AList.LayerExists(globalPage,GetLayer())==true){
					c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
	}
	else{
		for(XAlignmentArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
			c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
}
void	AlignmentInLayer::DrawItem(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentDrawAttr	*LAttr=dynamic_cast<AlignmentDrawAttr *>(Attr);
	if(LAttr!=NULL){
		if(LAttr->AList.GetNumber()==0){
			for(XAlignmentArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
				c->DrawItems(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
		else{
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			for(XAlignmentArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
				if(LAttr->AList.LayerExists(globalPage,GetLayer())==true){
					c->DrawItems(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
	}
	else{
		for(XAlignmentArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
			c->DrawItems(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
}

void	AlignmentInLayer::DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->DrawMove(dx ,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::DrawMove(dx ,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
}

void    AlignmentInLayer::InitializeFromImage(ImageBuffer &IBuff)
{
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		p->Initial(IBuff);
	}
    //最長の２原点を選ぶ
    double  MaxL=0;
    int L1=-1,L2=-1;

	int	N=0;
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		for(XAlignmentPointer *g=p->GPack.GetFirst();g!=NULL;g=g->GetNext()){
	        if(g->Point->IsNull()==true)
		        continue;
			N++;
		}
	}
	XAlignmentPointer	**GPoint=new XAlignmentPointer*[N];
	N=0;
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		for(XAlignmentPointer *g=p->GPack.GetFirst();g!=NULL;g=g->GetNext()){
	        if(g->Point->IsNull()==true)
		        continue;
			GPoint[N]=g;
			N++;
		}
	}

	for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
			double  L=hypot( GPoint[i]->Point->MasterX-GPoint[j]->Point->MasterX
							,GPoint[i]->Point->MasterY-GPoint[j]->Point->MasterY);
            if(L>MaxL){
                MaxL=L;
                L1=i;
                L2=j;
			}
		}
	}
	delete	[]GPoint;
}
void    AlignmentInLayer::Release(void)
{
	if(MVector!=NULL)
		delete	[]MVector;
	MVector=NULL;
}
void		AlignmentInLayer::RemoveItem(AlgorithmItemRoot *item)
{
	AlgorithmInLayerPLI::RemoveItem(item);
	XAlignment	*L=dynamic_cast<XAlignment *>(item);
	if(L!=NULL){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->RemoveItem(L);
		}
	}
}
bool AlignmentInLayer::BuildGlobalIndex(void)
{
	Release();
    MVectorXRes=32;
    MVectorYRes=32;
    MVectorXNumb=(GetDotPerLine()+MVectorXRes-1)/MVectorXRes;
    MVectorYNumb=(GetMaxLines()  +MVectorYRes-1)/MVectorYRes;
    if(MVector!=NULL)
        delete []MVector;
    MVector=new QPoint[MVectorXNumb*MVectorYNumb];
    for(int i=0;i<MVectorXNumb*MVectorYNumb;i++){
        MVector[i].setX(0);
        MVector[i].setY(0);
	}
	return(true);
}
ExeResult	AlignmentInLayer::ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteInitialAfterEdit	(ExeID,Res,EInfo);
	InitialThreadBufferForExecute();
	BuildGlobalIndex();
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		p->ExecuteInitialAfterEdit(EInfo);
	}
	return Ret;
}


XAlignment	*AlignmentInLayer::GetAlignment(int index)
{
	int	N=0;
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		for(XAlignmentPointer *g=p->GPack.GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Point->IsEffective()==true){
				if(N==index)
					return(g->Point);
				N++;
			}
		}
	}
	return(NULL);
}
void	AlignmentInLayer::RemoveArea(XAlignmentArea *a)
{
	XAlignmentPointer *p;
	while((p=a->GPack.GetFirst())!=NULL){
		RemoveItem(p->Point);
	}
	Areas.RemoveList(a);
	CleanupItems();
}

void    AlignmentInLayer::GetResultVectorXY(int rx ,int ry ,int &kx ,int &ky)
{
}

ExeResult	AlignmentInLayer::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	ResultShiftX=ResultShiftY=0;	//平行移動量
	ResultAngle=0;					//回転量（ラジアン）
	ResultExtend=1.0;				//拡大率

	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		p->ExecuteStartByInspection();
	}
	return _ER_true;
}

ExeResult	AlignmentInLayer::ExecuteAlignment(int ExeID ,ResultInLayerRoot *Res)
{
	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteAlignment(ExeID,Res);

	AlignmentBase	*PBase=(AlignmentBase *)GetParentBase();
	if(PBase->UseOtherPage==true){
		bool	ReqDone=true;
		for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->ReqOtherAlignment()==false){
				ReqDone=false;
			}
		}

		if(ReqDone==false){
			return _ER_ReqRetryLater;
		}
	}

	DataInLayer		*q=GetDataInLayer();
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentArea::_PriorityHigh){
			p->Calc(q->GetTargetBuff() ,MVector
						,MVectorXNumb ,MVectorYNumb
						,MVectorXRes  ,MVectorYRes);
		}
	}
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentArea::_PriorityMiddle){
			p->Calc(q->GetTargetBuff() ,MVector
						,MVectorXNumb ,MVectorYNumb
						,MVectorXRes  ,MVectorYRes);
		}
	}
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentArea::_PriorityLow){
			p->Calc(q->GetTargetBuff() ,MVector
						,MVectorXNumb ,MVectorYNumb
						,MVectorXRes  ,MVectorYRes);
		}
	}
	return Ret;
}
int     AlignmentInLayer::GetAlignmentNumb(void)
{
	int	N=0;
	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		for(XAlignmentPointer *g=p->GPack.GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Point->IsEffective()==true){
				N++;
			}
		}
	}
	return(N);
}

bool    AlignmentInLayer::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(AlgorithmInLayerPLI::Save(file)==false)
		return false;
    if(file->write((const char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	int32	N=Areas.GetNumber();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N))
		return(false);

	for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(file)==false)
			return(false);
	}
	return(true);
}

bool    AlignmentInLayer::Load(QIODevice *file)
{
	WORD	Ver;

	if(AlgorithmInLayerPLI::Load(file)==false)
		return false;
    if(file->read((char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N))
		return(false);

	Areas.RemoveAll();
	for(int i=0;i<N;i++){
		XAlignmentArea	*a=new XAlignmentArea(this);
		if(a->Load(file,this)==true)
			Areas.AppendList(a);
		else
			delete	a;
	}
	BuildGlobalIndex();

	CleanupItems();
	return(true);
}
void    AlignmentInLayer::CleanupItems(void)
{
NextReduction:;
	for(AlgorithmItemPLI *a=Data.GetFirst();a!=NULL;a=a->GetNext()){
		XAlignment	*La=dynamic_cast<XAlignment *>(a);
		if(La!=NULL){
			for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
				for(XAlignmentPointer *g=p->GPack.GetFirst();g!=NULL;g=g->GetNext()){
					if(g->Point==La)
						goto	Found;
				}
			}
		}
		Data.RemoveList(a);
		goto	NextReduction;
Found:;
	}
}
void	AlignmentInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	AddAlignmentAreaPacket	*AInL=dynamic_cast<AddAlignmentAreaPacket*>(packet);
	if(AInL!=NULL && AInL->Page==GetPage()){
		if(GetLayer()==AInL->Layer){
			XAlignmentArea	*a=new XAlignmentArea(this);
			a->AreaID	=AInL->Number;
			a->Area		=AInL->Area;
			a->AreaName	=AInL->AreaName;
			a->LimitedLib=AInL->LimitedLib;
			a->Priority	=AInL->Priority;
			a->ManualCreated=true;
			Areas.AppendList(a);

			UndoElement<AlignmentInLayer>	*UPointer=new UndoElement<AlignmentInLayer>(this,&AlignmentInLayer::UndoAppendManualArea);
			::Save(UPointer->GetWritePointer(),a->AreaID);
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		}
		return;
	}
	CmdReqAlignmentShiftPacket	*CmdReqAlignmentShiftPacketVar=dynamic_cast<CmdReqAlignmentShiftPacket *>(packet);
	if(CmdReqAlignmentShiftPacketVar!=NULL){
		for(IntClass *a=CmdReqAlignmentShiftPacketVar->ItemIDPoint->GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemRoot	*item=SearchIDItem(a->GetValue());
			AlignmentShiftList	*R=new AlignmentShiftList();
			if(item!=NULL){
				XAlignment	*AItem=dynamic_cast<XAlignment *>(item);
				if(AItem!=NULL){
					if(AItem->IsProcessDone()==true){
						R->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
						R->ItemID	=	AItem->GetID();
						R->CalcDone	=	true;
						R->ShiftX	=	AItem->CalcedX - AItem->MasterX;
						R->ShiftY	=	AItem->CalcedY - AItem->MasterY;
						R->MasterX	=	AItem->MasterX;
						R->MasterY	=	AItem->MasterY;
						CmdReqAlignmentShiftPacketVar->ShiftDataPoint->AppendList(R);
					}
				}
			}
		}
	}
	CmdReqAlignmentPointPacket	*CmdReqAlignmentPointPacketVar=dynamic_cast<CmdReqAlignmentPointPacket *>(packet);
	if(CmdReqAlignmentPointPacketVar!=NULL){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if((CmdReqAlignmentPointPacketVar->AreaName.isEmpty()==false && CmdReqAlignmentPointPacketVar->AreaName==a->AreaName)
			|| a->AreaID==CmdReqAlignmentPointPacketVar->AreaID){
				for(XAlignmentPointer *ap=a->GPack.GetFirst();ap!=NULL;ap=ap->GetNext()){
					AlignmentShiftList	*k=new AlignmentShiftList();
					k->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
					k->ItemID	=ap->Point->GetID();
					k->MasterX	=ap->Point->MasterX;
					k->MasterY	=ap->Point->MasterY;
					CmdReqAlignmentPointPacketVar->AlignmentPointData.AppendList(k);
				}
			}
		}
		return;
	}
	AddAlignmentPointPacket	*AInP=dynamic_cast<AddAlignmentPointPacket *>(packet);
	if(AInP!=NULL){
		XAlignment	*Item=dynamic_cast<XAlignment *>(CreateItem(0));
		Item->AreaID							=AInP->AreaID;
		Item->GetThresholdW()->MoveDot			=AInP->MoveDot;
		Item->GetThresholdW()->AlignmentOnOutline=AInP->AlignmentOnOutline;
		Item->GetThresholdW()->Threshold			=AInP->Threshold;
		Item->SetArea(AInP->Area);
		Item->SetManualCreated(true);
		AppendItemManual(Item);

		UndoElement<AlignmentInLayer>	*UPointer=new UndoElement<AlignmentInLayer>(this,&AlignmentInLayer::UndoAppendManualPoint);
		::Save(UPointer->GetWritePointer(),Item->GetID());
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	AddAlignmentGroupPacket	*AInG=dynamic_cast<AddAlignmentGroupPacket *>(packet);
	if(AInG!=NULL){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==AInG->AreaID){
				a->SetGroup(AInG->Area,AInG->GroupNumber);
			}
		}
		return;
	}
	RemoveAlignmentAreaPacket	*RInA=dynamic_cast<RemoveAlignmentAreaPacket *>(packet);
	if(RInA!=NULL){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==RInA->AreaID){
				RemoveArea(a);
				delete	a;
				return;				
			}
		}
		return;
	}
	ModifyAlignmentPointPacket	*MInP=dynamic_cast<ModifyAlignmentPointPacket *>(packet);
	if(MInP!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(MInP->ItemID);
		if(a!=NULL){
			XAlignment	*AItem=dynamic_cast<XAlignment *>(a);
			if(AItem!=NULL){
				AItem->GetThresholdW()->Threshold	=MInP->Threshold;
				AItem->GetThresholdW()->MoveDot		=MInP->MoveDot;
				AItem->GetThresholdW()->AlignmentOnOutline=MInP->AlignmentOnOutline;
			}
		}
		return;
	}
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(AlgorithmItemPLI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
			XAlignment	*AItem=dynamic_cast<XAlignment *>(Item);
			if(AItem!=NULL){
				AItem->GetThresholdW()->MoveDot=CmdAlignmentSetSearchDotVar->SearchDotX;
			}
		}
		return;
	}
	CmdReqAlignmentArea	*CmdReqAlignmentAreaVar=dynamic_cast<CmdReqAlignmentArea *>(packet);
	if(CmdReqAlignmentAreaVar!=NULL){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			CmdReqAlignmentAreaVar->Area+=a->Area;
		}
		return;
	}
}

bool	AlignmentInLayer::AppendItem(AlgorithmItemRoot *item)
{
	XAlignment	*AItem=dynamic_cast<XAlignment *>(item);
	if(AItem!=NULL){
		XAlignmentArea *A;
		for(A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
			if(A->AreaID==AItem->AreaID){
				break;
			}
		}
		if(A==NULL){
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			//AItem->SetParent(this);
			//AItem->MakeArea(AItem->Threshold ,*GetMasterBuff());
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			return false;
		}
		bool	Found=false;
		for(XAlignmentPointer *p=A->GPack.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Point==AItem){
				Found=true;
				break;
			}
		}
		if(Found==false){
			XAlignmentPointer	*AP=new XAlignmentPointer();
			AP->Point=AItem;
			AP->Parent=A;
			A->GPack.AppendList(AP);
		}

		AItem->SetParent(this);
		item->SetItemID();
		//AItem->MakeArea(AItem->GetThresholdR(GetLayersBase())->Threshold ,GetMasterBuff());
		AItem->CreateArea(GetMasterBuff());

		return AlgorithmInLayerPLI::AppendItemManual(AItem);
	}
	return false;
}
void	AlignmentInLayer::AppendItemWithoutMakeArea(AlgorithmItemRoot *item ,int AreaID)
{
	XAlignment	*AItem=dynamic_cast<XAlignment *>(item);
	if(AItem!=NULL){
		XAlignmentArea *A;
		for(A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
			if(A->AreaID==AreaID){
				break;
			}
		}
		if(A==NULL){
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			//AItem->SetParent(this);
			//AItem->MakeArea(AItem->Threshold ,*GetMasterBuff());
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			return;
		}
		bool	Found=false;
		for(XAlignmentPointer *p=A->GPack.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Point==AItem){
				Found=true;
				break;
			}
		}
		if(Found==false){
			XAlignmentPointer	*AP=new XAlignmentPointer();
			AP->Point=AItem;
			AP->Parent=A;
			A->GPack.AppendList(AP);
		}

		AItem->SetParent(this);
		item->SetItemID();
		AlgorithmInLayerPLI::AppendItemManual(AItem);
	}
}
bool	AlignmentInLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	XAlignment	*AItem=dynamic_cast<XAlignment *>(item);
	if(AItem!=NULL){
		XAlignmentArea *A;
		return AlgorithmInLayerPLI::AppendItem(AItem,AItem->GetID());
			//AItem->SetParent(this);
			//AItem->MakeArea(AItem->Threshold ,*GetMasterBuff());
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
	}
	return false;
}

QPoint	*AlignmentInLayer::GetPoint(int rx ,int ry)
{
	if(MVector==NULL)
		return(NULL);
	int	x=rx/MVectorXRes;
	int	y=ry/MVectorYRes;
	if(x<0)
		x=0;
	if(x>=MVectorXNumb)
		x=MVectorXNumb-1;
	if(y<0)
		y=0;
	if(y>=MVectorYNumb)
		y=MVectorYNumb-1;
	return(&MVector[y*MVectorXNumb+x]);
}

void	AlignmentInLayer::CopyFrom(AlgorithmInPageRoot *DestParent
							,AlgorithmInLayerRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)
{
	AlignmentInLayer	*srcAlign=dynamic_cast<AlignmentInLayer *>(src);
	if(srcAlign==NULL)
		return;
	for(XAlignmentArea *a=srcAlign->Areas.GetFirst();a!=NULL;a=a->GetNext()){
		XAlignmentArea *d=new XAlignmentArea(this);
		d->CopyWithoutItems(*a,true);
		d->PartsID		=PartsMaster;
		d->PartsAllocID	=PartsID;
		d->PartsAreaID	=a->AreaID;
		d->AreaID		=GetMaxAreaID()+1;

		d->MoveTo(OffsetX,OffsetY);

		for(XAlignmentPointer *g=a->GPack.GetFirst();g!=NULL;g=g->GetNext()){
			XAlignmentPointer	*gd=new XAlignmentPointer();
			gd->Parent=d;
			gd->Point=g->Point;	//仮に設定
			d->GPack.AppendList(gd);
		}
		Areas.AppendList(d);
		Changed=true;
		CalcDone =false;
	}
	for(AlgorithmItemPLI *Item=srcAlign->GetFirstData();Item!=NULL;Item=Item->GetNext()){
		AlgorithmItemRoot	*d=CreateItem(0);
		AlgorithmItemPLI	*dL=dynamic_cast<AlgorithmItemPLI *>(d);
		dL->SetParent(this);

		d->SetRefereneFrom(Item,OffsetX,OffsetY);
		d->CopyAttrFrom(Item);
		d->SetPartsData(PartsMaster ,PartsID ,Item->GetID());
		XAlignment	*a=dynamic_cast<XAlignment *>(d);

		int	DestAreaID=0;
		for(XAlignmentArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
			for(XAlignmentPointer *g=p->GPack.GetFirst();g!=NULL;g=g->GetNext()){
				if(g->Point==Item){
					g->Point=a;
					DestAreaID=p->AreaID;
				}
			}
		}

		if(a!=NULL && a->IsOtherAreaEffective()==true){
			AppendItemWithoutMakeArea(d,DestAreaID);
			Changed=true;
			CalcDone =false;
		}
		else{
			AppendItem(d);
			Changed=true;
			CalcDone =false;
		}
	}
	/*
	AlgorithmInLayerPLI::CopyFrom(DestParent
							,src 
							,OffsetX,OffsetY
							,PartsMaster ,PartsID
							,ReferedThresholdMode);
						*/
}

void	AlignmentInLayer::MoveItemsToDispatcherForLoadingParts(void)
{
	AlgorithmInLayerPLI::MoveItemsToDispatcherForLoadingParts();
	Dispatcher.RemoveAll();
	DispatchAreas.RemoveAll();
QNext:;
	for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PartsID>=0){
			Areas.RemoveList(a);
			DispatchAreas.AppendList(a);
			Changed=true;
			CalcDone =false;
			goto	QNext;
		}
	}
}

void	AlignmentInLayer::CopyItemsFormDispatcherForParts(void)
{
	AlgorithmInLayerPLI::CopyItemsFormDispatcherForParts();

	for(XAlignmentArea *Src=DispatchAreas.GetFirst();Src!=NULL;Src=Src->GetNext()){
		for(XAlignmentArea *Dest=Areas.GetFirst();Dest!=NULL;Dest=Dest->GetNext()){
			if(Src->PartsID==Dest->PartsID
			&& Src->PartsAllocID==Dest->PartsAllocID
			&& Src->PartsAreaID ==Dest->PartsAreaID){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				Src->SaveUnique(&Buff);
				Buff.seek(0);
				Dest->LoadUnique(&Buff);
			}
		}
	}
}

void	AlignmentInLayer::RemoveItemFormDispatcher(void)
{
	AlgorithmInLayerPLI::RemoveItemFormDispatcher();
	DispatchAreas.RemoveAll();
}


bool	AlignmentInLayer::IsModeItemEditing(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentForm" ,/**/"");
	CmdIsModeItemEditingPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
	}
	if(MCmd.ItemMode==CmdIsModeItemEditingPacket::_ItemMode)
		return true;
	return false;
}
bool	AlignmentInLayer::IsModeAreaEditing(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentForm" ,/**/"");
	CmdIsModeItemEditingPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
	}
	if(MCmd.ItemMode==CmdIsModeItemEditingPacket::_AreaMode)
		return true;
	return false;
}

int		AlignmentInLayer::GetSelectedItemCount(void)
{
	if(IsModeAreaEditing()==true){
		int	N=0;
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				N++;
		}
		return N;
	}
	return AlgorithmInLayerPLI::GetSelectedItemCount();
}
void	AlignmentInLayer::ReleaseAllSelectedItem(void)
{
	for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Selected=false;
	}
	AlgorithmInLayerPLI::ReleaseAllSelectedItem();
}
void	AlignmentInLayer::SelectAll(void)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Selected=true;
		}
	}
	else
		AlgorithmInLayerPLI::SelectAll();
}
void	AlignmentInLayer::SelectLocked(void)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Locked==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInLayerPLI::SelectLocked();
}
void	AlignmentInLayer::SelectLibs(AlgorithmLibraryListContainer &SelectedList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			for(AlgorithmLibraryList *L=a->LimitedLib.GetFirst();L!=NULL;L=L->GetNext()){
				for(AlgorithmLibraryList *m=SelectedList.GetFirst();m!=NULL;m=m->GetNext()){
					if(m->GetLibID()==L->GetLibID()){
						a->Selected=true;
						goto	HNext;
					}
				}
			}
			a->Selected=false;
HNext:;
		}
	}
	else
		AlgorithmInLayerPLI::SelectLibs(SelectedList);
}
void	AlignmentInLayer::SelectArea(FlexArea &localArea,bool MultiSelect)		
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.CheckOverlap(&localArea)==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInLayerPLI::SelectArea(localArea, MultiSelect);
}
void	AlignmentInLayer::SelectPoint(int localX, int localY)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.IsInclude(localX,localY)==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInLayerPLI::SelectPoint(localX,localY);
}
void	AlignmentInLayer::CutArea(FlexArea &localArea ,bool MultiSelect,const QByteArray &Something)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.CheckOverlap(&localArea)==true){
				FlexArea	area=a->Area;
				a->Area.Sub(area,localArea);
				Changed=true;
				CalcDone =false;
			}
		}
	}
	else
		AlgorithmInLayerPLI::CutArea(localArea ,MultiSelect,Something);
}
void	AlignmentInLayer::RegistArea(FlexArea &localArea)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInLayerPLI::RegistArea(localArea);
}
void	AlignmentInLayer::DeleteSelectedItems(void)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;){
			if(a->Selected==true){
				XAlignmentPointer *p;
				while((p=a->GPack.GetFirst())!=NULL){
					XAlignment		*item=p->Point;
					a->RemoveItem(item);
					AlgorithmInLayerPLI::RemoveItem(item);
					delete	item;
				}
				XAlignmentArea *NextA=a->GetNext();
				Areas.RemoveList(a);
				Changed=true;
				CalcDone =false;
				delete	a;
				a=NextA;
			}
			else{
				a=a->GetNext();
			}
		}
	}
	else
		AlgorithmInLayerPLI::DeleteSelectedItems();
}
void	AlignmentInLayer::LockSelectedItems(void)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				a->Locked=true;
			else
				a->Locked=false;
		}
	}
	else
		AlgorithmInLayerPLI::SelectLocked();
}
void	AlignmentInLayer::BindSelectedItems(void)
{
	if(IsModeAreaEditing()==true){
		XAlignmentArea *M;
		for(M=Areas.GetFirst();M!=NULL;M=M->GetNext()){
			if(M->Selected==true){
				break;
			}
		}
		if(M!=NULL){
			for(XAlignmentArea *a=M->GetNext();a!=NULL;){
				if(a->Selected==true){
					XAlignmentPointer *p;
					while((p=a->GPack.GetFirst())!=NULL){
						a->GPack.RemoveList(p);
						p->Parent=M;
						M->GPack.AppendList(p);
					}
				}
				M->Area+=a->Area;
				XAlignmentArea *NextA=a->GetNext();
				Areas.RemoveList(a);
				Changed=true;
				CalcDone =false;
				delete	a;
				a=NextA;
			}
		}
	}
	else
		AlgorithmInLayerPLI::BindSelectedItems();
}
void	AlignmentInLayer::Activate(int localX ,int localY ,ListLayerAndIDPack &RetItem)	
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(localX,localY)==true)
				a->Active=true;
			else
				a->Active=false;
		}
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Active==true){
				RetItem.AppendList(new ListLayerAndID(GetLayer(),a->AreaID));
			}
		}
	}
	else
		AlgorithmInLayerPLI::Activate(localX ,localY ,RetItem);
}
void	AlignmentInLayer::Activate(int ItemID)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==ItemID)
				a->Active=true;
			else
				a->Active=false;
		}
	}
	else
		AlgorithmInLayerPLI::Activate(ItemID);
}
void	AlignmentInLayer::Inactivate(void)
{
	for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Active=false;
	}
	AlgorithmInLayerPLI::Inactivate();
}

void	AlignmentInLayer::ExecuteCopy(ClipboardAlgorithm &Pack)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInLayerPLI::ExecuteCopy(Pack);
}
void	AlignmentInLayer::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if((AllItems==false && a->Locked==false && a->Selected==true)
			|| AllItems==true){
				a->Area.MoveToNoClip(GlobalDx,GlobalDy);
				for(XAlignmentPointer *p=a->GPack.GetFirst();p!=NULL;p=p->GetNext()){
					XAlignment		*item=p->Point;
					item->ExecuteMove(GlobalDx,GlobalDy);
					Changed=true;
					CalcDone =false;
				}
			}
		}
	}
	else
		AlgorithmInLayerPLI::ExecuteMove(GlobalDx,GlobalDy);
}

void	AlignmentInLayer::GetOriginRootNames(NPListPack<OriginNames> &OriginNameList)
{
	if(IsModeAreaEditing()==true){
		AlgorithmBase	*Dim[1000];
		int				DimNumb=0;
		int				ItemNumb[1000];

		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			int i;
			for(i=0;i<DimNumb;i++){
				if(Dim[i]==a->Origin){
					ItemNumb[i]++;
					break;
				}
			}
			if(i>=DimNumb && i<sizeof(Dim)/sizeof(Dim[0])){
				Dim[DimNumb]=a->Origin;
				ItemNumb[DimNumb]=1;
				DimNumb++;
			}
		}
		for(int i=0;i<DimNumb;i++){
			OriginNames	*v=new OriginNames();
			Dim[i]->GetDLLName(v->DLLRoot ,v->DLLName);
			v->Numb=ItemNumb[i];
			OriginNameList.AppendList(v);
		}
	}
	else
		AlgorithmInLayerPLI::GetOriginRootNames(OriginNameList);
}

void	AlignmentInLayer::SelectOriginRootNames(AlgorithmBase *OriginBase)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Origin==OriginBase)
				a->Selected=true;
		}
	}
	else
		AlgorithmInLayerPLI::SelectOriginRootNames(OriginBase);
}
void	AlignmentInLayer::VisibleAll(void)			
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Visible=true;
		}
	}
	else
		AlgorithmInLayerPLI::VisibleAll();
}
void	AlignmentInLayer::InvisibleAll(void)			
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Visible=false;
		}
	}
	else
		AlgorithmInLayerPLI::InvisibleAll();
}
void	AlignmentInLayer::InvisibleSelected(void)		
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				a->Visible=false;
			else
				a->Visible=true;
		}
	}
	else
		AlgorithmInLayerPLI::InvisibleSelected();
}
void	AlignmentInLayer::SelectManualCreature(void)	
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ManualCreated==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInLayerPLI::SelectManualCreature();
}

bool	AlignmentInLayer::ExistArea(int localX,int localY)
{
	for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Area.IsInclude(localX,localY)==true){
			return true;
		}
	}
	return false;
}

XAlignmentArea	*AlignmentInLayer::GetAlignmentArea(int AreaID)
{
	for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==AreaID)
			return a;
	}
	return NULL;
}

void	AlignmentInLayer::UndoAppendManualArea(QIODevice *f)
{
	int32	AreaID;
	::Load(f,AreaID);
	XAlignmentArea	*Area=GetAlignmentArea(AreaID);
	if(Area!=NULL){
		RemoveArea(Area);
		delete	Area;
	}
}
void	AlignmentInLayer::UndoAppendManualPoint(QIODevice *f)
{
	int	ItemID;
	::Load(f,ItemID);
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}

int		AlignmentInLayer::GetMaxAreaID(void)
{
	int	MaxAreaID=0;
	for(XAlignmentArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID>MaxAreaID){
			MaxAreaID=a->AreaID;
		}
	}
	return MaxAreaID;
}

//==========================================================================================
AlignmentInPage::AlignmentInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent)
{
}

bool	AlignmentInPage::ExistArea(int localX,int localY)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		if(L->ExistArea(localX,localY)==true){
			return true;
		}
	}
	return false;
}

AlignmentPacket2D	*AlignmentInPage::AppendAlignmentPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal)
{
	if(ExistArea(localX,localY)==true){	
		AlignmentPacket2DList	*L=new AlignmentPacket2DList();
		L->LibType		=Item->GetParentBase()->GetLibType();
		L->LibID		=Item->GetLibID();
		L->PosXOnTarget	=localX;
		L->PosYOnTarget	=localY;
		AlignmentPacket2DCreaterMutex.lock();
		AlignmentPacket2DContainer.AppendList(L);
		AlignmentPacket2DCreaterMutex.unlock();
		return L;
	}
	return NULL;
}
ExeResult	AlignmentInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	AlignmentPacket2DContainer.RemoveAll();
	return AlgorithmInPagePLI::ExecuteInitialAfterEdit(ExeID,Res,EInfo);
}
ExeResult	AlignmentInPage::ExecuteAlignment	(int ExeID ,ResultInPageRoot *Res)
{
	for(AlignmentPacket2DList *p=AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		p->ShiftX=99999999;
		p->ShiftY=99999999;
		p->Calculated=false;
	}
	ExeResult	ret=AlgorithmInPagePLI::ExecuteAlignment(ExeID,Res);
	for(AlignmentPacket2DList *p=AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ShiftX==99999999 && p->ShiftY==99999999){
			p->ShiftX=0;
			p->ShiftY=0;
		}
	}
	return ret;
}

void	AlignmentInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePLI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	if(LayerList.GetFirst()!=NULL){
		for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetValue()<0 || AllocatedLayerNumb<=c->GetValue()){
				continue;
			}
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(c->GetValue());
			L->DrawItem(pnt, movx,movy,ZoomRate ,Attr);
		}
	}
	else{
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
			L->DrawItem(pnt, movx,movy,ZoomRate ,Attr);
		}
	}
}

int	AlignmentLibType=1;
int	AlignmentPage=0;
int	AlignmentLayer=0;
int	AlignmentID	=139;
int	AlignmentDbg;

void	AlignmentInPage::GetAlignment(AlignmentPacket2D &AData)
{
	if(AData.LibType==AlignmentLibType
	&& AData.Page==AlignmentPage
	&& AData.Layer==AlignmentLayer
	&& AData.SourceID==AlignmentID)
		AlignmentDbg++;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityHigh){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned4){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityHigh){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned3){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityHigh){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned2){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityHigh){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned1){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityMiddle){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned4){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityMiddle){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned3){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityMiddle){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned2){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityMiddle){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned1){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityLow){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned4){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityLow){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned3){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityLow){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned2){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->Priority==XAlignmentArea::_PriorityLow){
				if(a->GetResultInPoint(AData.PosXOnTarget ,AData.PosYOnTarget)==XAlignmentArea::_Aligned1){
					a->GetAlignment(AData);
					return;
				}
			}
		}
	}
	AData.ShiftX=0;
	AData.ShiftY=0;
}

void	AlignmentInPage::GetAlignmentParam(double m[6])
{
	XAlignmentArea *Largest=NULL;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
		for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
			if(a->GetCalcedItemCount()>=3){
				if(Largest==NULL)
					Largest=a;
				else if(Largest->Area.GetPatternByte()<a->Area.GetPatternByte()){
					Largest=a;
				}
			}
		}
	}
	if(Largest==NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
			for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
				if(a->GetCalcedItemCount()==2){
					if(Largest==NULL)
						Largest=a;
					else if(Largest->Area.GetPatternByte()<a->Area.GetPatternByte()){
						Largest=a;
					}
				}
			}
		}
	}
	if(Largest==NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(layer);
			for(XAlignmentArea *a=L->Areas.GetLast();a!=NULL;a=a->GetPrev()){
				if(a->GetCalcedItemCount()==1){
					if(Largest==NULL)
						Largest=a;
					else if(Largest->Area.GetPatternByte()<a->Area.GetPatternByte()){
						Largest=a;
					}
				}
			}
		}
	}
	if(Largest!=NULL){
		for(int i=0;i<6;i++)
			m[i]=Largest->ALResult[0].AlignmentResult[i];
	}
	else{
		m[0]=1.0;
		m[1]=0.0;
		m[2]=0.0;
		m[3]=0.0;
		m[4]=1.0;
		m[5]=0.0;
	}
}

void	AlignmentInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	GetAlignmentConclusion	*GetAlignmentConclusionVar=dynamic_cast<GetAlignmentConclusion *>(packet);
	if(GetAlignmentConclusionVar!=NULL){
		GetAlignmentConclusionVar->m[0]=1.0;
		GetAlignmentConclusionVar->m[1]=0.0;
		GetAlignmentConclusionVar->m[2]=0.0;
		GetAlignmentConclusionVar->m[3]=0.0;
		GetAlignmentConclusionVar->m[4]=1.0;
		GetAlignmentConclusionVar->m[5]=0.0;
		GetAlignmentParam(GetAlignmentConclusionVar->m);
	}
	CmdGetAlignmentAreas	*CmdGetAlignmentAreasVar=dynamic_cast<CmdGetAlignmentAreas *>(packet);
	if(CmdGetAlignmentAreasVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(Layer);
			for(XAlignmentArea *a=L->Areas.GetFirst();a!=NULL;a=a->GetNext()){
				FlexAreaPointerList *f;
				for(f=CmdGetAlignmentAreasVar->Areas.GetFirst();f!=NULL;f=f->GetNext()){
					if(*f->GetArea()==a->Area){
						break;
					}
				}
				if(f==NULL){
					CmdGetAlignmentAreasVar->Areas.Add(&a->Area);
				}
			}
		}
		return;
	}
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(Layer);
			L->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqAlignmentArea	*CmdReqAlignmentAreaVar=dynamic_cast<CmdReqAlignmentArea *>(packet);
	if(CmdReqAlignmentAreaVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)GetLayerData(Layer);
			L->TransmitDirectly(packet);
		}
		return;
	}
}

//==========================================================================================
AlignmentBase::AlignmentBase(LayersBase *Base)
	:AlgorithmBase(Base)
{
	ColorArea			=Qt::darkYellow;
	ColorAreaSelected	=Qt::yellow;
	ColorAreaActive		=Qt::red;
	ColorPoint			=Qt::darkGreen;
	ColorPointSelected	=Qt::green;
	ColorPointActive	=Qt::red;
	AlphaLevel	=100;
	DefaultThreshold	=0;
	DefaultMoveDot		=20;
	DefaultAlignmentOnOutline=false;
	DefaultOutlineDivCount	=8;
	DefaultOutlineWidth		=4;
	UseOtherPage			=true;

	SetParam(&ColorArea					, /**/"Color"		,/**/"ColorArea"			,LangSolver.GetString(XAlignment_LS,LID_1)/*"Alignment Area color"*/);
	SetParam(&ColorAreaSelected			, /**/"Color"		,/**/"ColorAreaSelected"	,LangSolver.GetString(XAlignment_LS,LID_3)/*"Selected Alignment Area color"*/);
	SetParam(&ColorAreaActive			, /**/"Color"		,/**/"ColorAreaActive"	,LangSolver.GetString(XAlignment_LS,LID_5)/*"Active Alignment Area color"*/);
	SetParam(&ColorPoint				, /**/"Color"		,/**/"ColorPoint"			,LangSolver.GetString(XAlignment_LS,LID_7)/*"Alignment Point color"*/);
	SetParam(&ColorPointSelected		, /**/"Color"		,/**/"ColorPointSelected"	,LangSolver.GetString(XAlignment_LS,LID_9)/*"Selected Alignment Point color"*/);
	SetParam(&ColorPointActive			, /**/"Color"		,/**/"ColorPointActive"	,LangSolver.GetString(XAlignment_LS,LID_11)/*"Active Alignment Point color"*/);
	SetParam(&AlphaLevel				, /**/"Color"		,/**/"AlphaLevel"			,LangSolver.GetString(XAlignment_LS,LID_13)/*"Alignment transparent level"*/);

	SetParam(&DefaultThreshold			, /**/"Threshold"	,/**/"DefaultThreshold"		,LangSolver.GetString(XAlignment_LS,LID_15)/*"Threshold point separation"*/);
	SetParam(&DefaultMoveDot			, /**/"Threshold"	,/**/"DefaultMoveDot"		,LangSolver.GetString(XAlignment_LS,LID_17)/*"Searching dots for match"*/);
	SetParam(&DefaultAlignmentOnOutline	, /**/"Threshold"	,/**/"DefaultAlignmentOnOutline"		,LangSolver.GetString(XAlignment_LS,LID_19)/*"if true, enabled outline matching"*/);

	SetParam(&DefaultOutlineDivCount	,/**/"Threshold"	,/**/"DefaultOutlineDivCount"	,LangSolver.GetString(XAlignment_LS,LID_21)/*"Default Division count for Outline"*/);
	SetParam(&DefaultOutlineWidth		,/**/"Threshold"	,/**/"DefaultOutlineWidth"		,LangSolver.GetString(XAlignment_LS,LID_22)/*"Default OutlineWidth"*/);

	SetParam(&UseOtherPage				, /**/"Setting"		,/**/"UseOtherPage"			,"Use alignment in other pages");
}

AlgorithmDrawAttr	*AlignmentBase::CreateDrawAttr(void)
{
	return new AlignmentDrawAttr();
}

bool	AlignmentBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	XAlignment	AItem();
	GetSelectedAlignmentAreaPacket	SMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&SMode);
		}
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadOnly);
	SMode.SelectedArea.Save(&Buff);
	return true;
}

bool	AlignmentBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	FlexArea	area=item->Area;
	area.MoveToNoClip(globalDx,globalDy);
	for(int page=0;page<GetPageNumb();page++){
		if(GetLayersBase()->GetPageData(page)->IsOverlapped(area)==true){
			GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(area);
			AlgorithmInLayerPLI	*L;
			AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(GetPageData(page));
			if(Ap!=NULL){
				if(PastedLayer==-1){
					L=Ap->GetLayerDataPLI(item->Layer);
				}
				else{
					L=Ap->GetLayerDataPLI(PastedLayer);
				}
				AlgorithmItemRoot	*a=((AlignmentInLayer *)L)->CreateItem(item->ItemClassType);
				QBuffer	Buff(&item->ItemData);
				Buff.open(QIODevice::ReadOnly);
				ListLayerAndIDPack	SelectedArea;
				SelectedArea.Load(&Buff);
				for(ListLayerAndID *s=SelectedArea.GetFirst();s!=NULL;s=s->GetNext()){
					if(s->Layer!=PastedLayer)
						continue;
					((XAlignment *)a)->AreaID=s->ID;
					a->SetArea(area);
					L->AppendItem(a);
				}
			}
		}
	}
	return true;
}

void	AlignmentBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
}


