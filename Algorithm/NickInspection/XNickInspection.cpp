//#include "NickInspectionInspectionResource.h"
#include "XNickInspection.h"
#include "XGeneralFunc.h"

QString	AlgorithmLibraryListWithResult::GetLibName(LayersBase *base)
{
	if(base!=NULL){
		AlgorithmBase	*ABase=base->GetAlgorithmBase(LibType);
		if(ABase!=NULL){
			if(ABase->GetLibraryContainer()!=NULL){
				return ABase->GetLibraryContainer()->GetLibraryName(LibID);
			}
		}
	}
	return "";
}

bool	AlgorithmLibraryListWithResultContainer::IsIncludeLibType(int LibType) const
{
	for(AlgorithmLibraryListWithResult *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType)
			return true;
	}
	return false;
}

void	AlgorithmLibraryListWithResultContainer::MakeLibList(int LibType,IntList &LibList) const
{
	for(AlgorithmLibraryListWithResult *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType)
			LibList.Add(a->GetLibID());
	}
}
bool	AlgorithmLibraryListWithResultContainer::operator==(const AlgorithmLibraryListWithResultContainer &src)	const 
{
	for(AlgorithmLibraryListWithResult *d=GetFirst();d!=NULL;d=d->GetNext()){
		bool	Found=false;
		for(AlgorithmLibraryListWithResult *s=src.GetFirst();s!=NULL;s=s->GetNext()){
			if(*s==*d){
				Found=true;
				break;
			}
		}
		if(Found==false){
			return false;
		}
	}
	for(AlgorithmLibraryListWithResult *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(AlgorithmLibraryListWithResult *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*s==*d){
				Found=true;
				break;
			}
		}
		if(Found==false){
			return false;
		}
	}
	return true;	
}

//==========================================================================================================
NickInspectionThreshold::NickInspectionThreshold(NickInspectionItem *parent)
	:AlgorithmThreshold(parent)
{
	NGPercentage	=25;
	RefBrightness	=200;
	EnableWhite		=true;
	Layer			=0;
}

void	NickInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	AlgorithmThreshold::CopyFrom(src);

	const NickInspectionThreshold	*s=dynamic_cast<const NickInspectionThreshold *>(&src);
	NGPercentage	=s->NGPercentage;
	RefBrightness	=s->RefBrightness;
	EnableWhite		=s->EnableWhite;
	LibList			=s->LibList;
	Layer			=s->Layer;
}
bool	NickInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const NickInspectionThreshold	*s=dynamic_cast<const NickInspectionThreshold *>(&src);
	if(NGPercentage	!=s->NGPercentage	)	return false;
	if(RefBrightness!=s->RefBrightness	)	return false;
	if(EnableWhite	!=s->EnableWhite	)	return false;
	if(LibList		!=s->LibList		)	return false;
	if(Layer		!=s->Layer			)	return false;
	return true;
}
bool	NickInspectionThreshold::Save(QIODevice *f)
{
	int32	Ver=4;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,NGPercentage)==false){
		return false;
	}
	if(::Save(f,RefBrightness)==false){
		return false;
	}
	if(::Save(f,EnableWhite)==false){
		return false;
	}
	if(LibList.Save(f)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

bool	NickInspectionThreshold::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,NGPercentage)==false){
		return false;
	}
	if(::Load(f,RefBrightness)==false){
		return false;
	}
	if(::Load(f,EnableWhite)==false){
		return false;
	}
	if(LibList.Load(f)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}

	return true;
}

void	NickInspectionThreshold::FromLibrary(AlgorithmLibrary *src)
{
	NickInspectionLibrary	*s=dynamic_cast<NickInspectionLibrary *>(src);
	NGPercentage	=s->NGPercentage;
	RefBrightness	=s->RefBrightness;
	EnableWhite		=s->EnableWhite;
	LibList			=s->LibList;
	if(s->GetAdaptedGenLayers().GetFirst()!=NULL){
		Layer			=s->GetAdaptedGenLayers().GetFirst()->GetValue();
	}
}

void	NickInspectionThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	NickInspectionLibrary	*d=dynamic_cast<NickInspectionLibrary *>(Dest);
	d->NGPercentage	=NGPercentage;
	d->RefBrightness	=RefBrightness;
	d->EnableWhite		=EnableWhite;
	//d->LibList			=LibList;

	d->LibList.RemoveAll();
	for(AlgorithmLibraryListWithResult *s=LibList.GetFirst();s!=NULL;s=s->GetNext()){
		AlgorithmLibraryList	*dm=new AlgorithmLibraryList();
		dm->SetLibType	(s->GetLibType());
		dm->SetLibID		(s->GetLibID());
		d->LibList.AppendList(dm);
	}
}

//=====================================================================

NickInspectionInPage::NickInspectionInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
	ModeParallel.ModeParallelExecuteProcessing=false;
}

void	NickInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddNickInspectionItemPacket	*CmdAddNickInspectionItemVar=dynamic_cast<CmdAddNickInspectionItemPacket *>(packet);
	if(CmdAddNickInspectionItemVar!=NULL){
		AlgorithmItemRoot	*Item=CreateItem(0);
		Item->SetArea(CmdAddNickInspectionItemVar->Area);
		Item->SetLibID(CmdAddNickInspectionItemVar->LibID);
		NickInspectionBase	*BBase=(NickInspectionBase *)GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(CmdAddNickInspectionItemVar->LibID,LLib)==true){
			((NickInspectionItem *)Item)->CopyThresholdFromLibrary(&LLib);
			if(AppendItem(Item)==false){
				delete	Item;
			}
		}
		return;
	}

	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			bool	Found=false;
			for(NickInspectionListForPacket *s=MakeListPacketVar->ListInfo->GetFirst();s!=NULL;s=s->GetNext()){
				if(s->LibID==k->GetLibID()){
					s->ItemCount++;
					Found=true;
					break;
				}
			}
			if(Found==false){
				NickInspectionListForPacket	*d=new NickInspectionListForPacket();
				d->LibID=k->GetLibID();
				d->ItemCount=1;
				MakeListPacketVar->ListInfo->AppendList(d);
			}
		}
		return;
	}
	CmdGenerateNickInspectionPacket	*CmdGenerateNickInspectionPacketVar=dynamic_cast<CmdGenerateNickInspectionPacket *>(packet);
	if(CmdGenerateNickInspectionPacketVar!=NULL){
		GenerateBlocks(CmdGenerateNickInspectionPacketVar->LibList,NULL);
		return;
	}
}
void	NickInspectionInPage::GenerateBlocks(IntList &LibList
											,AlgorithmBase *Origin)
{
	RemoveAllDatas();
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	for(IntClass *s=LibList.GetFirst();s!=NULL;s=s->GetNext()){
		int	LibID=s->GetValue();
		AlgorithmBase	*ABase=GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(Container->GetLibrary(LibID,LLib)==true){
			NickInspectionLibrary	*ALib=dynamic_cast<NickInspectionLibrary *>(LLib.GetLibrary());
			ConstMapBufferListContainer MaskMap;
			if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
				ConstMapBuffer Map;
				MaskMap.BindOr(Map);
				PureFlexAreaListContainer Blocks;
				ALib->MakeBlocks(Blocks,Map.GetBitMap(),GetPage());
				PureFlexAreaList	*f;
				while((f=Blocks.GetFirst())!=NULL){
					Blocks.RemoveList(f);
					NickInspectionItem	*v=new NickInspectionItem(f);

					v->CopyThresholdFromLibrary(&LLib);
					v->SetLibID(LibID);
					AppendItem(v);
				}
			}
		}
	}
}

void	NickInspectionInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		NickInspectionItem	*BI=(NickInspectionItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

bool	NickInspectionInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	NickInspectionBase	*ABase=(NickInspectionBase *)GetParentBase();

	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){

		GetParentBase()->LoadAllManagedCacheLib();
		IntList LibList;
		LibList.Add(Info.LibID);
		GenerateBlocks(LibList,Info.Origin);
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			NickInspectionItem	*a=dynamic_cast<NickInspectionItem *>(k);
			if(a!=NULL){
				double	Cx,Cy;
				double	AckX,AckY;
				a->GetCenter(Cx,Cy);
				if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
					a->MoveTo(AckX-Cx,AckY-Cy);
				}
			}
		}
		return true;
	}

	return false;
}
//=====================================================================
NickInspectionBase::NickInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	MaxNSize		=60;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
	SetParam(&MaxNSize			, /**/"Setting" ,/**/"MaxNSize"			,"Absolutely NG if NG size is bigger than this");

}

AlgorithmDrawAttr	*NickInspectionBase::CreateDrawAttr(void)
{
	return new NickInspectionDrawAttr();
}

void	NickInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetNickInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetNickInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempNickInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempNickInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadNickInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadNickInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearNickInspectionLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearNickInspectionLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteNickInspectionLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteNickInspectionLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertNickInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertNickInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(NickInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateNickInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateNickInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(NickInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetNickInspectionLibraryNamePacket	*CmdGetNickInspectionLibraryNamePacketVar=dynamic_cast<CmdGetNickInspectionLibraryNamePacket *>(packet);
	if(CmdGetNickInspectionLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetNickInspectionLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetNickInspectionLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetNickInspectionLibraryNamePacketVar->Success==true){
				CmdGetNickInspectionLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
}

bool	NickInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==NickInspectionReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==NickInspectionReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*NickInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==NickInspectionReqThresholdReqCommand){
		return new NickInspectionThresholdReq();
	}
	else if(Command==NickInspectionReqThresholdSendCommand){
		NickInspectionThresholdSend	*pSend=new NickInspectionThresholdSend();
		if(reqData!=NULL){
			NickInspectionThresholdReq	*req=(NickInspectionThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	NickInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==NickInspectionReqThresholdReqCommand){
		NickInspectionThresholdReq	*p=(NickInspectionThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==NickInspectionReqThresholdSendCommand){
		NickInspectionThresholdSend	*p=(NickInspectionThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	NickInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==NickInspectionReqThresholdReqCommand){
		NickInspectionThresholdReq	*p=(NickInspectionThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==NickInspectionReqThresholdSendCommand){
		NickInspectionThresholdSend	*p=(NickInspectionThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	NickInspectionBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==NickInspectionReqThresholdReqCommand){
		NickInspectionThresholdReq	*p=(NickInspectionThresholdReq *)data;
		return true;
	}
	else if(Command==NickInspectionReqThresholdSendCommand){
		NickInspectionThresholdSend	*p=(NickInspectionThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

//======================================================================

NickInspectionThresholdReq::NickInspectionThresholdReq(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Layer		=-1;
	Mastered	=true;
	Dx			=0;
	Dy			=0;
}

bool	NickInspectionThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}

bool	NickInspectionThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

NickInspectionThresholdSend::NickInspectionThresholdSend(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Layer		=-1;
	Dx			=0;
	Dy			=0;
	NGPercentage	=30;	
	RefBrightness	=200;
	EnableWhite		=true;
}

void	NickInspectionThresholdSend::ConstructList(NickInspectionThresholdReq *reqPacket,NickInspectionBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ItemID		=reqPacket->ItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			NickInspectionItem	*Item=dynamic_cast<NickInspectionItem*>(item);
			const NickInspectionThreshold	*RThr=Item->GetThresholdR(Ap->GetLayersBase());
			NGPercentage	=RThr->NGPercentage	;
			RefBrightness	=RThr->RefBrightness	;
			EnableWhite		=RThr->EnableWhite		;
			Result			=RThr->LibList			;
		}
	}
}
	
bool	NickInspectionThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,NGPercentage)==false){
		return false;
	}
	if(::Save(f,RefBrightness)==false){
		return false;
	}
	if(::Save(f,EnableWhite)==false){
		return false;
	}
	if(Result.Save(f)==false){
		return false;
	}

	return true;
}
	
bool	NickInspectionThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,NGPercentage)==false){
		return false;
	}
	if(::Load(f,RefBrightness)==false){
		return false;
	}
	if(::Load(f,EnableWhite)==false){
		return false;
	}
	if(Result.Load(f)==false){
		return false;
	}

	return true;
}

