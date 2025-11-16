#include "PieceDef.h"
#include "XAlgorithmDLL.h"
#include "XPieceDef.h"
#include"XGeneralFunc.h"
#include"XFlexArea.h"
#include"XFlexAreaImageBuffer.h"
#include"XSweepPiece.h"
#include "XDisplayBitImage.h"


PieceDefThreshold::PieceDefThreshold(PieceDefItem *parent)
	:AlgorithmThreshold(parent)
{
}

PieceDefItem::PieceDefItem(void)
{
	MatchingRate=0;
	Original=true;
	SweepNumber=0;
}

bool    PieceDefItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	return true;
}
bool    PieceDefItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	return true;
}


void	PieceDefItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
}

void	PieceDefItem::Match(void)
{
}

//=======================================================================
PieceDefInPage::PieceDefInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
	PickupBmp		=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
}
PieceDefInPage::~PieceDefInPage(void)
{
	if(PickupBmp!=NULL){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
	}
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
}
void	PieceDefInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlgoCreatePieceDefManual	*CmdAlgoCreatePieceDefManualVar=dynamic_cast<CmdAlgoCreatePieceDefManual *>(packet);
	if(CmdAlgoCreatePieceDefManualVar!=NULL){
		PieceDefItem	*item=(PieceDefItem *)CreateItem();
		item->SetArea(CmdAlgoCreatePieceDefManualVar->Area);
		item->SetManualCreated(true);
		AppendItem(item);
		return;
	}
	CmdAlgoReqSeed	*CmdAlgoReqSeedVar=dynamic_cast<CmdAlgoReqSeed *>(packet);
	if(CmdAlgoReqSeedVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			if(p->GetSelected()==true){
				ImagePointerContainer ImageList;
				p->GetMasterBuffList(ImageList);
				CmdAlgoReqSeedVar->Seed->Copy(p->GetArea(),*ImageList[0],4);
				*CmdAlgoReqSeedVar->OriginalArea=p->GetArea();
				CmdAlgoReqSeedVar->SweepNumber	=p->GetID();
				return;
			}
		}
		return;
	}
	CmdAlgoSweepSeed	*CmdAlgoSweepSeedVar=dynamic_cast<CmdAlgoSweepSeed *>(packet);
	if(CmdAlgoSweepSeedVar!=NULL){
		int	W=CmdAlgoSweepSeedVar->Seed->GetArea().GetWidth();
		int	H=CmdAlgoSweepSeedVar->Seed->GetArea().GetHeight();
		ImagePointerContainer ImageList;
		GetMasterImages(ImageList);
		SweepResultContainer Found;
		PieceDefBase	*PBase=(PieceDefBase *)GetParentBase();
		
		PickupBmpXByte=(GetDotPerLine()+7)/8;
		PickupBmpYLen=GetMaxLines();
		if(PickupBmp==NULL)
			PickupBmp=MakeMatrixBuff(PickupBmpXByte,PickupBmpYLen);

		SweepPiece(*ImageList[0] ,*CmdAlgoSweepSeedVar->Seed,Found
					,PickupBmp,PickupBmpXByte,PickupBmpYLen
					,PBase->CoEfficient);
		for(SweepResult *a=Found.GetFirst();a!=NULL;a=a->GetNext()){
			PieceDefItem	*item=(PieceDefItem *)CreateItem();
			FlexArea	A=CmdAlgoSweepSeedVar->Seed->GetArea();
			A.MoveToClip(a->X,a->Y,0,0,GetDotPerLine(),GetMaxLines());
			int	cx,cy;
			A.GetCenter(cx,cy);
			if(CmdAlgoSweepSeedVar->OriginalArea->IsInclude(cx,cy)==false){
				item->SetArea(A);
				item->MatchingRate=a->MatchingRate;
				item->SetManualCreated(false);
				item->Original=false;
				item->SweepNumber=CmdAlgoSweepSeedVar->SweepNumber;
				AppendItem(item);
			}
			else{
				delete	item;
			}
		}
	}
	CmdAlgoReqDList	*CmdAlgoReqDListVar=dynamic_cast<CmdAlgoReqDList *>(packet);
	if(CmdAlgoReqDListVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			PieceDefItem	*Item=dynamic_cast<PieceDefItem *>(p);
			if(Item!=NULL){
				if(Item->Original==false){
					PieceDefInfo	*k=new PieceDefInfo();
					k->Page=0;
					Item->GetCenter(k->Cx,k->Cy);
					Item->GetXY(k->x1,k->y1,k->x2,k->y2);
					k->MatchingRate	=Item->MatchingRate;
					CmdAlgoReqDListVar->DefList.AppendList(k);
				}
			}
		}
		return;
	}
	CmdAlgoReqSeedData	*CmdAlgoReqSeedDataVar=dynamic_cast<CmdAlgoReqSeedData *>(packet);
	if(CmdAlgoReqSeedDataVar!=NULL){
		QBuffer	Buff(CmdAlgoReqSeedDataVar->SeedData);
		Buff.open(QIODevice::ReadWrite);
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			PieceDefItem	*SrcItem=dynamic_cast<PieceDefItem *>(p);
			if(SrcItem!=NULL && SrcItem->Original==true){
				int	SrcX,SrcY;
				SrcItem->GetCenter(SrcX,SrcY);
				for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					AlgorithmBase	*Ab=L->GetInstance();
					AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
					if(Ap==dynamic_cast<AlgorithmInPageRoot *>(this)){
						continue;
					}
					IntList LayerList;
					for(int Layer=0;Layer<GetLayerNumb();Layer++){
						LayerList.Add(Layer);
					}
					ListLayerAndIDPack ItemList;
					Ap->GetLayerAndItemID(SrcItem->GetArea(),ItemList ,LayerList);
					for(ListLayerAndID *k=ItemList.GetFirst();k!=NULL;k=k->GetNext()){
						AlgorithmItemRoot	*item=Ap->GetItemData(k->Layer,k->ID);
						::Save(&Buff,L->GetDLLRoot());
						::Save(&Buff,L->GetDLLName());
						::Save(&Buff,k->Layer);
						::Save(&Buff,k->ID);
						::Save(&Buff,item->GetItemClassType());
						item->Save(&Buff);
						CmdAlgoReqSeedDataVar->SeedCount++;
					}
				}
				*CmdAlgoReqSeedDataVar->OriginalArea=SrcItem->GetArea();
				CmdAlgoReqSeedDataVar->SweepNumber	=SrcItem->GetID();	
				break;
			}
		}
		return;
	}
	CmdAlgoCopyItemFromOrg	*CmdAlgoCopyItemFromOrgVar=dynamic_cast<CmdAlgoCopyItemFromOrg *>(packet);
	if(CmdAlgoCopyItemFromOrgVar!=NULL){
		int	SrcX,SrcY;
		CmdAlgoCopyItemFromOrgVar->OriginalArea.GetCenter(SrcX,SrcY);
		XYData	*SrcOffset=GetLayersBase()->GetGlobalOutlineOffset(CmdAlgoCopyItemFromOrgVar->OrgGlobalPage);
		XYData	*DstOffset=GetLayersBase()->GetGlobalOutlineOffset(GetLayersBase()->GetGlobalPageFromLocal(GetPage()));

		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			PieceDefItem	*PastedItem=dynamic_cast<PieceDefItem *>(p);
			if(PastedItem!=NULL && PastedItem->Original==false && PastedItem->SweepNumber==CmdAlgoCopyItemFromOrgVar->SweepNumber){
				int	Px,Py;
				PastedItem->GetCenter(Px,Py);

				QBuffer	Buff(&CmdAlgoCopyItemFromOrgVar->SeedData);
				Buff.open(QIODevice::ReadWrite);

				for(int i=0;i<CmdAlgoCopyItemFromOrgVar->SeedCount;i++){
					QString		DLLRoot;
					QString		DLLName;
					int32		Layer;
					int32		ID;
					int32		ClassType;
					if(::Load(&Buff,DLLRoot)==false)
						break;
					if(::Load(&Buff,DLLName)==false)
						break;
					if(::Load(&Buff,Layer)==false)
						break;
					if(::Load(&Buff,ID)==false)
						break;
					if(::Load(&Buff,ClassType)==false)
						break;
					AlgorithmBase	*DestAlgoBase=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
					if(DestAlgoBase!=NULL){
						AlgorithmInPageRoot	*DestAlgoPage=DestAlgoBase->GetPageData(GetPage());
						AlgorithmItemRoot	*DestItem=DestAlgoPage->CreateItem(ClassType);
						if(DestItem==NULL)
							break;
						if(DestItem->Load(&Buff,GetLayersBase())==false)
							break;
						int	dx=Px+DstOffset->x - (SrcX+SrcOffset->x);
						int	dy=Py+DstOffset->y - (SrcY+SrcOffset->y);
						int	Qx,Qy;
						DestItem->GetCenter(Qx,Qy);
						int	Lx=Qx+SrcOffset->x+dx - DstOffset->x;
						int	Ly=Qy+SrcOffset->y+dy - DstOffset->y;
						DestItem->MoveTo(Lx-Qx,Ly-Qy);
						DestItem->ClipPage(GetDotPerLine(),GetMaxLines());
						if(DestItem->IsNull()==false){
							DestAlgoPage->AppendItem(Layer,DestItem);
						}
						else{
							delete	DestItem;
						}
					}
				}
			}
		}
		return;
	}
	CmdAlgoMatchItems	*CmdAlgoMatchItemsVar=dynamic_cast<CmdAlgoMatchItems *>(packet);
	if(CmdAlgoMatchItemsVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			PieceDefItem	*Item=dynamic_cast<PieceDefItem *>(p);
			if(Item->GetSelected()==true){
				Item->Match();
			}
		}
	}
}

void	PieceDefInPage::CopyItems(FlexArea &SrcArea ,int mx ,int my)
{
	int	page=GetPage();
	AlgorithmBase	*ThisBase=GetParentBase();
	for(LogicDLL *f=GetLayersBase()->GetLogicDLLBase()->GetFirst();f!=NULL;f=f->GetNext()){
		AlgorithmBase	*B=f->GetInstance();
		if(B!=ThisBase){
			AlgorithmInPageRoot		*Pg=B->GetPageData(page);
			Pg->CopyItems(SrcArea ,mx ,my);
		}
	}
}

void	PieceDefInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(PickupBmp!=NULL){
		QColor	Col=Qt::red;
		Col.setAlpha(180);
		DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,Col);
	}
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
}
//=======================================================================
PieceDefBase::PieceDefBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPiece			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	CoEfficient			=0.7;

	SetParam(&ColorPiece		, /**/"Color" ,/**/"ColorPiece"			,"Color for piece area");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Piece");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Piece");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
	SetParam(&CoEfficient		, /**/"Setting" ,/**/"CoEfficient"		,"Matching rate 0-1.0");
}
PieceDefBase::~PieceDefBase(void)
{
}

AlgorithmDrawAttr	*PieceDefBase::CreateDrawAttr(void)
{
	return new PieceDefDrawAttr(GetLayersBase());
}

void	PieceDefBase::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool	PieceDefBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	PieceDefBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}