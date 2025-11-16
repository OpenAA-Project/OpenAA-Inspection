#include "ResultImportanceResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ResultImportance\XResultImportance.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XResultImportance.h"
#include "XGeneralFunc.h"


ResultImportanceLibrary::ResultImportanceLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
}

//=============================================================================

ResultImportanceThreshold::ResultImportanceThreshold(ResultImportanceItem *parent)
:AlgorithmThreshold(parent)
{
}

//=============================================================================
ResultImportanceItem::ResultImportanceItem(void)
{	
	ImportanceLevel=100;
	MaxCount	=0;
	RetDim=NULL;
}
ResultImportanceItem::~ResultImportanceItem(void)
{
	if(RetDim!=NULL){
		delete	[]RetDim;
		RetDim=NULL;
	}
}

bool    ResultImportanceItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,ImportanceLevel)==false)
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    ResultImportanceItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,ImportanceLevel)==false)
		return(false);

	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	return true;
}


void	ResultImportanceItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ResultImportanceBase	*ABase=tGetParentBase();
	if(ABase!=NULL){
		AlgorithmDrawAttr	A;
		A.NormalColor	=ABase->ColorArea;
		A.SelectedColor	=ABase->ColorSelected;
		A.ActiveColor	=ABase->ColorActive;
		if(ImportanceLevel<32)
			A.NormalColor	=ABase->AreaColor0;
		else if(ImportanceLevel<64)
			A.NormalColor	=ABase->AreaColor1;
		else if(ImportanceLevel<96)
			A.NormalColor	=ABase->AreaColor2;
		else if(ImportanceLevel<128)
			A.NormalColor	=ABase->AreaColor3;
		else if(ImportanceLevel<160)
			A.NormalColor	=ABase->AreaColor4;
		else if(ImportanceLevel<192)
			A.NormalColor	=ABase->AreaColor5;
		else if(ImportanceLevel<224)
			A.NormalColor	=ABase->AreaColor6;
		else if(ImportanceLevel<256)
			A.NormalColor	=ABase->AreaColor7;

		A.NormalColor.setAlpha(ABase->TransparentLevel);
		A.SelectedColor.setAlpha(ABase->TransparentLevel);
		A.ActiveColor.setAlpha(ABase->TransparentLevel);

		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

ExeResult	ResultImportanceItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	if(RetDim!=NULL){
		delete	[]RetDim;
	}
	MaxCount=GetParamGlobal()->MaxNGCountsPerCam*5;
	RetDim=new ResultPosList *[MaxCount];
	return _ER_true;
}

ExeResult	ResultImportanceItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	LocalPage=GetPage();
	ResultInspection	*R=((ResultInItemPI *)Res)->GetResultInspection();
	if(RetDim==NULL){
		MaxCount=GetParamGlobal()->MaxNGCountsPerCam*5;
		RetDim=new ResultPosList *[MaxCount];
	}
	int	N=R->GetPointerListOfResultPosList(GetArea() ,RetDim ,MaxCount);
	for(int i=0;i<N;i++){
		RetDim[i]->ImportanceLevel=ImportanceLevel;
	}

	return _ER_true;
}


//=============================================================================

ResultImportanceInPage::ResultImportanceInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<ResultImportanceItem,AlgorithmBase>(parent)
{
}
ResultImportanceInPage::~ResultImportanceInPage(void)
{
}

void	ResultImportanceInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddResultImportanceItemPacket	*CmdAddResultImportanceItemPacketVar=dynamic_cast<CmdAddResultImportanceItemPacket *>(packet);
	if(CmdAddResultImportanceItemPacketVar!=NULL){
		AlgorithmItemRoot	*item=tCreateItem();
		ResultImportanceItem	*Item=(ResultImportanceItem *)item;
		Item->SetArea(CmdAddResultImportanceItemPacketVar->Area);
		Item->ImportanceLevel	=CmdAddResultImportanceItemPacketVar->ImportanceLevel;
		AppendItem(Item);
	}
}

//=============================================================================

ResultImportanceBase::ResultImportanceBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorArea			, /**/"Color" ,/**/"ColorArea"			,LangSolver.GetString(XResultImportance_LS,LID_0)/*"Color for Area"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XResultImportance_LS,LID_1)/*"Color for Selected area"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XResultImportance_LS,LID_2)/*"Color for Active Mask"*/);
	SetParam(&NegColorArea		, /**/"Color" ,/**/"NegColorArea"		,LangSolver.GetString(XResultImportance_LS,LID_3)/*"Color for Negative area"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XResultImportance_LS,LID_4)/*"Color for Selected Negative Mask"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XResultImportance_LS,LID_5)/*"Color for Transparent display level"*/);

	AreaColor0	=Qt::green;
	AreaColor1	=Qt::yellow;
	AreaColor2	=Qt::darkRed;
	AreaColor3	=Qt::cyan;
	AreaColor4	=Qt::magenta;
	AreaColor5	=Qt::darkGreen;
	AreaColor6	=Qt::darkYellow;
	AreaColor7	=Qt::darkCyan;

	SetParam(&AreaColor0	, /**/"AreaColor" ,/**/"AreaColor0"	,LangSolver.GetString(XResultImportance_LS,LID_6)/*"Area Color 0"*/);
	SetParam(&AreaColor1	, /**/"AreaColor" ,/**/"AreaColor1"	,LangSolver.GetString(XResultImportance_LS,LID_7)/*"Area Color 1"*/);
	SetParam(&AreaColor2	, /**/"AreaColor" ,/**/"AreaColor2"	,LangSolver.GetString(XResultImportance_LS,LID_8)/*"Area Color 2"*/);
	SetParam(&AreaColor3	, /**/"AreaColor" ,/**/"AreaColor3"	,LangSolver.GetString(XResultImportance_LS,LID_9)/*"Area Color 3"*/);
	SetParam(&AreaColor4	, /**/"AreaColor" ,/**/"AreaColor4"	,LangSolver.GetString(XResultImportance_LS,LID_10)/*"Area Color 4"*/);
	SetParam(&AreaColor5	, /**/"AreaColor" ,/**/"AreaColor5"	,LangSolver.GetString(XResultImportance_LS,LID_11)/*"Area Color 5"*/);
	SetParam(&AreaColor6	, /**/"AreaColor" ,/**/"AreaColor6"	,LangSolver.GetString(XResultImportance_LS,LID_12)/*"Area Color 6"*/);
	SetParam(&AreaColor7	, /**/"AreaColor" ,/**/"AreaColor7"	,LangSolver.GetString(XResultImportance_LS,LID_13)/*"Area Color 7"*/);
}

AlgorithmDrawAttr	*ResultImportanceBase::CreateDrawAttr(void)
{
	return NULL;
}

void	ResultImportanceBase::TransmitDirectly(GUIDirectMessage *packet)
{

}
