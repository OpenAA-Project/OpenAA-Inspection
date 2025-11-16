/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPieceForReview.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PieceForReviewResource.h"
#include "XPieceForReview.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"
#include "XPieceForReviewPacket.h"
#include "XDataInLayerCommander.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//====================================================================

void	PieceForReviewInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddItemPieceForReview	*CmdAddItemPieceForReviewtVar=dynamic_cast<CmdAddItemPieceForReview *>(packet);
	if(CmdAddItemPieceForReviewtVar!=NULL){
		PieceForReviewItem	*item=(PieceForReviewItem *)CreateItem();
		item->AreaName		=CmdAddItemPieceForReviewtVar->AreaName;
		item->AreaNumber	=CmdAddItemPieceForReviewtVar->AreaNumber;
		item->SysRegNumber	=CmdAddItemPieceForReviewtVar->SysRegNumber;
		item->SetArea(CmdAddItemPieceForReviewtVar->Area);
		item->SetManualCreated(true);
		AppendItem(item);
		return;
	}
	CmdMakePieceForReviewList	*CmdMakePieceForReviewListVar=dynamic_cast<CmdMakePieceForReviewList *>(packet);
	if(CmdMakePieceForReviewListVar!=NULL){
		int	GlobalPage=GetGlobalPage();
		for(AlgorithmItemPI	*c=GetFirstData();c!=NULL;c=c->GetNext()){
			PieceForReviewItem	*a=dynamic_cast<PieceForReviewItem *>(c);
			if(a!=NULL){
				ItemsListPieceForReview	*r=new ItemsListPieceForReview();
				r->GlobalPage	=GlobalPage;
				r->ItemID		=c->GetID();
				r->AreaNumber	=a->AreaNumber;
				r->AreaName		=a->AreaName;
				r->SysRegNumber	=a->SysRegNumber;
				c->GetXY(r->X1,r->Y1,r->X2,r->Y2);
				CmdMakePieceForReviewListVar->ListData->AppendList(r);
			}
		}
		return;
	}
	CmdChangeItemPieceForReview	*CmdChangeItemPieceForReviewVar=dynamic_cast<CmdChangeItemPieceForReview *>(packet);
	if(CmdChangeItemPieceForReviewVar!=NULL){
		PieceForReviewItem	*item=(PieceForReviewItem *)SearchIDItem(CmdChangeItemPieceForReviewVar->ItemID);
		if(item!=NULL){
			item->AreaNumber	=CmdChangeItemPieceForReviewVar->AreaNumber;
			item->AreaName		=CmdChangeItemPieceForReviewVar->AreaName;
			item->SysRegNumber	=CmdChangeItemPieceForReviewVar->SysRegNumber;
		}
		return;
	}
}

static	void PosFunc(ResultInItemRoot *Item,ResultPosList *RPos,void *Something)
{
	((PieceForReviewItem *)Something)->BindResult(Item,RPos);
}

static	void NoAreaFunc(ResultInItemRoot *Item,ResultPosList *RPos,void *Something)
{
	if(RPos->AreaNames.count()==0){
		NGImageContainerInPage	*h=(NGImageContainerInPage	*)Something;

		ResultDLLBaseRoot	*RBase=Item->GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
		int	x1,y1,x2,y2;
		RPos->GetXY(x1,y1,x2,y2);
		if(x1==x2 && y1==y2){
			ErrorGroup *e;
			for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
				ErrorGroupPieceForReview	*g=(ErrorGroupPieceForReview *)e;
				if(g->Item!=NULL)
					continue;
				int	ex1,ey1,ex2,ey2;
				e->GetXY(ex1,ey1,ex2,ey2);
				int	rx1=min(ex1,x1);
				int	ry1=min(ey1,y1);
				int	rx2=max(ex2,x1);
				int	ry2=max(ey2,y1);
				if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
					g->SetRectangle(rx1,ry1,rx2,ry2);
					break;
				}
			}
			if(e==NULL){
				ErrorGroupPieceForReview	*g=new ErrorGroupPieceForReview(Item->GetLayersBase());
				g->SetRectangle(x1,y1,x2,y2);
				g->SetPieceAreaNumber(RPos->PieceAreaNumber);
				g->Item=NULL;
				g->SetImportanceLevel(RPos->ImportanceLevel);
				g->SetPieceAreaNumber(RPos->PieceAreaNumber);
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
				if(g->Item!=NULL)
					continue;
				int	ex1,ey1,ex2,ey2;
				e->GetXY(ex1,ey1,ex2,ey2);
				int	rx1=min(ex1,x1);
				int	ry1=min(ey1,y1);
				int	rx2=max(ex2,x2);
				int	ry2=max(ey2,y2);
				if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
					g->SetRectangle(rx1,ry1,rx2,ry2);
					break;
				}
			}
			if(e==NULL){
				if((x2-x1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (y2-y1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
					ErrorGroupPieceForReview	*g=new ErrorGroupPieceForReview(Item->GetLayersBase());
					g->SetRectangle(x1,y1,x2,y2);
					g->SetPieceAreaNumber(RPos->PieceAreaNumber);
					g->Item=NULL;
					g->SetImportanceLevel(RPos->ImportanceLevel);
					g->SetPieceAreaNumber(RPos->PieceAreaNumber);
					g->SetNGSize(RPos->NGSize);
					h->AddErrorGroupData(g);
				}
				else{
					RPos->NGShape.GetCenter(x1,y1);
					ErrorGroupPieceForReview	*g=new ErrorGroupPieceForReview(Item->GetLayersBase());
					g->SetRectangle( x1-RBase->NGImageWidth /2+RBase->NGImageBevel,y1-RBase->NGImageHeight/2+RBase->NGImageBevel
									,x2+RBase->NGImageWidth /2-RBase->NGImageBevel,y2+RBase->NGImageHeight/2-RBase->NGImageBevel);
					g->SetPieceAreaNumber(RPos->PieceAreaNumber);
					g->Item=NULL;
					g->SetImportanceLevel(RPos->ImportanceLevel);
					g->SetPieceAreaNumber(RPos->PieceAreaNumber);
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


bool	PieceForReviewInPage::ExecuteManageResult	(int ExeID ,ResultInspection *Res)
{
	NGImageContainerInPhase	*Ph=Res->GetNGImageInPhase(GetPhaseCode());
	if(Ph!=NULL){
		NGImageContainerInPage	*h=Ph->GetNGImageInPage(GetPage());
		if(h!=NULL){
			h->ClearErrorGroupData();
			h->ClearNGImageData();
		}

		for(ResultBaseForAlgorithmRoot *rb=Res->GetResultBaseDimFirst();rb!=NULL;rb=rb->GetNext()){
			ResultBasePhase		*rh=rb->GetPageDataPhase(GetPhaseCode());
			ResultInPageRoot	*rp=rh->GetPageData(GetPage());
			if(rp==NULL)
				continue;
			for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
				rp->ExecuteFuncInAllItemPos(PosFunc,item);
			}
			NGImageContainerInPage	*h=Ph->GetNGImageInPage(GetPage());
			rp->ExecuteFuncInAllItemPos(NoAreaFunc,h);
		}
	}
	return true;
}

PieceForReviewItem	*PieceForReviewInPage::FindItem(QString areaname)
{
	for(AlgorithmItemPI	*c=GetFirstData();c!=NULL;c=c->GetNext()){
		PieceForReviewItem *f=(PieceForReviewItem *)c;
		if(f->AreaName==areaname){
			return f;
		}
	}
	return NULL;
}
//===========================================================================================================

PieceForReviewBase::PieceForReviewBase(LayersBase *Base)
	:AlgorithmBase(Base)
{
	ColorPieceForReview			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorPieceForReview		=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;

	OverlappedRStrength			=100;
	OverlappedGStrength			=255;
	OverlappedBStrength			=100;

	OverlappedRStrengthActive	=255;
	OverlappedGStrengthActive	=100;
	OverlappedBStrengthActive	=100;

	OverlappedRStrengthSelected	=255;
	OverlappedGStrengthSelected	=255;
	OverlappedBStrengthSelected	=100;

	SetParam(&ColorPieceForReview	, /**/"Color" ,/**/"ColorPieceForReview"	,LangSolver.GetString(XPieceForReview_LS,LID_0)/*"Color for PieceForReview area"*/);
	SetParam(&ColorSelected			, /**/"Color" ,/**/"ColorSelected"			,LangSolver.GetString(XPieceForReview_LS,LID_1)/*"Color for Selected Piece"*/);
	SetParam(&ColorActive			, /**/"Color" ,/**/"ColorActive"			,LangSolver.GetString(XPieceForReview_LS,LID_2)/*"Color for Active Piece"*/);
	SetParam(&TransparentLevel		, /**/"Color" ,/**/"TransparentLevel"		,LangSolver.GetString(XPieceForReview_LS,LID_3)/*"Color for Transparent display level"*/);
	SetParam(&NegColorPieceForReview, /**/"Color" ,/**/"NegColorPieceForReview"	,LangSolver.GetString(XPieceForReview_LS,LID_4)/*"Color for Negative PieceForReview area"*/);
	SetParam(&NegColorSelected		, /**/"Color" ,/**/"NegColorSelected"		,LangSolver.GetString(XPieceForReview_LS,LID_5)/*"Color for Negative selected PieceForReview"*/);

	SetParam(&OverlappedRStrength	, /**/"Setting" ,/**/"OverlappedRStrength"	,LangSolver.GetString(XPieceForReview_LS,LID_6)/*"Overlapped Red Strength"*/,0,255);
	SetParam(&OverlappedGStrength	, /**/"Setting" ,/**/"OverlappedGStrength"	,LangSolver.GetString(XPieceForReview_LS,LID_7)/*"Overlapped Green Strength"*/,0,255);
	SetParam(&OverlappedBStrength	, /**/"Setting" ,/**/"OverlappedBStrength"	,LangSolver.GetString(XPieceForReview_LS,LID_8)/*"Overlapped Blue Strength"*/,0,255);

	SetParam(&OverlappedRStrengthActive	, /**/"Setting" ,/**/"OverlappedRStrengthActive"	,LangSolver.GetString(XPieceForReview_LS,LID_9)/*"Overlapped ActiveRed Strength"*/,0,255);
	SetParam(&OverlappedGStrengthActive	, /**/"Setting" ,/**/"OverlappedGStrengthActive"	,LangSolver.GetString(XPieceForReview_LS,LID_10)/*"Overlapped ActiveGreen Strength"*/,0,255);
	SetParam(&OverlappedBStrengthActive	, /**/"Setting" ,/**/"OverlappedBStrengthActive"	,LangSolver.GetString(XPieceForReview_LS,LID_11)/*"Overlapped ActiveBlue Strength"*/,0,255);

	SetParam(&OverlappedRStrengthSelected	, /**/"Setting" ,/**/"OverlappedRStrengthSelected"	,LangSolver.GetString(XPieceForReview_LS,LID_12)/*"Overlapped SelectedRed Strength"*/,0,255);
	SetParam(&OverlappedGStrengthSelected	, /**/"Setting" ,/**/"OverlappedGStrengthSelected"	,LangSolver.GetString(XPieceForReview_LS,LID_13)/*"Overlapped SelectedGreen Strength"*/,0,255);
	SetParam(&OverlappedBStrengthSelected	, /**/"Setting" ,/**/"OverlappedBStrengthSelected"	,LangSolver.GetString(XPieceForReview_LS,LID_14)/*"Overlapped SelectedBlue Strength"*/,0,255);

}
void	PieceForReviewBase::TransmitDirectly(GUIDirectMessage *packet)
{

}

ExeResult	PieceForReviewBase::ExecuteInitialAfterEdit	(int ExeID
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	if(GetParamComm()->Mastered==true){
		AreaNumberList.RemoveAll();
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),localPage);
			GUICmdReqAlgorithmGeneralData	PacketReq(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
			PacketReq.BuildData(sRoot,sName,PieceForReviewReqItemCount ,PieceForReviewSendItemCount);

			GUICmdSendAlgorithmGeneralData	PacketSend(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
			PacketReq.Send(globalPage,0,PacketSend);

			ClassPieceForReviewSendItemCount	*ThrePoint=(ClassPieceForReviewSendItemCount *)PacketSend.GetData();
			if(ThrePoint!=NULL){
				for(IntClass *c=ThrePoint->ItemAreaNumber.GetFirst();c!=NULL;c=c->GetNext()){
					if(AreaNumberList.IsInclude(c->GetValue())==false){
						AreaNumberList.Add(c->GetValue());
					}
				}
			}
		}
	}
	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

AlgorithmDrawAttr	*PieceForReviewBase::CreateDrawAttr(void)
{
	return NULL;
}

bool	PieceForReviewBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	PieceForReviewBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}

ExeResult	PieceForReviewBase::ExecuteManageResult		(int ExeID ,ResultInspection *Res)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			ExecuteManageResultOnPage(ExeID ,Res ,page);
		}
	}
	else{
		StrategicListContainer SList;
		GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumberForCalc(),SList);
		for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext()){
			ExecuteManageResultOnPage(ExeID ,Res ,s->Page);
		}
	}
	return _ER_true;
}
bool	PieceForReviewBase::ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage)
{
	((PieceForReviewInPage *)GetPageData(localPage))->ExecuteManageResult(ExeID ,Res);
	LayersBase	*LBase=GetLayersBase();
	int	ImageW	=Res->GetResultDLLBase()->NGImageWidth;
	int	ImageH	=Res->GetResultDLLBase()->NGImageHeight;
	int	Bevel	=Res->GetResultDLLBase()->NGImageBevel;
	int	quality	=Res->GetResultDLLBase()->NGImageQuality;

	for(int phase=0;phase<GetPhaseNumb();phase++){
		NGImageContainerInPhase	*Ph=Res->GetNGImageInPhase(phase);
		if(Ph!=NULL){
			NGImageContainerInPage	*s=Ph->GetNGImageInPage(localPage);
			if(s!=NULL){
				int32	N=0;
				for(ErrorGroup *e=s->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
					if(e->IsSentCompressor()==true)
						continue;
					e->SetSentCompressor(true);
					int	Cx,Cy;
					e->GetCenter(Cx,Cy);
					NGImage	*d=new NGImage(LBase);
					int	dx1,dy1,dx2,dy2;
					dx1=Cx-ImageW/2;
					dy1=Cy-ImageH/2;
					dx2=dx1+ImageW;
					dy2=dy1+ImageH;
					if(dx1<0){
						dx1=0;
						dx2=dx1+ImageW;
					}
					if(dy1<0){
						dy1=0;
						dy2=dy1+ImageH;
					}
					if(dx2>=GetDotPerLine(localPage)){
						dx2=GetDotPerLine(localPage)-1;
						dx1=dx2-ImageW;
					}
					if(dy2>=GetMaxLines(localPage)){
						dy2=GetMaxLines(localPage)-1;
						dy1=dy2-ImageH;
					}
					d->SetRectangle(dx1,dy1,dx2,dy2);
					d->SetNumber(N);
					d->SetGlobalPage(LBase->GetGlobalPageFromLocal(localPage));
					s->AddNGImageData(d);			
					N++;
				}

				if(N!=0){
					NGImage	*NGImageDim[1000];
					NGImage	**NGImageDimPointer=NGImageDim;
					if(N>sizeof(NGImageDim)/sizeof(NGImageDim[0])){
						NGImageDimPointer=new NGImage*[N];
					}
					NGImage	*c=s->GetNGImageDataFirst();
					for(int i=0;i<N && c!=NULL;i++,c=c->GetNext()){
						NGImageDimPointer[i]=c;
					}
	
					DataInPage	*P=LBase->GetPageData(localPage);
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for(int i=0;i<N;i++){
							NGImageDimPointer[i]->CompressImage(P,quality);
						}
					}
		
					if(NGImageDimPointer!=NGImageDim){
						delete	[]NGImageDimPointer;
					}
				}
			}
		}
	}

	return true;
}


bool	PieceForReviewBase::Name2GloalPos(QString Name ,int &XGlobalPos, int &YGlobalPos)
{
	for(int page=0;page<GetPageNumb();page++){
		PieceForReviewItem	*f=((PieceForReviewInPage *)GetPageData(page))->FindItem(Name);
		if(f!=NULL){
			int	cx,cy;
			f->GetCenter(cx,cy);
			
			XGlobalPos=cx+GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
			YGlobalPos=cy+GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
			return true;
		}
	}
	return false;
}
bool	PieceForReviewBase::Name2LocalPos(QString Name ,int &Page ,int &XLocalPos, int &YLocalPos)
{
	for(int page=0;page<GetPageNumb();page++){
		PieceForReviewItem	*f=((PieceForReviewInPage *)GetPageData(page))->FindItem(Name);
		if(f!=NULL){
			int	cx,cy;
			f->GetCenter(cx,cy);
			
			XLocalPos=cx;
			YLocalPos=cy;
			Page	=page;
			return true;
		}
	}
	return false;
}
bool	PieceForReviewBase::LocalPos2Name(int Page ,int XLocalPos, int YLocalPos ,QString &Name)
{
	AlgorithmItemPI	*f=((PieceForReviewInPage *)GetPageData(Page))->GetItem(XLocalPos,YLocalPos);
	if(f!=NULL){
		PieceForReviewItem	*N=(PieceForReviewItem *)f;
		Name=N->AreaName;
		return true;
	}
	return false;
}
bool	PieceForReviewBase::GlobalPos2Name(int XGlobalPos, int YGlobalPos ,QString &Name)
{
	IntList PageList;
	GetLayersBase()->GetGlobalPage(XGlobalPos, YGlobalPos ,XGlobalPos, YGlobalPos ,PageList);
	for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	page=c->GetValue();
		int	XLocalPos=XGlobalPos-GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
		int	YLocalPos=YGlobalPos-GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
		if(LocalPos2Name(page ,XLocalPos, YLocalPos ,Name)==true)
			return true;
	}
	return false;
}


bool	PieceForReviewBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==PieceForReviewReqItemCount){
		delete	data;
		return true;
	}
	else if(Command==PieceForReviewSendItemCount){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*PieceForReviewBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==PieceForReviewReqItemCount){
		return new ClassPieceForReviewReqItemCount();
	}
	else if(Command==PieceForReviewSendItemCount){
		ClassPieceForReviewSendItemCount	*pSend=new ClassPieceForReviewSendItemCount();
		if(reqData!=NULL){
			ClassPieceForReviewReqItemCount	*req=(ClassPieceForReviewReqItemCount *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
	return NULL;
}
bool	PieceForReviewBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==PieceForReviewReqItemCount){
		ClassPieceForReviewReqItemCount	*p=(ClassPieceForReviewReqItemCount *)data;
		return p->Load(f);
	}
	else if(Command==PieceForReviewSendItemCount){
		ClassPieceForReviewSendItemCount	*p=(ClassPieceForReviewSendItemCount *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	PieceForReviewBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==PieceForReviewReqItemCount){
		ClassPieceForReviewReqItemCount	*p=(ClassPieceForReviewReqItemCount *)data;
		return p->Save(f);
	}
	else if(Command==PieceForReviewSendItemCount){
		ClassPieceForReviewSendItemCount	*p=(ClassPieceForReviewSendItemCount *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
	return false;
}
bool	PieceForReviewBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==PieceForReviewReqItemCount){
		ClassPieceForReviewReqItemCount	*p=(ClassPieceForReviewReqItemCount *)data;
		return true;
	}
	else if(Command==PieceForReviewSendItemCount){
		ClassPieceForReviewSendItemCount	*p=(ClassPieceForReviewSendItemCount *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
	return false;
}

//===========================================================================================================
ClassPieceForReviewReqItemCount::ClassPieceForReviewReqItemCount(void)
{
	GlobalPage=0;
}

bool	ClassPieceForReviewReqItemCount::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	return true;
}

bool	ClassPieceForReviewReqItemCount::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	return true;
}

ClassPieceForReviewSendItemCount::ClassPieceForReviewSendItemCount(void)
{
	GlobalPage=0;
}

void	ClassPieceForReviewSendItemCount::ConstructList(ClassPieceForReviewReqItemCount *Req ,PieceForReviewBase *ABase)
{
	int	localpage=ABase->GetLayersBase()->GetLocalPageFromGlobal(Req->GlobalPage);
	PieceForReviewInPage	*APage=(PieceForReviewInPage *)ABase->GetPageData(localpage);
	GlobalPage	=Req->GlobalPage;
	ItemAreaNumber.RemoveAll();
	for(AlgorithmItemPI	*m=APage->GetFirstData();m!=NULL;m=m->GetNext()){
		PieceForReviewItem	*Am=(PieceForReviewItem *)m;
		ItemAreaNumber.Add(Am->AreaNumber);
	}
}

bool	ClassPieceForReviewSendItemCount::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	if(ItemAreaNumber.Save(f)==false){
		return false;
	}
	return true;
}

bool	ClassPieceForReviewSendItemCount::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	if(ItemAreaNumber.Load(f)==false){
		return false;
	}
	return true;
}