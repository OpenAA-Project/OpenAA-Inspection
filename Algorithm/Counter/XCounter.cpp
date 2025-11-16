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
	ChangedMask	=false;
	ModeParallel.ModeParallelExecuteProcessing=false;

	MostPixelsInBrightness[0]=0;
	MostPixelsInBrightness[1]=0;
	MostPixelsInBrightness[2]=0;
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
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
		GetParentBase()->ExecuteInitialAfterEdit(0,r,EInfo);

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
		if(GetFirstData()==NULL){
			MutexExecutedPickedFPack.lock();
			CmdReqResultCountVar->Count=ExecutedPickedFPack.GetCount();
			MutexExecutedPickedFPack.unlock();
			CmdReqResultCountVar->TimeOut=false;
		}
		return;
	}
	CmdReqAdoptedRate	*CmdReqAdoptedRateVar=dynamic_cast<CmdReqAdoptedRate *>(packet);
	if(CmdReqAdoptedRateVar!=NULL){
		CounterItem	*a=tGetFirstData();
		if(a!=NULL){
			CmdReqAdoptedRateVar->AdoptedRate=a->GetThresholdR(GetLayersBase())->AdoptedRate;
		}
		else{
			CmdReqAdoptedRateVar->AdoptedRate=0.3;
		}
		return;
	}
	CmdSetAdoptedRate	*CmdSetAdoptedRateVar=dynamic_cast<CmdSetAdoptedRate *>(packet);
	if(CmdSetAdoptedRateVar!=NULL){
		for(AlgorithmItemPI *c=GetFirstData();c!=NULL;c=c->GetNext()){
			CounterItem	*Item=dynamic_cast<CounterItem *>(c);
			Item->GetThresholdW()->AdoptedRate=CmdSetAdoptedRateVar->AdoptedRate;
		}
		CounterBase	*ABase=tGetParentBase();
		ABase->AdoptedRate=CmdSetAdoptedRateVar->AdoptedRate;
		return;
	}
	CmdSetBackGround	*CmdSetBackGroundVar=dynamic_cast<CmdSetBackGround *>(packet);
	if(CmdSetBackGroundVar!=NULL){
		if(CmdSetBackGroundVar->SetBackGround==true){
			SetBackGround();
		}
		else{
			ReleaseBackGround();
		}
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
	CmdSetFocusLevel	*CmdSetFocusLevelVar=dynamic_cast<CmdSetFocusLevel *>(packet);
	if(CmdSetFocusLevelVar!=NULL){
		for(AlgorithmItemPI *c=GetFirstData();c!=NULL;c=c->GetNext()){
			CounterItem	*Item=dynamic_cast<CounterItem *>(c);
			Item->CalcFocusLevel();
		}
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

void	CounterInPage::ReleaseBackGround(void)
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
			MaskLayer->BackGroundImage.Clear();
			MostPixelsInBrightness[0]=0;
			MostPixelsInBrightness[1]=0;
			MostPixelsInBrightness[2]=0;
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
	MaskingBase	*MaskBase=(MaskingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(MaskBase!=NULL){
		MaskingInPage	*Mp=(MaskingInPage *)MaskBase->GetPageData(GetPage());
		if(Mp!=NULL){
			MaskingDrawAttr	MAttr;
			
			MAttr.NegColorMask				=Qt::magenta;
			MAttr.NegColorSelected			=Qt::red;
			MAttr.EffectiveMode				=false;
			MAttr.IneffectiveMode			=true;
			MAttr.EffectiveLimitedMode		=false;
			MAttr.IneffectiveLimitedMode	=false;
			MAttr.ShowBackGround			=false;
			MAttr.ColorEffective			=qRgba(255,192,0,160);
			MAttr.ColorEffectiveLimited		=qRgba(255,192,0,160);
			MAttr.ColorIneffective			=qRgba(255,192,0,160);
			MAttr.ColorIneffectiveLimited	=qRgba(255,192,0,160);
			MAttr.SelectedLibID				=-1;
			MAttr.TransparentLevel			=192;

			Mp->Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,&MAttr);
		}
	}
	CounterItem	*Item=tGetFirstData();
	if(Item==NULL){
		DWORD	CurrentMilisec=::GetComputerMiliSec();
		if(((CurrentMilisec/300)&0x01)!=0){
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

	ExeResult	Ret=AlgorithmInPagePITemplate<CounterItem,CounterBase>::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	return Ret;
}

ExeResult	CounterInPage::ExecuteProcessing(int ExeID ,ResultInPageRoot *Res)
{
	DWORD	NowMilisec=::GetComputerMiliSec();
	ImagePointerContainer ImageList;
	GetTargetBuffList	(ImageList);

	int	CountBackGround=0;
	ImageBuffer	*BackGroundImage[100];
	ImageBuffer	*MotherImage[100];
	int	LayerNumb=min(GetLayerNumb(),3);

	if(ChangedMask==true){
		GetReflectionMap(_Reflection_Mask,MaskMapInPage);
		ChangedMask=false;
	}
	ConstMapBufferList	*MaskMap=MaskMapInPage[0];
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

			int	NYLen=YLen/4;
			int	NXLen=XLen/4;

			#pragma omp parallel for
			for(int i=0;i<NYLen;i++){
				int	y=i*4;
				BYTE	*s=MotherImage[layer]->GetYWithoutDepended(y);
				for(int x=0;x<XLen;x+=4){
					#pragma omp	atomic
					BrightTable[s[x]]++;
				}
			}
			qint64	MaxD=0;
			int		Index=0;
			for(int i=1;i<256;i++){
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
		if(MaskMap!=NULL
		&& MaskMap->GetMapBuffer()!=NULL){
			const BYTE	**MaskBitmap=MaskMap->GetMapBuffer()->GetBitMap();
			MatrixBuffAnd	(ExecuteMap ,MaskBitmap ,XByte ,YLen);
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
	else{
		int	XDivN=3;
		int	YDivN=3;
		int	XDivLen=GetDotPerLine()/XDivN;
		int	YDivLen=GetMaxLines()/YDivN;
		for(int yn=0;yn<YDivN;yn++){
			for(int xn=0;xn<XDivN;xn++){
				MakeActiveBinarize(xn*XDivLen,yn*YDivLen,(xn+1)*XDivLen,(yn+1)*YDivLen
								,ExecuteMap);
			}
		}

		if(MaskMap!=NULL
		&& MaskMap->GetMapBuffer()!=NULL){
			const BYTE	**MaskBitmap=MaskMap->GetMapBuffer()->GetBitMap();
			MatrixBuffAnd	(ExecuteMap ,MaskBitmap ,XByte ,YLen);
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

		int	ItemObjectPixels=10000*ABase->AdoptedRate;
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
		MatrixBuffClear	(ExecuteMap ,0 ,XByte,YLen);
		for(PureFlexAreaList *f=ExecutedPickedFPack.GetFirst();f!=NULL;f=f->GetNext()){
			f->MakeBitData(ExecuteMap ,XLen,YLen);
		}
		CounterThreshold	*WThr=Item->GetThresholdW(GetLayersBase());
		if(PickedPixels>GetDotPerLine()*GetMaxLines()*ABase->MaxPickedPixelsRate
		&& ((MasterBackH[0]-MasterBack[0]+10)>WThr->NoiseLevel)
		&& ((MasterBackH[1]-MasterBack[1]+10)>WThr->NoiseLevel)
		&& ((MasterBackH[2]-MasterBack[2]+10)>WThr->NoiseLevel)){
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
	
void	CounterInPage::MakeActiveBinarize(int x1,int y1,int x2,int y2
								,BYTE **ExecuteMap)
{
	CounterBase	*ABase=tGetParentBase();

	ImagePointerContainer ImageList;
	GetTargetBuffList	(ImageList);
	int	LayerNumb=min(GetLayerNumb(),3);
	for(int layer=0;layer<LayerNumb;layer++){
		qint64	BrightTable[256];
		qint64	BrightTableN[256];
		memset(BrightTable,0,sizeof(BrightTable));

		int	NYLen=YLen/4;
		int	NXLen=XLen/4;
		ImageBuffer	*MotherImage=ImageList[layer];
		int	YN=(y2-y1)/4;

		#pragma omp parallel for
		for(int i=0;i<YN;i++){
			int	y=y1+i*4;
			BYTE	*s=MotherImage->GetYWithoutDepended(y);
			for(int x=x1;x<x2;x+=4){
				#pragma omp	atomic
				BrightTable[s[x]]++;
			}
		}
		for(int i=2;i<256-2;i++){
			BrightTableN[i]=0;
			for(int j=-2;j<=2;j++){
				BrightTableN[i]+=BrightTable[i+j];
			}
		}
		BrightTableN[0]=0;
		BrightTableN[1]=0;
		BrightTableN[254]=0;
		BrightTableN[255]=0;

		int64	PeakN=0;
		int		PeakP=0;
		for(int i=0;i<256;i++){
			if(PeakN<BrightTableN[i]){
				PeakN=BrightTableN[i];
				PeakP=i;
			}
		}
		int	LowIndex=0;
		for(int i=PeakP-1;i>=0;i--){
			if(BrightTableN[i]<PeakN/4){
				LowIndex=i;
				break;
			}
		}
		int	HighIndex=255;
		for (int i=PeakP+1;i<256;i++) {
			if(BrightTableN[i]<PeakN/4){
				HighIndex=i;
				break;
			}
		}
		LowIndex =LowIndex-5;
		HighIndex=HighIndex+5;

		//int64	N=0;
		//for(int i=0;i<256;i++){
		//	N+=BrightTable[i];
		//}
		//int	Left=N*0.25;
		//int	LowIndex=0;
		//int	D=0;
		//for(int i=0;i<256;i++){
		//	D+=BrightTable[i];
		//	if(D>=Left){
		//		LowIndex=i;
		//		break;
		//	}
		//}
		//D=0;
		//int	HighIndex=255;
		//for(int i=255;i>=0;i--){
		//	D+=BrightTable[i];
		//	if(D>=Left){
		//		HighIndex=i;
		//		break;
		//	}
		//}
		double	A=0;
		int	Numb=0;
		double	AA=0;
		for(int i=LowIndex;i<=HighIndex;i++){
			A+=BrightTable[i]*i;
			AA+=BrightTable[i]*i*i;
			Numb+=BrightTable[i];
		}
		double	Avr=A/Numb;
		double	V=(AA-Avr*Avr*Numb)/Numb;
		if(V<0)
			return;
		double	S=sqrt(V);
		double	HRange=ABase->FocusLevel*2;
		int	L=floor(Avr-S*HRange);
		int	H=ceil(Avr+S*HRange);

		int	YNN=y2-y1;
		#pragma omp parallel for
		for(int i=0;i<YNN;i++){
			int	y=y1+i;
			BYTE	*d=ExecuteMap[y];
			BYTE	*s=MotherImage->GetYWithoutDepended(y);
			for(int x=x1;x<x2;x++){
				int	c=s[x];
				if(c<L || H<c){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
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
	MaxAreaPiece	=300*300;
	AdoptPixelsRate	=0.3;
	MaxPickedPixelsRate	=1.0/30.0;
	AngleStep		=2.5;
	CrossRateInPickedArea	=0.5;
	RotationalSame	=0.95;
	SkipFlat		=4;
	CountIndexLine	=3;
	FocusLevel		=7;
	OutsideCalc		=true;
	NonOverlappedRate	=0.8;
	ShowDebugMode	=false;
	SearchSep		=3;
	ShowMatchingRate=false;

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
	SetParam(&FocusLevel				, /**/"Setting"	,/**/"FocusLevel"			,"Focus level (0:Clear - 9:Loose)");
	SetParam(&OutsideCalc				, /**/"Setting"	,/**/"OutsideCalc"			,"Match outside ");
	SetParam(&NonOverlappedRate			, /**/"Setting"	,/**/"NonOverlappedRate"	,"No-overlapped area rate(0-1.0)");
	SetParam(&SearchSep					, /**/"Setting"	,/**/"SearchSep"			,"Separation to search");
	SetParam(&ShowMatchingRate			, /**/"Setting"	,/**/"ShowMatchingRate"		,"Show matching rate for each item");

	SetParam(&ShowDebugMode				, /**/"Mode"	,/**/"ShowDebugMode"		,"Debug mode to show");

	SetParam(&ItemColor0				, /**/"ItemColor",/**/"ItemColor0"			,"Item color 0");
	SetParam(&ItemColor1				, /**/"ItemColor",/**/"ItemColor1"			,"Item color 1");
	SetParam(&ItemColor2				, /**/"ItemColor",/**/"ItemColor2"			,"Item color 2");
	SetParam(&ItemColor3				, /**/"ItemColor",/**/"ItemColor3"			,"Item color 3");
	SetParam(&ItemColor4				, /**/"ItemColor",/**/"ItemColor4"			,"Item color 4");
	SetParam(&ItemColor5				, /**/"ItemColor",/**/"ItemColor5"			,"Item color 5");
	SetParam(&ItemColor6				, /**/"ItemColor",/**/"ItemColor6"			,"Item color 6");
	SetParam(&ItemColor7				, /**/"ItemColor",/**/"ItemColor7"			,"Item color 7");
}

AlgorithmDrawAttr	*CounterBase::CreateDrawAttr(void)
{
	return new CounterDrawAttr(GetLayersBase());
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
