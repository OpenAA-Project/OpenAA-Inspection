#include "XGUIMultiFileMapPacket.h"
#include "XGeneralFunc.h"


GUICmdReqMultiFileMapInfo::GUICmdReqMultiFileMapInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMultiFileMapInfo::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;

	return true;
}

bool	GUICmdReqMultiFileMapInfo::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;

	return true;
}

void	GUICmdReqMultiFileMapInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMultiFileMapInfo	*SendBack=GetSendBack(GUICmdAckMultiFileMapInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MultiFileMap");
	CmdReqMultiFileMapInfo	Cmd(GetLayersBase());
	Cmd.GlobalX	=GlobalX;
	Cmd.GlobalY	=GlobalY;
	Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	SendBack->FileName	= Cmd.FileName;
	SendBack->PosX		= Cmd.PosX;
	SendBack->PosY		= Cmd.PosY;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckMultiFileMapInfo::GUICmdAckMultiFileMapInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	PosX=-1;
	PosY=-1;
}

bool	GUICmdAckMultiFileMapInfo::Save(QIODevice *f)
{
	if(::Save(f,PosX)==false)
		return false;
	if(::Save(f,PosY)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;

	return true;
}
bool	GUICmdAckMultiFileMapInfo::Load(QIODevice *f)
{
	if(::Load(f,PosX)==false)
		return false;
	if(::Load(f,PosY)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;

	return true;
}
