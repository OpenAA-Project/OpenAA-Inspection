/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XARArrange.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XARArrange.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XLearningRegist.h"
#include "omp.h"

ARArrangeThreshold::ARArrangeThreshold(ARArrangeItem *parent)
:AlgorithmThreshold(parent)
{
}


bool	ARArrangeThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	return(true);
}
bool	ARArrangeThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	return(true);
}

AlgorithmItemPI	&ARArrangeItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    ARArrangeItem::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	if(Index!=NULL){
		if(::Save(f,Index->GetCreatedTime())==false){
			return false;
		}
	}
	else{
		XDateTime	TmNull;
		if(::Save(f,TmNull)==false){
			return false;
		}
	}

	return true;
}
bool    ARArrangeItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
			return false;

	XDateTime	SearchIndex;
	if(::Save(f,SearchIndex)==false)
		return false;

	DataInPage	*Pg=GetDataInPage();
	if(Pg!=NULL){
		Index=Pg->Find(SearchIndex);
	}

	return true;
}


void	ARArrangeItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(Index!=NULL){
		int	x1,y1,x2,y2;
		GetArea().GetXY(x1,y1,x2,y2);
		int	X1=(x1+movx)*ZoomRate;
		int	Y1=(y1+movy)*ZoomRate;
		int	X2=(x1+Index->GetWidth ()+movx)*ZoomRate;
		int	Y2=(y1+Index->GetHeight()+movy)*ZoomRate;

		QPainter	Pnt(&pnt);
		if(GetActive()==true){
			//AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
			if(Index!=NULL){
				Index->DrawImage(pnt,movx,movy,ZoomRate,QColor(255,255,255,196),x1,y1);
			}
			Pnt.setPen(Qt::red);
			Pnt.drawLine(X1,Y1,X1,Y2);
			Pnt.drawLine(X1,Y2,X2,Y2);
			Pnt.drawLine(X2,Y2,X2,Y1);
			Pnt.drawLine(X2,Y1,X1,Y1);
		}
		if(GetSelected()==true){
			//AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
			if(Index!=NULL){
				Index->DrawImage(pnt,movx,movy,ZoomRate,QColor(255,255,255,196),x1,y1);
			}
			Pnt.setPen(Qt::yellow);
			Pnt.drawLine(X1,Y1,X1,Y2);
			Pnt.drawLine(X1,Y2,X2,Y2);
			Pnt.drawLine(X2,Y2,X2,Y1);
			Pnt.drawLine(X2,Y1,X1,Y1);
		}
		else{
			//AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
			if(Index!=NULL){
				Index->DrawImage(pnt,movx,movy,ZoomRate,QColor(255,255,255,80),x1,y1);
			}
			Pnt.setPen(Qt::cyan);
			Pnt.drawLine(X1,Y1,X1,Y2);
			Pnt.drawLine(X1,Y2,X2,Y2);
			Pnt.drawLine(X2,Y2,X2,Y1);
			Pnt.drawLine(X2,Y1,X1,Y1);
		}
	}
}

//===========================================
ARArrangeInPage::ARArrangeInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate(parent)
{
}
ARArrangeInPage::~ARArrangeInPage(void)
{
}
void	ARArrangeInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqAddARArrange	*CmdReqAddARArrangeVar=dynamic_cast<CmdReqAddARArrange *>(packet);
	if(CmdReqAddARArrangeVar!=NULL){
		ARArrangeItem	*p=(ARArrangeItem *)CreateItem();
		LearningImage	*k=GetDataInPage()->Find(CmdReqAddARArrangeVar->CreatedTime);
		if(k!=NULL){
			FlexArea	FL;
			FL.SetRectangle( CmdReqAddARArrangeVar->Area.GetMinX()
							,CmdReqAddARArrangeVar->Area.GetMinY()
							,CmdReqAddARArrangeVar->Area.GetMinX()+k->GetWidth()
							,CmdReqAddARArrangeVar->Area.GetMinY()+k->GetHeight());
			p->SetArea(FL);
			p->SetIndex(k);
			AppendItem(p);
		}
		else{
			delete	p;
		}
		return;
	}
}

AlgorithmItemRoot		*ARArrangeInPage::CreateItem(int ItemClassType)
{	
	ARArrangeItem	*a=new ARArrangeItem();	
	a->SetParent(this);
	return a;
}
//===========================================
ARArrangeBase::ARArrangeBase(LayersBase *Base)
:AlgorithmBase(Base)
{
}

AlgorithmDrawAttr	*ARArrangeBase::CreateDrawAttr(void)
{
	return NULL;
}

