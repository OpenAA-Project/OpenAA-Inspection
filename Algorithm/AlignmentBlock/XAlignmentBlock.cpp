/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentBlock\XAlignmentBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlignmentBlock.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "XAlignmentBlockLibrary.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================


AlignmentBlockInPage::AlignmentBlockInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<AlignmentBlockItem,AlignmentBlockBase>(parent)
{
}
AlignmentBlockInPage::~AlignmentBlockInPage(void)
{
}
AlgorithmItemRoot	*AlignmentBlockInPage::CreateItem(int ItemClassType)
{
	return new AlignmentBlockItem();
}

void	AlignmentBlockInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdAddAlignmentBlockItemPacket	*AddBItem=dynamic_cast<CmdAddAlignmentBlockItemPacket *>(packet);
	//if(AddBItem!=NULL){
	//	AlignmentBlockItem	*Item=tCreateItem(0);
	//	Item->SetArea(AddBItem->Area);
	//	Item->SetLibID(AddBItem->LibID);
	//	AlignmentBlockBase	*BBase=tGetParentBase();
	//	AlgorithmLibraryLevelContainer	LLib(BBase);
	//	if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
	//		Item->CopyThresholdFromLibrary(&LLib);
	//		if(AppendItem(Item)==true){
	//			ImageBuffer *TargetImageList[100];
	//			GetTargetBuffList(TargetImageList);
	//			Item->ItemArea.Set(AddBItem->Area,*TargetImageList[0]);
	//			int	Dx=Item->ItemArea.GetMinX();
	//			int	Dy=Item->ItemArea.GetMinY();
	//			Item->ItemArea.MoveToNoClip(-Dx,-Dy);
	//			ExecuteInitialAfterEditInfo EInfo;
	//			Item->ExecuteInitialAfterEdit(0,0,NULL,EInfo);
	//		}
	//		else{
	//			delete	Item;
	//		}
	//	}
	//
	//	return;
	//}
	CmdAutoGenerateAlignmentBlock	*CmdAutoGenerateAlignmentBlockVar=dynamic_cast<CmdAutoGenerateAlignmentBlock *>(packet);
	if(CmdAutoGenerateAlignmentBlockVar!=NULL){
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		Container->GetLibrary(CmdAutoGenerateAlignmentBlockVar->LibID,SrcLib);
		AlignmentBlockLibrary	*ALib=(AlignmentBlockLibrary *)SrcLib.GetLibrary();
		GenerateItem(ALib);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		AlignmentBlockItem *Item=(AlignmentBlockItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);

			RotatedMatchingPattern	*m=Item->GetRotatedPattern(Item->CurrentRotationPatternNo);
			if(m==NULL){
				Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
			else{
				m->DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
			QBuffer	Buff(&CmdAlgoSimulateVar->Something);
			Buff.open(QIODevice::ReadOnly);
			bool	ModeDrawSubtract=false;
			int		SubtractItemID;
			if(::Load(&Buff,ModeDrawSubtract)==true){
				if(ModeDrawSubtract==true){
					if(::Load(&Buff,SubtractItemID)==true){
						QColor	Col=Qt::magenta;
						Col.setAlpha(70);
						if(SubtractItemID>=0){
							AlignmentBlockItem *SItem=(AlignmentBlockItem *)SearchIDItem(SubtractItemID);
							if(SItem!=NULL){
								int	sx=(SItem->ResultDx-Item->ResultDx);
								int	sy=(SItem->ResultDy-Item->ResultDy);
								RotatedMatchingPattern	*sm=SItem->GetRotatedPattern(SItem->CurrentRotationPatternNo);
								if(sm==NULL){
									SItem->GetArea().DrawAlpha(sx,sy, CmdAlgoSimulateVar->Image,Col.rgba()
											,CmdAlgoSimulateVar->ZoomRate 
											,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
								}
								else{
									sm->DrawAlpha(sx,sy , CmdAlgoSimulateVar->Image,Col.rgba()
										,CmdAlgoSimulateVar->ZoomRate 
										,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
								}
							}
						}
						else{
							for(SubtractItem *v=Item->GetSubBlock().GetFirst();v!=NULL;v=v->GetNext()){
								AlignmentBlockItem *SItem=(AlignmentBlockItem *)SearchIDItem(v->ItemID);
								if(SItem!=NULL){
									int	sx=(SItem->ResultDx-Item->ResultDx);
									int	sy=(SItem->ResultDy-Item->ResultDy);
									//int	sx=0;
									//int	sy=0;
									RotatedMatchingPattern	*sm=SItem->GetRotatedPattern(SItem->CurrentRotationPatternNo);
									if(sm==NULL){
										SItem->GetArea().DrawAlpha(sx,sy , CmdAlgoSimulateVar->Image,Col.rgba()
												,CmdAlgoSimulateVar->ZoomRate 
												,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
									}
									else{
										sm->DrawAlpha(sx,sy , CmdAlgoSimulateVar->Image,Col.rgba()
											,CmdAlgoSimulateVar->ZoomRate 
											,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
									}
								}
							}
						}
					}
				}
			}
		}
		return;
	}
}

void	AlignmentBlockInPage::GenerateItem(AlignmentBlockLibrary *ALib)
{
	AlignmentBlockBase	*BBase=tGetParentBase();
	AlgorithmLibraryLevelContainer	LLib(BBase);
	if(BBase->GetLibraryContainer()->GetLibrary(ALib->GetLibID(),LLib)==true){
		IntList	LibIDs;
		LibIDs.Add(ALib->GetLibID());
		AlgorithmItemPointerListContainer ItemPointers;
		EnumItemsByLib(LibIDs ,ItemPointers);
		for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext()){
			RemoveItem(p->GetItem());
		}
		
		PureFlexAreaListContainer FPack;
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);
			PickupFlexArea(Map.GetBitMap() ,Map.GetXByte() ,Map.GetXLen(),Map.GetYLen() ,FPack );
		}
		if(FPack.GetCount()>0){
			int	XLen=GetDotPerLine();
			int	XByte=(XLen+7)/8;
			int	YLen=GetMaxLines();
			BYTE	**BmpMap=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear	(BmpMap ,0 ,XByte,YLen);
			BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);

			for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
				f->MakeBitData(BmpMap,XLen,YLen);
			}
			GetLayersBase()->FatAreaN (BmpMap,TmpMap,XByte,YLen,ALib->NoisePinholeSize);
			GetLayersBase()->ThinAreaN(BmpMap,TmpMap,XByte,YLen,ALib->NoisePinholeSize);
			GetLayersBase()->ThinAreaN(BmpMap,TmpMap,XByte,YLen,ALib->NoiseIslandSize);
			GetLayersBase()->FatAreaN (BmpMap,TmpMap,XByte,YLen,ALib->NoiseIslandSize);

			for(int y=0;y<ALib->DeadZone;y++){
				BYTE	*d=BmpMap[y];
				for(int x=0;x<XLen;x++){
					SetBmpBitOnY0(d,x);
				}
			}
			for(int y=0;y<YLen;y++){
				BYTE	*d=BmpMap[y];
				for(int x=0;x<ALib->DeadZone;x++){
					SetBmpBitOnY0(d,x);
				}
				for(int x=XLen-ALib->DeadZone;x<XLen;x++){
					SetBmpBitOnY0(d,x);
				}
			}			
			for(int y=YLen-ALib->DeadZone;y<YLen;y++){
				BYTE	*d=BmpMap[y];
				for(int x=0;x<XLen;x++){
					SetBmpBitOnY0(d,x);
				}
			}

			FPack.RemoveAll();
			PureFlexAreaListContainer ItemAreaPack;
			PickupFlexArea(BmpMap ,XByte ,XLen,YLen ,FPack);

			DeleteMatrixBuff(BmpMap,YLen);
			DeleteMatrixBuff(TmpMap,YLen);

			for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
				PureFlexAreaList *NextF=f->GetNext();
				FPack.RemoveList(f);
				int	Len=hypot(f->GetWidth(),f->GetHeight());
				if(Len<ALib->MinAreaSize || ALib->MaxAreaSize<Len
				|| f->GetPatternByte()<ALib->MinAreaDots || ALib->MaxAreaDots<f->GetPatternByte()){
					delete	f;
					f=NextF;
					continue;
				}

				if(ALib->LimitSize<f->GetWidth() || ALib->LimitSize<f->GetHeight()){
					PureFlexAreaListContainer CpPack;
					f->ChopRect(CpPack,ALib->LimitSize);
					ItemAreaPack.AddMove(CpPack);
				}
				else{
					ItemAreaPack.AppendList(f);
				}
				f=NextF;
			}
			for(PureFlexAreaList *a=ItemAreaPack.GetFirst();a!=NULL;){
				PureFlexAreaList *NextA=a->GetNext();
				if(a->GetPatternByte()<ALib->LimitSize*ALib->LimitSize*0.1){
					for(PureFlexAreaList *b=ItemAreaPack.GetFirst();b!=NULL;b=b->GetNext()){
						if(b!=a && b->CheckOverlapNeighbor(a)==true){
							ItemAreaPack.RemoveList(a);
							*b += *a;
							break;
						}
					}
				}
				a=NextA;
			}
			AlignmentBlockBase	*BBase=tGetParentBase();
			for(PureFlexAreaList *a=ItemAreaPack.GetFirst();a!=NULL;a=a->GetNext()){
				a->FatAreaN(ALib->ExpandArea);
				AlignmentBlockItem	*Item=tCreateItem(0);
				a->FatAreaN(ALib->OverlapDot);
				Item->SetArea(*a);
				Item->SetLibID(ALib->GetLibID());
				Item->CopyThresholdFromLibrary(&LLib);
				AppendItem(Item);
			}
		}
	}
}

void	AlignmentBlockInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentBlockDrawAttr	*BAttr=dynamic_cast<AlignmentBlockDrawAttr *>(Attr);
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);

	QColor Col(255,255,0,196);
}

ExeResult	AlignmentBlockInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePITemplate<AlignmentBlockItem,AlignmentBlockBase>::ExecuteStartByInspection(ExeID ,Res);
}
ExeResult	AlignmentBlockInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	AlignmentPacket2DContainer.RemoveAll();
	return AlgorithmInPagePITemplate<AlignmentBlockItem,AlignmentBlockBase>::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
ExeResult	AlignmentBlockInPage::ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePITemplate<AlignmentBlockItem,AlignmentBlockBase>::ExecuteAlignment(ExeID ,Res);
	
	for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
		if(item->IsCalcDone()==false){
			item->CalcByNeighbor();
		}
	}

	double	ZLevel=tGetParentBase()->ZLevel;
	int	AddedDx=0;
	int	AddedDy=0;
	double	AddedDxAA=0;
	double	AddedDyAA=0;

	for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
		AddedDx		+=item->ResultDx;
		AddedDy		+=item->ResultDy;
		AddedDxAA	+=item->ResultDx*item->ResultDx;
		AddedDyAA	+=item->ResultDy*item->ResultDy;
	}
	int	N=GetItemCount();
	double	AvrX=((double)AddedDx)/((double)N);
	double	AvrY=((double)AddedDy)/((double)N);

	double	VmX=(AddedDxAA-N*AvrX*AvrX)/N;
	double	VmY=(AddedDyAA-N*AvrY*AvrY)/N;
	double	Sx=sqrt(VmX);
	double	Sy=sqrt(VmY);
	double	ZoneX=Sx*ZLevel;
	double	ZoneY=Sy*ZLevel;

	AddedDx=0;
	AddedDy=0;
	AddedDxAA=0;
	AddedDyAA=0;
	N=0;
	int	ZoneXL=AvrX-ZoneX;
	int	ZoneXH=AvrX+ZoneX;
	int	ZoneYL=AvrY-ZoneY;
	int	ZoneYH=AvrY+ZoneY;
	for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
		if(ZoneXL<=item->ResultDx && item->ResultDx<ZoneXH
		&& ZoneYL<=item->ResultDy && item->ResultDy<ZoneYH){
			AddedDx		+=item->ResultDx;
			AddedDy		+=item->ResultDy;
			AddedDxAA	+=item->ResultDx*item->ResultDx;
			AddedDyAA	+=item->ResultDy*item->ResultDy;
			N++;
		}
	}
	if(N>=4){
		AvrX=((double)AddedDx)/((double)N);
		AvrY=((double)AddedDy)/((double)N);

		VmX=AddedDxAA-N*AvrX*AvrX;
		VmY=AddedDyAA-N*AvrY*AvrY;
		Sx=sqrt(VmX);
		Sy=sqrt(VmY);
	}
	for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
		if(item->ResultDx<ZoneXL || ZoneXH<item->ResultDx
		|| item->ResultDy<ZoneYL || ZoneYH<item->ResultDy){
			item->ResultDx=AvrX;
			item->ResultDy=AvrY;
		}
	}

	for(AlignmentPacket2DList *p=AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		p->Rotation	=p->Item->ResultRadian;
		p->ShiftX	=p->Item->ResultDx;
		p->ShiftY	=p->Item->ResultDy;
	}
	return Ret;
}


AlignmentPacket2D	*AlignmentBlockInPage::AppendAlignmentBlockPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal)
{
	//if(ExistArea(localX,localY)==true){	
	{
		AlignmentPacket2DList	*L=new AlignmentPacket2DList();
		L->LibType		=Item->GetParentBase()->GetLibType();
		L->LibID		=Item->GetLibID();
		L->PosXOnTarget	=localX;
		L->PosYOnTarget	=localY;
		for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
			if(item->GetArea().IsInclude(localX,localY)==true){
				L->Item=item;
				break;
			}
		}
		if(L->Item==NULL){
			double	MinLen=99999999;
			AlignmentBlockItem *MinItem=NULL;
			for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
				int	Cx,Cy;
				item->GetCenter(Cx,Cy);
				double	Len=hypot(Cx-localX,Cy-localY);
				if(Len<MinLen){
					MinLen=Len;
					MinItem=item;
				}
			}
			if(MinItem!=NULL){
				L->Item=MinItem;
			}
		}

		if(L->Item!=NULL){
			AlignmentPacket2DCreaterMutex.lock();
			AlignmentPacket2DContainer.AppendList(L);
			AlignmentPacket2DCreaterMutex.unlock();
		}
		else{
			delete	L;
			L=NULL;
		}
		return L;
	}
	return NULL;
}

bool	AlignmentBlockInPage::GetAlignmentBlock(AlignmentPacket2D &Point)
{
	AlignmentPacket2DList	*L=dynamic_cast<AlignmentPacket2DList *>(&Point);
	if(L!=NULL){
		if(L->Item!=NULL){
			Point.Rotation	=L->Item->ResultRadian;
			Point.ShiftX	=L->Item->ResultDx;
			Point.ShiftY	=L->Item->ResultDy;
			return true;
		}
	}
	for(AlignmentBlockItem *item=tGetFirstData();item!=NULL;item=item->tGetNext()){
		if(item->GetArea().IsInclude(Point.PosXOnTarget,Point.PosYOnTarget)==true){
			Point.Rotation	=item->ResultRadian;
			Point.ShiftX	=item->ResultDx;
			Point.ShiftY	=item->ResultDy;
			return true;
		}
	}
	double	MinD=99999999;
	AlignmentPacket2DList	*MinL=NULL;
	for(L=AlignmentPacket2DContainer.GetFirst();L!=NULL;L=L->GetNext()){
		double	D=hypot(L->PosXOnTarget-Point.PosXOnTarget,L->PosYOnTarget-Point.PosYOnTarget);
		if(D<MinD){
			MinD=D;
			MinL=L;
		}
	}
	if(MinL!=NULL){
		Point.Rotation	=MinL->Item->ResultRadian;
		Point.ShiftX	=MinL->Item->ResultDx;
		Point.ShiftY	=MinL->Item->ResultDy;
		return true;
	}

	return false;
}

//===========================================================================================
AlignmentBlockBase::AlignmentBlockBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorArea		=Qt::darkGreen;
	ColorSelected	=Qt::green;
	ColorActive		=Qt::red;
	ModeCalcIncline	=false;
	ZLevel			=3.0;

	SetParam(&ColorArea			, /**/"Color"		,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"		,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"		,/**/"ColorActive"		,"Color for Active Area");
	SetParam(&ModeCalcIncline	, /**/"Process"		,/**/"ModeCalcIncline"	,"Mode Calculating Incline");

	SetParam(&ZLevel	, /**/"Process"		,/**/"ZLevel"	,"Magnification for adopted result zone by deviation");
}

AlgorithmDrawAttr	*AlignmentBlockBase::CreateDrawAttr(void)
{
	return new AlignmentBlockDrawAttr(GetLayersBase());
}

void	AlignmentBlockBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetAlignmentBlockLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAlignmentBlockLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetAlignmentBlockLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAlignmentBlockLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertAlignmentBlockLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAlignmentBlockLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AlignmentBlockVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAlignmentBlockLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAlignmentBlockLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AlignmentBlockVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadAlignmentBlockLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAlignmentBlockLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempAlignmentBlockLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAlignmentBlockLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearAlignmentBlockLibraryPacket	*CmdClearAlignmentBlockLibraryPacketVar=dynamic_cast<CmdClearAlignmentBlockLibraryPacket *>(packet);
	if(CmdClearAlignmentBlockLibraryPacketVar!=NULL){
		CmdClearAlignmentBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAlignmentBlockLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAlignmentBlockLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempAlignmentBlockItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempAlignmentBlockItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new AlignmentBlockItem();
		return;
	}
	CmdCreateByteArrayFromAlignmentBlockItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromAlignmentBlockItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadAlignmentBlockItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadAlignmentBlockItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
}

bool	AlignmentBlockBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==AlignmentBlockHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==AlignmentBlockHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==AlignmentBlockReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==AlignmentBlockReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==AlignmentBlockReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==AlignmentBlockSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==AlignmentBlockReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*AlignmentBlockBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	//if(Command==AlignmentBlockReqThresholdReqCommand){
	//	return new AlignmentBlockThresholdReq();
	//}
	//else if(Command==AlignmentBlockReqThresholdSendCommand){
	//	AlignmentBlockThresholdSend	*pSend=new AlignmentBlockThresholdSend();
	//	if(reqData!=NULL){
	//		AlignmentBlockThresholdReq	*req=(AlignmentBlockThresholdReq *)reqData;
	//		pSend->ConstructList(req,this);
	//	}
	//	return pSend;
	//}
	if(Command==AlignmentBlockReqTryThresholdCommand){
		return new AlignmentBlockReqTryThreshold();
	}
	else if(Command==AlignmentBlockSendTryThresholdCommand){
		AlignmentBlockSendTryThreshold	*pSend=new AlignmentBlockSendTryThreshold();
		if(reqData!=NULL){
			AlignmentBlockReqTryThreshold	*req=(AlignmentBlockReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	AlignmentBlockBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	//if(Command==AlignmentBlockReqThresholdReqCommand){
	//	AlignmentBlockThresholdReq	*p=(AlignmentBlockThresholdReq *)data;
	//	return p->Load(f);
	//}
	//else if(Command==AlignmentBlockReqThresholdSendCommand){
	//	AlignmentBlockThresholdSend	*p=(AlignmentBlockThresholdSend *)data;
	//	return p->Load(f);
	//}
	if(Command==AlignmentBlockReqTryThresholdCommand){
		AlignmentBlockReqTryThreshold	*p=(AlignmentBlockReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==AlignmentBlockSendTryThresholdCommand){
		AlignmentBlockSendTryThreshold	*p=(AlignmentBlockSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	AlignmentBlockBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	//if(Command==AlignmentBlockReqThresholdReqCommand){
	//	AlignmentBlockThresholdReq	*p=(AlignmentBlockThresholdReq *)data;
	//	return p->Save(f);
	//}
	//else if(Command==AlignmentBlockReqThresholdSendCommand){
	//	AlignmentBlockThresholdSend	*p=(AlignmentBlockThresholdSend *)data;
	//	return p->Save(f);
	//}
	if(Command==AlignmentBlockReqTryThresholdCommand){
		AlignmentBlockReqTryThreshold	*p=(AlignmentBlockReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==AlignmentBlockSendTryThresholdCommand){
		AlignmentBlockSendTryThreshold	*p=(AlignmentBlockSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	AlignmentBlockBase::GeneralDataReply(int32 Command,void *data)
{
	//if(Command==AlignmentBlockReqThresholdReqCommand){
	//	AlignmentBlockThresholdReq	*p=(AlignmentBlockThresholdReq *)data;
	//	return true;
	//}
	//else if(Command==AlignmentBlockReqThresholdSendCommand){
	//	AlignmentBlockThresholdSend	*p=(AlignmentBlockThresholdSend *)data;
	//	return true;
	//}
	if(Command==AlignmentBlockReqTryThresholdCommand){
		AlignmentBlockReqTryThreshold	*p=(AlignmentBlockReqTryThreshold *)data;
		return true;
	}
	else if(Command==AlignmentBlockSendTryThresholdCommand){
		AlignmentBlockSendTryThreshold	*p=(AlignmentBlockSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}


//=======================================================================================


AlignmentBlockReqTryThreshold::AlignmentBlockReqTryThreshold(void)
{
	GlobalPage=-1;
	AlignmentBlockItemID=-1;
}
bool	AlignmentBlockReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AlignmentBlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	AlignmentBlockReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AlignmentBlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

AlignmentBlockSendTryThreshold::AlignmentBlockSendTryThreshold(void)
{
	Result					=new ResultInItemPI();	//ResultInItemPI();

	ResultMoveDx			=0;
	ResultMoveDy			=0;
}

AlignmentBlockSendTryThreshold::AlignmentBlockSendTryThreshold(const AlignmentBlockSendTryThreshold &src)
{
	Result					=new ResultInItemPI();	//ResultInItemPI();

	ResultMoveDx			=src.ResultMoveDx			;
	ResultMoveDy			=src.ResultMoveDy			;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
}

AlignmentBlockSendTryThreshold::~AlignmentBlockSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
	
AlignmentBlockSendTryThreshold &AlignmentBlockSendTryThreshold::operator=(const AlignmentBlockSendTryThreshold &src)
{
	ResultMoveDx			=src.ResultMoveDx			;
	ResultMoveDy			=src.ResultMoveDy			;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
	return *this;
}

bool	AlignmentBlockSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;

	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;

	return true;
}
bool	AlignmentBlockSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;

	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;

	return true;
}

void	AlignmentBlockSendTryThreshold::ConstructList(AlignmentBlockReqTryThreshold *reqPacket,AlignmentBlockBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	AlignmentBlockInPage		*BP=(AlignmentBlockInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		AlignmentBlockItem		*BI=(AlignmentBlockItem *)BP->SearchIDItem(reqPacket->AlignmentBlockItemID);
		if(BI!=NULL){
			Calc(&reqPacket->Threshold,BI,Base);
		}
	}
}
void	AlignmentBlockSendTryThreshold::Calc(AlignmentBlockItem *Target,AlignmentBlockItem *Src,AlignmentBlockBase *Base)
{
	AlignmentBlockInPage		*BP=(AlignmentBlockInPage *)Base->GetPageData(Src->GetPage());
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());

	int	SaveMaxInspectMilisec	=Base->GetParamGlobal()->MaxInspectMilisec;

	Base->GetParamGlobal()->MaxInspectMilisec	=99999999;

	Target->SetParent(Src->GetParent());

	Target->SetLibID(Src->GetLibID());
	Target->SetMasterNo(Src->GetMasterNo());
	Target->CopyArea(*Src);
	AlignmentBlockThreshold			*WThr=Target->GetThresholdW();
	const	AlignmentBlockThreshold	*RThr=Src	->GetThresholdR();

	ExecuteInitialAfterEditInfo DummyEInfo;
	DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
	Target->ExecuteInitialAfterEdit(0,0,Result,DummyEInfo);
	Target->ExecuteInitialAfterEditPost(0,0,Result,DummyEInfo);

	//Target->CenterBrightR		=Src->CenterBrightR;
	//Target->CenterBrightG		=Src->CenterBrightG;
	//Target->CenterBrightB		=Src->CenterBrightB;
	//Target->AVector				=Src->AVector;
	//Target->MatchingType		=Src->MatchingType;
	//Target->SearchType			=Src->SearchType;
	//Target->MaxCoefItem			=Src->MaxCoefItem;

	WThr->CopyFrom(*RThr);

	Target->ExecuteStartByInspection	(0,0,Result);
	Target->ExecuteAlignment			(10000,0,Result);

	Result->SetAddedData(NULL,0);

	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();

	Base->GetParamGlobal()->MaxInspectMilisec	=SaveMaxInspectMilisec	;
}