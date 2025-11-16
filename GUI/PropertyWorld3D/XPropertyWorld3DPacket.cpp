#include "XPropertyWorld3DPacket.h"
#include "XGeneralFunc.h"
#include "XWorld3D.h"

GUICmdLoadStepFile::GUICmdLoadStepFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdLoadStepFile::Load(QIODevice *f)
{
	if(::Load(f,FArray)==false)	return false;
	return true;
}
bool	GUICmdLoadStepFile::Save(QIODevice *f)
{
	if(::Save(f,FArray)==false)	return false;
	return true;
}

void	GUICmdLoadStepFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	World3DBase *BBase=(World3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"World3D");
	if(BBase!=NULL){
		World3DInPage	*PData=dynamic_cast<World3DInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdLoadStepFile	Cmd(this);
			Cmd.FArray		=FArray;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

