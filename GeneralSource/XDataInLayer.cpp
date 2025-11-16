/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <QReadWriteLock>
#include <QCoreApplication>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include <QStandardPaths>
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
#include "XDataAlgorithmConfirm.h"
#include "XTransform.h"
#include "XDataAlgorithmThreshold.h"
#include "SelectMasterNoDialog.h"

//==================================================================================================

bool    LayersBase::InitialDatabaseLoader(QString &Msg,bool NoDatabase)
{
	if(NoDatabase==false){
		if(!GetDatabaseLoader()){
			DBLoader=std::make_shared<DatabaseLoader>(this);
			if(DatabaseInitialLoad("ServiceForDBLib")==false){
				Msg="ServiceForDBLib.dll does not exist.";
				return false;
			}
		}
	}
	return true;
}

bool    LayersBase::Initial(QString &Msg,bool NoDatabase)
{
	qRegisterMetaType<ResultInspection *>("ResultInspection *");
	qRegisterMetaType<XDateTime>("XDateTime");

	//omp_set_nested(1);
	if(InitialDatabaseLoader(Msg,NoDatabase)==false){
		return false;
	}
	InitialCreatePages();
	GetLocalParamStocker()->Load();
	OnProcessing	=new OnProcessingForm(this);

	GetLogoStockerInstance()->LoadFromLogoListFile(this);

	GUICmdContainer=new GUICmdReqBmpForTopView(this,QString("ANY"),QString("ANY"));
	GUICmdContainer=new GUICmdSendBmpForTopView(this,QString("ANY"),QString("ANY"));
	GUICmdContainer=new CmdReqSaveMasterForPage(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new CmdReqLoadMasterForPage(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new CmdAckLoadMasterForPage(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendAlgorithmItemIndependentPack	(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqAlgorithmItemIndependentPack	(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckAlgorithmItemIndependentPack(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqAlgorithmGeneralData(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendAlgorithmGeneralData(this,QString("ANY"),QString("ANY"),-1);
	
	GUICmdContainer=new GUICmdReqImageCheckByte(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckImageCheckByte(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqImageMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckImageMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSndImageMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqAlgoDataMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckAlgoDataMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSndAlgoDataMixTransfer(this,QString("ANY"),QString("ANY"),-1);

	GUICmdContainer=new ResultCmdSaveSlave				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqPartialImage			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendPartialImage			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendProcessing			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendProcessingAdd			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendClose					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendAck					(this ,"ANY","ANY",-1);
	GUICmdContainer=new CmdCameraErrorOccursMsg			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdCopyImage					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetForceChangedInspectID	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqMoveForAlignment		(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdSendParameters			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqUpdateAlgorithmOnPiece	(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckUpdateAlgorithmOnPiece	(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqEdited			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendEdited		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqCalcDone		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendCalcDone		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetEdited			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetCalcDone		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendOffset		(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqCheckSlave		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckCheckSlave		(this ,"ANY","ANY",-1);

	GUICmdContainer=new CmdReqRemoveStockedResult		(this ,"ANY","ANY",-1);
	GUICmdContainer=new ResultCmdReqLotChangedSlave		(this ,"ANY","ANY",-1);

	GUICmdContainer=new CmdWritternResult				(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqPixWithAlgorithm		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckPixWithAlgorithm		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdLoadPixWithAlgorithm		(this ,"ANY","ANY",-1);
	GUICmdContainer=new CmdReportError					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendInspectionNumber		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendMachineID				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendAllComms				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqSetCurrentPhase		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetThresholdLevel			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdCopyThresholdLevel		(this,"ANY","ANY",-1);

	PacketWritternResult=new CmdWritternResult			(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdMakeUncoveredMap			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqRewindExecuter			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetAutoRepeat				(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqEnumHistgram			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckEnumHistgram			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqHistgram				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckHistgram				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqInfoForHistgram		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckInfoForHistgram		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqInfoForHistDirect		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckInfoForHistDirect		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqAlgorithmUsageLib		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckAlgorithmUsageLib		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqHistgramLib			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckHistgramLib			(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdChangeLotInfo				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdDeliverManualExecuter		(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdSetCurrentScanPhaseNumber	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdForceStrategicNumber		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetLibFolderID			(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqChangedAlgo			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckChangedAlgo			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdDeliverChangedAlgo		(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdSendResultAnalizerData	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqResultAnalizerShowData	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckResultAnalizerShowData	(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqThresholdInstance			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckThresholdInstance			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReflectThresholdInstanceOne	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReflectThresholdInstanceAll	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdTestThresholdInstance			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdResultThresholdInstance		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdRebuildThresholdLevel			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetCurrentIntoThresholdLevel	(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdCopyShadowAlgorithm			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqUndo						(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqRedo						(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqConfirmItemList			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckConfirmItemList			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqBufferInfo					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckBufferInfo					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqClearBufferInfo			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqRemoveBufferInfo			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdChangeItemID					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUIAckChangeItemID					(this,"ANY","ANY",-1);

	DirectCmdContainer	=new SlaveCommForkStart	(this,"ANY","ANY",-1);
	DirectCmdContainer	=new SlaveCommJoin		(this,"ANY","ANY",-1);

	LearningRegisterData->InitialInSystem(GUICmdContainer);
	GUICmdContainer=PacketWritternResult;

	if(FileThreadListContainerInst!=NULL && StartThreadWriteMode==true){
		FileThreadListContainerInst->start();
	}

	return true;
}
int		LayersBase::GetCountAllMasterBuff(void)		const
{
	return AllocatedBufferInfoCount;
}
int		LayersBase::GetCountOnlyMasterBuff(void)	const
{
	int	N=0;
	for(int i=0;i<AllocatedBufferInfoCount;i++){
		if(BufferInfoListDim[i].OriginCode<=0){
			N++;
		}
	}
	return N;
}
int		LayersBase::GetCountAllBackGroundBuff(void)		const
{
	return AllocatedBufferInfoCount;
}
int		LayersBase::GetCountOnlyBackGroundBuff(void)	const
{
	int	N=0;
	for(int i=0;i<AllocatedBufferInfoCount;i++){
		if(BufferInfoListDim[i].OriginCode<=0){
			N++;
		}
	}
	return N;
}
int		LayersBase::GetCountDispatchMasterBuff(void)const
{
	int	N=0;
	for(int i=0;i<AllocatedBufferInfoCount;i++){
		if(BufferInfoListDim[i].OriginCode>0){
			N++;
		}
	}
	return N;
}
int		LayersBase::SetBufferInfo(const QString &BuffName ,int OriginCode ,int Pos)
{
	if(BufferInfoListDim==NULL){
		AllocatedBufferInfoCount=1;
		BufferInfoListDim=new BufferInfoList[AllocatedBufferInfoCount];
		Pos=0;
	}
	else{
		int	tAllocatedBufferInfoCount=AllocatedBufferInfoCount;
		if(Pos==-1){
			Pos=AllocatedBufferInfoCount;
			tAllocatedBufferInfoCount++;
		}
		else{
			if(tAllocatedBufferInfoCount<=Pos){
				tAllocatedBufferInfoCount=Pos+1;
			}
		}
		if(tAllocatedBufferInfoCount!=AllocatedBufferInfoCount){
			BufferInfoList	*tBufferInfoListDim=new BufferInfoList[tAllocatedBufferInfoCount];
			for(int i=0;i<AllocatedBufferInfoCount;i++){
				tBufferInfoListDim[i]=BufferInfoListDim[i];
			}
			AllocatedBufferInfoCount=tAllocatedBufferInfoCount;
			delete	[]BufferInfoListDim;
			BufferInfoListDim=tBufferInfoListDim;
		}
	}
	BufferInfoListDim[Pos].BufferName=BuffName;
	BufferInfoListDim[Pos].OriginCode=OriginCode;
	return Pos;
}
void	LayersBase::TF_BufferInfo(void)
{
	if(GetEntryPoint()!=NULL && GetParamComm()!=NULL){
		if(GetEntryPoint()->IsMasterPC()==true
		&& GetParamComm()->ConnectedPCNumb!=0){
			GUICmdReqBufferInfo	RCmd(this,/**/"ANY",/**/"ANY",0);
			GUICmdAckBufferInfo	ACmd(this,/**/"ANY",/**/"ANY",0);
			if(RCmd.Send(0,0,ACmd)==true){
				if(BufferInfoListDim!=NULL){
					delete	[]BufferInfoListDim;
				}
				AllocatedBufferInfoCount=ACmd.DimCount;
				BufferInfoListDim=new BufferInfoList[AllocatedBufferInfoCount];
				for(int i=0;i<AllocatedBufferInfoCount;i++){
					BufferInfoListDim[i]=ACmd.Dim[i];
				}
			}
		}
	}
}
BufferInfoList	*LayersBase::GetBufferInfo(int index)
{
	TF_BufferInfo();
	if(0<index && index<AllocatedBufferInfoCount){
		return &BufferInfoListDim[index];
	}
	if(BufferInfoListDim!=NULL){
		return &BufferInfoListDim[0];
	}
	return NULL;
}
int LayersBase::FindBufferInfo(int OriginCode)
{
	TF_BufferInfo();
	for(int i=0;i<AllocatedBufferInfoCount;i++){
		if(BufferInfoListDim[i].OriginCode==OriginCode){
			return i;
		}
	}
	return -1;
}
int		LayersBase::GetCountBufferInfo(void)
{
	TF_BufferInfo();
	return AllocatedBufferInfoCount;
}

int		LayersBase::ShowSelectMasterNoOriginCodeDialog(int OriginCode)
{
	SelectMasterNoDialog	D(this,OriginCode);
	if(D.exec()==true){
		return D.MasterNoOriginCode;
	}
	return -1;
}
void	LayersBase::ClearBufferInfo(void)
{
	TF_ClearBufferInfo();
	int	tAllocatedBufferInfoCount=0;
	for(int i=0;i<AllocatedBufferInfoCount;i++){
		if(BufferInfoListDim[i].OriginCode<=0){
			tAllocatedBufferInfoCount++;
		}
	}
	if(tAllocatedBufferInfoCount!=AllocatedBufferInfoCount){
		BufferInfoList	*tBufferInfoListDim=new BufferInfoList[tAllocatedBufferInfoCount];
		int	k=0;
		for(int i=0;i<AllocatedBufferInfoCount;i++){
			if(BufferInfoListDim[i].OriginCode<=0){
				tBufferInfoListDim[k]=BufferInfoListDim[i];
				k++;
			}
		}
		delete	[]BufferInfoListDim;
		AllocatedBufferInfoCount=tAllocatedBufferInfoCount;
		BufferInfoListDim=tBufferInfoListDim;
	}
}
void	LayersBase::RemoveBufferInfo(int OriginCode)
{
	int	Pos=FindBufferInfo(OriginCode);
	if(Pos<0){
		TF_RemoveBufferInfo(OriginCode);
		return;
	}
	for(int phase=0;phase<AllocatedPhaseNumb;phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->RemoveDispatchMaster(Pos);
	}
	TF_RemoveBufferInfo(OriginCode);
	int	tAllocatedBufferInfoCount=0;
	for(int i=0;i<AllocatedBufferInfoCount;i++){
		if(BufferInfoListDim[i].OriginCode!=OriginCode){
			tAllocatedBufferInfoCount++;
		}
	}
	if(tAllocatedBufferInfoCount!=AllocatedBufferInfoCount){
		BufferInfoList	*tBufferInfoListDim=new BufferInfoList[tAllocatedBufferInfoCount];
		int	k=0;
		for(int i=0;i<AllocatedBufferInfoCount;i++){
			if(BufferInfoListDim[i].OriginCode!=OriginCode){
				tBufferInfoListDim[k]=BufferInfoListDim[i];
				k++;
			}
		}
		delete	[]BufferInfoListDim;
		AllocatedBufferInfoCount=tAllocatedBufferInfoCount;
		BufferInfoListDim=tBufferInfoListDim;
	}
}
void	LayersBase::TF_ClearBufferInfo(void)
{
	if(GetEntryPoint()!=NULL && GetParamComm()!=NULL){
		if(GetEntryPoint()->IsMasterPC()==true
		&& GetParamComm()->ConnectedPCNumb!=0){
			GUICmdReqClearBufferInfo	RCmd(this,/**/"ANY",/**/"ANY",0);
			RCmd.Send(NULL,0,0);
		}
	}
}
void	LayersBase::TF_RemoveBufferInfo(int OriginCode)
{
	if(GetEntryPoint()!=NULL && GetParamComm()!=NULL){
		if(GetEntryPoint()->IsMasterPC()==true
		&& GetParamComm()->ConnectedPCNumb!=0){
			GUICmdReqRemoveBufferInfo	RCmd(this,/**/"ANY",/**/"ANY",0);
			RCmd.OriginCode=OriginCode;
			RCmd.Send(NULL,0,0);
		}
	}
}

void	LayersBase::InitialCreatePages(bool EnabledImageMemoryAllocation)
{
	if(GetParamGlobal()->AllocateMasterBuff==true){
		for(int i=0;i<GetParamGlobal()->AllocatedCountMasterBuff;i++){
			QString	s=QString(/**/"MasterBuff")+QString::number(i);
			SetBufferInfo(s ,-1);
		}
	}

	//QMessageBox::warning(NULL,"","1");
	if(PageDataPhase!=NULL){
		for(int i=0;i<AllocatedPhaseNumb;i++){
			delete	PageDataPhase[i];
		}
		delete	[]PageDataPhase;
	}
	//QMessageBox::warning(NULL,"",QString("NN:")
	//							+QString::number(GetPhaseNumb())
	//							+QString(",")
	//							+QString::number(GetPageNumb())
	//							+QString(",")
	//							+QString::number(GetLayerNumb())
	//							);
	AllocatedPhaseNumb=GetPhaseNumb();
	if(AllocatedPhaseNumb==0)
		AllocatedPhaseNumb=1;
	PageDataPhase=new PageDataInOnePhase*[AllocatedPhaseNumb];
	for(int i=0;i<AllocatedPhaseNumb;i++){
		PageDataPhase[i]=new PageDataInOnePhase(i,this);
		PageDataPhase[i]->InitialCreate(this,EnabledImageMemoryAllocation);

		connect(PageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
	}

	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}
	PageData=PageDataPhase[0];
	DrawPageIndex	=new DataInPage*[GetPageNumb()];
	//AllocatedPageNumb	=GetPageNumb();
	for(int i=0;i<GetPageNumb();i++){
		DrawPageIndex[i]=PageData->GetPageData(i);
	}

	if(GetOutlineOffsetWriter()!=NULL){
		GetOutlineOffsetWriter()->Initial();
	}
	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;

	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		GlobalPageNumb=GetPageNumb();
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
		SendingData=new bool[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			SendingData[page]=false;
		}
		if(GetIntegrationBasePointer()!=NULL){
			int	SlaveNumb=GetIntegrationBasePointer()->GetIntegrationSlaveCount();
			if(SlaveNumb==0)
				SlaveNumb=1;
			IntegrationSendingData=new bool[SlaveNumb];
			for(int n=0;n<SlaveNumb;n++){
				IntegrationSendingData[n]=false;
			}
		}
	}
	LoadControlPointsForPagesDefault();
}
int		LayersBase::GetLayerNumb(int page)	const
{	
	if(0<=page && page<GetPageNumb()){
		DataInPage *Pg=GetPageData(page);
		if(Pg!=NULL){
			return Pg->GetLayerNumb();
		}
	}
	return ParamGlobalData->LayerNumb;
}

int		LayersBase::GetMaxLayerNumb(void)	const
{
	int		MaxLayerNumb=0;
	for(int phase=0;phase!=GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		MaxLayerNumb=max(MaxLayerNumb,Ph->GetMaxLayerNumb());
	}
	return MaxLayerNumb;
}

int		LayersBase::GetDotPerLine(int page)	const
{	
	if(0<=page && page<GetPageNumb()){
		DataInPage *Pg=GetPageData(page);
		if(Pg!=NULL){
			return Pg->GetDotPerLine();
		}
	}
	return ParamGlobalData->DotPerLine;
}
int		LayersBase::GetMaxLines(int page)	const
{	
	if(0<=page && page<GetPageNumb()){
		DataInPage *Pg=GetPageData(page);
		if(Pg!=NULL){
			return Pg->GetMaxLines();
		}
	}
	return ParamGlobalData->MaxLines;
}
	
int		LayersBase::GetMaxDotPerLine(void)		const
{
	int	MaxDotPerLine=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		MaxDotPerLine=max(MaxDotPerLine,P->GetMaxDotPerLine());
	}
	return MaxDotPerLine;
}

int		LayersBase::GetMaxMaxLines(void)		const
{
	int	MaxMaxLines=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		MaxMaxLines=max(MaxMaxLines,P->GetMaxMaxLines());
	}
	return MaxMaxLines;
}
void	LayersBase::LockTarget(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->LockTarget();
	}
}
void	LayersBase::UnlockTarget(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->UnlockTarget();
	}
}
void	LayersBase::LockMaster(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->LockMaster();
	}
}
void	LayersBase::UnlockMaster(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->UnlockMaster();
	}
}

bool		LayersBase::IsValid(int page ,int layer)	const
{
	return GetParamGlobal()->IsValid(page ,layer);
}

const QString	LayersBase::GetUserPath(void)	const
{
	QStringList	L=UserPath.split('/');
	if(L.count()>=2){
		if(UserPath.isEmpty()==false){
			return UserPath;
		}
	}
	if(L.count()==1 && L[0].isEmpty()==false){
		QString s=QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)
				  +::GetSeparator()+UserPath;
		if(s.isEmpty()==false){
			QDir	d;
			if(d.exists(s)==true){
				return s;
			}
		}
	}
	else{
		QString s=QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)
				  +::GetSeparator()+QString(/**/"Regulus64");
		if(s.isEmpty()==false){
			QDir	d;
			if(d.exists(s)==true){
				return s;
			}
		}
		QString s2=QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
		if(s2.isEmpty()==false){
			QDir	d;
			if(d.exists(s2)==true){
				return s2;
			}
		}
	}
	return CurrentPath;
}

const QString	LayersBase::GetUserPath(const QString &_UserPath)
{
	QStringList	L=_UserPath.split('/');
	if(L.count()>=2){
		if(_UserPath.isEmpty()==false){
			return _UserPath;
		}
	}
	if(L.count()==1 && L[0].isEmpty()==false){
		QString s=QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)
				  +::GetSeparator()+_UserPath;
		if(s.isEmpty()==false){
			QDir	d;
			if(d.exists(s)==true){
				return s;
			}
		}
	}
	else{
		QString s=QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)
				  +::GetSeparator()+QString(/**/"Regulus64");
		if(s.isEmpty()==false){
			QDir	d;
			if(d.exists(s)==true){
				return s;
			}
		}
		QString s2=QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
		if(s2.isEmpty()==false){
			QDir	d;
			if(d.exists(s2)==true){
				return s2;
			}
		}
	}
	return QCoreApplication::applicationFilePath();
}

void	LayersBase::ResetSize(void)
{
	for(int i=0;i<AllocatedPhaseNumb;i++){
		PageDataPhase[i]->ResetSize();
	}
}
bool	LayersBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	GetLayersBase()->SetPossibleToUpdateDisplay(false);

	if(GetParamGlobal()->MaximumDotPerLine>0 && GetParamGlobal()->MaximumDotPerLine<NewDotPerLine){
		NewDotPerLine=GetParamGlobal()->MaximumDotPerLine;
	}
	if(GetParamGlobal()->MaximumMaxLines>0 && GetParamGlobal()->MaximumMaxLines<NewMaxLines){
		NewMaxLines=GetParamGlobal()->MaximumMaxLines;
	}
	if(GetParamGlobal()->DotPerLine!=NewDotPerLine || GetParamGlobal()->MaxLines !=NewMaxLines){
		LockWChangingDataStructure();
		SetOnChanging(true);
		//GSleep(1000);
		GetParamGlobal()->DotPerLine	=NewDotPerLine;
		GetParamGlobal()->MaxLines		=NewMaxLines;
		for(int i=0;i<AllocatedPhaseNumb;i++){
			if(PageDataPhase[i]!=NULL){
				PageDataPhase[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
			}
		}
		for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
			a->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
		}
		EntryPointBase	*EBase=GetEntryPoint();
		if(EBase!=NULL && GetShadowLevel()==0){
			ExecuteInspectBase	*E=EBase->GetExecuteInspect();
			if(E!=NULL){
				SetOnChanging(false);
				//UnlockChangingDataStructure();
				if(E->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
					UnlockChangingDataStructure();
					SetOnChanging(false);
					GetLayersBase()->SetPossibleToUpdateDisplay(true);
					return false;
				}
				//UnlockChangingDataStructure();
				//emit	SignalChangedXY();
				//return true;
			}
		}
		LoadFilterDef();
		SetOnChanging(false);
		UnlockChangingDataStructure();

		GUIInstancePack *cg=GetGUIInstancePack();
		if(cg!=NULL){
			for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
				GUIFormBase	*f=g->GetForm();
				f->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
			}
		}

		ReallocXYPixelsShadow(NewDotPerLine ,NewMaxLines);

		if(GetLightBase()!=NULL){
			GetLightBase()->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
		}

		emit	SignalChangedXY();
		GetLayersBase()->SetPossibleToUpdateDisplay(true);
	}
	else{
		GetLayersBase()->SetPossibleToUpdateDisplay(true);
	}
	return true;
}
bool	LayersBase::ReallocXYPixelsPage(int Phase ,int Page ,int NewDotPerLine ,int NewMaxLines)
{
	LockWChangingDataStructure();
	SetOnChanging(true);

	if(GetParamGlobal()->MaximumDotPerLine>0 && GetParamGlobal()->MaximumDotPerLine<NewDotPerLine){
		NewDotPerLine=GetParamGlobal()->MaximumDotPerLine;
	}
	if(GetParamGlobal()->MaximumMaxLines>0 && GetParamGlobal()->MaximumMaxLines<NewMaxLines){
		NewMaxLines=GetParamGlobal()->MaximumMaxLines;
	}
	if(0<=Phase && Phase<GetPhaseNumb() && PageDataPhase[Phase]!=NULL){
		PageDataPhase[Phase]->ReallocXYPixelsPage(Page,NewDotPerLine ,NewMaxLines);
	}
	//for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
	//	a->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
	//}
	GetParamGlobal()->DotPerLine=NewDotPerLine;
	GetParamGlobal()->MaxLines	=NewMaxLines;
	if(Page<GetParamGlobal()->CountOfPageLocal && GetParamGlobal()->PageLocalData!=NULL){
		if(GetParamGlobal()->PageLocalData[Page].UseEachPage==true){
			GetParamGlobal()->PageLocalData[Page].DotPerLine=NewDotPerLine;
			GetParamGlobal()->PageLocalData[Page].MaxLines	=NewMaxLines;
		}
	}

	EntryPointBase	*EBase=GetEntryPoint();
	if(EBase!=NULL && GetShadowLevel()==0){
		ExecuteInspectBase	*E=EBase->GetExecuteInspect();
		if(E!=NULL){
			SetOnChanging(false);
			//UnlockChangingDataStructure();
			if(E->ReallocXYPixelsPage(Phase,Page,NewDotPerLine ,NewMaxLines)==false){
				UnlockChangingDataStructure();
				return false;
			}
			UnlockChangingDataStructure();
			emit	SignalChangedXY();
			return true;
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	//GUIInstancePack *cg=GetGUIInstancePack();
	//if(cg!=NULL){
	//	for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
	//		GUIFormBase	*f=g->GetForm();
	//		f->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
	//	}
	//}

	emit	SignalChangedXY();
	
	return true;
}
bool	LayersBase::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(newPhaseNumb<=0){
		newPhaseNumb=GetParamGlobal()->GetPhaseNumb();
	}
	if(newPageNumb<=0){
		newPageNumb=GetParamGlobal()->GetPageNumb();
	}
	if(newLayerNumb<=0){
		newLayerNumb=GetParamGlobal()->GetLayerNumb(0);
	}
	if(GetParamGlobal()->PhaseNumb	==newPhaseNumb
	&& GetParamGlobal()->PageNumb	==newPageNumb
	&& GetParamGlobal()->LayerNumb	==newLayerNumb){
		emit	SignalChangedPhasePageLayer();
		return true;
	}

	LockWChangingDataStructure();

	SetOnChanging(true);
	//GSleep(1000);

	GetParamGlobal()->PhaseNumb	=newPhaseNumb;
	GetParamGlobal()->PageNumb	=newPageNumb;
	GetParamGlobal()->LayerNumb	=newLayerNumb;
	if(PageDataPhase!=NULL){
		if(newPhaseNumb>AllocatedPhaseNumb){
			PageDataInOnePhase	**iPageDataPhase=new PageDataInOnePhase*[newPhaseNumb];
			for(int i=0;i<AllocatedPhaseNumb;i++){
				iPageDataPhase[i]=PageDataPhase[i];
				//PageDataPhase[i]=NULL;
				if(iPageDataPhase[i]==NULL){
					iPageDataPhase[i]=new PageDataInOnePhase(i,this);
				}
				iPageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
			}
			PageDataInOnePhase	**tmpPhaseDim=PageDataPhase;
			PageDataPhase=iPageDataPhase;
			for(int i=AllocatedPhaseNumb;i<newPhaseNumb;i++){
				iPageDataPhase[i]=new PageDataInOnePhase(i,this);
				iPageDataPhase[i]->InitialCreate(this,true);
				connect(iPageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
			}
			delete	[]tmpPhaseDim;
		}
		else if(newPhaseNumb<AllocatedPhaseNumb){
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new PageDataInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate(this,true);
					connect(PageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
			for(int i=newPhaseNumb;i<AllocatedPhaseNumb;i++){
				delete	PageDataPhase[i];
				PageDataPhase[i]=NULL;
			}
		}
		else{
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new PageDataInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate(this,true);
					connect(PageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
		}
		AllocatedPhaseNumb=newPhaseNumb;
	}
	else{
		InitialCreatePages(true);
	}
	if(CurrentPhase>=AllocatedPhaseNumb)
		CurrentPhase=AllocatedPhaseNumb-1;
	PageData=PageDataPhase[CurrentPhase];

	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}
	DrawPageIndex	=new DataInPage*[newPageNumb];
	//AllocatedPageNumb	=newPageNumb;
	for(int i=0;i<newPageNumb;i++){
		DrawPageIndex[i]=PageData->GetPageData(i);
	}
	if(GetOutlineOffsetWriter()!=NULL){
		GetOutlineOffsetWriter()->Initial();
	}
	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;

	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		GlobalPageNumb=newPageNumb;
		if(GlobalOffset!=NULL){
			delete	[]GlobalOffset;
		}
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
		if(SendingData!=NULL){
			delete	[]SendingData;
		}
		SendingData=new bool[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			SendingData[page]=false;
		}
	}
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL && GetShadowLevel()==0){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			f->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
		}
	}
	if(GetLightBase()!=NULL){
		GetLightBase()->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	ReallocateShadow(newPhaseNumb ,newPageNumb ,newLayerNumb);

	emit	SignalChangedPhasePageLayer();
	return true;
}

bool	LayersBase::Reallocate(int newPhaseNumb)
{
	if(newPhaseNumb<=0){
		newPhaseNumb=GetParamGlobal()->GetPhaseNumb();
	}

	if(GetParamGlobal()->PhaseNumb	==newPhaseNumb){
		emit	SignalChangedPhasePageLayer();
		return true;
	}

	LockWChangingDataStructure();

	SetOnChanging(true);
	//GSleep(1000);

	GetParamGlobal()->PhaseNumb	=newPhaseNumb;
	if(PageDataPhase!=NULL){
		if(newPhaseNumb>AllocatedPhaseNumb){
			PageDataInOnePhase	**iPageDataPhase=new PageDataInOnePhase*[newPhaseNumb];
			for(int i=0;i<AllocatedPhaseNumb;i++){
				iPageDataPhase[i]=PageDataPhase[i];
				//PageDataPhase[i]=NULL;
				if(iPageDataPhase[i]==NULL){
					iPageDataPhase[i]=new PageDataInOnePhase(i,this);
				}
				iPageDataPhase[i]->Reallocate(GetPageNumb());
			}
			PageDataInOnePhase	**tmpPhaseDim=PageDataPhase;
			PageDataPhase=iPageDataPhase;
			for(int i=AllocatedPhaseNumb;i<newPhaseNumb;i++){
				iPageDataPhase[i]=new PageDataInOnePhase(i,this);
				iPageDataPhase[i]->InitialCreate(this,true);
				connect(iPageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
			}
			delete	[]tmpPhaseDim;
		}
		else if(newPhaseNumb<AllocatedPhaseNumb){
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new PageDataInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate(this,true);
					connect(PageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
				}
				else{
					PageDataPhase[i]->Reallocate(GetPageNumb());
				}
			}
			for(int i=newPhaseNumb;i<AllocatedPhaseNumb;i++){
				delete	PageDataPhase[i];
				PageDataPhase[i]=NULL;
			}
		}
		else{
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new PageDataInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate(this,true);
					connect(PageDataPhase[i],SIGNAL(SignalChangedMasterImage(int ,int ,int )),this,SLOT(SlotChangedMasterImage(int ,int ,int )));
				}
				else{
					PageDataPhase[i]->Reallocate(GetPageNumb());
				}
			}
		}
		AllocatedPhaseNumb=newPhaseNumb;
	}
	else{
		InitialCreatePages(true);
	}
	if(CurrentPhase>=AllocatedPhaseNumb)
		CurrentPhase=AllocatedPhaseNumb-1;
	PageData=PageDataPhase[CurrentPhase];

	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->Reallocate(newPhaseNumb);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->Reallocate(newPhaseNumb);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL && GetShadowLevel()==0){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->Reallocate(newPhaseNumb);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			f->Reallocate(newPhaseNumb);
		}
	}
	if(GetLightBase()!=NULL){
		GetLightBase()->Reallocate(newPhaseNumb);
	}

	ReallocateShadow(newPhaseNumb);


	emit	SignalChangedPhasePageLayer();
	return true;
}
bool	LayersBase::InsertPage(int IndexPage)	//Create page before Indexed page
{
	LockWChangingDataStructure();

	SetOnChanging(true);
	//GSleep(1000);

	int	sPageNumb=GetParamGlobal()->PageNumb;
	GetParamGlobal()->PageNumb++;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->InsertPage(IndexPage);
	}


	DataInPage	**tDrawPageIndex	=new DataInPage*[sPageNumb+1];
	int dpage=0;
	int spage=0;
	for(;spage<sPageNumb && spage<IndexPage;spage++,dpage++){
		tDrawPageIndex[dpage]=DrawPageIndex[spage];
		DrawPageIndex[spage]=NULL;
	}
	tDrawPageIndex[dpage]=PageData->GetPageData(dpage);
	dpage++;
	for(;spage<sPageNumb && dpage<sPageNumb+1;dpage++,spage++){
		tDrawPageIndex[dpage]=DrawPageIndex[spage];
		DrawPageIndex[spage]=NULL;
	}
	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}
	DrawPageIndex=tDrawPageIndex;

	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		GlobalPageNumb=sPageNumb+1;
		if(GlobalOffset!=NULL){
			delete	[]GlobalOffset;
		}
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
		if(SendingData!=NULL){
			delete	[]SendingData;
		}
		SendingData=new bool[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			SendingData[page]=false;
		}
	}


	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->InsertPage(IndexPage);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->InsertPage(IndexPage);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL && GetShadowLevel()==0){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->InsertPage(IndexPage);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			f->InsertPage(IndexPage);
		}
	}
	if(GetLightBase()!=NULL){
		GetLightBase()->InsertPage(IndexPage);
	}
	InsertPageShadow(IndexPage);

	emit	SignalChangedPhasePageLayer();
	return true;
}
bool	LayersBase::RemovePage(int IndexPage)
{
	LockWChangingDataStructure();

	SetOnChanging(true);
	//GSleep(1000);

	int	sPageNumb=GetParamGlobal()->PageNumb;
	GetParamGlobal()->PageNumb--;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->RemovePage(IndexPage);
	}

	DataInPage	**tDrawPageIndex	=new DataInPage*[sPageNumb-1];
	int dpage=0;
	int spage=0;
	for(;spage<sPageNumb && spage<IndexPage;spage++,dpage++){
		tDrawPageIndex[dpage]=DrawPageIndex[spage];
		DrawPageIndex[spage]=NULL;
	}
	spage++;
	for(;spage<sPageNumb && dpage<sPageNumb-1;dpage++,spage++){
		tDrawPageIndex[dpage]=DrawPageIndex[spage];
		DrawPageIndex[spage]=NULL;
	}
	delete	[]DrawPageIndex;
	DrawPageIndex=tDrawPageIndex;

	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		GlobalPageNumb=sPageNumb-1;
		if(GlobalOffset!=NULL){
			delete	[]GlobalOffset;
		}
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
		if(SendingData!=NULL){
			delete	[]SendingData;
		}
		SendingData=new bool[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			SendingData[page]=false;
		}
	}

	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->RemovePage(IndexPage);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->RemovePage(IndexPage);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL && GetShadowLevel()==0){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->RemovePage(IndexPage);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			f->RemovePage(IndexPage);
		}
	}
	if(GetLightBase()!=NULL){
		GetLightBase()->RemovePage(IndexPage);
	}
	RemovePageShadow(IndexPage);

	emit	SignalChangedPhasePageLayer();
	return true;
}

bool	LayersBase::RemovePhase(int RemovedPhaseCode)
{
	if(GetParamGlobal()->PhaseNumb<=1){
		return false;
	}
	if(RemovedPhaseCode<0 || GetParamGlobal()->PhaseNumb<=RemovedPhaseCode){
		return false;
	}

	LockWChangingDataStructure();

	SetOnChanging(true);
	//GSleep(1000);

	GetParamGlobal()->PhaseNumb	=GetParamGlobal()->PhaseNumb-1;
	if(PageDataPhase!=NULL){
		delete	PageDataPhase[RemovedPhaseCode];
		int	MaxAllocatedPhaseNumb=max(AllocatedPhaseNumb,GetParamGlobal()->PhaseNumb);
		for(int phase=RemovedPhaseCode+1;phase<MaxAllocatedPhaseNumb;phase++){
			PageDataPhase[phase-1]=PageDataPhase[phase];
		}
		for(int phase=GetParamGlobal()->PhaseNumb;phase<AllocatedPhaseNumb;phase++){
			PageDataPhase[phase]=0;
		}
	}
	if(CurrentPhase>=GetParamGlobal()->PhaseNumb){
		CurrentPhase=GetParamGlobal()->PhaseNumb-1;
	}
	PageData=PageDataPhase[CurrentPhase];
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->SetPhaseCode(phase);
	}

	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->RemovePhase(RemovedPhaseCode);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->RemovePhase(RemovedPhaseCode);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL && GetShadowLevel()==0){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->RemovePhase(RemovedPhaseCode);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	return true;
}

bool	LayersBase::ReallocateMasterCount(int CountMaster)
{
	if(CountMaster<0){
		return false;
	}

	LockWChangingDataStructure();
	SetOnChanging(true);
	//GSleep(1000);

	bool	Ret=true;
	if(PageDataPhase!=NULL){
		for(int i=0;i<AllocatedPhaseNumb;i++){
			if(GetPageDataPhase(i)->ReallocateMasterCount(CountMaster)==false){
				Ret=false;
			}
		}
	}
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			if(a->GetInstance()->ReallocateMasterCount(CountMaster)==false){
				Ret=false;
			}
		}
	}


	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			if(f->ReallocateMasterCount(CountMaster)==false){
				Ret=false;
			}
		}
	}
	if(ReallocateMasterCountShadow(CountMaster)==false){
		Ret=false;
	}
	
	GetParamGlobal()->AllocatedCountMasterBuff	=CountMaster;

	SetOnChanging(false);
	UnlockChangingDataStructure();

	emit	SignalChangedPhasePageLayer();
	return Ret;
}

bool	LayersBase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	x1=99999999;
	y1=99999999;
	x2=-99999999;
	y2=-99999999;
	bool	Ret=false;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		int		tx1 ,ty1 ,tx2 ,ty2;
		if(Ph->GetXY(tx1 ,ty1 ,tx2 ,ty2)==true){
			x1=min(x1,tx1);
			y1=min(y1,ty1);
			x2=max(x2,tx2);
			y2=max(y2,ty2);
			Ret=true;
		}
	}
	return Ret;
}

void	LayersBase::MakeCapturedAllList(ListPhasePageLayerPack &CapturedList)
{
	if(GetParamGlobal()->ModePhaseExecuteCaptured==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					CapturedList.Add(phase,page,layer);
				}
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteCaptured==-1){
		IntList PhaseCodes;
		GetCurrentPhaseFromScanPhase(PhaseCodes);
		for(IntClass *c=PhaseCodes.GetFirst();c!=NULL;c=c->GetNext()){
			int	Phase=c->GetValue();
			for(int page=0;page<GetPageNumb();page++){
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					CapturedList.Add(Phase,page,layer);
				}
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteCaptured
		&& GetParamGlobal()->ModePhaseExecuteCaptured<GetPhaseNumb()){
		int	Phase=GetParamGlobal()->ModePhaseExecuteCaptured;
		for(int page=0;page<GetPageNumb();page++){
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				CapturedList.Add(Phase,page,layer);
			}
		}
	}
}

void	LayersBase::SetGlobalOffset(int	_GlobalPageNumb ,DataInPage::ConstructionData *_GlobalOffset)
{
	GlobalPageNumb=_GlobalPageNumb;
	if(GlobalOffset!=NULL){
		delete	[]GlobalOffset;
	}
	GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
	for(int page=0;page<GlobalPageNumb;page++){
		GlobalOffset[page].OutlineOffset=(_GlobalOffset+page)->OutlineOffset;
	}
}
DataInPage::ConstructionData *LayersBase::GetGlobalOffset(int GlobalPage)	const
{
	if(0<=GlobalPage && GlobalPage<GlobalPageNumb){
		return &GlobalOffset[GlobalPage];
	}
	return NULL;
}

void	LayersBase::ChangeGlobalOffset(int _GlobalPage ,XYData &Dest)
{
	if(0<=_GlobalPage && _GlobalPage<GlobalPageNumb){
		GlobalOffset[_GlobalPage].OutlineOffset=Dest;
	}
}

LotInformation			*LayersBase::GetLot(int n)	const
{	
	return LotInfo->GetLot(n);
}

void    LayersBase::InitialAlgorithm(RootNameListContainer &List ,const QStringList &AlgorithmPath,bool LoadAll)
{
	GetGeneralStocker()->OpenDLL();
	GetGeneralStocker()->Initial();

	GetAlgoDLLContPointer()->SearchAddDLL(List,this,AlgorithmPath,LoadAll);
	GetLogicDLLBase()->AddDLLs(*GetAlgoDLLContPointer(),this);

	QStringList	ErrorMsg;
	if(GetLogicDLLBase()->CheckDuplicatedAlgorithm(ErrorMsg)==true){
		QString	Msg;
		for(int i=0;i<ErrorMsg.count();i++){
			Msg +=ErrorMsg[i];
		}
		QMessageBox::critical(0,"Duplicated algorithm dll",Msg);
	}
	CreateAlgorithmPointer();

	if(GetInstalledLibType()!=NULL){
		 for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;){
			 LibraryTypeList	*NextL=L->GetNext();
			 if(GetLogicDLLBase()->SearchByLibType(L->GetLibType())==NULL){
				GetLayersBase()->GetInstalledLibType()->RemoveList(L);
			 }
			 L=NextL;
		 }
	}
}

void    LayersBase::CopyAlgorithm(const LayersBase *parent ,RootNameListContainer &List ,const char *AlgorithmPath,bool LoadAll)
{
	GetGeneralStocker()->OpenDLL();
	GetGeneralStocker()->Initial();

	GetAlgoDLLContPointer()->CopyAddDLL((const AlgorithmDLLContainer *)(parent->GetAlgoDLLContPointer()));
	GetLogicDLLBase()->AddDLLs(*GetAlgoDLLContPointer(),this);

	QStringList	ErrorMsg;
	if(GetLogicDLLBase()->CheckDuplicatedAlgorithm(ErrorMsg)==true){
		QString	Msg;
		for(int i=0;i<ErrorMsg.count();i++){
			Msg +=ErrorMsg[i];
		}
		QMessageBox::critical(0,"Duplicated algorithm dll",Msg);
	}
	CreateAlgorithmPointer();
}
void	LayersBase::InitializeToStart(void)
{
	CurrentCalcPoint	=0;
	CurrentDrawPoint	=0;
	LastCurrentCalcPoint=0;

	_CurrentInspectID	=0;
	_LastInspectID		=0;
	CurrentStrategicNumber			=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	CurrentStrategicQueue.RemoveAll();
	CurrentScanPhaseNumber			=0;
	InspectionNumber				=0;
	LatchedInspectionNumber			=0;
}
void    LayersBase::InitialAfterParamLoaded(void)
{
	GetLogicDLLBase()->InitialAfterParamLoaded();
	GetGeneralStocker()->InitialAfterParamLoaded();
}
void    LayersBase::ReallocAlgorithm(void)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->ReallocAlgorithmBase(this);
	}
}

bool    LayersBase::InitialLight(bool OutputMode)
{
	if(GetLightBase()==NULL){
		LightBase=new LightClassPack(this);
		if(GetLightBase()->Initial(ErrorOccurs,OutputMode)==false){
			delete	LightBase;
			LightBase=NULL;
			return false;
		}
		if(QFile::exists(GetParamGlobal()->LightSettingFileName)==true){
			QFile	File(GetParamGlobal()->LightSettingFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(GetLightBase()->Load(&File)==true){
					GetLightBase()->SetPattern(0);
					if(GetParamGlobal()->InitialLightON==true){
						GetLightBase()->LightOn();
					}
					else{
						GetLightBase()->LightOff();
					}
					return true;
				}
			}
		}
	}
	else{
		return true;
	}
	return false;
}

bool    LayersBase::InitialFilterBank(void)
{
	if(GetFilterBank()!=NULL){
		GetFilterBank()->SearchAddDLL(ErrorOccurs);
	}
	if(ErrorOccurs!=Error_Nothing){
		return false;
	}
	return true;
}
bool    LayersBase::InitialResultAnalizer(void)
{
	if(GetResultAnalizerDLLContainer()!=NULL){
		if(GetResultAnalizerDLLContainer()->OpenDLL()==false){
			return false;
		}
	}
	if(GetResultAnalizerItemBaseContainer()!=NULL){
		GetResultAnalizerItemBaseContainer()->LoadDefault();
	}
	return true;
}
bool    LayersBase::InitialPrinter(void)
{
	if(GetPrinterClassPackData()==NULL){
		PrinterClassPackData=new PrinterClassPack(this);
		if(GetPrinterClassPackData()->Initial(ErrorOccurs)==false){
			delete	PrinterClassPackData;
			PrinterClassPackData=NULL;
			return false;
		}
		if(QFile::exists(GetParamGlobal()->LightSettingFileName)==true){
			QFile	File(GetParamGlobal()->LightSettingFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(GetPrinterClassPackData()->Load(&File)==true){
					return true;
				}
			}
		}
		return true;
	}
	else{
		return true;
	}
}
bool    LayersBase::InitialSyncGUI(void)
{
	if(SyncGUIData!=NULL && GetParamGlobal()->SyncGUIFileName.isEmpty()==false){
		QString	Path=GetUserPath();
		QDir::setCurrent(Path);
		QFile	F(GetParamGlobal()->SyncGUIFileName);
		if(F.open(QIODevice::ReadOnly)==true){
			if(SyncGUIData->Load(&F)==false){
				return false;
			}
			SyncGUIData->Start();
			return true;
		}
		return false;
	}
	else{
		return true;
	}
	return false;
}

void    LayersBase::CreateAlgorithmPointer(void)
{
	PreAlignmentBase	.RemoveAll();
	AlignmentBase		.RemoveAll();
	PreProcessingBase	.RemoveAll();
	ProcessingBase		.RemoveAll();
	PostProcessingBase	.RemoveAll();
	if(GetLogicDLLBase()!=NULL){
		for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypePreAlignment){
				PreAlignmentBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypeAlignment){
				AlignmentBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypePreProcessing){
				PreProcessingBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypeProcessing){
				ProcessingBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypePostProcessing){
				PostProcessingBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
		}
	}
}
void    LayersBase::InitialAlgorithmBlob(void)
{
	if(IsDatabaseOk()==true){
		GetLogicDLLBase()->CheckAndCreateBlobInMasterPageTable(GetDatabase());
	}
}
void    LayersBase::InitialAlgorithmLibrary(void)
{
	LogicDLLBaseClass	*ABase=GetLogicDLLBase();
	ABase->InitialLibrary(this);
	GetLibType()->LoadFromDatabase(this);
	GetInstalledLibType()->LoadFromDatabaseInstalled(this,ABase);
}

void    LayersBase::InitialFinalize(QWidget *mainform )
{
	if(GetMTransfer()==NULL){
		MTransfer=new MixTransferComm(this,mainform);
		GetMTransfer()->StartMixTransferServer();
	}
}

void    LayersBase::DeliverOutlineOffset(void)
{
	if(GetEntryPoint()->IsMasterPC()==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendOffset	RCmd(this,"ANY","ANY",page);
			RCmd.InitialInMaster();
			RCmd.Send(NULL,page,0);
		}
	}
}

bool    LayersBase::OpenCommsForDirectComm(void)
{
	if(GetDirectCommBase()==NULL){
		if(GetEntryPoint()->IsMasterPC()==false || GetParamComm()->ConnectedPCNumb==0){
			if(GetDirectCommBase()==NULL){
				DirectComm	*p=GetEntryPoint()->CreateDirectComm(GetMainWidget());
				SetDirectCommBase(p);
			}
		}
	}
	return true;
}

bool    LayersBase::DeliverAllCommsForDirectComm(int WaitingMiliSec)
{
	bool	Ret=true;
	if(GetEntryPoint()->IsMasterPC()==true && GetParamComm()->GetConnectedPCNumb()>0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendAllComms	RCmd(this,"ANY","ANY",page);
			RCmd.Initial();
			RCmd.Data.WaitingTimeToConnect=WaitingMiliSec;
			if(RCmd.SendOnly(page,0,WaitingMiliSec)==false)
				Ret=false;
		}
	}
	return Ret;
}


void    LayersBase::CheckSlave(NPListPack<ErrorInfoList>  &ErrorPages)
{
	int	tmpMaxWaitingCommMilisec=GetParamGlobal()->MaxWaitingCommMilisec;
	if(GetParamGlobal()->MaxWaitingCommMilisec<2000){
		GetParamGlobal()->MaxWaitingCommMilisec=2000;
	}
	if(GetEntryPoint()->IsMasterPC()==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCheckSlave	SCmd(this,"ANY","ANY",page);
			GUICmdAckCheckSlave	RCmd(this,"ANY","ANY",page);
			SCmd.NoCamDevice=GetEntryPoint()->NoCamDevice;
			if(SCmd.Send(page,0,RCmd)==false){
				ErrorInfoList	*a=new ErrorInfoList();
				a->Page	=page;
				a->Messages.append("No response");
				a->ReqReboot=false;
				ErrorPages.AppendList(a);
			}
			else if(RCmd.Ret==GUICmdAckCheckSlave::_ReqReboot){
				ErrorInfoList	*a=new ErrorInfoList();
				a->Page	=page;
				a->Messages=RCmd.Messages;
				a->ReqReboot=true;
				ErrorPages.AppendList(a);
			}
			else if(RCmd.Ret==GUICmdAckCheckSlave::_ErrorOccurs){
				ErrorInfoList	*a=new ErrorInfoList();
				a->Page	=page;
				a->Messages=RCmd.Messages;
				a->ReqReboot=false;
				ErrorPages.AppendList(a);
			}
		}
	}
	GetParamGlobal()->MaxWaitingCommMilisec=tmpMaxWaitingCommMilisec;
}

bool	LayersBase::CheckInstalledAlgorithm(RootNameListContainer &FromGUI,RootNameListContainer &LackOfAlgorithm)
{
	return GetLogicDLLBase()->CheckInstalledAlgorithm(FromGUI,LackOfAlgorithm);
}

bool	LayersBase::SendInfo(int globalPage)
{
	return true;
}


void    LayersBase::MakeAlgorithmBlobList(ExcludedListPack &List)
{
	GetLogicDLLBase()->MakeFieldList(List);
}

void    LayersBase::InitialAllocExecuterDim(void)
{
	if(AllocExecuterDim!=GetParamGlobal()->NGCacheNumb){
		if(ExecuterDim!=NULL){
			for(int i=0;i<AllocExecuterDim;i++){
				delete	ExecuterDim[i];
			}
			delete	[]ExecuterDim;
		}
		AllocExecuterDim=GetParamGlobal()->NGCacheNumb;
		ExecuterDim=new DataInExecuter*[AllocExecuterDim];
		for(int i=0;i<AllocExecuterDim;i++){
			ExecuterDim[i]=new DataInExecuter(i,this);
		}
	}
}

void    LayersBase::InitialResult(bool ShowInWindow)
{
	if(GetResultThread()!=NULL){
		GetResultThread()->Initial(this);

		GetResultThread()->SetMastered(GetParamComm()->Mastered);
		if(GetResultThread()->isRunning()==false
		&& GetInsideLearningEditor()==false
		&& GetShadowLevel()==0
		&& StartThreadWriteMode==true){
			GetResultThread()->start();
		}
	}
	if(GetResultDLLBase()!=NULL){
		GetResultDLLBase()->RemoveAll();
		/*
		if(GetParamGlobal()->ResultDLLPathName.isEmpty()==false){
			GetResultDLLBase()->SearchAddDLL(GetParamGlobal()->ResultDLLPathName);
		}
		*/
		if(GetParamGlobal()->ResultDLLFileName.isEmpty()==false){
			GetResultDLLBase()->LoadDLL(GetParamGlobal()->ResultDLLFileName,ShowInWindow);
		}
	}
	if(GetLotBase()!=NULL){
		GetLotBase()->Initial();
	}
}

void    LayersBase::PrepareResult(void)
{
	GetResultDLLBase()->Prepare();
}

bool	LayersBase::CheckResultDLL(void)
{
	if(GetResultDLLBase()!=NULL){
		if(GetParamGlobal()->ResultDLLFileName.isEmpty()==false){
			if(GetResultDLLBase()->IsEmpty()==true){
				return false;
			}
		}
	}
	return true;
}

void    LayersBase::InitialExecuter(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->SetCurrentResultForCalc(GetResultThread()->GetResult(i));
		ExecuterDim[i]->Initial();
	}
	CurrentCalcPoint	=0;

}
void    LayersBase::InitialArrangementDLL(void)
{
	GetArrangementDLLStock()->SearchAddDLL(GetParamGlobal()->ArrangementDLLPath);
}

bool	LayersBase::CheckDependencyDLL(ComponentListContainer &NoComponentList)
{
	ComponentListContainer List;
	if(GetLogicDLLBase()!=NULL){
		GetLogicDLLBase					()->AssociateComponent(List);
	}
	if(GetGUIInstancePack()!=NULL){
		GetGUIInstancePack				()->AssociateComponent(List);
	}
	if(GetResultDLLBase()!=NULL){
		GetResultDLLBase				()->AssociateComponent(List);
	}
	if(GetLightBase()!=NULL){
		GetLightBase					()->AssociateComponent(List);
	}
	if(GetFilterBank()!=NULL){
		GetFilterBank					()->AssociateComponent(List);
	}
	if(GetGeneralStocker()!=NULL){
		GetGeneralStocker				()->AssociateComponent(List);
	}
	if(GetPrinterClassPackData()!=NULL){
		GetPrinterClassPackData			()->AssociateComponent(List);
	}
	if(GetResultAnalizerDLLContainer()!=NULL){
		GetResultAnalizerDLLContainer	()->AssociateComponent(List);
	}

	if(GetEntryPoint()!=NULL){
		ExecuteInspectBase	*e=GetEntryPoint()->GetExecuteInspect();
		if(e!=NULL){
			int	CamCount=e->GetAllocatedCameraCount();
			for(int Cam=0;Cam<CamCount;Cam++){
				CameraClass		*C=e->GetCamera(Cam);
				if(C!=NULL){
					C->AssociateComponent(List);
				}
			}
		}
	}
	for(ComponentList *L=List.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->DLLType==DLLAlgorithmMode){
			LogicDLL	*s=GetLogicDLLBase()->Search(L->DLLRoot ,L->DLLName);
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==DLLCameraMode){
			if(GetEntryPoint()!=NULL){
				ExecuteInspectBase	*e=GetEntryPoint()->GetExecuteInspect();
				if(e!=NULL){
					int	CamCount=e->GetAllocatedCameraCount();
					int Cam;
					for(Cam=0;Cam<CamCount;Cam++){
						CameraClass		*C=e->GetCamera(Cam);
						if(C!=NULL){
							if(C->GetName()==L->DLLName){
								break;
							}
						}
					}
					if(Cam>=CamCount){
						NoComponentList.Merge(*L);
					}
				}
			}
		}
		else
		if(L->DLLType==DLLResultMode){
			ResultDLL	*s=GetResultDLLBase()->GetResultDLL(L->DLLRoot ,L->DLLName);
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==DLLLightMode){
			IntList RetN;
			GetLightBase()->GetLight(L->DLLName,RetN);
			if(RetN.GetCount()==0){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==DLLFilterMode){
			FilterDLLList	*s=GetFilterBank()->Search(L->DLLName);
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==DLLGeneralStockerMode){
			GeneralStocker	*s=GetGeneralStocker()->Search(L->DLLName);
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==DLLPrinterMode){
			PrinterClass	*s=GetPrinterClassPackData()->Search(L->DLLName);
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==DLLResultAnalizerMode){
			ResultAnalizerDLL	*s=GetResultAnalizerDLLContainer()->Search(L->DLLRoot,L->DLLName);
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
		else
		if(L->DLLType==GUILIB_ID){
			GUIFormBase	*s=FindByName(L->DLLRoot,L->DLLName,/**/"");
			if(s==NULL){
				NoComponentList.Merge(*L);
			}
		}
	}
	if(NoComponentList.GetCount()==0){
		return true;
	}
	return false;
}



std::shared_ptr<DatabaseLoader>	&LayersBase::GetDatabaseLoader(bool CheckDB)	const
{	
	//if(CheckDB==false){
		return (std::shared_ptr<DatabaseLoader>	&)DBLoader;
	//}
	//return (IsDatabaseOk()==true)?DBLoader:NULL;
}

bool    LayersBase::OpenDatabase(XUpdateDatabase &dbase)
{
	SetDatabase(&dbase.DBase);
	if(GetDatabaseLoader()){
		QSqlDatabase	*d=GetDatabaseLoader()->S_OpenDatabase(RootDBase);
		RootDBase=d;
		OriginalRootDBase=true;
		if(GetDatabaseLoader()->S_IsValidDatabase(RootDBase)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::CloseDatabase(void)
{
	if(RootDBase!=NULL && OriginalRootDBase==true){
		if(GetDatabaseLoader()){
			QSqlDatabase	*d=GetDatabaseLoader()->S_CloseDatabase(RootDBase);
			RootDBase=d;
		}
	}
	return true;
}
void	LayersBase::SetDatabase(QSqlDatabase *dbase)
{
	RootDBase=dbase;
}

DataInPage *LayersBase::GetPageDataByPoint(int globalX ,int globalY)
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int	x1,y1,x2,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if((x1<=globalX) && (globalX<=x2) && (y1<=globalY) && (globalY<=y2)){
			return P;
		}
	}
	return NULL;
}


AlgorithmBase	*LayersBase::GetAlgorithmBase(const QString &_DLLRoot ,const QString &_DLLName)	const
{
	if(GetLogicDLLBase()==NULL){
		return NULL;
	}
	LogicDLL	*L=GetLogicDLLBase()->Search(_DLLRoot ,_DLLName);
	if(L!=NULL){
		return L->GetInstance();
	}
	return NULL;
}
LogicDLL		*LayersBase::GetAlgorithmDLL(const QString &_DLLRoot ,const QString &_DLLName)	const
{
	if(GetLogicDLLBase()==NULL){
		return NULL;
	}
	LogicDLL	*L=GetLogicDLLBase()->Search(_DLLRoot ,_DLLName);
	return L;
}

GUIFormBase	*LayersBase::FindByName(const QString &FormRoot ,const QString &FormName ,const QString &InstName)	const
{
	if(GetGUIInstancePack()!=NULL){
		GUIFormBase	*hg=GetGUIInstancePack()->FindByName(FormRoot ,FormName ,InstName);
		if(hg!=NULL){
			return hg;
		}

		if(GetEntryPoint()!=NULL){
			for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
				GUIFormBase	*h=c->FindByName(FormRoot ,FormName ,InstName);
				if(h!=NULL){
					return h;
				}
			}
		}
	}
	return NULL;
}
GUIFormBase	*LayersBase::FindByName(const QString &InstName)	const
{
	if(GetGUIInstancePack()!=NULL){
		GUIFormBase	*hg=GetGUIInstancePack()->FindByName(InstName);
		if(hg!=NULL){
			return hg;
		}

		if(GetEntryPoint()!=NULL){
			for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
				GUIFormBase	*h=c->FindByName(InstName);
				if(h!=NULL){
					return h;
				}
			}
		}
	}
	return NULL;
}
void	LayersBase::SetAreaSizeInImagePanel(bool DrawWholeMode)
{
	for(GUIInstancePack *c=GetGUIInstancePack();c!=NULL;c=c->GetNext()){
		c->SetAreaSizeInImagePanel(DrawWholeMode);
	}
}
int LayersBase::EnumGUIInst(const QString &FormRoot ,const QString &FormName ,GUIFormBase *Ret[] ,int MaxRet)	const
{
	int	RetN=0;
	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		int	n=cg->EnumGUIInst(FormRoot ,FormName ,&Ret[RetN] ,MaxRet-RetN);
		RetN+=n;
		return RetN;
	}
	return 0;
}

int LayersBase::EnumGUI(GUIFormBase *Ret[] ,int MaxRet)	const
{
	int	RetN=0;
	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			if(f!=NULL && RetN<MaxRet){
				Ret[RetN]=f;
				RetN++;
			}
		}
	}
	return RetN;
}
bool	LayersBase::ChangeGUI(const QString &GUIFileData)
{
	return true;
}

bool	LayersBase::IsValidDatabase(void)
{
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->S_IsValidDatabase(RootDBase);
	}
	return true;
}

bool	LayersBase::DatabaseInitialLoad(const QString &PathAndFileName)
{
	if(DBLoader!=NULL){
		return DBLoader->DatabaseInitialLoad(PathAndFileName);
	}
	return false;
}
bool	LayersBase::DatabaseRelease(void)
{
	if(DBLoader!=NULL){
		return DBLoader->DatabaseRelease();
	}
	return false;
}
void	LayersBase::DatabaseLock(void)
{
	if(DBLoader!=NULL){
		DBLoader->DatabaseLock();
	}
}
void	LayersBase::DatabaseUnlock(void)
{
	if(DBLoader!=NULL){
		DBLoader->DatabaseUnlock();
	}
}

void	LayersBase::operator=(GUICmdPacketBase *s)
{
	GUICmdContainer=s;
}

void	LayersBase::operator=(DirectCommPacketBase *s)
{
	DirectCmdContainer=s;
}

void	LayersBase::operator=(IntegrationCmdPacketBase *s)
{
	IntegrationCmdContainer=s;
}

void	LayersBase::RemovePacket(const QString &DLLRoot,const QString &&DLLName)
{
	for(GUICmdPacketBasePointerList *s=GUICmdContainer.GetFirst();s!=NULL;){
		GUICmdPacketBasePointerList *NextS=s->GetNext();
		if(s->GetBase()->EmitterRoot==DLLRoot && s->GetBase()->EmitterName==DLLName){
			GUICmdContainer.RemoveList(s);
			delete	s;
		}
		s=NextS;
	}
	for(DirectCmdPacketBasePointerList *s=DirectCmdContainer.GetFirst();s!=NULL;){
		DirectCmdPacketBasePointerList *NextS=s->GetNext();
		if(s->GetBase()->EmitterRoot==DLLRoot && s->GetBase()->EmitterName==DLLName){
			DirectCmdContainer.RemoveList(s);
			delete	s;
		}
		s=NextS;
	}
	for(IntegrationCmdPacketBasePointerList *s=IntegrationCmdContainer.GetFirst();s!=NULL;){
		IntegrationCmdPacketBasePointerList *NextS=s->GetNext();
		if(s->GetBase()->EmitterRoot==DLLRoot && s->GetBase()->EmitterName==DLLName){
			IntegrationCmdContainer.RemoveList(s);
			delete	s;
		}
		s=NextS;
	}
}

void	LayersBase::SetUseDynamicMasking(bool b)
{	
	UseDynamicMasking=b;
}
bool	LayersBase::SetLanguageCode(int _LanguageCode,bool EnableAlgorithm,bool EnableGUI,bool EnableGeneralStocker)
{
	LanguagePackageData->SetLanguage(_LanguageCode);
	LangLibSolver.SetLanguage(GetLanguagePackageData(),LanguagePackageData->GetLanguageCode());
	if(EnableAlgorithm==true){
		if(GetLogicDLLBase()!=NULL && GetLogicDLLBase()->SetLanguageCode(LanguagePackageData->GetLanguageCode())==false){
			return false;
		}
	}
	if(EnableGUI==true){
		if(GetEntryPoint()!=NULL){
			GetEntryPoint()->SetLanguageCode(LanguagePackageData->GetLanguageCode());
		}
	}
	if(EnableGeneralStocker==true){
		if(GetGeneralStocker()!=NULL){
			GetGeneralStocker()->SetLanguage(LanguagePackageData->GetLanguageCode());
		}
	}
	return true;
}
int		LayersBase::GetLanguageCode(void)
{
	return LanguagePackageData->GetLanguageCode();
}
bool	LayersBase::SetLanguageCode(bool AlgorithmMode,bool GUIMode ,bool GeneralStockerMode)
{
	int	LanguageCode=GetFRegistry()->LoadRegInt("Language",0);
	return SetLanguageCode(LanguageCode,AlgorithmMode,GUIMode ,GeneralStockerMode);
}
bool	LayersBase::LoadLanguageSolution(const QString &LNGFileName)
{
	LocalLanguageSolutionFileName=LNGFileName;
	return LanguagePackageData->LoadSolutionFromFile(LNGFileName);
}

bool	LayersBase::LoadGUILanguage(const QString &GLNFileName)
{
	QFile	File(GLNFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(GUILanguageContainerInst.Load(&File)==false){
			return false;
		}
		return true;
	}
	return false;
}
	
bool	LayersBase::SaveGUILanguage(const QString &GLNFileName)
{
	QFile	File(GLNFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		return GUILanguageContainerInst.Save(&File);
	}
	return false;
}

void	LayersBase::SetDefaultCodec(void)
{
	LanguagePackageData->SetDefaultCodec();
}

void	LayersBase::RestoreCodec(void)
{
	LanguagePackageData->RestoreCodec();
}

void	PageDataInOnePhase::GetGlobalPage(int globalX1 ,int globalY1 
										 ,int globalX2 ,int globalY2 
										 ,IntList &PageList)	const
{
	PageList.RemoveAll();
	if((Parent->GetEntryPoint()!=NULL) && (Parent->GetEntryPoint()->IsMasterPC()==true)){
		ParamGlobal	*PGlobal=Parent->GetParamGlobal();
		for(int page=0;page<Parent->GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int Lx1 ,Ly1 ,Lx2 ,Ly2;
			P->GetArea(Lx1 ,Ly1 ,Lx2 ,Ly2);
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
				,Lx1 ,Ly1 ,Lx2 ,Ly2)==true){
				int gpage=Parent->GetParamComm()->GetGlobalPageFromLocal(*PGlobal,page);
				PageList.Add(gpage);
			}
		}
	}
	else{
		for(int i=0;i<Parent->GetGlobalPageNumb();i++){
			XYData	*XY=Parent->GetGlobalOutlineOffset(i);
			int	Lx1=XY->x;
			int	Ly1=XY->y;
			int	Lx2=XY->x+Parent->GetGlobalOffset(i)->GetDotPerLine();
			int	Ly2=XY->y+Parent->GetGlobalOffset(i)->GetMaxLines();
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
				,Lx1 ,Ly1 ,Lx2 ,Ly2)==true){
				PageList.Add(i);
			}
		}
	}
}

int		LayersBase::GetGlobalPage(int globalX ,int globalY)	const
{
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		if(DefaultArrangeMode==false){
			ParamGlobal	*PGlobal=GetParamGlobal();
			for(int i=0;i<GetPageNumb();i++){
				int x1 ,y1 ,x2 ,y2;
				if((*PageData)[i]!=NULL){
					(*PageData)[i]->GetArea(x1 ,y1 ,x2 ,y2);
					if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
						return GetParamComm()->GetGlobalPageFromLocal(*PGlobal,i);
						//return i;
					}
				}
			}
		}
		else{
			for(int i=0;i<GetPageNumb();i++){
				DataInPage *Pg=GetPageData(i);
				int	x1=Pg->GetOutlineOffset()->x;
				int	y1=Pg->GetOutlineOffset()->y;
				int	x2=x1+Pg->GetDotPerLine();
				int	y2=y1+Pg->GetMaxLines();
				if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
					return i;
				}
			}
		}
	}
	else{
		for(int i=0;i<GlobalPageNumb;i++){
			XYData	&XY=GlobalOffset[i].OutlineOffset;
			if((XY.x<=globalX) && (globalX<XY.x+GlobalOffset[i].GetDotPerLine())
			&& (XY.y<=globalY) && (globalY<XY.y+GlobalOffset[i].GetMaxLines())){
				return i;
			}
		}
	}
	return -1;
}

void	LayersBase::GetGlobalPage(int globalX1 ,int globalY1 
								 ,int globalX2 ,int globalY2 
								 ,IntList &PageList)	const
{
	PageList.RemoveAll();
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int Lx1 ,Ly1 ,Lx2 ,Ly2;
			P->GetArea(Lx1 ,Ly1 ,Lx2 ,Ly2);
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
				,Lx1 ,Ly1 ,Lx2 ,Ly2)==true){
				int gpage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				PageList.Add(gpage);
			}
		}
	}
	else{
		for(int i=0;i<GlobalPageNumb;i++){
			XYData	XY=GlobalOffset[i].OutlineOffset;
			int	Lx1=XY.x;
			int	Ly1=XY.y;
			int	Lx2=XY.x+GlobalOffset[i].GetDotPerLine();
			int	Ly2=XY.y+GlobalOffset[i].GetMaxLines();
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
				,Lx1 ,Ly1 ,Lx2 ,Ly2)==true){
				PageList.Add(i);
			}
		}
	}
}


void	LayersBase::BroadcastMachineID(void)
{
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendMachineID	RCmd(this,"ANY","ANY",page);
			RCmd.MachineID=GetMachineID();
			RCmd.Send(NULL,page,0);
		}
	}
}

bool	LayersBase::MachineIDExists(void)
{
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->G_MachineIDExists(GetDatabase() ,GetMachineID());
	}
	return false;
}



bool    LayersBase::SavePixWithAlgorithm(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqPixWithAlgorithm	RCmd(this,"ANY","ANY",page);
		GUICmdAckPixWithAlgorithm	ACmd(this,"ANY","ANY",page);
		RCmd.Send(page,0,ACmd);
		int64	L=ACmd.Buff.size();
		if(::Save(f,L)==false){
			return false;
		}
		if(f->write(ACmd.Buff)!=L){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadPixWithAlgorithm(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdLoadPixWithAlgorithm	RCmd(this,"ANY","ANY",page);
		int64	L;
		if(::Load(f,L)==false){
			return false;
		}
		RCmd.Buff=f->read(L);
		if(RCmd.Buff.size()!=L){
			return false;
		}
		RCmd.Send(NULL,page,0);
	}
	return true;
}

bool    LayersBase::SaveResult(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqResultInfo	RCmd(this,"ANY","ANY",page);
		GUICmdAckResultInfo	ACmd(this,"ANY","ANY",page);
		if(RCmd.Send(page,0,ACmd)==true){
			int64	L=ACmd.Buff.size();
			if(::Save(f,L)==false){
				return false;
			}
			if(f->write(ACmd.Buff)!=L){
				return false;
			}
		}
	}
	return true;
}

bool    LayersBase::LoadResult(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdLoadResultInfo	RCmd(this,"ANY","ANY",page);
		int64	L;
		if(::Load(f,L)==false){
			return false;
		}
		RCmd.Buff=f->read(L);
		if(RCmd.Buff.size()!=L){
			return false;
		}
		RCmd.Send(NULL,page,0);
	}
	return true;
}

bool	LayersBase::CopyImage(int sourceImageType ,int destImageType)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdCopyImage	RCmd(this,"ANY","ANY",page);
		RCmd.srcImageType=sourceImageType;
		RCmd.dstImageType=destImageType;
		if(RCmd.Send(NULL,page,0)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	x1=  99999999;
	y1=  99999999;
	x2= -99999999;
	y2= -99999999;
	for(int L=0;L<GetPageNumb();L++){
		int	px1,py1,px2,py2;
		if(IsValidData()==true){
			GetPageData(L)->GetArea(px1,py1,px2,py2);
			x1=min(x1,px1);
			y1=min(y1,py1);
			x2=max(x2,px2);
			y2=max(y2,py2);
		}
	}
}

void	LayersBase::ClearInspectID(void)
{	
	GetResultThread()->FlushWaitForWrite();
	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;
}
	
void	LayersBase::SetCurrentInspectID(int64 id)	
{	
	//GetResultThread()->FlushWaitForWrite();
	_LastInspectID=_CurrentInspectID;	
	_CurrentInspectID=id;			
}

void	LayersBase::SetForceChangedInspectID(void)
{	
	static	bool	ReEntrant=false;
	if(ReEntrant==false){
		ReEntrant=true;
		GetResultThread()->FlushWaitForWrite();
		ForceChangedInspectID=true;		
		if(GetParamComm()->Mastered==true){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdSetForceChangedInspectID	RCmd(this,"ANY","ANY",page);
				RCmd.Send(NULL,page,0);
			}
		}
		ReEntrant=false;
	}
}

bool    LayersBase::SaveAttrDefault(void)
{
	if(GetParamGlobal()->WriteEnableToDefaultFile()==true){
		QFile	f(GetParamGlobal()->LayerDefaultFileName);
		if(f.open(QIODevice::WriteOnly)==false){
			return false;
		}
		if(SaveAttr(&f)==false){
			return false;
		}
		//if(GetParamComm()->Mastered==true){
		//	if(SaveOutlineOffsetForDatabase()==false){
		//		return false;
		//	}
		//}
	}
	return true;
}
bool    LayersBase::LoadAttrDefault(void)
{
	QFile	f(GetParamGlobal()->LayerDefaultFileName);
	if(f.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(LoadAttr(&f)==false){
		return false;
	}
	return true;
}

bool    LayersBase::SaveAttr(QIODevice *f)
{
	int32	ID=0x5eea;
	if(::Save(f,ID)==false){
		return false;
	}
	int32	Ver=2;
	if(::Save(f,Ver)==false){
		return false;
	}
	int32	iPhaseNumb=GetPhaseNumb();
	if(::Save(f,iPhaseNumb)==false){
		return false;
	}
	for(int phase=0;phase<iPhaseNumb;phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->SaveAttr(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadAttr(QIODevice *f)
{
	int32	ID;
	if(::Load(f,ID)==false){
		return false;
	}
	if(ID!=0x5eea){
		return false;
	}
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver==1){
		int32	iPageNumb;
		if(::Load(f,iPageNumb)==false){
			return false;
		}
		for(int page=0;(page<GetPageNumb()) && (page<iPageNumb);page++){
			DataInPage *p=GetPageData(page);
			if(p->LoadAttr(f)==false){
				return false;
			}
		}
	}
	else if(Ver==2){
		int32	iPhaseNumb;
		if(::Load(f,iPhaseNumb)==false){
			return false;
		}
		for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
			PageDataInOnePhase	*P=GetPageDataPhase(phase);
			if(P->LoadAttr(f)==false){
				return false;
			}
		}
	}
	return true;
}

bool    LayersBase::SaveBrightTable(QIODevice *f)
{
	if(::Save(f,(int32)GetPhaseNumb())==false)
		return false;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->SaveBrightTable(f)==false){
			return false;
		}
	}
	return true;
}

bool    LayersBase::LoadBrightTable(QIODevice *f)
{
	int32	iPhaseNumb;
	if(::Load(f,iPhaseNumb)==false)
		return false;
	for(int phase=0;phase<GetPhaseNumb() && phase<iPhaseNumb;phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->LoadBrightTable(f)==false){
			return false;
		}
	}
	return true;
}

bool    LayersBase::SaveImages(QIODevice *f)
{
	int32	PageNumb=GetPageNumb();
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
bool    LayersBase::LoadImages(QIODevice *f)
{
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false){
		return false;
	}
	for(int page=0;(page<GetPageNumb()) && (page<iPageNumb);page++){
		DataInPage *p=GetPageData(page);
		if(p->Load(f)==false){
			return false;
		}
	}
	return true;
}

bool    LayersBase::SaveHeader(QIODevice *f)
{
	if(::Save(f,MasterCode	)==false){
		return false;
	}
	if(::Save(f,MasterName)==false){
		return false;
	}
	if(::Save(f,Remark)==false){
		return false;
	}
	if(::Save(f,MachineID)==false){
		return false;
	}
	if(::Save(f,RegTime)==false){
		return false;
	}
	if(::Save(f,WorkerID)==false){
		return false;
	}
	if(::Save(f,WorkerName)==false){
		return false;
	}
	if(::Save(f,Version)==false){
		return false;
	}
	if(::Save(f,LastEditTime)==false){
		return false;
	}
	if(::Save(f,CategoryID)==false){
		return false;
	}
	return true;
}
bool    LayersBase::LoadHeader(QIODevice *f)
{
	if(::Load(f,MasterCode	)==false){
		return false;
	}
	if(::Load(f,MasterName)==false){
		return false;
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	if(::Load(f,MachineID)==false){
		return false;
	}
	if(::Load(f,RegTime)==false){
		return false;
	}
	if(::Load(f,WorkerID)==false){
		return false;
	}
	if(::Load(f,WorkerName)==false){
		return false;
	}
	if(::Load(f,Version)==false){
		return false;
	}
	if(::Load(f,LastEditTime)==false){
		return false;
	}
	if(::Load(f,CategoryID)==false){
		return false;
	}
	return true;
}

bool	LayersBase::HasRegulation(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->HasRegulation()==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::SaveRegulation(QIODevice *f)
{
	if(::Save(f,(int32)GetPhaseNumb())==false)
		return false;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->SaveRegulation(f)==false){
			return false;
		}
	}
	return true;
}

bool    LayersBase::LoadRegulation(QIODevice *f)
{
	int32	iPhaseNumb;
	if(::Load(f,iPhaseNumb)==false)
		return false;
	for(int phase=0;phase<GetPhaseNumb() && phase<iPhaseNumb;phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->LoadRegulation(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::SaveRegulationDefault(void)
{
	if(GetParamGlobal()->RegulationFileName.isEmpty()==false){
		QString	FileName=GetUserPath()+::GetSeparator()+GetParamGlobal()->RegulationFileName;
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			return SaveRegulation(&File);
		}
		return false;
	}
	return true;
}
bool    LayersBase::LoadRegulationDefault(void)
{
	if(GetParamGlobal()->RegulationFileName.isEmpty()==false){
		QString	FileName=GetUserPath()+::GetSeparator()+GetParamGlobal()->RegulationFileName;
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			return LoadRegulation(&File);
		}
		return false;
	}
	return true;
}

bool	LayersBase::AddMasterFieldData(const QString &FieldName, const QVariant &data)
{
	if(IsDatabaseOk()==true){
		if(GetDatabaseLoader()){
			return GetDatabaseLoader()->G_SQLAddMasterFieldData(GetDatabase() ,MasterCode ,FieldName, data);
		}
		return true;
	}
	return false;
}
bool	LayersBase::AddMasterFieldData	(int _MasterCode,const QString &FieldName, const QVariant &data)
{
	if(IsDatabaseOk()==true){
		if(GetDatabaseLoader()){
			return GetDatabaseLoader()->G_SQLAddMasterFieldData(GetDatabase() ,_MasterCode ,FieldName, data);
		}
		return true;
	}
	return false;
}
bool	LayersBase::AddRelationFieldData(int RelationCode,const QString &FieldName, const QVariant &data)
{
	if(IsDatabaseOk()==true){
		if(GetDatabaseLoader()){
			return GetDatabaseLoader()->G_SQLAddRelationFieldData(GetDatabase() ,RelationCode ,FieldName, data);
		}
		return true;
	}
	return false;
}
bool	LayersBase::LoadMasterFieldData(const QString &FieldName,QVariant &data)
{
	if(IsDatabaseOk()==true){
		if(GetDatabaseLoader()){
			return GetDatabaseLoader()->G_SQLLoadMasterFieldData(GetDatabase() ,MasterCode ,FieldName, data);
		}
		return true;
	}
	return false;
}
bool	LayersBase::LoadMasterFieldData		(int _MasterCode,const QString &FieldName, QVariant &data)
{
	if(IsDatabaseOk()==true){
		if(GetDatabaseLoader()){
			return GetDatabaseLoader()->G_SQLLoadMasterFieldData(GetDatabase() ,_MasterCode ,FieldName, data);
		}
		return true;
	}
	return false;
}
bool	LayersBase::LoadRelationFieldData(int RelationCode,const QString &FieldName, QVariant &data)
{
	if(IsDatabaseOk()==true){
		if(GetDatabaseLoader()){
			return GetDatabaseLoader()->G_SQLLoadRelationFieldData(GetDatabase() ,RelationCode ,FieldName, data);
		}
		return true;
	}
	return false;
}

bool    LayersBase::SaveAllAlgorithm(QIODevice *f)
{
	return GetLogicDLLBase()->Save(f);
}
bool    LayersBase::LoadAllAlgorithm(QIODevice *f)
{
	return GetLogicDLLBase()->Load(f);
}

QString	LayersBase::GetColorString(int gx ,int gy)	const
{
	QString	ret;
	for(int page=0;page<GetPageNumb();page++){
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
void	LayersBase::GetGlobalPage(int globalX ,int globalY,IntList &PageList)	const
{
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int	LocalX=globalX-P->GetOutlineOffset()->x;
			int	LocalY=globalY-P->GetOutlineOffset()->y;
			if(0<=LocalX && LocalX<P->GetDotPerLine() && 0<=LocalY && LocalY<P->GetMaxLines()){
				PageList.Add(page);
			}
		}
	}
	else{
		for(int page=0;page<GlobalPageNumb;page++){
			int	LocalX=globalX-GlobalOffset[page].OutlineOffset.x;
			int	LocalY=globalY-GlobalOffset[page].OutlineOffset.y;
			if(0<=LocalX && LocalX<GlobalOffset[page].GetDotPerLine() && 0<=LocalY && LocalY<GlobalOffset[page].GetMaxLines()){
				PageList.Add(page);
			}
		}
	}
}

int		LayersBase::GetLocalPageFromArea(FlexArea &Area ,IntList &List)	const
{
	int	ret=0;
	for(int page=0;page<GetPageNumb();page++){
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

int		LayersBase::GetLocalPageFromArea(DisplayImage *p ,FlexArea &Area ,IntList &List)	const
{
	int	ret=0;
	if(p->ModeShowOnlyTopTurn==false){
		for(int page=0;page<GetPageNumb();page++){
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
		int	page=GetDrawturn(0)->GetPage();
			
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

int		LayersBase::GetLocalPageFromVector(VectorLineBase *v,IntList &PageList)	const
{
	int	ret=0;
	for(int page=0;page<GetPageNumb();page++){
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

int		LayersBase::GetLocalPageFromAreaFromDrawingTop(FlexArea &Area)	const
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetDrawturn(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			return P->GetPage();
		}
	}
	return -1;
}

int		LayersBase::GetLocalPageFromAreaFromDrawingTop(int globalX ,int globalY)	const
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetDrawturn(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
			return P->GetPage();
		}
	}
	return -1;
}

	
int		LayersBase::GetLocalPageFromGlobal	(int globalPage)	const
{
	return GetParamComm()->GetLocalPageFromGlobal(*GetParamGlobal(),globalPage);
}
int		LayersBase::GetGlobalPageFromLocal	(int localPage)	const
{
	return GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),localPage);
}

int		LayersBase::GetLocalMatrixFromGlobal(int globalX ,int globalY 
											,int &localX ,int &localY)	const
{	
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		int	gpage=GetGlobalPage(globalX ,globalY);
		int	lPage=GetLocalPageFromGlobal(gpage);
		if((lPage<0) || (lPage>=GetPageNumb())){
			XYData	*p=GetGlobalOutlineOffset(gpage);
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
		for(int page=0;page<GlobalPageNumb;page++){
			int	LocalX=globalX-GlobalOffset[page].OutlineOffset.x;
			int	LocalY=globalY-GlobalOffset[page].OutlineOffset.y;
			if(0<=LocalX && LocalX<GlobalOffset[page].GetDotPerLine() && 0<=LocalY && LocalY<GlobalOffset[page].GetMaxLines()){
				localX=LocalX;
				localY=LocalY;
				return page;
			}
		}
	}
	return -1;
}
void	LayersBase::GetLocalMatrixFromGlobal(int GlobalPage,int globalX ,int globalY ,int &localX ,int &localY)	const
{
	XYData	*p=GetGlobalOutlineOffset(GlobalPage);
	if(p!=NULL){
		localX=globalX - p->x;
		localY=globalY - p->y;
	}
	else{
		int	lPage=GetLocalPageFromGlobal(GlobalPage);
		GetPageData(lPage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
	}
}

void	LayersBase::GetGlobalMatrixFromLocal(int localPage 
											,int localX ,int localY 
											,int &globalX ,int &globalY)	const
{
	int	gpage=GetGlobalPageFromLocal(localPage);
	XYData	*p=GetGlobalOutlineOffset(gpage);
	if(p!=NULL){
		globalX=localX+p->x;
		globalY=localY+p->y;
	}
}
bool	LayersBase::GetRealMatrixFromGlobal(int globalX ,int globalY 
											,double &realX ,double &realY)	const
{
	int		localX ,localY;
	int	Page=GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	if(Page<0 || GetPageNumb()<=Page)
		return false;
	DataInPage	*P=GetPageData(Page);
	if(P->TransformImageToReal(localX ,localY,realX ,realY)==false){
		realX=((double)localX)/((double)GetParamGlobal()->ResolutionXNano)/1000000.0;
		realY=((double)localY)/((double)GetParamGlobal()->ResolutionYNano)/1000000.0;
	}
	return true;
}

bool	LayersBase::HasRealTransform(int globalX ,int globalY)	const
{
	int		localX ,localY;
	int	Page=GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	if(Page<0 || GetPageNumb()<=Page)
		return false;
	DataInPage	*P=GetPageData(Page);
	double realX ,realY;
	if(P->TransformImageToReal(localX ,localY,realX ,realY)==false){
		return false;
	}
	return true;
}

XYData	*LayersBase::GetGlobalOutlineOffset(int globalpage)	const
{	
	static	XYData	_XYData;
	if(GlobalOffset==NULL || globalpage<0 || globalpage>=GlobalPageNumb){
		_XYData.x=0;
		_XYData.y=0;
		return &_XYData;
	}
	return &GlobalOffset[globalpage].OutlineOffset;	
}
void	LayersBase::IncrementInspectID(void)
{	
	_LastInspectID=_CurrentInspectID;
	_CurrentInspectID+=GetParamGlobal()->AddInspectID;
}
void	LayersBase::DecrementInspectID(void)
{	
	_CurrentInspectID-=GetParamGlobal()->AddInspectID;
	_LastInspectID=_CurrentInspectID;
}

DataInExecuter	*LayersBase::GetExecuter(const XDateTime &Key)	const
{
	for(int i=0;i<AllocExecuterDim;i++){
		if(ExecuterDim[i]->GetResultInspection()->GetStartTimeForInspection()==Key){
			return ExecuterDim[i];
		}
	}
	return NULL;
}
DataInExecuter	*LayersBase::GetExecuter(ResultInspection *Res)	const
{
	for(int i=0;i<AllocExecuterDim;i++){
		if(ExecuterDim[i]->GetResultInspection()==Res){
			return ExecuterDim[i];
		}
	}
	return NULL;
}
void	LayersBase::ClearAllReceivedResultCounts(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->ClearReceivedResultCounts();
	}
}

void	LayersBase::PushExecuterState(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->PushState();
	}
}
void	LayersBase::PopExecuterState(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->PopState();
	}
}
bool		LayersBase::MakeExecuteInitialAfterEditInfo	(ExecuteInitialAfterEditInfo &EInfo)
{
	bool	Ret=true;
	if(GetLayersBase()->GetLogicDLLBase()!=NULL){
		if(GetLayersBase()->GetLogicDLLBase()->MakeExecuteInitialAfterEditInfo(0,GetCurrentResultForCalc(),EInfo)==false){
			Ret=false;
		}
	}
	return Ret;
}
ExeResult	LayersBase::ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(int p=0;p<AllocExecuterDim;p++){
		ExecuterDim[p]->ExecuteInitialAfterEditLoop(p);
	}
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=ExecuterDim[CurrentCalcPoint]->ExecuteInitialAfterEdit(CurrentCalcPoint,EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);
	}
	for(int p=0;p<AllocExecuterDim;p++){
		ExecuterDim[p]->ExecuteInitialAfterEditLoop(p);
	}
	if(ResultDLLBase!=NULL){
		ResultDLLBase->ExecuteInitialAfterEdit(CurrentCalcPoint,GetCurrentResultForCalc());
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->SetEdited(false);
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteInitialAfterEdit(CurrentCalcPoint);
	}
	ChildrenExecuteInitialAfterEdit(EInfo,ProgressStep);

	return Ret;
}
ExeResult	LayersBase::ExecuteStartByScanOnly	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecuteStartByScanOnly(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);
	}
	if(ResultDLLBase!=NULL){
		ResultDLLBase->ExecuteStartByInspection(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
	}
	ChildrenExecuteStartByScanOnly(ProgressStep);

	return Ret;
}
ExeResult	LayersBase::ExecuteStartByInspection(bool ProgressStep)
{
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	LastCurrentCalcPoint=CurrentCalcPoint;
	if(GetParamGlobal()->AllocateTargetTRBuff==true){
		CopyTargetToTransposition();
	}
	int	tCurrentCalcPoint=CurrentCalcPoint;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecuteStartByInspection(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecuteStartByInspection(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
		if(ProgressStep==true){
			if(GetParamGlobal()->GetMaxScanStrategy()<=1
			|| GetParamGlobal()->GetMaxScanStrategy()<=(GetCurrentStrategicNumber()+1)){
				if((GetCurrentScanPhaseNumber()+1)>=GetParamGlobal()->GetScanPhaseCount()){
					CurrentCalcPoint++;
					if(CurrentCalcPoint>=AllocExecuterDim){
						CurrentCalcPoint=0;
					}
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteStartByInspection(tCurrentCalcPoint);
	}

	ChildrenExecuteStartByInspection(ProgressStep);

	UnlockChangingDataStructure();

	return Ret;
}

void	LayersBase::SetCurrentStrategicNumberInExe(int d)
{	
	if(d<GetParamGlobal()->GetMaxScanStrategy()){
		CurrentStrategicNumberInExe=d;
		for(int i=0;i<GetShadowChildrenCount();i++){
			GetShadowChildren(i)->GetTreeLayersBase()->SetCurrentStrategicNumberInExe(d);
		}
	}
	else{
		CurrentStrategicNumberInExe=0;
		for(int i=0;i<GetShadowChildrenCount();i++){
			GetShadowChildren(i)->GetTreeLayersBase()->SetCurrentStrategicNumberInExe(0);
		}
	}
}
	
DataInExecuter::ExecutingState	LayersBase::GetCurrentStateInexecuter(int index)	const
{
	return ExecuterDim[index]->GetState();
}

int		LayersBase::GetIndexInCurrentStateExecuter(DataInExecuter::ExecutingState state)
{
	for(int i=0;i<AllocExecuterDim;i++){
		if(ExecuterDim[i]->GetState()==state){
			return i;
		}
	}
	return -1;
}
bool	LayersBase::SetCurrentStateInExecuter(int index ,DataInExecuter::ExecutingState state)
{
	if(0<=index && index<AllocExecuterDim){
		ExecuterDim[index]->ForceState(state);
		return true;
	}
	return false;
}
ExeResult	LayersBase::ExecuteCaptured(ListPhasePageLayerPack &CapturedList ,bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			DataInExecuter::ExecutingState	s=ExecuterDim[i]->GetState();
			if(s==DataInExecuter::FinExecuteStartByInspection
			|| s==DataInExecuter::FinExecuteStartByScanOnly){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteCaptured(i,CapturedList);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);

				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteCaptured(i,ExecuterDim[i]->GetResultInspection(),CapturedList);
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteCaptured(Point,CapturedList);
	}
	ChildrenExecuteCaptured(CapturedList,ProgressStep);

	return Ret;
}

ExeResult	LayersBase::ExecutePreAlignment		(bool ProgressStep)
{	
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			DataInExecuter::ExecutingState	s=ExecuterDim[i]->GetState();
			if(s==DataInExecuter::FinExecuteStartByInspection
			|| s==DataInExecuter::FinExecuteStartByScanOnly){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecutePreAlignment	(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);

				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecutePreAlignment(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecutePreAlignment(Point);
	}

	ChildrenExecutePreAlignment(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::ExecuteAlignment		(bool ProgressStep)
{	
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecutePreAlignment){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteAlignment(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);

				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteAlignment(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteAlignment(Point);
	}
	ChildrenExecuteAlignment(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::ExecutePreProcessing	(bool ProgressStep)
{	
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteAlignment){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecutePreProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecutePreProcessing(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecutePreProcessing(Point);
	}

	ChildrenExecutePreProcessing(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::ExecuteProcessing		(bool ProgressStep)
{
	static	int		DebugPage=11;
	static	bool	DebugMode=false;

	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		if(GetCurrentStrategicNumberInExe()==DebugPage){
			DebugMode=true;
		}
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecutePreProcessing){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteProcessing(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteProcessing(Point);
	}
	ChildrenExecuteProcessing(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::ExecuteProcessingRevived(bool ProgressStep)
{
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteProcessing){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteProcessingRevived(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteProcessingRevived(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteProcessingRevived(Point);
	}
	ChildrenExecuteProcessingRevived(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::PretendFinishProcessing	(bool ProgressStep)
{
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			DataInExecuter::ExecutingState	s=ExecuterDim[i]->GetState();
			if(s==DataInExecuter::FinExecuteStartByInspection
			|| s==DataInExecuter::FinExecuteStartByScanOnly){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->PretendFinishProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
			}
		}
	}
	ChildrenPretendFinishProcessing(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}

ExeResult	LayersBase::ExecutePostProcessing	(bool ProgressStep)
{	
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			DataInExecuter::ExecutingState	s=ExecuterDim[i]->GetState();
			if(s==DataInExecuter::FinExecuteProcessingRevived
			|| s==DataInExecuter::NowExecuteStartByInspection){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecutePostProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecutePostProcessing(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
		CurrentDrawPoint=LastCurrentCalcPoint;
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecutePostProcessing(Point);
	}
	ChildrenExecutePostProcessing(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}

ExeResult	LayersBase::ExecutePreScanning	(bool ProgressStep)
{	
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecutePreScanning(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecutePreScanning(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecutePreScanning(CurrentCalcPoint);
	}
	ChildrenExecutePreScanning(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::ExecuteScanning	(bool ProgressStep)
{
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecuteScanning(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecuteScanning(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecuteScanning(CurrentCalcPoint);
	}
	ChildrenExecuteScanning(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}
ExeResult	LayersBase::ExecutePostScanning	(bool ProgressStep)
{	
	//LockWChangingDataStructure();
	LockRChangingDataStructure();

	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecutePostScanning(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecutePostScanning(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL && GetShadowLevel()==0){
		GetEntryPoint()->GetExecuteInspect()->ExecutePostScanning(CurrentCalcPoint);
	}
	ChildrenExecutePostScanning(ProgressStep);
	UnlockChangingDataStructure();
	return Ret;
}

void	LayersBase::StandardManageResult(ResultInspection *Res)
{
	Res->BuildNGImages();
	//Res->BuildNGImages2();
}
bool	LayersBase::PutCurrentResult(void)
{
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecutePostProcessing
			&& ExecuterDim[i]->GetDonePutCurrentResult()==false){
				ExecuterDim[i]->PutCurrentResult();
				return true;
			}
		}
	}
	return false;
}

bool	LayersBase::PutForceResult(int InspectionID,bool DependOnPhaseMode,bool DependOnPageMode)
{
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetResultInspection()->GetInspectionID()==InspectionID){
				ExecuterDim[i]->PutForceCurrentResult(DependOnPhaseMode,DependOnPageMode);
				return true;
			}
		}
	}
	return false;
}
void	LayersBase::RefreshByMap(int phase ,int page ,ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			AlgorithmInPageInOnePhase	*Ah=a->GetInstance()->GetPageDataPhase(phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
				Ap->RefreshByMap(Mode,Map);
			}
		}
	}
}
void	LayersBase::RefreshByMap(int phase ,int page ,int layer ,ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			AlgorithmInPageInOnePhase	*Ah=a->GetInstance()->GetPageDataPhase(phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
				Ap->RefreshByMap(layer ,Mode,Map);
			}
		}
	}
}

ResultInspection	*LayersBase::GetCurrentResultForCalc(void)	const
{
	if(ExecuterDim!=NULL){
		ResultInspection	*Ret=ExecuterDim[LastCurrentCalcPoint]->GetResultInspection();
		return Ret;
	}
	return NULL;
}
ResultInspection	*LayersBase::GetNextResultForCalc(void)	const
{
	if(ExecuterDim!=NULL){
		ResultInspection	*Ret=ExecuterDim[CurrentCalcPoint]->GetResultInspection();
		return Ret;
	}
	return NULL;
}
void	LayersBase::RewindCalcPoint(void)
{
	CurrentCalcPoint=LastCurrentCalcPoint;
}

void	LayersBase::GetCalcPoint(int CPoints[])	const
{
	CPoints[0]=CurrentCalcPoint;
	CPoints[1]=CurrentDrawPoint;
	CPoints[2]=LastCurrentCalcPoint;
}
void	LayersBase::SetCalcPoint(int CPoints[])
{
	ExecuterDim[CPoints[0]]->ClearReceivedResultCounts();
	if(CPoints[0]+1>=AllocExecuterDim){
		ExecuterDim[0]->ClearReceivedResultCounts();
		}
	else{
		ExecuterDim[CPoints[0]+1]->ClearReceivedResultCounts();
	}

	CurrentCalcPoint	=CPoints[0];
	CurrentDrawPoint	=CPoints[1];
	LastCurrentCalcPoint=CPoints[2];
}
void	LayersBase::DecPoint(void)
{
	CurrentCalcPoint--;
	if(CurrentCalcPoint<0){
		CurrentCalcPoint=AllocExecuterDim-1;
	}
}

void	LayersBase::SetCurrentScanPhaseNumber(int n)
{	
	if(GetParamGlobal()->UseScanPhaseNumber==true){
		CurrentScanPhaseNumber=n;
		IntList PhaseCodes;
		GetParamGlobal()->GetPhaseNumber(PhaseCodes ,CurrentScanPhaseNumber);
		if(PhaseCodes.GetCount()>0){
			int	Ph=PhaseCodes[0];
			SetCurrentPhase(Ph);
		}
	}
}
void	LayersBase::IncreaseCurrentScanPhaseNumber(void)
{
	if(GetParamGlobal()->UseScanPhaseNumber==true){
		CurrentScanPhaseNumber++;
		if(CurrentScanPhaseNumber>=GetPhaseNumb()){
			CurrentScanPhaseNumber=0;
		}
	}
}

void	LayersBase::TF_SetCurrentScanPhaseNumber(int n)
{
	if(GetParamGlobal()->UseScanPhaseNumber==true){
		SetCurrentScanPhaseNumber(n);
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdSetCurrentScanPhaseNumber	Cmd(this,"ANY","ANY",globalPage);
			Cmd.CurrentScanPhaseNumber=n;
			Cmd.Send(NULL,globalPage ,0);
		}
	}
}
int32	LayersBase::GetCurrentScanPhaseNumber(void)	const
{
	return GetTopLayersBase()->CurrentScanPhaseNumber;
}
void	LayersBase::GetCurrentPhaseFromScanPhase(IntList &PhaseCodes)	const
{
	if(GetShadowLevel()==0){
		PhaseCodes.RemoveAll();
		if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-2){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				PhaseCodes.Add(phase);
			}
		}
		else
		if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-1){
			GetParamGlobal()->GetPhaseNumber(PhaseCodes ,CurrentScanPhaseNumber);
		}
		else
		if(GetParamGlobal()->ModePhaseExecuteStartByInspection>=0){
			PhaseCodes.Add(GetParamGlobal()->ModePhaseExecuteStartByInspection);
		}
	}
	else{
		GetParentLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	}
}

void	LayersBase::GetPhaseFromScanPhase(int ScanPhaseNumber ,IntList &PhaseCodes)	const
{
	if(GetShadowLevel()==0){
		GetParamGlobal()->GetPhaseNumber(PhaseCodes ,ScanPhaseNumber);
	}
	else{
		GetParentLayersBase()->GetPhaseFromScanPhase(ScanPhaseNumber ,PhaseCodes);
	}
}

void	LayersBase::GetScanPhaseFromPhase(int phase ,int &RetScanPhaseNumber)	const
{
	if(GetShadowLevel()==0){
		GetParamGlobal()->GetScanPhaseFromPhase(phase ,RetScanPhaseNumber);
	}
	else{
		GetParentLayersBase()->GetScanPhaseFromPhase(phase ,RetScanPhaseNumber);
	}
}

ResultInspection	*LayersBase::GetCurrentResultForDraw(void)	const
{
	static	ResultInspection	Dummy(NULL);

	if(ExecuterDim==NULL){
		return &Dummy;
	}
	ResultInspection	*Ret=ExecuterDim[CurrentDrawPoint]->GetResultInspection();
	return Ret;
}

ResultInspection	*LayersBase::GetBufferedResult(int64 inspectionID)	const
{
	return GetResultThread()->GetBufferedResult(inspectionID);
}

ResultInspection	*LayersBase::GetBufferedResultAbsolutely(int64 inspectionID)	const
{
	return GetResultThread()->GetBufferedResultAbsolutely(inspectionID);
}

ResultInspection	*LayersBase::GetBufferedOlderResult(int64 inspectionID, int GenerationLevel)	const
{
	return GetResultThread()->GetBufferedOlderResult(inspectionID, GenerationLevel);
}

void	LayersBase::ExecuteCopy(const QString &AlgoRoot ,const QString &AlgoName ,int localPage 
								,const XDateTime &createdTime,IntList &LayerList,bool EnableDup)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckDLL(AlgoRoot,AlgoName)==true){
			ClipboardAlgorithm	*C=L->ExecuteCopy(localPage ,createdTime,LayerList);
			if(C!=NULL){
				for(ClipboardAlgorithm *c=GetClipboardDatas()->GetFirst();c!=NULL;c=c->GetNext()){
					if(c->GetCreatedTime()==createdTime){
						c->Absorb(C);
						goto	QNext;
					}
				}
				GetClipboardDatas()->AppendList(C,EnableDup);
			}
QNext:;
		}
	}
}
void	LayersBase::Draw(QImage &img, int movx ,int movy ,double ZoomRate)
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		P->Draw(img, movx ,movy ,ZoomRate);
	}
}

ClipboardAlgorithm	*LayersBase::SearchClipboard(const XDateTime &id)
{
	for(ClipboardAlgorithm *c=GetClipboardDatas()->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetCreatedTime()==id){
			return c;
		}
	}
	return NULL;
}

int		LayersBase::GetSelectedItemCount(const QString &DLLRoot ,const QString &DLLName)
{
	AlgorithmBase	*A=GetAlgorithmBase(DLLRoot ,DLLName);
	if(A!=NULL){
		return A->GetSelectedItemCount();
	}
	return 0;
}
AlgorithmBase	*LayersBase::GetAlgorithmBase(int LibType)	const
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->GetLibType()==LibType){
			return L->GetInstance();
		}
	}
	return NULL;
}

void	LayersBase::GetAlgorithmByType(AlgorithmBasePointerContainer &Bases ,int AlgorithmType)	const
{
	Bases.RemoveAll();
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmType)==true){
			Bases.Add(L->GetInstance());
		}
	}
}

void	LayersBase::SetStartInspectTime(const XDateTime &d)
{	
	StartInspectionTime=d;
	//InspectionTimeMilisec=GetComputerMiliSec();
}
void	LayersBase::SetEndInspectionTime(const XDateTime &d)
{	
	EndInspectionTime=d;
}
XDateTime	&LayersBase::GetStartInspectTime(void)
{	
	return StartInspectionTime;	
}
XDateTime	&LayersBase::GetEndInspectionTime(void)	
{	
	return EndInspectionTime;	
}
	
void	LayersBase::SetMainForm(GUIFormBase *form)
{
	if(form!=NULL){
		MainWidget=form;
		MainWidget->setObjectName(/**/"MainForm");
		connect(this,SIGNAL(SignalMainFormCommand(int)),MainWidget,SLOT(SlotCommand(int)),Qt::QueuedConnection);
		connect(ResultThread,SIGNAL(SignalWroteSlave(XDateTime))	,MainWidget,SLOT(SlotWroteSlave(XDateTime))	,Qt::QueuedConnection);
		connect(ResultThread,SIGNAL(SignalChangeLotInfo(int))			,MainWidget,SLOT(SlotChangeLotInfo(int))		,Qt::QueuedConnection);
		MainWidget->GiveName(NULL);
	}
}
void	LayersBase::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	if(GetGUIInstancePack()!=NULL && GetEntryPoint()!=NULL){
		for(GUIInstancePack *c=GetGUIInstancePack();c!=NULL;c=c->GetNext()){
			for(GUIItemInstance *d=c->NPListPack<GUIItemInstance>::GetFirst();d!=NULL;d=d->GetNext()){
				d->GetForm()->TransmitDirectly(packet);
			}
		}
	}
	if(GetLogicDLLBase()!=NULL){
		for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmBase	*B=a->GetInstance();
			B->DeliverTransmitDirectly(packet);
		}
	}
	if(GetLightBase()!=NULL){
		for(LightAccessList *L=GetLightBase()->GetFirst();L!=NULL;L=L->GetNext()){
			L->TransmitDirectly(packet);
		}
	}
	if(GetResultDLLBase()!=NULL){
		for(ResultDLL *R=GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
			R->GetDLLPoint()->TransmitDirectly(packet);
		}
	}
	if(GetResultDLLBase()!=NULL){
		for(ResultDLL *R=GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
			R->GetDLLPoint()->TransmitDirectly(packet);
		}
	}
	for(int phase=0;phase!=GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		for(int page=0;page!=GetPageNumb();page++){
			FilterInstanceContainer	*F=Ph->GetFilterContainer(page);
			for(FilterInstanceList *f=F->GetFirst();f!=NULL;f=f->GetNext()){
				f->TransmitDirectly(packet);
			}
		}
	}			
}

void	LayersBase::WroteSlave(const XDateTime &tm)
{
	ResultInspectionForStock	*r=GetResultThread()->Pickup(tm);
	if(r!=NULL){
		ResultWrittenID=r->GetInspectionID();
		if(GetParamComm()->Mastered==false){
			PacketWritternResult->InspectedTime=tm;
			PacketWritternResult->SendFromSlaveToMaster(GetGlobalPageFromLocal(0),0);
		}
	}
	else{
		ErrorOccurs++;
	}
}
void	LayersBase::SetResultWrittenID(int64 id)
{	
	ResultWrittenID=id;
	if(GetMainWidget()!=NULL){
		GetMainWidget()->BroadcastWroteResult(id);
	}
}

int64	LayersBase::GetUnsavedMinimumID(void)
{
	return GetResultThread()->GetUnsavedMinimumID();
}

void	LayersBase::CommandSaveResultToSlave(ResultInspection *res)
{
	if(GetParamComm()->GetConnectedPCNumb()==0){
		SaveSlaveCommand(res);
	}
	else{
		ResultInspectionPointerStocker->AddPoint(res);
		emit	SignalMainFormCommand(ResultCmdSaveSlaveCommand);
	}
}

void	LayersBase::CommandOutputInLotChangedToSlave(void)
{
	emit	SignalMainFormCommand(ResultCmdLotChangedSlaveCommand);
}
void	LayersBase::SaveSlaveCommand(ResultInspection *Res)
{
	static	QString	LStr;
	if(Res!=NULL){
		LStr=Res->GetStartTimeForInspection().toString("hhmmss");
		char	buff[50];
		QString2Char(LStr,buff ,sizeof(buff));
		GetLogCreater()->PutLogA2(__LINE__,"MainFormCommand",buff,Res->GetInspectionID());

		QBuffer	LotBuff;
		LotBuff.open(QIODevice::ReadWrite);
		::Save(&LotBuff,Res->GetLotID());
		::Save(&LotBuff,Res->GetLotName());
		//::Save(&LotBuff,GetLotBase()->GetLotID());
		//::Save(&LotBuff,GetLotBase()->GetLotName());

		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
				ResultCmdSaveSlave	Cmd(this,"ANY","ANY",page);
				Cmd.InspectedTime	=Res->GetStartTimeForInspection();
				Cmd.MachineID		=Res->GetLayersBase()->MachineID;
				Cmd.LotData			=LotBuff.buffer();
				Cmd.MasterID		=GetMasterCode();
				Cmd.Phase			=phase;
				Cmd.DeliveryInfo	=Res->GetDeliveredInfo();
				Cmd.Send(NULL,page ,0);
			}
		}
	}
}
void	LayersBase::MainFormCommand(int cmd)
{
	if(cmd==ResultCmdSaveSlaveCommand){
		ResultInspection	*Res=ResultInspectionPointerStocker->PopPointer();
		SaveSlaveCommand(Res);
		//delete	Res;
	}
	else if(cmd==ResultCmdLotChangedSlaveCommand){
		if(GetParamComm()->Mastered==true){
			ShowProcessingForm(/**/"Changing lot");
			for(int page=0;page<GetPageNumb();page++){
				ResultCmdReqLotChangedSlave	Cmd(this,"ANY","ANY",page);
				//GUICmdSendAck	Ack(this,"ANY","ANY",page);
				//Cmd.Send(page ,0,Ack);
				Cmd.Send(NULL,page,0);
				//Cmd.SendFromSlaveToMaster(GetGlobalPageFromLocal(page),0);
			}
			WaitAllAcknowledged(60*100);
			CloseProcessingForm();
		}
	}
	else if(cmd==ReportErrorFromSlaveCommand){
		if(GetParamComm()->Mastered==false){
			CmdReportError	SCmd(this,"ANY","ANY");
			ErrorCodeList	*e;
			for(;;){
				e=PopError();
				if(e==NULL){
					break;
				}
				SCmd.SetError(*e);
				delete	e;
				SCmd.SendFromSlaveToMaster(GetGlobalPageFromLocal(0),0);
			}
		}
	}
	else if(cmd==ShowCriticalErrorCommand){
		static	bool	ReEntrant=false;
		if(ReEntrant==false){
			ReEntrant=true;
			QString	S=GetAnyData()->ToString("CriticalError");
			AlertDialog		*Dlg=new AlertDialog(S);
			Dlg->exec();
			CloseOne();
			Dlg->deleteLater();
			ReEntrant=false;
		}
	}
	else if(cmd==BroadcastShowInPlayerCommand){
		if(GetMainWidget()!=NULL){
			GetMainWidget()->BroadcastShowInPlayer(GetCurrentInspectIDForDisplay());
		}
	}
}

bool	LayersBase::CreatePartialData(int globalX1 ,int globalY1 ,int globalX2, int globalY2
							,QIODevice *createdGlobalParam ,QIODevice *createdPix)
{
	bool	Ret=true;
	ParamGlobal	GParam(this);

	int	globalW=globalX2-globalX1;
	int	globalH=globalY2-globalY1;
	if(createdGlobalParam!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(GetParamGlobal()->SaveParam(&Buff)==false){
			return false;
		}
		Buff.seek(0);
		if(GParam.LoadParam(&Buff)==false){
			return false;
		}
		GParam.PageNumb=1;
		GParam.DotPerLine=globalW;
		GParam.MaxLines	 =globalH;
		GParam.TotalCameraNumb=1;
		if(GParam.SaveParam(createdGlobalParam)==false){
			return false;
		}
	}
	if(createdPix!=NULL){
		ImageBuffer		**PartialImage=NULL;
		int				LayerNumb=0;
		for(int p=0;p<GetPageNumb();p++){
			DataInPage *P=GetDrawturn(p);
			int		localX1=globalX1-P->GetOutlineOffset()->x;
			int		localY1=globalY1-P->GetOutlineOffset()->y;
			int		localX2=globalX2-P->GetOutlineOffset()->x;
			int		localY2=globalY2-P->GetOutlineOffset()->y;
			if((localX1>=P->GetDotPerLine()) || (localY1>=P->GetMaxLines()) || ((localX2<0) || (localY2<0))){
				continue;
			}
			if(localX1<0){
				localX1=0;
			}
			if(localY1<0){
				localY1=0;
			}
			if(localX2>P->GetDotPerLine()){
				localX2=P->GetDotPerLine();
			}
			if(localY2>P->GetMaxLines()){
				localY2=P->GetMaxLines();
			}
			if((localX1==localX2) || (localY1==localY2)){
				continue;
			}
			LayerNumb=GetLayerNumb(p);
			PartialImage=new ImageBuffer*[LayerNumb];
			for(int layer=0;layer<LayerNumb;layer++){
				PartialImage[layer]=new ImageBuffer();
				PartialImage[layer]->Set(0,ImageBufferOther,globalW,globalH);
			}

			GUICmdReqPartialImage	CmdReqPartialImage (this,"ANY","ANY",P->GetPage());
			GUICmdSendPartialImage	CmdSendPartialImage(this,"ANY","ANY",P->GetPage());

			CmdReqPartialImage.localX1=localX1;
			CmdReqPartialImage.localY1=localY1;
			CmdReqPartialImage.localX2=localX2;
			CmdReqPartialImage.localY2=localY2;
			CmdReqPartialImage.LayerNumb=LayerNumb;
			if(CmdReqPartialImage.Send(P->GetPage(),0,CmdSendPartialImage)==true){
				int	mx=localX1+P->GetOutlineOffset()->x-globalX1;
				int	my=localY1+P->GetOutlineOffset()->y-globalY1;
				int	localW=localX2-localX1;
				int	localH=localY2-localY1;
				for(int layer=0;layer<LayerNumb;layer++){
					for(int y=0;y<localH;y++){
						memcpy(PartialImage[layer]->GetY(my+y)+mx,CmdSendPartialImage.GetLayer(layer)->GetY(y),localW);
					}
				}
				//break;
			}
		}

		DWORD	ID=0xA55AE01F;
		int32	D=1;

		if(::Save(createdPix,ID)==false){
			Ret=false;
			goto	ErrorOut;
		}
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}
		D=globalW;
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}
		D=globalH;
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}
		D=LayerNumb;
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}

		for(int layer=0;layer<LayerNumb;layer++){
			for(int y=0;y<globalH;y++){
				BYTE    *dp=PartialImage[layer]->GetY(y);
				if(createdPix->write((const char *)dp ,globalW)!=globalW){
					Ret=false;
					goto	ErrorOut;
				}
            }
		}
		ErrorOut:;
		for(int layer=0;layer<LayerNumb;layer++){
			delete	PartialImage[layer];
		}
		delete	[]PartialImage;
	}
	return Ret;
}

void	LayersBase::CloseAll(int _ReturnCode)
{
	SetOnChanging(true);
	GSleep(1000);
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSendClose	MCmd(this,"ANY","ANY",page);
		MCmd.ReturnCode	=_ReturnCode;
		MCmd.Send(NULL,page,0);
	}
	SetReturnCode(_ReturnCode);
	OnTerminating=true;
	for(time_t t=time(NULL);time(NULL)-t<3;){
		QApplication::processEvents();
	}
}

void	LayersBase::CloseOne(int _ReturnCode)
{
	SetReturnCode(_ReturnCode);
	OnTerminating=true;
	SetOnChanging(true);
	GSleep(1000);
}


void	LayersBase::ShowProcessingForm (const QString &Title ,bool CancelMode,int MaxValue)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	//if(GetOnProcessing()!=NULL && GetParamGlobal()->ViewProcessingWindow==true){
	if(GetOnProcessing()!=NULL){
		GetOnProcessing()->setWindowTitle(Title);
		GetOnProcessing()->SetCancelMode(CancelMode);
		GetOnProcessing()->SetMax(MaxValue);
		for(int page=0;page<GetPageNumb();page++){
			GetOnProcessing()->SetValue(page,0);
		}
		GetOnProcessing()->Show();
		GetOnProcessing()->update();
		GetOnProcessing()->raise();
		//QApplication::processEvents();
		
		TmpHidingProcessingForm=false;
	}
	ProcessingReEntrant--;
}
void	LayersBase::StepProcessing(int localpage ,const QString &message)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	if(GetOnProcessing()!=NULL){
		if(GetOnProcessing()->isVisible()==true){
			if(localpage>=0){
				GetOnProcessing()->SetMessage(message);
				GetOnProcessing()->Step(localpage);
				GetOnProcessing()->update();
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					GetOnProcessing()->SetMessage(message);
					GetOnProcessing()->Step(page);
					GetOnProcessing()->update();
				}
			}
			if(GetParamComm()->Mastered==true){
				QCoreApplication::processEvents();
			}
		}
		else if(GetParamComm()->Mastered==false){
			if(localpage>=0){
				int	globalPage=GetGlobalPageFromLocal(localpage);
				GUICmdSendProcessing	MCmd(this,"ANY","ANY",globalPage);
				MCmd.SendFromSlaveToMaster(globalPage,0);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					int	globalPage=GetGlobalPageFromLocal(page);
					GUICmdSendProcessing	MCmd(this,"ANY","ANY",globalPage);
					MCmd.SendFromSlaveToMaster(globalPage,0);
				}
			}
		}
	}
	ProcessingReEntrant--;
}

void	LayersBase::SetMaxProcessing(int maxValue)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	if(GetOnProcessing()!=NULL){
		if(GetOnProcessing()->isVisible()==true){
			GetOnProcessing()->SetMax(maxValue);
			GetOnProcessing()->update();
		}
		else if(GetParamComm()->Mastered==false){
			GUICmdSendProcessing	MCmd(this,"ANY","ANY",0);
			MCmd.MaxValue	 =maxValue;
			MCmd.SendFromSlaveToMaster(0,1);
		}
	}
	ProcessingReEntrant--;
}

void	LayersBase::AddMaxProcessing(int localpage ,int maxValue)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	if(GetOnProcessing()!=NULL){
		if(GetOnProcessing()->isVisible()==true){
			GetOnProcessing()->AddMax(localpage,maxValue);
			GetOnProcessing()->update();
		}
		else if(GetParamComm()->Mastered==false){
			if(localpage>=0){
				int	globalPage=GetGlobalPageFromLocal(localpage);
				GUICmdSendProcessingAdd	MCmd(this,"ANY","ANY",globalPage);
				MCmd.MaxValue	 =maxValue;
				MCmd.SendFromSlaveToMaster(globalPage,1);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					int	globalPage=GetGlobalPageFromLocal(page);
					GUICmdSendProcessingAdd	MCmd(this,"ANY","ANY",globalPage);
					MCmd.MaxValue	 =maxValue;
					MCmd.SendFromSlaveToMaster(globalPage,1);
				}
			}
		}
	}
	ProcessingReEntrant--;
}
void	LayersBase::CloseProcessingForm(void)
{
	if(GetOnProcessing()==NULL){
		return;
	}
	GetOnProcessing()->Hide();
	TmpHidingProcessingForm=false;
}

void	LayersBase::DelayedCloseProcessingForm(int sec)
{
	if(GetOnProcessing()==NULL){
		return;
	}
	GetOnProcessing()->DelayedHide(sec);
	GetOnProcessing()->update();
	TmpHidingProcessingForm=false;
}

void	LayersBase::TmpHideProcessingForm(void)
{
	if(GetOnProcessing()==NULL){
		return;
	}
	if(GetOnProcessing()->isHidden()==false){
		GetOnProcessing()->hide();
		TmpHidingProcessingForm=true;
	}
}
	
void	LayersBase::TmpRercoverProcessingForm(void)
{
	if(TmpHidingProcessingForm==true){
		TmpHidingProcessingForm=false;
		if(GetOnProcessing()!=NULL){
			GetOnProcessing()->show();
		}
	}
}

void	LayersBase::SendAckToMaster(int localpage,int FilterdID)
{
	int	gpage=GetGlobalPageFromLocal(localpage);
	GUICmdSendAck	Cmd(this ,"ANY","ANY",0);
	Cmd.AckFilterID	=FilterdID;
	Cmd.SendFromSlaveToMaster(gpage ,0);
	SetAckFlag(localpage,FilterdID);
}
void	LayersBase::SendErrorAckToMaster(int localPage
						,int errorCode ,const QString &errorMessage ,ErrorCodeList::CautionLevel level
						,int FilterdID)
{
	int	gpage=GetGlobalPageFromLocal(localPage);
	GUICmdSendAck	Cmd(this ,"ANY","ANY",0);
	Cmd.AckFilterID	=FilterdID;
	Cmd.SetError(errorCode ,errorMessage,level);
	Cmd.SendFromSlaveToMaster(gpage ,0);
	SetAckFlag(localPage,FilterdID);
}

void	LayersBase::SetAckFlag(int localPage,int FilterdID)
{
	if((AckFlag!=NULL) && (AllocatedAckFlag!=GetPageNumb())){
		delete	[]AckFlag;
		AckFlag=NULL;
		AllocatedAckFlag=0;
	}
	if(AckFlag==NULL){
		AckFlag=new bool[GetPageNumb()];
		AllocatedAckFlag=GetPageNumb();
		for(int page=0;page<GetPageNumb();page++){
			AckFlag[page]=false;
		}
	}
	if(AckFilterID==FilterdID || AckFilterID==-1){
		AckFlag[localPage]=true;
	}
}
void	LayersBase::ClearAllAckFlag(int FilterdID)
{
	if((AckFlag!=NULL) && (AllocatedAckFlag!=GetPageNumb())){
		delete	[]AckFlag;
		AckFlag=NULL;
		AllocatedAckFlag=0;
	}
	if(AckFlag==NULL){
		AckFlag=new bool[GetPageNumb()];
		AllocatedAckFlag=GetPageNumb();
	}
	GetEntryPoint()->WaitReadyReadAll(300);
	for(int page=0;page<GetPageNumb();page++){
		AckFlag[page]=false;
	}
	AckFilterID=FilterdID;
}
bool	LayersBase::IsAllAcknowledged(void)
{
	if((AckFlag!=NULL) && (AllocatedAckFlag!=GetPageNumb())){
		delete	[]AckFlag;
		AckFlag=NULL;
		AllocatedAckFlag=0;
	}
	if(AckFlag==NULL){
		AckFlag=new bool[GetPageNumb()];
		AllocatedAckFlag=GetPageNumb();
		for(int page=0;page<GetPageNumb();page++){
			AckFlag[page]=false;
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		if(AckFlag[page]==false){
			return false;
		}
	}
	return true;
}
bool	LayersBase::WaitAllAcknowledged(int waitsecond ,bool CallProcessEvent)
{
	if(GetParamComm()->GetConnectedPCNumb()==0){
		return true;
	}
	StopCommSender=true;
	for(time_t	t=time(NULL);(time(NULL)-t)<waitsecond;){
		if(IsAllAcknowledged()==true){
			StopCommSender=false;
			return true;
		}
		if(GetOnProcessing()!=NULL){
			if(GetOnProcessing()->isVisible()==true){
				GetOnProcessing()->update();
				GetOnProcessing()->repaint();
			}
		}
		if(CallProcessEvent==true){
			QCoreApplication::processEvents ();
		}
		GetEntryPoint()->WaitReadyReadAll(300);
	}
	StopCommSender=false;
	return false;
}

DataInPage	*LayersBase::GetDrawturn(int TurnForPage)	const
{
	if(DrawPageIndex!=NULL){
		return DrawPageIndex[TurnForPage];
	}
	return GetPageData(TurnForPage);
}
void	LayersBase::SetTopInPage(DataInPage	*CurrentPage)
{
	if(DrawPageIndex==NULL){
		return;
	}
	DataInPage	*TmpTop=NULL;
	for(int page=0;page<GetPageNumb();page++){
		if(DrawPageIndex[page]->GetPage()==CurrentPage->GetPage()){
			TmpTop=DrawPageIndex[page];
			for(int i=page;i>0;i--){
				DrawPageIndex[i]=DrawPageIndex[i-1];
			}
			DrawPageIndex[0]=TmpTop;
			return;
		}
	}
}
bool	LayersBase::IsLocalCamera(void)	const
{
	if(((GetParamComm()->Mastered==true ) && (GetParamGlobal()->TotalCameraNumb!=0) && (GetParamComm()->ConnectedPCNumb==0))
	|| ((GetParamComm()->Mastered==false) && (GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0)){
		return(true);
	}
	return(false);
}
void	LayersBase::ClearExecuterState(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->InitializeState();
	}
}

void	LayersBase::SwitchImageBuff(void)
{
	for(int page=0;page<GetPageNumb();page++){
		GetPageData(page)->SwitchImageBuff();
	}
}
	

void	LayersBase::SendSettingsToSlave(void)
{
	if(GetParamComm()->Mastered==true && GetParamComm()->GetConnectedPCNumb()!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendParameters	SCmd(this,"ANY","ANY",page);
			SCmd.Initial();
			SCmd.Send(NULL,GetGlobalPageFromLocal(page),0);
		}
	}
	else
	if(GetParamComm()->Mastered==true && GetParamComm()->GetConnectedPCNumb()==0){
		if(GetResultDLLBase()!=NULL){
			for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				CopyShadowTreeParamResultDLL(L);
			}
		}
		if(GetLogicDLLBase()!=NULL){
			for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				CopyShadowTreeParamLogicDLL(L);
			}
		}
	}
}

void	LayersBase::WriteAllSettingFiles(void)
{
	if(GetParamComm()->Mastered==true){
		if(GetParamGlobal()->WriteEnableToDefaultFile()==true){
			QFile	FGeneral(CurrentPath
							+GetSeparator()+GetParamGlobal()->GetSavedFileName());
			if(FGeneral.open(QIODevice::WriteOnly)==true){
				GetParamGlobal()->SaveParam(&FGeneral);
			}
			/*
			QFile	FComm(GetParamComm()->GetSavesdFileName());
			if(FComm.open(QIODevice::WriteOnly)==true){
				GetParamComm()->SaveParam(&FComm);
			}
			*/
			if(GetResultDLLBase()!=NULL){
				for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					ResultDLLBaseRoot	*H=L->GetDLLPoint();
					QFile	FResult(CurrentPath
									+GetSeparator()+H->GetSavedFileName());
					if(FResult.open(QIODevice::WriteOnly)==true){
						H->SaveParam(&FResult);					
					}
				}
			}
			if(GetLogicDLLBase()!=NULL){		
				for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					ParamBaseForAlgorithm	*P=L->GetInstance();
					QFile	FAlgprithm(CurrentPath
									 +GetSeparator()+P->GetSavedFileName());
					if(FAlgprithm.open(QIODevice::WriteOnly)==true){
						P->SaveParam(&FAlgprithm);
					}
				}
			}
			QFile	FShareMData(CurrentPath
							+GetSeparator()+GetParamGlobal()->FileNameOfShareMasterData);
			if(FShareMData.open(QIODevice::WriteOnly)==true){
				DataOfShareMasterContainer->Save(&FShareMData);
			}
		}
	}
}
ShareMasterDestination	*LayersBase::GetDataOfShareMaster(void)	const
{	
	return DataOfShareMasterContainer->FindDestination(GetMachineID());		
}

void	LayersBase::ReadBaseSettingFiles(bool Initialized,int BootSmall)
{
	if((GetParamComm()->Mastered==true) || (Initialized==true)){
		QFile	FGeneral(CurrentPath
						+GetSeparator()+GetParamGlobal()->GetSavedFileName());
		if(FGeneral.open(QIODevice::ReadOnly)==true){
			GetParamGlobal()->LoadParam(&FGeneral);
		}
		if(BootSmall>=1){
			GetParamGlobal()->DotPerLine=100;
			GetParamGlobal()->MaxLines=100;
			GetParamGlobal()->PageNumb=BootSmall;
		}
	}
}

void	LayersBase::ReadOtherSettingFiles(bool Initialized,int BootSmall)
{
	if((GetParamComm()->Mastered==true) || (Initialized==true)){
		if(GetResultDLLBase()!=NULL){
			QString	GmFileName;
			QString	tFileName;
			for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ResultDLLBaseRoot	*H=L->GetDLLPoint();
				GmFileName=CurrentPath;
				GmFileName=GmFileName+GetSeparator();
				tFileName=H->GetSavedFileName();
				GmFileName=GmFileName+tFileName;
				QFile	FResult(GmFileName);
				if(FResult.open(QIODevice::ReadOnly)==true){
					H->LoadParam(&FResult);					
				}
			}
		}
		//ReadLogicSettingFiles(Initialized);

		QFile	FShareMData(CurrentPath
						+GetSeparator()+GetParamGlobal()->FileNameOfShareMasterData);
		if(FShareMData.open(QIODevice::ReadOnly)==true){
			DataOfShareMasterContainer->Load(&FShareMData);
		}
	}
}

void	LayersBase::ReadAllSettingFiles(bool Initialized,int BootSmall)
{
	ReadBaseSettingFiles(Initialized,BootSmall);
	ReadOtherSettingFiles(Initialized,BootSmall);
}

void	LayersBase::ReadLogicSettingFiles(bool Initialized)
{
	if((GetParamComm()->Mastered==true) || (Initialized==true)){
		if(GetLogicDLLBase()!=NULL){		
			for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ParamBaseForAlgorithm	*P=L->GetInstance();
				if(P!=NULL){
					QFile	FAlgprithm(CurrentPath
									 +GetSeparator()+P->GetSavedFileName());
					if(FAlgprithm.open(QIODevice::ReadOnly)==true){
						P->LoadParam(&FAlgprithm);
					}
				}
			}
		}
	}
}

int		LayersBase::GetCurrentStrategicNumber(void)
{	
	if(GetShadowLevel()==0){
		return CurrentStrategicNumber;
	}
	else{
		return GetTopLayersBase()->GetCurrentStrategicNumber();
	}
}

void	LayersBase::IncreaseCurrentStrategicNumber(void)
{
	if(GetShadowLevel()==0){
		MutexCurrentStrategic.lock();
		CurrentStrategicNumber++;
		if(CurrentStrategicNumber>=GetParamGlobal()->GetMaxScanStrategy()){
			CurrentStrategicNumber=0;
		}
		if(GetParamGlobal()->BufferedProcessing==true){
			CurrentStrategicQueue.Add(CurrentStrategicNumber);
		}
		MutexCurrentStrategic.unlock();
		emit	SignalChangeCurrentStrategicNumber();
	}
}

void	LayersBase::SetCurrentStrategicNumber(int n)
{
	if(GetShadowLevel()==0){
		if((0<=n) && (n<GetParamGlobal()->GetMaxScanStrategy())){
			CurrentStrategicNumber=n;
			if(GetParamGlobal()->BufferedProcessing==true){
				CurrentStrategicQueue.Add(CurrentStrategicNumber);
			}
			emit	SignalChangeCurrentStrategicNumber();
		}
	}
}

void	LayersBase::SetCurrentStrategicNumberForSeq(int n)
{	
	if(GetShadowLevel()==0){
		if(CurrentStrategicNumberForSeq!=n){
			CurrentStrategicNumberForSeq=n;
			emit	SignalChangeCurrentStrategicNumberSeq();
		}
	}
}
int		LayersBase::GetCurrentStrategicNumberForSeq(void)
{	
	if(GetShadowLevel()==0){
		return CurrentStrategicNumberForSeq;
	}
	else{
		return GetTopLayersBase()->GetCurrentStrategicNumberForSeq();
	}
}
int		LayersBase::GetCurrentStrategicNumberForCalc(void)
{	
	if(GetShadowLevel()==0){
		return CurrentStrategicNumberForCalc;
	}
	else{
		return GetTopLayersBase()->GetCurrentStrategicNumberForCalc();
	}
}

void	LayersBase::PopCurrentStrategicNumberForCalc(void)
{
	if(GetShadowLevel()==0){
		MutexCurrentStrategic.lock();
		IntClass	*c=CurrentStrategicQueue.GetFirst();
		if(c==NULL){
			if((0<=CurrentStrategicNumber) && (CurrentStrategicNumber<GetParamGlobal()->GetMaxScanStrategy())){
				CurrentStrategicNumberForCalc=CurrentStrategicNumber;
			}
		}
		else{
			if((0<=c->GetValue()) && (c->GetValue()<GetParamGlobal()->GetMaxScanStrategy())){
				CurrentStrategicNumberForCalc=c->GetValue();
			}
			CurrentStrategicQueue.RemoveList(c);
			delete	c;
		}
		MutexCurrentStrategic.unlock();
	}
}
void	LayersBase::ClearCurrentStrategicNumberForCalc(void)
{
	MutexCurrentStrategic.lock();
	CurrentStrategicQueue.RemoveAll();
	MutexCurrentStrategic.unlock();
}

void	LayersBase::ForceStrategicNumber(int n)
{
	MutexCurrentStrategic.lock();
	CurrentStrategicQueue.RemoveAll();
	if((0<=n) && (n<GetParamGlobal()->GetMaxScanStrategy())){
		CurrentStrategicNumber			=n;
		CurrentStrategicNumberForCalc	=n;
	}
	CurrentStrategicNumberForSeq	=n;
	MutexCurrentStrategic.unlock();

	int CPoints[10];
	GetCalcPoint(CPoints);

	if(GetParamComm()->Mastered==true && IsLocalCamera()==false){
		for(int page=0;page<GetPageNumb();page++){
			int	globalpage=GetGlobalPageFromLocal(page);
			GUICmdForceStrategicNumber	SCmd(this,"ANY","ANY",globalpage);
			SCmd.StrategicNumber	=n;
			SCmd.CPoints[0]=CPoints[0];
			SCmd.CPoints[1]=CPoints[1];
			SCmd.CPoints[2]=CPoints[2];

			SCmd.Send(NULL,globalpage,0);
		}
	}
	emit	SignalChangeCurrentStrategicNumber();
	emit	SignalChangeCurrentStrategicNumberSeq();
}

bool	LayersBase::SQLGetMachineInfo(int MachineID 
									 ,QString &NetID
									 ,QString &Name
									 ,QString &Version
									 ,QString &Remark)
{
	if(GetDatabaseLoader() && GetDatabaseLoader()->G_GetMachineInfo!=NULL){
		if(GetDatabaseLoader()->G_GetMachineInfo(GetDatabase()
												,MachineID
												,NetID 
												,Name 
												,Version
												,Remark)==true){
			return true;
		}
	}
	return false;
}

bool	LayersBase::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	if(GetAlgoDLLContPointer()!=NULL){		
		for(AlgorithmDLLList *L=GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckSystemVersion(Str)==false){
				Ret=false;
			}
		}
	}
	if(GetResultDLLBase()!=NULL){
		for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckSystemVersion(Str)==false){
				Ret=false;
			}
		}
	}
	for(ArrangementDLLClass *a=GetArrangementDLLStock()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetLightBase()!=NULL){
		if(GetLightBase()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetFilterBank()!=NULL){
		if(GetFilterBank()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetGeneralStocker()!=NULL){
		if(GetGeneralStocker()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetPrinterClassPackData()!=NULL){
		if(GetPrinterClassPackData()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetResultAnalizerDLLContainer()!=NULL){
		if(GetResultAnalizerDLLContainer()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

void	LayersBase::ExecuteLogoInGUIForm(GUIFormBase *W ,const QString &dllroot ,const QString &dllname)
{
	GetLogoStockerInstance()->ExecuteInGUIForm(W ,dllroot ,dllname);
}
	
void	LayersBase::ExecuteLogoInQWidget(QWidget *W ,const char *_typename ,const QString &dllroot ,const QString &dllname)
{
	GetLogoStockerInstance()->ExecuteInQWidget(W ,_typename ,dllroot ,dllname);
}

void	LayersBase::MessageSocketError(IntList &ErrorPages)
{
	QString	S=QString("Socket error!!");
	for(IntClass *s=ErrorPages.GetFirst();s!=NULL;s=s->GetNext()){
		S=S+QString("  Page:")+QString::number(s->GetValue());
	}
	CloseProcessingForm();
	GetAnyData()->Set("CriticalError",S);
	emit	SignalMainFormCommand(ShowCriticalErrorCommand);
}

void	LayersBase::PushCapturedPageLayer(PageAndLayerFlagListContainer &CurrentCapturedPageLayerList)
{
	MutexCapturedPageLayerList.lock();
	CapturedPageLayerList+=CurrentCapturedPageLayerList;
	MutexCapturedPageLayerList.unlock();
}
int		LayersBase::GetTopPageInCapturedPageLayer(void)
{
	int	RetPage= -1;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		RetPage=CapturedPageLayerList.GetFirst()->Page;
	}
	MutexCapturedPageLayerList.unlock();
	return RetPage;
}
int		LayersBase::GetTopPageInCapturedPageLayer(bool DoneFlag)
{
	int	RetPage= -1;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		RetPage=CapturedPageLayerList.GetFirst()->Page;
		CapturedPageLayerList.GetFirst()->Done=DoneFlag;
	}
	MutexCapturedPageLayerList.unlock();
	return RetPage;
}
bool	LayersBase::GetTopFlagInCaptured(void)
{
	bool	DoneFlag=false;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		DoneFlag=CapturedPageLayerList.GetFirst()->Done;
	}
	MutexCapturedPageLayerList.unlock();
	return DoneFlag;
}
int		LayersBase::GetTopLayerInCapturedPageLayer(void)
{
	int	RetLayer= -1;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		RetLayer=CapturedPageLayerList.GetFirst()->Layer;
	}
	MutexCapturedPageLayerList.unlock();
	return RetLayer;
}

void	LayersBase::ClearTopInCapturedPageLayer(void)
{
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		PageAndLayerFlagList *L=CapturedPageLayerList.GetFirst();
		CapturedPageLayerList.RemoveList(L);
		delete L;
	}
	MutexCapturedPageLayerList.unlock();
}


bool	LayersBase::IsEdited(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return false;
	}
	ReEntrant=true;

	for(int phase=0;phase<AllocatedPhaseNumb && phase<GetPhaseNumb();phase++){
		if(GetPageDataPhase(phase)->IsEdited()==true){
			ReEntrant=false;
			return true;
		}
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqEdited		ReqCmd(this ,"ANY","ANY",page);
			GUICmdSendEdited	SendCmd(this ,"ANY","ANY",page);
			ReqCmd.Send(page,0,SendCmd);
			if(SendCmd.Edited==true){
				ReEntrant=false;
				return true;
			}
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsEdited()==true){
			ReEntrant=false;
			return true;
		}
	}

	for(int i=0;i<GetShadowChildrenCount();i++){
		if(GetShadowChildren(i)->GetTreeLayersBase()->IsEdited()==true){
			ReEntrant=false;
			return true;
		}
	}

	ReEntrant=false;

	return false;
}

bool	LayersBase::IsCalcDone(void)
{
	for(int page=0;page<GetPageNumb();page++){
		if(GetPageData(page)->IsCalcDone()==false){
			return false;
		}
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCalcDone	ReqCmd(this ,"ANY","ANY",page);
			GUICmdSendCalcDone	SendCmd(this ,"ANY","ANY",page);
			ReqCmd.Send(page,0,SendCmd);
			if(SendCmd.CalcDone==false){
				return false;
			}
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}


void	LayersBase::SetEdited(bool edited)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	for(int phase=0;phase<AllocatedPhaseNumb && phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->SetEdited(edited);
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSetEdited		ReqCmd(this ,"ANY","ANY",page);
			ReqCmd.Edited=edited;
			ReqCmd.Send(NULL,page,0);
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->SetEdited(edited);
	}
	ReEntrant=false;
}
void	LayersBase::SetCalcDone(bool calcdone)
{
	for(int page=0;page<GetPageNumb();page++){
		GetPageData(page)->SetCalcDone(calcdone);
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSetCalcDone		ReqCmd(this ,"ANY","ANY",page);
			ReqCmd.CalcDone=calcdone;
			ReqCmd.Send(NULL,page,0);
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->SetCalcDone(calcdone);
	}
}

void	LayersBase::RemoveStockedResult(void)
{
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			CmdReqRemoveStockedResult	RCmd(this ,"ANY","ANY",page);
			RCmd.Send(NULL,page,0);
		}
	}

	ResultInspection	*Ref;
	for(;;){
		Ref=GetResultThread()->NeedDeleteResult();
		if(Ref==NULL){
			break;
		}
		GetLogicDLLBase()->ExecuteRemoveResult(GetMasterCode()
											,LotInfo//GetLotAutoCount()
											,Ref->GetInspectionID()
											,Ref);
	}
}

int		LayersBase::GetErrorCount(void)
{
	ErrorMutex.lock();
	int	ret=GetErrorContainer()->GetNumber();
	ErrorMutex.unlock();
	return ret;
}

void	LayersBase::ClearErrorCount(void)
{
	ErrorMutex.lock();
	GetErrorContainer()->RemoveAll();
	ErrorMutex.unlock();
}

bool	LayersBase::GetError(int index ,ErrorCodeList &Ret)
{
	if((0<=index) && (index<GetErrorContainer()->GetNumber())){
		ErrorMutex.lock();
		ErrorCodeList	*r=GetErrorContainer()->GetItem(index);
		Ret= *r;
		ErrorMutex.unlock();
		return true;
	}
	return false;
}

ErrorCodeList	*LayersBase::PopError(void)
{
	ErrorMutex.lock();
	ErrorCodeList	*r=GetErrorContainer()->GetFirst();
	GetErrorContainer()->RemoveList(r);
	ErrorMutex.unlock();
	return r;
}

void	LayersBase::SendErrorToMaster(int errorCode , const QString &errorMessage ,ErrorCodeList::CautionLevel level)
{
	ErrorCodeList *e=new ErrorCodeList(level,errorMessage ,errorCode);
	ErrorMutex.lock();
	GetErrorContainer()->AppendList(e);
	ErrorMutex.unlock();

	emit	SignalMainFormCommand(ReportErrorFromSlaveCommand);
}

void	LayersBase::BroadcastInspectionNumber(void)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSendInspectionNumber	Cmd(this,"ANY","ANY",page);
		Cmd.InspectionNumber=GetInspectionNumber();
		Cmd.Send(NULL,page,0);
	}
}

bool	LayersBase::IsDoneCompressed(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			if(GetPageData(page)->IsDoneCompressed()==false){
				return false;
			}
		}
	}
	else{
		IntList PageList;
		GetParamGlobal()->GetStrategyPage(GetCurrentStrategicNumber(),PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			if(GetPageData(page)->IsDoneCompressed()==false){
				return false;
			}
		}
	}
	return true;
}

bool	LayersBase::NeedWaitingForCompress(void)
{
	if(GetParamGlobal()->ModePhaseOutputResult==-3){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
			if(Ph->GetCountOfCompressing()>=GetParamGlobal()->MaxStackCompressCount){
				return true;
			}
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
			if(Ph->GetCountOfCompressing()>=GetParamGlobal()->MaxStackCompressCount){
				return true;
			}
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-1){
		IntList PhaseCodes;
		GetCurrentPhaseFromScanPhase(PhaseCodes);
		for(IntClass *c=PhaseCodes.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
			if(Ph->GetCountOfCompressing()>=GetParamGlobal()->MaxStackCompressCount){
				return true;
			}
		}
	}
	else
	if(0<=GetParamGlobal()->ModePhaseOutputResult){
		int	phase=GetParamGlobal()->ModePhaseOutputResult;
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->GetCountOfCompressing()>=GetParamGlobal()->MaxStackCompressCount){
			return true;
		}
	}
	return false;
}

int			LayersBase::SetCurrentPhase(int phase)
{
	static	bool	ReEntrantSetCurrentPhase=false;

	bool	PhaseChanged=false;
	if(ReEntrantSetCurrentPhase==false){
		ReEntrantSetCurrentPhase=true;
		if(AllocatedPhaseNumb>phase){
			if(CurrentPhase!=phase){
				PhaseChanged=true;
			}
			PageData=PageDataPhase[phase];
			CurrentPhase=phase;
			if(GetParamComm()->Mastered==true && GetParamComm()->GetConnectedPCNumb()!=0){
				for(int page=0;page<GetPageNumb();page++){
					GUICmdReqSetCurrentPhase	Cmd(this,"ANY","ANY",page);
					Cmd.CurrentPhase=GetCurrentPhase();
					Cmd.Send(NULL,page,0);
				}
			}
		}
	}
	ReEntrantSetCurrentPhase=false;

	if(PhaseChanged==true){
		emit	SignalChangeCurrentPhase();
	}
	return CurrentPhase;
}

QString	LayersBase::GetFilterDefFileName(void)	const
{
	QString	Path=GetUserPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	QString	FileName=Path+GetParamGlobal()->FilterDefFile;
	return FileName;
}
bool	LayersBase::LoadFilterDef(void)
{
	QString	FileName=GetFilterDefFileName();
	QFile	f(FileName);
	if(f.open(QIODevice::ReadOnly)==true){
		return LoadFilterDef(&f);
	}
	return false;
}
bool	LayersBase::LoadFilterDef(QIODevice *f)
{
	int32	Ph;
	if(::Load(f,Ph)==false){
		return false;
	}
	for(int phase=0;phase<Ph && phase<GetPhaseNumb();phase++){
		if(PageDataPhase[phase]->LoadFilterContainer(f)==false){
			return false;
		}
		if(PageDataPhase[phase]->LoadPhaseSource(f)==false){
			return false;
		}
	}
	return true;
}

bool	LayersBase::SaveFilterDef(void)
{
	QString	Path=GetUserPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	QString	FileName=Path+GetParamGlobal()->FilterDefFile;
	QFile	f(FileName);
	if(f.open(QIODevice::WriteOnly)==true){
		return SaveFilterDef(&f);
	}
	return false;
}

bool	LayersBase::SaveFilterDef(QIODevice *f)
{
	int32	Ph=GetPhaseNumb();
	if(::Save(f,Ph)==false){
		return false;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(PageDataPhase[phase]->SaveFilterContainer(f)==false){
			return false;
		}
		if(PageDataPhase[phase]->SavePhaseSource(f)==false){
			return false;
		}
	}
	return true;
}
bool	LayersBase::ExecuteFilterBeforeScan(void)
{
	bool	Ret=true;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->ExecuteFilterBeforeScan(this)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	LayersBase::ExecuteFilteringMaster()
{
	if(GetEntryPoint()->NoCamDevice==true){
		return true;
	}
	bool	Ret=true;
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->GetFromSourcePhase()==GetCurrentPhase()){
			P->CopyImageMasterFrom(this,CP);
		}
		if(P->ExecuteFilteringMaster(this)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	LayersBase::ExecuteFilteringTarget()
{
	if(GetEntryPoint()->NoCamDevice==true){
		return true;
	}
	bool	Ret=true;
	if(EnableFilter==true){
		StartTimeExecuteFilter=QTime::currentTime ();
		PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
		{
			IntList PhaseCodes;
 			GetCurrentPhaseFromScanPhase(PhaseCodes);
			for(int phase=0;phase<GetPhaseNumb();phase++){
				bool	NoChange=false;
				for(IntClass *d=PhaseCodes.GetFirst();d!=NULL;d=d->GetNext()){
					if(phase==d->GetValue()){
						NoChange=true;
						break;
					}
				}
				if(NoChange==true){
					PageDataInOnePhase	*P=GetPageDataPhase(phase);
					if(P->GetFromSourcePhase()==GetCurrentPhase() && CP->GetPhaseCode()!=P->GetPhaseCode()){
						P->CopyImageTargetFrom(this,CP);
					}
				}
			}
		}
		{
			IntList PhaseCodes;
 			GetCurrentPhaseFromScanPhase(PhaseCodes);
			for(int phase=0;phase<GetPhaseNumb();phase++){
				bool	NoChange=false;
				for(IntClass *d=PhaseCodes.GetFirst();d!=NULL;d=d->GetNext()){
					if(phase==d->GetValue()){
						NoChange=true;
						break;
					}
				}
				if(NoChange==true){
					PageDataInOnePhase	*P=GetPageDataPhase(phase);
					if(P->ExecuteFilteringTarget(this)==false){
						Ret=false;
					}
				}
			}
		}
		MilisecExecuteFilter=StartTimeExecuteFilter.msecsTo (QTime::currentTime());
	}
	return Ret;
}

void	LayersBase::RemoveResultFromOldest(int n)
{
	ResultInspectionForStock	*r=GetResultThread()->RemoveResultFromOldest(n);
	if(r!=NULL){
		GetResultHistryData()->RemoveResult(r->GetStartTimeForInspection());
		emit	SignalMainFormCommand(BroadcastShowInPlayerCommand);
	}
}

void	LayersBase::SetStatusModes(GUIFormBase *f,const QStringList &modes)
{
	//if(GetStatusController()!=NULL){
	//	GetStatusController()->SetStatusModes(f,modes);
	//}
}
void	LayersBase::SetStatusModes(GUIFormBase *f,const QString &mode)
{
	QStringList	L;
	L.append(mode);
	SetStatusModes(f,L);
}

bool	LayersBase::DeliverMakeUncoveredArea(void)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdMakeUncoveredMap	RCmd(this,/**/"ANY",/**/"ANY",page);
		if(RCmd.SendOnly(page,0)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::GetAlignmentForProcessing(int Page ,AlignmentPacketBase &Packet)
{
	LogicDLL	*L=GetLogicDLLBase()->SearchByAlgorithmType(AlgorithmBit_TypeAlignment);
	if(L==NULL){
		return;
	}
	L->GetAlignmentForProcessing(Page,Packet);
}

void	LayersBase::DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
							,bool Mastered
							,const QColor &LColor
							,int OffsetX ,int OffsetY)
{
	for(int page=0;page<GetPageNumb();page++){
		XYData	*xy=GetPageData(page)->GetOutlineOffset();
		GetPageData(page)->DrawImage(Img, movx ,movy ,ZoomRate
							,Mastered
							,LColor
							,OffsetX+xy->x,OffsetY+xy->y);
	}
}
void	LayersBase::SendToOtherPhaseMaster(void)
{
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(phase==GetCurrentPhase()){
			continue;
		}
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->GetFromSourcePhase()==GetCurrentPhase()){
			P->CopyImageMasterFrom(this,CP);
			P->ExecuteFilteringMaster(this);
		}
	}
}
void	LayersBase::SendToOtherPhaseTarget(void)
{
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(phase==GetCurrentPhase()){
			continue;
		}
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->GetFromSourcePhase()==GetCurrentPhase()){
			P->CopyImageTargetFrom(this,CP);
			P->ExecuteFilteringTarget(this);
		}
	}
}

int32	LayersBase::GetIDForUndo(void)
{
	UndoTopic	*L=UndoDataStocker.GetCurrentTopic();
	if(L!=NULL){
		return L->GetIDForUndo();
	}
	return -1;
}

void	LayersBase::AddUndo(UndoTopic *a)
{
	UndoDataStocker.AppendList(a);
	UndoDataStocker.IDBase++;
}

void	LayersBase::AddRedo(UndoTopic *a)
{
	RedoDataStocker.AppendList(a);
	RedoDataStocker.IDBase++;
}

bool	LayersBase::ExecuteUndoInMaster(void)
{
	UndoTopic	*L=GetLayersBase()->GetUndoStocker().UndoInMaster();
	if(L!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqUndo	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
			Cmd.IDForUndo=L->GetIDForUndo();
			if(Cmd.SendOnly(GlobalPage,0)==false){
				return false;
			}
		}
	}
	return true;
}

bool	LayersBase::ExecuteRedoInMaster(void)
{
	UndoTopic	*L=GetLayersBase()->GetUndoStocker().RedoInMaster();
	if(L!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRedo	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY" ,GlobalPage);
			Cmd.IDForUndo=L->GetIDForUndo();
			if(Cmd.SendOnly(GlobalPage,0)==false){
				return false;
			}
		}
	}
	return true;
}

void	LayersBase::TestLoadDLL(const QString &FileName)
{
	if(IsMainThread()==true){
		if(InstShowLoadingDLLForm==NULL){
			InstShowLoadingDLLForm=new ShowLoadingDLLForm(this,NULL);
			if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
				InstShowLoadingDLLForm->show();
			}
		}
		InstShowLoadingDLLForm->TestAdd(FileName);
		if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
			InstShowLoadingDLLForm->show();
		}
		QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents | QEventLoop::ExcludeSocketNotifiers);
		//InstShowLoadingDLLForm->update();
	}
}
void	LayersBase::InformToLoadDLL(const QString &FileName)
{
	if(IsMainThread()==true){
		if(InstShowLoadingDLLForm==NULL){
			InstShowLoadingDLLForm=new ShowLoadingDLLForm(this,NULL);
			if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
				InstShowLoadingDLLForm->show();
			}
		}
		InstShowLoadingDLLForm->Add(FileName);
		if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
			InstShowLoadingDLLForm->show();
			InstShowLoadingDLLForm->update();
		}
		//QCoreApplication::processEvents();
	}
}

void	LayersBase::CloseInformed(void)
{
	if(InstShowLoadingDLLForm!=NULL){
		InstShowLoadingDLLForm->close();
		InstShowLoadingDLLForm->deleteLater();
		InstShowLoadingDLLForm=NULL;
	}
}

bool	LayersBase::IsMainThread(void)
{
	if(MainThread==QThread::currentThreadId()){
		return true;
	}
	return false;
}
AlgorithmItemRoot	*LayersBase::FindItem(const AlgorithmItemIndex &Index)	const
{
	if(Index.GetShadowLevel()==GetShadowLevel()
	&& Index.GetShadowNumber()==GetShadowNumber()){
		AlgorithmBase	*A=GetAlgorithmBase(Index.GetDLLRoot() ,Index.GetDLLName());
		if(A==NULL){
			return NULL;
		}
		return A->FindItem(Index);
	}
	LayersBase	*Base=GetShadowTree(Index.GetShadowLevel() ,Index.GetShadowNumber());
	if(Base!=NULL){
		return Base->FindItem(Index);
	}
	return NULL;
}

void	LayersBase::CenterizeDialog(QWidget *f)
{
	QWidget	*s=GetMainWidget();
	f->setParent(NULL);
	f->move( s->geometry().x()+(s->width ()-f->width ())/2 
			,s->geometry().y()+(s->height()-f->height())/2);
}

void	LayersBase::ClearHistgramData(void)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=L->GetInstance();
		if(ABase!=NULL){
			ABase->ClearHistgram();
		}
	}
}
bool	LayersBase::SaveHistgram(QIODevice *f)
{
	int32	N=GetLogicDLLBase()->GetCount();
	if(::Save(f,N)==false){
		return false;
	}

	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=L->GetInstance();
		QString	DLLRoot;
		QString	DLLName;
		ABase->GetAlgorithmRootName(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		if(ABase->SaveHistgram(f)==false){
			return false;
		}
	}
	return true;
}
	
bool	LayersBase::LoadHistgram(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		QString	DLLRoot;
		QString	DLLName;
		if(::Load(f,DLLRoot)==false){
			return false;
		}
		if(::Load(f,DLLName)==false){
			return false;
		}
		AlgorithmBase	*ABase=GetAlgorithmBase(DLLRoot,DLLName);
		if(ABase==NULL){
			return false;
		}
		if(ABase->LoadHistgram(f)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::LoopOnIdle(void)
{
	if(GetLogicDLLBase()!=NULL){
		for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*ABase=L->GetInstance();
			if(ABase!=NULL){
				ABase->LoopOnIdle();
			}
		}
	}
	if(GetLightBase()!=NULL){
		GetLightBase()->LoopOnIdle();
	}
}
int		LayersBase::GetCountOfCompressing(void)
{
	int	Count=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		Count	+=	P->GetCountOfCompressing();
	}
	return Count;
}

void	LayersBase::SwapImageOutOfBuffer(int ImageDataType)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->SwapImageOutOfBuffer(ImageDataType);
	}
}
void	LayersBase::SwapImageInToBuffer(int ImageDataType)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->SwapImageInToBuffer(ImageDataType);
	}
}


void	LayersBase::InstallOperationLog(QObject *window)
{
	if(GetOperationLoggerData()!=NULL){
		GetOperationLoggerData()->Install(window);
	}
}

bool	EntryPointBase::IsMasterPC(void)
{
	return GetLayersBase()->GetParamComm()->Mastered;
}
bool	LayersBase::LoadShrinkingPackContainer(void)
{
	if(!ShrinkingPackContainerInstance){
		ShrinkingPackContainerInstance	=std::make_shared<ShrinkingPackContainer>();
		return ShrinkingPackContainerInstance->LoadDefault();
	}
	return true;
}
bool	LayersBase::ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(Numb==0){
		return true;
	}
	if(abs(Numb)>GetParamGlobal()->MaxFatThin){
		return false;
	}
	LoadShrinkingPackContainer();
	if(Numb>0){
		return ShrinkingPackContainerInstance->ThinAreaN(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,Numb
					,ForceZone
					,EnableThread);
	}
	else{
		return ShrinkingPackContainerInstance->FatAreaN(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,-Numb
					,ForceZone
					,EnableThread);
	}
}
bool   LayersBase::FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if (Numb==0) {
		return true;
	}
	if(abs(Numb)>GetParamGlobal()->MaxFatThin){
		return false;
	}
	LoadShrinkingPackContainer();
	if(Numb>0){
		return ShrinkingPackContainerInstance->FatAreaN(bmpdata
						,bitoperation
						,xbyte ,YLenDot 
						,Numb
						,ForceZone
						,EnableThread);
	}
	else{
		return ShrinkingPackContainerInstance->ThinAreaN(bmpdata
						,bitoperation
						,xbyte ,YLenDot 
						,-Numb
						,ForceZone
						,EnableThread);
	}
}

bool	LayersBase::ThinArea1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,FlexArea *ForceZone
				,bool EnableThread)
{
	LoadShrinkingPackContainer();

	BYTE	**TmpMap=MakeMatrixBuff(xbyte,YLenDot);
	MatrixBuffCopy(TmpMap				,xbyte,YLenDot
				,(const BYTE **)bmpdata ,xbyte,YLenDot);
	ShrinkingPackContainerInstance->ThinAreaN(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,1
					,ForceZone
					,EnableThread);
	BYTE	**DstMap=MakeMatrixBuff(xbyte,YLenDot);
	MatrixBuffCopy(DstMap				,xbyte,YLenDot
				,(const BYTE **)bmpdata ,xbyte,YLenDot);

	int	XLen=xbyte*8;
	int	LoopY=YLenDot-2;

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<LoopY;i++){
			int	y=i+1;
			BYTE	*s =TmpMap[y];
			BYTE	*s0=bmpdata[y-1];
			BYTE	*st=bmpdata[y];
			BYTE	*s1=bmpdata[y+1];
			BYTE	*d =DstMap[y];
			for(int x=1;x<XLen-1;x++){
				if(GetBmpBitOnY(s,x)!=0 && GetBmpBitOnY(st,x)==0){
					BYTE	K=((GetBmpBitOnY(s0,x-1)!=0)?0x80:0)
							| ((GetBmpBitOnY(s0,x  )!=0)?0x40:0)
							| ((GetBmpBitOnY(s0,x+1)!=0)?0x20:0)
							| ((GetBmpBitOnY(st,x-1)!=0)?0x10:0)
							| ((GetBmpBitOnY(st,x+1)!=0)?0x08:0)
							| ((GetBmpBitOnY(s1,x-1)!=0)?0x04:0)
							| ((GetBmpBitOnY(s1,x  )!=0)?0x02:0)
							| ((GetBmpBitOnY(s1,x+1)!=0)?0x01:0);
					if(K==0
					|| ((K&0b11100000)!=0 && (K&0b00011000)==0 && (K&0b00000111)!=0)
					|| ((K&0b10010100)!=0 && (K&0b01000010)==0 && (K&0b00101001)!=0)){
						if((K!=0b10000100) && (K!=0b00100001) && (K!=0b10100000) && (K!=0b00000101)){
							SetBmpBitOnY1(d,x);
						}
					}
				}
			}
		}
	}
	MatrixBuffCopy(bmpdata				,xbyte,YLenDot
				,(const BYTE **)DstMap	,xbyte,YLenDot);

	DeleteMatrixBuff(TmpMap,YLenDot);
	DeleteMatrixBuff(DstMap,YLenDot);
	return true;
}
void	LayersBase::SetLibFolderID(int libFolderID ,int originalLibFolder ,bool TransferToSlave)
{	
	CurrentLibFolderID=libFolderID;	
	if(TransferToSlave==true && GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSetLibFolderID	RCmd(this,"ANY","ANY",page);
			RCmd.LibFolderID		=libFolderID;
			RCmd.originalLibFolder	=originalLibFolder;
			RCmd.Send(NULL,page,0);
		}
	}
}

QString		LayersBase::GetLibFolderName(int libFolderID)	const
{
	if(GetDatabaseLoader() && GetDatabaseLoader()->S_LibFolderFindData!=NULL){
		QString FolderName;
		int		ParentID;
		int		NumberInFolder;
		if(GetDatabaseLoader()->S_LibFolderFindData(GetDatabase(),libFolderID ,FolderName ,ParentID ,NumberInFolder)==true){
			return FolderName;
		}
	}
	return /**/"";
}
bool	LayersBase::ScanChangedInSlave(void)
{
	ChangedAlgo.ChangedPreAlignment		=false;
	ChangedAlgo.ChangedAlignment		=false;
	ChangedAlgo.ChangedPreProcessing	=false;
	ChangedAlgo.ChangedProcessing		=false;
	ChangedAlgo.ChangedProcessingRevived=false;
	ChangedAlgo.ChangedPostProcessing	=false;
	ChangedAlgo.ChangedNoProcessing		=false;
	ChangedAlgo.ChangedPieceProcessing	=false;
	ChangedAlgo.ChangedPreScanning		=false;
	ChangedAlgo.ChangedScanning			=false;
	ChangedAlgo.ChangedPostScanning		=false;
	ChangedAlgo.ChangedMatchAlignment	=false;
	ChangedAlgo.ChangedManageResult		=false;
	ChangedAlgo.ChangedMasking			=false;
	ChangedAlgo.ChangedDynamicMasking	=false;
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqChangedAlgo	RCmd(this,"ANY","ANY",page);
			GUICmdAckChangedAlgo	ACmd(this,"ANY","ANY",page);
			if(RCmd.Send(page,0,ACmd)==true){
				if(ACmd.ChangedAlgo.ChangedPreAlignment==true)
					ChangedAlgo.ChangedPreAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedAlignment==true)
					ChangedAlgo.ChangedAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedPreAlignment==true)
					ChangedAlgo.ChangedPreAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedPreProcessing==true)
					ChangedAlgo.ChangedPreProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedProcessing==true)
					ChangedAlgo.ChangedProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedProcessingRevived==true)
					ChangedAlgo.ChangedProcessingRevived	=true;

				if(ACmd.ChangedAlgo.ChangedPostProcessing==true)
					ChangedAlgo.ChangedPostProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedNoProcessing==true)
					ChangedAlgo.ChangedNoProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedPieceProcessing==true)
					ChangedAlgo.ChangedPieceProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedPreScanning==true)
					ChangedAlgo.ChangedPreScanning	=true;

				if(ACmd.ChangedAlgo.ChangedScanning==true)
					ChangedAlgo.ChangedScanning	=true;

				if(ACmd.ChangedAlgo.ChangedPostScanning==true)
					ChangedAlgo.ChangedPostScanning	=true;

				if(ACmd.ChangedAlgo.ChangedMatchAlignment==true)
					ChangedAlgo.ChangedMatchAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedMatchAlignment==true)
					ChangedAlgo.ChangedMatchAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedManageResult==true)
					ChangedAlgo.ChangedManageResult	=true;

				if(ACmd.ChangedAlgo.ChangedMasking==true)
					ChangedAlgo.ChangedMasking	=true;

				if(ACmd.ChangedAlgo.ChangedDynamicMasking==true)
					ChangedAlgo.ChangedDynamicMasking	=true;
			}
			else{
				return false;
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			GUICmdDeliverChangedAlgo	DCmd(this,"ANY","ANY",page);
			DCmd.ChangedAlgo	=ChangedAlgo;
			DCmd.Send(NULL,page,0);
		}
	}
	return true;
}
bool	LayersBase::IsChanged(int AlgorithmBit_Type)
{
	bool	Ret=false;
	if((AlgorithmBit_Type & AlgorithmBit_TypePreAlignment		)!=0)	Ret=(ChangedAlgo.ChangedPreAlignment		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeAlignment			)!=0)	Ret=(ChangedAlgo.ChangedAlignment			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePreProcessing		)!=0)	Ret=(ChangedAlgo.ChangedPreProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeProcessing			)!=0)	Ret=(ChangedAlgo.ChangedProcessing			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeProcessingRevived	)!=0)	Ret=(ChangedAlgo.ChangedProcessingRevived	==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePostProcessing		)!=0)	Ret=(ChangedAlgo.ChangedPostProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeNoProcessing		)!=0)	Ret=(ChangedAlgo.ChangedNoProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePieceProcessing	)!=0)	Ret=(ChangedAlgo.ChangedPieceProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePreScanning		)!=0)	Ret=(ChangedAlgo.ChangedPreScanning			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeScanning			)!=0)	Ret=(ChangedAlgo.ChangedScanning			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePostScanning		)!=0)	Ret=(ChangedAlgo.ChangedPostScanning		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeMatchAlignment		)!=0)	Ret=(ChangedAlgo.ChangedMatchAlignment		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeManageResult		)!=0)	Ret=(ChangedAlgo.ChangedManageResult		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeMasking			)!=0)	Ret=(ChangedAlgo.ChangedMasking				==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeDynamicMasking		)!=0)	Ret=(ChangedAlgo.ChangedDynamicMasking		==true)?true:Ret;

	return Ret;
}
void	LayersBase::SetAllModeLoadSaveInPlayer(bool b)
{
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->SetModeLoadSaveInPlayer(b);
		}
	}
}

LensWindowForm	*LayersBase::ShowLensWindow(bool ON ,const QString &WindowTitle)
{
	if(ON==true){
		if(LensWindow==NULL){
			LensWindow=new LensWindowForm(this);
		}
		LensWindow->setWindowTitle(WindowTitle);
		LensWindow->show();
	}
	else{
		if(LensWindow!=NULL){
			LensWindow->hide();
		}
	}
	return LensWindow;
}
LensWindowForm	*LayersBase::ShowLensWindow(void)
{
	if(LensWindow==NULL){
		LensWindow=new LensWindowForm(this);
	}
	LensWindow->show();
	return LensWindow;
}
bool	LayersBase::IsShowingLensWindow(void)
{
	if(LensWindow!=NULL && LensWindow->isHidden()==false){
		return true;
	}
	return false;
}

void	LayersBase::CopyTargetToTransposition(void)
{
	if(GetParamGlobal()->CommonTargetBetweenPhases==false){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PageDataInOnePhase	*P=GetPageDataPhase(phase);
			P->CopyTargetToTransposition();
		}
	}
	else{
		PageDataInOnePhase	*P=GetPageDataPhase(0);
		P->CopyTargetToTransposition();
	}
}

LensWindowForm	*LayersBase::ShowLens(DisplayImage *_TargetPanel ,int GlobalX ,int GlobalY)
{
	if(LensWindow!=NULL){
		LensWindow->ShowLens(_TargetPanel ,GlobalX ,GlobalY , _TargetPanel->GetDisplayType());
	}
	return LensWindow;
}

void	LayersBase::SetZoneWindow(GUIFormBase *w)
{
	if(ZoneWindow!=NULL){
		delete	ZoneWindow;
		ZoneWindow=NULL;
	}
	QWidget	*P=w->parentWidget();
	if(P!=NULL){
		ZoneWindow=new ZoneWindowForEdit();
		//w->setParent(NULL);
		ZoneWindow->setParent(P);
		//w->setParent(P);
		ZoneWindow->stackUnder(w);
		//w->move(x1,y1);
		//w->resize(x2-x1+1,y2-y1+1);
		ZoneWindow->show();
		CurrentZoneWindowComponent	=w;
		SetMoveZoneWindow(w);
	}
}
void	LayersBase::SetMoveZoneWindow(GUIFormBase *w)
{
	if(ZoneWindow!=NULL && w!=NULL && w==CurrentZoneWindowComponent){
		ZoneWindow->move(w->geometry().left()-2,w->geometry().top()-2);
		ZoneWindow->resize(w->width()+4,w->height()+4);
		ZoneWindow->update();
	}
}

void	LayersBase::DeliverResultAnalizerData(void)
{
	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	GetResultAnalizerItemBaseContainer()->Save(&Buff);

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSendResultAnalizerData	RCmd(this,/**/"ANY",/**/"ANY",globalPage);
		RCmd.Data	=Buff.buffer();
		RCmd.Send(NULL,globalPage,0);
	}
}

QString	LayersBase::GetLibTypeName(int LibType)	const
{
	if(GetLibType()!=NULL){
		return GetLibType()->FindLibraryTypeName(LibType);
	}
	return /**/"";
}

QString	LayersBase::GetLibraryName(int LibType ,int LibID)	const
{
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->G_GetLibraryName2(*GetDataBase(),LibType ,LibID);
	}
	return /**/"";
}

void	LayersBase::SetProcessDone(bool b)
{
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->SetProcessDone(b);
		}
	}
}
void	LayersBase::SetStartInspectionTimeMilisec(DWORD	s)
{
	StartInspectionTimeMilisec=s;
	ShadowSetStartInspectionTimeMilisec(s);
}

SeqControl	*LayersBase::GetSeqControl(void)	const
{
	if(GetSequenceInstance()!=NULL){
		return GetSequenceInstance()->GetMainSeqControl();
	}
	return NULL;
}
bool	LayersBase::LoadLevelFolderContainerFromDB(void)
{
	if(GetLevelFolderContainer()!=NULL){
		return GetLevelFolderContainer()->BuildFromDB();
	}
	return false;
}
int32	LayersBase::GetThresholdLevelID(void)
{	
	if(GetShadowLevel()==0){
		if(ThresholdLevelID<=0){
			if(GetLevelFolderContainer()->GetCount()>0){
				return GetLevelFolderContainer()->GetFirst()->LevelID;
			}
		}
	}
	else{
		return GetTopLayersBase()->GetThresholdLevelID();
	}
	return ThresholdLevelID;
}

int32	LayersBase::GetThresholdLevelOrderInParent(int &CountInParent,int LevelID,int LevelParentID)
{
	if(GetShadowLevel()==0){
		if(LevelID<0){
			LevelID=ThresholdLevelID;
		}
		if(LevelParentID<0){
			LevelParentID=ThresholdLevelParentID;
		}
		if(LevelParentID<0){
			LevelParentID=0;
		}
		if(LevelFolderContainerInst!=NULL){
			if(LevelParentID==0){
				int	N=0;
				CountInParent=LevelFolderContainerInst->GetCount();
				for(LevelFolder *c=LevelFolderContainerInst->GetFirst();c!=NULL;c=c->GetNext(),N++){
					if(c->LevelID==LevelID){
						return N;
					}
				}
			}
			else{
				LevelFolder	*P=LevelFolderContainerInst->FindByLevelID(LevelParentID);
				if(P!=NULL){
					int	N=0;
					CountInParent=P->Children.GetCount();
					for(LevelFolder *c=P->Children.GetFirst();c!=NULL;c=c->GetNext(),N++){
						if(c->LevelID==LevelID){
							return N;
						}
					}
				}
			}
		}
		CountInParent=0;
		return -1;
	}
	else{
		return GetTopLayersBase()->GetThresholdLevelOrderInParent(CountInParent,LevelID,LevelParentID);
	}
}

int32	LayersBase::GetThresholdLevelOrderInParentOnly(int LevelID,int LevelParentID)
{
	if(GetShadowLevel()==0){
		int CountInParent;
		return GetThresholdLevelOrderInParent(CountInParent,LevelID,LevelParentID);
	}
	else{
		return GetTopLayersBase()->GetThresholdLevelOrderInParentOnly(LevelID,LevelParentID);
	}
}

int32	LayersBase::GetThresholdLevelIDFromOrder(int Order,int LevelParentID)
{
	if(GetShadowLevel()==0){
		if(LevelParentID<0){
			LevelParentID=ThresholdLevelParentID;
		}
		if(LevelParentID<0){
			LevelParentID=0;
		}
		if(LevelFolderContainerInst!=NULL){
			if(LevelParentID==0){
				int	CountInParent=LevelFolderContainerInst->GetCount();
				if(Order<CountInParent){
					return LevelFolderContainerInst->GetItem(Order)->LevelID;
				}
			}
			else{
				LevelFolder	*P=LevelFolderContainerInst->FindByLevelID(LevelParentID);
				if(P!=NULL){
					int	CountInParent=P->Children.GetCount();
					if(Order<CountInParent){
						return P->Children[Order]->LevelID;
					}
				}
			}
		}
		return -1;
	}
	else{
		return GetTopLayersBase()->GetThresholdLevelIDFromOrder(Order,LevelParentID);
	}
}

int32	LayersBase::GetThresholdParentLevelID(int LevelID)
{
	if(GetShadowLevel()==0){
		if(LevelID<0){
			LevelID=ThresholdLevelID;
		}
		if(LevelFolderContainerInst!=NULL){
			if(CurrentLevel!=NULL && CurrentLevel->LevelID==LevelID){
				return CurrentLevel->ParentID;
			}
			LevelFolder	*c=LevelFolderContainerInst->FindByLevelID(LevelID);
			if(c!=NULL){
				if(CurrentLevel==NULL || c->LevelID!=CurrentLevel->LevelID){
					CurrentLevel=c;
				}
			}
		}
		int		LevelValue;
		QString LevelName;
		int		ParentID;
		QString Remark;
		if(GetDatabaseLoader()){
			if(GetDatabaseLoader()->S_LevelFindData(GetDatabase(),LevelID ,LevelValue ,LevelName ,ParentID,Remark)==true){
				return ParentID;
			}
		}
		
		return -1;
	}
	else{
		return GetTopLayersBase()->GetThresholdParentLevelID(LevelID);
	}
}
int32	LayersBase::GetThresholdLevelValue(int LevelID)
{
	if(GetShadowLevel()==0){
		if(LevelID<0){
			LevelID=ThresholdLevelID;
		}
		if(CurrentLevel!=NULL && CurrentLevel->LevelID==LevelID){
			return CurrentLevel->LevelValue;
		}
		int		LevelValue;
		QString LevelName;
		int		ParentID;
		QString Remark;
		if(GetDatabaseLoader()){
			if(GetDatabaseLoader()->S_LevelFindData(GetDatabase(),LevelID ,LevelValue ,LevelName ,ParentID,Remark)==true){
				return LevelValue;
			}
		}
		return -1;
	}
	else{
		return GetTopLayersBase()->GetThresholdLevelValue(LevelID);
	}
}
void	LayersBase::SetThresholdLevel(int LevelParentID ,int LevelID)
{	
	if(GetShadowLevel()==0){
		if(ThresholdLevelID!=LevelID){
			bool	ReEntrant=false;
			if(ReEntrant==true){
				return;
			}
			ReEntrant=true;
			int	OldLevel=ThresholdLevelID;
			if(GetLogicDLLBase()!=NULL){
				for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					AlgorithmBase	*ABase=L->GetInstance();
					if(ABase!=NULL){
						ABase->SwitchThresholdLevel(ThresholdLevelID ,LevelID);
					}
				}
			}
			if(LevelParentID<0){
				LevelParentID=GetThresholdParentLevelID(LevelID);
			}
			ThresholdLevelParentID	=LevelParentID;
			ThresholdLevelID		=LevelID;

			if(LevelFolderContainerInst!=NULL){
				if(CurrentLevel==NULL || LevelID!=CurrentLevel->LevelID){
					CurrentLevel=LevelFolderContainerInst->FindByLevelID(LevelID);
				}
			}

			emit	SignalChangeThresholdLevel(OldLevel ,ThresholdLevelID);
			SetThresholdLevelShadowTree(LevelParentID ,LevelID);
			ReEntrant=false;
		}
	}
	else{
		GetTopLayersBase()->SetThresholdLevel(LevelParentID ,LevelID);
	}
}
void	LayersBase::CopyThresholdLevel(int SourceLevelID ,int DestLevelID)
{
	if(GetShadowLevel()==0){
		if(GetLogicDLLBase()!=NULL){
			for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				AlgorithmBase	*ABase=L->GetInstance();
				if(ABase!=NULL){
					ABase->CopyThresholdLevel(SourceLevelID ,DestLevelID);
				}
			}
		}
	}
	else{
		GetTopLayersBase()->CopyThresholdLevel(SourceLevelID ,DestLevelID);
	}
}
void	LayersBase::SetThresholdLevel(int LevelID)
{
	SetThresholdLevel(-1 ,LevelID);
}
void	LayersBase::DeliverThresholdLevel(int LevelParentID ,int LevelID)
{
	if(LevelParentID<0){
		LevelParentID=ThresholdLevelParentID;
	}
	if(LevelID<0){
		LevelID=ThresholdLevelID;
	}
	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdSetThresholdLevel	Cmd(this,"ANY","ANY",globalPage);
			Cmd.ThresholdLevelParentID	=LevelParentID;
			Cmd.ThresholdLevelID		=LevelID;
			Cmd.Send(NULL,globalPage ,0);
		}
		SetThresholdLevel(LevelParentID,LevelID);
	}
}
void	LayersBase::DeliverThresholdLevel(void)
{
	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdSetThresholdLevel	Cmd(this,"ANY","ANY",globalPage);
			Cmd.ThresholdLevelParentID	=ThresholdLevelParentID;
			Cmd.ThresholdLevelID		=ThresholdLevelID;
			Cmd.Send(NULL,globalPage ,0);
		}
	}
}
void	LayersBase::DeliverCopyThresholdLevel(int SourceLevelID ,int DestLevelID)
{
	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		CopyThresholdLevel(SourceLevelID ,DestLevelID);
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdCopyThresholdLevel	Cmd(this,"ANY","ANY",globalPage);
			Cmd.SourceLevelID	=SourceLevelID;
			Cmd.DestLevelID		=DestLevelID;
			Cmd.Send(NULL,globalPage ,0);
		}
	}
}
void	LayersBase::DeliverRebuildThresholdLevel(void)
{
	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdRebuildThresholdLevel	Cmd(this,"ANY","ANY",globalPage);
			Cmd.Send(NULL,globalPage ,0);
		}
	}
}
void	LayersBase::CopyPageData(int DstPage ,int SrcPage	
					,bool ModeCopyAllAlgorithm ,bool ModeCopyAllFilter)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->CopyPageData(DstPage ,SrcPage	
					,ModeCopyAllAlgorithm ,ModeCopyAllFilter);
	}
	ShadowCopyPageData(DstPage ,SrcPage ,ModeCopyAllAlgorithm ,ModeCopyAllFilter);
}
QString	LayersBase::GetThresholdLevelName(int LevelID)
{
	if(GetLevelFolderContainer()!=NULL){
		if(LevelID<0){
			LevelID=ThresholdLevelID;
		}
		if(CurrentLevel!=NULL && CurrentLevel->LevelID==LevelID){
			return CurrentLevel->LevelName;
		}
		LevelFolder	*f=GetLevelFolderContainer()->FindByLevelID(LevelID);
		if(f!=NULL){
			return f->LevelName;
		}
	}
	return /**/"";
}
QString	LayersBase::GetThresholdParentLevelName(int LevelParentID)
{
	if(GetLevelFolderContainer()!=NULL){
		if(LevelParentID<0){
			LevelParentID=ThresholdLevelParentID;
		}
		if(LevelParentID==0){
			return /**/"Top";
		}
		LevelFolder	*f=GetLevelFolderContainer()->FindByLevelID(LevelParentID);
		if(f!=NULL){
			return f->LevelName;
		}
	}
	return /**/"";
}
int	LayersBase::EnumThresholdLevelIDInFolder(IntList &RetLevelIDs ,int LevelParentID)
{
	if(LevelParentID<0){
		LevelParentID=ThresholdLevelParentID;
	}
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->S_EnumLevelID(GetDatabase() ,LevelParentID ,RetLevelIDs);
	}
	return 0;
}
int	LayersBase::SelectThresholdLevel(void)
{
	if(GetLevelFolderContainer()==NULL || GetLevelFolderContainer()->GetCount()<=1){
		LoadLevelFolderContainerFromDB();
		if(GetLevelFolderContainer()==NULL || GetLevelFolderContainer()->GetCount()<=1){
			return GetThresholdLevelID();
		}
	}
	SelectThresholdLevelDialog	D(this);
	if(D.exec()==true && D.SelectedLevelID>=0){
		return D.SelectedLevelID;
	}
	return GetThresholdLevelID();
}
void	LayersBase::DeliverSetCurrentIntoThresholdLevel(int LevelID)
{
	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdSetCurrentIntoThresholdLevel	Cmd(this,"ANY","ANY",globalPage);
			Cmd.LevelID=LevelID;
			Cmd.Send(NULL,globalPage ,0);
		}
	}
}
void	LayersBase::SetCurrentIntoThresholdLevel(int LevelID)
{
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()!=NULL){
			L->GetInstance()->SetCurrentIntoThresholdLevel(LevelID);
		}
	}
}

LayersBase	*LayersBase::GetShadowLayersBase(int n)
{
	ShadowTree	*w=ShadowTree::GetShadowChildren(n);
	if(w!=NULL){
		return w->GetTreeLayersBase();
	}
	return NULL;
}

void	LayersBase::ReloadAllAlgorithm(void)
{
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=L->GetInstance();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		ABase->Save(&Buff);
		Buff.seek(0);
		ABase->Release();
		ABase->Initial(GetLayersBase());
		ABase->Load(&Buff);
	}
}

void	LayersBase::DeliverMoveForAlignment(void)
{
	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true) && GetParamComm()->GetConnectedPCNumb()!=0){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdReqMoveForAlignment	Cmd(this,"ANY","ANY",globalPage);
			Cmd.Send(NULL,globalPage ,0);
		}
	}
	else{
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if((L->GetAlgorithmType() & AlgorithmBit_TypeAlignment)==0
			&& (L->GetAlgorithmType() & AlgorithmBit_TypePreAlignment)==0){
				AlgorithmBase	*ABase=L->GetInstance();
				ABase->MoveForAlignment();
			}
		}
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if((L->GetAlgorithmType() & AlgorithmBit_TypeAlignment)!=0
			|| (L->GetAlgorithmType() & AlgorithmBit_TypePreAlignment)!=0){
				AlgorithmBase	*ABase=L->GetInstance();
				ABase->MoveForAlignment();
			}
		}
	}
}

IntegrationCommPack				*LayersBase::GetIntegrationCommPointer(void)
{
	if(GetGuiInitializer()!=NULL){
		return GetGuiInitializer()->GetIntegrationCommPointer();
	}
	return NULL;
}

void	LayersBase::CopyTargetToCameraBuff(void)
{
	int32	iPhaseNumb=GetPhaseNumb();
	for(int phase=0;phase<iPhaseNumb;phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->CopyTargetToCameraBuff();
	}
}

bool    LayersBase::SaveControlPointsForPages(QIODevice *f)
{
	int32	iPhaseNumb=GetPhaseNumb();
	if(::Save(f,iPhaseNumb)==false)
		return false;
	for(int phase=0;phase<iPhaseNumb;phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->SaveControlPointsForPages(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadControlPointsForPages(QIODevice *f)
{
	int32	iPhaseNumb;
	if(::Load(f,iPhaseNumb)==false)
		return false;
	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->LoadControlPointsForPages(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::SaveControlPointsForPagesDefault(void)
{
	QFile	File(GetParamGlobal()->FileNameControlPointsForPages);
	if(File.open(QIODevice::WriteOnly)==true){
		if(SaveControlPointsForPages(&File)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadControlPointsForPagesDefault(void)
{
	QFile	File(GetParamGlobal()->FileNameControlPointsForPages);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LoadControlPointsForPages(&File)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::CopyControlPointsForPages(int SourcePhase ,int DestPhase)
{
	PageDataInOnePhase	*Sh=GetPageDataPhase(SourcePhase);
	PageDataInOnePhase	*Dh=GetPageDataPhase(DestPhase);
	if(Sh!=NULL && Dh!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			DataInPage	*Dp=Dh->GetPageData(page);
			DataInPage	*Sp=Sh->GetPageData(page);
			if(Dp!=NULL && Sp!=NULL){
				Dp->ControlPointsForPages = Sp->ControlPointsForPages;
			}
		}
	}
}
const	XYPointContainerWithName	&LayersBase::GetControlPointsForPages(int phase ,int page)
{
	PageDataInOnePhase	*h=GetPageDataPhase(phase);
	return h->GetControlPointsForPages(page);
}

void	LayersBase::LockForLoadSave(void)
{
	MutexForLoadSave.lock();
}
void	LayersBase::UnlockForLoadSave(void)
{
	MutexForLoadSave.unlock();
}

void	LayersBase::SlotChangedMasterImage(int PhaseNo,int PageNo,int LayerNo)
{
	emit	SignalChangedMasterImage(PhaseNo ,PageNo ,LayerNo);
}
void	LayersBase::SetChangedMasterImage(int PhaseNo,int PageNo,int LayerNo)
{
	emit	SignalChangedMasterImage(PhaseNo ,PageNo ,LayerNo);
}
		
bool	LayersBase::CopyThresholdToClipboard(AlgorithmThreshold *Thr)
{
    QClipboard *clipboard = QApplication::clipboard();
    //const QMimeData *mimeData = clipboard->mimeData();

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Thr->Save(&Buff);
	AlgorithmItemRoot	*AItem=Thr->GetParentItem();
	if(AItem!=NULL){
		AlgorithmBase	*ABase=AItem->GetParentBase();
		if(ABase!=NULL){
			QString	AlgoRoot;
			QString	AlgoName;
			ABase->GetAlgorithmRootName(AlgoRoot,AlgoName);
			QString	AName=AlgoRoot+QString(':')+AlgoName;
			QMimeData	*s=new QMimeData();
			s->setData(AName,Buff.buffer());
			clipboard->setMimeData(s);
			return true;
		}
	}
	return false;
}
	
bool	LayersBase::PasteThresholdFromClipboard(AlgorithmThreshold *Thr)
{
    QClipboard *clipboard = QApplication::clipboard();
    //const QMimeData *mimeData = clipboard->mimeData();

	AlgorithmItemRoot	*AItem=Thr->GetParentItem();
	if(AItem!=NULL){
		AlgorithmBase	*ABase=AItem->GetParentBase();
		if(ABase!=NULL){
			QString	AlgoRoot;
			QString	AlgoName;
			ABase->GetAlgorithmRootName(AlgoRoot,AlgoName);
			QString	AName=AlgoRoot+QString(':')+AlgoName;
			const QMimeData	*s=clipboard->mimeData();
			QByteArray	AData=s->data(AName);
			QBuffer	Buff(&AData);
			Buff.open(QIODevice::ReadWrite);
			if(Thr->Load(&Buff)==true){
				return true;
			}
		}
	}
	return false;
}

void	LayersBase::ClearSystemResult(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->ClearSystemResult();
	}
	SystemResultContainer.ClearSystemResult();
}

void	LayersBase::ReallocateSystemResult(int AllocCount)
{
	SystemResultContainer.ReallocateDimCount(AllocCount);
}

void	LayersBase::PushSystemResult(const QByteArray &data)
{
	SystemResultContainer.PushResult(data);
}

SystemResult	*LayersBase::PopSystemResult(void)
{
	return SystemResultContainer.PopResult();
}
SystemResult	*LayersBase::GetLastSystemResult(void)
{
	return SystemResultContainer.GetLastResult();
}
int		LayersBase::GetStockedSystemResult(void)
{
	return SystemResultContainer.GetStockedSystemResult();
}
