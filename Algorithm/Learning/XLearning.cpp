/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Learning\XLearning.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XLearning.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XCriticalFunc.h"
#include "XLotInformation.h"
#include "XDataAlgorithm.h"
#include "omp.h"


//=====================================================================

LearningRuleThreshold::LearningRuleThreshold(LearningRuleItem *parent)
:AlgorithmThreshold(parent)
{
	NGLevel=100;
}

void	LearningRuleThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const LearningRuleThreshold *s=(const LearningRuleThreshold *)&src;
    NGLevel=s->NGLevel;
}
bool	LearningRuleThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const LearningRuleThreshold *s=(const LearningRuleThreshold *)&src;
	if(NGLevel!=s->NGLevel)	return false;
	return true;
}
bool	LearningRuleThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,Ok)==false)
		return(false);
	if(::Save(file,NGLevel)==false)
		return(false);
	return(true);
}
bool	LearningRuleThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,Ok)==false)
		return(false);
	if(::Load(file,NGLevel)==false)
		return(false);
	return(true);
}

AlgorithmItemPI	&LearningRuleItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    LearningRuleItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    LearningRuleItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	return true;
}

void	LearningRuleItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	LearningRuleDrawAttr *a=dynamic_cast<LearningRuleDrawAttr *>(Attr);
	if(a!=NULL){
		LearningRuleDrawAttr	A=*((LearningRuleDrawAttr *)Attr);
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}


double	LearningRuleItem::GetCalcFromResult(ResultInspection &Res ,int Page)
{
	const LearningRuleThreshold	*RThr=GetThresholdR();
	if(RThr->Ok==true){
		for(ResultBaseForAlgorithmRoot *c=Res.GetResultBaseDimFirst();c!=NULL;c=c->GetNext()){
			ResultBasePhase		*Ph=c->GetPageDataPhase(GetPhaseCode());
			ResultInPageRoot	*p=Ph->GetPageData(Page);
			if(p!=NULL){
				NPListPack<ResultInItemRootPointerList> Ret;
				p->GetNGItemList(Ret ,GetArea());
				if(Ret.GetFirst()!=NULL){
					return 0;
				}
			}
		}
		return 1.0/(double)(RThr->NGLevel+1);
	}
	else{
		for(ResultBaseForAlgorithmRoot *c=Res.GetResultBaseDimFirst();c!=NULL;c=c->GetNext()){
			ResultBasePhase		*Ph=c->GetPageDataPhase(GetPhaseCode());
			ResultInPageRoot	*p=Ph->GetPageData(Page);
			if(p!=NULL){
				NPListPack<ResultInItemRootPointerList> Ret;
				p->GetNGItemList(Ret ,GetArea());
				if(Ret.GetFirst()!=NULL){
					return 1.0/(double)(RThr->NGLevel+1);
				}
			}
		}
		return 0;
	}
}


//===========================================

LearningRuleInPage::LearningRuleInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent),LearningPlanBase(parent->GetLayersBase())
{}

void	LearningRuleInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	LearningAddFilePacket	*LearningAddFilePacketVar=dynamic_cast<LearningAddFilePacket *>(packet);
	if(LearningAddFilePacketVar!=NULL){
		LearningRuleInPage	*c=((LearningRuleBase *)GetParentBase())->LearningRuleInPageStocker[GetPage()].GetItem(LearningAddFilePacketVar->Index);
		if(c==NULL){
			c=(LearningRuleInPage *)((LearningRuleBase *)GetParentBase())->NewChild(GetParentBase());
			c->SetPage(GetPage());
			//c->Initial(AlgorithmInPagePI::GetLayersBase());
			((LearningRuleBase *)GetParentBase())->LearningRuleInPageStocker[GetPage()].InsertList(LearningAddFilePacketVar->Index,c);
		}
		c->FileName=LearningAddFilePacketVar->FileName;
		return;
	}
	LearningReqStoredFileList	*LearningReqStoredFileListVar=dynamic_cast<LearningReqStoredFileList *>(packet);
	if(LearningReqStoredFileListVar!=NULL){
		LearningRuleInPage::MakeFileLists(*LearningReqStoredFileListVar->List
							, LearningReqStoredFileListVar->MasterCode
							, LearningReqStoredFileListVar->LotAutoCount);
		return;
	}
	AddLearningAreaWithAttr	*AddLearningAreaWithAttrVar=dynamic_cast<AddLearningAreaWithAttr *>(packet);
	if(AddLearningAreaWithAttrVar!=NULL){
		LearningRuleItem	*MData=(LearningRuleItem *)CreateItem();
		MData->GetThresholdW()->Ok		=AddLearningAreaWithAttrVar->Ok;
		MData->GetThresholdW()->NGLevel	=AddLearningAreaWithAttrVar->NGLevel;
		MData->SetArea(AddLearningAreaWithAttrVar->Area);
		MData->SetManualCreated(true);
		AppendItem(MData);
		return;
	}
	AlgoLearningAreaListContainer	*AlgoLearningAreaListContainerVar=dynamic_cast<AlgoLearningAreaListContainer *>(packet);
	if(AlgoLearningAreaListContainerVar!=NULL){
		AlgoLearningAreaListContainerVar->List->RemoveAll();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			LearningRuleItem	*L=(LearningRuleItem *)a;
			LearningAreaList	*d=new LearningAreaList();
			const LearningRuleThreshold	*RThr=L->GetThresholdR(AlgorithmInPagePI::GetLayersBase());
			d->GlobalPage	=AlgorithmInPagePI::GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			d->ItemID		=L->GetID();
			d->Ok			=RThr->Ok;
			d->NGLevel		=RThr->NGLevel;
			d->X1=L->GetArea().GetMinX();
			d->Y1=L->GetArea().GetMinY();
			d->X2=L->GetArea().GetMaxX();
			d->Y2=L->GetArea().GetMaxY();
			AlgoLearningAreaListContainerVar->List->AppendList(d);
		}
		return;
	}
	CmdReqStartLearning	*CmdReqStartLearningVar=dynamic_cast<CmdReqStartLearning *>(packet);
	if(CmdReqStartLearningVar!=NULL){
		((LearningRuleBase *)GetParentBase())->TryCalcMode=true;

		double	Add2=0;
		for(LearningRuleInPage *c=((LearningRuleBase *)GetParentBase())->LearningRuleInPageStocker[GetPage()].GetFirst();c!=NULL;c=c->GetNext()){
			c->LoadLearnFile();
			c->TryCalc();
			double	d=c->CalcResult();
			Add2+=d*d;
		}

		((LearningRuleBase *)GetParentBase())->TryCalcMode=false;
		return;
	}
	LearningReqStartOne	*LearningReqStartOneVar=dynamic_cast<LearningReqStartOne *>(packet);
	if(LearningReqStartOneVar!=NULL){
		LearningReqStartOneVar->ResultValueInPage=CalcResult();
		return;
	}
	LearningExeTop	*LearningExeTopVar=dynamic_cast<LearningExeTop *>(packet);
	if(LearningExeTopVar!=NULL){
		ExeLowLevelTotalFirst();
		return;
	}
	LearningExeLoopTop	*LearningExeLoopTopVar=dynamic_cast<LearningExeLoopTop *>(packet);
	if(LearningExeLoopTopVar!=NULL){
		ExeLowLevelLoopFirst();
		return;
	}
	LearningExeLoopNext	*LearningExeLoopNextVar=dynamic_cast<LearningExeLoopNext *>(packet);
	if(LearningExeLoopNextVar!=NULL){
		ResultValueInPage=LearningExeLoopNextVar->ResultValueInPage;
		ExeLowLevelLoopContent();
		return;
	}
}

void	LearningRuleInPage::TryCalc(void)
{
	ListPhasePageLayerPack	CapturedList;
	AlgorithmInPagePI::GetLayersBase()->MakeCapturedAllList(CapturedList);

	AlgorithmInPagePI::GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	AlgorithmInPagePI::GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());

	int	TempStrategy=AlgorithmInPagePI::GetParamGlobal()->GetMaxScanStrategy();
	AlgorithmInPagePI::GetParamGlobal()->SetMaxScanStrategy(1);

	AlgorithmInPagePI::GetLayersBase()->StepProcessing(GetPage());
	//if(IsExecInitialAfterEdit==true)
	//	AlgorithmInPagePI::GetLayersBase()->ExecuteInitialAfterEdit(AlgorithmInPagePI::GetLayersBase()->GetEntryPoint());

	XDateTime	NowD=AlgorithmInPagePI::GetLayersBase()->GetStartInspectTime();
	//AlgorithmInPagePI::GetLayersBase()->GetLogicDLLBase()->SetStartTimeForInspection(NowD);

	AlgorithmInPagePI::GetLayersBase()->ExecuteStartByInspection	();
	AlgorithmInPagePI::GetLayersBase()->ExecuteCaptured				(CapturedList);
	AlgorithmInPagePI::GetLayersBase()->ExecutePreAlignment			();
	AlgorithmInPagePI::GetLayersBase()->ExecuteAlignment			();
	AlgorithmInPagePI::GetLayersBase()->ExecutePreProcessing		();
	AlgorithmInPagePI::GetLayersBase()->ExecuteProcessing			();
	AlgorithmInPagePI::GetLayersBase()->SetShouldWriteResult(false);
	AlgorithmInPagePI::GetLayersBase()->ExecutePostProcessing		();
	AlgorithmInPagePI::GetLayersBase()->SetShouldWriteResult(true);

	AlgorithmInPagePI::GetParamGlobal()->SetMaxScanStrategy(TempStrategy);
}

double	LearningRuleInPage::CalcResult(void)
{
	ResultInspection	*CurrentResult=AlgorithmInPagePI::GetLayersBase()->GetCurrentResultForCalc();
	double	ret=0;
	if(CurrentResult!=NULL){
		for(AlgorithmItemPI	*c=GetFirstData();c!=NULL;c=c->GetNext()){
			LearningRuleItem	*Item=dynamic_cast<LearningRuleItem *>(c);
			if(Item!=NULL){
				double	d=Item->GetCalcFromResult(*CurrentResult,GetPage());
				ret+=d*d;
			}
		}
	}
	return ret;
}

double	LearningRuleInPage::GetResult(ResultInspection &CurrentResult)
{
	ResultValueInPage=0;
	for(AlgorithmItemPI	*c=GetFirstData();c!=NULL;c=c->GetNext()){
		LearningRuleItem	*Item=dynamic_cast<LearningRuleItem *>(c);
		if(Item!=NULL){
			double	d=Item->GetCalcFromResult(CurrentResult,GetPage());
			ResultValueInPage+=d*d;
		}
	}
	return ResultValueInPage;
}

//---------------------------------------------------------------------

void	LearningRuleInPage::MakeFileLists(LearningFileListContainer &Dest
							,int MasterCode, int LotAutoCount)
{
	QString	path=((LearningRuleBase *)GetParentBase())->ImageFolder;

	int	GlobalPage=AlgorithmInPagePI::GetLayersBase()->GetGlobalPageFromLocal(GetPage());

	try{
		QString	filename=
				 QString(/**/"-")+QString::number(MasterCode)
				+QString(/**/"-")+QString::number(LotAutoCount)
				+QString(/**/"-")+QString::number(GlobalPage)
				+QString(/**/"*")
				+QString(/**/".lrn");

		QDir	Dir(path);
		QStringList	Filter;
		Filter.append(filename);
		QFileInfoList IList=Dir.entryInfoList (Filter,QDir::Files);

		int	N=IList.count();
		if(AlgorithmInPagePI::GetLayersBase()->GetLot(0)!=NULL){
			int	AutoCount=AlgorithmInPagePI::GetLayersBase()->GetLot(0)->GetLotAutoCount();
			for(int i=0;i<N;i++){
				LearningFileList	*a=new LearningFileList();
				a->FileName=IList[i].fileName();
				a->GlobalPage=GlobalPage;
				a->LotAutoCount=AutoCount;
				QStringList	L=a->FileName.split('-');
				QString	s=L[L.count()-1].section('.',0,0);
				a->ID=s.toInt();
				Dest.AppendList(a);
			}
		}
		Dest.SortByID();
	}
	catch(...){
	}

	if(((LearningRuleBase *)GetParentBase())->LoadBmpMode==true){
		QString	filename=/**/"*.bmp";

		QDir	Dir(path);
		QStringList	Filter;
		Filter.append(filename);
		QFileInfoList IList=Dir.entryInfoList (Filter,QDir::Files);

		LearningFileListContainer TmpDest;
		int	N=IList.count();
		if(AlgorithmInPagePI::GetLayersBase()->GetLot(0)!=NULL){
			int	AutoCount=AlgorithmInPagePI::GetLayersBase()->GetLot(0)->GetLotAutoCount();
			for(int i=0;i<N;i++){
				LearningFileList	*a=new LearningFileList();
				a->FileName=IList[i].fileName();
				a->GlobalPage=GlobalPage;
				a->LotAutoCount=AutoCount;
				a->ID=-1;
				TmpDest.AppendList(a);
			}
		}
		TmpDest.SortByName();
		Dest+=TmpDest;
	}
	if(((LearningRuleBase *)GetParentBase())->LoadJpgMode==true){
		QString	filename=/**/"*.jpg";

		QDir	Dir(path);
		QStringList	Filter;
		Filter.append(filename);
		QFileInfoList IList=Dir.entryInfoList (Filter,QDir::Files);

		LearningFileListContainer TmpDest;
		int	N=IList.count();
		if(AlgorithmInPagePI::GetLayersBase()->GetLot(0)!=NULL){
			int	AutoCount=AlgorithmInPagePI::GetLayersBase()->GetLot(0)->GetLotAutoCount();
			for(int i=0;i<N;i++){
				LearningFileList	*a=new LearningFileList();
				a->FileName=IList[i].fileName();
				a->GlobalPage=GlobalPage;
				a->LotAutoCount=AutoCount;
				a->ID=-2;
				TmpDest.AppendList(a);
			}
		}
		TmpDest.SortByName();
		Dest+=TmpDest;
	}
}

bool	LearningRuleInPage::LoadLearnFile(void)
{
	int32	Ver;

	QString	path=((LearningRuleBase *)GetParentBase())->ImageFolder;
	if(path.right(1)!=/**/"/" && path.right(1)!=/**/"\\")
		path=path+::GetSeparator();
	QFileInfo	FInfo(FileName);
	if(FInfo.suffix()==/**/"lrn"){
		QFile	F(path+FileName);

		if(F.open(QIODevice::ReadOnly)==true){
			if(::Load(&F,Ver)==false)
				return false;

			int32	iAllocatedLayerNumb;
			int32	iXLen,iYLen;

			if(::Load(&F,iAllocatedLayerNumb)==false)
				return false;
			if(::Load(&F,iXLen)==false)
				return false;
			if(::Load(&F,iYLen)==false)
				return false;
			ImagePointerContainer Images;
			GetTargetImages(Images);
			for(int L=0;L<iAllocatedLayerNumb;L++){
				ImageBuffer	*c=Images[L];
				if(c!=NULL){
					if(c->LoadSimple(&F)==false)
						return false;
				}
			}
			return true;
		}
	}
	if(FInfo.suffix()==/**/"bmp" || FInfo.suffix()==/**/"jpg"){
		QImage	Img;
		Img.load(path+FileName);
		AlgorithmInPagePI::GetLayersBase()->GetPageData(GetPage())->CopyFrom(Img,false);
	}
	return false;
}

bool    LearningRuleInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	return true;
}
bool    LearningRuleInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	return true;
}

//===========================================

LeaningSaveThread::LeaningSaveThread(LearningRuleBase *parent ,int localPage)
:QThread(parent->GetLayersBase()->GetMainWidget()),ServiceForLayers(parent->GetLayersBase())
{	
	BaseParent		=parent;
	SavedImage		=NULL;	
	InspectionID	=0;
	LotAutoCount	=0;
	LocalPage		=localPage;
	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	NowOnWriting	=false;
	AllocatedLayerNumb=0;
}

LeaningSaveThread::~LeaningSaveThread(void)
{
	while(NowOnWriting==true){
		sleep(100);
	}
	Release();
	//_CrtCheckMemory();
}

void	LeaningSaveThread::ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed)
{
	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

	XLen	=GetDotPerLine(LocalPage);
	YLen	=GetMaxLines(LocalPage);
	if(GetLayerNumb(LocalPage)!=AllocatedLayerNumb){
		if(SavedImage!=NULL){
			for(int L=0;L<AllocatedLayerNumb;L++){
				delete	SavedImage[L];
			}
			delete	[]SavedImage;
		}
	}
	AllocatedLayerNumb=GetLayerNumb(LocalPage);
	Allocate();
}

void	LeaningSaveThread::Allocate(void)
{
	if(SavedImage==NULL){
		SavedImage=new ImageBuffer*[AllocatedLayerNumb];
		for(int L=0;L<AllocatedLayerNumb;L++){
			SavedImage[L]=NULL;
		}
	}

	for(int L=0;L<AllocatedLayerNumb;L++){
		if(SavedImage[L]!=NULL){
			if(SavedImage[L]->GetWidth()!=GetDotPerLine(LocalPage) || SavedImage[L]->GetHeight()!=GetMaxLines(LocalPage)){
				delete	SavedImage[L];
				SavedImage[L]=NULL;
			}
		}

		if(SavedImage[L]==NULL){
			SavedImage[L]=new ImageBuffer();
			SavedImage[L]->Set(LocalPage,ImageBufferOther,GetDotPerLine(LocalPage),GetMaxLines(LocalPage));
		}
	}
}
void	LeaningSaveThread::Release(void)
{
	if(SavedImage!=NULL){
		for(int L=0;L<AllocatedLayerNumb;L++){
			delete	SavedImage[L];
		}
		delete	[]SavedImage;
	}
	SavedImage=NULL;
}

void LeaningSaveThread::run ()
{
	NowOnWriting=true;
	if(BaseParent->AllocBufferPerDemand==true){
		Allocate();
	}
	if(AllocatedLayerNumb==0){
		ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);
	}
	Save();

	if(BaseParent->AllocBufferPerDemand==true){
		Release();
	}

	NowOnWriting=false;
}

void	LeaningSaveThread::CopyFromTarget(void)
{
	MasterCode		=GetLayersBase()->GetMasterCode();
	InspectionID	=GetLayersBase()->GetCurrentInspectIDForExecute();
	if(GetLayersBase()->GetLot(0)!=NULL){
		LotAutoCount	=GetLayersBase()->GetLot(0)->GetLotAutoCount();
	}
	else{
		LotAutoCount=-1;
	}
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);

	if(AllocatedLayerNumb==0){
		ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);
	}
	for(int L=0;L<GetLayerNumb(LocalPage) && L<AllocatedLayerNumb;L++){
		*SavedImage[L]	=GetLayersBase()->GetPageData(LocalPage)->GetLayerData(L)->GetTargetBuff();
	}
}
void	LeaningSaveThread::CopyToTarget(void)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	for(int L=0;L<GetLayerNumb(LocalPage) && L<AllocatedLayerNumb;L++){
		GetLayersBase()->GetPageData(LocalPage)->GetLayerData(L)->GetTargetBuff()=*SavedImage[L];
	}
}

bool	LeaningSaveThread::Save(void)
{
	QString	filename=CreateFileName();

	try{
		QFileInfo	hInfo(filename);
		QString	path=hInfo.path();
		ForceDirectories(path);

		QFile	F(filename);
		if(F.open(QIODevice::WriteOnly)==true){
			if(Save(&F)==false){
				return false;
			}
		}
	}
	catch(...){
		return false;
	}
	return true;
}

bool	LeaningSaveThread::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,AllocatedLayerNumb)==false)
		return false;
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	for(int L=0;L<AllocatedLayerNumb;L++){
		if(SavedImage[L]==NULL)
			return false;
		if(SavedImage[L]->Save(f)==false)
			return false;
	}
	return true;
}
bool	LeaningSaveThread::Load(QString FileName)
{
	try{
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==true){
			if(Load(&F)==false){
				return false;
			}
		}
	}
	catch(...){
		return false;
	}
	return true;
}
bool	LeaningSaveThread::Load(QIODevice *f)
{
	int32	Ver;

	if(SavedImage==NULL)
		ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);

	if(::Load(f,Ver)==false)
		return false;

	int32	iAllocatedLayerNumb;
	int32	iXLen,iYLen;

	if(::Load(f,iAllocatedLayerNumb)==false)
		return false;
	if(::Load(f,iXLen)==false)
		return false;
	if(::Load(f,iYLen)==false)
		return false;
	for(int L=0;L<iAllocatedLayerNumb && L<AllocatedLayerNumb;L++){
		if(SavedImage[L]!=NULL){
			if(SavedImage[L]->LoadSimple(f)==false)
				return false;
		}
	}
	return true;
}

QString	LeaningSaveThread::CreateFileName(void)
{
	QString	filename=BaseParent->ImageFolder;
	if(filename.right(1)!=/**/"/" && filename.right(1)!=/**/"\\")
		filename=filename+::GetSeparator();
	filename=filename
			+QString(/**/"-")+QString::number(MasterCode)
			+QString(/**/"-")+QString::number(LotAutoCount)
			+QString(/**/"-")+QString::number(GlobalPage)
			+QString(/**/"-")+QString::number(InspectionID)
			+QString(/**/".lrn");
	return filename;
}


LearningRuleBase::LearningRuleBase(LayersBase *Base)
	:AlgorithmBase(Base)
{
	ThreadSaver=NULL;
	ThreadSaverCount=0;
	LearningRuleInPageStocker=NULL;
	AllocatedPageCount=0;
	Saved=NULL;

	ColorRuleNG		=Qt::green;
	ColorRuleOK		=Qt::darkGreen;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorRule	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	ImageFolder		=/**/"D:/Image";
	AllocBufferPerDemand	=false;
	SaveMode		=false;
	TryCalcMode		=false;
	LoadBmpMode		=true;
	LoadJpgMode		=true;

	SetParam(&ColorRuleNG			, /**/"Color"	,/**/"ColorRuleNG"			,"Color for LearningRule NG Zone");
	SetParam(&ColorRuleOK			, /**/"Color"	,/**/"ColorRuleOK"			,"Color for LearningRule OK Zone(Non NG)");
	SetParam(&ColorSelected			, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected Zone");
	SetParam(&ColorActive			, /**/"Color"	,/**/"ColorActive"			,"Color for Active Zone");
	SetParam(&NegColorRule			, /**/"Color"	,/**/"NegColorRule"			,"Color for Negative Zone");
	SetParam(&NegColorSelected		, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative Zone");
	SetParam(&TransparentLevel		, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");
	SetParam(&ImageFolder			, /**/"Setting" ,/**/"ImageFolder"			,"Folder path for image to learn");
	SetParam(&AllocBufferPerDemand	, /**/"Setting" ,/**/"AllocBufferPerDemand"	,"True if buffer is allocated every PreProcessing.");
	SetParam(&LoadBmpMode			, /**/"Setting" ,/**/"LoadBmpMode"			,"True if BMP file is enumerated and loaded.");
	SetParam(&LoadJpgMode			, /**/"Setting" ,/**/"LoadJpgMode"			,"True if JPEG file is enumerated and loaded.");
}

LearningRuleBase::~LearningRuleBase(void)
{
	if(LearningRuleInPageStocker!=NULL)
		delete	[]LearningRuleInPageStocker;
	LearningRuleInPageStocker=NULL;

	if(ThreadSaver!=NULL){
		for(int p=0;p<ThreadSaverCount;p++){
			delete	ThreadSaver[p];
			ThreadSaver[p]=NULL;
		}
		delete	[]ThreadSaver;
	}
	ThreadSaver=NULL;

	if(Saved!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			SetPageData(page,Saved[page].Pointer);
		}
		delete	[]Saved;
		Saved=NULL;
	}
}

AlgorithmDrawAttr	*LearningRuleBase::CreateDrawAttr(void)
{
	return new LearningRuleDrawAttr();
}

void	LearningRuleBase::Initial(LayersBase *Base)
{
	AlgorithmBase::Initial(Base);

	AllocatedPageCount=GetPageNumb();
	if(LearningRuleInPageStocker!=NULL)
		delete	[]LearningRuleInPageStocker;
	LearningRuleInPageStocker=new NPListPack<LearningRuleInPage>[AllocatedPageCount];

	if(ThreadSaver!=NULL){
		for(int p=0;p<ThreadSaverCount;p++){
			delete	ThreadSaver[p];
			ThreadSaver[p]=NULL;
		}
		delete	[]ThreadSaver;
	}

	ThreadSaverCount=GetPageNumb();
	ThreadSaver=new LeaningSaveThread*[ThreadSaverCount];
	for(int page=0;page<ThreadSaverCount;page++){
		ThreadSaver[page]=new LeaningSaveThread(this,page);
	}
	Saved=new LearningRuleInPagePointer[GetPageNumb()];
	for(int page=0;page<GetPageNumb();page++){
		Saved[page].Pointer=GetPageData(page);
	}
}

ExeResult	LearningRuleBase::ExecutePreProcessing(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	ExeResult	Ret=AlgorithmBase::ExecutePreProcessing(ExeID ,Res);

	if(TryCalcMode==false){
		if(SaveMode==true){
			for(int page=0;page<ThreadSaverCount;page++){
				ThreadSaver[page]->CopyFromTarget();
				ThreadSaver[page]->start();
			}
		}
	}
	return Ret;
}

bool	LearningRuleBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

void	LearningRuleBase::TransmitDirectly(GUIDirectMessage *packet)
{
	/*
	LearningDelFilePacket	*LearningDelFilePacketVar=dynamic_cast<LearningDelFilePacket *>(packet);
	if(LearningDelFilePacketVar!=NULL){
		LearningRuleInPage	*PData=(LearningRuleInPage *)GetPageData(LearningDelFilePacketVar->Page);
		if(PData!=NULL){
			if(PData->LNumber==LearningDelFilePacketVar->IndexNumber){
				if(LearningRuleInPageStocker.GetNumber()!=0){
					RemovePage(PData);
					PData=LearningRuleInPageStocker.GetFirst();
					SetPageData(LearningDelFilePacketVar->Page,PData);
				}
			}
		}
	}
	*/
	LearningSetSaveMode	*LearningSetSaveModeVar=dynamic_cast<LearningSetSaveMode *>(packet);
	if(LearningSetSaveModeVar!=NULL){
		SaveMode=LearningSetSaveModeVar->Mode;
		return;
	}
	LearningReqSaveMode	*LearningReqSaveModeVar=dynamic_cast<LearningReqSaveMode *>(packet);
	if(LearningReqSaveModeVar!=NULL){
		LearningReqSaveModeVar->Mode=SaveMode;
		return;
	}
	LearningChangeSelectedNumber	*LearningChangeSelectedNumberVar=dynamic_cast<LearningChangeSelectedNumber *>(packet);
	if(LearningChangeSelectedNumberVar!=NULL){
		LearningRuleInPage	*P=LearningRuleInPageStocker[LearningChangeSelectedNumberVar->Page].GetItem(LearningChangeSelectedNumberVar->SelectedNumber);
		SetPageData(LearningChangeSelectedNumberVar->Page,P);
		P->LoadLearnFile();
	}
	LearningReqPickedFileList	*LearningReqPickedFileListVar=dynamic_cast<LearningReqPickedFileList *>(packet);
	if(LearningReqPickedFileListVar!=NULL){
		int	LocalPage=LearningReqPickedFileListVar->LocalPage;
		int	i=0;
		for(LearningRuleInPage *c=LearningRuleInPageStocker[LocalPage].GetFirst();c!=NULL;c=c->GetNext(),i++){
			LearningFileList	*d=new LearningFileList();
			d->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
			d->FileName		=c->FileName;
			d->ID			=i;
			LearningReqPickedFileListVar->List->AppendList(d);
		}
	}
}

bool	LearningRuleBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	if(::Save(f,AllocatedPageCount)==false)
		return false;
	for(int page=0;page<AllocatedPageCount;page++){
		int32	N=LearningRuleInPageStocker[page].GetNumber();
		if(::Save(f,N)==false)
			return false;
		for(LearningRuleInPage *L=LearningRuleInPageStocker[page].GetFirst();L!=NULL;L=L->GetNext()){
			if(L->Save(f)==false)
				return false;
		}
	}
	return true;
}

bool	LearningRuleBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	int32	iAllocatedPageCount;
	if(::Load(f,iAllocatedPageCount)==false)
		return false;

	int page;
	for(page=0;page<AllocatedPageCount && page<iAllocatedPageCount;page++){
		int32	N;
		if(::Load(f,N)==false)
			return false;
		LearningRuleInPageStocker[page].RemoveAll();
		SetPageData(page,Saved[page].Pointer);
		for(int i=0;i<N;i++){
			LearningRuleInPage *L=(LearningRuleInPage *)NewChild(this);
			L->SetPage(page);
			if(L->Load(f)==false){
				delete	L;
				return false;
			}
			//L->Initial(GetLayersBase());
			LearningRuleInPageStocker[page].AppendList(L);
		}
	}

	for(;page<iAllocatedPageCount;page++){
		int32	N;
		if(::Load(f,N)==false)
			return false;
		for(int i=0;i<N;i++){
			LearningRuleInPage *L=new LearningRuleInPage(this);
			if(L->Load(f)==false)
				return false;
			delete	L;
		}
	}
	return true;
}
