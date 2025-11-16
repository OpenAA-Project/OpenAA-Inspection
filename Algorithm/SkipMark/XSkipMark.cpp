/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XSkipMark.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XSkipMarkResource.h"
#include "XSkipMark.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XAlgorithmDLL.h"
#include "XAlgorithmBase.h"

SkipMarkThreshold::SkipMarkThreshold(SkipMarkItem *parent)
:AlgorithmThreshold(parent)
{
}

void	SkipMarkThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	SkipMarkThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);

	return(true);
}
bool	SkipMarkThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
SkipMarkItem::SkipMarkItem(void)
	:SourceItems(NULL)
{
	AVector		=NULL;
	NamingBase	=NULL;
	NamingID	=-1;
	ResultON	=false;
	NamingItem	=NULL;
}

void	SkipMarkItem::SetParent(AlgorithmInLayerPLI *parent)
{
	AlgorithmItemPLITemplate<SkipMarkInLayer,SkipMarkInPage,SkipMarkBase>::SetParent(parent);
	SourceItems.SetLayersBase(parent->GetLayersBase());
}

AlgorithmItemPLI	&SkipMarkItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);

	const SkipMarkItem	*Item=dynamic_cast<const SkipMarkItem *>(&src);
	if(Item!=NULL){
		NamingBase	=Item->NamingBase;
		NamingID	=Item->NamingID;
		ResultON	=Item->ResultON;
	}

	return *this;
}

void	SkipMarkItem::CopyThreshold(SkipMarkItem &src)
{
	NamingBase			=src.NamingBase;
	NamingID			=src.NamingID;
}

bool    SkipMarkItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false)
		return false;

	WORD	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	QString NamingDLLRoot;
	QString NamingDLLName;
	NamingBase->GetAlgorithmRootName(NamingDLLRoot ,NamingDLLName);
	if(::Save(f,NamingDLLRoot)==false)
		return false;
	if(::Save(f,NamingDLLName)==false)
		return false;
	if(::Save(f,NamingID)==false)
		return false;
	if(SourceItems.Save(f)==false)
		return false;
	return true;
}
bool    SkipMarkItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;
	
	QString NamingDLLRoot;
	QString NamingDLLName;
	if(::Load(f,NamingDLLRoot)==false)
		return false;
	if(::Load(f,NamingDLLName)==false)
		return false;
	if(::Load(f,NamingID)==false)
		return false;
	NamingBase=LBase->GetAlgorithmBase(NamingDLLRoot ,NamingDLLName);
	if(NamingBase==NULL)
		return false;
	if(SourceItems.Load(f)==false)
		return false;

	return true;
}

void	SkipMarkItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SetVisible(true);
	AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	int	kx=(cx+movx)*ZoomRate;
	int	ky=(cy+movy)*ZoomRate;
	if(NamingBase!=NULL && 0<=kx && (kx+120)<pnt.width() && 0<=ky && (ky+40)<pnt.height()){
		QRect	rect(0,0,pnt.width(),pnt.height());

		QString NamingDLLRoot;
		QString NamingDLLName;
		NamingBase->GetAlgorithmRootName(NamingDLLRoot ,NamingDLLName);

		QPainter	PData(&pnt);	
		PData.drawText(kx,ky,pnt.width()-kx,pnt.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"Pg=")+QString::number(GetPage()) +QString(/**/" ")
						 +GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						,&rect);

		AlgorithmItemRoot	*r=NamingBase->GetPageData(GetPage())->SearchIDItem(NamingID);
		QString	ItemName;
		if(r!=NULL)
			ItemName=r->GetItemName();

		PData.drawText(kx,ky+16,pnt.width()-kx,pnt.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"Naming=")+NamingDLLRoot+QString(/**/":")+NamingDLLName
						 +QString(/**/" Item=")+QString::number(NamingID) +QString(/**/":")+ItemName
						,&rect);
	}
}

void	SkipMarkItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(ZoomRate>1.0){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(NamingBase!=NULL && 0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());

					QString NamingDLLRoot;
					QString NamingDLLName;
					NamingBase->GetAlgorithmRootName(NamingDLLRoot ,NamingDLLName);

					QPainter	PData(&IData);	
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
									,Qt::AlignLeft | Qt::AlignTop
									//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
									,QString(/**/"Pg=")+QString::number(GetPage()) +QString(/**/" ")
									 +GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
									,&rect);

					AlgorithmItemRoot	*r=NamingBase->GetPageData(GetPage())->SearchIDItem(NamingID);
					QString	ItemName;
					if(r!=NULL)
						ItemName=r->GetItemName();

					PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
									,QString(/**/"Naming=")+NamingDLLRoot+QString(/**/":")+NamingDLLName
									 +QString(/**/" Item=")+QString::number(NamingID) +QString(/**/":")+ItemName
									,&rect);

					PData.drawText(kx,ky+16*2,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
									,QString(/**/"Result=")+QString((ResultON==true)?/**/"Skipped":/**/"Pass")
									,&rect);
				}
			}
		}
	}
}
struct	SkipMarkItemStruct
{
	int		Layer;
	IntList	*IDList;
	SkipMarkItem	*SkipMarkPoint;
};

static void SkipMarkItemFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	SkipMarkItemStruct	*s=(struct	SkipMarkItemStruct *)_Something;
	if(Item->GetLayer()==s->Layer && s->IDList->IsInclude(Item->GetID())==true){
		s->SkipMarkPoint->SourcePointer.Add(Item);
	}
}

struct	FindNamingArea
{
	int					NamingID;
	FlexArea			NamingArea;
	AlgorithmItemRoot	*NamingItem;
};

static void FindNamingAreaFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	FindNamingArea	*s=(struct	FindNamingArea *)_Something;
	if(s->NamingID==Item->GetID()){
		s->NamingArea=Item->GetArea();
		s->NamingItem=Item;
	}
}

struct	DestinationItemStruct
{
	FlexArea		Area;
	SkipMarkItem	*SkipMarkPoint;
};

static void DestinationItemFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	DestinationItemStruct	*s=(struct	DestinationItemStruct *)_Something;
	if(Item->GetArea().CheckOverlap(&s->Area)==true){
		s->SkipMarkPoint->DestPointer.Add(Item);
	}
}

ExeResult	SkipMarkItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	SourcePointer.RemoveAll();
	for(SkipMarkSourceAlgoList *s=SourceItems.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->AlgoBase!=NULL){
			struct	SkipMarkItemStruct	S;
			S.Layer		=GetLayer();
			S.IDList	=&s->IDList;
			S.SkipMarkPoint	=this;
			s->AlgoBase->GetPageData(GetPage())->LoopforAllItems(SkipMarkItemFunc,&S);
		}
	}
	DestPointer.RemoveAll();
	if(NamingBase!=NULL){
		struct	FindNamingArea	S;
		S.NamingID	=NamingID;
		S.NamingItem=NULL;
		NamingBase->GetPageData(GetPage())->LoopforAllItems(FindNamingAreaFunc,&S);
		NamingItem=S.NamingItem;

		struct	DestinationItemStruct	D;
		D.Area	=S.NamingArea;
		D.SkipMarkPoint	=this;
		for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
			AlgorithmBase	*ABase=DLL->GetInstance();
			if(ABase==GetParentBase() || ABase==NamingBase){
				continue;
			}
			AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
			APage->LoopforAllItems(DestinationItemFunc,&D);
		}
	}
	return Ret;
}

ExeResult	SkipMarkItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
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
	AlgorithmBasePointerContainer	AlgoBases;
	GetLayersBase()->GetAlgorithmByType(AlgoBases ,AlgorithmBit_TypeProcessing);

	FinishCalc();
	return _ER_true;
}


ExeResult	SkipMarkItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ResultON=false;
	for(AlgorithmItemPointerList *a=SourcePointer.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*Item=a->GetItem();
		if(Item->GetCurrentResult()!=NULL){
			if(Item->GetCurrentResult()->IsOk()==false){
				ResultON=true;
				break;
			}
		}
	}
	if(ResultON==true){
		for(AlgorithmItemPointerList *a=DestPointer.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemRoot	*Item=a->GetItem();
			if(Item->GetCurrentResult()!=NULL){
				Item->GetCurrentResult()->SetError(1);
			}
		}
		if(NamingItem!=NULL && NamingItem->GetCurrentResult()!=NULL){
			NamingItem->SetError(1);
		}
	}
	FinishCalc();
	return _ER_true;
}

void	SkipMarkItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOneSkipMark){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			SkipMarkInLayer	*Ly=dynamic_cast<SkipMarkInLayer *>(GetParentInLayer());
			UndoElement<SkipMarkInLayer>	*UPointer=new UndoElement<SkipMarkInLayer>(Ly,&SkipMarkInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			SkipMarkItem *src=(SkipMarkItem *)Data;
			SetItemName(src->GetItemName());
			CopyThreshold(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_AllSkipMark){
		if(GetLibID()==((SkipMarkItem *)Data)->GetLibID()){
			SkipMarkInLayer	*Ly=dynamic_cast<SkipMarkInLayer *>(GetParentInLayer());
			UndoElement<SkipMarkInLayer>	*UPointer=new UndoElement<SkipMarkInLayer>(Ly,&SkipMarkInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			SkipMarkItem *src=(SkipMarkItem *)Data;
			CopyThreshold(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessThis){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			SkipMarkInLayer	*Ly=dynamic_cast<SkipMarkInLayer *>(GetParentInLayer());
			UndoElement<SkipMarkInLayer>	*UPointer=new UndoElement<SkipMarkInLayer>(Ly,&SkipMarkInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			SkipMarkItem *src=(SkipMarkItem *)Data;
			//double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
			//ThreshL	=C-src->WidthL;
			//ThreshH	=C+src->WidthH;
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessAll){
		if(GetLibID()==((SkipMarkItem *)Data)->GetLibID()){
			SkipMarkInLayer	*Ly=dynamic_cast<SkipMarkInLayer *>(GetParentInLayer());
			UndoElement<SkipMarkInLayer>	*UPointer=new UndoElement<SkipMarkInLayer>(Ly,&SkipMarkInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			SkipMarkItem *src=(SkipMarkItem *)Data;
			//double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
			//ThreshL	=C-src->WidthL;
			//ThreshH	=C+src->WidthH;
		}
	}
}
//===========================================

SkipMarkInLayer::SkipMarkInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLITemplate<SkipMarkItem,SkipMarkInPage,SkipMarkBase>(parent)
{
}

AlgorithmItemRoot	*SkipMarkInLayer::CreateItem(int ItemClassType)
{	
	if(ItemClassType==0){
		SkipMarkItem	*a=new SkipMarkItem();	
		a->SetParent(this);
		return a;
	}
	else{
		return NULL;
	}
}

void	SkipMarkInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(CmdAddAreaManualVar->NamingDLLRoot,CmdAddAreaManualVar->NamingDLLName);
		if(ABase==NULL)
			return;
		AlgorithmItemRoot	*r=ABase->GetPageData(GetPage())->SearchIDItem(CmdAddAreaManualVar->NamingID);
		if(r==NULL)
			return;

		SkipMarkItem	*item=(SkipMarkItem *)CreateItem(0);
		item->SetArea(CmdAddAreaManualVar->Area);
		item->SetManualCreated(true);
		item->SetItemName(CmdAddAreaManualVar->ItemName);
		item->NamingBase			=ABase;
		item->NamingID				=CmdAddAreaManualVar->NamingID;

		AppendItem(item);
		return;
	}
	CmdReqSkipMarkInfo	*CmdReqSkipMarkInfoVar=dynamic_cast<CmdReqSkipMarkInfo *>(packet);
	if(CmdReqSkipMarkInfoVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			SkipMarkItem	*a=dynamic_cast<SkipMarkItem *>(L);
			if(a!=NULL){
				SkipMarkInfo	*item=new SkipMarkInfo();
				item->ItemID			=a->GetID();
				item->GlobalPage		=GetLayersBase()->GetGlobalPageFromLocal(a->GetPage());
				item->Layer				=a->GetLayer();
				item->ItemName			=a->GetItemName();
				int	Cx,Cy;
				a->GetCenter(Cx,Cy);
				item->Cx	=Cx;
				item->Cy	=Cy;
				a->GetXY(item->x1,item->y1 ,item->x2,item->y2);
				a->NamingBase->GetAlgorithmRootName(item->NamingDLLRoot,item->NamingDLLName);
				item->NamingItemID	=a->NamingID;
				AlgorithmItemRoot	*r=a->NamingBase->GetPageData(GetPage())->SearchIDItem(a->NamingID);
				if(r!=NULL)
					item->NamingItemName	=r->GetItemName();
	
				CmdReqSkipMarkInfoVar->Info->AppendList(item);
			}
		}
		return;
	}
	CmdReqItemInfo	*CmdReqItemInfoVar=dynamic_cast<CmdReqItemInfo *>(packet);
	if(CmdReqItemInfoVar!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(CmdReqItemInfoVar->ItemID);
		if(a!=NULL){
			SkipMarkItem	*item=dynamic_cast<SkipMarkItem *>(a);
			if(item!=NULL){
				CmdReqItemInfoVar->ItemName		=item->GetItemName();
				item->NamingBase->GetAlgorithmRootName(CmdReqItemInfoVar->NamingDLLRoot,CmdReqItemInfoVar->NamingDLLName);
				CmdReqItemInfoVar->NamingID		=item->NamingID;
			}
		}
		return;
	}
	CmdUpdateManual	*CmdUpdateManualVar=dynamic_cast<CmdUpdateManual *>(packet);
	if(CmdUpdateManualVar!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(CmdUpdateManualVar->ItemID);
		if(a!=NULL){
			SkipMarkItem	*item=dynamic_cast<SkipMarkItem *>(a);
			if(item!=NULL){
				AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(CmdUpdateManualVar->NamingDLLRoot,CmdUpdateManualVar->NamingDLLName);
				if(ABase==NULL)
					return;
				AlgorithmItemRoot	*r=ABase->GetPageData(GetPage())->SearchIDItem(CmdUpdateManualVar->NamingID);
				if(r==NULL)
					return;
				item->SetItemName(CmdUpdateManualVar->ItemName);
				item->NamingBase			=ABase;
				item->NamingID				=CmdUpdateManualVar->NamingID;
			}
		}
		return;
	}
	CmdReqSource	*CmdReqSourceVar=dynamic_cast<CmdReqSource *>(packet);
	if(CmdReqSourceVar!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(CmdReqSourceVar->ItemID);
		if(a!=NULL){
			SkipMarkItem	*item=dynamic_cast<SkipMarkItem *>(a);
			if(item!=NULL){
				*CmdReqSourceVar->Sources	=item->SourceItems;
			}
		}
		return;
	}
	CmdModifySource	*CmdModifySourceVar=dynamic_cast<CmdModifySource *>(packet);
	if(CmdModifySourceVar!=NULL){
		AlgorithmItemRoot		*aitem=SearchIDItem(CmdModifySourceVar->ItemID);
		if(aitem!=NULL){
			SkipMarkItem	*item=dynamic_cast<SkipMarkItem *>(aitem);
			if(item!=NULL){
				item->SourceItems	=*CmdModifySourceVar->Sources;
			}
		}
		return;
	}
}
void	SkipMarkInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		SkipMarkItem	*BI=(SkipMarkItem *)Item;
		BI->Load(f,GetLayersBase());
	}
}
//===========================================
SkipMarkInPage::SkipMarkInPage(AlgorithmBase *parent)
:AlgorithmInPagePLITemplate<SkipMarkItem,SkipMarkInLayer,SkipMarkBase>(parent)
{
}
SkipMarkInPage::~SkipMarkInPage(void)
{
}

void	SkipMarkInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		int	Layer=CmdAddAreaManualVar->Layer;
		GetLayerData(Layer)->TransmitDirectly(packet);
		return;
	}
	CmdReqSkipMarkInfo	*CmdReqSkipMarkInfoVar=dynamic_cast<CmdReqSkipMarkInfo *>(packet);
	if(CmdReqSkipMarkInfoVar!=NULL){
		CmdReqSkipMarkInfoVar->Info->RemoveAll();
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqItemInfo	*CmdReqItemInfoVar=dynamic_cast<CmdReqItemInfo *>(packet);
	if(CmdReqItemInfoVar!=NULL){
		GetLayerData(CmdReqItemInfoVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdUpdateManual	*CmdUpdateManualVar=dynamic_cast<CmdUpdateManual *>(packet);
	if(CmdUpdateManualVar!=NULL){
		GetLayerData(CmdUpdateManualVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdReqSource	*CmdReqSourceVar=dynamic_cast<CmdReqSource *>(packet);
	if(CmdReqSourceVar!=NULL){
		GetLayerData(CmdReqSourceVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdModifySource	*CmdModifySourceVar=dynamic_cast<CmdModifySource *>(packet);
	if(CmdModifySourceVar!=NULL){
		GetLayerData(CmdModifySourceVar->Layer)->TransmitDirectly(packet);
		return;
	}
}

/*
bool	SkipMarkInPage::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==SkipMarkReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==SkipMarkReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*SkipMarkInPage::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==SkipMarkReqThresholdReqCommand){
		return new SkipMarkThresholdReq();
	}
	else if(Command==SkipMarkReqThresholdSendCommand){
		HoughThresholdSend	*pSend=new HoughThresholdSend();
		if(reqData!=NULL){
			HoughThresholdReq	*req=(HoughThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	SkipMarkInPage::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==SkipMarkReqThresholdReqCommand){
		HoughThresholdReq	*p=(HoughThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==SkipMarkReqThresholdSendCommand){
		HoughThresholdSend	*p=(HoughThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	SkipMarkInPage::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==SkipMarkReqThresholdReqCommand){
		HoughThresholdReq	*p=(HoughThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==SkipMarkReqThresholdSendCommand){
		HoughThresholdSend	*p=(HoughThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	SkipMarkInPage::GeneralDataReply(int32 Command,void *data)
{
	if(Command==HoughReqThresholdReqCommand){
		HoughThresholdReq	*p=(HoughThresholdReq *)data;
		return true;
	}
	else if(Command==HoughReqThresholdSendCommand){
		HoughThresholdSend	*p=(HoughThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}
*/

//===========================================
SkipMarkBase::SkipMarkBase(LayersBase *Base)
	:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;

	SetParam(&ColorArea					, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected				, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive				, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea				, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected			, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel			, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");
}
AlgorithmDrawAttr	*SkipMarkBase::CreateDrawAttr(void)
{
	return new SkipMarkDrawAttr(GetLayersBase());
}
