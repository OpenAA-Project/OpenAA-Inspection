#include "XPropertyXRay3DPacket.h"
#include "XXRay3D.h"
#include "XGeneralFunc.h"
	
GUICmdLoadImages::GUICmdLoadImages(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}


bool	GUICmdLoadImages::Load(QIODevice *f)
{
	if(::Load(f,ImageFileNames)==false)	return false;
	return true;
}
bool	GUICmdLoadImages::Save(QIODevice *f)
{
	if(::Save(f,ImageFileNames)==false)	return false;
	return true;
}

void	GUICmdLoadImages::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		XRay3DInPage	*PData=dynamic_cast<XRay3DInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdLoadImages	Cmd(GetLayersBase());
			Cmd.ImageFileNames		=ImageFileNames	;	;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

GUICmdSetPointY::GUICmdSetPointY(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetPointY::Load(QIODevice *f)
{
	if(::Load(f,PointToDraw)==false)	return false;
	return true;
}
bool	GUICmdSetPointY::Save(QIODevice *f)
{
	if(::Save(f,PointToDraw)==false)	return false;
	return true;
}

void	GUICmdSetPointY::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		XRay3DInPage	*PData=dynamic_cast<XRay3DInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdSetPointY	Cmd(GetLayersBase());
			Cmd.PointToDraw		=PointToDraw	;	;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

GUICmdReqSmooth::GUICmdReqSmooth(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSmooth::Load(QIODevice *f)
{
	return true;
}

bool	GUICmdReqSmooth::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSmooth::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		XRay3DInPage	*PData=dynamic_cast<XRay3DInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqSmooth	Cmd(GetLayersBase());
			PData->TransmitDirectly(&Cmd);
		}
	}
}

GUICmdReqEmphasize::GUICmdReqEmphasize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqEmphasize::Load(QIODevice *f)
{
	return true;
}

bool	GUICmdReqEmphasize::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqEmphasize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		XRay3DInPage	*PData=dynamic_cast<XRay3DInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqEmphasize	Cmd(GetLayersBase());
			PData->TransmitDirectly(&Cmd);
		}
	}
}

GUICmdReqMatchFile::GUICmdReqMatchFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMatchFile::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)	return false;
	return true;
}
bool	GUICmdReqMatchFile::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)	return false;
	return true;
}

void	GUICmdReqMatchFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMatchFile	*SendBack=GetSendBack(GUICmdAckMatchFile,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		XRay3DInPage	*PData=dynamic_cast<XRay3DInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdMatchFile	Cmd(GetLayersBase());
			Cmd.FileName		=FileName	;	;
			PData->TransmitDirectly(&Cmd);
			SendBack->RetFileNo = Cmd.RetFileNo;
			SendBack->RetX = Cmd.RetX;
			SendBack->RetY = Cmd.RetY;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMatchFile::GUICmdAckMatchFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMatchFile::Load(QIODevice *f)
{
	if(::Load(f,RetFileNo)==false)	return false;
	if(::Load(f,RetX)==false)	return false;
	if(::Load(f,RetY)==false)	return false;
	return true;
}

bool	GUICmdAckMatchFile::Save(QIODevice *f)
{
	if(::Save(f,RetFileNo)==false)	return false;
	if(::Save(f,RetX)==false)	return false;
	if(::Save(f,RetY)==false)	return false;
	return true;
}