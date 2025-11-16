#include "BrightHistgramFormResource.h"
#include "PropertyAreaShaderForm.h"
#include "XAreaShader.h"
#include "XAreaShaderPacket.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPropertyAreaShaderPacket.h"
#include "EditLibrary.h"
#include "XGeneralFunc.h"

//=====================================================================================
GUICmdSendAddManualAreaShader::GUICmdSendAddManualAreaShader(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualAreaShader::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,CellSize)==false)
		return false;
	if(::Load(f,AdoptRate)==false)
		return false;
	if(::Load(f,Fixed)==false)
		return false;
	if(::Load(f,Average)==false)
		return false;
	if(::Load(f,Sigma)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualAreaShader::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,CellSize)==false)
		return false;
	if(::Save(f,AdoptRate)==false)
		return false;
	if(::Save(f,Fixed)==false)
		return false;
	if(::Save(f,Average)==false)
		return false;
	if(::Save(f,Sigma)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualAreaShader::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AreaShaderBase *BBase=(AreaShaderBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
	if(BBase!=NULL){
		CmdAddAreaShaderItemPacket	Cmd(this);
		Cmd.Area			=Area;
		Cmd.LayerList		=LayerList;
		Cmd.LocalPage		=localPage;
		Cmd.CellSize		=CellSize;
		Cmd.AdoptRate		=AdoptRate;
		Cmd.Fixed			=Fixed;
		Cmd.Average			=Average;
		Cmd.Sigma			=Sigma;		//•W€•Î·
		BBase->TransmitDirectly(&Cmd);
	}

	SendAck(localPage);
}

//======================================================================================================================


GUICmdReqAreaShaderList::GUICmdReqAreaShaderList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAreaShaderList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaShaderList	*SendBack=GetSendBack(GUICmdSendAreaShaderList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaShaderList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAreaShaderList::GUICmdSendAreaShaderList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAreaShaderList::MakeAreaShaderList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AreaShaderBase	*ABase=(AreaShaderBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
	if(ABase==NULL)
		return;
	AreaShaderInfo.RemoveAll();

	AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(ABase->GetPageData(localPage));
	if(PData!=NULL){
		for(int layer=0;layer<ABase->GetLayerNumb(localPage);layer++){
			AlgorithmInLayerRoot *PLayer=PData->GetLayerData(layer);
			AreaShaderInLayer *AreaShaderLayer=dynamic_cast<AreaShaderInLayer *>(PLayer);
			if(AreaShaderLayer!=NULL){
				for(AlgorithmItemPLI *item=AreaShaderLayer->GetFirstData();item!=NULL;item=item->GetNext()){
					AreaShaderItem	*MItem=dynamic_cast<AreaShaderItem *>(item);
					if(MItem!=NULL){
						AreaShaderListForPacket	*L=new AreaShaderListForPacket();
						L->Page=PBase->GetGlobalPageFromLocal(localPage);
						L->Layer=layer;
						int x1 ,y1 ,x2 ,y2;
						MItem->GetXY(x1 ,y1 ,x2 ,y2);
						L->ItemID=MItem->GetID();
						L->x1=x1;
						L->y1=y1;
						L->x2=x2;
						L->y2=y2;
						L->CellSize	=MItem->GetThresholdR()->CellSize;
						L->AdoptRate=MItem->GetThresholdR()->AdoptRate;	//Ì—p—¦
						L->Fixed	=MItem->GetThresholdR()->Fixed;
						L->Average	=MItem->GetThresholdR()->Average;
						L->Sigma	=MItem->GetThresholdR()->Sigma;		//•W€•Î·

						AreaShaderInfo.AppendList(L);
					}
				}
			}
		}
	}
}
bool	GUICmdSendAreaShaderList::Load(QIODevice *f)
{
	if(AreaShaderInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAreaShaderList::Save(QIODevice *f)
{
	if(AreaShaderInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAreaShaderList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//=============================================================================================================
GUICmdCreateAreaShader::GUICmdCreateAreaShader(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCreateAreaShader::Load(QIODevice *f)
{
	if(SelectedLibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdCreateAreaShader::Save(QIODevice *f)
{
	if(SelectedLibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}
void	GUICmdCreateAreaShader::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AreaShaderBase *PBase=(AreaShaderBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
	if(PBase!=NULL){
		CmdCreateAreaShaderPacket	Cmd(this);
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
		if(Ab!=NULL){
			CmdCreateTempAreaShaderLibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestAreaShaderPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
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
	CmdClearTestAreaShaderPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//=============================================================================================================

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