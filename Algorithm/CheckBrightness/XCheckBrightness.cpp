/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCheckBrightness.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XCheckBrightnessResource.h"
#include "XCheckBrightness.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"


CheckBrightnessThreshold::CheckBrightnessThreshold(CheckBrightnessItem *parent)
:AlgorithmThreshold(parent)
{
}

void	CheckBrightnessThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	CheckBrightnessThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);

	return(true);
}
bool	CheckBrightnessThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
CheckBrightnessItem::CheckBrightnessItem(void)
{
	AVector	=NULL;
	ThreshL	=0;
	ThreshH	=256;
	RepeatableCount =1;
	CurrentNGCount	=0;
	RegNumber		=400;
	WidthL=0;
	WidthH=0;

	CurrentBrightness=0;
	ResultOK		=true;
	Condition		=_AverageMustBeInside;
}
AlgorithmItemPLI	&CheckBrightnessItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);

	const CheckBrightnessItem	*Item=dynamic_cast<const CheckBrightnessItem *>(&src);
	if(Item!=NULL){
		ThreshL			=Item->ThreshL;
		ThreshH			=Item->ThreshH;
		RepeatableCount =Item->RepeatableCount;
		CurrentNGCount	=Item->CurrentNGCount;
		RegNumber		=Item->RegNumber;
		WidthL			=Item->WidthL;
		WidthH			=Item->WidthH;
	}

	return *this;
}

void	CheckBrightnessItem::CopyThreshold(CheckBrightnessItem &src)
{
	ThreshL			=src.ThreshL;
	ThreshH			=src.ThreshH;
	RepeatableCount =src.RepeatableCount;
	CurrentNGCount	=src.CurrentNGCount;
	RegNumber		=src.RegNumber;
	WidthL			=src.WidthL;
	WidthH			=src.WidthH;
}

bool    CheckBrightnessItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false)
		return false;

	WORD	Ver=2;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	QString	tItemName=GetItemName();
	if(::Save(f,tItemName)==false)
		return false;
	if(::Save(f,ThreshL)==false)
		return false;
	if(::Save(f,ThreshH)==false)
		return false;
	if(::Save(f,RepeatableCount)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;
	int16	d=(int16)Condition;
	if(::Save(f,d)==false)
		return false;

	if(::Save(f,WidthL)==false)
		return false;
	if(::Save(f,WidthH)==false)
		return false;
	return true;
}
bool    CheckBrightnessItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	
	QString	tItemName;
	if(::Load(f,tItemName)==false)
		return false;
	SetItemName(tItemName);

	if(::Load(f,ThreshL)==false)
		return false;
	if(::Load(f,ThreshH)==false)
		return false;
	if(::Load(f,RepeatableCount)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;
	int16	d;
	if(::Load(f,d)==false)
		return false;
	Condition	=(CheckBrightnessItem::_Condition)d;

	if(Ver>=2){
		if(::Load(f,WidthL)==false)
			return false;
		if(::Load(f,WidthH)==false)
			return false;
	}
	return true;
}

void	CheckBrightnessItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SetVisible(true);
	AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	int	kx=(cx+movx)*ZoomRate;
	int	ky=(cy+movy)*ZoomRate;
	if(0<=kx && (kx+120)<pnt.width() && 0<=ky && (ky+40)<pnt.height()){
		QRect	rect(0,0,pnt.width(),pnt.height());
		QPainter	PData(&pnt);	
		PData.drawText(kx,ky,pnt.width()-kx,pnt.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Pg=")+QString::number(GetPage()) +QString(/**/" ")
						 +GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						 +QString(/**/"L=")+QString::number(ThreshL)
						 +QString(/**/", H=")+QString::number(ThreshH) 
						,&rect);
		PData.drawText(kx,ky+16,pnt.width()-kx,pnt.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"RegNo=")+QString::number(RegNumber) 
						+QString(/**/" Repeat=")+QString::number(RepeatableCount)
						,&rect);
	}
}

void	CheckBrightnessItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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
			if(Res->IsOk()==false && ZoomRate>1.0){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"Pg=")+QString::number(GetPage()) +QString(/**/" ")
						 +GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						 +QString(/**/"L=")+QString::number(ThreshL)
						 +QString(/**/", H=")+QString::number(ThreshH)
						 +QString(/**/", Now=")+QString::number(CurrentBrightness)
						,&rect);
					PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						 +QString(/**/"Repeat=")+QString::number(RepeatableCount)
						 +QString(/**/", Now=")+QString::number(CurrentNGCount)
						,&rect);
				}
			}
		}
	}
}

ExeResult	CheckBrightnessItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	CurrentNGCount=0;
	//_CrtCheckMemory();
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	return Ret;
}

ExeResult	CheckBrightnessItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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

	ImageBuffer	&IBuff=GetTargetBuff();
	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(0,0);
	Res->SetResult2(0);
	if(Condition==_AverageMustBeInside){
		double	d=GetArea().GetAverage(IBuff,mx,my);
		Res->SetResult1(d);
		if(ThreshL<=d && d<=ThreshH){
			Res->SetError(1);	//OK
			CurrentNGCount=0;
			ResultOK=true;
		}
		else{
			Res->SetError(2);	//NG
			NGFunc(Res);
		}
	}
	else if(Condition==_AllMustBeInside){
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int	y =GetArea().GetFLineAbsY(i)	+my;
			int	x1=GetArea().GetFLineLeftX(i)	+mx;
			int	x2=GetArea().GetFLineRightX(i)	+mx;
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				int	d=s[x];
				if(d<ThreshL || ThreshH<d){
					Res->SetResult1(d);
					NGFunc(Res);
					goto	Fin;
				}
			}
		}
		Res->SetError(1);	//OK
		CurrentNGCount=0;
		ResultOK=true;
		goto	Fin;
	}
	else if(Condition==_OneMustBeInsideAtLeast){
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int	y =GetArea().GetFLineAbsY(i)	+my;
			int	x1=GetArea().GetFLineLeftX(i)	+mx;
			int	x2=GetArea().GetFLineRightX(i)	+mx;
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				int	d=s[x];
				if(ThreshL<=d && d<=ThreshH){
					Res->SetError(1);	//OK
					CurrentNGCount=0;
					ResultOK=true;
					goto	Fin;
				}
			}
		}
		Res->SetResult1(0);
		NGFunc(Res);
		goto	Fin;
	}
	else if(Condition==_AverageMustBeOutside){
		double	d=GetArea().GetAverage(IBuff,mx,my);
		Res->SetResult1(d);
		if(ThreshL<=d && d<=ThreshH){
			NGFunc(Res);
		}
		else{
			Res->SetError(1);	//OK
			CurrentNGCount=0;
			ResultOK=true;
		}
	}
	else if(Condition==_AllMustBeOutside){
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int	y =GetArea().GetFLineAbsY(i)	+my;
			int	x1=GetArea().GetFLineLeftX(i)	+mx;
			int	x2=GetArea().GetFLineRightX(i)	+mx;
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				int	d=s[x];
				if(ThreshL<=d && d<=ThreshH){
					Res->SetResult1(d);
					NGFunc(Res);
					goto	Fin;
				}
			}
		}
		Res->SetError(1);	//OK
		CurrentNGCount=0;
		ResultOK=true;
		goto	Fin;
	}
	else if(Condition==_OneMustBeOutsideAtLeast){
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int	y =GetArea().GetFLineAbsY(i)	+my;
			int	x1=GetArea().GetFLineLeftX(i)	+mx;
			int	x2=GetArea().GetFLineRightX(i)	+mx;
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				int	d=s[x];
				if(d<ThreshL || ThreshH<d){
					Res->SetResult1(d);
					Res->SetError(1);	//OK
					CurrentNGCount=0;
					ResultOK=true;
					goto	Fin;
				}
			}
		}
		Res->SetResult1(0);
		NGFunc(Res);
		goto	Fin;
	}
	Fin:;

	FinishCalc();
	return _ER_true;
}

void	CheckBrightnessItem::NGFunc(ResultInItemRoot *Res)
{
	CurrentNGCount++;
	if(CurrentNGCount>=RepeatableCount){
		Res->SetError(2);	//NG
		ResultOK=false;
	}
	else{
		Res->SetError(1);	//OK
		ResultOK=true;
	}
}

void	CheckBrightnessItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOneCheckBrightness){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			CheckBrightnessInLayer	*Ly=dynamic_cast<CheckBrightnessInLayer *>(GetParentInLayer());
			UndoElement<CheckBrightnessInLayer>	*UPointer=new UndoElement<CheckBrightnessInLayer>(Ly,&CheckBrightnessInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CheckBrightnessItem *src=(CheckBrightnessItem *)Data;
			SetItemName(src->GetItemName());
			CopyThreshold(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_AllCheckBrightness){
		if(GetLibID()==((CheckBrightnessItem *)Data)->GetLibID()){
			CheckBrightnessInLayer	*Ly=dynamic_cast<CheckBrightnessInLayer *>(GetParentInLayer());
			UndoElement<CheckBrightnessInLayer>	*UPointer=new UndoElement<CheckBrightnessInLayer>(Ly,&CheckBrightnessInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CheckBrightnessItem *src=(CheckBrightnessItem *)Data;
			CopyThreshold(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessThis){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			CheckBrightnessInLayer	*Ly=dynamic_cast<CheckBrightnessInLayer *>(GetParentInLayer());
			UndoElement<CheckBrightnessInLayer>	*UPointer=new UndoElement<CheckBrightnessInLayer>(Ly,&CheckBrightnessInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CheckBrightnessItem *src=(CheckBrightnessItem *)Data;
			double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
			ThreshL	=C-src->WidthL;
			ThreshH	=C+src->WidthH;
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessAll){
		if(GetLibID()==((CheckBrightnessItem *)Data)->GetLibID()){
			CheckBrightnessInLayer	*Ly=dynamic_cast<CheckBrightnessInLayer *>(GetParentInLayer());
			UndoElement<CheckBrightnessInLayer>	*UPointer=new UndoElement<CheckBrightnessInLayer>(Ly,&CheckBrightnessInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CheckBrightnessItem *src=(CheckBrightnessItem *)Data;
			double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
			ThreshL	=C-src->WidthL;
			ThreshH	=C+src->WidthH;
		}
	}
}
//===========================================

CheckBrightnessInLayer::CheckBrightnessInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLITemplate<CheckBrightnessItem,CheckBrightnessInPage,CheckBrightnessBase>(parent)
{
}

AlgorithmItemRoot	*CheckBrightnessInLayer::CreateItem(int ItemClassType)
{	
	if(ItemClassType==0){
		CheckBrightnessItem	*a=new CheckBrightnessItem();	
		a->SetParent(this);
		return a;
	}
	else{
		return NULL;
	}
}

void	CheckBrightnessInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		CheckBrightnessItem	*item=(CheckBrightnessItem *)CreateItem(0);
		item->SetArea(CmdAddAreaManualVar->Area);
		item->SetManualCreated(true);
		item->SetItemName(CmdAddAreaManualVar->ItemName);
		item->ThreshL			=CmdAddAreaManualVar->ThreshL;
		item->ThreshH			=CmdAddAreaManualVar->ThreshH;
		item->RepeatableCount	=CmdAddAreaManualVar->RepeatableCount;
		item->RegNumber			=CmdAddAreaManualVar->RegNumber;
		item->Condition			=CmdAddAreaManualVar->Condition;
		AppendItem(item);
		return;
	}
	CmdReqCheckBrightnessInfo	*CmdReqCheckBrightnessInfoVar=dynamic_cast<CmdReqCheckBrightnessInfo *>(packet);
	if(CmdReqCheckBrightnessInfoVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			CheckBrightnessItem	*a=dynamic_cast<CheckBrightnessItem *>(L);
			if(a!=NULL){
				CheckBrightnessInfo	*item=new CheckBrightnessInfo();
				item->ItemID			=a->GetID();
				item->Page				=a->GetPage();
				item->Layer				=a->GetLayer();
				item->ItemName			=a->GetItemName();
				item->ThreshL			=a->ThreshL;
				item->ThreshH			=a->ThreshH;
				item->Condition			=a->Condition;
				int	Cx,Cy;
				a->GetCenter(Cx,Cy);
				item->Cx	=Cx;
				item->Cy	=Cy;
				a->GetXY(item->x1,item->y1 ,item->x2,item->y2);
				CmdReqCheckBrightnessInfoVar->Info->AppendList(item);
			}
		}
		return;
	}
	CmdReqItemInfo	*CmdReqItemInfoVar=dynamic_cast<CmdReqItemInfo *>(packet);
	if(CmdReqItemInfoVar!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(CmdReqItemInfoVar->ItemID);
		if(a!=NULL){
			CheckBrightnessItem	*item=dynamic_cast<CheckBrightnessItem *>(a);
			if(item!=NULL){
				CmdReqItemInfoVar->ItemName			=item->GetItemName();
				CmdReqItemInfoVar->ThreshL			=item->ThreshL;
				CmdReqItemInfoVar->ThreshH			=item->ThreshH;
				CmdReqItemInfoVar->RepeatableCount	=item->RepeatableCount;
				CmdReqItemInfoVar->RegNumber		=item->RegNumber;
				CmdReqItemInfoVar->Condition		=item->Condition;
			}
		}
		return;
	}
	CmdUpdateManual	*CmdUpdateManualVar=dynamic_cast<CmdUpdateManual *>(packet);
	if(CmdUpdateManualVar!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(CmdUpdateManualVar->ItemID);
		if(a!=NULL){
			CheckBrightnessItem	*item=dynamic_cast<CheckBrightnessItem *>(a);
			if(item!=NULL){
				item->SetItemName(CmdUpdateManualVar->ItemName);
				item->ThreshL			=CmdUpdateManualVar->ThreshL;
				item->ThreshH			=CmdUpdateManualVar->ThreshH;
				item->RepeatableCount	=CmdUpdateManualVar->RepeatableCount;
				item->RegNumber			=CmdUpdateManualVar->RegNumber;
				item->Condition			=CmdUpdateManualVar->Condition;
			}
		}
		return;
	}
	CmdReqCBPanelInfo	*CmdReqCBPanelInfoVar=dynamic_cast<CmdReqCBPanelInfo *>(packet);
	if(CmdReqCBPanelInfoVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			CheckBrightnessItem	*a=dynamic_cast<CheckBrightnessItem *>(L);
			if(a!=NULL){
				CBPanelList	*item=new CBPanelList();
				item->ItemID			=a->GetID();
				item->Layer				=a->GetLayer();
				item->ItemName			=a->GetItemName();
				item->RegNumber			=a->RegNumber;
				CmdReqCBPanelInfoVar->Info->AppendList(item);
			}
		}
		return;
	}
	CmdReqCBPanelResult	*CmdReqCBPanelResultVar=dynamic_cast<CmdReqCBPanelResult *>(packet);
	if(CmdReqCBPanelResultVar!=NULL){
		AlgorithmItemRoot		*a=SearchIDItem(CmdReqCBPanelResultVar->ItemID);
		if(a!=NULL){
			CheckBrightnessItem	*item=dynamic_cast<CheckBrightnessItem *>(a);
			if(item!=NULL){
				CmdReqCBPanelResultVar->ResultOK	=item->ResultOK;
			}
		}
		return;
	}
}
void	CheckBrightnessInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		CheckBrightnessItem	*BI=(CheckBrightnessItem *)Item;
		BI->Load(f,GetLayersBase());
	}
}
//===========================================
CheckBrightnessInPage::CheckBrightnessInPage(AlgorithmBase *parent)
:AlgorithmInPagePLITemplate<CheckBrightnessItem,CheckBrightnessInLayer,CheckBrightnessBase>(parent)
{
}
CheckBrightnessInPage::~CheckBrightnessInPage(void)
{
}

void	CheckBrightnessInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		for(IntClass *a=CmdAddAreaManualVar->LayerList.GetFirst();a!=NULL;a=a->GetNext()){
			int	Layer=a->GetValue();
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqCheckBrightnessInfo	*CmdReqCheckBrightnessInfoVar=dynamic_cast<CmdReqCheckBrightnessInfo *>(packet);
	if(CmdReqCheckBrightnessInfoVar!=NULL){
		CmdReqCheckBrightnessInfoVar->Info->RemoveAll();
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
	CmdReqCBPanelInfo	*CmdReqCBPanelInfoVar=dynamic_cast<CmdReqCBPanelInfo *>(packet);
	if(CmdReqCBPanelInfoVar!=NULL){
		GetLayerData(CmdReqCBPanelInfoVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdReqCBPanelResult	*CmdReqCBPanelResultVar=dynamic_cast<CmdReqCBPanelResult *>(packet);
	if(CmdReqCBPanelResultVar!=NULL){
		GetLayerData(CmdReqCBPanelResultVar->Layer)->TransmitDirectly(packet);
		return;
	}

}

/*
bool	CheckBrightnessInPage::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==CheckBrightnessReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==CheckBrightnessReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*CheckBrightnessInPage::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==CheckBrightnessReqThresholdReqCommand){
		return new CheckBrightnessThresholdReq();
	}
	else if(Command==CheckBrightnessReqThresholdSendCommand){
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
bool	CheckBrightnessInPage::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==CheckBrightnessReqThresholdReqCommand){
		HoughThresholdReq	*p=(HoughThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==CheckBrightnessReqThresholdSendCommand){
		HoughThresholdSend	*p=(HoughThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	CheckBrightnessInPage::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==CheckBrightnessReqThresholdReqCommand){
		HoughThresholdReq	*p=(HoughThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==CheckBrightnessReqThresholdSendCommand){
		HoughThresholdSend	*p=(HoughThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	CheckBrightnessInPage::GeneralDataReply(int32 Command,void *data)
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
CheckBrightnessBase::CheckBrightnessBase(LayersBase *Base)
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
AlgorithmDrawAttr	*CheckBrightnessBase::CreateDrawAttr(void)
{
	return new CheckBrightnessDrawAttr(GetLayersBase());
}
