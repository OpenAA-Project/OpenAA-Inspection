/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XPartialImaging.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XPartialImagingResource.h"
#include <QDateTime>
#include "XPartialImaging.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XMainSchemeMemory.h"
#include "XLotInformation.h"
#include "swap.h"
#include "omp.h"

PartialImagingThreshold::PartialImagingThreshold(PartialImagingItem *parent)
:AlgorithmThreshold(parent)
{
	Priority		=0;
	SaveTargetImage	=true;
	SaveOnlyInNG	=false;
	BufferType		=ImageBufferTarget;
}

void	PartialImagingThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const PartialImagingThreshold	*s=dynamic_cast<const PartialImagingThreshold *>(&src);
	if(s!=NULL){
		Priority		=s->Priority;
		SaveTargetImage	=s->SaveTargetImage;
		SaveOnlyInNG	=s->SaveOnlyInNG;
		BufferType		=s->BufferType;
	}
}
bool	PartialImagingThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const PartialImagingThreshold	*s=dynamic_cast<const PartialImagingThreshold *>(&src);
	if(s!=NULL){
		if(Priority			!=s->Priority		)	return false;
		if(SaveTargetImage	!=s->SaveTargetImage)	return false;
		if(SaveOnlyInNG		!=s->SaveOnlyInNG	)	return false;
		if(BufferType		!=s->BufferType		)	return false;
		return true;
	}
	return false;
}
bool	PartialImagingThreshold::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,SaveTargetImage)==false)
		return false;
	if(::Save(f,SaveOnlyInNG)==false)
		return false;	
	if(::Save(f,BufferType)==false)
		return false;	
	
	return(true);
}
bool	PartialImagingThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,SaveTargetImage)==false)
		return false;
	if(::Load(f,SaveOnlyInNG)==false)
		return false;
	if(::Load(f,BufferType)==false)
		return false;	
	return(true);
}

//------------------------------

PartialImagingItem::PartialImagingItem(void)
{	
	AVector		=NULL;
	Buffer		=NULL;
}

PartialImagingItem::~PartialImagingItem(void)
{
}

AlgorithmItemPI	&PartialImagingItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    PartialImagingItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	return true;
}
bool    PartialImagingItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	return true;
}


void	PartialImagingItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	PartialImagingDrawAttr	*a=dynamic_cast<PartialImagingDrawAttr	*>(Attr);
	if(a!=NULL){
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

ExeResult	PartialImagingItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	Buffer=NULL;

	return Ret;
}
ExeResult	PartialImagingItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	const PartialImagingThreshold	*RThr=GetThresholdR();
	if(Buffer!=NULL){
		Buffer->SetPriority(RThr->Priority);
		Buffer->Area=GetArea();

		for(int Layer=0;Layer<Buffer->LayerNumb;Layer++){
			DataInLayer	*DL=GetDataInPage()->GetLayerData(Layer);
			if(RThr->BufferType==ImageBufferMaster && DL->IsMasterBuffEnabled()==true)
				CopyImageData(Buffer->ImageData[Layer],Buffer->AreaByte,DL->GetMasterBuff(),mx,my);
			else if(RThr->BufferType==ImageBufferTarget && DL->IsTargetBuffEnabled()==true)
				CopyImageData(Buffer->ImageData[Layer],Buffer->AreaByte,DL->GetTargetBuff(),mx,my);
			else if(RThr->BufferType==ImageBufferDelayedView && DL->IsDelayedViewBuffEnabled()==true)
				CopyImageData(Buffer->ImageData[Layer],Buffer->AreaByte,DL->GetDelayedViewBuff(),mx,my);
			else if(RThr->BufferType==ImageBufferRawTarget && DL->IsRawTargetBuffEnabled()==true)
				CopyImageData(Buffer->ImageData[Layer],Buffer->AreaByte,DL->GetRawTargetBuff(),mx,my);
			else if(RThr->BufferType==ImageBufferCamTarget && DL->IsCamTargetBuffEnabled()==true)
				CopyImageData(Buffer->ImageData[Layer],Buffer->AreaByte,DL->GetCamTargetBuff(),mx,my);
			else
				Ret=_ER_false;
		}
	}
	return Ret;
}

bool	PartialImagingItem::CopyImageData(BYTE *DataPointer,int DataByte,ImageBuffer &IBuff,int dx,int dy)
{
	BYTE	*p=DataPointer;
	int	N=GetArea().GetFLineLen();
	for(int i=0;i<N;i++){
		int	X1	=GetArea().GetFLineLeftX(i)	+dx;
		int	Numb=GetArea().GetFLineNumb(i)	;
		int	AbsY=GetArea().GetFLineAbsY(i)	+dy;

		if(0<=AbsY && AbsY<GetMaxLines()){
			BYTE	*s=IBuff.GetY(AbsY);
			if(0<=X1){
				if(X1+Numb<GetDotPerLine()){
					if(DataByte>=Numb){
						memcpy(p,&s[X1],Numb);
						p+=Numb;
						DataByte-=Numb;
					}
					else{
						memcpy(p,&s[X1],DataByte);
						return false;
					}
				}
				else if(X1<GetDotPerLine()){
					int	ExLen=X1+Numb-GetDotPerLine();
					if(DataByte>=Numb){
						memcpy(p,&s[X1],Numb-ExLen);
						p+=Numb-ExLen;
						memset(p,0,ExLen);
						p+=ExLen;
						DataByte-=Numb;
					}
					else{
						int	L=min(DataByte,Numb-ExLen);
						memcpy(p,&s[X1],L);
						DataByte-=L;
						memset(p,0,DataByte);
						return false;
					}
				}
				else{
					if(DataByte>=Numb){
						memset(p,0,Numb);
						p+=Numb;
						DataByte-=Numb;
					}
					else{
						memset(p,0,DataByte);
						return false;
					}
				}
			}
			else{
				if(0<=(X1+Numb) && (X1+Numb)<GetDotPerLine()){
					int	PreLen=-X1;
					if(DataByte>=Numb){
						memset(p,0,PreLen);
						p+=PreLen;
						memcpy(p,&s[0],Numb-PreLen);
						p+=Numb-PreLen;
						DataByte-=Numb;
					}
					else{
						int	L=min(DataByte,PreLen);
						memset(p,0,L);
						DataByte-=L;
						p+=L;
						L=min(DataByte,Numb-PreLen);
						memcpy(p,&s[0],L);
						return false;
					}
				}
				else if(GetDotPerLine()<=(X1+Numb)){
					int	PreLen=-X1;
					if(DataByte>=Numb){
						memset(p,0,PreLen);
						p+=PreLen;
						memcpy(p,&s[0],GetDotPerLine());
						p+=GetDotPerLine();
						int	L=Numb-PreLen-GetDotPerLine();
						memset(p,0,L);
						p+=L;
						DataByte-=Numb;
					}
					else{
						int	L=min(DataByte,PreLen);
						memset(p,0,L);
						DataByte-=L;
						p+=L;
						L=min(DataByte,GetDotPerLine());
						memcpy(p,&s[0],L);
						p+=L;
						DataByte-=L;
						L=min(DataByte,Numb-PreLen-GetDotPerLine());
						memset(p,0,L);
						return false;
					}
				}
				else{
					if(DataByte>=Numb){
						memset(p,0,Numb);
						p+=Numb;
						DataByte-=Numb;
					}
					else{
						memset(p,0,DataByte);
						return false;
					}
				}
			}
		}
		else{
			if(DataByte>=Numb){
				memset(p,0,Numb);
				p+=Numb;
				DataByte-=Numb;
			}
			else{
				memset(p,0,DataByte);
				return false;
			}
		}
	}
	return true;
}

//===========================================
WriteBufferInItem::WriteBufferInItem(void)
{
	Priority	=100;
	ItemID		=-1;
	LayerNumb	=0;
	AreaByte	=0;
	ImageData	=NULL;
}

WriteBufferInItem::~WriteBufferInItem(void)
{
	if(ImageData!=NULL){
		for(int Layer=0;Layer<LayerNumb;Layer++){
			delete	[]ImageData[Layer];
		}
		AreaByte=0;
		LayerNumb=0;
		delete	[]ImageData;
		ImageData=NULL;
	}
}

bool	WriteBufferInItem::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,LayerNumb)==false)
		return false;
	if(::Save(f,AreaByte)==false)
		return false;
	
	if(::Save(f,Priority)==false)
		return false;
	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(f->write((const char *)ImageData[Layer],AreaByte)!=AreaByte){
			return false;
		}
	}
	return true;
}
bool	WriteBufferInItem::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false)
		return false;
	int32	iAreaByte;
	if(::Load(f,iAreaByte)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(AreaByte!=iAreaByte || LayerNumb!=iLayerNumb){
		if(ImageData!=NULL){
			for(int Layer=0;Layer<LayerNumb;Layer++){
				delete	[]ImageData[Layer];
			}
			delete	[]ImageData;
			ImageData=NULL;
		}
		LayerNumb	=iLayerNumb;
		AreaByte	=iAreaByte;
		ImageData=new BYTE *[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			ImageData[Layer]=new BYTE[AreaByte];
		}
	}

	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(f->read((char *)ImageData[Layer],AreaByte)!=AreaByte){
			return false;
		}
	}
	return true;
}

void	WriteBufferInItem::Allocate(PartialImagingItem *parent)
{
	if(ImageData!=NULL){
		for(int Layer=0;Layer<LayerNumb;Layer++){
			delete	[]ImageData[Layer];
		}
		AreaByte=0;
		LayerNumb=0;
		delete	[]ImageData;
		ImageData=NULL;
	}
	LayerNumb	=parent->GetLayerNumb();
	AreaByte	=parent->GetArea().GetPatternByte();
	ImageData=new BYTE *[LayerNumb];
	for(int Layer=0;Layer<LayerNumb;Layer++){
		ImageData[Layer]=new BYTE[AreaByte];
	}
}


WriteBufferInPage::WriteBufferInPage(void)
{
	WriteBufferNumb	=0;
	BufferDim		=NULL;
	Empty			=true; 
}
WriteBufferInPage::~WriteBufferInPage(void)
{
	if(BufferDim!=NULL){
		delete	[]BufferDim;
		BufferDim=NULL;
	}
	WriteBufferNumb	=0;
}

bool	WriteBufferInPage::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,WriteBufferNumb)==false)
		return false;
	for(int i=0;i<WriteBufferNumb;i++){
		if(BufferDim[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	WriteBufferInPage::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,InspectionID)==false)
		return false;

	int32	iWriteBufferNumb;
	if(::Load(f,iWriteBufferNumb)==false)
		return false;
	if(iWriteBufferNumb!=WriteBufferNumb){
		delete	[]BufferDim;
		WriteBufferNumb=iWriteBufferNumb;
		BufferDim=new WriteBufferInItem[WriteBufferNumb];
	}
	for(int i=0;i<WriteBufferNumb;i++){
		if(BufferDim[i].Load(f)==false)
			return false;
	}
	return true;
}

bool	WriteBufferInPage::Save(PartialImagingInPage *Parent)
{
	PartialImagingBase	*PBase=(PartialImagingBase *)Parent->GetParentBase();
	QString	FileName=PBase->MakeSavedFileName(MasterCode,LotID,InspectionID,Parent->GetPage());

	QFileInfo	FInfo(FileName);
	QString	Path=FInfo.absolutePath();
	::ForceDirectories(Path);

	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		return Save(&File);
	}
	return false;
}

WriteBufferInItem	*WriteBufferInPage::GetPoint(int ItemID)
{
	for(int i=0;i<WriteBufferNumb;i++){
		if(BufferDim[i].ItemID==ItemID)
			return &BufferDim[i];
	}
	return NULL;
}
void	WriteBufferInPage::Allocate(PartialImagingInPage *parent)
{
	if(BufferDim!=NULL)
		delete	[]BufferDim;
	WriteBufferNumb=parent->GetItemCount();
	BufferDim=new WriteBufferInItem[WriteBufferNumb];
	int	n=0;
	for(AlgorithmItemPI *a=parent->GetFirstData();a!=NULL;a=a->GetNext()){
		BufferDim[n].ItemID		=a->GetID();
		BufferDim[n].ItemName	=a->GetItemName();
		PartialImagingItem	*Item=dynamic_cast<PartialImagingItem *>(a);
		if(Item!=NULL){
			BufferDim[n].Allocate(Item);
		}
	}
}


WriteBufferThread::WriteBufferThread(QObject *parent,PartialImagingInPage *p)
	:QThread(parent),Parent(p)
{
	WriteBufferNumb	=0;
	BuffDim			=NULL;
	Terminated		=false;
}
WriteBufferThread::~WriteBufferThread(void)
{
	if(BuffDim!=NULL){
		delete	[]BuffDim;
		BuffDim=NULL;
	}
	WriteBufferNumb	=0;
}

void	WriteBufferThread::run()
{
	while(Terminated==false){
		WriteBufferInPage	*W=GetWritePoint();
		if(W!=NULL){
			W->Save(Parent);
			SetEmptyFlag(true,W);
			W->Empty=true;
		}
		msleep(50);
	}
}
WriteBufferInPage	*WriteBufferThread::GetWritePoint()
{
	Mutex.lock();
	for(int i=0;i<WriteBufferNumb;i++){
		if(BuffDim[i].Empty==false){
			Mutex.unlock();
			return &BuffDim[i];
		}
	}
	Mutex.unlock();
	return NULL;
}
WriteBufferInPage	*WriteBufferThread::GetBufferStorePoint()
{
	Mutex.lock();
	for(int i=0;i<WriteBufferNumb;i++){
		if(BuffDim[i].Empty==true){
			Mutex.unlock();
			return &BuffDim[i];
		}
	}
	Mutex.unlock();
	return NULL;
}

int	WriteBufferThread::GetStackedCount(void)
{
	int	Count=0;
	Mutex.lock();
	for(int i=0;i<WriteBufferNumb;i++){
		if(BuffDim[i].Empty==false){
			Count++;
		}
	}
	Mutex.unlock();
	return Count;
}
void	WriteBufferThread::SetEmptyFlag(bool flag ,WriteBufferInPage *point)
{
	Mutex.lock();
	point->Empty=flag;
	Mutex.unlock();
}
void	WriteBufferThread::Allocate(void)
{
	if(BuffDim!=NULL){
		delete	[]BuffDim;
	}
	PartialImagingBase	*PBase=(PartialImagingBase *)Parent->GetParentBase();
	Mutex.lock();
	WriteBufferNumb	=PBase->WriteBufferNumb;
	BuffDim=new WriteBufferInPage[WriteBufferNumb];
	for(int i=0;i<WriteBufferNumb;i++){
		BuffDim[i].Allocate(Parent);
	}
	Mutex.unlock();
}

//--------------------------------------------------

PartialImagingInPage::PartialImagingInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
	Thread	= new WriteBufferThread(GetLayersBase()->GetMainWidget(),this);
	Thread->start();
}

PartialImagingInPage::~PartialImagingInPage(void)
{
	Thread->Terminated=true;
	Thread->wait(10000);
	Thread->deleteLater();
	Thread=NULL;
}


void	PartialImagingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaPartialImaging	*AddMArea=dynamic_cast<CmdAddAreaPartialImaging *>(packet);
	if(AddMArea!=NULL){
		PartialImagingItem	*MData=(PartialImagingItem	*)CreateItem(0);
		MData->SetArea(AddMArea->Area);
		MData->SetManualCreated(true);
		MData->SetItemName(AddMArea->ItemName);
		MData->GetThresholdW()->Priority		=AddMArea->Priority;
		MData->GetThresholdW()->SaveTargetImage	=AddMArea->SaveTargetImage;
		MData->GetThresholdW()->SaveOnlyInNG	=AddMArea->SaveOnlyInNG;
		MData->GetThresholdW()->BufferType		=AddMArea->BufferType;
		AppendItem(MData);
		return;
	}
	CmdEditAreaPartialImaging	*EditMArea=dynamic_cast<CmdEditAreaPartialImaging *>(packet);
	if(EditMArea!=NULL){
		FastSearchIDItemStart();
		PartialImagingItem	*MData=(PartialImagingItem *)SearchIDItem(EditMArea->ItemID);
		MData->SetManualCreated(true);
		MData->SetItemName(EditMArea->ItemName);
		MData->GetThresholdW()->Priority		=EditMArea->Priority;
		MData->GetThresholdW()->SaveTargetImage	=EditMArea->SaveTargetImage;
		MData->GetThresholdW()->SaveOnlyInNG	=EditMArea->SaveOnlyInNG;
		MData->GetThresholdW()->BufferType		=EditMArea->BufferType;
		return;
	}
	CmdDeletePartialImaging	*DelMArea=dynamic_cast<CmdDeletePartialImaging *>(packet);
	if(DelMArea!=NULL){
		FastSearchIDItemStart();
		PartialImagingItem	*MData=(PartialImagingItem *)SearchIDItem(DelMArea->ItemID);
		RemoveItem(MData);
		return;
	}
	CmdReqEnumInfo	*CmdReqEnumInfoVar=dynamic_cast<CmdReqEnumInfo *>(packet);
	if(CmdReqEnumInfoVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			PartialImagingItem	*Item=dynamic_cast<PartialImagingItem *>(a);
			if(Item!=NULL){
				PartialImagingInfo	*Info=new PartialImagingInfo();
				const PartialImagingThreshold	*RThr=Item->GetThresholdR(GetLayersBase());

				Info->GlobalPage		=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				Info->x1				=Item->GetArea().GetMinX();
				Info->y1				=Item->GetArea().GetMinY();
				Info->x2				=Item->GetArea().GetMaxX();
				Info->y2				=Item->GetArea().GetMaxY();
				Info->ItemID			=Item->GetID();
				Info->ItemName			=Item->GetItemName();
				Info->Priority			=RThr->Priority;
				Info->SaveTargetImage	=RThr->SaveTargetImage;
				Info->SaveOnlyInNG		=RThr->SaveOnlyInNG;
				Info->BufferType		=RThr->BufferType;
				CmdReqEnumInfoVar->PInfoContainer.AppendList(Info);
			}
		}
		return;
	}
}

ExeResult	PartialImagingInPage::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	while(Thread->GetStackedCount()!=0){
		GSleep(100);
	}
	Thread->Allocate();
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}

ExeResult	PartialImagingInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	WriteBufferInPage	*R=Thread->GetBufferStorePoint();
	if(R!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			PartialImagingItem	*Item=dynamic_cast<PartialImagingItem *>(a);
			if(Item!=NULL){
				WriteBufferInItem	*p=R->GetPoint(a->GetID());
				if(p==NULL)
					break;
				Item->SetBufferPoint(p);
			}
		}
		R->MasterCode	=GetLayersBase()->GetMasterCode();
		R->LotID		=GetLayersBase()->GetLotBase()->GetLotID();
		R->InspectionID	=Res->GetResultInspection()->GetInspectionID();

		ExeResult	Ret=AlgorithmInPagePI::ExecuteProcessing(ExeID ,Res);
		Thread->SetEmptyFlag(false,R);
		return Ret;
	}
	return _ER_false;
}

//===========================================
PartialImagingBase::PartialImagingBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorArea		=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;
	WriteBufferNumb		=32;
	SavedPathFormat		=/**/"\\\\ServerIP\\Data\\FixedImage\\[MachineID]\\yyMMdd-hh";

	SetParam(&ColorArea			, /**/"Color" ,/**/"ColorArea"			,LangSolver.GetString(XPartialImaging_LS,LID_0)/*"Color for area"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XPartialImaging_LS,LID_1)/*"Color for Selected area"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XPartialImaging_LS,LID_2)/*"Color for Active area"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XPartialImaging_LS,LID_3)/*"Color for Transparent display level"*/);
	SetParam(&NegColorArea		, /**/"Color" ,/**/"NegColorArea"		,LangSolver.GetString(XPartialImaging_LS,LID_4)/*"Color for Negative area"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XPartialImaging_LS,LID_5)/*"Color for Negative selected area"*/);
	SetParam(&WriteBufferNumb	, /**/"Setting" ,/**/"WriteBufferNumb"	,LangSolver.GetString(XPartialImaging_LS,LID_6)/*"Buffer count to allocate writing data"*/);
	SetParam(&SavedPathFormat	, /**/"Setting" ,/**/"SavedPathFormat"	,LangSolver.GetString(XPartialImaging_LS,LID_7)/*"Path to save image, [MachineID]"*/);

}

AlgorithmDrawAttr	*PartialImagingBase::CreateDrawAttr(void)
{
	return new PartialImagingDrawAttr();
}

void	PartialImagingBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqBufferedData	*CmdReqBufferedDataVar=dynamic_cast<CmdReqBufferedData *>(packet);
	if(CmdReqBufferedDataVar!=NULL){
		CmdReqBufferedDataVar->PageNumb	=GetPageNumb();
		CmdReqBufferedDataVar->PointDim	=new WriteBufferInPage[GetPageNumb()];
		ResultInspection	*Res=GetLayersBase()->GetCurrentResultForDraw();
		if(Res!=NULL){
			for(int page=0;page<GetPageNumb();page++){

				QString	FileName=MakeSavedFileName(GetLayersBase()->GetMasterCode()
												,GetLayersBase()->GetLotBase()->GetLotID()
												,Res->GetInspectionID()
												,page);
				QFile	File(FileName);
				if(File.open(QIODevice::ReadOnly)==true){
					CmdReqBufferedDataVar->PointDim[page].Load(&File);
				}
			}
		}
		return;
	}
	CmdReleaseBufferedData	*CmdReleaseBufferedDataVar=dynamic_cast<CmdReleaseBufferedData *>(packet);
	if(CmdReleaseBufferedDataVar!=NULL){
		delete	[]CmdReleaseBufferedDataVar->PointDim;
		CmdReleaseBufferedDataVar->PointDim=NULL;
		return;
	}
}

bool	PartialImagingBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
/*
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,GetLayersBase()->GetMainWidget());
	//DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	PartialImagingItem	Item;
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
*/
	return true;
}

QString	ReplaceStr(QString &Src ,const QString &Keyword ,const QString &ReplacedStr)
{
	QString	Ret;
	for(;;){
		int	n=Src.toUpper().indexOf(Keyword);
		if(n>=0){
			Ret+=Src.left(n);
			Ret+=ReplacedStr;
			Src = Src.mid(n+Keyword.length());
		}
		else{
			Ret+=Src;
			break;
		}
	}
	return Ret;
}



QString	PartialImagingBase::MakeSavedFileName(int MasterCode,const QString &LotID,int InspectionID,int page)
{
	QDateTime	TM=QDateTime::currentDateTime();

	QString	Ret=SavedPathFormat;
	Ret=::ReplaceStr(Ret,/**/"[MASTERID]"	,QString::number(MasterCode));
	Ret=::ReplaceStr(Ret,/**/"[MACHINEID]"	,QString::number(GetLayersBase()->GetMachineID()));
	Ret=::ReplaceStr(Ret,/**/"[MASTERCODE]"	,QString::number(MasterCode));
	Ret=::ReplaceStr(Ret,/**/"[LOTID]"		,LotID);
	Ret=::ReplaceStr(Ret,/**/"[DATE]"		,TM.toString(/**/"yyMMdd"));
	Ret=::ReplaceStr(Ret,/**/"[TIME]"		,TM.toString(/**/"hhmmss"));
	Ret=::ReplaceStr(Ret,/**/"[YEAR]"		,TM.toString(/**/"yy"));
	Ret=::ReplaceStr(Ret,/**/"[MONTH]"		,TM.toString(/**/"MM"));
	Ret=::ReplaceStr(Ret,/**/"[DAY]"		,TM.toString(/**/"dd"));
	Ret=::ReplaceStr(Ret,/**/"[HOUR]"		,TM.toString(/**/"hh"));
	Ret=::ReplaceStr(Ret,/**/"[MINUTE]"		,TM.toString(/**/"mm"));
	Ret=::ReplaceStr(Ret,/**/"[SECOND]"		,TM.toString(/**/"ss"));
	Ret=::ReplaceStr(Ret,/**/"[INSPECTIONID]",QString::number(InspectionID));
	Ret+=::GetSeparator();

	Ret+=QString::number(MasterCode)
		+QString(/**/"-")
		+LotID
		+QString(/**/"-")
		+QString::number(InspectionID)
		+QString(/**/"-")
		+QString::number(GetLayersBase()->GetGlobalPageFromLocal(page))
		+QString(/**/".pimg");

	return Ret;
}
