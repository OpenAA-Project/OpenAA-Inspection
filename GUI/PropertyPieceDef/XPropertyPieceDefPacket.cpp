#include "PropertyPieceDefResource.h"
#include"XPropertyPieceDefPacket.h"
#include "XPieceDef.h"
#include "XGeneralFunc.h"

GUICmdAddPieceAreaManual::GUICmdAddPieceAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdAddPieceAreaManual::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAddPieceAreaManual::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddPieceAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoCreatePieceDefManual	Da(GetLayersBase());
		Da.Area=Area;
		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//==========================================================================================
GUICmdReqSeed::GUICmdReqSeed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqSeed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSeed	*SendBack=GetSendBack(GUICmdAckSeed,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoReqSeed	Da(GetLayersBase());
		Da.Seed			=&SendBack->Seed;
		Da.OriginalArea	=&SendBack->OriginalArea;
		PPage->TransmitDirectly(&Da);
		SendBack->SweepNumber=Da.SweepNumber;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSeed::GUICmdAckSeed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckSeed::Load(QIODevice *f)
{
	if(Seed.Load(f)==false)
		return false;
	if(OriginalArea.Load(f)==false)
		return false;
	if(::Load(f,SweepNumber)==false)
		return false;
	return true;
}
bool	GUICmdAckSeed::Save(QIODevice *f)
{
	if(Seed.Save(f)==false)
		return false;
	if(OriginalArea.Save(f)==false)
		return false;
	if(::Save(f,SweepNumber)==false)
		return false;
	return true;
}

GUICmdSweepSeed::GUICmdSweepSeed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSweepSeed::Load(QIODevice *f)
{
	if(Seed.Load(f)==false)
		return false;
	if(OriginalArea.Load(f)==false)
		return false;
	if(::Load(f,SweepNumber)==false)
		return false;
	return true;
}
bool	GUICmdSweepSeed::Save(QIODevice *f)
{
	if(Seed.Save(f)==false)
		return false;
	if(OriginalArea.Save(f)==false)
		return false;
	if(::Save(f,SweepNumber)==false)
		return false;
	return true;
}
void	GUICmdSweepSeed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoSweepSeed	Da(GetLayersBase());
		Da.Seed=&Seed;
		Da.OriginalArea	=&OriginalArea;
		Da.SweepNumber	=SweepNumber;
		PPage->TransmitDirectly(&Da);
	}
}


//==================================================================================

GUICmdReqDefList::GUICmdReqDefList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDefList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDefList	*SendBack=GetSendBack(GUICmdSendDefList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoReqDList	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->DefList=Da.DefList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendDefList::GUICmdSendDefList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendDefList::Load(QIODevice *f)
{
	if(DefList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendDefList::Save(QIODevice *f)
{
	if(DefList.Load(f)==false)
		return false;
	return true;
}


GUICmdCopyItemFromOrg::GUICmdCopyItemFromOrg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	OrgGlobalPage	=0;
	SweepNumber		=-1;
	SeedCount		=0;
}

bool	GUICmdCopyItemFromOrg::Load(QIODevice *f)
{	
	if(::Load(f,OrgGlobalPage)==false)
		return false;
	if(::Load(f,SeedData)==false)
		return false;
	if(::Load(f,SweepNumber)==false)
		return false;
	if(OriginalArea.Load(f)==false)
		return false;
	if(::Load(f,SeedCount)==false)
		return false;
	return true;
}
bool	GUICmdCopyItemFromOrg::Save(QIODevice *f)
{	
	if(::Save(f,OrgGlobalPage)==false)
		return false;
	if(::Save(f,SeedData)==false)
		return false;
	if(::Save(f,SweepNumber)==false)
		return false;
	if(OriginalArea.Save(f)==false)
		return false;
	if(::Save(f,SeedCount)==false)
		return false;
	return true;
}

void	GUICmdCopyItemFromOrg::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoCopyItemFromOrg	Da(GetLayersBase());
		Da.OrgGlobalPage=OrgGlobalPage;
		Da.SeedData		=SeedData;
		Da.SweepNumber	=SweepNumber;
		Da.OriginalArea	=OriginalArea;
		Da.SeedCount	=SeedCount;
		PPage->TransmitDirectly(&Da);
	}
}

//==================================================================================

GUICmdReqSeedData::GUICmdReqSeedData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqSeedData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSeedData	*SendBack=GetSendBack(GUICmdAckSeedData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoReqSeedData	Da(GetLayersBase());
		Da.SeedData		=&SendBack->SeedData;
		Da.SeedCount	=0;
		Da.OriginalArea	=&SendBack->OriginalArea;
		PPage->TransmitDirectly(&Da);
		SendBack->SweepNumber	=Da.SweepNumber;
		SendBack->SeedCount		=Da.SeedCount;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSeedData::GUICmdAckSeedData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	SeedCount=0;
	SweepNumber=0;
}

bool	GUICmdAckSeedData::Load(QIODevice *f)
{
	if(::Load(f,SeedCount)==false)
		return false;
	if(::Load(f,SweepNumber)==false)
		return false;
	if(::Load(f,SeedData)==false)
		return false;
	if(OriginalArea.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckSeedData::Save(QIODevice *f)
{
	if(::Save(f,SeedCount)==false)
		return false;
	if(::Save(f,SweepNumber)==false)
		return false;
	if(::Save(f,SeedData)==false)
		return false;
	if(OriginalArea.Save(f)==false)
		return false;
	return true;
}

//==================================================================================

GUICmdMatchItems::GUICmdMatchItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdMatchItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceDef");
	if(PBase==NULL)
		return;
	PieceDefInPage	*PPage=dynamic_cast<PieceDefInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAlgoMatchItems	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
	}
}
