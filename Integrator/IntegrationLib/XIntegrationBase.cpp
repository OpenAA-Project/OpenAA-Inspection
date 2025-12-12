#include <cmath>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QSqlDatabase>
#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"
#include "XResult.h"
#include "swap.h"
#include "XPointer.h"
#include "XCriticalFunc.h"
#include "XIntegrationBasePacket.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"
#include "XIntegrationSimpleImagePanel.h"
#include "XParamDatabase.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"

NGPoint::NGPoint(const NGPoint &src)
{	
	MasterX		=src.MasterX;
	MasterY		=src.MasterY;
	MX			=src.MX;
	MY			=src.MY;
	HX			=src.HX;
	HY			=src.HY;
	Cause[0]	=src.Cause[0];
	Cause[1]	=src.Cause[1];
	Index		=src.Index;
	LibType		=src.LibType;
	LibID		=src.LibID;
	UniqueID	=src.UniqueID;
	ShadowLevel	=src.ShadowLevel;
	ShadowNumber=src.ShadowNumber;
	ExtraData	=src.ExtraData;
	PagePoint	=src.PagePoint;
}

NGPoint   &NGPoint::operator=(NGPoint &src)
{	
	MasterX		=src.MasterX;
	MasterY		=src.MasterY;
	MX			=src.MX;
	MY			=src.MY;
	HX			=src.HX;
	HY			=src.HY;
	Cause[0]	=src.Cause[0];
	Cause[1]	=src.Cause[1];
	Index		=src.Index;
	LibType		=src.LibType;
	LibID		=src.LibID;
	UniqueID	=src.UniqueID;
	ShadowLevel	=src.ShadowLevel;
	ShadowNumber=src.ShadowNumber;
	ExtraData	=src.ExtraData;
	//PagePoint	=src.PagePoint;
	return(*this);
}

IntegNGImage::IntegNGImage(int _ShadowLevel,int _ShadowNumber)
	:ShadowLevel(_ShadowLevel),ShadowNumber(_ShadowNumber)
{
    CompressedPtn	=NULL;
    PtnByte			=0;

	GlobalPage	=0;
	Number		=0;
    x1=y1=x2=y2	=0;

	for(int layer=0;layer<3;layer++){
		SrcImage[layer]=NULL;
	}
}
IntegNGImage::~IntegNGImage(void)
{
	if(CompressedPtn!=NULL){
		delete	[]CompressedPtn;
		CompressedPtn=NULL;
	}
	for(int layer=0;layer<3;layer++){
		if(SrcImage[layer]!=NULL){
			DeleteMatrixBuff(SrcImage[layer],SrcImageYLen);
			SrcImage[layer]=NULL;
		}
	}
}

bool	IntegNGImage::Uncompress(void)
{
	if(CompressedPtn!=NULL){
		QByteArray pixData=QByteArray::fromRawData((const char *)CompressedPtn, PtnByte );

		if(Image.loadFromData(pixData, /**/"PNG")==true){
			return true;
		}
	}
	else{
		MakeImage(Image ,SrcImage,SrcImageXLen ,SrcImageYLen);
	}
	return false;
}
bool	IntegNGImage::LoadJDT(QIODevice *f)
{
	DWORD	JVer;

	if(::Load(f,JVer)==false){
		return false;
	}
	int32	iGlobalPage;
	if(::Load(f,iGlobalPage)==false){
		return false;
	}
	GlobalPage=iGlobalPage;
	if(::Load(f,Number)==false){
		return false;
	}
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	if(::Load(f,PtnByte)==false){
		return false;
	}
	if(PtnByte!=0){
		if(CompressedPtn!=NULL){
			delete	[]CompressedPtn;
		}
		CompressedPtn=new uchar[PtnByte];
		if(f->read((char *)CompressedPtn	,PtnByte)!=PtnByte){
			return false;
		}
	}
	return true;
}

bool	IntegNGImage::LoadRawImage(QIODevice *f)
{
	DWORD	JVer;

	if(::Load(f,JVer)==false){
		return false;
	}
	int32	iGlobalPage;
	if(::Load(f,iGlobalPage)==false){
		return false;
	}
	GlobalPage=iGlobalPage;
	if(::Load(f,Number)==false){
		return false;
	}
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	for(int layer=0;layer<3;layer++){
		if(SrcImage[layer]!=NULL){
			DeleteMatrixBuff(SrcImage[layer],SrcImageYLen);
			SrcImage[layer]=NULL;
		}
	}

	if(::Load(f,SrcImageXLen)==false){
		return false;
	}
	if(::Load(f,SrcImageYLen)==false){
		return false;
	}
	for(int layer=0;layer<3;layer++){
		SrcImage[layer]=MakeMatrixBuff(SrcImageXLen,SrcImageYLen);
		if(::Load(f,SrcImage[layer],SrcImageXLen,SrcImageYLen)==false){
			return false;
		}
	}

	return true;
}
void	IntegNGImage::EnumNGPoint(NGPointInPage *PageData ,NPListPack<NGPointPointerList> &NGList)
{
	for(NGPoint *p=PageData->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
		int	cx,cy;
		p->GetMasterCenter(cx,cy);
		if(x1<=cx && cx<=x2 && y1<=cy && cy<=y2){
			NGList.AppendList(new NGPointPointerList(p));
		}
	}
}


NGPointInPage::NGPointInPage(NGPointInAllPage *p,NGPointInPage &src)
	:Parent(p)
{
	NPListPack<NGPoint>::RemoveAll();
	for(NGPoint *p=NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
		NGPoint	*a=new NGPoint(this);
		*a=*p;
		NPListPack<NGPoint>::AppendList(a);
	}
	FlagSet			=src.FlagSet;
	ImageFileName	=src.ImageFileName;
	Page			=src.Page;
}

NGPointInPage &NGPointInPage::operator=(NGPointInPage &src)
{
	NPListPack<NGPoint>::RemoveAll();
	for(NGPoint *p=NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
		NGPoint	*a=new NGPoint(this);
		*a=*p;
		NPListPack<NGPoint>::AppendList(a);
	}
	FlagSet			=src.FlagSet;
	ImageFileName	=src.ImageFileName;
	Page			=src.Page;
	return *this;
}

int		NGPointInPage::GetNGCount(void)	const
{	
	int	NGCount=0;
	for(NGPoint *p=NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
		if(p->IsNG()==true){
			NGCount++;
		}
	}
	return NGCount;
}

void	NGPointInPage::BindNGPoint(int XLen ,int YLen,NPListPack<IntegBindedNGArea> &NGAreaPack)
{
	for(NGPoint *p=NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
		IntegBindedNGArea *n;
		for(n=NGAreaPack.GetFirst();n!=NULL;n=n->GetNext()){
			int	x1=n->x1;
			int	y1=n->y1;
			int	x2=n->x2;
			int	y2=n->y2;
			int	TargetCx,TargetCy;
			p->GetTargetCenter(TargetCx,TargetCy);
			x1=min(x1,TargetCx);
			y1=min(y1,TargetCy);
			x2=max(x2,TargetCx);
			y2=max(y2,TargetCy);
			if((x2-x1)<XLen && (y2-y1)<YLen){
				n->x1=x1;
				n->y1=y1;
				n->x2=x2;
				n->y2=y2;
				n->NGPointerList.AppendList(new NGPointPointerList(p));
				break;
			}
		}
		if(n==NULL){
			n=new IntegBindedNGArea(this);
			int	TargetCx,TargetCy;
			p->GetTargetCenter(TargetCx,TargetCy);
			n->x1=TargetCx;
			n->y1=TargetCy;
			n->x2=TargetCx;
			n->y2=TargetCy;
			n->NGPointerList.AppendList(new NGPointPointerList(p));
			NGAreaPack.AppendList(n);
		}
	}
}

bool	NGPointInPage::UncompressImages(void)
{
	bool	Ret=true;
	for(IntegNGImage *p=NGImages.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Uncompress()==false){
			Ret=false;
		}
	}
	return Ret;
}
IntegNGImage	*NGPointInPage::FindImage(int number)	const
{
	for(IntegNGImage *p=NGImages.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetNumber()==number)
			return p;
	}
	return NULL;
}
void	NGPointInPage::MakeMasterImage(QImage *Image, int cx, int cy ,double ZoomRate)
{
	double	Z=1.0/ZoomRate;
	int	w=Image->width() *Z;
	int	h=Image->height()*Z;
	int	x1=cx-w/2;
	int	x2=x1+w;
	int	y1=cy-h/2;
	int	y2=y1+h;

	int	XLen=min(Image->width() ,x2-x1);
	int	YLen=min(Image->height(),y2-y1);
	if(GetParent()==NULL
	|| GetParent()->GetParent()==NULL
	|| GetParent()->GetParent()->GetParent()==NULL)
		return;
	InspectionList	*Ins=GetParent()->GetParent()->GetParent();
	if(Ins==NULL)
		return;
	EachMaster	*m=Ins->GetMaster();
	if(m==NULL)
		return;
	int	LayerNumb=m->GetLayerNumb(GetPhase() ,GetPage());
	//int	Index=GetPhase()*m->GetPageNumb()+GetPage();
	int	iDotPerLine	=m->GetDotPerLine(GetPhase() ,GetPage());	//CData[Index].GetDotPerLine();
	int	iMaxLines	=m->GetMaxLines(GetPhase() ,GetPage());		//CData[Index].GetMaxLines();
	if(LayerNumb>=3){
		ImageBuffer	*B0=m->GetMasterImage(GetPhase() ,GetPage(),0);
		ImageBuffer	*B1=m->GetMasterImage(GetPhase() ,GetPage(),1);
		ImageBuffer	*B2=m->GetMasterImage(GetPhase() ,GetPage(),2);
		double	FY=y1;
		for(int y=0;y<YLen;y++,FY+=Z){
			int	Y=(int)FY;
			if(0<=Y && Y<iMaxLines){
				BYTE	*s0=B0->GetY(Y);
				BYTE	*s1=B1->GetY(Y);
				BYTE	*s2=B2->GetY(Y);
				QRgb	*d=(QRgb *)Image->scanLine(y);
				if(0<=x1 && (x1+XLen*Z)<iDotPerLine){
					double	FX=x1;
					for(int x=0;x<XLen;x++,FX+=Z){
						int	X=FX;
						*d=qRgb(s0[X],s1[X],s2[X]);
						d++;
					}
				}
				else{
					double	FX=x1;
					for(int x=0;x<XLen;x++,FX+=Z){
						int	X=FX;
						if(0<=X && X<iDotPerLine){
							*d=qRgb(s0[X],s1[X],s2[X]);
							d++;
						}
					}
				}
			}
		}
	}
	if(LayerNumb==2){
		ImageBuffer	*B0=m->GetMasterImage(GetPhase() ,GetPage(),0);
		ImageBuffer	*B1=m->GetMasterImage(GetPhase() ,GetPage(),1);
		double	FY=y1;
		for(int y=0;y<YLen;y++,FY+=Z){
			int	Y=(int)FY;
			if(0<=Y && Y<iMaxLines){
				BYTE	*s0=B0->GetY(Y);
				BYTE	*s1=B1->GetY(Y);
				QRgb	*d=(QRgb *)Image->scanLine(y);
				double	FX=x1;
				if(0<=x1 && (x1+XLen*Z)<iDotPerLine){
					for(int x=0;x<XLen;x++,FX+=Z){
						int	X=FX;
						*d=qRgb(s0[X],s1[X],s1[X]);
						d++;
					}
				}
				else{
					double	FX=x1;
					for(int x=0;x<XLen;x++,FX+=Z){
						int	X=FX;
						if(0<=X && X<iDotPerLine){
							*d=qRgb(s0[X],s1[X],s1[X]);
							d++;
						}
					}
				}
			}
		}
	}
	if(LayerNumb==1){
		ImageBuffer	*B0=m->GetMasterImage(GetPhase() ,GetPage(),0);
		double	FY=y1;
		for(int y=0;y<YLen;y++,FY+=Z){
			int	Y=(int)FY;
			if(0<=Y && Y<iMaxLines){
				BYTE	*s0=B0->GetY(Y);
				QRgb	*d=(QRgb *)Image->scanLine(y);
				double	FX=x1;
				if(0<=x1 && (x1+XLen*Z)<iDotPerLine){
					for(int x=0;x<XLen;x++,FX+=Z){
						int	X=FX;
						if(0<=x1 && x1*Z<iDotPerLine){
							*d=qRgb(s0[X],s0[X],s0[X]);
							d++;
						}
					}
				}
				else{
					double	FX=x1;
					for(int x=0;x<XLen;x++,FX+=Z){
						int	X=FX;
						if(0<=X && X<iDotPerLine){
							*d=qRgb(s0[X],s0[X],s0[X]);
							d++;
						}
					}
				}
			}
		}
	}
}

NGPointInAllPage &NGPointInAllPage::operator=(NGPointInAllPage &src)
{
	for(NGPointInPage *a=NPListPack<NGPointInPage>::GetFirst();a!=NULL;a=a->GetNext()){
		NGPointInPage	*b=new NGPointInPage(this);
		*b=*a;
		AppendList(b);
	}
	Phase=src.Phase;
	return *this;
}
int		NGPointInAllPage::GetNGCount(void)	const
{
	int	Ret=0;
	for(NGPointInPage *a=NPListPack<NGPointInPage>::GetFirst();a!=NULL;a=a->GetNext()){
		Ret+=a->GetNGCount();
	}
	return Ret;
}

bool	NGPointInAllPage::IsSetAllPages(void)	const
{
	for(NGPointInPage *a=NPListPack<NGPointInPage>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FlagSet==false){
			return false;
		}
	}
	return true;
}

NGPointInAllPhase &NGPointInAllPhase::operator=(NGPointInAllPhase &src)
{
	for(NGPointInAllPage *a=NPListPack<NGPointInAllPage>::GetFirst();a!=NULL;a=a->GetNext()){
		NGPointInAllPage	*b=new NGPointInAllPage(this,a->GetPhase());
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	NGPointInAllPhase::IsSetAllPhases(void)	const
{
	for(NGPointInAllPage *a=NPListPack<NGPointInAllPage>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsSetAllPages()==false){
			return false;
		}
	}
	return true;
}
int		NGPointInAllPhase::GetNGCount(void)	const
{
	int	Ret=0;
	for(NGPointInAllPage *a=NPListPack<NGPointInAllPage>::GetFirst();a!=NULL;a=a->GetNext()){
		Ret+=a->GetNGCount();
	}
	return Ret;
}
//=================================================================================

int		InspectionList::GetNGCount(void)	const
{
	return NGPointAllPhases.GetNGCount();
}

QString	InspectionList::GetFileName(void)	const
{
	return FileName;
}

InspectionListContainer::InspectionListContainer(EachMaster *p)
	:Parent(p)
{	
	CountingPoint	=0;
	AllocatedResultCount	=MaxCountTotalResultDim;
	ResultDim	=new struct	TotalResultStruct[AllocatedResultCount];
	ResultCount		=0;
	for(int i=0;i<AllocatedResultCount;i++){
		ResultDim[i].Error=0;
	}
	TotalCount	=0;
	NGCount		=0;
}
InspectionListContainer::~InspectionListContainer(void)
{
	delete	[]ResultDim;
	ResultDim			=NULL;
	ResultCount			=0;
	AllocatedResultCount=0;
}
void	InspectionListContainer::AppendList(InspectionList *n)
{
	NPListPack<InspectionList>::AppendList(n);
	if(ResultCount<AllocatedResultCount){
		struct	TotalResultStruct	*R=&ResultDim[ResultCount];
		R->Year		=n->InspectionTime.year()-2000;
		R->Month	=n->InspectionTime.month();
		R->Day		=n->InspectionTime.day();
		R->Hour		=n->InspectionTime.hour();
		R->Minute	=n->InspectionTime.minute();
		R->Second	=n->InspectionTime.second();
		R->Microsec	=::GetComputerMiliSec();
		R->InspectionID	=n->ID;
		R->Error	=1;
		R->LoadedPageCount	=0;
		ResultCount++;
		TotalCount++;
	}
}
void	InspectionListContainer::SetResultPage(int Phase ,int GlobalPage,InspectionList *n)
{
	if(ResultCount>0 && (ResultCount-1)<AllocatedResultCount){
		struct	TotalResultStruct	*R=&ResultDim[ResultCount-1];
		NGPointInAllPage	*Ph=n->GetPhaseData(Phase);
		if(Ph!=NULL){
			NGPointInPage	*Pg=Ph->GetPageData(GlobalPage);
			if(Pg!=NULL){
				int	NGCount=n->GetNGCount();
				if(NGCount>0){
					R->Error=2;
				}
			}
		}
		R->LoadedPageCount++;
		if(R->LoadedPageCount>=Parent->GetPageNumb()*Parent->GetPhaseNumb()){
			if(R->Error>1){
				NGCount++;
			}
			emit	SignalDoneLoadResult(n);
		}
	}
}
void	InspectionListContainer::RemoveAll(void)
{
	NPListPack<InspectionList>::RemoveAll();
	CountingPoint=0;

	for(int i=0;i<AllocatedResultCount;i++){
		ResultDim[i].Error=0;
	}
	ResultCount	=0;
	TotalCount	=0;
	NGCount		=0;
	emit	SignalDoneLoadResult(NULL);
}

//=================================================================================
AccessToPage	&AccessToPage::operator=(const AccessToPage &src)
{
	GlobalPage	=src.GlobalPage	;
	IPAddress	=src.IPAddress	;
	Port		=src.Port		;
	return *this;
}
bool	AccessToPage::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,Port)==false)
		return false;
	return true;
}
bool	AccessToPage::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,Port)==false)
		return false;
	return true;
}
//====================================================================================================
IntegrationSystemResultStocker::IntegrationSystemResultStocker(int AllocCount)
{
	Dim=new IntegrationSystemResult[AllocCount];
	DimCount=AllocCount;
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;
}
IntegrationSystemResultStocker::~IntegrationSystemResultStocker(void)
{
	AccessMutex.lock();
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;
	AccessMutex.unlock();
}

bool	IntegrationSystemResultStocker::ReallocateDimCount(int AllocCount)
{
	AccessMutex.lock();

	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	Dim=new IntegrationSystemResult[AllocCount];
	DimCount=AllocCount;
	WPoint	=0;
	RPoint	=0;
	StockedCount	=0;

	AccessMutex.unlock();
	return true;
}

void	IntegrationSystemResultStocker::PushResult(const QByteArray &data)
{
	AccessMutex.lock();
	Dim[WPoint].Result		=data;
	WPoint++;
	if(WPoint>=DimCount){
		WPoint=0;
	}
	StockedCount++;
	AccessMutex.unlock();
}
IntegrationSystemResult	*IntegrationSystemResultStocker::PopResult(void)
{
	AccessMutex.lock();
	IntegrationSystemResult	*R=NULL;
	if(StockedCount>0){
		R=&Dim[RPoint];
		RPoint++;
		if(RPoint>=DimCount){
			RPoint=0;
		}
		StockedCount--;
	}
	AccessMutex.unlock();
	return R;
}

//=================================================================================
EachMaster::EachMaster(IntegrationBase *parent,IntegrationSlave *slave)
	:ServiceForLayers(parent->GetLayersBase())
	,Parent(parent),Slave(slave)
	,CurrentInspection(this)
{
	Ins=NULL;

	MasterCode	=-1;
	PageNumb	=0;
	//LayerNumb	=0;
	PhaseNumb	=0;
	CData		=0;
	MasterImage=NULL;
	TargetImage=NULL;
	CurrentLot	=NULL;
	CurrentPhase=0;
	AccessToPageDim=NULL;
	LayerNumbDim	=new int32[1];
	LayerNumbDim[0]=0;

	TransformUnitPerPixelX=0.065;
	TransformUnitPerPixelY=0.065;

	connect(&CurrentInspection,SIGNAL(SignalDoneLoadResult(InspectionList *)),this,SLOT(SlotDoneLoadResult(InspectionList *)));
}
EachMaster::~EachMaster(void)
{
	if(CData!=NULL){
		delete	[]CData;
		CData=NULL;
	}
	ReleaseImageBuffer();
	if(AccessToPageDim!=NULL){
		delete	[]AccessToPageDim;
		AccessToPageDim=NULL;
	}
	if(LayerNumbDim!=NULL){
		delete	[]LayerNumbDim;
		LayerNumbDim=NULL;
	}
}
bool	EachMaster::ClearMaster(void)
{
	ReleaseImageBuffer();
	MasterCode	=-1;
	PageNumb	=0;
	PhaseNumb	=0;
	LotContainer.RemoveAll();
	CurrentInspection.RemoveAll();
	CurrentLot	=NULL;
	return true;
}
void	EachMaster::ClearImageBuff(void)
{
	for(int phase=0; phase<PhaseNumb; phase++){
		for(int page=0; page<PageNumb; page++){
			for(int layer=0;layer<GetLayerNumb(phase,page);layer++){
				if(MasterImage!=NULL){
					MasterImage[phase][page][layer].Memset(0);
				}
				if(TargetImage!=NULL){
					TargetImage[phase][page][layer].Memset(0);
				}
			}
		}
	}
}
int		EachMaster::GetDotPerLine(int phase ,int page)	const
{	
	if(0<=phase && phase<GetPhaseNumb() && 0<=page && page<GetPageNumb()){
		return (CData!=NULL)?CData[phase*PageNumb+page].DotPerLine:0;
	}
	return -1;
}
int		EachMaster::GetMaxLines(int phase ,int page)	const
{	
	if(0<=phase && phase<GetPhaseNumb() && 0<=page && page<GetPageNumb()){
		return (CData!=NULL)?CData[phase*PageNumb+page].MaxLines:0;
	}
	return -1;
}
int		EachMaster::GetLayerNumb(int phase ,int page)	const
{
	if(Slave->SlaveIsInMaster==false){
		if(0<=phase && phase<GetPhaseNumb() && 0<=page && page<GetPageNumb()){
			return LayerNumbDim[page];
		}
	}
	else{
		return GetLayersBase()->GetLayerNumb(page);
	}
	return -1;
}

int		EachMaster::GetPhaseNumb(void)	const
{	
	if(Slave->SlaveIsInMaster==false){
		return PhaseNumb;
	}
	else{
		return GetLayersBase()->GetPhaseNumb();
	}
}
int		EachMaster::GetPageNumb(void)	const
{	
	if(Slave->SlaveIsInMaster==false){
		return PageNumb;
	}
	else{
		return GetLayersBase()->GetPageNumb();
	}
}



int		EachMaster::GetMaxLayerNumb(void)	const
{
	int	MaxLayerNumb=0;
	if(Slave->SlaveIsInMaster==false){
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<PageNumb;page++){
				MaxLayerNumb=max(MaxLayerNumb,LayerNumbDim[page]);
			}
		}
	}
	else{
		for(int page=0;page<PageNumb;page++){
			MaxLayerNumb=max(MaxLayerNumb,GetLayersBase()->GetLayerNumb(page));
		}
	}
	return MaxLayerNumb;
}

ImageBuffer	*EachMaster::GetMasterImage(int phase ,int page ,int layer)	const
{	
	if(0<=phase && phase<PhaseNumb && 0<=page && page<PageNumb){
		if(0<=layer && layer<GetLayerNumb(phase,page)){
			return (MasterImage!=NULL)?&((MasterImage[phase])[page])[layer]:NULL;
		}
	}
	return NULL;
}
ImageBuffer	*EachMaster::GetTargetImage(int phase ,int page ,int layer)	const
{	
	if(0<=phase && phase<PhaseNumb && 0<=page && page<PageNumb){
		if(0<=layer && layer<GetLayerNumb(phase,page)){
			return (TargetImage!=NULL)?&((TargetImage[phase])[page])[layer]:NULL;
		}
	}
	return NULL;
}
bool	EachMaster::GetMasterImage(int phase ,int page ,ImagePointerContainer &ImageList)	const
{
	if(MasterImage!=NULL){
		if(0<=phase && phase<PhaseNumb && 0<=page && page<PageNumb){
			for(int layer=0;layer<GetLayerNumb(phase,page);layer++){
				ImagePointerList	*p=new ImagePointerList(&((MasterImage[phase])[page])[layer]);
				ImageList.AppendList(p);
			}
		}
	}
	return NULL;
}
bool	EachMaster::GetTargetImage(int phase ,int page ,ImagePointerContainer &ImageList)	const
{
	if(TargetImage!=NULL){
		if(0<=phase && phase<PhaseNumb && 0<=page && page<PageNumb){
			for(int layer=0;layer<GetLayerNumb(phase,page);layer++){
				ImagePointerList	*p=new ImagePointerList(&((TargetImage[phase])[page])[layer]);
				ImageList.AppendList(p);
			}
		}
	}
	return NULL;
}

QString	EachMaster::GetMachineName(void)	const
{
	QString NetID;
	QString Name;
	QString Version;
	QString Remark;

	if(Parent->GetLayersBase()->GetDatabaseLoader()->G_GetMachineInfo(*Parent->GetLayersBase()->GetDataBase()
								,GetMachineCode()
								,NetID
								,Name
								,Version
								,Remark)==true){
		return Name;
	}
	return /**/"";
}

bool	EachMaster::IsDependent(void)	const
{
	IntegrationSlave	*s=GetParamIntegrationMaster()->Slaves[GetIntegrationSlaveNo()];
	if(s!=NULL){
		return s->Dependent;
	}
	return false;
}

bool	EachMaster::LoadMaster(int _MasterCode)
{
	MasterCode=_MasterCode;
	int32		iMachineID;
	XDateTime	RegTime;
	QString		Remark;
	int32		Version;
	XDateTime	LastEditTime;
	int32		CategoryID;
	int16		MasterType;
	int			iDotPerLine;
	int			iMaxLines;
	int			iLayerNumb;
	int			iPageNumb;
	int			iPhaseNumb;
	int32		iLibFolderID;
	int32 		iThresholdLevelID	=0;
	int32 		iThresholdLevelParentID=0;

	if(Parent->GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterData2(*Parent->GetLayersBase()->GetDataBase()
							,MasterCode
							,iMachineID
							,RegTime
							,MasterName ,Remark
							,Version
							,LastEditTime
							,CategoryID
							,MasterType
							,iDotPerLine
							,iMaxLines
							,iLayerNumb
							,iPageNumb
							,iPhaseNumb
							,iLibFolderID
							,iThresholdLevelID
							,iThresholdLevelParentID)==true){
		ReleaseImageBuffer();

		//LayerNumb		=iLayerNumb;
		PageNumb		=iPageNumb;
		PhaseNumb		=iPhaseNumb;
		ThresholdLevelID=iThresholdLevelID;
		if(CData!=NULL){
			delete	[]CData;
			CData=NULL;
		}
		CData=new DataInPage::ConstructionData[PhaseNumb*PageNumb];

		OutlineOffsetInBlob outlineBlob(Parent->GetLayersBase());
		if(Parent->GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(*Parent->GetLayersBase()->GetDataBase() ,GetMachineCode()
								, &outlineBlob)==true){
			for(int phase=0; phase<PhaseNumb; phase++){
				for(int page=0; page<PageNumb; page++){
					int x = outlineBlob.GetData(phase, page).Dx;
					int y = outlineBlob.GetData(phase, page).Dy;
					int	Index=phase*PageNumb+page;
					CData[Index].OutlineOffset.x=x;
					CData[Index].OutlineOffset.y=y;
					CData[Index].DotPerLine	=iDotPerLine;
					CData[Index].MaxLines	=iMaxLines;
				}
			}
			AllocateImageBuffer();
			if(MasterImage!=NULL){
				LoadMasterImage(MasterImage);
			}
			CurrentLot=NULL;
			return true;
		}
	}
	return false;
}
bool	EachMaster::LoadLotList(int _MasterCode)
{
	if(CurrentLot!=NULL){
		LotContainer.RemoveList(CurrentLot);
	}
	LotContainer.RemoveAll();

	QDir	cd;

	QString	path=Slave->SharedFolder
				+GetSeparator()
				+QString::number(GetMachineCode())+QString(/**/"-")+QString::number(_MasterCode);

	cd.setPath(path);

	QStringList	nameFilters;
	nameFilters<</**/"*.rdt";
	QFileInfoList FInfo=cd.entryInfoList(nameFilters, QDir::Files,QDir::Time);
	bool	FoundSaveLot=false;
	for(int i=0;i<FInfo.count();i++){
		LotList	*L=new LotList();
		L->LotName		=FInfo[i].baseName();
		L->LotFileName	=FInfo[i].absoluteFilePath();
		LotContainer.AppendList(L);
		if(CurrentLot!=NULL && L->LotName==CurrentLot->LotName){
			delete	CurrentLot;
			CurrentLot=L;
			FoundSaveLot=true;
		}
	}
	if(FoundSaveLot==false){
		if(CurrentLot!=NULL){
			LotContainer.AppendList(CurrentLot);
		}
	}
	return true;
}

bool	EachMaster::ClearCurrentLot(void)
{
	CurrentLot	=NULL;
	CurrentInspection.RemoveAll();
	return true;
}
bool	EachMaster::LoadLot(LotList *Current)
{
	if(Current!=NULL){
		QFile	File(Current->LotFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			return LoadLotFile(Current ,File);
		}
	}
	return true;
}

bool	EachMaster::AppendSelectLot(LotList *Current)
{
	if(Current!=NULL){
		ParamIntegrationMaster	*Param=GetParamIntegrationMaster();
		if(Param->UseSystemResultStocker==false){
			if(Current->LotFileName.isEmpty()==false){
				QFile	File(Current->LotFileName);
				if(File.open(QIODevice::ReadOnly)==true){
					File.seek(Current->LastSeekPoint);
					return LoadLotFile(Current ,File);
				}
			}
			else{
				return false;
			}
		}
		else{
			for(;;){
				IntegrationSystemResult	*s=SystemResultContainer.PopResult();
				if(s==NULL){
					break;
				}
				QBuffer	Buff(&s->Result);
				Buff.open(QIODevice::ReadOnly);
				LoadLotFile(Current ,Buff);
			}
		}
	}
	return true;
}
bool	EachMaster::SetCurrentLot(LotList *Lot)
{
	if(Lot==NULL){
		return false;
	}
	for(LotList *L=LotContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LotFileName==Lot->LotFileName){
			CurrentLot=L;
			return;
		}
	}
	CurrentLot=NULL;
	return true;
}

static	int	LoadWatingMilisec=2000;
bool	EachMaster::LoadLotFile(LotList *Current ,QIODevice &File)
{
	struct	ResultHeader	Header;
	int	ErrorCnt=0;
	int		LastResult;
	for(;;){
		char	Type;
		if(::Load(&File,Type)==false){
			return true;
		}
		if(Type==0){
			Current->LastSeekPoint=File.pos();
			continue;
		}
		ChallengeAgain:;
		if(Type=='L'){
			int32	iMasterCode;
			int32	iLotAutoCount;

			if(::Load(&File,iMasterCode)==false){
				goto	EndLoad;
			}
			if(::Load(&File,iLotAutoCount)==false){
				goto	EndLoad;
			}
			Current->LastSeekPoint=File.pos();
		}
		else if(Type=='O'){
			if(LoadOutputLibData(File)==false){
				goto	EndLoad;
			}
			Current->LastSeekPoint=File.pos();
		}
		else  if(Type=='N'){
			if(LoadNaming(File)==false){
				goto	EndLoad;
			}
			Current->LastSeekPoint=File.pos();
		}
		else  if(Type=='C'){
			if(File.read((char *)&Header,sizeof(Header))!=sizeof(Header))
				goto	EndLoad;
			if(Header.Year>200){
				Header.Year-=0xD0;
			}
			Ins=new InspectionList(this);
			Ins->ID				=Header.InspectionID;
			Ins->InspectionTime	=XDateTime(Header.Year+2000,Header.Month,Header.Day ,Header.Hour,Header.Minute,Header.Second);

			Ins->RemarkData.append((char *)Header.RemarkData);
			Ins->Result	=Header.Result;
			LastResult	=Header.Result;

			for(int phase=0;phase<PhaseNumb;phase++){
				NGPointInAllPage	*P=new NGPointInAllPage(&Ins->NGPointAllPhases,phase);
				Ins->NGPointAllPhases.AppendList(P);
				for(int page=0;page<PageNumb;page++){
					P->AppendList(new NGPointInPage(P,page));
				}
			}
			CurrentInspection.AppendList(Ins);
			Current->LastSeekPoint=File.pos();
		}
		else  if(Type=='S'){
			int32	phase;
			if(::Load(&File,phase)==false)
				goto	EndLoad;
			int32	GlobalPage;
			if(::Load(&File,GlobalPage)==false)
				goto	EndLoad;
			NGPointInPage	*PageR=NULL;
			//int	SlaveNo=GetIntegrationSlaveNo();
			if(Ins!=NULL){
				NGPointInAllPage	*P=Ins->NGPointAllPhases[phase];
				if(P==NULL){
					phase=0;
					P=Ins->NGPointAllPhases[phase];
				}
				if(P!=NULL){
					PageR=P->GetItem(GlobalPage);
					if(PageR!=NULL){
						PageR->FlagSet=true;
					}
					int32	AlgoNumb;
					int32	Ver=0;
					if(::Load(&File,AlgoNumb)==false){
						goto	EndLoad;
					}
					if(AlgoNumb>=100000000){
						if(::Load(&File,Ver)==false){
							goto	EndLoad;
						}
						AlgoNumb-=100000000;
					}
					int32	ShadowTotalCount=0;
					if(AlgoNumb>=100000000){
						if(::Load(&File,ShadowTotalCount)==false){
							goto	EndLoad;
						}
						AlgoNumb-=100000000;
					}
					ShadowTotalCount++;

					for(int t=0;t<ShadowTotalCount;t++){
						int		ShadowLevel=0;
						int		ShadowNumber=0;
						if(t>0){
							if(::Load(&File,ShadowLevel)==false){
								goto	EndLoad;
							}
							if(::Load(&File,ShadowNumber)==false){
								goto	EndLoad;
							}
						}
						for(int a=0;a<AlgoNumb;a++){
							//int32	LibType;
							//if(::Load(&File,LibType)==false){
							//	return false;
							//}
							int32	N;
							if(::Load(&File,N)==false){
								goto	EndLoad;
							}
							if(t==0 && LastResult==2 && N==0 && a==3){
								ErrorCnt++;
							}
							if(Ver==0){
								for(int i=0;i<N;i++){
									struct	ResultPositionInfomationOld	RData;
									if(File.read((char *)&RData,sizeof(RData))!=sizeof(RData))
										goto	EndLoad;
									NGPoint	*p=new NGPoint(PageR);
									p->Error	=RData.Error;
									p->PosResult=0;
									p->MasterX	=RData.X-RData.MX-RData.HX;
									p->MasterY	=RData.Y-RData.MY-RData.HY;
									p->MX		=RData.MX;
									p->MY		=RData.MY;
									p->HX		=RData.HX;
									p->HY		=RData.HY;
									p->ResultType=_ResultDWORD;
									p->Cause[0]	=RData.result1;
									p->Cause[1]	=RData.result2;
									p->DoubleCause	=RData.ResultValue.ResultDouble;
									p->LibType	=RData.LibType;
									p->LibID	=RData.LibID;
									p->UniqueID	=RData.UniqueID1;
									p->ShadowLevel	=ShadowLevel;
									p->ShadowNumber	=ShadowNumber;	
									if(PageR!=NULL){
										PageR->AppendList(p);
									}
								}
							}
							else if(Ver==1){
								for(int i=0;i<N;i++){
									struct	ResultPositionInfomationOld2	RData;
									if(File.read((char *)&RData,sizeof(RData))!=sizeof(RData))
										goto	EndLoad;
									NGPoint	*p=new NGPoint(PageR);
									p->Error	=RData.Error;
									p->PosResult=0;
									p->MasterX	=RData.X-RData.MX-RData.HX;
									p->MasterY	=RData.Y-RData.MY-RData.HY;
									p->MX		=RData.MX;
									p->MY		=RData.MY;
									p->HX		=RData.HX;
									p->HY		=RData.HY;
									p->ResultType=RData.ResultType;
									if(RData.LibType!=0){
										p->Cause[0]	=RData.result1;
										p->Cause[1]	=RData.result2;
									}
									else{
										memset(p->Message,0,8);
										strncpy(p->Message,(char *)RData.Something,8);
									}
									p->DoubleCause	=RData.ResultValue.ResultDouble;
									p->LibType	=RData.LibType;
									p->LibID	=RData.LibID;
									p->UniqueID	=RData.UniqueID1;
									p->ShadowLevel	=ShadowLevel;
									p->ShadowNumber	=ShadowNumber;	
									if(PageR!=NULL){
										PageR->AppendList(p);
									}
								}
							}
							else if(Ver==2){
								for(int i=0;i<N;i++){
									struct	ResultPositionInfomationVer2	RData;
									if(File.read((char *)&RData,sizeof(RData))!=sizeof(RData))
										goto	EndLoad;
									NGPoint	*p=new NGPoint(PageR);
									p->Error	=RData.Error;
									p->PosResult=RData.PosResult;
									p->MasterX	=RData.X-RData.MX-RData.HX;
									p->MasterY	=RData.Y-RData.MY-RData.HY;
									p->MX		=RData.MX;
									p->MY		=RData.MY;
									p->HX		=RData.HX;
									p->HY		=RData.HY;
									p->ResultType=RData.ResultType;
									if(RData.LibType!=0){
										p->Cause[0]	=RData.result1;
										p->Cause[1]	=RData.result2;
									}
									else{
										memset(p->Message,0,8);
										strncpy(p->Message,(char *)RData.Something,8);
									}
									p->DoubleCause	=RData.ResultValue.ResultDouble;
									p->LibType	=RData.LibType;
									p->LibID	=RData.LibID;
									p->UniqueID	=RData.UniqueID1;
									p->ShadowLevel	=ShadowLevel;
									p->ShadowNumber	=ShadowNumber;	
									if(PageR!=NULL){
										PageR->AppendList(p);
									}
								}
							}
							else if(Ver==3){
								for(int i=0;i<N;i++){
									struct	ResultPositionInfomation	RData;
									if(File.read((char *)&RData,sizeof(RData))!=sizeof(RData))
										goto	EndLoad;
									NGPoint	*p=new NGPoint(PageR);
									p->Error	=RData.Error;
									p->PosResult=RData.PosResult;
									p->MasterX	=RData.X-RData.MX-RData.HX;
									p->MasterY	=RData.Y-RData.MY-RData.HY;
									p->MX		=RData.MX;
									p->MY		=RData.MY;
									p->HX		=RData.HX;
									p->HY		=RData.HY;
									p->ResultType=RData.ResultType;
									if(RData.LibType!=0){
										p->Cause[0]	=RData.result1;
										p->Cause[1]	=RData.result2;
									}
									else{
										memset(p->Message,0,8);
										strncpy(p->Message,(char *)RData.Something,8);
									}
									p->DoubleCause	=RData.ResultValue.ResultDouble;
									p->LibType	=RData.LibType;
									p->LibID	=RData.LibID;
									p->UniqueID	=RData.UniqueID1;
									p->ShadowLevel	=ShadowLevel;
									p->ShadowNumber	=ShadowNumber;	
									if(PageR!=NULL){
										PageR->AppendList(p);
									}
									if(RData.ExtraDataByte>0 && RData.ExtraDataByte<1000000){
										p->ExtraData=File.read(RData.ExtraDataByte);
										if(p->ExtraData.size()!=RData.ExtraDataByte){
											goto	EndLoad;
										}
									}
								}
							}
						}
					}
				}
				else{
					goto	EndLoad;
				}
			}
			else{
				goto	EndLoad;
			}
		
			int32	NGINumb=0;
			if(::Load(&File,NGINumb)==false){
				goto	EndLoad;
			}
			for(int i=0;i<NGINumb;i++){
				struct	NGIInfo	NGIData;
				if(File.read((char *)&NGIData,sizeof(NGIData))!=sizeof(NGIData)){
					goto	EndLoad;
				}
			}
			int16	FileNameLen;
			if(::Load(&File,FileNameLen)==false){
				goto	EndLoad;
			}
			if(FileNameLen>0){
				char	IFileNameStr[64];
				if(FileNameLen>=sizeof(IFileNameStr)){
					ErrorCnt++;
					goto	EndLoad;
				}
				if(File.read((char *)IFileNameStr,FileNameLen)!=FileNameLen){
					goto	EndLoad;
				}
				if(PageR!=NULL){
					PageR->ImageFileName=IFileNameStr;
				}
				else{
					goto	EndLoad;
				}
			}
			CurrentInspection.SetResultPage(phase,GlobalPage,Ins);

			Current->LastSeekPoint=File.pos();
		}
		else{
EndLoad:;
			GSleep(LoadWatingMilisec);
			for(int i=0;i<20;i++){
				if(::Load(&File,Type)==false){
					Current->LastSeekPoint=File.pos();
					return true;
				}
				if(Type==0)
					continue;
				if(strchr("LOSCN",Type)!=NULL){
					goto	ChallengeAgain;
				}
			}
		}
	}
}


bool	EachMaster::LoadNaming(QIODevice &File)
{
	int32	N;
	if(::Load(&File,N)==false){
		return false;
	}
	//----
	//----
	return true;
}

bool	EachMaster::LoadOutputLibData(QIODevice &File)
{
	int32	N;
	if(::Load(&File,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		QString	AlgoName;

		if(::Load(&File,AlgoName)==false){
			return false;
		}
		bool	LibExist;
		if(::Load(&File,LibExist)==false){
			return false;
		}
		if(LibExist==true){
			int32	LibIDListCount;
			if(::Load(&File,LibIDListCount)==false){
				return false;
			}
			for(int j=0;j<LibIDListCount;j++){
				int32	NGTypeContainerCount;
				if(::Load(&File,NGTypeContainerCount)==false){
					return false;
				}
				if(NGTypeContainerCount!=0){
						
					int32	LibNGTypeItemCount;
					if(::Load(&File,LibNGTypeItemCount)==false){
						return false;
					}
					for(int k=0;k<LibNGTypeItemCount;k++){
						QString	AlgoName;
						int32	LibID;
						int32	TypeCode;
						QColor	NGColor;

						if(::Load(&File,AlgoName)==false){
							return false;
						}
						
						if(::Load(&File,LibID)==false){
							return false;
						}
						QString	LibName;
						if(::Load(&File,LibName)==false){
							return false;
						}
						if(::Load(&File,TypeCode)==false){
							return false;
						}
						QString	TypeName;
						if(::Load(&File,TypeName)==false){
							return false;
						}
						if(::Load(&File,NGColor)==false){
							return false;
						}
						int32	NGShape;
						if(::Load(&File,NGShape)==false){
							return false;
						}
						bool	Blink;
						if(::Load(&File,Blink)==false){
							return false;
						}
						int32	Priority;
						if(::Load(&File,Priority)==false){
							return false;
						}
						int32	NextJumpMilisec;
						if(::Load(&File,NextJumpMilisec)==false){
							return false;
						}
					}
				}
				else{
					QString	AlgoName;
					int32	LibID;
					if(::Load(&File,AlgoName)==false){
						return false;
					}
					if(::Load(&File,LibID)==false){
						return false;
					}
					QString	LibName;
					if(::Load(&File,LibName)==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}
	
void	EachMaster::ReleaseImageBuffer(void)
{
	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<PageNumb;page++){
			if(MasterImage!=NULL){
				delete	[]MasterImage[phase][page];
			}
			if(TargetImage!=NULL){
				delete	[]TargetImage[phase][page];
			}
		}
		if(MasterImage!=NULL){
			delete	[]MasterImage[phase];
		}
		if(TargetImage!=NULL){
			delete	[]TargetImage[phase];
		}
	}
	if(MasterImage!=NULL){
		delete	[]MasterImage;
	}
	if(TargetImage!=NULL){
		delete	[]TargetImage;
	}
	MasterImage=NULL;
	TargetImage=NULL;
}

void	EachMaster::AllocateImageBuffer(void)
{
	if(GetParamIntegrationMaster()->AllocateMasterBuff==true){
		MasterImage=new ImageBuffer**[PhaseNumb];
		for(int phase=0;phase<PhaseNumb;phase++){
			MasterImage[phase]=new ImageBuffer*[PageNumb];
			for(int page=0;page<PageNumb;page++){
				int	Index=phase*PageNumb+page;
				int	LayerNumb=GetLayerNumb(phase,page);
				MasterImage[phase][page]=new ImageBuffer[LayerNumb];
				for(int layer=0;layer<LayerNumb;layer++){
					MasterImage[phase][page][layer].Set(page,ImageBufferMaster,CData[Index].DotPerLine,CData[Index].MaxLines);
				}
			}
		}
	}
	if(GetParamIntegrationMaster()->AllocateTargetBuff==true){
		TargetImage=new ImageBuffer**[PhaseNumb];
		for(int phase=0;phase<PhaseNumb;phase++){
			TargetImage[phase]=new ImageBuffer*[PageNumb];
			for(int page=0;page<PageNumb;page++){
				int	Index=phase*PageNumb+page;
				int	LayerNumb=GetLayerNumb(phase,page);
				TargetImage[phase][page]=new ImageBuffer[LayerNumb];
				for(int layer=0;layer<LayerNumb;layer++){
					TargetImage[phase][page][layer].Set(page,ImageBufferTarget,CData[Index].DotPerLine,CData[Index].MaxLines);
				}
			}
		}
	}
}

void	EachMaster::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{
	x1=  99999999;
	y1=  99999999;
	x2= -99999999;
	y2= -99999999;
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);
			int	px1=L->x;
			int	py1=L->y;
			int	px2=L->x+GetDotPerLine(Ph, page);
			int	py2=L->y+GetMaxLines(Ph, page);

			x1=min(x1,px1);
			y1=min(y1,py1);
			x2=max(x2,px2);
			y2=max(y2,py2);
		}
	}
}
int		EachMaster::GetGlobalPage(int globalX ,int globalY)	const
{
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);
			int	x1=L->x;
			int	y1=L->y;
			int	x2=L->x+GetDotPerLine(Ph, page);
			int	y2=L->y+GetMaxLines(Ph, page);
			if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
				return page;
			}
		}
	}
	return -1;
}
void	EachMaster::GetGlobalPage(int globalX ,int globalY,IntList &PageList)	const
{
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);
			int	x1=L->x;
			int	y1=L->y;
			int	x2=L->x+GetDotPerLine(Ph, page);
			int	y2=L->y+GetMaxLines(Ph, page);
			if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
				PageList.Merge(page);
			}
		}
	}
}
void	EachMaster::GetGlobalPage(int globalX1 ,int globalY1 ,int globalX2 ,int globalY2 
								,IntList &PageList)	const
{
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);
			int	x1=L->x;
			int	y1=L->y;
			int	x2=L->x+GetDotPerLine(Ph, page);
			int	y2=L->y+GetMaxLines(Ph, page);
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
									,x1 ,y1 ,x2,y2)==true){
				PageList.Merge(page);
			}
		}
	}
}
int		EachMaster::GetPageFromArea(FlexArea &Area,IntList &PageList)	const
{
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);
			int	x1=L->x;
			int	y1=L->y;
			int	x2=L->x+GetDotPerLine(Ph, page);
			int	y2=L->y+GetMaxLines(Ph, page);
			if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
				PageList.Merge(page);
			}
		}
	}
	return PageList.GetCount();
}
int		EachMaster::GetPageFromVector(VectorLineBase *v,IntList &PageList)	const
{
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);
			int	x1=L->x;
			int	y1=L->y;
			int	x2=L->x+GetDotPerLine(Ph, page);
			int	y2=L->y+GetMaxLines(Ph, page);
			if(v->CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
				PageList.Merge(page);
			}
		}
	}
	return PageList.GetCount();
}

int		EachMaster::GetLocalMatrixFromGlobal(int globalX ,int globalY 
											,int &localX ,int &localY)	const
{
	for(int Ph=0;Ph<GetPhaseNumb();Ph++){
		for(int page=0;page<GetPageNumb();page++){
			XYData	*L=GetOutlineOffset(Ph, page);

			int	LocalX=globalX-L->x;
			int	LocalY=globalY-L->y;
			if(0<=LocalX && LocalX<GetDotPerLine(Ph, page) && 0<=LocalY && LocalY<GetMaxLines(Ph, page)){
				localX=LocalX;
				localY=LocalY;
				return page;
			}
		}
	}
	return -1;
}

void	EachMaster::GetGlobalMatrixFromLocal(int Page ,int localX ,int localY 
											,int &globalX ,int &globalY)	const
{
	XYData	*p=GetOutlineOffset(0, Page);
	if(p!=NULL){
		globalX=localX+p->x;
		globalY=localY+p->y;
	}
}
int		EachMaster::GetLocalPageFromGlobal(int GlobalPage)	const
{
	return GlobalPage;
}

bool	EachMaster::ReallocXYPixels(int page,int NewDotPerLine ,int NewMaxLines)
{
	ReleaseImageBuffer();
	for(int phase=0;phase<PhaseNumb;phase++){
		int	Index=phase*PageNumb+page;
		CData[Index].DotPerLine	=NewDotPerLine;
		CData[Index].MaxLines	=NewMaxLines;
	}
	AllocateImageBuffer();
	return true;
}

bool	EachMaster::MoveAll(bool Mastered,bool Targeted,int XDir,int YDir)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	iLayerNumb=GetLayerNumb(phase ,page);
			for(int layer=0;layer<iLayerNumb;layer++){
				if(Mastered==true){
					ImageBuffer	*B=GetMasterImage(phase ,page ,layer);
					if(B!=NULL){
						B->MoveImage(XDir,YDir);
					}
				}
				if(Targeted==true){
					ImageBuffer	*B=GetTargetImage(phase ,page ,layer);
					if(B!=NULL){
						B->MoveImage(XDir,YDir);
					}
				}
			}
		}
	}
}

bool	EachMaster::AddPhase(int _AddedPhaseCount)
{
	ImageBuffer	***TmpImage;

	DataInPage::ConstructionData	*tmpCData=new DataInPage::ConstructionData[(PhaseNumb+_AddedPhaseCount)*PageNumb];

	TmpImage=new ImageBuffer**[PhaseNumb+_AddedPhaseCount];
	for(int phase=0;phase<PhaseNumb;phase++){
		TmpImage[phase]=MasterImage[phase];
		MasterImage[phase]=NULL;
		for(int page=0;page<PageNumb;page++){
			int	Index=phase*PageNumb+page;
			tmpCData[Index]=CData[Index];
		}
	}
	for(int phase=PhaseNumb;phase<(PhaseNumb+_AddedPhaseCount);phase++){
		TmpImage[phase]=new ImageBuffer*[PageNumb];
		for(int page=0;page<PageNumb;page++){
			int	Index=phase*PageNumb+page;
			tmpCData[Index]=CData[page];
			int	LayerNumb=GetLayerNumb(PhaseNumb-1,page);
			TmpImage[phase][page]=new ImageBuffer[LayerNumb];
			for(int layer=0;layer<LayerNumb;layer++){
				TmpImage[phase][page][layer].Set(page,ImageBufferMaster,tmpCData[Index].DotPerLine,tmpCData[Index].MaxLines);
			}
		}
	}
	delete	[]CData;
	CData=tmpCData;
	delete	[]MasterImage;
	MasterImage=TmpImage;

	if(TargetImage!=NULL){
		TmpImage=new ImageBuffer**[PhaseNumb+_AddedPhaseCount];
		for(int phase=0;phase<PhaseNumb;phase++){
			TmpImage[phase]=TargetImage[phase];
			TargetImage[phase]=NULL;
		}
		for(int phase=PhaseNumb;phase<(PhaseNumb+_AddedPhaseCount);phase++){
			TmpImage[phase]=new ImageBuffer*[PageNumb];
			for(int page=0;page<PageNumb;page++){
				int	Index=phase*PageNumb+page;
				int	LayerNumb=GetLayerNumb(PhaseNumb-1,page);
				TmpImage[phase][page]=new ImageBuffer[LayerNumb];
				for(int layer=0;layer<LayerNumb;layer++){
					TmpImage[phase][page][layer].Set(page,ImageBufferTarget,CData[Index].DotPerLine,CData[Index].MaxLines);
				}
			}
		}
		delete	[]TargetImage;
		TargetImage=TmpImage;
	}

	for(int phase=PhaseNumb;phase<(PhaseNumb+_AddedPhaseCount);phase++){
		if(PhaseNumb>0){
			for(int page=0;page<PageNumb;page++){
				int	IndexS=page;
				int	IndexD=phase*PageNumb+page;
				CData[IndexD].OutlineOffset.x=CData[IndexS].OutlineOffset.x;
				CData[IndexD].OutlineOffset.y=CData[IndexS].OutlineOffset.y;
			}
		}
		else{
			for(int page=0;page<PageNumb;page++){
				int	IndexD=phase*PageNumb+page;
				CData[IndexD].OutlineOffset.x=0;
				CData[IndexD].OutlineOffset.y=0;
			}
		}
	}

	CurrentInspection.RemoveAll();

	PhaseNumb+=_AddedPhaseCount;

	return true;
}

bool	EachMaster::RemovePhase(int PhaseCode)
{
	if(0<=PhaseCode && PhaseCode<PhaseNumb){
		for(int page=0;page<PageNumb;page++){
			if(MasterImage!=NULL){
				delete	[]MasterImage[PhaseCode][page];
			}
		}
		delete	MasterImage[PhaseCode];
		for(int phase=PhaseCode;phase<PhaseNumb-1;phase++){
			MasterImage[phase]=MasterImage[phase+1];
		}
		MasterImage[PhaseNumb-1]=NULL;

		if(TargetImage!=NULL){
			for(int page=0;page<PageNumb;page++){
				if(TargetImage!=NULL){
					delete	[]TargetImage[PhaseCode][page];
				}
			}
			delete	TargetImage[PhaseCode];
			for(int phase=PhaseCode;phase<PhaseNumb-1;phase++){
				TargetImage[phase]=TargetImage[phase+1];
			}
			TargetImage[PhaseNumb-1]=NULL;
		}

		for(int phase=PhaseCode;phase<PhaseNumb-1;phase++){
			for(int page=0;page<PageNumb;page++){
				int	IndexS=(phase+1)*PageNumb+page;
				int	IndexD=phase*PageNumb+page;
				CData[IndexD]=CData[IndexS];
			}
		}

		for(InspectionList *L=CurrentInspection.GetFirst();L!=NULL;L=L->GetNext()){
			NGPointInAllPage	*Ph=L->NGPointAllPhases.GetItem(PhaseCode);
			if(Ph!=NULL){
				L->NGPointAllPhases.RemoveList(Ph);
				delete	Ph;
			}
			int	phasecode=0;
			for(NGPointInAllPage *p=L->NGPointAllPhases.GetFirst();p!=NULL;p=p->GetNext(),phasecode++){
				p->Phase=phasecode;
			}
		}
		if(CurrentPhase==PhaseNumb-1){
			CurrentPhase--;
		}
		PhaseNumb--;
		return true;
	}
	return false;
}

bool	EachMaster::LoadTargetImage(InspectionList *p,QString &RetImageFileName)
{
	QString	FileName=p->GetFileName();

	if(QFile::exists(FileName)==false){
		for(int i=0;i<Slave->ImageFolders.count();i++){
			QString	Folder=Slave->ImageFolders[i];
			QString	s=p->InspectionTime.toString(/**/"yyMMdd_hhmmss*.pix");
			QDir	cd(Folder);

			QStringList	FilterList;
			FilterList.append(s);
			QStringList	FileNames=cd.entryList(FilterList);
			if(FileNames.count()>=1){
				QString	filename=Folder+GetSeparator()+FileNames[0];
				if(QFile::exists(filename)==true){
					FileName=filename;
					break;
				}
			}
		}
	}
	if(QFile::exists(FileName)==true){
		LoadImage(FileName ,TargetImage);
		RetImageFileName=FileName;
	}
	return true;
}
bool	EachMaster::LoadMasterImage(ImageBuffer ***ImageNuff)
{
	bool	Ret=true;
	for(int Phase=0;Phase<PhaseNumb;Phase++){
		for(int Page=0;Page<PageNumb;Page++){
			QString	Path=GetParamGlobal()->ImageFilePath;
			QString	FileName=CreateMasterImageFileName(Path,Phase,Page);
			ImageBuffer	*Buff=ImageNuff[Phase][Page];
			if(LoadMasterImageFile(Phase,Page,FileName,Buff)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

QString	EachMaster::CreateMasterImageFileName(const QString &ImagePath,int Phase,int Page)
{
	QString Sep=/**/"";
	QString s = ImagePath.right(1);
	if(s!=::GetSeparator() && s!=QString("\\")){
		Sep= GetSeparator();
	}
	QString	Ret;
	if(Phase==0){
		Ret =ImagePath+Sep
			+QString("Image")+QString::number(MasterCode)+QString("-")
			+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(Page))+QString("-")
			+QString("Mac")+QString::number(GetMachineCode())
			+QString(".img");
	}
	else{
		Ret =ImagePath+Sep
			+QString("Image")+QString::number(MasterCode)+QString("-")
			+QString("Phase")+QString::number(Phase)+QString("-")
			+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(Page))+QString("-")
			+QString("Mac")+QString::number(GetMachineCode())
			+QString(".img");
	}
	return Ret;
}

bool	EachMaster::LoadMasterImageFile(int Phase, int Page ,const QString &ImageFileName ,ImageBuffer *BufferByLayer)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile	ImageFile(ImageFileName);
		if(ImageFile.open(QIODevice::ReadOnly)==false){
			return false;
		}
		if(LoadMasterImageFile(Phase, Page,ImageFile,BufferByLayer)==false){
			return false;
		}
	}
	/*
	else{
		TrFile	ImageFile(ImageFileName ,GetParamGlobal()->TransDatabaseIP
										,GetParamGlobal()->ImageFileCachePort);
		if(ImageFile.open(QIODevice::ReadOnly)==false){
			return false;
		}
		if(LoadMasterImageFile(ImageFile,BufferByLayer)==false){
			return false;
		}
	}
	*/
	return true;
}

bool	EachMaster::LoadMasterImageFile(int Phase, int Page ,QIODevice &ImageFile,ImageBuffer *BufferByLayer)
{
	for(int LNumb=0;LNumb<GetLayerNumb(Phase,Page);LNumb++){
		if(GetParamGlobal()->NoLoadSaveMasterImage==false){
			if(BufferByLayer[LNumb].Load(&ImageFile,false)==false){
				return false;
			}
			if(BufferByLayer[LNumb].IsNull()==false){
				BufferByLayer[LNumb].SetChanged(false);
			}
			ImageBuffer	Dummy;
			if(Dummy.Load(&ImageFile)==false){
				return false;
			}
			if(Dummy.Load(&ImageFile)==false){
				return false;
			}
			GetParamGlobal()->IsLoadedMasterImageSuccessful=true;
		}
		else{
			BufferByLayer[LNumb].SetChanged(false);
			GetParamGlobal()->IsLoadedMasterImageSuccessful=false;
		}
	}
	return true;
}

bool EachMaster::LoadImage(QString FileName ,ImageBuffer ***Buff)
{
	QFile	RFile(FileName);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;
	if(Ver>=2){
		if(::Load(&RFile,iPhaseNumb)==false)
			return false;
	}
	if(::Load(&RFile,iPageNumb)==false)
		return false;
	if(::Load(&RFile,iLayerNumb)==false)
		return false;
	if(::Load(&RFile,iDotPerLine)==false)
		return false;
	if(::Load(&RFile,iMaxLines)==false)
		return false;
	if(::Load(&RFile,iYCountBase)==false)
		return false;

	int	ProcessCount[10000];
	for(int page=0;page<PageNumb;page++){
		ProcessCount[page]=0;
	}
	for(int phase=0;phase<iPhaseNumb && phase<PhaseNumb;phase++){
		for(int page=0;page<PageNumb && page<iPageNumb;page++){
			int	Index=phase*PageNumb+page;
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<CData[Index].MaxLines && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines){
					YCount=iMaxLines-TopY;
				}
				ProcessCount[page]++;
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines){
						YCount=iMaxLines-TopY;
					}
					ProcessCount[page]++;
				}			
			}
			ProcessCount[page]++;
		}
	}

	GetLayersBase()->ShowProcessingForm ("Load PIX image in target buffer");
	GetLayersBase()->SetMaxProcessing(ProcessCount[0]);

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<PageNumb && page<iPageNumb;page++){
			int	Index=phase*PageNumb+page;
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<CData[Index].GetMaxLines() && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				int	LayerNumb=GetLayerNumb(phase,page);
				for(Layer=0;Layer<LayerNumb && Layer<iLayerNumb;Layer++){
					QByteArray	Array=RFile.read(YCount*iDotPerLine);
					BYTE	*Src=(BYTE *)Array.data();
					int		SrcByte=Array.size();
					int	XLen=min(iDotPerLine,CData[Index].DotPerLine);
					for(int y=TopY;y<TopY+YCount;y++){
						if(y<CData[Index].MaxLines && SrcByte>=XLen){
							memcpy(Buff[phase][page][Layer].GetY(y),Src,XLen);
							Src+=iDotPerLine;
							SrcByte-=XLen;
						}
					}
				}
				if(Layer<iLayerNumb){
					for(;Layer<iLayerNumb;Layer++){
						RFile.read(YCount*iDotPerLine);
					}
				}
				GetLayersBase()->StepProcessing(page);
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines)
						YCount=iMaxLines-TopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb;Layer++){
						RFile.read(YCount*iDotPerLine);
					}
					GetLayersBase()->StepProcessing(page);
				}			
			}
			GetLayersBase()->StepProcessing(page);
		}
	}
	GetLayersBase()->CloseProcessingForm ();

	return true;
}
bool	EachMaster::GetXY(int &areax1, int &areay1 ,int &areax2 ,int &areay2)	const
{
	areax1=99999999;
	areay1=99999999;
	areax2=-99999999;
	areay2=-99999999;
	bool	Ret=false;
	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<PageNumb;page++){
			int	Index=phase*PageNumb+page;
			XYData	c=CData[Index].OutlineOffset;
			int	x1=c.x;
			int	y1=c.y;
			int	x2=c.x+CData[Index].DotPerLine;
			int	y2=c.y+CData[Index].MaxLines;
			areax1=min(areax1,x1);
			areay1=min(areay1,y1);
			areax2=max(areax2,x2);
			areay2=max(areay2,y2);
			Ret=true;
		}
	}
	return Ret;
}

XYData	*EachMaster::GetOutlineOffset(int phase, int page)	const
{
	int	Index=phase*PageNumb+page;
	return &CData[Index].OutlineOffset;
}

void EachMaster::DrawImage(QImage *Img,XYData &c
							,int phase ,int page
							,ImageBuffer *IBuff[]
							,double ZoomRate,int movx ,int movy
							,bool EnableToColorizeFor3Layers)
{
	if(CData==NULL){
		return;
	}
	int	Yn=Img->height();
	int	Xn=Img->width();
	int	Index=phase*PageNumb+page;
	int	iDotPerLine	=CData[Index].DotPerLine;
	int	iMaxLines	=CData[Index].MaxLines;

	double	Z=1.0/ZoomRate;
	int	LayerNumb=GetLayerNumb(phase,page);
	if(LayerNumb>=3){
		if(IBuff[0]!=NULL
		&& IBuff[1]!=NULL
		&& IBuff[2]!=NULL){
			if(EnableToColorizeFor3Layers==true){
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<Yn;y++){
						QRgb	*d=(QRgb *)Img->scanLine(y);
						int	Y=y*Z-movy-c.y;
						if(Y<0 || iMaxLines<=Y)
							continue;
						BYTE	*sr=IBuff[0]->GetY(Y);
						BYTE	*sg=IBuff[1]->GetY(Y);
						BYTE	*sb=IBuff[2]->GetY(Y);
						for(int x=0;x<Xn;x++,d++){
							int	X=x*Z-movx-c.x;
							if(0<=X && X<iDotPerLine){
								*d=qRgba(sr[X],sg[X],sb[X],255);
							}
						}
					}
				}
			}
			else{
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<Yn;y++){
						QRgb	*d=(QRgb *)Img->scanLine(y);
						int	Y=y*Z-movy-c.y;
						if(Y<0 || iMaxLines<=Y)
							continue;
						BYTE	*sr=IBuff[0]->GetY(Y);
						BYTE	*sg=IBuff[1]->GetY(Y);
						BYTE	*sb=IBuff[2]->GetY(Y);
						for(int x=0;x<Xn;x++,d++){
							int	X=x*Z-movy-c.x;
							if(0<=X && X<iDotPerLine){
								int	c=sqrt((sr[X]*sr[X]+sg[X]*sg[X]+sb[X]*sb[X])/3.0);
								*d=qRgba(c,c,c,255);
							}
						}
					}
				}
			}
		}
	}
	else if(LayerNumb==2){
		if(IBuff[0]!=NULL
		&& IBuff[1]!=NULL){
			if(EnableToColorizeFor3Layers==true){
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<Yn;y++){
						QRgb	*d=(QRgb *)Img->scanLine(y);
						int	Y=y*Z-movy-c.y;
						if(Y<0 || iMaxLines<=Y)
							continue;
						BYTE	*sr=IBuff[0]->GetY(Y);
						BYTE	*sg=IBuff[1]->GetY(Y);
						for(int x=0;x<Xn;x++,d++){
							int	X=x*Z-movy-c.x;
							if(0<=X && X<iDotPerLine){
								*d=qRgba(sr[X],sg[X],sg[X],255);
							}
						}
					}
				}
			}
			else{
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<Yn;y++){
						QRgb	*d=(QRgb *)Img->scanLine(y);
						int	Y=y*Z-movy-c.y;
						if(Y<0 || iMaxLines<=Y)
							continue;
						BYTE	*sr=IBuff[0]->GetY(Y);
						BYTE	*sg=IBuff[1]->GetY(Y);
						for(int x=0;x<Xn;x++,d++){
							int	X=x*Z-movx-c.x;
							if(0<=X && X<iDotPerLine){
								int	c=sqrt((sr[X]*sr[X]+sg[X]*sg[X])/2.0);
								*d=qRgba(c,c,c,255);
							}
						}
					}
				}
			}
		}
	}
	else if(LayerNumb==1){
		if(IBuff[0]!=NULL){
			if(EnableToColorizeFor3Layers==true){
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<Yn;y++){
						QRgb	*d=(QRgb *)Img->scanLine(y);
						int	Y=y*Z-movy-c.y;
						if(Y<0 || iMaxLines<=Y)
							continue;
						BYTE	*sr=IBuff[0]->GetY(Y);
						for(int x=0;x<Xn;x++,d++){
							int	X=x*Z-movx-c.x;
							if(0<=X && X<iDotPerLine){
								*d=qRgba(sr[X],sr[X],sr[X],255);
							}
						}
					}
				}
			}
			else{
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<Yn;y++){
						QRgb	*d=(QRgb *)Img->scanLine(y);
						int	Y=y*Z-movy-c.y;
						if(Y<0 || iMaxLines<=Y)
							continue;
						BYTE	*sr=IBuff[0]->GetY(Y);
						for(int x=0;x<Xn;x++,d++){
							int	X=x*Z-movx-c.x;
							if(0<=X && X<iDotPerLine){
								*d=qRgba(sr[X],sr[X],sr[X],255);
							}
						}
					}
				}
			}
		}
	}
}
int		EachMaster::GetIntegrationSlaveNo(void)	const
{
	int	N=Parent->GetIntegrationSlaveCount();
	for(int i=0;i<N;i++){
		EachMaster *m=Parent->MasterDatas[i];
		if(m==this)
			return i;
	}
	return -1;
}
bool	EachMaster::RequireMasterImage(bool MixMaster,int SparseCountOfLine)
{
	if(GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		if(MasterImage==NULL){
			AllocateImageBuffer();
		}
		if(MasterImage==NULL)
			return false;

		int	ErrorLoopCounter=0;
		int	LineCount=SparseCountOfLine;
		int	SlaveNo	=GetIntegrationSlaveNo();
		IntegrationReqMasterImage	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		IntegrationAckMasterImage	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			for(int Page=0;Page<GetPageNumb();Page++){
				int	Index=Phase*PageNumb+Page;
				int	LayerNumb=GetLayerNumb(Phase,Page);
				for(int Layer=0;Layer<LayerNumb;Layer++){
					ImageBuffer	&Buff=MasterImage[Phase][Page][Layer];
					for(int y=0;y<CData[Index].GetMaxLines();y+=LineCount){
						RCmd.Info.Phase	=Phase;
						RCmd.Info.Page	=Page;
						RCmd.Info.Layer	=Layer;
						RCmd.Info.TopY	=y;
						RCmd.Info.LineCount	=LineCount;
						RCmd.Info.MixMaster	=MixMaster;
						if(RCmd.Info.TopY+RCmd.Info.LineCount>CData[Index].GetMaxLines()){
							RCmd.Info.LineCount=CData[Index].GetMaxLines()-RCmd.Info.TopY;
						}
						SendAgain:;
						if(RCmd.Send(SlaveNo,0,ACmd,10000)==true){
							BYTE	*s=ACmd.Data;
							int	XLen=min(CData[Index].GetDotPerLine(),ACmd.Info.DotPerLine);
							for(int i=0;i<ACmd.Info.LineCount;i++){
								BYTE	*d=Buff.GetY(ACmd.Info.TopY+i);
								memcpy(d,s,XLen);
								s+=XLen;
							}
						}
						else{
							if(ErrorLoopCounter<10){
								ErrorLoopCounter++;
								goto	SendAgain;
							}
							return false;
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool	EachMaster::RequireMasterImageInPhase(int Phase,bool MixMaster)
{
	if(GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		if(MasterImage==NULL){
			AllocateImageBuffer();
		}
		if(MasterImage==NULL)
			return false;

		int	LineCount=100;
		int	SlaveNo	=GetIntegrationSlaveNo();
		IntegrationReqMasterImage	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		IntegrationAckMasterImage	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		for(int Page=0;Page<GetPageNumb();Page++){
			int	Index=Phase*PageNumb+Page;
			int	LayerNumb=GetLayerNumb(Phase,Page);
			for(int Layer=0;Layer<LayerNumb;Layer++){
				ImageBuffer	&Buff=MasterImage[Phase][Page][Layer];
				for(int y=0;y<CData[Index].GetMaxLines();y+=LineCount){
					RCmd.Info.Phase	=Phase;
					RCmd.Info.Page	=Page;
					RCmd.Info.Layer	=Layer;
					RCmd.Info.TopY	=y;
					RCmd.Info.LineCount	=LineCount;
					RCmd.Info.MixMaster	=MixMaster;
					if(RCmd.Info.TopY+RCmd.Info.LineCount>CData[Index].GetMaxLines()){
						RCmd.Info.LineCount=CData[Index].GetMaxLines()-RCmd.Info.TopY;
					}
					if(RCmd.Send(SlaveNo,0,ACmd)==true){
						BYTE	*s=ACmd.Data;
						for(int i=0;i<ACmd.Info.LineCount;i++){
							BYTE	*d=Buff.GetY(ACmd.Info.TopY+i);
							memcpy(d,s,CData[Index].GetDotPerLine());
							s+=CData[Index].GetDotPerLine();
						}
					}
					else{
						return false;
					}
				}
			}
		}
		
		return true;
	}
	return false;
}
bool	EachMaster::RequireSlaveInfo(void)
{
	if(GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		int	SlaveNo	=GetIntegrationSlaveNo();
		IntegrationReqMasterInfo	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		IntegrationAckMasterInfo	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			MasterCode	=ACmd.MasterCode;
			PhaseNumb	=ACmd.PhaseNumb	;
			PageNumb	=ACmd.PageNumb	;
			//LayerNumb	=ACmd.LayerNumb	;
			if(LayerNumbDim!=NULL){
				delete	[]LayerNumbDim;
			}
			LayerNumbDim=new int32[PageNumb];
			for(int page=0;page<PageNumb;page++){
				LayerNumbDim[page]=ACmd.LayerNumbDim[page];
			}

			TransformUnitPerPixelX	=ACmd.TransformUnitPerPixelX;
			TransformUnitPerPixelY	=ACmd.TransformUnitPerPixelY;
			if(CData!=NULL){
				delete	[]CData;
			}
			CData=new DataInPage::ConstructionData[PhaseNumb*PageNumb];
			for(int phase=0;phase<PhaseNumb;phase++){
				for(int page=0;page<PageNumb;page++){
					int	Index=phase*PageNumb+page;
					CData[Index]=ACmd.CData[Index];
				}
			}

			if(AccessToPageDim!=NULL){
				delete	[]AccessToPageDim;
			}
			AccessToPageDim=new AccessToPage[PageNumb];
			ParamIntegrationMaster	*c=GetParamIntegrationMaster();
			for(int page=0;page<PageNumb;page++){
				AccessToPageDim[page]=ACmd.AccessToPageDim[page];
				if(AccessToPageDim[page].Port==0){
					AccessToPageDim[page].IPAddress	=c->Slaves[SlaveNo]->SlaveAddress;
					AccessToPageDim[page].Port		=c->IntegrationPageDirectlyPortNo;
				}
			}

			LoadOutlineOffsetForDatabase();
			return true;
		}
	}
	return false;
}

bool	EachMaster::ReqPhaseNames(QStringList &RetPhaseNames)
{
	int	SlaveNo	=GetIntegrationSlaveNo();
	IntegrationCmdReqPhaseNames	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
	IntegrationCmdAckPhaseNames	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		RetPhaseNames=ACmd.PhaseNames;
		return true;
	}
	return false;
}

bool	EachMaster::SetPhaseName(int Phase ,const QString PhaseName)
{
	int	SlaveNo	=GetIntegrationSlaveNo();
	IntegrationCmdSetPhase	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
	RCmd.Phase=Phase;
	RCmd.PhaseName=PhaseName;
	if(RCmd.Send(NULL,SlaveNo,0)==true){
		return true;
	}
	return false;
}

bool	EachMaster::LoadOutlineOffsetForDatabase(void)
{
	if(GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		OutlineOffsetInBlob outlineBlob(Parent->GetLayersBase());
		if(Parent->GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(*Parent->GetLayersBase()->GetDataBase() ,GetMachineCode()
								, &outlineBlob)==true){
			for(int phase=0; phase<PhaseNumb; phase++){
				for(int page=0; page<PageNumb; page++){
					int x = outlineBlob.GetData(phase, page).Dx;
					int y = outlineBlob.GetData(phase, page).Dy;
					int	Index=phase*PageNumb+page;
					CData[Index].OutlineOffset.x=x;
					CData[Index].OutlineOffset.y=y;
				}
			}
			return true;
		}
	}
	return false;
}

bool	EachMaster::AddCurrentLot(LotList *L)
{
	if(L==NULL){
		return false;
	}
	for(LotList *a=LotContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LotFileName==L->LotFileName){
			LotContainer.RemoveList(a);
			if(a!=L){
				a->LotName=L->LotName;
			}
			LotContainer.AppendList(a);
			SetCurrentLot(a);
			return;
		}
	}
	SetCurrentLot(L);
	LotContainer.AppendList(L);
	CurrentInspection.RemoveAll();
	return true;
}
void	EachMaster::SlotDoneLoadResult(InspectionList *n)
{
	emit	SignalDoneLoadResult(n);
}

double	EachMaster::TransformPixelDistanceToUnit(double PixelX1,double PixelY1 ,double PixelX2,double PixelY2)	const
{
	return TransformPixelDistanceToUnit(PixelX2-PixelX1,PixelY2-PixelY1);
}
double	EachMaster::TransformUnitDistanceToPixel(double UnitX1 ,double UnitY1  ,double UnitX2 ,double UnitY2)	const
{
	return TransformUnitDistanceToPixel(UnitX2-UnitX1,UnitY2-UnitY1);
}
double	EachMaster::TransformPixelDistanceToUnit(double PixelXLen,double PixelYLen)	const
{
	double	Len=hypot(PixelXLen,PixelYLen);
	if(Len==0.0){
		return 0.0;
	}
	double	Px=PixelXLen/Len;
	double	Py=PixelYLen/Len;
	double	Ux=PixelXLen*Px*TransformUnitPerPixelX;
	double	Uy=PixelYLen*Py*TransformUnitPerPixelY;
	return hypot(Ux,Uy);
}
double	EachMaster::TransformUnitDistanceToPixel(double UnitXLen ,double UnitYLen)	const
{
	double	Len=hypot(UnitXLen,UnitYLen);
	if(Len==0.0){
		return 0.0;
	}
	double	Ux=UnitXLen/Len;
	double	Uy=UnitYLen/Len;
	double	Px=UnitXLen*Ux/TransformUnitPerPixelX;
	double	Py=UnitYLen*Uy/TransformUnitPerPixelY;
	return hypot(Px,Py);
}

double	EachMaster::TransformPixelToUnit(double pixel)	const
{	
	double	AvrTransformUnitPerPixel=(TransformUnitPerPixelX+TransformUnitPerPixelY)/2;
	return AvrTransformUnitPerPixel*pixel;
}
double	EachMaster::TransformUnitToPixel(double unit)	const
{	
	double	AvrTransformUnitPerPixel=(TransformUnitPerPixelX+TransformUnitPerPixelY)/2;
	return unit/AvrTransformUnitPerPixel;
}

QString	EachMaster::TransformPixelToUnitStr(double pixel)	const
{
	double	AvrTransformUnitPerPixel=(TransformUnitPerPixelX+TransformUnitPerPixelY)/2;
	return GetUnitStr(pixel*AvrTransformUnitPerPixel);
}
QString	EachMaster::GetUnitStr(void)	const
{
	return GetParamGlobal()->UnitName;
}
QString	EachMaster::GetUnitStr(double unit)	const
{
	return QString::number(unit,'f',GetParamGlobal()->SmallNumberFigure)
		  +QString(' ')
		  +GetParamGlobal()->UnitName;
}

double	EachMaster::TransformPixelToUnitSquare(double pixel)	const
{
	return pixel*TransformUnitPerPixelX*TransformUnitPerPixelY;
}	
double	EachMaster::TransformUnitToPixelSquare(double unit)		const
{
	return unit/(TransformUnitPerPixelX*TransformUnitPerPixelY);
}
QString	EachMaster::TransformPixelToUnitSquareStr(double pixel)	const
{
	return GetUnitSquareStr(pixel*TransformUnitPerPixelX*TransformUnitPerPixelY);
}

QString	EachMaster::GetUnitSquareStr(double unit)	const
{
	return QString::number(unit,'f',GetParamGlobal()->SmallNumberFigure)
		  +QString(' ')
		  +GetParamGlobal()->UnitSquareName;
}


LotList &LotList::operator=(const LotList &src)	
{	
	LotName		=src.LotName;
	LotID		=src.LotID;
	LotFileName	=src.LotFileName;
	GlobalID	=src.GlobalID;
	LastSeekPoint=src.LastSeekPoint;
	return *this;
}
LotListContainer	&LotListContainer::operator=(const LotListContainer &src)
{
	RemoveAll();
	for(LotList	*s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LotList	*d=new LotList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

LotListContainer	&LotListContainer::operator=(const NPListPack<LotList> &src)
{
	RemoveAll();
	for(LotList	*s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LotList	*d=new LotList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	LotListContainer::MergeByFileName(LotList *a)
{
	for(LotList	*s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->LotFileName==a->LotFileName){
			return false;
		}
	}
	AppendList(a);
	return true;
}

//=================================================================================
IntegrationCommonData::IntegrationCommonData(void)
{
	CommonSizeX	=100.0;
	CommonSizeY	=100.0;
	CommonSizeZ	=0.0;
	AddedX		=0.0;
	AddedY		=0.0;
	AddedZ		=0.0;

}

IntegrationCommonData::IntegrationCommonData(const QByteArray &data)	
{
	QBuffer	Buff((QByteArray *)&data);
	Buff.open(QIODevice::ReadOnly);
	Load(&Buff);
}

bool	IntegrationCommonData::Save(QIODevice *f)
{
	int32	Ver=4;

	if(::Save(f,Ver		   )==false)	return false;
	if(::Save(f,CommonSizeX)==false)	return false;
	if(::Save(f,CommonSizeY)==false)	return false;
	if(::Save(f,CommonSizeZ)==false)	return false;
	if(::Save(f,RelationName)==false)	return false;
	if(::Save(f,RelationRemark)==false)	return false;
	if(::Save(f,Something	)==false)	return false;
	if(::Save(f,RelationNumber)==false)	return false;
	if(::Save(f,AddedX		)==false)	return false;
	if(::Save(f,AddedY		)==false)	return false;
	if(::Save(f,AddedZ		)==false)	return false;
	
	return true;
}
bool	IntegrationCommonData::Load(QIODevice *f)
{
	int32	Ver=0;
	if(::Load(f,Ver		   )==false)	return false;
	if(::Load(f,CommonSizeX)==false)	return false;
	if(::Load(f,CommonSizeY)==false)	return false;
	if(::Load(f,CommonSizeZ)==false)	return false;
	if(::Load(f,RelationName)==false)	return false;
	if(::Load(f,RelationRemark)==false)	return false;
	if(Ver>=2){
		if(::Load(f,Something	)==false)	return false;
	}
	if(Ver>=2){
		if(::Load(f,RelationNumber)==false)	return false;
	}
	if(Ver>=4){
		if(::Load(f,AddedX		)==false)	return false;
		if(::Load(f,AddedY		)==false)	return false;
		if(::Load(f,AddedZ		)==false)	return false;
	}
	return true;
}
IntegrationCommonData	&IntegrationCommonData::operator=(IntegrationCommonData &src)
{
	CommonSizeX		=src.CommonSizeX;
	CommonSizeY		=src.CommonSizeY;
	CommonSizeZ		=src.CommonSizeZ;
	RelationName	=src.RelationName;
	RelationRemark	=src.RelationRemark;
	RelationNumber	=src.RelationNumber;
	Something		=src.Something;
	AddedX			=src.AddedX;
	AddedY			=src.AddedY;
	AddedZ			=src.AddedZ;
	return *this;
}

//=================================================================================
IntegrationBase::IntegrationBase(LayersBase *base,ParamIntegrationMaster	*p)
	:ServiceForLayers(base),ParamIntegrationMasterData(p)
{
	CurrentLotGlobalID	=-1;
	MasterRelationCode	=-1;
	TotalCount			=0;
	NGCount				=0;
	AvailableIntegrationResource	=true;
	ThresholdLevelID	=0;
	ReEntrant			=false;
}

IntegrationBase::~IntegrationBase(void)
{
}

bool	IntegrationBase::Initialize(void)
{
	MasterDatas.RemoveAll();

	if(GetLayersBase()->GetDataBase()==NULL || GetLayersBase()->GetDataBase()->isOpen()==false)
		return false;

	for(IntegrationSlave *s=ParamIntegrationMasterData->Slaves.GetFirst();s!=NULL;s=s->GetNext()){
		EachMaster	*m=new EachMaster(this,s);
		QString NetID;
		QString Name;
		QString Version;
		QString Remark;

		GetLayersBase()->GetDatabaseLoader()->G_GetMachineInfo(*GetLayersBase()->GetDataBase() ,m->GetMachineCode()
								,NetID
								,Name
								,Version
								,Remark);
		m->SetMachineName(Name);
		connect(m,SIGNAL(SignalDoneLoadResult(InspectionList *)),this,SLOT(SlotDoneLoadResult(InspectionList *)));
		MasterDatas.AppendList(m);

	}

	new IntegrationReqMasterImage			(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationAckMasterImage			(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationReqMasterInfo			(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationAckMasterInfo			(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationReqAlive					(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationAckAlive					(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationExecuteInitialAfterEdit	(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCmdAddPhase				(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCmdDelPhase				(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCmdChangeCurrentPhase	(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCmdReqPhaseNames			(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCmdAckPhaseNames			(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCmdSetPhase				(GetLayersBase(),/**/"ANY",/**/"ANY");

	new IntegrationReqUsageAlgorithm		(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationAckUsageAlgorithm		(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationReqReportedTopics		(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationAckReportedTopics		(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationAck						(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationSetThresholdLevel		(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationCopyThresholdLevel		(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationRebuildThresholdLevel	(GetLayersBase(),/**/"ANY",/**/"ANY");
	new IntegrationSetCurrentIntoThresholdLevel	(GetLayersBase(),/**/"ANY",/**/"ANY");

	return true;
}
bool	IntegrationBase::InitialForLocalHost(void)
{
	bool	Ret=true;
	for(IntegrationSlave *s=ParamIntegrationMasterData->Slaves.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->SlaveAddress==/**/"localhost" 
		|| s->SlaveAddress==/**/"127.0.0.0"){
			EachMaster	*m=FindMaster(s->MachineCode);
			if(m!=NULL){
				if(m->RequireSlaveInfo()==false){
					Ret=false;
				}
			}
		}
	}
	return Ret;
}
bool	IntegrationBase::IsLocal(int SlaveNo)	const
{
	IntegrationSlave *s=ParamIntegrationMasterData->Slaves[SlaveNo];
	if(s!=NULL){
		if(s->SlaveAddress==/**/"localhost" 
		|| s->SlaveAddress==/**/"127.0.0.0"){
			return true;
		}
	}
	return false;

}

//bool	IntegrationBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
//{
//	bool	Ret=true;
//	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
//		if(m->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
//			Ret=false;
//		}
//	}
//	return Ret;
//}

bool	IntegrationBase::AddPhase(int SlaveNo ,QStringList &AddedPhaseNameList)
{
	if(ReEntrant==true){
		return true;
	}
	ReEntrant=true;
	bool	Ret=true;
	int	AddedPhaseNumb=AddedPhaseNameList.count();
	if(SlaveNo==-1){
		for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->AddPhase(AddedPhaseNumb)==false){
				Ret=false;
			}
			int	sNo=m->GetIntegrationSlaveNo();
			IntegrationCmdAddPhase	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
			Cmd.PhaseNameList=AddedPhaseNameList;
			if(Cmd.Send(NULL,sNo,0)==false){
				Ret=false;
			}
		}
	}
	else{
		EachMaster *m=GetMaster(SlaveNo);
		if(m!=NULL){
			if(m->AddPhase(AddedPhaseNumb)==false){
				Ret=false;
			}
			IntegrationCmdAddPhase	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
			Cmd.PhaseNameList=AddedPhaseNameList;
			if(Cmd.Send(NULL,SlaveNo,0)==false){
				Ret=false;
			}
		}
	}
	ReEntrant=false;

	return Ret;
}
bool	IntegrationBase::SetCurrentPhase(int SlaveNo ,int PhaseCode)
{
	if(ReEntrant==true){
		return true;
	}
	ReEntrant=true;
	bool	Ret=true;
	if(SlaveNo==-1){
		for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	sNo=m->GetIntegrationSlaveNo();
			IntegrationCmdChangeCurrentPhase	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
			Cmd.PhaseNo=PhaseCode;
			if(Cmd.Send(NULL,sNo,0)==false){
				Ret=false;
			}
			m->SetCurrentPhase(PhaseCode);
		}
	}
	else{
		EachMaster *m=GetMaster(SlaveNo);
		if(m!=NULL){
			IntegrationCmdChangeCurrentPhase	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
			Cmd.PhaseNo=PhaseCode;
			if(Cmd.Send(NULL,SlaveNo,0)==false){
				Ret=false;
			}
			m->SetCurrentPhase(PhaseCode);
		}
	}
	ReEntrant=false;

	return Ret;
}
bool	IntegrationBase::RemovePhase(int SlaveNo ,int PhaseCode)
{
	bool	Ret=true;
	if(SlaveNo==-1){
		for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->RemovePhase(PhaseCode)==false){
				Ret=false;
			}
			int	sNo=m->GetIntegrationSlaveNo();
			IntegrationCmdDelPhase	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
			Cmd.PhaseNo=PhaseCode;
			if(Cmd.Send(NULL,sNo,0)==false){
				Ret=false;
			}
		}
	}
	else{
		EachMaster *m=GetMaster(SlaveNo);
		if(m!=NULL){
			if(m->RemovePhase(PhaseCode)==false){
				Ret=false;
			}
			int	SlaveNo=m->GetIntegrationSlaveNo();
			IntegrationCmdDelPhase	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
			Cmd.PhaseNo=PhaseCode;
			if(Cmd.Send(NULL,SlaveNo,0)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
bool	IntegrationBase::DeliverRebuildThresholdLevel(void)
{
	if(ReEntrant==true){
		return true;
	}
	ReEntrant=true;

	bool	Ret=true;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	sNo=m->GetIntegrationSlaveNo();
		IntegrationRebuildThresholdLevel	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
		if(Cmd.Send(NULL,sNo,0)==false){
			Ret=false;
		}
	}
	ReEntrant=false;

	return Ret;
}
bool	IntegrationBase::DeliverThresholdLevel(int LevelID)
{
	if(ReEntrant==true){
		return true;
	}
	ReEntrant=true;

	bool	Ret=true;
	int		OldLevelID=LevelID;
	ThresholdLevelID=LevelID;

	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	sNo=m->GetIntegrationSlaveNo();
		IntegrationSetThresholdLevel	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
		Cmd.LevelID=LevelID;
		if(Cmd.Send(NULL,sNo,0)==false){
			Ret=false;
		}
	}
	emit	SignalChangeThresholdLevel(OldLevelID ,ThresholdLevelID);
	ReEntrant=false;

	return Ret;
}

bool	IntegrationBase::DeliverCopyThresholdLevel(int SourceLevelID ,int DestLevelID)
{
	if(ReEntrant==true){
		return true;
	}
	ReEntrant=true;
	bool	Ret=true;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	sNo=m->GetIntegrationSlaveNo();
		IntegrationCopyThresholdLevel	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
		Cmd.SourceLevelID	=SourceLevelID;
		Cmd.DestLevelID		=DestLevelID;
		if(Cmd.Send(NULL,sNo,0)==false){
			Ret=false;
		}
	}
	ReEntrant=false;

	return Ret;
}

int		IntegrationBase::GetIntegrationSlaveNoFromMachineCode(int MachineCode)	const
{
	int	Ret=0;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),Ret++){
		if(m->GetMachineCode()==MachineCode){
			return Ret;
		}
	}
	return -1;
}
bool	IntegrationBase::SetCurrentIntoThresholdLevel(int LevelID)
{
	if(ReEntrant==true){
		return true;
	}
	ReEntrant=true;
	bool	Ret=true;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	sNo=m->GetIntegrationSlaveNo();
		IntegrationSetCurrentIntoThresholdLevel	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",sNo);
		Cmd.LevelID	=LevelID;
		if(Cmd.Send(NULL,sNo,0)==false){
			Ret=false;
		}
	}
	ReEntrant=false;

	return Ret;
}

bool	IntegrationBase::HasLocalCamera(void)
{
	if(GetParamIntegrationMaster()->Mastered==false)
		return true;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->GetSlave()->SlaveIsInMaster==true){
			return true;
		}
	}
	return false;
}

bool	IntegrationBase::LoadRelationMaster(int RelationCode)
{
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		m->ClearMaster();
	}
	RelationMasterList MasterListDim[10000];
	int	N=GetLayersBase()->GetDatabaseLoader()->G_SearchMasterCode(*GetLayersBase()->GetDataBase(),RelationCode ,MasterListDim ,sizeof(MasterListDim)/sizeof(MasterListDim[0]));
	for(int n=0;n<N;n++){
		for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(MasterListDim[n].MachineID==m->GetMachineCode()){
				m->LoadMaster(MasterListDim[n].MasterCode);
				break;
			}
		}
	}
	CurrentLotGlobalID=-1;
	return true;
}

bool	IntegrationBase::UpdateLastLoadedTimeMasterRelation(void)
{
	return GetLayersBase()->GetDatabaseLoader()->G_UpdateLastLoadedTimeMasterRelation(*GetLayersBase()->GetDataBase(),GetMasterRelationCode());
}

QString	IntegrationBase::ReplaceImageFile(const QString &ImageFileName,int MachineID)
{
	QStringList	List=ImageFileName.split('/');
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->GetMachineCode()==MachineID){
			if(m->GetSlave()!=NULL){
				int	N=m->GetSlave()->ImageFolders.count();
				for(int i=0;i<N;i++){
					QString	s=m->GetSlave()->ImageFolders[i];
					QString	Ret=s;
					for(int k=0;k<2;k++){
						Ret+=QDir::separator();
						Ret+=List[List.count()-2+k];
					}
					if(QFile::exists(Ret)==true){
						return Ret;
					}
				}
			}
		}
	}
	return ImageFileName;
}

bool	IntegrationBase::IsMastered(void)	const
{
	return GetParamIntegrationMaster()->Mastered;
}

void	IntegrationBase::SetCommonData(IntegrationCommonData &src)
{
	CommonData=src;
}

struct	MergeLotStruct
{
	LotList		*Lot;
	EachMaster	*Master;
};
int	MergeLotStructFunc(const void *a ,const void *b)
{
	struct	MergeLotStruct	*aa=(struct	MergeLotStruct *)a;
	struct	MergeLotStruct	*bb=(struct	MergeLotStruct *)b;
	if(aa->Lot->LotName<bb->Lot->LotName)
		return -1;
	if(aa->Lot->LotName>bb->Lot->LotName)
		return 1;
	int n=aa->Master->GetMachineCode() - bb->Master->GetMachineCode();
	return n;
}

bool	IntegrationBase::LoadLotData(void)
{
	int	AllLotCount=0;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		m->LoadLotList(m->GetMasterCode());
		AllLotCount+=m->GetLotCount();
	}

	if(AllLotCount!=0){
		struct	MergeLotStruct	*Dim=new struct	MergeLotStruct[AllLotCount];
		int	Index=0;
		for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			for(LotList *L=m->GetLotFirst();L!=NULL;L=L->GetNext()){
				Dim[Index].Lot=L;
				Dim[Index].Master	=m;
				Index++;
			}
		}
		qsort(Dim,AllLotCount,sizeof(struct	MergeLotStruct),MergeLotStructFunc);
		int	GlobalID=-1;
		QString	LastLotName;
		for(int i=0;i<AllLotCount;i++){
			if(Dim[i].Lot->LotName!=LastLotName){
				GlobalID++;
				LastLotName=Dim[i].Lot->LotName;
			}
			Dim[i].Lot->GlobalID=GlobalID;
		}
		delete	[]Dim;
	}
	return true;
}

bool	IntegrationBase::SelectLot(int GlobalID)
{
	CurrentLotGlobalID=GlobalID;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		m->ClearCurrentLot();
		for(LotList *L=m->GetLotFirst();L!=NULL;L=L->GetNext()){
			if(L->GlobalID==GlobalID){
				m->LoadLot(L);
				m->SetCurrentLot(L);
			}
		}
	}
	return true;
}
EachMaster	*IntegrationBase::FindMaster(int MachineCode)	const
{
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->GetMachineCode()==MachineCode){
			return m;
		}
	}
	return NULL;
}

int		IntegrationBase::EnumMaster(int MachineCode 
									,EachMaster *Pointer[],int MaxCountOfBuffer)	const
{
	int	n=0;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		if(n>=MaxCountOfBuffer){
			return n;
		}
		if(m->GetMachineCode()==MachineCode){
			Pointer[n]=m;
			n++;
		}
	}
	return n;
}

int		IntegrationBase::EnumMaster(EachMaster *Pointer[],int MaxCountOfBuffer)	const
{
	int	n=0;
	for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		if(n>=MaxCountOfBuffer){
			return n;
		}
		Pointer[n]=m;
		n++;
	}
	return n;
}
QString	IntegrationBase::GetLibraryName(int LibType ,int LibID)
{
	if(GetLayersBase()->GetDatabaseLoader()){
		QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase()
								,LibType,LibID);
		return LibName;
	}
	return /**/"";
}

void	IntegrationBase::SlaveConnected(void)
{
	emit	SignalSlaveConnected();

	bool	ConnectedAll=true;
	IntegrationCommPack		*C=GetLayersBase()->GetIntegrationCommPointer();
	if(C!=NULL){
		int	N=GetIntegrationSlaveCount();
		for(int i=0;i<N;i++){
			IntegrationCommPipe	*s=C->GetSocket(i);
			if(s==NULL || s->IsConnected()==false){
				ConnectedAll=false;
			}
		}
	}
	if(ConnectedAll==true){
		//QElapsedTimer timer;
		//timer.start();
		//
		//while (!timer.hasExpired(5000)){
		//	QCoreApplication::processEvents();
		//}
		GSleep(1000);
		emit	SignalAllSlaveConnected();
	}
}

void	IntegrationBase::SlaveDisconnected(void)
{
	emit	SignalSlaveDisconnected();
}
bool	IntegrationBase::IsConnected(int SlaveNo)	const
{
	IntegrationCommPack		*C=GetLayersBase()->GetIntegrationCommPointer();
	if(GetParamIntegrationMaster()->Mastered==true && C!=NULL){
		int	N=GetIntegrationSlaveCount();
		if(SlaveNo<N){
			IntegrationCommPipe	*s=C->GetSocket(SlaveNo);
			if(s!=NULL && s->IsConnected()==true){
				return true;
			}
			if(IsLocal(SlaveNo)==true){
				return true;
			}
		}
	}
	return false;
}
bool	IntegrationBase::CheckOnProcessing(int SlaveNo)
{
	if(IsConnected(SlaveNo)==true){
		IntegrationReqAlive	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		IntegrationAckAlive	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);

		if(RCmd.Send(SlaveNo,0,ACmd,1000)==true){
			return true;
		}
		QApplication::processEvents();
	}
	return false;
}
bool	IntegrationBase::WaitWhileProcessing(void)
{
	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SlaveNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);
	return true;
}
void	IntegrationBase::BroadcastInspectionDone(int SlaveNo,int64 InspectionID ,bool OK)
{
	EachMaster	*m=GetMaster(SlaveNo);
	if(m!=NULL){
		if(m->GetMasterCode()>0 && m->GetCurrentLot()!=NULL){
			m->AppendSelectLot(m->GetCurrentLot());
			emit	SignalInspectionDone(SlaveNo,InspectionID,OK);
		}
		else{
			m->SetCurrentLot(NULL);
		}
	}
}

void	IntegrationBase::BroadcastScanningDone(int SlaveNo,int64 InspectionID)
{
	EachMaster	*m=GetMaster(SlaveNo);
	if(m!=NULL){
		emit	SignalScanningDone(SlaveNo,InspectionID);
	}
}

void	IntegrationBase::ExecuteInitialAfterEdit(int SlaveNo)
{
	IntegrationExecuteInitialAfterEdit	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
	RCmd.Send(NULL,SlaveNo,0);
}

void	IntegrationBase::ResetTotalResult(void)
{
	TotalCount	=0;
	NGCount		=0;
}
void	IntegrationBase::SlotDoneLoadResult(InspectionList *n)
{
	for(;;){
		int	MinID=99999999;
		EachMaster	*MinM=NULL;
		for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->GetCurrentInspection().ResultCount>m->GetCurrentInspection().CountingPoint){
				int	cID=m->GetCurrentInspection().ResultDim[m->GetCurrentInspection().CountingPoint].InspectionID;
				if(MinID>cID){
					MinID	=cID;
					MinM	=m;
				}
			}
		}
		if(MinM!=NULL){
			bool	NotLoadedInOther=false;
			for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				if(m==MinM){
					continue;
				}
				if(m->GetCurrentInspection().ResultCount<=m->GetCurrentInspection().CountingPoint){
					NotLoadedInOther=true;
					break;
				}
			}
			if(NotLoadedInOther==false){
				TotalCount++;
				bool	NGFlag=false;
				for(EachMaster *m=MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
					if(m->GetCurrentInspection().ResultCount>m->GetCurrentInspection().CountingPoint){
						int	cID=m->GetCurrentInspection().ResultDim[m->GetCurrentInspection().CountingPoint].InspectionID;
						if(MinID==cID){
							if(m->GetCurrentInspection().ResultDim[m->GetCurrentInspection().CountingPoint].Error>1){
								NGFlag=true;
							}
							m->IncCountingPoint();
						}
					}
				}
				if(NGFlag==true){
					NGCount++;
				}
			}
			else{
				break;
			}
		}
		else{
			break;
		}
	}
	emit	SignalDoneLoadResult(n);
}

bool	IntegrationBase::GetInformation( QString &RetRelationNumber
										,QString &RetRelationName
										,QString &RetRemark
										,int &RetRelationType
										,QByteArray &CommonData
										,int32 &ThresholdLevelID)
{
	bool	Ret=GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation
														(*GetLayersBase()->GetDataBase()
														,MasterRelationCode
														,RetRelationNumber
														,RetRelationName
														,RetRemark
														,RetRelationType
														,CommonData
														,ThresholdLevelID);
	return  Ret;
}
void	IntegrationBase::UpdateInspection(void)
{
	LastActionTime=::GetComputerMiliSec();
}
bool	IntegrationBase::NowOnUsing(void)
{
	DWORD	t=::GetComputerMiliSec()-LastActionTime;
	if(t>2000)
		return false;
	return true;
}
