
#include "XMatchShiftRotation.h"
#include "XDataInLayerCommander.h"
#include "XPropertyMatchShiftRotationPacket.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"

//=====================================================================================

bool	MatchShiftRotationAreaList::Load(QIODevice *f)
{
	if(::Load(f,Number)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,XSize)==false)
		return false;
	if(::Load(f,YSize)==false)
		return false;

	return true;
}
bool	MatchShiftRotationAreaList::Save(QIODevice *f)
{
	if(::Save(f,Number)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,XSize)==false)
		return false;
	if(::Save(f,YSize)==false)
		return false;

	return true;
}

MatchShiftRotationAreaList	&MatchShiftRotationAreaList::operator=(MatchShiftRotationAreaList &src)
{
	Number			=src.Number;
	AreaID			=src.AreaID;
	LibID			=src.LibID;
	AreaName		=src.AreaName;
	GlobalPage		=src.GlobalPage;
	XSize			=src.XSize;
	YSize			=src.YSize;

	return *this;
}

bool	MatchShiftRotationAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		MatchShiftRotationAreaList *p=new MatchShiftRotationAreaList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	MatchShiftRotationAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(MatchShiftRotationAreaList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

MatchShiftRotationAreaListPack	&MatchShiftRotationAreaListPack::operator=(MatchShiftRotationAreaListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
MatchShiftRotationAreaListPack	&MatchShiftRotationAreaListPack::operator+=(MatchShiftRotationAreaListPack &src)
{
	for(MatchShiftRotationAreaList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		MatchShiftRotationAreaList *q=new MatchShiftRotationAreaList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}

//=====================================================================================
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

//==============================================================================================

GUICmdReqMatchShiftRotationPutArea::GUICmdReqMatchShiftRotationPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	GlobalPage	=-1;
	LibID		=-1;
}

bool	GUICmdReqMatchShiftRotationPutArea::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;

	return true;
}
bool	GUICmdReqMatchShiftRotationPutArea::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;

	return true;
}

void	GUICmdReqMatchShiftRotationPutArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		AddMatchShiftRotationAreaPacket	RCmd(GetLayersBase());
		RCmd.Area			=Area	;
		RCmd.LibID			=LibID;
		RCmd.AreaName		=AreaName;
		PData->TransmitDirectly(&RCmd);
	}
}

//==============================================================================================

GUICmdReqModifyMatchShiftRotationAreaInfo::GUICmdReqModifyMatchShiftRotationAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID		=-1;
	LibID		=-1;
}

bool	GUICmdReqModifyMatchShiftRotationAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;

	return true;
}
bool	GUICmdReqModifyMatchShiftRotationAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;

	return true;
}

void	GUICmdReqModifyMatchShiftRotationAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		ModifyMatchShiftRotationAreaPacket	RCmd(GetLayersBase());
		RCmd.AreaID			=AreaID;
		RCmd.Area			=Area	;
		RCmd.AreaName		=AreaName;
		RCmd.LibID			=LibID;
		PData->TransmitDirectly(&RCmd);
	}
}
//==============================================================================================

GUICmdReqMatchShiftRotationAreaList::GUICmdReqMatchShiftRotationAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMatchShiftRotationAreaList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqMatchShiftRotationAreaList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqMatchShiftRotationAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendMatchShiftRotationAreaList	*SendBack=GetSendBack(GUICmdSendMatchShiftRotationAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaList(localPage ,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendMatchShiftRotationAreaList::GUICmdSendMatchShiftRotationAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendMatchShiftRotationAreaList::MakeAreaList(int localPage,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	Area.RemoveAll();
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		MatchShiftRotationInPage	*Ap=dynamic_cast<MatchShiftRotationInPage *>(PData);
		if(Ap!=NULL){
			int	N=0;
			for(XMatchShiftRotationArea *a=Ap->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
				MatchShiftRotationAreaList	*L=new MatchShiftRotationAreaList();
				L->Number			=N;
				L->AreaID			=a->AreaID;
				L->AreaName			=a->AreaName;
				L->GlobalPage		=PBase->GetGlobalPageFromLocal(localPage);
				L->XSize			=a->Area.GetWidth();
				L->YSize			=a->Area.GetHeight();
				Area.AppendList(L);
			}
		}
	}
}
bool	GUICmdSendMatchShiftRotationAreaList::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendMatchShiftRotationAreaList::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendMatchShiftRotationAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================================

GUICmdSendAddManualMatchShiftRotation::GUICmdSendAddManualMatchShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID	=-1;
	LibID	=-1;
}
bool	GUICmdSendAddManualMatchShiftRotation::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualMatchShiftRotation::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualMatchShiftRotation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddMatchShiftRotationPointPacket	DPacket(this);
	DPacket.Area				=Area;
	DPacket.AreaID				=AreaID;
	DPacket.LibID				=LibID;
	DPacket.ItemName			=ItemName;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdUpdateManualMatchShiftRotation::GUICmdUpdateManualMatchShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
	LibID	=-1;
}
bool	GUICmdUpdateManualMatchShiftRotation::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdUpdateManualMatchShiftRotation::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdUpdateManualMatchShiftRotation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	ModifyMatchShiftRotationPointPacket	DPacket(this);
	DPacket.ItemID		=ItemID;
	DPacket.LibID		=LibID;
	DPacket.ItemName	=ItemName;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdDeleteManualMatchShiftRotation::GUICmdDeleteManualMatchShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
}
bool	GUICmdDeleteManualMatchShiftRotation::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
bool	GUICmdDeleteManualMatchShiftRotation::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

void	GUICmdDeleteManualMatchShiftRotation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DeleteMatchShiftRotationPointPacket	DPacket(this);
	DPacket.ItemID		=ItemID;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdGenerateMatchShiftRotations::GUICmdGenerateMatchShiftRotations(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdGenerateMatchShiftRotations::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdGenerateMatchShiftRotations::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}
void	GUICmdGenerateMatchShiftRotations::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	//CmdReqGenerateByLibID	DPacket(this);
	//DPacket.AreaID		=AreaID;
	//DPacket.LibList		=LibList;

	//AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdGenerateMatchShiftRotationFromMask::GUICmdGenerateMatchShiftRotationFromMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdGenerateMatchShiftRotationFromMask::Load(QIODevice *f)
{
	if(::Load(f,ItemLibID)==false)
		return false;
	return true;
}
bool	GUICmdGenerateMatchShiftRotationFromMask::Save(QIODevice *f)
{
	if(::Save(f,ItemLibID)==false)
		return false;
	return true;
}
void	GUICmdGenerateMatchShiftRotationFromMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	//CmdReqGenerateAreaWithItemLibFromMask	DPacket(this);
	//DPacket.Priority	=Priority;
	//DPacket.ItemLibID	=ItemLibID;

	//AP->TransmitDirectly(&DPacket);
}
//==============================================================================================

GUICmdDeleteArea::GUICmdDeleteArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeleteArea::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdDeleteArea::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}
void	GUICmdDeleteArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	RemoveMatchShiftRotationAreaPacket	DPacket(this);
	DPacket.AreaID	=AreaID;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdReqMatchShiftRotationPointList::GUICmdReqMatchShiftRotationPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID=-1;
}
bool	GUICmdReqMatchShiftRotationPointList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqMatchShiftRotationPointList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqMatchShiftRotationPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	GUICmdSendMatchShiftRotationPointList	*SendBack=GetSendBack(GUICmdSendMatchShiftRotationPointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqMatchShiftRotationInfoListPack	RCmd(GetLayersBase());
	RCmd.AreaID=AreaID;
	AP->TransmitDirectly(&RCmd);
	SendBack->Points=RCmd.Points;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendMatchShiftRotationPointList::GUICmdSendMatchShiftRotationPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendMatchShiftRotationPointList::Load(QIODevice *f)
{
	if(Points.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendMatchShiftRotationPointList::Save(QIODevice *f)
{
	if(Points.Save(f)==false)
		return false;
	return true;
}


//==============================================================================================

GUICmdReqMatchShiftRotationSetMode::GUICmdReqMatchShiftRotationSetMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeFlexAreaArea	=false;
	ModeOutline			=false;
}
bool	GUICmdReqMatchShiftRotationSetMode::Load(QIODevice *f)
{
	if(::Load(f,ModeFlexAreaArea)==false)
		return false;
	if(::Load(f,ModeOutline)==false)
		return false;
	return true;
}
bool	GUICmdReqMatchShiftRotationSetMode::Save(QIODevice *f)
{
	if(::Save(f,ModeFlexAreaArea)==false)
		return false;
	if(::Save(f,ModeOutline)==false)
		return false;
	return true;
}
void	GUICmdReqMatchShiftRotationSetMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchShiftRotationForm" ,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(this);
	}
}

//==============================================================================================

GUICmdReqMatchShiftRotationSetCurrentArea::GUICmdReqMatchShiftRotationSetCurrentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID		=-1;
	GlobalPage	=-1;
}
bool	GUICmdReqMatchShiftRotationSetCurrentArea::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	return true;
}
bool	GUICmdReqMatchShiftRotationSetCurrentArea::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	return true;
}
void	GUICmdReqMatchShiftRotationSetCurrentArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchShiftRotationForm" ,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(this);
	}
}

//==============================================================================================

GUICmdReqMatchShiftRotationItemPack::GUICmdReqMatchShiftRotationItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID	=-1;
}
bool	GUICmdReqMatchShiftRotationItemPack::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqMatchShiftRotationItemPack::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqMatchShiftRotationItemPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMatchShiftRotationItemPack	*SendBack=GetSendBack(GUICmdAckMatchShiftRotationItemPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqMatchShiftRotationItemPack	RCmd(GetLayersBase());
	RCmd.AreaID	=AreaID;
	RCmd.Items	=&SendBack->Items;
	AP->TransmitDirectly(&RCmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMatchShiftRotationItemPack::GUICmdAckMatchShiftRotationItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckMatchShiftRotationItemPack::Load(QIODevice *f)
{
	if(Items.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckMatchShiftRotationItemPack::Save(QIODevice *f)
{
	if(Items.Save(f)==false)
		return false;
	return true;
}

//==============================================================================================

GUICmdReqMatchShiftItemImages::GUICmdReqMatchShiftItemImages(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID=-1;
	ItemID=-1;
}
bool	GUICmdReqMatchShiftItemImages::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqMatchShiftItemImages::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqMatchShiftItemImages::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	GUICmdSendMatchShiftItemImages	*SendBack=GetSendBack(GUICmdSendMatchShiftItemImages,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqMatchShiftRotationItemImages	RCmd(GetLayersBase());
	RCmd.AreaID=AreaID;
	RCmd.ItemID=ItemID;
	RCmd.Patterns=&SendBack->Patterns;
	AP->TransmitDirectly(&RCmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendMatchShiftItemImages::GUICmdSendMatchShiftItemImages(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendMatchShiftItemImages::Load(QIODevice *f)
{
	if(Patterns.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendMatchShiftItemImages::Save(QIODevice *f)
{
	if(Patterns.Save(f)==false)
		return false;
	return true;
}
//==============================================================================================