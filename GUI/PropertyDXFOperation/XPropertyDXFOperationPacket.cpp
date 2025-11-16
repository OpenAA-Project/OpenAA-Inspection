#include "XPropertyDXFOperationPacket.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDXFOperation.h"
#include "XDXFOperationPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdLoadDXF::GUICmdLoadDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdLoadDXF::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	if(::Load(f,FileNo)==false)
		return false;
	return true;
}

bool	GUICmdLoadDXF::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	if(::Save(f,FileNo)==false)
		return false;
	return true;
}

void	GUICmdLoadDXF::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DXFOperationBase	*PBase=(DXFOperationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage;
	PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdLoadDXF	Da(GetLayersBase());
		Da.FileName		=FileName;
		Da.pData		=&Data;
		Da.FileNo		=FileNo;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//=========================================================================
GUICmdMove::GUICmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XDir	=0;
	YDir	=0;
	PixelMode=true;
	OnlySelected=true;
}

bool	GUICmdMove::Load(QIODevice *f)
{
	if(::Load(f,XDir)==false)
		return false;
	if(::Load(f,YDir)==false)
		return false;
	if(::Load(f,PixelMode)==false)
		return false;
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFMove	Cmd(GetLayersBase());
		Cmd.XDir=XDir;
		Cmd.YDir=YDir;
		Cmd.PixelMode=PixelMode;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdRotate::GUICmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Angle	=0;
	CenterX	=0;
	CenterY	=0;
	OnlySelected=true;
}

bool	GUICmdRotate::Load(QIODevice *f)
{
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdRotate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFRotate	Cmd(GetLayersBase());
		Cmd.Angle=Angle;
		Cmd.CenterX=CenterX;
		Cmd.CenterY=CenterY;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
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
	OnlySelected=true;
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
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdZoom::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFZoom	Cmd(GetLayersBase());
		Cmd.XZoomDir=XZoomDir;
		Cmd.YZoomDir=YZoomDir;
		Cmd.CenterX=CenterX;
		Cmd.CenterY=CenterY;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
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
	OnlySelected=true;
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
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdShear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFShear	Cmd(GetLayersBase());
		Cmd.XMode=XMode;
		Cmd.Shear=Shear;
		Cmd.CenterX=CenterX;
		Cmd.CenterY=CenterY;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdMirror::GUICmdMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	XMode	=true;
	CenterX	=0;
	CenterY	=0;
	OnlySelected=true;
}

bool	GUICmdMirror::Load(QIODevice *f)
{
	if(::Load(f,XMode)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdMirror::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFMirror	Cmd(GetLayersBase());
		Cmd.XMode=XMode;
		Cmd.CenterX=CenterX;
		Cmd.CenterY=CenterY;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdCenterize::GUICmdCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MovX=MovY	=0.0;
	ZoomRate	=1.0;
	CenterX=CenterY	=0.0;
	OnlySelected=true;
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
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFCenterize	Cmd(GetLayersBase());
		Cmd.MovX=MovX;
		Cmd.MovY=MovY;
		Cmd.ZoomRate=ZoomRate;
		Cmd.CenterX	=CenterX;
		Cmd.CenterY	=CenterY;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================
GUICmdCenterizeOnly::GUICmdCenterizeOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MovX=MovY	=0.0;
	CenterX=CenterY	=0.0;
	OnlySelected=true;
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
	if(::Load(f,OnlySelected)==false)
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
	if(::Save(f,OnlySelected)==false)
		return false;
	return true;
}

void	GUICmdCenterizeOnly::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDXFCenterizeOnly	Cmd(GetLayersBase());
		Cmd.MovX=MovX;
		Cmd.MovY=MovY;
		Cmd.CenterX	=CenterX;
		Cmd.CenterY	=CenterY;
		Cmd.OnlySelected	=OnlySelected;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================

GUICmdReqDXFArea::GUICmdReqDXFArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{

}

void	GUICmdReqDXFArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDXFArea	*SendBack=GetSendBack(GUICmdAckDXFArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqDXFArea	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->MinX=Da.MinX;
		SendBack->MinY=Da.MinY;
		SendBack->MaxX=Da.MaxX;
		SendBack->MaxY=Da.MaxY;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckDXFArea::GUICmdAckDXFArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
}
bool	GUICmdAckDXFArea::Load(QIODevice *f)
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

bool	GUICmdAckDXFArea::Save(QIODevice *f)
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

GUICmdReqDXFLayerInfo::GUICmdReqDXFLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDXFLayerInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDXFLayerInfo	*SendBack=GetSendBack(GUICmdAckDXFLayerInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		SendBack->DXFLayerList=PPage->DXFLayerList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckDXFLayerInfo::GUICmdAckDXFLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,DXFLayerList(NULL)
{
}
bool	GUICmdAckDXFLayerInfo::Load(QIODevice *f)
{
	if(DXFLayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckDXFLayerInfo::Save(QIODevice *f)
{
	if(DXFLayerList.Save(f)==false)
		return false;
	return true;
}

//=========================================================================

GUICmdSetLineWidth::GUICmdSetLineWidth(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetLineWidth::Load(QIODevice *f)
{
	if(::Load(f,LineWidth)==false)
		return false;
	return true;
}
bool	GUICmdSetLineWidth::Save(QIODevice *f)
{
	if(::Save(f,LineWidth)==false)
		return false;
	return true;
}

void	GUICmdSetLineWidth::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSetLineWidth	Da(GetLayersBase());
		Da.LineWidth=LineWidth;
		PPage->TransmitDirectly(&Da);
	}
}

//====================================================================================

GUICmdDXFDrawMode::GUICmdDXFDrawMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdDXFDrawMode::Save(QIODevice *f)
{
	BYTE	m=(BYTE)Mode;
	if(::Save(f,m)==false)
		return false;

	if(::Save(f,MoveMode)==false)
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

	return true;
}
bool	GUICmdDXFDrawMode::Load(QIODevice *f)
{
	BYTE	m;
	if(::Load(f,m)==false)
		return false;
	Mode=(DisplayImage::__DrawingMode)m;

	if(::Load(f,MoveMode)==false)
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

	return true;}

void	GUICmdDXFDrawMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	DXFOperationInPage	*GPage	=(DXFOperationInPage *)Base->GetPageData(localPage);

	GPage->MoveMode				=MoveMode;
	GPage->RotateMode			=RotateMode;
	GPage->SlopeXMode			=SlopeXMode;
	GPage->SlopeYMode			=SlopeYMode;
	GPage->ExtendMode			=ExtendMode;
	GPage->Mode					=Mode;
	GPage->LastPosX				=LastPosX;
	GPage->LastPosY				=LastPosY;
	GPage->MoveStartPosX		=MoveStartPosX;
	GPage->MoveStartPosY		=MoveStartPosY;
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
}

//====================================================================================

GUICmdMakeAlgo::GUICmdMakeAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMakeAlgo::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdMakeAlgo::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}
void	GUICmdMakeAlgo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMakeAlgo	Da(GetLayersBase());
		Da.LibType	=LibType;
		Da.LibID	=LibID	;
		PPage->TransmitDirectly(&Da);
	}
}

//====================================================================================

GUICmdMakeAlgoFillArea::GUICmdMakeAlgoFillArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMakeAlgoFillArea::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdMakeAlgoFillArea::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}
void	GUICmdMakeAlgoFillArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMakeAlgoFillArea	Da(GetLayersBase());
		Da.LibType	=LibType;
		Da.LibID	=LibID	;
		PPage->TransmitDirectly(&Da);
	}
}
//====================================================================================

GUICmdMakeAlgoByColor::GUICmdMakeAlgoByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMakeAlgoByColor::Load(QIODevice *f)
{
	if(ColorCode.Load(f)==false)
		return false;
	if(::Load(f,Color)==false)
		return false;
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdMakeAlgoByColor::Save(QIODevice *f)
{
	if(ColorCode.Save(f)==false)
		return false;
	if(::Save(f,Color)==false)
		return false;
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}
void	GUICmdMakeAlgoByColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMakeAlgoByColor	Da(GetLayersBase());
		Da.ColorCode=ColorCode;
		Da.Color	=Color;
		Da.LibType	=LibType;
		Da.LibID	=LibID	;
		PPage->TransmitDirectly(&Da);
	}
}

//====================================================================================

GUICmdMatchAutomatic::GUICmdMatchAutomatic(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMatchAutomatic::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMatchAutomatic	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
	}
}

//====================================================================================

GUICmdSelectInColor::GUICmdSelectInColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectInColor::Load(QIODevice *f)
{
	if(::Load(f,PickupRL)==false)	return false;
	if(::Load(f,PickupRH)==false)	return false;
	if(::Load(f,PickupGL)==false)	return false;
	if(::Load(f,PickupGH)==false)	return false;
	if(::Load(f,PickupBL)==false)	return false;
	if(::Load(f,PickupBH)==false)	return false;

	if(::Load(f,AreaX1)==false)	return false;
	if(::Load(f,AreaY1)==false)	return false;
	if(::Load(f,AreaX2)==false)	return false;
	if(::Load(f,AreaY2)==false)	return false;

	return true;
}
bool	GUICmdSelectInColor::Save(QIODevice *f)
{
	if(::Save(f,PickupRL)==false)	return false;
	if(::Save(f,PickupRH)==false)	return false;
	if(::Save(f,PickupGL)==false)	return false;
	if(::Save(f,PickupGH)==false)	return false;
	if(::Save(f,PickupBL)==false)	return false;
	if(::Save(f,PickupBH)==false)	return false;

	if(::Save(f,AreaX1)==false)	return false;
	if(::Save(f,AreaY1)==false)	return false;
	if(::Save(f,AreaX2)==false)	return false;
	if(::Save(f,AreaY2)==false)	return false;
	return true;
}
void	GUICmdSelectInColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSelectInColor	Da(GetLayersBase());
		Da.PickupRL=PickupRL;
		Da.PickupRH=PickupRH;
		Da.PickupGL=PickupGL;
		Da.PickupGH=PickupGH;
		Da.PickupBL=PickupBL;
		Da.PickupBH=PickupBH;
		Da.AreaX1	=AreaX1;
		Da.AreaY1	=0;
		Da.AreaX2	=AreaX2;
		Da.AreaY2	=PPage->GetMaxLines();
		PPage->TransmitDirectly(&Da);
	}
}

//====================================================================================

GUICmdReqColorFromDXF::GUICmdReqColorFromDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqColorFromDXF::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorFromDXF	*SendBack=GetSendBack(GUICmdAckColorFromDXF,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqColorFromDXF	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
		SendBack->ColorList=Cmd.ColorList;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorFromDXF::GUICmdAckColorFromDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,ColorList(DXFCommonDataID)
{
}
bool	GUICmdAckColorFromDXF::Load(QIODevice *f)
{
	if(ColorList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckColorFromDXF::Save(QIODevice *f)
{
	if(ColorList.Save(f)==false)
		return false;
	return true;

}

//====================================================================================

GUICmdDelMaskByCAD::GUICmdDelMaskByCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdDelMaskByCAD::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
		AlgorithmBase	*OriginBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
		struct	OriginTypeSelection SelectMode(OriginBase);
		SelectMode._FromCAD=true;
		PPage->SelectItemsByOriginType(SelectMode,LayerList);
		PPage->DeleteSelectedItems(LayerList);
	}
}

//====================================================================================

GUICmdExecuteInitialMask::GUICmdExecuteInitialMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdExecuteInitialMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Masking");
	if(PBase==NULL)
		return;
	if(localPage==0){
		ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
		if(Res!=NULL){
			ResultBaseForAlgorithmRoot	*ARes=Res->GetResultBaseForAlgorithm(PBase);
			ExecuteInitialAfterEditInfo EInfo;
			EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			PBase->ExecuteInitialAfterEdit	(0,ARes,EInfo);
		}
	}
}

//====================================================================================

GUICmdDXFDraw::GUICmdDXFDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDXFDraw::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	if(::Load(f,FileNo)==false)	return false;
	return true;
}
bool	GUICmdDXFDraw::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;
	if(::Save(f,FileNo)==false)	return false;
	return true;
}

void	GUICmdDXFDraw::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMakeDXFPaint	Cmd(GetLayersBase());
		Cmd.LocalX=LocalX;
		Cmd.LocalY=LocalY;
		Cmd.FileNo=FileNo;
		PPage->TransmitDirectly(&Cmd);
	}
}

//====================================================================================

GUICmdSelectFileNo::GUICmdSelectFileNo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSelectFileNo::Load(QIODevice *f)
{
	if(::Load(f,FileNo)==false)	return false;
	return true;
}
bool	GUICmdSelectFileNo::Save(QIODevice *f)
{
	if(::Save(f,FileNo)==false)	return false;
	return true;
}

void	GUICmdSelectFileNo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSelectFileNo	Cmd(GetLayersBase());
		Cmd.FileNo=FileNo;
		PPage->TransmitDirectly(&Cmd);
	}
}

//========================================================================================================

GUICmdReqAllocationLibByColor::GUICmdReqAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAllocationLibByColor::Load(QIODevice *f)
{
	if(::Load(f,LevelID)==false)	return false;
	return true;
}
bool	GUICmdReqAllocationLibByColor::Save(QIODevice *f)
{
	if(::Save(f,LevelID)==false)	return false;
	return true;
}

void	GUICmdReqAllocationLibByColor::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAllocationLibByColor	*SendBack=GetSendBack(GUICmdAckAllocationLibByColor,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	DXFOperationBase *BBase=(DXFOperationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DXFOperation");
	if(BBase!=NULL){
		CmdReqAllocationLibByColor	Cmd(GetLayersBase());
		Cmd.ThresholdLevelID=LevelID;
		BBase->TransmitDirectly(&Cmd);

		SendBack->AllocationLibByColorContainerInst	=Cmd.Container;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAllocationLibByColor::GUICmdAckAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
	,AllocationLibByColorContainerInst(DXFCommonDataID)
{
}
bool	GUICmdAckAllocationLibByColor::Load(QIODevice *f)
{
	if(AllocationLibByColorContainerInst.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckAllocationLibByColor::Save(QIODevice *f)
{
	if(AllocationLibByColorContainerInst.Save(f)==false)
		return false;
	return true;
}

GUICmdSetAllocationLibByColor::GUICmdSetAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
	,AllocationLibByColorContainerInst(DXFCommonDataID)
{
}
bool	GUICmdSetAllocationLibByColor::Load(QIODevice *f)
{
	if(::Load(f,LevelID)==false)
		return false;
	if(AllocationLibByColorContainerInst.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetAllocationLibByColor::Save(QIODevice *f)
{
	if(::Save(f,LevelID)==false)
		return false;
	if(AllocationLibByColorContainerInst.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetAllocationLibByColor::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DXFOperationBase *BBase=(DXFOperationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DXFOperation");
	if(BBase!=NULL){
		CmdSetAllocationLibByColor	Cmd(GetLayersBase());
		Cmd.ThresholdLevelID=LevelID;
		Cmd.Container		=AllocationLibByColorContainerInst;
		BBase->TransmitDirectly(&Cmd);

		CmdSaveAllocationLibByColor	RCmd(GetLayersBase());
		BBase->TransmitDirectly(&RCmd);
	}
}

//========================================================================================================

GUICmdMakeEffectiveMask::GUICmdMakeEffectiveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ShrinkDot=0;
}
bool	GUICmdMakeEffectiveMask::Load(QIODevice *f)
{
	if(::Load(f,ShrinkDot)==false)
		return false;
	return true;
}
bool	GUICmdMakeEffectiveMask::Save(QIODevice *f)
{
	if(::Save(f,ShrinkDot)==false)
		return false;
	return true;
}
void	GUICmdMakeEffectiveMask::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdMakeEffectiveMask	Cmd(GetLayersBase());
		Cmd.ShrinkDot=ShrinkDot;
		PPage->TransmitDirectly(&Cmd);
	}
}
GUICmdSendEffectiveMask::GUICmdSendEffectiveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendEffectiveMask::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSendEffectiveMask	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
	}
}

//========================================================================================================

GUICmdSetDXFWithSelfTransform::GUICmdSetDXFWithSelfTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetDXFWithSelfTransform::Load(QIODevice *f)
{
	if(::Load(f,DXFData)==false)	return false;
	return true;
}
bool	GUICmdSetDXFWithSelfTransform::Save(QIODevice *f)
{
	if(::Save(f,DXFData)==false)	return false;
	return true;
}

void	GUICmdSetDXFWithSelfTransform::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSetDXFWithSelfTransform	Cmd(GetLayersBase());
		Cmd.DXFData=DXFData;
		PPage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================================================

GUICmdReqDXFTransformInfo::GUICmdReqDXFTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDXFTransformInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDXFTransformInfo	*SendBack=GetSendBack(GUICmdAckDXFTransformInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqDXFTransformInfo	Cmd(GetLayersBase());
		PPage->TransmitDirectly(&Cmd);
		SendBack->TransformData=Cmd.TransformData;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckDXFTransformInfo::GUICmdAckDXFTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckDXFTransformInfo::Load(QIODevice *f)
{
	if(::Load(f,TransformData)==false)	return false;
	return true;
}
bool	GUICmdAckDXFTransformInfo::Save(QIODevice *f)
{
	if(::Save(f,TransformData)==false)	return false;
	return true;
}

GUICmdSetDXFTransformInfo::GUICmdSetDXFTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetDXFTransformInfo::Load(QIODevice *f)
{
	if(::Load(f,TransformData)==false)	return false;
	return true;
}
bool	GUICmdSetDXFTransformInfo::Save(QIODevice *f)
{
	if(::Save(f,TransformData)==false)	return false;
	return true;
}
void	GUICmdSetDXFTransformInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	if(PBase==NULL)
		return;
	DXFOperationInPage	*PPage=dynamic_cast<DXFOperationInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdSetDXFTransformInfo	Cmd(GetLayersBase());
		Cmd.TransformData=TransformData;
		PPage->TransmitDirectly(&Cmd);
	}
}