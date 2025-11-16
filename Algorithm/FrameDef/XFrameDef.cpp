#include "FrameDef.h"
#include "XAlgorithmDLL.h"
#include "XFrameDef.h"
#include"XGeneralFunc.h"
#include"XFlexArea.h"
#include"XFlexAreaImageBuffer.h"
#include "XDisplayBitImage.h"
#include "XFrameDefPacket.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


FrameDefThreshold::FrameDefThreshold(FrameDefItem *parent)
	:AlgorithmThreshold(parent)
{
}

FrameDefItem::FrameDefItem(void)
{
	LastZoomRate	=0;

	Original=true;
	FrameNumber=-1;
}

void	FrameDefItem::SetArea(const FlexArea &area)
{
	GlobalArea=area;
	FlexArea	A;
	A=area;
	DataInPage	*pdata=GetDataInPage();
	pdata->ClipMoveAreaFromGlobal(A);
	AlgorithmItemPI::SetArea(A);
}
void    FrameDefItem::MoveTo(int dx ,int dy)
{
	GlobalArea.MoveToNoClip(dx,dy);

	FlexArea	A;
	A=GlobalArea;
	DataInPage	*pdata=GetDataInPage();
	pdata->ClipMoveAreaFromGlobal(A);
	AlgorithmItemPI::SetArea(A);
}
bool    FrameDefItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(GlobalArea.Save(f)==false)
		return false;
	if(::Save(f,Original)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,FrameNumber)==false)
		return false;

	return true;
}
bool    FrameDefItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(GlobalArea.Load(f)==false)
		return false;
	if(::Load(f,Original)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,FrameNumber)==false)
		return false;
	return true;
}
void	FrameDefItem::MakeMasterImage(QImage &MasterImage,double ZoomRate
									, int Gx1,int Gy1,int Gx2,int Gy2,int DestGCx,int DestGCy)
{
	if(Original==false)
		return;
	int	SrcGx,SrcGy;
	GlobalArea.GetCenter(SrcGx,SrcGy);
	//int	Dx=DestGCx-SrcGx;
	//int	Dy=DestGCy-SrcGy;
	XYData	*GXY=GetGlobalOutlineOffset();

	ImageBuffer *ImageList[100];
	GetParent()->GetMasterBuffList(ImageList);
					
	MasterImage=QImage(Gx2-Gx1,Gy2-Gy1,QImage::Format_ARGB32);
	MasterImage.fill(0);

	FlexArea	XArea;
	XArea=GlobalArea;
	XArea.MoveToClip(-GXY->x,-GXY->y,0,0,GetDotPerLine(),GetMaxLines());
	XArea.Draw(0,0,&MasterImage,ImageList,GetLayerNumb(),ZoomRate,-XArea.GetMinX(),-XArea.GetMinY());

}

void	FrameDefItem::MakeMasterImageFromOther(QImage &MasterImage,double ZoomRate,int Lx1,int Ly1,int Lx2,int Ly2)
{
	int	Gx1,Gy1,Gx2,Gy2;
	GetLayersBase()->GetGlobalMatrixFromLocal(GetPage(),Lx1,Ly1,Gx1,Gy1);
	GetLayersBase()->GetGlobalMatrixFromLocal(GetPage(),Lx2,Ly2,Gx2,Gy2);
	int	GCx,GCy;
	GlobalArea.GetCenter(GCx,GCy);

	QPainter	Pnt(&MasterImage);
	Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
	for(int globalPage=0;globalPage<GetLayersBase()->GetGlobalPageNumb();globalPage++){
		SlaveCommReqMasterImage		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		SlaveCommAckMasterImage		ACmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Gx1=Gx1;
		RCmd.Gy1=Gy1;
		RCmd.Gx2=Gx2;
		RCmd.Gy2=Gy2;
		RCmd.DestGCx=GCx;
		RCmd.DestGCy=GCy;
		RCmd.GroupNumber	=GroupNumber;
		RCmd.ZoomRate		=ZoomRate;
		if(RCmd.Send(globalPage,0,ACmd)==true){
			Pnt.drawImage(0,0,ACmd.MasterImage);
		}
	}
	/*
	QFile	File("Test.png");
	File.open(QIODevice::WriteOnly);
	MasterImage.save(&File,"PNG");
	*/
}

void	FrameDefItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	FrameDefDrawAttr	*FAttr=dynamic_cast<FrameDefDrawAttr *>(Attr);
	if(FAttr!=NULL && FAttr->Overlapped==true){
		if(Original==true){
			QRgb	Col=qRgba(128,255,0,128);
			GetArea().DrawAlpha(0,0,&pnt,Col,ZoomRate,movx,movy);
		}
		if(Original==false){
			int	Lx1=(GetArea().GetMinX()+movx)*ZoomRate;
			int	Ly1=(GetArea().GetMinY()+movy)*ZoomRate;
			int	Lx2=(GetArea().GetMaxX()+movx)*ZoomRate;
			int	Ly2=(GetArea().GetMaxY()+movy)*ZoomRate;
			if(0<=Lx2 && Lx1<pnt.width() && 0<=Ly2 && Ly1<pnt.height()){
				Lx1=max(0,Lx1);
				Ly1=max(0,Ly1);
				Lx2=min(pnt.width() ,Lx2);
				Ly2=min(pnt.height(),Ly2);
				if(LastZoomRate!=ZoomRate){
					FrameDefBase	*PBase=(FrameDefBase *)GetParentBase();
					LastZoomRate=ZoomRate;
					OriginImage=QImage(Lx2-Lx1,Ly2-Ly1,QImage::Format_ARGB32);
					OriginImage.fill(0);
					MakeMasterImageFromOther(OriginImage,ZoomRate,Lx1,Ly1,Lx2,Ly2);
					::AddAlphaChannel(OriginImage,PBase->TransparentLevel);
				}
				QPainter	Pnt(&pnt);
				Pnt.drawImage(Lx1,Ly1,OriginImage);

				QRgb	Col=qRgba(128,255,0,96);
				GetArea().DrawAlpha(0,0,&pnt,Col,ZoomRate,movx,movy);
			}
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
	
ExeResult	FrameDefItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	FlexArea	Area;
	XYData	*XY=GetGlobalOutlineOffset();
	Area=GlobalArea;
	Area.MoveToClip(-XY->x,-XY->y,0,0,GetDotPerLine(),GetMaxLines());
	SetArea(Area);

	if(GetLayersBase()==NULL)
		return _ER_true;
	if(GetLayersBase()->GetResultDLLBase()==NULL)
		return _ER_true;
	if(GetLayersBase()->GetResultDLLBase()->GetFirst()==NULL)
		return _ER_true;

	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
	if(RBase==NULL)
		return _ER_true;

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	int	BBL	  =RBase->NGImageBevel;
	NGAreaXLen=RBase->NGImageWidth-BBL*2;
	NGAreaYLen=RBase->NGImageHeight-BBL*2;
	NGAreaXNumb	=(W+NGAreaXLen-1)/NGAreaXLen;
	NGAreaYNumb	=(H+NGAreaYLen-1)/NGAreaYLen;

	return _ER_true;
}

void	FrameDefItem::BindResult(ResultInItemRoot *Item,ResultPosList *RPos)
{
	if(Item->IsOk()==false && RPos->IsOverlap(GetArea())==true){
		int	x1,y1,x2,y2;

		int	Mx=Item->GetAlignedX()+RPos->Rx;
		int	My=Item->GetAlignedY()+RPos->Ry;
		RPos->GetXY(x1,y1,x2,y2);

		int	Cx=(x1+x2)/2;
		int	Cy=(y1+y2)/2;
		bool	Found=false;
		for(ErrorGroup *g=Result.GetFirst();g!=NULL;g=g->GetNext()){
			int		qx1,qy1,qx2,qy2;
			g->GetXY(qx1,qy1,qx2,qy2);
			int	tx1=min(qx1,Cx+Mx);
			int	ty1=min(qy1,Cy+My);
			int	tx2=max(qx2,Cx+Mx);
			int	ty2=max(qy2,Cy+My);
			if((tx2-tx1)<NGAreaXLen && (ty2-ty1)<NGAreaYLen){
				g->SetRectangle(tx1,ty1,tx2,ty2);
				g->SetRepresentativeItem(Item,NULL);
				Found=true;
				break;
			}
		}
		if(Found==false){
			ErrorGroup	*g=new ErrorGroup(GetLayersBase());
			g->SetRectangle(Cx+Mx,Cy+My,Cx+Mx,Cy+My);
			g->SetPage(GetPage());

			g->SetCause(/**/"");
			g->SetName(GetItemName());
			g->SetRepresentativeItem(Item,NULL);

			Result.AppendList(g);
		}

		QStringList	AreaNames;
		if(RPos->AreaNames.count()==0){
			QString	AreaName;
			if(GetLayersBase()->GetLogicDLLBase()->LocalPos2Name(GetPage()  ,RPos->Px	//+a->GetAlignedX()+p->Rx
																			,RPos->Py	//+a->GetAlignedY()+p->Ry 
																			,AreaName)==true){
				AreaNames.append(AreaName);
			}
		}
		else{
			AreaNames=RPos->AreaNames;
		}

		QString	Msg
				=QString(/**/"<NGP X=\"")
				+QString::number(RPos->Px+Item->GetAlignedX()+RPos->Rx)
				+QString(/**/"\" Y=\"")
				+QString::number(RPos->Py+Item->GetAlignedY()+RPos->Ry)
				+QString(/**/"\" MX=\"")
				+QString::number(Item->GetAlignedX())
				+QString(/**/"\" MY=\"")
				+QString::number(Item->GetAlignedY())
				+QString(/**/"\" HX=\"")
				+QString::number(RPos->Rx)
				+QString(/**/"\" HY=\"")
				+QString::number(RPos->Ry);

		if(AreaNames.count()!=0){
			int	AreaNameCount=0;
			for(int k=0;k<AreaNames.count();k++){
				if(AreaNames[k].length()!=0){
					AreaNameCount++;
				}
			}
			if(AreaNameCount!=0){
				Msg=Msg+QString(/**/"\" ARA=\"#");
				for(int k=0;k<AreaNames.count();k++){
					Msg=Msg+AreaNames[k];
					if(k<AreaNames.count()-1){
						Msg=Msg+QString(",");
					}
				}
			}
		}
		AlgorithmItemRoot	*AItem=Item->GetAlgorithmItemRoot();
		AlgorithmBase		*ABase=(AItem!=NULL)?AItem->GetParentBase():NULL;
		if(GetLayersBase()->GetParamGlobal()->OutputNGCause==true){
			if(AItem!=NULL){
				Msg=Msg	+QString(/**/"\" LC=\"")
					+QString::number(AItem->GetLibID());
			}
			if(ABase!=NULL){
				LibNGTypeItem	*t=ABase->GetLibNGTypeItem(RPos->NGTypeUniqueCode);
				if(t!=NULL){
					Msg=Msg	+QString(/**/"\" TC=\"")
							+QString::number(t->TypeCode);
				}
			}
		}
		if(AItem!=NULL){	
			QString	m=AItem->OutputResult(RPos);
			if(m.isEmpty()==false){
				Msg =Msg+QString(" ")+m;
			}
		}

		Msg=Msg	+QString(/**/"\" RS1=\"")
				+QString::number(RPos->GetResult1())
				+QString(/**/"\" RS2=\"")
				+QString::number(RPos->GetResult2())
				+QString(/**/"\" RAL=\"")
				+ABase->GetLogicDLL()->GetDLLRoot()
				+QString(/**/":")
				+ABase->GetLogicDLL()->GetDLLName()
				+QString(/**/"\" LY=\"")
				+QString::number(0)
				+QString(/**/"\"/>");
		ResList<<Msg;
		
	}
}

ExeResult	FrameDefItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	Result.RemoveAll();
	ResList.clear();


	return _ER_true;
}
void	FrameDefItem::ResizeResult(void)
{
	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
	if(RBase==NULL)
		return;

	int	RWidth	=RBase->NGImageWidth;
	int	RHeight	=RBase->NGImageHeight;
	int	RWidth2	=RWidth/2;
	int	RHeight2=RHeight/2;	

	for(ErrorGroup *m=Result.GetFirst();m!=NULL;m=m->GetNext()){
		int	w=(RWidth -m->GetWidth());
		int	h=(RHeight-m->GetHeight());
		if(w>=0 && h>=0){
			int		Cx,Cy;
			m->GetCenter(Cx,Cy);
			m->SetRectangle(Cx-RWidth2 ,Cy-RHeight2 ,Cx+RWidth-RWidth2 ,Cy+RHeight-RHeight2);
		}
	}
}

//=======================================================================
FrameDefInPage::FrameDefInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
}
FrameDefInPage::~FrameDefInPage(void)
{
}
FrameDefItem	*FrameDefInPage::FindOriginalInGroup(int GroupNumber)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
		if(a!=NULL){
			if(a->GroupNumber==GroupNumber && a->Original==true){
				return a;
			}
		}
	}
	return NULL;
}
void	FrameDefInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlgoCreateFrameDefManual	*CmdAlgoCreateFrameDefManualVar=dynamic_cast<CmdAlgoCreateFrameDefManual *>(packet);
	if(CmdAlgoCreateFrameDefManualVar!=NULL){
		FrameDefItem	*item=(FrameDefItem *)CreateItem();
		item->SetArea(CmdAlgoCreateFrameDefManualVar->Area);
		item->GroupNumber	=CmdAlgoCreateFrameDefManualVar->GroupNumber;
		item->FrameNumber	=CmdAlgoCreateFrameDefManualVar->FrameNumber;
		item->Original		=CmdAlgoCreateFrameDefManualVar->Original;
		item->SetManualCreated(true);
		AppendItem(item);
		return;
	}
	CmdAckFrameContainer	*CmdAckFrameContainerVar=dynamic_cast<CmdAckFrameContainer *>(packet);
	if(CmdAckFrameContainerVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			if(a!=NULL){
				bool	Found=false;
				for(FrameList *f=CmdAckFrameContainerVar->ItemContainer->GetFirst();f!=NULL;f=f->GetNext()){
					if(f->GroupNumber==a->GroupNumber && f->FrameNumber==a->FrameNumber){
						f->Items.Add(GetGlobalPage(),a->GetID());
						Found=true;
						break;
					}
				}
				if(Found==false){
					FrameList	*f=new FrameList();
					f->GroupNumber=a->GroupNumber;
					f->FrameNumber=a->FrameNumber;
					f->Items.Add(GetGlobalPage(),a->GetID());
					f->GlobalX1	=a->GlobalArea.GetMinX();
					f->GlobalY1	=a->GlobalArea.GetMinY();
					f->GlobalX2	=a->GlobalArea.GetMaxX();
					f->GlobalY2	=a->GlobalArea.GetMaxY();
					f->Original	=a->Original;
					CmdAckFrameContainerVar->ItemContainer->AppendList(f);
				}
			}
		}
		return;
	}
	CmdAckMaxFrameNumber	*CmdAckMaxFrameNumberVar=dynamic_cast<CmdAckMaxFrameNumber *>(packet);
	if(CmdAckMaxFrameNumberVar!=NULL){
		CmdAckMaxFrameNumberVar->OriginExists=false;
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			if(a!=NULL){
				CmdAckMaxFrameNumberVar->FrameNumber=0;
				if(a->GroupNumber==CmdAckMaxFrameNumberVar->GroupNumber){
					if(a->FrameNumber>CmdAckMaxFrameNumberVar->FrameNumber){
						CmdAckMaxFrameNumberVar->FrameNumber=a->FrameNumber;
					}
					if(a->Original==true){
						CmdAckMaxFrameNumberVar->OriginExists=true;
					}
				}
			}
		}
		return;
	}
	CmdSetItemNumber	*CmdSetItemNumberVar=dynamic_cast<CmdSetItemNumber *>(packet);
	if(CmdSetItemNumberVar!=NULL){
		AlgorithmItemRoot	*Item=SearchIDItem(CmdSetItemNumberVar->ItemID);
		if(Item!=NULL){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(Item);
			if(a!=NULL){
				a->GroupNumber	=CmdSetItemNumberVar->GroupNumber;
				a->FrameNumber	=CmdSetItemNumberVar->FrameNumber;
				a->Original		=CmdSetItemNumberVar->Original;
			}
		}
		return;
	}
	CmdReqGroupList	*CmdReqGroupListVar	=dynamic_cast<CmdReqGroupList *>(packet);
	if(CmdReqGroupListVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			if(CmdReqGroupListVar->GroupList.IsInclude(a->GroupNumber)==false){
				CmdReqGroupListVar->GroupList.Add(a->GroupNumber);
			}
		}
		return;
	}
	CmdReqGroupFrameList	*CmdReqGroupFrameListVar=dynamic_cast<CmdReqGroupFrameList *>(packet);
	if(CmdReqGroupFrameListVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			GroupFrameNumberResultList	*k=new GroupFrameNumberResultList();
			k->GroupNumber=a->GroupNumber;
			k->FrameNumber=a->FrameNumber;
			CmdReqGroupFrameListVar->GroupFrameList.AppendList(k);
		}
		return;
	}
	CmdReqGroupFrameResultList	*CmdReqGroupFrameResultListVar=dynamic_cast<CmdReqGroupFrameResultList *>(packet);
	if(CmdReqGroupFrameResultListVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			GroupFrameNumberResultList	*k=new GroupFrameNumberResultList();
			k->GroupNumber	=a->GroupNumber;
			k->FrameNumber	=a->FrameNumber;
			k->NGCount		=a->Result.GetCount();
			CmdReqGroupFrameResultListVar->GroupFrameList.AppendList(k);
		}
		return;
	}
	CmdOutputResult	*CmdOutputResultVar=dynamic_cast<CmdOutputResult *>(packet);
	if(CmdOutputResultVar!=NULL){
		LayersBase	*LBase=GetLayersBase();
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			if(a->GroupNumber==CmdOutputResultVar->GroupNumber && a->FrameNumber==CmdOutputResultVar->FrameNumber){
				*CmdOutputResultVar->ResList=a->ResList;

				for(ErrorGroup *m=a->Result.GetFirst();m!=NULL;m=m->GetNext()){
					int mx1,my1,mx2,my2;
					m->GetXY(mx1,my1,mx2,my2);

					int32	Mx1=mx1;
					int32	My1=my1;
					LBase->ConvertToTop(Mx1,My1);

					*CmdOutputResultVar->ResList
						   <<QString("<NGI X=\"")
							+QString::number(Mx1)
							+QString("\" Y=\"")
							+QString::number(My1)
							+QString("\" W=\"")
							+QString::number(m->GetWidth())
							+QString("\" H=\"")
							+QString::number(m->GetHeight())
							+QString("\" MX=\"")
							+QString::number(m->GetMx())
							+QString("\" MY=\"")
							+QString::number(m->GetMy())
							+QString("\" IDX=\"")
							+QString::number(CmdOutputResultVar->Res->GetLayersBase()->GetGlobalPageFromLocal(GetPage()))
							+QString("\" Index=\"")
							+QString::number(m->GetNumber())
							+QString("\"/>");
				}
			}
		}
	}
}

void	FrameDefInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
}

static	void PosFunc(ResultInItemRoot *Item,ResultPosList *RPos,void *Something)
{
	((FrameDefItem *)Something)->BindResult(Item,RPos);
}

bool	FrameDefInPage::ExecuteManageResult	(int ExeID ,ResultInspection *Res)
{
	NGImageContainerInPhase	*Ph=Res->GetNGImageInPhase(GetPhaseCode());
	if(Ph!=NULL){
		NGImageContainerInPage	*h=Ph->GetNGImageInPage(GetPage());
		if(h!=NULL){
			h->ClearErrorGroupData();
			h->ClearNGImageData();
		}

		for(ResultBaseForAlgorithmRoot *rb=Res->GetResultBaseDimFirst();rb!=NULL;rb=rb->GetNext()){
			ResultBasePhase		*Ph=rb->GetPageDataPhase(GetPhaseCode());
			ResultInPageRoot	*rp=Ph->GetPageData(GetPage());
			if(rp==NULL)
				continue;
			for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
				rp->ExecuteFuncInAllItemPos(PosFunc,item);
			}
		}
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			if(a!=NULL){
				a->ResizeResult();
			}
		}
	}

	return true;
}
//=======================================================================
FrameDefBase::FrameDefBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorFrame			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;

	SetParam(&ColorFrame		, /**/"Color" ,/**/"ColorFrame"			,"Color for Frame area");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Frame");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Frame");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
}
FrameDefBase::~FrameDefBase(void)
{
}
AlgorithmDrawAttr	*FrameDefBase::CreateDrawAttr(void)
{
	return new FrameDefDrawAttr(GetLayersBase());
}

void	FrameDefBase::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool	FrameDefBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	FrameDefBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}
ExeResult	FrameDefBase::ExecuteManageResult		(int ExeID ,ResultInspection *Res)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			ExecuteManageResultOnPage(ExeID ,Res ,page);
		}
	}
	else{
		IntList PageList;
		GetParamGlobal()->GetStrategyPage(GetLayersBase()->GetCurrentStrategicNumberForCalc(),PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			ExecuteManageResultOnPage(ExeID ,Res ,s->GetValue());
		}
	}

	return _ER_true;
}


bool	FrameDefBase::ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage)
{
	((FrameDefBase *)GetPageData(localPage))->ExecuteManageResult(ExeID ,Res);
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
				for(ErrorGroup *e=s->GetErrorGroupDataFirst();e!=NULL && N<GetParamGlobal()->MaxNGImageNumbPerPage;e=e->GetNext()){
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
					d->AllocateBuffer(LBase->GetLayerNumb(localPage));
					d->CopyImageFromTarget(LBase->GetPhaseData()[phase]->GetPageData(localPage));
					s->AddNGImageData(d);			
					N++;
				}
					
				if(N!=0){
					DataInPage	*P=LBase->GetPageDataPhase(phase)->GetPageData(localPage);
					P->SetCompressedContainer(s);
				}
				else{
					s->SetCompressedFlag(true);
				}

			}
		}
	}

	return true;
}