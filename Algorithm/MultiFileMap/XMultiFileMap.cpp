/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MultiFileMap\XMultiFileMap.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XMultiFileMapResource.h"
#include "XMultiFileMap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "omp.h"

MultiFileMapThreshold::MultiFileMapThreshold(MultiFileMapItem *parent)
:AlgorithmThreshold(parent)
{
}

void	MultiFileMapThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	MultiFileMapThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	return(true);
}
bool	MultiFileMapThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	return(true);
}

AlgorithmItemPI	&MultiFileMapItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    MultiFileMapItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,PosX)==false)
		return false;
	if(::Save(f,PosY)==false)
		return false;
	return true;
}
bool    MultiFileMapItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(AlgorithmItemPI::Load(f,LBase)==false)
			return false;

	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,PosX)==false)
		return false;
	if(::Load(f,PosY)==false)
		return false;
	return true;
}

void	MultiFileMapItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MultiFileMapDrawAttr	*a=dynamic_cast<MultiFileMapDrawAttr	*>(Attr);
	if(a!=NULL){
		MultiFileMapDrawAttr	A=*((MultiFileMapDrawAttr *)Attr);

		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

		QPainter	Pnt(&pnt);
		Pnt.setPen(Qt::red);

		int	x1=(GetArea().GetMinX()+movx)*ZoomRate;
		int	y1=(GetArea().GetMinY()+movy)*ZoomRate;
		int	x2=(GetArea().GetMaxX()+movx)*ZoomRate;
		int	y2=(GetArea().GetMaxY()+movy)*ZoomRate;

		Pnt.drawLine(x1,y1,x2,y1);
		Pnt.drawLine(x2,y1,x2,y2);
		Pnt.drawLine(x2,y2,x1,y2);
		Pnt.drawLine(x1,y2,x1,y1);
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

//===========================================


void	MultiFileMapInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMultiFileMapAreaPacket	*AddMArea=dynamic_cast<AddMultiFileMapAreaPacket *>(packet);
	if(AddMArea!=NULL){
		MultiFileMapItem	*MData=(MultiFileMapItem	*)CreateItem();
		MData->SetManualCreated(true);
		MData->FileName	=AddMArea->FileName;
		MData->PosX		=AddMArea->PosX;
		MData->PosY		=AddMArea->PosY;
		MData->SetArea(AddMArea->Area);
		AppendItem(MData);
		return;
	}
	ClearMultiFileMapAllPacket	*ClearMultiFileMapAllPacketVar=dynamic_cast<ClearMultiFileMapAllPacket *>(packet);
	if(ClearMultiFileMapAllPacketVar!=NULL){
		RemoveAllDatas();
		return;
	}
	CmdReqMultiFileMapInfo	*CmdReqMultiFileMapInfoVar=dynamic_cast<CmdReqMultiFileMapInfo *>(packet);
	if(CmdReqMultiFileMapInfoVar!=NULL){
		int	GlobalPage=GetLayersBase()->GetGlobalPage(CmdReqMultiFileMapInfoVar->GlobalX ,CmdReqMultiFileMapInfoVar->GlobalY);
		int	LPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
		if(LPage==GetPage()){
			int localX ,localY;
			if(GetLayersBase()->GetLocalMatrixFromGlobal(CmdReqMultiFileMapInfoVar->GlobalX ,CmdReqMultiFileMapInfoVar->GlobalY
													,localX ,localY)>=0){
				AlgorithmItemPI		*a=GetItem(localX ,localY);
				if(a!=NULL){
					MultiFileMapItem	*Item=dynamic_cast<MultiFileMapItem *>(a);
					if(Item!=NULL){
						CmdReqMultiFileMapInfoVar	->FileName	=Item->FileName;
						CmdReqMultiFileMapInfoVar	->PosX		=Item->PosX;
						CmdReqMultiFileMapInfoVar	->PosY		=Item->PosY;
					}
				}
			}
		}
		return;
	}
}

//===========================================
MultiFileMapBase::MultiFileMapBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorArea			, /**/"Color" ,/**/"ColorMask"			,LangSolver.GetString(XMultiFileMap_LS,LID_0)/*"Color for Area"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XMultiFileMap_LS,LID_1)/*"Color for Selected Area"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XMultiFileMap_LS,LID_2)/*"Color for Active Area"*/);
	SetParam(&NegColorArea		, /**/"Color" ,/**/"NegColorMask"		,LangSolver.GetString(XMultiFileMap_LS,LID_3)/*"Color for Negative Area"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XMultiFileMap_LS,LID_4)/*"Color for Selected Negative Area"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XMultiFileMap_LS,LID_5)/*"Color for Transparent display level"*/);
}

AlgorithmDrawAttr	*MultiFileMapBase::CreateDrawAttr(void)
{
	return new MultiFileMapDrawAttr();
}

bool	MultiFileMapBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

void	MultiFileMapBase::TransmitDirectly(GUIDirectMessage *packet)
{
	ClearMultiFileMapAllPacket	*ClearMultiFileMapAllPacketVar=dynamic_cast<ClearMultiFileMapAllPacket *>(packet);
	if(ClearMultiFileMapAllPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
}