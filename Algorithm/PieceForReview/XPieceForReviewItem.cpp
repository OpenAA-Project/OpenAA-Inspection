/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPieceForReviewItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PieceForReviewResource.h"
#include "XPieceForReview.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"
#include "XPieceForReviewPacket.h"


BYTE	PieceForReviewItem::OverlappedColorTable[3][256];
BYTE	PieceForReviewItem::OverlappedColorTableActive[3][256];
BYTE	PieceForReviewItem::OverlappedColorTableSelected[3][256];
bool	PieceForReviewItem::InitializedTable=false;


PieceForReviewThreshold::PieceForReviewThreshold(PieceForReviewItem *parent):AlgorithmThreshold(parent)
{
}


bool    PieceForReviewItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,SysRegNumber)==false)
		return false;	
	return true;
}
bool    PieceForReviewItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,SysRegNumber)==false)
		return false;
	return true;
}
bool	PieceForReviewItem::SaveUnique(QIODevice *f)
{
	if(AlgorithmItemPI::SaveUnique(f)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,SysRegNumber)==false)
		return false;
	return true;
}
bool	PieceForReviewItem::LoadUnique(QIODevice *f)
{
	if(AlgorithmItemPI::LoadUnique(f)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,SysRegNumber)==false)
		return false;
	return true;
}

void	PieceForReviewItem::DrawOverlappedImage(QImage &pnt, int movx ,int movy ,double ZoomRate
												,int dx, int dy
												,BYTE ColorTable[3][256])
{
	SetColorTable();

	ImageBuffer	*BuffPointer[100];
	((PieceForReviewInPage *)GetParentInPage())->GetMasterBuffList(BuffPointer);

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	int	Lx1=GetArea().GetMinX();
	int	Ly1=GetArea().GetMinY();

	QImage	tmpImage(W*ZoomRate,H*ZoomRate,QImage::Format_ARGB32);
	tmpImage.fill(0);
	GetArea().Draw(-Lx1,-Ly1,&tmpImage ,BuffPointer,GetLayerNumb()
						,ZoomRate ,0 ,0
						,ColorTable
						,0x80);
	QPainter	Pnt(&pnt);
	Pnt.drawImage((Lx1+dx+movx)*ZoomRate,(Ly1+dy+movy)*ZoomRate,tmpImage);
}

void	PieceForReviewItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	PieceForReviewDrawAttr	*LAttr=dynamic_cast<PieceForReviewDrawAttr *>(Attr);
	if(LAttr!=NULL){
		if(LAttr->OverlapImage==true){
			PieceForReviewItem	*FirstItem=(PieceForReviewItem *)((PieceForReviewInPage *)GetParentInPage())->GetFirstData();
			if(FirstItem!=NULL){
				int	Cx,Cy;
				GetCenter(Cx,Cy);
				int	Dx,Dy;
				FirstItem->GetCenter(Dx,Dy);
				if(GetSelected()==true){
					FirstItem->DrawOverlappedImage(pnt, movx ,movy ,ZoomRate 
													,Cx-Dx,Cy-Dy
													,OverlappedColorTableSelected);
				}
				else if(GetActive()==true){
					FirstItem->DrawOverlappedImage(pnt, movx ,movy ,ZoomRate 
													,Cx-Dx,Cy-Dy
													,OverlappedColorTableActive);
				}
				else{
					FirstItem->DrawOverlappedImage(pnt, movx ,movy ,ZoomRate 
													,Cx-Dx,Cy-Dy
													,OverlappedColorTable);
				}
			}
		}
		else{
			AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	if(ZoomRate>0.3){
		int	cx,cy;
		GetArea().GetCenter(cx,cy);
		GetLayersBase()->LockDraw();
		QPainter	P(&pnt);
		P.drawText ((cx+movx)*ZoomRate ,(cy+movy)*ZoomRate		,AreaName);
		P.drawText ((cx+movx)*ZoomRate ,(cy+movy)*ZoomRate+12	,QString("No :")+QString::number(AreaNumber));
		P.drawText ((cx+movx)*ZoomRate ,(cy+movy)*ZoomRate+24	,QString("Seq:")+QString::number(SysRegNumber));
		GetLayersBase()->UnlockDraw();
	}
}
void	PieceForReviewItem::DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	if((GetSelected()==true) && (GetEditLocked()==false)){
		bool	Viewed=false;

		PieceForReviewItem	*FirstItem=(PieceForReviewItem *)((PieceForReviewInPage *)GetParentInPage())->GetFirstData();
		if(FirstItem!=NULL){
			int	Cx,Cy;
			GetCenter(Cx,Cy);
			int	Dx,Dy;
			FirstItem->GetCenter(Dx,Dy);
			FirstItem->DrawOverlappedImage(pnt, movx ,movy ,ZoomRate 
											,Cx-Dx+dx,Cy-Dy+dy
											,OverlappedColorTableActive);
			Viewed=true;
		}
		if(Viewed==false){
			GetArea().Draw(dx,dy ,&pnt ,Col.rgba()
							,ZoomRate ,movx ,movy);
		}
	}
}

void	PieceForReviewItem::SetColorTable(void)
{
	if(InitializedTable==false){
		PieceForReviewBase	*PBase=(PieceForReviewBase *)GetParentBase();
		if(PBase!=NULL){
			int		OverlappedRStrength	=PBase->OverlappedRStrength;
			int		OverlappedGStrength	=PBase->OverlappedGStrength;
			int		OverlappedBStrength	=PBase->OverlappedBStrength;

			int		OverlappedRStrengthActive	=PBase->OverlappedRStrengthActive;
			int		OverlappedGStrengthActive	=PBase->OverlappedGStrengthActive;
			int		OverlappedBStrengthActive	=PBase->OverlappedBStrengthActive;

			int		OverlappedRStrengthSelected	=PBase->OverlappedRStrengthSelected;
			int		OverlappedGStrengthSelected	=PBase->OverlappedGStrengthSelected;
			int		OverlappedBStrengthSelected	=PBase->OverlappedBStrengthSelected;

			for(int i=0;i<256;i++){
				OverlappedColorTable[0][i]=OverlappedRStrength*i/255;
				OverlappedColorTable[1][i]=OverlappedGStrength*i/255;
				OverlappedColorTable[2][i]=OverlappedBStrength*i/255;

				OverlappedColorTableActive[0][i]=OverlappedRStrengthActive*i/255;
				OverlappedColorTableActive[1][i]=OverlappedGStrengthActive*i/255;
				OverlappedColorTableActive[2][i]=OverlappedBStrengthActive*i/255;

				OverlappedColorTableSelected[0][i]=OverlappedRStrengthSelected*i/255;
				OverlappedColorTableSelected[1][i]=OverlappedGStrengthSelected*i/255;
				OverlappedColorTableSelected[2][i]=OverlappedBStrengthSelected*i/255;
			}
		}
	}
}

static	void PieceForReviewFunc(ResultInItemRoot *Item ,void *Something)
{
	PieceForReviewItem	*NItem=(PieceForReviewItem *)Something;
	if(NItem->GetParentInPage()->GetPage()==Item->GetPage()){
		for(ResultPosList *c=Item->GetPosListFirst();c!=NULL;c=c->GetNext()){
			if(NItem->GetArea().IsInclude(c->Px,c->Py)==true){
				c->AreaNames.append(NItem->AreaName);
				c->PieceAreaNumber=NItem->AreaNumber;
			}
		}
	}
}

ExeResult	PieceForReviewItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(AreaName==/**/"")
		return _ER_true;
	ResultInspection	*R=Res->GetResultInspection();
	R->ExecuteInAllItems(PieceForReviewFunc,this);
	return _ER_true;
}

void	PieceForReviewItem::BindResult(ResultInItemRoot *Item,ResultPosList *RPos)
{
	if(Item->IsOk()==false && RPos->IsOverlap(GetArea())==true){
		int	x1,y1,x2,y2;
		RPos->AreaNames.append(AreaName);

		RPos->GetXY(x1,y1,x2,y2);
		ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
		ResultInspection	*p=Item->GetResultInspection();

		NGImageContainerInPhase	*Ph=p->GetNGImageInPhase(GetPhaseCode());
		if(Ph!=NULL){
			NGImageContainerInPage	*h=Ph->GetNGImageInPage(GetPage());
			if(x1==x2 && y1==y2){
				ErrorGroup *e;
				for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
					ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
					if(g->Item!=this)
						continue;
					int	ex1,ey1,ex2,ey2;
					e->GetXY(ex1,ey1,ex2,ey2);
					int	rx1=min(ex1,x1);
					int	ry1=min(ey1,y1);
					int	rx2=max(ex2,x1);
					int	ry2=max(ey2,y1);
					if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel
					&&  g->GetPieceAreaNumber()==AreaNumber){
						g->SetRectangle(rx1,ry1,rx2,ry2);
						break;
					}
				}
				if(e==NULL){
					ErrorGroupPieceForReview	*g=new ErrorGroupPieceForReview(GetLayersBase());
					g->SetRectangle(x1,y1,x2,y2);
					g->Item=this;
					g->SetName(AreaName);
					g->SetImportanceLevel(RPos->ImportanceLevel);
					g->SetPieceAreaNumber(AreaNumber);
					g->SetNGSize(RPos->NGSize);
					h->AddErrorGroupData(g);
				}
				else{
					if(RPos->ImportanceLevel<e->GetImportanceLevel()){
						ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
						g->SetImportanceLevel(RPos->ImportanceLevel);
					}
					if(RPos->NGSize>e->GetNGSize()){
						ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
						g->SetNGSize(RPos->NGSize);
					}
				}
			}
			else{
				ErrorGroup *e;
				for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
					ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
					if(g->Item!=this)
						continue;
					int	ex1,ey1,ex2,ey2;
					e->GetXY(ex1,ey1,ex2,ey2);
					int	rx1=min(ex1,x1);
					int	ry1=min(ey1,y1);
					int	rx2=max(ex2,x2);
					int	ry2=max(ey2,y2);
					if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel
					&&  g->GetPieceAreaNumber()==AreaNumber){
						g->SetRectangle(rx1,ry1,rx2,ry2);
						break;
					}
				}
				if(e==NULL){
					if((x2-x1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (y2-y1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
						ErrorGroupPieceForReview	*g=new ErrorGroupPieceForReview(GetLayersBase());
						g->SetRectangle(x1,y1,x2,y2);
						g->Item=this;
						g->SetName(AreaName);
						g->SetImportanceLevel(RPos->ImportanceLevel);
						g->SetPieceAreaNumber(AreaNumber);
						g->SetNGSize(RPos->NGSize);
						h->AddErrorGroupData(g);
					}
					else{
						FlexArea	A;
						FlexArea	B;
						A.Sub(RPos->NGShape, GetArea());
						B.Sub(RPos->NGShape,A);
						B.GetCenter(x1,y1);
						ErrorGroupPieceForReview	*g=new ErrorGroupPieceForReview(GetLayersBase());
						g->SetRectangle( x1-RBase->NGImageWidth /2+RBase->NGImageBevel,y1-RBase->NGImageHeight/2+RBase->NGImageBevel
										,x2+RBase->NGImageWidth /2-RBase->NGImageBevel,y2+RBase->NGImageHeight/2-RBase->NGImageBevel);
						g->Item=this;
						g->SetName(AreaName);
						g->SetImportanceLevel(RPos->ImportanceLevel);
						g->SetPieceAreaNumber(AreaNumber);
						g->SetNGSize(RPos->NGSize);
						h->AddErrorGroupData(g);
					}
				}
				else{
					if(RPos->ImportanceLevel<e->GetImportanceLevel()){
						ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
						g->SetImportanceLevel(RPos->ImportanceLevel);
					}
					if(RPos->NGSize>e->GetNGSize()){
						ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
						g->SetNGSize(RPos->NGSize);
					}
				}
			}
		}
	}
}
