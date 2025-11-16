#include "XTypeDef.h"
#include "XLearningRegist.h"
#include "XLearningRegistPacket.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XDatabaseLoader.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGUI.h"

/*
class	LeariningGUIInitializer : public GUIInitializer	
{
public:
	LeariningGUIInitializer(void){}
};
*/

LearningImage::LearningImage(LayersBase *base)
{
	Base=base;
	SavedImage			=NULL;
	SavedMasterImage	=NULL;
	ShowingShiftX		=0;
	ShowingShiftY		=0;
	GlobalPage			=0;
	OrgLocalX1			=0;
	OrgLocalY1			=0;
	OrgLocalX2			=0;
	OrgLocalY2			=0;
	ShowingTarget		=false;
	ShowingMaster		=false;
	AVector				=NULL;

	LearningLayersBase	=NULL;
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	for(int layer=0;layer<GetLayersParentBase()->GetLayerNumb(LocalPage);layer++){
		MarkToProceed.Add(false);
		ResultMark	 .Add(true);
	}
}

LearningImage::~LearningImage(void)
{
	if(SavedImage!=NULL){
		delete	[]SavedImage;
		SavedImage=NULL;
	}
	if(SavedMasterImage!=NULL){
		delete	[]SavedMasterImage;
		SavedMasterImage=NULL;
	}
}

LearningImage::LNLayersBase::LNLayersBase(LearningImage *parent,LayersBase *ParentLayer)
	:Parent(parent)
	,LayersBase(/**/"LearningImage",ParentLayer)
{}

bool	LearningImage::LNLayersBase::Set(LayersBase *Base,LearningImage *parent)
{
	InsideLearningEditor	=true;
	BootingLevel			=1;

	CurrentPath		=Base->GetSystemPath();
	UserPath		=Base->GetUserPath();
	RootDBase		=Base->GetDataBase();
	DBLoader		=Base->GetDatabaseLoader();
	MasterCode		=Base->GetMasterCode();
	OnProcessing	=NULL;	//Base->OnProcessing;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Base->GetParamGlobal()->SaveParam(&Buff);
	Buff.seek(0);
	GetParamGlobal()->LoadParam(&Buff);
	GetParamGlobal()->AllocateTargetBuff	=true;	//false;
	GetParamGlobal()->DotPerLine			=parent->GetWidth();
	GetParamGlobal()->MaxLines				=parent->GetHeight();
	GetParamGlobal()->PageNumb				=1;
	GetParamGlobal()->TotalCameraNumb		=1;

	InitialCreatePages(parent);

	//for(

	LogicDLLBase->CopyFrom(this,*Base->GetLogicDLLBase());
	SetLanguageCode(Base->GetLanguageCode());
	CreateAlgorithmPointer();
	ResultDLLBase	=NULL;
	//InitialArrangementDLL();
	InitialAlgorithmLibrary();
	InitialAllocExecuterDim();
	InitialResult();
	for(LogicDLL *s=Base->GetLogicDLLBase()->GetFirst();s!=NULL;s=s->GetNext()){
		AlgorithmBase	*si=s->GetInstance();
		for(LogicDLL *d=GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
			if(d->GetDLLRoot()==s->GetDLLRoot() && d->GetDLLName()==s->GetDLLName()){
				AlgorithmBase	*di=d->GetInstance();
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				si->SaveParam(&Buff);
				Buff.seek(0);
				di->LoadParam(&Buff);
				di->InitialAfterParamLoaded();
				break;
			}
		}
	}
	return true;
}


inline ImageBuffer	&LearningImage::LNLayersBase::GetMasterBuff(int layer)
{
	return GetPageData(0)->GetLayerData(layer)->GetMasterBuff();
}

int		LearningImage::GetLayerNumb(void)		const
{	
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	return GetLayersBase()->GetLayerNumb(LocalPage);
}
bool	LearningImage::SendData (int32 commID ,int globalPage
									,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
									,QBuffer *f 
									,ErrorCodeList &ErrorData)
{
	return true;
}
bool	LearningImage::SendArray(int32 commID ,int globalPage
									,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
									,QByteArray *f
									,ErrorCodeList &ErrorData)
{
	return true;
}
bool	LearningImage::SendDataDirectComm(int32 commID ,int privatePage
											,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
											,QBuffer *f 
											,ErrorCodeList &ErrorData)
{
	return true;
}
bool	LearningImage::SendIntegrationData (int slaveNo
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)
{
	return true;
}

void	LearningImage::ReadyReadDirectComm(void)
{
}
GUIInstancePack		*LearningImage::GetGUIInstancePack(void)
{		
	return(LearningLayersBase->GetGuiInitializer()->GetGUIInstanceRoot());
}

void	LearningImage::GetOrgCenter(int &Cx, int &Cy)	const
{
	Cx=(OrgLocalX1+OrgLocalX2)/2;
	Cy=(OrgLocalY1+OrgLocalY2)/2;
}

void	LearningImage::GetOrgLocalArea(int &x1, int &y1 , int &x2 ,int &y2)	const
{
	x1=OrgLocalX1;
	y1=OrgLocalY1;
	x2=OrgLocalX2;
	y2=OrgLocalY2;
}

bool	LearningImage::SetAllocImage(const XDateTime &_CreatedTime ,int _GlobalPage
									, int _LocalX1 ,int _LocalY1 ,int _LocalX2 ,int _LocalY2
									, AlignmentPacket2D *Align)
{
	CreatedTime=_CreatedTime;
	GlobalPage=_GlobalPage;
	if(LearningLayersBase!=NULL){
		delete	LearningLayersBase;
	}
	
	int	dx=0;
	int	dy=0;
	if(Align!=NULL){
		dx=Align->ShiftX;
		dy=Align->ShiftY;
	}
	OrgLocalX1=_LocalX1;
	OrgLocalY1=_LocalY1;
	OrgLocalX2=_LocalX2;
	OrgLocalY2=_LocalY2;
	if(OrgLocalX1<0){
		OrgLocalX1=0;
	}
	if(OrgLocalY1<0){
		OrgLocalY1=0;
	}
	if(OrgLocalX1+dx<0){
		OrgLocalX1=-dx;
	}
	if(OrgLocalY1+dy<0){
		OrgLocalY1=-dy;
	}

	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	DataInPage *Pg=GetLayersParentBase()->GetPageData(LocalPage);

	if(OrgLocalX2>=Pg->GetDotPerLine()){
		OrgLocalX2=Pg->GetDotPerLine()-1;
	}
	if(OrgLocalY2>=Pg->GetMaxLines()){
		OrgLocalY2=Pg->GetMaxLines()-1;
	}
	if(OrgLocalX2+dx>=Pg->GetDotPerLine()){
		OrgLocalX2=Pg->GetDotPerLine()-1-dx;
	}
	if(OrgLocalY2+dy>=Pg->GetMaxLines()){
		OrgLocalY2=Pg->GetMaxLines()-1-dy;
	}
	int	RectWidth=OrgLocalX2-OrgLocalX1;
	int	RectHeight=OrgLocalY2-OrgLocalY1;
	if(RectWidth<=0 || RectHeight<=0){
		return false;
	}

	LearningLayersBase=new LNLayersBase(this,GetLayersParentBase());
	LearningLayersBase->Set(GetLayersParentBase(),this);

	for(int L=0;L<GetLayerNumb();L++){
		LearningLayersBase->GetMasterBuff(L).PartialCopy(Pg->GetLayerData(L)->GetTargetBuff()
														,OrgLocalX1+dx	,OrgLocalY1+dy	);
	}
	return true;
}

void	LearningImage::LNLayersBase::SetIndexedToTargetBuff(ImageBuffer *SrcBuffPointer[]
										,int SrcX1 ,int SrcY1 ,int SrcX2 ,int SrcY2)
{
	DataInPage *P=GetPageData(0);
	int	LocalPage=Parent->GetLayersParentBase()->GetLocalPageFromGlobal(Parent->GlobalPage);
	for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
		ImageBuffer	&TBuff=P->GetLayerData(layer)->GetTargetBuff();
		TBuff.SetIndexImage(*SrcBuffPointer[layer]
							,SrcX1 ,SrcY1 ,SrcX2 ,SrcY2);
	}
}


void	LearningImage::SetImageToMasterOrg(void)
{
	if(LearningLayersBase==NULL){
		return;
	}
	int hLocalX1=OrgLocalX1;
	int hLocalY1=OrgLocalY1;
	//int hLocalX2=OrgLocalX2;
	//int hLocalY2=OrgLocalY2;
	if(SavedMasterImage==NULL){
		SavedMasterImage=new ImageBuffer[GetLayerNumb()];
	}
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	for(int L=0;L<GetLayerNumb();L++){
		SavedMasterImage[L].Set(LocalPage,ImageBufferMaster,GetWidth(), GetHeight());
		SavedMasterImage[L].PartialCopy(GetLayersParentBase()->GetPageData(LocalPage)->GetLayerData(L)->GetMasterBuff(),hLocalX1	,hLocalY1	);
		GetLayersParentBase()->GetPageData(LocalPage)->GetLayerData(L)->GetMasterBuff().PartialCopy(hLocalX1,hLocalY1	,LearningLayersBase->GetMasterBuff(L)	);
	}
	ShowingMaster=true;
}

void	LearningImage::RestoreToMasterOrg(void)
{
	ShowingMaster=false;
	int hLocalX1=OrgLocalX1;
	int hLocalY1=OrgLocalY1;
	//int hLocalX2=OrgLocalX2;
	//int hLocalY2=OrgLocalY2;

	if(SavedMasterImage==NULL){
		return;
	}
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	for(int L=0;L<GetLayerNumb();L++){
		GetLayersParentBase()->GetPageData(LocalPage)->GetLayerData(L)->GetMasterBuff().PartialCopy(hLocalX1
																							, hLocalY1
																							, SavedMasterImage[L]	);
	}
}

void	LearningImage::SetImageToTargetOrg(AlignmentPacket2D *Align)
{
	if(LearningLayersBase==NULL){
		return;
	}
	int	dx=0;
	int	dy=0;
	if(Align!=NULL){
		dx=Align->ShiftX;
		dy=Align->ShiftY;
	}
	int hLocalX1=OrgLocalX1;
	int hLocalY1=OrgLocalY1;
	int hLocalX2=OrgLocalX2;
	int hLocalY2=OrgLocalY2;
	if(hLocalX1+dx<0){
		hLocalX1=-dx;
	}
	if(hLocalY1+dy<0){
		hLocalY1=-dy;
	}
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	DataInPage *P=GetLayersParentBase()->GetPageData(LocalPage);

	if(hLocalX2+dx>=P->GetDotPerLine()){
		hLocalX2=P->GetDotPerLine()-1-dx;
	}
	if(hLocalY2+dy>=P->GetMaxLines()){
		hLocalY2=P->GetMaxLines()-1-dy;
	}
	int	Lx=hLocalX2-hLocalX1;
	int	Ly=hLocalY2-hLocalY1;
	if(Lx<=0 || Ly<=0){
		return;
	}
	if(SavedImage==NULL){
		SavedImage=new ImageBuffer[GetLayerNumb()];
	}
	ShowingShiftX=dx;
	ShowingShiftY=dy;
	for(int L=0;L<GetLayerNumb();L++){
		SavedImage[L].Set(LocalPage,ImageBufferTarget,Lx, Ly);
		SavedImage[L].PartialCopy(P->GetLayerData(L)->GetTargetBuff(),hLocalX1+dx	,hLocalY1+dy	);
		P->GetLayerData(L)->GetTargetBuff().PartialCopy(hLocalX1+dx,hLocalY1+dy	,LearningLayersBase->GetMasterBuff(L)	);
	}
	ShowingTarget=true;
}

void	LearningImage::RestoreToTargetOrg(void)
{
	ShowingTarget=false;
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	DataInPage *P=GetLayersParentBase()->GetPageData(LocalPage);

	int hLocalX1=OrgLocalX1;
	int hLocalY1=OrgLocalY1;
	int hLocalX2=OrgLocalX2;
	int hLocalY2=OrgLocalY2;
	if(hLocalX1+ShowingShiftX<0){
		hLocalX1=-ShowingShiftX;
	}
	if(hLocalY1+ShowingShiftY<0){
		hLocalY1=-ShowingShiftY;
	}
	if(hLocalX2+ShowingShiftX>=P->GetDotPerLine()){
		hLocalX2=P->GetDotPerLine()-1-ShowingShiftX;
	}
	if(hLocalY2+ShowingShiftY>=P->GetMaxLines()){
		hLocalY2=P->GetMaxLines()-1-ShowingShiftY;
	}
	int	Lx=hLocalX2-hLocalX1;
	int	Ly=hLocalY2-hLocalY1;
	if(Lx<=0 || Ly<=0){
		return;
	}
	if(SavedImage==NULL){
		return;
	}
	for(int L=0;L<GetLayerNumb();L++){
		P->GetLayerData(L)->GetTargetBuff().PartialCopy(hLocalX1+ShowingShiftX
														, hLocalY1+ShowingShiftY
														, SavedImage[L]	);
	}
}

void	LearningImage::ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep)
{
	LearningLayersBase->ExecuteInitialAfterEdit(EInfo,ProgressStep);
}
void	LearningImage::ExecuteStartByScanOnly	(bool ProgressStep)
{
	LearningLayersBase->ExecuteStartByScanOnly(ProgressStep);
}
void	LearningImage::ExecuteStartByInspection	(bool ProgressStep)
{
	LearningLayersBase->ExecuteStartByInspection(ProgressStep);
}
void	LearningImage::ExecuteCaptured			(ListPhasePageLayerPack &CapturedList ,bool ProgressStep)
{
	LearningLayersBase->ExecuteCaptured	(CapturedList,ProgressStep);
}
void	LearningImage::ExecutePreAlignment		(bool ProgressStep)
{
	LearningLayersBase->ExecutePreAlignment	(ProgressStep);
}
void	LearningImage::ExecuteAlignment			(bool ProgressStep)
{
	LearningLayersBase->ExecuteAlignment	(ProgressStep);
}
void	LearningImage::ExecutePreProcessing		(bool ProgressStep)
{
	LearningLayersBase->ExecutePreProcessing(ProgressStep);
}
void	LearningImage::ExecuteProcessing		(bool ProgressStep)
{
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	DataInPage	*P=LearningLayersBase->GetPageData(0);
	P->ClearNGCounterWithMutex();

	AlignmentPacket2D	V;
	int	cx,cy;
	GetOrgCenter(cx,cy);
	V.PosXOnTarget=cx;
	V.PosYOnTarget=cy;
	V.ShiftX=0;
	V.ShiftY=0;
	LogicDLL	*L=GetLayersParentBase()->GetLogicDLLBase()->SearchByAlgorithmType(AlgorithmBit_TypeAlignment);
	if(L!=NULL){
		L->GetAlignmentForProcessing(LocalPage,V);
	}

	ImageBuffer *SrcBuffPointer[1000];
	for(int layer=0;layer<GetLayersParentBase()->GetLayerNumb(LocalPage);layer++){
		SrcBuffPointer[layer]=&GetLayersParentBase()->GetPageData(LocalPage)->GetLayerData(layer)->GetTargetBuff();
	}
	LearningLayersBase->SetIndexedToTargetBuff(SrcBuffPointer
										,OrgLocalX1+V.ShiftX
										,OrgLocalY1+V.ShiftY
										,OrgLocalX2+V.ShiftX
										,OrgLocalY2+V.ShiftY);
	LearningLayersBase->ExecuteProcessing	(ProgressStep);

	if(P->GetOKCounter()!=0 && P->GetNGCounter()==0){
		for(int layer=0;layer<GetLayersParentBase()->GetLayerNumb(LocalPage);layer++){
			if(ResultMark.GetItem(layer)!=NULL){
				ResultMark.GetItem(layer)->SetValue(true);
			}
		}
	}
	else{
		for(int layer=0;layer<GetLayersParentBase()->GetLayerNumb(LocalPage);layer++){
			if(ResultMark.GetItem(layer)!=NULL){
				ResultMark.GetItem(layer)->SetValue(false);
			}
		}
	}
}
void	LearningImage::ExecuteProcessingRevived	(bool ProgressStep)
{
	LearningLayersBase->ExecuteProcessingRevived(ProgressStep);
}
void	LearningImage::ExecutePostProcessing	(bool ProgressStep)
{
	LearningLayersBase->ExecutePostProcessing(ProgressStep);
}
void	LearningImage::ExecutePreScanning		(bool ProgressStep)
{
	LearningLayersBase->ExecutePreScanning	(ProgressStep);
}
void	LearningImage::ExecuteScanning			(bool ProgressStep)
{
	LearningLayersBase->ExecuteScanning		(ProgressStep);
}
void	LearningImage::ExecutePostScanning		(bool ProgressStep)
{
	LearningLayersBase->ExecutePostScanning	(ProgressStep);
}

bool	LearningImage::IsIncludeOrg(int LocalX ,int LocalY)
{
	if(OrgLocalX1<=LocalX && LocalX<=OrgLocalX2 && OrgLocalY1<=LocalY && LocalY<=OrgLocalY2){
		return true;
	}
	return false;
}

bool	LearningImage::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,CreatedTime)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,OrgLocalX1)==false)
		return false;
	if(::Load(f,OrgLocalY1)==false)
		return false;
	if(::Load(f,OrgLocalX2)==false)
		return false;
	if(::Load(f,OrgLocalY2)==false)
		return false;

	if(LearningLayersBase==NULL){
		LearningLayersBase=new LNLayersBase(this,GetLayersParentBase());
	}
	LearningLayersBase->Set(GetLayersParentBase(),this);
	if(LearningLayersBase->LoadImages(f)==false){
		return false;
	}
	LearningLayersBase->CloseInformed();

	return true;
}
bool	LearningImage::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,CreatedTime)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,OrgLocalX1)==false)
		return false;
	if(::Save(f,OrgLocalY1)==false)
		return false;
	if(::Save(f,OrgLocalX2)==false)
		return false;
	if(::Save(f,OrgLocalY2)==false)
		return false;

	if(LearningLayersBase->SaveImages(f)==false)
		return false;
	return true;
}

bool	LearningImage::SaveAlgorithm(QIODevice *f, const QString &AlgoBlobName)
{
	LogicDLL *p;
	AlgorithmBase	*base;
	AlgorithmInPageRoot	*ap;
	int32	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	for(p=LearningLayersBase->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName()==AlgoBlobName){
			base=LearningLayersBase->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
			if(base==NULL || base->GetModeLoadSaveInPlayer()==false){
				continue;
			}
			ap=base->GetPageData(LocalPage);
			if(ap==NULL){
				continue;
			}
			base->SaveOnlyBase(f);
			ap->Save(f);	//アルゴリズムによってはfalseを吐く
		}
	}
	return true;
}
bool	LearningImage::LoadAlgorithm(QIODevice *f, const QString &AlgoBlobName)
{
	int32	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	QString	LogicFileName;
	for(LogicDLL *p=LearningLayersBase->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName()==AlgoBlobName){
			AlgorithmBase	*base=LearningLayersBase->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
			if(base==NULL){
				continue;
			}

			AlgorithmInPageRoot	*ap=base->GetPageData(LocalPage);
			if(ap==NULL){
				continue;
			}
			if(base->LoadOnlyBase(f)==false){
				continue;
			}
			ap->Load(f);
		}
	}
	return true;
}

void	LearningImage::DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
					,const QColor &LColor
					,int OffsetX ,int OffsetY)
{
	if(GetLearningLayersBase()!=NULL){
		GetLearningLayersBase()->DrawImage(Img, movx ,movy ,ZoomRate
											,true
											,LColor
											,OffsetX ,OffsetY);
	}
}

void	LearningImage::DrawThumnailImage(QImage &Img, int ImageWidth ,int ImageHeight)
{
	int	LocalPage=GetLayersParentBase()->GetLocalPageFromGlobal(GlobalPage);
	DataInPage *Pg=GetLayersParentBase()->GetPageData(LocalPage);

	double	ZoomRateX=((double)ImageWidth )/((double)Pg->GetDotPerLine());
	double	ZoomRateY=((double)ImageHeight)/((double)Pg->GetMaxLines());

	double	ZoomRate=(ZoomRateX<ZoomRateY)?ZoomRateX:ZoomRateY;

	DrawImage(Img, 0,0,ZoomRate
				,Qt::white,0,0);
}


//============================================================================================
LearningInPage::LearningInPage(int _Page ,LayersBase *Base)
:ServiceForLayers(Base)
{
	LocalPage=_Page;
}

bool	LearningInPage::LoadLearning(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	LearningImageStocker.RemoveAll();
	for(int i=0;i<N;i++){
		LearningImage *c=new LearningImage(GetLayersBase());
		if(c->Load(f)==false)
			return false;
		LearningImageStocker.AppendList(c);
	}
	return true;
}

bool	LearningInPage::SaveLearning(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int32	N=LearningImageStocker.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}

bool	LearningInPage::SaveAlgorithm(const QString &ImagePath)
{
	QString Sep=/**/"";
	QString s = ImagePath.right(1);
	if(s!=::GetSeparator() && s!=QString("\\")){
		Sep= GetSeparator();
	}
	for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName().isEmpty()==false){
			AlgorithmBase	*Algo=p->GetInstance();
			if(Algo!=NULL && Algo->GetModeLoadSaveInPlayer()==true){
				QString	LogicFileName=ImagePath+Sep+MakeAlgorithmFileName(p->GetBlobName());
				QFile	LogicFile(LogicFileName);
				LogicFile.open(QIODevice::WriteOnly);

				int32	N=LearningImageStocker.GetCount();

				if(::Save(&LogicFile,N)==false){
					return false;
				}

				for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
					if(::Save(&LogicFile,c->GetCreatedTime())==false){
						return false;
					}
					if(c->SaveAlgorithm(&LogicFile,p->GetBlobName())==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}
	
bool	LearningInPage::LoadAlgorithm(void)
{
	for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName().isEmpty()==false){
			QString	LogicFileName=GetParamGlobal()->ImageFilePath+MakeAlgorithmFileName(p->GetBlobName());
			if(QFile::exists(LogicFileName)==true){
				QFile	LogicFile(LogicFileName);
				LogicFile.open(QIODevice::ReadOnly);

				int32	N=0;
				if(::Load(&LogicFile,N)==false){
					return false;
				}
				for(int i=0;i<N;i++){
					XDateTime	CreatedTime;
					if(::Load(&LogicFile,CreatedTime)==false){
						break;
					}
					LearningImage	*c=Find(CreatedTime);
					if(c!=NULL){
						if(c->LoadAlgorithm(&LogicFile,p->GetBlobName())==false){
							break;
						}
					}
					else{
						//return false;
					}
				}
			}
		}
	}
	return true;
}


LearningImage *LearningInPage::SetAllocImage(const XDateTime &_CreatedTime ,int GlobalPage
									, int LocalX1 ,int LocalY1 ,int LocalX2 ,int LocalY2
									, AlignmentPacket2D *Align)
{
	LearningImage *c=new LearningImage(GetLayersBase());
	if(c->SetAllocImage(_CreatedTime ,GlobalPage, LocalX1 ,LocalY1 ,LocalX2 ,LocalY2 , Align)==false){
		delete	c;
		return NULL;
	}
	LearningImageStocker.AppendList(c);
	if(SaveLearningDefault(GetLayersBase()->GetSelectedImagePath())==false){
		return NULL;
	}
	return c;
}


bool	LearningInPage::LoadLearningDefault(void)
{
	QString	FileName=GetParamGlobal()->ImageFilePath+MakeFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LoadLearning(&File)==false){
			return false;
		}
	}
	if(LoadAlgorithm()==false){
		return false;
	}
	return true;
}

bool	LearningInPage::SaveLearningDefault(const QString &ImagePath)
{
	if(GetParamGlobal()->AllocateMasterBuff==true){
		QString Sep=/**/"";
		QString s = ImagePath.right(1);
		if(s!=::GetSeparator() && s!=QString("\\")){
			Sep= GetSeparator();
		}

		QString	FileName=ImagePath+Sep+MakeFileName();
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(SaveLearning(&File)==false){
				return false;
			}
		}
	}
	if(SaveAlgorithm(ImagePath)==false){
		return false;
	}
	return true;
}
void	LearningInPage::ClearResultMark(int layer)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ResultMark.GetItem(layer)!=NULL){
			c->ResultMark.GetItem(layer)->SetValue(true);
		}
	}
}
void	LearningInPage::ClearAllMarkToProceed(int layer)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->SetMarkToProceed(layer,false);
	}
}
void	LearningInPage::SetResultMarkForLearning(int layer ,int x ,int y)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->IsIncludeOrg(x,y)==true){
			c->SetMarkToProceed(layer,true);
		}
	}
}

LearningImage	*LearningInPage::Find(const XDateTime &CreatedTime)	const
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetCreatedTime()==CreatedTime){
			return c;
		}
	}
	return NULL;
}
bool	LearningInPage::DeleteLearning(LearningImage *f)
{
	LearningImageStocker.RemoveList(f);
	delete	f;
	if(SaveLearningDefault(GetLayersBase()->GetSelectedImagePath())==false){
		return false;
	}
	return true;
}

void	LearningInPage::RestoreAllLearningImageTarget(void)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetShowingTarget()==true){
			c->RestoreToTargetOrg();
		}
	}
}


void	LearningInPage::AddShowingLearningImageTarget(LearningImage *f)
{
	int	Cx,Cy;
	f->GetOrgCenter(Cx,Cy);
	AlignmentPacket2D	Packet2D;
	Packet2D.PosXOnTarget=Cx;
	Packet2D.PosYOnTarget=Cy;
	Packet2D.ShiftX=0;
	Packet2D.ShiftY=0;
	GetLayersBase()->GetAlignmentForProcessing(LocalPage ,Packet2D);
	f->SetImageToTargetOrg(&Packet2D);
}

void	LearningInPage::RestoreAllLearningImageMaster(void)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetShowingMaster()==true){
			c->RestoreToMasterOrg();
		}
	}
}

void	LearningInPage::AddShowingLearningImageMaster(LearningImage *f)
{
	f->SetImageToMasterOrg();
}


QString	LearningInPage::MakeFileName(void)
{
	if(GetLayersBase()->GetMasterCode()<=0){
		return /**/"";
	}
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	return   QString(/**/"LearningImage")
			+QString::number(GetLayersBase()->GetMasterCode())
			+QString(/**/"-Page")
			+QString::number(GlobalPage)
			+QString(/**/"-MAC")
			+QString::number(GetLayersBase()->GetMachineID())
			+QString(/**/".blb");
}

QString	LearningInPage::MakeAlgorithmFileName(const QString &AlgoBlobName)
{
	if(GetLayersBase()->GetMasterCode()<=0){
		return /**/"";
	}
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	return   QString(/**/"Learning-")
			+AlgoBlobName
			+QString::number(GetLayersBase()->GetMasterCode())
			+QString(/**/"-Page")
			+QString::number(GlobalPage)
			+QString(/**/"-MAC")
			+QString::number(GetLayersBase()->GetMachineID())
			+QString(/**/".blb");
}

void	LearningInPage::ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteInitialAfterEdit	(EInfo,ProgressStep);
	}
}
void	LearningInPage::ExecuteStartByScanOnly	(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteStartByScanOnly	(ProgressStep);
	}
}
void	LearningInPage::ExecuteStartByInspection(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteStartByInspection	(ProgressStep);
	}
}
void	LearningInPage::ExecuteCaptured	(ListPhasePageLayerPack &CapturedList ,bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteCaptured	(CapturedList,ProgressStep);
	}
}
void	LearningInPage::ExecutePreAlignment		(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecutePreAlignment	(ProgressStep);
	}
}
void	LearningInPage::ExecuteAlignment		(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteAlignment	(ProgressStep);
	}
}
void	LearningInPage::ExecutePreProcessing	(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecutePreProcessing	(ProgressStep);
	}
}
void	LearningInPage::ExecuteProcessing		(ResultInspection *Res ,bool ProgressStep)
{
	bool	Revived=false;
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		bool	ShouldProceed=false;
		for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
			if(c->GetMarkToProceed(layer)==true){
				ShouldProceed=true;
				break;
			}
		}
		if(ShouldProceed==true){
			c->ExecuteProcessing(ProgressStep);
			bool	ResultOk=true;
			for(int layer=0;layer<GetLayerNumb(LocalPage);layer++){
				BoolClass	*B=c->ResultMark.GetItem(layer);
				if(*B==false){
					ResultOk=false;
					break;
				}
			}
			if(ResultOk==true){
				Res->ReviveResult(c);
				Revived=true;
			}
		}
	}
	if(Revived==true){
		Res->SetResultReceivedFlag(LocalPage
								,Res->GetNGCount()
								,Res->IsResultTimeOut()
								,Res->IsResultMaxError());
	}
}
void	LearningInPage::ExecuteProcessingRevived(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteProcessingRevived	(ProgressStep);
	}
}
void	LearningInPage::ExecutePostProcessing	(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecutePostProcessing	(ProgressStep);
	}
}
void	LearningInPage::ExecutePreScanning		(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecutePreScanning	(ProgressStep);
	}
}
void	LearningInPage::ExecuteScanning			(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteScanning	(ProgressStep);
	}
}
void	LearningInPage::ExecutePostScanning		(bool ProgressStep)
{
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecutePostScanning	(ProgressStep);
	}
}

void	LearningInPage::MakeLearningImagePointerContainer(LearningImagePointerContainer &Container)
{
	Container.RemoveAll();
	for(LearningImage *c=LearningImageStocker.GetFirst();c!=NULL;c=c->GetNext()){
		LearningImagePointerList	*a=new LearningImagePointerList(c);
		Container.AppendList(a);
	}
}


//============================================================================================

LearningRegister::LearningRegister(LayersBase *Base)
:ServiceForLayers(Base)
{
}

void	LearningRegister::InitialInSystem(GUICmdPacketBasePointerListContainer &GUICmdContainer)
{
	GUICmdContainer=new GUICmdReqPartialImageForLearn(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdAckPartialImageForLearn(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdReqPartialItems		(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdAckPartialItems		(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdReqItemSize			(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdAckItemSize			(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdRegImageForLearn		(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdReqAlignmentForLearn	(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdAckAlignmentForLearn	(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdReqLearningMenu		(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdAckLearningMenu		(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdReqItemIData			(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
	GUICmdContainer=new GUICmdAckItemIData			(GetLayersBase(),/**/"ANY",/**/"ANY",-1);
}


bool	LearningRegister::RegistForLearning(int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
						, bool OkMode
						,AlgorithmLibraryListContainer &LibList
						,int Priority
						,FlexArea &PointArea)
{
	LayersBase	*LBase=GetLayersBase();
	int	LearningID=SaveForLearning(GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2 ,OkMode,Priority);
	if(LearningID<0){
		return false;
	}

	//FlexArea	hPointArea=PointArea;
	//hPointArea.MoveToNoClip(GlobalX1,GlobalY1);
	//hPointArea.Save(&PBuff);

	//FlexArea	TargetArea=PointArea;
	//TargetArea.MoveToNoClip(Align->ShiftX,Align->ShiftY);

	int	LibCount=0;
	for(LogicDLL *g=LBase->GetLogicDLLBase()->GetFirst();g!=NULL;g=g->GetNext()){
		if(g->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==true){
			IntList GPageList;
			LBase->GetGlobalPage(GlobalX1,GlobalY1,GlobalX2,GlobalY2,GPageList);
			for(IntClass *p=GPageList.GetFirst();p!=NULL;p=p->GetNext()){
				int	GlobalPage=p->GetValue();
				int localpage=LBase->GetLocalPageFromGlobal(GlobalPage);
				DataInPage	*P=LBase->GetPageData(localpage);
				FlexArea	LocalArea=PointArea;
				P->ClipMoveAreaFromGlobal(LocalArea);

				int	ShiftX=0;
				int	ShiftY=0;
				GUICmdReqAlignmentForLearn	RaCmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
				GUICmdAckAlignmentForLearn	AaCmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
				P->GetLocalMatrixFromGlobalInMaster((GlobalX1+GlobalX2)/2,(GlobalY1+GlobalY2)/2,RaCmd.LocalX,RaCmd.LocalY);
				if(RaCmd.Send(GlobalPage,0,AaCmd)==true){
					ShiftX=AaCmd.ShiftX;
					ShiftY=AaCmd.ShiftY;
				}
				LocalArea.MoveToNoClip(-ShiftX,-ShiftY);

				GUICmdReqPartialItems	RCmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
				GUICmdAckPartialItems	ACmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
				RCmd.LocalArea=LocalArea;
				RCmd.AlgoRoot=g->GetDLLRoot();
				RCmd.AlgoName=g->GetDLLName();
				RCmd.LibList	=LibList;
				AlgorithmBase	*Inst=g->GetInstance();
				RCmd.OkMode=OkMode;
				RCmd.AddedX	=-(GlobalX1-ShiftX);
				RCmd.AddedY	=-(GlobalY1-ShiftY);
				//RCmd.AddedX	=-GlobalX1;
				//RCmd.AddedY	=-GlobalY1;
				if(RCmd.Send(GlobalPage,0,ACmd)==true){
					for(ItemDataListWithID *c=ACmd.CData.GetFirst();c!=NULL;c=c->GetNext()){
						LBase->GetDatabaseLoader()->G_InsertLearningParam(*LBase->GetDataBase()
										,LearningID
										,Inst->GetLibType()
										,c->LibID
										,c->IData);
						LibCount++;
					}
				}
			}
		}
	}
	if(LibCount==0){
		RemoveLearning(LearningID);
		return false;
	}
	
	return true;
}

int		LearningRegister::SaveForLearning(int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
											, bool OkMode,int Priority)
{
	LayersBase	*LBase=GetLayersBase();
	if(!LBase->GetDatabaseLoader()){
		return -1;
	}
	if(LBase->GetMasterCode()<0){
		return -1;
	}

	ImageBuffer	**RMaster=NULL;
	ImageBuffer	**RTarget=NULL;
	int	LayerNumb=0;

	XDateTime	CreatedTime=XDateTime::currentDateTime();

	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*P=LBase->GetPageData(page);
		int	x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(GlobalX2<x1 || x2<=GlobalX1 || GlobalY2<y1 || y2<=GlobalY1){
			continue;
		}
		
		int	ShiftX=0;
		int	ShiftY=0;
		GUICmdReqAlignmentForLearn	RaCmd(LBase,/**/"ANY",/**/"ANY",page);
		GUICmdAckAlignmentForLearn	AaCmd(LBase,/**/"ANY",/**/"ANY",page);
		P->GetLocalMatrixFromGlobalInMaster((GlobalX1+GlobalX2)/2,(GlobalY1+GlobalY2)/2,RaCmd.LocalX,RaCmd.LocalY);
		if(RaCmd.Send(page,0,AaCmd)==true){
			ShiftX=AaCmd.ShiftX;
			ShiftY=AaCmd.ShiftY;
		}
		int	mx1=max(x1,GlobalX1-ShiftX);
		int	my1=max(y1,GlobalY1-ShiftY);
		int	mx2=min(x2,GlobalX2-ShiftX);
		int	my2=min(y2,GlobalY2-ShiftY);
		LayerNumb=P->GetLayerNumb();
		RMaster=new ImageBuffer *[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			RMaster[Layer]=new ImageBuffer(ImageBufferMaster,GlobalX2-GlobalX1,GlobalY2-GlobalY1);
			RMaster[Layer]->Memset(0);
		}
		for(int Layer=0;Layer<LayerNumb;Layer++){
			GUICmdReqPartialImageForLearn	RCmd(LBase,/**/"ANY",/**/"ANY",page);
			GUICmdAckPartialImageForLearn	ACmd(LBase,/**/"ANY",/**/"ANY",page);
			P->GetLocalMatrixFromGlobalInMaster(mx1,my1,RCmd.LocalX1,RCmd.LocalY1);
			P->GetLocalMatrixFromGlobalInMaster(mx2,my2,RCmd.LocalX2,RCmd.LocalY2);
			RCmd.LocalPage=LBase->GetLocalPageFromGlobal(page);
			RCmd.Layer=Layer;
			RCmd.CreatedTime=CreatedTime;
			RCmd.Mastered=true;
			if(RCmd.Send(page,0,ACmd)==true && ACmd.ImageOK==true){
				QBuffer	ImgBuff(&ACmd.IData);
				ImgBuff.open(QIODevice::ReadOnly);
				int	Xn=RCmd.LocalX2-RCmd.LocalX1;
				int	Yn=RCmd.LocalY2-RCmd.LocalY1;
				for(int y=0;y<Yn;y++){
					BYTE	*s=RMaster[Layer]->GetY(y);
					ImgBuff.read((char *)s,Xn);
				}
			}
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*P=LBase->GetPageData(page);
		int	x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(GlobalX2<x1 || x2<=GlobalX1 || GlobalY2<y1 || y2<=GlobalY1){
			continue;
		}
		int	mx1=max(x1,GlobalX1);
		int	my1=max(y1,GlobalY1);
		int	mx2=min(x2,GlobalX2);
		int	my2=min(y2,GlobalY2);
		LayerNumb=P->GetLayerNumb();
		RTarget=new ImageBuffer *[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			RTarget[Layer]=new ImageBuffer(ImageBufferTarget,GlobalX2-GlobalX1,GlobalY2-GlobalY1);
			RTarget[Layer]->Memset(0);
		}
		for(int Layer=0;Layer<LayerNumb;Layer++){
			GUICmdReqPartialImageForLearn	RCmd(LBase,/**/"ANY",/**/"ANY",page);
			GUICmdAckPartialImageForLearn	ACmd(LBase,/**/"ANY",/**/"ANY",page);
			P->GetLocalMatrixFromGlobalInMaster(mx1,my1,RCmd.LocalX1,RCmd.LocalY1);
			P->GetLocalMatrixFromGlobalInMaster(mx2,my2,RCmd.LocalX2,RCmd.LocalY2);
			RCmd.LocalPage=LBase->GetLocalPageFromGlobal(page);
			RCmd.Layer=Layer;
			RCmd.Mastered=false;
			if(RCmd.Send(page,0,ACmd)==true && ACmd.ImageOK==true){
				QBuffer	ImgBuff(&ACmd.IData);
				ImgBuff.open(QIODevice::ReadOnly);
				int	Xn=RCmd.LocalX2-RCmd.LocalX1;
				int	Yn=RCmd.LocalY2-RCmd.LocalY1;
				for(int y=0;y<Yn;y++){
					BYTE	*s=RTarget[Layer]->GetY(y);
					ImgBuff.read((char *)s,Xn);
				}
			}
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*P=LBase->GetPageData(page);
		int	x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(GlobalX2<x1 || x2<=GlobalX1 || GlobalY2<y1 || y2<=GlobalY1){
			continue;
		}
		int	mx1=max(x1,GlobalX1);
		int	my1=max(y1,GlobalY1);
		int	mx2=min(x2,GlobalX2);
		int	my2=min(y2,GlobalY2);
			
		GUICmdRegImageForLearn	RCmd(LBase,/**/"ANY",/**/"ANY",page);
		P->GetLocalMatrixFromGlobalInMaster(mx1,my1,RCmd.LocalX1,RCmd.LocalY1);
		P->GetLocalMatrixFromGlobalInMaster(mx2,my2,RCmd.LocalX2,RCmd.LocalY2);
		RCmd.CreatedTime=CreatedTime;
		RCmd.Send(NULL,page,0);
	}
	QBuffer	MBuff;
	MBuff.open(QIODevice::ReadWrite);
	QBuffer	TBuff;
	TBuff.open(QIODevice::ReadWrite);

	QBuffer	PBuff;
	PBuff.open(QIODevice::ReadWrite);
	QBuffer	ABuff;
	ABuff.open(QIODevice::ReadWrite);

	for(int Layer=0;Layer<LayerNumb;Layer++){
		RMaster[Layer]->Save(&MBuff);
		RTarget[Layer]->Save(&TBuff);
	}

	QByteArray tMasterImage	=MBuff.buffer();
	QByteArray tTargetImage	=TBuff.buffer();
	QByteArray tPointData	=PBuff.buffer();
	QByteArray tAlignment	=ABuff.buffer();

	int	SampleType=(OkMode==true)?1:2;

	int	LearningID=LBase->GetDatabaseLoader()->G_GetMaxLearningIDAndInsertEmpty(*LBase->GetDataBase());
	bool	ret=LBase->GetDatabaseLoader()->G_UpdateLearning(*LBase->GetDataBase()
								,LearningID
								,LBase->GetMachineID()
								,LBase->GetMasterCode()
								,SampleType
								,Priority
								,1
								,GlobalX2-GlobalX1,GlobalY2-GlobalY1
								,GlobalX1,GlobalY1
								,LayerNumb
								,tMasterImage
								,tTargetImage
								,tPointData
								,tAlignment);


	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(RMaster!=NULL){
			delete	RMaster[Layer];
		}
		if(RTarget!=NULL){
			delete	RTarget[Layer];
		}
	}
	delete	[]RMaster;
	delete	[]RTarget;

	return LearningID;
}

bool	LearningRegister::RemoveLearning(int LearningID)
{
	bool	ret=GetLayersBase()->GetDatabaseLoader()->G_DeleteLearning(*GetLayersBase()->GetDataBase()
																		,LearningID);
	return ret;
}

bool	LearningRegister::RegistForLearning(int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
						, bool OkMode
						,AlgorithmItemRoot *Item
						,int Priority)
{
	LayersBase	*LBase=GetLayersBase();
	int	LearningID=SaveForLearning(GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2 ,OkMode,Priority);
	if(LearningID<0){
		return false;
	}

	DataInPage	*P=LBase->GetPageData(Item->GetPage());
	int	GlobalPage=LBase->GetGlobalPageFromLocal(Item->GetPage());

	int	ShiftX=0;
	int	ShiftY=0;
	GUICmdReqAlignmentForLearn	RaCmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
	GUICmdAckAlignmentForLearn	AaCmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
	P->GetLocalMatrixFromGlobalInMaster((GlobalX1+GlobalX2)/2,(GlobalY1+GlobalY2)/2,RaCmd.LocalX,RaCmd.LocalY);
	if(RaCmd.Send(GlobalPage,0,AaCmd)==true){
		ShiftX=AaCmd.ShiftX;
		ShiftY=AaCmd.ShiftY;
	}

	GUICmdReqItemIData	RCmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
	GUICmdAckItemIData	ACmd(LBase,/**/"ANY",/**/"ANY",GlobalPage);
	RCmd.OkMode=OkMode;
	RCmd.AddedX	=-(GlobalX1-ShiftX);
	RCmd.AddedY	=-(GlobalY1-ShiftY);
	RCmd.Index.Set(*Item);
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		LBase->GetDatabaseLoader()->G_InsertLearningParam(*LBase->GetDataBase()
						,LearningID
						,Item->GetLibType()
						,Item->GetLibID()
						,ACmd.IData);
	}
	
	return true;
}

bool	LearningRegister::GetLearningArea(int GlobalCx ,int GlobalCy
										 ,int &RetGlobalX1 ,int &RetGlobalY1 ,int &RetGlobalX2 ,int &RetGlobalY2)
{
	LayersBase	*LBase=GetLayersBase();
	RetGlobalX1=99999999;
	RetGlobalY1=99999999;
	RetGlobalX2=-99999999;
	RetGlobalY2=-99999999;

	int	tDotPerLine	=0;
	int	tMaxLines	=0;
	IntList PageList;
	LBase->GetGlobalPage(GlobalCx ,GlobalCy,PageList);
	for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
		int	Page=p->GetValue();
		GUICmdReqItemSize	RCmd(LBase,/**/"ANY",/**/"ANY",Page);
		GUICmdAckItemSize	ACmd(LBase,/**/"ANY",/**/"ANY",Page);
		int	LocalX ,LocalY;
		DataInPage	*P=LBase->GetPageData(Page);
		P->GetLocalMatrixFromGlobalInMaster(GlobalCx ,GlobalCy ,LocalX ,LocalY);
		RCmd.LocalX=LocalX;
		RCmd.LocalY=LocalY;
		if(RCmd.Send(Page,0,ACmd)==true){
			int Gx ,Gy;
			P->GetGlobalMatrixFromLocalInMaster(ACmd.AreaMinX ,ACmd.AreaMinY,Gx ,Gy);
			if(Gx<RetGlobalX1){
				RetGlobalX1=Gx;
			}
			if(Gy<RetGlobalY1){
				RetGlobalY1=Gy;
			}
			P->GetGlobalMatrixFromLocalInMaster(ACmd.AreaMaxX ,ACmd.AreaMaxY,Gx ,Gy);
			if(Gx>RetGlobalX2){
				RetGlobalX2=Gx;
			}
			if(Gy>RetGlobalY2){
				RetGlobalY2=Gy;
			}
			tDotPerLine	=max(tDotPerLine,P->GetDotPerLine()	);
			tMaxLines	=max(tMaxLines	,P->GetMaxLines()	);
		}
	}
	int	W=RetGlobalX2-RetGlobalX1;
	int	H=RetGlobalY2-RetGlobalY1;

	if(W<=0 || H<=0){
		return false;
	}

	if(GetParamGlobal()->MinLearningSize>W){
		int	w=(GetParamGlobal()->MinLearningSize-W+1)/2;
		RetGlobalX1-=w;
		RetGlobalX2+=w;
	}
	if(GetParamGlobal()->MinLearningSize>H){
		int	h=(GetParamGlobal()->MinLearningSize-H+1)/2;
		RetGlobalY1-=h;
		RetGlobalY2+=h;
	}
	if(RetGlobalX1<0){
		RetGlobalX2+=-RetGlobalX1;
		RetGlobalX1=0;
	}
	if(RetGlobalY1<0){
		RetGlobalY2+=-RetGlobalY1;
		RetGlobalY1=0;
	}
	if(GetParamGlobal()->MaxLearningSize<W){
		int	w2=GetParamGlobal()->MaxLearningSize/2;
		RetGlobalX1=GlobalCx-w2;
		RetGlobalX2=GlobalCx+w2;
	}
	if(GetParamGlobal()->MaxLearningSize<H){
		int	h2=GetParamGlobal()->MaxLearningSize/2;
		RetGlobalY1=GlobalCy-h2;
		RetGlobalY2=GlobalCy+h2;
	}
	if(RetGlobalX1<0){
		RetGlobalX2+=-RetGlobalX1;
		RetGlobalX1=0;
	}

	if(RetGlobalY1<0){
		RetGlobalY2+=-RetGlobalY1;
		RetGlobalY1=0;
	}
	//if(RetGlobalX2>=tDotPerLine){
	//	int	dw=RetGlobalX2-tDotPerLine;
	//	RetGlobalX2-=dw;
	//	RetGlobalX1-=dw;
	//}
	//if(RetGlobalY2>=tMaxLines){
	//	int	dh=RetGlobalY2-tMaxLines;
	//	RetGlobalY2-=dh;
	//	RetGlobalY1-=dh;
	//}

	return true;
}
int		LearningRegister::GetLearningMenu(int LibType
							,LearningMenu LearningMenuDim[]
							,int MaxMenuDim)
{
	GUICmdReqLearningMenu	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",0);
	GUICmdAckLearningMenu	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",0);
	RCmd.LibType=LibType;
	int	N=0;
	if(RCmd.Send(0,0,ACmd)==true){
		for(int i=0;i<ACmd.MenuDimNumb && i<MaxMenuDim;i++){
			LearningMenuDim[i]=ACmd.LearningMenuDim[i];
			N++;
		}
	}
	return N;
}
//========================================================================================

LearningImagePointerList::LearningImagePointerList(LearningImage *p)
{	
	Pointer=p;	
	GlobalPage=p->GetGlobalPage();	
	CreatedTime=p->GetCreatedTime();
	GetOrgLocalArea(OrgLocalX1 ,OrgLocalY1 ,OrgLocalX2 ,OrgLocalY2);
}

LearningImagePointerList	&LearningImagePointerList::operator=(LearningImagePointerList &src)
{
	Pointer		=src.Pointer;
	GlobalPage	=src.GlobalPage;
	CreatedTime	=src.CreatedTime;
	OrgLocalX1	=src.OrgLocalX1;
	OrgLocalY1	=src.OrgLocalY1;
	OrgLocalX2	=src.OrgLocalX2;
	OrgLocalY2	=src.OrgLocalY2;

	return *this;
}

void	LearningImagePointerList::GetOrgLocalArea(int &x1, int &y1 , int &x2 ,int &y2)
{
	x1=OrgLocalX1;
	y1=OrgLocalY1;
	x2=OrgLocalX2;
	y2=OrgLocalY2;
}

bool	LearningImagePointerList::Load(QIODevice *f ,LayersBase *Base)
{
	bool	ExistPointer;
	if(::Load(f,ExistPointer)==false){
		return false;
	}
	Pointer=NULL;
	if(ExistPointer==true){
		if(::Load(f,CreatedTime)==false){
			return false;
		}
		if(::Load(f,GlobalPage)==false){
			return false;
		}
		if(::Load(f,OrgLocalX1)==false){
			return false;
		}
		if(::Load(f,OrgLocalY1)==false){
			return false;
		}
		if(::Load(f,OrgLocalX2)==false){
			return false;
		}
		if(::Load(f,OrgLocalY2)==false){
			return false;
		}
		int	LocalPage=Base->GetLocalPageFromGlobal(GlobalPage);
		DataInPage	*Pg=Base->GetPageData(LocalPage);
		if(Pg!=NULL){
			Pointer=Pg->Find(CreatedTime);
		}
	}
	return true;
}

bool	LearningImagePointerList::Save(QIODevice *f)
{
	bool	ExistPointer;
	if(Pointer==NULL){
		ExistPointer=false;
		if(::Save(f,ExistPointer)==false){
			return false;
		}
	}
	else{
		ExistPointer=true;
		if(::Save(f,ExistPointer)==false){
			return false;
		}
		XDateTime	tm=Pointer->GetCreatedTime();
		if(::Save(f,tm)==false){
			return false;
		}
		if(::Save(f,Pointer->GetGlobalPage())==false){
			return false;
		}
		if(::Save(f,OrgLocalX1)==false){
			return false;
		}
		if(::Save(f,OrgLocalY1)==false){
			return false;
		}
		if(::Save(f,OrgLocalX2)==false){
			return false;
		}
		if(::Save(f,OrgLocalY2)==false){
			return false;
		}
	}
	return true;
}

LearningImagePointerContainer	&LearningImagePointerContainer::operator=(LearningImagePointerContainer &src)
{
	RemoveAll();
	return operator+=(src);
}

LearningImagePointerContainer	&LearningImagePointerContainer::operator+=(LearningImagePointerContainer &src)
{
	for(LearningImagePointerList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LearningImagePointerList	*b=new LearningImagePointerList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

bool	LearningImagePointerContainer::Load(QIODevice *f,LayersBase *Base)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		LearningImagePointerList *a=new LearningImagePointerList();
		if(a->Load(f,Base)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

bool	LearningImagePointerContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(LearningImagePointerList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
//========================================================================================
LearningParamInDB::LearningParamInDB(void)
{
	ParamID	=-1;
	LibType	=-1;
	LibID	=-1;
}
LearningParamInDB::LearningParamInDB(const LearningParamInDB &src)
{
	ParamID		=src.ParamID	;
	LibType		=src.LibType	;
	LibID		=src.LibID		;
	ParamData	=src.ParamData	;
}

LearningParamInDB	&LearningParamInDB::operator=(const LearningParamInDB &src)
{
	ParamID		=src.ParamID	;
	LibType		=src.LibType	;
	LibID		=src.LibID		;
	//ParamData	=src.ParamData	;
	return *this;
}
bool	LearningParamInDB::operator==(const LearningParamInDB &src)
{
	if(ParamID	!=src.ParamID	)	return false;
	if(LibType	!=src.LibType	)	return false;
	if(LibID	!=src.LibID		)	return false;
	if(ParamData!=src.ParamData	)	return false;
	return true;
}
bool	LearningParamInDB::operator!=(const LearningParamInDB &src)
{
	return !operator==(src);
}

bool	LearningParamInDB::Save(QIODevice *f)
{
	if(::Save(f,ParamID	 )==false)	return false;
	if(::Save(f,LibType	 )==false)	return false;
	if(::Save(f,LibID	 )==false)	return false;
	if(::Save(f,ParamData)==false)	return false;
	return true;
}
bool	LearningParamInDB::Load(QIODevice *f)
{
	if(::Load(f,ParamID	 )==false)	return false;
	if(::Load(f,LibType	 )==false)	return false;
	if(::Load(f,LibID	 )==false)	return false;
	if(::Load(f,ParamData)==false)	return false;
	return true;
}

LearningInDB::LearningInDB(void)
{
	LearningID	=-1;
	MachineID	=-1;
	MasterCode	=-1;
	SampleType	=-1;
	Priority	=-1;
	Version		=-1;
	XSize		=-1;
	YSize		=-1;
	Layer		=-1;
	Result		=0;
	LayerForCalc	=NULL;
	EPointForCalc	=NULL;
}
LearningInDB::LearningInDB(const LearningInDB &src)
{
	LearningID	=src.LearningID	;
	MachineID	=src.MachineID	;
	UpdateTime	=src.UpdateTime	;
	MasterCode	=src.MasterCode	;
	SampleType	=src.SampleType	;
	Priority	=src.Priority	;
	Version		=src.Version	;	
	XSize		=src.XSize		;
	YSize		=src.YSize		;
	Layer		=src.Layer		;
	MasterImage	=src.MasterImage;	
	TargetImage	=src.TargetImage;	
	PointData	=src.PointData	;
	Alignment	=src.Alignment	;
	Result		=src.Result		;

	for(LearningParamInDB *a=src.NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
		LearningParamInDB *d=new LearningParamInDB(*a);
		AppendList(d);
	}
}

LearningInDB::~LearningInDB(void)
{
	if(LayerForCalc!=NULL){
		delete	LayerForCalc;
		LayerForCalc=NULL;
	}
	if(EPointForCalc!=NULL){
		delete	EPointForCalc;
		EPointForCalc=NULL;
	}
}

LearningInDB	&LearningInDB::operator=(const LearningInDB &src)
{
	LearningID	=src.LearningID	;
	MachineID	=src.MachineID	;
	UpdateTime	=src.UpdateTime	;
	MasterCode	=src.MasterCode	;
	SampleType	=src.SampleType	;
	Priority	=src.Priority	;
	Version		=src.Version	;	
	XSize		=src.XSize		;
	YSize		=src.YSize		;
	Layer		=src.Layer		;
	MasterImage	=src.MasterImage;	
	TargetImage	=src.TargetImage;	
	PointData	=src.PointData	;
	Alignment	=src.Alignment	;
	Result		=src.Result		;

	RemoveAll();
	for(LearningParamInDB *a=src.NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
		LearningParamInDB *d=new LearningParamInDB(*a);
		AppendList(d);
	}
	return *this;
}
LearningParamInDB	*LearningInDB::Create(void)
{
	return new LearningParamInDB();
}
bool	LearningInDB::operator==(const LearningInDB &src)
{
	NPListPointerForComparePack<LearningParamInDB>	Sa;
	NPListPointerForComparePack<LearningParamInDB>	Sb;

	Sa.Set(*this);
	Sb.Set(src);

	//if(Sa!=Sb)	return false;

	if(LearningID	!=src.LearningID	)	return false;
	if(MachineID	!=src.MachineID		)	return false;
	if(UpdateTime	!=src.UpdateTime	)	return false;
	if(MasterCode	!=src.MasterCode	)	return false;
	if(SampleType	!=src.SampleType	)	return false;
	if(Priority		!=src.Priority		)	return false;
	if(Version		!=src.Version		)	return false;
	if(XSize		!=src.XSize			)	return false;
	if(YSize		!=src.YSize			)	return false;
	if(Layer		!=src.Layer			)	return false;
	if(MasterImage	!=src.MasterImage	)	return false;
	if(TargetImage	!=src.TargetImage	)	return false;
	if(PointData	!=src.PointData		)	return false;
	if(Alignment	!=src.Alignment		)	return false;

	return true;
}
bool	LearningInDB::operator!=(const LearningInDB &src)
{
	return !operator==(src);
}

bool	LearningInDB::Save(QIODevice *f)
{
	if(::Save(f,LearningID	)==false)	return false;
	if(::Save(f,MachineID	)==false)	return false;
	if(::Save(f,UpdateTime	)==false)	return false;
	if(::Save(f,MasterCode	)==false)	return false;
	if(::Save(f,SampleType	)==false)	return false;
	if(::Save(f,Priority	)==false)	return false;
	if(::Save(f,Version		)==false)	return false;
	if(::Save(f,XSize		)==false)	return false;
	if(::Save(f,YSize		)==false)	return false;
	if(::Save(f,Layer		)==false)	return false;
	if(::Save(f,MasterImage	)==false)	return false;
	if(::Save(f,TargetImage	)==false)	return false;
	if(::Save(f,PointData	)==false)	return false;
	if(::Save(f,Alignment	)==false)	return false;

	if(NPListPackSaveLoad<LearningParamInDB>::Save(f)==false){
		return false;
	}
	return true;
}
bool	LearningInDB::Load(QIODevice *f)
{
	if(::Load(f,LearningID	)==false)	return false;
	if(::Load(f,MachineID	)==false)	return false;
	if(::Load(f,UpdateTime	)==false)	return false;
	if(::Load(f,MasterCode	)==false)	return false;
	if(::Load(f,SampleType	)==false)	return false;
	if(::Load(f,Priority	)==false)	return false;
	if(::Load(f,Version		)==false)	return false;
	if(::Load(f,XSize		)==false)	return false;
	if(::Load(f,YSize		)==false)	return false;
	if(::Load(f,Layer		)==false)	return false;
	if(::Load(f,MasterImage	)==false)	return false;
	if(::Load(f,TargetImage	)==false)	return false;
	if(::Load(f,PointData	)==false)	return false;
	if(::Load(f,Alignment	)==false)	return false;

	if(NPListPackSaveLoad<LearningParamInDB>::Load(f)==false){
		return false;
	}
	return true;
}

LearningInDBAll::LearningInDBAll(void)
{
}
LearningInDBAll::LearningInDBAll(const LearningInDBAll &src)
{
	for(LearningInDB *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LearningInDB *d=new LearningInDB(*a);
		AppendList(d);
	}
}

LearningInDBAll	&LearningInDBAll::operator=(const LearningInDBAll &src)
{
	RemoveAll();
	for(LearningInDB *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LearningInDB *d=new LearningInDB(*a);
		AppendList(d);
	}
	return *this;
}

bool	LearningInDBAll::operator==(const LearningInDBAll &src)
{
	NPListPointerForComparePack<LearningInDB>	Sa;
	NPListPointerForComparePack<LearningInDB>	Sb;

	Sa.Set(*this);
	Sb.Set(src);

	if(Sa==Sb)	return true;
	return false;
}
bool	LearningInDBAll::operator!=(const LearningInDBAll &src)
{
	return !operator==(src);
}

LearningInDB	*LearningInDBAll::Search(int LearningID)
{
	for(LearningInDB *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LearningID==LearningID){
			return a;
		}
	}
	return NULL;
}

bool	LearningInDBAll::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)	return false;

	for(LearningInDB *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)	return false;
	}
	return true;
}
bool	LearningInDBAll::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)	return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		LearningInDB *a=new LearningInDB();
		if(a->Load(f)==false)	return false;
		AppendList(a);
	}
	return true;
}

template<class T>
LearningInDBThresholdParam<T>::~LearningInDBThresholdParam<T>(void)
{
	Offset	=0;
	Value	=0;
}
template<class T>
void	LearningInDBThresholdParam<T>::SetLearningParam(AlgorithmThreshold *Thr ,T *value,T minValue,T maxValue	,double stepoffset,double stepmultiply)
{
	Offset=((char *)value)-((char *)Thr);

	Value		=*value;
	MinValue	=minValue;
	MaxValue	=maxValue;
	StepOffset	=stepoffset;
	StepMultiply=stepmultiply;
}
template<class T>
void	LearningInDBThresholdParam<T>::StepLoose(AlgorithmThreshold *Thr,double Level)
{
	T	tvalue	;
	tvalue=Value;	
	tvalue=tvalue+StepOffset*Level+tvalue*StepMultiply*Level;
	if(MinValue<=tvalue && tvalue<=MaxValue){
		Value=tvalue;
	}
	else if(tvalue<=MaxValue){
		Value=MinValue;
	}
	else if(MinValue<=tvalue){
		Value=MaxValue;
	}
	*((T *)(((char *)Thr)+Offset))=Value;
}
template<class T>
void	LearningInDBThresholdParam<T>::StepStrict(AlgorithmThreshold *Thr,double Level)
{
	T	tvalue	;
	tvalue=Value;	
	tvalue=tvalue-StepOffset*Level-tvalue*StepMultiply*Level;
	if(MinValue<=tvalue && tvalue<=MaxValue){
		Value=tvalue;
	}
	else if(tvalue<=MaxValue){
		Value=MinValue;
	}
	else if(MinValue<=tvalue){
		Value=MaxValue;
	}
	*((T *)(((char *)Thr)+Offset))=Value;
}
template<class T>	
void	LearningInDBThresholdParam<T>::BackupValue(AlgorithmThreshold *Thr)
{
	Value=*((T *)(((char *)Thr)+Offset));
	OldValue=Value;
}
template<class T>	
void	LearningInDBThresholdParam<T>::RestoreValue(AlgorithmThreshold *Thr)
{
	Value=OldValue;
	*((T *)(((char *)Thr)+Offset))=OldValue;
}

LearningInDBThresholdGroup::LearningInDBThresholdGroup(void)
{
}

void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,char *value	,char MinValue,char MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<char>	*p=new LearningInDBThresholdParam<char>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,BYTE *value	,BYTE MinValue,BYTE MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<BYTE>	*p=new LearningInDBThresholdParam<BYTE>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,short *value	,short MinValue,short MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<short>	*p=new LearningInDBThresholdParam<short>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,WORD *value	,WORD MinValue,WORD MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<WORD>	*p=new LearningInDBThresholdParam<WORD>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,int32 *value	,int32 MinValue,int32 MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<int32>	*p=new LearningInDBThresholdParam<int32>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,DWORD *value	,DWORD MinValue,DWORD MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<DWORD>	*p=new LearningInDBThresholdParam<DWORD>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,int64 *value	,int64 MinValue,int64 MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<int64>	*p=new LearningInDBThresholdParam<int64>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,float *value	,float MinValue,float MaxValue	,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<float>	*p=new LearningInDBThresholdParam<float>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}
void	LearningInDBThresholdGroup::AddLearningParam(AlgorithmThreshold *Thr ,double *value	,double MinValue,double MaxValue,double stepoffset,double stepmultiply	)
{
	LearningInDBThresholdParam<double>	*p=new LearningInDBThresholdParam<double>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	Container.AppendList(p);
}

void	LearningInDBThresholdGroup::StepStrict(AlgorithmThreshold *Thr,double Level)
{
	for(LearningInDBThresholdParamBase *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		p->StepStrict(Thr,Level);
	}
}
void	LearningInDBThresholdGroup::StepLoose (AlgorithmThreshold *Thr,double Level)
{
	for(LearningInDBThresholdParamBase *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		p->StepLoose(Thr,Level);
	}
}
void	LearningInDBThresholdGroup::BackupValue(AlgorithmThreshold *Thr)
{
	for(LearningInDBThresholdParamBase *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		p->BackupValue(Thr);
	}
}
void	LearningInDBThresholdGroup::RestoreValue(AlgorithmThreshold *Thr)
{
	for(LearningInDBThresholdParamBase *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		p->RestoreValue(Thr);
	}
}
LearningInDBThreshold::LearningInDBThreshold(void)
{
}

void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,char *value,char MinValue,char MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<char>	*p=new LearningInDBThresholdParam<char>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,BYTE *value,BYTE MinValue,BYTE MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<BYTE>	*p=new LearningInDBThresholdParam<BYTE>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,short *value,short MinValue,short MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<short>	*p=new LearningInDBThresholdParam<short>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,WORD *value,WORD MinValue,WORD MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<WORD>	*p=new LearningInDBThresholdParam<WORD>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,int32 *value,int32 MinValue,int32 MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<int32>	*p=new LearningInDBThresholdParam<int32>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,DWORD *value,DWORD MinValue,DWORD MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<DWORD>	*p=new LearningInDBThresholdParam<DWORD>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,int64 *value,int64 MinValue,int64 MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<int64>	*p=new LearningInDBThresholdParam<int64>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,float *value,float MinValue,float MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<float>	*p=new LearningInDBThresholdParam<float>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
void	LearningInDBThreshold::AddLearningParam(AlgorithmThreshold *Thr ,double *value,double MinValue,double MaxValue	,double stepoffset,double stepmultiply)
{
	LearningInDBThresholdParam<double>	*p=new LearningInDBThresholdParam<double>();
	p->SetLearningParam(Thr,value,MinValue,MaxValue,stepoffset,stepmultiply);
	AppendList(p);
}
//========================================================================================

GUICmdReqPartialImageForLearn::GUICmdReqPartialImageForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqPartialImageForLearn::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false){
		return false;
	}
	if(::Load(f,LocalY1)==false){
		return false;
	}
	if(::Load(f,LocalX2)==false){
		return false;
	}
	if(::Load(f,LocalY2)==false){
		return false;
	}
	if(::Load(f,LocalPage)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Mastered)==false){
		return false;
	}
	if(::Load(f,CreatedTime)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqPartialImageForLearn::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false){
		return false;
	}
	if(::Save(f,LocalY1)==false){
		return false;
	}
	if(::Save(f,LocalX2)==false){
		return false;
	}
	if(::Save(f,LocalY2)==false){
		return false;
	}
	if(::Save(f,LocalPage)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Mastered)==false){
		return false;
	}
	if(::Save(f,CreatedTime)==false){
		return false;
	}
	return true;
}

void	GUICmdReqPartialImageForLearn::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPartialImageForLearn	*SendBack=GetSendBack(GUICmdAckPartialImageForLearn,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);

	SendBack->BuildData(LocalX1,LocalY1,LocalX2,LocalY2,LocalPage,Layer,Mastered);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckPartialImageForLearn::GUICmdAckPartialImageForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckPartialImageForLearn::Load(QIODevice *f)
{
	if(::Load(f,IData)==false){
		return false;
	}
	if(::Load(f,ImageOK)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckPartialImageForLearn::Save(QIODevice *f)
{
	if(::Save(f,IData)==false){
		return false;
	}
	if(::Save(f,ImageOK)==false){
		return false;
	}
	return true;
}

void	GUICmdAckPartialImageForLearn::BuildData(int LocalX1,int LocalY1,int LocalX2,int LocalY2
											,int LocalPage,int Layer
											,bool Mastered)
{
	DataInPage	*P=GetLayersBase()->GetPageData(LocalPage);
	if(P==NULL){
		return;
	}
	DataInLayer	*L=P->GetLayerData(Layer);
	if(L==NULL){
		return;
	}
	if(Mastered==true){
		ImageBuffer		&Img=L->GetMasterBuff();
		if(Img.IsNull()==false){
			QBuffer	Buff(&IData);
			Buff.open(QIODevice::ReadWrite);
			for(int y=LocalY1;y<LocalY2;y++){
				BYTE	*s=Img.GetY(y);
				Buff.write((const char *)(s+LocalX1),LocalX2-LocalX1);
			}
			ImageOK=true;
		}
		else{
			ImageOK=true;
		}
	}
	else{
		ImageBuffer		&Img=L->GetTargetBuff();
		if(Img.IsNull()==false){
			QBuffer	Buff(&IData);
			Buff.open(QIODevice::ReadWrite);
			for(int y=LocalY1;y<LocalY2;y++){
				BYTE	*s=Img.GetY(y);
				Buff.write((const char *)(s+LocalX1),LocalX2-LocalX1);
			}
			ImageOK=true;
		}
		else{
			ImageOK=true;
		}
	}
}

//========================================================================================

GUICmdReqPartialItems::GUICmdReqPartialItems(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqPartialItems::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false){
		return false;
	}
	if(LibList.Load(f)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,AddedX)==false){
		return false;
	}
	if(::Load(f,AddedY)==false){
		return false;
	}
	if(::Load(f,OkMode)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqPartialItems::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false){
		return false;
	}
	if(LibList.Save(f)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,AddedX)==false){
		return false;
	}
	if(::Save(f,AddedY)==false){
		return false;
	}
	if(::Save(f,OkMode)==false){
		return false;
	}
	return true;
}

void	GUICmdReqPartialItems::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPartialItems	*SendBack=GetSendBack(GUICmdAckPartialItems,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);
	AlgorithmBase	*base=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(base!=NULL){
		AlgorithmInPageRoot	*P=base->GetPageData(localPage);
		SendBack->BuildData(P,LocalArea,LibList,AddedX,AddedY,OkMode);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

bool	ItemDataListWithID::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Error)==false){
		return false;
	}
	if(::Save(f,IData)==false){
		return false;
	}
	return true;
}
bool	ItemDataListWithID::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Error)==false){
		return false;
	}
	if(::Load(f,IData)==false){
		return false;
	}
	return true;
}


bool	ItemDataListWithIDContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(ItemDataListWithID *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ItemDataListWithIDContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ItemDataListWithID	*c=new ItemDataListWithID();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}

bool	ItemDataWithPhasePageLayer::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,Data)==false){
		return false;
	}
	return true;
}
bool	ItemDataWithPhasePageLayer::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,Data)==false){
		return false;
	}
	return true;
}

ItemDataWithPhasePageLayer	*ItemDataWithPhasePageLayerContainer::Create(void)
{
	return new ItemDataWithPhasePageLayer();
}


GUICmdAckPartialItems::GUICmdAckPartialItems(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckPartialItems::Load(QIODevice *f)
{
	if(CData.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckPartialItems::Save(QIODevice *f)
{
	if(CData.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdAckPartialItems::BuildData(AlgorithmInPageRoot *P
										,FlexArea &LocalArea
										,AlgorithmLibraryListContainer &LibList
										,int AddedX,int AddedY
										,bool OkMode)
{
	P->SaveItemsForLearning(CData,LocalArea,LibList,AddedX,AddedY,OkMode);
}

void	GUICmdAckPartialItems::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//===============================================================================================
GUICmdReqItemSize::GUICmdReqItemSize(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LocalX=0;
	LocalY=0;
}

bool	GUICmdReqItemSize::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqItemSize::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	return true;
}

void	GUICmdReqItemSize::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemSize	*SendBack=GetSendBack(GUICmdAckItemSize,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);
	SendBack->AreaMinX= 99999999;
	SendBack->AreaMinY= 99999999;
	SendBack->AreaMaxX=-99999999;
	SendBack->AreaMaxY=-99999999;

	for(LogicDLL *g=GetLayersBase()->GetLogicDLLBase()->GetFirst();g!=NULL;g=g->GetNext()){
		if(g->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==true){
			AlgorithmBase	*L=g->GetInstance();
			AlgorithmInPageRoot		*P=L->GetPageData(localPage);
			NPListPack<ItemPointerList> Items;
			P->GetPointedItems(LocalX,LocalY,Items);
			for(ItemPointerList *k=Items.GetFirst();k!=NULL;k=k->GetNext()){
				int	x1,y1,x2,y2;
				AlgorithmItemRoot	*Item=k->GetItem();
				ResultInItemRoot	*R=Item->GetCurrentResult();
				if(R!=NULL){
					for(ResultPosList *r=R->GetPosList().GetFirst();r!=NULL;r=r->GetNext()){
						if(r->NGShape.IsInclude(LocalX,LocalY)==true){
							SendBack->AreaMinX=min(SendBack->AreaMinX,r->NGShape.GetMinX());
							SendBack->AreaMinY=min(SendBack->AreaMinY,r->NGShape.GetMinY());
							SendBack->AreaMaxX=max(SendBack->AreaMaxX,r->NGShape.GetMaxX());
							SendBack->AreaMaxY=max(SendBack->AreaMaxY,r->NGShape.GetMaxY());
						}
					}
				}
				else{
					k->ItemPointer->GetXY(x1,y1,x2,y2);
					SendBack->AreaMinX=min(SendBack->AreaMinX,x1);
					SendBack->AreaMinY=min(SendBack->AreaMinY,y1);
					SendBack->AreaMaxX=max(SendBack->AreaMaxX,x2);
					SendBack->AreaMaxY=max(SendBack->AreaMaxY,y2);
				}
			}
		}
	}
	if(SendBack->AreaMinX>SendBack->AreaMaxX){
		for(int i=0;i<GetLayersBase()->GetShadowChildrenCount();i++){
			LayersBase	*LBase=GetLayersBase()->GetShadowChildren(i)->GetTreeLayersBase();
			for(LogicDLL *g=LBase->GetLogicDLLBase()->GetFirst();g!=NULL;g=g->GetNext()){
				if(g->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==true){
					AlgorithmBase	*L=g->GetInstance();
					AlgorithmInPageRoot		*P=L->GetPageData(localPage);
					NPListPack<ItemPointerList> Items;
					int	tLocalX=LocalX;
					int	tLocalY=LocalY;
					LBase->ConvertToLocal(tLocalX,tLocalY);
					P->GetPointedItems(tLocalX,tLocalY,Items);
					for(ItemPointerList *k=Items.GetFirst();k!=NULL;k=k->GetNext()){
						AlgorithmItemRoot	*Item=k->GetItem();
						ResultInItemRoot	*R=Item->GetCurrentResult();
						if(R!=NULL){
							for(ResultPosList *r=R->GetPosList().GetFirst();r!=NULL;r=r->GetNext()){
								if(r->NGShape.IsInclude(tLocalX,tLocalY)==true){
									int	x1=r->NGShape.GetMinX();
									int	y1=r->NGShape.GetMinY();
									int	x2=r->NGShape.GetMaxX();
									int	y2=r->NGShape.GetMaxY();
									LBase->ConvertToTop(x1,y1);
									LBase->ConvertToTop(x2,y2);
									SendBack->AreaMinX=min(SendBack->AreaMinX,x1);
									SendBack->AreaMinY=min(SendBack->AreaMinY,y1);
									SendBack->AreaMaxX=max(SendBack->AreaMaxX,x2);
									SendBack->AreaMaxY=max(SendBack->AreaMaxY,y2);
								}
							}
						}
						else{
							int	x1,y1,x2,y2;
							k->ItemPointer->GetXY(x1,y1,x2,y2);
							LBase->ConvertToTop(x1,y1);
							LBase->ConvertToTop(x2,y2);
							SendBack->AreaMinX=min(SendBack->AreaMinX,x1);
							SendBack->AreaMinY=min(SendBack->AreaMinY,y1);
							SendBack->AreaMaxX=max(SendBack->AreaMaxX,x2);
							SendBack->AreaMaxY=max(SendBack->AreaMaxY,y2);
						}
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemSize::GUICmdAckItemSize(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemSize::Load(QIODevice *f)
{
	if(::Load(f,AreaMinX)==false){
		return false;
	}
	if(::Load(f,AreaMinY)==false){
		return false;
	}
	if(::Load(f,AreaMaxX)==false){
		return false;
	}
	if(::Load(f,AreaMaxY)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckItemSize::Save(QIODevice *f)
{
	if(::Save(f,AreaMinX)==false){
		return false;
	}
	if(::Save(f,AreaMinY)==false){
		return false;
	}
	if(::Save(f,AreaMaxX)==false){
		return false;
	}
	if(::Save(f,AreaMaxY)==false){
		return false;
	}
	return true;
}

//===============================================================================================

GUICmdRegImageForLearn::GUICmdRegImageForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdRegImageForLearn::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false){
		return false;
	}
	if(::Load(f,LocalY1)==false){
		return false;
	}
	if(::Load(f,LocalX2)==false){
		return false;
	}
	if(::Load(f,LocalY2)==false){
		return false;
	}
	if(::Load(f,CreatedTime)==false){
		return false;
	}
	return true;
}
bool	GUICmdRegImageForLearn::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false){
		return false;
	}
	if(::Save(f,LocalY1)==false){
		return false;
	}
	if(::Save(f,LocalX2)==false){
		return false;
	}
	if(::Save(f,LocalY2)==false){
		return false;
	}
	if(::Save(f,CreatedTime)==false){
		return false;
	}
	return true;
}

static	int	SListSortFunc(const void *a ,const void *b)
{
	LogicDLL *aL=((LogicDLL **)a)[0];
	LogicDLL *bL=((LogicDLL **)b)[0];
	if(aL->GetPriority(PriorityType_ExecuteAutoGeneration)<bL->GetPriority(PriorityType_ExecuteAutoGeneration)){
		return -1;
	}
	else if(aL->GetPriority(PriorityType_ExecuteAutoGeneration)>bL->GetPriority(PriorityType_ExecuteAutoGeneration)){
		return 1;
	}
	return 0;
}

void	GUICmdRegImageForLearn::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	int	Cx=(LocalX1+LocalX2)/2;
	int	Cy=(LocalY1+LocalY2)/2;
	AlignmentPacket2D	Packet2D;
	Packet2D.PosXOnTarget=Cx;
	Packet2D.PosYOnTarget=Cy;
	Packet2D.ShiftX=0;
	Packet2D.ShiftY=0;
	GetLayersBase()->GetAlignmentForProcessing(localPage ,Packet2D);
	LearningImage *c;
	c=GetLayersBase()->GetPageData(localPage)->SetAllocImage(CreatedTime,GlobalPage
													, LocalX1 ,LocalY1 ,LocalX2 ,LocalY2
													, &Packet2D);
	if(c!=NULL){
		LogicDLL *SList[10000];
		int	SListNumb=0;
		for(LogicDLL *s=GetLayersBase()->GetLogicDLLBase()->GetFirst();s!=NULL;s=s->GetNext()){
			SList[SListNumb]=s;
			SListNumb++;
		}
		QSort(SList,SListNumb,sizeof(SList[0]),SListSortFunc);

		for(int i=0;i<SListNumb;i++){
			LogicDLL *s=SList[i];
			AlgorithmBase	*si=s->GetInstance();
			for(LogicDLL *d=c->GetLearningLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
				if(d->GetDLLRoot()==s->GetDLLRoot() && d->GetDLLName()==s->GetDLLName()){
					AlgorithmBase	*di=d->GetInstance();
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					si->PipeOutAutoGenerationForLearning(&Buff,localPage ,LocalX1, LocalY1, LocalX2 ,LocalY2);
					Buff.seek(0);
					di->PipeInAutoGenerationForLearning (&Buff,localPage ,LocalX1, LocalY1, LocalX2 ,LocalY2);
				}
			}
		}
	}
}

//===============================================================================================
GUICmdReqAlignmentForLearn::GUICmdReqAlignmentForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentForLearn::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	return true;
}
bool	GUICmdReqAlignmentForLearn::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;
	return true;
}

void	GUICmdReqAlignmentForLearn::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentForLearn	*SendBack=GetSendBack(GUICmdAckAlignmentForLearn,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);
	SendBack->ShiftX= 0;
	SendBack->ShiftY= 0;

	AlignmentPacket2D	Packet2D;
	Packet2D.PosXOnTarget=LocalX;
	Packet2D.PosYOnTarget=LocalY;
	Packet2D.ShiftX=0;
	Packet2D.ShiftY=0;
	GetLayersBase()->GetAlignmentForProcessing(localPage ,Packet2D);

	SendBack->ShiftX=Packet2D.ShiftX;
	SendBack->ShiftY=Packet2D.ShiftY;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentForLearn::GUICmdAckAlignmentForLearn(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlignmentForLearn::Load(QIODevice *f)
{
	if(::Load(f,ShiftX)==false)	return false;
	if(::Load(f,ShiftY)==false)	return false;
	return true;
}
bool	GUICmdAckAlignmentForLearn::Save(QIODevice *f)
{
	if(::Save(f,ShiftX)==false)	return false;
	if(::Save(f,ShiftY)==false)	return false;
	return true;
}

//===============================================================================================
LearningMenu	&LearningMenu::operator=(const LearningMenu &src)
{
	MenuMessage	=src.MenuMessage;
	MenuID		=src.MenuID;
	OkMode		=src.OkMode;
	return *this;
}
bool	LearningMenu::Save(QIODevice *f)
{
	if(::Save(f,MenuMessage)==false)	return false;
	if(::Save(f,MenuID)==false)			return false;
	if(::Save(f,OkMode)==false)			return false;
	return true;
}

bool	LearningMenu::Load(QIODevice *f)
{
	if(::Load(f,MenuMessage)==false)	return false;
	if(::Load(f,MenuID)==false)			return false;
	if(::Load(f,OkMode)==false)			return false;
	return true;
}

LearningResource	&LearningResource::operator=(const LearningResource &src)
{
	x1=src.x1;
	y1=src.y1;
	x2=src.x2;
	y2=src.y2;
	Image=src.Image;
	Cause[0]=src.Cause[0];
	Cause[1]=src.Cause[1];
	DoubleCause=src.DoubleCause;
	Hx=src.Hx;
	Hy=src.Hy;
	return *this;
}

bool	LearningResource::Save(QIODevice *f)
{
	if(::Save(f,x1)==false)		return false;
	if(::Save(f,y1)==false)		return false;
	if(::Save(f,x2)==false)		return false;
	if(::Save(f,y2)==false)		return false;
	if(::Save(f,Image)==false)	return false;
	if(::Save(f,Cause[0])==false)		return false;
	if(::Save(f,Cause[1])==false)		return false;
	if(::Save(f,DoubleCause)==false)	return false;
	if(::Save(f,Hx)==false)	return false;
	if(::Save(f,Hy)==false)	return false;

	return true;
}

bool	LearningResource::Load(QIODevice *f)
{
	if(::Load(f,x1)==false)		return false;
	if(::Load(f,y1)==false)		return false;
	if(::Load(f,x2)==false)		return false;
	if(::Load(f,y2)==false)		return false;
	if(::Load(f,Image)==false)	return false;
	if(::Load(f,Cause[0])==false)		return false;
	if(::Load(f,Cause[1])==false)		return false;
	if(::Load(f,DoubleCause)==false)	return false;
	if(::Load(f,Hx)==false)	return false;
	if(::Load(f,Hy)==false)	return false;

	return true;
}


GUICmdReqLearningMenu::GUICmdReqLearningMenu(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLearningMenu::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	return true;
}
bool	GUICmdReqLearningMenu::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	return true;
}

void	GUICmdReqLearningMenu::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckLearningMenu	*SendBack=GetSendBack(GUICmdAckLearningMenu,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);
	
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		SendBack->MenuDimNumb=ABase->GetLearningMenu(SendBack->LearningMenuDim,100);
	}
	else{
		SendBack->MenuDimNumb=0;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckLearningMenu::GUICmdAckLearningMenu(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckLearningMenu::Load(QIODevice *f)
{

	if(::Load(f,MenuDimNumb)==false)	return false;
	for(int i=0;i<MenuDimNumb && i<100;i++){
		if(LearningMenuDim[i].Load(f)==false){
			return false;
		}
	}
	return true;
}
bool	GUICmdAckLearningMenu::Save(QIODevice *f)
{
	if(::Save(f,MenuDimNumb)==false)	return false;
	for(int i=0;i<MenuDimNumb;i++){
		if(LearningMenuDim[i].Save(f)==false){
			return false;
		}
	}

	return true;
}

GUICmdReqItemIData::GUICmdReqItemIData(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqItemIData::Load(QIODevice *f)
{
	if(Index.Load(f)==false){
		return false;
	}
	if(::Load(f,AddedX)==false){
		return false;
	}
	if(::Load(f,AddedY)==false){
		return false;
	}
	if(::Load(f,OkMode)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqItemIData::Save(QIODevice *f)
{
	if(Index.Save(f)==false){
		return false;
	}
	if(::Save(f,AddedX)==false){
		return false;
	}
	if(::Save(f,AddedY)==false){
		return false;
	}
	if(::Save(f,OkMode)==false){
		return false;
	}
	return true;
}
void	GUICmdReqItemIData::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemIData	*SendBack=GetSendBack(GUICmdAckItemIData,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);
	
	AlgorithmItemRoot	*Item=GetLayersBase()->FindItem(Index);
	if(Item!=NULL){
		ItemDataListWithID	*h=Item->MakeItemForLearning(AddedX,AddedY,OkMode);
		if(h!=NULL){
			SendBack->IData=h->IData;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckItemIData::GUICmdAckItemIData(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckItemIData::Load(QIODevice *f)
{
	if(::Load(f,IData)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckItemIData::Save(QIODevice *f)
{
	if(::Save(f,IData)==false){
		return false;
	}
	return true;
}

//===============================================================================================

LibInfoList::LibInfoList(void)
{}
LibInfoList::LibInfoList(const LibInfoList &src)
{
	LibType=src.LibType;
	LibIDs =src.LibIDs ;
}

LibInfoList	&LibInfoList::operator=(const LibInfoList &src)
{
	LibType=src.LibType;
	LibIDs =src.LibIDs ;
	return *this;
}
bool	LibInfoList::operator==(const LibInfoList &src)
{
	if(LibType==src.LibType
	&& LibIDs ==src.LibIDs ){
		return true;
	}
	return false;
}
bool	LibInfoList::operator!=(const LibInfoList &src)
{
	return !operator==(src);
}
bool	LibInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(LibIDs.Save(f)==false)		return false;
	return true;
}
bool	LibInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(LibIDs.Load(f)==false)		return false;
	return true;
}


LibInfoListContainer::LibInfoListContainer(void)
{
}
LibInfoListContainer::LibInfoListContainer(const LibInfoListContainer &src)
{
	for(LibInfoList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LibInfoList *b=new LibInfoList(*a);
		AppendList(b);
	}
}

LibInfoListContainer	&LibInfoListContainer::operator=(const LibInfoListContainer &src)
{
	for(LibInfoList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LibInfoList *b=new LibInfoList(*a);
		AppendList(b);
	}
	return *this;
}

LibInfoList	*LibInfoListContainer::Create(void)
{
	return new LibInfoList();
}

bool	LibInfoListContainer::AppendMerge(LibInfoList *t)
{
	for(LibInfoList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(*a==*t){
			return false;
		}
	}
	AppendList(t);
	return true;
}
void	LibInfoListContainer::AppendMerge(const LibInfoListContainer &src)
{
	for(LibInfoList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LibInfoList *d;
		for(d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*s==*d){
				break;
			}
		}
		if(d==NULL){
			LibInfoList *b=new LibInfoList(*s);
			AppendList(b);
		}
	}
}


LibDataList::LibDataList(void)
{
	LibType	=-1;
	LibID	=-1;
}
LibDataList::LibDataList(const LibDataList &src)
{
	LibType	=src.LibType;
	LibID	=src.LibID ;
	LibData	=src.LibData;
}

LibDataList	&LibDataList::operator=(const LibDataList &src)
{
	LibType	=src.LibType;
	LibID	=src.LibID ;
	LibData	=src.LibData;
	return *this;
}

bool	LibDataList::Save(QIODevice *f)
{
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	if(::Save(f,LibData	)==false)	return false;

	return true;
}
bool	LibDataList::Load(QIODevice *f)
{
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	if(::Load(f,LibData	)==false)	return false;

	return true;
}


LibDataListContainer::LibDataListContainer(void)
{
}
LibDataListContainer::LibDataListContainer(const LibDataListContainer &src)
{
	for(LibDataList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LibDataList *b=new LibDataList(*a);
		AppendList(b);
	}
}

LibDataListContainer	&LibDataListContainer::operator=(const LibDataListContainer &src)
{
	for(LibDataList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LibDataList *b=new LibDataList(*a);
		AppendList(b);
	}
	return *this;
}

LibDataList	*LibDataListContainer::Create(void)
{
	return new LibDataList();
}