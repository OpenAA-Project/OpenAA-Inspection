/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TreeMaster\XTreeMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTreeMaster.h"
#include "XGeneralFunc.h"


TreeMasterLibrary::TreeMasterLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
}

//=============================================================================

TreeMasterThreshold::TreeMasterThreshold(TreeMasterItem *parent)
:AlgorithmThreshold(parent)
{
	ThreShape=0.9;
	ThreColor=0.9;
	SearchDot=5;
}

void	TreeMasterThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const TreeMasterThreshold	*s=(const TreeMasterThreshold *)&src;
	SearchDot	=s->SearchDot;
	ThreShape	=s->ThreShape;
	ThreColor	=s->ThreColor;
}
bool	TreeMasterThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const TreeMasterThreshold	*s=(const TreeMasterThreshold *)&src;
	if(SearchDot	!=s->SearchDot)	return false;
	if(ThreShape	!=s->ThreShape)	return false;
	if(ThreColor	!=s->ThreColor)	return false;
	return true;
}
bool	TreeMasterThreshold::Save(QIODevice *f)
{
	if(::Save(f,ThreShape)==false)
		return false;
	if(::Save(f,ThreColor)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}

bool	TreeMasterThreshold::Load(QIODevice *f)
{
	if(::Load(f,ThreShape)==false)
		return false;
	if(::Load(f,ThreColor)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}

//=============================================================================

TreeMasterInPage::TreeMasterInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<TreeMasterItem,AlgorithmBase>(parent)
{
}
TreeMasterInPage::~TreeMasterInPage(void)
{
}

bool TreeMasterInPage::testLoad(QIODevice *f){
	Data.RemoveAll();
	if(AlgorithmInPageRoot::Load(f)==false){
		return false;
	}
	int32	Ver;
	if(::Load(f,Ver)==false){
		return(false);
	}
	int32	N;
	if(::Load(f,N)==false){
		return(false);
	}
	for(int i=0;i<N;i++){
		int32	ItemClassType=0;
		if(Ver>=2){
			if(::Load(f,ItemClassType)==false){
				return false;
			}
		}
		AlgorithmItemRoot	*c=CreateItem(ItemClassType);
		((AlgorithmItemPI *)c)->SetParent(this);
		if(c->Load(f,GetLayersBase())==false){
			delete	c;
            return(false);
		}
		AppendItemFromLoad(c);
		if(c->GetID()>=StartItemID){
			StartItemID=c->GetID()+1;
		}
	}
    return(true);
}

TreeMasterItem *TreeMasterInPage::getItemFromMasterCode(int MasterCode){
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
		if(item->MasterCode == MasterCode)
			return item;
	}
	return NULL;
}

void TreeMasterInPage::copyMatchingArea(TreeMasterItem *srcItem){
	TreeMasterItem *dstItem = getItemFromMasterCode(srcItem->MasterCode);
	dstItem->MatchingArea = srcItem->MatchingArea;
	if(dstItem->MatchingArea.IsNull())
		return;
	ColorLogic *Col = &dstItem->MatchingArea.GetFirst()->Color;
	QRgb rgb = Col->GetFirstBase()->GetCenter();
	QColor C(rgb);
	int R = C.red();
	int G = C.green();
	int B = C.blue();
}

void	TreeMasterInPage::RemoveItem(AlgorithmItemRoot *item)
{
	TreeMasterItem	*t=dynamic_cast<TreeMasterItem *>(item);
	if(t!=NULL){
		t->RemoveArea();
	}

	Changed=true;
	CalcDone =false;
}

void	TreeMasterInPage::DeleteSelectedItems(const IntList &LayerList)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPI *NextL=L->GetNext();
		if(L->GetSelected()==true && L->GetEditLocked()==false && L->GetVisible()==true){
			UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoDeleteSelectedItems);
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			L->Save(UndoPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

			SetChanged();
			RemoveItem(L);
			Changed=true;
			CalcDone =false;
		}
		L=NextL;
	}
}
void	TreeMasterInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddTreeMasterItemPacket	*CmdAddTreeMasterItemPacketVar=dynamic_cast<CmdAddTreeMasterItemPacket *>(packet);
	if(CmdAddTreeMasterItemPacketVar!=NULL){
		AlgorithmItemRoot	*item=tCreateItem();
		TreeMasterItem	*Item=(TreeMasterItem *)item;
		Item->TMItemID	=CmdAddTreeMasterItemPacketVar->TMItemID;
		Item->CatName	=CmdAddTreeMasterItemPacketVar->CatName;
		Item->MasterCode=CmdAddTreeMasterItemPacketVar->MasterCode;
		Item->MasterName = CmdAddTreeMasterItemPacketVar->MasterName;
		AppendItem(Item);
		return;
	}
	CmdReqMaxTMItemIDPacket	*CmdReqMaxTMItemIDPacketVar=dynamic_cast<CmdReqMaxTMItemIDPacket *>(packet);
	if(CmdReqMaxTMItemIDPacketVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*d=dynamic_cast<TreeMasterItem *>(a);
			if(d!=NULL){
				if(CmdReqMaxTMItemIDPacketVar->MaxTMItemID<d->TMItemID){
					CmdReqMaxTMItemIDPacketVar->MaxTMItemID=d->TMItemID;
				}
			}
		}
		return;
	}
	CmdAddItemAreaPacket	*CmdAddItemAreaPacketVar=dynamic_cast<CmdAddItemAreaPacket *>(packet);
	if(CmdAddItemAreaPacketVar!=NULL){
		bool	Found=false;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*d=dynamic_cast<TreeMasterItem *>(a);
			if(d!=NULL && d->TMItemID==CmdAddItemAreaPacketVar->TMItemID){
				if(CmdAddItemAreaPacketVar->Selection==1){
					AreaWithColor	*r=new AreaWithColor();
					r->Area	=CmdAddItemAreaPacketVar->Area;
					r->Color.Add(CmdAddItemAreaPacketVar->TreeMasterColor.rgb(),1);
					d->MatchingArea.AppendList(r);
					if(d->GetArea().IsNull()==true){
						d->SetArea(r->Area); // test —v‘f‘I‘ð‚Ì‚½‚ß
					}
					d->GetThresholdW()->ThreColor	=CmdAddItemAreaPacketVar->ThreColor;
					d->GetThresholdW()->ThreShape	=CmdAddItemAreaPacketVar->ThreShape;
					Found=true;
					break;
				}
				else if(CmdAddItemAreaPacketVar->Selection==2){
					FlexAreaImageListCoeff	*r=new FlexAreaImageListCoeff();
					ImageBuffer *ImageList[10];
					GetMasterBuffList(ImageList);
					r->Set(CmdAddItemAreaPacketVar->Area,*ImageList[1]);
					d->ShapeList.AppendList(r);
					if(d->GetArea().IsNull()==true){
						d->SetArea(CmdAddItemAreaPacketVar->Area); // test —v‘f‘I‘ð‚Ì‚½‚ß
					}
					d->GetThresholdW()->ThreColor	=CmdAddItemAreaPacketVar->ThreColor;
					d->GetThresholdW()->ThreShape	=CmdAddItemAreaPacketVar->ThreShape;
					d->GetThresholdW()->SearchDot	=CmdAddItemAreaPacketVar->SearchDot;
					Found=true;
					break;
				}
			}
		}
		if(Found==false){
			AlgorithmItemRoot	*item=tCreateItem();
			TreeMasterItem	*Item=dynamic_cast<TreeMasterItem *>(item);
			Item->TMItemID	=CmdAddItemAreaPacketVar->TMItemID;
			Item->CatName	=CmdAddItemAreaPacketVar->CatName;
			Item->MasterCode=CmdAddItemAreaPacketVar->MasterCode;
			Item->MasterName=CmdAddItemAreaPacketVar->MasterName;
			AppendItem(Item);
			if(CmdAddItemAreaPacketVar->Selection==1){
				AreaWithColor	*r=new AreaWithColor();
				r->Area	=CmdAddItemAreaPacketVar->Area;
				r->Color.Add(CmdAddItemAreaPacketVar->TreeMasterColor.rgb(),1);
				Item->MatchingArea.AppendList(r);
				Item->SetArea(r->Area); // test —v‘f‘I‘ð‚Ì‚½‚ß
				Item->GetThresholdW()->ThreColor	=CmdAddItemAreaPacketVar->ThreColor;
				Item->GetThresholdW()->ThreShape	=CmdAddItemAreaPacketVar->ThreShape;
			}
			else if(CmdAddItemAreaPacketVar->Selection==2){
				FlexAreaImageListCoeff	*r=new FlexAreaImageListCoeff();
				ImageBuffer *ImageList[10];
				GetMasterBuffList(ImageList);
				r->Set(CmdAddItemAreaPacketVar->Area,*ImageList[1]);
				Item->ShapeList.AppendList(r);
				Item->SetArea(CmdAddItemAreaPacketVar->Area); // test —v‘f‘I‘ð‚Ì‚½‚ß
				Item->GetThresholdW()->ThreColor	=CmdAddItemAreaPacketVar->ThreColor;
				Item->GetThresholdW()->ThreShape	=CmdAddItemAreaPacketVar->ThreShape;
				Item->GetThresholdW()->SearchDot	=CmdAddItemAreaPacketVar->SearchDot;
			}
		}
		return;
	}
	CmdSetCategoryNamePacket *CmdSetCategoryNamePacketVar=dynamic_cast<CmdSetCategoryNamePacket *>(packet);
	if(CmdSetCategoryNamePacketVar!=NULL){
		TreeMasterItem* item = getItemFromMasterCode(CmdSetCategoryNamePacketVar->MasterCode);
		if(item!=NULL)
			item->CatName = CmdSetCategoryNamePacketVar->CatName;
		return;
	}
	CmdRemoveItemPacket *CmdRemoveItemPacketVar=dynamic_cast<CmdRemoveItemPacket *>(packet);
	if(CmdRemoveItemPacketVar!=NULL){

		RemoveAgain:;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
			if(item->MasterCode == CmdRemoveItemPacketVar->MasterCode){
				decreaseItemID(item->TMItemID);
				AlgorithmInPagePI::RemoveItem(item);
				//item->Remove();
				delete	item;
				goto	RemoveAgain;
			}
		}
		return;
	}
	CmdSelectItemPacket *CmdSelectItemPacketVar=dynamic_cast<CmdSelectItemPacket *>(packet);
	if(CmdSelectItemPacketVar!=NULL){
		ReleaseAllSelectedItem();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
			if(item->MasterCode == CmdSelectItemPacketVar->MasterCode){
				item->SetSelected(true);
			}
		}
		return;
	}
	CmdSetAlertTreeMaster	*CmdSetAlertTreeMasterVar=dynamic_cast<CmdSetAlertTreeMaster *>(packet);
	if(CmdSetAlertTreeMasterVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
			if(item->MasterCode == CmdSetAlertTreeMasterVar->MasterCode){
				item->AlertMark	=CmdSetAlertTreeMasterVar->AlertMark;
			}
		}
		return;
	}
	CmdSetPickedMaser	*CmdSetPickedMaserVar=dynamic_cast<CmdSetPickedMaser *>(packet);
	if(CmdSetPickedMaserVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
			if(item->MasterName==CmdSetPickedMaserVar->MasterName){
				TreeMasterBase	*Tb=(TreeMasterBase *)GetParentBase();
				Tb->PickedMasterCode	=item->MasterCode;
				CmdSetPickedMaserVar->AlertMark	=item->AlertMark;
				break;
			}
		}
		return;
	}
}


void TreeMasterInPage::decreaseItemID(int removedID){
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
		if(item->TMItemID>removedID)
			item->TMItemID--;
	}
}

//=============================================================================

TreeMasterBase::TreeMasterBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorArea			, /**/"Color" ,/**/"ColorArea"			,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorArea		, /**/"Color" ,/**/"NegColorArea"		,"Color for Negative area");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");

	AreaColor0	=Qt::green;
	AreaColor1	=Qt::yellow;
	AreaColor2	=Qt::darkRed;
	AreaColor3	=Qt::cyan;
	AreaColor4	=Qt::magenta;
	AreaColor5	=Qt::darkGreen;
	AreaColor6	=Qt::darkYellow;
	AreaColor7	=Qt::darkCyan;

	SetParam(&AreaColor0	, /**/"AreaColor" ,/**/"AreaColor0"	,"Area Color 0");
	SetParam(&AreaColor1	, /**/"AreaColor" ,/**/"AreaColor1"	,"Area Color 1");
	SetParam(&AreaColor2	, /**/"AreaColor" ,/**/"AreaColor2"	,"Area Color 2");
	SetParam(&AreaColor3	, /**/"AreaColor" ,/**/"AreaColor3"	,"Area Color 3");
	SetParam(&AreaColor4	, /**/"AreaColor" ,/**/"AreaColor4"	,"Area Color 4");
	SetParam(&AreaColor5	, /**/"AreaColor" ,/**/"AreaColor5"	,"Area Color 5");
	SetParam(&AreaColor6	, /**/"AreaColor" ,/**/"AreaColor6"	,"Area Color 6");
	SetParam(&AreaColor7	, /**/"AreaColor" ,/**/"AreaColor7"	,"Area Color 7");

	PickedMasterCode	=-1;
	PosibilityItem		=NULL;
}

AlgorithmDrawAttr	*TreeMasterBase::CreateDrawAttr(void)
{
	return new TreeMasterDrawAttr();
}

void	TreeMasterBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCopyTreeMasterItemPacket *CmdCopyTreeMasterItemPacketVar=dynamic_cast<CmdCopyTreeMasterItemPacket *>(packet);
	if(CmdCopyTreeMasterItemPacketVar!=NULL){
		copyItem(CmdCopyTreeMasterItemPacketVar->MasterSrc,CmdCopyTreeMasterItemPacketVar->MasterDst);
		return;
	}
	CmdFoundTheMost	*CmdFoundTheMostVar=dynamic_cast<CmdFoundTheMost*>(packet);
	if(CmdFoundTheMostVar!=NULL){
		if(PickedMasterCode<0){
			IntList	MasterCodeList;
			for(int page=0;page<GetPageNumb();page++){
				TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
				for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
					TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
					if(MasterCodeList.IsInclude(item->MasterCode)==false){
						MasterCodeList.Add(item->MasterCode);
					}
				}
			}
			double	TopResult=0.0;
			TreeMasterItem	*TopItem=NULL;
			for(IntClass *c=MasterCodeList.GetFirst();c!=NULL;c=c->GetNext()){
				int	MasterCode=c->GetValue();
				TreeMasterItem	*RefItem=NULL;
				double	MatchingRate=1.0;
				for(int page=0;page<GetPageNumb();page++){
					TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
					for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
						TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
						if(item->MasterCode==MasterCode){
							MatchingRate*=item->ResultE;
							RefItem=item;
						}
					}
				}
				if(MatchingRate>TopResult){
					TopResult=MatchingRate;
					TopItem=RefItem;
				}
			}
			CmdFoundTheMostVar->Item=TopItem;
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
				for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
					TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
					if(item->MasterCode==PickedMasterCode){
						CmdFoundTheMostVar->Item=item;
						goto	MNext;
					}
				}
			}
			MNext:;
		}
		return;
	}
	CmdSetPickedMaser	*CmdSetPickedMaserVar=dynamic_cast<CmdSetPickedMaser *>(packet);
	if(CmdSetPickedMaserVar!=NULL){
		PickedMasterCode=-1;
		for(int page=0;page<GetPageNumb();page++){
			TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
			P->TransmitDirectly(CmdSetPickedMaserVar);
		}
		CmdSetPickedMaserVar->PickedMasterCode=PickedMasterCode;
		return;
	}
	CmdReqTotalResult	*CmdReqTotalResultVar=dynamic_cast<CmdReqTotalResult *>(packet);
	if(CmdReqTotalResultVar!=NULL){
		CmdReqTotalResultVar->ResultColor=1.0;
		CmdReqTotalResultVar->ResultShape=1.0;
		CmdReqTotalResultVar->ResultE	=1.0;
		CmdReqTotalResultVar->ResultOk	=true;
		for(int page=0;page<GetPageNumb();page++){
			TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
			for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
				TreeMasterItem	*item=dynamic_cast<TreeMasterItem *>(a);
				if(item->MasterCode==PickedMasterCode && item->MasterName.isNull()==false){
					CmdReqTotalResultVar->ResultColor*=item->ResultColor;
					CmdReqTotalResultVar->ResultShape*=item->ResultShape;
					CmdReqTotalResultVar->ResultE	 *=item->ResultE;
					if(item->ResultOk==false)
						CmdReqTotalResultVar->ResultOk	=false;
				}
			}
		}
		if(PosibilityItem!=NULL){
			CmdReqTotalResultVar->Posibility=PosibilityItem->MasterName;
		}
		return;
	}
}

void TreeMasterBase::copyItem(int MasterSrc,int MasterDst){
	for(int page=0;page<GetPageNumb();page++){
		DataInPage* P = GetLayersBase()->GetPageData(page);
		QString LogicFileName=P->CreateLogicFileName(MasterSrc,GetLogicDLL()
													,GetLayersBase()->GetMachineID()
													,GetLayersBase()->GetSelectedImagePath()
													,0,0);
		TreeMasterBase *base = new TreeMasterBase(GetLayersBase());
		base->SetLayersBase(GetLayersBase());
		TreeMasterInPage *ap = new TreeMasterInPage(base);
		QFile LogicFile(LogicFileName);
		if(LogicFile.open(QIODevice::ReadOnly)==false)
			return;
		if(base->testLoad(&LogicFile)==false)
			return;
		if(ap->testLoad(&LogicFile)==false)
			return;
		TreeMasterItem* item = ap->getItemFromMasterCode(MasterSrc);
		if(item==NULL)
			return;
		TreeMasterInPage* TP = (TreeMasterInPage *)GetPageData(page);
		TP->copyMatchingArea(item);
	}
}

bool TreeMasterBase::testLoad(QIODevice* f){
	int32 Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(Ver<0 || Ver>2){
		return false;
	}
	QString	dllRoot,dllName;
	if(::Load(f,dllRoot)==false){
		return false;
	}
	if(::Load(f,dllName)==false){
		return false;
	}
	int32	iAllocatedPageNumb;
	if(::Load(f,iAllocatedPageNumb)==false){
		return(false);
	}
	if(Ver>=2){
		WORD	LVer;
		if(::Load(f,LVer)==false){
			return false;
		}
	}
	return true;
}

ExeResult	TreeMasterBase::ExecutePreProcessing(int ExeID ,ResultBaseForAlgorithmRoot* Res)
{
	AlgorithmBase::ExecutePreProcessing(ExeID ,Res);

	for(int page=0;page<GetPageNumb();page++){
		TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
		int	Dx=0;
		int	Dy=0;
		QString	EffectiveShapeCode;
		for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*A=dynamic_cast<TreeMasterItem *>(a);
			if(A!=NULL){
				if(A->MasterCode==PickedMasterCode){
					EffectiveShapeCode=A->GetShapeCode();
					Dx=A->ResultDx;
					Dy=A->ResultDy;
				}
			}
		}
		for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*A=dynamic_cast<TreeMasterItem *>(a);
			if(A!=NULL){
				QString	ShapeCode=A->GetShapeCode();
				if(A->MasterCode!=PickedMasterCode && EffectiveShapeCode==ShapeCode){
					A->ExecutePreProcessingColor	(Dx ,Dy);
				}
			}
		}
	}


	TreeMasterInPage *P0 = (TreeMasterInPage *)GetPageData(0);
	for(AlgorithmItemPI	*a=P0->GetFirstData();a!=NULL;a=a->GetNext()){
		TreeMasterItem	*A=dynamic_cast<TreeMasterItem *>(a);
		if(A->MasterCode==PickedMasterCode){
			for(int page=1;page<GetPageNumb();page++){
				TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
				for(AlgorithmItemPI	*b=P->GetFirstData();b!=NULL;b=b->GetNext()){
					TreeMasterItem	*B=dynamic_cast<TreeMasterItem *>(b);
					if(B->MasterCode==PickedMasterCode){
						if(B->ResultOk==false){
							A->ResultOk=false;
						}
					}
				}
			}
		}
	}

	double	MasterResultColor=1.0;
	QString	EffectiveShapeCode;
	for(int page=0;page<GetPageNumb();page++){
		TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
		for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
			TreeMasterItem	*A=dynamic_cast<TreeMasterItem *>(a);
			if(A!=NULL){
				if(A->MasterCode==PickedMasterCode){
					EffectiveShapeCode=A->GetShapeCode();
					MasterResultColor*=A->ResultColor;
				}
			}
		}
	}
	double	MaxResultColor=MasterResultColor;
	PosibilityItem=NULL;
	for(AlgorithmItemPI	*a=P0->GetFirstData();a!=NULL;a=a->GetNext()){
		double	TargetResultColor=1.0;
		TreeMasterItem	*A=dynamic_cast<TreeMasterItem *>(a);
		if(A!=NULL){
			QString	ShapeCode=A->GetShapeCode();
			if(A->MasterCode!=PickedMasterCode && EffectiveShapeCode==ShapeCode){
				TargetResultColor*=A->ResultColor;
				for(int page=1;page<GetPageNumb();page++){
					TreeMasterInPage *P = (TreeMasterInPage *)GetPageData(page);
					for(AlgorithmItemPI	*b=P->GetFirstData();b!=NULL;b=b->GetNext()){
						TreeMasterItem	*B=dynamic_cast<TreeMasterItem *>(b);
						if(B!=NULL){
							QString	ShapeCodeB=B->GetShapeCode();
							if(B->MasterCode!=PickedMasterCode && EffectiveShapeCode==ShapeCodeB){
								TargetResultColor*=B->ResultColor;
							}
						}
					}
				}
				if(TargetResultColor>MaxResultColor){
					PosibilityItem=A;
					MaxResultColor=TargetResultColor;
				}
			}
		}
	}

	CmdFoundTheMost	Cmd(GetLayersBase());
	TransmitDirectly(&Cmd);
	if(Cmd.Item!=NULL){
		MatchedNameOfResult	=Cmd.Item->MasterName;
	}

	return _ER_true;
}