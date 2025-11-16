/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInLayerCommander.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QSqlDatabase>
#include "XDataInLayerCommander.h"
#include "XDataInLayerCmdLocal.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XTransfer.h"
#include "MessageBoxStringList.h"
#include "XResultDLLManager.h"
#include <QThread>
#include "XForWindows.h"
#include "XShareMasterData.h"
#include "XLotInformation.h"
#include "XGeneralStocker.h"
#include "XAlgorithmDLL.h"
#include "XResultAnalizer.h"
#include "XCameraClass.h"
#include "XWriteResultThread.h"
#include "XDataAlgorithmList.h"
#include "XEntryPoint.h"

//====================================================================================
GUICmdSendAlgorithmItemIndependentPack::GUICmdSendAlgorithmItemIndependentPack(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage,bool needUndo)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage),IData(base)
{
	NeedInitializerOfUndo	=needUndo;
}
bool	GUICmdSendAlgorithmItemIndependentPack::Load(QIODevice *f)
{
	if(IData.Load(f)==false){
		return false;
	}
	if(::Load(f,Command)==false){
		return false;
	}
	if(::Load(f,NeedInitializerOfUndo)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendAlgorithmItemIndependentPack::Save(QIODevice *f)
{
	if(IData.Save(f)==false){
		return false;
	}
	if(::Save(f,Command)==false){
		return false;
	}
	if(::Save(f,NeedInitializerOfUndo)==false){
		return false;
	}
	return true;
}

void	GUICmdSendAlgorithmItemIndependentPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(NeedInitializerOfUndo==true){
		GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	}
	LayersBase	*Base=GetLayersBase();
	for(AlgorithmItemIndependent *a=IData.Items.GetFirst();a!=NULL;a=a->GetNext()){
		int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(a->GlobalPage);
		LogicDLL		*L=Base->GetAlgorithmDLL(a->AlgorithmRoot,a->AlgorithmName);
		if(L==NULL){
			continue;
		}
		if(GetParamGlobal()->ModePhaseAdaptChangingThreshold==-2){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				QByteArray	AckData;
				L->SetIndependentItemData(Command
										,phase
										,LocalPage
										,a->Layer
										,a->ItemID
										,a->Data
										,IData.EdittedMemberID
										,a->Something
										,AckData);
			}
		}
		else
		if(GetParamGlobal()->ModePhaseAdaptChangingThreshold==-1){
			QByteArray	AckData;
			L->SetIndependentItemData(Command
									,a->PhaseCode
									,LocalPage
									,a->Layer
									,a->ItemID
									,a->Data
									,IData.EdittedMemberID
									,a->Something
									,AckData);
		}
		else
		if(0<=GetParamGlobal()->ModePhaseAdaptChangingThreshold && GetParamGlobal()->ModePhaseAdaptChangingThreshold<GetPhaseNumb()){
			QByteArray	AckData;
			L->SetIndependentItemData(Command
									,GetParamGlobal()->ModePhaseAdaptChangingThreshold
									,LocalPage
									,a->Layer
									,a->ItemID
									,a->Data
									,IData.EdittedMemberID
									,a->Something
									,AckData);
		}
	}
	GetLayersBase()->SendAckToMaster(localPage);
}
//====================================================================================
GUICmdReqAlgorithmItemIndependentPack::GUICmdReqAlgorithmItemIndependentPack(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage,bool needUndo)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage),IData(base)
{
	NeedInitializerOfUndo	=needUndo;
}
bool	GUICmdReqAlgorithmItemIndependentPack::Load(QIODevice *f)
{
	if(IData.Load(f)==false){
		return false;
	}
	if(::Load(f,Command)==false){
		return false;
	}
	if(::Load(f,NeedInitializerOfUndo)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqAlgorithmItemIndependentPack::Save(QIODevice *f)
{
	if(IData.Save(f)==false){
		return false;
	}
	if(::Save(f,Command)==false){
		return false;
	}
	if(::Save(f,NeedInitializerOfUndo)==false){
		return false;
	}
	return true;
}

void	GUICmdReqAlgorithmItemIndependentPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlgorithmItemIndependentPack *SendBack=(GUICmdAckAlgorithmItemIndependentPack *)((GetSendBackPacket()==NULL)?new GUICmdSendAlgorithmGeneralData(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	if(NeedInitializerOfUndo==true){
		GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	}
	LayersBase	*Base=GetLayersBase();
	for(AlgorithmItemIndependent *a=IData.Items.GetFirst();a!=NULL;a=a->GetNext()){
		int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(a->GlobalPage);
		LogicDLL		*L=Base->GetAlgorithmDLL(a->AlgorithmRoot,a->AlgorithmName);
		if(L==NULL){
			continue;
		}
		if(GetParamGlobal()->ModePhaseAdaptChangingThreshold==-2){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				ItemDataWithPhasePageLayer	*W=new ItemDataWithPhasePageLayer();
				W->ItemID=a->ItemID;
				W->Layer	=a->Layer;
				W->Page		=a->GlobalPage;
				W->Phase	=a->PhaseCode;
				L->SetIndependentItemData(Command
										,phase
										,LocalPage
										,a->Layer
										,a->ItemID
										,a->Data
										,IData.EdittedMemberID
										,a->Something
										,W->Data);
				SendBack->Container.AppendList(W);
			}
		}
		else
		if(GetParamGlobal()->ModePhaseAdaptChangingThreshold==-1){
			ItemDataWithPhasePageLayer	*W=new ItemDataWithPhasePageLayer();
			W->ItemID=a->ItemID;
			W->Layer	=a->Layer;
			W->Page		=a->GlobalPage;
			W->Phase	=a->PhaseCode;
			L->SetIndependentItemData(Command
									,a->PhaseCode
									,LocalPage
									,a->Layer
									,a->ItemID
									,a->Data
									,IData.EdittedMemberID
									,a->Something
									,W->Data);
			SendBack->Container.AppendList(W);
		}
		else
		if(0<=GetParamGlobal()->ModePhaseAdaptChangingThreshold && GetParamGlobal()->ModePhaseAdaptChangingThreshold<GetPhaseNumb()){
			ItemDataWithPhasePageLayer	*W=new ItemDataWithPhasePageLayer();
			W->ItemID=a->ItemID;
			W->Layer	=a->Layer;
			W->Page		=a->GlobalPage;
			W->Phase	=a->PhaseCode;
			L->SetIndependentItemData(Command
									,GetParamGlobal()->ModePhaseAdaptChangingThreshold
									,LocalPage
									,a->Layer
									,a->ItemID
									,a->Data
									,IData.EdittedMemberID
									,a->Something
									,W->Data);
			SendBack->Container.AppendList(W);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdAckAlgorithmItemIndependentPack::GUICmdAckAlgorithmItemIndependentPack(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage,bool needUndo)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAlgorithmItemIndependentPack::Load(QIODevice *f)
{
	if(Container.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckAlgorithmItemIndependentPack::Save(QIODevice *f)
{
	if(Container.Save(f)==false){
		return false;
	}
	return true;
}
//====================================================================================
GUICmdReqAlgorithmGeneralData::GUICmdReqAlgorithmGeneralData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Data=NULL;
}
bool	GUICmdReqAlgorithmGeneralData::BuildData(QString algorithmRoot,QString	algorithmName ,int32 reqCommand ,int32 sendCommand)
{
	if(Data!=NULL){
		LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
		if(L!=NULL){
			L->ReleaseGeneralAlgorithmData(ReqCommand,Data);
		}
	}

	ReqCommand	=reqCommand;
	SendCommand	=sendCommand;
	AlgorithmRoot	=algorithmRoot;
	AlgorithmName	=algorithmName;

	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L!=NULL){
		Data=L->CreateGeneralAlgorithmData(ReqCommand,NULL);
		if(Data!=NULL){
			return true;
		}
	}
	return false;
}

bool	GUICmdReqAlgorithmGeneralData::Load(QIODevice *f)
{
	if(::Load(f,ReqCommand)==false){
		return false;
	}
	if(::Load(f,SendCommand)==false){
		return false;
	}
	if(::Load(f,AlgorithmRoot)==false){
		return false;
	}
	if(::Load(f,AlgorithmName)==false){
		return false;
	}

	if(Data!=NULL){
		LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
		if(L!=NULL){
			L->ReleaseGeneralAlgorithmData(ReqCommand,Data);
		}
	}
	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return false;
	}
	Data=L->CreateGeneralAlgorithmData(ReqCommand,NULL);
	if(Data==NULL){
		return false;
	}
	if(L->LoadGeneralAlgorithmData(f,ReqCommand,Data)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqAlgorithmGeneralData::Save(QIODevice *f)
{
	if(Data==NULL){
		return false;
	}
	if(::Save(f,ReqCommand)==false){
		return false;
	}
	if(::Save(f,SendCommand)==false){
		return false;
	}
	if(::Save(f,AlgorithmRoot)==false){
		return false;
	}
	if(::Save(f,AlgorithmName)==false){
		return false;
	}
	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return false;
	}
	if(L->SaveGeneralAlgorithmData(f,ReqCommand,Data)==false){
		return false;
	}
	return true;
}

void	GUICmdReqAlgorithmGeneralData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlgorithmGeneralData *SendBack=(GUICmdSendAlgorithmGeneralData *)((GetSendBackPacket()==NULL)?new GUICmdSendAlgorithmGeneralData(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	SendBack->BuildData(AlgorithmRoot,AlgorithmName ,SendCommand,Data);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}
//====================================================================================
GUICmdSendAlgorithmGeneralData::GUICmdSendAlgorithmGeneralData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Data=NULL;
}
bool	GUICmdSendAlgorithmGeneralData::BuildData(QString algorithmRoot,QString algorithmName ,int32 sendCommand ,void *reqData)
{
	if(Data!=NULL){
		LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
		if(L!=NULL){
			L->ReleaseGeneralAlgorithmData(SendCommand,Data);
		}
	}

	SendCommand	=sendCommand;
	AlgorithmRoot	=algorithmRoot;
	AlgorithmName	=algorithmName;

	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L!=NULL){
		Data=L->CreateGeneralAlgorithmData(SendCommand,reqData);
		if(Data!=NULL){
			return true;
		}
	}
	return false;
}

bool	GUICmdSendAlgorithmGeneralData::Load(QIODevice *f)
{
	if(::Load(f,SendCommand)==false){
		return false;
	}
	if(::Load(f,AlgorithmRoot)==false){
		return false;
	}
	if(::Load(f,AlgorithmName)==false){
		return false;
	}

	if(Data!=NULL){
		LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
		if(L!=NULL){
			L->ReleaseGeneralAlgorithmData(SendCommand,Data);
		}
	}
	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return false;
	}
	Data=L->CreateGeneralAlgorithmData(SendCommand,NULL);
	if(Data==NULL){
		return false;
	}
	if(L->LoadGeneralAlgorithmData(f,SendCommand,Data)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendAlgorithmGeneralData::Save(QIODevice *f)
{
	if(Data==NULL){
		return false;
	}
	if(::Save(f,SendCommand)==false){
		return false;
	}
	if(::Save(f,AlgorithmRoot)==false){
		return false;
	}
	if(::Save(f,AlgorithmName)==false){
		return false;
	}
	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return false;
	}
	if(L->SaveGeneralAlgorithmData(f,SendCommand,Data)==false){
		return false;
	}
	return true;
}

void	GUICmdSendAlgorithmGeneralData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LogicDLL		*L=GetLayersBase()->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return;
	}
	L->ReplyGeneralAlgorithmData(SendCommand,Data);
}

//====================================================================================
GUICmdReqPartialImage::GUICmdReqPartialImage(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqPartialImage::Load(QIODevice *f)
{
	if(::Load(f,localX1)==false){
		return false;
	}
	if(::Load(f,localY1)==false){
		return false;
	}
	if(::Load(f,localX2)==false){
		return false;
	}
	if(::Load(f,localY2)==false){
		return false;
	}
	if(::Load(f,LayerNumb)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqPartialImage::Save(QIODevice *f)
{
	if(::Save(f,localX1)==false){
		return false;
	}
	if(::Save(f,localY1)==false){
		return false;
	}
	if(::Save(f,localX2)==false){
		return false;
	}
	if(::Save(f,localY2)==false){
		return false;
	}
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	return true;
}

void	GUICmdReqPartialImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendPartialImage	*SendBack=GetSendBack(GUICmdSendPartialImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->CreateImage(GetLayersBase(),localPage,localX1,localY1,localX2,localY2,LayerNumb);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendPartialImage::GUICmdSendPartialImage(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ImageData	=NULL;
	LayerNumb	=0;
	ImageWidth	=0;
	ImageHeight	=0;
}

GUICmdSendPartialImage::~GUICmdSendPartialImage(void)
{
	if(ImageData!=NULL){
		for(int layer=0;layer<LayerNumb;layer++){
			delete	ImageData[layer];
		}
		delete	[]ImageData;
		ImageData=NULL;
		LayerNumb=0;
	}
}

bool	GUICmdSendPartialImage::Load(QIODevice *f)
{
	if(::Load(f,LayerNumb)==false){
		return false;
	}
	if(::Load(f,ImageWidth)==false){
		return false;
	}
	if(::Load(f,ImageHeight)==false){
		return false;
	}
	if(ImageData==NULL){
		CreateData();
	}
	for(int layer=0;layer<LayerNumb;layer++){
		ImageData[layer]->Set(0,0,ImageWidth,ImageHeight);
		if(ImageData[layer]->Load(f)==false){
			return false;
		}
	}
	return true;
}
bool	GUICmdSendPartialImage::Save(QIODevice *f)
{
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	if(::Save(f,ImageWidth)==false){
		return false;
	}
	if(::Save(f,ImageHeight)==false){
		return false;
	}
	for(int layer=0;layer<LayerNumb;layer++){
		if(ImageData[layer]->Save(f)==false){
			return false;
		}
	}
	return true;
}

void	GUICmdSendPartialImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendPartialImage::CreateData(void)
{
	ImageData=new ImageBuffer*[LayerNumb];
	for(int layer=0;layer<LayerNumb;layer++){
		ImageData[layer]=new ImageBuffer();
	}
}

void	GUICmdSendPartialImage::CreateImage(LayersBase *Base ,int localPageSrc ,int localX1,int localY1,int localX2,int localY2,int iLayerNumb)
{
	LayerNumb=iLayerNumb;
	CreateData();
	DataInPage	*P=Base->GetPageData(localPageSrc);
	ImageWidth=localX2-localX1;
	ImageHeight=localY2-localY1;
	for(int layer=0;layer<LayerNumb;layer++){
		ImageData[layer]->Set(0,ImageBufferOther,ImageWidth,ImageHeight);
		DataInLayer	*L=P->GetLayerData(layer);
		for(int y=0;y<ImageHeight;y++){
			memcpy(ImageData[layer]->GetY(y),L->GetMasterBuff().GetY(localY1+y)+localX1,ImageWidth);
		}
	}
}

//====================================================================================
GUICmdSendProcessing::GUICmdSendProcessing(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CurrentValue=-1;
	MaxValue=-1;
}
bool	GUICmdSendProcessing::Load(QIODevice *f)
{
	if(::Load(f,CurrentValue)==false){
		return false;
	}
	if(::Load(f,MaxValue)==false){
		return false;
	}
	if(::Load(f,Message)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendProcessing::Save(QIODevice *f)
{
	if(::Save(f,CurrentValue)==false){
		return false;
	}
	if(::Save(f,MaxValue)==false){
		return false;
	}
	if(::Save(f,Message)==false){
		return false;
	}
	return true;
}

void	GUICmdSendProcessing::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(cmd==0){
		GetLayersBase()->StepProcessing(localPage,Message);
	}
	else if(cmd==1){
		GetLayersBase()->SetMaxProcessing(MaxValue);
	}
}

//====================================================================================
GUICmdSendProcessingAdd::GUICmdSendProcessingAdd(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CurrentValue=-1;
	MaxValue=-1;
}
bool	GUICmdSendProcessingAdd::Load(QIODevice *f)
{
	if(::Load(f,CurrentValue)==false){
		return false;
	}
	if(::Load(f,MaxValue)==false){
		return false;
	}
	if(::Load(f,Message)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendProcessingAdd::Save(QIODevice *f)
{
	if(::Save(f,CurrentValue)==false){
		return false;
	}
	if(::Save(f,MaxValue)==false){
		return false;
	}
	if(::Save(f,Message)==false){
		return false;
	}
	return true;
}

void	GUICmdSendProcessingAdd::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(cmd==0){
		GetLayersBase()->StepProcessing(localPage,Message);
	}
	else if(cmd==1){
		GetLayersBase()->AddMaxProcessing(localPage,MaxValue);
	}
}

//====================================================================================
GUICmdSendClose::GUICmdSendClose(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendClose::Load(QIODevice *f)
{
	if(::Load(f,ReturnCode)==false)	return false;
	return true;
}

bool	GUICmdSendClose::Save(QIODevice *f)
{
	if(::Save(f,ReturnCode)==false)	return false;
	return true;
}


void	GUICmdSendClose::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CloseApplicationSpecifiedBroadcaster	SData;
	GetLayersBase()->GetMainWidget()->BroadcastSpecifiedDirectly(&SData);

	GetLayersBase()->SetOnTerminating(true);
	GSleep(2000);
	QCoreApplication::quit();	
}

//====================================================================================
GUICmdSendAck::GUICmdSendAck(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AckFilterID=-1;
}

bool	GUICmdSendAck::Load(QIODevice *f)
{
	if(::Load(f,AckFilterID)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendAck::Save(QIODevice *f)
{
	if(::Save(f,AckFilterID)==false){
		return false;
	}
	return true;
}

void	GUICmdSendAck::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetAckFlag(localPage,AckFilterID);
}
//====================================================================================
CmdCameraErrorOccursMsg::CmdCameraErrorOccursMsg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdCameraErrorOccursMsg::Load(QIODevice *f)
{
	if(::Load(f,Msg)==false){
		return false;
	}
	return true;
}
bool	CmdCameraErrorOccursMsg::Save(QIODevice *f)
{
	if(::Save(f,Msg)==false){
		return false;
	}
	return true;
}

void	CmdCameraErrorOccursMsg::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	QString	MTitle=QString("Camera error Page(")+QString::number(globalPage) +QString(")");
	MessageBoxStringList	Q(GetLayersBase(),Msg,GetLayersBase()->GetMainWidget());
	Q.setWindowTitle(MTitle);
	Q.exec();
}

//====================================================================================
GUICmdCopyImage::GUICmdCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	srcImageType	=0;
	dstImageType	=0;
}
bool	GUICmdCopyImage::Load(QIODevice *f)
{
	if(::Load(f,srcImageType)==false){
		return false;
	}
	if(::Load(f,dstImageType)==false){
		return false;
	}
	return true;
}
bool	GUICmdCopyImage::Save(QIODevice *f)
{
	if(::Save(f,srcImageType)==false){
		return false;
	}
	if(::Save(f,dstImageType)==false){
		return false;
	}
	return true;
}

void	GUICmdCopyImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetPageData(localPage)->CopyImage(srcImageType ,dstImageType);
}

//====================================================================================

GUICmdSendParameters::GUICmdSendParameters(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendParameters::Initial(void)
{
	Buff.open(QIODevice::ReadWrite);
	if(GetParamGlobal()->SaveParam(&Buff ,ParamEnableInTransfer)==false){
		return false;
	}
	int	N=0;
	if(GetLayersBase()->GetResultDLLBase()!=NULL){
		for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			N++;
		}
	}
	if(GetLayersBase()->GetLogicDLLBase()!=NULL){
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			N++;
		}
	}
	if(GetLayersBase()->GetDataOfShareMaster()!=NULL){
		N++;
	}
	if(GetParamGUI()!=NULL){
		N++;
	}
	if(::Save(&Buff,N)==false)
		return false;
	if(GetLayersBase()->GetResultDLLBase()!=NULL){
		for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			ResultDLLBaseRoot	*P=L->GetDLLPoint();
			if(::Save(&Buff,"Result",7)==false){
				return false;
			}
			if(::Save(&Buff,L->GetDLLRoot())==false){
				return false;
			}
			if(::Save(&Buff,L->GetDLLName())==false){
				return false;
			}
			if(P->SaveParam(&Buff ,ParamEnableInTransfer)==false){
				return false;
			}
		}
	}
	if(GetLayersBase()->GetLogicDLLBase()!=NULL){
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			ParamBaseForAlgorithm	*P=L->GetInstance();
			if(::Save(&Buff,"Logic",6)==false){
				return false;
			}
			if(::Save(&Buff,L->GetDLLRoot())==false){
				return false;
			}
			if(::Save(&Buff,L->GetDLLName())==false){
				return false;
			}
			if(P->SaveParam(&Buff,ParamEnableInTransfer)==false){
				return false;
			}
		}
	}
	if(GetLayersBase()->GetDataOfShareMaster()!=NULL){
		if(::Save(&Buff,"ShareMasterData",16)==false){
				return false;
		}
		if(GetLayersBase()->GetDataOfShareMasterContainer()->Save(&Buff)==false){
			return false;
		}
	}
	if(GetParamGUI()!=NULL){
		if(::Save(&Buff,"ParamGUI",16)==false){
				return false;
		}
		if(GetLayersBase()->GetParamGUI()->SaveParam(&Buff)==false){
			return false;
		}
	}
	return true;
}

bool	GUICmdSendParameters::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false){
		return false;
	}
	QByteArray	A=f->read(Len);
	Buff.open(QIODevice::ReadWrite);
	Buff.write(A);
	return true;
}
bool	GUICmdSendParameters::Save(QIODevice *f)
{
	Buff.seek(0);
	QByteArray	A=Buff.readAll();
	int64	Len=A.size();
	if(::Save(f,Len)==false){
		return false;
	}
	f->write(A);
	return true;
}
void	GUICmdSendParameters::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	Buff.seek(0);
	if(GetParamGlobal()->LoadParam(&Buff,ParamEnableInTransfer)==false){
		return;
	}
	int	N;
	if(::Load(&Buff,N)==false){
		return;
	}
	for(int i=0;i<N;i++){
		char	ParamType[20];
		int64	len;
		if(::Load(&Buff,ParamType,len,sizeof(ParamType))==false){
			return;
		}
		if(strcmp(ParamType,"Result")==0){
			QString	DLLRoot;
			QString	DLLName;
			if(::Load(&Buff,DLLRoot)==false){
				return;
			}
			if(::Load(&Buff,DLLName)==false){
				return;
			}
			for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetDLLRoot()==DLLRoot && L->GetDLLName()==DLLName){
					ResultDLLBaseRoot	*P=L->GetDLLPoint();
					if(P->LoadParam(&Buff,ParamEnableInTransfer)==false){
						return;
					}
					GetLayersBase()->CopyShadowTreeParamResultDLL(L);
					break;
				}
			}
		}
		else if(strcmp(ParamType,"Logic")==0){
			QString	DLLRoot;
			QString	DLLName;
			if(::Load(&Buff,DLLRoot)==false){
				return;
			}
			if(::Load(&Buff,DLLName)==false){
				return;
			}
			for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				if(L->CheckDLL(DLLRoot,DLLName)==true){
					ParamBaseForAlgorithm	*P=L->GetInstance();
					if(P->LoadParam(&Buff,ParamEnableInTransfer)==false){
						return;
					}
					GetLayersBase()->CopyShadowTreeParamLogicDLL(L);
					break;
				}
			}
		}
		else if(strcmp(ParamType,"ShareMasterData")==0){
			if(GetLayersBase()->GetDataOfShareMasterContainer()->Load(&Buff)==false){
				return;
			}
		}
		else if(strcmp(ParamType,"ParamGUI")==0){
			if(GetLayersBase()->GetParamGUI()->LoadParam(&Buff)==false){
				return;
			}
		}
	}
	if(GetParamComm()->Mastered==false){
		QFile	FGeneral(GetLayersBase()->GetUserPath()
						+GetSeparator()+GetParamGlobal()->GetSavedFileName());
		if(FGeneral.open(QIODevice::WriteOnly)==true){
			if(GetParamGlobal()->SaveParam(&FGeneral)==false){
				return;
			}
		}
		if(GetLayersBase()->GetResultDLLBase()!=NULL){
			for(ResultDLL *L=GetLayersBase()->GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ResultDLLBaseRoot	*P=L->GetDLLPoint();
				QFile	FResult(GetLayersBase()->GetUserPath()
								+GetSeparator()+P->GetDefaultFileName());
				if(FResult.open(QIODevice::WriteOnly)==true){
					if(P->SaveParam(&FResult)==false){
						return;
					}
				}
			}
		}
		if(GetLayersBase()->GetLogicDLLBase()!=NULL){
			for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ParamBaseForAlgorithm	*P=L->GetInstance();
				QFile	FAlgprithm(GetLayersBase()->GetUserPath()
								  +GetSeparator()+P->GetDefaultFileName());
				if(FAlgprithm.open(QIODevice::WriteOnly)==true){
					if(P->SaveParam(&FAlgprithm)==false){
						return;
					}
				}
			}
		}
		if(GetLayersBase()->GetDataOfShareMaster()!=NULL){
			QFile	FShareMData(GetLayersBase()->GetUserPath()
							+GetSeparator()+GetParamGlobal()->FileNameOfShareMasterData);
			if(FShareMData.open(QIODevice::WriteOnly)==true){
				GetLayersBase()->GetDataOfShareMaster()->Save(&FShareMData);
			}
		}
	}
}
//====================================================================================
GUICmdSetForceChangedInspectID::GUICmdSetForceChangedInspectID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetForceChangedInspectID::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdSetForceChangedInspectID::Save(QIODevice *f)
{
	return true;
}

void	GUICmdSetForceChangedInspectID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->ClearInspectID();
	GetLayersBase()->SetForceChangedInspectID();
}

//====================================================================================

GUICmdReqEdited::GUICmdReqEdited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqEdited::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqEdited::Save(QIODevice *f)
{
	return true;
}
void	GUICmdReqEdited::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendEdited	*SendBack=GetSendBack(GUICmdSendEdited,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->Edited=GetLayersBase()->IsEdited();
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendEdited::GUICmdSendEdited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Edited=true;
}

bool	GUICmdSendEdited::Load(QIODevice *f)
{
	if(::Load(f,Edited)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendEdited::Save(QIODevice *f)
{
	if(::Save(f,Edited)==false){
		return false;
	}
	return true;
}
void	GUICmdSendEdited::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	return;
}

//====================================================================================

GUICmdReqCalcDone::GUICmdReqCalcDone(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqCalcDone::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqCalcDone::Save(QIODevice *f)
{
	return true;
}
void	GUICmdReqCalcDone::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendCalcDone	*SendBack=GetSendBack(GUICmdSendCalcDone,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->CalcDone=GetLayersBase()->IsCalcDone();
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendCalcDone::GUICmdSendCalcDone(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CalcDone=true;
}
bool	GUICmdSendCalcDone::Load(QIODevice *f)
{
	if(::Load(f,CalcDone)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendCalcDone::Save(QIODevice *f)
{
	if(::Save(f,CalcDone)==false){
		return false;
	}
	return true;
}
void	GUICmdSendCalcDone::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//============================================================================

GUICmdSetEdited::GUICmdSetEdited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Edited=true;
}

bool	GUICmdSetEdited::Load(QIODevice *f)
{
	if(::Load(f,Edited)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetEdited::Save(QIODevice *f)
{
	if(::Save(f,Edited)==false){
		return false;
	}
	return true;
}
void	GUICmdSetEdited::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendCalcDone	*SendBack=GetSendBack(GUICmdSendCalcDone,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	GetLayersBase()->SetEdited(Edited);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


//============================================================================

GUICmdSetCalcDone::GUICmdSetCalcDone(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CalcDone=true;
}

bool	GUICmdSetCalcDone::Load(QIODevice *f)
{
	if(::Load(f,CalcDone)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetCalcDone::Save(QIODevice *f)
{
	if(::Save(f,CalcDone)==false){
		return false;
	}
	return true;
}
void	GUICmdSetCalcDone::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	GUICmdSendCalcDone	*SendBack=GetSendBack(GUICmdSendCalcDone,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	GetLayersBase()->SetCalcDone(CalcDone);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//============================================================================

GUICmdSendOffset::GUICmdSendOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	GlobalOffset=NULL;
	GlobalPageNumb=0;
}
GUICmdSendOffset::~GUICmdSendOffset(void)
{
	if(GlobalOffset!=NULL){
		delete	[]GlobalOffset;
	}
	GlobalOffset=NULL;
}

void	GUICmdSendOffset::InitialInMaster(void)
{
	GlobalPageNumb=GetLayersBase()->GetPageNumb();

	if(GlobalOffset!=NULL){
		delete	[]GlobalOffset;
	}
	GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
	for(int page=0;page<GlobalPageNumb;page++){
		GlobalOffset[page].OutlineOffset= *GetLayersBase()->GetPageData(page)->GetOutlineOffset();
	}
}

bool	GUICmdSendOffset::Load(QIODevice *f)
{
	if(::Load(f,GlobalPageNumb)==false){
		return false;
	}
	if(GlobalOffset!=NULL){
		delete	[]GlobalOffset;
	}
	GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
	for(int page=0;page<GlobalPageNumb;page++){
		if(GlobalOffset[page].Load(f)==false){
			return false;
		}
	}
	return true;
}
bool	GUICmdSendOffset::Save(QIODevice *f)
{
	if(::Save(f,GlobalPageNumb)==false){
		return false;
	}
	for(int page=0;page<GlobalPageNumb;page++){
		if(GlobalOffset[page].Save(f)==false){
			return false;
		}
	}
	return true;
}
void	GUICmdSendOffset::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetGlobalOffset(GlobalPageNumb,GlobalOffset);
}

//============================================================================
GUICmdReqCheckSlave::GUICmdReqCheckSlave(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	QBuffer	TmpBuff;
	TmpBuff.open(QIODevice::WriteOnly);
	Base->GetParamGlobal()->SaveParam(&TmpBuff);

	struct	PropertyGeneralStocker	Prop;
	Prop.SaveInMasterData	=false;
	Prop.SynchronizeToSlave	=true;
	QBuffer	GeneralStockerBuffer;
	GeneralStockerBuffer.open(QIODevice::WriteOnly);
	if(Base->GetGeneralStocker()!=NULL){
		Base->GetGeneralStocker()->Save(&GeneralStockerBuffer,Prop);
		QByteArray	GeneralStockerArray=GeneralStockerBuffer.buffer();
		::Save(&TmpBuff,GeneralStockerArray);
	}
	Buff=TmpBuff.buffer();
	
	NowTime=XDateTime::currentDateTime(); 
	NoCamDevice	=GetLayersBase()->GetEntryPoint()->NoCamDevice;
}
bool	GUICmdReqCheckSlave::Load(QIODevice *f)
{
	if(::Load(f,Buff)==false){
		return false;
	}
	if(::Load(f,NowTime)==false){
		return false;
	}
	if(::Load(f,NoCamDevice)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqCheckSlave::Save(QIODevice *f)
{
	if(::Save(f,Buff)==false){
		return false;
	}
	if(::Save(f,NowTime)==false){
		return false;
	}
	if(::Save(f,NoCamDevice)==false){
		return false;
	}
	return true;
}
void	GUICmdReqCheckSlave::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QTime tm=NowTime.GetQDateTime().time ();
	MtAdjustTime(tm.hour(),tm.minute() ,tm.second());
	
	//time_t t=time(NULL);
	//struct tm *Tm=localtime(&t);
	//Tm->tm_hour	=tm.hour();
	//Tm->tm_min	=tm.minute();
	//Tm->tm_sec	=tm.second();

	ParamGlobal	TmpParam(GetLayersBase());
	QBuffer	TmpBuff(&Buff);
	TmpBuff.open(QIODevice::ReadWrite);
	TmpParam.LoadParam(&TmpBuff);

	QByteArray	GeneralStockerArray;
	if(::Load(&TmpBuff,GeneralStockerArray)==true){
		QBuffer	GeneralStockerBuffer(&GeneralStockerArray);
		struct	PropertyGeneralStocker	Prop;
		Prop.SaveInMasterData	=false;
		Prop.SynchronizeToSlave	=true;
		GeneralStockerBuffer.open(QIODevice::ReadOnly);
		if(GetLayersBase()->GetGeneralStocker()!=NULL){
			GetLayersBase()->GetGeneralStocker()->Load(&GeneralStockerBuffer,Prop);
		}
	}

	GUICmdAckCheckSlave	*SendBack=GetSendBack(GUICmdAckCheckSlave,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	bool	NeedReboot=false;
	if(GetParamGlobal()->CheckAndRefer(TmpParam)==false){
		SendBack->Ret=GUICmdAckCheckSlave::_ReqReboot;
		NeedReboot=true;
	}
	else{
		SendBack->Ret=GUICmdAckCheckSlave::_NoProblem;	
		if(GetLayersBase()->CheckResultDLL()==false){
			SendBack->Messages.append("Result DLL is not loaded");
			SendBack->Ret=GUICmdAckCheckSlave::_ErrorOccurs;	
		}
		if(GetEntryPoint()->GetExecuteInspect()!=NULL){
			if(GetEntryPoint()->GetExecuteInspect()->CheckCameraDLL()==false
			&& NoCamDevice==false){
				SendBack->Messages.append("Camera DLL is not loaded");
				SendBack->Ret=GUICmdAckCheckSlave::_ErrorOccurs;	
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

	if(NeedReboot==true){
		QFile	FGeneral(GetLayersBase()->GetUserPath()
						+GetSeparator()+GetParamGlobal()->GetSavedFileName());
		if(FGeneral.open(QIODevice::WriteOnly)==true){
			if(GetParamGlobal()->SaveParam(&FGeneral)==false){
				return;
			}
		}
		GetLayersBase()->CloseOne();
		QCoreApplication::quit();
	}
}

GUICmdAckCheckSlave::GUICmdAckCheckSlave(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Ret=_NoProblem;
}
bool	GUICmdAckCheckSlave::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Ret=(RetMode)N;
	if(::Load(f,Messages)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckCheckSlave::Save(QIODevice *f)
{
	int32	N=(int32)Ret;
	if(::Save(f,N)==false){
		return false;
	}
	if(::Save(f,Messages)==false){
		return false;
	}
	return true;
}
void	GUICmdAckCheckSlave::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//============================================================================

CmdReqRemoveStockedResult::CmdReqRemoveStockedResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	CmdReqRemoveStockedResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetParamComm()->Mastered==false){
		ResultInspection	*Ref;
		for(;;){
			Ref=GetLayersBase()->GetResultThread()->NeedDeleteResult();
			if(Ref==NULL){
				break;
			}
			GetLayersBase()->GetLogicDLLBase()->ExecuteRemoveResult(GetLayersBase()->GetMasterCode()
																	,GetLayersBase()->GetLotBase()
																	,Ref->GetInspectionID()
																	,Ref);
		}
	}
}

//============================================================================

ResultCmdReqLotChangedSlave::ResultCmdReqLotChangedSlave(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	ResultCmdReqLotChangedSlave::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//if(localPage==0){
		GetLayersBase()->GetResultDLLBase()->OutputInLotChangedSlave (localPage);
	//}
	GUICmdSendAck	*SendBack=GetSendBack(GUICmdSendAck,GetLayersBase(),"ANY","ANY",localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//============================================================================

CmdWritternResult::CmdWritternResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdWritternResult::Load(QIODevice *f)
{
	if(::Load(f,InspectedTime)==false){
		return false;
	}
	return true;
}
bool	CmdWritternResult::Save(QIODevice *f)
{
	if(::Save(f,InspectedTime)==false){
		return false;
	}
	return true;
}

void	CmdWritternResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ResultInspectionForStock	*r=GetLayersBase()->GetResultThread()->Pickup(InspectedTime);
	if(r!=NULL){
		r->GetConnectedPCs().Add(localPage);
		if(r->GetConnectedPCs().GetCount()>=GetParamComm()->ConnectedPCNumb){
			GetLayersBase()->SetResultWrittenID(r->GetInspectionID());
		}
	}
}


//============================================================================

GUICmdReqPixWithAlgorithm::GUICmdReqPixWithAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqPixWithAlgorithm::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqPixWithAlgorithm::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqPixWithAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPixWithAlgorithm	*SendBack=GetSendBack(GUICmdAckPixWithAlgorithm,GetLayersBase(),"ANY","ANY",localPage);

	QBuffer	FL(&SendBack->Buff);
	FL.open(QIODevice::WriteOnly);

	GetParamGlobal()->SaveParam(&FL);
	GetParamComm()	->SaveParam(&FL);

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	for(int LNumb=0;LNumb<P->GetLayerNumb();LNumb++){
		DataInLayer	*L=P->GetLayerData(LNumb);
		if(L->GetMasterBuff().Save(&FL)==false){
			return;
		}
		if(L->GetTargetBuff().Save(&FL)==false){
			return;
		}
	}
	int32	AlgoCount=GetLayersBase()->GetLogicDLLBase()->GetNumber();
	if(::Save(&FL,AlgoCount)==false){
		return;
	}

	LogicDLL *p;
	AlgorithmBase	*base;
	int	Error=0;
	for(p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName().isEmpty()==true){
			continue;
		}
		base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
		if(base==NULL){
			Error++;
			continue;
		}
		if(::Save(&FL,p->GetDLLRoot())==false){
			Error++;
			continue;
		}
		if(::Save(&FL,p->GetDLLName())==false){
			Error++;
			continue;
		}

		if(base->SaveOnlyBase(&FL)==false){
			Error++;
			continue;
		}

		AlgorithmInPageRoot	*ap=base->GetPageData(localPage);
		if(ap==NULL){
			Error++;
			continue;
		}
		if(ap->Save(&FL)==false){
			Error++;
			continue;
		}
	}


	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckPixWithAlgorithm::GUICmdAckPixWithAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckPixWithAlgorithm::Load(QIODevice *f)
{
	Buff=f->readAll();
	return true;
}
bool	GUICmdAckPixWithAlgorithm::Save(QIODevice *f)
{
	f->write(Buff);
	return true;
}

void	GUICmdAckPixWithAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

GUICmdLoadPixWithAlgorithm::GUICmdLoadPixWithAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLoadPixWithAlgorithm::Load(QIODevice *f)
{
	Buff=f->readAll();
	return true;
}
bool	GUICmdLoadPixWithAlgorithm::Save(QIODevice *f)
{
	f->write(Buff);
	return true;
}

void	GUICmdLoadPixWithAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QBuffer	FL(&Buff);
	FL.open(QIODevice::ReadOnly);

	GetParamGlobal()->LoadParam(&FL);
	GetParamComm()	->LoadParam(&FL);

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	for(int LNumb=0;LNumb<P->GetLayerNumb();LNumb++){
		DataInLayer	*L=P->GetLayerData(LNumb);
		if(L->GetMasterBuff().Load(&FL)==false){
			return;
		}
		if(L->GetTargetBuff().Load(&FL)==false){
			return;
		}
	}

	int32	AlgoCount;
	if (::Load(&FL, AlgoCount) == false) {
		return;
	}
	AlgorithmBase	*base;
	int	Error=0;
	for(int i=0;i<AlgoCount;i++){
		QString	DLLRoot;
		QString	DLLName;
		if(::Load(&FL,DLLRoot)==false){
			Error++;
			continue;
		}
		if(::Load(&FL,DLLName)==false){
			Error++;
			continue;
		}

		base=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
		if(base==NULL){
			Error++;
			continue;
		}

		if(base->LoadOnlyBase(&FL)==false){
			Error++;
			continue;
		}

		AlgorithmInPageRoot	*ap=base->GetPageData(localPage);
		if(ap==NULL){
			Error++;
			continue;
		}
		if(ap->Load(&FL)==false){
			Error++;
			continue;
		}
	}
}

//============================================================================

CmdReportError::CmdReportError(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	CmdReportError::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//============================================================================
GUICmdSendInspectionNumber::GUICmdSendInspectionNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendInspectionNumber::Load(QIODevice *f)
{
	if(::Load(f,InspectionNumber)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendInspectionNumber::Save(QIODevice *f)
{
	if(::Save(f,InspectionNumber)==false){
		return false;
	}
	return true;
}

void	GUICmdSendInspectionNumber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetInspectionNumber(InspectionNumber);
}

//============================================================================
GUICmdSendMachineID::GUICmdSendMachineID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendMachineID::Load(QIODevice *f)
{
	if(::Load(f,MachineID)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendMachineID::Save(QIODevice *f)
{
	if(::Save(f,MachineID)==false){
		return false;
	}
	return true;
}
void	GUICmdSendMachineID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetMachineID(MachineID);
}
//============================================================================

GUICmdReqResultInfo::GUICmdReqResultInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqResultInfo::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqResultInfo::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqResultInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultInfo	*SendBack=GetSendBack(GUICmdAckResultInfo,GetLayersBase(),"ANY","ANY",localPage);

	QBuffer	FL(&SendBack->Buff);
	FL.open(QIODevice::WriteOnly);

	ResultInspection	*RCalc=GetLayersBase()->GetCurrentResultForCalc();
	ResultInspection	*RDraw=GetLayersBase()->GetCurrentResultForDraw();

	if(RCalc!=NULL){
		if(localPage==0){
			RCalc->SaveWithoutPage(&FL);
		}
		RCalc->SaveOnlyPage(&FL,localPage);
	}

	if(RDraw!=NULL){
		if(localPage==0){
			RDraw->SaveWithoutPage(&FL);
		}
		RDraw->SaveOnlyPage(&FL,localPage);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckResultInfo::GUICmdAckResultInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckResultInfo::Load(QIODevice *f)
{
	Buff=f->readAll();
	return true;
}
bool	GUICmdAckResultInfo::Save(QIODevice *f)
{
	f->write(Buff);
	return true;
}

void	GUICmdAckResultInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

GUICmdLoadResultInfo::GUICmdLoadResultInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLoadResultInfo::Load(QIODevice *f)
{
	Buff=f->readAll();
	return true;
}
bool	GUICmdLoadResultInfo::Save(QIODevice *f)
{
	f->write(Buff);
	return true;
}

void	GUICmdLoadResultInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QBuffer	FL(&Buff);
	FL.open(QIODevice::ReadOnly);

	ResultInspection	*RCalc=GetLayersBase()->GetCurrentResultForCalc();
	ResultInspection	*RDraw=GetLayersBase()->GetCurrentResultForDraw();

	if(RCalc!=NULL){
		if(localPage==0){
			RCalc->LoadWithoutPage(&FL);
		}
		RCalc->LoadOnlyPage(&FL,localPage);
	}
	if(RDraw!=NULL){
		if(localPage==0){
			RDraw->LoadWithoutPage(&FL);
		}
		RDraw->LoadOnlyPage(&FL,localPage);
	}
}

//============================================================================
GUICmdSendAllComms::GUICmdSendAllComms(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

GUICmdSendAllComms::~GUICmdSendAllComms(void)
{
}

void	GUICmdSendAllComms::Initial(void)
{
	int	N=0;
	for(int page=0;page<GetPageNumb();page++){
		if(GetGlobalPage()==page){
			continue;
		}
		ConnectionInfo	*p=GetParamComm()->GetConnectionFromPage(*GetParamGlobal(),page);
		if(p!=NULL){
			SystemConnectionInfo	*s=new SystemConnectionInfo(page,N,p->IPAddress);
			Data.AppendList(s);
			N++;
		}
	}
}

bool	GUICmdSendAllComms::Load(QIODevice *f)
{
	if(Data.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendAllComms::Save(QIODevice *f)
{
	if(Data.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendAllComms::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetDirectCommBase()!=NULL){
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false || GetParamComm()->ConnectedPCNumb==0){
			GetLayersBase()->GetEntryPoint()->InitialDirectCommInSlave(GetLayersBase()->GetDirectCommBase(),GetLayersBase()->GetMainWidget(),Data);
		}
	}
	SendAck(localPage);
}

//============================================================================
GUICmdReqSetCurrentPhase::GUICmdReqSetCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CurrentPhase=0;
}

bool	GUICmdReqSetCurrentPhase::Load(QIODevice *f)
{
	if(::Load(f,CurrentPhase)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSetCurrentPhase::Save(QIODevice *f)
{
	if(::Save(f,CurrentPhase)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSetCurrentPhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCurrentPhase(CurrentPhase);
	}
}

//============================================================================
GUICmdMakeUncoveredMap::GUICmdMakeUncoveredMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMakeUncoveredMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetPageData(localPage)->MakeUncoveredMap();
	SendAck(localPage);
}

//============================================================================

GUICmdReqRewindExecuter::GUICmdReqRewindExecuter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	memset(CPoint,0,sizeof(CPoint));
}
bool	GUICmdReqRewindExecuter::Load(QIODevice *f)
{
	for(int i=0;i<sizeof(CPoint)/sizeof(CPoint[0]);i++){
		if(::Load(f,CPoint[i])==false){
			return false;
		}
	}
	return true;
}

bool	GUICmdReqRewindExecuter::Save(QIODevice *f)
{
	for(int i=0;i<sizeof(CPoint)/sizeof(CPoint[0]);i++){
		if(::Save(f,CPoint[i])==false){
			return false;
		}
	}
	return true;
}
void	GUICmdReqRewindExecuter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCalcPoint(CPoint);
	}
	SendAck(localPage);
}

//============================================================================

GUICmdSetCurrentScanPhaseNumber::GUICmdSetCurrentScanPhaseNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CurrentScanPhaseNumber=0;
}

bool	GUICmdSetCurrentScanPhaseNumber::Load(QIODevice *f)
{
	if(::Load(f,CurrentScanPhaseNumber)==false){
		return false;
	}
	return true;
}

bool	GUICmdSetCurrentScanPhaseNumber::Save(QIODevice *f)
{
	if(::Save(f,CurrentScanPhaseNumber)==false){
		return false;
	}
	return true;
}


void	GUICmdSetCurrentScanPhaseNumber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetCurrentScanPhaseNumber(CurrentScanPhaseNumber);
	SendAck(localPage);
}

//============================================================================

GUICmdForceStrategicNumber::GUICmdForceStrategicNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	StrategicNumber=0;
	memset(CPoints,0,sizeof(CPoints));
}

bool	GUICmdForceStrategicNumber::Load(QIODevice *f)
{
	if(::Load(f,StrategicNumber)==false){
		return false;
	}
	for(int i=0;i<10;i++){
		if(::Load(f,CPoints[i])==false){
			return false;
		}
	}
	return true;
}

bool	GUICmdForceStrategicNumber::Save(QIODevice *f)
{
	if(::Save(f,StrategicNumber)==false){
		return false;
	}
	for(int i=0;i<10;i++){
		if(::Save(f,CPoints[i])==false){
			return false;
		}
	}
	return true;
}


void	GUICmdForceStrategicNumber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->ForceStrategicNumber(StrategicNumber);
	if(StrategicNumber==0){
		GetLayersBase()->SetCalcPoint(CPoints);
	}
	SendAck(localPage);
}

//========================================================================================================================
GUICmdChangeLotInfo::GUICmdChangeLotInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LotAutoCount=0;
	DeliveryNo=-1;
}


bool	GUICmdChangeLotInfo::Load(QIODevice *f)
{
	if(::Load(f,DeliveryNo)==false)
		return false;
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	return true;
}

bool	GUICmdChangeLotInfo::Save(QIODevice *f)
{
	if(::Save(f,DeliveryNo)==false)
		return false;
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	return true;
}

void	GUICmdChangeLotInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			GetLayersBase()->GetLot(DeliveryNo)->SetLotAutoCount	(LotAutoCount);
			GetLayersBase()->GetLot(DeliveryNo)->SetLotID			(LotID);
			GetLayersBase()->GetLot(DeliveryNo)->SetLotName		(LotName);

			GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
			for(ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
				ResultDLLBaseRoot	*RL=R->GetDLLPoint();

				CmdChangeResultLotInfo	ResCmd(GetLayersBase());
				ResCmd.LotID	=LotID;
				ResCmd.LotName	=LotName;
				ResCmd.Remark	=Remark;
				RL->TransmitDirectly(&ResCmd);
			}
		}
	}
}

//========================================================================================================================
GUICmdDeliverManualExecuter::GUICmdDeliverManualExecuter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeliverManualExecuter::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(::Load(f,ManualArray)==false)
		return false;
	return true;
}

bool	GUICmdDeliverManualExecuter::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(::Save(f,ManualArray)==false)
		return false;
	return true;
}

void	GUICmdDeliverManualExecuter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DLLRoot ,DLLName);
		if(ABase!=NULL){
			QBuffer	Buff(&ManualArray);
			Buff.open(QIODevice::ReadOnly);
			ABase->GetManualExecuter().LoadCommand(&Buff);
		}
	}
}

//========================================================================================================================

GUICmdSetLibFolderID::GUICmdSetLibFolderID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibFolderID			=-1;
	originalLibFolder	=-1;
}

bool	GUICmdSetLibFolderID::Load(QIODevice *f)
{
	if(::Load(f,LibFolderID)==false)
		return false;
	if(::Load(f,originalLibFolder)==false)
		return false;
	return true;
}
bool	GUICmdSetLibFolderID::Save(QIODevice *f)
{
	if(::Save(f,LibFolderID)==false)
		return false;
	if(::Save(f,originalLibFolder)==false)
		return false;
	return true;
}

void	GUICmdSetLibFolderID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetLibFolderID(LibFolderID,originalLibFolder,false);
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*Ab=L->GetInstance();
			if(Ab!=NULL){
				Ab->SetupLibFolder(LibFolderID,originalLibFolder);
			}
		}
	}
}
//============================================================================

GUICmdReqChangedAlgo::GUICmdReqChangedAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqChangedAlgo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckChangedAlgo	*SendBack=GetSendBack(GUICmdAckChangedAlgo,GetLayersBase(),"ANY","ANY",localPage);

	for(LogicDLL *f=GetLayersBase()->GetLogicDLLBase()->GetFirst();f!=NULL;f=f->GetNext()){
		AlgorithmBase	*ABase=f->GetInstance();
		if(ABase==NULL)
			continue;
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
			if(Ph!=NULL){
				AlgorithmInPageRoot *PData=Ph->GetPageData(localPage);
				if(PData->IsEdited()==true){
					if(f->CheckAlgorithmType(AlgorithmBit_TypePreAlignment)==true)
						SendBack->ChangedAlgo.ChangedPreAlignment=true;
					else
						SendBack->ChangedAlgo.ChangedPreAlignment=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==true)
						SendBack->ChangedAlgo.ChangedAlignment=true;
					else
						SendBack->ChangedAlgo.ChangedAlignment=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypePreProcessing)==true)
						SendBack->ChangedAlgo.ChangedPreProcessing=true;
					else
						SendBack->ChangedAlgo.ChangedPreProcessing=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==true)
						SendBack->ChangedAlgo.ChangedProcessing=true;
					else
						SendBack->ChangedAlgo.ChangedProcessing=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeProcessingRevived)==true)
						SendBack->ChangedAlgo.ChangedProcessingRevived=true;
					else
						SendBack->ChangedAlgo.ChangedProcessingRevived=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypePostProcessing)==true)
						SendBack->ChangedAlgo.ChangedPostProcessing=true;
					else
						SendBack->ChangedAlgo.ChangedPostProcessing=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeNoProcessing)==true)
						SendBack->ChangedAlgo.ChangedNoProcessing=true;
					else
						SendBack->ChangedAlgo.ChangedNoProcessing=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypePieceProcessing)==true)
						SendBack->ChangedAlgo.ChangedPieceProcessing=true;
					else
						SendBack->ChangedAlgo.ChangedPieceProcessing=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypePreScanning)==true)
						SendBack->ChangedAlgo.ChangedPreScanning=true;
					else
						SendBack->ChangedAlgo.ChangedPreScanning=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeScanning)==true)
						SendBack->ChangedAlgo.ChangedScanning=true;
					else
						SendBack->ChangedAlgo.ChangedScanning=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypePostScanning)==true)
						SendBack->ChangedAlgo.ChangedPostScanning=true;
					else
						SendBack->ChangedAlgo.ChangedPostScanning=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeMatchAlignment)==true)
						SendBack->ChangedAlgo.ChangedMatchAlignment=true;
					else
						SendBack->ChangedAlgo.ChangedMatchAlignment=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeManageResult)==true)
						SendBack->ChangedAlgo.ChangedManageResult=true;
					else
						SendBack->ChangedAlgo.ChangedManageResult=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeMasking)==true)
						SendBack->ChangedAlgo.ChangedMasking=true;
					else
						SendBack->ChangedAlgo.ChangedMasking=false;

					if(f->CheckAlgorithmType(AlgorithmBit_TypeDynamicMasking)==true)
						SendBack->ChangedAlgo.ChangedDynamicMasking=true;
					else
						SendBack->ChangedAlgo.ChangedDynamicMasking=false;
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckChangedAlgo::GUICmdAckChangedAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	memset(&ChangedAlgo,0,sizeof(ChangedAlgo));
}
bool	GUICmdAckChangedAlgo::Load(QIODevice *f)
{
	if(f->read((char *)&ChangedAlgo,sizeof(ChangedAlgo))!=sizeof(ChangedAlgo))
		return false;
	return true;
}
bool	GUICmdAckChangedAlgo::Save(QIODevice *f)
{
	if(f->write((const char *)&ChangedAlgo,sizeof(ChangedAlgo))!=sizeof(ChangedAlgo))
		return false;
	return true;
}

GUICmdDeliverChangedAlgo::GUICmdDeliverChangedAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	memset(&ChangedAlgo,0,sizeof(ChangedAlgo));
}
bool	GUICmdDeliverChangedAlgo::Load(QIODevice *f)
{
	if(f->read((char *)&ChangedAlgo,sizeof(ChangedAlgo))!=sizeof(ChangedAlgo))
		return false;
	return true;
}
bool	GUICmdDeliverChangedAlgo::Save(QIODevice *f)
{
	if(f->write((const char *)&ChangedAlgo,sizeof(ChangedAlgo))!=sizeof(ChangedAlgo))
		return false;
	return true;
}
void	GUICmdDeliverChangedAlgo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetChangedStruct(ChangedAlgo);
}

//============================================================================
GUICmdSendResultAnalizerData::GUICmdSendResultAnalizerData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendResultAnalizerData::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSendResultAnalizerData::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}
void	GUICmdSendResultAnalizerData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		QBuffer	Buff(&Data);
		Buff.open(QIODevice::ReadOnly);
		GetLayersBase()->GetResultAnalizerItemBaseContainer()->Load(&Buff);
	}
}

//============================================================================
GUICmdSetThresholdLevel::GUICmdSetThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ThresholdLevelParentID	=0;
	ThresholdLevelID		=0;
}
bool	GUICmdSetThresholdLevel::Load(QIODevice *f)
{
	if(::Load(f,ThresholdLevelParentID)==false){
		return false;
	}
	if(::Load(f,ThresholdLevelID)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetThresholdLevel::Save(QIODevice *f)
{
	if(::Save(f,ThresholdLevelParentID)==false){
		return false;
	}
	if(::Save(f,ThresholdLevelID)==false){
		return false;
	}
	return true;
}

void	GUICmdSetThresholdLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetThresholdLevel(ThresholdLevelParentID,ThresholdLevelID);
}


//============================================================================
GUICmdCopyThresholdLevel::GUICmdCopyThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	SourceLevelID	=0;
	DestLevelID		=0;
}
bool	GUICmdCopyThresholdLevel::Load(QIODevice *f)
{
	if(::Load(f,SourceLevelID)==false){
		return false;
	}
	if(::Load(f,DestLevelID)==false){
		return false;
	}
	return true;
}
bool	GUICmdCopyThresholdLevel::Save(QIODevice *f)
{
	if(::Save(f,SourceLevelID)==false){
		return false;
	}
	if(::Save(f,DestLevelID)==false){
		return false;
	}
	return true;
}

void	GUICmdCopyThresholdLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->CopyThresholdLevel(SourceLevelID,DestLevelID);
}

//============================================================================
GUICmdRebuildThresholdLevel::GUICmdRebuildThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdRebuildThresholdLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->LoadLevelFolderContainerFromDB();
	}
}
//============================================================================

GUICmdReqThresholdInstance::GUICmdReqThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqThresholdInstance::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqThresholdInstance::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	return true;
}

void	GUICmdReqThresholdInstance::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckThresholdInstance	*SendBack=GetSendBack(GUICmdAckThresholdInstance,GetLayersBase(),"ANY","ANY",localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		AlgorithmItemRoot	*Item=Ap->GetItemData(Layer ,ItemID);
		if(Item!=NULL){
			const	AlgorithmThreshold	*Thr=Item->GetThresholdBaseReadable();
			if(Thr!=NULL){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				if(((AlgorithmThreshold *)Thr)->Save(&Buff)==true){
					SendBack->Array=Buff.buffer();
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckThresholdInstance::GUICmdAckThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckThresholdInstance::Load(QIODevice *f)
{
	if(::Load(f,Array)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckThresholdInstance::Save(QIODevice *f)
{
	if(::Save(f,Array)==false){
		return false;
	}
	return true;
}

GUICmdReflectThresholdInstanceOne::GUICmdReflectThresholdInstanceOne(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReflectThresholdInstanceOne::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(ItemID.Load(f)==false){
		return false;
	}
	if(::Load(f,ThresholdData)==false){
		return false;
	}
	if(ChangedMapInThreshold.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReflectThresholdInstanceOne::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(ItemID.Save(f)==false){
		return false;
	}
	if(::Save(f,ThresholdData)==false){
		return false;
	}
	if(ChangedMapInThreshold.Save(f)==false){
		return false;
	}
	return true;
}
void	GUICmdReflectThresholdInstanceOne::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmThreshold	*SrcThr=NULL;
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		for(IntClass *c=ItemID.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmItemRoot	*Item=Ap->GetItemData(Layer ,c->GetValue());
			if(Item!=NULL && Item->GetLibID()==LibID){
				if(SrcThr==NULL){
					SrcThr=Item->CreateThresholdInstance();
					QBuffer	Buff(&ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					SrcThr->Load(&Buff);
				}

				AlgorithmThreshold	*Thr=Item->GetThresholdBaseWritable();
				if(Thr!=NULL){
					Thr->Reflect(SrcThr,ChangedMapInThreshold);
				}
			}
		}
	}
}


GUICmdReflectThresholdInstanceAll::GUICmdReflectThresholdInstanceAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReflectThresholdInstanceAll::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ThresholdData)==false){
		return false;
	}
	if(ChangedMapInThreshold.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReflectThresholdInstanceAll::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ThresholdData)==false){
		return false;
	}
	if(ChangedMapInThreshold.Save(f)==false){
		return false;
	}
	return true;
}
void	GUICmdReflectThresholdInstanceAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmThreshold	*SrcThr=NULL;
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		IntList LibIDs;
		LibIDs.Add(LibID);
		AlgorithmItemPointerListContainer ItemPointers;
		Ap->EnumItemsByLib(LibIDs ,ItemPointers);
		for(AlgorithmItemPointerList *c=ItemPointers.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmItemRoot	*Item=c->GetItem();
			if(Item!=NULL && Item->GetLibID()==LibID){
				if(SrcThr==NULL){
					SrcThr=Item->CreateThresholdInstance();
					QBuffer	Buff(&ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					SrcThr->Load(&Buff);
				}

				AlgorithmThreshold	*Thr=Item->GetThresholdBaseWritable();
				if(Thr!=NULL){
					Thr->Reflect(SrcThr,ChangedMapInThreshold);
				}
			}
		}
	}
}


GUICmdTestThresholdInstance::GUICmdTestThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdTestThresholdInstance::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(ItemID.Load(f)==false){
		return false;
	}
	if(::Load(f,ThresholdData)==false){
		return false;
	}
	if(ChangedMapInThreshold.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdTestThresholdInstance::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(ItemID.Save(f)==false){
		return false;
	}
	if(::Save(f,ThresholdData)==false){
		return false;
	}
	if(ChangedMapInThreshold.Save(f)==false){
		return false;
	}
	return true;
}
void	GUICmdTestThresholdInstance::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdResultThresholdInstance	*SendBack=GetSendBack(GUICmdResultThresholdInstance,GetLayersBase(),"ANY","ANY",localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		QBuffer	ResultBuff;
		ResultBuff.open(QIODevice::ReadWrite);
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		for(IntClass *c=ItemID.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmItemRoot	*Item=Ap->GetItemData(Layer ,c->GetValue());

			ResultInItemRoot	*Result=Item->GetCurrentResult();
			if(Result!=NULL){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				Result->Save(&Buff);

				Item->ExecuteStartByInspection	(0,0,Result);
				Item->ExecuteProcessing			(0,0,Result);

				::Save(&ResultBuff,Item->GetID());
				Result->Save(&ResultBuff);

				Buff.seek(0);
				Result->Load(&Buff);
			}
		}
		SendBack->ResultInItemData=ResultBuff.buffer();
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}



GUICmdResultThresholdInstance::GUICmdResultThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdResultThresholdInstance::Load(QIODevice *f)
{
	if(::Load(f,ResultInItemData)==false){
		return false;
	}
	return true;
}
bool	GUICmdResultThresholdInstance::Save(QIODevice *f)
{
	if(::Save(f,ResultInItemData)==false){
		return false;
	}
	return true;
}

//============================================================================================================

GUICmdSetCurrentIntoThresholdLevel::GUICmdSetCurrentIntoThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetCurrentIntoThresholdLevel::Load(QIODevice *f)
{
	if(::Load(f,LevelID)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetCurrentIntoThresholdLevel::Save(QIODevice *f)
{
	if(::Save(f,LevelID)==false){
		return false;
	}
	return true;
}

void	GUICmdSetCurrentIntoThresholdLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCurrentIntoThresholdLevel(LevelID);
	}
}

//============================================================================================================

GUICmdCopyShadowAlgorithm::GUICmdCopyShadowAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCopyShadowAlgorithm::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot				)==false)	return false;
	if(::Load(f,DLLName				)==false)	return false;
	if(::Load(f,Phase				)==false)	return false;
	if(::Load(f,ParentShadowLevel	)==false)	return false;
	if(::Load(f,ParentShadowNumber	)==false)	return false;
	if(::Load(f,ChildShadowLevel	)==false)	return false;
	if(::Load(f,ChildShadowNumber	)==false)	return false;
	return true;
}
bool	GUICmdCopyShadowAlgorithm::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot				)==false)	return false;
	if(::Save(f,DLLName				)==false)	return false;
	if(::Save(f,Phase				)==false)	return false;
	if(::Save(f,ParentShadowLevel	)==false)	return false;
	if(::Save(f,ParentShadowNumber	)==false)	return false;
	if(::Save(f,ChildShadowLevel	)==false)	return false;
	if(::Save(f,ChildShadowNumber	)==false)	return false;
	return true;
}
void	GUICmdCopyShadowAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*ParentBase	=GetLayersBase()->GetShadowTree(ParentShadowLevel,ParentShadowNumber);
	LayersBase	*ChildBase	=GetLayersBase()->GetShadowTree(ChildShadowLevel ,ChildShadowNumber);
	if(ParentBase!=NULL && ChildBase!=NULL){
		AlgorithmBase	*PBase=ParentBase->GetAlgorithmBase(DLLRoot,DLLName);
		AlgorithmBase	*CBase=ChildBase ->GetAlgorithmBase(DLLRoot,DLLName);
		if(PBase!=NULL && CBase!=NULL){
			AlgorithmInPageInOnePhase	*PPh=PBase->GetPageDataPhase(Phase);
			AlgorithmInPageInOnePhase	*CPh=CBase->GetPageDataPhase(Phase);
			if(PPh!=NULL && CPh!=NULL){
				AlgorithmInPageRoot		*PPg=PPh->GetPageData(localPage);
				AlgorithmInPageRoot		*CPg=CPh->GetPageData(localPage);
				if(PPg!=NULL && CPg!=NULL){
					ChildBase->CopyShadowAlgorithmPage(*PPg,CPg);
				}
			}
		}
	}
}
//============================================================================================================

GUICmdSetAutoRepeat::GUICmdSetAutoRepeat(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetAutoRepeat::Load(QIODevice *f)
{
	if(::Load(f,RepeatMode	)==false)	return false;
	return true;
}
bool	GUICmdSetAutoRepeat::Save(QIODevice *f)
{
	if(::Save(f,RepeatMode	)==false)	return false;
	return true;
}

void	GUICmdSetAutoRepeat::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		if(GetLayersBase()->GetEntryPoint()!=NULL
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			int	n=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAllocatedCameraCount();
			for(int cam=0;cam<n;cam++){
				CameraClass		*C=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetCamera(cam);
				if(C!=NULL){
					C->SetAutoRepeat(RepeatMode);
				}
			}
		}
	}				
}
//============================================================================================================

GUICmdReqMoveForAlignment::GUICmdReqMoveForAlignment(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqMoveForAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if((L->GetAlgorithmType() & AlgorithmBit_TypeAlignment)==0
		&& (L->GetAlgorithmType() & AlgorithmBit_TypePreAlignment)==0){
			AlgorithmBase	*ABase=L->GetInstance();
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(phase);
				if(Ah!=NULL){
					AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
					if(Ap!=NULL){
						Ap->MoveForAlignment();
					}
				}
			}

		}
	}
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if((L->GetAlgorithmType() & AlgorithmBit_TypeAlignment)!=0
		|| (L->GetAlgorithmType() & AlgorithmBit_TypePreAlignment)!=0){
			AlgorithmBase	*ABase=L->GetInstance();
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(phase);
				if(Ah!=NULL){
					AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
					if(Ap!=NULL){
						Ap->MoveForAlignment();
					}
				}
			}

		}
	}
}


//=======================================================================
GUICmdReqUndo::GUICmdReqUndo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	IDForUndo=-1;
}
bool	GUICmdReqUndo::Load(QIODevice *f)
{
	if(::Load(f,IDForUndo)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqUndo::Save(QIODevice *f)
{
	if(::Save(f,IDForUndo)==false){
		return false;
	}
	return true;
}

void	GUICmdReqUndo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		UndoTopic	*L=GetLayersBase()->GetUndoStocker().SearchTopic(IDForUndo);
		if(L!=NULL){
			L->ExecuteUndo();
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdReqRedo::GUICmdReqRedo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	IDForUndo=-1;
}
bool	GUICmdReqRedo::Load(QIODevice *f)
{
	if(::Load(f,IDForUndo)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqRedo::Save(QIODevice *f)
{
	if(::Save(f,IDForUndo)==false){
		return false;
	}
	return true;
}

void	GUICmdReqRedo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		UndoTopic	*L=GetLayersBase()->GetUndoStocker().SearchTopic(IDForUndo);
		if(L!=NULL){
			L->ExecuteRedo();
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdReqBufferInfo::GUICmdReqBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqBufferInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBufferInfo	*SendBack=GetSendBack(GUICmdAckBufferInfo,GetLayersBase(),"ANY","ANY",localPage);

	SendBack->DimCount=GetLayersBase()->GetCountBufferInfo();
	SendBack->Dim=new BufferInfoList[SendBack->DimCount];
	for(int i=0;i<SendBack->DimCount;i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL){
			SendBack->Dim[i]=*B;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBufferInfo::GUICmdAckBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckBufferInfo::Load(QIODevice *f)
{
	if(Dim!=NULL){
		delete	[]Dim;
	}
	if(::Load(f,DimCount)==false){
		return false;
	}
	Dim=new BufferInfoList[DimCount];
	for(int i=0;i<DimCount;i++){
		if(Dim[i].Load(f)==false){
			return false;
		}
	}
	return true;
}
bool	GUICmdAckBufferInfo::Save(QIODevice *f)
{
	if(::Save(f,DimCount)==false){
		return false;
	}
	for(int i=0;i<DimCount;i++){
		if(Dim[i].Save(f)==false){
			return false;
		}
	}
	return true;
}

//=======================================================================

GUICmdReqClearBufferInfo::GUICmdReqClearBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqClearBufferInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBufferInfo	*SendBack=GetSendBack(GUICmdAckBufferInfo,GetLayersBase(),"ANY","ANY",localPage);

	GetLayersBase()->ClearBufferInfo();

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//=======================================================================

GUICmdReqRemoveBufferInfo::GUICmdReqRemoveBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRemoveBufferInfo::Load(QIODevice *f)
{
	if(::Load(f,OriginCode)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqRemoveBufferInfo::Save(QIODevice *f)
{
	if(::Save(f,OriginCode)==false){
		return false;
	}
	return true;
}

void	GUICmdReqRemoveBufferInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBufferInfo	*SendBack=GetSendBack(GUICmdAckBufferInfo,GetLayersBase(),"ANY","ANY",localPage);

	GetLayersBase()->RemoveBufferInfo(OriginCode);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//=======================================================================

CmdGetCurrentInfo::CmdGetCurrentInfo(LayersBase *base)
	:GUIDirectMessage(base)
{
	ShadowLevel =-1;
	ShadowNumber=-1;
	Phase	=-1;
	Page	=-1;
	Layer	=-1;
	ItemID	=-1;
	LibID	=-1;
	RepresentativeItem=NULL;

}
CmdGetCurrentInfo::CmdGetCurrentInfo(GUICmdPacketBase *gbase)
	:GUIDirectMessage(gbase)
{
	ShadowLevel =-1;
	ShadowNumber=-1;
	Phase	=-1;
	Page	=-1;
	Layer	=-1;
	ItemID	=-1;
	LibID	=-1;
	RepresentativeItem=NULL;
}

//=======================================================================

GUICmdChangeItemID::GUICmdChangeItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdChangeItemID::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false)	return false;
	if(::Load(f,AlgoName)==false)	return false;
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	if(::Load(f,OldItemID)==false)	return false;
	if(::Load(f,NewItemID)==false)	return false;

	return true;
}
bool	GUICmdChangeItemID::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false)	return false;
	if(::Save(f,AlgoName)==false)	return false;
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	if(::Save(f,OldItemID)==false)	return false;
	if(::Save(f,NewItemID)==false)	return false;

	return true;
}
void	GUICmdChangeItemID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckChangeItemID	*SendBack=GetSendBack(GUIAckChangeItemID,GetLayersBase(),"ANY","ANY",localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				AlgorithmItemRoot	*Item=Ap->GetItemData(Layer ,OldItemID);
				if(Item!=NULL){
					AlgorithmItemRoot	*NewItem=Ap->GetItemData(Layer ,NewItemID);
					if(NewItem==NULL){
						Item->SetID(NewItemID);
						SendBack->DupID=false;
						SendBack->NoItem=false;
						SendBack->DoneSuccessful=true;
					}
					else{
						SendBack->DupID=true;
						SendBack->NoItem=false;
						SendBack->DoneSuccessful=false;
					}
				}
				else{
					SendBack->DupID=false;
					SendBack->NoItem=true;
					SendBack->DoneSuccessful=false;
				}
			}
			else{
				SendBack->DupID=false;
				SendBack->NoItem=true;
				SendBack->DoneSuccessful=false;
			}
		}
		else{
			SendBack->DupID=false;
			SendBack->NoItem=true;
			SendBack->DoneSuccessful=false;
		}
	}
	else{
		SendBack->DupID=false;
		SendBack->NoItem=true;
		SendBack->DoneSuccessful=false;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckChangeItemID::GUIAckChangeItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUIAckChangeItemID::Load(QIODevice *f)
{
	if(::Load(f,DoneSuccessful)==false)	return false;
	if(::Load(f,NoItem)==false)	return false;
	if(::Load(f,DupID	)==false)	return false;

	return true;
}
bool	GUIAckChangeItemID::Save(QIODevice *f)
{
	if(::Save(f,DoneSuccessful)==false)	return false;
	if(::Save(f,NoItem)==false)	return false;
	if(::Save(f,DupID	)==false)	return false;

	return true;
}