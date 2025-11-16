
#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <QReadWriteLock>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
#include "XDLLType.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XTransferInterface.h"
#include "XTransfer.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightInterfaceDLL.h"
#include "XLightClass.h"
#include "ServiceLibResource.h"
#include "XGUIFormBase.h"
#include "XFilterManager.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XOutlineOffset.h"
#include "XLogo.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XDirectComm.h"
#include "XGeneralStocker.h"
#include "XLearningRule.h"
#include "XPassword.h"
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "ShowLoadingDLLForm.h"
#include "XLotInformation.h"
#include "XHistgramByParam.h"
#include "XDateTime.h"
#include "AlertDialog.h"
#include "XShareMasterData.h"
#include "XCSV.h"
#include "XPrinterManager.h"
#include "XPointer.h"
#include "XImageExpand.h"
#include "LensWindowForm.h"
#include "XIntegrationComm.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "XResize.h"
#include "XResultAnalizer.h"
#include "XDirectCommPacket.h"
#include "XDataInLayerToDisplayImage.h"
#include "ThreadSequence.h"
#include "XDataInLayerCmdLocal.h"
#include "XFilterInstance.h"
#include "XCameraClass.h"
#include "XAuthenticationInside.h"
#include "XResult.h"
#include "XWriteResultThread.h"
#include "XLibraryType.h"
#include "XArrangementFromFile.h"
#include "XLogOut.h"
#include "XParamDatabase.h"
#include "XImageStocker.h"
#include "XLanguageStockerLoader.h"
#include "XShadowTree.h"
#include "XFileThread.h"
#include "XLevel.h"
#include "SelectThresholdLevelDialog.h"
#include "XMultiLayerColor.h"
#include "XMasterData.h"
#include "XDataComponent.h"

//====================================================================================================

ThreadImageCompresserInPage::ThreadImageCompresserInPage(LayersBase *base,DataInPage *p)
:ServiceForLayers(base),ParentPage(p)
{	
	CloseMode=false;
}
ThreadImageCompresserInPage::~ThreadImageCompresserInPage(void)
{
	if(isRunning()==true){
		CloseMode=true;
		wait(300);
	}
}
void	ThreadImageCompresserInPage::Set(NGImageContainerInPage *point)
{
	Accessor.lock();
	NGImageContainerInPageContainer.AppendList(new NGImageContainerInPagePointerList(point));
	Accessor.unlock();
}

bool	ThreadImageCompresserInPage::IsDone(void)
{
	Accessor.lock();
	int	n=NGImageContainerInPageContainer.GetCount();
	Accessor.unlock();
	if(n==0)
		return true;
	return false;
}
int		ThreadImageCompresserInPage::GetCountOfCompressing(void)
{
	Accessor.lock();
	int	n=NGImageContainerInPageContainer.GetCount();
	Accessor.unlock();
	return n;
}
void ThreadImageCompresserInPage::run()
{
	for(;;){
		if((GetLayersBase()->GetOnTerminating()==true) || (CloseMode==true)){
			return;
		}
		msleep(10);
			
		Accessor.lock();
		NGImageContainerInPagePointerList	*r=NGImageContainerInPageContainer.GetFirst();
		if(r!=NULL){
			NGImageContainerInPageContainer.RemoveList(r);
		}
		Accessor.unlock();
		if(r!=NULL){
			ResultInspection	*R=r->GetPoint()->GetParent()->GetParent();
			if(r!=NULL){
				if(R->GetTimeOutBreak()==false){
					r->GetPoint()->CompressImages();
				}
				else{
					r->GetPoint()->SetCompressedFlag(true);
				}
				delete	r;
			}
		}
	}
}

//==================================================================================

NGImageContainerInPagePointerList::NGImageContainerInPagePointerList(NGImageContainerInPage *p)
	:Point(p)
{}

NGImageContainerInPagePointerList	&NGImageContainerInPagePointerList::operator=(const NGImageContainerInPagePointerList &src)
{	
	Point=src.Point;
	return *this;
}
NGImageContainerInPage *NGImageContainerInPagePointerList::GetPoint(void)
{	
	return Point;
}

//====================================================================================================
SystemResultStocker::SystemResultStocker(LayersBase *base ,int AllocCount)
	:ServiceForLayers(base)
{
	Dim=new SystemResult[AllocCount];
	DimCount=AllocCount;
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;
}
SystemResultStocker::~SystemResultStocker(void)
{
	AccessMutex.lock();
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;
	AccessMutex.unlock();
}

void	SystemResultStocker::ClearSystemResult(void)
{
	AccessMutex.lock();
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;
	AccessMutex.unlock();
}

void	SystemResultStocker::ReallocateDimCount(int AllocCount)
{
	AccessMutex.lock();

	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	Dim=new SystemResult[AllocCount];
	DimCount=AllocCount;
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;

	AccessMutex.unlock();
}

void	SystemResultStocker::PushResult(const QByteArray &data)
{
	AccessMutex.lock();
	Dim[WPoint].MasterCode	=GetLayersBase()->GetMasterCode();
	Dim[WPoint].LotAutoCount=GetLayersBase()->GetLot(0)->GetLotAutoCount();
	Dim[WPoint].StoredTime	=::GetComputerMiliSec();
	Dim[WPoint].Result		=data;
	WPoint++;
	if(WPoint>=DimCount){
		WPoint=0;
	}
	StockedCount++;
	AccessMutex.unlock();
}
SystemResult	*SystemResultStocker::PopResult(void)
{
	AccessMutex.lock();
	SystemResult	*R=NULL;
	if(StockedCount>0){
		R=&Dim[RPoint];
		RPoint++;
		if(RPoint>=DimCount){
			RPoint=0;
		}
		StockedCount--;
	}
	AccessMutex.unlock();
	return R;
}
SystemResult	*SystemResultStocker::GetLastResult(void)
{
	if(StockedCount>0){
		return PopResult();
	}

	AccessMutex.lock();
	
	int	iRPoint=RPoint;
	iRPoint--;
	if(iRPoint<0){
		iRPoint=DimCount-1;
	}
	SystemResult	*R=&Dim[iRPoint];

	AccessMutex.unlock();
	return R;
}
int		SystemResultStocker::GetStockedSystemResult(void)
{
	return StockedCount;
}

//====================================================================================================
BufferInfoList::BufferInfoList(void)
{
	OriginCode=-1;
}
BufferInfoList::BufferInfoList(const BufferInfoList &src)
{
	BufferName=src.BufferName;
	OriginCode=src.OriginCode;
}

BufferInfoList &BufferInfoList::operator=(const BufferInfoList &src)
{
	BufferName=src.BufferName;
	OriginCode=src.OriginCode;
	return *this;
}
	
bool	BufferInfoList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,BufferName)==false)
		return false;
	if(::Save(f,OriginCode)==false)
		return false;
	return true;
}
bool	BufferInfoList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,BufferName)==false)
		return false;
	if(::Load(f,OriginCode)==false)
		return false;
	return true;
}

//====================================================================================================

DataInLayer::ConstructionData::ConstructionData(DataInLayer *parent)
{
	if(parent!=NULL){
		ResNumb=(int)pow(2.0,parent->GetParamGlobal()->CameraResolutionBit);
	}
	else{
		ResNumb=256;
	}
	if((ResNumb>65536) || (ResNumb<0)){
		Alert("Invalid Camera resolution bit");
	}
	RBrightTable=new BYTE[ResNumb];
	GBrightTable=new BYTE[ResNumb];
	BBrightTable=new BYTE[ResNumb];
	for(int i=0;i<ResNumb;i++){
		RBrightTable[i]=(BYTE)i;
		GBrightTable[i]=(BYTE)i;
		BBrightTable[i]=(BYTE)i;
	}
	UseTable=false;
}
DataInLayer::ConstructionData::ConstructionData(const DataInLayer::ConstructionData &src)
{
	ResNumb=src.ResNumb;
	
	if((ResNumb>65536) || (ResNumb<0)){
		Alert("Invalid Camera resolution bit");
	}
	RBrightTable=new BYTE[ResNumb];
	GBrightTable=new BYTE[ResNumb];
	BBrightTable=new BYTE[ResNumb];
	for(int i=0;i<ResNumb;i++){
		RBrightTable[i]=src.RBrightTable[i];
		GBrightTable[i]=src.GBrightTable[i];
		BBrightTable[i]=src.BBrightTable[i];
	}
	UseTable=src.UseTable;
}

DataInLayer::ConstructionData::~ConstructionData(void)
{
	delete	[]RBrightTable;
	delete	[]GBrightTable;
	delete	[]BBrightTable;
	RBrightTable=NULL;
	GBrightTable=NULL;

	BBrightTable=NULL;
}
DataInLayer::ConstructionData	&DataInLayer::ConstructionData::operator=(const DataInLayer::ConstructionData &src)
{
	if(this!=&src){
		ResNumb=src.ResNumb;
		
		if((ResNumb>65536) || (ResNumb<0)){
			Alert("Invalid Camera resolution bit");
		}
		delete	[]RBrightTable;
		delete	[]GBrightTable;
		delete	[]BBrightTable;

		RBrightTable=new BYTE[ResNumb];
		GBrightTable=new BYTE[ResNumb];
		BBrightTable=new BYTE[ResNumb];
		for(int i=0;i<ResNumb;i++){
			RBrightTable[i]=src.RBrightTable[i];
			GBrightTable[i]=src.GBrightTable[i];
			BBrightTable[i]=src.BBrightTable[i];
		}
		UseTable=src.UseTable;
	}
	return *this;
}

bool    DataInLayer::ConstructionData::SaveBrightTable(QIODevice *f)
{
	if(::Save(f,ResNumb)==false){
		return false;
	}
	if(f->write((const char *)RBrightTable,ResNumb*sizeof(RBrightTable[0]))!=ResNumb*sizeof(RBrightTable[0])){
		return false;
	}
	if(f->write((const char *)GBrightTable,ResNumb*sizeof(GBrightTable[0]))!=ResNumb*sizeof(GBrightTable[0])){
		return false;
	}
	if(f->write((const char *)BBrightTable,ResNumb*sizeof(BBrightTable[0]))!=ResNumb*sizeof(BBrightTable[0])){
		return false;
	}
	return true;
}
bool    DataInLayer::ConstructionData::LoadBrightTable(QIODevice *f)
{
	int32	iResNumb;
	if(::Load(f,iResNumb)==false){
		return false;
	}
	if(iResNumb<=ResNumb){
		ResNumb=iResNumb;
	}
	else{
		delete	[]RBrightTable;
		delete	[]GBrightTable;
		delete	[]BBrightTable;
		ResNumb=iResNumb;
		RBrightTable=new BYTE[iResNumb];
		GBrightTable=new BYTE[iResNumb];
		BBrightTable=new BYTE[iResNumb];
	}
	if(f->read((char *)RBrightTable,ResNumb*sizeof(RBrightTable[0]))!=ResNumb*sizeof(RBrightTable[0])){
		return false;
	}
	if(f->read((char *)GBrightTable,ResNumb*sizeof(GBrightTable[0]))!=ResNumb*sizeof(GBrightTable[0])){
		return false;
	}
	if(f->read((char *)BBrightTable,ResNumb*sizeof(BBrightTable[0]))!=ResNumb*sizeof(BBrightTable[0])){
		return false;
	}
	UseTable=false;
	for(int i=0;i<256;i++){
		if(RBrightTable[i]!=i || GBrightTable[i]!=i || BBrightTable[i]!=i){
			UseTable=true;
			break;
		}
	}

	return true;
}

bool    DataInLayer::SaveAttr(QIODevice *f)
{
	if(CData.SaveBrightTable(f)==false){
		return false;
	}
	return true;
}
bool    DataInLayer::LoadAttr(QIODevice *f)
{
	if(CData.LoadBrightTable(f)==false){
		return false;
	}
	return true;
}

bool    DataInLayer::Save(QIODevice *f)
{
	int	tAllocatedCountMasterBuff=0;
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL && B->OriginCode<0){
			tAllocatedCountMasterBuff++;
		}
	}
	if(::Save(f,tAllocatedCountMasterBuff)==false){
		return false;
	}
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL && B->OriginCode<0){
			bool	MasterBuffOk= !MasterBuff[i]->IsNull();
			if(::Save(f,MasterBuffOk)==false){
				return false;
			}
			if(MasterBuffOk==true){
				if(MasterBuff[i]->Save(f)==false){
					return false;
				}
			}
		}
	}

	bool	TargetBuffOk= !TargetBuffDim[TargetWPoint]->IsNull();
	if(::Save(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuffDim[TargetWPoint]->Save(f)==false){
			return false;
		}
	}
	ImageBuffer	Dummy;
	if(Dummy.Save(f)==false){
		return false;
	}
	if(Dummy.Save(f)==false){
		return false;
	}
	return true;
}
bool    DataInLayer::Load(QIODevice *f)
{
	int32	tAllocatedCountMasterBuff;
	if(::Load(f,tAllocatedCountMasterBuff)==false){
		return false;
	}
	int	PIndex=0;
	for(int i=0;i<tAllocatedCountMasterBuff && i<AllocatedCountMasterBuff;i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL && B->OriginCode<0){
			bool	MasterBuffOk;
			if(::Load(f,MasterBuffOk)==false){
				return false;
			}
			if(MasterBuffOk==true){
				if(MasterBuff[PIndex]->Load(f)==false){
					return false;
				}
				PIndex++;
			}
		}
	}
	for(int i=AllocatedCountMasterBuff;i<tAllocatedCountMasterBuff;i++){
		bool	MasterBuffOk;
		if(::Load(f,MasterBuffOk)==false){
			return false;
		}
		if(MasterBuffOk==true){
			ImageBuffer	TmpBuff;
			if(TmpBuff.Load(f)==false){
				return false;
			}
		}
	}

	bool	TargetBuffOk;
	if(::Load(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuffDim[TargetWPoint]->Load(f)==false){
			return false;
		}
	}
	ImageBuffer	Dummy;
	if(Dummy.Load(f)==false){
		return false;
	}
	if(Dummy.Load(f)==false){
		return false;
	}
	return true;
}

bool	DataInLayer::SaveImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	if(::Save(f,AllocatedCountMasterBuff)==false){
		return false;
	}
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		bool	MasterBuffOk=!MasterBuff[i]->IsNull();
		if(::Save(f,MasterBuffOk)==false){
			return false;
		}
		if(MasterBuffOk==true){
			if(MasterBuff[i]->SavePartially(f,X1,Y1,X2,Y2)==false){
				return false;
			}
		}
	}
	bool	TargetBuffOk=!TargetBuffDim[TargetWPoint]->IsNull();
	if(::Save(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuffDim[TargetWPoint]->SavePartially(f,X1,Y1,X2,Y2)==false){
			return false;
		}
	}
	bool	MinBuffOk=false;
	::Save(f,MinBuffOk);
	bool	MaxBuffOk=false;
	::Save(f,MaxBuffOk);

	return true;
}
bool	DataInLayer::LoadImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	int32	tAllocatedCountMasterBuff;
	if(::Load(f,tAllocatedCountMasterBuff)==false){
		return false;
	}
	for(int i=0;i<tAllocatedCountMasterBuff && i<AllocatedCountMasterBuff;i++){
		bool	MasterBuffOk;
		if(::Load(f,MasterBuffOk)==false){
			return false;
		}
		if(MasterBuffOk==true){
			if(MasterBuff[i]->LoadPartially(f,X1,Y1,X2,Y2)==false){
				return false;
			}
		}
	}
	for(int i=AllocatedCountMasterBuff;i<tAllocatedCountMasterBuff;i++){
		bool	MasterBuffOk;
		if(::Load(f,MasterBuffOk)==false){
			return false;
		}
		if(MasterBuffOk==true){
			ImageBuffer	TmpBuff;
			if(TmpBuff.LoadPartially(f,X1,Y1,X2,Y2)==false){
				return false;
			}
		}
	}

	bool	TargetBuffOk;
	if(::Load(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuffDim[TargetWPoint]->LoadPartially(f,X1,Y1,X2,Y2)==false){
			return false;
		}
	}
	bool	MinBuffOk;
	if(::Load(f,MinBuffOk)==false){
		return false;
	}
	bool	MaxBuffOk;
	if(::Load(f,MaxBuffOk)==false){
		return false;
	}
	return true;
}
void	DataInLayer::CopyImage(int sourceImageType ,int destImageType)
{
	ImageBuffer	*Src=NULL;	
	switch(sourceImageType){
		case ImageBufferMaster:
			Src= &GetMasterBuff();
			break;
		case ImageBufferTarget:
			Src= &GetTargetBuff();
			break;
		case ImageBufferDelayedView:
			Src= &GetDelayedViewBuff();
			break;
		case ImageBufferRawTarget:
			Src= &GetRawTargetBuff();
			break;
		case ImageBufferCamTarget:
			Src= &GetCamTargetBuff();
			break;
		case ImageBufferOther:
			Src= &GetTargetBuff();
			break;
		case ImageBufferBitBuffer:
			Src= &GetBitBuff();
			break;
		case ImageBufferTrialTargetBuffer:
			Src= &GetTrialTargetBuff();
			break;
	}
	ImageBuffer	*Dst=NULL;	
	switch(destImageType){
		case ImageBufferMaster:
			Dst= &GetMasterBuff();
			break;
		case ImageBufferTarget:
			Dst= &GetTargetBuff();
			break;
		case ImageBufferDelayedView:
			Dst= &GetDelayedViewBuff();
			break;
		case ImageBufferRawTarget:
			Dst= &GetRawTargetBuff();
			break;
		case ImageBufferCamTarget:
			Dst= &GetCamTargetBuff();
			break;
		case ImageBufferOther:
			Dst= &GetTargetBuff();
			break;
		case ImageBufferBitBuffer:
			Dst= &GetBitBuff();
			break;
		case ImageBufferTrialTargetBuffer:
			Dst= &GetTrialTargetBuff();
			break;
	}
	if((Src!=NULL) && (Dst!=NULL)){
		*Dst= *Src;
	}
}

bool    DataInLayer::SaveBrightTable(QIODevice *f)
{
	return CData.SaveBrightTable(f);
}

bool    DataInLayer::LoadBrightTable(QIODevice *f)
{
	return CData.LoadBrightTable(f);
}

//---------------------------------------------------------------------------
DataInLayer::DataInLayer(DataInPage *parent) 
	:ParentPage(parent)
	,Exchanged(false)
	,CData(this)
{
	Layer			=0;
	AllocatedCountMasterBuff	=0;
	AllocatedCountBackGroundBuff=0;
	MasterBuff			=NULL;
	BackGroundBuff		=NULL;
	//TargetBuff		=NULL;
	TargetBuffDim[0]	=NULL;
	TargetBuffDim[1]	=NULL;
	StoringTargetCounter=0;
	TargetWPoint		=0;
	TargetRPoint		=0;
	TargetTRBuff		=NULL;
	RawTargetBuff		=NULL;
	TempTargetBuff		=NULL;
	//ViewTargetBuff	=NULL;
	CamTargetBuff		=NULL;
	BitBuff				=NULL;
	TrialTargetBuff		=NULL;
	AnyData				=new AnyDataContainer();
	EnableCapture		=true;
}

DataInLayer::~DataInLayer(void)
{
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL && B->OriginCode<0){
			if(MasterBuff[i]!=NULL){
				delete	MasterBuff[i];
				MasterBuff[i]=NULL;
			}
		}
	}
	if(MasterBuff!=NULL){
		delete	[]MasterBuff;
		MasterBuff=NULL;
	}
	AllocatedCountMasterBuff=0;

	for(int i=0;i<AllocatedCountBackGroundBuff;i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL && B->OriginCode<0){
			if(BackGroundBuff[i]!=NULL){
				delete	BackGroundBuff[i];
				BackGroundBuff[i]=NULL;
			}
		}
	}
	if(BackGroundBuff!=NULL){
		delete	[]BackGroundBuff;
		BackGroundBuff=NULL;
	}
	AllocatedCountBackGroundBuff=0;

	if(TargetBuffDim[0]!=NULL){
		delete	TargetBuffDim[0];
		TargetBuffDim[0]=NULL;
	}
	if(TargetBuffDim[1]!=NULL){
		delete	TargetBuffDim[1];
		TargetBuffDim[1]=NULL;
	}
	if(TargetTRBuff!=NULL){
		delete	TargetTRBuff;
		TargetTRBuff=NULL;
	}
	if(RawTargetBuff!=NULL){
		delete	RawTargetBuff;
		RawTargetBuff=NULL;
	}

	if(TempTargetBuff!=NULL){
		delete	TempTargetBuff;
		TempTargetBuff=NULL;
	}
	//if(ViewTargetBuff!=NULL){
	//	delete	ViewTargetBuff;
	//	ViewTargetBuff=NULL;
	//}
	if(CamTargetBuff!=NULL){
		delete	CamTargetBuff;
		CamTargetBuff=NULL;
	}
	if(BitBuff!=NULL){
		delete	BitBuff;
		BitBuff=NULL;
	}
	if(TrialTargetBuff!=NULL){
		delete	TrialTargetBuff;
		TrialTargetBuff=NULL;
	}
	if(AnyData!=NULL){
		delete	AnyData;
		AnyData=NULL;
	}
}
int	DataInLayer::GetLayerNumb(void)	const
{
	return GetParent()->GetLayerNumb();
}

int		DataInLayer::GetDotPerLine(void)	const
{	
	return(GetParent()->GetDotPerLine());
}
int		DataInLayer::GetMaxLines(void)	const
{	
	return(GetParent()->GetMaxLines());
}
void	DataInLayer::Initial(bool EnabledImageMemoryAllocation)
{
	AllocatedCountMasterBuff	=GetParamGlobal()->AllocatedCountMasterBuff;
	if(GetParamGlobal()->AllocateMasterBuff==true && AllocatedCountMasterBuff==0){
		AllocatedCountMasterBuff=1;
	}
	MasterBuff		=new ImageBuffer*[AllocatedCountMasterBuff];
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		MasterBuff[i]=new ImageBuffer();
		connect(MasterBuff[i],SIGNAL(SignalChanged()),this,SLOT(SlotChangedMasterImage()));
	}

	AllocatedCountBackGroundBuff	=GetParamGlobal()->AllocatedCountBackGroundBuff;
	if(GetParamGlobal()->AllocateBackGroundBuff==true && AllocatedCountBackGroundBuff==0){
		AllocatedCountBackGroundBuff=1;
	}
	BackGroundBuff		=new ImageBuffer*[AllocatedCountBackGroundBuff];
	for(int i=0;i<AllocatedCountBackGroundBuff;i++){
		BackGroundBuff[i]=new ImageBuffer();
	}

	TargetBuffDim[0]=new ImageBuffer();
	TargetTRBuff	=new ImageBuffer();
	RawTargetBuff	=new ImageBuffer();
	//ViewTargetBuff	=new ImageBuffer();
	CamTargetBuff	=new ImageBuffer();
	BitBuff			=new ImageBuffer();
	TrialTargetBuff	=new ImageBuffer();

	int		tDotPerLine	=ParentPage->GetDotPerLine();
	int		tMaxLines	=ParentPage->GetMaxLines();
	if(EnabledImageMemoryAllocation==true && GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				MasterBuff[i]->Set(GetPage(),ImageBufferMaster ,tDotPerLine ,tMaxLines);
			}
		}
		if(GetParamGlobal()->AllocateBackGroundBuff==true){
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				BackGroundBuff[i]->Set(GetPage(),ImageBufferBackGround ,tDotPerLine ,tMaxLines);
			}
		}
		if(GetParamGlobal()->CommonTargetBetweenPhases==false || GetPhase()==0){
			if(GetParamGlobal()->AllocateTargetBuff==true){
				TargetBuffDim[0]->Set(GetPage(),ImageBufferTarget ,tDotPerLine ,tMaxLines);
			}
			if(GetParamGlobal()->AllocateTargetTRBuff==true){
				TargetTRBuff->Set(GetPage(),ImageBufferTarget ,tMaxLines,tDotPerLine);
			}
		}
		else{
			DataInLayer	*P0L=GetLayersBase()->GetPageDataPhase(0)->GetPageData(GetPage())->GetLayerData(GetLayer());
			if(GetParamGlobal()->AllocateTargetBuff==true){
				TargetBuffDim[0]->SetDependency(P0L->GetTargetBuff());
			}
			if(GetParamGlobal()->AllocateTargetTRBuff==true){
				TargetTRBuff->SetDependency(P0L->GetTargetTRBuff());
			}
		}
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			RawTargetBuff->Set(GetPage(),ImageBufferRawTarget ,tDotPerLine ,tMaxLines);
		}
		if(GetParamGlobal()->AllocViewTargetBuffer==true){
			if(TargetBuffDim[1]==NULL){
				TargetBuffDim[1]=new ImageBuffer();
			}
			TargetBuffDim[1]->Set(GetPage(),ImageBufferTarget ,tDotPerLine ,tMaxLines);
		}
		else{
			if(GetParamGlobal()->AllocateTargetBuff==true && TargetBuffDim[1]!=NULL){
				TargetBuffDim[1]->MakeDup(*TargetBuffDim[0]);
			}
		}
		if(GetParamGlobal()->AllocCamTargetBuffer==true){
			CamTargetBuff->Set(GetPage(),ImageBufferCamTarget ,tDotPerLine ,tMaxLines);
		}
		if(GetParamGlobal()->AllocBitBuffer==true){
			BitBuff->Set(GetPage(),ImageBufferBitBuffer ,(tDotPerLine+7)/8 ,tMaxLines);
		}
		if(GetParamGlobal()->AllocTrialTargetBuffer==true){
			TrialTargetBuff->Set(GetPage(),ImageBufferTrialTargetBuffer ,tDotPerLine ,tMaxLines);
		}
	}
}
int	DataInLayer::SetDispatchMaster(const QString &MasterBuffName, int OriginCode
								,ImageBuffer *s,int pos)
{
	int	tAllocatedCountMasterBuff=AllocatedCountMasterBuff;
	if(pos<0){
		pos=tAllocatedCountMasterBuff;
		tAllocatedCountMasterBuff++;
	}
	if(pos>=tAllocatedCountMasterBuff){
		tAllocatedCountMasterBuff=pos+1;
	}
	ImageBuffer     **tMasterBuff=new ImageBuffer*[tAllocatedCountMasterBuff];
	for(int i=0;i<tAllocatedCountMasterBuff;i++){
		tMasterBuff[i]=NULL;
	}
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		tMasterBuff[i]=MasterBuff[i];
	}
	tMasterBuff[pos]=s;
	if(MasterBuff!=NULL){
		delete	[]MasterBuff;
	}
	MasterBuff=tMasterBuff;
	AllocatedCountMasterBuff=tAllocatedCountMasterBuff;
	GetLayersBase()->SetBufferInfo(MasterBuffName,OriginCode,pos);

	return pos;
}
bool	DataInLayer::RemoveDispatchMaster(int Pos)
{
	if(GetLayersBase()!=NULL){
		if(0<=Pos){
			MasterBuff[Pos]=NULL;
		}
		int	tAllocatedCountMasterBuff=0;
		for(int i=0;i<AllocatedCountMasterBuff;i++){
			if(MasterBuff[i]!=NULL){
				tAllocatedCountMasterBuff++;
			}
		}
		ImageBuffer	**tMasterBuff=new ImageBuffer*[tAllocatedCountMasterBuff];
		int	k=0;
		for(int i=0;i<AllocatedCountMasterBuff;i++){
			if(MasterBuff[i]!=NULL){
				tMasterBuff[k]=MasterBuff[i];
				k++;
			}
		}
		if(MasterBuff!=NULL){
			delete	[]MasterBuff;
		}
		MasterBuff=tMasterBuff;
		AllocatedCountMasterBuff=tAllocatedCountMasterBuff;
		return true;
	}
	return false;
}
void	DataInLayer::SetEnableCapture(bool b)
{
	EnableCapture=b;
}
bool	DataInLayer::GetEnableCapture(void)	const
{
	return EnableCapture;
}
QString	DataInLayer::GetFileNameToSwapBuffer(void)
{
	return QString("SwapBuff-")+QString::number(GetPhase())
		  +QString("-")+QString::number(GetPage())
		  +QString("-")+QString::number(GetLayer())
		  +QString(".swp");
}

void	DataInLayer::SwapImageOutOfBuffer(int ImageDataType)
{
	QString	FileName=GetFileNameToSwapBuffer();

	QFile	File(FileName);

	if(File.open(QIODevice::WriteOnly)==true){
		if((ImageDataType & ImageBufferMaster)!=0){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				MasterBuff[i]->Save(&File);
				delete	MasterBuff[i];
				MasterBuff[i]		=NULL;
			}
		}
		if((ImageDataType & ImageBufferBackGround)!=0){
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				BackGroundBuff[i]->Save(&File);
				delete	BackGroundBuff[i];
				BackGroundBuff[i]		=NULL;
			}
		}
		if((ImageDataType & ImageBufferTarget)!=0 && TargetBuffDim[0]!=NULL){
			TargetBuffDim[0]		->Save(&File);
			delete	TargetBuffDim[0];
			TargetBuffDim[0]	=NULL;
		}
		if((ImageDataType & ImageBufferRawTarget)!=0 && RawTargetBuff!=NULL){
			RawTargetBuff	->Save(&File);
			delete	RawTargetBuff;
			RawTargetBuff	=NULL;
		}
		if((ImageDataType & ImageBufferDelayedView)!=0 && TargetBuffDim[1]!=NULL){
			TargetBuffDim[1]		->Save(&File);
			delete	TargetBuffDim[1];
			TargetBuffDim[1]	=NULL;
		}
		if((ImageDataType & ImageBufferRawTarget)!=0 && RawTargetBuff!=NULL){
			RawTargetBuff		->Save(&File);
			delete	RawTargetBuff;
			RawTargetBuff		=NULL;
		}
		if((ImageDataType & ImageBufferCamTarget)!=0 && CamTargetBuff!=NULL){
			CamTargetBuff		->Save(&File);
			delete	CamTargetBuff;
			CamTargetBuff		=NULL;
		}
		if((ImageDataType & ImageBufferBitBuffer)!=0 && BitBuff!=NULL){
			BitBuff		->Save(&File);
			delete	BitBuff;
			BitBuff		=NULL;
		}
		if((ImageDataType & ImageBufferTrialTargetBuffer)!=0 && TrialTargetBuff!=NULL){
			TrialTargetBuff		->Save(&File);
			delete	TrialTargetBuff;
			TrialTargetBuff		=NULL;
		}
	}
}
void	DataInLayer::SwapImageInToBuffer(int ImageDataType)
{
	QString	FileName=GetFileNameToSwapBuffer();

	QFile	File(FileName);

	if(File.open(QIODevice::ReadOnly)==true){
		Initial(true);
		if((ImageDataType & ImageBufferMaster)!=0){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				MasterBuff[i]->Load(&File);
			}
		}
		if((ImageDataType & ImageBufferBackGround)!=0){
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				BackGroundBuff[i]->Load(&File);
			}
		}
		if((ImageDataType & ImageBufferTarget)!=0 && TargetBuffDim[0]!=NULL){
			TargetBuffDim[0]->Load(&File);
		}
		if((ImageDataType & ImageBufferRawTarget)!=0 && RawTargetBuff!=NULL){
			RawTargetBuff	->Load(&File);
		}
		if((ImageDataType & ImageBufferDelayedView)!=0 && TargetBuffDim[1]!=NULL){
			TargetBuffDim[1]->Load(&File);
		}
		if((ImageDataType & ImageBufferRawTarget)!=0 && RawTargetBuff!=NULL){
			RawTargetBuff	->Load(&File);
		}
		if((ImageDataType & ImageBufferCamTarget)!=0 && CamTargetBuff!=NULL){
			CamTargetBuff	->Load(&File);
		}
		if((ImageDataType & ImageBufferBitBuffer)!=0 && BitBuff!=NULL){
			BitBuff			->Load(&File);
		}
		if((ImageDataType & ImageBufferTrialTargetBuffer)!=0 && TrialTargetBuff!=NULL){
			TrialTargetBuff	->Load(&File);
		}
	}
}

bool	DataInLayer::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(GetParamGlobal()->MaximumDotPerLine>0 && GetParamGlobal()->MaximumDotPerLine<NewDotPerLine){
		NewDotPerLine=GetParamGlobal()->MaximumDotPerLine;
	}
	if(GetParamGlobal()->MaximumMaxLines>0 && GetParamGlobal()->MaximumMaxLines<NewMaxLines){
		NewMaxLines=GetParamGlobal()->MaximumMaxLines;
	}
	if(GetParamComm()->ImageBufferNecessary()==true){
		ImageBuffer	*Tmp=NULL;
		if(GetParamGlobal()->AllocateMasterBuff==true){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
				if(B!=NULL && B->OriginCode<0){
					if(MasterBuff[i]==NULL){
						MasterBuff[i]=new ImageBuffer();
						connect(MasterBuff[i],SIGNAL(SignalChanged()),this,SLOT(SlotChangedMasterImage()));
					}
					if(Tmp==NULL){
						Tmp=new ImageBuffer();
						Tmp->Set(0,ImageBufferMaster ,MasterBuff[i]->GetWidth(),MasterBuff[i]->GetHeight());
					}
					if(Tmp!=NULL && MasterBuff[i]->IsNull()==false){
						*Tmp=*MasterBuff[i];
					}
					MasterBuff[i]->Set(GetPage(),ImageBufferMaster ,NewDotPerLine ,NewMaxLines);
					if(Tmp!=NULL){
						*MasterBuff[i]=*Tmp;
					}
				}
			}
		}
		if(GetParamGlobal()->AllocateBackGroundBuff==true){
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
				if(B!=NULL && B->OriginCode<0){
					if(BackGroundBuff[i]==NULL){
						BackGroundBuff[i]=new ImageBuffer();
					}
					if(Tmp==NULL){
						Tmp=new ImageBuffer();
						Tmp->Set(0,ImageBufferBackGround ,BackGroundBuff[i]->GetWidth(),BackGroundBuff[i]->GetHeight());
					}
					if(Tmp!=NULL && BackGroundBuff[i]->IsNull()==false){
						*Tmp=*BackGroundBuff[i];
					}
					BackGroundBuff[i]->Set(GetPage(),ImageBufferBackGround ,NewDotPerLine ,NewMaxLines);
					if(Tmp!=NULL){
						*BackGroundBuff[i]=*Tmp;
					}
				}
			}
		}
		if(GetParamGlobal()->AllocateTargetBuff==true){
			if(TargetBuffDim[0]==NULL){
				TargetBuffDim[0]=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,TargetBuffDim[0]->GetWidth(),TargetBuffDim[0]->GetHeight());
			}
			if(Tmp!=NULL && TargetBuffDim[0]->IsNull()==false){
				*Tmp=*TargetBuffDim[0];
			}
			if(GetParamGlobal()->CommonTargetBetweenPhases==false || GetPhase()==0){
				TargetBuffDim[0]->Set(GetPage(),ImageBufferTarget ,NewDotPerLine ,NewMaxLines);
			}
			else{
				DataInLayer	*P0L=GetLayersBase()->GetPageDataPhase(0)->GetPageData(GetPage())->GetLayerData(GetLayer());
				TargetBuffDim[0]->SetDependency(P0L->GetTargetBuff());
			}
			if(Tmp!=NULL){
				*TargetBuffDim[0]=*Tmp;
			}
		}
		if(GetParamGlobal()->AllocateTargetTRBuff==true){
			if(TargetTRBuff==NULL){
				TargetTRBuff=new ImageBuffer();
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,TargetTRBuff->GetWidth(),TargetTRBuff->GetHeight());
			}
			if(Tmp!=NULL && TargetTRBuff->IsNull()==false){
				*Tmp=*TargetTRBuff;
			}
			TargetTRBuff->Set(GetPage(),ImageBufferTarget ,NewMaxLines,NewDotPerLine);
			if(Tmp!=NULL){
				TargetTRBuff->PartialCopy(*Tmp ,0,0);
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
		}
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			if(RawTargetBuff==NULL){
				RawTargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,RawTargetBuff->GetWidth(),RawTargetBuff->GetHeight());
			}
			if(Tmp!=NULL && RawTargetBuff->IsNull()==false){
				*Tmp=*RawTargetBuff;
			}
			RawTargetBuff->Set(GetPage(),ImageBufferTarget ,NewDotPerLine ,NewMaxLines);
			if(Tmp!=NULL){
				*RawTargetBuff=*Tmp;
			}
		}
		if(GetParamGlobal()->AllocViewTargetBuffer==true){
			if(TargetBuffDim[1]==NULL){
				TargetBuffDim[1]=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,TargetBuffDim[1]->GetWidth(),TargetBuffDim[1]->GetHeight());
			}
			if(Tmp!=NULL && TargetBuffDim[1]->IsNull()==false){
				*Tmp=*TargetBuffDim[1];
			}
			TargetBuffDim[1]->Set(GetPage(),ImageBufferTarget ,NewDotPerLine ,NewMaxLines);
			if(Tmp!=NULL){
				*TargetBuffDim[1]=*Tmp;
			}
		}
		else{
			if(TargetBuffDim[1]==NULL){
				TargetBuffDim[1]=new ImageBuffer();
			}
			if(GetParamGlobal()->AllocateTargetBuff==true && TargetBuffDim[1]!=NULL){
				TargetBuffDim[1]->MakeDup(*TargetBuffDim[0]);
			}
		}
		if(GetParamGlobal()->AllocCamTargetBuffer==true){
			if(CamTargetBuff==NULL){
				CamTargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,CamTargetBuff->GetWidth(),CamTargetBuff->GetHeight());
			}
			if(Tmp!=NULL && CamTargetBuff->IsNull()==false){
				*Tmp=*CamTargetBuff;
			}
			CamTargetBuff->Set(GetPage(),ImageBufferTarget ,NewDotPerLine ,NewMaxLines);
			if(Tmp!=NULL){
				*CamTargetBuff=*Tmp;
			}
		}
		if(GetParamGlobal()->AllocTrialTargetBuffer==true){
			if(TrialTargetBuff==NULL){
				TrialTargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,CamTargetBuff->GetWidth(),CamTargetBuff->GetHeight());
			}
			if(Tmp!=NULL && CamTargetBuff->IsNull()==false){
				*Tmp=*CamTargetBuff;
			}
			TrialTargetBuff->Set(GetPage(),ImageBufferTrialTargetBuffer ,NewDotPerLine ,NewMaxLines);
			if(Tmp!=NULL){
				*TrialTargetBuff=*Tmp;
			}
		}
		if(GetParamGlobal()->AllocBitBuffer==true){
			if(BitBuff==NULL){
				BitBuff=new ImageBuffer();
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,BitBuff->GetWidth(),BitBuff->GetHeight());
			}
			if(Tmp!=NULL && BitBuff->IsNull()==false){
				*Tmp=*BitBuff;
			}
			BitBuff->Set(GetPage(),ImageBufferBitBuffer ,(NewDotPerLine+7)/8 ,NewMaxLines);
			if(Tmp!=NULL){
				BitBuff->PartialCopy(*Tmp ,0,0);
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
		}
		if(Tmp!=NULL){
			delete	Tmp;
		}
	}
	return true;
}
void	DataInLayer::StoringStartTargetBuff(void)
{
	StoringTargetCounter++;
	if(TargetBuffDim[1]!=NULL){
		if(TargetWPoint==0)
			TargetWPoint=1;
		else
			TargetWPoint=0;
	}
}
void	DataInLayer::StoringFinishTargetBuff(void)
{
	TargetRPoint=TargetWPoint;
}

void	DataInLayer::ReallocMemoryMaster(void)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(MasterBuff!=NULL){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
				if(B!=NULL && B->OriginCode<0){
					if(MasterBuff[i]!=NULL){
						delete	MasterBuff[i];
						MasterBuff[i]=NULL;
					}
				}
			}
		}
		if(MasterBuff==NULL){
			MasterBuff=new ImageBuffer*[AllocatedCountMasterBuff];
		}
		for(int i=0;i<AllocatedCountMasterBuff;i++){
			BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
			if(B!=NULL && B->OriginCode<0){
				MasterBuff[i]	=new ImageBuffer();
				connect(MasterBuff[i],SIGNAL(SignalChanged()),this,SLOT(SlotChangedMasterImage()));
			}
		}
		if(GetParamGlobal()->AllocateMasterBuff==true){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
				if(B!=NULL && B->OriginCode<0){
					MasterBuff[i]->Set(GetPage()
										,ImageBufferMaster 
										,ParentPage->GetDotPerLine()
										,ParentPage->GetMaxLines());
				}
			}
		}
	}
}

void	DataInLayer::ReallocMemoryBackGround(void)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(BackGroundBuff!=NULL){
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
				if(B!=NULL && B->OriginCode<0){
					if(BackGroundBuff[i]!=NULL){
						delete	BackGroundBuff[i];
						BackGroundBuff[i]=NULL;
					}
				}
			}
		}
		if(BackGroundBuff==NULL){
			BackGroundBuff=new ImageBuffer*[AllocatedCountBackGroundBuff];
		}
		for(int i=0;i<AllocatedCountBackGroundBuff;i++){
			BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
			if(B!=NULL && B->OriginCode<0){
				BackGroundBuff[i]	=new ImageBuffer();
			}
		}
		if(GetParamGlobal()->AllocateBackGroundBuff==true){
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
				if(B!=NULL && B->OriginCode<0){
					BackGroundBuff[i]->Set(GetPage()
										,ImageBufferBackGround
										,ParentPage->GetDotPerLine()
										,ParentPage->GetMaxLines());
				}
			}
		}
	}
}

void	DataInLayer::ReallocMemoryTarget(void)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(TargetBuffDim[0]!=NULL){
			delete	TargetBuffDim[0];
		}
		TargetBuffDim[0]		=new ImageBuffer();
		if(GetParamGlobal()->AllocateTargetBuff==true){
			if(GetParamGlobal()->CommonTargetBetweenPhases==false || GetPhase()==0){
				TargetBuffDim[0]->Set(GetPage(),ImageBufferTarget ,ParentPage->GetDotPerLine() ,ParentPage->GetMaxLines());
			}
			else{
				DataInLayer	*P0L=GetLayersBase()->GetPageDataPhase(0)->GetPageData(GetPage())->GetLayerData(GetLayer());
				TargetBuffDim[0]->SetDependency(P0L->GetTargetBuff());
			}
		}
		if(TargetTRBuff!=NULL){
			delete	TargetTRBuff;
		}
		TargetTRBuff		=new ImageBuffer();
		if(GetParamGlobal()->AllocateTargetTRBuff==true){
			TargetTRBuff->Set(GetPage(),ImageBufferTarget ,ParentPage->GetMaxLines() ,ParentPage->GetDotPerLine());
		}
	}
}
void	DataInLayer::ReallocUseBufferToTarget(BYTE **Buff)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(TargetBuffDim[0]!=NULL){
			delete	TargetBuffDim[0];
		}
		TargetBuffDim[0]		=new ImageBuffer();
		if(GetParamGlobal()->AllocateTargetBuff==true){
			TargetBuffDim[0]->Set(Buff,ImageBufferTarget ,ParentPage->GetDotPerLine() ,ParentPage->GetMaxLines(),true);
		}
	}
}


void	DataInLayer::AllocateTargetTRBuff(void)
{
	if(TargetTRBuff->IsNull()==true){
		TargetTRBuff->Set(GetPage(),ImageBufferTarget ,ParentPage->GetMaxLines(),ParentPage->GetDotPerLine());
	}
}

void	DataInLayer::ReleaseTargetTRBuff(void)
{
	if(GetParamGlobal()->AllocateTargetTRBuff==false){
		delete	TargetTRBuff;
		TargetTRBuff=new ImageBuffer();
	}
}
bool	DataInLayer::ReallocateMasterCount(int CountMaster)
{
	int	CountOnlyMasterBuff=GetCountOnlyMasterBuff();
	if(CountOnlyMasterBuff!=CountMaster && 0<=CountMaster){
		int	TmpAllocatedCountMasterBuff=CountMaster+GetCountDispatchMasterBuff();
		ImageBuffer     **iMasterBuff=new ImageBuffer*[TmpAllocatedCountMasterBuff];
		int	i;
		for(i=0;i<CountMaster && i<CountOnlyMasterBuff;i++){
			iMasterBuff[i]=MasterBuff[i];
		}
		int	DispatchPoint=i;
		for(i=0;i<CountMaster;i++){
			iMasterBuff[i]=new ImageBuffer();
			connect(iMasterBuff[i],SIGNAL(SignalChanged()),this,SLOT(SlotChangedMasterImage()));
			iMasterBuff[i]->Set(GetPage()
								,ImageBufferMaster
								,GetDotPerLine(),GetMaxLines());
		}
		for(i=0;i<CountOnlyMasterBuff;i++){
			iMasterBuff[i]=MasterBuff[DispatchPoint];
		}
		for(int j=CountMaster;j<CountOnlyMasterBuff;j++){
			BufferInfoList	*B=GetLayersBase()->GetBufferInfo(j);
			if(B!=NULL && B->OriginCode<=0){
				delete	MasterBuff[j];
			}
		}

		ImageBuffer     **tMasterBuff=MasterBuff;
		MasterBuff=iMasterBuff;
		delete	[]tMasterBuff;
		AllocatedCountMasterBuff=TmpAllocatedCountMasterBuff;
	}
	return true;
}

bool	DataInLayer::ReallocateBackGroundCount(int CountBackGround)
{
	int	CountOnlyBackGroundBuff=GetCountOnlyBackGroundBuff();
	if(CountOnlyBackGroundBuff!=CountBackGround && 0<=CountBackGround){
		int	TmpAllocatedCountBackGroundBuff=CountBackGround;
		ImageBuffer     **iBackGroundBuff=new ImageBuffer*[TmpAllocatedCountBackGroundBuff];
		int	i;
		for(i=0;i<CountBackGround && i<CountOnlyBackGroundBuff;i++){
			iBackGroundBuff[i]=BackGroundBuff[i];
		}
		int	DispatchPoint=i;
		for(i=0;i<CountBackGround;i++){
			iBackGroundBuff[i]=new ImageBuffer();
			iBackGroundBuff[i]->Set(GetPage()
								,ImageBufferBackGround
								,GetDotPerLine(),GetMaxLines());
		}
		for(i=0;i<CountBackGround;i++){
			iBackGroundBuff[i]=BackGroundBuff[DispatchPoint];
		}
		for(int j=CountBackGround;j<CountOnlyBackGroundBuff;j++){
			BufferInfoList	*B=GetLayersBase()->GetBufferInfo(j);
			if(B!=NULL && B->OriginCode<=0){
				delete	BackGroundBuff[j];
			}
		}

		ImageBuffer     **tBackGroundBuff=MasterBuff;
		MasterBuff=iBackGroundBuff;
		delete	[]tBackGroundBuff;
		AllocatedCountMasterBuff=TmpAllocatedCountBackGroundBuff;
	}
	return true;
}

void	DataInLayer::Mirror(bool XMode ,bool YMode)
{
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		if(GetMasterBuffPointer(i)!=NULL)		GetMasterBuffPointer(i)		->Mirror(XMode,YMode);
	}
	for(int i=0;i<AllocatedCountBackGroundBuff;i++){
		if(GetBackGroundBuffPointer(i)!=NULL)		GetMasterBuffPointer(i)		->Mirror(XMode,YMode);
	}
	if(GetTargetBuffPointer()!=NULL)		GetTargetBuffPointer()		->Mirror(XMode,YMode);
	if(GetTargetTRBuffPointer()!=NULL)		GetTargetTRBuffPointer()	->Mirror(YMode,XMode);
	if(GetRawTargetBuffPointer()!=NULL)		GetRawTargetBuffPointer()	->Mirror(XMode,YMode);
	if(GetDelayedViewBuffPointer()!=NULL)	GetDelayedViewBuffPointer()	->Mirror(XMode,YMode);
	if(GetCamTargetBuffPointer()!=NULL)		GetCamTargetBuffPointer()	->Mirror(XMode,YMode);
	if(GetBitBuffPointer()!=NULL)			GetBitBuffPointer()			->Mirror(XMode,YMode);
	if(GetTrialTargetBuffPointer()!=NULL)	GetTrialTargetBuffPointer()	->Mirror(XMode,YMode);
}
void	DataInLayer::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	x1=ParentPage->GetOutlineOffset()->x;
	y1=ParentPage->GetOutlineOffset()->y;
	x2=ParentPage->GetOutlineOffset()->x+ParentPage->GetDotPerLine();
	y2=ParentPage->GetOutlineOffset()->y+ParentPage->GetMaxLines();
}

ImageBuffer	&DataInLayer::GetMasterBuff(void)	const
{	
	if(Exchanged==false){
		return *MasterBuff[0];
	}	
	return *TargetBuffDim[TargetWPoint];
}

ImageBuffer	&DataInLayer::GetMasterBuff(int n)	const
{	
	if(Exchanged==false){
		if(n<0){
			n=0;
		}
		if(n<AllocatedCountMasterBuff){
			return *MasterBuff[n];
		}
		else{
			qCritical(/**/"Out of dim for MasterBuff[%d]",n);
		}
	}	
	return *TargetBuffDim[TargetWPoint];
}


ImageBuffer	&DataInLayer::GetBackGroundBuff(void)	const
{	
	return *BackGroundBuff[0];
}

ImageBuffer	&DataInLayer::GetBackGroundBuff(int n)	const
{	
	if(n<0){
		n=0;
	}
	if(n<AllocatedCountBackGroundBuff){
		return *BackGroundBuff[n];
	}
	else{
		qCritical(/**/"Out of dim for MasterBuff[%d]",n);
	}
}

		
ImageBuffer	&DataInLayer::GetTargetBuff(void)	const
{	
	if(Exchanged==false){
		return *TargetBuffDim[TargetWPoint];
	}
	return *MasterBuff[0];
}
	
ImageBuffer	&DataInLayer::GetTargetTRBuff(void)	const
{	
	return *TargetTRBuff;
}
ImageBuffer	&DataInLayer::GetRawTargetBuff(void)	const
{	
	return *RawTargetBuff;
}
ImageBuffer     &DataInLayer::GetDelayedViewBuff(void)	const
{
	return *TargetBuffDim[TargetRPoint];
}
ImageBuffer     &DataInLayer::GetLastDelayedViewBuff(void)	const
{
	if(TargetBuffDim[1]!=NULL){
		if(TargetRPoint==0)
			return *TargetBuffDim[1];
		else
			return *TargetBuffDim[0];
	}
	return *TargetBuffDim[TargetRPoint];
}
ImageBuffer     &DataInLayer::GetCamTargetBuff(void)	const
{
	return *CamTargetBuff;
}
ImageBuffer     &DataInLayer::GetBitBuff(void)	const
{
	return *BitBuff;
}
ImageBuffer     &DataInLayer::GetTrialTargetBuff(void)	const
{
	return *TrialTargetBuff;
}


ImageBuffer	*DataInLayer::GetMasterBuffPointer(void)	const
{	
	if(Exchanged==false){
		return MasterBuff[0];
	}
	return TargetBuffDim[TargetWPoint];
}

ImageBuffer	*DataInLayer::GetMasterBuffPointer(int n)	const
{	
	if(Exchanged==false){
		if(0<=n && n<AllocatedCountMasterBuff){
			return MasterBuff[n];
		}
		else if(n<0){
			return MasterBuff[0];
		}
		else{
			return NULL;
		}
	}
	return TargetBuffDim[TargetWPoint];
}
ImageBuffer	*DataInLayer::GetDispatchMasterBuffPointer(int n)			const
{
	if(0<=n && n<AllocatedCountMasterBuff){
		return MasterBuff[n];
	}
	return NULL;
}
ImageBuffer	*DataInLayer::FindDispatchMasterBuffPointer(int OriginCode)	const
{
	LayersBase	*LBase=GetLayersBase();
	for(int i=0;i<LBase->AllocatedBufferInfoCount;i++){
		if(MasterBuff[i]!=NULL){
			if(LBase->BufferInfoListDim[i].OriginCode==OriginCode){
				return MasterBuff[i];
			}
		}
	}
	return NULL;
}

ImageBuffer	*DataInLayer::GetBackGroundBuffPointer(void)	const
{	
	return BackGroundBuff[0];
}

ImageBuffer	*DataInLayer::GetBackGroundBuffPointer(int n)	const
{	
	if(0<=n && n<AllocatedCountBackGroundBuff){
		return MasterBuff[n];
	}
	else if(n<0){
		return MasterBuff[0];
	}
	else{
		return NULL;
	}
}
ImageBuffer	*DataInLayer::GetTargetBuffPointer(void)	const
{	
	if(Exchanged==false){
		return TargetBuffDim[TargetWPoint];
	}
	return MasterBuff[0];
}
ImageBuffer	*DataInLayer::GetTargetTRBuffPointer(void)	const
{	
	return TargetTRBuff;
}
ImageBuffer	*DataInLayer::GetRawTargetBuffPointer(void)	const
{	
	return RawTargetBuff;
}
ImageBuffer	*DataInLayer::GetDelayedViewBuffPointer(void)	const
{
	return TargetBuffDim[TargetRPoint];
}
ImageBuffer	*DataInLayer::GetLastDelayedViewBuffPointer(void)	const
{
	if(TargetBuffDim[1]!=NULL){
		if(TargetRPoint==0)
			return TargetBuffDim[1];
		else
			return TargetBuffDim[0];
	}
	return TargetBuffDim[TargetRPoint];
}
ImageBuffer	*DataInLayer::GetCamTargetBuffPointer(void)	const
{
	return CamTargetBuff;
}
ImageBuffer	*DataInLayer::GetBitBuffPointer(void)	const
{
	return BitBuff;
}
ImageBuffer	*DataInLayer::GetTrialTargetBuffPointer(void)	const
{
	return TrialTargetBuff;
}

bool	DataInLayer::IsMasterBuffEnabled(void)	const
{
	if(MasterBuff!=NULL && MasterBuff[0]->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsMasterBuffEnabled(int n)	const
{
	if(0<=n && n<AllocatedCountMasterBuff){
		if(MasterBuff[n]!=NULL && MasterBuff[n]->IsNull()==false){
			return true;
		}
	}
	return false;
}

bool	DataInLayer::IsBackGroundBuffEnabled(void)	const
{
	if(BackGroundBuff!=NULL && BackGroundBuff[0]->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsBackGroundBuffEnabled(int n)	const
{
	if(0<=n && n<AllocatedCountBackGroundBuff){
		if(BackGroundBuff[n]!=NULL && BackGroundBuff[n]->IsNull()==false){
			return true;
		}
	}
	return false;
}

bool	DataInLayer::IsTargetBuffEnabled(void)	const
{
	if(TargetBuffDim[TargetWPoint]!=NULL && TargetBuffDim[TargetWPoint]->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsTargetTRBuffEnabled(void)	const
{
	if(TargetTRBuff!=NULL && TargetTRBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsRawTargetBuffEnabled(void)	const
{
	if(RawTargetBuff!=NULL && RawTargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsDelayedViewBuffEnabled(void)	const
{
	if(TargetBuffDim[TargetRPoint]!=NULL && TargetBuffDim[TargetRPoint]->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsCamTargetBuffEnabled(void)	const
{
	if(CamTargetBuff!=NULL && CamTargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsBitBuffEnabled(void)	const
{
	if(BitBuff!=NULL && BitBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsTrialTargetBuffEnabled(void)	const
{
	if(TrialTargetBuff!=NULL && TrialTargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::HasDataInBitBuff(void)
{
	if(IsBitBuffEnabled()==false)
		return false;
	int	XByte=BitBuff->GetWidth();
	for(int y=0;y<GetMaxLines();y++){
		BYTE	*d=BitBuff->GetY(y);
		for(int x=0;x<XByte;x++){
			if(d[x]!=0){
				return true;
			}
		}
	}
	return false;
}

void	DataInLayer::SetToMasterBuff(ImageBuffer &Img)
{
	if(Exchanged==false){
		*TargetBuffDim[TargetWPoint]=Img;
	}
	*MasterBuff[0]=Img;
}

void	DataInLayer::SetToMasterBuff(int n,ImageBuffer &Img)
{
	if(Exchanged==false){
		*TargetBuffDim[TargetWPoint]=Img;
	}
	if(0<=n && n<AllocatedCountMasterBuff){
		*MasterBuff[n]=Img;
	}
}


void	DataInLayer::SetToBackGroundBuff(ImageBuffer &Img)
{
	*BackGroundBuff[0]=Img;
}

void	DataInLayer::SetToBackGroundBuff(int n,ImageBuffer &Img)
{
	if(0<=n && n<AllocatedCountBackGroundBuff){
		*BackGroundBuff[n]=Img;
	}
}

void	DataInLayer::SetToTargetBuff(ImageBuffer &Img)
{
	if(Exchanged==false){
		*MasterBuff[0]=Img;
	}
	*TargetBuffDim[TargetWPoint]=Img;
}

void	DataInLayer::CopyToDelayedView(void)
{
	if(GetParamGlobal()->AllocViewTargetBuffer==true){
		if(TargetWPoint!=TargetRPoint){
			*TargetBuffDim[TargetRPoint] = *TargetBuffDim[TargetWPoint];
		}
	}
}

bool	DataInLayer::IsEdited(void)	const
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				if(MasterBuff[i]->IsChanged()==true){
					return true;
				}
			}
		}
		if(GetParamGlobal()->AllocateTargetBuff==true
		&& (GetParamGlobal()->AllocateMasterBuff==false || AllocatedCountMasterBuff==0)){
			return TargetBuffDim[TargetWPoint]->IsChanged();
		}
	}
	return false;
}
bool	DataInLayer::IsCalcDone(void)	const
{
	return true;
}
void	DataInLayer::SetEdited(bool edited)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true){
			//MasterBuff->SetChanged(edited);
		}
		if(GetParamGlobal()->AllocateTargetBuff==true){
			//TargetBuff->SetChanged(edited);
		}
	}
}
void	DataInLayer::SetCalcDone(bool calcdone)
{
}

void	DataInLayer::CreateAndCopyTempTargetBuff(void)
{
	if(TempTargetBuff!=NULL){
		delete	TempTargetBuff;
	}

	if((TargetBuffDim[TargetWPoint]!=NULL) && (TargetBuffDim[TargetWPoint]->IsNull()==false)){
		TempTargetBuff=new ImageBuffer();
		TempTargetBuff->Set(GetPage(),ImageBufferTarget ,ParentPage->GetDotPerLine() ,ParentPage->GetMaxLines());
		*TempTargetBuff= *TargetBuffDim[TargetWPoint];
	}
}

void	DataInLayer::CopyTempToTargetBuff(void)
{
	if((TargetBuffDim[TargetWPoint]!=NULL) && (TargetBuffDim[TargetWPoint]->IsNull()==false)){
		*TargetBuffDim[TargetWPoint]= *TempTargetBuff;
	}
}


void	DataInLayer::ReleaseTempTargetBuff(void)
{
	if(TempTargetBuff!=NULL){
		*TargetBuffDim[TargetWPoint]= *TempTargetBuff;
		delete	TempTargetBuff;
		TempTargetBuff=NULL;
	}
}
void	DataInLayer::CopyTargetImageToRaw(void)
{
	if((TargetBuffDim[TargetWPoint]!=NULL)
	&& (RawTargetBuff!=NULL) 
	&& (TargetBuffDim[TargetWPoint]->IsNull()==false) 
	&& (RawTargetBuff->IsNull()==false)){
		*RawTargetBuff= *TargetBuffDim[TargetWPoint];
	}
}
void	DataInLayer::CopyTargetToTransposition(void)
{
	if((TargetBuffDim[TargetWPoint]!=NULL)
	&& (TargetTRBuff!=NULL) 
	&& (TargetBuffDim[TargetWPoint]->IsNull()==false)
	&& (TargetTRBuff->IsNull()==false)){
		if(TargetTRBuff->GetFlagCaptured()==false){
			TargetTRBuff->TranspositionXY(*TargetBuffDim[TargetWPoint]);
		}
	}
}
void	DataInLayer::CopyTargetToCameraBuff(void)
{
	if((TargetBuffDim[TargetWPoint]!=NULL)
	&& (TargetBuffDim[TargetWPoint]->IsNull()==false)
	&& (CamTargetBuff->IsNull()==false)){
		*CamTargetBuff=*TargetBuffDim[TargetWPoint];
	}
}
void	DataInLayer::CopyBitBuffToTransposition(void)
{
	if((BitBuff!=NULL) && (TargetTRBuff!=NULL) && (BitBuff->IsNull()==false) && (TargetTRBuff->IsNull()==false)){
		TargetTRBuff->TranspositionXY(*BitBuff);
	}
}
void	DataInLayer::CopyTargetToTrial(void)
{
	if((TargetBuffDim[TargetWPoint]!=NULL)
	&& (TrialTargetBuff!=NULL)
	&& (TargetBuffDim[TargetWPoint]->IsNull()==false)
	&& (TrialTargetBuff->IsNull()==false)){
		*TrialTargetBuff= *TargetBuffDim[TargetWPoint];
	}
}

void	DataInLayer::RestoreTargetImageFromRaw(void)
{
	if((TargetBuffDim[TargetWPoint]!=NULL)
	&& (RawTargetBuff!=NULL)
	&& (TargetBuffDim[TargetWPoint]->IsNull()==false)
	&& (RawTargetBuff->IsNull()==false)){
		*TargetBuffDim[TargetWPoint] =*RawTargetBuff;
	}
}
bool	DataInLayer::CopyFrom(QImage &SrcImg ,bool ToMaster)
{
	ImageBuffer *DestBuff;
	if(ToMaster==true){
		DestBuff= &GetMasterBuff();
	}
	else{
		DestBuff= &GetTargetBuff();
	}

	QImage	Img=SrcImg.convertToFormat(QImage::Format_ARGB32);
	int	YLen=min(Img.height(),GetMaxLines());
	int	XLen=min(Img.width() ,GetDotPerLine());

	for(int y=0;y<YLen;y++){
		BYTE	*s=Img.scanLine(y);
		BYTE	*d2=DestBuff->GetY(y);
		for(int x=0;x<XLen;x++){
			*d2= *s;
			s+=4;
			d2++;
		}
	}
	return true;
}

void	DataInLayer::UndoPasteRect(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return;
	}
	DisplayImage::DisplayType	DType=(DisplayImage::DisplayType)d;
	ImageBuffer	*DBuff=NULL;
	if(DType==DisplayImage::__Target){
		DBuff=&GetTargetBuff();
	}
	else if(DType==DisplayImage::__Master){
		DBuff=&GetMasterBuff();
	}
	else if(DType==DisplayImage::__DelayedView){
		DBuff=&GetDelayedViewBuff();
	}
	else if(DType==DisplayImage::__RawTarget){
		DBuff=&GetRawTargetBuff();
	}
	else if(DType==DisplayImage::__CamTarget){
		DBuff=&GetCamTargetBuff();
	}
	else if(DType==DisplayImage::__TrialTarget){
		DBuff=&GetTrialTargetBuff();
	}
	FlexAreaImage	UndoAreaImage;
	if(UndoAreaImage.Load(f)==false){
		return;
	}
	UndoAreaImage.CopyToBuffer(*DBuff);
}
void	DataInLayer::UndoMoveImage(QIODevice *f)
{
	int		XDir,YDir;
	bool	FlagMaster;
	bool	FlagTarget;

	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(::Load(f,XDir)==false){
		return;
	}
	if(::Load(f,YDir)==false){
		return;
	}
	if(FlagMaster==true){
		FlexAreaImage	UndoAreaImageV;
		FlexAreaImage	UndoAreaImageH;
		UndoAreaImageV.Load(f);
		UndoAreaImageH.Load(f);
		GetMasterBuff().MoveImage(-XDir,-YDir);
		UndoAreaImageV.CopyToBuffer(GetMasterBuff());
		UndoAreaImageH.CopyToBuffer(GetMasterBuff());
	}
	if(FlagTarget==true){
		FlexAreaImage	UndoAreaImageV;
		FlexAreaImage	UndoAreaImageH;
		UndoAreaImageV.Load(f);
		UndoAreaImageH.Load(f);
		GetTargetBuff().MoveImage(-XDir,-YDir);
		UndoAreaImageV.CopyToBuffer(GetTargetBuff());
		UndoAreaImageH.CopyToBuffer(GetTargetBuff());
	}
}

void	DataInLayer::UndoRotateImage(QIODevice *f)
{
	double	Angle;
	bool	FlagMaster;
	bool	FlagTarget;

	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(::Load(f,Angle)==false){
		return;
	}
	if(FlagMaster==true){
		GetMasterBuff().Load(f);
	}
	if(FlagTarget==true){
		GetTargetBuff().Load(f);
	}
}
//---------------------------------------------------------------------------

void	DataInLayer::UndoMirrorImage(QIODevice *f)
{
	bool	FlagMaster;
	bool	FlagTarget;
	bool	MirrorX;
	bool	MirrorY;

	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(::Load(f,MirrorX)==false){
		return;
	}
	if(::Load(f,MirrorY)==false){
		return;
	}
	if(FlagMaster==true){
		GetMasterBuff().Load(f);
	}
	if(FlagTarget==true){
		GetTargetBuff().Load(f);
	}
}
void	DataInLayer::SlotChangedMasterImage()
{
	emit	SignalChangedMasterImage(Layer);
}
//---------------------------------------------------------------------------

DataInPage::ConstructionData::ConstructionData(DataInPage *parent)
{
	DotPerLine	=0;
	MaxLines	=0;
	OutlineOffset.x=parent->GetParamGlobal()->DotPerLine * parent->Page;
	OutlineOffset.y=0;
}
DataInPage::ConstructionData::ConstructionData(void)
{
	DotPerLine	=0;
	MaxLines	=0;
}

DataInPage::ConstructionData::~ConstructionData(void)
{
}

bool    DataInPage::ConstructionData::Save(QIODevice *f)
{
	if(::Save(f,OutlineOffset)==false){
		return false;
	}
	if(::Save(f,DotPerLine)==false){
		return false;
	}
	if(::Save(f,MaxLines)==false){
		return false;
	}
	return true;
}
bool    DataInPage::ConstructionData::Load(QIODevice *f)
{
	if(::Load(f,OutlineOffset)==false){
		return false;
	}
	if(::Load(f,DotPerLine)==false){
		return false;
	}
	if(::Load(f,MaxLines)==false){
		return false;
	}
	return true;
}

DataInPage::DataInPage(int page,PageDataInOnePhase	*parentPhase) 
:LearningInPage(page,parentPhase->GetLayersBase())
,Parent(parentPhase->GetLayersBase())
,ParentPhase(parentPhase)
,SystemResultContainer(parentPhase->GetLayersBase())
,Page(page)
,CData(this)
,CDataBack(this)
,ThreadImageCompresser(parentPhase->GetLayersBase(),this)
{
	IsWaitingReq		=false;
	LayerData		=NULL;
	UncoveredMap	=NULL;
	UncoveredXByte	=0;
	UncoveredYLen	=0;
	OKCounter		=0;
	NGCounter		=0;

	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
	ResultLoaded=new LoadedInfoContainerInPhase();
	AnyData		=new AnyDataContainer();
	EnableCapture		=true;
}

DataInPage::~DataInPage(void)
{
    Release();
}

void	DataInPage::SetCData(void)
{
	if(GetParamGlobal()->CountOfPageLocal>GetPage()){
		if(GetParamGlobal()->PageLocalData[GetPage()].UseEachPage==true
		&& GetParamGlobal()->PageLocalData[GetPage()].DotPerLine!=0
		&& GetParamGlobal()->PageLocalData[GetPage()].MaxLines!=0){
			CData.DotPerLine=GetParamGlobal()->PageLocalData[GetPage()].DotPerLine;
			CData.MaxLines	=GetParamGlobal()->PageLocalData[GetPage()].MaxLines;
			//CData.OutlineOffset	=GetPage()*GetParamGlobal()->DotPerLine;
		}
	}
}

void    DataInPage::Initial(bool EnabledImageMemoryAllocation)
{
	if(LayerData!=NULL){
		delete	[]LayerData;
	}

	AllocatedLayerNumb	=GetLayerNumb();
	LayerData			=new DataInLayer*[GetLayerNumb()];
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]=new DataInLayer(this);
		LayerData[Ly]->Layer				=Ly;
		//LayerData[Ly]->ParentPage		=this;
		LayerData[Ly]->Initial(EnabledImageMemoryAllocation);
		connect(LayerData[Ly],SIGNAL(SignalChangedMasterImage(int)),this,SLOT(SlotChangedMasterImage(int)));
	}
	if(GetParamGlobal()->ModeCompressNGImage==true && GetParamGlobal()->OutputResult==true && GetParamGlobal()->OMPResultCompress==true){
		ThreadImageCompresser.start();
	}

	DymmyPointsForPages.RemoveAll();
	DymmyPointsForPages.Add(0				,0				,/**/"0");
	DymmyPointsForPages.Add(GetDotPerLine()	,0				,/**/"1");
	DymmyPointsForPages.Add(0				,GetMaxLines()	,/**/"2");
}
void    DataInPage::ReleaseInside(void)
{
	LoadedInfoList	*r;
	while((r=ResultLoaded->GetFirst())!=NULL){
		ResultLoaded->RemoveList(r);
		delete	r;
	}
	AllocatedLayerNumb=0;
	ThreadImageCompresser.CloseMode=true;
	ThreadImageCompresser.wait(10000);
}
void    DataInPage::Release(void)
{
	if(LayerData!=NULL){
		for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
			delete	LayerData[Ly];
		}
		delete	[]LayerData;
		LayerData=NULL;
	}

	if(UncoveredMap!=NULL){
		DeleteMatrixBuff(UncoveredMap,UncoveredYLen);
		UncoveredMap=NULL;
	}
	UncoveredXByte	=0;
	UncoveredYLen	=0;

	//_heapchk();
	if(ResultLoaded!=NULL){
		ResultLoaded->RemoveAll();
		delete	ResultLoaded;
		ResultLoaded=NULL;
	}

	if(DynamicMaskMap!=NULL){
		DeleteMatrixBuff(DynamicMaskMap,DynamicMaskMapYLen);
		DynamicMaskMap		=NULL;
		DynamicMaskMapXByte	=0;
		DynamicMaskMapYLen	=0;
	}
	if(AnyData!=NULL){
		delete	AnyData;
		AnyData=NULL;
	}
}

void	DataInPage::SetEnableCapture(bool b)
{
	EnableCapture=b;
}
bool	DataInPage::GetEnableCapture(void)	const
{
	return EnableCapture;
}
void	DataInPage::SlotChangedMasterImage(int LayerNo)
{
	emit	SignalChangedMasterImage(Page ,LayerNo);
}

int	DataInPage::GetLayerNumb(void)	const
{	
	ParamGlobal	*Pg=GetLayersBase()->GetParamGlobal();
	if(Pg->CountOfPageLocal>GetPage() && Pg->PageLocalData[GetPage()].UseEachPage==true){
		return Pg->PageLocalData[GetPage()].LayerNumb;
	}
	return(Pg->LayerNumb);
}

int		DataInPage::GetDotPerLine(void)	const
{	
	if(CData.DotPerLine>0)
		return CData.DotPerLine;
	ParamGlobal	*Pg=GetLayersBase()->GetParamGlobal();
	if(Pg->CountOfPageLocal>GetPage() && Pg->PageLocalData[GetPage()].UseEachPage==true){
		return Pg->PageLocalData[GetPage()].DotPerLine;
	}
	return Pg->DotPerLine;
}
int		DataInPage::GetMaxLines(void)	const
{	
	if(CData.DotPerLine>0)
		return CData.MaxLines;
	ParamGlobal	*Pg=GetLayersBase()->GetParamGlobal();
	if(Pg->CountOfPageLocal>GetPage() && Pg->PageLocalData[GetPage()].UseEachPage==true){
		return Pg->PageLocalData[GetPage()].MaxLines;
	}
	return(Pg->MaxLines);
}
void	DataInPage::SetDotPerLine(int d)
{
	CData.DotPerLine=d;
}
void	DataInPage::SetMaxLines(int d)
{
	CData.MaxLines=d;
}
void	DataInPage::ResetSize(void)
{
	CData.DotPerLine=-1;
	CData.MaxLines	=-1;
}

void	DataInPage::SetResultLoaded(LoadedInfoContainerInPhase &res)
{	
	*ResultLoaded=res;
}

LoadedInfoContainerInPhase	&DataInPage::GetResultLoaded(void)
{	
	return *ResultLoaded;
}

void	DataInPage::ClearResultLoaded(void)
{	
	ResultLoaded->RemoveAll();
}

bool	DataInPage::AllocateDynamicMasking(void)
{
	if(Parent->UseDynamicMasking==true){
		int	iXByte=(GetDotPerLine()+7)/8;
		if((iXByte!=GetDynamicMaskMapXByte()) || (GetDynamicMaskMapYLen()!=GetMaxLines()) || DynamicMaskMap==NULL){
			if(DynamicMaskMap!=NULL){
				DeleteMatrixBuff(DynamicMaskMap,DynamicMaskMapYLen);
			}
			DynamicMaskMapXByte	=iXByte;
			DynamicMaskMapYLen	=GetMaxLines();
			DynamicMaskMap	=MakeMatrixBuff(DynamicMaskMapXByte ,DynamicMaskMapYLen);
		}
	}
	return true;
}
bool	DataInPage::Reallocate(int newLayerNumb)
{
	if(AllocatedLayerNumb<newLayerNumb){
		DataInLayer	**tLayerData	=new DataInLayer*[newLayerNumb];
		int	Ly;
		for(Ly=0;Ly<AllocatedLayerNumb;Ly++){
			if(LayerData[Ly]==NULL){
				break;
			}
			tLayerData[Ly]=LayerData[Ly];
		}
		LayerData=tLayerData;
		for(;Ly<newLayerNumb;Ly++){
			LayerData[Ly]=new DataInLayer(this);
			LayerData[Ly]->Layer				=Ly;
			//LayerData[Ly]->ParentPage		=this;
			LayerData[Ly]->Initial(true);
			connect(LayerData[Ly],SIGNAL(SignalChangedMasterImage(int)),this,SLOT(SlotChangedMasterImage(int)));
		}
	}
	else if(AllocatedLayerNumb>newLayerNumb){
		for(int Ly=newLayerNumb;Ly<AllocatedLayerNumb;Ly++){
			if(LayerData[Ly]!=NULL){
				delete	LayerData[Ly];
				LayerData[Ly]=NULL;
			}
		}
	}
	AllocatedLayerNumb=newLayerNumb;
	return true;
}
bool	DataInPage::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			if(LayerData[Ly]->ReallocateMasterCount(CountMaster)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
bool	DataInPage::ReallocateBackGroundCount(int CountMaster)
{
	bool	Ret=true;
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			if(LayerData[Ly]->ReallocateBackGroundCount(CountMaster)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
void	DataInPage::ClearDynamicMaskMap(void)
{
	if(Parent->UseDynamicMasking==true){
		if(DynamicMaskMap==NULL){
			AllocateDynamicMasking();
		}
		if(DynamicMaskMap!=NULL){
			MatrixBuffClear	(DynamicMaskMap ,0 ,DynamicMaskMapXByte ,DynamicMaskMapYLen);
		}
	}
}

bool	DataInPage::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	if(GetParamGlobal()->MaximumDotPerLine>0 && GetParamGlobal()->MaximumDotPerLine<NewDotPerLine){
		NewDotPerLine=GetParamGlobal()->MaximumDotPerLine;
	}
	if(GetParamGlobal()->MaximumMaxLines>0 && GetParamGlobal()->MaximumMaxLines<NewMaxLines){
		NewMaxLines=GetParamGlobal()->MaximumMaxLines;
	}

	CData.DotPerLine	=NewDotPerLine;
	CData.MaxLines		=NewMaxLines;
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			if(LayerData[Ly]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
				Ret=false;
			}
		}
	}
	DymmyPointsForPages.RemoveAll();
	DymmyPointsForPages.Add(0				,0				,/**/"0");
	DymmyPointsForPages.Add(GetDotPerLine()	,0				,/**/"1");
	DymmyPointsForPages.Add(0				,GetMaxLines()	,/**/"2");
	return Ret;
}
	
void	DataInPage::ReallocMemoryMaster(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReallocMemoryMaster();
		}
	}
}
void	DataInPage::ReallocMemoryBackGround(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReallocMemoryBackGround();
		}
	}
}

void	DataInPage::ReallocMemoryTarget(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReallocMemoryTarget();
		}
	}
}

void	DataInPage::AllocateTargetTRBuff(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->AllocateTargetTRBuff();
		}
	}
}

void	DataInPage::ReleaseTargetTRBuff(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReleaseTargetTRBuff();
		}
	}
}
void	DataInPage::LockTarget(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessTarget.lock();
	}
}
void	DataInPage::UnlockTarget(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessTarget.unlock();
	}
}
void	DataInPage::LockMaster(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessMaster.lock();
	}
}
void	DataInPage::UnlockMaster(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessMaster.unlock();
	}
}

void	DataInPage::SwapImageOutOfBuffer(int ImageDataType)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->SwapImageOutOfBuffer(ImageDataType);
	}
}

void	DataInPage::SwapImageInToBuffer(int ImageDataType)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->SwapImageInToBuffer(ImageDataType);
	}
}

XYData	*DataInPage::GetOutlineOffset(void)
{	
	if(GetLayersBase()->GetDefaultArrangeMode()==false){
		return &CData.OutlineOffset;
	}
	else{
		switch(GetLayersBase()->GetParamGlobal()->DefaultImageArrange){
			case 1:
				CDataBack.OutlineOffset.x=GetLayersBase()->GetParamGlobal()->DotPerLine*GetPage();
				CDataBack.OutlineOffset.y=0;
				break;
			case 2:
				CDataBack.OutlineOffset.x=0;
				CDataBack.OutlineOffset.y=GetLayersBase()->GetParamGlobal()->MaxLines*GetPage();
				break;
			default:
				CDataBack.OutlineOffset.x=0;
				CDataBack.OutlineOffset.y=0;
		}
		return &CDataBack.OutlineOffset;
	}
}
void	DataInPage::SetGlobalOutlineOffset(int X ,int Y)
{
	CData.OutlineOffset.x=X;
	CData.OutlineOffset.y=Y;
}

XYData	*DataInPage::GetGlobalOutlineOffset(void)	const
{
	int	GPage=Parent->GetGlobalPageFromLocal(GetPage());
	XYData	*XY=Parent->GetGlobalOutlineOffset(GPage);
	return XY;
}

void	DataInPage::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	x1=CData.OutlineOffset.x;
	y1=CData.OutlineOffset.y;
	x2=CData.OutlineOffset.x+GetDotPerLine();
	y2=CData.OutlineOffset.y+GetMaxLines();
}

bool    DataInPage::SaveAttr(QIODevice *f)
{
	ConstructionData	CDataDummy(this);
	if(CDataDummy.Save(f)==false){
		return false;
	}
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->SaveAttr(f)==false){
			return false;
		}
	}
	return true;
}
bool    DataInPage::LoadAttr(QIODevice *f)
{
	ConstructionData	CDataDummy(this);
	if(CDataDummy.Load(f)==false){
		return false;
	}
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;Ly<(AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->LoadAttr(f)==false){
			return false;
		}
	}
	if(Ly<iLayerNumb){
		DataInLayer	Dummy(this);
		for(;Ly<iLayerNumb;Ly++){
			if(Dummy.LoadAttr(f)==false){
				return false;
			}
		}
	}
	return true;
}
bool    DataInPage::SaveBrightTable(QIODevice *f)
{
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->SaveBrightTable(f)==false){
			return false;
		}
	}
	return true;
}

bool    DataInPage::LoadBrightTable(QIODevice *f)
{
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;Ly<(AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->LoadBrightTable(f)==false){
			return false;
		}
	}
	return true;
}
bool    DataInPage::Save(QIODevice *f)
{
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool    DataInPage::Load(QIODevice *f)
{
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;(Ly<AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->Load(f)==false){
			return false;
		}
	}
	if(Ly<iLayerNumb){
		DataInLayer	Dummy(this);
		for(;Ly<iLayerNumb;Ly++){
			if(Dummy.Load(f)==false){
				return false;
			}
		}
	}

	return true;
}
bool    DataInPage::SaveControlPointsForPages(QIODevice *f)
{
	if(ControlPointsForPages.Save(f)==false)
		return false;
	return true;
}
bool    DataInPage::LoadControlPointsForPages(QIODevice *f)
{
	if(ControlPointsForPages.Load(f)==false)
		return false;
	return true;
}
void	DataInPage::ClearSystemResult(void)
{
	SystemResultContainer.ClearSystemResult();
}
void	DataInPage::ReallocateSystemResult(int AllocCount)
{
	SystemResultContainer.ReallocateDimCount(AllocCount);
}

void	DataInPage::PushSystemResult(const QByteArray &data)
{
	SystemResultContainer.PushResult(data);
}

SystemResult	*DataInPage::PopSystemResult(void)
{
	return SystemResultContainer.PopResult();
}
SystemResult	*DataInPage::GetLastSystemResult(void)
{
	return SystemResultContainer.GetLastResult();
}
int		DataInPage::GetStockedSystemResult(void)
{
	return SystemResultContainer.GetStockedSystemResult();
}


const	XYPointContainerWithName	&DataInPage::GetControlPointsForPages(void)
{
	if(ControlPointsForPages.GetCount()==0){
		return DymmyPointsForPages;
	}
	return ControlPointsForPages;
}

bool	DataInPage::SaveImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->SaveImage(f ,X1 ,Y1 ,X2, Y2)==false){
			return false;
		}
	}
	return true;
}
bool	DataInPage::LoadImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;(Ly<AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->LoadImage(f ,X1 ,Y1 ,X2, Y2)==false){
			return false;
		}
	}
	if(Ly<iLayerNumb){
		DataInLayer	Dummy(this);
		for(;Ly<iLayerNumb;Ly++){
			if(Dummy.LoadImage(f ,X1 ,Y1 ,X2, Y2)==false){
				return false;
			}
		}
	}
	return true;
}

bool	DataInPage::ClipAreaGlobal(FlexArea &Area)
{
	int x1 ,y1 ,x2 ,y2;
	GetArea(x1 ,y1 ,x2 ,y2);
	Area.ClipArea(x1 ,y1 ,x2 ,y2);
	if(Area.IsNull()==true){
		return false;
	}
	return true;
}
bool	DataInPage::ClipAreaLocal(FlexArea &Area)
{
	Area.ClipArea(0 ,0 , GetDotPerLine()-1, GetMaxLines()-1);
	if(Area.IsNull()==true){
		return false;
	}
	return true;
}

bool	DataInPage::ClipMoveAreaFromGlobal(FlexArea &GlobalArea)
{
	GlobalArea.MoveToNoClip(-GetOutlineOffset()->x ,-GetOutlineOffset()->y);
	return ClipAreaLocal(GlobalArea);
}


bool	DataInPage::ClipMoveVectorFromGlobal(VectorLineBase *GlobalVector)
{
	GlobalVector->MoveTo(-GetOutlineOffset()->x ,-GetOutlineOffset()->y);
	return ClipVectorLocal(GlobalVector);
}

bool	DataInPage::ClipVectorLocal(VectorLineBase *LocalVector)
{
	LocalVector->ClipArea(0 ,0 , GetDotPerLine(), GetMaxLines());
	if(LocalVector->IsNull()==true){
		return false;
	}
	return true;
}


void	DataInPage::GetLocalMatrixFromGlobalInMaster(int globalX ,int globalY ,int &localX ,int &localY)
{
	localX=globalX-GetOutlineOffset()->x;
	localY=globalY-GetOutlineOffset()->y;
}
void	DataInPage::GetGlobalMatrixFromLocalInMaster(int localX ,int localY ,int &globalX ,int &globalY)
{
	globalX=localX+GetOutlineOffset()->x;
	globalY=localY+GetOutlineOffset()->y;
}
bool	DataInPage::IsInclude(int localX ,int localY)	const
{
	if((localX<0) || (GetDotPerLine()<=localX)
	|| (localY<0) || (GetMaxLines()<=localY)){
		return false;
	}
	return true;
}


bool	DataInPage::IsOverlapped(FlexArea &globalArea)	const
{
	return globalArea.CheckOverlapRectangle( CData.OutlineOffset.x,CData.OutlineOffset.y
											,CData.OutlineOffset.x+GetDotPerLine() ,CData.OutlineOffset.y+GetMaxLines() );
}

bool	DataInPage::IsOverlapped(VectorLineBase *Vector)	const
{
	return Vector->CheckOverlapRectangle( CData.OutlineOffset.x,CData.OutlineOffset.y
											,CData.OutlineOffset.x+GetDotPerLine() ,CData.OutlineOffset.y+GetMaxLines() );
}
void	DataInPage::IncrementNGCounterWithMutex(int result)
{
	MutexNGCounter.lockForWrite();
	if(result>1){
		NGCounter++;
	}
	else if(result==1){
		OKCounter++;
	}
	MutexNGCounter.unlock();
}
void	DataInPage::AddNGCounter(int NGCount)
{
	MutexNGCounter.lockForWrite();
	NGCounter+=NGCount;
	MutexNGCounter.unlock();
}

int		DataInPage::GetNGCounter(void)	
{
	MutexNGCounter.lockForRead();
	int	ret=NGCounter;
	MutexNGCounter.unlock();
	return ret;
}
int		DataInPage::GetOKCounter(void)
{
	MutexNGCounter.lockForRead();
	int	ret=OKCounter;
	MutexNGCounter.unlock();
	return ret;
}
void	DataInPage::ClearNGCounterWithMutex(void)
{
	MutexNGCounter.lockForWrite();
	NGCounter=0;
	OKCounter=0;
	MutexNGCounter.unlock();
}

XYRegPointContainer	&DataInPage::GetRegulation(void)
{	
	return XYRegulation;
}

bool	DataInPage::HasRegulation(void)
{
	if(XYRegulation.GetCount()==0){
		return false;
	}
	return true;
}

void	DataInPage::SetRegulation(XYRegPointContainer &s)
{	
	XYRegulation=s;
}
void	DataInPage::ClearRegulation(void)
{	
	XYRegulation.RemoveAll();
}
bool	DataInPage::HasRealTransform(int localX ,int localY)	const
{
	double realX ,realY;
	if(TransformImageToReal(localX ,localY,realX ,realY)==false){
		return false;
	}
	return true;
}

int		DataInPage::GetStoringTargetCounter(void)	const
{
	int	MaxD=0;
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		int	d=LayerData[Ly]->GetStoringTargetCounter();
		if(MaxD<d){
			MaxD=d;
		}
	}
	return MaxD;
}
void	DataInPage::SwitchImageBuff(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->SwitchImageBuff();
	}
}
void	DataInPage::CopyImage(int sourceImageType ,int destImageType)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->CopyImage(sourceImageType ,destImageType);
	}
}
void	DataInPage::GetMasterImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetMasterBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetMasterImages(int n,ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(p->GetMasterBuffPointer(n));
		Images.AppendList(r);
	}
}
void	DataInPage::GetTargetImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetTargetBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetTargetTRImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetTargetTRBuff());
		Images.AppendList(r);
	}
}void	DataInPage::GetBitImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetBitBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetDelayedViewImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetDelayedViewBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetLastDelayedViewImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetLastDelayedViewBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetRawTargetImages	(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetRawTargetBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetCamTargetImages	(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetCamTargetBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetTrialTargetImages(ImagePointerContainer &Images)	const
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetTrialTargetBuff());
		Images.AppendList(r);
	}
}
int	DataInPage::GetMasterImages		(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetMasterBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetMasterImages	(int n,ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetMasterBuffPointer(n);
	}
	return LNumb;
}
int	DataInPage::GetTargetImages		(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetTargetBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetTargetTRImages	(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetTargetTRBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetDelayedViewImages(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetDelayedViewBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetLastDelayedViewImages(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetLastDelayedViewBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetBitImages		(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetBitBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetRawTargetImages	(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetRawTargetBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetCamTargetImages	(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetCamTargetBuffPointer();
	}
	return LNumb;
}
int	DataInPage::GetTrialTargetImages	(ImageBuffer *Images[],int MaxCountOfBuff)	const
{
	int	LNumb=min(GetLayerNumb(),MaxCountOfBuff);
	for(int i=0;i<LNumb;i++){
		DataInLayer	*p=GetLayerData(i);
		Images[i]=p->GetTrialTargetBuffPointer();
	}
	return LNumb;
}
bool	DataInPage::IsEdited(void)	const
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		if(p->IsEdited()==true){
			return true;
		}
	}
	return false;
}
bool	DataInPage::IsCalcDone(void)	const
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		if(p->IsCalcDone()==false){
			return false;
		}
	}
	return false;
}
void	DataInPage::SetEdited(bool edited)
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		p->SetEdited(edited);
	}
}
void	DataInPage::SetCalcDone(bool calcdone)
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		p->SetCalcDone(calcdone);
	}
}

void	DataInPage::CopyTargetImageToRaw(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyTargetImageToRaw();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyTargetImageToRaw();
		}
	}
}
void	DataInPage::CopyTargetToTransposition(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyTargetToTransposition();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyTargetToTransposition();
		}
	}
}
void	DataInPage::CopyTargetToCameraBuff(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyTargetToCameraBuff();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyTargetToCameraBuff();
		}
	}
}

void	DataInPage::CopyBitBuffToTransposition(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyBitBuffToTransposition();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyBitBuffToTransposition();
		}
	}
}
void	DataInPage::CopyTargetToTrial(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyTargetToTrial();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyTargetToTrial();
		}
	}
}

void	DataInPage::SetCompressedContainer(NGImageContainerInPage *point)
{
	ThreadImageCompresser.Set(point);
	point->SetCompressedFlag(false);
}

void	DataInPage::MakeUncoveredMap(void)
{
	if(UncoveredMap==NULL){
		UncoveredXByte	=(GetDotPerLine()+7)/8;
		UncoveredYLen	=GetMaxLines();
		UncoveredMap=MakeMatrixBuff(UncoveredXByte,UncoveredYLen);
	}
	MatrixBuffClear(UncoveredMap ,0 ,UncoveredXByte ,UncoveredYLen);
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->MakeUncoveredMap(GetPage() ,UncoveredMap, UncoveredXByte ,UncoveredYLen);
	}
	MatrixBuffNot(UncoveredMap, UncoveredXByte ,UncoveredYLen);
	BYTE	**TmpMap=MakeMatrixBuff(UncoveredXByte,UncoveredYLen);
	for(int i=0;i<GetParamGlobal()->ShrinkDotUncoveredArea;i++){
		ThinArea(UncoveredMap
				,TmpMap
				,UncoveredXByte ,UncoveredYLen);
	}
	DeleteMatrixBuff(TmpMap,UncoveredYLen);
}

const BYTE	**DataInPage::GetUncoveredMap(int &XByte ,int &YLen)
{
	XByte	=UncoveredXByte;
	YLen	=UncoveredYLen;
	return (const BYTE **)UncoveredMap;
}

void	DataInPage::LockTxComm(void)	
{	
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()!=0){
//		CommTxLock.lock();
	}
}
void	DataInPage::UnlockTxComm(void)
{	
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()!=0){
//		CommTxLock.unlock();	
	}
}
void	DataInPage::LockRxComm(void)	
{	
//	CommRxLock.lock();
}
void	DataInPage::UnlockRxComm(void)
{	
//	CommRxLock.unlock();	
}

bool	DataInPage::IsIncludeFromGlobal(int GlobalX ,int GlobalY)
{
	int	localX ,localY;
	GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,localX ,localY);
	return IsInclude(localX ,localY);
}

bool	DataInPage::CopyFrom(QImage &SrcImg ,bool ToMaster)
{
	ImageBuffer **DestBuff=new ImageBuffer*[GetLayerNumb()];
	for(int layer=0;layer<GetLayerNumb();layer++){
		if(ToMaster==true){
			DestBuff[layer]= &GetLayerData(layer)->GetMasterBuff();
		}
		else{
			DestBuff[layer]= &GetLayerData(layer)->GetTargetBuff();
		}
	}
	bool	ret=CopyFrom(DestBuff,SrcImg);
	delete	[]DestBuff;
	return ret;
}
void	DataInPage::CopyToDelayedView(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		GetLayerData(layer)->CopyToDelayedView();
	}
}

bool	DataInPage::CopyFrom(ImageBuffer *DestBuff[],QImage &SrcImg)
{
	QImage	Img=SrcImg.convertToFormat(QImage::Format_ARGB32);
	int	YLen=min(Img.height(),GetMaxLines());
	int	XLen=min(Img.width() ,GetDotPerLine());
	if(GetLayerNumb()>=3){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Img.scanLine(y);
			BYTE	*d0;
			BYTE	*d1;
			BYTE	*d2;
			d0=DestBuff[0]->GetY(y);
			d1=DestBuff[1]->GetY(y);
			d2=DestBuff[2]->GetY(y);
			for(int x=0;x<XLen;x++){
				*d2= *s;
				*d1= *(s+1);
				*d0= *(s+2);
				s+=4;
				d0++;
				d1++;
				d2++;
			}
		}
	}
	if(GetLayerNumb()==2){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Img.scanLine(y);
			BYTE	*d0;
			BYTE	*d1;
			d0=DestBuff[0]->GetY(y);
			d1=DestBuff[1]->GetY(y);
			for(int x=0;x<XLen;x++){
				*d0= *s;
				*d1= *(s+1);
				s+=4;
				d0++;
				d1++;
			}
		}
	}
	if(GetLayerNumb()==1){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Img.scanLine(y);
			BYTE	*d0;
			d0=DestBuff[0]->GetY(y);
			for(int x=0;x<XLen;x++){
				*d0= *s;
				s+=4;
				d0++;
			}
		}
	}
	return true;
}
bool	DataInPage::CopyTo(QImage &DstImg ,bool ToMaster)
{
	ImageBuffer *SrcBuff[3];
	for(int layer=0;layer<GetLayerNumb() && layer<3;layer++){
		if(ToMaster==true){
			SrcBuff[layer]= &GetLayerData(layer)->GetMasterBuff();
		}
		else{
			SrcBuff[layer]= &GetLayerData(layer)->GetTargetBuff();
		}
	}

	DstImg	=QImage(GetDotPerLine(),GetMaxLines(),QImage::Format_RGB32);
	int	YLen=GetMaxLines();
	int	XLen=GetDotPerLine();
	if(GetLayerNumb()>=3){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*d=DstImg.scanLine(y);
				BYTE	*s0=SrcBuff[0]->GetY(y);
				BYTE	*s1=SrcBuff[1]->GetY(y);
				BYTE	*s2=SrcBuff[2]->GetY(y);
				for(int x=0;x<XLen;x++){
					*(d+0)= *s2;
					*(d+1)= *s1;
					*(d+2)= *s0;
					*(d+3)=0xFF;
					d+=4;
					s0++;
					s1++;
					s2++;
				}
			}
		}
	}
	if(GetLayerNumb()==2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*d=DstImg.scanLine(y);
				BYTE	*s0=SrcBuff[0]->GetY(y);
				BYTE	*s1=SrcBuff[1]->GetY(y);
				for(int x=0;x<XLen;x++){
					*(d+0)= *s1;
					*(d+1)= *s0;
					*(d+2)= *s0;
					*(d+3)=0xFF;
					d+=4;
					s0++;
					s1++;
				}
			}
		}
	}
	if(GetLayerNumb()==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*d=DstImg.scanLine(y);
				BYTE	*s0=SrcBuff[0]->GetY(y);
				for(int x=0;x<XLen;x++){
					*(d+0)= *s0;
					*(d+1)= *s0;
					*(d+2)= *s0;
					*(d+3)=0xFF;
					d+=4;
					s0++;
				}
			}
		}
	}
	return true;
}
void	DataInPage::UndoCopyImageInPhases(QIODevice *f)
{
	bool	FlagMaster;
	bool	FlagTarget;
	int		LayerNumb;
	int		SrcPhase;
	int		DstPhase;

	if(::Load(f,SrcPhase)==false){
		return;
	}
	if(::Load(f,DstPhase)==false){
		return;
	}
	if(::Load(f,LayerNumb)==false){
		return;
	}
	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(0<=SrcPhase && SrcPhase<GetPhaseNumb() && 0<=DstPhase && DstPhase<GetPhaseNumb()){
		//PageDataInOnePhase	*PhSrc=GetLayersBase()->GetPageDataPhase(SrcPhase);
		PageDataInOnePhase	*PhDst=GetLayersBase()->GetPageDataPhase(DstPhase);
		//DataInPage *PageSrc=PhSrc->GetPageData(GetPage());
		DataInPage *PageDst=PhDst->GetPageData(GetPage());
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			//DataInLayer	*LySrc=PageSrc->GetLayerData(Layer);
			DataInLayer	*LyDst=PageDst->GetLayerData(Layer);

			if(FlagMaster==true){
				LyDst->GetMasterBuff().Load(f);
				LyDst->GetMasterBuff().SetChanged(true);
			}

			if(FlagTarget==true){
				LyDst->GetTargetBuff().Load(f);
				LyDst->GetTargetBuff().SetChanged(true);
			}
		}
	}
}
void	DataInPage::UndoPourImage(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return;
	int	MasterNo;
	if(::Load(f,MasterNo)==false)	return;
	DisplayImage::DisplayType	DType=(DisplayImage::DisplayType)d;
	FlexAreaColorImage	UndoAreaImage;
	if(UndoAreaImage.Load(f)==false)	return;

	ImagePointerContainer Images;
	if((DType&DisplayImage::__Master)!=0){
		GetMasterImages(MasterNo,Images);
	}
	else if((DType&DisplayImage::__Target)!=0){
		GetTargetImages(Images);
	}
	else if((DType&DisplayImage::__TargetTR)!=0){
		GetTargetTRImages(Images);
	}
	else if((DType&DisplayImage::__DelayedView)!=0){
		GetDelayedViewImages(Images);
	}
	else if((DType&DisplayImage::__BitBuff)!=0){
	}
	else if((DType&DisplayImage::__RawTarget)!=0){
		GetRawTargetImages(Images);
	}
	else if((DType&DisplayImage::__CamTarget)!=0){
		GetCamTargetImages(Images);
	}
	UndoAreaImage.Draw(Images);
}
void	DataInPage::UndoReplaceColorImage(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return;
	int	MasterNo;
	if(::Load(f,MasterNo)==false)	return;
	DisplayImage::DisplayType	DType=(DisplayImage::DisplayType)d;
	int32	LayerNumb;
	if(::Load(f,LayerNumb)==false)	return;

	ImagePointerContainer Images;
	if((DType&DisplayImage::__Master)!=0){
		GetMasterImages(MasterNo,Images);
	}
	else if((DType&DisplayImage::__Target)!=0){
		GetTargetImages(Images);
	}
	else if((DType&DisplayImage::__TargetTR)!=0){
		GetTargetTRImages(Images);
	}
	else if((DType&DisplayImage::__DelayedView)!=0){
		GetDelayedViewImages(Images);
	}
	else if((DType&DisplayImage::__BitBuff)!=0){
	}
	else if((DType&DisplayImage::__RawTarget)!=0){
		GetRawTargetImages(Images);
	}
	else if((DType&DisplayImage::__CamTarget)!=0){
		GetCamTargetImages(Images);
	}
	for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
		p->GetImage()->Load(f);
	}
}

int		DataInPage::GetCountOfCompressing(void)
{
	return ThreadImageCompresser.GetCountOfCompressing();
}

void	DataInPage::GetMasterPixel(MultiLayerColor &R ,int X,int Y)	const
{
	R.Allocate(GetLayerNumb());
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		DataInLayer	*Ly=GetLayerData(Layer);
		if(Ly->GetMasterBuff().IsNull()==false){
			BYTE	c=Ly->GetMasterBuff().GetPixel(X,Y);
			R.SetBrightness(Layer,c);
		}
	}
}
void	DataInPage::SetMasterPixel(MultiLayerColor &R ,int X,int Y)
{
	for(int Layer=0;Layer<GetLayerNumb() && R.GetLayerNumb();Layer++){
		DataInLayer	*Ly=GetLayerData(Layer);
		if(Ly->GetMasterBuff().IsNull()==false){
			Ly->GetMasterBuff().SetPixel(X,Y,R.GetBrightness(Layer));
		}
	}
}
void	DataInPage::GetTargetPixel(MultiLayerColor &R ,int X,int Y)	const
{
	R.Allocate(GetLayerNumb());
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		DataInLayer	*Ly=GetLayerData(Layer);
		if(Ly->GetTargetBuff().IsNull()==false){
			BYTE	c=Ly->GetTargetBuff().GetPixel(X,Y);
			R.SetBrightness(Layer,c);
		}
	}
}
void	DataInPage::SetTargetPixel(MultiLayerColor &R ,int X,int Y)
{
	for(int Layer=0;Layer<GetLayerNumb() && R.GetLayerNumb();Layer++){
		DataInLayer	*Ly=GetLayerData(Layer);
		if(Ly->GetTargetBuff().IsNull()==false){
			Ly->GetTargetBuff().SetPixel(X,Y,R.GetBrightness(Layer));
		}
	}
}
	
int	DataInPage::SetDispatchMaster(const QString &MasterBuffName, int OriginCode
								,ImageBufferListContainer &s,int pos)
{
	int	Ret=-1;
	ImageBufferList	*p=s.GetFirst();
	for(int Layer=0;Layer<GetLayerNumb() && p!=NULL;Layer++,p=p->GetNext()){
		DataInLayer	*Ly=GetLayerData(Layer);
		Ret=Ly->SetDispatchMaster(MasterBuffName, OriginCode,p,pos);
	}
	return Ret;
}
void	DataInPage::RemoveDispatchMaster(int pos)
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		DataInLayer	*Ly=GetLayerData(Layer);
		Ly->RemoveDispatchMaster(pos);
	}
}

bool	DataInPage::GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,AlgorithmLibrary *LibData ,void *Anything)
{
	bool	Ret=true;
	int	tLayerNumb=GetLayerNumb();
	LogicDLLBaseClass	*LC=GetLayersBase()->GetLogicDLLBase();
	for(int layer=0;layer<tLayerNumb;layer++){
		if(Map[layer]==NULL){
			Map.AppendList(new ConstMapBufferList());
		}
		if(Map[layer]->GetMapBuffer()!=NULL){
			if(LC->GetReflectionMap(Mode,*Map[layer]->GetMapBuffer() ,GetPhaseCode(),GetPage(),layer,LibData ,Anything)==false){
				Ret=false;
			}
		}
		else{
			ConstMapBuffer	*m=new ConstMapBuffer();
			if(LC->GetReflectionMap(Mode,*m ,GetPhaseCode(),GetPage(),layer,LibData ,Anything)==false){
				delete	m;
				Ret=false;
			}
			else{
				Map[layer]->Set(m);
			}
		}
	}
	return Ret;
}

//---------------------------------------------------------------------------
PageDataInOnePhase::PageDataInOnePhase(int phaseCode ,LayersBase *parent)
{
	PhaseCode		=phaseCode;
	Parent			=parent;
	PageData		=NULL;
	FilterContainer	=NULL;
	AllocatedPageNumb=0;
	MasterCode		=-1;
	FromSourcePhase	=-1;
	LotAutoCount	=-1;
	AnyData			=new AnyDataContainer();
}
PageDataInOnePhase::~PageDataInOnePhase(void)
{
	Release();
	delete	AnyData;
	AnyData=NULL;
}

void	PageDataInOnePhase::InitialCreate(LayersBase *Base ,bool EnabledImageMemoryAllocation)
{
	if(PageData!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			if(PageData[page]!=NULL){
				PageData[page]->ReleaseInside();
			}
		}
	}

	if(FilterContainer!=NULL){
	    for(int page=0;page<AllocatedPageNumb;page++){
			FilterContainer[page]->ReleaseAll();
			delete	FilterContainer[page];
		}
		delete	[]FilterContainer;
		FilterContainer=NULL;
	}

	if(PageData!=NULL){
	    for(int i=0;i<AllocatedPageNumb;i++){
		    PageData[i]->Release();
			delete	PageData[i];
	    }
		delete	[]PageData;
		PageData=NULL;
	}

	AllocatedPageNumb	=Base->GetPageNumb();
	PageData		=new DataInPage*[AllocatedPageNumb];

	FilterContainer=new FilterInstanceContainer*[AllocatedPageNumb];
	for(int page=0;page<AllocatedPageNumb;page++){
		FilterContainer[page]=new FilterInstanceContainer(PhaseCode,page,GetLayersBase());
	}

	for(int i=0;i<AllocatedPageNumb;i++){
		PageData[i]=new DataInPage(i,this);
		//PageData[i]->Parent=this;
		PageData[i]->SetCData();
		PageData[i]->Initial(EnabledImageMemoryAllocation);
		PageData[i]->Page=i;
		connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
	}
}
void	PageDataInOnePhase::Release(void)
{
	if(PageData!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			PageData[page]->ReleaseInside();
		}
	    for(int page=0;page<AllocatedPageNumb;page++){
		    PageData[page]->Release();
			delete	PageData[page];
	        }
		delete	[]PageData;
		PageData=NULL;
	}
	if(FilterContainer!=NULL){
	    for(int page=0;page<AllocatedPageNumb;page++){
			FilterContainer[page]->ReleaseAll();
			delete	FilterContainer[page];
		}
		delete	[]FilterContainer;
		FilterContainer=NULL;
	}
	AllocatedPageNumb=0;
}

int		PageDataInOnePhase::GetMaxLayerNumb(void)	const
{
	int	MaxLayerNumb=0;
	for(int i=0;i<AllocatedPageNumb;i++){
		if(PageData[i]!=NULL){
			MaxLayerNumb=max(MaxLayerNumb,PageData[i]->GetLayerNumb());
		}
	}
	return MaxLayerNumb;
}
void	PageDataInOnePhase::LockTarget(void)
{
	int32	PageNumb=Parent->GetPageNumb();
	for(int page=0;page<PageNumb;page++){
		DataInPage	*dp=GetPageData(page);
		dp->LockTarget();
	}
}
void	PageDataInOnePhase::UnlockTarget(void)
{
	int32	PageNumb=Parent->GetPageNumb();
	for(int page=0;page<PageNumb;page++){
		DataInPage	*dp=GetPageData(page);
		dp->UnlockTarget();
	}
}
void	PageDataInOnePhase::LockMaster(void)
{
	int32	PageNumb=Parent->GetPageNumb();
	for(int page=0;page<PageNumb;page++){
		DataInPage	*dp=GetPageData(page);
		dp->LockMaster();
	}
}
void	PageDataInOnePhase::UnlockMaster(void)
{
	int32	PageNumb=Parent->GetPageNumb();
	for(int page=0;page<PageNumb;page++){
		DataInPage	*dp=GetPageData(page);
		dp->UnlockMaster();
	}
}

bool	PageDataInOnePhase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	if(Parent->GetParamGlobal()->MaximumDotPerLine>0 && Parent->GetParamGlobal()->MaximumDotPerLine<NewDotPerLine){
		NewDotPerLine=Parent->GetParamGlobal()->MaximumDotPerLine;
	}
	if(Parent->GetParamGlobal()->MaximumMaxLines>0 && Parent->GetParamGlobal()->MaximumMaxLines<NewMaxLines){
		NewMaxLines=Parent->GetParamGlobal()->MaximumMaxLines;
	}

	for(int i=0;i<AllocatedPageNumb;i++){
		if(PageData[i]!=NULL){
			if(PageData[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
				Ret=false;
			}
		}
	}
	if(FilterContainer!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			if(FilterContainer[page]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
bool	PageDataInOnePhase::ReallocXYPixelsPage(int Page ,int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	if(Parent->GetParamGlobal()->MaximumDotPerLine>0 && Parent->GetParamGlobal()->MaximumDotPerLine<NewDotPerLine){
		NewDotPerLine=Parent->GetParamGlobal()->MaximumDotPerLine;
	}
	if(Parent->GetParamGlobal()->MaximumMaxLines>0 && Parent->GetParamGlobal()->MaximumMaxLines<NewMaxLines){
		NewMaxLines=Parent->GetParamGlobal()->MaximumMaxLines;
	}

	if(0<=Page && Page<Parent->GetPageNumb() && PageData[Page]!=NULL){
		if(PageData[Page]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
		if(FilterContainer!=NULL){
			if(FilterContainer[Page]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
bool	PageDataInOnePhase::Reallocate(int newPageNumb ,int newLayerNumb)
{
	if(newLayerNumb==Parent->GetLayerNumb(0)){
		FilterInstanceContainer	**tFilterContainer=new FilterInstanceContainer*[newPageNumb];
		if(FilterContainer!=NULL){
		    for(int page=0;page<AllocatedPageNumb && page<newPageNumb;page++){
				tFilterContainer[page]=FilterContainer[page];
				FilterContainer[page]=NULL;
			}
			for(int page=newPageNumb;page<AllocatedPageNumb;page++){
				FilterContainer[page]->ReleaseAll();
				delete	FilterContainer[page];
			}
			delete	[]FilterContainer;
			FilterContainer=NULL;
		}
		FilterContainer=tFilterContainer;
		
		for(int page=AllocatedPageNumb;page<newPageNumb;page++){
			FilterContainer[page]=new FilterInstanceContainer(PhaseCode,page,GetLayersBase());
			FilterContainer[page]->Reallocate(newLayerNumb);
		}
	}
	else{
		for(int page=0;page<AllocatedPageNumb;page++){
			FilterContainer[page]->ReleaseAll();
			delete	FilterContainer[page];
		}
		delete	[]FilterContainer;

		FilterContainer=new FilterInstanceContainer*[newPageNumb];
		for(int page=0;page<newPageNumb;page++){
			FilterContainer[page]=new FilterInstanceContainer(PhaseCode,page,GetLayersBase());
			FilterContainer[page]->Reallocate(newLayerNumb);
		}
	}
	if(AllocatedPageNumb<newPageNumb){
		DataInPage	**tPageData=new DataInPage*[newPageNumb];
		int	i;
		for(i=0;i<AllocatedPageNumb;i++){
			if(PageData[i]==NULL){
				break;
			}
			tPageData[i]=PageData[i];
			PageData[i]=NULL;
			tPageData[i]->Reallocate(newLayerNumb);
		}
		delete	[]PageData;
		PageData=tPageData;
		for(;i<newPageNumb;i++){
			PageData[i]=new DataInPage(i,this);
			//PageData[i]->Parent=this;
			PageData[i]->Initial(true);
			PageData[i]->Page=i;
			connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
		}
	}
	else if(AllocatedPageNumb>newPageNumb){
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=new DataInPage(i,this);
				//PageData[i]->Parent=this;
				PageData[i]->Initial(true);
				PageData[i]->Page=i;
				connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
		for(int i=newPageNumb;i<AllocatedPageNumb;i++){
			PageData[i]->Release();
			delete	PageData[i];
			PageData[i]=NULL;
		}
	}
	else{
		if(PageData==NULL){
			PageData=new DataInPage*[newPageNumb];
			for(int i=0;i<newPageNumb;i++){
				PageData[i]=NULL;
			}
		}
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=new DataInPage(i,this);
				//PageData[i]->Parent=this;
				PageData[i]->Initial(true);
				PageData[i]->Page=i;
				connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
	}
	AllocatedPageNumb	=newPageNumb;

	return true;
}

bool	PageDataInOnePhase::Reallocate(int newPageNumb)
{
		FilterInstanceContainer	**tFilterContainer=new FilterInstanceContainer*[newPageNumb];
		if(FilterContainer!=NULL){
		    for(int page=0;page<AllocatedPageNumb && page<newPageNumb;page++){
				tFilterContainer[page]=FilterContainer[page];
				FilterContainer[page]=NULL;
			}
			for(int page=newPageNumb;page<AllocatedPageNumb;page++){
				FilterContainer[page]->ReleaseAll();
				delete	FilterContainer[page];
			}
			delete	[]FilterContainer;
			FilterContainer=NULL;
		}
		FilterContainer=tFilterContainer;
		
		for(int page=AllocatedPageNumb;page<newPageNumb;page++){
			FilterContainer[page]=new FilterInstanceContainer(PhaseCode,page,GetLayersBase());
			FilterContainer[page]->Reallocate(Parent->GetLayerNumb(page));
		}

	if(AllocatedPageNumb<newPageNumb){
		DataInPage	**tPageData=new DataInPage*[newPageNumb];
		int	i;
		for(i=0;i<AllocatedPageNumb;i++){
			if(PageData[i]==NULL){
				break;
			}
			tPageData[i]=PageData[i];
			PageData[i]=NULL;
		}
		delete	[]PageData;
		PageData=tPageData;
		for(;i<newPageNumb;i++){
			PageData[i]=new DataInPage(i,this);
			//PageData[i]->Parent=this;
			PageData[i]->Initial(true);
			PageData[i]->Page=i;
			connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
		}
	}
	else if(AllocatedPageNumb>newPageNumb){
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=new DataInPage(i,this);
				//PageData[i]->Parent=this;
				PageData[i]->Initial(true);
				PageData[i]->Page=i;
				connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
			}
		}
		for(int i=newPageNumb;i<AllocatedPageNumb;i++){
			PageData[i]->Release();
			delete	PageData[i];
			PageData[i]=NULL;
		}
	}
	else{
		if(PageData==NULL){
			PageData=new DataInPage*[newPageNumb];
			for(int i=0;i<newPageNumb;i++){
				PageData[i]=NULL;
			}
		}
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=new DataInPage(i,this);
				//PageData[i]->Parent=this;
				PageData[i]->Initial(true);
				PageData[i]->Page=i;
				connect(PageData[i],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
			}
		}
	}
	AllocatedPageNumb	=newPageNumb;

	return true;
}

bool	PageDataInOnePhase::InsertPage(int IndexPage)	//Create page before Indexed page
{
	int	sPageNumb=GetPageNumb();
	FilterInstanceContainer	**tFilterContainer=new FilterInstanceContainer*[sPageNumb+1];
	if(FilterContainer!=NULL){
		if(0<=IndexPage){
		    int dpage=0;
			int spage=0;
			for(;spage<AllocatedPageNumb && spage<IndexPage;spage++,dpage++){
				tFilterContainer[dpage]=FilterContainer[spage];
				FilterContainer[spage]=NULL;
			}
			tFilterContainer[dpage]=new FilterInstanceContainer(PhaseCode,dpage,GetLayersBase());
			dpage++;
			for(;spage<AllocatedPageNumb && dpage<sPageNumb+1;dpage++,spage++){
				tFilterContainer[dpage]=FilterContainer[spage];
				FilterContainer[spage]=NULL;
			}
		}
		else{
		    int dpage=0;
			int spage=0;
			for(;spage<AllocatedPageNumb && spage<sPageNumb;spage++,dpage++){
				tFilterContainer[dpage]=FilterContainer[spage];
				FilterContainer[spage]=NULL;
			}
			tFilterContainer[dpage]=new FilterInstanceContainer(PhaseCode,dpage,GetLayersBase());
		}
		delete	[]FilterContainer;
		FilterContainer=tFilterContainer;
	}

	if(0<=IndexPage){
		DataInPage	**tPageData=new DataInPage*[sPageNumb+1];
		int dpage=0;
		int spage=0;
		for(;spage<AllocatedPageNumb && spage<IndexPage;spage++,dpage++){
			tPageData[dpage]=PageData[spage];
			PageData[spage]=NULL;
		}
		tPageData[dpage]=new DataInPage(dpage,this);
		tPageData[dpage]->Initial(true);
		tPageData[dpage]->Page=dpage;
		connect(PageData[dpage],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
		dpage++;
		for(;spage<AllocatedPageNumb && dpage<sPageNumb+1;dpage++,spage++){
			tPageData[dpage]=PageData[spage];
			tPageData[dpage]->Page=dpage;
			PageData[spage]=NULL;
		}
		delete	[]PageData;
		PageData=tPageData;
	}
	else{
		DataInPage	**tPageData=new DataInPage*[sPageNumb+1];
		int dpage=0;
		int spage=0;
		for(;spage<AllocatedPageNumb && spage<sPageNumb;spage++,dpage++){
			tPageData[dpage]=PageData[spage];
			PageData[spage]=NULL;
		}
		tPageData[dpage]=new DataInPage(dpage,this);
		tPageData[dpage]->Initial(true);
		tPageData[dpage]->Page=dpage;
		connect(PageData[dpage],SIGNAL(SignalChangedMasterImage(int ,int)),this,SLOT(SlotChangedMasterImage(int,int)));
		delete	[]PageData;
		PageData=tPageData;
	}
	AllocatedPageNumb	=sPageNumb+1;

	return true;
}

bool	PageDataInOnePhase::RemovePage(int IndexPage)
{
	int	sPageNumb=GetPageNumb();
	FilterInstanceContainer	**tFilterContainer=new FilterInstanceContainer*[sPageNumb-1];
	if(FilterContainer!=NULL){
		if(0<=IndexPage){
		    int dpage=0;
			int spage=0;
			for(;spage<AllocatedPageNumb && spage<IndexPage;spage++,dpage++){
				tFilterContainer[dpage]=FilterContainer[spage];
				FilterContainer[dpage]=NULL;
			}
			delete	FilterContainer[spage];
			spage++;
			for(;spage<AllocatedPageNumb && dpage<sPageNumb;dpage++,spage++){
				tFilterContainer[dpage]=FilterContainer[spage];
				FilterContainer[dpage]=NULL;
			}
			delete	[]FilterContainer;
			FilterContainer=tFilterContainer;
		}
	}

	if(0<=IndexPage){
		DataInPage	**tPageData=new DataInPage*[sPageNumb-1];
		int dpage=0;
		int spage=0;
		for(;spage<AllocatedPageNumb && spage<IndexPage;spage++,dpage++){
			tPageData[dpage]=PageData[spage];
			PageData[spage]=NULL;
		}
		delete	PageData[spage];
		spage++;
		for(;spage<AllocatedPageNumb && dpage<sPageNumb;dpage++,spage++){
			tPageData[dpage]=PageData[spage];
			tPageData[dpage]->Page=dpage;
			PageData[spage]=NULL;
		}
		delete	[]PageData;
		PageData=tPageData;
	}

	AllocatedPageNumb	=sPageNumb-1;

	return true;
}

bool	PageDataInOnePhase::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(int page=0;page<AllocatedPageNumb;page++){
		DataInPage *Pg=GetPageData(page);
		if(Pg!=NULL){
			if(Pg->ReallocateMasterCount(CountMaster)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	PageDataInOnePhase::ReallocateBackGroundCount(int CountBackGround)
{
	bool	Ret=true;
	for(int page=0;page<AllocatedPageNumb;page++){
		DataInPage *Pg=GetPageData(page);
		if(Pg!=NULL){
			if(Pg->ReallocateBackGroundCount(CountBackGround)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

void	PageDataInOnePhase::RemoveDispatchMaster(int pos)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		DataInPage *Pg=GetPageData(page);
		Pg->RemoveDispatchMaster(pos);
	}
}
void	PageDataInOnePhase::ResetSize(void)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		DataInPage *Pg=GetPageData(page);
		if(Pg!=NULL){
			Pg->ResetSize();
		}
	}
}
bool	PageDataInOnePhase::LoadFilterContainer(QIODevice *f)
{
	if(FilterContainer!=NULL){
		int32	Ver;
		if(::Load(f,Ver)==false){
			return false;
		}
		if(Ver>=100000){
			int32	PageNumb;
			if(::Load(f,PageNumb)==false){
				return false;
			}
			int	n=max(PageNumb,GetAllocatedPageNumb());
			int	page;
			for(page=0;page<GetAllocatedPageNumb();page++){
				delete	FilterContainer[page];
			}
			delete	[]FilterContainer;
					
			FilterContainer=new FilterInstanceContainer*[n];
			for(page=0;page<GetAllocatedPageNumb();page++){
				FilterContainer[page]=new FilterInstanceContainer(PhaseCode,page,GetLayersBase());
			}
			for(page=0;page<PageNumb && page<GetAllocatedPageNumb();page++){
				if(FilterContainer[page]->Load(f)==false){
					return false;
				}
			}
			while(page<PageNumb){
				FilterInstanceContainer *DummyContainer=new FilterInstanceContainer(PhaseCode,page,GetLayersBase());
				if(DummyContainer->Load(f)==false){
					delete	DummyContainer;
					return false;
				}
				delete	DummyContainer;
				page++;
			}
			return true;
		}
	}
	return false;
}
bool	PageDataInOnePhase::SaveFilterContainer(QIODevice *f)
{
	if(FilterContainer!=NULL){
		int32	Ver=100000;
		if(::Save(f,Ver)==false){
			return false;
		}
		int32	PageNumb=GetAllocatedPageNumb();
		if(::Save(f,PageNumb)==false){
			return false;
		}
		for(int page=0;page<PageNumb;page++){
			if(FilterContainer[page]->Save(f)==false){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool	PageDataInOnePhase::SavePhaseSource(QIODevice *f)
{
	if(::Save(f,FromSourcePhase)==false){
		return false;
	}
	return true;
}
bool	PageDataInOnePhase::LoadPhaseSource(QIODevice *f)
{
	if(::Load(f,FromSourcePhase)==false){
		return false;
	}
	return true;
}
bool    PageDataInOnePhase::SaveBrightTable(QIODevice *f)
{
	int32	PageNumb=Parent->GetPageNumb();
	if(::Save(f,PageNumb)==false){
		return false;
	}
	for(int page=0;page<PageNumb;page++){
		DataInPage *p=GetPageData(page);
		if(p->SaveBrightTable(f)==false){
			return false;
		}
	}
	return true;
}

bool    PageDataInOnePhase::LoadBrightTable(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false){
		return false;
	}
	for(int page=0;(page<Parent->GetPageNumb()) && (page<iPageNumb);page++){
		DataInPage *p=GetPageData(page);
		if(p->LoadBrightTable(f)==false){
			return false;
		}
	}
	return true;
}

bool    PageDataInOnePhase::SaveAttr(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}	
	int32	PageNumb=Parent->GetPageNumb();
	if(::Save(f,PageNumb)==false){
		return false;
	}
	for(int page=0;page<PageNumb;page++){
		DataInPage *p=GetPageData(page);
		if(p->SaveAttr(f)==false){
			return false;
		}
	}
	return true;
}

bool    PageDataInOnePhase::LoadAttr(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false){
		return false;
	}
	for(int page=0;(page<Parent->GetPageNumb()) && (page<iPageNumb);page++){
		DataInPage *p=GetPageData(page);
		if(p->LoadAttr(f)==false){
			return false;
		}
	}
	return true;
}

void	PageDataInOnePhase::CopyPageData(int DstPage ,int SrcPage 
										,bool ModeCopyAllAlgorithm ,bool ModeCopyAllFilter)
{
	if(ModeCopyAllAlgorithm==true){
		for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmInPageInOnePhase	*Ph=a->GetInstance()->GetPageDataPhase(GetPhaseCode());
			AlgorithmInPageRoot	*sPg=Ph->GetPageData(SrcPage);
			AlgorithmInPageRoot	*dPg=Ph->GetPageData(DstPage);
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			sPg->Save(&Buff);
			Buff.seek(0);
			dPg->Load(&Buff);
		}
	}
	if(ModeCopyAllFilter==true){
		FilterInstanceContainer	*sFC=GetFilterContainer(SrcPage);
		FilterInstanceContainer	*dFC=GetFilterContainer(DstPage);
		*dFC=*sFC;
		dFC->SetPage(DstPage);
	}
}


bool    PageDataInOnePhase::SaveImages(QIODevice *f)
{
	int32	PageNumb=Parent->GetPageNumb();
	if(::Save(f,PageNumb)==false){
		return false;
	}
	for(int page=0;page<PageNumb;page++){
		DataInPage *p=GetPageData(page);
		if(p->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool    PageDataInOnePhase::LoadImages(QIODevice *f)
{
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false){
		return false;
	}
	for(int page=0;(page<Parent->GetPageNumb()) && (page<iPageNumb);page++){
		DataInPage *p=GetPageData(page);
		if(p->Load(f)==false){
			return false;
		}
	}
	return true;
}

bool	PageDataInOnePhase::ExecuteFilterBeforeScan(LayersBase *Base)
{
	bool	Ret=true;

	int strategic = GetLayersBase()->GetCurrentStrategicNumber();
	StrategicListContainer SList;
	GetLayersBase()->GetParamGlobal()->GetStrategy(strategic,SList);

	QList<int> execPageList;
	for(StrategicList *item = SList.GetFirst(); item!=NULL; item=item->GetNext()){
		execPageList.append( item->Page );
	}

	for(int page=0;page<GetAllocatedPageNumb();page++){
		if(execPageList.contains(page)==false){
			continue;
		}
		FilterContainer[page]->ExecuteBeforeScan();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecuteInitialAfterEdit(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecuteInitialAfterEdit();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecuteStartByInspection(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecuteStartByInspection();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecutePreAlignment		(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecutePreAlignment();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecuteAlignment		(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecuteAlignment();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecutePreProcessing	(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecutePreProcessing();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecuteProcessing		(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecuteProcessing();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecuteProcessingRevived(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecuteProcessingRevived();
	}
	return Ret;
}
ExeResult	PageDataInOnePhase::ExecuteFilterExecutePostProcessing	(void)
{
	ExeResult	Ret;
	for(int page=0;page<GetAllocatedPageNumb();page++){
		Ret=FilterContainer[page]->ExecutePostProcessing();
	}
	return Ret;
}

bool	PageDataInOnePhase::ExecuteFilteringMaster(LayersBase *Base)
{
	ImageBuffer *IBuff[100];
	bool	Ret=true;

	int strategic = GetLayersBase()->GetCurrentStrategicNumber();
	StrategicListContainer SList;
	GetLayersBase()->GetParamGlobal()->GetStrategy(strategic,SList);

	QList<int> execPageList;
	for(StrategicList *item = SList.GetFirst(); item!=NULL; item=item->GetNext()){
		execPageList.append( item->Page );
	}

	for(int page=0;page<GetAllocatedPageNumb();page++){
		if(execPageList.contains(page)==false){
			continue;
		}
		ImageBuffer **IPointer;
		int		LayerNumb=Base->GetLayerNumb(page);
		if(LayerNumb>sizeof(IBuff)/sizeof(IBuff[0])){
			IPointer=new ImageBuffer*[LayerNumb];
		}
		else{
			IPointer=IBuff;
		}

		for(int L=0;L<LayerNumb;L++){
			IPointer[L]=&GetPageData(page)->GetLayerData(L)->GetMasterBuff();
		}
		if(FilterContainer[page]->ExecuteImage(IPointer,LayerNumb)==false){
			Ret=false;
			break;
		}
		if(IPointer!=IBuff){
			delete	[]IPointer;
		}
	}
	return Ret;
}
bool	PageDataInOnePhase::ExecuteFilteringTarget(LayersBase *Base)
{
	ImageBuffer *IBuff[100];
	bool	Ret=true;

	if(Base->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetAllocatedPageNumb();page++){
			DataInPage	*Dp=GetPageData(page);
			if(Dp->GetEnableCapture()==true){
				ImageBuffer **IPointer;
				int		LayerNumb=Dp->GetLayerNumb();
				if(LayerNumb>sizeof(IBuff)/sizeof(IBuff[0])){
					IPointer=new ImageBuffer*[LayerNumb];
				}
				else{
					IPointer=IBuff;
				}
				for(int L=0;L<LayerNumb;L++){
					IPointer[L]=&Dp->GetLayerData(L)->GetTargetBuff();
				}
				if(FilterContainer[page]->ExecuteImage(IPointer,LayerNumb)==false){
					Ret=false;
					break;
				}
				if(IPointer!=IBuff){
					delete	[]IPointer;
				}
			}
		}
	}
	else{
		StrategicListContainer SList;
		Base->GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),SList);
		int	N=0;
		int	PageType[10];
		int	PageTypeNumb=0;
		for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
			DataInPage	*Dp=GetPageData(s->Page);
			if(Dp->GetEnableCapture()==true){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>=sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}
		}
	
		//éÊÇËçûÇ›ÇëÅÇ≠Ç∑ÇÈÇΩÇﬂÇ…êÊÇ…GetImageÇæÇØÇçsÇ§
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for
		for(int camcode=0;camcode<PageTypeNumb;camcode++){
			int	BuffNumb=0;
			ImageBuffer **IPointer=IBuff;

			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				if(PageType[camcode]!=s->Page)
					continue;

				IPointer[BuffNumb]=&GetPageData(s->Page)->GetLayerData(s->Layer)->GetTargetBuff();
				BuffNumb++;
			}
			if(FilterContainer[PageType[camcode]]->ExecuteImage(IPointer,BuffNumb)==false){
				Ret=false;
				break;
			}
		}
	}

	return Ret;
}

void	PageDataInOnePhase::CopyImageMasterFrom(LayersBase *Base,PageDataInOnePhase *src)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		for(int L=0;L<Base->GetLayerNumb(page);L++){
			GetPageData(page)->GetLayerData(L)->GetMasterBuff()=src->GetPageData(page)->GetLayerData(L)->GetMasterBuff();
		}
	}
}

void	PageDataInOnePhase::CopyImageTargetFrom(LayersBase *Base,PageDataInOnePhase *src)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		for(int L=0;L<Base->GetLayerNumb(page);L++){
			GetPageData(page)->GetLayerData(L)->GetTargetBuff()=src->GetPageData(page)->GetLayerData(L)->GetTargetBuff();
		}
	}
}
void	PageDataInOnePhase::CopyTargetToTransposition(void)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		GetPageData(page)->CopyTargetToTransposition();
	}
}
void	PageDataInOnePhase::CopyTargetToCameraBuff(void)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		GetPageData(page)->CopyTargetToCameraBuff();
	}
}
bool	PageDataInOnePhase::GetMasterInfo(int32 &MachineID ,QString &MasterName ,QString &Remark)
{
	XDateTime	RegTime;
	int32		Version;
	XDateTime	LastEditTime;
	int32		CategoryID;
	int16		MasterType;
	int32		iLibFolderID;
	int32 		iThresholdLevelID	=0;
	int32 		iThresholdLevelParentID=0;

	std::shared_ptr<DatabaseLoader>	DLoader=GetLayersBase()->GetDatabaseLoader();
	if(DLoader){
		bool	ret=DLoader->G_SQLGetMasterInfo(GetLayersBase()->GetDatabase()
									,MasterCode
									,MachineID
									,RegTime
									,MasterName ,Remark
									,Version
									,LastEditTime
									,CategoryID
									,MasterType
									,iLibFolderID
									,iThresholdLevelID
									,iThresholdLevelParentID);
		return ret;
	}
	return false;
}

bool	PageDataInOnePhase::GetLotInfo(QString &LotID ,QString &LotName,QString &Remark)
{
	XDateTime LastUpdated;

	std::shared_ptr<DatabaseLoader>	DLoader=GetLayersBase()->GetDatabaseLoader();
	if(DLoader){
		bool	ret=DLoader->G_GetInspectionLot(GetLayersBase()->GetDatabase()
								,LotAutoCount,MasterCode
								,LastUpdated
								,LotID
								,LotName
								,Remark);
		return ret;
	}
	return false;
}
bool	PageDataInOnePhase::IsEdited(void)	const
{
	for(int page=0;page<AllocatedPageNumb;page++){
		if(GetPageData(page)->IsEdited()==true){
			return true;
		}
	}
	return false;
}

void	PageDataInOnePhase::SetEdited(bool edited)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		GetPageData(page)->SetEdited(edited);
	}
}

void	PageDataInOnePhase::SwapImageOutOfBuffer(int ImageDataType)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		GetPageData(page)->SwapImageOutOfBuffer(ImageDataType);
	}
}
void	PageDataInOnePhase::SwapImageInToBuffer(int ImageDataType)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		GetPageData(page)->SwapImageInToBuffer(ImageDataType);
	}
}
bool	PageDataInOnePhase::HasRegulation(void)
{
	int32	PageNumb=Parent->GetPageNumb();
	for(int page=0;page<PageNumb;page++){
		DataInPage	*dp=GetPageData(page);
		if(dp->HasRegulation()==false){
			return false;
		}
	}
	return true;
}
bool    PageDataInOnePhase::SaveRegulation(QIODevice *f)
{
	int32	PageNumb=Parent->GetPageNumb();
	if(::Save(f,PageNumb)==false)
		return false;
	for(int page=0;page<PageNumb;page++){
		DataInPage	*dp=GetPageData(page);
		int32	DotPerLine	=dp->GetDotPerLine();
		int32	MaxLines	=dp->GetMaxLines();

		if(::Save(f,DotPerLine)==false)
			return false;
		if(::Save(f,MaxLines)==false)
			return false;

		if(dp->GetRegulation().Save(f)==false){
			return false;
		}
	}
	return true;
}

bool    PageDataInOnePhase::LoadRegulation(QIODevice *f)
{
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false)
		return false;
	for(int page=0;page<iPageNumb && page<Parent->GetPageNumb();page++){
		DataInPage	*dp=GetPageData(page);
		int32	iDotPerLine	;
		int32	iMaxLines	;

		if(::Load(f,iDotPerLine)==false)
			return false;
		if(::Load(f,iMaxLines)==false)
			return false;
		if(iDotPerLine	!=dp->GetDotPerLine()
		|| iMaxLines	!=dp->GetMaxLines()){
			return false;
		}
		if(dp->GetRegulation().Load(f)==false){
			return false;
		}
	}
	return true;

}
bool    PageDataInOnePhase::SaveControlPointsForPages(QIODevice *f)
{
	int32	iPageNumb=Parent->GetPageNumb();
	if(::Save(f,iPageNumb)==false)
		return false;
	for(int page=0;page<iPageNumb;page++){
		if(GetPageData(page)->SaveControlPointsForPages(f)==false){
			return false;
		}
	}
	return true;
}
bool    PageDataInOnePhase::LoadControlPointsForPages(QIODevice *f)
{
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false)
		return false;
	for(int page=0;page<Parent->GetPageNumb() && page<iPageNumb;page++){
		if(GetPageData(page)->LoadControlPointsForPages(f)==false){
			return false;
		}
	}
	return true;
}
const	XYPointContainerWithName	&PageDataInOnePhase::GetControlPointsForPages(int page)
{
	return GetPageData(page)->GetControlPointsForPages();
}
void	PageDataInOnePhase::CopyControlPointsForPages(int SourcePage ,int DestPage)
{
	DataInPage	*Sp=GetPageData(SourcePage);
	DataInPage	*Dp=GetPageData(DestPage);
	if(Sp!=NULL && Dp!=NULL){
		Dp->ControlPointsForPages = Sp->ControlPointsForPages;
	}
}

bool	PageDataInOnePhase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	DataInPage	*Pg=GetPageData(0);
	x1=Pg->GetOutlineOffset()->x;
	y1=Pg->GetOutlineOffset()->y;
	x2=Pg->GetOutlineOffset()->x+Pg->GetDotPerLine();
	y2=Pg->GetOutlineOffset()->y+Pg->GetMaxLines();
	for(int page=1;page<Parent->GetPageNumb();page++){
		DataInPage	*Pg=GetPageData(page);
		int	ix1=Pg->GetOutlineOffset()->x;
		int	iy1=Pg->GetOutlineOffset()->y;
		int	ix2=Pg->GetOutlineOffset()->x+Pg->GetDotPerLine();
		int	iy2=Pg->GetOutlineOffset()->y+Pg->GetMaxLines();
		x1=min(x1,ix1);
		y1=min(x1,iy1);
		x2=max(x2,ix2);
		y2=max(x2,iy2);
	}
	return true;
}
DataInPage *PageDataInOnePhase::GetPageDataByPoint(int globalX ,int globalY)	const
{
	for(int page=0;page<Parent->GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int	x1,y1,x2,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if((x1<=globalX) && (globalX<=x2) && (y1<=globalY) && (globalY<=y2)){
			return P;
		}
	}
	return NULL;
}

QString	PageDataInOnePhase::GetColorString(int gx ,int gy)	const
{
	QString	ret;
	for(int page=0;page<Parent->GetPageNumb();page++){
		DataInPage	*Lp=GetPageData(page);
		for(int layer=0;layer<Lp->GetLayerNumb();layer++){
			DataInLayer	*Ly=Lp->GetLayerData(layer);
			int	px1,py1,px2,py2;
			Ly->GetArea(px1,py1,px2,py2);
			if((px1<=gx) && (gx<px2) && (py1<=gy) && (gy<py2) && (0<=gy) && (gy<Ly->GetMasterBuff().GetHeight())){
				int	c=Ly->GetMasterBuff().GetY(gy)[gx];
				ret = ret + QString::number(c) + QString(" ");
			}
		}
	}
	return(ret);
}

int		PageDataInOnePhase::GetLocalPageFromArea(FlexArea &Area ,IntList &List)	const
{
	int	ret=0;
	for(int page=0;page<Parent->GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			List.Add(page);
			ret++;
		}
	}
	return ret;
}

int		PageDataInOnePhase::GetLocalPageFromArea(DisplayImage *p ,FlexArea &Area ,IntList &List)	const
{
	int	ret=0;
	if(p->ModeShowOnlyTopTurn==false){
		for(int page=0;page<Parent->GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int x1 ,y1 ,x2 ,y2;
			P->GetArea(x1 ,y1 ,x2 ,y2);
			if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
				List.Add(page);
				ret++;
			}
		}
	}
	else{
		int	page=Parent->GetDrawturn(0)->GetPage();
			
		DataInPage *P=GetPageData(page);
		if(P!=NULL){
			int x1 ,y1 ,x2 ,y2;
			P->GetArea(x1 ,y1 ,x2 ,y2);
			if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
				List.Add(page);
				ret++;
			}
		}
	}
	return ret;
}

int		PageDataInOnePhase::GetLocalPageFromVector(VectorLineBase *v,IntList &PageList)	const
{
	int	ret=0;
	for(int page=0;page<Parent->GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(v->CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			PageList.Add(page);
			ret++;
		}
	}
	return ret;
}

int		PageDataInOnePhase::GetLocalPageFromAreaFromDrawingTop(FlexArea &Area)	const
{
	for(int page=0;page<Parent->GetPageNumb();page++){
		DataInPage *P=Parent->GetDrawturn(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			return P->GetPage();
		}
	}
	return -1;
}

int		PageDataInOnePhase::GetLocalPageFromAreaFromDrawingTop(int globalX ,int globalY)	const
{
	for(int page=0;page<Parent->GetPageNumb();page++){
		DataInPage *P=Parent->GetDrawturn(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
			return P->GetPage();
		}
	}
	return -1;
}

int		PageDataInOnePhase::GetLocalMatrixFromGlobal(int globalX ,int globalY 
													,int &localX ,int &localY)	const
{	
	if((Parent->GetEntryPoint()!=NULL) && (Parent->GetEntryPoint()->IsMasterPC()==true)){
		int	gpage=Parent->GetGlobalPage(globalX ,globalY);
		int	lPage=Parent->GetLocalPageFromGlobal(gpage);
		if((lPage<0) || (lPage>=Parent->GetPageNumb())){
			XYData	*p=Parent->GetGlobalOutlineOffset(gpage);
			if(p!=NULL){
				localX=globalX - p->x;
				localY=globalY - p->y;
				return gpage;
			}
		}
		else{
			GetPageData(lPage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
			return gpage;
		}
	}
	else{
		for(int page=0;page<Parent->GetGlobalPageNumb();page++){
			int	LocalX=globalX-Parent->GetGlobalOffset(page)->OutlineOffset.x;
			int	LocalY=globalY-Parent->GetGlobalOffset(page)->OutlineOffset.y;
			if(0<=LocalX
			&& LocalX<Parent->GetGlobalOffset(page)->GetDotPerLine()
			&& 0<=LocalY && LocalY<Parent->GetGlobalOffset(page)->GetMaxLines()){
				localX=LocalX;
				localY=LocalY;
				return page;
			}
		}
	}
	return -1;
}
void	PageDataInOnePhase::GetGlobalMatrixFromLocal(int localPage ,int localX ,int localY 
													,int &globalX ,int &globalY)	const
{
	int	gpage=Parent->GetGlobalPageFromLocal(localPage);
	XYData	*p=Parent->GetGlobalOutlineOffset(gpage);
	if(p!=NULL){
		globalX=localX+p->x;
		globalY=localY+p->y;
	}
}
bool	PageDataInOnePhase::GetRealMatrixFromGlobal(int globalX ,int globalY 
													,double &realX ,double &realY)	const
{
	int		localX ,localY;
	int	Page=GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	if(Page<0 || Parent->GetPageNumb()<=Page)
		return false;
	DataInPage	*P=GetPageData(Page);
	if(P->TransformImageToReal(localX ,localY,realX ,realY)==false){
		ParamGlobal	*PGlobal=Parent->GetParamGlobal();
		realX=((double)localX)/((double)PGlobal->ResolutionXNano)/1000000.0;
		realY=((double)localY)/((double)PGlobal->ResolutionYNano)/1000000.0;
	}
	return true;
}
int		PageDataInOnePhase::GetCountOfCompressing(void)
{
	int	MaxN=0;
	for(int page=0;page<Parent->GetGlobalPageNumb();page++){
		int	N=GetPageData(page)->GetCountOfCompressing();
		if(N>MaxN){
			MaxN=N;
		}
	}
	return MaxN;
}

bool	PageDataInOnePhase::HasRealTransform(int globalX ,int globalY)	const
{
	int		localX ,localY;
	int	Page=GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	if(Page<0 || Parent->GetPageNumb()<=Page)
		return false;
	DataInPage	*P=GetPageData(Page);
	double realX ,realY;
	if(P->TransformImageToReal(localX ,localY,realX ,realY)==false){
		return false;
	}
	return true;
}
void	PageDataInOnePhase::SwitchImageBuff(void)
{
	for(int page=0;page<Parent->GetPageNumb();page++){
		GetPageData(page)->SwitchImageBuff();
	}
}
int		PageDataInOnePhase::GetDotPerLine(int page)		const
{
	return GetPageData(page)->GetDotPerLine();
}
int		PageDataInOnePhase::GetMaxLines(int page)		const
{
	return GetPageData(page)->GetMaxLines();
}
int		PageDataInOnePhase::GetMaxDotPerLine(void)		const
{
	int	MaxDotPerLine=0;
	for(int page=0;page<Parent->GetPageNumb();page++){
		int	d=GetPageData(page)->GetDotPerLine();
		MaxDotPerLine=max(MaxDotPerLine,d);
	}
	return MaxDotPerLine;
}
int		PageDataInOnePhase::GetMaxMaxLines(void)		const
{
	int	MaxMaxLines=0;
	for(int page=0;page<Parent->GetPageNumb();page++){
		int	d=GetPageData(page)->GetMaxLines();
		MaxMaxLines=max(MaxMaxLines,d);
	}
	return MaxMaxLines;
}

bool	PageDataInOnePhase::IsCalcDone(void)	const
{
	for(int page=0;page<Parent->GetPageNumb();page++){
		if(GetPageData(page)->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}
void	PageDataInOnePhase::SlotChangedMasterImage(int PageNo,int LayerNo)
{
	emit	SignalChangedMasterImage(PhaseCode,PageNo ,LayerNo);
}
void	PageDataInOnePhase::ClearSystemResult(void)
{
	for(int page=0;page<Parent->GetPageNumb();page++){
		GetPageData(page)->ClearSystemResult();
	}
}
