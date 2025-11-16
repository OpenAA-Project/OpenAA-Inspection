#include "XIntegrationBasePacket.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "XParamGlobal.h"
#include "XDataAlgorithmList.h"
#include "swap.h"
#include <omp.h>

IntegrationReqMasterImage::IntegrationReqMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	memset(&Info,0,sizeof(Info));
}
bool	IntegrationReqMasterImage::Load(QIODevice *f)
{
	if(f->read((char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;
	return true;
}
bool	IntegrationReqMasterImage::Save(QIODevice *f)
{
	if(f->write((const char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;
	return true;
}

struct FuncStruct
{
	int	TopY;
	int	BottomY;
};

static	bool Func(void *caller,AlgorithmItemRoot *item)
{
	struct FuncStruct	*L=((struct FuncStruct *)caller);
	if(item->GetMasterNo()>0){
		int	x1,y1,x2,y2;
		item->GetXY(x1,y1,x2,y2);
		if((y1<=L->TopY && L->TopY<y2)
		|| (y1<=L->BottomY && L->BottomY<y2)
		|| (L->TopY<=y1 && y1<L->BottomY)){
			return true;
		}
	}
	return false;
}
void	IntegrationReqMasterImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckMasterImage	*SendBack=GetSendBackIntegration(IntegrationAckMasterImage,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	SendBack->Info.OK=false;
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Info.Phase);
	if(Ph!=NULL){
		DataInPage	*Pg=Ph->GetPageData(Info.Page);
		if(Pg!=NULL){
			DataInLayer	*L=Pg->GetLayerData(Info.Layer);
			if(L!=NULL){
				if(Info.MixMaster==false){
					ImageBuffer	&Buff=L->GetMasterBuff();
					if(SendBack->Data==NULL){
						SendBack->AllocatedByteCount=Info.LineCount*Pg->GetDotPerLine();
						SendBack->Data=new BYTE[SendBack->AllocatedByteCount];
					}
					BYTE	*d=SendBack->Data;
					int	y=Info.TopY;
					int	XLen=Pg->GetDotPerLine();
					SendBack->Info.LineCount=0;
					for(int i=0;y<Pg->GetMaxLines() && i<Info.LineCount;y++,i++){
						BYTE	*s=Buff.GetY(y);
						memcpy(d,s,XLen);
						d+=XLen;
						SendBack->Info.LineCount++;
					}
					SendBack->Info.Phase	=Info.Phase;
					SendBack->Info.Page		=Info.Page;
					SendBack->Info.Layer	=Info.Layer;
					SendBack->Info.TopY		=Info.TopY;
					SendBack->Info.DotPerLine=XLen;
					SendBack->Info.OK=true;
				}
				else{
					if(SendBack->Data==NULL
					|| SendBack->AllocatedByteCount!=Info.LineCount*Pg->GetDotPerLine()){
						if(SendBack->Data!=NULL){
							delete	[]SendBack->Data;
						}
						SendBack->AllocatedByteCount=Info.LineCount*Pg->GetDotPerLine();
						SendBack->Data=new BYTE[SendBack->AllocatedByteCount];
					}
					ImageBuffer	&Buff=L->GetMasterBuff();
					BYTE	*d=SendBack->Data;
					int	y=Info.TopY;
					int	XLen=Pg->GetDotPerLine();
					SendBack->Info.LineCount=0;
					for(int i=0;y<Pg->GetMaxLines() && i<Info.LineCount;y++,i++){
						BYTE	*s=Buff.GetY(y);
						memcpy(d,s,XLen);
						d+=XLen;
						SendBack->Info.LineCount++;
					}
					struct FuncStruct	DStruct;
					DStruct.TopY	=Info.TopY;
					DStruct.BottomY	=Info.TopY+Info.LineCount;
					QImage	Img=QImage(GetDotPerLine(Info.Page)
										,Info.LineCount
										,QImage::Format_ARGB32);
					//Img.fill(qRgba(0,0,0,0));
					::ClearImage(Img, 0);
					for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
						AlgorithmBase	*ABase=DLL->GetInstance();
						AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Info.Phase);
						AlgorithmInPageRoot	*Ap=Ah->GetPageData(Info.Page);
						AlgorithmItemPointerListContainer Items;
						Ap->EnumItems(Info.Layer,&DStruct,Items , Func);
						for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
							ImageBuffer *IBuff[3];
							int	MasterNo=a->GetItem()->GetMasterNo();
							if(MasterNo<L->GetCountAllMasterBuff()){
								ImagePointerContainer Images;
								Ap->GetMasterImages(MasterNo,Images);
								int	k=0;
								for(ImagePointerList *q=Images.GetFirst();q!=NULL && k<3;q=q->GetNext(),k++){
									IBuff[k]=q->GetImage();
								}
								a->GetItem()->GetArea().Draw(0,-Info.TopY,&Img
															,IBuff,k
															,1.0,0,0);
							}
						}
					}
					d=SendBack->Data;
					int	N=min(Pg->GetMaxLines()-Info.TopY,Info.LineCount);
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for(int i=0;i<N;i++){
							QRgb	*s=(QRgb *)Img.scanLine(i);
							BYTE	*dn=&SendBack->Data[i*XLen];
							if(Info.Layer==0){
								for(int x=0;x<XLen;x++){
									int	Alpha=qAlpha(*s);
									dn[x]=Clipping(dn[x]*(256-Alpha)+qRed(*s)*Alpha,0,65535)>>8;
									s++;
								}
							}
							else
							if(Info.Layer==1){
								for(int x=0;x<XLen;x++){
									int	Alpha=qAlpha(*s);
									dn[x]=Clipping(dn[x]*(256-Alpha)+qGreen(*s)*Alpha,0,65535)>>8;
									s++;
								}
							}
							else
							if(Info.Layer>=2){
								for(int x=0;x<XLen;x++){
									int	Alpha=qAlpha(*s);
									dn[x]=Clipping(dn[x]*(256-Alpha)+qBlue(*s)*Alpha,0,65535)>>8;
									s++;
								}
							}
						}
					}

					SendBack->Info.Phase	=Info.Phase;
					SendBack->Info.Page		=Info.Page;
					SendBack->Info.Layer	=Info.Layer;
					SendBack->Info.TopY		=Info.TopY;
					SendBack->Info.DotPerLine=XLen;
					SendBack->Info.OK=true;
				}
			}
		}
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckMasterImage::IntegrationAckMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Data=NULL;
	AllocatedByteCount=0;
}

IntegrationAckMasterImage::~IntegrationAckMasterImage(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

bool	IntegrationAckMasterImage::Load(QIODevice *f)
{
	if(f->read((char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;
	int	iAllocatedByteCount;
	if(::Load(f,iAllocatedByteCount)==false)
		return false;
	if(Data!=NULL && AllocatedByteCount!=iAllocatedByteCount){
		delete	[]Data;
		Data=NULL;
	}
	AllocatedByteCount=iAllocatedByteCount;
	if(Data==NULL){
		Data=new BYTE[AllocatedByteCount];
	}
	if(f->read((char *)Data,AllocatedByteCount)!=AllocatedByteCount)
		return false;

	return true;
}

bool	IntegrationAckMasterImage::Save(QIODevice *f)
{
	if(f->write((const char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;
	if(::Save(f,AllocatedByteCount)==false)
		return false;
	if(f->write((const char *)Data,AllocatedByteCount)!=AllocatedByteCount)
		return false;
	return true;
}


IntegrationReqMasterInfo::IntegrationReqMasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
	
void	IntegrationReqMasterInfo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	IntegrationAckMasterInfo	*SendBack=GetSendBackIntegration(IntegrationAckMasterInfo,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	SendBack->MasterCode=GetLayersBase()->GetMasterCode();
	SendBack->PhaseNumb	=GetPhaseNumb();
	SendBack->PageNumb	=GetPageNumb();
	
	SendBack->CData=new DataInPage::ConstructionData[SendBack->PhaseNumb*SendBack->PageNumb];
	SendBack->LayerNumbDim=new int32[SendBack->PageNumb];
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *Pg=Ph->GetPageData(page);
			SendBack->CData[phase*SendBack->PageNumb+page]=Pg->CData;
			//SendBack->LayerNumb	=GetLayerNumb(page);
			if(Pg->CData.DotPerLine<=0)
				SendBack->CData[phase*SendBack->PageNumb+page].DotPerLine=Pg->GetDotPerLine();
			if(Pg->CData.MaxLines<=0)
				SendBack->CData[phase*SendBack->PageNumb+page].MaxLines=Pg->GetMaxLines();
		}
	}
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(0);
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *Pg=Ph->GetPageData(page);
		SendBack->LayerNumbDim[page]=Pg->GetLayerNumb();
	}
	SendBack->TransformUnitPerPixelX=GetParamGlobal()->ResolutionXNano/GetParamGlobal()->TransformUnitToNano;
	SendBack->TransformUnitPerPixelY=GetParamGlobal()->ResolutionYNano/GetParamGlobal()->TransformUnitToNano;

	SendBack->AccessToPageDim=new AccessToPage[SendBack->PageNumb];
	if(GetParamComm()->ConnectedPCNumb==0){
		for(int page=0;page<GetPageNumb();page++){
			SendBack->AccessToPageDim[page].IPAddress=/**/"localhost";
			SendBack->AccessToPageDim[page].Port	 =0;
			SendBack->AccessToPageDim[page].GlobalPage=page;
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			ConnectionInfo	*c=GetParamComm()->GetConnectionFromPage(*GetLayersBase()->GetParamGlobal(),page);
			SendBack->AccessToPageDim[page].IPAddress=c->IPAddress;
			SendBack->AccessToPageDim[page].Port	 =c->GetPortNo();
			SendBack->AccessToPageDim[page].GlobalPage=page;
		}	
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckMasterInfo::IntegrationAckMasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	CData			=NULL;
	LayerNumbDim	=NULL;
	AccessToPageDim	=NULL;
}

IntegrationAckMasterInfo::~IntegrationAckMasterInfo(void)
{
	if(CData!=NULL){
		delete	[]CData;
		CData=NULL;
	}
	if(AccessToPageDim!=NULL){
		delete	[]AccessToPageDim;
		AccessToPageDim=NULL;
	}
	if(LayerNumbDim!=NULL){
		delete	[]LayerNumbDim;
		LayerNumbDim=NULL;
	}
}

bool	IntegrationAckMasterInfo::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,PhaseNumb)==false)
		return false;
	if(::Load(f,PageNumb)==false)
		return false;
	//if(::Load(f,LayerNumb)==false)
	//	return false;
	if(CData!=NULL){
		delete	[]CData;
	}
	CData=new DataInPage::ConstructionData[PhaseNumb*PageNumb];
	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<PageNumb;page++){
			if(CData[phase*PageNumb+page].Load(f)==false)
				return false;
		}
	}
	if(::Load(f,TransformUnitPerPixelX)==false){
		return false;
	}
	if(::Load(f,TransformUnitPerPixelY)==false){
		return false;
	}

	if(AccessToPageDim!=NULL){
		delete	[]AccessToPageDim;
	}
	AccessToPageDim=new AccessToPage[PageNumb];
	for(int page=0;page<PageNumb;page++){
		if(AccessToPageDim[page].Load(f)==false){
			return false;
		}
	}
	if(LayerNumbDim!=NULL){
		delete	[]LayerNumbDim;
	}
	LayerNumbDim=new int32[PageNumb];
	for(int page=0;page<PageNumb;page++){
		if(::Load(f,LayerNumbDim[page])==false){
			return false;
		}
	}

	return true;
}
bool	IntegrationAckMasterInfo::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,PhaseNumb)==false)
		return false;
	if(::Save(f,PageNumb)==false)
		return false;
	//if(::Save(f,LayerNumb)==false)
	//	return false;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<PageNumb;page++){
			if(CData[phase*PageNumb+page].Save(f)==false)
				return false;
		}
	}
	if(::Save(f,TransformUnitPerPixelX)==false)
		return false;
	if(::Save(f,TransformUnitPerPixelY)==false)
		return false;

	for(int page=0;page<PageNumb;page++){
		if(AccessToPageDim[page].Save(f)==false)
			return false;
	}
	for(int page=0;page<PageNumb;page++){
		if(::Save(f,LayerNumbDim[page])==false){
			return false;
		}
	}
	return true;
}
	
IntegrationReqAlive::IntegrationReqAlive(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqAlive::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckAlive	*SendBack=GetSendBackIntegration(IntegrationAckAlive,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAlive::IntegrationAckAlive(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}


IntegrationExecuteInitialAfterEdit::IntegrationExecuteInitialAfterEdit(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationExecuteInitialAfterEdit::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"CalcFinalization",/**/"");
	if(f!=NULL){
		QStringList Args;
		bool ExeReturn;
		f->ExecuteMacro(/**/"Execute", Args, ExeReturn);
	}
}
//===================================================================================================
IntegrationCmdAddPhase::IntegrationCmdAddPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAddPhase::Load(QIODevice *f)
{
	if(::Load(f,PhaseNameList)==false)
		return false;
	return true;
}

bool	IntegrationCmdAddPhase::Save(QIODevice *f)
{
	if(::Save(f,PhaseNameList)==false)
		return false;
	return true;
}

void	IntegrationCmdAddPhase::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	AddedCount=PhaseNameList.count();
	int	PhaseCode=GetPhaseNumb();
	GetLayersBase()->Reallocate(PhaseCode+AddedCount);
	for(int i=0;i<AddedCount;i++){
		GetParamGlobal()->SetPhaseString(PhaseCode+i,PhaseNameList[i]);
	}
}

	
IntegrationCmdDelPhase::IntegrationCmdDelPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	PhaseNo=0;
}

bool	IntegrationCmdDelPhase::Load(QIODevice *f)
{
	if(::Load(f,PhaseNo)==false)
		return false;
	return true;
}
bool	IntegrationCmdDelPhase::Save(QIODevice *f)
{
	if(::Save(f,PhaseNo)==false)
		return false;
	return true;
}

void	IntegrationCmdDelPhase::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->RemovePhase(PhaseNo);
}

IntegrationCmdChangeCurrentPhase::IntegrationCmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	PhaseNo=0;
}

bool	IntegrationCmdChangeCurrentPhase::Load(QIODevice *f)
{
	if(::Load(f,PhaseNo)==false)
		return false;
	return true;
}
bool	IntegrationCmdChangeCurrentPhase::Save(QIODevice *f)
{
	if(::Save(f,PhaseNo)==false)
		return false;
	return true;
}

void	IntegrationCmdChangeCurrentPhase::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetCurrentPhase(PhaseNo);
}

IntegrationCmdReqPhaseNames::IntegrationCmdReqPhaseNames(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdReqPhaseNames::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckPhaseNames	*SendBack=GetSendBackIntegration(IntegrationCmdAckPhaseNames,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	for(int phase=0;phase<GetParamGlobal()->PhaseNumb;phase++){
		SendBack->PhaseNames.append(GetParamGlobal()->GetPhaseString(phase));
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckPhaseNames::IntegrationCmdAckPhaseNames(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAckPhaseNames::Load(QIODevice *f)
{
	if(::Load(f,PhaseNames)==false){
		return false;
	}
	return true;
}
bool	IntegrationCmdAckPhaseNames::Save(QIODevice *f)
{
	if(::Save(f,PhaseNames)==false){
		return false;
	}
	return true;
}

IntegrationCmdSetPhase::IntegrationCmdSetPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdSetPhase::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,PhaseName)==false){
		return false;
	}
	return true;
}
bool	IntegrationCmdSetPhase::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,PhaseName)==false){
		return false;
	}
	return true;
}

void	IntegrationCmdSetPhase::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetParamGlobal()->SetPhaseString(Phase,PhaseName);
}

//===================================================================================================

bool	AlgorithmRootNameList::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot			)==false)	return false;
	if(::Save(f,DLLName			)==false)	return false;
	if(::Save(f,AlgorithmType	)==false)	return false;
	if(::Save(f,LibType			)==false)	return false;
	return true;
}
bool	AlgorithmRootNameList::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot			)==false)	return false;
	if(::Load(f,DLLName			)==false)	return false;
	if(::Load(f,AlgorithmType	)==false)	return false;
	if(::Load(f,LibType			)==false)	return false;
	return true;
}

IntegrationReqUsageAlgorithm::IntegrationReqUsageAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqUsageAlgorithm::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckUsageAlgorithm	*SendBack=GetSendBackIntegration(IntegrationAckUsageAlgorithm,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmRootNameList	*a=new AlgorithmRootNameList();
		a->DLLRoot	=L->GetDLLRoot();
		a->DLLName	=L->GetDLLName();
		a->AlgorithmType	=L->GetAlgorithmType();
		if(L->GetLibContainer()!=NULL){
			a->LibType			=L->GetLibContainer()->GetLibType();
		}
		SendBack->Datas.AppendList(a);
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckUsageAlgorithm::IntegrationAckUsageAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckUsageAlgorithm::Load(QIODevice *f)
{
	if(Datas.Save(f)==false)	return false;
	return true;
}

bool	IntegrationAckUsageAlgorithm::Save(QIODevice *f)
{
	if(Datas.Load(f)==false)	return false;
	return true;
}

//===================================================================================================
IntegrationReqReportedTopics::IntegrationReqReportedTopics(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqReportedTopics::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot)==false)	return false;
	if(::Load(f,DLLName)==false)	return false;
	return true;
}
bool	IntegrationReqReportedTopics::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot)==false)	return false;
	if(::Save(f,DLLName)==false)	return false;
	return true;
}

void	IntegrationReqReportedTopics::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckReportedTopics	*SendBack=GetSendBackIntegration(IntegrationAckReportedTopics,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
	if(ABase!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot	*Ap=ABase->GetPageData(page);
			IntList LibIDList;
			Ap->EnumLibID(LibIDList);
			for(IntClass *v=LibIDList.GetFirst();v!=NULL;v=v->GetNext()){
				int	LibID=v->GetValue();
				AlgorithmItemPointerListContainer RetContainer;
				Ap->MakeItemList(LibID,RetContainer);
				
				for(AlgorithmItemPointerList *L=RetContainer.GetFirst();L!=NULL;L=L->GetNext()){
					ReportedTopicContainer	TopicContainer;
					L->GetItem()->GetThresholdBaseWritable()->MakeReportedTopics(TopicContainer);
					bool	Found=false;
					for(ReportedTopicsInItem *R=SendBack->Datas.GetFirst();R!=NULL;R=R->GetNext()){
						if(R->LibID==LibID && R->TopicsContainer==TopicContainer){
							R->ItemCount++;
							Found=true;
							break;
						}
					}
					if(Found==false){
						ReportedTopicsInItem	*R=new ReportedTopicsInItem();
						R->LibID=LibID;
						R->TopicsContainer	=TopicContainer;
						SendBack->Datas.AppendList(R);
					}
				}
			}
		}
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckReportedTopics::IntegrationAckReportedTopics(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckReportedTopics::Load(QIODevice *f)
{
	if(Datas.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckReportedTopics::Save(QIODevice *f)
{
	if(Datas.Load(f)==false)	return false;
	return true;
}

IntegrationAck::IntegrationAck(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

//===================================================================================================
IntegrationRebuildThresholdLevel::IntegrationRebuildThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationRebuildThresholdLevel::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->DeliverRebuildThresholdLevel();
}
//===================================================================================================
IntegrationSetThresholdLevel::IntegrationSetThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetThresholdLevel::Load(QIODevice *f)
{
	if(::Load(f,LevelID)==false)	return false;
	return true;
}
bool	IntegrationSetThresholdLevel::Save(QIODevice *f)
{
	if(::Save(f,LevelID)==false)	return false;
	return true;
}

void	IntegrationSetThresholdLevel::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetThresholdLevel(LevelID);
	GetLayersBase()->DeliverThresholdLevel();
}
//===================================================================================================
IntegrationSetCurrentIntoThresholdLevel::IntegrationSetCurrentIntoThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetCurrentIntoThresholdLevel::Load(QIODevice *f)
{
	if(::Load(f,LevelID)==false)	return false;
	return true;
}
bool	IntegrationSetCurrentIntoThresholdLevel::Save(QIODevice *f)
{
	if(::Save(f,LevelID)==false)	return false;
	return true;
}

void	IntegrationSetCurrentIntoThresholdLevel::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->DeliverSetCurrentIntoThresholdLevel(LevelID);
}
//===================================================================================================
IntegrationCopyThresholdLevel::IntegrationCopyThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCopyThresholdLevel::Load(QIODevice *f)
{
	if(::Load(f,SourceLevelID)==false)	return false;
	if(::Load(f,DestLevelID)==false)	return false;
	return true;
}
bool	IntegrationCopyThresholdLevel::Save(QIODevice *f)
{
	if(::Save(f,SourceLevelID)==false)	return false;
	if(::Save(f,DestLevelID)==false)	return false;
	return true;
}

void	IntegrationCopyThresholdLevel::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->DeliverCopyThresholdLevel(SourceLevelID ,DestLevelID);
}