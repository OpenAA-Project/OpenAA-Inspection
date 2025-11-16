//#include "LinePatternInspectionResource.h"
#include "XLinePatternInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XLinePatternPacket.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "XPropertyLinePatternCommon.h"
#include "XLinePatternAlgoPacket.h"
#include "DisplaySimPanelLinePattern.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool	LinePatternThreshold::LinePatternThreshBag::operator==(const LinePatternThreshold::LinePatternThreshBag &src)	const 
{
	const LinePatternThreshold::LinePatternThreshBag *s=(const LinePatternThreshold::LinePatternThreshBag *)&src;
	if(BrightWidthIL	!=s->BrightWidthIL	)	return false;
	if(BrightWidthIH	!=s->BrightWidthIH	)	return false;
	if(BrightWidthOL	!=s->BrightWidthOL	)	return false;
	if(BrightWidthOH	!=s->BrightWidthOH	)	return false;
	if(NGSizeIL			!=s->NGSizeIL		)	return false;
	if(NGSizeIH			!=s->NGSizeIH		)	return false;
	if(NGSizeOL			!=s->NGSizeOL		)	return false;
	if(NGSizeOH			!=s->NGSizeOH		)	return false;
	if(TransitDot		!=s->TransitDot		)	return false;
	if(SearchDot		!=s->SearchDot		)	return false;
	if(AdjustBrightIL	!=s->AdjustBrightIL	)	return false;
	if(AdjustBrightIH	!=s->AdjustBrightIH	)	return false;
	if(AdjustBrightOL	!=s->AdjustBrightOL	)	return false;
	if(AdjustBrightOH	!=s->AdjustBrightOH	)	return false;
	if(GlobalSearchDot	!=s->GlobalSearchDot)	return false;

	if(PointMove.ModeEnabled				!=s->PointMove.ModeEnabled				)	return false;
	if(PointMove.ModeAbsoluteBright			!=s->PointMove.ModeAbsoluteBright		)	return false;
	if(PointMove.ModeCenterBrightFromParts	!=s->PointMove.ModeCenterBrightFromParts)	return false;
	if(PointMove.ModeDynamicMask			!=s->PointMove.ModeDynamicMask			)	return false;
	if(PointMove.ModeUseRegularBrightness	!=s->PointMove.ModeUseRegularBrightness	)	return false;

	if(RegulatedColI	!=s->RegulatedColI	)	return false;
	if(RegulatedColO	!=s->RegulatedColO	)	return false;

	return true;
}

LinePatternThreshold::LinePatternThreshold(LinePatternItem *parent)
	:AlgorithmThreshold(parent)
{
	ThreshBag.BrightWidthIL		=20;
	ThreshBag.BrightWidthIH		=20;
	ThreshBag.BrightWidthOL		=20;
	ThreshBag.BrightWidthOH		=20;
	ThreshBag.NGSizeIL			=10;
	ThreshBag.NGSizeIH			=10;
	ThreshBag.NGSizeOL			=10;
	ThreshBag.NGSizeOH			=10;
	ThreshBag.TransitDot		=1;
	ThreshBag.SearchDot			=5;
	ThreshBag.AdjustBrightIL	=20;
	ThreshBag.AdjustBrightIH	=20;
	ThreshBag.AdjustBrightOL	=20;
	ThreshBag.AdjustBrightOH	=20;
	ThreshBag.GlobalSearchDot	=100;

	ThreshBag.PointMove.ModeEnabled					=true;
	ThreshBag.PointMove.ModeAbsoluteBright			=false;
	ThreshBag.PointMove.ModeCenterBrightFromParts	=false;
	ThreshBag.PointMove.ModeDynamicMask				=true;
	ThreshBag.PointMove.ModeUseRegularBrightness	=true;
	ThreshBag.RegulatedColI	=0;
	ThreshBag.RegulatedColO	=0;
	AngleNumb				=1;
}

void	LinePatternThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	AlgorithmThreshold::CopyFrom(src);

	const LinePatternThreshold	*s=dynamic_cast<const LinePatternThreshold *>(&src);
	ThreshBag		=s->ThreshBag;
}
bool	LinePatternThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const LinePatternThreshold	*s=dynamic_cast<const LinePatternThreshold *>(&src);
	if(ThreshBag!=s->ThreshBag)	return false;
	return true;
}
bool	LinePatternThreshold::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false){
		return false;
	}

	if(f->write((const char *)&ThreshBag,sizeof(ThreshBag))!=sizeof(ThreshBag)){
		return false;
	}
	if(::Save(f,AngleNumb)==false){
		return false;
	}
	return true;
}

bool	LinePatternThreshold::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(f->read((char *)&ThreshBag,sizeof(ThreshBag))!=sizeof(ThreshBag)){
		return false;
	}
	if(Ver>=2){
		if(::Load(f,AngleNumb)==false){
			return false;
		}
	}
	return true;
}

void	LinePatternThreshold::FromLibrary(AlgorithmLibrary *src)
{
	LinePatternLibrary	*s=dynamic_cast<LinePatternLibrary *>(src);
		
	ThreshBag.BrightWidthIL		=s->BrightWidthIL;
	ThreshBag.BrightWidthIH		=s->BrightWidthIH;
	ThreshBag.BrightWidthOL		=s->BrightWidthOL;
	ThreshBag.BrightWidthOH		=s->BrightWidthOH;
	ThreshBag.NGSizeIL			=s->NGSizeIL;
	ThreshBag.NGSizeIH			=s->NGSizeIH;
	ThreshBag.NGSizeOL			=s->NGSizeOL;
	ThreshBag.NGSizeOH			=s->NGSizeOH;
	ThreshBag.TransitDot		=s->TransitDot;
	ThreshBag.SearchDot			=s->SearchDot;
	ThreshBag.AdjustBrightIL	=s->AdjustBrightIL;
	ThreshBag.AdjustBrightIH	=s->AdjustBrightIH;
	ThreshBag.AdjustBrightOL	=s->AdjustBrightOL;
	ThreshBag.AdjustBrightOH	=s->AdjustBrightOH;
	ThreshBag.GlobalSearchDot	=s->GlobalSearchDot;

	ThreshBag.PointMove.ModeEnabled					=s->PointMove.ModeEnabled;
	ThreshBag.PointMove.ModeAbsoluteBright			=s->PointMove.ModeAbsoluteBright;
	ThreshBag.PointMove.ModeCenterBrightFromParts	=s->PointMove.ModeCenterBrightFromParts;
	ThreshBag.PointMove.ModeDynamicMask				=s->PointMove.ModeDynamicMask;
	ThreshBag.PointMove.ModeUseRegularBrightness	=s->PointMove.ModeUseRegularBrightness;
	ThreshBag.RegulatedColI		=s->RegulatedColI;
	ThreshBag.RegulatedColO		=s->RegulatedColO;
	AngleNumb					=s->AngleNumb;
}

void	LinePatternThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	LinePatternLibrary	*d=dynamic_cast<LinePatternLibrary *>(Dest);
	d->BrightWidthIL	=ThreshBag.BrightWidthIL;
	d->BrightWidthIH	=ThreshBag.BrightWidthIH;
	d->BrightWidthOL	=ThreshBag.BrightWidthOL;
	d->BrightWidthOH	=ThreshBag.BrightWidthOH;
	d->NGSizeIL			=ThreshBag.NGSizeIL;
	d->NGSizeIH			=ThreshBag.NGSizeIH;
	d->NGSizeOL			=ThreshBag.NGSizeOL;
	d->NGSizeOH			=ThreshBag.NGSizeOH;
	d->TransitDot		=ThreshBag.TransitDot;
	d->SearchDot		=ThreshBag.SearchDot;
	d->AdjustBrightIL	=ThreshBag.AdjustBrightIL;
	d->AdjustBrightIH	=ThreshBag.AdjustBrightIH;
	d->AdjustBrightOL	=ThreshBag.AdjustBrightOL;
	d->AdjustBrightOH	=ThreshBag.AdjustBrightOH;
	d->GlobalSearchDot	=ThreshBag.GlobalSearchDot;

	d->PointMove.ModeEnabled				=ThreshBag.PointMove.ModeEnabled;
	d->PointMove.ModeAbsoluteBright			=ThreshBag.PointMove.ModeAbsoluteBright;
	d->PointMove.ModeCenterBrightFromParts	=ThreshBag.PointMove.ModeCenterBrightFromParts;
	d->PointMove.ModeDynamicMask			=ThreshBag.PointMove.ModeDynamicMask;
	d->PointMove.ModeUseRegularBrightness	=ThreshBag.PointMove.ModeUseRegularBrightness;

	d->RegulatedColI	=ThreshBag.RegulatedColI;
	d->RegulatedColO	=ThreshBag.RegulatedColO;
	d->AngleNumb		=AngleNumb;
}

//===========================================================================================

ExeResult	LinePatternItemPointerListContainer::ExecuteProcessing		(int ExeID ,bool ThreadMode)
{
	int	Mx=0,My=0;
	ExecuteProcessingTryMatch(Mx ,My);
	for(LinePatternItemPointerList *L=NPListPack<LinePatternItemPointerList>::GetFirst();L!=NULL;L=L->GetNext()){
		L->GetItem()->ResultGlobalShiftX=Mx;
		L->GetItem()->ResultGlobalShiftY=My;
	}
	return _ER_true;
}
void	LinePatternItemPointerListContainer::ExecuteProcessingTryMatch(int &ShiftX ,int &ShiftY ,int GlobalSearchDot)
{
	LinePatternItemPointerList *L=NPListPack<LinePatternItemPointerList>::GetFirst();
	if(L==NULL)
		return;
	if(GlobalSearchDot<0){
		GlobalSearchDot=L->GetItem()->GetThresholdR(NULL)->ThreshBag.GlobalSearchDot;
	}
	double	DMax=0;
	int		Mx=0;
	int		My=0;

	struct	LinePatternShiftInfo	*ShiftXY=new struct	LinePatternShiftInfo[(2*GlobalSearchDot+1)*(2*GlobalSearchDot+1)+9];
	int	n=0;
	for(int dy=-GlobalSearchDot;dy<=GlobalSearchDot;dy+=2){
		for(int dx=-GlobalSearchDot;dx<=GlobalSearchDot;dx+=2){
			ShiftXY[n].Dx=dx;
			ShiftXY[n].Dy=dy;
			n++;
		}
	}
	int	NCount=NPListPack<LinePatternItemPointerList>::GetCount();
	int	NSep=NCount/25;
	if(NSep==0)
		NSep=1;

	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int i=0;i<n;i++){
			int	dx=ShiftXY[i].Dx;
			int	dy=ShiftXY[i].Dy;
			double	DSum=0;
			int	K=0;
			for(LinePatternItemPointerList *L=NPListPack<LinePatternItemPointerList>::GetFirst();L!=NULL;L=L->GetNext(),K++){
				if((K%NSep)==0){
					double	D=L->GetItem()->TryToMatchRough(dx ,dy,0);
					DSum+=D;
				}
			}
			ShiftXY[i].MatchResult=DSum;
		}
	}
	QSort(ShiftXY,n,sizeof(LinePatternShiftInfo),SortLinePatternShiftInfo);
	DMax=0;
	int		Rx=0;
	int		Ry=0;
	int		MaxIndex=0;
	if(n>10)
		n=10;

	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int i=0;i<n;i++){
			int	Mx=ShiftXY[i].Dx;
			int	My=ShiftXY[i].Dy;
			for(int dy=-1;dy<=1;dy++){
				for(int dx=-1;dx<=1;dx++){
					double	DSum=0;
					for(LinePatternItemPointerList *L=NPListPack<LinePatternItemPointerList>::GetFirst();L!=NULL;L=L->GetNext()){
						double	D=L->GetItem()->TryToMatch(Mx+dx ,My+dy,0);
						DSum+=D;
					}
					#pragma omp critical
					{
						if(DMax<DSum){
							DMax=DSum;
							Rx=dx;
							Ry=dy;
							MaxIndex=i;
						}
					}
				}
			}
		}
	}
	ShiftX=ShiftXY[MaxIndex].Dx+Rx;
	ShiftY=ShiftXY[MaxIndex].Dy+Ry;

	delete	[]ShiftXY;
}


LinePatternExecutablePointerList::LinePatternExecutablePointerList(void)
{
	Container	=NULL;
	ParentLayer	=NULL;
}
LinePatternExecutablePointerList::~LinePatternExecutablePointerList(void)
{
}

void	LinePatternExecutablePointerList::ExecuteInitialAfterEdit	(int ExeID 
																	,ResultInLayerRoot *Res
																	,ExecuteInitialAfterEditInfo &EInfo)
{
	LinePatternLibrary	*LibP=dynamic_cast<LinePatternLibrary *>(ParentLayer->GetParentBase()->FindLibFromManagedCacheLib(LibID));
	if(LibP==NULL){
		ParentLayer->GetParentBase()->LoadAllManagedCacheLib();
		LibP=dynamic_cast<LinePatternLibrary *>(ParentLayer->GetParentBase()->FindLibFromManagedCacheLib(LibID));
	}
	if(LibP!=NULL){
		int	x1,y1,x2,y2;
		int	MinX= 99999999;
		int	MinY= 99999999;
		int	MaxX=-99999999;
		int	MaxY=-99999999;
		for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;p=p->GetNext()){
			p->GetItem()->GetXY(x1,y1,x2,y2);
			MinX=min(MinX,x1);
			MinY=min(MinY,y1);
			MaxX=max(MinX,x2);
			MaxY=max(MinY,y2);
		}
		GroupContainer.RemoveAll();
		int	W=MaxX-MinX;
		int	H=MaxY-MinY;
		int	WNumb=(W+LibP->GlobalSize-1)/LibP->GlobalSize;
		int	HNumb=(H+LibP->GlobalSize-1)/LibP->GlobalSize;
		int	WLen=W/WNumb;
		int	HLen=H/HNumb;
		for(int xi=0;xi<WNumb;xi++){
			for(int yi=0;yi<HNumb;yi++){
				LinePatternItemPointerListContainer	*H=new LinePatternItemPointerListContainer();
				H->xn=xi;
				H->yn=yi;
				int	rx1=MinX+xi*WLen;
				int	ry1=MinY+yi*HLen;
				int	rx2=MinX+(xi+1)*WLen;
				int	ry2=MinY+(yi+1)*HLen;
				for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetItem()->GetXY(x1,y1,x2,y2);
					int	cx=(x1+x2)/2;
					int	cy=(y1+y2)/2;
					if(rx1<=cx && cx<rx2 && ry1<=cy && cy<ry2){
						H->Add((LinePatternItem *)p->GetItem());
					}
				}
				GroupContainer.AppendList(H);
			}
		}
	}
}
void		LinePatternExecutablePointerList::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
}

void	LinePatternExecutablePointerList::MakeDynamicMask(void)
{
	/*
	if(ParentLayer->IndexDynamicMaskMap!=NULL && DynamicMaskMap!=NULL){
		MatrixBuffCopy(DynamicMaskMap	,DynamicMaskMapXByte,DynamicMaskMapYLen
					,(const BYTE **)ParentLayer->IndexDynamicMaskMap ,ParentLayer->IndexDynamicMaskMapXByte,ParentLayer->IndexDynamicMaskMapYLen);
	}
	if(DynamicMaskMap!=NULL){
		for(AlgorithmItemPointerList *p=MaskLinkedItems.GetFirst();p!=NULL;p=p->GetNext()){
			LinePatternItem	*BI=(LinePatternItem *)p->GetItem();
			int	ShiftByAlignmentX,ShiftByAlignmentY;
			BI->GetShiftByAlignemnt(ShiftByAlignmentX,ShiftByAlignmentY);
			int	ShiftByCommonX	=BI->ShiftX;
			int	ShiftByCommonY	=BI->ShiftY;
			int	sx,sy;
			BI->GetCurrentResult()->GetTotalShifted(sx,sy);
			BI->FLineBeforeShrink.MakeBitData(DynamicMaskMap,sx,sy,DynamicMaskMapXByte*8,DynamicMaskMapYLen);
		}
		ParentLayer->DynamicMaskMap		=DynamicMaskMap;
		ParentLayer->DynamicMaskMapXByte=DynamicMaskMapXByte;
		ParentLayer->DynamicMaskMapYLen	=DynamicMaskMapYLen;
	}
	else{
		ParentLayer->DynamicMaskMap		=ParentLayer->IndexDynamicMaskMap;
		ParentLayer->DynamicMaskMapXByte=ParentLayer->IndexDynamicMaskMapXByte;
		ParentLayer->DynamicMaskMapYLen	=ParentLayer->IndexDynamicMaskMapYLen;
	}
	*/
}
ExeResult	LinePatternExecutablePointerList::ExecuteProcessing		(int ExeID ,bool ThreadMode)
{
	DWORD	StartMilisec=ParentLayer->GetLayersBase()->GetStartInspectionTimeMilisec();
	int		MaxInspectMilisec=ParentLayer->GetParamGlobal()->MaxInspectMilisec;

	for(LinePatternItemPointerListContainer *L=GroupContainer.GetFirst();L!=NULL;L=L->GetNext()){
		DWORD	NowTime=::GetComputerMiliSec();
		if(ParentLayer->GetNGCounter()<=ParentLayer->GetParamGlobal()->MaxNGCountsPerCam
		&& NowTime-StartMilisec<=MaxInspectMilisec){
			L->ExecuteProcessing		(ExeID ,ThreadMode);
		}
	}
	return _ER_true;
}
bool	LinePatternExecutablePointerList::IsLinkedToMask(AlgorithmItemRoot *Item)
{
	if(MaskLinkedLibList.IsInclude(Item->GetLibID())==true)
		return true;
	return false;
}

bool	LinePatternItemPointerListContainer::IsInclude(int ItemID)
{
	for(LinePatternItemPointerList *L=NPListPack<LinePatternItemPointerList>::GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetItem()->GetID()==ItemID){
			return true;
		}
	}
	return false;
}
void	LinePatternExecutablePointerContainer::ExecuteInitialAfterEdit	(int ExeID 
																		,ResultInLayerRoot *Res
																		,ExecuteInitialAfterEditInfo &EInfo)
{
	for(LinePatternExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		E->ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	}
}
void		LinePatternExecutablePointerContainer::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	for(LinePatternExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		E->ExecuteStartByInspection(ExeID ,Res);
	}
}
ExeResult	LinePatternExecutablePointerContainer::ExecuteProcessing		(int ExeID ,bool ThreadMode)
{
	ExeResult	Ret=_ER_true;
	for(LinePatternExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		ExeResult	tRet;
		if((tRet=E->ExecuteProcessing(ExeID ,ThreadMode))!=_ER_true){
			Ret=tRet;
		}
	}
	return Ret;
}
bool	LinePatternExecutablePointerContainer::IsLinkedToMask(AlgorithmItemRoot *Item)
{
	for(LinePatternExecutablePointerList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->IsLinkedToMask(Item)==true)
			return true;
	}
	return false;
}
LinePatternExecutablePointerList	*LinePatternExecutablePointerContainer::FindItem(AlgorithmItemRoot *Item)
{
	for(LinePatternExecutablePointerList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ItemPointer.IsExist(Item)==true)
			return p;
	}
	return NULL;
}
LinePatternExecutablePointerList	*LinePatternExecutablePointerContainer::FindByLibID(int LibID)
{
	for(LinePatternExecutablePointerList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->LibID==LibID)
			return p;
	}
	return NULL;
}
//===========================================================================================

LinePatternInLayer::LinePatternInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLI(parent)
	,ExecutableContainer(this)
{
	IndexDynamicMaskMap		=NULL;
	IndexDynamicMaskMapXByte=0;
	IndexDynamicMaskMapYLen	=0;
	DynamicMaskMap			=NULL;
	DynamicMaskMapXByte		=0;
	DynamicMaskMapYLen		=0;
	ModeParallel.ModeParallelExecuteInitialAfterEdit	=true;
}
LinePatternInLayer::~LinePatternInLayer(void)
{
	IndexDynamicMaskMap		=NULL;		//This is only pointer. So memory doesn't leak
	IndexDynamicMaskMapXByte=0;
	IndexDynamicMaskMapYLen	=0;

	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}
void	LinePatternInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddLinePatternItemPacket	*CmdAddLinePatternItemVar=dynamic_cast<CmdAddLinePatternItemPacket *>(packet);
	if(CmdAddLinePatternItemVar!=NULL){
		AlgorithmItemRoot	*Item=CreateItem(0);
		Item->SetArea(CmdAddLinePatternItemVar->Area);
		Item->SetLibID(CmdAddLinePatternItemVar->LibID);
		LinePatternBase	*BBase=(LinePatternBase *)GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(CmdAddLinePatternItemVar->LibID,LLib)==true){
			((LinePatternItem *)Item)->CopyThresholdFromLibrary(&LLib);
			if(AppendItem(Item)==false){
				delete	Item;
			}
		}
		else{
			delete	Item;
		}
		return;
	}
	CmdAddByteLinePatternItemPacket	*CmdAddByteLinePatternItemPacketVar=dynamic_cast<CmdAddByteLinePatternItemPacket *>(packet);
	if(CmdAddByteLinePatternItemPacketVar!=NULL){
		QBuffer	MBuff(&CmdAddByteLinePatternItemPacketVar->Buff);
		MBuff.open(QIODevice::ReadWrite);

		AlgorithmItemRoot	*Item=CreateItem(0);
		Item->Load(&MBuff,GetLayersBase());
		if(CmdAddByteLinePatternItemPacketVar->Vector!=NULL){
			Item->SetVector(*CmdAddByteLinePatternItemPacketVar->Vector);
		}

		Item->SetManualCreated(true);
		Item->SetLibID(CmdAddByteLinePatternItemPacketVar->SelectedLibID);
		Item->SetItemName(CmdAddByteLinePatternItemPacketVar->ItemName);
		AppendItem(Item);
		return;
	}
	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			LinePatternItem	*a=dynamic_cast<LinePatternItem *>(k);
			if(a!=NULL){
				LinePatternListForPacket	*k=new LinePatternListForPacket();
				k->ItemID	=a->GetID();
				k->Page		=a->GetPage();
				k->Layer	=a->GetLayer();
				a->GetXY(k->x1,k->y1,k->x2,k->y2);
				k->Angle	=0;
				MakeListPacketVar->ListInfo->AppendList(k);
			}
		}
		return;
	}
	CmdGenerateLinePatternPacket	*CmdGenerateLinePatternPacketVar=dynamic_cast<CmdGenerateLinePatternPacket *>(packet);
	if(CmdGenerateLinePatternPacketVar!=NULL){

	}
	CmdBlockInfoListPacket	*CmdBlockInfoListPacketVar=dynamic_cast<CmdBlockInfoListPacket *>(packet);
	if(CmdBlockInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			BlockInfoList	*a;
			for(a=CmdBlockInfoListPacketVar->BlockInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->BlockCount.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new BlockInfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					if(layer==GetLayer())
						a->BlockCount.Add(1);
					else
						a->BlockCount.Add(0);
				}
				CmdBlockInfoListPacketVar->BlockInfos->AppendList(a);
			}
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		LinePatternItem *Item=(LinePatternItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			int	tIndex=CmdAlgoSimulateVar->ResultAngleNumber;
			if(tIndex>=Item->AreaNumb)
				tIndex=Item->AreaNumb-1;
			if(CmdAlgoSimulateVar->ModeShowArea==true){
				QColor	Col=Qt::green;
				Col.setAlpha(100);
				Item->GetArea().DrawAlpha(
						// CmdAlgoSimulateVar->ResultGlobalShiftX+Item->ResultShiftX,CmdAlgoSimulateVar->ResultGlobalShiftY+Item->ResultShiftY 
						 CmdAlgoSimulateVar->ResultGlobalShiftX,CmdAlgoSimulateVar->ResultGlobalShiftY 
						,CmdAlgoSimulateVar->Image ,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
			if(CmdAlgoSimulateVar->ModeShowInside==true){
				QColor	Col=Qt::yellow;
				Col.setAlpha(100);
				Item->InsideAreaDim[tIndex].DrawAlpha(
						// CmdAlgoSimulateVar->ResultGlobalShiftX+Item->ResultShiftX,CmdAlgoSimulateVar->ResultGlobalShiftY+Item->ResultShiftY
						 CmdAlgoSimulateVar->ResultGlobalShiftX,CmdAlgoSimulateVar->ResultGlobalShiftY 
						,CmdAlgoSimulateVar->Image ,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
			if(CmdAlgoSimulateVar->ModeShowOutside==true){
				QColor	Col=Qt::blue;
				Col.setAlpha(100);
				Item->OutsideAreaDim[tIndex].DrawAlpha(
						// CmdAlgoSimulateVar->ResultGlobalShiftX+Item->ResultShiftX,CmdAlgoSimulateVar->ResultGlobalShiftY+Item->ResultShiftY
						 CmdAlgoSimulateVar->ResultGlobalShiftX,CmdAlgoSimulateVar->ResultGlobalShiftY 
						,CmdAlgoSimulateVar->Image ,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
		}
		return;
	}
	ChangeLinePatternsThresholdCommon	*ChangeLinePatternsThresholdCommonVar=dynamic_cast<ChangeLinePatternsThresholdCommon *>(packet);
	if(ChangeLinePatternsThresholdCommonVar!=NULL){
		SetThresholdLinePatternInfo	ThresholdInfo;
		QBuffer	Buff(&ChangeLinePatternsThresholdCommonVar->InfosData);
		Buff.open(QIODevice::ReadWrite);
		if(ThresholdInfo.Load(&Buff)==true){
			for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
				if(ChangeLinePatternsThresholdCommonVar->LinePatternLibID==L->GetLibID()){
					LinePatternItem	*B=(LinePatternItem *)L;
					B->SetThresholdFromCommon(&ThresholdInfo);
				}
			}
		}
		return;
	}
	CmdRemoveAllOriginalLinePatternItems	*CmdRemoveAllOriginalLinePatternItemsVar=dynamic_cast<CmdRemoveAllOriginalLinePatternItems *>(packet);
	if(CmdRemoveAllOriginalLinePatternItemsVar!=NULL){
		AlgorithmItemPointerListContainer Items;
		EnumOriginTypeItems((OriginType)CmdRemoveAllOriginalLinePatternItemsVar->GeneratedOrigin,Items);
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
			AlgorithmItemPointerList *NextP=a->GetNext();
			if(a->GetItem()->GetEditLocked()==true){
				Items.RemoveList(a);
				delete	a;
			}
			a=NextP;
		}
		RemoveItems(Items);
		return;
	}
}

void	LinePatternInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		LinePatternItem	*BI=(LinePatternItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
void	LinePatternInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		Item->SetItemName(ItemName);
	}
}

ExeResult	LinePatternInLayer::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInLayerRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{	
	IndexDynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	IndexDynamicMaskMapXByte=GetDataInPage()->GetDynamicMaskMapXByte();
	IndexDynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	DynamicMaskMap		=IndexDynamicMaskMap;
	DynamicMaskMapXByte	=IndexDynamicMaskMapXByte;
	DynamicMaskMapYLen	=IndexDynamicMaskMapYLen;

	LinePatternBase	*BBase=dynamic_cast<LinePatternBase *>(GetParentBase());

	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);

	ExecutableContainer.RemoveAll();
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		LinePatternItem	*Item=dynamic_cast<LinePatternItem *>(L);

		if(Item!=NULL){
			LinePatternExecutablePointerList	*W=ExecutableContainer.FindByLibID(L->GetLibID());
			if(W==NULL){
				W=new LinePatternExecutablePointerList();
				W->ParentLayer	=this;
				W->LibID		=L->GetLibID();
				W->Container	=&ExecutableContainer;
				ExecutableContainer.AppendList(W);
			}
			W->ItemPointer.Add(L);
		}
	}

	//LinePatternExecutablePointerList	*W=new LinePatternExecutablePointerList();
	//W->ParentLayer	=this;
	//W->Container	=&ExecutableContainer;
	//for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
	//	W->ItemPointer.Add(L);
	//}
	//ExecutableContainer.AppendList(W);
	ExecutableContainer.ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	return Ret;
}
ExeResult	LinePatternInLayer::ExecuteProcessing		(int ExeID ,ResultInLayerRoot *Res)
{
	for(LinePatternExecutablePointerList *p=ExecutableContainer.GetFirst();p!=NULL;p=p->GetNext()){
		p->ExecuteProcessing(ExeID ,true);
	}
	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteProcessing		(ExeID ,Res);
	return _ER_true;
}
void	LinePatternInLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		LinePatternItem	*a=dynamic_cast<LinePatternItem *>(k);
		if(a!=NULL){
			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}
	}
}

bool	LinePatternInLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}

LinePatternItemPointerListContainer	*LinePatternInLayer::FindGroup(int ItemID)
{
	for(LinePatternExecutablePointerList *L=ExecutableContainer.GetFirst();L!=NULL;L=L->GetNext()){
		for(LinePatternItemPointerListContainer *a=L->GroupContainer.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(ItemID)==true)
				return a;
		}
	}
	return NULL;
}

//=====================================================================

LinePatternInPage::LinePatternInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLI(parent)
{
}

void	LinePatternInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddLinePatternItemPacket	*CmdAddLinePatternItemVar=dynamic_cast<CmdAddLinePatternItemPacket *>(packet);
	if(CmdAddLinePatternItemVar!=NULL){
		for(IntClass *L=CmdAddLinePatternItemVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			AL->TransmitDirectly(packet);
		}
		return;
	}
	CmdAddByteLinePatternItemPacket	*CmdAddByteLinePatternItemPacketVar=dynamic_cast<CmdAddByteLinePatternItemPacket *>(packet);
	if(CmdAddByteLinePatternItemPacketVar!=NULL){
		for(IntClass *L=CmdAddByteLinePatternItemPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			AL->TransmitDirectly(packet);
		}
		return;
	}
	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			AL->TransmitDirectly(packet);
		}
		return;

	}
	CmdGenerateLinePatternPacket	*CmdGenerateLinePatternPacketVar=dynamic_cast<CmdGenerateLinePatternPacket *>(packet);
	if(CmdGenerateLinePatternPacketVar!=NULL){
		for(IntClass *L=CmdGenerateLinePatternPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			AL->TransmitDirectly(packet);
		}
		return;
	}
	CmdBlockInfoListPacket	*CmdBlockInfoListPacketVar=dynamic_cast<CmdBlockInfoListPacket *>(packet);
	if(CmdBlockInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdBlockInfoListPacketVar);
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdRemoveAllOriginalLinePatternItems	*CmdRemoveAllOriginalLinePatternItemsVar=dynamic_cast<CmdRemoveAllOriginalLinePatternItems *>(packet);
	if(CmdRemoveAllOriginalLinePatternItemsVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
}
bool	LinePatternInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_InitialBmpMap){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmItemPointerListContainer Items;
			GetLayerData(layer)->EnumOriginTypeItems(Info.OperationOrigin,Items);
			for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
				AlgorithmItemPointerList *NextP=a->GetNext();
				if(a->GetItem()->GetEditLocked()==true){
					Items.RemoveList(a);
					delete	a;
				}
				a=NextP;
			}
			GetLayerData(layer)->RemoveItems(Items);
		}
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){
		//GetParentBase()->LoadAllManagedCacheLib();
		GetParentBase()->LoadManagedCacheLib(Info.LibID);
		LinePatternLibrary	*TmpLib=(LinePatternLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			for(int layer=0;layer<GetLayerNumb();layer++){
				NPListPack<AlgorithmItemPLI>	TmpLinePatternData;
				if(TmpLib->HasGenLayer(layer)==true){
					LinePatternInLayer	*BL=(LinePatternInLayer*)GetLayerData(layer);

					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					ConstMapBuffer MaskMap;
					BL->GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib);

					bool	LimitedMaskInOtherPage=BL->UseLibraryForMaskingInOtherPage(TmpLib->GetLibID());
					bool	LimitedMaskInThisPage =BL->IncludeLibInReflection(_Reflection_Mask,TmpLib,NULL);
					if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
						MatrixBuffAnd	(TmpData ,MaskMap.GetBitMap() ,Info.XByte ,Info.YLen);
						
						if(Info.Something.count()>0){
							QBuffer	tBuff(&Info.Something);
							tBuff.open(QIODevice::ReadOnly);

							int32	AlgoCount;
							if(::Load(&tBuff,AlgoCount)==false){
								DeleteMatrixBuff(TmpData,Info.YLen);
								return false;
							}
							QByteArray	DataArray;
							bool		Found=false;
							for(int i=0;i<AlgoCount;i++){
								QString	AlgoName;
								if(::Load(&tBuff,AlgoName)==false){
									DeleteMatrixBuff(TmpData,Info.YLen);
									return false;
								}
								if(::Load(&tBuff,DataArray)==false){
									DeleteMatrixBuff(TmpData,Info.YLen);
									return false;
								}
								if(AlgoName==/**/"LinePattern"){
									Found=true;
									break;
								}
							}
							if(Found==true){
								QBuffer	Buff(&DataArray);
								Buff.open(QIODevice::ReadOnly);

								SetThresholdLinePatternInfo	ThresholdLinePatternInfoData;
								if(ThresholdLinePatternInfoData.Load(&Buff)==true){
									//TmpLib->SpaceToOutline	= 0;
									TmpLib->MakeLinePatternOnly(GetPage()
														,TmpData,MaskMap.GetBitMap(),Info.DriftMap
														,Info.XByte 
														,Info.XByte*8,Info.YLen
														,TmpLinePatternData
														,((LinePatternBase *)GetParentBase())->OmitZoneDot);
									for(AlgorithmItemPLI *aq=TmpLinePatternData.GetFirst();aq!=NULL;aq=aq->GetNext()){
										LinePatternItem	*BItem=dynamic_cast<LinePatternItem *>(aq);
										if(BItem!=NULL){	
											BItem->SetThresholdFromCommon(&ThresholdLinePatternInfoData);
										}
									}
								}
							}
						}
						else{
							TmpLib->MakeLinePatternOnly(GetPage()
												,TmpData,MaskMap.GetBitMap(),Info.DriftMap
												,Info.XByte 
												,Info.XByte*8,Info.YLen
												,TmpLinePatternData
												,((LinePatternBase *)GetParentBase())->OmitZoneDot);
						}

						AlgorithmItemPLI	*q;
						while((q=TmpLinePatternData.GetFirst())!=NULL){
							TmpLinePatternData.RemoveList(q);
							q->SetOriginType(Info.OperationOrigin);
							q->SetOrigin(Info.Origin);
							BL->AppendItem(q);
							//((LinePatternItem *)q)->MakeFLineBeforeShrink(*TmpLib,Info.BmpMap,Info.XByte ,Info.XByte*8,Info.YLen);
							//((LinePatternItem *)q)->MakeOmitArea(Info.OmitMap,Info.XByte ,Info.YLen);
						}
					}
					DeleteMatrixBuff(TmpData,Info.YLen);
					ManualExecuteAll(GetParentBase()->GetManualExecuter());
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(int layer=0;layer<GetLayerNumb();layer++){
			LinePatternInLayer	*L=(LinePatternInLayer *)GetLayerData(layer);
			L->MoveFromPipe(Info);
		}
		return true;
	}

	return false;
}
//=====================================================================
LinePatternBase::LinePatternBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	OmitZoneDot		=100;
	MultiplyInAngle	=2.0;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");

	SetParam(&OmitZoneDot		, /**/"Setting"		,/**/"OmitZoneDot"		,"Omit zone dot in block generation");
	SetParam(&MultiplyInAngle	, /**/"Setting"		,/**/"MultiplyInAngle"	,"Number to multiply in Angle");
}

AlgorithmDrawAttr	*LinePatternBase::CreateDrawAttr(void)
{
	return new LinePatternDrawAttr();
}

void	LinePatternBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetLinePatternLibraryListPacket	*AListPacket=dynamic_cast<CmdGetLinePatternLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempLinePatternLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempLinePatternLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadLinePatternLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadLinePatternLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearLinePatternLibraryPacket	*CmdClearLinePatternLibraryPacketVar=dynamic_cast<CmdClearLinePatternLibraryPacket *>(packet);
	if(CmdClearLinePatternLibraryPacketVar!=NULL){
		CmdClearLinePatternLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteLinePatternLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteLinePatternLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertLinePatternLibraryPacket	*BInsLib=dynamic_cast<CmdInsertLinePatternLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(LinePatternVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateLinePatternLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateLinePatternLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(LinePatternVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetLinePatternLibraryNamePacket	*CmdGetLinePatternLibraryNamePacketVar=dynamic_cast<CmdGetLinePatternLibraryNamePacket *>(packet);
	if(CmdGetLinePatternLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetLinePatternLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetLinePatternLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetLinePatternLibraryNamePacketVar->Success==true){
				CmdGetLinePatternLibraryNamePacketVar->LibName=TmpLib.GetLibName();
				GetLibraryContainer()->GetLibraryNames(CmdGetLinePatternLibraryNamePacketVar->AList);
			}
		}
		return;
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
}

bool	LinePatternBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==LinePatternHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==LinePatternHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==LinePatternReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==LinePatternReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==LinePatternReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==LinePatternSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*LinePatternBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==LinePatternHistogramListSendCommand){
		LinePatternHistogramListSend	*pSend=new LinePatternHistogramListSend();
		if(reqData!=NULL){
			LinePatternHistogramListReq	*req=(LinePatternHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==LinePatternHistogramListReqCommand){
		return new LinePatternHistogramListReq();
	}
	else if(Command==LinePatternReqThresholdReqCommand){
		return new LinePatternThresholdReq();
	}
	else if(Command==LinePatternReqThresholdSendCommand){
		LinePatternThresholdSend	*pSend=new LinePatternThresholdSend();
		if(reqData!=NULL){
			LinePatternThresholdReq	*req=(LinePatternThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==LinePatternReqTryThresholdCommand){
		return new LinePatternReqTryThreshold();
	}
	else if(Command==LinePatternSendTryThresholdCommand){
		LinePatternSendTryThreshold	*pSend=new LinePatternSendTryThreshold();
		if(reqData!=NULL){
			LinePatternReqTryThreshold	*req=(LinePatternReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	LinePatternBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==LinePatternHistogramListSendCommand){
		LinePatternHistogramListSend	*p=(LinePatternHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==LinePatternHistogramListReqCommand){
		LinePatternHistogramListReq	*p=(LinePatternHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==LinePatternReqThresholdReqCommand){
		LinePatternThresholdReq	*p=(LinePatternThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==LinePatternReqThresholdSendCommand){
		LinePatternThresholdSend	*p=(LinePatternThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==LinePatternReqTryThresholdCommand){
		LinePatternReqTryThreshold	*p=(LinePatternReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==LinePatternSendTryThresholdCommand){
		LinePatternSendTryThreshold	*p=(LinePatternSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	LinePatternBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==LinePatternHistogramListSendCommand){
		LinePatternHistogramListSend	*p=(LinePatternHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==LinePatternHistogramListReqCommand){
		LinePatternHistogramListReq	*p=(LinePatternHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==LinePatternReqThresholdReqCommand){
		LinePatternThresholdReq	*p=(LinePatternThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==LinePatternReqThresholdSendCommand){
		LinePatternThresholdSend	*p=(LinePatternThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==LinePatternReqTryThresholdCommand){
		LinePatternReqTryThreshold	*p=(LinePatternReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==LinePatternSendTryThresholdCommand){
		LinePatternSendTryThreshold	*p=(LinePatternSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	LinePatternBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==LinePatternHistogramListSendCommand){
		LinePatternHistogramListSend	*p=(LinePatternHistogramListSend *)data;
		return true;
	}
	else if(Command==LinePatternHistogramListReqCommand){
		LinePatternHistogramListReq	*p=(LinePatternHistogramListReq *)data;
		return true;
	}
	else if(Command==LinePatternReqThresholdReqCommand){
		LinePatternThresholdReq	*p=(LinePatternThresholdReq *)data;
		return true;
	}
	else if(Command==LinePatternReqThresholdSendCommand){
		LinePatternThresholdSend	*p=(LinePatternThresholdSend *)data;
		return true;
	}
	else if(Command==LinePatternReqTryThresholdCommand){
		LinePatternReqTryThreshold	*p=(LinePatternReqTryThreshold *)data;
		return true;
	}
	else if(Command==LinePatternSendTryThresholdCommand){
		LinePatternSendTryThreshold	*p=(LinePatternSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	LinePatternBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	ChangeCreateLinePatternForm	Q(this,Layer,GetLayersBase()->GetMainWidget());
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultLinePattern.Save(&Buff)==false)
			return false;
	}
	return ret;
	*/
	return true;
}

//======================================================================

LinePatternHistogramListReq::LinePatternHistogramListReq(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	ItemID	=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;
}
bool	LinePatternHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	LinePatternHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


LinePatternHistogramListSend::LinePatternHistogramListSend(void)
{
	GlobalPage=-1;
	Layer		=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMasterI,0,sizeof(ListMasterI));
	memset(ListTargetI,0,sizeof(ListTargetI));
	memset(ListMasterO,0,sizeof(ListMasterO));
	memset(ListTargetO,0,sizeof(ListTargetO));
	MasterColI=0;
	MasterColO=0;
	TargetColI=0;
	TargetColO=0;
}
void	LinePatternHistogramListSend::ConstructList(LinePatternHistogramListReq *reqPacket,LinePatternBase *Base)
{
	memset(ListMasterI,0,sizeof(ListMasterI));
	memset(ListTargetI,0,sizeof(ListTargetI));
	memset(ListMasterO,0,sizeof(ListMasterO));
	memset(ListTargetO,0,sizeof(ListTargetO));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ItemID		=reqPacket->ItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(ItemID);
				
			LinePatternItem	*Item=dynamic_cast<LinePatternItem*>(item);
			bool	BuiltList=false;
			if(item->IsOriginParts()==true && Item->GetThresholdR(Ap->GetLayersBase())->ThreshBag.PointMove.ModeCenterBrightFromParts==true){
				PieceClass	*Pc=NULL;
				Pc=Base->GetLayersBase()->GetPieceStock()->SearchOnly(item->GetPartsID());
				if(Pc!=NULL){
					QString DLLRoot ,DLLName;
					Base->GetAlgorithmRootName(DLLRoot ,DLLName);
					LinePatternItem	*PItem=dynamic_cast<LinePatternItem *>(Pc->GetAlgorithmItem(DLLRoot,DLLName,Layer ,item->GetPartsItemID()));
					if(PItem!=NULL){
						if(PItem->GetDataInLayer()->GetMasterBuff().IsNull()==false){
							PItem->InsideAreaDim[0] .MakeBrightList(ListMasterI ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetMasterBuff(),0 ,0);
							PItem->OutsideAreaDim[0].MakeBrightList(ListMasterO ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetMasterBuff(),0 ,0);
						}
						else if(PItem->GetDataInLayer()->GetTargetBuff().IsNull()==false){
							PItem->InsideAreaDim[0] .MakeBrightList(ListMasterI ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetTargetBuff(),0 ,0);
							PItem->OutsideAreaDim[0].MakeBrightList(ListMasterO ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetTargetBuff(),0 ,0);
						}
						BuiltList=true;
					}
				}
			}
			if(BuiltList==false){
				if(Item->GetMasterBuff().IsNull()==false){
					Item->InsideAreaDim[0] .MakeBrightList(ListMasterI ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
					Item->OutsideAreaDim[0].MakeBrightList(ListMasterO ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
				}
				else if(Item->GetTargetBuff().IsNull()==false){
					Item->InsideAreaDim[0] .MakeBrightList(ListMasterI ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
					Item->OutsideAreaDim[0].MakeBrightList(ListMasterO ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
				}
			}
				
			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				if(Rp!=NULL){
					ResultInLayerPLI	&rLayer=Rp->GetLayerData(Item->GetParent()->GetLayer());
					ResultInItemPLI		*rItem=rLayer.FindResultInItem(Item->GetID());

					if(rItem!=NULL){
						int	ResultAngleNumber=rItem->GetResult2();
						int	tIndex=ResultAngleNumber;
						if(tIndex>=Item->AreaNumb)
							tIndex=Item->AreaNumb-1;
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						Item->InsideAreaDim[tIndex] .MakeBrightList(ListTargetI ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
						Item->OutsideAreaDim[tIndex].MakeBrightList(ListTargetO ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
					}
					else{
						Item->InsideAreaDim[0] .MakeBrightList(ListTargetI ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
						Item->OutsideAreaDim[0].MakeBrightList(ListTargetO ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
					}
				}
				
				MasterColI=Item->MasterColI;
				MasterColO=Item->MasterColO;
				TargetColI=Item->CalcTargetColI;
				TargetColO=Item->CalcTargetColO;
			}
		}
	}
}

bool	LinePatternHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(f->write((const char *)ListMasterI,sizeof(ListMasterI))!=sizeof(ListMasterI))
		return false;
	if(f->write((const char *)ListTargetI,sizeof(ListTargetI))!=sizeof(ListTargetI))
		return false;
	if(f->write((const char *)ListMasterO,sizeof(ListMasterO))!=sizeof(ListMasterO))
		return false;
	if(f->write((const char *)ListTargetO,sizeof(ListTargetO))!=sizeof(ListTargetO))
		return false;
	if(::Save(f,MasterColI)==false)
		return false;
	if(::Save(f,MasterColO)==false)
		return false;
	if(::Save(f,TargetColI)==false)
		return false;
	if(::Save(f,TargetColO)==false)
		return false;
	return true;
}
bool	LinePatternHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(f->read((char *)ListMasterI,sizeof(ListMasterI))!=sizeof(ListMasterI))
		return false;
	if(f->read((char *)ListTargetI,sizeof(ListTargetI))!=sizeof(ListTargetI))
		return false;
	if(f->read((char *)ListMasterO,sizeof(ListMasterO))!=sizeof(ListMasterO))
		return false;
	if(f->read((char *)ListTargetO,sizeof(ListTargetO))!=sizeof(ListTargetO))
		return false;
	if(::Load(f,MasterColI)==false)
		return false;
	if(::Load(f,MasterColO)==false)
		return false;
	if(::Load(f,TargetColI)==false)
		return false;
	if(::Load(f,TargetColO)==false)
		return false;
	return true;
}
//======================================================================
LinePatternThresholdReq::LinePatternThresholdReq(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Layer		=-1;
	Mastered	=true;
	Dx			=0;
	Dy			=0;
}

bool	LinePatternThresholdReq::Save(QIODevice *f)
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

bool	LinePatternThresholdReq::Load(QIODevice *f)
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

LinePatternThresholdSend::LinePatternThresholdSend(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Layer		=-1;
	Dx			=0;
	Dy			=0;
	BrightWidthIL	=0;
	BrightWidthIH	=0;
	BrightWidthOL	=0;
	BrightWidthOH	=0;
	NGSizeIL		=0;
	NGSizeIH		=0;
	NGSizeOL		=0;
	NGSizeOH		=0;
	TransitDot		=0;
	SearchDot		=0;
	AdjustBrightIL	=0;
	AdjustBrightIH	=0;
	AdjustBrightOL	=0;
	AdjustBrightOH	=0;
	GlobalSearchDot	=0;
	ModeEnabled					=true;
	ModeAbsoluteBright			=true;
	ModeCenterBrightFromParts	=true;
	ModeDynamicMask				=true;
	ModeUseRegularBrightness	=true;
	RegulatedColI	=0;
	RegulatedColO	=0;
	AngleNumb		=1;
}

void	LinePatternThresholdSend::ConstructList(LinePatternThresholdReq *reqPacket,LinePatternBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ItemID		=reqPacket->ItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ItemID);
			if(item!=NULL){
				LinePatternItem	*Item=dynamic_cast<LinePatternItem*>(item);

				const LinePatternThreshold	*RThr=Item->GetThresholdR(Ap->GetLayersBase());
				BrightWidthIL	=RThr->ThreshBag.BrightWidthIL	;
				BrightWidthIH	=RThr->ThreshBag.BrightWidthIH	;
				BrightWidthOL	=RThr->ThreshBag.BrightWidthOL	;
				BrightWidthOH	=RThr->ThreshBag.BrightWidthOH	;
				NGSizeIL		=RThr->ThreshBag.NGSizeIL		;
				NGSizeIH		=RThr->ThreshBag.NGSizeIH		;
				NGSizeOL		=RThr->ThreshBag.NGSizeOL		;
				NGSizeOH		=RThr->ThreshBag.NGSizeOH		;
				TransitDot		=RThr->ThreshBag.TransitDot	;	
				SearchDot		=RThr->ThreshBag.SearchDot		;
				AdjustBrightIL	=RThr->ThreshBag.AdjustBrightIL;	
				AdjustBrightIH	=RThr->ThreshBag.AdjustBrightIH;	
				AdjustBrightOL	=RThr->ThreshBag.AdjustBrightOL;	
				AdjustBrightOH	=RThr->ThreshBag.AdjustBrightOH;	
				GlobalSearchDot	=RThr->ThreshBag.GlobalSearchDot;	

				ModeEnabled					=RThr->ThreshBag.PointMove.ModeEnabled					;
				ModeAbsoluteBright			=RThr->ThreshBag.PointMove.ModeAbsoluteBright			;
				ModeCenterBrightFromParts	=RThr->ThreshBag.PointMove.ModeCenterBrightFromParts	;
				ModeDynamicMask				=RThr->ThreshBag.PointMove.ModeDynamicMask				;
				ModeUseRegularBrightness	=RThr->ThreshBag.PointMove.ModeUseRegularBrightness	;

				RegulatedColI	=RThr->ThreshBag.RegulatedColI;	
				RegulatedColO	=RThr->ThreshBag.RegulatedColO;	
				AngleNumb		=RThr->AngleNumb;
			}
		}
	}
}
	
bool	LinePatternThresholdSend::Save(QIODevice *f)
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
	if(::Save(f,BrightWidthIL)==false)
		return false;
	if(::Save(f,BrightWidthIH)==false)
		return false;
	if(::Save(f,BrightWidthOL)==false)
		return false;
	if(::Save(f,BrightWidthOH)==false)
		return false;
	if(::Save(f,NGSizeIL)==false)
		return false;
	if(::Save(f,NGSizeIH)==false)
		return false;
	if(::Save(f,NGSizeOL)==false)
		return false;
	if(::Save(f,NGSizeOH)==false)
		return false;
	if(::Save(f,TransitDot)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,AdjustBrightIL)==false)
		return false;
	if(::Save(f,AdjustBrightIH)==false)
		return false;
	if(::Save(f,AdjustBrightOL)==false)
		return false;
	if(::Save(f,AdjustBrightOH)==false)
		return false;
	if(::Save(f,GlobalSearchDot)==false)
		return false;
	if(::Save(f,ModeEnabled)==false)
		return false;
	if(::Save(f,ModeAbsoluteBright)==false)
		return false;
	if(::Save(f,ModeCenterBrightFromParts)==false)
		return false;
	if(::Save(f,ModeDynamicMask)==false)
		return false;
	if(::Save(f,ModeUseRegularBrightness)==false)
		return false;
	if(::Save(f,RegulatedColI)==false)
		return false;
	if(::Save(f,RegulatedColO)==false)
		return false;
	if(::Save(f,AngleNumb)==false)
		return false;

	return true;
}
	
bool	LinePatternThresholdSend::Load(QIODevice *f)
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
	if(::Load(f,BrightWidthIL)==false)
		return false;
	if(::Load(f,BrightWidthIH)==false)
		return false;
	if(::Load(f,BrightWidthOL)==false)
		return false;
	if(::Load(f,BrightWidthOH)==false)
		return false;
	if(::Load(f,NGSizeIL)==false)
		return false;
	if(::Load(f,NGSizeIH)==false)
		return false;
	if(::Load(f,NGSizeOL)==false)
		return false;
	if(::Load(f,NGSizeOH)==false)
		return false;
	if(::Load(f,TransitDot)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,AdjustBrightIL)==false)
		return false;
	if(::Load(f,AdjustBrightIH)==false)
		return false;
	if(::Load(f,AdjustBrightOL)==false)
		return false;
	if(::Load(f,AdjustBrightOH)==false)
		return false;
	if(::Load(f,GlobalSearchDot)==false)
		return false;
	if(::Load(f,ModeEnabled)==false)
		return false;
	if(::Load(f,ModeAbsoluteBright)==false)
		return false;
	if(::Load(f,ModeCenterBrightFromParts)==false)
		return false;
	if(::Load(f,ModeDynamicMask)==false)
		return false;
	if(::Load(f,ModeUseRegularBrightness)==false)
		return false;
	if(::Load(f,RegulatedColI)==false)
		return false;
	if(::Load(f,RegulatedColO)==false)
		return false;
	if(::Load(f,AngleNumb)==false)
		return false;

	return true;
}
//====================================================================================

LinePatternReqTryThreshold::LinePatternReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	LinePatternItemID=-1;
}
bool	LinePatternReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,LinePatternItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	LinePatternReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,LinePatternItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

LinePatternSendTryThreshold::LinePatternSendTryThreshold(void)
{
	NGDotIL			=0;
	NGDotIH			=0;
	NGDotOL			=0;
	NGDotOH			=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
	Error			=0;
	Result	=new ResultInItemPLI();
}
LinePatternSendTryThreshold::~LinePatternSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}


bool	LinePatternSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotIL	)==false)
		return false;
	if(::Save(f,NGDotIH	)==false)
		return false;
	if(::Save(f,NGDotOL	)==false)
		return false;
	if(::Save(f,NGDotOH	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,AlignedX)==false)
		return false;
	if(::Save(f,AlignedY)==false)
		return false;
	if(::Save(f,ShiftByCommonX)==false)
		return false;
	if(::Save(f,ShiftByCommonY)==false)
		return false;
	if(::Save(f,ShiftBySelfX)==false)
		return false;
	if(::Save(f,ShiftBySelfY)==false)
		return false;
	if(::Save(f,ResultAngle)==false)
		return false;
	return true;
}
bool	LinePatternSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotIL	)==false)
		return false;
	if(::Load(f,NGDotIH	)==false)
		return false;
	if(::Load(f,NGDotOL	)==false)
		return false;
	if(::Load(f,NGDotOH	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,AlignedX)==false)
		return false;
	if(::Load(f,AlignedY)==false)
		return false;
	if(::Load(f,ShiftByCommonX)==false)
		return false;
	if(::Load(f,ShiftByCommonY)==false)
		return false;
	if(::Load(f,ShiftBySelfX)==false)
		return false;
	if(::Load(f,ShiftBySelfY)==false)
		return false;
	if(::Load(f,ResultAngle)==false)
		return false;
	return true;
}

void	LinePatternSendTryThreshold::ConstructList(LinePatternReqTryThreshold *reqPacket,LinePatternBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	LinePatternInPage		*BP=(LinePatternInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		LinePatternInLayer	*BL=(LinePatternInLayer *)BP->GetLayerData(reqPacket->Layer);
		if(BL!=NULL){
			LinePatternItem		*BI=(LinePatternItem *)BL->SearchIDItem(reqPacket->LinePatternItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
				if(reqPacket->Threshold.InsideAreaDim!=NULL){
					delete	[]reqPacket->Threshold.InsideAreaDim;
					reqPacket->Threshold.InsideAreaDim=NULL;
				}
				if(reqPacket->Threshold.OutsideAreaDim!=NULL){
					delete	[]reqPacket->Threshold.OutsideAreaDim;
					reqPacket->Threshold.OutsideAreaDim=NULL;
				}
				if(BI->AreaNumb!=0){
					reqPacket->Threshold.AreaNumb	=BI->AreaNumb;
					reqPacket->Threshold.InsideAreaDim	=new FlexArea[reqPacket->Threshold.AreaNumb];
					reqPacket->Threshold.OutsideAreaDim	=new FlexArea[reqPacket->Threshold.AreaNumb];
				}
				for(int i=0;i<reqPacket->Threshold.AreaNumb;i++){
					reqPacket->Threshold.InsideAreaDim[i]	=BI->InsideAreaDim[i];
					reqPacket->Threshold.OutsideAreaDim[i]	=BI->OutsideAreaDim[i];
				}

				reqPacket->Threshold.MasterColI	=BI->MasterColI	;
				reqPacket->Threshold.MasterColO	=BI->MasterColO	;
				reqPacket->Threshold.TargetColI	=BI->TargetColI	;
				reqPacket->Threshold.TargetColO	=BI->TargetColO	;

				//reqPacket->Threshold.GetThresholdW()->CopyFrom(*BI->GetThresholdW());
				reqPacket->Threshold.AVector	=BI->AVector;

				reqPacket->Threshold.ResultGlobalShiftX	=BI->ResultGlobalShiftX;
				reqPacket->Threshold.ResultGlobalShiftY	=BI->ResultGlobalShiftY;
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.SetArea(BI->GetArea());
				LinePatternItemPointerListContainer	*CC=BL->FindGroup(reqPacket->LinePatternItemID);
				if(CC!=NULL){
					ImageBuffer &DBuff=BI->GetTargetBuff();
					int	MaxDx=0;
					int	MaxDy=0;
					CC->ExecuteProcessingTryMatch(MaxDx,MaxDy,reqPacket->Threshold.GetThresholdR()->ThreshBag.GlobalSearchDot);
					reqPacket->Threshold.ResultGlobalShiftX=MaxDx;
					reqPacket->Threshold.ResultGlobalShiftY=MaxDy;
				}
				
				if(reqPacket->ReqAngleNumber<0){
					reqPacket->Threshold.ExecuteProcessing(0,0,Result );
				}
				else{
					reqPacket->Threshold.ExecuteProcessingAngle(0,0,Result ,reqPacket->ReqAngleNumber);
				}
				NGDotIL			=0;
				NGDotIH			=0;
				NGDotOL			=0;
				NGDotOH			=0;
				for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
					if(r->result==0x110000)
						NGDotIL+=r->GetResult1();
					if(r->result==0x120000)
						NGDotIH+=r->GetResult1();
					if(r->result==0x210000)
						NGDotOL+=r->GetResult1();
					if(r->result==0x220000)
						NGDotOH+=r->GetResult1();
				}
				ResultAngle		=Result->GetResult2();
				AlignedX		=Result->GetAlignedX();
				AlignedY		=Result->GetAlignedY();
				ShiftByCommonX	=reqPacket->Threshold.ResultGlobalShiftX;
				ShiftByCommonY	=reqPacket->Threshold.ResultGlobalShiftY;
				ShiftBySelfX	=reqPacket->Threshold.ResultShiftX;
				ShiftBySelfY	=reqPacket->Threshold.ResultShiftY;
			}
		}
	}
	Result->SetAddedData(NULL,0);

	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();
}
