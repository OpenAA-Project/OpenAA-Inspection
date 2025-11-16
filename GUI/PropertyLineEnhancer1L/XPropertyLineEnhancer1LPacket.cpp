#include "PropertyLineEnhancer1LForm.h"
#include "XLineEnhancer1L.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPropertyLineEnhancer1LPacket.h"
#include "EditLibrary.h"
#include "XGeneralFunc.h"

//=============================================================================================================
GUICmdCreateLineEnhancer1L::GUICmdCreateLineEnhancer1L(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCreateLineEnhancer1L::Load(QIODevice *f)
{
	if(SelectedLibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdCreateLineEnhancer1L::Save(QIODevice *f)
{
	if(SelectedLibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}
void	GUICmdCreateLineEnhancer1L::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LineEnhancer1LBase *PBase=(LineEnhancer1LBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
	if(PBase!=NULL){
		CmdCreateLineEnhancer1LPacket	Cmd(this);
		Cmd.SelectedLibList	=SelectedLibList;
		Cmd.LocalPage		=localPage;
		Cmd.LayerList		=LayerList;
		PBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================================

GUICmdPickupTestList::GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibPoint=NULL;
	CreatedInside=false;
}

GUICmdPickupTestList::~GUICmdPickupTestList(void)
{
	if(CreatedInside==true)
		delete	LibPoint;
	LibPoint=NULL;
}


bool	GUICmdPickupTestList::Load(QIODevice *f)
{
	if(LibPoint==NULL){
		CreatedInside=true;
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
		if(Ab!=NULL){
			CmdCreateTempLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
			Ab->TransmitDirectly(&Packet);
			LibPoint=Packet.Point;
		}
	}
	if(LibPoint==NULL)
		return false;
	int32	LibID;
	if(::Load(f,LibID)==false)
		return false;
	LibPoint->SetLibID(LibID);
	if(LibPoint->LoadBlob(f)==false)
		return false;

	if(LayerList.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(LibPoint==NULL)
		return false;
	int32	LibID=LibPoint->GetLibID();
	if(::Save(f,LibID)==false)
		return false;
	if(LibPoint->SaveBlob(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;

	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestLineEnhancer1LPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}

//=============================================================================================================

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestLineEnhancePacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//=============================================================================================================

GUICmdSetDrawing::GUICmdSetDrawing(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetDrawing::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	DrawingArea=(LineEnhancer1LDrawAttr::_DrawingArea)N;
	if(::Load(f,InstName)==false)
		return false;
	return true;
}
bool	GUICmdSetDrawing::Save(QIODevice *f)
{
	int	N=(int)DrawingArea;
	if(::Save(f,N)==false)
		return false;
	if(::Save(f,InstName)==false)
		return false;
	return true;
}

void	GUICmdSetDrawing::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSetLineEnhancer1LDrawMode	DrawMode(this);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLineEnhancer1L" ,InstName);
	if(GProp!=NULL){
		DrawMode.DrawingArea	=DrawingArea;
		GProp->TransmitDirectly(&DrawMode);
	}

}


GUICmdReqAreaHistgramInMaster::GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAreaHistgramInMaster::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqAreaHistgramInMaster::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqAreaHistgramInMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaHistgramInMaster	*SendBack=GetSendBack(GUICmdSendAreaHistgramInMaster,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeLists(Area,LayerList,localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=====================================================================================
BrightnessMapList::BrightnessMapList(void)
{
	memset(BrightList,0,sizeof(BrightList));
}

bool	BrightnessMapList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(f->write((const char *)BrightList,sizeof(BrightList))!=sizeof(BrightList))
		return false;
	return true;
}
bool	BrightnessMapList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(f->read((char *)BrightList,sizeof(BrightList))!=sizeof(BrightList))
		return false;
	return true;
}
//=====================================================================================

GUICmdSendAreaHistgramInMaster::GUICmdSendAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendAreaHistgramInMaster::MakeLists(FlexArea &area ,IntList &LayerList ,int localPage,LayersBase *Base)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		DataInLayer	*BLayer=Base->GetPageData(localPage)->GetLayerData(L->GetValue());
		BrightnessMapList	*BList=new BrightnessMapList();
		area.MakeBrightList(BList->BrightList,BLayer->GetDotPerLine(),BLayer->GetMaxLines(),BLayer->GetMasterBuff(),0 ,0);
		MapList.AppendList(BList);
	}
}
bool	GUICmdSendAreaHistgramInMaster::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	MapList.RemoveAll();
	for(int i=0;i<N;i++){
		BrightnessMapList *L=new BrightnessMapList();
		if(L->Load(f)==false)
			return false;
		MapList.AppendList(L);
	}
	return true;
}
bool	GUICmdSendAreaHistgramInMaster::Save(QIODevice *f)
{
	int32	N=MapList.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(BrightnessMapList *L=MapList.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendAreaHistgramInMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=====================================================================================
GUICmdSendAddManualLineEnhancer1L::GUICmdSendAddManualLineEnhancer1L(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualLineEnhancer1L::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualLineEnhancer1L::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualLineEnhancer1L::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	LineEnhancer1LBase *BBase=(LineEnhancer1LBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
	if(BBase!=NULL){
		CmdAddByteLineEnhancer1LItemPacket	Cmd(this);
		Cmd.LibID		=LibID;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
