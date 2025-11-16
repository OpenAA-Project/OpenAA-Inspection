#include "XLinePatternPacket.h"
#include "XGeneralFunc.h"
#include "XPropertyLinePatternCommon.h"

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
	CmdAddLinePatternItemPacket	PPacket(this);
	PPacket.LibID		=LibID;
	PPacket.LayerList	=LayerList;
	PPacket.Area		=Area;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&PPacket);
	}
	SendAck(localPage);
}



GUICmdSendAddManualLinePattern::GUICmdSendAddManualLinePattern(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Vector			=NULL;
	SelectedLibID	=-1;
}

GUICmdSendAddManualLinePattern::~GUICmdSendAddManualLinePattern(void)
{
	if(Vector!=NULL){
		delete	Vector;
		Vector=NULL;
	}
}

bool	GUICmdSendAddManualLinePattern::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);

	if(LayerList.Load(f)==false)
		return false;
	int		VectorID;
	if(::Load(f,VectorID)==false)
		return false;

	Vector	=VectorLineBase::Create(VectorID);
	if(Vector->Load(f)==false)
		return false;

	if(::Load(f,SelectedLibID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(Area.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdSendAddManualLinePattern::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;

	if(LayerList.Save(f)==false)
		return false;
	int	VectorID=Vector->GetID();
	if(::Save(f,VectorID)==false)
		return false;

	if(Vector->Save(f)==false)
		return false;

	if(::Save(f,SelectedLibID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(Area.Save(f)==false)
		return false;

	return true;
}

void	GUICmdSendAddManualLinePattern::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LinePatternBase *BBase=(LinePatternBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(BBase!=NULL){
		CmdAddByteLinePatternItemPacket	Cmd(this);
		Cmd.Buff			=BItem;
		if(Vector!=NULL){
			Cmd.Vector			=Vector->CreateDup();
		}
		Cmd.LayerList		=LayerList;
		Cmd.SelectedLibID	=SelectedLibID;
		Cmd.ItemName		=ItemName;
		Cmd.Area			=Area;

		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
}
GUIReqLinePatternListForPacketPack::GUIReqLinePatternListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUIReqLinePatternListForPacketPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckLinePatternListForPacketPack	*SendBack=GetSendBack(GUIAckLinePatternListForPacketPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(Ab!=NULL){
		MakeListPacket	RCmd(GetLayersBase());
		RCmd.ListInfo=&SendBack->Data;
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&RCmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckLinePatternListForPacketPack::GUIAckLinePatternListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIAckLinePatternListForPacketPack::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUIAckLinePatternListForPacketPack::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

//=======================================================================================
GUIReqGenerateLinePatternItems::GUIReqGenerateLinePatternItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIReqGenerateLinePatternItems::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUIReqGenerateLinePatternItems::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUIReqGenerateLinePatternItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateLinePatternPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}


//=============================================================================================

GUICmdReqSetButtonMode::GUICmdReqSetButtonMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSetButtonMode::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	Mode=(ButtonMode)d;
	if(::Load(f,InstForm)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSetButtonMode::Save(QIODevice *f)
{
	BYTE	d=(BYTE)Mode;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,InstForm)==false){
		return false;
	}
	return true;
}
void	GUICmdReqSetButtonMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstForm);
	if(L!=NULL){
		CmdReqSetButtonMode	Cmd(this);
		Cmd.Mode=Mode;
		L->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================

GUICmdReqBlockInfoList::GUICmdReqBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBlockInfoList	*SendBack=GetSendBack(GUICmdSendBlockInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendBlockInfoList::GUICmdSendBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendBlockInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	BlockInfos.RemoveAll();
	for(int i=0;i<N;i++){
		BlockInfoList	*a=new BlockInfoList();
		if(a->Load(f)==false)
			return false;
		BlockInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendBlockInfoList::Save(QIODevice *f)
{
	int	N=BlockInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(BlockInfoList	*a=BlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendBlockInfoList::Make(int localPage)
{
	LinePatternBase	*BBase=(LinePatternBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(BBase!=NULL){
		CmdBlockInfoListPacket	Cmd(this);
		Cmd.LocalPage=localPage;
		Cmd.BlockInfos=&BlockInfos;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
}
//=============================================================================================

GUICmdReqRemoveAllOriginal::GUICmdReqRemoveAllOriginal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdReqRemoveAllOriginal::Load(QIODevice *f)
{
	if(::Load(f,GeneratedOrigin)==false)
		return false;
	return true;
}
	
bool	GUICmdReqRemoveAllOriginal::Save(QIODevice *f)
{
	if(::Save(f,GeneratedOrigin)==false)
		return false;
	return true;
}

	
void	GUICmdReqRemoveAllOriginal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(BBase!=NULL){
		CmdRemoveAllOriginalLinePatternItems	Cmd(GetLayersBase());
		Cmd.GeneratedOrigin			=GeneratedOrigin;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdChangeLinePatternThreshold::GUICmdChangeLinePatternThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LinePatternLibID=-1;
}

bool	GUICmdChangeLinePatternThreshold::Load(QIODevice *f)
{
	if(::Load(f,LinePatternLibID)==false)
		return false;
	if(::Load(f,InfosData)==false)
		return false;
	return true;
}	
bool	GUICmdChangeLinePatternThreshold::Save(QIODevice *f)
{
	if(::Save(f,LinePatternLibID)==false)
		return false;
	if(::Save(f,InfosData)==false)
		return false;
	return true;
}
	
void	GUICmdChangeLinePatternThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
	if(BBase!=NULL){
		ChangeLinePatternsThresholdCommon	Cmd(GetLayersBase());
		Cmd.LinePatternLibID	=LinePatternLibID;
		Cmd.InfosData			=InfosData;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}