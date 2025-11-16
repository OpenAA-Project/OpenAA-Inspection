#include <cmath>
#include "XRasterInspectionPacket.h"
#include "XGeneralFunc.h"
#include "XRasterInspection.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "swap.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


RasterInspectionThresholdReq::RasterInspectionThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	RasterInspectionThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
bool	RasterInspectionThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

RasterInspectionThresholdSend::RasterInspectionThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;

	GenColorDistance	=0;
	SearchAreaDot		=0;
	SearchWaveDiv		=0;
	WaveDistance		=0;
	OKDot				=0;

}

void	RasterInspectionThresholdSend::ConstructList(RasterInspectionThresholdReq *reqPacket,RasterInspectionBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			RasterInspectionItem	*BItem=(RasterInspectionItem *)item;

			const	RasterInspectionThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			GenColorDistance	=RThr->GenColorDistance	;
			SearchAreaDot		=RThr->SearchAreaDot	;
			SearchWaveDiv		=RThr->SearchWaveDiv	;
			WaveDistance		=RThr->WaveDistance		;
			OKDot				=RThr->OKDot			;
		}
	}
}

bool	RasterInspectionThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	if(::Save(f,GenColorDistance)==false)
		return false;
	if(::Save(f,SearchAreaDot)==false)
		return false;
	if(::Save(f,SearchWaveDiv)==false)
		return false;
	if(::Save(f,WaveDistance)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;

	return true;
}
bool	RasterInspectionThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	if(::Load(f,GenColorDistance)==false)
		return false;
	if(::Load(f,SearchAreaDot)==false)
		return false;
	if(::Load(f,SearchWaveDiv)==false)
		return false;
	if(::Load(f,WaveDistance)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;

	return true;
}

RasterInspectionReqTryThreshold::RasterInspectionReqTryThreshold(void)
{
	Data.GlobalPage=-1;
	Data.ItemID=-1;
}
bool	RasterInspectionReqTryThreshold::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	RasterInspectionReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

RasterInspectionSendTryThreshold::RasterInspectionSendTryThreshold(void)
{
	Result		=new ResultInItemPI();
}
RasterInspectionSendTryThreshold::~RasterInspectionSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	RasterInspectionSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;

	return true;
}
bool	RasterInspectionSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;

	return true;
}

void	RasterInspectionSendTryThreshold::ConstructList(RasterInspectionReqTryThreshold *reqPacket,RasterInspectionBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	RasterInspectionInPage		*BP=(RasterInspectionInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->Data.GlobalPage));
	if(BP!=NULL){
		RasterInspectionItem		*BI=(RasterInspectionItem *)BP->SearchIDItem(reqPacket->Data.ItemID);
		if(BI!=NULL){
			Calc(&reqPacket->Threshold,BI,Base);
		}
	}
}
void	RasterInspectionSendTryThreshold::Calc(RasterInspectionItem *Target
												,RasterInspectionItem *Src
												,RasterInspectionBase *Base)

{
	RasterInspectionInPage		*BP=(RasterInspectionInPage *)Base->GetPageData(Src->GetPage());
	RasterInspectionBase		*BBase=(RasterInspectionBase *)BP->GetParentBase();
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());

	int	SaveMaxInspectMilisec	=Base->GetParamGlobal()->MaxInspectMilisec;

	Base->GetParamGlobal()->MaxInspectMilisec	=99999999;
	Target->SetParent(Src->GetParent());

	Target->SetLibID(Src->GetLibID());
	//Target->CopyArea(*Src);
	RasterInspectionThreshold			*WThr=Target->GetThresholdW();
	const	RasterInspectionThreshold	*RThr=Src	->GetThresholdR();	
	WThr->CopyFrom(*RThr);

	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
	Target->ExecuteStartByInspection(0 ,0,Result);
	Target->ExecuteProcessing		(0 ,0,Result);

	Result->SetAddedData(NULL,0);	
}

//=================================================================================

LibraryEfectivity::LibraryEfectivity(void)
{
	LibID	=0;
	IncludedInMask	=false;
}

bool	LibraryEfectivity::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,IncludedInMask)==false)
		return false;
	return true;
}

bool	LibraryEfectivity::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,IncludedInMask)==false)
		return false;
	return true;
}


bool	LibraryEfectivityContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(LibraryEfectivity *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	LibraryEfectivityContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		LibraryEfectivity	*a=new LibraryEfectivity();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
bool	LibraryEfectivityContainer::IsIncluded(int LibID)
{
	for(LibraryEfectivity *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID){
			return a->IncludedInMask;
		}
	}
	return false;
}

//================================================================================
SlaveCommReqLibraryInMaskOfRasterInspection::SlaveCommReqLibraryInMaskOfRasterInspection(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqLibraryInMaskOfRasterInspection::Load(QIODevice *f)
{
	if(UsedLibraries.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqLibraryInMaskOfRasterInspection::Save(QIODevice *f)
{
	if(UsedLibraries.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqLibraryInMaskOfRasterInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckLibraryInMaskOfRasterInspection	*S
	=(SlaveCommAckLibraryInMaskOfRasterInspection *)((GetSendBackPacket()==NULL)?new SlaveCommAckLibraryInMaskOfRasterInspection(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmLibraryLevelContainer	LLib(BBase);
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		for(IntClass *a=UsedLibraries.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibrary *Lib=BBase->GetLibraryContainer()->CreateNew();
			Lib->SetParent(&LLib);
			LLib.SetLibID(a->GetValue());
			S->UsedLibraries.AppendList(new LibraryEfectivity(a->GetValue(),Pg->IncludeLibInReflection(_Reflection_Mask,Lib)));
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckLibraryInMaskOfRasterInspection::SlaveCommAckLibraryInMaskOfRasterInspection(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommAckLibraryInMaskOfRasterInspection::Load(QIODevice *f)
{
	if(UsedLibraries.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckLibraryInMaskOfRasterInspection::Save(QIODevice *f)
{
	if(UsedLibraries.Save(f)==false)
		return false;
	return true;
}

static	int	TestDbg=1;
void	SlaveCommAckLibraryInMaskOfRasterInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	TestDbg++;
}
