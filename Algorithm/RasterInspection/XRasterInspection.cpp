/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RasterInspection\XRasterInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRasterInspection.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XRasterInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include "XMainSchemeMemory.h"
#include <omp.h>
#include "EditWaveGraphDialog.h"
#include "ReferenceColorDialog.h"
#include "XRasterInspectionPacket.h"
#include "XRasterPacket.h"
#include "XMultiEquSolve.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================


RasterInspectionInPage::RasterInspectionInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<RasterInspectionItem,RasterInspectionBase>(parent)
{
}
RasterInspectionInPage::~RasterInspectionInPage(void)
{
}
AlgorithmItemRoot	*RasterInspectionInPage::CreateItem(int ItemClassType)
{
	return new RasterInspectionItem();
}

void	RasterInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddRasterInspectionItemPacket	*AddBItem=dynamic_cast<CmdAddRasterInspectionItemPacket *>(packet);
	if(AddBItem!=NULL){
		RasterInspectionItem	*Item=tCreateItem(0);
		Item->SetArea(AddBItem->Area);
		Item->SetLibID(AddBItem->LibID);
		RasterInspectionBase	*BBase=tGetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
			Item->CopyThresholdFromLibrary(&LLib);
			if(AppendItem(Item)==true){
				//ImageBuffer *TargetImageList[100];
				//GetTargetBuffList(TargetImageList);
				//Item->ItemArea.Set(AddBItem->Area,*TargetImageList[0]);
				//int	Dx=Item->ItemArea.GetMinX();
				//int	Dy=Item->ItemArea.GetMinY();
				//Item->ItemArea.MoveToNoClip(-Dx,-Dy);
				//ExecuteInitialAfterEditInfo EInfo;
				//Item->ExecuteInitialAfterEdit(0,0,NULL,EInfo);
			}
			else{
				delete	Item;
			}
		}

		return;
	}
	CmdGenerateRasterInspection	*CmdGenerateRasterInspectionVar=dynamic_cast<CmdGenerateRasterInspection *>(packet);
	if(CmdGenerateRasterInspectionVar!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[CmdGenerateRasterInspectionVar->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=CmdGenerateRasterInspectionVar->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(GetParentBase());
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				RasterInspectionLibrary	*Index1=dynamic_cast<RasterInspectionLibrary *>(LibDim[i  ]->GetLibrary());
				RasterInspectionLibrary	*Index2=dynamic_cast<RasterInspectionLibrary *>(LibDim[i+1]->GetLibrary());
				if(Index1->Priority>Index2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(GetLibraryContainer());
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}

		RasterInspectionLibrary	**DDim=new RasterInspectionLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<RasterInspectionLibrary *>(LibDim[i]->GetLibrary());
		}
		GenerateRasterInspection(DDim,N);
		delete	[]DDim;

		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}

	//CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	//if(CmdAlgoSimulateVar!=NULL){
	//	//GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
	//	return;
	//}
}


bool	RasterInspectionInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfRasterInspection	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfRasterInspection	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
int	RasterInspectionLibrarySortFunc(const void *a , const void *b)
{
	RasterInspectionLibrary	*pa=((RasterInspectionLibrary **)a)[0];
	RasterInspectionLibrary	*pb=((RasterInspectionLibrary **)b)[0];
	int	n=pa->Priority - pb->Priority;
	return n;
}
void	RasterInspectionInPage::GenerateRasterInspection(RasterInspectionLibrary *LibDim[],int LibDimNumb)
{
	AlgorithmBase	*RABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
	if(RABase==NULL)
		return;
	AlgorithmInPageInOnePhase	*RAh=RABase->GetPageDataPhase(GetPhaseCode());
	if(RAh==NULL)
		return;
	AlgorithmInPageRoot		*RAp=RAh->GetPageData(GetPage());
	if(RAp==NULL)
		return;

	qsort(LibDim,LibDimNumb,sizeof(RasterInspectionLibrary *),RasterInspectionLibrarySortFunc);

	UndoElement<RasterInspectionInPage>	*UPointer=new UndoElement<RasterInspectionInPage>(this,&RasterInspectionInPage::UndoGenerateItems);
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

	//Data.RemoveAll();
	int	DeletedItemCount=0;
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetEditLocked()==false){
			DeletedItemCount++;
		}
	}
	::Save(UPointer->GetWritePointer(),DeletedItemCount);

	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			L->Save(UPointer->GetWritePointer());
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	AlgorithmLibraryContainer	*Container=GetParentBase()->GetLibraryContainer();
	if(Container!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
			if(Lib==NULL){
				Lib=new AlgorithmLibraryLevelContainer(Container);
				if(Container->GetLibrary(L->GetLibID() ,*Lib)==true){
					LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
				}
				else{
					delete	Lib;
					Lib=NULL;
				}
			}
		}
	}

	for(AlgorithmLibraryStockerList *B=LibStocker.GetFirst();B!=NULL;B=B->GetNext()){
		MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}

	BYTE **OcupyMap				=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **OcupyMapSamePriority	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());
	RasterInspectionBase	*ABase=(RasterInspectionBase *)GetParentBase();

	ImageBufferListContainer	ImageContainer;
	ImageContainer.MakeImageBuff(3 ,ImageBufferMaster ,GetDotPerLine() ,GetMaxLines());

	IntList	AddedItemIDList;
	for(int i=0;i<LibDimNumb;i++){
		ImageContainer.Memset(0);

		ConstMapBufferListContainer MaskMap;
		GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		MapBuffer Map;
		MaskMap.BindOr(Map);
		BYTE	**MaskBitmap=Map.GetBitMap();
		
		if(LibDim[i]->EnableOverlap==false){
			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());
		}
		bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibDim[i]->GetLibID());
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,LibDim[i],NULL);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){

			CmdRasterMakeImage	RCmd(GetLayersBase());
			RCmd.DestBuff.Set(ImageContainer);
			RAp->TransmitDirectly(&RCmd);

			NPListPack<AlgorithmItemPI>	TmpRasterInspectionData;
			LibDim[i]->MakeRasterInspection(
					ImageContainer
					,MaskBitmap,LastOcupyMap
					,XByte ,GetDotPerLine(),GetMaxLines()
					,((RasterInspectionBase *)GetParentBase())->OmitZoneDot
					,GetPage()
					,TmpRasterInspectionData);

			for(AlgorithmItemPI *a=TmpRasterInspectionData.GetFirst();a!=NULL;a=a->GetNext()){
				a->GetArea().MakeBitData(OcupyMap,GetDotPerLine(),GetMaxLines());
			}

			AlgorithmItemPI	*q;
			while((q=TmpRasterInspectionData.GetFirst())!=NULL){
				TmpRasterInspectionData.RemoveList(q);
				RasterInspectionItem	*Item=dynamic_cast<RasterInspectionItem *>(q);
				AppendItem(Item);
				AddedItemIDList.Add(Item->GetID());
			}
		}

		MatrixBuffOr (OcupyMapSamePriority,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
		if((i+1)<LibDimNumb && LibDim[i]->Priority!=LibDim[i+1]->Priority){
			MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMapSamePriority ,XByte,GetMaxLines());
			MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());
		}
	}
	//for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
	//	RasterInspectionItem	*Item=dynamic_cast<RasterInspectionItem *>(a);
	//	if(Item!=NULL){
	//		Item->GetThresholdW()->SetToOrigin();
	//	}
	//}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());

	AddedItemIDList.Save(UPointer->GetWritePointer());

	DeleteMatrixBuff(OcupyMap				,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
	DeleteMatrixBuff(OcupyMapSamePriority	,GetMaxLines());
}

void	RasterInspectionInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	RasterInspectionDrawAttr	*BAttr=dynamic_cast<RasterInspectionDrawAttr *>(Attr);
	AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);

	if(BAttr!=NULL && BAttr->ModeShowPDF==true){
		AlgorithmBase	*RABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
		if(RABase!=NULL){
			AlgorithmInPageInOnePhase	*RAh=RABase->GetPageDataPhase(GetPhaseCode());
			AlgorithmInPageRoot	*RAp=RAh->GetPageData(GetPage());
			if(RAp!=NULL){
				RAp->Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,NULL);
			}
		}
	}
}

ExeResult	RasterInspectionInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePITemplate<RasterInspectionItem,RasterInspectionBase>::ExecuteStartByInspection(ExeID ,Res);
}
ExeResult	RasterInspectionInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmBase	*RABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
	if(RABase==NULL)
		return _ER_false;
	AlgorithmInPageInOnePhase	*RAh=RABase->GetPageDataPhase(GetPhaseCode());
	if(RAh==NULL)
		return _ER_false;
	AlgorithmInPageRoot		*RAp=RAh->GetPageData(GetPage());
	if(RAp==NULL)
		return _ER_false;
	MasterByPDF.Memset(0);

	ImageBufferListContainer	ImageContainer;
	ImageContainer.MakeImageBuff(3 ,ImageBufferMaster ,GetDotPerLine() ,GetMaxLines());
			
	CmdRasterMakeImage	RCmd(GetLayersBase());
	RCmd.DestBuff.Set(ImageContainer);
	RAp->TransmitDirectly(&RCmd);

	MasterByPDF.MakeImageBuff(GetLayerNumb() ,0 ,GetDotPerLine() ,GetMaxLines());

	RasterInspectionBase	*ABase=tGetParentBase();
	for(int y=0;y<GetMaxLines();y++){
		BYTE	*sR=ImageContainer[0]->GetY(y);
		BYTE	*sG=ImageContainer[1]->GetY(y);
		BYTE	*sB=ImageContainer[2]->GetY(y);
		for(int x=0;x<GetDotPerLine();x++,sR++,sG++,sB++){
			QColor	Col(*sR,*sG,*sB);
			ReferencePDF	*R1;
			ReferencePDF	*R2;
			ReferencePDF	*R3;
			ABase->RContainer.FindClosed(Col ,&R1 ,&R2 ,&R3);
			if(R1!=NULL && R2!=NULL && R3!=NULL){
				XMultiEquSolve	Sol;
				Sol.AllocateMatrix(3);
				Sol.SetMatrixValue(1,1,R1->PDFColor.red());
				Sol.SetMatrixValue(2,1,R2->PDFColor.red());
				Sol.SetMatrixValue(3,1,R3->PDFColor.red());
				Sol.SetMatrixValue(1,2,R1->PDFColor.green());
				Sol.SetMatrixValue(2,2,R2->PDFColor.green());
				Sol.SetMatrixValue(3,2,R3->PDFColor.green());
				Sol.SetMatrixValue(1,3,R1->PDFColor.blue());
				Sol.SetMatrixValue(2,3,R2->PDFColor.blue());
				Sol.SetMatrixValue(3,3,R3->PDFColor.blue());
				Sol.SetMatrixValueBn(1,Col.red());
				Sol.SetMatrixValueBn(2,Col.green());
				Sol.SetMatrixValueBn(3,Col.blue());
				Sol.ExecuteGaussianElimination();

				double	t1=Sol.GetAnswer(1);
				double	t2=Sol.GetAnswer(2);
				double	t3=Sol.GetAnswer(3);

				ImageBufferList	*d=MasterByPDF.GetFirst();
				for(int layer=0;layer<GetLayerNumb();layer++,d=d->GetNext()){
					d->SetPixel(x ,y ,R1->ColorDim[layer]*t1
									 +R2->ColorDim[layer]*t2
									 +R3->ColorDim[layer]*t3);
				}
			}
		}
	}

	return AlgorithmInPagePITemplate<RasterInspectionItem,RasterInspectionBase>::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
ExeResult	RasterInspectionInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePITemplate<RasterInspectionItem,RasterInspectionBase>::ExecuteProcessing(ExeID ,Res);

	return Ret;
}

void	RasterInspectionInPage::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RasterInspectionItem	*BI=(RasterInspectionItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

void	RasterInspectionInPage::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		RasterInspectionItem	*B=(RasterInspectionItem	*)CreateItem();
		if(B->Load(f,GetLayersBase())==false)
			return;
		RemovedItems.Add(B);
	}
	IntList	AddedItemIDList;
	if(AddedItemIDList.Load(f)==false)
		return;
	for(IntClass *a=AddedItemIDList.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*Item=SearchIDItem(a->GetValue());
		if(Item!=NULL){
			RemoveItem(Item);
			delete	Item;
		}
	}
	for(AlgorithmItemPointerList *item=RemovedItems.GetFirst();item!=NULL;item=item->GetNext()){
		AppendItem(item->GetItem());
	}
}
//===========================================================================================
RasterInspectionBase::RasterInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
,RContainer(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorArea		=Qt::darkGreen;
	ColorSelected	=Qt::green;
	ColorActive		=Qt::red;
	OmitZoneDot		=4;
	TransparentPDF	=160;

	SetParam(&ColorArea			, /**/"Color"		,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"		,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"		,/**/"ColorActive"		,"Color for Active Area");
	SetParam(&TransparentPDF	, /**/"Color"		,/**/"TransparentPDF"	,"Transparent rate (0-255)",0,255);

	SetParam(&OmitZoneDot		, /**/"Setting"		,/**/"OmitZoneDot"		,"Omit zone dot in RasterInspection generation");

	RContainer.LoadDefault();
}

AlgorithmDrawAttr	*RasterInspectionBase::CreateDrawAttr(void)
{
	return new RasterInspectionDrawAttr(GetLayersBase());
}

void	RasterInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetRasterInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetRasterInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetRasterInspectionLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetRasterInspectionLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertRasterInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertRasterInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(RasterInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateRasterInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateRasterInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(RasterInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadRasterInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadRasterInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempRasterInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempRasterInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearRasterInspectionLibraryPacket	*CmdClearRasterInspectionLibraryPacketVar=dynamic_cast<CmdClearRasterInspectionLibraryPacket *>(packet);
	if(CmdClearRasterInspectionLibraryPacketVar!=NULL){
		CmdClearRasterInspectionLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteRasterInspectionLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteRasterInspectionLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempRasterInspectionItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempRasterInspectionItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new RasterInspectionItem();
		return;
	}
	CmdCreateByteArrayFromRasterInspectionItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromRasterInspectionItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
		return;
	}
	CmdLoadRasterInspectionItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadRasterInspectionItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
		return;
	}
	CmdRasterAddReferencePDF	*CmdRasterAddReferencePDFVar=dynamic_cast<CmdRasterAddReferencePDF *>(packet);
	if(CmdRasterAddReferencePDFVar!=NULL){
		ReferencePDF	*p=new ReferencePDF();
		*p=CmdRasterAddReferencePDFVar->RData;
		RContainer.AppendListItem(p);
		RContainer.SaveDefault();
		return;
	}
	CmdRasterShowReferencePDF	*CmdRasterShowReferencePDFVar=dynamic_cast<CmdRasterShowReferencePDF *>(packet);
	if(CmdRasterShowReferencePDFVar!=NULL){
		EditWaveGraphDialog	D(&CmdRasterShowReferencePDFVar->RData,GetLayersBase());
		D.SetDeletable(CmdRasterShowReferencePDFVar->Deletable);
		int	Ret=D.exec();
		if(Ret==3){
			CmdRasterShowReferencePDFVar->RData.ReferenceName=D.ReferenceName;
		}
		return;
	}
	CmdRasterShowReferencePDFList	*CmdRasterShowReferencePDFListVar=dynamic_cast<CmdRasterShowReferencePDFList *>(packet);
	if(CmdRasterShowReferencePDFListVar!=NULL){
		ReferenceColorDialog	D(GetLayersBase());
		D.exec();
		return;
	}
}

bool	RasterInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==RasterInspectionHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==RasterInspectionHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==RasterInspectionReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==RasterInspectionReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==RasterInspectionReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==RasterInspectionSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==RasterInspectionReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*RasterInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==RasterInspectionReqThresholdReqCommand){
		return new RasterInspectionThresholdReq();
	}
	else if(Command==RasterInspectionReqThresholdSendCommand){
		RasterInspectionThresholdSend	*pSend=new RasterInspectionThresholdSend();
		if(reqData!=NULL){
			RasterInspectionThresholdReq	*req=(RasterInspectionThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==RasterInspectionReqTryThresholdCommand){
		return new RasterInspectionReqTryThreshold();
	}
	else if(Command==RasterInspectionSendTryThresholdCommand){
		RasterInspectionSendTryThreshold	*pSend=new RasterInspectionSendTryThreshold();
		if(reqData!=NULL){
			RasterInspectionReqTryThreshold	*req=(RasterInspectionReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	RasterInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==RasterInspectionReqThresholdReqCommand){
		RasterInspectionThresholdReq	*p=(RasterInspectionThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==RasterInspectionReqThresholdSendCommand){
		RasterInspectionThresholdSend	*p=(RasterInspectionThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==RasterInspectionReqTryThresholdCommand){
		RasterInspectionReqTryThreshold	*p=(RasterInspectionReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==RasterInspectionSendTryThresholdCommand){
		RasterInspectionSendTryThreshold	*p=(RasterInspectionSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	RasterInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==RasterInspectionReqThresholdReqCommand){
		RasterInspectionThresholdReq	*p=(RasterInspectionThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==RasterInspectionReqThresholdSendCommand){
		RasterInspectionThresholdSend	*p=(RasterInspectionThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==RasterInspectionReqTryThresholdCommand){
		RasterInspectionReqTryThreshold	*p=(RasterInspectionReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==RasterInspectionSendTryThresholdCommand){
		RasterInspectionSendTryThreshold	*p=(RasterInspectionSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	RasterInspectionBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==RasterInspectionReqThresholdReqCommand){
		RasterInspectionThresholdReq	*p=(RasterInspectionThresholdReq *)data;
		return true;
	}
	else if(Command==RasterInspectionReqThresholdSendCommand){
		RasterInspectionThresholdSend	*p=(RasterInspectionThresholdSend *)data;
		return true;
	}
	else if(Command==RasterInspectionReqTryThresholdCommand){
		RasterInspectionReqTryThreshold	*p=(RasterInspectionReqTryThreshold *)data;
		return true;
	}
	else if(Command==RasterInspectionSendTryThresholdCommand){
		RasterInspectionSendTryThreshold	*p=(RasterInspectionSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}
ExeResult	RasterInspectionBase::ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	RContainer.ReGenerateID();
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	return Ret;
}