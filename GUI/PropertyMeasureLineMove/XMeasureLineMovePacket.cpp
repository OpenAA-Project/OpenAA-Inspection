/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureLineMove\XMeasureLineMovePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XMeasureLineMovePacket.h"
#include "XMeasureLineMove.h"


GUICmdSendAddManualMeasureLineMove::GUICmdSendAddManualMeasureLineMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemClass		=0;
	Vector			=NULL;
	SelectedLibID	=-1;

	NoCalc			=false;
	GlobalPage1		=-1;
	ClosedItemID1	=-1;
	GlobalPage2		=-1;
	ClosedItemID2	=-1;
}

GUICmdSendAddManualMeasureLineMove::~GUICmdSendAddManualMeasureLineMove(void)
{
	if(Vector!=NULL){
		delete	Vector;
		Vector=NULL;
	}
}

bool	GUICmdSendAddManualMeasureLineMove::Load(QIODevice *f)
{
	if(::Load(f,BItem)==false)
		return false;
	int		VectorID;
	if(::Load(f,VectorID)==false)
		return false;

	Vector	=VectorLineBase::Create(VectorID);
	if(Vector->Load(f)==false)
		return false;
	if(::Load(f,ItemClass)==false)
		return false;

	if(::Load(f,SelectedLibID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(Area.Load(f)==false)
		return false;

	if(::Load(f,NoCalc)==false)
		return false;
	if(::Load(f,GlobalPage1)==false)
		return false;
	if(::Load(f,ClosedItemID1)==false)
		return false;
	if(::Load(f,GlobalPage2)==false)
		return false;
	if(::Load(f,ClosedItemID2)==false)
		return false;

	return true;
}
bool	GUICmdSendAddManualMeasureLineMove::Save(QIODevice *f)
{
	if(::Save(f,BItem)==false)
		return false;

	int	VectorID=Vector->GetID();
	if(::Save(f,VectorID)==false)
		return false;

	if(Vector->Save(f)==false)
		return false;
	if(::Save(f,ItemClass)==false)
		return false;

	if(::Save(f,SelectedLibID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(Area.Save(f)==false)
		return false;

	if(::Save(f,NoCalc)==false)
		return false;
	if(::Save(f,GlobalPage1)==false)
		return false;
	if(::Save(f,ClosedItemID1)==false)
		return false;
	if(::Save(f,GlobalPage2)==false)
		return false;
	if(::Save(f,ClosedItemID2)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualMeasureLineMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		CmdAddByteMeasureLineMoveItemPacket	Cmd(this);
		Cmd.Buff			=BItem;
		if(Vector!=NULL){
			Cmd.Vector			=Vector->CreateDup();
		}
		Cmd.LocalPage		=localPage;
		Cmd.ItemClass		=ItemClass;
		Cmd.SelectedLibID	=SelectedLibID;
		Cmd.ItemName		=ItemName;
		Cmd.Area			=Area;

		Cmd.NoCalc			=NoCalc;
		Cmd.GlobalPage1		=GlobalPage1;
		Cmd.ClosedItemID1	=ClosedItemID1;
		Cmd.GlobalPage2		=GlobalPage2;
		Cmd.ClosedItemID2	=ClosedItemID2;

		BBase->TransmitDirectly(&Cmd);
	}
}

GUICmdSendAddCSVMeasureLineMove::GUICmdSendAddCSVMeasureLineMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Vector=NULL;
}
GUICmdSendAddCSVMeasureLineMove::~GUICmdSendAddCSVMeasureLineMove(void)
{
	if(Vector!=NULL){
		delete	Vector;
		Vector=NULL;
	}
}
bool	GUICmdSendAddCSVMeasureLineMove::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);

	int		VectorID;
	if(::Load(f,VectorID)==false)
		return false;
	Vector	=VectorLineBase::Create(VectorID);
	if(Vector->Load(f)==false)
		return false;

	return true;
}
bool	GUICmdSendAddCSVMeasureLineMove::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;

	int	VectorID=Vector->GetID();
	if(::Save(f,VectorID)==false)
		return false;
	if(Vector->Save(f)==false)
		return false;

	return true;
}

void	GUICmdSendAddCSVMeasureLineMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		CmdAddByteMeasureLineMoveItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		if(Vector!=NULL){
			Cmd.Vector		=Vector->CreateDup();
		}
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

CmdReqMeasureLineMoveColorMap::CmdReqMeasureLineMoveColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdReqMeasureLineMoveColorMap::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	CmdReqMeasureLineMoveColorMap::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	CmdReqMeasureLineMoveColorMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAckMeasureLineMoveColorMap	*SendBack=GetSendBack(CmdAckMeasureLineMoveColorMap,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ImagePointerContainer Images;
	GetLayersBase()->GetPageData(localPage)->GetMasterImages(Images);
	RGBStock	PickupSamples;
	Area.CreateRGBStock(Images, PickupSamples);
		
	ColorSphere	*b=new ColorSphere();
	b->Create(PickupSamples);
	SendBack->Color.AddBase(b);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

CmdAckMeasureLineMoveColorMap::CmdAckMeasureLineMoveColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdAckMeasureLineMoveColorMap::Load(QIODevice *f)
{
	if(Color.Load(f)==false)
		return false;
	return true;
}
bool	CmdAckMeasureLineMoveColorMap::Save(QIODevice *f)
{
	if(Color.Save(f)==false)
		return false;
	return true;
}

void	CmdAckMeasureLineMoveColorMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


//==============================================================================================================
GUICmdReqItemList::GUICmdReqItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemList	*SendBack=GetSendBack(GUICmdSendItemList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->MakeList(localPage,GetLayersBase());

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendItemList::GUICmdSendItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendItemList::MakeList(int localPage ,LayersBase *PBase)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;

	MakeListPacket	Cmd(GetLayersBase());
	Cmd.ListInfo=&ListInfo;
	PData->TransmitDirectly(&Cmd);
}
	
bool	GUICmdSendItemList::Load(QIODevice *f)
{
	if(ListInfo.Load(f)==false)
		return false;
	return true;
}
	
bool	GUICmdSendItemList::Save(QIODevice *f)
{
	if(ListInfo.Save(f)==false)
		return false;
	return true;
}

//==============================================================================================================

GUICmdReqItemThreshold::GUICmdReqItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=0;
}

bool	GUICmdReqItemThreshold::Load(QIODevice *f)	
{	
	if(::Load(f,ItemID)==false)
		return false;
	return true;	
}

bool	GUICmdReqItemThreshold::Save(QIODevice *f)	
{	
	if(::Save(f,ItemID)==false)
		return false;
	return true;	
}
	
void	GUICmdReqItemThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemThreshold	*SendBack=GetSendBack(GUICmdSendItemThreshold,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;
	AlgorithmItemRoot	*a=PData->SearchIDItem(ItemID);
	if(a!=NULL){
		MeasureLineMoveItemBase	*ai=dynamic_cast<MeasureLineMoveItemBase *>(a);
		if(ai!=NULL){
			SendBack->ItemName=ai->GetItemName();
			CmdCreateThresholdPacket	PCmd(GetLayersBase());
			BBase->TransmitDirectly(&PCmd);
			SendBack->Thre	=PCmd.Thre;
			SendBack->Thre->CopyFrom(*ai->GetThresholdW());
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendItemThreshold::GUICmdSendItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Thre=NULL;
}
GUICmdSendItemThreshold::~GUICmdSendItemThreshold(void)
{
	if(Thre!=NULL){
		delete	Thre;
		Thre=NULL;
	}
}


bool	GUICmdSendItemThreshold::Load(QIODevice *f)
{
	if(Thre!=NULL){
		MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
		if(BBase==NULL)
			return false;
		CmdCreateThresholdPacket	PCmd(GetLayersBase());
		BBase->TransmitDirectly(&PCmd);
		Thre	=PCmd.Thre;
	}
	if(Thre->Load(f)==false)
		return false;

	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	GUICmdSendItemThreshold::Save(QIODevice *f)
{
	if(Thre->Save(f)==false)
		return false;

	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

GUICmdSetItemThreshold::GUICmdSetItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Thre=NULL;
}
GUICmdSetItemThreshold::~GUICmdSetItemThreshold(void)
{
	if(Thre!=NULL){
		delete	Thre;
		Thre=NULL;
	}
}

bool	GUICmdSetItemThreshold::Load(QIODevice *f)
{
	if(Thre!=NULL){
		MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
		if(BBase==NULL)
			return false;
		CmdCreateThresholdPacket	PCmd(GetLayersBase());
		BBase->TransmitDirectly(&PCmd);
		Thre	=PCmd.Thre;
	}
	if(Thre->Load(f)==false)
		return false;

	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdSetItemThreshold::Save(QIODevice *f)
{
	if(Thre->Save(f)==false)
		return false;

	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

void	GUICmdSetItemThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;
	AlgorithmItemRoot	*a=PData->SearchIDItem(ItemID);
	if(a!=NULL){
		MeasureLineMoveItemBase	*ai=dynamic_cast<MeasureLineMoveItemBase *>(a);
		if(ai!=NULL){
			ai->SetItemName(ItemName);
			ai->GetThresholdW()->CopyFrom(*Thre);
		}
	}
}

//=====================================================================================================

GUICmdReqMeasureLineMoveID::GUICmdReqMeasureLineMoveID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	GlobalX	=0;
	GlobalY	=0;
}

bool	GUICmdReqMeasureLineMoveID::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;

	return true;
}
bool	GUICmdReqMeasureLineMoveID::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;

	return true;
}

void	GUICmdReqMeasureLineMoveID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMeasureLineMoveID	*SendBack=GetSendBack(GUICmdAckMeasureLineMoveID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqMeasureLineMoveIDPacket	Cmd(this);

			if(GetLayersBase()->GetLocalMatrixFromGlobal(GlobalX ,GlobalY ,Cmd.LocalX,Cmd.LocalY)>=0){
				PData->TransmitDirectly(&Cmd);
				SendBack->ItemID	=Cmd.ItemID;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckMeasureLineMoveID::GUICmdAckMeasureLineMoveID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}
	
bool	GUICmdAckMeasureLineMoveID::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
bool	GUICmdAckMeasureLineMoveID::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}


//=====================================================================================================

GUICmdGenerateMeasure::GUICmdGenerateMeasure(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	OnlyGenerateFilmLen=false;
}

bool	GUICmdGenerateMeasure::Load(QIODevice *f)
{
	if(::Load(f,BladePickupRL)==false)	return false;
	if(::Load(f,BladePickupRH)==false)	return false;
	if(::Load(f,BladePickupGL)==false)	return false;
	if(::Load(f,BladePickupGH)==false)	return false;
	if(::Load(f,BladePickupBL)==false)	return false;
	if(::Load(f,BladePickupBH)==false)	return false;
	if(::Load(f,BladeLeft	)==false)	return false;
	if(::Load(f,BladeRight	)==false)	return false;
	if(::Load(f,LineLib		)==false)	return false;
	if(::Load(f,RxLineLib	)==false)	return false;
	if(::Load(f,MaskLib		)==false)	return false;
	if(::Load(f,DistanceLib	)==false)	return false;
	if(::Load(f,BladeHoleMinArea	)==false)	return false;
	if(::Load(f,BladeHoleErosionDot	)==false)	return false;
	if(BladeMeasureData.Load(f)==false)
		return false;
	if(FilmMeasureData.Load(f)==false)
		return false;
	if(::Load(f,OnlyGenerateFilmLen	)==false)	return false;
	return true;
}
bool	GUICmdGenerateMeasure::Save(QIODevice *f)
{
	if(::Save(f,BladePickupRL)==false)	return false;
	if(::Save(f,BladePickupRH)==false)	return false;
	if(::Save(f,BladePickupGL)==false)	return false;
	if(::Save(f,BladePickupGH)==false)	return false;
	if(::Save(f,BladePickupBL)==false)	return false;
	if(::Save(f,BladePickupBH)==false)	return false;
	if(::Save(f,BladeLeft	)==false)	return false;
	if(::Save(f,BladeRight	)==false)	return false;
	if(::Save(f,LineLib		)==false)	return false;
	if(::Save(f,RxLineLib	)==false)	return false;
	if(::Save(f,MaskLib		)==false)	return false;
	if(::Save(f,DistanceLib	)==false)	return false;
	if(::Save(f,BladeHoleMinArea	)==false)	return false;
	if(::Save(f,BladeHoleErosionDot	)==false)	return false;
	if(BladeMeasureData.Save(f)==false)
		return false;
	if(FilmMeasureData.Save(f)==false)
		return false;
	if(::Save(f,OnlyGenerateFilmLen	)==false)	return false;
	return true;
}

void	GUICmdGenerateMeasure::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdGenerateMeasure	RCmd(GetLayersBase());

			RCmd.BladePickupRL		=BladePickupRL;
			RCmd.BladePickupRH		=BladePickupRH;
			RCmd.BladePickupGL		=BladePickupGL;
			RCmd.BladePickupGH		=BladePickupGH;
			RCmd.BladePickupBL		=BladePickupBL;
			RCmd.BladePickupBH		=BladePickupBH;
			RCmd.BladeLeft			=BladeLeft;
			RCmd.BladeRight			=BladeRight;
			RCmd.LineLib			=LineLib;
			RCmd.RxLineLib			=RxLineLib;
			RCmd.DistanceLib		=DistanceLib;
			RCmd.MaskLib			=MaskLib;
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.FilmMeasureData	=FilmMeasureData;
			RCmd.BladeHoleMinArea	=BladeHoleMinArea	;
			RCmd.BladeHoleErosionDot=BladeHoleErosionDot;
			RCmd.OnlyGenerateFilmLen=OnlyGenerateFilmLen;

			PData->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
}


//=====================================================================================================

GUICmdReqCorrentValues::GUICmdReqCorrentValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqCorrentValues::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)
		return false;
	if(::Load(f,Mastered)	==false)
		return false;
	return true;
}
bool	GUICmdReqCorrentValues::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)
		return false;
	if(::Save(f,Mastered)	==false)
		return false;
	return true;
}

void	GUICmdReqCorrentValues::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckCorrentValues	*SendBack=GetSendBack(GUICmdAckCorrentValues,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqCorrentValues	RCmd(GetLayersBase());
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.Mastered			=Mastered;
			PData->TransmitDirectly(&RCmd);
			SendBack->BladeMeasureData	=RCmd.BladeMeasureData;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckCorrentValues::GUICmdAckCorrentValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckCorrentValues::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckCorrentValues::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)
		return false;
	return true;
}

//=====================================================================================================

GUICmdSetCorrentValues::GUICmdSetCorrentValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetCorrentValues::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)
		return false;
	if(::Load(f,LineLib)==false)
		return false;
	if(::Load(f,DistanceLib)==false)
		return false;
	if(::Load(f,BladePickupRL)==false)	return false;
	if(::Load(f,BladePickupRH)==false)	return false;
	if(::Load(f,BladePickupGL)==false)	return false;
	if(::Load(f,BladePickupGH)==false)	return false;
	if(::Load(f,BladePickupBL)==false)	return false;
	if(::Load(f,BladePickupBH)==false)	return false;
	if(::Load(f,MaskLib		)==false)	return false;

	return true;
}
bool	GUICmdSetCorrentValues::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)
		return false;
	if(::Save(f,LineLib)==false)
		return false;
	if(::Save(f,DistanceLib)==false)
		return false;
	if(::Save(f,BladePickupRL)==false)	return false;
	if(::Save(f,BladePickupRH)==false)	return false;
	if(::Save(f,BladePickupGL)==false)	return false;
	if(::Save(f,BladePickupGH)==false)	return false;
	if(::Save(f,BladePickupBL)==false)	return false;
	if(::Save(f,BladePickupBH)==false)	return false;
	if(::Save(f,MaskLib		)==false)	return false;
	return true;
}

void	GUICmdSetCorrentValues::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetCorrectValues	RCmd(GetLayersBase());
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.LineLib			=LineLib;
			RCmd.DistanceLib		=DistanceLib;
			RCmd.BladePickupRL		=BladePickupRL;
			RCmd.BladePickupRH		=BladePickupRH;
			RCmd.BladePickupGL		=BladePickupGL;
			RCmd.BladePickupGH		=BladePickupGH;
			RCmd.BladePickupBL		=BladePickupBL;
			RCmd.BladePickupBH		=BladePickupBH;
			RCmd.MaskLib			=MaskLib;
			PData->TransmitDirectly(&RCmd);
		}
	}
}

//=====================================================================================================

GUICmdSetOnlyBladeThreshold::GUICmdSetOnlyBladeThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetOnlyBladeThreshold::Load(QIODevice *f)
{
	if(BladeMeasureData.Load(f)==false)
		return false;
	if(FilmMeasureData.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdSetOnlyBladeThreshold::Save(QIODevice *f)
{
	if(BladeMeasureData.Save(f)==false)
		return false;
	if(FilmMeasureData.Save(f)==false)
		return false;

	return true;
}

void	GUICmdSetOnlyBladeThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetOnlyBladeThreshold	RCmd(GetLayersBase());
			RCmd.BladeMeasureData	=BladeMeasureData;
			RCmd.FilmMeasureData	=FilmMeasureData;
			PData->TransmitDirectly(&RCmd);
		}
	}
}

//=====================================================================================================

GUICmdSetMeasureEndPoint::GUICmdSetMeasureEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetMeasureEndPoint::Load(QIODevice *f)
{
	if(::Load(f,EndNo)==false)	return false;
	if(::Load(f,MeasureNo)==false)	return false;
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	return true;
}
bool	GUICmdSetMeasureEndPoint::Save(QIODevice *f)
{
	if(::Save(f,EndNo)==false)	return false;
	if(::Save(f,MeasureNo)==false)	return false;
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;
	return true;
}
void	GUICmdSetMeasureEndPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetMeasureEndPoint	RCmd(GetLayersBase());
			RCmd.EndNo		=EndNo;
			RCmd.MeasureNo	=MeasureNo;
			RCmd.X			=LocalX;
			RCmd.Y			=LocalY;

			PData->TransmitDirectly(&RCmd);
		}
	}

}

//=====================================================================================================

GUICmdReqListData::GUICmdReqListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqListData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckListData	*SendBack=GetSendBack(GUICmdAckListData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(phase);
			AlgorithmInPageRoot		*PData=Ah->GetPageData(localPage);
			if(PData!=NULL){
				CmdReqDistancePacket	RCmd(GetLayersBase());
				PData->TransmitDirectly(&RCmd);
				for(MeasureDistanceItemInfo *L=RCmd.DataList.GetFirst();L!=NULL;L=L->GetNext()){
					L->Data.Phase=phase;
				}
				SendBack->ListData	+=RCmd.DataList;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckListData::GUICmdAckListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckListData::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckListData::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)
		return false;
	return true;
}

	
GUICmdSetCorrectValue::GUICmdSetCorrectValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetCorrectValue::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,OKLengthLUnit)==false)
		return false;
	if(::Load(f,OKLengthHUnit)==false)
		return false;
	return true;
}
bool	GUICmdSetCorrectValue::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,OKLengthLUnit)==false)
		return false;
	if(::Save(f,OKLengthHUnit)==false)
		return false;
	return true;
}

void	GUICmdSetCorrectValue::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot		*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetDistanceCorrectValue	RCmd(GetLayersBase());
			RCmd.Phase			=Phase		;
			RCmd.Page			=Page		;
			RCmd.ItemID			=ItemID		;
			RCmd.OKLengthLUnit	=OKLengthLUnit	;
			RCmd.OKLengthHUnit	=OKLengthHUnit	;	

			PData->TransmitDirectly(&RCmd);
		}
	}
}
//=====================================================================================================
GUICmdAddDistance::GUICmdAddDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddDistance::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false)
		return false;
	if(::Load(f,LocalY1)==false)
		return false;
	if(::Load(f,LocalX2)==false)
		return false;
	if(::Load(f,LocalY2)==false)
		return false;
	if(::Load(f,LineLength)==false)
		return false;
	if(::Load(f,LineLibID1)==false)
		return false;
	if(::Load(f,LineLibID2)==false)
		return false;
	if(::Load(f,DistanceLibID)==false)
		return false;

	return true;
}
bool	GUICmdAddDistance::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false)
		return false;
	if(::Save(f,LocalY1)==false)
		return false;
	if(::Save(f,LocalX2)==false)
		return false;
	if(::Save(f,LocalY2)==false)
		return false;
	if(::Save(f,LineLength)==false)
		return false;
	if(::Save(f,LineLibID1)==false)
		return false;
	if(::Save(f,LineLibID2)==false)
		return false;
	if(::Save(f,DistanceLibID)==false)
		return false;

	return true;
}

void	GUICmdAddDistance::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdAddDistance	RCmd(GetLayersBase());
			RCmd.X1				=LocalX1		;
			RCmd.Y1				=LocalY1		;
			RCmd.X2				=LocalX2		;
			RCmd.Y2				=LocalY2		;
			RCmd.LineLength		=LineLength		;
			RCmd.LineLibID1		=LineLibID1		;	
			RCmd.LineLibID2		=LineLibID2		;	
			RCmd.DistanceLibID	=DistanceLibID	;	
			PData->TransmitDirectly(&RCmd);
		}
	}
}

//=====================================================================================================
GUICmdDeleteMeasureDistance::GUICmdDeleteMeasureDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeleteMeasureDistance::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,MeasureNo)==false)
		return false;

	return true;
}
bool	GUICmdDeleteMeasureDistance::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,MeasureNo)==false)
		return false;

	return true;
}

void	GUICmdDeleteMeasureDistance::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot		*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			CmdDeleteMeasureDistance	RCmd(GetLayersBase());
			RCmd.MeasureNo				=MeasureNo		;
			PData->TransmitDirectly(&RCmd);
		}
	}
}


//=====================================================================================================

GUICmdReqMeasureLineInfo::GUICmdReqMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMeasureLineInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,DistanceItemID)==false)
		return false;
	if(::Load(f,EndNo)==false)
		return false;
	if(::Load(f,MeasureNo)==false)
		return false;

	return true;
}
bool	GUICmdReqMeasureLineInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,DistanceItemID)==false)
		return false;
	if(::Save(f,EndNo)==false)
		return false;
	if(::Save(f,MeasureNo)==false)
		return false;

	return true;
}

void	GUICmdReqMeasureLineInfo::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMeasureLineInfo	*SendBack=GetSendBack(GUICmdAckMeasureLineInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqMeasureLineInfo	RCmd(GetLayersBase());
			RCmd.Phase	=Phase;
			RCmd.DistanceItemID	=DistanceItemID;
			RCmd.EndNo			=EndNo;
			RCmd.MeasureNo		=MeasureNo;
			PData->TransmitDirectly(&RCmd);
			SendBack->SearchDot	=RCmd.SearchDot;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMeasureLineInfo::GUICmdAckMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMeasureLineInfo::Load(QIODevice *f)
{
	if(::Load(f,SearchDot)==false)
		return false;

	return true;
}
bool	GUICmdAckMeasureLineInfo::Save(QIODevice *f)
{
	if(::Save(f,SearchDot)==false)
		return false;

	return true;
}

GUICmdSetMeasureLineInfo::GUICmdSetMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetMeasureLineInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,DistanceItemID)==false)
		return false;
	if(::Load(f,EndNo)==false)
		return false;
	if(::Load(f,MeasureNo)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}
bool	GUICmdSetMeasureLineInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,DistanceItemID)==false)
		return false;
	if(::Save(f,EndNo)==false)
		return false;
	if(::Save(f,MeasureNo)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}
void	GUICmdSetMeasureLineInfo::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetMeasureLineInfo	RCmd(GetLayersBase());
			RCmd.Phase	=Phase;
			RCmd.DistanceItemID	=DistanceItemID;
			RCmd.EndNo			=EndNo;
			RCmd.MeasureNo		=MeasureNo;
			RCmd.SearchDot		=SearchDot;
			PData->TransmitDirectly(&RCmd);
		}
	}
}

GUICmdSetMeasureLineInfoAll::GUICmdSetMeasureLineInfoAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetMeasureLineInfoAll::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,DistanceItemID)==false)
		return false;
	if(::Load(f,EndNo)==false)
		return false;
	if(::Load(f,MeasureNo)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}
bool	GUICmdSetMeasureLineInfoAll::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,DistanceItemID)==false)
		return false;
	if(::Save(f,EndNo)==false)
		return false;
	if(::Save(f,MeasureNo)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}
void	GUICmdSetMeasureLineInfoAll::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetMeasureLineInfoAll	RCmd(GetLayersBase());
			RCmd.Phase	=Phase;
			RCmd.DistanceItemID	=DistanceItemID;
			RCmd.EndNo			=EndNo;
			RCmd.MeasureNo		=MeasureNo;
			RCmd.SearchDot		=SearchDot;
			PData->TransmitDirectly(&RCmd);
		}
	}
}


//=====================================================================================================

GUICmdReqMeasureLineMovePosition::GUICmdReqMeasureLineMovePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMeasureLineMovePosition::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
bool	GUICmdReqMeasureLineMovePosition::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

void	GUICmdReqMeasureLineMovePosition::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMeasureLineMovePosition	*SendBack=GetSendBack(GUICmdAckMeasureLineMovePosition,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqMeasureLinePosition	RCmd(GetLayersBase());
			RCmd.Phase	=Phase;
			RCmd.DistanceItemID	=ItemID;
			PData->TransmitDirectly(&RCmd);
			SendBack->Point1X=RCmd.RetPos1X;
			SendBack->Point1Y=RCmd.RetPos1Y;
			SendBack->Point2X=RCmd.RetPos2X;
			SendBack->Point2Y=RCmd.RetPos2Y;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMeasureLineMovePosition::GUICmdAckMeasureLineMovePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMeasureLineMovePosition::Load(QIODevice *f)
{
	if(::Load(f,Point1X)==false)	return false;
	if(::Load(f,Point1Y)==false)	return false;
	if(::Load(f,Point2X)==false)	return false;
	if(::Load(f,Point2Y)==false)	return false;

	return true;
}
bool	GUICmdAckMeasureLineMovePosition::Save(QIODevice *f)
{
	if(::Save(f,Point1X)==false)	return false;
	if(::Save(f,Point1Y)==false)	return false;
	if(::Save(f,Point2X)==false)	return false;
	if(::Save(f,Point2Y)==false)	return false;

	return true;
}
//=====================================================================================================
GUICmdReqChangeMeasureLineMoveEndPoint::GUICmdReqChangeMeasureLineMoveEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqChangeMeasureLineMoveEndPoint::Load(QIODevice *f)
{
	if(::Load(f,Point1)==false)	return false;
	if(::Load(f,Point2)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	return true;
}
bool	GUICmdReqChangeMeasureLineMoveEndPoint::Save(QIODevice *f)
{
	if(::Save(f,Point1)==false)	return false;
	if(::Save(f,Point2)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;

	return true;
}
void	GUICmdReqChangeMeasureLineMoveEndPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqChangeMeasureLineMoveEndPoint	Cmd(GetLayersBase());
			Cmd.Point1=Point1;
			Cmd.Point2=Point2;
			Cmd.ItemID=ItemID;
			Cmd.LocalX=LocalX;
			Cmd.LocalY=LocalY;

			PData->TransmitDirectly(&Cmd);
		}
	}

}