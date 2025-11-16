/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyRasterInspection\XPropertyRasterInspectionPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyRasterInspectionPacket.h"
#include "XRasterInspection.h"
#include "XRaster.h"
#include "XGeneralFunc.h"
#include "XRasterInspectionLibrary.h"

//=====================================================================================
GUICmdSendAddManualRasterInspection::GUICmdSendAddManualRasterInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualRasterInspection::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualRasterInspection::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualRasterInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	RasterInspectionBase *BBase=(RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
	if(BBase!=NULL){
		RasterInspectionInPage	*PData=dynamic_cast<RasterInspectionInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddRasterInspectionItemPacket	Cmd(this);
			Cmd.Area		=Area;
			Cmd.LibID		=LibID;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
//=====================================================================================
GUICmdReqReferencePDFData::GUICmdReqReferencePDFData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqReferencePDFData::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqReferencePDFData::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqReferencePDFData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckReferencePDFData	*SendBack=GetSendBack(GUICmdAckReferencePDFData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	RasterBase *RBBase=(RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
	if(RBBase!=NULL){
		RasterInPage	*PData=dynamic_cast<RasterInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			int	MinX=Area.GetMinX();
			int	MinY=Area.GetMinY();
			QImage	Pnt(Area.GetWidth(),Area.GetHeight(),QImage::Format_RGB32);
			Pnt.fill(Qt::black);
			IntList LayerList;
			PData->Draw(Pnt,LayerList,-MinX,-MinY,1.0,NULL);

			FlexArea	LocalArea=Area;
			LocalArea.MoveToNoClip(-MinX,-MinY);

			SendBack->Data.PDFColor=LocalArea.MakeAverage(Pnt);
		}
		DataInPage	*Dp=GetLayersBase()->GetPageData(localPage);
		if(Dp!=NULL){
			int	LayerNumb=Dp->GetLayerNumb();
			SendBack->Data.CountOfColorDim=LayerNumb;
			SendBack->Data.ColorDim=new double[LayerNumb];
			ImagePointerContainer	MasterImages;
			Dp->GetMasterImages(MasterImages);
			for(int layer=0;layer<LayerNumb;layer++){
				SendBack->Data.ColorDim[layer]=Area.GetAverage(0,0 ,*MasterImages[layer],1.0,1.0);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckReferencePDFData::GUICmdAckReferencePDFData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckReferencePDFData::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckReferencePDFData::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

GUICmdSendReferencePDFData::GUICmdSendReferencePDFData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendReferencePDFData::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendReferencePDFData::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendReferencePDFData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterInspectionBase *BBase=(RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
	if(BBase!=NULL){
		CmdRasterAddReferencePDF	Cmd(GetLayersBase());
		Cmd.RData=Data;
		BBase->TransmitDirectly(&Cmd);
	}
}	

//===================================================================
GUICmdGenerateRasterInspection::GUICmdGenerateRasterInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdGenerateRasterInspection::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateRasterInspection::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateRasterInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RasterInspectionBase *BBase=(RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
	if(BBase!=NULL){
		RasterInspectionInPage	*PData=dynamic_cast<RasterInspectionInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdGenerateRasterInspection	Cmd(this);
			Cmd.LibList		=LibList;
			PData->TransmitDirectly(&Cmd);
		}
	}

}

//===================================================================

GUICmdReqRasterInspectionInfoList::GUICmdReqRasterInspectionInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqRasterInspectionInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendRasterInspectionInfoList	*SendBack=GetSendBack(GUICmdSendRasterInspectionInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	RasterInspectionBase *BBase=(RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
	if(BBase!=NULL){
		BBase->EnumItems(SendBack->ItemIDList);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendRasterInspectionInfoList::GUICmdSendRasterInspectionInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendRasterInspectionInfoList::Load(QIODevice *f)
{
	if(ItemIDList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendRasterInspectionInfoList::Save(QIODevice *f)
{
	if(ItemIDList.Save(f)==false)
		return false;
	return true;
}
