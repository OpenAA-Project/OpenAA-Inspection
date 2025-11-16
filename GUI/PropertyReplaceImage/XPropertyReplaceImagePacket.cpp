#include "XGeneralFunc.h"
#include "XPropertyReplaceImagePacket.h"
#include "XDataInLayer.h"
#include "XReplaceImage.h"


GUICmdReplaceImageAddMaskArea::GUICmdReplaceImageAddMaskArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageAddMaskArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageAddMaskArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReplaceImageAddMaskArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdReplaceImageAckMaskArea	*SendBack=GetSendBack(GUICmdReplaceImageAckMaskArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageAddMaskArea	Cmd(GetLayersBase());
			Cmd.Area=Area;
			PData->TransmitDirectly(&Cmd);
			SendBack->AverageColor=Cmd.AverageColor;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplaceImageAckMaskArea::GUICmdReplaceImageAckMaskArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageAckMaskArea::Load(QIODevice *f)
{
	if(::Load(f,AverageColor)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageAckMaskArea::Save(QIODevice *f)
{
	if(::Save(f,AverageColor)==false)
		return false;
	return true;
}

//=============================================================================================================

GUICmdReplaceImageAddMaskImage::GUICmdReplaceImageAddMaskImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageAddMaskImage::Load(QIODevice *f)
{
	if(::Load(f,Image)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageAddMaskImage::Save(QIODevice *f)
{
	if(::Save(f,Image)==false)
		return false;
	return true;
}

void	GUICmdReplaceImageAddMaskImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageAddMaskImage	Cmd(GetLayersBase());
			Cmd.Image=Image;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageCalcMask::GUICmdReplaceImageCalcMask(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReplaceImageCalcMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageCalcMask	Cmd(GetLayersBase());
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageMouseLDown::GUICmdReplaceImageMouseLDown(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReplaceImageMouseLDown::Load(QIODevice *f)
{
	if(::Load(f,X)==false)
		return false;
	if(::Load(f,Y)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageMouseLDown::Save(QIODevice *f)
{
	if(::Save(f,X)==false)
		return false;
	if(::Save(f,Y)==false)
		return false;
	return true;
}

void	GUICmdReplaceImageMouseLDown::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageMouseLDown	Cmd(GetLayersBase());
			Cmd.X=X;
			Cmd.Y=Y;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageSetCompositeColor::GUICmdReplaceImageSetCompositeColor(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageSetCompositeColor::Load(QIODevice *f)
{
	if(::Load(f,Color)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageSetCompositeColor::Save(QIODevice *f)
{
	if(::Save(f,Color)==false)
		return false;
	return true;
}

void	GUICmdReplaceImageSetCompositeColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageSetCompositeColor	Cmd(GetLayersBase());
			Cmd.Color=Color;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageSetCompositeImage::GUICmdReplaceImageSetCompositeImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageSetCompositeImage::Load(QIODevice *f)
{
	if(::Load(f,Image)==false)
		return false;
	return true;
}

bool	GUICmdReplaceImageSetCompositeImage::Save(QIODevice *f)
{
	if(::Save(f,Image)==false)
		return false;
	return true;
}

void	GUICmdReplaceImageSetCompositeImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageSetCompositeImage	Cmd(GetLayersBase());
			Cmd.Image=Image;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageSetCompositePage::GUICmdReplaceImageSetCompositePage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageSetCompositePage::Load(QIODevice *f)
{
	if(::Load(f,CompPage)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageSetCompositePage::Save(QIODevice *f)
{
	if(::Save(f,CompPage)==false)
		return false;
	return true;
}

void	GUICmdReplaceImageSetCompositePage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageSetCompositePage	Cmd(GetLayersBase());
			Cmd.CompPage=CompPage;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageReqDraw::GUICmdReplaceImageReqDraw(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageReqDraw::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	GUICmdReplaceImageReqDraw::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

void	GUICmdReplaceImageReqDraw::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdReplaceImageAckDraw	*SendBack=GetSendBack(GUICmdReplaceImageAckDraw,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageReqDraw	Cmd(GetLayersBase());

			Cmd.movx		=Data.movx		;
			Cmd.movy		=Data.movy		;
			Cmd.ZoomRate	=Data.ZoomRate	;
			Cmd.CanvasWidth	=Data.CanvasWidth	;
			Cmd.CanvasHeight=Data.CanvasHeight;
			Cmd.Attr.ShowIsoMask=Data.ShowIsoMask;
			SendBack->Image=QImage(Data.CanvasWidth,Data.CanvasHeight,QImage::Format_ARGB32);
			Cmd.Image		=&SendBack->Image;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplaceImageAckDraw::GUICmdReplaceImageAckDraw(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageAckDraw::Load(QIODevice *f)
{
	if(::Load(f,Image)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageAckDraw::Save(QIODevice *f)
{
	if(::Save(f,Image)==false)
		return false;
	return true;
}

//=============================================================================================================

GUICmdReplaceImageProcessMode::GUICmdReplaceImageProcessMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageProcessMode::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	CompMode=(ReplaceImageThreshold::OperateComposite)d;
	if(::Load(f,CompositeInside)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageProcessMode::Save(QIODevice *f)
{
	BYTE	d=(BYTE)CompMode;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,CompositeInside)==false)
		return false;
	return true;
}
void	GUICmdReplaceImageProcessMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageProcessMode	Cmd(GetLayersBase());
			Cmd.CompMode		=CompMode;
			Cmd.CompositeInside	=CompositeInside;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageMaskMode::GUICmdReplaceImageMaskMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageMaskMode::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	OpeMode=(ReplaceImageThreshold::OperateIsolation)d;

	return true;
}
bool	GUICmdReplaceImageMaskMode::Save(QIODevice *f)
{
	BYTE	d=(BYTE)OpeMode;
	if(::Save(f,d)==false)
		return false;

	return true;
}

void	GUICmdReplaceImageMaskMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageMaskMode	Cmd(GetLayersBase());
			Cmd.OpeMode		=OpeMode;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================================

GUICmdReplaceImageMakeAreaMask::GUICmdReplaceImageMakeAreaMask(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceImageMakeAreaMask::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReplaceImageMakeAreaMask::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}
void	GUICmdReplaceImageMakeAreaMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ReplaceImage");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReplaceImageMakeAreaMask	Cmd(GetLayersBase());
			Cmd.Area		=Area;
			PData->TransmitDirectly(&Cmd);
		}
	}
}
