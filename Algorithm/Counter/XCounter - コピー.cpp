/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XCounter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XCounterResource.h"
#include "XCounter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XMasking.h"
#include "XDisplayBitImage.h"
#include "XCriticalFunc.h"

//===========================================
CounterInPage::CounterInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<CounterItem,CounterBase>(parent)
{
	ExecuteMap=NULL;
	TempMap	=NULL;
	XLen	=0;
	YLen	=0;
	MaskPage=NULL;
	FilterON=false;
}
CounterInPage::~CounterInPage(void)
{
	if(ExecuteMap!=NULL){
		DeleteMatrixBuff(ExecuteMap,YLen);
		DeleteMatrixBuff(TempMap,YLen);
		ExecuteMap	=NULL;
		TempMap		=NULL;
		XLen		=0;
		YLen		=0;
	}
}
AlgorithmItemRoot	*CounterInPage::CreateItem(int ItemClassType)
{
	CounterItem	*Item=new CounterItem();
	Item->SetParent(this);
	return Item;
}

void	CounterInPage::UndoAppendManualItem(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}

void	CounterInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	if(CmdAddAreaManualVar!=NULL){
		RemoveAllDatas();
		CounterItem	*item=(CounterItem *)CreateItem(0);
		item->SetArea(CmdAddAreaManualVar->Area);
		item->SetManualCreated(true);
		AppendItem(item);
		item->MakeInitial();
			
		ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
		ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(GetParentBase());
		GetParentBase()->ExecuteInitialAfterEdit(0,r,ExecuteInitialAfterEdit_ChangedAlgorithm);

		return;
	}
	CmdReqItemImage	*CmdReqItemImageVar=dynamic_cast<CmdReqItemImage *>(packet);
	if(CmdReqItemImageVar!=NULL){
		CounterItem	*a=tGetFirstData();
		if(a!=NULL){
			double	ZoomRate=a->MakeImage(CmdReqItemImageVar->Width
										 ,CmdReqItemImageVar->Height
										 ,CmdReqItemImageVar->ItemImage
										 ,CmdReqItemImageVar->ItemImageWithMask
										 ,CmdReqItemImageVar->ItemBackGround);
			ZoomRate=a->GetRotatedZoomRate	(CmdReqItemImageVar->Width
											,CmdReqItemImageVar->Height);
			for(RotatedMatchingPattern *r=a->RotatedContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QImage	tImage;
				r->MakeImage(CmdReqItemImageVar->Width
							,CmdReqItemImageVar->Height
							,ZoomRate
							,tImage);
				CmdReqItemImageVar->Angles.Add(r->Angle*180/M_PI);
				CmdReqItemImageVar->RotatedImages.append(tImage);
			}
		}
		return;
	}
	CmdReqResultCount	*CmdReqResultCountVar=dynamic_cast<CmdReqResultCount *>(packet);
	if(CmdReqResultCountVar!=NULL){
		CmdReqResultCountVar->Count	 =0;
		CmdReqResultCountVar->TimeOut=false;
		for(AlgorithmItemPI *c=GetFirstData();c!=NULL;c=c->GetNext()){
			CounterItem	*Item=dynamic_cast<CounterItem *>(c);
			CmdReqResultCountVar->Count	+=Item->ResultCount;
			if(Item->TimeOut==true){
				CmdReqResultCountVar->TimeOut=true;
			}
		}
		return;
	}
	CmdReqAdoptedRate	*CmdReqAdoptedRateVar=dynamic_cast<CmdReqAdoptedRate *>(packet);
	if(CmdReqAdoptedRateVar!=NULL){
		CounterItem	*a=tGetFirstData();
		if(a!=NULL){
			CmdReqAdoptedRateVar->AdoptedRate=a->GetThresholdR(GetLayersBase())->AdoptedRate;
		}
		return;
	}
	CmdSetAdoptedRate	*CmdSetAdoptedRateVar=dynamic_cast<CmdSetAdoptedRate *>(packet);
	if(CmdSetAdoptedRateVar!=NULL){
		for(AlgorithmItemPI *c=GetFirstData();c!=NULL;c=c->GetNext()){
			CounterItem	*Item=dynamic_cast<CounterItem *>(c);
			Item->GetThresholdW()->AdoptedRate=CmdSetAdoptedRateVar->AdoptedRate;
		}
		return;
	}
	CmdSetBackGround	*CmdSetBackGroundVar=dynamic_cast<CmdSetBackGround *>(packet);
	if(CmdSetBackGroundVar!=NULL){
		SetBackGround();
		return;
	}
	CmdReqItemArea	*CmdReqItemAreaVar=dynamic_cast<CmdReqItemArea *>(packet);
	if(CmdReqItemAreaVar!=NULL){
		for(AlgorithmItemPI *c=GetFirstData();c!=NULL;c=c->GetNext()){
			CounterItem	*Item=dynamic_cast<CounterItem *>(c);
			PureFlexAreaList	*p=new PureFlexAreaList();
			*p=Item->GetArea();
			CmdReqItemAreaVar->Areas->AppendList(p);
		}
		return;
	}
	CmdSetFilterMode	*CmdSetFilterModeVar=dynamic_cast<CmdSetFilterMode *>(packet);
	if(CmdSetFilterModeVar!=NULL){
		FilterON=CmdSetFilterModeVar->FilterON;
		return;
	}
}

void	CounterInPage::SetBackGround(void)
{
	AlgorithmBase	*MaskBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	AlgorithmInPageRoot	*MaskPage=NULL;
	if(MaskBase!=NULL){
		MaskPage=MaskBase->GetPageData(GetPage());
	}

	int	LayerNumb=min(GetLayerNumb(),3);
	for(int layer=0;layer<LayerNumb;layer++){
		if(MaskPage!=NULL){
			MaskingInLayer	*MaskLayer=(MaskingInLayer *)MaskPage->GetLayerData(layer);
			if(MaskLayer->BackGroundImage.IsNull()==false){
				ImageBuffer	*BackGroundImage=&MaskLayer->BackGroundImage;
				qint64	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				for(int y=0;y<YLen;y++){
					BYTE	*s=BackGroundImage->GetYWithoutDepended(y);
					for(int x=0;x<XLen;x++){
						BrightTable[s[x]]++;
					}
				}
				qint64	MaxD=0;
				int		Index=0;
				for(int i=0;i<256;i++){
					if(MaxD<BrightTable[i]){
						MaxD=BrightTable[i];
						Index=i;
					}
				}
				MostPixelsInBrightness[layer]=Index;
			}
		}
	}
}

void	CounterInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePITemplate<CounterItem,CounterBase>::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);

	CounterDrawAttr	*MAttr=dynamic_cast<CounterDrawAttr *>(Attr);
	if(MAttr!=NULL){
		if(MAttr->ShowExecuteMap==true){
			int		XByte=(XLen+7)/8;
			::DrawBitImageOr(pnt, (const BYTE **)ExecuteMap ,XLen ,XByte ,YLen
							,movx ,movy ,ZoomRate
							,0,0
							,Qt::darkYellow);

			QRgb Col=qRgba(255,0,0,128);
			MutexExecutedPickedFPack.lock();
			for(PureFlexAreaList *f=ExecutedPickedFPack.GetFirst();f!=NULL;f=f->GetNext()){
				f->DrawAlpha(0 ,0 ,&pnt ,Col
										,ZoomRate ,movx ,movy);
			}
			MutexExecutedPickedFPack.unlock();
		}
	}
}

ExeResult	CounterInPage::ExecuteInitialAfterEdit	(int ExeID 
													,ResultInPageRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	XLen	=GetDotPerLine();
	YLen	=GetMaxLines();
	int		XByte=(XLen+7)/8;
	if(ExecuteMap!=NULL){
		DeleteMatrixBuff(ExecuteMap,YLen);
	}
	if(TempMap!=NULL){
		DeleteMatrixBuff(TempMap,YLen);
	}
	ExecuteMap	=MakeMatrixBuff(XByte,YLen);
	TempMap		=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear	(ExecuteMap ,0 ,XByte,YLen);

	AlgorithmBase	*MaskBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	MaskPage=NULL;
	if(MaskBase!=NULL){
		MaskPage=MaskBase->GetPageData(GetPage());
	}

	ExeResult	Ret=AlgorithmInPagePITemplate<CounterItem,CounterBase>::ExecuteInitialAfterEdit	(ExeID ,Res,ExecuteInitialAfterEdit_Changed);
	return Ret;
}

ExeResult	CounterInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	DWORD	NowMilisec=::GetComputerMiliSec();
	ImagePointerContainer ImageList;
	GetTargetBuffList	(ImageList);

	int	CountBackGround=0;
	ImageBuffer	*BackGroundImage[100];
	ImageBuffer	*MotherImage[100];
	int	LayerNumb=min(GetLayerNumb(),3);

	for(int layer=0;layer<LayerNumb;layer++){
		BackGroundImage[layer]=NULL;
		if(MaskPage!=NULL){
			MaskingInLayer	*MaskLayer=(MaskingInLayer *)MaskPage->GetLayerData(layer);
			if(MaskLayer->BackGroundImage.IsNull()==false){
				BackGroundImage[layer]=&MaskLayer->BackGroundImage;
				CountBackGround++;
			}
		}
		MotherImage[layer]=ImageList[layer];
	}
	int		XByte=(XLen+7)/8;

	CounterBase	*ABase=(CounterBase *)GetParentBase();
	int64	PickedPixels=0;

	int		MasterBack[3];
	int		MasterBackH[3];

	MasterBack[0]=0;
	MasterBack[1]=0;
	MasterBack[2]=0;
	MasterBackH[0]=0;
	MasterBackH[1]=0;
	MasterBackH[2]=0;

	MatrixBuffClear	(ExecuteMap ,0 ,XByte,YLen);
	CounterItem	*Item=tGetFirstData();
	if(Item!=NULL){
		for(int layer=0;layer<LayerNumb;layer++){
			qint64	BrightTable[256];
			memset(BrightTable,0,sizeof(BrightTable));

			int	NYLen=YLen/2;

			#pragma omp parallel for
			for(int i=0;i<NYLen;i++){
				int	y=i*2;
				BYTE	*s=MotherImage[layer]->GetYWithoutDepended(y);
				for(int x=0;x<XLen;x++){
					#pragma omp	atomic
					BrightTable[s[x]]++;
				}
			}
			qint64	MaxD=0;
			int		Index=0;
			for(int i=0;i<256;i++){
				if(MaxD<BrightTable[i]){
					MaxD=BrightTable[i];
					Index=i;
				}
			}

			MasterBack[layer]=Index;

			qint64	LastD=MaxD;
			for(;Index<255;Index++){
				if(BrightTable[Index]>LastD){
					break;
				}
				LastD=BrightTable[Index];
			}
			Index++;
			MasterBackH[layer]=Index;
		}
		const	CounterThreshold	*RThr=Item->GetThresholdR(GetLayersBase());
		int		NoisePass=RThr->NoiseLevel;
		if(CountBackGround==GetLayerNumb()){
			int	DiffAvr[100];
			for(int layer=0;layer<LayerNumb;layer++){
				DiffAvr[layer]=MasterBack[layer]-MostPixelsInBrightness[layer];
			}
			#pragma omp parallel for
			for(int y=0;y<YLen;y++){
				BYTE	*s[100];
				BYTE	*b[100];
				for(int layer=0;layer<LayerNumb;layer++){
					s[layer]=MotherImage[layer]		->GetYWithoutDepended(y);
					b[layer]=BackGroundImage[layer]	->GetYWithoutDepended(y);
				}
				BYTE	*d=ExecuteMap[y];
				for(int x=0;x<XLen;x++){
					int layer;
					for(layer=0;layer<LayerNumb;layer++){
						int	t=abs((s[layer])[x]-((b[layer])[x]+DiffAvr[layer]));
						if(t>NoisePass){
							break;
						}
					}
					if(layer<LayerNumb){
						SetBmpBitOnY1(d,x);
					}
				}
			}
		}
		else{
			#pragma omp parallel for
			for(int y=0;y<YLen;y++){
				BYTE	*s[100];
				for(int layer=0;layer<LayerNumb;layer++){
					s[layer]=MotherImage[layer]->GetYWithoutDepended(y);
				}
				BYTE	*d=ExecuteMap[y];
				for(int x=0;x<XLen;x++){
					int layer;
					for(layer=0;layer<LayerNumb;layer++){
						int	t=abs((s[layer])[x]-MasterBack[layer]);
						if(t>NoisePass){
							break;
						}
					}
					if(layer<LayerNumb){
						SetBmpBitOnY1(d,x);
					}
				}
			}
		}
		if(FilterON==true){
			int	ReduceNoise=5;
			if(ReduceNoise>0){
				GetLayersBase()->FatAreaN(ExecuteMap
							,TempMap
							,XByte ,YLen
							,ReduceNoise);
			
				GetLayersBase()->ThinAreaN(ExecuteMap
							,TempMap
							,XByte ,YLen
							,ReduceNoise*2);
			
				GetLayersBase()->FatAreaN(ExecuteMap
							,TempMap
							,XByte ,YLen
							,ReduceNoise);
			}
		}

		GetLayersBase()->FatAreaN(ExecuteMap
					,TempMap
					,XByte ,YLen
					,2);

		int	ItemObjectPixels=Item->PickedAreaInPattern.GetPatternByte()*ABase->AdoptPixelsRate;
		MutexExecutedPickedFPack.lock();
		ExecutedPickedFPack.RemoveAll();
		PickupFlexArea(ExecuteMap ,XByte ,XLen,YLen ,ExecutedPickedFPack ,10000);
		for(PureFlexAreaList *f=ExecutedPickedFPack.GetFirst();f!=NULL;){
			PureFlexAreaList *NextF=f->GetNext();
			if(f->GetPatternByte()<ItemObjectPixels){
				ExecutedPickedFPack.RemoveList(f);
				delete	f;
			}
			else{
				PickedPixels+=f->GetPatternByte();
			}
			f=NextF;
		}
		MutexExecutedPickedFPack.unlock();
	}
	NowMilisec1=::GetComputerMiliSec()-NowMilisec;

	MutexExecutedPickedFPack.lock();
	int	ExecutedPickedFPackCount=ExecutedPickedFPack.GetCount();
	MutexExecutedPickedFPack.unlock();

	ExeResult	Ret=_ER_true;
	if(Item!=NULL){
		CounterThreshold	*WThr=Item->GetThresholdW(GetLayersBase());
		if(PickedPixels>GetDotPerLine()*GetMaxLines()*ABase->MaxPickedPixelsRate
		&& ((MasterBackH[0]-MasterBack[0]+50)>WThr->NoiseLevel)
		&& ((MasterBackH[1]-MasterBack[1]+50)>WThr->NoiseLevel)
		&& ((MasterBackH[2]-MasterBack[2]+50)>WThr->NoiseLevel)){
			WThr->NoiseLevel++;
		}
		else
		if(ExecutedPickedFPackCount==0
		&& WThr->NoiseLevel>0){
			WThr->NoiseLevel--;
		}
		else{
			Ret=AlgorithmInPagePITemplate<CounterItem,CounterBase>::ExecuteProcessing	(ExeID ,Res);
		}
	}

	NowMilisec2=::GetComputerMiliSec()-NowMilisec;
	return Ret;
}

//===========================================
CounterBase::CounterBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;
	TextColor		=Qt::black;
	MaxMatchingResultCount	=300;
	MinAreaPiece	=200;
	AdoptPixelsRate	=0.5;
	MaxPickedPixelsRate	=1.0/30.0;
	AngleStep		=2.5;
	CrossRateInPickedArea	=0.5;
	RotationalSame	=0.95;
	SkipFlat		=4;
	CountIndexLine	=3;
	NonOverlappedRate	=0.8;

	ItemColor0	=Qt::green;
	ItemColor1	=Qt::magenta;
	ItemColor2	=Qt::cyan;
	ItemColor3	=Qt::darkRed;
	ItemColor4	=Qt::blue;
	ItemColor5	=Qt::yellow;
	ItemColor6	=Qt::darkGreen;
	ItemColor7	=Qt::darkYellow;

	SetParam(&ColorArea					, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected				, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive				, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea				, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected			, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel			, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");
	SetParam(&TextColor					, /**/"Color"	,/**/"TextColor"			,"Color for text message");

	SetParam(&MaxMatchingResultCount	, /**/"Setting"	,/**/"MaxMatchingResultCount","Maximum matching-result count");
	SetParam(&MinAreaPiece				, /**/"Setting"	,/**/"MinAreaPiece"			,"Minimum area in picked^up item area");
	SetParam(&AdoptPixelsRate			, /**/"Setting"	,/**/"AdoptPixelsRate"		,"Rate(0-1.0) of pixels to adopt target area");
	SetParam(&MaxPickedPixelsRate		, /**/"Setting"	,/**/"MaxPickedPixelsRate"	,"Maximum PickedPixels Rate(0-1.0)");
	SetParam(&AngleStep					, /**/"Setting"	,/**/"AngleStep"			,"Step angle (degree)  ,normal:2.5");
	SetParam(&CrossRateInPickedArea		, /**/"Setting"	,/**/"CrossRateInPickedArea","CrossedRate in PickedArea (Normal 0.8)");
	SetParam(&RotationalSame			, /**/"Setting"	,/**/"RotationalSame"		,"Rotational matching rate to remove same pattern (0-1.0)");
	SetParam(&SkipFlat					, /**/"Setting"	,/**/"SkipFlat"				,"Skip Flat for accelaration");
	SetParam(&CountIndexLine			, /**/"Setting"	,/**/"CountIndexLine"		,"Count of IndexLine in edge (2-4)");
	SetParam(&NonOverlappedRate			, /**/"Setting"	,/**/"NonOverlappedRate"	,"No-overlapped area rate(0-1.0)");

	SetParam(&ItemColor0				, /**/"ItemColor",/**/"ItemColor0"			,"Item color 0");
	SetParam(&ItemColor1				, /**/"ItemColor",/**/"ItemColor1"			,"Item color 1");
	SetParam(&ItemColor2				, /**/"ItemColor",/**/"ItemColor2"			,"Item color 2");
	SetParam(&ItemColor3				, /**/"ItemColor",/**/"ItemColor3"			,"Item color 3");
	SetParam(&ItemColor4				, /**/"ItemColor",/**/"ItemColor4"			,"Item color 4");
	SetParam(&ItemColor5				, /**/"ItemColor",/**/"ItemColor5"			,"Item color 5");
	SetParam(&ItemColor6				, /**/"ItemColor",/**/"ItemColor6"			,"Item color 6");
	SetParam(&ItemColor7				, /**/"ItemColor",/**/"ItemColor7"			,"Item color 7");
}

void	CounterBase::TransmitDirectly(GUIDirectMessage *packet)
{

}
const QColor	CounterBase::GetItemColor(int n)
{
	switch(n%8){
	case 0:	return ItemColor0;
	case 1:	return ItemColor1;
	case 2:	return ItemColor2;
	case 3:	return ItemColor3;
	case 4:	return ItemColor4;
	case 5:	return ItemColor5;
	case 6:	return ItemColor6;
	case 7:	return ItemColor7;
	}
	return Qt::black;
}
