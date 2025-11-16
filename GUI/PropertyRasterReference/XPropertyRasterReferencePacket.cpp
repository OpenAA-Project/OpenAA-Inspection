#include "XGUIRasterPacket.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XRaster.h"
#include "XDataAlgorithm.h"
#include <QString>
#include <QBuffer>
#include <QByteArray>
#include "XRasterPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==========================================================================================
GUICmdMakeRasterReferenceItem::GUICmdMakeRasterReferenceItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMakeRasterReferenceItem::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdMakeRasterReferenceItem::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false)
		return false;
	return true;
}

void	GUICmdMakeRasterReferenceItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage==NULL)
		return;
	CmdMakeRasterReferenceItem	Cmd(this);
	Cmd.LocalArea		=LocalArea;
	PPage->TransmitDirectly(&Cmd);
}
//==========================================================================================

GUICmdReqRasterReference::GUICmdReqRasterReference(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqRasterReference::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterReference	*SendBack=GetSendBack(GUICmdAckRasterReference,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		CmdReqRasterReference	Cmd(GetLayersBase());
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
		SendBack->ColorProfiler=Cmd.ColorProfile;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRasterReference::GUICmdAckRasterReference(LayersBase *Base ,const QString &emitterRoot,const QString &emitterName ,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckRasterReference::Load(QIODevice *f)
{
	if(ColorProfiler.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckRasterReference::Save(QIODevice *f)
{
	if(ColorProfiler.Save(f)==false)	return false;
	return true;
}

GUICmdMakeAutoRasterReference::GUICmdMakeAutoRasterReference(LayersBase *Base ,const QString &emitterRoot,const QString &emitterName ,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMakeAutoRasterReference::Load(QIODevice *f)
{
	if(::Load(f,ColorMergin	)==false)	return false;
	if(::Load(f,MinItemArea	)==false)	return false;
	if(::Load(f,ShrinkSize	)==false)	return false;
	return true;
}
bool	GUICmdMakeAutoRasterReference::Save(QIODevice *f)
{
	if(::Save(f,ColorMergin	)==false)	return false;
	if(::Save(f,MinItemArea	)==false)	return false;
	if(::Save(f,ShrinkSize	)==false)	return false;
	return true;
}
void	GUICmdMakeAutoRasterReference::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		CmdMakeAutoRasterReference	Cmd(GetLayersBase());
		Cmd.ColorMergin	=ColorMergin;
		Cmd.MinItemArea	=MinItemArea;
		Cmd.ShrinkSize	=ShrinkSize;
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
}

//==========================================================================================
GUICmdSaveDefaultColorProfile::GUICmdSaveDefaultColorProfile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSaveDefaultColorProfile::Load(QIODevice *f)
{
	if(ColorProfiler.Load(f)==false)	return false;
	return true;
}
bool	GUICmdSaveDefaultColorProfile::Save(QIODevice *f)
{
	if(ColorProfiler.Save(f)==false)	return false;
	return true;
}

void	GUICmdSaveDefaultColorProfile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		CmdSaveDefaultColorProfile	Cmd(GetLayersBase());
		Cmd.ColorProfiler	=ColorProfiler;
		Base->TransmitDirectly(&Cmd);
	}
}
