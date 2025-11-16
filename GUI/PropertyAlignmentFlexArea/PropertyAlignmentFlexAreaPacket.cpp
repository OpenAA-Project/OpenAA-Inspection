
#include "XAlignmentFlexArea.h"
#include "XDataInLayerCommander.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XPropertyAlignmentFlexAreaCommon.h"

//=====================================================================================

bool	AlignmentFlexAreaAreaList::Load(QIODevice *f)
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
	if(LimitedLib.Load(f)==false)
		return false;
	if(LibToCreateItems.Load(f)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Priority=(XAlignmentFlexAreaArea::_EnumPriority)d;

	return true;
}
bool	AlignmentFlexAreaAreaList::Save(QIODevice *f)
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
	if(LimitedLib.Save(f)==false)
		return false;
	if(LibToCreateItems.Save(f)==false)
		return false;
	BYTE	d=(BYTE)Priority;
	if(::Save(f,d)==false)
		return false;

	return true;
}

AlignmentFlexAreaAreaList	&AlignmentFlexAreaAreaList::operator=(AlignmentFlexAreaAreaList &src)
{
	Number			=src.Number;
	AreaID			=src.AreaID;
	LibID			=src.LibID;
	AreaName		=src.AreaName;
	GlobalPage		=src.GlobalPage;
	XSize			=src.XSize;
	YSize			=src.YSize;
	LimitedLib		=src.LimitedLib;
	LibToCreateItems=src.LibToCreateItems;
	Priority		=src.Priority;
	return *this;
}

bool	AlignmentFlexAreaAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentFlexAreaAreaList *p=new AlignmentFlexAreaAreaList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentFlexAreaAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentFlexAreaAreaList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentFlexAreaAreaListPack	&AlignmentFlexAreaAreaListPack::operator=(AlignmentFlexAreaAreaListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentFlexAreaAreaListPack	&AlignmentFlexAreaAreaListPack::operator+=(AlignmentFlexAreaAreaListPack &src)
{
	for(AlignmentFlexAreaAreaList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaAreaList *q=new AlignmentFlexAreaAreaList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}

//=====================================================================================

bool	AlignmentWholeMatchList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Division)==false)
		return false;

	return true;
}
bool	AlignmentWholeMatchList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Division)==false)
		return false;

	return true;
}

AlignmentWholeMatchList	&AlignmentWholeMatchList::operator=(AlignmentWholeMatchList &src)
{
	ID			=src.ID;
	GlobalPage	=src.GlobalPage;
	Division	=src.Division;

	return *this;
}

bool	AlignmentWholeMatchListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentWholeMatchList *p=new AlignmentWholeMatchList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentWholeMatchListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentWholeMatchList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentWholeMatchListPack	&AlignmentWholeMatchListPack::operator=(AlignmentWholeMatchListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentWholeMatchListPack	&AlignmentWholeMatchListPack::operator+=(AlignmentWholeMatchListPack &src)
{
	for(AlignmentWholeMatchList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentWholeMatchList *q=new AlignmentWholeMatchList();
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

GUICmdReqAlignmentFlexAreaPutArea::GUICmdReqAlignmentFlexAreaPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	GlobalPage	=-1;
	Priority	=XAlignmentFlexAreaArea::_PriorityMiddle;
}

bool	GUICmdReqAlignmentFlexAreaPutArea::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Priority=(XAlignmentFlexAreaArea::_EnumPriority)d;

	if(LimitedLib.Load(f)==false)
		return false;
	if(LibToCreateItems.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentFlexAreaPutArea::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	BYTE	d=(BYTE)Priority;
	if(::Save(f,d)==false)
		return false;

	if(LimitedLib.Save(f)==false)
		return false;
	if(LibToCreateItems.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentFlexAreaPutArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		AddAlignmentFlexAreaAreaPacket	RCmd(GetLayersBase());
		RCmd.Area			=Area	;
		RCmd.AreaName		=AreaName;
		RCmd.Priority		=Priority;
		RCmd.LimitedLib		=LimitedLib;
		RCmd.LibToCreateItems=LibToCreateItems;
		PData->TransmitDirectly(&RCmd);
	}
}

//==============================================================================================

GUICmdReqModifyAlignmentFlexAreaAreaInfo::GUICmdReqModifyAlignmentFlexAreaAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID		=-1;
	Priority	=XAlignmentFlexAreaArea::_PriorityMiddle;
}

bool	GUICmdReqModifyAlignmentFlexAreaAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Priority=(XAlignmentFlexAreaArea::_EnumPriority)d;

	if(LimitedLib.Load(f)==false)
		return false;
	if(LibToCreateItems.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqModifyAlignmentFlexAreaAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	BYTE	d=(BYTE)Priority;
	if(::Save(f,d)==false)
		return false;

	if(LimitedLib.Save(f)==false)
		return false;
	if(LibToCreateItems.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqModifyAlignmentFlexAreaAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		ModifyAlignmentFlexAreaAreaPacket	RCmd(GetLayersBase());
		RCmd.AreaID				=AreaID;
		RCmd.Area				=Area	;
		RCmd.AreaName			=AreaName;
		RCmd.Priority			=Priority;
		RCmd.LimitedLib			=LimitedLib;
		RCmd.LibToCreateItems	=LibToCreateItems;
		PData->TransmitDirectly(&RCmd);
	}
}
//==============================================================================================

GUICmdReqAlignmentFlexAreaAreaList::GUICmdReqAlignmentFlexAreaAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentFlexAreaAreaList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqAlignmentFlexAreaAreaList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqAlignmentFlexAreaAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentFlexAreaAreaList	*SendBack=GetSendBack(GUICmdSendAlignmentFlexAreaAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaList(localPage ,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentFlexAreaAreaList::GUICmdSendAlignmentFlexAreaAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentFlexAreaAreaList::MakeAreaList(int localPage,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	Area.RemoveAll();
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		AlignmentFlexAreaInPage	*Ap=dynamic_cast<AlignmentFlexAreaInPage *>(PData);
		if(Ap!=NULL){
			int	N=0;
			for(XAlignmentFlexAreaArea *a=Ap->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
				AlignmentFlexAreaAreaList	*L=new AlignmentFlexAreaAreaList();
				L->Number			=N;
				L->AreaID			=a->AreaID;
				L->AreaName			=a->AreaName;
				L->GlobalPage		=PBase->GetGlobalPageFromLocal(localPage);
				L->XSize			=a->Area.GetWidth();
				L->YSize			=a->Area.GetHeight();
				L->LimitedLib		=a->LimitedLib;
				L->LibToCreateItems	=a->LibToCreateItems;
				L->Priority			=a->Priority;
				Area.AppendList(L);
			}
		}
	}
}
bool	GUICmdSendAlignmentFlexAreaAreaList::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentFlexAreaAreaList::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentFlexAreaAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================================

GUICmdReqWholeMatchList::GUICmdReqWholeMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqWholeMatchList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqWholeMatchList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqWholeMatchList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendWholeMatchList	*SendBack=GetSendBack(GUICmdSendWholeMatchList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeWholeMatchList(localPage ,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendWholeMatchList::GUICmdSendWholeMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendWholeMatchList::MakeWholeMatchList(int localPage,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	WholeMatchInfo.RemoveAll();
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		AlignmentFlexAreaInPage	*Ap=dynamic_cast<AlignmentFlexAreaInPage *>(PData);
		if(Ap!=NULL){
			for(int	N=0;N<Ap->WholeMatchData.SImageNumb;N++){
				AlignmentWholeMatchList	*L=new AlignmentWholeMatchList();
				L->ID			=N;
				L->GlobalPage		=PBase->GetGlobalPageFromLocal(localPage);
				L->Division			=Ap->WholeMatchData.SImageInfo[N]->Division;
				WholeMatchInfo.AppendList(L);
			}
		}
	}
}
bool	GUICmdSendWholeMatchList::Load(QIODevice *f)
{
	if(WholeMatchInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendWholeMatchList::Save(QIODevice *f)
{
	if(WholeMatchInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendWholeMatchList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================================

GUICmdSendAddManualAlignmentFlexArea::GUICmdSendAddManualAlignmentFlexArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID	=-1;
	LibID	=-1;
}
bool	GUICmdSendAddManualAlignmentFlexArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualAlignmentFlexArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualAlignmentFlexArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddAlignmentFlexAreaPointPacket	DPacket(this);
	DPacket.Area				=Area;
	DPacket.AreaID				=AreaID;
	DPacket.LibID				=LibID;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdPickupTestList::GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdPickupTestList::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}
void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqTestByLibID	DPacket(this);
	DPacket.AreaID		=AreaID;
	DPacket.LibList		=LibList;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdGenerateAlignmentFlexAreas::GUICmdGenerateAlignmentFlexAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdGenerateAlignmentFlexAreas::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdGenerateAlignmentFlexAreas::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}
void	GUICmdGenerateAlignmentFlexAreas::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqGenerateByLibID	DPacket(this);
	DPacket.AreaID		=AreaID;
	DPacket.LibList		=LibList;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================================

GUICmdGenerateAlignmentFlexAreaFromMask::GUICmdGenerateAlignmentFlexAreaFromMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdGenerateAlignmentFlexAreaFromMask::Load(QIODevice *f)
{
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,ItemLibID)==false)
		return false;
	return true;
}
bool	GUICmdGenerateAlignmentFlexAreaFromMask::Save(QIODevice *f)
{
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,ItemLibID)==false)
		return false;
	return true;
}
void	GUICmdGenerateAlignmentFlexAreaFromMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqGenerateAreaWithItemLibFromMask	DPacket(this);
	DPacket.Priority	=Priority;
	DPacket.ItemLibID	=ItemLibID;

	AP->TransmitDirectly(&DPacket);
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
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	RemoveAlignmentFlexAreaAreaPacket	DPacket(this);
	DPacket.AreaID	=AreaID;

	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}
//==============================================================================================

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqClearTestMap	DPacket(this);
	AP->TransmitDirectly(&DPacket);
}

//==============================================================================================

GUICmdReqAlignmentFlexAreaPointList::GUICmdReqAlignmentFlexAreaPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID=-1;
}
bool	GUICmdReqAlignmentFlexAreaPointList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentFlexAreaPointList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentFlexAreaPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	GUICmdSendAlignmentFlexAreaPointList	*SendBack=GetSendBack(GUICmdSendAlignmentFlexAreaPointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqAlignmentFlexAreaInfoListPack	RCmd(GetLayersBase());
	RCmd.AreaID=AreaID;
	AP->TransmitDirectly(&RCmd);
	SendBack->Points=RCmd.Points;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentFlexAreaPointList::GUICmdSendAlignmentFlexAreaPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAlignmentFlexAreaPointList::Load(QIODevice *f)
{
	if(Points.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentFlexAreaPointList::Save(QIODevice *f)
{
	if(Points.Save(f)==false)
		return false;
	return true;
}


//==============================================================================================

GUICmdReqAlignmentFlexAreaSetMode::GUICmdReqAlignmentFlexAreaSetMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeFlexAreaArea	=false;
	ModeWholeMatch		=false;
	ModeOutline			=false;
}
bool	GUICmdReqAlignmentFlexAreaSetMode::Load(QIODevice *f)
{
	if(::Load(f,ModeFlexAreaArea)==false)
		return false;
	if(::Load(f,ModeWholeMatch)==false)
		return false;
	if(::Load(f,ModeOutline)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentFlexAreaSetMode::Save(QIODevice *f)
{
	if(::Save(f,ModeFlexAreaArea)==false)
		return false;
	if(::Save(f,ModeWholeMatch)==false)
		return false;
	if(::Save(f,ModeOutline)==false)
		return false;
	return true;
}
void	GUICmdReqAlignmentFlexAreaSetMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" ,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(this);
	}
}

//==============================================================================================

GUICmdReqAlignmentFlexAreaSetCurrentArea::GUICmdReqAlignmentFlexAreaSetCurrentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID		=-1;
	GlobalPage	=-1;
}
bool	GUICmdReqAlignmentFlexAreaSetCurrentArea::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentFlexAreaSetCurrentArea::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	return true;
}
void	GUICmdReqAlignmentFlexAreaSetCurrentArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" ,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(this);
	}
}

//==============================================================================================

GUICmdReqAlignmentFlexAreaItemPack::GUICmdReqAlignmentFlexAreaItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibID	=-1;
	AreaID	=-1;
}
bool	GUICmdReqAlignmentFlexAreaItemPack::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentFlexAreaItemPack::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentFlexAreaItemPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentFlexAreaItemPack	*SendBack=GetSendBack(GUICmdAckAlignmentFlexAreaItemPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqAlignmentFlexAreaItemtPack	RCmd(GetLayersBase());
	RCmd.AreaID	=AreaID;
	RCmd.LibID	=LibID;
	RCmd.Items	=&SendBack->Items;
	AP->TransmitDirectly(&RCmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentFlexAreaItemPack::GUICmdAckAlignmentFlexAreaItemPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAlignmentFlexAreaItemPack::Load(QIODevice *f)
{
	if(Items.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentFlexAreaItemPack::Save(QIODevice *f)
{
	if(Items.Save(f)==false)
		return false;
	return true;
}

//=============================================================================================

GUICmdChangeAlignmentFlexAreaThreshold::GUICmdChangeAlignmentFlexAreaThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibID=-1;
}

bool	GUICmdChangeAlignmentFlexAreaThreshold::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,InfosData)==false)
		return false;
	return true;
}	
bool	GUICmdChangeAlignmentFlexAreaThreshold::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,InfosData)==false)
		return false;
	return true;
}
	
void	GUICmdChangeAlignmentFlexAreaThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
	if(BBase!=NULL){
		ChangeAlignmentFlexAreaThresholdCommon	Cmd(GetLayersBase());
		Cmd.LibID	=LibID;
		Cmd.InfosData			=InfosData;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//=============================================================================================

GUICmdReqRemoveAllOriginal::GUICmdReqRemoveAllOriginal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdReqRemoveAllOriginal::Load(QIODevice *f)
{
	if(::Load(f,GeneratedOrigin)==false)
		return false;
	return true;
}
	
bool	GUICmdReqRemoveAllOriginal::Save(QIODevice *f)
{
	if(::Save(f,GeneratedOrigin)==false)
		return false;
	return true;
}

	
void	GUICmdReqRemoveAllOriginal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
	if(BBase!=NULL){
		CmdRemoveAllOriginalAlignmentFlexAreaItems	Cmd(GetLayersBase());
		Cmd.GeneratedOrigin			=GeneratedOrigin;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================
GUICmdGenerateBaseMatch::GUICmdGenerateBaseMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdGenerateBaseMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	CmdGenerateBaseMatch	RCmd(GetLayersBase());
	AlignBase->TransmitDirectly(&RCmd);
}
//=============================================================================================

GUICmdExecBaseMatch::GUICmdExecBaseMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdExecBaseMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	CmdExecBaseMatch	RCmd(GetLayersBase());
	AlignBase->TransmitDirectly(&RCmd);
}
//=============================================================================================

GUICmdReqBaseMatchList::GUICmdReqBaseMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
void	GUICmdReqBaseMatchList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBaseMatchList	*SendBack=GetSendBack(GUICmdAckBaseMatchList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	CmdReqBaseMatchList	RCmd(GetLayersBase());
	RCmd.ListPoint	=&SendBack->ListData;
	AlignBase->TransmitDirectly(&RCmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBaseMatchList::GUICmdAckBaseMatchList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckBaseMatchList::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckBaseMatchList::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)
		return false;
	return true;
}

//=============================================================================================

GUICmdCreateAreaInMaskingArea::GUICmdCreateAreaInMaskingArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Priority=XAlignmentFlexAreaArea::_PriorityMiddle;
}

bool	GUICmdCreateAreaInMaskingArea::Load(QIODevice *f)
{
	if(::Load(f,Priority)==false)
		return false;
	return true;
}
bool	GUICmdCreateAreaInMaskingArea::Save(QIODevice *f)
{
	if(::Save(f,Priority)==false)
		return false;
	return true;
}

void	GUICmdCreateAreaInMaskingArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdCreateAreaInMaskingArea	RCmd(GetLayersBase());
	RCmd.Priority=Priority;
	AP->TransmitDirectly(&RCmd);
}
//=============================================================================================

GUICmdReqAlignmentPointList::GUICmdReqAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqAlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}	
void	GUICmdReqAlignmentPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentPointList	*SendBack=GetSendBack(GUICmdAckAlignmentPointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	CmdReqAlignmentPointList	RCmd(GetLayersBase());
	RCmd.AreaID=AreaID;
	RCmd.PointList	=&SendBack->PointList;
	AlignBase->GetPageData(localPage)->TransmitDirectly(&RCmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentPointList::GUICmdAckAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlignmentPointList::Load(QIODevice *f)
{
	if(PointList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentPointList::Save(QIODevice *f)
{
	if(PointList.Save(f)==false)
		return false;
	return true;
}
