#include "XPropertyGerberFastPacket.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdLoadGerber::GUICmdLoadGerber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FileLayerID=-1;
}
	
bool	GUICmdLoadGerber::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}

bool	GUICmdLoadGerber::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdLoadGerber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GerberFastBase	*PBase=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage;
	if(PBase->ModeDeliverAllPhasesInLoadGerber==true){
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(0);
		PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
	}
	else{
		PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	}
	if(PPage!=NULL){
		CmdLoadGerber	Da(GetLayersBase());
		Da.FileLayerID	=FileLayerID;
		Da.FileName		=FileName;
		Da.pData		=&Data;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

GUICmdAckLoadGerber::GUICmdAckLoadGerber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Ret=true;
}

bool	GUICmdAckLoadGerber::Load(QIODevice *f)
{
	if(::Load(f,Ret)==false)
		return false;
	return true;
}
	
bool	GUICmdAckLoadGerber::Save(QIODevice *f)
{
	if(::Save(f,Ret)==false)
		return false;
	return true;
}
//=========================================================================
GUICmdDeliverGerberToOtherPhases::GUICmdDeliverGerberToOtherPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdDeliverGerberToOtherPhases::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GerberFastBase	*PBase=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	if(PBase->ModeDeliverAllPhasesInLoadGerber==true){
		AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(0);
		GerberFastInPage	*SrcPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		for(int phase=1;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
			GerberFastInPage	*DestPPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		
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
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	QBuffer	Buff(&Array);
	Buff.open(QIODevice::ReadWrite);
}

//=========================================================================

GUICmdReqGerberArea::GUICmdReqGerberArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{

}

void	GUICmdReqGerberArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckGerberArea	*SendBack=GetSendBack(GUICmdAckGerberArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqGerberArea	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->MinX=Da.MinX;
		SendBack->MinY=Da.MinY;
		SendBack->MaxX=Da.MaxX;
		SendBack->MaxY=Da.MaxY;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckGerberArea::GUICmdAckGerberArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
}
bool	GUICmdAckGerberArea::Load(QIODevice *f)
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

bool	GUICmdAckGerberArea::Save(QIODevice *f)
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
GUICmdRegulateGerberArea::GUICmdRegulateGerberArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
}
bool	GUICmdRegulateGerberArea::Load(QIODevice *f)
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

bool	GUICmdRegulateGerberArea::Save(QIODevice *f)
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

void	GUICmdRegulateGerberArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdRegulateGerberArea	Da(GetLayersBase());
		Da.MinX	=MinX;
		Da.MinY	=MinY;
		Da.MaxX	=MaxX;
		Da.MaxY	=MaxY;
		PPage->TransmitDirectly(&Da);
	}
}

//=========================================================================
GUICmdClearGerber::GUICmdClearGerber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeToClearAllPhases=false;
}
	
bool	GUICmdClearGerber::Load(QIODevice *f)
{	
	if(::Load(f,ModeToClearAllPhases)==false)
		return false;
	return true;
}

bool	GUICmdClearGerber::Save(QIODevice *f)
{	
	if(::Save(f,ModeToClearAllPhases)==false)
		return false;
	return true;
}

void	GUICmdClearGerber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	if(ModeToClearAllPhases==true){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*H=PBase->GetPageDataPhase(phase);
			if(H!=NULL){
				GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(H->GetPageData(localPage));
				if(PPage!=NULL){
					CmdClearGerber	Cmd(GetLayersBase());
					PPage->TransmitDirectly(&Cmd);
				}
			}
		}
	}
	else{
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdClearGerber	Cmd(GetLayersBase());
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdMove::GUICmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XDir	=0;
	YDir	=0;
	PixelMode=true;
	OnlyOnePhase	=false;
}

bool	GUICmdMove::Load(QIODevice *f)
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
bool	GUICmdMove::Save(QIODevice *f)
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

void	GUICmdMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdMove	Cmd(GetLayersBase());
			Cmd.XDir=XDir;
			Cmd.YDir=YDir;
			Cmd.PixelMode=PixelMode;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdRotate::GUICmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Angle	=0;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdRotate::Load(QIODevice *f)
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
bool	GUICmdRotate::Save(QIODevice *f)
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

void	GUICmdRotate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdRotate	Cmd(GetLayersBase());
			Cmd.Angle=Angle;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdZoom::GUICmdZoom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XZoomDir	=0;
	YZoomDir	=0;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdZoom::Load(QIODevice *f)
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
bool	GUICmdZoom::Save(QIODevice *f)
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

void	GUICmdZoom::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdZoom	Cmd(GetLayersBase());
			Cmd.XZoomDir=XZoomDir;
			Cmd.YZoomDir=YZoomDir;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdShear::GUICmdShear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XMode=true;
	Shear=0;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdShear::Load(QIODevice *f)
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
bool	GUICmdShear::Save(QIODevice *f)
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

void	GUICmdShear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdShear	Cmd(GetLayersBase());
			Cmd.XMode=XMode;
			Cmd.Shear=Shear;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdMirror::GUICmdMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XMode	=true;
	CenterX	=0;
	CenterY	=0;
	OnlyOnePhase	=false;
}

bool	GUICmdMirror::Load(QIODevice *f)
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
bool	GUICmdMirror::Save(QIODevice *f)
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

void	GUICmdMirror::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdMirror	Cmd(GetLayersBase());
			Cmd.XMode=XMode;
			Cmd.CenterX=CenterX;
			Cmd.CenterY=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}

//=========================================================================
GUICmdCenterize::GUICmdCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MovX=MovY	=0.0;
	ZoomRate	=1.0;
	CenterX=CenterY	=0.0;
	OnlyOnePhase	=false;
}

bool	GUICmdCenterize::Load(QIODevice *f)
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
bool	GUICmdCenterize::Save(QIODevice *f)
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

void	GUICmdCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdCenterize	Cmd(GetLayersBase());
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
GUICmdCenterizeOnly::GUICmdCenterizeOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MovX=MovY	=0.0;
	CenterX=CenterY	=0.0;
	OnlyOnePhase	=false;
}

bool	GUICmdCenterizeOnly::Load(QIODevice *f)
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
bool	GUICmdCenterizeOnly::Save(QIODevice *f)
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

void	GUICmdCenterizeOnly::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
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
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
		if(PPage!=NULL){
			CmdCenterizeOnly	Cmd(GetLayersBase());
			Cmd.MovX=MovX;
			Cmd.MovY=MovY;
			Cmd.CenterX	=CenterX;
			Cmd.CenterY	=CenterY;
			PPage->TransmitDirectly(&Cmd);
		}
	}
}
//=========================================================================
GUICmdMatchingRoughly::GUICmdMatchingRoughly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMatchingRoughly::Load(QIODevice *f)
{
	if(ButtonsToShowLayer.Load(f)==false)
		return false;
	if(OperateCompositeIDList.Load(f)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,ZoomX)==false)
		return false;
	if(::Load(f,ZoomY)==false)
		return false;
	if(::Load(f,ZoomStartX)==false)
		return false;
	if(::Load(f,ZoomStartY)==false)
		return false;
	return true;
}
bool	GUICmdMatchingRoughly::Save(QIODevice *f)
{
	if(ButtonsToShowLayer.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,ZoomX)==false)
		return false;
	if(::Save(f,ZoomY)==false)
		return false;
	if(::Save(f,ZoomStartX)==false)
		return false;
	if(::Save(f,ZoomStartY)==false)
		return false;
	return true;
}

void	GUICmdMatchingRoughly::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMatchingRoughly	Cmd(GetLayersBase());
		Cmd.OperateCompositeIDList	=OperateCompositeIDList;
		Cmd.ButtonsToShowLayer		=ButtonsToShowLayer;
		Cmd.Dx=Dx;
		Cmd.Dy=Dy;
		Cmd.ZoomX		=ZoomX;
		Cmd.ZoomY		=ZoomY;
		Cmd.ZoomStartX	=ZoomStartX;
		Cmd.ZoomStartY	=ZoomStartY;
		PPage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//=========================================================================
GUICmdMatchingRoughlyReqShrinked::GUICmdMatchingRoughlyReqShrinked(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMatchingRoughlyReqShrinked::Load(QIODevice *f)
{
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	if(OperateCompositeIDList.Load(f)==false)
		return false;
	if(::Load(f,ShrinkedRate)==false)
		return false;
	return true;
}
bool	GUICmdMatchingRoughlyReqShrinked::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	if(::Save(f,ShrinkedRate)==false)
		return false;
	return true;
}

void	GUICmdMatchingRoughlyReqShrinked::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdMatchingRoughlyAckShrinked	*SendBack=GetSendBack(GUICmdMatchingRoughlyAckShrinked,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqGerberShrinked	Cmd(GetLayersBase());
		Cmd.ButtonsToOperateLayer		=ButtonsToOperateLayer;
		Cmd.OperateCompositeIDList		=OperateCompositeIDList;
		Cmd.ShrinkedRate			=ShrinkedRate;
		PPage->TransmitDirectly(&Cmd);
		SendBack->ImageData	=Cmd.ImageData;
		SendBack->GerberData=Cmd.GerberData;

	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}
GUICmdMatchingRoughlyAckShrinked::GUICmdMatchingRoughlyAckShrinked(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMatchingRoughlyAckShrinked::Load(QIODevice *f)
{
	if(::Load(f,ImageData)==false)
		return false;
	if(::Load(f,GerberData)==false)
		return false;
	return true;
}
bool	GUICmdMatchingRoughlyAckShrinked::Save(QIODevice *f)
{
	if(::Save(f,ImageData)==false)
		return false;
	if(::Save(f,GerberData)==false)
		return false;
	return true;
}
//=========================================================================
GUICmdMakeAutoMatch::GUICmdMakeAutoMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	UsageLayer		=true;
	UsageLayerID	=0;
	RemoveShiftable	=true;
}

bool	GUICmdMakeAutoMatch::Save(QIODevice *f)
{
	if(::Save(f,UsageLayer)==false)
		return false;
	if(::Save(f,UsageLayerID)==false)
		return false;
	if(::Save(f,RemoveShiftable)==false)
		return false;
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(ShiftableCompositeIDList.Save(f)==false)
		return false;
	if(ShiftableLayer.Save(f)==false)
		return false;
	if(ShiftableComposite.Save(f)==false)
		return false;
	if(::Save(f,MinDotsForAutoMatching)==false)
		return false;
	if(::Save(f,ShrinkDotForAutoMatchingArea)==false)
		return false;
	return true;
}
bool	GUICmdMakeAutoMatch::Load(QIODevice *f)
{
	if(::Load(f,UsageLayer)==false)
		return false;
	if(::Load(f,UsageLayerID)==false)
		return false;
	if(::Load(f,RemoveShiftable)==false)
		return false;
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	if(ShiftableCompositeIDList.Load(f)==false)
		return false;
	if(ShiftableLayer.Load(f)==false)
		return false;
	if(ShiftableComposite.Load(f)==false)
		return false;
	if(::Load(f,MinDotsForAutoMatching)==false)
		return false;
	if(::Load(f,ShrinkDotForAutoMatchingArea)==false)
		return false;
	return true;
}

void	GUICmdMakeAutoMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMakeAutoMatch	Cmd(GetLayersBase());
		Cmd.UsageLayer					=UsageLayer;
		Cmd.UsageLayerID				=UsageLayerID;
		Cmd.RemoveShiftable				=RemoveShiftable;
		Cmd.ShiftableLayer				=ShiftableLayer;
		Cmd.ShiftableCompositeIDList	=ShiftableCompositeIDList;
		Cmd.MinDotsForAutoMatching		=MinDotsForAutoMatching;
		Cmd.ShrinkDotForAutoMatchingArea=ShrinkDotForAutoMatchingArea;
		PPage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=========================================================================
GUICmdClearAutoMatch::GUICmdClearAutoMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdClearAutoMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdClearAutoMatch	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdExecAutoMatch::GUICmdExecAutoMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	UsageLayer		=true;
	UsageLayerID	=0;
	RemoveShiftable	=true;
	BrighterInPattern	=false;
}

bool	GUICmdExecAutoMatch::Save(QIODevice *f)
{
	if(::Save(f,UsageLayer)==false)
		return false;
	if(::Save(f,UsageLayerID)==false)
		return false;
	if(::Save(f,RemoveShiftable)==false)
		return false;
	if(ShiftableLayer.Save(f)==false)
		return false;
	if(ShiftableComposite.Save(f)==false)
		return false;
	if(::Save(f,BrighterInPattern)==false)
		return false;

	return true;
}
bool	GUICmdExecAutoMatch::Load(QIODevice *f)
{
	if(::Load(f,UsageLayer)==false)
		return false;
	if(::Load(f,UsageLayerID)==false)
		return false;
	if(::Load(f,RemoveShiftable)==false)
		return false;
	if(ShiftableLayer.Load(f)==false)
		return false;
	if(ShiftableComposite.Load(f)==false)
		return false;
	if(::Load(f,BrighterInPattern)==false)
		return false;

	return true;
}
void	GUICmdExecAutoMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdExecAutoMatch	Cmd(GetLayersBase());
		Cmd.UsageLayer					=UsageLayer;
		Cmd.UsageLayerID				=UsageLayerID;
		Cmd.RemoveShiftable				=RemoveShiftable;
		Cmd.ShiftableLayer				=ShiftableLayer;
		Cmd.ShiftableComposite			=ShiftableComposite;
		Cmd.BrighterInPattern			=BrighterInPattern;
		PPage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//=========================================================================

GUICmdReqOutsideOtherAlgorithm::GUICmdReqOutsideOtherAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


void	GUICmdReqOutsideOtherAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckOutsideOtherAlgorithm	*SendBack=GetSendBack(GUICmdAckOutsideOtherAlgorithm,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLRoot()==/**/"Basic" && L->GetDLLName()==/**/"GerberFast")
			continue;

		int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
			if(CurrentGlobalPage==globalpage){
				continue;
			}
			SlaveCommReqItemsOutside	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
			SlaveCommAckItemsOutside	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);

			RCmd.DestGlobalPage	=CurrentGlobalPage;
			RCmd.AlgoRoot	=L->GetDLLRoot();
			RCmd.AlgoName	=L->GetDLLName();

			if(RCmd.Send(globalpage,0,ACmd,60000)==true){
				ItemsDataOutsideList	*Item=new ItemsDataOutsideList();
				Item->AlgoRoot	= L->GetDLLRoot();
				Item->AlgoName	= L->GetDLLName();
				Item->ItemsData = ACmd.ItemsData;
				SendBack->Items.AppendList(Item);
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckOutsideOtherAlgorithm::GUICmdAckOutsideOtherAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckOutsideOtherAlgorithm::Save(QIODevice *f)
{
	if(Items.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdAckOutsideOtherAlgorithm::Load(QIODevice *f)
{
	if(Items.Load(f)==false)
		return false;
	return true;
}


SlaveCommReqItemsOutside::SlaveCommReqItemsOutside(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	DestGlobalPage=-1;
}

	
bool	SlaveCommReqItemsOutside::Load(QIODevice *f)
{
	if(::Load(f,DestGlobalPage)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	return true;
}

bool	SlaveCommReqItemsOutside::Save(QIODevice *f)
{
	if(::Save(f,DestGlobalPage)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	return true;
}


void	SlaveCommReqItemsOutside::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckItemsOutside	*S
	=(SlaveCommAckItemsOutside *)((GetSendBackPacket()==NULL)?new SlaveCommAckItemsOutside(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	CmdReqGeneralPipeInfo	PipeInfoCmd(GetLayersBase());
	if(PPage!=NULL){
		PPage->TransmitDirectly(&PipeInfoCmd);
	}

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);

		PipeInfoCmd.Point->Cmd	=GeneralPipeInfo::_GI_ReqItemsToMoveByAlignmentOutside;
		PipeInfoCmd.Point->DestinationPage	=DestGlobalPage;
		if(Pg->PipeGeneration(*PipeInfoCmd.Point)==true && PipeInfoCmd.Point->Something.count()>0){
			S->ItemsData=PipeInfoCmd.Point->Something;
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}


SlaveCommAckItemsOutside::SlaveCommAckItemsOutside(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}
	
bool	SlaveCommAckItemsOutside::Load(QIODevice *f)
{
	if(::Load(f,ItemsData)==false)
		return false;
	return true;
}

bool	SlaveCommAckItemsOutside::Save(QIODevice *f)
{
	if(::Save(f,ItemsData)==false)
		return false;
	return true;
}

//=========================================================================
GUICmdReflectOtherAlgorithm::GUICmdReflectOtherAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReflectOtherAlgorithm::Save(QIODevice *f)
{
	if(AddedItems.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdReflectOtherAlgorithm::Load(QIODevice *f)
{
	if(AddedItems.Load(f)==false)
		return false;
	return true;
}
void	GUICmdReflectOtherAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReflectOtherAlgorithm	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
	}

	CmdReqGeneralPipeInfo	PipeInfoCmd(GetLayersBase());
	if(PPage!=NULL){
		PPage->TransmitDirectly(&PipeInfoCmd);
	}

	for(ItemsDataOutsideList *L=AddedItems.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(L->AlgoRoot ,L->AlgoName);
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		PipeInfoCmd.Point->Cmd	=GeneralPipeInfo::_GI_CopyMoveByAlignmentFromOutside;
		PipeInfoCmd.Point->Something	=L->ItemsData;
		Ap->PipeGeneration(*PipeInfoCmd.Point);
	}
}
//=========================================================================
GUICmdSetAutoMatchButtons::GUICmdSetAutoMatchButtons(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	DrawAutoMatchingArea	=true;
	DrawAutoMatchingImage	=false;
}

bool	GUICmdSetAutoMatchButtons::Save(QIODevice *f)
{
	if(::Save(f,DrawAutoMatchingArea)==false)
		return false;
	if(::Save(f,DrawAutoMatchingImage)==false)
		return false;
	return true;
}
bool	GUICmdSetAutoMatchButtons::Load(QIODevice *f)
{
	if(::Load(f,DrawAutoMatchingArea)==false)
		return false;
	if(::Load(f,DrawAutoMatchingImage)==false)
		return false;
	return true;
}

void	GUICmdSetAutoMatchButtons::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamComm()->Mastered==false){
		GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
		if(DProp!=NULL){
			DProp->TransmitDirectly(this);
		}
	}
}
//=========================================================================
GUICmdRemoveAutoMatchingPoint::GUICmdRemoveAutoMatchingPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdRemoveAutoMatchingPoint::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdRemoveAutoMatchingPoint::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdRemoveAutoMatchingPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdRemoveAutoMatchPoint	Cmd(GetLayersBase());
		Cmd.LocalX=LocalX;
		Cmd.LocalY=LocalY;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdAllocateAutoMatching::GUICmdAllocateAutoMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdAllocateAutoMatching::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAllocateAutoMatching	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdReqAlgoGenMap::GUICmdReqAlgoGenMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlgoGenMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlgoGenMap	*SendBack=GetSendBack(GUICmdAckAlgoGenMap,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqAlgoGenMap	Da(GetLayersBase());
		Da.Pointer	=&SendBack->Data;
		PPage->TransmitDirectly(&Da);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlgoGenMap::GUICmdAckAlgoGenMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlgoGenMap::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdAckAlgoGenMap::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}


GUICmdSetAlgoGenMap::GUICmdSetAlgoGenMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetAlgoGenMap::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSetAlgoGenMap::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}
void	GUICmdSetAlgoGenMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSetAlgoGenMap	Da(GetLayersBase());
		Da.Pointer	=&Data;
		PPage->TransmitDirectly(&Da);
	}
}
//=========================================================================
GUICmdReqApertureInfo::GUICmdReqApertureInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,GerberLayer(-1)
{
}

bool	GUICmdReqApertureInfo::Save(QIODevice *f)
{
	if(::Save(f,GerberLayer)==false)
		return false;
	return true;
}
bool	GUICmdReqApertureInfo::Load(QIODevice *f)
{
	if(::Load(f,GerberLayer)==false)
		return false;
	return true;
}

void	GUICmdReqApertureInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckApertureInfo	*SendBack=GetSendBack(GUICmdAckApertureInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdReqGerberAperture	Da(GetLayersBase());
			Da.GerberLayer	=GerberLayer;
			PPage->TransmitDirectly(&Da);
			SendBack->InfoList	=Da.InfoList;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckApertureInfo::GUICmdAckApertureInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckApertureInfo::Save(QIODevice *f)
{
	if(InfoList.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdAckApertureInfo::Load(QIODevice *f)
{
	if(InfoList.Load(f)==false)
		return false;
	return true;
}

GUICmdChangeApertureInfo::GUICmdChangeApertureInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,GerberLayer(-1)
{
}
bool	GUICmdChangeApertureInfo::Save(QIODevice *f)
{
	if(::Save(f,GerberLayer)==false)
		return false;
	if(InfoList.Save(f)==false)
		return false;
	if(SelectedList.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdChangeApertureInfo::Load(QIODevice *f)
{
	if(::Load(f,GerberLayer)==false)
		return false;
	if(InfoList.Load(f)==false)
		return false;
	if(SelectedList.Load(f)==false)
		return false;
	return true;
}

void	GUICmdChangeApertureInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdChangeGerberAperture	Da(GetLayersBase());
			Da.GerberLayer	=GerberLayer;
			Da.ApertureList	=&InfoList;
			Da.SelectedList	=SelectedList;
			PPage->TransmitDirectly(&Da);
		}
	}
}

//=========================================================================

GUICmdReqFlushMatrix::GUICmdReqFlushMatrix(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqFlushMatrix::Save(QIODevice *f)
{
	if(ButtonsToShowLayer.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	return true;
}

bool	GUICmdReqFlushMatrix::Load(QIODevice *f)
{
	if(ButtonsToShowLayer.Load(f)==false)
		return false;
	if(OperateCompositeIDList.Load(f)==false)
		return false;
	return true;
}

void	GUICmdReqFlushMatrix::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFlushMatrix	*SendBack=GetSendBack(GUICmdAckFlushMatrix,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdFlushMatrix	Da(GetLayersBase());
			Da.ButtonsToShowLayer		=ButtonsToShowLayer;
			Da.ButtonsToOperateLayer	=ButtonsToShowLayer;
			PPage->TransmitDirectly(&Da);
			SendBack->MatrixData		=Da.MatrixData;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}




GUICmdAckFlushMatrix::GUICmdAckFlushMatrix(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckFlushMatrix::Save(QIODevice *f)
{
	if(MatrixData.Save(f)==false)
		return false;
	return true;
}

bool	GUICmdAckFlushMatrix::Load(QIODevice *f)
{
	if(MatrixData.Load(f)==false)
		return false;
	return true;
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
	if(ShownCompositeID.Load(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,LayerColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,CompColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
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
	if(ShownCompositeID.Save(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,LayerColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,CompColor[i])==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,FileLayerIDTable[i])==false){
			return false;
		}
	}
	return true;
}
void	GUICmdSetDrawAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamComm()->Mastered==false){
		GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
		if(DProp!=NULL){
			DProp->TransmitDirectly(this);
		}
	}
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdSetDrawAttr	WCmd(GetLayersBase());
			WCmd.ShownFileID		=ShownFileID;
			WCmd.ShownCompositeID	=ShownCompositeID;
			for(int i=0;i<MaxGerberLayer;i++){
				WCmd.FileLayerIDTable[i]	=FileLayerIDTable[i];
			}
			PPage->TransmitDirectly(&WCmd);
		}
	}
}

//=========================================================================

GUICmdReqMatchAutoLikeManual::GUICmdReqMatchAutoLikeManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqMatchAutoLikeManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMatchAutoLikeManual	*SendBack=GetSendBack(GUICmdAckMatchAutoLikeManual,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdReqMatchAutoLikeManual	Da(GetLayersBase());
			PPage->TransmitDirectly(&Da);
			SendBack->MatchAutoLikeManualData		=Da.MatchAutoLikeManualData;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMatchAutoLikeManual::GUICmdAckMatchAutoLikeManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMatchAutoLikeManual::GUICmdAckMatchAutoLikeManual::Save(QIODevice *f)
{
	if(::Save(f,MatchAutoLikeManualData)==false)
		return false;
	return true;
}
bool	GUICmdAckMatchAutoLikeManual::GUICmdAckMatchAutoLikeManual::Load(QIODevice *f)
{
	if(::Load(f,MatchAutoLikeManualData)==false)
		return false;
	return true;
}


GUICmdSendMatchAutoLikeManual::GUICmdSendMatchAutoLikeManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendMatchAutoLikeManual::Save(QIODevice *f)
{
	if(::Save(f,MatchAutoLikeManualData)==false)
		return false;
	return true;
}
bool	GUICmdSendMatchAutoLikeManual::Load(QIODevice *f)
{
	if(::Load(f,MatchAutoLikeManualData)==false)
		return false;
	return true;
}

void	GUICmdSendMatchAutoLikeManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdLoadMatchAutoLikeManual	Cmd(GetLayersBase());
			Cmd.MatchAutoLikeManualData	=MatchAutoLikeManualData;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	if(GetParamComm()->Mastered==false){
		GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
		if(DProp!=NULL){
			DProp->TransmitDirectly(this);
		}
	}
}

//=========================================================================

GUICmdAddMatchAutoLikeManualPoint::GUICmdAddMatchAutoLikeManualPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	PointType=1;
}

bool	GUICmdAddMatchAutoLikeManualPoint::Save(QIODevice *f)
{
	if(::Save(f,PointType)==false)
		return false;
	return true;
}
bool	GUICmdAddMatchAutoLikeManualPoint::Load(QIODevice *f)
{
	if(::Load(f,PointType)==false)
		return false;
	return true;
}

void	GUICmdAddMatchAutoLikeManualPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdAddMatchAutoLikeManualPoint	Cmd(GetLayersBase());
			Cmd.PointType	=PointType;
			PPage->TransmitDirectly(&Cmd);
		}
	}

}

//=========================================================================

GUICmdAddMatchingAlignmentPoint::GUICmdAddMatchingAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	PointType=1;
}

bool	GUICmdAddMatchingAlignmentPoint::Save(QIODevice *f)
{
	if(::Save(f,PointType)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdAddMatchingAlignmentPoint::Load(QIODevice *f)
{
	if(::Load(f,PointType)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

void	GUICmdAddMatchingAlignmentPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdAddMatchAutoLikeManualAlignment	Cmd(GetLayersBase());
			Cmd.PointType	=PointType;
			Cmd.Area		=Area;
			Cmd.LayerList	=LayerList;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=========================================================================

GUICmdGenerateOutline::GUICmdGenerateOutline(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGenerateOutline::Load(QIODevice *f)
{
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	if(ButtonsToOperateComposite.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateOutline::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(ButtonsToOperateComposite.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateOutline::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdGenerateOutline	Cmd(GetLayersBase());
			Cmd.ButtonsToOperateLayer		=ButtonsToOperateLayer;
			Cmd.ButtonsToOperateComposite	=ButtonsToOperateComposite;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=========================================================================

GUICmdCreateEchingFactor::GUICmdCreateEchingFactor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdCreateEchingFactor::Load(QIODevice *f)
{
	if(::Load(f,CornerR)==false)
		return false;
	return true;
}

bool	GUICmdCreateEchingFactor::Save(QIODevice *f)
{
	if(::Save(f,CornerR)==false)
		return false;
	return true;
}

void	GUICmdCreateEchingFactor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
			GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
			if(PPage!=NULL){
				CmdCreateEchingFactor	Cmd(GetLayersBase());
				Cmd.CornerR	=CornerR;
				PPage->TransmitDirectly(&Cmd);
			}
		}
	}
	SendAck(localPage);
}

//=========================================================================

GUICmdClearOutline::GUICmdClearOutline(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdClearOutline::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=PBase->GetPageDataPhase(phase);
			GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
			if(PPage!=NULL){
				CmdClearOutline	Cmd(GetLayersBase());
				PPage->TransmitDirectly(&Cmd);
			}
		}
	}
	SendAck(localPage);
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
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(Ab==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
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
	LineNo=0;
}

bool	GUICmdSelectLine::Save(QIODevice *f)
{
	if(::Save(f,LineNo)==false)
		return false;

	return true;
}
bool	GUICmdSelectLine::Load(QIODevice *f)
{
	if(::Load(f,LineNo)==false)
		return false;

	return true;
}

void	GUICmdSelectLine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdSelectLine	Cmd(GetLayersBase());
			Cmd.LineNo		=LineNo;
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
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
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
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
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
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(Ah->GetPageData(localPage));
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

GUICmdAddEmptyLayer::GUICmdAddEmptyLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LineNo=0;
}

bool	GUICmdAddEmptyLayer::Save(QIODevice *f)
{
	if(::Save(f,LineNo)==false)
		return false;

	return true;
}
bool	GUICmdAddEmptyLayer::Load(QIODevice *f)
{
	if(::Load(f,LineNo)==false)
		return false;

	return true;
}

void	GUICmdAddEmptyLayer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAddEmptyLayer	*SendBack=GetSendBack(GUICmdAckAddEmptyLayer,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdAddEmptyLayer	Cmd(GetLayersBase());
			Cmd.LineNo		=LineNo;
			PPage->TransmitDirectly(&Cmd);
			SendBack->FileLayerID=Cmd.FileLayerID;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAddEmptyLayer::GUICmdAckAddEmptyLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FileLayerID=0;
}

bool	GUICmdAckAddEmptyLayer::Load(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;

	return true;
}

bool	GUICmdAckAddEmptyLayer::Save(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;

	return true;
}

//=========================================================================

GUICmdAddGerberLine::GUICmdAddGerberLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FileLayerNo	=0;
	X1=Y1=X2=Y2	=0;
}

bool	GUICmdAddGerberLine::Save(QIODevice *f)
{
	if(::Save(f,FileLayerNo)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;

	return true;
}
bool	GUICmdAddGerberLine::Load(QIODevice *f)
{
	if(::Load(f,FileLayerNo)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;

	return true;
}

void	GUICmdAddGerberLine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdAddGerberLineA	Cmd(GetLayersBase());
			Cmd.FileLayerNo	=FileLayerNo;
			Cmd.DCode		=DCode;
			Cmd.X1	=X1;
			Cmd.Y1	=Y1;
			Cmd.X2	=X2;
			Cmd.Y2	=Y2;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}


//=========================================================================

GUICmdGenerateCenterize::GUICmdGenerateCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MaxWidth=100.0;
}

bool	GUICmdGenerateCenterize::Save(QIODevice *f)
{
	if(::Save(f,MaxWidth)==false)
		return false;

	return true;
}
bool	GUICmdGenerateCenterize::Load(QIODevice *f)
{
	if(::Load(f,MaxWidth)==false)
		return false;

	return true;
}
void	GUICmdGenerateCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdGenerateCenterize	Cmd(GetLayersBase());
			Cmd.MaxWidth	=MaxWidth;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}


//=========================================================================

GUICmdGenerateBlockFrom::GUICmdGenerateBlockFrom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LayerOrComposite		=0;	//0:Layer ,1:Composite;
	LayerCompositeID		=-1;
	GeneratedLibType		=1;
	GeneratedLibID			=-1;
	OmitLayerOrComposite	=0;	//0:Layer ,1:Composite;
	OmitLayerCompositeID	=-1;
}

bool	GUICmdGenerateBlockFrom::Save(QIODevice *f)
{
	if(::Save(f,LayerOrComposite)==false)
		return false;
	if(::Save(f,LayerCompositeID)==false)
		return false;
	if(::Save(f,GeneratedLibType)==false)
		return false;
	if(::Save(f,GeneratedLibID)==false)
		return false;
	if(::Save(f,OmitLayerOrComposite)==false)
		return false;
	if(::Save(f,OmitLayerCompositeID)==false)
		return false;

	if(GFileContainer.Save(f)==false)
		return false;
	if(::Save(f,ThresholdData)==false)
		return false;
	return true;
}
bool	GUICmdGenerateBlockFrom::Load(QIODevice *f)
{
	if(::Load(f,LayerOrComposite)==false)
		return false;
	if(::Load(f,LayerCompositeID)==false)
		return false;
	if(::Load(f,GeneratedLibType)==false)
		return false;
	if(::Load(f,GeneratedLibID)==false)
		return false;
	if(::Load(f,OmitLayerOrComposite)==false)
		return false;
	if(::Load(f,OmitLayerCompositeID)==false)
		return false;

	if(GFileContainer.Load(f)==false)
		return false;
	if(::Load(f,ThresholdData)==false)
		return false;
	return true;
}
void	GUICmdGenerateBlockFrom::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			GenerateBlocksFrom	Cmd(GetLayersBase());
			Cmd.LayerOrComposite	=LayerOrComposite	;
			Cmd.LayerCompositeID	=LayerCompositeID	;
			Cmd.GeneratedLibType	=GeneratedLibType	;
			Cmd.GeneratedLibID		=GeneratedLibID		;
			Cmd.OmitLayerOrComposite=OmitLayerOrComposite	;
			Cmd.OmitLayerCompositeID=OmitLayerCompositeID	;
			
			Cmd.ThresholdData		=ThresholdData		;
			Cmd.GFileContainer		=GFileContainer;
			PPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=========================================================================

GUICmdMakeClusterItem::GUICmdMakeClusterItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMakeClusterItem::Load(QIODevice *f)
{
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	if(OperateCompositeIDList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdMakeClusterItem::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdMakeClusterItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase!=NULL){
		GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
		if(PPage!=NULL){
			CmdMakeClusterItem	RCmd(GetLayersBase());
			RCmd.ButtonsToOperateLayer		=ButtonsToOperateLayer;
			RCmd.OperateCompositeIDList		=OperateCompositeIDList;
			PPage->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
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



