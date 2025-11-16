#include "XNickInspectionPacket.h"
#include "XGeneralFunc.h"


GUICmdSendAddManualBlock::GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	LibID=-1;
}

bool	GUICmdSendAddManualBlock::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendAddManualBlock::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAddNickInspectionItemPacket	PPacket(this);
	PPacket.LibID		=LibID;
	PPacket.LayerList	=LayerList;
	PPacket.Area		=Area;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&PPacket);
	}
	SendAck(localPage);
}


GUIReqNickInspectionListForPacketPack::GUIReqNickInspectionListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUIReqNickInspectionListForPacketPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckNickInspectionListForPacketPack	*SendBack=GetSendBack(GUIAckNickInspectionListForPacketPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
	if(Ab!=NULL){
		MakeListPacket	RCmd(GetLayersBase());
		RCmd.ListInfo=&SendBack->Data;
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&RCmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckNickInspectionListForPacketPack::GUIAckNickInspectionListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIAckNickInspectionListForPacketPack::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUIAckNickInspectionListForPacketPack::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

//=======================================================================================
GUIReqGenerateNickInspectionItems::GUIReqGenerateNickInspectionItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIReqGenerateNickInspectionItems::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;

	return true;
}

bool	GUIReqGenerateNickInspectionItems::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;

	return true;
}

void	GUIReqGenerateNickInspectionItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateNickInspectionPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}


//=======================================================================================
GUIReqTestMap::GUIReqTestMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIReqTestMap::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUIReqTestMap::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUIReqTestMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdTestNickInspectionPacket	PTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
	if(Ab!=NULL){
		PTestPacket.LayerList=LayerList;
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}

//=======================================================================================
GUIClearMap::GUIClearMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUIClearMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearNickInspectionPacket	PTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}
