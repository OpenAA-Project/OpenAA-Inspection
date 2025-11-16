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

GUICmdLoadRaster::GUICmdLoadRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FileLayerID=-1;
}
	
bool	GUICmdLoadRaster::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}

bool	GUICmdLoadRaster::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdLoadRaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterBase	*PBase=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage;
	if(PBase->ModeDeliverAllPhasesInLoadRaster==true){
		int	Phase=GetLayersBase()->GetCurrentPhase();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(Phase);
		PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
	}
	else{
		PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	}
	if(PPage!=NULL){
		CmdLoadRaster	Da(GetLayersBase());
		Da.FileLayerID	=FileLayerID;
		Da.FileName		=FileName;
		Da.pData		=&Data;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

GUICmdAckLoadRaster::GUICmdAckLoadRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Ret=true;
}

bool	GUICmdAckLoadRaster::Load(QIODevice *f)
{
	if(::Load(f,Ret)==false)
		return false;
	return true;
}
	
bool	GUICmdAckLoadRaster::Save(QIODevice *f)
{
	if(::Save(f,Ret)==false)
		return false;
	return true;
}
//=========================================================================
GUICmdDeliverRasterToOtherPhases::GUICmdDeliverRasterToOtherPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdDeliverRasterToOtherPhases::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterBase	*PBase=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	if(PBase->ModeDeliverAllPhasesInLoadRaster==true){
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(0);
		RasterInPage	*SrcPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		for(int phase=1;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
			RasterInPage	*DestPPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		
			CmdCopyPageAllFrom	Da(GetLayersBase());
			Da.SourcePage	=SrcPage;

			DestPPage->TransmitDirectly(&Da);
		}
	}
}
//=========================================================================
GUICmdTransferInfo::GUICmdTransferInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdTransferInfo::Load(QIODevice *f)
{
	if(::Load(f,Array)==false)
		return false;
	return true;
}
bool	GUICmdTransferInfo::Save(QIODevice *f)
{
	if(::Save(f,Array)==false)
		return false;
	return true;
}

void	GUICmdTransferInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	QBuffer	Buff(&Array);
	Buff.open(QIODevice::ReadWrite);
}

//=========================================================================

GUICmdReqRasterArea::GUICmdReqRasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{

}

void	GUICmdReqRasterArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterArea	*SendBack=GetSendBack(GUICmdAckRasterArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqRasterArea	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->MinX=Da.MinX;
		SendBack->MinY=Da.MinY;
		SendBack->MaxX=Da.MaxX;
		SendBack->MaxY=Da.MaxY;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRasterArea::GUICmdAckRasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
}
bool	GUICmdAckRasterArea::Load(QIODevice *f)
{
	if(::Load(f,MinX)==false)
		return false;
	if(::Load(f,MinY)==false)
		return false;
	if(::Load(f,MaxX)==false)
		return false;
	if(::Load(f,MaxY)==false)
		return false;
	return true;
}

bool	GUICmdAckRasterArea::Save(QIODevice *f)
{
	if(::Save(f,MinX)==false)
		return false;
	if(::Save(f,MinY)==false)
		return false;
	if(::Save(f,MaxX)==false)
		return false;
	if(::Save(f,MaxY)==false)
		return false;
	return true;
}

//=========================================================================
GUICmdClearRaster::GUICmdClearRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeToClearAllPhases=false;
}
	
bool	GUICmdClearRaster::Load(QIODevice *f)
{	
	if(::Load(f,ModeToClearAllPhases)==false)
		return false;
	return true;
}

bool	GUICmdClearRaster::Save(QIODevice *f)
{	
	if(::Save(f,ModeToClearAllPhases)==false)
		return false;
	return true;
}

void	GUICmdClearRaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	if(ModeToClearAllPhases==true){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*H=PBase->GetPageDataPhase(phase);
			if(H!=NULL){
				RasterInPage	*PPage=dynamic_cast<RasterInPage *>(H->GetPageData(localPage));
				if(PPage!=NULL){
					CmdClearRaster	Cmd(GetLayersBase());
					PPage->TransmitDirectly(&Cmd);
				}
			}
		}
	}
	else{
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdClearRaster	Cmd(GetLayersBase());
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterMove::GUICmdRasterMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XDir	=0;
	YDir	=0;
	PixelMode=true;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterMove::Load(QIODevice *f)
{
	if(::Load(f,XDir)==false)
		return false;
	if(::Load(f,YDir)==false)
		return false;
	if(::Load(f,PixelMode)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterMove::Save(QIODevice *f)
{
	if(::Save(f,XDir)==false)
		return false;
	if(::Save(f,YDir)==false)
		return false;
	if(::Save(f,PixelMode)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterMove	Cmd(GetLayersBase());
			Cmd.XDir=XDir;
			Cmd.YDir=YDir;
			Cmd.PixelMode=PixelMode;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterRotate::GUICmdRasterRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Angle	=0;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterRotate::Load(QIODevice *f)
{
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterRotate::Save(QIODevice *f)
{
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterRotate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterRotate	Cmd(GetLayersBase());
			Cmd.Angle=Angle;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterZoom::GUICmdRasterZoom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XZoomDir	=0;
	YZoomDir	=0;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterZoom::Load(QIODevice *f)
{
	if(::Load(f,XZoomDir)==false)
		return false;
	if(::Load(f,YZoomDir)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterZoom::Save(QIODevice *f)
{
	if(::Save(f,XZoomDir)==false)
		return false;
	if(::Save(f,YZoomDir)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterZoom::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterZoom	Cmd(GetLayersBase());
			Cmd.XZoomDir=XZoomDir;
			Cmd.YZoomDir=YZoomDir;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterShear::GUICmdRasterShear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XMode=true;
	Shear=0;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterShear::Load(QIODevice *f)
{
	if(::Load(f,XMode)==false)
		return false;
	if(::Load(f,Shear)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterShear::Save(QIODevice *f)
{
	if(::Save(f,XMode)==false)
		return false;
	if(::Save(f,Shear)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterShear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterShear	Cmd(GetLayersBase());
			Cmd.XMode=XMode;
			Cmd.Shear=Shear;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterMirror::GUICmdRasterMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XMode	=true;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterMirror::Load(QIODevice *f)
{
	if(::Load(f,XMode)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterMirror::Save(QIODevice *f)
{
	if(::Save(f,XMode)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterMirror::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterMirror	Cmd(GetLayersBase());
			Cmd.XMode=XMode;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterCenterize::GUICmdRasterCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MovX=MovY	=0.0;
	ZoomRate	=1.0;
	CenterX=CenterY	=0.0;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterCenterize::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterCenterize::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterCenterize	Cmd(GetLayersBase());
			Cmd.MovX=MovX;
			Cmd.MovY=MovY;
			Cmd.ZoomRate=ZoomRate;
			Cmd.CenterX	=CenterX;
			Cmd.CenterY	=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRasterCenterizeOnly::GUICmdRasterCenterizeOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MovX=MovY	=0.0;
	CenterX=CenterY	=0.0;
	OnlyOnePhase	=false;
}

bool	GUICmdRasterCenterizeOnly::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlyOnePhase)==false)
		return false;
	return true;
}
bool	GUICmdRasterCenterizeOnly::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,OnlyOnePhase)==false)
		return false;
	return true;
}

void	GUICmdRasterCenterizeOnly::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	if(OnlyOnePhase==false){
		ActivePhaseList(PhaseList);
	}
	else{
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRasterCenterizeOnly	Cmd(GetLayersBase());
			Cmd.MovX=MovX;
			Cmd.MovY=MovY;
			Cmd.CenterX	=CenterX;
			Cmd.CenterY	=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================

GUICmdSetDrawAttr::GUICmdSetDrawAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetDrawAttr::Load(QIODevice *f)
{
	if(ShownFileID.Load(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Load(f,LayerColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Load(f,FileLayerIDTable[i])==false){
			return false;
		}
	}
	return true;
}
bool	GUICmdSetDrawAttr::Save(QIODevice *f)
{
	if(ShownFileID.Save(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Save(f,LayerColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Save(f,FileLayerIDTable[i])==false){
			return false;
		}
	}
	return true;
}
void	GUICmdSetDrawAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamComm()->Mastered==false){
		GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
		if(DProp!=NULL){
			DProp->TransmitDirectly(this);
		}
	}
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdSetDrawAttr	WCmd(GetLayersBase());
			WCmd.ShownFileID		=ShownFileID;
			for(int i=0;i<MaxRasterLayer;i++){
				WCmd.FileLayerIDTable[i]	=FileLayerIDTable[i];
			}
			PPage->TransmitDirectly(&WCmd);
		}
	}
}

//=========================================================================
GUICmdDrawAllSelected::GUICmdDrawAllSelected(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdDrawAllSelected::Load(QIODevice *f)
{
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdDrawAllSelected::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;

	return true;
}

void	GUICmdDrawAllSelected::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Ab==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdDrawAllSelected	Cmd(GetLayersBase());
			Cmd.ButtonsToOperateLayer	=ButtonsToOperateLayer;

			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=========================================================================

GUICmdSelectLine::GUICmdSelectLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FileLayerID=0;
}

bool	GUICmdSelectLine::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;

	return true;
}
bool	GUICmdSelectLine::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;

	return true;
}

void	GUICmdSelectLine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdSelectLine	Cmd(GetLayersBase());
			Cmd.FileLayerID		=FileLayerID;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
//=========================================================================

GUICmdRemoveLine::GUICmdRemoveLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LineNo=0;
}

bool	GUICmdRemoveLine::Save(QIODevice *f)
{
	if(::Save(f,LineNo)==false)
		return false;

	return true;
}
bool	GUICmdRemoveLine::Load(QIODevice *f)
{
	if(::Load(f,LineNo)==false)
		return false;

	return true;
}

void	GUICmdRemoveLine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRemoveLine	Cmd(GetLayersBase());
			Cmd.LineNo		=LineNo;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
//=========================================================================

GUICmdSwapNext::GUICmdSwapNext(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LineNo=0;
}

bool	GUICmdSwapNext::Save(QIODevice *f)
{
	if(::Save(f,LineNo)==false)
		return false;

	return true;
}
bool	GUICmdSwapNext::Load(QIODevice *f)
{
	if(::Load(f,LineNo)==false)
		return false;

	return true;
}

void	GUICmdSwapNext::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdSwapNext	Cmd(GetLayersBase());
			Cmd.LineNo		=LineNo;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
//=========================================================================

GUICmdDuplicateLine::GUICmdDuplicateLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LineNo=0;
}

bool	GUICmdDuplicateLine::Save(QIODevice *f)
{
	if(::Save(f,LineNo)==false)
		return false;

	return true;
}
bool	GUICmdDuplicateLine::Load(QIODevice *f)
{
	if(::Load(f,LineNo)==false)
		return false;

	return true;
}

void	GUICmdDuplicateLine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDuplicateLine	*SendBack=GetSendBack(GUICmdAckDuplicateLine,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
			if(PPage!=NULL){
				CmdDuplicateLine	Cmd(GetLayersBase());
				Cmd.LineNo		=LineNo;
				PPage->TransmitDirectly(&Cmd);
				SendBack->FileLayerID=Cmd.FileLayerID;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckDuplicateLine::GUICmdAckDuplicateLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FileLayerID=0;
}

bool	GUICmdAckDuplicateLine::Load(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;

	return true;
}

bool	GUICmdAckDuplicateLine::Save(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;

	return true;
}

//=========================================================================
GUICmdChangeCurrentPhase::GUICmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeCurrentPhase::Load(QIODevice *f)
{
	if(::Load(f,NewPhase)==false)
		return false;
	return true;
}
bool	GUICmdChangeCurrentPhase::Save(QIODevice *f)
{
	if(::Save(f,NewPhase)==false)
		return false;
	return true;
}

void	GUICmdChangeCurrentPhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCurrentPhase(NewPhase);
	}
	SendAck(localPage);
}

//==========================================================================================
GUICmdRasterExec3PointAlignment::GUICmdRasterExec3PointAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRasterExec3PointAlignment::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Save(f)==false)
			return false;
		if(CadPoint[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	GUICmdRasterExec3PointAlignment::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}
	return true;
}

void	GUICmdRasterExec3PointAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//if(localPage==0){
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
		CmdRasterExec3PointAlignment	Cmd(this);
		for(int i=0;i<MaxRasterPointNumb;i++){
			Cmd.ImagePoint[i]	=ImagePoint[i];
			Cmd.CadPoint[i]		=CadPoint[i];
		}
		Cmd.FileLayerID=FileLayerID;
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	//}
}
//==========================================================================================
GUICmdRasterExecAddAlignmentPoint::GUICmdRasterExecAddAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRasterExecAddAlignmentPoint::Save(QIODevice *f)
{
	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Save(f)==false)
			return false;
		if(CadPoint[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	GUICmdRasterExecAddAlignmentPoint::Load(QIODevice *f)
{
	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}
	return true;
}

void	GUICmdRasterExecAddAlignmentPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		CmdRasterExecAddAlignmentPoint	Cmd(this);
		for(int i=0;i<MaxRasterPointNumb;i++){
			Cmd.ImagePoint[i]	=ImagePoint[i];
			Cmd.CadPoint[i]		=CadPoint[i];
		}		
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		Base->TransmitDirectly(&Cmd);
	}
}
//==========================================================================================
GUICmdReqRasterCenterize::GUICmdReqRasterCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqRasterCenterize::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(XYArea.Write(f)==false)
		return false;
	return true;
}
bool	GUICmdReqRasterCenterize::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(XYArea.Read(f)==false)
		return false;
	return true;
}

void	GUICmdReqRasterCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MsgRasterCenterize	Cmd(this);
	Cmd.Area	=Area;
	Cmd.XYArea	=XYArea;
	Cmd.GlobalPage=localPage;	//‚±‚ê‚ÍOK
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	Base->GetPageData(localPage)->TransmitDirectly(&Cmd);

	GUICmdSendRasterCenterize	*SendBack=GetSendBack(GUICmdSendRasterCenterize,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->x=Cmd.x;
	SendBack->y=Cmd.y;
	SendBack->Ret=Cmd.Ret;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendRasterCenterize::GUICmdSendRasterCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendRasterCenterize::Save(QIODevice *f)
{
	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;
	if(::Save(f,Ret)==false)
		return false;
	return true;
}
bool	GUICmdSendRasterCenterize::Load(QIODevice *f)
{
	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	if(::Load(f,Ret)==false)
		return false;
	return true;
}

void	GUICmdSendRasterCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{

}

//==========================================================================================
GUICmdSendImagePointXY::GUICmdSendImagePointXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendImagePointXY::Save(QIODevice *f)
{
	if(::Save(f,Turn)==false)
		return false;
	if(::Save(f,GPx)==false)
		return false;
	if(::Save(f,GPy)==false)
		return false;
	return true;
}
bool	GUICmdSendImagePointXY::Load(QIODevice *f)
{
	if(::Load(f,Turn)==false)
		return false;
	if(::Load(f,GPx)==false)
		return false;
	if(::Load(f,GPy)==false)
		return false;
	return true;
}

void	GUICmdSendImagePointXY::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"RasterImagePanel" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(this);
	}
}

//==========================================================================================

GUICmdRasterSetAlignmentPoint::GUICmdRasterSetAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRasterSetAlignmentPoint::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,LineNo)==false)
		return false;
	if(::Load(f,IsImage)==false)
		return false;

	return true;
}
bool	GUICmdRasterSetAlignmentPoint::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,LineNo)==false)
		return false;
	if(::Save(f,IsImage)==false)
		return false;

	return true;
}

void	GUICmdRasterSetAlignmentPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//===================================================================================
GUICmdRasterSendShowingLayerInfo::GUICmdRasterSendShowingLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRasterSendShowingLayerInfo::Load(QIODevice *f)
{
	if(ButtonsToShowLayer.Load(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Load(f,LayerColor[i])==false)
			return false;
	}
	return true;
}
bool	GUICmdRasterSendShowingLayerInfo::Save(QIODevice *f)
{
	if(ButtonsToShowLayer.Save(f)==false)
		return false;

	for(int i=0;i<MaxRasterLayer;i++){
		if(::Save(f,LayerColor[i])==false)
			return false;
	}
	return true;
}

void	GUICmdRasterSendShowingLayerInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		QString	AlgoRoot=/**/"Basic";
		QString	AlgoName=/**/"Raster";
		RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(Base!=NULL){
			Base->TransmitDirectly(this);
		}
	}
}

//===================================================================================

GUICmdMakeImage::GUICmdMakeImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMakeImage::Load(QIODevice *f)
{
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Load(f,LayerColor[i])==false)
			return false;
	}

	return true;
}
bool	GUICmdMakeImage::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	for(int i=0;i<MaxRasterLayer;i++){
		if(::Save(f,LayerColor[i])==false)
			return false;
	}

	return true;
}

void	GUICmdMakeImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(this);
	}
}
//===================================================================================

GUICmdMakeImageInMask::GUICmdMakeImageInMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMakeImageInMask::Load(QIODevice *f)
{
	if(ChangeableAreas.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdMakeImageInMask::Save(QIODevice *f)
{
	if(ChangeableAreas.Save(f)==false)
		return false;

	return true;
}

void	GUICmdMakeImageInMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdCopyImageToMaster	Cmd(GetLayersBase());
		Cmd.ChangeableAreas=ChangeableAreas;
		PPage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//===================================================================================

GUICmdMakeBitImage::GUICmdMakeBitImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMakeBitImage::Load(QIODevice *f)
{
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;

	for(int i=0;i<MaxRasterLayer;i++){
		if(::Load(f,LayerColor[i])==false)
			return false;
	}

	return true;
}
bool	GUICmdMakeBitImage::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;

	for(int i=0;i<MaxRasterLayer;i++){
		if(::Save(f,LayerColor[i])==false)
			return false;
	}

	return true;
}

void	GUICmdMakeBitImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(this);
	}
}
//===================================================================================
GUICmdAlgoPipeOut::GUICmdAlgoPipeOut(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdAlgoPipeOut::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(this);
	}
	SendAck(localPage);
}

//===================================================================================
GUICmdReqSaveConstruct::GUICmdReqSaveConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSaveConstruct::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	return true;
}

bool	GUICmdReqSaveConstruct::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	return true;
}
void	GUICmdReqSaveConstruct::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GUICmdAckSaveConstruct	*SendBack=GetSendBack(GUICmdAckSaveConstruct,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	MsgSaveConstruct	Cmd(GetLayersBase());
	AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(Phase);
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(&Cmd);
	}
	SendBack->Data=Cmd.Data;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSaveConstruct::GUICmdAckSaveConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckSaveConstruct::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}

bool	GUICmdAckSaveConstruct::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}

//===================================================================================

GUICmdReqLoadConstruct::GUICmdReqLoadConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLoadConstruct::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}

bool	GUICmdReqLoadConstruct::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdReqLoadConstruct::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	MsgLoadConstruct	Cmd(GetLayersBase());
	Cmd.Data=Data;
	AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(Phase);
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Ah->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(&Cmd);
	}
}


//==========================================================================================

GUICmdReqRasterInfo::GUICmdReqRasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqRasterInfo::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;
	if(DrawingLayers.Save(f)==false)
		return false;
	return true;
}

bool	GUICmdReqRasterInfo::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;
	if(DrawingLayers.Load(f)==false)
		return false;
	return true;
}

void	GUICmdReqRasterInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterInfo	*SendBack=GetSendBack(GUICmdAckRasterInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	CmdReqRasterInfo	Cmd(GetLayersBase());
	Cmd.GlobalX	=GlobalX;
	Cmd.GlobalY	=GlobalY;
	Cmd.DrawingLayers	=DrawingLayers;
	Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	SendBack->GInfo=Cmd.Answer;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckRasterInfo::GUICmdAckRasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckRasterInfo::Save(QIODevice *f)
{
	if(GInfo.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdAckRasterInfo::Load(QIODevice *f)
{
	if(GInfo.Load(f)==false)
		return false;
	return true;
}

//==========================================================================================

GUICmdRasterDrawMode::GUICmdRasterDrawMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	DrawPickUpArea=false;
	LastElementPosX=0;
	LastElementPosY=0;
	MoveStartElementPosX=0;
	MoveStartElementPosY=0;
}

bool	GUICmdRasterDrawMode::Save(QIODevice *f)
{
	BYTE	m=(BYTE)Mode;
	if(::Save(f,m)==false)
		return false;

	if(::Save(f,MoveMode)==false)
		return false;
	if(::Save(f,MoveElementMode)==false)
		return false;
	if(::Save(f,RotateMode)==false)
		return false;
	if(::Save(f,SlopeXMode)==false)
		return false;
	if(::Save(f,SlopeYMode)==false)
		return false;
	if(::Save(f,ExtendMode)==false)
		return false;
	if(::Save(f,LastPosX)==false)
		return false;
	if(::Save(f,LastPosY)==false)
		return false;
	if(::Save(f,MoveStartPosX)==false)
		return false;
	if(::Save(f,MoveStartPosY)==false)
		return false;
	if(::Save(f,LastElementPosX)==false)
		return false;
	if(::Save(f,LastElementPosY)==false)
		return false;
	if(::Save(f,MoveStartElementPosX)==false)
		return false;
	if(::Save(f,MoveStartElementPosY)==false)
		return false;
	if(::Save(f,RotateCenterXOnData)==false)
		return false;
	if(::Save(f,RotateCenterYOnData)==false)
		return false;
	if(::Save(f,RotateFirstX)==false)
		return false;
	if(::Save(f,RotateFirstY)==false)
		return false;
	if(::Save(f,RotateAngle)==false)
		return false;
	if(::Save(f,ExtendCenterXOnData)==false)
		return false;
	if(::Save(f,ExtendCenterYOnData)==false)
		return false;
	if(::Save(f,ExtendFirstX)==false)
		return false;
	if(::Save(f,ExtendFirstY)==false)
		return false;

	if(::Save(f,SlopeXCenterXOnData)==false)
		return false;
	if(::Save(f,SlopeXCenterYOnData)==false)
		return false;
	if(::Save(f,SlopeXFirstX)==false)
		return false;
	if(::Save(f,SlopeXFirstY)==false)
		return false;
	if(::Save(f,SlopeXAngle)==false)
		return false;

	if(::Save(f,SlopeYCenterXOnData)==false)
		return false;
	if(::Save(f,SlopeYCenterYOnData)==false)
		return false;
	if(::Save(f,SlopeYFirstX)==false)
		return false;
	if(::Save(f,SlopeYFirstY)==false)
		return false;
	if(::Save(f,SlopeYAngle)==false)
		return false;

	if(::Save(f,AlignmentMode)==false)
		return false;
	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Save(f)==false)
			return false;
		if(CadPoint[i].Save(f)==false)
			return false;
	}
	if(::Save(f,DrawPickUpArea)==false)
		return false;

	return true;
}
bool	GUICmdRasterDrawMode::Load(QIODevice *f)
{
	BYTE	m;
	if(::Load(f,m)==false)
		return false;
	Mode=(DisplayImage::__DrawingMode)m;

	if(::Load(f,MoveMode)==false)
		return false;
	if(::Load(f,MoveElementMode)==false)
		return false;
	if(::Load(f,RotateMode)==false)
		return false;
	if(::Load(f,SlopeXMode)==false)
		return false;
	if(::Load(f,SlopeYMode)==false)
		return false;
	if(::Load(f,ExtendMode)==false)
		return false;
	if(::Load(f,LastPosX)==false)
		return false;
	if(::Load(f,LastPosY)==false)
		return false;
	if(::Load(f,MoveStartPosX)==false)
		return false;
	if(::Load(f,MoveStartPosY)==false)
		return false;
	if(::Load(f,LastElementPosX)==false)
		return false;
	if(::Load(f,LastElementPosY)==false)
		return false;
	if(::Load(f,MoveStartElementPosX)==false)
		return false;
	if(::Load(f,MoveStartElementPosY)==false)
		return false;
	if(::Load(f,RotateCenterXOnData)==false)
		return false;
	if(::Load(f,RotateCenterYOnData)==false)
		return false;
	if(::Load(f,RotateFirstX)==false)
		return false;
	if(::Load(f,RotateFirstY)==false)
		return false;
	if(::Load(f,RotateAngle)==false)
		return false;
	if(::Load(f,ExtendCenterXOnData)==false)
		return false;
	if(::Load(f,ExtendCenterYOnData)==false)
		return false;
	if(::Load(f,ExtendFirstX)==false)
		return false;
	if(::Load(f,ExtendFirstY)==false)
		return false;

	if(::Load(f,SlopeXCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeXCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeXFirstX)==false)
		return false;
	if(::Load(f,SlopeXFirstY)==false)
		return false;
	if(::Load(f,SlopeXAngle)==false)
		return false;

	if(::Load(f,SlopeYCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeYCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeYFirstX)==false)
		return false;
	if(::Load(f,SlopeYFirstY)==false)
		return false;
	if(::Load(f,SlopeYAngle)==false)
		return false;

	if(::Load(f,AlignmentMode)==false)
		return false;
	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}
	if(::Load(f,DrawPickUpArea)==false)
		return false;

	return true;}

void	GUICmdRasterDrawMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	RasterInPage	*GPage	=(RasterInPage *)Base->GetPageData(localPage);

	GPage->Mode					=Mode;
	GPage->LastPosX				=LastPosX;
	GPage->LastPosY				=LastPosY;
	GPage->MoveStartPosX		=MoveStartPosX;
	GPage->MoveStartPosY		=MoveStartPosY;
	GPage->LastElementPosX		=LastElementPosX;
	GPage->LastElementPosY		=LastElementPosY;
	GPage->MoveStartElementPosX	=MoveStartElementPosX;
	GPage->MoveStartElementPosY	=MoveStartElementPosY;
	GPage->RotateCenterXOnData	=RotateCenterXOnData;
	GPage->RotateCenterYOnData	=RotateCenterYOnData;
	GPage->RotateFirstX			=RotateFirstX;
	GPage->RotateFirstY			=RotateFirstY;
	GPage->RotateAngle			=RotateAngle;
	GPage->ExtendCenterXOnData	=ExtendCenterXOnData;
	GPage->ExtendCenterYOnData	=ExtendCenterYOnData;
	GPage->ExtendFirstX			=ExtendFirstX;
	GPage->ExtendFirstY			=ExtendFirstY;

	GPage->SlopeXCenterXOnData	=SlopeXCenterXOnData;
	GPage->SlopeXCenterYOnData	=SlopeXCenterYOnData;
	GPage->SlopeXFirstX			=SlopeXFirstX;
	GPage->SlopeXFirstY			=SlopeXFirstY;
	GPage->SlopeXAngle			=SlopeXAngle;

	GPage->SlopeYCenterXOnData	=SlopeYCenterXOnData;
	GPage->SlopeYCenterYOnData	=SlopeYCenterYOnData;
	GPage->SlopeYFirstX			=SlopeYFirstX;
	GPage->SlopeYFirstY			=SlopeYFirstY;
	GPage->SlopeYAngle			=SlopeYAngle;

	for(int i=0;i<MaxRasterPointNumb;i++){
		GPage->ImagePoint[i]=ImagePoint[i];
		GPage->CadPoint[i]	=CadPoint[i];
	}

}

//====================================================================================

GUICmdSelectItemsRaster::GUICmdSelectItemsRaster(LayersBase *Base ,const QString &EmitterRoot ,const QString &EmitterName,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MultiSelect=false;
}
bool	GUICmdSelectItemsRaster::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(ButtonsToOperateLayer.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectItemsRaster::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(ButtonsToOperateLayer.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectItemsRaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
		if(Ap!=NULL){
			CmdSelectItemsRaster	Cmd(GetLayersBase());
			Cmd.Area					=Area;
			Cmd.ButtonsToOperateLayer	=ButtonsToOperateLayer;
			Ap->TransmitDirectly(&Cmd);
		}
	}
	
	SendAck(localPage);
}
//====================================================================================

GUICmdMsgRasterSelectAll::GUICmdMsgRasterSelectAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMsgRasterSelectAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	AlgorithmInPageRoot	*GPage=Base->GetPageData(localPage);
	MsgRasterSelectAll	MCmd(this);
	GPage->TransmitDirectly(&MCmd);
}

//====================================================================================

GUICmdRasterDraw::GUICmdRasterDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRasterDraw::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;
	if(ButtonsToShowLayer.Save(f)==false)
		return false;
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdRasterDraw::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;
	if(ButtonsToShowLayer.Load(f)==false)
		return false;
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	return true;
}

void	GUICmdRasterDraw::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*GPage=Ah->GetPageData(localPage);
		CmdRasterDraw	LCmd(this);
		LCmd.GlobalX=GlobalX;
		LCmd.GlobalY=GlobalY;
		LCmd.ButtonsToShowLayer		=ButtonsToShowLayer;
		LCmd.ButtonsToOperateLayer	=ButtonsToOperateLayer;
		GPage->TransmitDirectly(&LCmd);
	}
}

//==========================================================================================
GUICmdMsgRasterExtendWithCenter::GUICmdMsgRasterExtendWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	RateX=RateY=0;
}

bool	GUICmdMsgRasterExtendWithCenter::Save(QIODevice *f)
{
	if(::Save(f,RateX)==false)
		return false;
	if(::Save(f,RateY)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgRasterExtendWithCenter::Load(QIODevice *f)
{
	if(::Load(f,RateX)==false)
		return false;
	if(::Load(f,RateY)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgRasterExtendWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");

		MsgRasterExtend	MCmd(this);
		MCmd.RateX=RateX;
		MCmd.RateY=RateY;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}

//==========================================================================================
GUICmdMsgRasterRotateWithCenter::GUICmdMsgRasterRotateWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Radian=0;
}

bool	GUICmdMsgRasterRotateWithCenter::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgRasterRotateWithCenter::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgRasterRotateWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		MsgRasterRotate	MCmd(this);
		MCmd.Radian	=Radian;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}
//==========================================================================================
GUICmdMsgRasterSlopeXWithCenter::GUICmdMsgRasterSlopeXWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Radian=0;
}

bool	GUICmdMsgRasterSlopeXWithCenter::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgRasterSlopeXWithCenter::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgRasterSlopeXWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		MsgRasterSlopeX	MCmd(this);
		MCmd.Radian	=Radian;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}
//==========================================================================================
GUICmdMsgRasterSlopeYWithCenter::GUICmdMsgRasterSlopeYWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Radian=0;
}

bool	GUICmdMsgRasterSlopeYWithCenter::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgRasterSlopeYWithCenter::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgRasterSlopeYWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		MsgRasterSlopeY	MCmd(this);
		MCmd.Radian	=Radian;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}

//==========================================================================================
GUICmdMsgRasterPaste::GUICmdMsgRasterPaste(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMsgRasterPaste::Save(QIODevice *f)
{
	if(::Save(f,index)==false)
		return false;
	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;
	return true;
}
bool	GUICmdMsgRasterPaste::Load(QIODevice *f)
{
	if(::Load(f,index)==false)
		return false;
	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	return true;
}

void	GUICmdMsgRasterPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		if(Base==NULL)
			return;
		MsgRasterPaste	Cmd(this);
		Cmd.index=index;
		Cmd.x=x;
		Cmd.y=y;
		Base->TransmitDirectly(&Cmd);
	}
}

//==========================================================================================
GUICmdRasterDrawArea::GUICmdRasterDrawArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRasterDrawArea::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false)
		return false;
	if(::Save(f,Color)==false)
		return false;
	if(::Save(f,FileLayerID)==false)
		return false;
	return true;
}
bool	GUICmdRasterDrawArea::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false)
		return false;
	if(::Load(f,Color)==false)
		return false;
	if(::Load(f,FileLayerID)==false)
		return false;
	return true;
}

void	GUICmdRasterDrawArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage==NULL)
		return;
	CmdRasterDrawArea	Cmd(this);
	Cmd.Area		=LocalArea;
	Cmd.Color		=Color;
	Cmd.FileLayerID	=FileLayerID;
	PPage->TransmitDirectly(&Cmd);
}

//==========================================================================================

GUICmdRasterPickupByColor::GUICmdRasterPickupByColor(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdRasterPickupByColor::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,InsideEdgeWidth)==false)
		return false;
	if(::Load(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Load(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Load(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdRasterPickupByColor::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,InsideEdgeWidth)==false)
		return false;
	if(::Save(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Save(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Save(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Save(f)==false)
		return false;
	return true;
}
void	GUICmdRasterPickupByColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage==NULL)
		return;
	CmdRasterPickupByColor	Cmd(GetLayersBase());
	Cmd.FileLayerID	=FileLayerID;
	Cmd.LocalX		=LocalX;
	Cmd.LocalY		=LocalY;
	Cmd.ShrinkDot	=ShrinkDot;
	Cmd.InsideEdgeWidth			=InsideEdgeWidth;
	Cmd.OutsideEdgeWidth		=OutsideEdgeWidth;
	Cmd.AllocatedStaticLib		=AllocatedStaticLib		;
	Cmd.AllocatedInsideEdgeLib	=AllocatedInsideEdgeLib	;
	Cmd.AllocatedOutsideEdgeLib	=AllocatedOutsideEdgeLib;
	PPage->TransmitDirectly(&Cmd);
}
//==========================================================================================

GUICmdRasterPickupByColorArea::GUICmdRasterPickupByColorArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdRasterPickupByColorArea::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	if(LocalColorArea.Load(f)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,InsideEdgeWidth)==false)
		return false;
	if(::Load(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Load(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Load(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdRasterPickupByColorArea::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	if(LocalColorArea.Save(f)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,InsideEdgeWidth)==false)
		return false;
	if(::Save(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Save(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Save(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Save(f)==false)
		return false;
	return true;
}
void	GUICmdRasterPickupByColorArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(PBase==NULL)
		return;
	RasterInPage	*PPage=dynamic_cast<RasterInPage *>(PBase->GetPageData(localPage));
	if(PPage==NULL)
		return;
	CmdRasterPickupByColorArea	Cmd(GetLayersBase());
	Cmd.FileLayerID		=FileLayerID;
	Cmd.LocalColorArea	=LocalColorArea;
	Cmd.ShrinkDot		=ShrinkDot;
	Cmd.InsideEdgeWidth			=InsideEdgeWidth;
	Cmd.OutsideEdgeWidth		=OutsideEdgeWidth;
	Cmd.AllocatedStaticLib		=AllocatedStaticLib		;
	Cmd.AllocatedInsideEdgeLib	=AllocatedInsideEdgeLib	;
	Cmd.AllocatedOutsideEdgeLib	=AllocatedOutsideEdgeLib;
	PPage->TransmitDirectly(&Cmd);
}

//==========================================================================================

GUICmdReqRasterElements::GUICmdReqRasterElements(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	FileLayerID=-1;
}
bool	GUICmdReqRasterElements::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	return true;
}
bool	GUICmdReqRasterElements::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	return true;
}

void	GUICmdReqRasterElements::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterElements	*SendBack=GetSendBack(GUICmdAckRasterElements,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		ReqRasterElements	Cmd(GetLayersBase());
		Cmd.FileLayerID	=FileLayerID;
		Cmd.Elements	=&SendBack->Elements;
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRasterElements::GUICmdAckRasterElements(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRasterElements::Load(QIODevice *f)
{
	if(Elements.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckRasterElements::Save(QIODevice *f)
{
	if(Elements.Save(f)==false)
		return false;
	return true;
}

//==========================================================================================

GUICmdReqRasterElementData::GUICmdReqRasterElementData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ItemID		=-1;
	ElementID	=-1;
}
bool	GUICmdReqRasterElementData::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ElementID)==false)
		return false;
	return true;
}
bool	GUICmdReqRasterElementData::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ElementID)==false)
		return false;
	return true;
}

void	GUICmdReqRasterElementData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterElementData	*SendBack=GetSendBack(GUICmdAckRasterElementData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		CmdReqRasterElementData	Cmd(GetLayersBase());
		Cmd.ItemID		=ItemID;
		Cmd.ElementID	=ElementID;
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
		SendBack->ShrinkDot					=Cmd.ShrinkDot;
		SendBack->InsideEdgeWidth			=Cmd.InsideEdgeWidth;
		SendBack->OutsideEdgeWidth			=Cmd.OutsideEdgeWidth;
		SendBack->AllocatedStaticLib		=Cmd.AllocatedStaticLib		;
		SendBack->AllocatedInsideEdgeLib	=Cmd.AllocatedInsideEdgeLib	;
		SendBack->AllocatedOutsideEdgeLib	=Cmd.AllocatedOutsideEdgeLib;
		SendBack->Found			=Cmd.Found;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRasterElementData::GUICmdAckRasterElementData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Found=false;
}
bool	GUICmdAckRasterElementData::Load(QIODevice *f)
{
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,InsideEdgeWidth)==false)
		return false;
	if(::Load(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Load(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Load(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Load(f)==false)
		return false;
	if(::Load(f,Found)==false)
		return false;
	return true;
}
bool	GUICmdAckRasterElementData::Save(QIODevice *f)
{
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,InsideEdgeWidth)==false)
		return false;
	if(::Save(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Save(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Save(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Save(f)==false)
		return false;
	if(::Save(f,Found)==false)
		return false;
	return true;
}

//==========================================================================================

GUICmdSetRasterElementData::GUICmdSetRasterElementData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ItemID		=-1;
	ElementID	=-1;
	DeleteMode	=false;
}
bool	GUICmdSetRasterElementData::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ElementID)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,InsideEdgeWidth)==false)
		return false;
	if(::Load(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Load(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Load(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Load(f)==false)
		return false;
	if(::Load(f,DeleteMode)==false)
		return false;
	return true;
}
bool	GUICmdSetRasterElementData::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ElementID)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,InsideEdgeWidth)==false)
		return false;
	if(::Save(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Save(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Save(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Save(f)==false)
		return false;
	if(::Save(f,DeleteMode)==false)
		return false;
	return true;
}

void	GUICmdSetRasterElementData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterElementData	*SendBack=GetSendBack(GUICmdAckRasterElementData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		CmdSetRasterElementData	Cmd(GetLayersBase());
		Cmd.ItemID		=ItemID;
		Cmd.ElementID	=ElementID;
		Cmd.ShrinkDot	=ShrinkDot;
		Cmd.InsideEdgeWidth			=InsideEdgeWidth;
		Cmd.OutsideEdgeWidth		=OutsideEdgeWidth;
		Cmd.AllocatedStaticLib		=AllocatedStaticLib		;
		Cmd.AllocatedInsideEdgeLib	=AllocatedInsideEdgeLib	;
		Cmd.AllocatedOutsideEdgeLib	=AllocatedOutsideEdgeLib;
		Cmd.DeleteMode	=DeleteMode;
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//==========================================================================================

GUICmdReqRefreshLines::GUICmdReqRefreshLines(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqRefreshLines::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRefreshLines	*SendBack=GetSendBack(GUICmdAckRefreshLines,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		CmdReqRefreshLines	Cmd(GetLayersBase());
		Cmd.FileLayerListContainer	=&SendBack->FileLayerListContainer;
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRefreshLines::GUICmdAckRefreshLines(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRefreshLines::Load(QIODevice *f)
{
	if(FileLayerListContainer.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckRefreshLines::Save(QIODevice *f)
{
	if(FileLayerListContainer.Save(f)==false)
		return false;
	return true;
}
//====================================================================================

GUIRasterCmdDelMaskByCAD::GUIRasterCmdDelMaskByCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUIRasterCmdDelMaskByCAD::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Masking");
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	if(PPage!=NULL){
		IntList LayerList;
		for(int layer=0;layer<GetLayerNumb(localPage);layer++){
			LayerList.Add(layer);
		}
		AlgorithmBase	*OriginBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
		struct	OriginTypeSelection SelectMode(OriginBase);
		SelectMode._FromCAD=true;
		PPage->SelectItemsByOriginType(SelectMode,LayerList);
		PPage->DeleteSelectedItems(LayerList);
	}
}

//====================================================================================
GUICmdReqPickRasterColor::GUICmdReqPickRasterColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqPickRasterColor::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	if(::Load(f,FileLayerID)==false)
		return false;
	return true;
}
bool	GUICmdReqPickRasterColor::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	if(::Save(f,FileLayerID)==false)
		return false;
	return true;
}

void	GUICmdReqPickRasterColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPickRasterColor	*SendBack=GetSendBack(GUICmdAckPickRasterColor,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdPickRasterColor	Cmd(GetLayersBase());
		Cmd.LocalX		=LocalX;
		Cmd.LocalY		=LocalY;
		Cmd.FileLayerID	=FileLayerID;
		PPage->TransmitDirectly(&Cmd);
		SendBack->Color=Cmd.Color;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckPickRasterColor::GUICmdAckPickRasterColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckPickRasterColor::Load(QIODevice *f)
{
	if(::Load(f,Color)==false)
		return false;
	return true;
}
bool	GUICmdAckPickRasterColor::Save(QIODevice *f)
{
	if(::Save(f,Color)==false)
		return false;
	return true;
}

//====================================================================================
GUICmdSetPickupArea::GUICmdSetPickupArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetPickupArea::Save(QIODevice *f)
{
	if(LocalPickupArea.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdSetPickupArea::Load(QIODevice *f)
{
	if(LocalPickupArea.Load(f)==false)
		return false;
	return true;
}

void	GUICmdSetPickupArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		PPage->LocalPickupArea=LocalPickupArea;
	}
}

//====================================================================================
GUICmdMoveElement::GUICmdMoveElement(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMoveElement::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)	return false;
	if(::Save(f,MovY)==false)	return false;
	if(::Save(f,ElementID)==false)	return false;
	return true;
}
bool	GUICmdMoveElement::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)	return false;
	if(::Load(f,MovY)==false)	return false;
	if(::Load(f,ElementID)==false)	return false;
	return true;
}

void	GUICmdMoveElement::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdMoveElement	Cmd(GetLayersBase());
		Cmd.MovX		=MovX;
		Cmd.MovY		=MovY;
		Cmd.ElementID	=ElementID;
		PPage->TransmitDirectly(&Cmd);
	}
}

//====================================================================================

GUICmdReqPickRasterColorProfile::GUICmdReqPickRasterColorProfile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqPickRasterColorProfile::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	return true;
}
bool	GUICmdReqPickRasterColorProfile::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;
	return true;
}

void	GUICmdReqPickRasterColorProfile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdPickRasterColorProfile	Cmd(GetLayersBase());
		Cmd.LocalX		=LocalX;
		Cmd.LocalY		=LocalY;
		PPage->TransmitDirectly(&Cmd);
	}
}

GUICmdReqRasterColorProfiles::GUICmdReqRasterColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqRasterColorProfiles::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterColorProfiles	*SendBack=GetSendBack(GUICmdAckRasterColorProfiles,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		SendBack->ColorProfiles=Base->ColorProfiles;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckRasterColorProfiles::GUICmdAckRasterColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRasterColorProfiles::Load(QIODevice *f)
{
	if(ColorProfiles.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckRasterColorProfiles::Save(QIODevice *f)
{
	if(ColorProfiles.Save(f)==false)
		return false;
	return true;
}

GUICmdSetRasterColorProfiles::GUICmdSetRasterColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetRasterColorProfiles::Load(QIODevice *f)
{
	if(ColorProfiles.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetRasterColorProfiles::Save(QIODevice *f)
{
	if(ColorProfiles.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetRasterColorProfiles::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		Base->ColorProfiles	=ColorProfiles;
		Base->ColorProfiles.MakeTable();
	}
}
	
GUICmdConvertColorProfiles::GUICmdConvertColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdConvertColorProfiles::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdConvertColorProfiles	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
	}
}

GUICmdReqRasterProfileValue::GUICmdReqRasterProfileValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRasterProfileValue::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	return true;
}
bool	GUICmdReqRasterProfileValue::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;
	return true;
}
void	GUICmdReqRasterProfileValue::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterProfileValue	*SendBack=GetSendBack(GUICmdAckRasterProfileValue,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdReqRasterProfileValue	Cmd(GetLayersBase());
		Cmd.LocalX		=LocalX;
		Cmd.LocalY		=LocalY;
		PPage->TransmitDirectly(&Cmd);
		SendBack->PDFColor				=Cmd.PDFColor;
		SendBack->ConvertedImageColor	=Cmd.ConvertedImageColor;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckRasterProfileValue::GUICmdAckRasterProfileValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRasterProfileValue::Load(QIODevice *f)
{
	if(::Load(f,PDFColor)			==false)	return false;
	if(::Load(f,ConvertedImageColor)==false)	return false;
	return true;
}
bool	GUICmdAckRasterProfileValue::Save(QIODevice *f)
{
	if(::Save(f,PDFColor)			==false)	return false;
	if(::Save(f,ConvertedImageColor)==false)	return false;
	return true;
}
//=====================================================================================================================
GUICmdSetPartialArea::GUICmdSetPartialArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetPartialArea::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false)	return false;
	return true;
}
bool	GUICmdSetPartialArea::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false)	return false;
	return true;
}
void	GUICmdSetPartialArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdSetPartialArea	Cmd(GetLayersBase());
		Cmd.Area=LocalArea;
		PPage->TransmitDirectly(&Cmd);
	}

}

//=====================================================================================================================
GUICmdAddMaskArea::GUICmdAddMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddMaskArea::Load(QIODevice *f)
{
	if(MaskArea.Load(f)==false)			return false;
	if(::Load(f,FileLayerID)==false)	return false;
	return true;
}
bool	GUICmdAddMaskArea::Save(QIODevice *f)
{
	if(MaskArea.Save(f)==false)			return false;
	if(::Save(f,FileLayerID)==false)	return false;
	return true;
}

void	GUICmdAddMaskArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdAddRasterMaskArea	Cmd(GetLayersBase());
		Cmd.MaskArea=MaskArea;
		Cmd.FileLayerID=FileLayerID;
		PPage->TransmitDirectly(&Cmd);
	}
}

GUICmdDelMaskArea::GUICmdDelMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDelMaskArea::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)	return false;
	if(::Load(f,MaskID)==false)			return false;
	return true;
}
bool	GUICmdDelMaskArea::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)	return false;
	if(::Save(f,MaskID)==false)			return false;
	return true;
}

void	GUICmdDelMaskArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdDelRasterMaskArea	Cmd(GetLayersBase());
		Cmd.MaskID		=MaskID;
		Cmd.FileLayerID	=FileLayerID;
		PPage->TransmitDirectly(&Cmd);
	}
}

GUICmdReqEnumMaskArea::GUICmdReqEnumMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqEnumMaskArea::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)	return false;
	return true;
}
bool	GUICmdReqEnumMaskArea::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)	return false;
	return true;
}

void	GUICmdReqEnumMaskArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckEnumMaskArea	*SendBack=GetSendBack(GUICmdAckEnumMaskArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdReqEnumMaskArea	Cmd(GetLayersBase());
		Cmd.FileLayerID	=FileLayerID;
		PPage->TransmitDirectly(&Cmd);
		SendBack->MaskIDList=Cmd.MaskIDList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckEnumMaskArea::GUICmdAckEnumMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckEnumMaskArea::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)	return false;
	if(MaskIDList.Load(f)	==false)	return false;
	return true;
}
bool	GUICmdAckEnumMaskArea::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)	return false;
	if(MaskIDList.Save(f)	==false)	return false;
	return true;
}
//=====================================================================================================================
GUICmdSetPDFWithSelfTransform::GUICmdSetPDFWithSelfTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetPDFWithSelfTransform::Load(QIODevice *f)
{
	if(::Load(f,PDFData)==false)	return false;
	return true;
}
bool	GUICmdSetPDFWithSelfTransform::Save(QIODevice *f)
{
	if(::Save(f,PDFData)==false)	return false;
	return true;
}
void	GUICmdSetPDFWithSelfTransform::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdSetPDFWithSelfTransform	Cmd(GetLayersBase());
		Cmd.PDFData		=PDFData;
		PPage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================================================

GUICmdReqRasterTransformInfo::GUICmdReqRasterTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqRasterTransformInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRasterTransformInfo	*SendBack=GetSendBack(GUICmdAckRasterTransformInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdReqRasterTransformInfo	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
		SendBack->TransformData=Cmd.TransformData;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckRasterTransformInfo::GUICmdAckRasterTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRasterTransformInfo::Load(QIODevice *f)
{
	if(::Load(f,TransformData)==false)	return false;
	return true;
}
bool	GUICmdAckRasterTransformInfo::Save(QIODevice *f)
{
	if(::Save(f,TransformData)==false)	return false;
	return true;
}

GUICmdSetRasterTransformInfo::GUICmdSetRasterTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetRasterTransformInfo::Load(QIODevice *f)
{
	if(::Load(f,TransformData)==false)	return false;
	return true;
}
bool	GUICmdSetRasterTransformInfo::Save(QIODevice *f)
{
	if(::Save(f,TransformData)==false)	return false;
	return true;
}
void	GUICmdSetRasterTransformInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdSetRasterTransformInfo	Cmd(GetLayersBase());
		Cmd.TransformData=TransformData;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================================================

GUICmdReqMakeProfileByImage::GUICmdReqMakeProfileByImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Mastered=true;
}
bool	GUICmdReqMakeProfileByImage::Load(QIODevice *f)
{
	if(::Load(f,Mastered)==false)	return false;
	return true;
}
bool	GUICmdReqMakeProfileByImage::Save(QIODevice *f)
{
	if(::Save(f,Mastered)==false)	return false;
	return true;
}

void	GUICmdReqMakeProfileByImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		RasterInPage	*PPage=dynamic_cast<RasterInPage *>(Base->GetPageData(localPage));
		CmdReqMakeProfileByImage	Cmd(GetLayersBase());
		Cmd.Mastered=Mastered;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================================================
GUICmdSetColorProfile::GUICmdSetColorProfile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetColorProfile::Load(QIODevice *f)
{
	if(::Load(f,ColorProfileData)==false)	return false;
	return true;
}
bool	GUICmdSetColorProfile::Save(QIODevice *f)
{
	if(::Save(f,ColorProfileData)==false)	return false;
	return true;
}

void	GUICmdSetColorProfile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterBase	*Base=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Raster");
	if(Base!=NULL){
		QBuffer	Buff(&ColorProfileData);
		if(Buff.open(QIODevice::ReadWrite)==true){
			ColorProfileContainer   ColorProfiler;
			if(ColorProfiler.Load(&Buff)==true){
				Base->ColorProfiles=ColorProfiler;
			}
		}
	}
}

