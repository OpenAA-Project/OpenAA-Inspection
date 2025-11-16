/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\World3D\XWorld3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XWorld3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
//#include "XWorld3DLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//=====================================================================================

World3DThreshold::World3DThreshold(World3DItem *parent)
:AlgorithmThreshold(parent)
{
}

void	World3DThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const World3DThreshold *s=(const World3DThreshold *)&src;
}
bool	World3DThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const World3DThreshold *s=(const World3DThreshold *)&src;
	return true;
}
bool	World3DThreshold::Save(QIODevice *f)
{
	WORD	Ver=World3DVersion;

	if(::Save(f,Ver)==false)
		return false;

	return true;
}

bool	World3DThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	return true;
}

//===========================================================================================

World3DItem::World3DItem(void)
{
}

World3DItem::~World3DItem(void)
{
}

World3DItem &World3DItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((World3DItem *)&src));
	return *this;
}

void	World3DItem::CopyThreshold(World3DItem &src)
{
	GetThresholdW()->CopyFrom(*((World3DThreshold *)src.GetThresholdR()));
}

void	World3DItem::CopyThresholdOnly(World3DItem &src)
{
	GetThresholdW()->CopyFrom(*((World3DThreshold *)src.GetThresholdR()));
}

bool    World3DItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;

	return true;
}
bool    World3DItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;

	return true;
}

void	World3DItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((World3DItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((World3DItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((World3DItem *)Data));
		}
	}
}

void	World3DItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
}
void	World3DItem::CopyArea(World3DItem &src)
{
	SetArea(src.GetArea());
}

void	World3DItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	World3DDrawAttr	*BAttr=dynamic_cast<World3DDrawAttr *>(Attr);
	if(BAttr!=NULL){
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	World3DItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c=Qt::red;
		c.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);

		int	GWidth	=IData.width();
		int	GHeight=IData.height();

		PData.setBrush(Qt::yellow);
		PData.setPen(Qt::yellow);
	}
}

void	World3DItem::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	World3DItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	AlgorithmItemPITemplate<World3DInPage,World3DBase>::MakeIndependentItems(AInd,LocalX ,LocalY);

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	//MasterPositions.Save(&Buff);
	AInd->Something=Buff.buffer();
}

ExeResult	World3DItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	return Ret;
}

ExeResult	World3DItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	return _ER_true;
}
