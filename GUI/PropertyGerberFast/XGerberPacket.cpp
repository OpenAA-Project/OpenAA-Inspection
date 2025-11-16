/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyGerber\XGerberPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGerberAperture.h"
#include "XGUIGerberPacket.h"
#include "XGeneralFunc.h"
#include "XGerberFast.h"
#include "XPropertyGerberFastPacket.h"
/*
void	GerberFastBase::GerberLayerList::MakeLayerBitmap(GerberFastBase *GBase
													 ,GerberFastInPage *GPage
													 ,BYTE **GerberMap ,int GXByte ,int GYLen)
{}
void	GerberCompositeLayer::MakeLayerBitmap(GerberFastBase *GBase
											,GerberInPage *GPage
											,BYTE **GerberMap ,int XByte ,int YLen)
{}
*/

GUICmdReqApertureList::GUICmdReqApertureList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqApertureList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqApertureList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

void	GUICmdReqApertureList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendApertureList	*SendBack=GetSendBack(GUICmdSendApertureList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	if(localPage==0){
		SendBack->Layer=Layer;
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		if(Base!=NULL){
			AlgorithmInPageRoot	*APage=Base->GetPageData(localPage);
			APage->TransmitDirectly(SendBack);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendApertureList::GUICmdSendApertureList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ApertureDim=NULL;
	Count=0;
}
GUICmdSendApertureList::~GUICmdSendApertureList(void)
{
	if(ApertureDim!=NULL){
		delete	[]ApertureDim;
		ApertureDim=NULL;
	}
	Count=0;
}
bool	GUICmdSendApertureList::Save(QIODevice *f)
{
	if(::Save(f,Count)==false){
		return false;
	}
	if(f->write((const char *)ApertureDim,sizeof(ApertureDim[0])*Count)!=sizeof(ApertureDim[0])*Count){
		return false;
	}
	return true;
}
bool	GUICmdSendApertureList::Load(QIODevice *f)
{
	if(::Load(f,Count)==false){
		return false;
	}

	if(ApertureDim!=NULL){
		delete	[]ApertureDim;
		ApertureDim=NULL;
	}
	ApertureDim=new struct	ApertureInfo[Count];
	if(f->read((char *)ApertureDim,sizeof(ApertureDim[0])*Count)!=sizeof(ApertureDim[0])*Count){
		return false;
	}

	return true;
}

void	GUICmdSendApertureList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
GUICmdReqSetApertureList::GUICmdReqSetApertureList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ApertureDim=NULL;
	Count=0;
}

void	GUICmdReqSetApertureList::Set(struct	ApertureInfo *ApertureList ,int ACount)
{
	if(ApertureDim!=NULL){
		delete	[]ApertureDim;
		ApertureDim=NULL;
	}
	Count=ACount;
	ApertureDim=new struct	ApertureInfo[Count];
	memcpy(ApertureDim,ApertureList,Count*sizeof(ApertureDim[0]));
}

bool	GUICmdReqSetApertureList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Count)==false){
		return false;
	}
	if(f->write((const char *)ApertureDim,sizeof(ApertureDim[0])*Count)!=sizeof(ApertureDim[0])*Count){
		return false;
	}
	return true;
}
bool	GUICmdReqSetApertureList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Count)==false){
		return false;
	}

	if(ApertureDim!=NULL){
		delete	[]ApertureDim;
		ApertureDim=NULL;
	}
	ApertureDim=new struct	ApertureInfo[Count];
	if(f->read((char *)ApertureDim,sizeof(ApertureDim[0])*Count)!=sizeof(ApertureDim[0])*Count){
		return false;
	}

	return true;
}
void	GUICmdReqSetApertureList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		if(Base!=NULL){
			Base->TransmitDirectly(this);
		}
	}
	SendAck(localPage);
}

//===========================================================================================================

/*
GUICmdSendGerberBuffer::GUICmdSendGerberBuffer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,LoadedData(Base)
{
}

bool	GUICmdSendGerberBuffer::SetupLoading(void)
{
	for(int i=0;i<LoadedData.FileListToLoad.count() && i<MaxGerberLayer;i++){
		QFile	f(LoadedData.FileListToLoad[i]);
		if(f.open(QIODevice::ReadOnly)==false)
			return false;
		Buff[i]=f.readAll();
	}
	return true;
}
bool	GUICmdSendGerberBuffer::CreateTmpFiles(QStringList &FileNames)
{
	int	N=LoadedData.FileListToLoad.count();
	for(int i=0;i<N;i++){
		QString Str=QDir::homePath()+QString("/TmpGerber")+QString::number(i)+QString(".gbr");
		FileNames.append(Str);
		QFile	f(Str);
		if(f.open(QIODevice::WriteOnly)==false)
			return false;
		f.write(Buff[i]);
	}
	return false;
}

bool	GUICmdSendGerberBuffer::Save(QIODevice *f)
{
	if(LoadedData.Save(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,Buff[i])==false)
		return false;
	}
	return true;
}
bool	GUICmdSendGerberBuffer::Load(QIODevice *f)
{
	if(LoadedData.Load(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,Buff[i])==false)
		return false;
	}
	return true;
}


void	GUICmdSendGerberBuffer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase("Basic" ,"GerberFast");
	LoadGerberFromCmdList	Cmd(this);
	Cmd.LocalPage=localPage;
	*((GerberFromFilesList *)&Cmd)=*((GerberFromFilesList *)&LoadedData);
	Cmd.FileListToLoad.clear();
	CreateTmpFiles(Cmd.FileListToLoad);
	Base->TransmitDirectly(&Cmd);
	for(int i=0;i<Cmd.FileListToLoad.count();i++){
		char	FileNameStr[1024];
		::QString2Char(Cmd.FileListToLoad[i],FileNameStr,sizeof(FileNameStr));
		remove(FileNameStr);
	}
	SendAck(localPage);
}
*/
//==========================================================================================

/*
GUICmdReqGerberGetPickInfo::GUICmdReqGerberGetPickInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqGerberGetPickInfo::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;
	return true;
}
bool	GUICmdReqGerberGetPickInfo::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;
	return true;
}

void	GUICmdReqGerberGetPickInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendGerberGetPickInfo	*SendBack=GetSendBack(GUICmdSendGerberGetPickInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase("Basic" ,"GerberFast");
	MsgGerberGetPickInfo	Cmd(this);
	Cmd.GlobalX=GlobalX;
	Cmd.GlobalY=GlobalY;
	Base->TransmitDirectly(&Cmd);

	SendBack->PDataNumb=Cmd.PDataNumb;
	SendBack->PData=new GUI_AXGR_PICKDATA[Cmd.PDataNumb];
	for(int i=0;i<Cmd.PDataNumb;i++){
		SendBack->PData[i].x	=Cmd.PData[i].x;
		SendBack->PData[i].y	=Cmd.PData[i].y;
		SendBack->PData[i].no	=Cmd.PData[i].no;
		SendBack->PData[i].kind	=Cmd.PData[i].kind;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendGerberGetPickInfo::GUICmdSendGerberGetPickInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	PData=NULL;
}
GUICmdSendGerberGetPickInfo::~GUICmdSendGerberGetPickInfo(void)
{
	if(PData!=NULL){
		delete	[]PData;
	}
}

bool	GUICmdSendGerberGetPickInfo::Save(QIODevice *f)
{
	if(::Save(f,PDataNumb)==false)
		return false;
	f->write((const char *)PData,sizeof(PData[0])*PDataNumb);
	return true;
}
bool	GUICmdSendGerberGetPickInfo::Load(QIODevice *f)
{
	if(::Load(f,PDataNumb)==false)
		return false;
	if(PData!=NULL){
		delete	[]PData;
	}
	PData=new GUI_AXGR_PICKDATA[PDataNumb];
	f->read((char *)PData,sizeof(PData[0])*PDataNumb);
	return true;
}
*/

/*
//==========================================================================================
GUICmdMsgGerberCopy::GUICmdMsgGerberCopy(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMsgGerberCopy::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		MsgGerberCopy	Cmd(this);
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase("Basic" ,"GerberFast");
		Base->TransmitDirectly(&Cmd);
	}
}
//==========================================================================================
GUICmdMsgGerberCut::GUICmdMsgGerberCut(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMsgGerberCut::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		MsgGerberCut	Cmd(this);
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase("Basic" ,"GerberFast");
		Base->TransmitDirectly(&Cmd);
	}
}
*/
//==========================================================================================
GUICmdGerberExec3PointAlignment::GUICmdGerberExec3PointAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberExec3PointAlignment::Save(QIODevice *f)
{
	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Save(f)==false)
			return false;
		if(CadPoint[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	GUICmdGerberExec3PointAlignment::Load(QIODevice *f)
{
	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}
	return true;
}

void	GUICmdGerberExec3PointAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//if(localPage==0){
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
		CmdGerberExec3PointAlignment	Cmd(this);
		for(int i=0;i<MaxGerberPointNumb;i++){
			Cmd.ImagePoint[i]	=ImagePoint[i];
			Cmd.CadPoint[i]		=CadPoint[i];
		}		
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	//}
}
//==========================================================================================
GUICmdGerberExecAddAlignmentPoint::GUICmdGerberExecAddAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberExecAddAlignmentPoint::Save(QIODevice *f)
{
	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Save(f)==false)
			return false;
		if(CadPoint[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	GUICmdGerberExecAddAlignmentPoint::Load(QIODevice *f)
{
	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}
	return true;
}

void	GUICmdGerberExecAddAlignmentPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		CmdGerberExecAddAlignmentPoint	Cmd(this);
		for(int i=0;i<MaxGerberPointNumb;i++){
			Cmd.ImagePoint[i]	=ImagePoint[i];
			Cmd.CadPoint[i]		=CadPoint[i];
		}		
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		Base->TransmitDirectly(&Cmd);
	}
}
//==========================================================================================
GUICmdReqGerberCenterize::GUICmdReqGerberCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqGerberCenterize::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(XYArea.Write(f)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}
bool	GUICmdReqGerberCenterize::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(XYArea.Read(f)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqGerberCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MsgGerberCenterize	Cmd(this);
	Cmd.Area	=Area;
	Cmd.XYArea	=XYArea;
	Cmd.Layer	=Layer;
	Cmd.GlobalPage=localPage;	//‚±‚ê‚ÍOK
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	Base->GetPageData(localPage)->TransmitDirectly(&Cmd);

	GUICmdSendGerberCenterize	*SendBack=GetSendBack(GUICmdSendGerberCenterize,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->x=Cmd.x;
	SendBack->y=Cmd.y;
	SendBack->Ret=Cmd.Ret;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendGerberCenterize::GUICmdSendGerberCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendGerberCenterize::Save(QIODevice *f)
{
	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;
	if(::Save(f,Ret)==false)
		return false;
	return true;
}
bool	GUICmdSendGerberCenterize::Load(QIODevice *f)
{
	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	if(::Load(f,Ret)==false)
		return false;
	return true;
}

void	GUICmdSendGerberCenterize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"GerberFastImagePanel" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(this);
	}
}

//==========================================================================================
GUICmdSendAMImagePointXY::GUICmdSendAMImagePointXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAMImagePointXY::Save(QIODevice *f)
{
	if(::Save(f,Turn)==false)
		return false;
	if(::Save(f,GPx)==false)
		return false;
	if(::Save(f,GPy)==false)
		return false;
	return true;
}
bool	GUICmdSendAMImagePointXY::Load(QIODevice *f)
{
	if(::Load(f,Turn)==false)
		return false;
	if(::Load(f,GPx)==false)
		return false;
	if(::Load(f,GPy)==false)
		return false;
	return true;
}

void	GUICmdSendAMImagePointXY::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"GerberFastImagePanel" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(this);
	}
}

//==========================================================================================

GUICmdGerberReqPointFromArea::GUICmdGerberReqPointFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberReqPointFromArea::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGerberReqPointFromArea::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGerberReqPointFromArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(AlignBase==NULL)
		return;
	GetCenterPacket		DPacket(this);
	DPacket.Area		=Area;
	DPacket.Layer		=Layer;
	DPacket.Page		=localPage;

	AlignBase->GetPageData(localPage)->TransmitDirectly(&DPacket);

	GUICmdGerberSendPointFromArea	*SendBack=GetSendBack(GUICmdGerberSendPointFromArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->LocalX=DPacket.LocalX;
	SendBack->LocalY=DPacket.LocalY;
	SendBack->DifBrightness=DPacket.DifBrightness;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdGerberSendPointFromArea::GUICmdGerberSendPointFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberSendPointFromArea::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdGerberSendPointFromArea::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdGerberSendPointFromArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//===================================================================================
GUICmdGerberSendShowingLayerInfo::GUICmdGerberSendShowingLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberSendShowingLayerInfo::Load(QIODevice *f)
{
	if(ButtonsToShowLayer.Load(f)==false)
		return false;
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	if(LayerTypes.Load(f)==false)
		return false;
	if(ButtonsToShowComposite.Load(f)==false)
		return false;
	if(OperateCompositeIDList.Load(f)==false)
		return false;
	if(CompositeIDList.Load(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,LayerColor[i])==false)
			return false;
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,CompositeLayerColor[i])==false)
			return false;
	}
	if(CompositeLayer.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGerberSendShowingLayerInfo::Save(QIODevice *f)
{
	if(ButtonsToShowLayer.Save(f)==false)
		return false;
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(LayerTypes.Save(f)==false)
		return false;
	if(ButtonsToShowComposite.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	if(CompositeIDList.Save(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,LayerColor[i])==false)
			return false;
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,CompositeLayerColor[i])==false)
			return false;
	}
	if(CompositeLayer.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGerberSendShowingLayerInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		QString	AlgoRoot=/**/"Basic";
		QString	AlgoName=/**/"GerberFast";
		GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(Base!=NULL){
			Base->TransmitDirectly(this);
		}
	}
}

//===================================================================================
GUICmdSendGerberCompositeDefPack::GUICmdSendGerberCompositeDefPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendGerberCompositeDefPack::Load(QIODevice *f)
{
	if(CompData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendGerberCompositeDefPack::Save(QIODevice *f)
{
	if(CompData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendGerberCompositeDefPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	if(localPage==0){
		QString	AlgoRoot=/**/"Basic";
		QString	AlgoName=/**/"GerberFast";
		GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(Base!=NULL){
			/*
			CmdSetGerberCompositeDefPack	Cmd(this);
			Cmd.CompData=CompData;
			Base->TransmitDirectly(&Cmd);
			*/
		}
	}
}

//===================================================================================
GUICmdSendLayerTypeList::GUICmdSendLayerTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendLayerTypeList::Save(QIODevice *f)
{
	if(::Save(f,LayerTypeList)==false)
		return false;
	return true;
}
bool	GUICmdSendLayerTypeList::Load(QIODevice *f)
{
	if(::Load(f,LayerTypeList)==false)
		return false;
	return true;
}

void	GUICmdSendLayerTypeList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		QString	AlgoRoot=/**/"Basic";
		QString	AlgoName=/**/"GerberFast";
		GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
		if(Base!=NULL){
			Base->TransmitDirectly(this);
		}
	}
}

//===================================================================================

GUICmdSendAddLayer::GUICmdSendAddLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddLayer::Save(QIODevice *f)
{
	if(::Save(f,LayerName)==false)
		return false;
	return true;
}
bool	GUICmdSendAddLayer::Load(QIODevice *f)
{
	if(::Load(f,LayerName)==false)
		return false;
	return true;
}
void	GUICmdSendAddLayer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamComm()->Mastered==false){
		GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
		if(DProp!=NULL){
			DProp->TransmitDirectly(this);
		}
	}
}

//===================================================================================

GUICmdMakeImage::GUICmdMakeImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MIMode=_MIM_Standard;
}
bool	GUICmdMakeImage::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	MIMode=(MakeImageMode)d;

	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	if(OperateCompositeIDList.Load(f)==false)
		return false;

	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,LayerColor[i])==false)
			return false;
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,CompositeLayerColor[i])==false)
			return false;
	}
	return true;
}
bool	GUICmdMakeImage::Save(QIODevice *f)
{
	BYTE	d=(BYTE)MIMode;
	if(::Save(f,d)==false)
		return false;

	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,LayerColor[i])==false)
			return false;
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,CompositeLayerColor[i])==false)
			return false;
	}
	return true;
}

void	GUICmdMakeImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(this);
	}
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
	if(OperateCompositeIDList.Load(f)==false)
		return false;

	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,LayerColor[i])==false)
			return false;
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Load(f,CompositeLayerColor[i])==false)
			return false;
	}
	return true;
}
bool	GUICmdMakeBitImage::Save(QIODevice *f)
{
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	if(OperateCompositeIDList.Save(f)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,LayerColor[i])==false)
			return false;
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(::Save(f,CompositeLayerColor[i])==false)
			return false;
	}
	return true;
}

void	GUICmdMakeBitImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(this);
	}
}
//===================================================================================
GUICmdMakeAlgo::GUICmdMakeAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMakeAlgo::Load(QIODevice *f)
{
	if(MakeAlgoAllList.Load(f)==false)
		return false;
	if(::Load(f,ExecutedLine)==false)
		return false;
	return true;
}
bool	GUICmdMakeAlgo::Save(QIODevice *f)
{
	if(MakeAlgoAllList.Save(f)==false)
		return false;
	if(::Save(f,ExecutedLine)==false)
		return false;
	return true;
}

void	GUICmdMakeAlgo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
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

void	GUICmdReqSaveConstruct::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GUICmdAckSaveConstruct	*SendBack=GetSendBack(GUICmdAckSaveConstruct,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	MsgSaveConstruct	Cmd(GetLayersBase());
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
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
	if(::Load(f,Data)==false)
		return false;
	return true;
}

bool	GUICmdReqLoadConstruct::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdReqLoadConstruct::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	if(PBase==NULL)
		return;
	MsgLoadConstruct	Cmd(GetLayersBase());
	Cmd.Data=Data;
	GerberFastInPage	*PPage=dynamic_cast<GerberFastInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		PPage->TransmitDirectly(&Cmd);
	}
}


//==========================================================================================

GUICmdReqGerberInfo::GUICmdReqGerberInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqGerberInfo::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;
	if(DrawingLayers.Save(f)==false)
		return false;
	return true;
}

bool	GUICmdReqGerberInfo::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;
	if(DrawingLayers.Load(f)==false)
		return false;
	return true;
}

void	GUICmdReqGerberInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckGerberInfo	*SendBack=GetSendBack(GUICmdAckGerberInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	CmdReqGerberInfo	Cmd(GetLayersBase());
	Cmd.GlobalX	=GlobalX;
	Cmd.GlobalY	=GlobalY;
	Cmd.DrawingLayers	=DrawingLayers;
	Base->GetPageData(localPage)->TransmitDirectly(&Cmd);
	SendBack->GInfo	= Cmd.Answer;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckGerberInfo::GUICmdAckGerberInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckGerberInfo::Save(QIODevice *f)
{
	if(GInfo.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdAckGerberInfo::Load(QIODevice *f)
{
	if(GInfo.Load(f)==false)
		return false;
	return true;
}
